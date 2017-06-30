///////////////////////////////////////////////////////////////////////////////
//
// Simulator.h
//
// TBC
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <netinet/ip.h>
#include <unistd.h>

#include <3waytypes.h>

#include <boost/shared_ptr.hpp>
#include <comms/IPv4Address.h>
#include <comms/UdpSocket.h>
#include <messaging/transport/ApplicationWithMessaging.h>
#include <list>
#include <system/TimerInterface.h>
#include <system/Trace.h>

#include "FreqNTP.h"

void SetFakeDac(u32 dacIn);

class FakeTimer
{
public:
    FakeTimer() :
        m_tSecsToExpire(0), m_tPeriod(0), m_repeat(false), m_handle(0)
    {
    }

    FakeTimer(u32 tSecsToExpire, bool repeat) :
        m_tSecsToExpire(tSecsToExpire), m_tPeriod(tSecsToExpire), m_repeat(repeat), m_handle(m_handleCounter)
    {
        m_handleCounter++;
    }

    void ResetTimer(void) { m_tSecsToExpire = m_tPeriod; }
    u32 GettSecsToExpire() { return m_tSecsToExpire; }
    void SetSecsToExpire(u32 secsToExpire) { m_tSecsToExpire = secsToExpire; }
    threeway::TimerHandle GetHandle() { return m_handle; }
    bool GetRepeat() { return m_repeat; }

    void Display(void)
    {
        TRACE_PRINTF("Handle = %u, Expire = %" PRIu32 ", repeat = %u",(uint32_t)GetHandle(),GettSecsToExpire(),GetRepeat() ? 1 : 0);
    }

private:
    u32 m_tSecsToExpire;
    u32 m_tPeriod;
    bool m_repeat;
    threeway::TimerHandle m_handle;
    static threeway::TimerHandle m_handleCounter;
};

class FakeTimerEngine
{
public:
    FakeTimerEngine() :
        m_appcallback(NULL)
    {
    }

    ~FakeTimerEngine()
    {
        m_timers.clear();
    }

    threeway::TimerHandle InsertTimer(u32 tSecsToExpire, bool repeat);
    void InsertAndSort(FakeTimer& inTimer);
    void SetAppCallback(threeway::ApplicationWithMessaging* appcallback) { m_appcallback = appcallback; }
    bool RunFakeTimer();
    void DisplayTimers();
    void DecrementAllTimers(u32 decAmount);
private:
    threeway::ApplicationWithMessaging* m_appcallback;
    std::list<FakeTimer> m_timers;
};

class FakeDACXtal
{
    static const u32 NLUT_MAX = 20;
    static const u32 DAC_MAX = 0xFFF;
public:
    FakeDACXtal();
    virtual ~FakeDACXtal();
    bool CheckDacLutForMonotonicity(void);
    long double GetFreqGivenDac(u32 DacVal);
    bool ReadDacLut(const char *filename);
    bool Start(const char *filename);
    long double GetDACDrift(void) { return (m_fakeDACDriftppmperday); }

private:

    typedef struct
    {
        u32 DacVal;
        long double Foff;
    } DacLutPoint;

    DacLutPoint Points[NLUT_MAX];
    long double m_fakeDACDriftppmperday;
};

class TimeMachine
{
public:

    enum tSimulatedDistribution
    {
        POISSON,
        LAPLACE,
        ONE_SIDED_LAPLACE,
        ASYMMETRIC_LAPLACE,
        ASYMMETRIC_NORMAL
    };

private:
    static const u32 SECS_PER_DAY = 86400;
    static long double m_StartTime;
    static long double m_AddedTime;
    static long double m_targetFreqOffset;
    static long double m_fakeDACAdjustment;
    static FakeDACXtal m_fakeDACXtal;
    static FakeTimerEngine m_fakeTimerEngine;
    static u32 m_simDuration;
    static bool m_simulatorActive;
    static bool m_simulationFinished;
    static bool m_adjustDAC;
    static u32 m_cmdLineInitialDAC;
    static long double m_delayAsymmetryRatio;
    static tSimulatedDistribution m_simulatedDistribution;
    long double m_serverFreqOffset;
    long double m_serverTimeOffset;
    long double m_timeLastTimeOffsetCalced;
    long double m_jitterUL_mean;
    long double m_jitterUL_SD;
    long double m_jitterUL;
    long double m_jitterDL_mean;
    long double m_jitterDL_SD;
    long double m_jitterDL;
    long double m_delayUL;
    long double m_delayUL_mean;
    long double m_delayUL_SD;
    long double m_delayDL;
    long double m_delayDL_SD;
    long double m_delayDL_mean;
    long double m_processDelay;
    long double m_processDelayJitter;

    NtpPacket *m_pkt;
public:

    TimeMachine();
    static bool InitStatic(long double targetFreqOffset, u32 simDuration);
    void InitNonStatic(long double serverFreqOffset, long double delayUL_mean, long double delayUL_SD, long double delayDL_mean, long double delayDL_SD,
                       long double jitterUL_mean, long double jitterUL_SD, long double jitterDL_mean, long double jitterDL_SD, long double processDelay,
                       long double processDelayJitter);
    bool GetParamsFromFile(const char *FileName);
    static bool IncreaseTargetTime(long double deltaTime);
    static void SetTargetFreqOffset(long double targetFreqOffset) { m_targetFreqOffset = targetFreqOffset; }
    void SetServerFreqOffset(long double serverFreqOffset) { m_serverFreqOffset = serverFreqOffset; }
    static bool SetFakeDac(u32 dacVal);
    static long double GetFakeDacAdjustment(void) { return m_fakeDACAdjustment; }
    static u32 GetSimDuration(void) { return m_simDuration; }
    static void SetSimDuration(u32 simDuration) { m_simDuration = simDuration; }
    static bool GetSimulationFinished(void) { return (m_simulationFinished); }
    static void RewindSim(void);
    //static bool GetSimulatorActive(void) {return m_simulatorActive;}
    static bool GetSimulatorActive(void);
    static void SetSimulatorActive(bool simulatorActive) { m_simulatorActive = simulatorActive; }
    static FakeTimerEngine& GetFakeTimerEngine() { return (m_fakeTimerEngine); }
    long double GetServerTime(void);
    long double GetTimeShift(long double delay, long double jitter);
    void CreateTimeShift(long double delay, long double jitter);
    static void SetAFakeTimer(u32 tSecsToExpire, bool repeat);
    void SendPacketToSim(NtpPacket *pkt);
    void GetPacketFromSim();
    void ProcessPkt();
    void SetLongTermVars();
    long double Poisson(long double m, long double s);
    long double Uniform(long double m, long double s);
    long double AsymmetricNormal(long double m, long double sRhs, long double sLhs);
    long double GeneralisedExtremeValue(long double location, long double scale, long double shape);
    long double Normal(long double m, long double s);
    long double Laplace(long double m, long double s);
    long double AsymmetricLaplace(long double m, long double sRhs, long double sLhs);
    long double OneSidedLaplace(long double m, long double s);
    void SpewDistributions(u32 nSamples, long double m, long double s);
    static void SetAdjustDAC(bool adjustDAC) { m_adjustDAC = adjustDAC; }
    static bool GetAdjustDAC(void) { return m_adjustDAC; }
    static void SetcmdLineInitialDAC(u32 cmdLineInitialDAC) { m_cmdLineInitialDAC = cmdLineInitialDAC; }
    static u32 GetcmdLineInitialDAC(void) { return (m_cmdLineInitialDAC); }

    static void SetdelayAsymmetryRatio(long double delayAsymmetryRatio)
    {
        if (delayAsymmetryRatio > 0.0)
        {
            m_delayAsymmetryRatio = delayAsymmetryRatio;
        }
    }

    static long double GetdelayAsymmetryRatio(void) { return (m_delayAsymmetryRatio); }
    static void SetsimulatedDistribution(tSimulatedDistribution simulatedDistribution) { m_simulatedDistribution = simulatedDistribution; }
    static tSimulatedDistribution GetsimulatedDistribution(void) { return (m_simulatedDistribution); }
    static bool ProcessTargetFile(const char *targetFileName);
};

#endif /*SIMULATOR_H_*/
