/*********************************************************************17*/
///////////////////////////////////////////////////////////////////////////////
//
// SwUpdateEngine.h
//
// Perform FTP downloads and software update operations
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SwUpdateEngine_h__
#define __SwUpdateEngine_h__

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>
#include <string>
#include <queue>
#include <3waytypes.h>
#include <system/Thread.h>
#include <system/TimeWrap.h>
#include <messaging/transport/MessagingEntity.h>


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "UpdateConstants.h"
#include "UpdateRequests.h"

using namespace std;
using namespace threeway;
using namespace boost;

#define _NEVER_REQUIRE_SIGNED_UPDATES

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////


//
// SwUpdateInterface
//
// Interface class to be inherited from (and implemented by) whatever entity
// actually initiates/controls/whatever the upload/download/update process.
// Basically just a couple of callbacks invoked when download, upload, or update
// operations complete.
//
class SwUpdateInterface
{
public:
    virtual ~SwUpdateInterface() {};

    /**
     * Callbacks to signal events back from the update engine to the
     * parent application.
     *
     * \param request - The request associated with this event.
     */
    virtual void FtpCallback(FtpRequestPtr request) = 0 ;
};


//
// Classes which perform FTP and apply updates.
//

//
// Update.
//
class SwUpdateEngine : public threeway::Thread
{
public:
    SwUpdateEngine(SwUpdateInterface &owner);
    virtual ~SwUpdateEngine();

    /**
     * Put an update or FTP request on the worker thread's queue.
     * \param objectTo Queue - what it says really...
     */
    void Enqueue(SwUpdateOperationRequestPtr objectToQueue);

    /**
     * Pull an update or FTP request off the worker thread's queue.
     * \param timeout - How long to wait before returning anyway.
     *
     * \return An FTP or Update request structure (or null if queue was empty at timeout).
     */
    SwUpdateOperationRequestPtr Dequeue(u32 timeoutMilliSecs = 1000);

    /**
     * Abort a request - if it's being actioned halt it, if it's in the queue then remove it
     * currently only supported for FTP operations.
     *
     * \param clientRequestId Client ID for request to be aborted.
     * \param localRequestId Our ID for request to be aborted.
     */
    bool Abort (u32 clientRequestId, u32 localRequestId) ;


private:
    /**
     * The worker thread!
     */
    u32 ThreadProcedure();

    /**
     * Process incoming requests
     *
     * \param requestPtr Object describing the update/ftp operation (location of file(s), operation to carry out, requesting entity, etc).
     */
    void HandleFtpRequest(FtpRequestPtr requestPtr);

    /**
     * Functions used to build FTP commands.
     *
     * \param requestPtr    Object describing the FTP operation (location of file, operation to carry out, requesting entity, etc).
     * \param ftpPutCommand A command string which when executed will perform the requested operation.
     */
    bool BuildFtpPutCommand(FtpRequestPtr requestPtr, std::ostringstream& ftpPutCommand);
    bool BuildFtpGetCommand(FtpRequestPtr requestPtr, std::ostringstream& ftpGetCommand);


    deque<SwUpdateOperationRequestPtr> m_queue;
    SwUpdateOperationRequestPtr m_currentRequest;
    Mutex          m_queueMutex;
    Condition      m_queueCondition;

    SwUpdateInterface &m_swUpdateInterface ;
    static const int oam_ret_zero = 0;
};

/*
 * Used to distinguish V3.5 boards from V4 or later. V4e boards
 * report HW_TYPE value of 6, V4 Wistron boards report 7 so we
 * can identify both through something along the lines of
 *         if (hwType < HW_TYPE_V4)
 *         {
 *               3.5 stuff
 *         }
 *         else
 *         {
 *               4e or later stuff
 *         }
 */
static const u32 HW_TYPE_V4 = 6 ;


#endif
