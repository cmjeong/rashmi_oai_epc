/*
 * FNTPDataTypes.cpp
 *
 *  Created on: 10-Sep-2009
 *      Author: jouroussoff
 */
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
#include "AppLevelVars.h"
#include "FreqNTP.h"
#include "FNTPDataTypes.h"
//using namespace std;



//#############################################################################################
//< operator required by sort for MeasBurst. Note not a member of MeasBurst as such
bool operator<(const MeasPoint& a, const MeasPoint& b)
{
    ENTER();
    return (a.x < b.x);
    EXIT();
}


MeasBurst operator-(const MeasBurst& lhArg, const MeasBurst& rhArg)
{
    ENTER();
    MeasBurst retVal;
    u32 i;
    for (i = 0; i < (tAppLevelVars::GetNumInBurst()); i++)
    {
        retVal.m_measPoints[i].x = lhArg.m_measPoints[i].x - rhArg.m_measPoints[i].x;
        retVal.m_measPoints[i].t = lhArg.m_measPoints[i].t;
    }

    RETURN(retVal);
}

MeasBurst::MeasBurst()
{
    m_stdDev = 0.0;
    m_mean = 0.0;
    m_xCorrDelay = 0.0;
    m_sorted = false;
    m_measPoints = new MeasPoint[(tAppLevelVars::GetNumInBurst())];
    RSYS_ASSERT(m_measPoints != NULL);
}

MeasBurst::MeasBurst(const MeasBurst& copyRHS)
{
    ENTER();
    RSYS_ASSERT(copyRHS.m_measPoints != NULL);
    m_measPoints = new MeasPoint[(tAppLevelVars::GetNumInBurst())];
    RSYS_ASSERT(m_measPoints != NULL);

    m_sorted = copyRHS.m_sorted;
    m_stdDev = copyRHS.m_stdDev;
    m_mean = copyRHS.m_mean;
    m_xCorrDelay = copyRHS.m_xCorrDelay;

    u32 i;
    for (i = 0; i < (tAppLevelVars::GetNumInBurst()); i++)
    {
        m_measPoints[i] = copyRHS.m_measPoints[i];
    }
}

MeasBurst::~MeasBurst()
{
    if (m_measPoints != NULL)
    {
        delete[] m_measPoints;
        m_measPoints = NULL;
    }
}

MeasBurst& MeasBurst::operator=(const MeasBurst& rhs)
{
    ENTER();

    // Check for self-assignment!
    if (this == &rhs)
    {
        RETURN(*this);
    }

    m_stdDev = rhs.m_stdDev;
    m_mean = rhs.m_mean;
    m_xCorrDelay = rhs.m_xCorrDelay;
    m_sorted = rhs.m_sorted;

    u32 i;
    RSYS_ASSERT(rhs.m_measPoints != NULL);
    RSYS_ASSERT(m_measPoints != NULL);
    for (i = 0; i < (tAppLevelVars::GetNumInBurst()); i++)
    {
        m_measPoints[i] = rhs.m_measPoints[i];
    }

    RETURN(*this);
}

//sort a burst. Uses std::sort
void MeasBurst::Sort(void)
{
    ENTER();
    std::sort(m_measPoints, (m_measPoints + (tAppLevelVars::GetNumInBurst())));
    //sort(m_measPoints, (m_measPoints + (tAppLevelVars::GetNumInBurst())));
    EXIT();
}

void MeasBurst::CalcMean(u32 inLim)
{
    ENTER();
    long double sum = 0;
    u32 i;
    for (i = 0; i < inLim; i++)
    {
        sum += m_measPoints[i].x;
    }
    sum /= inLim;
    m_mean = sum;
    EXIT();
}

void MeasBurst::CalcxCorr(MeasBurst *xCorrBurst, u32 numInBurst)
{
    ENTER();
    u32 i;
    long double sx, sy, sxy, denom;

    CalcMean(numInBurst);
    xCorrBurst->CalcMean(numInBurst);

    sx = 0;
    sy = 0;
    for (i = 0; i < numInBurst; i++)
    {
        sx += ldSquare(m_measPoints[i].x - m_mean);
        sy += ldSquare(xCorrBurst->m_measPoints[i].x - xCorrBurst->m_mean);
    }
    denom = sqrt(sx * sy);

    sxy = 0;
    for (i = 0; i < numInBurst; i++)
    {
        sxy += (m_measPoints[i].x - m_mean) * (xCorrBurst->m_measPoints[i].x - xCorrBurst->m_mean);
    }
    m_xCorrDelay = sxy / denom;
    EXIT();
}

void MeasBurst::CalcStdDev(u32 inLim)
{
    ENTER();
    u32 i;
    long double variance = 0;
    long double diff;

    if (inLim > (tAppLevelVars::GetNumInBurst()))
    {
        inLim = (tAppLevelVars::GetNumInBurst());
    }

    CalcMean(inLim); //first calculate the mean of the burst

    //calculate the variance
    for (i = 0; i < inLim; i++)
    {
        diff = m_mean - m_measPoints[i].x;
        variance += ldSquare(diff);
    }
    variance /= inLim;

    //SD is square root of variance
    m_stdDev = sqrt(variance);

    TRACE_PRINTF("SD = %0.10Lf", m_stdDev);

    //implement a lower floor if we have a SD of zero
    if (m_stdDev == 0.0)
    {
        m_stdDev = SD_MIN;
        TRACE_PRINTF("SD = 0.0 detected");
    }
    EXIT();
}

void MeasBurst::Display()
{
    ENTER();
    u32 i;
    for (i = 0; i < (tAppLevelVars::GetNumInBurst()); i++)
    {
        TRACE_PRINTF("%" PRIu32 " %0.10Lf %0.10Lf",i,m_measPoints[i].x,m_measPoints[i].t);
    }
    EXIT();
}

//#############################################################################################

FreqResult::FreqResult() :
    m_valid(false),
    m_ppm(0.0),
    m_uncertainty(0.0),
    m_clustered(false)
{

}

FreqResult::~FreqResult()
{

}

//create a FreqResult from 2 (must be sorted) MeasBursts
void FreqResult::create(MeasBurst& inThisMeasBurst, MeasBurst& inLastMeasBurst)
{
    long double dt;
    MeasPoint thisMeasPoint = inThisMeasBurst.m_measPoints[0];
    MeasPoint lastMeasPoint = inLastMeasBurst.m_measPoints[0];

    // inThisMeasBurst.Display();
    //inLastMeasBurst.Display();

    dt = (thisMeasPoint.t - lastMeasPoint.t);
    m_ppm = ((thisMeasPoint.x - lastMeasPoint.x) / dt);
    //m_uncertainty = (sqrt((ldSquare(inThisMeasBurst.m_stdDev)) + (ldSquare(inLastMeasBurst.m_stdDev)))) / dt;
    m_uncertainty = ((inThisMeasBurst.m_stdDev) + (inLastMeasBurst.m_stdDev)) / dt;
}

void FreqResult::Display()
{
    TRACE_PRINTF("m_ppm = %0.10lf, m_uncertainty = %0.10lf, m_valid = %d",(double)(m_ppm * PPU_TO_PPM),(double)(m_uncertainty * PPU_TO_PPM),m_valid);
}

void FreqResult::Display(const char* label)
{
    TRACE_PRINTF("%s m_ppm = %0.10lf, m_uncertainty = %0.10lf, m_valid = %d",label,(double)(m_ppm * PPU_TO_PPM),(double)(m_uncertainty * PPU_TO_PPM),m_valid);
}

void FreqResult::Invert()
{
    m_ppm = -m_ppm;
}

bool FreqResult::InRange(FreqResult& inFRes)
{
    bool retVal;
    //TRACE_PRINTF("Dist = %0.10lf uns = %0.10lf",(double)(fabs(m_ppm - InFRes.m_ppm)), (double)(m_uncertainty + InFRes.m_uncertainty);
    if (((fabs(m_ppm - inFRes.m_ppm)) <= (m_uncertainty + inFRes.m_uncertainty)))
    {
        retVal = true;
    }
    else
    {
        retVal = false;
    }
    return (retVal);
}

//used in the clustering operation only. Increase the m_ppm and the uncertainty so that this encompasses this and inFRes
void FreqResult::CombineMaxMin(FreqResult& inFRes)
{
    long double min, max;

    max = MAX((inFRes.m_ppm + inFRes.m_uncertainty),(m_ppm + m_uncertainty));
    min = MIN((inFRes.m_ppm - inFRes.m_uncertainty),(m_ppm - m_uncertainty));

    m_ppm = (max + min) / 2;
    m_uncertainty = (max - min) / 2;
}

//#############################################################################################
ComboResult::ComboResult()
{

}

ComboResult::~ComboResult()
{

}

ComboResult& ComboResult::operator=(const FreqResult& inFres)
{
    if (this != &inFres)
    {
        m_ppm = inFres.m_ppm;
        m_uncertainty = inFres.m_uncertainty;
        m_valid = inFres.m_valid;
        m_clustered = inFres.m_clustered;
    }
    return *this;
}

void ComboResult::combine(FreqResult inResult1, FreqResult inResult2)
{
    ComboResult resArray[2];

    resArray[0] = inResult1;
    resArray[1] = inResult2;

    combine(resArray, 2);
}

//The fundamental combine operation! Combines an array of nRes InResults. Combines the results in the inverse proportion to
//their uncertainty so that a result showing less uncertainty is represented more in the final result. The result
//of the operation is stores in the members m_ppm and m_uncertainty
//
//              n = nRes                                        n = nRes
//             _____                                            _____
//        1    \    |   m_ppm                                   \    |
//     _______  \      ________             where      norm =    \       m_uncertainty
//              /                                                /
//      norm   /    |   m_uncertainty                           /    |
//             -----                                            -----
//              n = 0                                            n = 0
//
//
void ComboResult::combine(ComboResult inResults[], u32 nRes)
{
    ENTER();

    u32 i;
    u32 numCombined = 0;
    long double normaliser = 0.0;
    long double sum = 0.0;
    long double invUncertainty;
    long double uncertaintySum = 0.0;
    long double bestUncertainty = 1000000.0;

    for (i = 0; i < nRes; i++)
    {
        //TRACE_PRINTF("Result %" PRIu32 ,i);
        if (inResults[i].m_valid)
        {
            //TRACE_PRINTF("Result %" PRIu32 "is valid",i);
            if ((inResults[i].m_uncertainty) < bestUncertainty)
            {
                bestUncertainty = (inResults[i].m_uncertainty);
                TRACE_PRINTF("Best uncertainty =  %0.10Lf",bestUncertainty);
            }
        }
    }

    //TRACE_PRINTF("Combining");

    for (i = 0; i < nRes; i++)
    {
        if (inResults[i].m_valid)
        {
            TRACE_PRINTF("CRes combining %d",(int)i);
            //should not happen as SD has an (artificial)  floor
            if ((inResults[i].m_uncertainty) == 0.0)
            {
                TRACE_PRINTF("Help! m_uncertainty = 0.0");
            }
            else
            {
                if ((inResults[i].m_uncertainty) < (((long double) (tAppLevelVars::GetUncertaintyInvalidFactor())) * bestUncertainty))
                {
                    invUncertainty = (1 / (inResults[i].m_uncertainty));
                    sum += ((inResults[i].m_ppm) * invUncertainty);
                    normaliser += invUncertainty;
                    uncertaintySum += ldSquare(inResults[i].m_uncertainty);
                    numCombined++;
                }
                else
                {
                    TRACE_PRINTF("Result %" PRIu32 " invalidaded due to relative uncertainty = %0.10Lf, best = %0.10Lf",i,(inResults[i].m_uncertainty),bestUncertainty);
                    inResults[i].m_valid = false;
                }
            }
        }
    }

    if (numCombined > 0)
    {
        m_ppm = sum / normaliser;
        m_uncertainty = ((sqrt(uncertaintySum)) / numCombined);
        m_valid = true;
    }
    else
    {
        m_valid = false;
    }

    EXIT();

}

void ComboResult::combine(ComboResult& inResult)
{
    ComboResult comboArray[2];

    comboArray[0] = inResult;
    comboArray[1] = *this;

    combine(comboArray, 2);
}

void ComboResult::DriftCalc(unsigned long long int t1, unsigned long long int t2, ComboResult& last)
{
    long double multFac;

    TRACE_PRINTF("t1 = %Lu", t1);
    TRACE_PRINTF("t2 = %Lu", t2);
    Display("Drift Calc this ");
    last.Display("Drift calc last ");
    multFac = (1000000.0 * SECS_PER_DAY) / (t2 - t1);
    TRACE_PRINTF("Mult fac = %0.10Lf", multFac);
    TRACE_PRINTF("Top = %0.10Lf",(m_ppm - last.m_ppm));
    m_ppm = (m_ppm - last.m_ppm) * multFac;
    m_uncertainty = (sqrt((ldSquare(m_uncertainty)) + (ldSquare(last.m_uncertainty))));

    Display("Drift Calc finished  this ");
}

//#############################################################################################
ComboResultFilter::ComboResultFilter() :
    m_count(0), m_filterPoints(NULL), m_numPoints(0)
{

}

ComboResultFilter::~ComboResultFilter()
{
    if (m_filterPoints != NULL)
    {
        delete[] m_filterPoints;
    }
}

bool ComboResultFilter::Init(u32 inNumPoints)
{
    ENTER();
    m_numPoints = inNumPoints;

    if ((m_filterPoints = new ComboResult[m_numPoints]) == NULL)
    {
        RETURN(false);
    }
    else
    {
        TRACE_PRINTF("newing %d filter points",(int)m_numPoints);
        RETURN(true);
    }
}

void ComboResultFilter::Add(ComboResult& inCRes)
{
    TRACE_PRINTF("m_numPoints = %d,In =",(int)m_numPoints);
    inCRes.Display();

    m_filterPoints[m_count] = inCRes;

    if ((++m_count) >= m_numPoints)
    {
        m_count = 0;
    }
    TRACE_PRINTF("Filter elements  = ");
    for (u32 i = 0; i < m_numPoints; i++)
    {
        m_filterPoints[i].Display();
    }
    combine(m_filterPoints, m_numPoints);
    TRACE_PRINTF("Filter now = ");
    Display();
}

void ComboResultFilter::Reset()
{
    for (u32 i = 0; i < m_numPoints; i++)
    {
        m_filterPoints[i].Reset();
    }
    m_count = 0;
}

//##################################################################################################

