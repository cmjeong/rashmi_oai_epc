///////////////////////////////////////////////////////////////////////////////
//
// KpiManager.h
//
// Manages collecting KPI readings including setting up poll timers.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __KpiManager_h_
#define __KpiManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/TimerInterface.h>
#include <messaging/transport/ApplicationWithMessaging.h>
#include <messaging/messages/common/KpiConfigureReq.h>
#include <messaging/messages/common/EventNotify.h>
#include <system/Timer.h>
#include <string.h>
#include <set>
#include <map>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class KpiManager
{
public:
    // We have two different measurements sets, one for normal use e.g.
    // as reported to an external management system in the final product,
    // and one for trace/debug/test use.  The difference (at this level)
    // is that the INTERVAL set gets polled at regular intervals and the
    // values reset (in the KpiCollector's), and the NO_RESET set is used
    // for trace/debug use only and is never reset.
    static const u8 KPI_MEASUREMENT_SET_INTERVAL = 0;
    static const u8 KPI_MEASUREMENT_SET_NO_RESET = 1;
    
    //Static const Variables represents hours,min,microsec per day,hour,sec
    static const u32 HoursInDay = 24;
    static const u32 MinInHour = 60;
    static const u32 SecInMin = 60;
    static const u32 MicroSecInSec = 1000;

    KpiManager(threeway::TimerEngineInterface& timerEngine,
               threeway::TimerNotifyInterface& timerNotifyInterface,
               threeway::SendMessageInterface& messageSender);
    ~KpiManager();

    /**
     * Register KPI group handler entities.
     */
    void RegisterKpiEntities(MessagingEntity entity, const std::set<KpiGroupId>& kpiGroupIds);

    /**
     * Configure a set of KPI measurements.
     */
    void ConfigureMeasurements(MessagingEntity managingEntity, const KpiConfigureReq& kpiConfigureReq);
    
    /**
     * Alligning to First Collection Period if there is any delta time difference.
     */
    void AllignToFirstCollectionPeriod(void);
    
    /**
     * Alligning to phase shift so that Peiodic uploads are alligned to PUT
     */
    u32 AllignToPhaseShift(void);
    
    /**
     * Actions to be taken on KpiT2Expiry
     */
    void ActOnKpiT2Expiry(bool noPhaseShiftReq = false);
    
    /**
     * Creating Timer
     */
    void CreateTimer(const std::string& timerName, u32 timeoutPeriodMs, TimerEngineInterface::TimerMode timerMode);
    
    /**
     * Deleting Timer
     */
    void DeleteTimer(void);
    
    /**
     * Check if timer is for us and deal with it.
     */
    bool HandleTimerExpiry(threeway::TimerHandle timerHandle);

    /**
     * Sends poll Kpis info to entity and restart collection tmr
    */
    void SendPollKpis(void);
    /**
     * Poll for current KPIs without resetting for debug purposes.
     * KpiReadCnf's will be sent to OAM for it to stick them in trace file.
     *
     * \param pollForTotals If true then we request the totals since power on
     *                      otherwise we request the interim counts since the
     *                      last periodic poll reset them.
     */
    void PollKpisWithoutReset(bool pollForTotals) const;

    /**
     * Poll the KPIs and ensure the results from the KPI entities are sent to
     * TR069. Routine is called periodically and when we are about to reboot.
     */
    void PollKpisSendToManagingEntity(bool storeMessagingEntities = false, bool isCollectionReqPending = false);
    
    /** 
     * Upload the prevoius collected KPI's immediately after restart or after phase allignment
    */
    void SendKpiCollecReqNow(u32 bootStrapStatus) const;
    
    /** 
     * Notify L2 TimeOutValue so that both timer at SM and OAM are alligned
    */
    void NotifyL2TimeOutValue(u32 timeoutPeriodMs) const;

    bool isCollectionReqPending()
    {
       return m_isCollectionReqPending;
    }

    void sendUploadRequest(const MessagingEntity&);
private:

    // Typedefs
    typedef map<KpiGroupId, MessagingEntity> KpiEntities;

    /**
     * Interface for sending messages.
     */
    threeway::SendMessageInterface& m_messageSender;

    /**
     * Interface for managing timers.
     */
    threeway::TimerEngineInterface& m_timerEngine;
    threeway::TimerNotifyInterface& m_timerNotifyInterface;

    /**
     * KPI groups and their corresponding managing entity.
     * I.e. tells us where to poll for a particular set of results.
     */
    KpiEntities m_kpiEntities;

    /**
     * KPI groups to poll for.
     * TODO: Extend to allow multiple measurement sets.
     */
    std::set<KpiGroupId> m_kpiGroupIdsToPoll;

    /**
     * Entity that configured the measurements.  I.e. where to send the results.
     * TODO: Extend to allow multiple managing entities.
     */
    MessagingEntity m_managingEntity;

    /**
     * Timer used to poll for KPI results.
     * TODO: Extend to allow multiple timers for different configured measurement sets.
     */
    threeway::TimerHandle m_kpiPollTimerHandle;
    
    /**
     * Below memeber variables are PM related paramaters which are passed
     * in KPIConfigure req to KPIManager.
     */
    u32 m_periodicUploadIntervalInMins;
    u32 m_collectionIntervalInMins;
    u32 m_cummCollectionInterval;
    u32 m_perodicUploadPhaseAllignInMin;
    bool m_phaseShiftTmrExp;
    u32 m_phaseShiftInSecs;

    //Whenever a readKPIs request is sent to messaging entity/entities and if the read request has to be followed by a collection request 
    //to TR-069 process, an entry is created for that messaging entity in the set m_entitiesYetToRespond. After receiving response
    //for the read request from messaging entity, corresponding entry will be removed from the set. When set size becomes zero,
    //it means that TR-069 has got latest information from all the messaging entities and collection request can be issued.
    bool m_isCollectionReqPending;
    std::set<MessagingEntity> m_entitiesYetToRespond;

};

#endif
