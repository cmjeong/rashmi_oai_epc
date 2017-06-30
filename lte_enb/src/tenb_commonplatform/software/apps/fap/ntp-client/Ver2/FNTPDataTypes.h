#ifndef FNTPDATATYPES_H_
#define FNTPDATATYPES_H_
///////////////////////////////////////////////////////////////////////////////
//
// FNTPDataTypes.h
//
// Types, structs and classes to handle FNTP data
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

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

//#include "Simulator.h"
//#include "FNTPTime.h"
#include "NTPPacket.h"

#include "FreqNTP.h"
#include "ServerIPInterface.h"
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


class MeasPoint
{
public:
    //time at which the measurement was taken
    long double t;
    //value of the measurement
    long double x;
};

class MeasBurst
{
public:
    MeasBurst();
    MeasBurst(const MeasBurst& copyRHS);
    ~MeasBurst();
    //floor of the value m_stdDev to avoid div by zeros
    MeasBurst& operator=(const MeasBurst& rhs);
    static const long double SD_MIN = 0.000000001;
    MeasPoint *m_measPoints;
    long double m_stdDev;
    long double m_mean;
    long double m_xCorrDelay;
    bool m_sorted;
    //sort the burst so that they are sorted by x, lowest first (element [0])
    void Sort(void);
    //calc mean (average) of the burst
    void CalcMean(u32 inLim);
    /*
     * Calculate the correlation between xCorrBurst and the roundtrip delay burst
     */
    void CalcxCorr(MeasBurst *xCorrBurst, u32 numInBurst);
    //calculate the standard deviation of the burst
    void CalcStdDev(u32 inLim);
    //output the burst to stdio
    void Display();
};

//Frequency mesurement result. This is a result of 2 bursts,
//yeilding a measurement of time offset drift rate and the uncertainty therof
class FreqResult
{

public:
    //factor to convert PPU (parts per unit) to PPM (parts per million)
    static const long double PPU_TO_PPM = 1000000;

    FreqResult();
    ~FreqResult();
    //Instantiate using the 2 burst measurements
    void create(MeasBurst& inThisMeasBurst, MeasBurst& inLastMeasBurst);
    //change sign of the offset (m_ppm)
    void Invert();
    //display the internals
    void Display();
    //display (with a label)
    void Display(const char* label);
    //check to see if we are in range of another FreqResult
    bool InRange(FreqResult& inFRes);
    //used in clustering to set the
    void CombineMaxMin(FreqResult& inFRes);
    //clear the data
    void Reset(void)
    {
        m_ppm = 0;
        m_uncertainty = 0;
        m_valid = false;
    }
    //frequency drift in s/s
    long double m_ppm;
    //uncertainty of the above
    long double m_uncertainty;
    //is the result valid?
    bool m_valid;
    //have we been included in a cluster?
    bool m_clustered;
private:
};

class ComboResult: public FreqResult
{
    static const u32 SECS_PER_DAY = 86400;//1 day

public:
    ComboResult();
    virtual ~ComboResult();
    ComboResult& operator=(const FreqResult& inFres);
    //combine an array of FreqResults size nRes
    void combine(ComboResult inResults[], u32 nRes);
    //combine 2 freq results
    void combine(FreqResult inResult1, FreqResult inResult2);
    //combine one FreqResult + this
    void combine(ComboResult& inResult);
    //see documentation for this
    void DriftCalc(unsigned long long int t1, unsigned long long int t2, ComboResult& last);
private:
};

class ComboResultFilter: public ComboResult
{
public:
    ComboResultFilter();
    ~ComboResultFilter();
    bool Init(u32 inNumPoints);
    void Add(ComboResult& inCRes);
    void Reset();
    s32 GetResultppb() { return ((s32) (m_ppm * 1000000000)); }

private:
    // Ensure objects of this type can't be copied.
    ComboResultFilter(const ComboResultFilter&);
    ComboResultFilter& operator=(const ComboResultFilter&);

    ComboResult *m_filterPoints;
    u32 m_count;
    u32 m_numPoints;
};
//}

#endif /* FNTPDATATYPES_H_ */
