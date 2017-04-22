///////////////////////////////////////////////////////////////////////////////
//
// RemScanReq.h
//
// Message for requesting a REM scan.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __RemScanReq_h_
#define __RemScanReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/UmtsBands.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////
// parameters from the configuration file
#define NUM_UARFCNS 64
#define NUM_SCRAMBLING_CODES 32
#define NUM_EQUIVALENT_NETWORKS 32 //changed from 15 to 32 for CR-ccpu00123362

class ConfigFileParams
{
public:
    ConfigFileParams() :
        numUarfcns(0),
        initialPower(0),
        dynamicPowerLimit(0),
        epsilonPercent(0),
        oscDac(0),
        planningCpichRscp(0),
        planningRssi(0),
        minNeighbourCpichEcn0(0),
        minNeighbourCpichRscp(0),
        mcc(0),
        mnc(0),
        forcedPsc(512),
        uBandsSupported(false),
        qQualMinDb(0),
        qRxLevMinDbm(0),
        powerMarginSelection(0),
        fapCoverageTargetDb(0),
        qMeasureCpich(0),
        qQualMinOffsetDb(0),
        qRxLevMinOffsetDb(0),
        cpichPowerMinDlimDbm10(0),
        cpichPowerMaxDlimDbm10(0),
	minFapTxPowerDbm10(0),
	maxFapTxPowerDbm10(0)
        {
        	u32 i;
        	for(i = 0; i < NUM_SCRAMBLING_CODES; i++)
        	{
            		sC[i] = 0;
        	}
        	for(i = 0; i < NUM_UARFCNS; i++)
        	{
            		uarfcn[i] = 0;
        	}
        	for(i = 0; i < NUM_EQUIVALENT_NETWORKS; i++)
        	{
            		equivalentMcc[i] = 0;
            		equivalentMnc[i] = 0;
        	}
    	}

    u16 sC[NUM_SCRAMBLING_CODES];
    u16 uarfcn[NUM_UARFCNS];
    u32 numUarfcns;
    s32 initialPower;
    s32 dynamicPowerLimit;
    u32 epsilonPercent;
    u32 oscDac;
    s32 planningCpichRscp;
    s32 planningRssi;
    s32 minNeighbourCpichEcn0;
    s32 minNeighbourCpichRscp;
    u16 equivalentMcc[NUM_EQUIVALENT_NETWORKS];
    u16 equivalentMnc[NUM_EQUIVALENT_NETWORKS];
    u16 mcc;
    u16 mnc;
    u16 forcedPsc;
    UmtsBands uBandsSupported;
    s32 qQualMinDb;
    s32 qRxLevMinDbm;
    u32 powerMarginSelection;
    u32 fapCoverageTargetDb;
    u32 qMeasureCpich;
    u32 qQualMinOffsetDb;
    u32 qRxLevMinOffsetDb;
    s32 cpichPowerMinDlimDbm10;
    s32 cpichPowerMaxDlimDbm10;
    s32 minFapTxPowerDbm10;
    s32 maxFapTxPowerDbm10;
};

class RemScanReq : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    RemScanReq();

    RemScanReq(ConfigFileParams& params);
    virtual ~RemScanReq();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_REM_SCAN_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    const ConfigFileParams &GetConfig() const { return m_configFileParams; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:
    // The set of parameters to inform this entity about.
     ConfigFileParams m_configFileParams;
};

#endif // __RemScanReq_h_
