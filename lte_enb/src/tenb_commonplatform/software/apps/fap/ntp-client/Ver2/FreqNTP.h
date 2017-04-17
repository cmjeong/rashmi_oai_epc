///////////////////////////////////////////////////////////////////////////////
//
// FreqNTP.h
//
// Send and receive UDP packets.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FreqNTP_h_
#define __FreqNTP_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <vector>

#include <3waytypes.h>

#include <boost/shared_ptr.hpp>
#include <comms/IPv4Address.h>
#include <comms/UdpSocket.h>

//#include "Simulator.h"

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "FNTPTime.h"
#include "NTPPacket.h"
#include "ServerIPInterface.h"
#include "FNTPDataTypes.h"
#include "AppLevelVars.h"

//namespace threeway
//{
///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

void FNTPSleep(int sleepTime);

typedef enum
{
    UPLINK_BAD,
    DOWNLINK_BAD,
} eWhichLinkBad;

//interface to an NTP server. There is an instance of FreqNTPServerInterface declared for every NTP server we use.
class FreqNTPServerInterface: public threeway::UdpRxInterface /* interface */
{
    //consts
    static const u32 NTP_PORT = 123;
    static const u32 NTP_REPLY_TIMEOUT = 6;
    static const u32 LOG_AUX = 0;
    static const long double DELAY_SD_IGNORE_THRESHOLD = 0.1;
    static const u32 SECS_RETRY_SEND_REC = 10;
    static const u32 SECS_BETWEEN_READINGS = 1;
    static const u32 BURST_GET_MAX_RETRIES = 2;
    static const u32 MAX_DUP_CHK = (8 * 128);

public:

    //the start time (secs since 1970)
    static unsigned long long int m_TimeStart;

private:

    //the main result of all our measurements
    ComboResult m_CResult;

    //the MeasBurst structs where the bursts are recorded and used for calculation.
    MeasBurst m_ULBursts;
    MeasBurst m_DLBursts;
    MeasBurst m_delayBursts;
    MeasBurst m_lastULBursts;
    MeasBurst m_lastDLBursts;
    MeasBurst m_lastDelayBursts;

    //shared pointer to the dynamically created UdpSocket that is opened on the NTP server for the NTP packet sending and receiving

    s32 m_ntpRecfd;
    bool m_ntpPktReceived;

    //file pointers for (mostly) debug files
    FILE *m_OutFile;
    FILE *m_BurstFile;

    //Uplink result
    FreqResult m_CULResult;
    //downlink result
    FreqResult m_CDLResult;

    //various flags:
    //is the overall result of the server valid for whatever reason?
    bool m_resultValid;
    //denotes the fact that the initial burst has not been obtained
    bool m_UnInited;
    //TimeMachine m_simulator;
    long double m_ULandDLcombinedDeviation;
    static long double m_SDSqSum;
    static long double m_inverseSDSum;
    static u32 m_numResultsCombined;
    static bool m_firstBurstAcquired;
    u32 m_nPingTransmitted;
    ServerIPInterface m_serverIPInterface;
public:
    //constructors
    FreqNTPServerInterface();
    ~FreqNTPServerInterface();
    void InitVars();
    //Initters
    //accessors
    void SetServerUnInited();
    bool GetServerValid();
    bool GetInited();
    bool GetResultValid();
    void SetResultValid(bool inVal);
    bool GetServerInactive();
    ComboResult& GetCResult();
    IPv4Address& GetIPAddr() { return m_serverIPInterface.GetIPAddr(); }
    void SetIPAddr(const IPv4Address& inremoteIpAddress);
    long double GetULandDLCombinedDeviation() { return (m_ULandDLcombinedDeviation); }
    static long double GetCombinedSds();
    static long double GetCombinedInverseSumSds();
    static bool GetfirstBurstAcquired() { return (m_firstBurstAcquired); }
    static void SetLocalIPAddress(const IPv4Address localIpAddress) {ServerIPInterface::SetIPSecFGWAddress(localIpAddress);}

    // Implementation of UdpRxInterface.
    void HandleUdpRx(s32 fd);
    //open all the files relevant to the server, i.e. the Burst File and the Output File
    bool OpenFiles(char *InBurstFileName, char *inOutputFileName);
    //go and get a burst from the server and process
    bool DoABurst(void);
    //get a load of data for stat analysis
    //void GetStatBurst();
    //do a set time single burst.
    bool SyncTime(long double* burstDelay);
    //initialise the internal start time to now
    static void InitTime();
private:
    //convert the NTP packet (along with records of the sent and received time) into MeasPoints
    void PktToMeasPoints(long double weSend, long double weRec, NtpPacket* inPkt, MeasPoint *inUL, MeasPoint *inDL, MeasPoint *inDelay);
    void PktToMeasPointsRelative(long double tStart,long double weSend, long double weRec, NtpPacket* inPkt, MeasPoint *inUL, MeasPoint *inDL,MeasPoint *inDelay);
    //output all the bursts to the burst file for debugging purposes
    void BurstsToFile(MeasBurst *inULBurst, MeasBurst *inDLBurst, MeasBurst *inDelayBurst);
    //determine if a step has occured between thisBurst and lastBurst
    bool IsStep(MeasBurst *thisBurst, MeasBurst *lastBurst);
    //Get a burst of NTP packets from the server
    bool FNTPBurstGet(u32 numInBurst, struct timeval *tv);
    MeasPoint ExtractMinimumFromDataSet(std::vector<MeasPoint> & dataPoints,u32 start,u32 finish);
    bool ExtractMinimaFromData(u32 divisor,std::vector<MeasPoint> & dataPoints,std::vector<MeasPoint> &minima);
    long double LeastSquaresFitLineToMinima(std::vector<MeasPoint> &minima);
    long double GetBestLineFitToData(std::vector<MeasPoint> & dataPoints);
    void DisplayVector(std::vector<MeasPoint> & dataPoints);
    long double SuperFastConverganceBurst(u32 maxNumInBurst);
    //remove either the UL or DL result based on the UL or DL change relative to the change in round trip delay
    void RemoveBadResult();
    //attempt to remove error by removing the step in round trip delay from the afflicted leg
    void CompensateBadResult();
    /**
     *send out NTP packet to outside, or to the simulator
     */
    //int SendNTPPacket(NtpPacket* pkt, u32 pktSize);
    //Get NTP packet from the outside, or the simulator
    //int GetNTPPacketWithTimeout(NtpPacket* pkt, u32 pktSize);
    void CalcULandDLCombinedDeviation();
    static void ResetSDSum()
    {
        m_SDSqSum = 0.0;
        m_numResultsCombined = 0;
    }
    static void ResetInverseSDSum()
    {
        m_inverseSDSum = 0.0;
        m_numResultsCombined = 0;
    }
    eWhichLinkBad FindBadLinkUsingDelayCorrelation();
};
//}

#endif
