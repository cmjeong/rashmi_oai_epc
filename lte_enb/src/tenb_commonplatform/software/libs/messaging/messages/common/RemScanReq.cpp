///////////////////////////////////////////////////////////////////////////////
//
// RemScanReq.cpp
//
// See header file for documentation.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>
#include <system/NumberConversions.h>
#include <system/SerialisationUtils.h>
#include <system/UmtsBands.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "RemScanReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

RemScanReq::RemScanReq(ConfigFileParams &params) :
    m_configFileParams(params)
{
}

RemScanReq::RemScanReq()
{
}

RemScanReq::~RemScanReq()
{
}

s32 RemScanReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    // Complex message... fairly arbitrary test but should be plenty.  We validate this below.
    // This is more maintainable than trying to calculate the exact space requirement.
    static const u32 MAX_SERIALISED_BYTES = 2000;
    RSYS_ASSERT(dataMaxBytes >= MAX_SERIALISED_BYTES);

    u8 * pOrigData = data;
    u8 i;

    for(i = 0; i < sizeof(m_configFileParams.sC) / sizeof(m_configFileParams.sC[0]); i++)
    {
        SerialiseIt(m_configFileParams.sC[i], data);
    }
    for(i = 0; i < sizeof(m_configFileParams.uarfcn) / sizeof(m_configFileParams.uarfcn[0]); i++)
    {
        SerialiseIt(m_configFileParams.uarfcn[i], data);
    }
    SerialiseIt(m_configFileParams.initialPower, data);
    SerialiseIt(m_configFileParams.oscDac, data);
    SerialiseIt(m_configFileParams.planningCpichRscp, data);
    SerialiseIt(m_configFileParams.minNeighbourCpichEcn0, data);
    SerialiseIt(m_configFileParams.minNeighbourCpichRscp, data);
    SerialiseIt(m_configFileParams.numUarfcns, data);
    SerialiseIt(m_configFileParams.epsilonPercent, data);
    SerialiseIt(m_configFileParams.dynamicPowerLimit, data);
    SerialiseIt(m_configFileParams.planningRssi, data);
    SerialiseIt(m_configFileParams.mcc, data);
    SerialiseIt(m_configFileParams.mnc, data);
    SerialiseIt(m_configFileParams.forcedPsc, data);

    // Bands
    const UmtsBandIds & bands = m_configFileParams.uBandsSupported.Get();
    u16 bandListLength = bands.size();
    SerialiseIt(bandListLength, data);
    data += 2;

    for (UmtsBandIds::const_iterator iter = bands.begin();
         iter != bands.end();
         ++iter)
    {
        u16 band = u16(*iter);
        SerialiseIt(band, data);
    }

    for(u32 i = 0; i < sizeof(m_configFileParams.equivalentMcc) / sizeof(m_configFileParams.equivalentMcc[0]); i++)
    {
        SerialiseIt(m_configFileParams.equivalentMcc[i], data);
        SerialiseIt(m_configFileParams.equivalentMnc[i], data);
    }

    SerialiseIt(m_configFileParams.qQualMinDb, data);
    SerialiseIt(m_configFileParams.qRxLevMinDbm, data);
    SerialiseIt(m_configFileParams.powerMarginSelection, data);
    SerialiseIt(m_configFileParams.fapCoverageTargetDb, data);
    SerialiseIt(m_configFileParams.qMeasureCpich, data);
    SerialiseIt(m_configFileParams.qQualMinOffsetDb, data);
    SerialiseIt(m_configFileParams.qRxLevMinOffsetDb, data);
    SerialiseIt(m_configFileParams.cpichPowerMinDlimDbm10, data);
    SerialiseIt(m_configFileParams.cpichPowerMaxDlimDbm10, data);

    RSYS_ASSERT((u32)(data - pOrigData) <= MAX_SERIALISED_BYTES);
    return (data - pOrigData);
}

bool RemScanReq::DeSerialise(const u8* data, u32 dataLen)
{
    u8 i;

    const u8 *pOrigData = data;

	for(i = 0; i < sizeof(m_configFileParams.sC) / sizeof(m_configFileParams.sC[0]); i++)
	{
		DeSerialiseIt(m_configFileParams.sC[i], data);
	}
	for(i = 0; i < sizeof(m_configFileParams.uarfcn) / sizeof(m_configFileParams.uarfcn[0]); i++)
	{
		DeSerialiseIt(m_configFileParams.uarfcn[i], data);
	}
	DeSerialiseIt(m_configFileParams.initialPower, data);
	DeSerialiseIt(m_configFileParams.oscDac, data);
	DeSerialiseIt(m_configFileParams.planningCpichRscp, data);
	DeSerialiseIt(m_configFileParams.minNeighbourCpichEcn0, data);
	DeSerialiseIt(m_configFileParams.minNeighbourCpichRscp, data);
    DeSerialiseIt(m_configFileParams.numUarfcns, data);
    DeSerialiseIt(m_configFileParams.epsilonPercent, data);
    DeSerialiseIt(m_configFileParams.dynamicPowerLimit, data);
    DeSerialiseIt(m_configFileParams.planningRssi, data);
    DeSerialiseIt(m_configFileParams.mcc, data);
    DeSerialiseIt(m_configFileParams.mnc, data);
    DeSerialiseIt(m_configFileParams.forcedPsc, data);

    // Bands
    u16 bandListLength;
    DeSerialiseIt(bandListLength, data);
    data += 2;

    for (; bandListLength != 0; --bandListLength)
    {
        u16 band;

        DeSerialiseIt(band, data);
        m_configFileParams.uBandsSupported.Insert( UmtsBandId(band) );
    }

    for(u32 i = 0; i < sizeof(m_configFileParams.equivalentMcc) / sizeof(m_configFileParams.equivalentMcc[0]); i++)
    {
    	DeSerialiseIt(m_configFileParams.equivalentMcc[i], data);
    	DeSerialiseIt(m_configFileParams.equivalentMnc[i], data);
    }

    DeSerialiseIt(m_configFileParams.qQualMinDb, data);
    DeSerialiseIt(m_configFileParams.qRxLevMinDbm, data);
    DeSerialiseIt(m_configFileParams.powerMarginSelection, data);
    DeSerialiseIt(m_configFileParams.fapCoverageTargetDb, data);
    DeSerialiseIt(m_configFileParams.qMeasureCpich, data);
    DeSerialiseIt(m_configFileParams.qQualMinOffsetDb, data);
    DeSerialiseIt(m_configFileParams.qRxLevMinOffsetDb, data);
    DeSerialiseIt(m_configFileParams.cpichPowerMinDlimDbm10, data);
    DeSerialiseIt(m_configFileParams.cpichPowerMaxDlimDbm10, data);

    // Changes for patch3, CR = ccpu00123462
	TRACE_PRINTF("Data=%x pOrigData=%x dataLen=%d\n", (unsigned int)data, (unsigned int)pOrigData, dataLen);

	return true;
}

string RemScanReq::ToString() const
{
    ostringstream stream;

    stream << "RemScanReq\n{ Scrambling Codes: { ";
    for (u32 i = 0; i < NUM_SCRAMBLING_CODES; i++)
    {
        stream << m_configFileParams.sC[i] << " ";
    }
    stream << "}\n  NumUarfcns=" << m_configFileParams.numUarfcns << ": { ";
    for (u32 i = 0; i < NUM_UARFCNS; i++)
    {
        stream << m_configFileParams.uarfcn[i] << " ";
    }
    stream << "}\n  Initial Power=" << m_configFileParams.initialPower << " Dynamic Power Limit=" << m_configFileParams.dynamicPowerLimit;
    stream <<  "\n  OscDac=" << m_configFileParams.oscDac;
    stream << "\n  PlanningCpichRscp=" << m_configFileParams.planningCpichRscp
           << " PlanningRssi=" << m_configFileParams.planningRssi
           << " minNeighbourCpichEcn0=" << m_configFileParams.minNeighbourCpichEcn0
           << " minNeighbourCpichRscp=" << m_configFileParams.minNeighbourCpichRscp;
    stream << "\nepsilonPercent=" << m_configFileParams.epsilonPercent << "\n}";

    stream << "\nequivalent PLMN IDs = {\n";
    for (u32 i = 0; i < NUM_EQUIVALENT_NETWORKS; i++)
    {
        stream << " " << m_configFileParams.equivalentMcc[i] << " " << m_configFileParams.equivalentMnc[i] << "\n";
    }
    stream << "}\n";
    stream << "mnc=" << m_configFileParams.mnc << " mcc=" << m_configFileParams.mcc << "forcedPsc=" << m_configFileParams.forcedPsc;
    stream << "Ubands=" << m_configFileParams.uBandsSupported.ToString() << "\n";

    return stream.str();
}
