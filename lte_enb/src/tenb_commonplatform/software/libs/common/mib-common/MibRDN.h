///////////////////////////////////////////////////////////////////////////////
//
// MibRDN.h
//
// Relative distinguished name.  Represents an object class and instance.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibRDN_h_
#define __MibRDN_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <Radisys.h>
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibObjectClass.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibRDN : public threeway::Serialisable
{
public:
    static const u32 SERIALISATION_LENGTH = 8; // class, instance

    /**
     * Constructor.
     */
    MibRDN() : m_mibObjectClass(MIB_OBJECT_CLASS_INVALID), m_mibObjectInstance(0) {};
    MibRDN(MibObjectClass mibObjectClass,
           u32            mibObjectInstance);

    /**
     * Destructor.
     */
    ~MibRDN();

    /**
     * Implement Serialisable.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_RDN; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    std::string ToString() const;

    /**
     * Getters
     */
    MibObjectClass GetMibObjectClass() const { return m_mibObjectClass; }
    u32            GetMibObjectInstance() const { return m_mibObjectInstance; }

    /**
     * Check if matches another RDN.
     */
    bool operator==(const MibRDN& rhs) const;
    bool operator!=(const MibRDN& rhs) const;

    /**
     * Comparison operators need for STL map.
     */
    bool operator<(const MibRDN &rhs) const;
    bool operator>(const MibRDN &rhs) const; // not necessary for Strict Weak Ordering

    /**
     * Allow the ostream operator<< to access the private members of this class
     *
     * @param os output stream
     * @param s MibRDN to be sent to the output stream
     * @return os
     */
    friend std::ostream& operator<< (std::ostream& os, const MibRDN& s);

private:
    MibObjectClass m_mibObjectClass;
    u32            m_mibObjectInstance;
};



#endif
