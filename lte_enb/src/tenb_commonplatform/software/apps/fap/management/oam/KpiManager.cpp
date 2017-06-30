
///////////////////////////////////////////////////////////////////////////////
//
// KpiManager.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <messaging/messages/common/KpiReadReq.h>
#include <messaging/messages/common/KpiCollectionReq.h>
#include <messaging/messages/common/L2TimerNotify.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "KpiManager.h"



///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

KpiManager::KpiManager(TimerEngineInterface& timerEngine,
                       TimerNotifyInterface& timerNotifyInterface,
                       SendMessageInterface& messageSender) :
    m_timerEngine(timerEngine),
    m_timerNotifyInterface(timerNotifyInterface),
    m_messageSender(messageSender),
    m_managingEntity(ENTITY_INVALID),
    m_kpiPollTimerHandle(NULL_TIMER),
    m_periodicUploadIntervalInMins(0),
    m_collectionIntervalInMins(0),
    m_cummCollectionInterval(0),
    m_perodicUploadPhaseAllignInMin(0),
    m_phaseShiftTmrExp(false),
    m_phaseShiftInSecs(0),
    m_isCollectionReqPending(false)
{
    ENTER();
    
    EXIT();
}

KpiManager::~KpiManager()
{
    ENTER();

    EXIT();
}

void KpiManager::RegisterKpiEntities(MessagingEntity entity, const set<KpiGroupId>& kpiGroupIds)
{
    ENTER();

    TRACE_PRINTF_LEV(TRACE_INFO,"Registering KPIs for entity %s", MessagingEntityToString(entity));

    // Loop through the group IDs and associate each with the given entity.
    set<KpiGroupId>::const_iterator iter = kpiGroupIds.begin();
    while(iter != kpiGroupIds.end())
    {
        KpiGroupId kpiGroupId = *iter;
        m_kpiEntities[kpiGroupId] = entity;

        ++iter;
    }

    EXIT();
}

void KpiManager::ConfigureMeasurements(MessagingEntity managingEntity, const KpiConfigureReq& kpiConfigureReq)
{
    ENTER();
    
    TRACE_PRINTF_LEV(TRACE_INFO,"Configuring KPIs for entity %s: %s", MessagingEntityToString(managingEntity), kpiConfigureReq.ToString().c_str());

    m_kpiGroupIdsToPoll = kpiConfigureReq.GetKpiGroupIds();
    m_managingEntity = managingEntity;
    m_periodicUploadIntervalInMins = kpiConfigureReq.GetPerodicUploadIntervalSecs() / SecInMin;
    m_collectionIntervalInMins = kpiConfigureReq.GetMeasurementIntervalSecs() / SecInMin;
    m_perodicUploadPhaseAllignInMin = kpiConfigureReq.GetPerodicUploadPhaseAllignInMin();
    
    AllignToFirstCollectionPeriod();
    
    EXIT();
}

u32 KpiManager::AllignToPhaseShift(void)
{
    ENTER();
    
    TimeWrap now;
    TimeStructure timeStructure = now.GetTimeStructure();
    u32 phaseShiftInSecs = 0;
    u32 secsAdj = 0;
    u32 minsAdj = 0;
    
    //For example say PUT is 00.30 min, periodic upload of file should happen at 24hr + 30 min
    //Here reference time 30 min is added to PUI so that periodic upload of file happen at reference time
    //Reference time is choosen so that OMC/ftp sever shall manages femto without overload
    //Web reference for finding differnce between given time intervals
    //http://www.grun1.com/utils/timeDiff.cfm
    
    phaseShiftInSecs = (HoursInDay * MinInHour) - ((timeStructure.theHour * MinInHour)+timeStructure.theMinutes);
    minsAdj = phaseShiftInSecs % m_periodicUploadIntervalInMins;
    minsAdj = (timeStructure.theSeconds>0)? (minsAdj - 1) : minsAdj;
    secsAdj = (timeStructure.theSeconds>0)? (SecInMin - timeStructure.theSeconds) : 0;
    phaseShiftInSecs = (minsAdj * SecInMin) + secsAdj;
    phaseShiftInSecs += (m_perodicUploadPhaseAllignInMin * SecInMin);
    
    return phaseShiftInSecs;
    
    EXIT(); 
}

void KpiManager::AllignToFirstCollectionPeriod(void)
{
    ENTER();
    
    TimeWrap now;
    TimeStructure timeStructure = now.GetTimeStructure();
    u32 minsAdj = 0;
    u32 deltaTimeDiff = 0;
    u32 secsAdj = 0;
    
    //For example say CollectionInterval is 15min, current time is "05.12.00"
    //The first collection interval shall be 3 min so that from the second collection interval
    //onwards it will be alligned to actual clock
    //Web reference for finding differnce between given time intervals
    //http://www.grun1.com/utils/timeDiff.cfm 
    
    minsAdj = m_collectionIntervalInMins - (timeStructure.theMinutes % m_collectionIntervalInMins);
    minsAdj = (timeStructure.theSeconds>0)? (minsAdj - 1) : minsAdj; 	    
    secsAdj = (timeStructure.theSeconds>0)? (SecInMin - timeStructure.theSeconds) : 0;
    deltaTimeDiff = (minsAdj * SecInMin) + secsAdj;
   
    TRACE_PRINTF_LEV(TRACE_INFO,"deltaTimeDiff [%d] theMinutes[%d] theSeconds[%d] collectionPeriod[%d]", deltaTimeDiff, timeStructure.theMinutes, timeStructure.theSeconds, m_collectionIntervalInMins );
 
    // Delete any existing timer.
    DeleteTimer();
    
    // Create and start timer for delta time so that next timer will allign with actual clock.
    CreateTimer("KPI Poll Timer-1", deltaTimeDiff * MicroSecInSec, TimerEngineInterface::TIMER_SINGLE_SHOT_WITHOUT_DELETE);

    EXIT();
}

void KpiManager::sendUploadRequest(const MessagingEntity& messageEntity)
{
    ENTER();

    m_entitiesYetToRespond.erase(messageEntity);

    if(m_entitiesYetToRespond.size())
    {
       return;
    }

    KpiCollectionReq kpiCollectionReq;
    m_messageSender.SendMessage(kpiCollectionReq, ENTITY_TR069, ENTITY_OAM);
    m_isCollectionReqPending = false;

    EXIT();
}

bool KpiManager::HandleTimerExpiry(TimerHandle timerHandle)
{
    ENTER();
    
    if(timerHandle == m_kpiPollTimerHandle)
    {
        TRACE_PRINTF_LEV(TRACE_INFO,"KPI poll timer has expired... so we're off to poll for KPIs");

        EventNotify evntntfy;
        m_messageSender.SendMessage(evntntfy, ENTITY_SM, ENTITY_OAM);
 
        Timer* foundTimer = NULL;
	foundTimer = m_timerEngine.FindTimer(m_kpiPollTimerHandle);
	
	if ( foundTimer && (0 == strcmp ("KPI Poll Timer-1", foundTimer->GetTimerName())) )
	{
	   DeleteTimer();
	   
	   m_phaseShiftInSecs = AllignToPhaseShift();
	   TRACE_PRINTF_LEV(TRACE_INFO,"PhaseShift required is %d sec", m_phaseShiftInSecs );
	
	   if (m_phaseShiftInSecs > 0)
	   {   
	      if ( m_phaseShiftInSecs >= (m_collectionIntervalInMins * SecInMin) )
	      {
	         // Create and start timer to go off in specified Collection period
		 CreateTimer("KPI Poll Timer-2", m_collectionIntervalInMins * SecInMin * MicroSecInSec, TimerEngineInterface::TIMER_REPEAT);
                 TRACE_PRINTF_LEV(TRACE_INFO,"KPI Poll Timer-2 Condition: m_phaseShiftInSecs(%d) >= m_collectionIntervalInSecs(%d)", m_phaseShiftInSecs, (m_collectionIntervalInMins * SecInMin));						 
	      }
	      else if ( m_phaseShiftInSecs < (m_collectionIntervalInMins * SecInMin) )
	      {
	         // Create and start timer to go off in specified Collection period
		 CreateTimer("KPI Poll Timer-2", m_phaseShiftInSecs * MicroSecInSec, TimerEngineInterface::TIMER_REPEAT);
                 TRACE_PRINTF_LEV(TRACE_INFO,"KPI Poll Timer-2 Condition: m_phaseShiftInSecs(%d) < m_collectionIntervalInSecs(%d)", m_phaseShiftInSecs, (m_collectionIntervalInMins * SecInMin));						 
	      }
	   }   
	   else
	   {
	      TRACE_PRINTF_LEV(TRACE_INFO,"No Phase shift Allignment is required");
	      ActOnKpiT2Expiry(true);
	   }
	}
	else if ( foundTimer && (0 == strcmp ("KPI Poll Timer-2", foundTimer->GetTimerName())) )
	{
	   ActOnKpiT2Expiry(); 
	}
	
        RETURN(true);
    }

    RETURN(false);
}

void KpiManager::ActOnKpiT2Expiry(bool noPhaseShiftReq)
{
   ENTER();
   
   if ( true == noPhaseShiftReq )
   {
      m_phaseShiftInSecs = 0;
   }

   if ( m_phaseShiftInSecs > (m_collectionIntervalInMins * SecInMin) )
   {
      m_phaseShiftInSecs -= (m_collectionIntervalInMins * SecInMin);
   }
   else
   {
      m_phaseShiftInSecs = 0;
   }
   
   TRACE_PRINTF_LEV(TRACE_INFO,"Current m_phaseShift value is %d secs", m_phaseShiftInSecs);
   
   if ( m_phaseShiftInSecs <= 0 )
   {
       //PhaseShift allignment completed.
       m_phaseShiftTmrExp = true;
       DeleteTimer();
   }
   else if ( m_phaseShiftInSecs > (m_collectionIntervalInMins * SecInMin) ) 
   {
      //This means phaseShift allignment is not yet completed
      TRACE_PRINTF_LEV(TRACE_INFO,"ActOnKpiT2Expiry:Nothing TO DO");
   }
   else if ( m_phaseShiftInSecs < (m_collectionIntervalInMins * SecInMin) )
   {
       TRACE_PRINTF_LEV(TRACE_INFO,"ActOnKpiT2Expiry:ModifyTimer KPI Poll Timer-2 timeout value to %d secs", m_phaseShiftInSecs);
       //modify the existing timer Timeout Value
       m_timerEngine.ModifyTimer(m_kpiPollTimerHandle, m_phaseShiftInSecs * MicroSecInSec);
   }
    
   if ( m_phaseShiftTmrExp )
   {
       //PhaseShift allignment completed, now regular collection timer can be run
       TRACE_PRINTF_LEV(TRACE_INFO,"PhaseShiftTmrExp Expired continuing with regular Collection Interval %d sec", m_collectionIntervalInMins * SecInMin);
       CreateTimer("KPI Poll Timer-3", m_collectionIntervalInMins * SecInMin * MicroSecInSec, TimerEngineInterface::TIMER_REPEAT);
   }   
   
   EXIT();  
}

void KpiManager::SendPollKpis(void)
{
   ENTER();
   
   TRACE_MSG("KpiManager::SendPollKpis, now polling for KPI's ");
   KpiCollectionReq kpiCollectionReq;

   m_cummCollectionInterval += m_collectionIntervalInMins;
      
   if ( ( m_cummCollectionInterval == m_periodicUploadIntervalInMins ) && !m_phaseShiftTmrExp )
   {
      TRACE_PRINTF_LEV(TRACE_INFO,"Condition: m_cummCollectionInterval == m_periodicUploadIntervalInMins is met, send CollectionReq to Tr069  cummint:%d,uploadint:%d",m_cummCollectionInterval,m_periodicUploadIntervalInMins);
      //m_messageSender.SendMessage(kpiCollectionReq, ENTITY_TR069, ENTITY_OAM);
      m_isCollectionReqPending = true;
      m_cummCollectionInterval = 0;
   }
   else if ( m_phaseShiftTmrExp )
   {
      //PhaseShift timer/allignment completed, required to poll now!!
      TRACE_PRINTF_LEV(TRACE_INFO,"m_phaseShiftTmrExp Timer is expired, send CollectionReq to Tr069");
      //m_messageSender.SendMessage(kpiCollectionReq, ENTITY_TR069, ENTITY_OAM);
      m_isCollectionReqPending = true;
      m_phaseShiftTmrExp = false;
      m_cummCollectionInterval = 0;
   }
   else
   {
      TRACE_PRINTF_LEV(TRACE_VERBOSE,"None of Pre-condition met to send KPI Collection Req!!");
   } 
   PollKpisSendToManagingEntity(true, m_isCollectionReqPending);

   //No collection request need to be sent this time. So clear m_entitiesYetToRespond set
   if(!m_isCollectionReqPending)
   {
      m_entitiesYetToRespond.clear();
   }
   
   EXIT();
}

void KpiManager::CreateTimer(const std::string& timerName, u32 timeoutPeriodMs, TimerEngineInterface::TimerMode timerMode)
{
    ENTER();
    
    NotifyL2TimeOutValue(timeoutPeriodMs);
    
    m_kpiPollTimerHandle = m_timerEngine.CreateTimer(timerName,
                                                 timeoutPeriodMs,
                                                 m_timerNotifyInterface,
                                                 TimerEngineInterface::TIMER_START_NOW,
                                                 timerMode);	
    
    EXIT();
}

void KpiManager::DeleteTimer(void)
{
   ENTER();
   
   Timer* foundTimer = NULL;
   foundTimer = m_timerEngine.FindTimer(m_kpiPollTimerHandle);
   
   if (foundTimer && m_kpiPollTimerHandle)
   {
       TRACE_PRINTF_LEV(TRACE_INFO,"Deleting Timer %s", foundTimer->GetTimerName());
       m_timerEngine.DeleteTimer(m_kpiPollTimerHandle);
       m_kpiPollTimerHandle = NULL_TIMER;
   }
   else
   {
      TRACE_PRINTF_LEV(TRACE_VERBOSE,"Timer not found for deletion");
   } 
   
   EXIT(); 
}
	   				    				    
void KpiManager::PollKpisSendToManagingEntity(bool storeMessagingEntities, bool isCollectionReqPending)
{
    ENTER();
    
    // Go poll all our KPI-gathering entities.
    // Send results directly to managing entity.
    std::set<KpiGroupId>::const_iterator iter = m_kpiGroupIdsToPoll.begin();
    std::map<MessagingEntity, std::set<KpiGroupId> > messageEntities;
    while(iter != m_kpiGroupIdsToPoll.end())
    {
        KpiGroupId kpiGroupIdToPoll = *iter;
        // Look for this group ID in our map of entities.
        KpiEntities::const_iterator entityIter = m_kpiEntities.find(kpiGroupIdToPoll);
        if(entityIter != m_kpiEntities.end())
        {
            messageEntities[entityIter->second].insert(kpiGroupIdToPoll);
        }
        else
        {
            TRACE_PRINTF_LEV(TRACE_WARNING,
                             "Would love to poll for %s but can't find an entity to poll.",
                              KpiGroup::GetKpiGroupDescription(kpiGroupIdToPoll));
        }

        ++iter;
    }

    map<MessagingEntity, std::set<KpiGroupId> >::const_iterator messageEntitiesIter = messageEntities.begin();
    for(;messageEntitiesIter != messageEntities.end(); messageEntitiesIter++)
    {
        // Send a read request to the entity.  Tell it to send result
        // to the managing entity.
        KpiReadReq kpiReadReq(messageEntitiesIter->second, 
                              KPI_MEASUREMENT_SET_INTERVAL, 
                              KpiReadReq::READ_AND_RESET_KPIS, 
                              isCollectionReqPending, 
                              m_periodicUploadIntervalInMins * SecInMin);
        m_messageSender.SendMessage(kpiReadReq, messageEntitiesIter->first, m_managingEntity);
        if(storeMessagingEntities)
        {
            m_entitiesYetToRespond.insert(messageEntitiesIter->first);
        }
    }

    EXIT();
 }

void KpiManager::PollKpisWithoutReset(bool pollForTotals) const
{
    ENTER();

    KpiEntities::const_iterator iter = m_kpiEntities.begin();
    std::map<MessagingEntity, set<KpiGroupId> > managingEntities;
    while(iter != m_kpiEntities.end())
    {
        managingEntities[iter->second].insert(iter->first);
        ++iter;
    }

    std::map<MessagingEntity, set<KpiGroupId> >::iterator managingEntitiesIter = managingEntities.begin();
    for(;managingEntitiesIter != managingEntities.end(); managingEntitiesIter++)
    {
        if(pollForTotals)
        {
            KpiReadReq kpiReadReq(managingEntitiesIter->second, KPI_MEASUREMENT_SET_NO_RESET, KpiReadReq::READ_KPIS);
            TRACE("Polling KPIs (totals since power on) without reset", kpiReadReq.ToString());
            m_messageSender.SendMessage(kpiReadReq, managingEntitiesIter->first, ENTITY_OAM);
        }
        else
        {
            KpiReadReq kpiReadReq(managingEntitiesIter->second, KPI_MEASUREMENT_SET_INTERVAL, KpiReadReq::READ_KPIS);
            TRACE("Polling KPIs (values since last periodic reset) without reset", kpiReadReq.ToString());
            m_messageSender.SendMessage(kpiReadReq, managingEntitiesIter->first, ENTITY_OAM);
        }
    }

    EXIT();
}

void KpiManager::SendKpiCollecReqNow(u32 bootStrapStatus) const
{
   ENTER();
   
   //Make sure KPIs are uploaded at startup if bootstrap is completed.
   if(bootStrapStatus)
   {
      KpiCollectionReq kpiCollectionReq(true);
      m_messageSender.SendMessage(kpiCollectionReq, ENTITY_TR069, ENTITY_OAM);
      TRACE_PRINTF_LEV(TRACE_INFO,"Boot Strap is completed, so need collect the couters for last periodic interval");
   }
   else
   {
      TRACE_PRINTF_LEV(TRACE_INFO,"Boot Strap is not completed, FAP is starting for very fist time");
   }   
   
   EXIT();
}

void KpiManager::NotifyL2TimeOutValue(u32 timeoutPeriodMs) const
{
   ENTER();
   
   //Inform stack application about the timeout value so that timer are alligned properly
   L2TimerNotify l2timernotify(timeoutPeriodMs);
   m_messageSender.SendMessage(l2timernotify, ENTITY_SM, ENTITY_OAM);
   TRACE_PRINTF_LEV(TRACE_INFO,"L2TimerNotify timeoutVal %d",timeoutPeriodMs);
   
   EXIT();
}
