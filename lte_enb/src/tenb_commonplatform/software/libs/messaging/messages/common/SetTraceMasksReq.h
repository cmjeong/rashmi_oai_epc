///////////////////////////////////////////////////////////////////////////////
//
// SetTraceMasksReq.h
//
// Set criticality and categories masks on an entity (actually currently
// applies to whole application).
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SetTraceMasksReq_h_
#define __SetTraceMasksReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class SetTraceMasksReq : public threeway::Serialisable
{
public:

    /**
     * Default constructor.  For messaging internal use only.
     */
    SetTraceMasksReq();

    /**
     * Construct a SetTraceMasksReq with the two masks to apply to the target
     * entity's trace object.
     */
    SetTraceMasksReq(u32 criticalityMask, u32 categoriesMask);

    virtual ~SetTraceMasksReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_SET_TRACE_MASKS_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters
     */
    u32 GetTraceCriticalityMask() const { return m_traceCriticalityMask; };
    u32 GetTraceCategoriesMask() const { return m_traceCategoriesMask; };

private:

    // Trace masks.
    u32 m_traceCriticalityMask;
    u32 m_traceCategoriesMask;
};

#endif
