///////////////////////////////////////////////////////////////////////////////
//
// NlmCoscReq.h
//
// Message for requesting a NLM COSC, to acquire a cell for freq-sync.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NlmCoscReq_h_
#define __NlmCoscReq_h_

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
#define NUM_ARFCNS 3

class CoscArfcnList
{
public:
    CoscArfcnList() :
        numArfcns(0)
        {
        u8 i;
        for(i = 0; i < NUM_ARFCNS; i++)
        {
            arfcn[i] = 0;
        }
    }

    u16 arfcn[NUM_ARFCNS];
    u8 numArfcns;
};

class NlmCoscReq : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    NlmCoscReq();

    NlmCoscReq(CoscArfcnList& arfcnList);
    virtual ~NlmCoscReq();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_NLM_COSC_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    u8 GetNumArfcns() const { return m_coscArfcnList.numArfcns; }
    /* 0.9_patch2 */
    u16 GetArfcn(u16 cnt) const { return m_coscArfcnList.arfcn[cnt]; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:
    // The set of parameters to inform this entity about.
     CoscArfcnList m_coscArfcnList;
};

#endif // __NlmCoscReq_h_
