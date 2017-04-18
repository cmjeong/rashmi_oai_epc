///////////////////////////////////////////////////////////////////////////////
//
// RemGsmRemDACEstimateInd.h
//
// TBD
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __RemGsmRemDACEstimateInd_h_
#define __RemGsmRemDACEstimateInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/SerialisationUtils.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class RemGsmRemDACEstimateInd : public threeway::Serialisable
{
public:
    RemGsmRemDACEstimateInd(u32 dacEstimate,bool remGsmRemScanWasOK) : m_dacEstimate(dacEstimate),m_remGsmRemScanWasOK(remGsmRemScanWasOK) {};
    RemGsmRemDACEstimateInd() : m_dacEstimate(0),m_remGsmRemScanWasOK(false) {};
    ~RemGsmRemDACEstimateInd() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_REM_GSM_REM_DAC_ESTIMATE_IND; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const { RSYS_ASSERT(dataMaxBytes >= 5); const u8 * const dataStart = data; SerialiseIt(m_dacEstimate, data); SerialiseIt(m_remGsmRemScanWasOK, data);return(data - dataStart); }
    virtual bool DeSerialise(const u8* data, u32 dataLen) { RSYS_ASSERT(dataLen >= 5); DeSerialiseIt(m_dacEstimate, data); DeSerialiseIt(m_remGsmRemScanWasOK, data);return(true); }
    virtual std::string ToString() const { ostringstream stream; stream << "DAC Estimate=" << m_dacEstimate << "Success = " << m_remGsmRemScanWasOK; return(stream.str()); }

    /**
     * Accessors.
     */
    u32 GetDACEstimate() { return m_dacEstimate; }
    bool GetremGsmRemScanWasOK() {return m_remGsmRemScanWasOK;}

private:

    u32 m_dacEstimate;
    bool m_remGsmRemScanWasOK;
};

#endif
