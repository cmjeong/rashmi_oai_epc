///////////////////////////////////////////////////////////////////////////////
//
// Simulator.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <system/Trace.h>
#include <comms/UdpSocket.h>
#include <system/TimerEngine.h>

#include "FNTPTime.h"
#include "FreqNTP.h"
#include "Simulator.h"

void SetFakeDac(u32 dacIn)
{
    TimeMachine::SetFakeDac(dacIn);
}

//#############################################################################################
bool operator<(FakeTimer& a, FakeTimer& b)
{
    ENTER();
    u32 secsa = a.GettSecsToExpire();
    u32 secsb = b.GettSecsToExpire();
    //bool retVal = (a.GettSecsToExpire()) < (b.GettSecsToExpire());
    return ((secsa < secsb));
    EXIT();
}

threeway::TimerHandle FakeTimer::m_handleCounter = 1;

void FakeTimerEngine::InsertAndSort(FakeTimer& inTimer)
{
    m_timers.push_back(inTimer);
    m_timers.sort();
}

threeway::TimerHandle FakeTimerEngine::InsertTimer(u32 tSecsToExpire, bool repeat)
{
    FakeTimer tempTimer(tSecsToExpire, repeat);
    threeway::TimerHandle retHandle = tempTimer.GetHandle();
    TRACE_PRINTF("Insert timer handle = %" PRIu32, tempTimer.GetHandle());
    InsertAndSort(tempTimer);
    return (retHandle);
}

bool FakeTimerEngine::RunFakeTimer()
{
    bool retVal = true;
    if (!(m_timers.empty()))
    {
        FakeTimer tempTimer = m_timers.front();
        //TRACE_PRINTF("Front timer");
        //tempTimer.Display();
        m_timers.pop_front();

        if (m_appcallback != NULL)
        {
            retVal = TimeMachine::IncreaseTargetTime(tempTimer.GettSecsToExpire());
            DecrementAllTimers(tempTimer.GettSecsToExpire());
            m_appcallback->NotifyTimerExpiry(tempTimer.GetHandle());

            if (tempTimer.GetRepeat())
            {
                //TRACE_PRINTF("Reinserting..");
                //tempTimer.Display();
                //DisplayTimers();
                tempTimer.ResetTimer();
                InsertAndSort(tempTimer);
            }
        }
        else
        {
            TRACE_PRINTF("Fake time engine m_appcallback not set");
            retVal = false;
        }
    }
    return retVal;
}

void FakeTimerEngine::DecrementAllTimers(u32 decAmount)
{
    std::list<FakeTimer>::iterator iter;
    u32 tSecs;
    for (iter = m_timers.begin(); iter != m_timers.end(); iter++)
    {
        tSecs = iter->GettSecsToExpire();
        iter->SetSecsToExpire((tSecs - decAmount));
    }
}

void FakeTimerEngine::DisplayTimers()
{
    std::list<FakeTimer>::iterator iter;
    for (iter = m_timers.begin(); iter != m_timers.end(); iter++)
    {
        iter->Display();
    }
}

//#############################################################################################
long double TimeMachine::m_StartTime = 0.0;
long double TimeMachine::m_AddedTime = 0.0;
long double TimeMachine::m_targetFreqOffset = 0.0;
long double TimeMachine::m_fakeDACAdjustment = 0.0;
FakeTimerEngine TimeMachine::m_fakeTimerEngine;
u32 TimeMachine::m_simDuration = 10000;
FakeDACXtal TimeMachine::m_fakeDACXtal;
bool TimeMachine::m_simulatorActive = false;
bool TimeMachine::m_simulationFinished = false;
bool TimeMachine::m_adjustDAC = true;
u32 TimeMachine::m_cmdLineInitialDAC = 0;
long double TimeMachine::m_delayAsymmetryRatio = 3.0;
TimeMachine::tSimulatedDistribution TimeMachine::m_simulatedDistribution = ASYMMETRIC_NORMAL;

TimeMachine::TimeMachine() :
    m_serverFreqOffset(0.0),
    m_serverTimeOffset(0.0),
    m_timeLastTimeOffsetCalced(0.0),
    m_jitterUL_mean(0.0),
    m_jitterUL_SD(0.0),
    m_jitterUL(0.0),
    m_jitterDL_mean(0.0),
    m_jitterDL_SD(0.0),
    m_jitterDL(0.0),
    m_delayUL(0.0),
    m_delayUL_mean(0.0),
    m_delayUL_SD(0.0),
    m_delayDL(0.0),
    m_delayDL_SD(0.0),
    m_delayDL_mean(0.0),
    m_processDelay(0.0),
    m_processDelayJitter(0.0),
    m_pkt()
{

}

bool TimeMachine::GetSimulatorActive(void)
{
    return m_simulatorActive;
}

bool TimeMachine::InitStatic(long double targetFreqOffset, u32 simDuration)
{
    bool initResult;
    m_targetFreqOffset = targetFreqOffset;
    m_simDuration = simDuration;
    m_StartTime = GetLDTime();
    m_AddedTime = 0.0;
    m_fakeDACAdjustment = 0.0;
    m_adjustDAC = true;
    if (ProcessTargetFile("/mnt/dbx/SimTargetFile") == false)
    {
        initResult = false;
    }
    else
    {
        if (m_fakeDACXtal.Start("/mnt/dbx/SimDacLut") == false)
        {
            initResult = false;
        }
        else
        {
            initResult = true;
        }
    }
    return (initResult);
}

bool TimeMachine::IncreaseTargetTime(long double deltaTime)
{
    bool retVal;
    struct timeval tv, dT;
    gettimeofday(&tv, NULL); //get the time
    dT = LDtotv(deltaTime);
    timevaladd(&tv, &dT); //add on the required offset to the time
    //TRACE_PRINTF("m_AddedTime = %d m_simDuration = %d delta = %0.10lf",((u32)m_AddedTime),m_simDuration,deltaTime);
    m_AddedTime += deltaTime; //add it on to m_AddedTime so that changes can be rewound once we stop the sim
    if (((u32) m_AddedTime) > m_simDuration)
    {
        TRACE_PRINTF("m_AddedTime = %" PRIu32 " m_simDuration = %" PRIu32 " delta = %0.10Lf",
                ((u32)m_AddedTime), m_simDuration, deltaTime);
        m_simulationFinished = true;
        m_simulatorActive = false;
        retVal = false;
    }
    else
    {
        settimeofday(&tv, NULL); //set the absolute time
        retVal = true;
    }
    return retVal;
}

void TimeMachine::InitNonStatic(long double serverFreqOffset, long double delayUL_mean, long double delayUL_SD, long double delayDL_mean,
                                long double delayDL_SD, long double jitterUL_mean, long double jitterUL_SD, long double jitterDL_mean, long double jitterDL_SD,
                                long double processDelay, long double processDelayJitter)
{
    m_serverFreqOffset = serverFreqOffset;
    m_delayUL_mean = delayUL_mean;
    m_delayUL_SD = delayUL_SD;
    m_delayDL_mean = delayDL_mean;
    m_delayDL_SD = delayDL_SD;
    m_jitterUL_mean = jitterUL_mean;
    m_jitterUL_SD = jitterUL_SD;
    m_jitterDL_mean = jitterDL_mean;
    m_jitterDL_SD = jitterDL_SD;
    m_processDelay = processDelay;
    m_processDelayJitter = processDelayJitter;
    m_serverTimeOffset = 0.0;
    m_timeLastTimeOffsetCalced = GetLDTime();
}

bool TimeMachine::GetParamsFromFile(const char *FileName)
{
    FILE *fp = NULL;
    bool RetVal;

    fp = fopen(FileName, "r");

    if (fp != NULL)
    {
        TRACE_PRINTF("Sim file opened OK");
        fscanf(fp, "%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf", &m_serverFreqOffset, &m_delayUL_mean, &m_delayUL_SD, &m_delayDL_mean, &m_delayDL_SD, &m_jitterUL_mean,
               &m_jitterUL_SD, &m_jitterDL_mean, &m_jitterDL_SD, &m_processDelay, &m_processDelayJitter);
        m_timeLastTimeOffsetCalced = GetLDTime();
        RetVal = true;
        fclose(fp);
    }
    else
    {
        //only report a file opening error if it is not a 'file does not exist' error. ENOENT in errno.h
        if (errno != ENOENT)
        {
            TRACE_PRINTF("Sim file not opened name = %s errno = %d errname = %s",FileName,errno,strerror(errno));
        }

        RetVal = false;
    }
    return RetVal;
}

long double TimeMachine::GetServerTime(void)
{
    long double timeNow;
    long double diffTime;
    long double returnTime;

    timeNow = GetLDTime();
    diffTime = timeNow - m_timeLastTimeOffsetCalced;
    m_timeLastTimeOffsetCalced = timeNow;

    long double num, den;
    num = ((m_fakeDACXtal.GetDACDrift()) * diffTime);
    den = ((((long double) SECS_PER_DAY) * 1000000));
    m_targetFreqOffset += num / den;
    //m_targetFreqOffset += (((m_fakeDACXtal.GetDACDrift()) * diffTime) / ((long double)(SECS_PER_DAY * 1000000)));
    // m_targetFreqOffset += ((m_fakeDACXtal.GetDACDrift()) * diffTime) / ((long double)(SECS_PER_DAY));
    //TRACE_PRINTF("**********num = %0.10lf, den = % 0.10lf target Freq offset = %0.10lf",num,den,m_targetFreqOffset);

    m_serverTimeOffset += (diffTime * (m_serverFreqOffset - (m_targetFreqOffset + m_fakeDACAdjustment)));

    returnTime = timeNow + m_serverTimeOffset;
    return returnTime;
}

long double TimeMachine::GetTimeShift(long double delay, long double jitter)
{
    long double timeShiftinS = 0.0;
    switch (m_simulatedDistribution)
    {
    case POISSON:
    {
        timeShiftinS = Poisson(delay, jitter);
    }
        break;
    case LAPLACE:
    {
        timeShiftinS = Laplace(delay, jitter);
    }
        break;
    case ONE_SIDED_LAPLACE:
    {
        timeShiftinS = OneSidedLaplace(delay, jitter);
    }
        break;
    case ASYMMETRIC_LAPLACE:
    {
        timeShiftinS = AsymmetricLaplace(delay, jitter, (jitter / m_delayAsymmetryRatio));
    }
        break;
    case ASYMMETRIC_NORMAL:
    {
        timeShiftinS = AsymmetricNormal(delay, jitter, (jitter / m_delayAsymmetryRatio));
    }
        break;
    default:
    {
        timeShiftinS = 0.0;
        break;
    }
    }
    return (timeShiftinS);
}

void TimeMachine::CreateTimeShift(long double delay, long double jitter)
{
    IncreaseTargetTime((GetTimeShift(delay, jitter)));
}

void TimeMachine::SetAFakeTimer(u32 tSecsToExpire, bool repeat)
{

}

void TimeMachine::SendPacketToSim(NtpPacket *pkt)
{
    m_pkt = pkt;
}

void TimeMachine::GetPacketFromSim()
{
    ProcessPkt();
}

void TimeMachine::ProcessPkt()
{
    unsigned long int secs, frac;
    long double serverTime;

    m_pkt->GetNTPData()->stratum = 1; //All FNTP servers are stratum 1. Could be in the fake server config file if required to be other
    //test KOD functionality
    //m_pkt->stratum = 0;
    //memcpy(&(m_pkt->reference_identifier),"arse",4);
    CreateTimeShift(m_delayUL, m_jitterUL);
    serverTime = GetServerTime();
    LongDoubletoNTP(serverTime, &secs, &frac);
    m_pkt->GetNTPData()->receive_timestamp_secs = secs;
    m_pkt->GetNTPData()->receive_timestamp_frac = frac;

    CreateTimeShift(m_processDelay, m_processDelayJitter);
    serverTime = GetServerTime();
    LongDoubletoNTP(serverTime, &secs, &frac);
    m_pkt->GetNTPData()->transmit_timestamp_secs = secs;
    m_pkt->GetNTPData()->transmit_timestamp_frac = frac;

    CreateTimeShift(m_delayDL, m_jitterDL);
}

void TimeMachine::RewindSim(void)
{
    long double timeNow;
    struct timeval tv;

    timeNow = GetLDTime();
    TRACE_PRINTF("added = %0.10Lf now = %0.10Lf",m_AddedTime,timeNow);
    timeNow -= m_AddedTime;
    TRACE_PRINTF("added = %0.10Lf now = %0.10Lf",m_AddedTime,timeNow);
    tv = LDtotvAbs(timeNow);
    TRACE_PRINTF("tv secs = %ld", tv.tv_sec);
    settimeofday(&tv, NULL);
}

long double TimeMachine::AsymmetricLaplace(long double m, long double sRhs, long double sLhs)
{
    long double retVal;
    long double norm;

    norm = Uniform(0, 1.0);
    if (norm > 0)
    {
        retVal = m - ((sRhs * (log(1.0 - (2.0 * ldModulus(norm))))));
    }
    else
    {
        retVal = m + ((sLhs * (log(1.0 - (2.0 * ldModulus(norm))))));
    }
    return (retVal);
}

long double TimeMachine::OneSidedLaplace(long double m, long double s)
{
    long double retVal;
    long double norm;

    norm = Uniform(0, 1.0);
    retVal = m - ((s * (log(1.0 - (2.0 * ldModulus(norm))))));
    return (retVal);
}
long double TimeMachine::Laplace(long double m, long double s)
{
    long double retVal;
    long double norm;

    norm = Uniform(0, 1.0);
    retVal = m - (s * (ldSign(norm)) * (log(1.0 - (2.0 * ldModulus(norm)))));

    return (retVal);
}

long double TimeMachine::Poisson(long double m,/* fixed propagation delay (s) */long double s/* exponential parameter (mu) */)
{
    double q1;

    /*
     * Roll a sample from a composite distribution with propagation
     * delay m and exponential distribution time with parameter s.
     * For m = 0, s = 1, mean(y) = std(y) = 1.
     */
    if (s == 0)
    {
        return (m);
    }

    while ((q1 = drand48()) == 0);

    return (m - s * log(q1 * s));
}

long double TimeMachine::Uniform(long double m, long double s)
{
    return ((m + ((s * ldrand()) - (s / 2))));
}

long double TimeMachine::AsymmetricNormal(long double m, long double sRhs, long double sLhs)
{
    long double retAsymmetricNormal;
    long double lhsDist;
    long double rhsDist;
    long double selector;

    lhsDist = Normal(m, sLhs);
    rhsDist = Normal(m, sRhs);
    selector = ldrand();

    if (selector >= 0.5)
    {
        retAsymmetricNormal = m + ldModulus(m - rhsDist);
    }
    else
    {
        retAsymmetricNormal = m - ldModulus(m - lhsDist);
    }

    return (retAsymmetricNormal);
}

long double TimeMachine::GeneralisedExtremeValue(long double location, long double scale, long double shape)
{
    long double x;
    long double selector;
    long double probatx;
    long double z;
    u32 rejectCount = 0;

    do
    {
        x = Uniform(location, (10 * scale));
        selector = ldrand();
        z = (x - location) / scale;
        probatx = ((1.0 / scale) * (pow((1.0 + (shape * z)), (-1.0 / (shape - 1.0))))) * exp(-(pow(((1.0 + (shape * z))), (-1.0 / shape))));
        TRACE_PRINTF("z = %0.10Lf,x =  %0.10Lf, probatx = %0.10Lf",z,x,probatx);
        rejectCount++;
    } while (selector > probatx);

    TRACE_PRINTF("Reject count = %" PRIu32, rejectCount);

    return (x);
}

long double TimeMachine::Normal(long double m, long double s)
{
    static int iset = 0;
    static long double gset;
    long double fac, rsq, v1, v2;
    long double RetVal;
    //We don’t have an extra deviate handy, so
    if (iset == 0)
    {
        do
        {
            //pick two uniform numbers in the square ex-
            v1 = 2.0 * ldrand() - 1.0;
            //tending from -1 to +1 in each direction,
            v2 = 2.0 * ldrand() - 1.0;
            //see if they are in the unit circle,
            rsq = v1 * v1 + v2 * v2;
            //and if they are not, try again.
        } while (rsq >= 1.0 || rsq == 0.0);
        fac = sqrt(-2.0 * log(rsq) / rsq);

        /*Now make the Box-Muller transformation to get two normal deviates. Return one and
         save the other for next time.*/

        gset = v1 * fac;
        //Set ﬂag.
        iset = 1;
        RetVal = v2 * fac;
        //We have an extra deviate handy,
    }
    else
    {
        //so unset the ﬂag,
        iset = 0;
        //and return it.
        RetVal = gset;
    }
    return ((RetVal * s) + m);
}

void TimeMachine::SetLongTermVars()
{
    /*m_delayUL = Uniform(m_delayUL_mean,m_delayUL_SD);
     m_delayDL = Uniform(m_delayDL_mean,m_delayDL_SD);
     m_jitterUL = Uniform(m_jitterUL_mean,m_jitterUL_SD);
     m_jitterDL = Uniform(m_jitterDL_mean,m_jitterDL_SD);*/

    m_delayUL = Normal(m_delayUL_mean, m_delayUL_SD);
    m_delayDL = Normal(m_delayDL_mean, m_delayDL_SD);
    m_jitterUL = Normal(m_jitterUL_mean, m_jitterUL_SD);
    m_jitterDL = Normal(m_jitterDL_mean, m_jitterDL_SD);
}

bool TimeMachine::SetFakeDac(u32 dacVal)
{
    //TODO simulate drift
    TRACE_PRINTF("m_fakeDACAdjustment (outside) = %" PRIu32 " m_adjustDAC = %d", dacVal, m_adjustDAC?1:0);
    if (m_adjustDAC)
    {
        m_fakeDACAdjustment = m_fakeDACXtal.GetFreqGivenDac(dacVal);
        TRACE_PRINTF("dacVal = %" PRIu32 " m_fakeDACAdjustment = %0.10Lf", dacVal, m_fakeDACAdjustment);
    }
    return true;
}

void TimeMachine::SpewDistributions(u32 nSamples, long double m, long double s)
{
    FILE* calPtsFile;
    long double randNumber;
    long double normalNumber;
    long double ldRandNumber;

    if ((calPtsFile = fopen("/mnt/dbx/disribSpew", "w")) == NULL)
    {
        TRACE_PRINTF("Error opening disribSpew");
    }
    else
    {
        for (u32 i = 0; i < nSamples; i++)
        {
            ldRandNumber = ldrand();
            randNumber = Laplace(m, s);
            normalNumber = Uniform(0, 1);
            fprintf(calPtsFile, "%0.10Lf\t%0.10Lf\t%0.10Lf\n", randNumber, normalNumber, ldRandNumber);
        }
        fclose(calPtsFile);
    }
}

bool TimeMachine::ProcessTargetFile(const char *targetFileName)
{
    FILE *targetFP = NULL;
    bool RetVal;

    targetFP = fopen(targetFileName, "r");

    if (targetFP != NULL)
    {
        TRACE_PRINTF("Sim file opened OK");
        int simulatedDistribution;
        fscanf(targetFP, "%Lf%Lf%d", &m_targetFreqOffset, &m_delayAsymmetryRatio, &simulatedDistribution);
        m_simulatedDistribution = (TimeMachine::tSimulatedDistribution) simulatedDistribution;
        RetVal = true;
        fclose(targetFP);
    }
    else
    {
        TRACE_PRINTF("Sim target file not opened name = %s errno = %d errname = %s",targetFileName,errno,strerror(errno));
        RetVal = false;
    }
    return RetVal;
}

//###############################################################################################################################

FakeDACXtal::FakeDACXtal() :
    m_fakeDACDriftppmperday(0.0)
{
    for (u32 i = 0; i < NLUT_MAX; i++)
    {
        Points[i].DacVal = 0;
        Points[i].Foff = 0.0;
    }
}

FakeDACXtal::~FakeDACXtal()
{

}

//ensure that the look up table is monotonic i.e. each point is larger than the rest.
bool FakeDACXtal::CheckDacLutForMonotonicity(void)
{
    u32 i;
    for (i = 0; i < (NLUT_MAX - 1); i++)
    {
        if (Points[i + 1].Foff < Points[i].Foff)
        {
            return false;
        }
    }
    return true;
}

long double FakeDACXtal::GetFreqGivenDac(u32 DacVal)
{
    u32 i = 0;
    long double RetFreq = 0.0;

    //find the first point in the DAC look up table that is higher than the input value
    while (i < NLUT_MAX)
    {
        if (Points[i].DacVal > DacVal)
        {
            break;
        }
        else
        {
            i++;
        }
    }

    if ((i >= NLUT_MAX) || (i == 0))
    {
        //fallen off table
        TRACE_PRINTF("DAC interpolation failed at DAC = %04X. Required DAC value is not within the table's bounds",(int)DacVal);
        RetFreq = 0;
    }
    else
    {
        //special case where DacVal matches one of the points on the table
        if (Points[i].DacVal == DacVal)
        {
            RetFreq = Points[i].Foff;
            TRACE_PRINTF("here i = %" PRIu32, i);
        }
        else
        {
            //do the calculation, interpolating between the point we are at and the previous point.
            RetFreq = Points[i - 1].Foff + ((((long double) (DacVal - Points[i - 1].DacVal)) / ((long double) (Points[i].DacVal - Points[i - 1].DacVal))) * (Points[i].Foff - Points[i - 1].Foff));
            TRACE_PRINTF("*** Dac Freq calc in = %d point = %d, point + 1 = %d, fpoint = %0.10lf, fpoint + 1 = %0.10lf, Calced f = %0.10lf\n",
                    (int)DacVal, (int)Points[i-1].DacVal, (int)Points[i].DacVal, (double)(Points[i-1].Foff), (double)Points[i].Foff,(double)RetFreq);
        }
    }
    return RetFreq;
}

//read the look up table from file filename. return true is this is successful, false if else
bool FakeDACXtal::ReadDacLut(const char *filename)
{
    FILE *fp = NULL;
    double frequencyPPM;
    int dacValue;
    bool RetVal;
    u32 nlut;

    fp = fopen(filename, "r");

    if (fp != NULL)
    {
        for (nlut = 0; nlut < NLUT_MAX; nlut++)
        {
            fscanf(fp, "%d%lf", &dacValue, &frequencyPPM);
            Points[nlut].DacVal = dacValue;
            Points[nlut].Foff = 1.0e-6 * frequencyPPM;
            TRACE_PRINTF("dac lut points dac = %d, off = %0.10lf", dacValue, frequencyPPM);
            if (feof(fp))
                break;
        }

        if (nlut < NLUT_MAX)
        {
            RetVal = false;
            TRACE_PRINTF_LEV(TRACE_WARNING, "Error reading DAC LUT file (not enough points in file)\n");
        }
        else
        {
#ifdef DAC_DEBUG

            TRACE_PRINTF ("*** %d values read from LUT\n", (int)nlut);
            for (nlut=0; nlut<NLUT_MAX; nlut++)
            {
                TRACE_PRINTF ("*** %10d%0.10lf\n", (int)Points[nlut].DacVal,(double)Points[nlut].Foff);
            }
#endif
            fscanf(fp, "%Lf", &m_fakeDACDriftppmperday);
            TRACE_PRINTF("Drift rate read as %0.10Lf ppm per day",m_fakeDACDriftppmperday);
            RetVal = true;
        }
        fclose(fp);
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "Error reading DAC LUT file (could not open file name %s)\n",filename);
        RetVal = false;
    }
    return RetVal;
}

bool FakeDACXtal::Start(const char *FileName)
{
    bool RetVal;

    TRACE_PRINTF("FakeDACXtal::Start");
    if (ReadDacLut(FileName) == false)
    {
        RetVal = false;
    }
    else
    {
        if (CheckDacLutForMonotonicity() == false)
        {
            TRACE_PRINTF_LEV(TRACE_WARNING, "DAC look up table in fake DACXtal not monotonic\n");
            RetVal = false;
        }
        else
        {
            RetVal = true;
        }
    }
    return RetVal;
}

