///////////////////////////////////////////////////////////////////////////////
//
// UpdateOperations.h
//
// Defines objects used to request an update or FTP operation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UpdateRequests_h__
#define __UpdateRequests_h__

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
using namespace std;

class  SwUpdateOperationRequest
{
public:

    typedef enum
    {
        FTP_REQUEST,
        UPDATE_REQUEST,
    } SwUpdateEventType;

    /**
     * Construct a request object.
     *
     * \param eventType       Type of request (FTP or Update) to construct
     * \param clientRequestId Request ID supplied by requesting entity.
     */
    SwUpdateOperationRequest (SwUpdateEventType eventType, u32 clientRequestId) :
                        m_eventType(eventType),
                        m_clientRequestId(clientRequestId),
                        m_localRequestId(m_nextLocalRequestId++),
                        m_succeeded(false) {} ;
    virtual ~SwUpdateOperationRequest (){};

    /**
     * Getters
     */
    SwUpdateEventType GetSwUpdateEventType() { return m_eventType; } ;
    u32 GetClientRequestId() { return m_clientRequestId ; } ;
    u32 GetLocalRequestId() { return m_localRequestId ; } ;
    string GetFailureString () const { return m_failureString; }
    bool GetSuccess () const { return m_succeeded; }
    void SetSuccess (bool status) { m_succeeded = status; }

    /**
     * Setters.
     */
    void SetFailureString (const string& failString) { m_failureString = failString; };


private:
    SwUpdateEventType m_eventType ;
    static u32 m_nextLocalRequestId ;
    u32 m_clientRequestId ;
    u32 m_localRequestId ;
    string m_failureString ;
    bool m_succeeded;
};

typedef shared_ptr<SwUpdateOperationRequest> SwUpdateOperationRequestPtr ;

//
// FtpRequest
//
// Used to pass (and enqueue) FTP download/upload requests.
//
class FtpRequest : public SwUpdateOperationRequest
{
public :

    typedef enum
    {
        FTP_DIRECTION_GET,
        FTP_DIRECTION_PUT,
        FTP_DIRECTION_INVALID
    } FtpDirection;

    typedef enum
    {
    	FTP_PENDING,
    	FTP_QUEUED,
    	FTP_STARTED,
    	FTP_COMPLETED,
    	FTP_ABORTED
    } FtpStatus ;

    /**
     * Construct an FTP request object.
     *
     * \param server           FTP server to get or put file to/from.
     * \param user             User ID to use when connecting to client.
     * \param password         Password to use when connecting to client.
     * \param remoteDir        Name of directory to get/put to/from on FTP server.
     * \param remoteFileName   Name of file to get/put on FTP server.
     * \param localIpAddress   Local IP address to bind to when performing action.
     * \param localDir         Name of directory to get/put to/from on FAP.
     * \param localFileName    Name of file to get/put on FAP.
     * \param requestingEntity Requesting application.
     * \param FtpDirection     Identifies request for get or put operation.
     * \param clientRequestId  Request ID supplied by requesting entity.
     */
    FtpRequest(const string& server, const string& user, const string& password,
                  string remoteDir, const string& remoteFilename,
                  const string& localIpAddress,
                  string localDir, const string& localFilename,
                  MessagingEntity requestingEntity, FtpDirection direction,
                  u32 clientRequestId = 0);

    virtual ~FtpRequest();

    /**
     * Getters.
     */
    string GetUsername() const {return m_username;}
    string GetPassword() const {return m_password;}
    string GetServer() const {return m_server;}
    string GetRemoteDir() const {return m_remoteDir;}
    string GetRemoteFilename()const {return m_remoteFilename;}
    string GetLocalIpAddress() const {return m_localIpAddress;}
    string GetLocalDir() const {return m_localDir;}
    string GetLocalFilename() const {return m_localFilename;}
    MessagingEntity GetRequestingEntity() const {return m_requestingEntity;}
    FtpDirection GetDirection() const { return m_direction; }
    threeway::TimeWrap GetStartTime() const {return m_startTime;}
    threeway::TimeWrap GetStopTime() const {return m_stopTime;}
    FtpStatus GetFtpStatus() const {return m_FtpStatus;}

    /**
     * Setters.
     */
    void SetFtpStatus (FtpStatus status) {m_FtpStatus = status;}


    /**
     * Update start/stop time for operation.
     */
    void UpdateStartTime() {m_startTime.Touch();}
    void UpdateStopTime() {m_stopTime.Touch();}

private:
    /*
     * FTP transfer parameters
     */
    string m_username ;
    string m_password ;
    string m_server;
    string m_remoteDir;
    string m_remoteFilename;
    string m_localIpAddress ;
    string m_localDir;
    string m_localFilename;
    FtpDirection m_direction;
    FtpStatus m_FtpStatus ;

    /*
     *  Member data used to report status back to
     *  original requester.
     */
    MessagingEntity m_requestingEntity ;
    threeway::TimeWrap m_startTime;
    threeway::TimeWrap m_stopTime;
};

typedef shared_ptr<FtpRequest> FtpRequestPtr ;



//
// SwUpdateRequest
//
// Used to pass (and enqueue) Software update requests.
//

/*class SwUpdateRequest : public SwUpdateOperationRequest
{
public :

	typedef enum
	{
	   UPDATE_PENDING,
	   UPDATE_QUEUED,
	   UPDATE_STARTED,
           UPDATE_IN_PROGRESS,
           UPDATE_COMPLETED,
           UPDATE_ABORTED
        } SwUpdateStatus ;

        typedef enum
        {
		UPDATE_INSTALL,
                UPDATE_ACTIVATE,
                UPDATE_INSTALL_AND_ACTIVATE,
                UPDATE_REVERT
        } SwUpdateAction;*/

    /**
     * Construct an Update request object.
     *
	 * \param updateDir        Location of update package file on FAP.
	 * \param updateFilename   Name of update package file on FAP.
	 * \param requestingEntity FAP application/entity request originates from.
	 * \param action           Operation required (install, activate, install and activate, revert).
	 * \param clientRequestId  Request ID supplied by requesting entity.
     */
    //SwUpdateRequest(string updateDir,
    //                const string& updateFilename,
    //                MessagingEntity requestingEntity,
    //                SwUpdateAction action,
    //                u32 clientRequestId = 0);
    //virtual ~SwUpdateRequest();

    /**
     * Getters.
     */
    //string GetUpdateDir() {return m_updateDir;};
    //string GetUpdateFilename(){return m_updateFilename;};
    //string GetInstalledBank() {return m_installedBank;} ;
    //SwUpdateStatus GetSwUpdateStatus() {return m_updateStatus; } ;
    //MessagingEntity GetRequestingEntity(){return m_requestingEntity;};
    //SwUpdateAction GetSwUpdateAction(){return m_updateAction;};

    /**
     * Setters.
     */
    //void SetSwUpdateStatus (SwUpdateStatus status) {m_updateStatus = status;};
    //void SetInstalledBank(const string& bank) {m_installedBank = bank;};

//private:
    /*
     * Update parameters
     */

    //string m_updateDir ;
    //string m_updateFilename ;
    //SwUpdateAction m_updateAction ;

    /*
     * Member data used to report status back to original requester.
     */
    //MessagingEntity m_requestingEntity ;
    //SwUpdateStatus m_updateStatus ;
    //string m_installedBank ;
//};

//typedef shared_ptr<SwUpdateRequest> SwUpdateRequestPtr;


#endif /* UPDATEOPERATIONS_H_ */
