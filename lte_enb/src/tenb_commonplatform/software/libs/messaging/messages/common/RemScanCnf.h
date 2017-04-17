///////////////////////////////////////////////////////////////////////////////
//
// RemScanCnf.h
//
// Message for confirming completion of a REM scan.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __RemScanCnf_h_
#define __RemScanCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

enum eRemScanResult
{
    REM_SCAN_RESULT_NOT_YET_PERFORMED = 0,
    REM_SCAN_RESULT_FAILED ,
    REM_SCAN_RESULT_PASSED,
    REM_SCAN_RESULT_INTERRUPTED
} ;

class RemScanCnf : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    RemScanCnf(eRemScanResult remResult);
    RemScanCnf();
    virtual ~RemScanCnf();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_REM_SCAN_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters
     */
    eRemScanResult GetRemResult() const { return m_remResult; }

private:
    eRemScanResult m_remResult;
};

#endif // __RemScanCnf_h_
