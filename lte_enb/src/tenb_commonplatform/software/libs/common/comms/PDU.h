///////////////////////////////////////////////////////////////////////////////
//
// PDU.h
//
// Abstract class for a protocol data unit i.e. a message passed between
// two protocol layers.
//
// Traditionally this would be a simple data packet with head and tail
// management and we have a concrete PDU class 'SimplePDU' that does this.
// But by having an abstract base class we can have alternative PDU types
// e.g. we might want one that contains a message structures for a particular
// protocol or have a class for inter-layer control messages.  
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __PDU_h_
#define __PDU_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <3waytypes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class PDU
{
public:

    // Constants
    static const u32 PDU_SOURCE_ID_UNDEFINED = 0xffffffff;
    static const u32 PDU_CONNECTION_ID_UNDEFINED = 0xffffffff;
    
    /**
     * Destruction.
     * Virtual destructor to allow specific types of PDU to derive from this.
     */
    virtual ~PDU();

    /**
     * Access source ID.  General purpose field, this can be used as clients see fit.
     */
    void SetSourceId(u32 sourceId) { m_sourceId = sourceId; };
    u32  GetSourceId() const { return m_sourceId; };
    
    /**
     * Access connection ID.  General purpose field, this can be used as clients see fit.
     */
    void SetConnectionId(u32 connectionId) { m_connectionId = connectionId; };
    u32  GetConnectionId() const { return m_connectionId; };
    
    /**
     * Get as a string for debug.
     */
    virtual std::string ToString() const;
    
    /**
     * Get the total number of PDUs in existence.
     */
    static u32 GetTotalNumberPDUs() { return sm_pduCount; }

protected:
    /**
     * Construction.
     * Make this class abstract by having protected constructor.
     */
    PDU();

private:
    // Source ID, e.g. to indicate which stack this PDU came from.
    u32      m_sourceId;
    
    // Connection ID, e.g. to indicate which TCP connection this PDU relates to.
    u32      m_connectionId;
    
    // Total count of PDUs in existence.
    static u32 sm_pduCount;
};

}

#endif
