///////////////////////////////////////////////////////////////////////////////
//
// FreqNTP.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <algorithm>


#include <system/Trace.h>
#include <system/StringUtils.h>
#include <comms/UdpSocket.h>
#include <comms/TOSValues.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "FNTPTime.h"
#include "FreqNTP.h"
#include "NtpClientApplication.h"

using namespace std;

void FNTPSleep(int sleepTime)
{
    if (TimeMachine::GetSimulatorActive())
    {
        TimeMachine::IncreaseTargetTime((long double) sleepTime);
    }
    else
    {
        sleep(sleepTime); //send NTP packet
    }
}

unsigned long long int FreqNTPServerInterface::m_TimeStart;
long double FreqNTPServerInterface::m_SDSqSum = 0.0;
long double FreqNTPServerInterface::m_inverseSDSum = 0.0;
bool FreqNTPServerInterface::m_firstBurstAcquired = false;
u32 FreqNTPServerInterface::m_numResultsCombined = 0;

FreqNTPServerInterface::FreqNTPServerInterface() :
    m_UnInited(true),
    m_resultValid(false),
    m_ntpRecfd(),
    m_ntpPktReceived(false),
    m_OutFile(NULL),
    m_BurstFile(NULL),
    //m_simulator(),
    m_ULandDLcombinedDeviation(),
    m_nPingTransmitted(0)
{
    InitVars();
}

void FreqNTPServerInterface::InitVars()
{
    m_UnInited = true;
    m_resultValid = false;
    m_OutFile = NULL;
    m_BurstFile = NULL;
    m_ULandDLcombinedDeviation = 0.0;
    m_ntpPktReceived = false;
    m_ntpRecfd = 0;
    m_nPingTransmitted = 0;
}

FreqNTPServerInterface::~FreqNTPServerInterface()
{
    if (m_OutFile != NULL)
    {
        fclose(m_OutFile);
    }

    if (m_BurstFile != NULL)
    {
        fclose(m_BurstFile);
    }
}


void FreqNTPServerInterface::SetIPAddr(const IPv4Address& inremoteIpAddress)
{
    m_serverIPInterface.SetIpAddress(inremoteIpAddress);
}

void FreqNTPServerInterface::PktToMeasPoints(long double weSend, long double weRec, NtpPacket* inPkt, MeasPoint *inUL, MeasPoint *inDL,
                                             MeasPoint *inDelay)
{
    ENTER();
    long double t1, t2, t3, t4;

    t1 = weSend;
    t4 = weRec;
    t2 = inPkt->Gett2();
    t3 = inPkt->Gett3();

    inUL->t = t1;
    inUL->x = (t2 - t1);
    inDL->t = t1;
    inDL->x = (t4 - t3);
    inDelay->t = t1;
    inDelay->x = (t4 - t1) - (t3 - t2);
    EXIT();
}

void FreqNTPServerInterface::PktToMeasPointsRelative(long double tStart,long double weSend, long double weRec, NtpPacket* inPkt, MeasPoint *inUL, MeasPoint *inDL,MeasPoint *inDelay)
{
    long double t1, t2, t3, t4;

    t1 = weSend;
    t4 = weRec;
    t2 = inPkt->Gett2();
    t3 = inPkt->Gett3();

    inUL->t = (t1 - tStart);
    inUL->x = (t2 - t1);
    inDL->t = (t1 - tStart);
    inDL->x = (t4 - t3);
    inDelay->t = (t1 - tStart);
    inDelay->x = (t4 - t1) - (t3 - t2);
}

void FreqNTPServerInterface::BurstsToFile(MeasBurst *inULBurst, MeasBurst *inDLBurst, MeasBurst *inDelayBurst)
{
    ENTER();

    if ((tAppLevelVars::GetDebugLevel()) > 0)
    {
        u32 i;
        for (i = 0; i < (tAppLevelVars::GetNumInBurst()); i++)
        {
            fprintf(m_BurstFile, "%0.10lf\t%0.10lf\t%0.10lf\t%0.10lf\n", (double) inULBurst->m_measPoints[i].t, (double) inULBurst->m_measPoints[i].x,
                    (double) inDLBurst->m_measPoints[i].x, (double) inDelayBurst->m_measPoints[i].x);
        }
        fflush(m_BurstFile);
    }
    EXIT();
}

// discover if the lastBurst is out of range of thisBurst, by seeing if the results are withing the range of
//their standard deviations. If not a step has occured.
bool FreqNTPServerInterface::IsStep(MeasBurst *thisBurst, MeasBurst *lastBurst)
{
    ENTER();

    if ((fabs(thisBurst->m_mean - lastBurst->m_mean)) > (((lastBurst->m_stdDev) + (thisBurst->m_stdDev)) / 2))
    {
        TRACE_PRINTF("Step %0.10lf\t%0.10lf\t%0.10lf\t%0.10lf",(double)thisBurst->m_mean,(double)lastBurst->m_mean,(double)lastBurst->m_stdDev,(double)thisBurst->m_stdDev);
        RETURN(true);
    }
    else RETURN(false);
}

eWhichLinkBad FreqNTPServerInterface::FindBadLinkUsingDelayCorrelation()
{
    eWhichLinkBad retVal;

    if (m_ULBursts.m_xCorrDelay >= m_DLBursts.m_xCorrDelay)
    {
        retVal = UPLINK_BAD;
    }
    else
    {
        retVal = DOWNLINK_BAD;
    }
    RETURN(retVal);
}

void FreqNTPServerInterface::RemoveBadResult()
{
    if (FindBadLinkUsingDelayCorrelation() == UPLINK_BAD)
    {
        TRACE_PRINTF("UL bad");
        m_CULResult.m_valid = false;
    }
    else
    {
        TRACE_PRINTF("DL bad");
        m_CDLResult.m_valid = false;
    }
}

void FreqNTPServerInterface::CompensateBadResult()
{
    long double deltaDelay, deltaUL, deltaDL;

    deltaDelay = (m_delayBursts.m_measPoints[0].x - m_lastDelayBursts.m_measPoints[0].x);
    deltaUL = m_ULBursts.m_measPoints[0].x - m_lastULBursts.m_measPoints[0].x;
    deltaDL = m_DLBursts.m_measPoints[0].x - m_lastDLBursts.m_measPoints[0].x;

    TRACE_PRINTF("dUL = %0.10lf, dDL = %0.10lf,  dD = %0.10lf",(double)deltaUL,(double)deltaDL,(double)deltaDelay);

    if ((fabs(deltaUL - deltaDelay)) < (fabs(deltaDL - deltaDelay)))
    {
        TRACE_PRINTF("UL bad dUL = %0.10lf, dD = %0.10lf, correcting",(double)deltaUL,(double)deltaDelay);
        m_ULBursts.m_measPoints[0].x -= deltaDelay;
        m_CULResult.create(m_ULBursts, m_lastULBursts);
        m_ULBursts.m_measPoints[0].x += deltaDelay;
        m_CULResult.Display();
    }
    else
    {
        TRACE_PRINTF("DL bad dDL = %0.10lf, dD = %0.10lf, correcting",(double)deltaDL,(double)deltaDelay);
        m_DLBursts.m_measPoints[0].x -= deltaDelay;
        m_CDLResult.create(m_DLBursts, m_lastDLBursts);
        m_DLBursts.m_measPoints[0].x += deltaDelay;
        m_CDLResult.Display();
    }
}

void FreqNTPServerInterface::HandleUdpRx(s32 fd)
{
    ENTER();
    //TRACE_PRINTF("FreqNTPServerInterface::HandleUdpRx Recieved from ntp");
    m_ntpPktReceived = true;
    m_ntpRecfd = fd;
    EXIT();
}


bool FreqNTPServerInterface::FNTPBurstGet(u32 numInBurst, struct timeval *tv)
{
    ENTER();
    RSYS_ASSERT(numInBurst > 0);
    RSYS_ASSERT(tv != NULL);
    long double weSend, weRec;
    u32 numPacketsCorrectlyReceived = 0;
    NtpPacket pkt;
    s32 retries = BURST_GET_MAX_RETRIES;
    bool retVal;

    if (m_serverIPInterface.ReopenSocketIfChanged() == false)
    {
        // Failed to create the UDP socket for sending stuff, let's bail out of here
        return false;
    }

    TRACE_PRINTF("Starting burst of %" PRIu32 " ",(u32)numInBurst);

    //keep going until we have a successful result of we have run out of retries
    while ((numPacketsCorrectlyReceived < numInBurst) && (retries >= 0))
    {
        //construct various elements of NTP packet required.
        pkt.InitNow();

        if(m_serverIPInterface.SendGetNTPPacket(&pkt,&weSend,&weRec) != SERVER_IP_ERROR_NONE)
        {
            FNTPSleep(SECS_RETRY_SEND_REC);
            retries--;
        }
        else
        {
            //reset the retry mechanism
            retries = BURST_GET_MAX_RETRIES;

            if(!(pkt.CheckStratumCorrect()))
            {
                TRACE_PRINTF("WARNING: Stratum of NTP server %s is substandard",GetIPAddr().ToString());
            }

            //convert the NTP packet into useful data
            PktToMeasPoints(weSend, weRec, &pkt, &(m_ULBursts.m_measPoints[numPacketsCorrectlyReceived]), &(m_DLBursts.m_measPoints[numPacketsCorrectlyReceived]), &(m_delayBursts.m_measPoints[numPacketsCorrectlyReceived]));

            numPacketsCorrectlyReceived++;
            //PrintPacket(&pkt);
            if (numInBurst > 1)
            {
                FNTPSleep(SECS_BETWEEN_READINGS);
            }
        }
    }

    //if retries is 0 then we have a problem else note the last actual time (used in syncs)
    if (((int) retries) > 0)
    {
        tv->tv_sec = ntohl((pkt.GetNTPData())->transmit_timestamp_secs) - NTP_EPOCH;
        tv->tv_usec = ntohl((pkt.GetNTPData())->transmit_timestamp_frac) / 4295;
        retVal = true;
    }
    else
    {
        //if we have run out of retries then the server is denoted inactive
        retVal = false;
    }

return retVal;
}

MeasPoint FreqNTPServerInterface::ExtractMinimumFromDataSet(std::vector<MeasPoint> & dataPoints,u32 start,u32 finish)
{
    u32 minIndex = start;
    for(u32 i = start;i <= finish;i++)
    {
        if(dataPoints[i].x < dataPoints[minIndex].x)
        {
            minIndex = i;
        }
    }
    return dataPoints[minIndex];
}

bool FreqNTPServerInterface::ExtractMinimaFromData(u32 divisor,std::vector<MeasPoint> & dataPoints,std::vector<MeasPoint> &minima)
{
    u32 numPoints = dataPoints.size();
    u32 start,end;
    MeasPoint ourMP;

        u32 interval = numPoints / divisor;
        minima.clear();
        TRACE_PRINTF ("Minima extraction divisor = %d",divisor);
        for(start = 0,end = interval;end <= numPoints;start += interval,end += interval)
        {
            ourMP = ExtractMinimumFromDataSet(dataPoints,start,end);
            minima.push_back(ourMP);
            //TRACE_PRINTF ("Minimum found t = %0.10lf,x = %0.10lf",((double)(ourMP.t)),((double)(ourMP.x)));
        }
return true;
}

long double FreqNTPServerInterface::LeastSquaresFitLineToMinima(std::vector<MeasPoint> &minima)
{
   long double SUMx, SUMy, SUMxy, SUMxx, SUMres, res, slope,
           y_intercept, y_estimate ;
    u32 i,n;
    n = minima.size();

    long double x,y;
    SUMx = 0; SUMy = 0; SUMxy = 0; SUMxx = 0;
    for (i=0; i<n; i++)
    {
      x = minima[i].t;
      y = minima[i].x;
      SUMx = SUMx + x;
      SUMy = SUMy + y;
      SUMxy = SUMxy + x*y;
      SUMxx = SUMxx + x*x;
    }
    slope = ( SUMx*SUMy - n*SUMxy ) / ( SUMx*SUMx - n*SUMxx );
    y_intercept = ( SUMy - slope*SUMx ) / n;

    TRACE_PRINTF ("The linear equation that best fits the given data:");
    TRACE_PRINTF ("       y = %6.10lfx + %6.10lf", (double)slope, (double)y_intercept);
    TRACE_PRINTF ("--------------------------------------------------");
    TRACE_PRINTF ("   Original (x,y)     Estimated y     Residual");
    TRACE_PRINTF ("--------------------------------------------------");

    SUMres = 0;
    for (i=0; i<n; i++)
    {
      x = minima[i].t;
      y = minima[i].x;
      y_estimate = slope*x + y_intercept;
      res = y - y_estimate;
      SUMres = SUMres + res*res;
      TRACE_PRINTF ("   (%6.10lf %6.10lf)      %6.10lf       %6.10lf",
              (double)x, (double)y, (double)y_estimate,(double) res);
    }
    TRACE_PRINTF("--------------------------------------------------");
    TRACE_PRINTF("Residual sum = %6.10lf", (double)SUMres);

    return slope;
}

long double FreqNTPServerInterface::GetBestLineFitToData(std::vector<MeasPoint> & dataPoints)
{
    u32 numPoints = dataPoints.size();
    u32 divisor;
    std::vector<MeasPoint> minima;
    for(divisor = 2;divisor < numPoints;divisor <<= 1)
    {
        ExtractMinimaFromData(divisor,dataPoints,minima);
        long double lineFit = LeastSquaresFitLineToMinima(minima);
        TRACE_PRINTF("Line fit to data, nPoints = %d, divisor = %d, fit = %0.10lf",numPoints,divisor,(double)lineFit);
        TRACE_PRINTF("Minima = ");
        DisplayVector(minima);
    }
    return 0.0;
}

void FreqNTPServerInterface::DisplayVector(std::vector<MeasPoint> & dataPoints)
{
    for(u32 i = 0;i < (dataPoints.size());i++)
    {
        TRACE_PRINTF(" %0.10lf %0.10lf", (double)dataPoints[i].t,(double)dataPoints[i].x);
    }
}

long double FreqNTPServerInterface::SuperFastConverganceBurst(u32 maxNumInBurst)
{
    ENTER();
    RSYS_ASSERT(maxNumInBurst > 0);
    long double weSend, weRec,timeStart;
    u32 numPacketsCorrectlyReceived = 0;
    NtpPacket pkt;
    s32 retries = BURST_GET_MAX_RETRIES;
    long double retVal = 0.0;

    //FNTPSleep(100);

    std::vector<MeasPoint> ulPoints;
    std::vector<MeasPoint>::iterator ulIter;
    std::vector<MeasPoint> dlPoints;
    std::vector<MeasPoint>::iterator dlIter;
    std::vector<MeasPoint> delayPoints;
    std::vector<MeasPoint>::iterator delayIter;

    if (m_serverIPInterface.ReopenSocketIfChanged() == false)
    {
        // Failed to create the UDP socket for sending stuff, let's bail out of here
        return -1;
    }


    timeStart = GetLDTime();
    ulPoints.resize(1000);
    dlPoints.resize(1000);
    delayPoints.resize(1000);

    //keep going until we have a successful result of we have run out of retries
    while ((numPacketsCorrectlyReceived < maxNumInBurst) && (retries >= 0))
    {
        //construct various elements of NTP packet required.
        pkt.InitNow();

        //weSend = GetLDTime(); //get and note send time

        if(m_serverIPInterface.SendGetNTPPacket(&pkt,&weSend,&weRec) != SERVER_IP_ERROR_NONE)
        {
            FNTPSleep(SECS_RETRY_SEND_REC);
            retries--;
        }
        else
        {
            //get and record the time of reception of the packet
            //weRec = GetLDTime();
            //reset the retry mechanism
            retries = BURST_GET_MAX_RETRIES;

            //convert the NTP packet into useful data

            MeasPoint ulPoint;
            MeasPoint dlPoint;
            MeasPoint delayPoint;
            PktToMeasPointsRelative(timeStart,weSend, weRec, &pkt, &ulPoint, &dlPoint, &delayPoint);
            /*ulPoints.push_back(ulPoint);
            dlPoints.push_back(dlPoint);
            delayPoints.push_back(delayPoint);*/
            ulPoints[numPacketsCorrectlyReceived] = ulPoint;
            dlPoints[numPacketsCorrectlyReceived] = dlPoint;
            delayPoints[numPacketsCorrectlyReceived] = delayPoint;

            if(numPacketsCorrectlyReceived == 600)
            {
                TRACE_PRINTF ("Fitting uplink uplink data = ");
                DisplayVector(ulPoints);
                //GetBestLineFitToData(ulPoints);
                TRACE_PRINTF ("Fitting downlink downlink data = ");
                //DisplayVector(dlPoints);
                //GetBestLineFitToData(dlPoints);
                //TRACE_PRINTF ("Displaying delay data = ");
                //DisplayVector(delayPoints);
                return true;
            }

            numPacketsCorrectlyReceived++;
            //PrintPacket(&pkt);
            if (maxNumInBurst > 1)
            {
                FNTPSleep(SECS_BETWEEN_READINGS);
            }
        }
    }

    //if retries is 0 then we have a problem else note the last actual time (used in syncs)
    if (((int) retries) > 0)
    {

    }
    else
    {
        //if we have run out of retries then the server is denoted inactive

    }

return retVal;
}

bool FreqNTPServerInterface::DoABurst(void)
{
    ENTER();
    struct timeval tv;
    static unsigned long long int timeNow;
    bool step;
    bool retVal = true;

    if (TimeMachine::GetSimulatorActive())
    {
        //m_simulator.SetLongTermVars();
    }

    if ((FNTPBurstGet((tAppLevelVars::GetNumInBurst()), &tv)) == false)
    {
        TRACE_PRINTF("Burst get failed");
        SetResultValid(false);
        retVal = false;
    }
    else
    {
        m_firstBurstAcquired = true; //indicate a burst (any bust ) has been successfully got
        m_ULBursts.CalcxCorr(&m_delayBursts, (tAppLevelVars::GetNumInBurst()));
        m_DLBursts.CalcxCorr(&m_delayBursts, (tAppLevelVars::GetNumInBurst()));
        TRACE_PRINTF("UL xcorr = %0.10Lf, DL xcorr = %0.10Lf",
                m_ULBursts.m_xCorrDelay, m_DLBursts.m_xCorrDelay);

        m_ULBursts.Sort();
        m_DLBursts.Sort();
        m_delayBursts.Sort();
        BurstsToFile(&m_ULBursts, &m_DLBursts, &m_delayBursts);

        u32 sdLen = tAppLevelVars::GetsdCalcLength();
        TRACE_PRINTF("sdlen = %d",((int)sdLen));

        TRACE_PRINTF("UPLINK");
        m_ULBursts.CalcStdDev(sdLen);
        TRACE_PRINTF("DOWNLINK");
        m_DLBursts.CalcStdDev(sdLen);
        TRACE_PRINTF("DELAY");
        m_delayBursts.CalcStdDev(sdLen);

        //round trip delay is too great, don't process
        if ((m_delayBursts.m_mean) < (tAppLevelVars::GetdelayIgnoreThreshold()))
        {
            if((m_delayBursts.m_stdDev) < DELAY_SD_IGNORE_THRESHOLD)
            {
                TRACE_PRINTF("DBSD is OK %0.10Lf",(m_delayBursts.m_stdDev));
                //we need to have collected two bursts separated in time to get a valid value of freq drift so do not try to process if we have not

                CalcULandDLCombinedDeviation();

                if (m_UnInited)
                {
                    SetResultValid(false); //denote the result is invalid
                    m_UnInited = false; // we'll have a frequency drift estimate next time
                    retVal = false;
                }
                else
                {
                    //create the frequency drift estimates from the UL and DL
                    m_CULResult.create(m_ULBursts, m_lastULBursts);
                    m_CULResult.m_valid = true;
                    TRACE_PRINTF("Uplink.");
                    m_CULResult.Display();
                    m_CDLResult.create(m_DLBursts, m_lastDLBursts);
                    m_CDLResult.m_valid = true;
                    m_CDLResult.Invert(); //note invert to preserve sign (with a +ve frequency drift the UL will increase & the DL will decrease)
                    TRACE_PRINTF("Downlink.");
                    m_CDLResult.Display();

                    //m_burstCollection.CalcAndDisplay();
                    //if a step change in round trip delay has occurred, ascertain whether the UL or DL is
                    //responsible and remove it.
                    if (IsStep(&m_delayBursts, &m_lastDelayBursts))
                    {
                        TRACE_PRINTF("DelayStep");
                        if ((tAppLevelVars::GetCorrectStepChangeResult()))
                        {
                            CompensateBadResult();
                        }
                        else
                        {
                            RemoveBadResult();
                        }
                        step = true;
                    }
                    else
                    {
                        step = false;
                    }

                    //combine the UL and DL result to get an overall result
                    m_CResult.combine(m_CULResult, m_CDLResult);
                    TRACE_PRINTF("Combined based on m_uncertainty.");
                    m_CResult.Display();

                    if ((fabs(m_CResult.m_ppm)) > (tAppLevelVars::GetMassiveStep())) //result is too huge to be real..
                    {
                        long double timedifful, timediffdl;
                        timedifful = ((m_ULBursts.m_measPoints[0].t) - (m_lastULBursts.m_measPoints[0].t));
                        timediffdl = ((m_DLBursts.m_measPoints[0].t) - (m_lastDLBursts.m_measPoints[0].t));
                        TRACE_PRINTF("Massive step! UL dt = %0.10lf\t DL dt = %0.10lf",(double)timedifful,(double)timediffdl);
                        SetResultValid(false);
                        retVal = false;
                        m_UnInited = true;
                    }
                    else
                    {
                        SetResultValid(true);

                        timeNow = (unsigned long long int) (m_ULBursts.m_measPoints[0].t);

                        if ((tAppLevelVars::GetDebugLevel()) > 0)
                        {
                            fprintf(m_OutFile, "%d\t%0.10lf\t%0.10lf\t%0.10lf\t%0.10lf\t%0.10lf\t%d\t%0.10lf\t%0.10lf\t%d\n", (int) (timeNow - m_TimeStart),
                                    (double) m_CULResult.m_ppm, (double) m_CDLResult.m_ppm, (double) m_CULResult.m_uncertainty,
                                    (double) m_CDLResult.m_uncertainty, (double) m_delayBursts.m_stdDev, (int) step, (double) m_delayBursts.m_mean,
                                    (double) (m_CResult.m_ppm), m_resultValid);
                            fflush(m_OutFile);
                        }

                        TRACE_PRINTF("Time = %d",(unsigned int)(timeNow - m_TimeStart));
                        m_CResult.Display();
                    }
                }
                // swap the current bursts into the last bursts ready for the next bursts
                m_lastULBursts = m_ULBursts;
                m_lastDLBursts = m_DLBursts;
                m_lastDelayBursts = m_delayBursts;
            }
            else
            {
                TRACE_PRINTF("Burst delay SD is too great and will be skipped DBSD = %0.10Lf",(m_delayBursts.m_stdDev));
                fflush(stdout);
                SetResultValid(false);
                retVal = false;
            }
        }
        else
        {
            TRACE_PRINTF("Burst delay is too great and will be skipped delay = %0.10Lf",(m_delayBursts.m_mean));
            fflush(stdout);
            SetResultValid(false);
            retVal = false;
        }
    }
    RETURN(retVal);
}

bool FreqNTPServerInterface::OpenFiles(char *inBurstFileName, char *inOutputFileName)
{
    ENTER();
    bool retVal;
    if ((m_BurstFile = fopen(inBurstFileName, "w")) == NULL)
    {
        TRACE_PRINTF("Error opening Burst file");
        retVal = false;
    }
    else
    {
        if ((m_OutFile = fopen(inOutputFileName, "w")) == NULL)
        {
            TRACE_PRINTF("Error opening output file %s", inOutputFileName);
            retVal = false;
        }
        else
        {
            if ((tAppLevelVars::GetDebugLevel()) > 0)
            {
                fprintf(m_OutFile, "t\tUL\tDL\tULuns\tDLuns\tDBSD\tstep\tDelay\tSDest\tValid?\n");
                fflush(m_OutFile);
            }
            retVal = true;
        }
    }

    RETURN(retVal);
}

//gets a single NTP packet and sets the system time according to it. Also serves as an alive test, i.e to check if the server is responding after it was deemed unresponsive
bool FreqNTPServerInterface::SyncTime(long double* burstDelay)
{
    bool retVal = false;
    ENTER();
    struct timeval tv;

    if (FNTPBurstGet(1, &tv) == true)
    {
        settimeofday(&tv, NULL); //set the absolute time
        *burstDelay = m_delayBursts.m_measPoints[0].x; //get the roundtrip delay, so as to ascertain which is the best server
        TRACE_PRINTF("Time synced = %d:%d",(int)tv.tv_sec,(int)tv.tv_usec);

        //m_UnInited = true; //once we have changed the local time our last burst measurements become invalid so we must go through the init process again - suhas
        retVal = true;
    }

    //SuperFastConverganceBurst(1500);

    RETURN(retVal);
}

bool FreqNTPServerInterface::GetInited()
{
    return (!m_UnInited);
}

bool FreqNTPServerInterface::GetResultValid()
{
    return (m_resultValid);
}

void FreqNTPServerInterface::SetResultValid(bool inVal)
{
    m_resultValid = inVal;
    m_CResult.m_valid = inVal;
    if (inVal)
    {
        m_CResult.m_clustered = false;
    }
}

ComboResult& FreqNTPServerInterface::GetCResult()
{
    return (m_CResult);
}

void FreqNTPServerInterface::SetServerUnInited()
{
    m_UnInited = true;
}

bool FreqNTPServerInterface::GetServerValid()
{
    return m_serverIPInterface.GetServerValid();
}

bool FreqNTPServerInterface::GetServerInactive()
{
    return m_serverIPInterface.GetServerInactive();
    //return (m_serverInactive);
}

void FreqNTPServerInterface::InitTime()
{
    m_TimeStart = (unsigned long long int) GetLDTime();
}

void FreqNTPServerInterface::CalcULandDLCombinedDeviation()
{
    long double sqSum;
    //long double denom;

    /*denom =  (1 / m_ULBursts.m_stdDev)  + (1 / m_DLBursts.m_stdDev);


     m_ULandDLcombinedDeviation =  1 / denom;
     m_reciprocalSDSum += denom;*/

    sqSum = ldSquare(m_ULBursts.m_stdDev) + ldSquare(m_DLBursts.m_stdDev);
    TRACE_PRINTF("sqSum = %0.20Lf",sqSum);
    m_ULandDLcombinedDeviation = sqrt((sqSum / 2.0));
    TRACE_PRINTF("m_ULandDLcombinedDeviation = %0.20Lf",m_ULandDLcombinedDeviation);
    m_SDSqSum += sqSum;
    m_numResultsCombined++;
    m_inverseSDSum += (1 / (sqrt((sqSum / (m_numResultsCombined * 2)))));
}

long double FreqNTPServerInterface::GetCombinedSds()
{
    ENTER();

    long double combinedDev;

    TRACE_PRINTF("m_SDSqSum no. 2 = %0.20Lf, m_numResultsCombined = %" PRIu32, m_SDSqSum, m_numResultsCombined);
    combinedDev = (sqrt((m_SDSqSum) / (m_numResultsCombined * 2)));
    TRACE_PRINTF("Overall combined Deviation of %" PRIu32 " results = %0.20Lf", m_numResultsCombined, combinedDev);
    ResetSDSum();

    RETURN(combinedDev);
}

long double FreqNTPServerInterface::GetCombinedInverseSumSds()
{
    ENTER();

    long double retVal;

    retVal = 1 / m_inverseSDSum;

    TRACE_PRINTF("1 / m_inverseSDSum = %0.10Lf", retVal);
    ResetInverseSDSum();

    RETURN(retVal);
}
