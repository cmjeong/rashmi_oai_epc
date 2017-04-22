///////////////////////////////////////////////////////////////////////////////
//
// SerialisingProtocolLayer.h
//
// Protocol layer with a queue for serialised processing of PDUs.
// NOTE: Not thread safe!
//
// Derived classes simply need to implement ProcessPdu() then use
// an instance of ProtocolStack to join up different protocol layers.
// And that's about it...  They may also want to derive from PDU to create
// PDUs specific to the protocol they are handling.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SerialisingProtocolLayer_h_
#define __SerialisingProtocolLayer_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/ThreadWithQueue.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ProtocolLayer.h"

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class SerialisingProtocolLayer;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class SerialisingProtocolLayer : public ProtocolLayer
{
public:
    /**
     * Construction / destruction.
     * Virtual destructor as concrete protocol layers derived from this.
     */
    SerialisingProtocolLayer();
    virtual ~SerialisingProtocolLayer();
 
    /**
     * Implement ProtocolLayer pure virtual.
     * Receive packet from the layer above and place on queue
     * for processing by the main thread.
     */
    virtual void ReceiveFromHigherLayer(shared_ptr<PDU> pdu);

    /**
     * Implement ProtocolLayer pure virtual.
     * Receive packet from the layer below and place on queue
     * for processing by the main thread.
     */
    virtual void ReceiveFromLowerLayer(shared_ptr<PDU> pdu);
    
    /**
     * Override ProtocolLayer virtual.
     * Receive packet from LME and place on queue for processing
     * by the main thread.
     */
    virtual void ReceiveFromLME(shared_ptr<PDU> pdu);

    /**
     * Override TimerNotifyInterface virtual.
     * 
     * Put a message on our queue then when dequeued, call ProcessTimerExpiry().
     */
    virtual void NotifyTimerExpiry(TimerHandle expiredTimer);

protected:
    /**
     * Concrete protocol layer class implements this to process
     * dequeued PDUs.  No need to worry about deleting the PDU as
     * we are using shared (smart) pointers.  Indeed, the layer may
     * want to keep hold of it by copying it to another shared_ptr.
     * Just don't forget to call .reset() on the copy when finished with it.
     */
    virtual void ProcessPdu(shared_ptr<PDU> pdu, PduDirection direction) = 0;

    /**
     * Concrete protocol layer class implements this to process timer expiries.
     */
    virtual void ProcessTimerExpiry(TimerHandle expiredTimer) = 0;

    /**
     * Process an LME PDU.  Default implementation simply warns about
     * unhandled LME PDU.
     */
    virtual void ProcessLmePdu(shared_ptr<PDU> pdu);

    /**
     * Override these to aid re-entrancy detection.
     */
    virtual bool SendToHigherLayer(shared_ptr<PDU> pdu) const;
    virtual bool SendToLowerLayer(shared_ptr<PDU> pdu) const;

private:
    /**
     * Process any events that have been queued up to avoid re-entrancy.
     */
    void ProcessQueue();

    /**
     * Queue for events that arrive while we are still processing another event.
     * In a single threaded environment this can only happen due to re-entrancy
     * in the same thread so we don't need to mutex it.
     */
    bool m_processingEvent;
    std::queue< shared_ptr<Queueable> > m_queue;
    
};

}

#endif
