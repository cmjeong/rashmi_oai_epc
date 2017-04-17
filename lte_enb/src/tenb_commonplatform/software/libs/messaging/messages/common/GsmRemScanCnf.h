///////////////////////////////////////////////////////////////////////////////
//
// GsmRemScanCnf.h
//
// TBD
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __GsmRemScanCnf_h_
#define __GsmRemScanCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class GsmRemScanCnf : public threeway::Serialisable
{
public:

    static const u32 NUM_GSM_DCS_FREQUENCIES = 20;
    static const u32 NUM_PCS_FREQUENCIES = 20;

    /**
     * Construction / destruction.
     */
    GsmRemScanCnf():m_scanCompletedSuccessfully(false) {};
    GsmRemScanCnf(bool scanCompletedSuccessfully):m_scanCompletedSuccessfully(scanCompletedSuccessfully) {};
    virtual ~GsmRemScanCnf();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_GSM_REM_SCAN_CNF; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    void SetscanCompletedSuccessfully(bool scanCompletedSuccessfully) {m_scanCompletedSuccessfully = scanCompletedSuccessfully;}
    bool GetscanCompletedSuccessfully(void) {return m_scanCompletedSuccessfully;}


    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:
    bool m_scanCompletedSuccessfully;
};


#endif
