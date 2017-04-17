///////////////////////////////////////////////////////////////////////////////
//
// SwUpdateApplication.h
//
// Application for performing FTP and software update.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////


#ifndef __SwUpdateApplication_h_
#define __SwUpdateApplication_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <system/TimerInterface.h>
#include <system/TimerExpiry.h>
#include <system/ThreadlessTimerEngine.h>
#include <system/Utilities.h>
#include <messaging/transport/SingleThreadedAppWithAttrCache.h>


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SwUpdateEngine.h"

#define MAX_PERF_MGMT_ENTRY 1

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;

class SwUpdateApplication : public threeway::SingleThreadedAppWithAttrCache,
                          public SwUpdateInterface
{
private:
    // Is singleton so private constructor.
    SwUpdateApplication();

public:
    bool isreadyForSwUpgrade;
    ~SwUpdateApplication();
    static SwUpdateApplication& GetInstance();

   void HandleAdminDownAck() ;
    SwUpdateEngine& GetSwUpdateEngine() {return m_updateEngine;};

    /**
     * Pure virtuals inherited from SwUpdateInterface - these are
     * callbacks used by update engine to signal progress and/or
     * completion of FTP or update actions to "owning" app.
     */
    void FtpCallback(FtpRequestPtr request);

    /**
     * Get status of all (pending, completed, or in progress) FTP transfer activities
     * in text form - used by CLI command.
     *
     * \param extended		If true return extra information beyond basic summary
     */
    string GetFtpStatusString (bool extended = false) ;

    /**
     * Get status of most recent software update operation in text form - used
     * by CLI command
     *
     * \param extended		If true return extra information beyond basic summary
     */
    string GetUpdateStatusString (bool extended = false) ;

    //static bool swIsDeregWatchDog;
    static bool swIsDeregWatchDog;

    /**
     * This function will set swIsDeregWatchDog value with input value
     *
     * \param val		Bool value to set swIsDeregWatchDog value to true or false
     */
    void SetIsDeregWatchDog(bool val)
    {
       swIsDeregWatchDog = val;
    }
    /* Allows to apply different TOS values if QoS is disabled */
    bool IsQosEnabled();
    
    threeway::TimerHandle m_watchdogKickTimer;
    // Handle received connectionless messages
    void HandleTimerExpiry(shared_ptr<threeway::TimerExpiry> expiredTimer);
    void HandleLogUpload(); 
    void StartLogTimer(u32 timer_value); 

    string newSwFileName;
    bool isSwUpgradeStarted;
protected:

    /**
     * Implement base class hooks relating to application start-up.
     */
    virtual void InitialiseApp();
    virtual void StartApp();
    virtual std::vector<MessagingEntity> GetSupportedEntities();
    virtual void GetSubscriptions(std::vector<SubscriptionDescriptor>& subscriptions);

private:
    /**
     * Singleton instance.
     */
    static SwUpdateApplication *instance;
    threeway::TimerHandle m_logTimerHandle;
    string logFileDir;
    // Implement MessageHandler interface
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

    /**
     * Subscription IDs for MIB subscription requests so we
     * can match CNF messages to requests and identify
     * any duplicates!.
     */
	typedef enum
	{
		UPDATE_APP_FAP_MIB_SUBSCRIPTION_ID,
		UPDATE_APP_FACTORY_MIB_SUBSCRIPTION_ID,
      UPDATE_APP_FAP_MIB_SUBSCRIPTION_ID_PERF_MGMNT,
      ADMIN_DOWN_ACK,
      LOG_UPLOAD_INTERVAL_CHANGE
	} SwUpdateMibSubsReqId;

    /**
     * Handler functions for incoming messages.
     *
     * \param message      The received message
     * \param currentState Current state of application state machine (see SwUpdateAppStates).
     * \return New state of application state machine after handling message,
     */
	void HandleFtpReq(shared_ptr<threeway::MessageSerialisedData> message) ;
	void HandleFtpCnf(shared_ptr<threeway::MessageSerialisedData> message) ;
	void HandleFtpAbortReq(shared_ptr<threeway::MessageSerialisedData> message) ;
	void HandleFtpGetReq(shared_ptr<threeway::MessageSerialisedData> message) ;
	void HandleFtpPutReq(shared_ptr<threeway::MessageSerialisedData> message) ;
	void HandleFtpCompleteInd(shared_ptr<threeway::MessageSerialisedData> message) ;
   void SetLogDirPath(string dir){ logFileDir = dir;}
   string GetLogDirPath(){ return logFileDir;}
	/**
	 * Initialise and configure the update engine. Gets details of kernel in use, app
	 * bank in use etc, makes sure they're consistent, updates MIB parameters where
	 * appropriate, checks state of app bank directories/links and attempts to repair
	 * if necessary.
	 *
	 */
    void ConfigureUpdateEngine();

	/**
	 * Class to hold the status of an FTP operation.
	 */
    class FtpStatusInfo
    {
    public:
    	/**
    	 * Create an FTP status object.
    	 *
    	 * \param clientRequestId Request ID supplied by requesting entity.
    	 * \param serverRequestId Request ID generated by us.
    	 * \param status          Status string which will be sent back to an app requesting status.
    	 * \param extendedStatus  Extra status information which can (optionally) be sent to CLI.
    	 */
    	FtpStatusInfo (u32 clientRequestId, u32 serverRequestId, string status = "", string extendedStatus = "") :
				m_clientRequestId(clientRequestId),
				m_serverRequestId(serverRequestId),
				m_requestStatus(status),
				m_extendedRequestStatus(extendedStatus) {};

    	FtpStatusInfo() :
			m_clientRequestId(0),
			m_serverRequestId(0),
			m_requestStatus(""),
			m_extendedRequestStatus("") {};


		/**
		 * Setters.
		 */
		void SetStatus (const string& status) {m_requestStatus = status;};
		void SetExtendedStatus (const string& status) {m_extendedRequestStatus = status;};

		/**
		 * Getters.
		 */
		u32 GetClientRequestId() {return m_clientRequestId;};
		u32 GetServerRequestId() {return m_serverRequestId;};
		string GetStatus() {return m_requestStatus;};
		string GetExtendedStatus() {return m_extendedRequestStatus;};

    private:
    	u32 m_clientRequestId ;
    	u32 m_serverRequestId ;
    	string m_requestStatus ;
    	string m_extendedRequestStatus ;
    } ;

    /**
     * FTP status history.
     */
	map <u32, FtpStatusInfo> m_ftpStatus ;

	/**
     * Class to hold the state of the last completed or in
     * progress update operation for query over CLI.
     */
    class UpdateStatusInfo
    {
    public:
    	UpdateStatusInfo (string status = "", string extendedStatus = "") :
				m_requestStatus(status),
				m_extendedRequestStatus(extendedStatus) {};

		/**
		 * Setters.
		 */
		void SetStatus (const string& status) {m_requestStatus = status;};
		void SetExtendedStatus (const string& status) {m_extendedRequestStatus = status;};

		/**
		 * Getters.
		 */
		string GetStatus() {return m_requestStatus;};
		string GetExtendedStatus() {return m_extendedRequestStatus;};

    private:
    	string m_requestStatus ;
    	string m_extendedRequestStatus ;
    } ;

    /*
     * Status information for most recent (or current) update operation.
     */
    UpdateStatusInfo m_updateStatus ;

    /**
     * Instance of "update engine" class which encapsulates the "worker thread", it's queues and
     * the methods which actually do the work
     */
    SwUpdateEngine m_updateEngine ;
};

#endif
