///////////////////////////////////////////////////////////////////////////////
//
// Tr069Application.h
//
// Main class for TR-069 interface application.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069Application_h_
#define __Tr069Application_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <system/Trace.h>
#include <messaging/transport/ApplicationWithParamCache.h>
#include <comms/IPv4Address.h>
#include <pthread.h>
#include <mib-common/messages/MibSubscribeAttributesInd.h>
#include <system/KpiLogFileMgr.h>
#include <system/TimerExpiry.h>
#include <system/Filename.h>
#include <system/Utilities.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069ServerConnection.h"
#include "Tr069TransactionSession.h"
#include "Tr069FileTransfer.h"
#include "Tr069RebootReq.h"
#include "Tr069Reboot.h"
#include "Tr069TimerTriggeredEvents.h"
#include "Tr069AlarmManager.h"
#include "Tr069ParameterAttributeManager.h"
#include "Tr069Cli.h"
#include "Tr069ParamAttributeNvStore.h"
#include "Tr069Stun.h"

#define MAX_CRYPTO_PROFILES 2
#define MAX_REM_SCANED_UMTS_CELL 16
#define MAX_PERF_MGMT_ENTRY 1
#define DFLT_UPLOAD_INTERVAL 900
#define MAX_PM_FILES 5

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;
static const int oam_ret_zero = 0;
static const int ONE = 1;

#define REM_STATUS_SUCCESS "Success"
#define REM_STATUS_IN_PROGRESS "InProgress"

namespace tr069
{

class Tr069Application : public threeway::ApplicationWithParamCache
{
private:
    // Is singleton so private constructor.
    Tr069Application();
   map<string,string> m_digestMap;
   string m_auth;
    std::vector<std::string> m_PmFileNames;
    u32 m_currentPmFilenameIdx;
    u32 m_max_pmFiles;
    void RemoveOldPmFile(std::string);


public:
    /*
     * Add more contributors to TR069's op-state here.
     * Each has its own "bit", and add to "BitMask" too.
     */
    /**
     * Construction / destruction.
     */
    virtual ~Tr069Application ();
    static Tr069Application& GetInstance();

    /**
     * Implement Application virtuals.
     */
    virtual u32 ThreadProcedure();

    // Handle received connectionless messages
    void HandleTimerExpiry(shared_ptr<threeway::TimerExpiry> expiredTimer);
    void HandleOtherEvent(shared_ptr<threeway::Queueable> otherEvent);
    void HandleLogUpload(); 
    void SendBindingRequest(int fd,StunAddress4 stunServerAddr);
    void StartStunTimer(u32 timer_value);
    void StartLogTimer(u32 timer_value); 
    /**
     * Override base class method so we get informed of MIB attribute value changes.
     */
    virtual void MibAttributesUpdated(u32 subscriptionId, const MibAttributeValuesByDn &oldValues, const MibAttributeValuesByDn &newValues);
    virtual void MibAttributesUpdated(u32 subscriptionId, const MibAttributeIdsByDn& mibAttributeValuesByDn);

    std::string & GetFormattedUtcTime ( std::string & timeString, const threeway::TimeWrap & timeWrap, u8 subSecondDecimalPlaces = 0 ) const;
    std::string & GetFormattedLocalTime ( std::string & timeString, const threeway::TimeWrap & timeWrap, u8 subSecondDecimalPlaces = 0 ) const;
    std::string & GetFormattedCurrentTime ( std::string & timeString, u8 subSecondDecimalPlaces = 0 ) const;

    const string & GetFapUrlAbsolutePath( ) {
        return m_fapTr069ServerUrlAbsolutePath;
    }

    void RebootFapViaOam();

    TimerTriggeredEvents timerDelayedProcedures;

    bool GeneratePmDataFile( const Filename& filename, bool IsReqAfterReboot = false );
    void GeneratePmFileName( std::string &fileName );
    void UploadPmDataFile ( std::string fileName );

    void StartKeyPerformanceIndicationLogging();

    void Tr069OperationalStatus ( bool opStateEnabled );

    shared_ptr<AlarmManager> getAlarmManager() 
    { 
       return m_alarmManager; 
    }
    void SetDigestAttribute(map<std::string,std::string> digestMap, string auth)
   {
      m_digestMap = digestMap;
      m_auth = auth;
      TRACE_PRINTF("Tr069Application::set the digestMap");
   }
   void ClearDigestValues()
   {
      TRACE_PRINTF("Tr069Application::clear the digestMap");
      m_digestMap.clear();
      m_auth.clear();
   }
   std::string GetDigestAttribute(std::string attribute);
   std::string GetAuthMethod();
    shared_ptr<ParameterAttributeManager> GetParameterAttributeManager() const { return m_parameterAttributeManager;}
    shared_ptr<Tr069ParamAttributeNvStore> GetParamAttNvStore() const { return m_paramAttNvStore;}
    std::string GetSoapTimeout(); 
    bool useUrlInUse;
    UpTime m_uptime;
    static bool isWatchdogDereg;
    static string authMethod;
private:

    void SubscribeToMibParams(void);
    void ImportCommissioningAttributes(void);

    void SetFapRebootRequired() { m_FapRebooting = true; }

    std::string & GetFormattedTime ( std::string & timeString, const threeway::TimeWrap & timeWrap ) const;

    // Implement MessageHandler interface
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

    bool m_FapRebooting;
    bool m_StartMsgReceived;
    
    u32 m_collectionPeriodInSecs;
    u32 m_perodicUploadInterval;
    u32 m_perodicUploadPhaseAllignInMin;
    bool m_perodicUploadEnable;
    std::string m_UserName;
    std::string m_Passwd;
    bool m_enableFileCompress;
    std::string m_compressMethod;
    TimerHandle m_logTimerHandle;
    TimerHandle m_stunTimerHandle;

    queue< shared_ptr<TransactionSessionCommand> > m_queuedTransactionSessions;
    static Tr069Application* s_instance;

    void InitialisePMParms();
    void UpdatePMParams(u32 inst);
    void GenerateFapTr069ServerUrl();
    std::string m_fapTr069ServerUrlAbsolutePath;

    void GenerateHwVersionString();
    void GenerateSwVersionString();

    shared_ptr<threeway::KpiLogFileMgr> m_kpiLogFileMgr;
    std::set<KpiGroupId> m_kpiGroupList;
    void KpiConfigure( void );
    bool GetIPAddress(const char * interfaceName, IPv4Address &addr, IPv4Address &mask);
    bool GetIPV6Address();
    TimerHandle m_notifyReadyGuardTimer;
    TimerHandle m_startDelayTimer;
    threeway::TimerHandle m_watchdogKickTimer; 

    Tr069CliCommands m_cliCommands;

    shared_ptr<AlarmManager> m_alarmManager;
    shared_ptr<ParameterAttributeManager> m_parameterAttributeManager;
    shared_ptr<Tr069ParamAttributeNvStore> m_paramAttNvStore;
};

extern string XmlSafeString( const string & input );
}
#endif
