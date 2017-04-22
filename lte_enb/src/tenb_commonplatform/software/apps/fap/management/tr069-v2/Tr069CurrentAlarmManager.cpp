///////////////////////////////////////////////////////////////////////////////
//
// Tr069CurrentAlarmManager
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <system/Trace.h>
#include <platform/RadisysFapAlarmId.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069CurrentAlarmManager.h"
#include "Tr069MultiInstanceMibObjectManager.h"
#include "MibHelper.h"

using namespace std;
using namespace threeway;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{
   void CurrentAlarmManager::SupportedAlarmEvent( const SupportedAlarm & supportedAlarm, const AlarmEvent & alarmEvent )
   {
      bool clearedAlarm = (alarmEvent.GetSeverity() == AlarmEvent::ALARM_SEVERITY_CLEARED );

      if(clearedAlarm)
      {
         ClearAlarm( supportedAlarm, alarmEvent );
      }
      else
      {
         RaiseAlarm( supportedAlarm, alarmEvent );
      }

      UpdateHighestSeverityAlarmStatus();
   }

   void CurrentAlarmManager::AddExpeditedAlarmsToParameterList( ParameterList & parameterList )
   {
   }

   void CurrentAlarmManager::RaiseAlarm( const SupportedAlarm & supportedAlarm, const AlarmEvent & alarmEvent )
   {
      string probableCause(supportedAlarm.probableCause);
      map<string, MibDN >::iterator i = m_raisedCurrentAlarms.find( probableCause );

      shared_ptr<Tr069MultiInstanceObject> m_multiInstanceObject = MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.SupportedAlarm.");
      u32 reporting = 0;
      for(u32 idx = 0; idx < m_multiInstanceObject->GetNumberOfEntries(); idx++)
      {
         string cause;
         MibDN fap0 = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_TR196_SUPPORTED_ALARM, idx );
         if( m_mib.IsMibAttributePresent(fap0, PARAM_ID_ALARM_PROBABLE_CAUSE))
         {
            m_mib.GetMibAttribute(fap0, PARAM_ID_ALARM_PROBABLE_CAUSE, cause );
            TRACE_PRINTF("Supported probable cause is ...%s", cause.c_str());
         }
         if (cause.compare(supportedAlarm.probableCause) == 0)
         {
            m_mib.GetMibAttribute(fap0, PARAM_ID_ALARM_REPORTING_MECHANISM, reporting );
            TRACE_PRINTF("Supported reporting mechanism ...%d", reporting);
            break;
         }
      }

      if(reporting != ALARM_REPORTING_MECHANISM_DISABLED)
      {
         if( i == m_raisedCurrentAlarms.end() )
         {
            shared_ptr<FapAlarmId> alarmId = dynamic_pointer_cast<FapAlarmId>(alarmEvent.GetAlarmId());

            MibAttributeValues attr;
            string addText = "CellId is ";
            u32 cId = u32(alarmId->GetNumericAlarmId())/(u32(FapAlarmId::MAX_ALARMS));
            stringstream ss;
            ss << (cId+1);
            addText +=ss.str();
            attr.AddAttribute(PARAM_ID_ALARM_EVENT_TYPE, u32(alarmEvent.GetAlarmType()));
            attr.AddAttribute(PARAM_ID_ALARM_PROBABLE_CAUSE, string(supportedAlarm.probableCause));
            attr.AddAttribute(PARAM_ID_ALARM_SPECIFIC_PROBLEM, string(alarmEvent.GetAdditionalInfo()) );
            attr.AddAttribute(PARAM_ID_ALARM_PERCEIVED_SEVERITY, u32(alarmEvent.GetSeverity()));
            attr.AddAttribute(PARAM_ID_ALARM_IDENTIFIER, u32(alarmId->GetNumericAlarmId()));
            attr.AddAttribute(PARAM_ID_ALARM_RAISED_TIME, u32(alarmEvent.GetObservationTime().GetUnixTime()));
            attr.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, addText );
            attr.AddAttribute(PARAM_ID_ALARM_ADDITIONAL_TEXT, addText );
            attr.AddAttribute(PARAM_ID_ALARM_ADDITIONAL_INFORMATION, string(alarmEvent.GetAddtnlInfo()) );

            // Check the lifetime of alarm, Transient means warning (update to Logged/History List).   
            if(alarmEvent.GetLifetime() == AlarmEvent::ALARM_EVENT_NONTRANSIENT)
            {
               // New current alarms
                  shared_ptr<MibCreateObjectReq> mibCreateObjectReq = MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.CurrentAlarm.")->New(attr);

                  // Should not be possible to fail - suggests MIB provisioned incorrectly;
                  if(mibCreateObjectReq)
                  {
                     u32 current_entries; 
                     MibDN fap0 = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP, 0);
                     m_mib.GetMibAttribute(fap0, PARAM_ID_ALARM_MAX_CURRENT_ENTRIES, current_entries );

                     MibDN dn = mibCreateObjectReq->GetParentDn();
                     u32 instance = mibCreateObjectReq->GetChildRdn().GetMibObjectInstance();
                     TRACE_PRINTF("Current instance for Current Alarm%d", instance);
                     if (instance >= current_entries)
                     {
                        // If current instance is greater than max current alarm entries,reset to the zero.
                        u32 instanceToDelete = (instance) % current_entries;
                        MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.CurrentAlarm.")->Delete(instanceToDelete);
                        u32 newMibInstance = instanceToDelete;
                        MibRDN childRdn(MIB_OBJECT_CLASS_TR196_CURRENT_ALARM, newMibInstance);
                        mibCreateObjectReq.reset(new MibCreateObjectReq(dn, childRdn, attr));
                        dn.push_back(mibCreateObjectReq->GetChildRdn());
                     }
                     else
                     {
                        // update the next available instance. 
                        dn.push_back(mibCreateObjectReq->GetChildRdn());
                     }
                     // update the Mibdn with probable cause.  
                     m_raisedCurrentAlarms[probableCause] = dn;
                     m_messenger.SendMessage( *mibCreateObjectReq, ENTITY_MIB, ENTITY_TR069 );
                     // update Managed Object Instance
                     ostringstream manObjInst;
                     manObjInst << "Device.FaultMgmt.CurrentAlarm." << (mibCreateObjectReq->GetChildRdn().GetMibObjectInstance()+1) <<".";
                     attr.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, manObjInst.str() );
                     Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, attr, ENTITY_TR069);
                  }
                  else
                  {
                     TRACE_PRINTF("Addition to CurrentAlarm failure.");
                  }

               MibAttributeValues attr1;
               attr1.AddAttribute(PARAM_ID_ALARM_EVENT_TYPE, u32(alarmEvent.GetAlarmType()));
               attr1.AddAttribute(PARAM_ID_ALARM_PROBABLE_CAUSE, string(supportedAlarm.probableCause));
               attr1.AddAttribute(PARAM_ID_ALARM_SPECIFIC_PROBLEM, string(alarmEvent.GetAdditionalInfo()) );
               attr1.AddAttribute(PARAM_ID_ALARM_PERCEIVED_SEVERITY, u32(alarmEvent.GetSeverity()));
               attr1.AddAttribute(PARAM_ID_ALARM_IDENTIFIER, u32(alarmId->GetNumericAlarmId()));
               attr1.AddAttribute(PARAM_ID_ALARM_EVENT_TIME, u32(alarmEvent.GetObservationTime().GetUnixTime()));
               attr1.AddAttribute(PARAM_ID_ALARM_NOTIFICATION_TYPE, u32(NewAlarm));
               attr1.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, string("Unspecified Managed Object Instance") );
               attr1.AddAttribute(PARAM_ID_ALARM_ADDITIONAL_TEXT, addText);
               attr1.AddAttribute(PARAM_ID_ALARM_ADDITIONAL_INFORMATION, string(alarmEvent.GetAddtnlInfo()) );

               // Addition to Expedited alarms        
               if(reporting == ALARM_REPORTING_MECHANISM_EXPEDITED)
               {
                  shared_ptr<MibCreateObjectReq> mibCreateObjectReq1 = MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.ExpeditedEvent.")->New(attr1);

                  // Should not be possible to fail - suggests MIB provisioned incorrectly;
                  if(mibCreateObjectReq1)
                  {

                     MibDN dn = mibCreateObjectReq1->GetParentDn();
                     u32 instance = mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance();
                     TRACE_PRINTF("Expedited current instance %d", instance);
                     if (instance >= MAX_EXPEDITED_ALARMS)
                     {
                        // If current instance is greater than max expedited event entries,reset to the zero.
                        u32 instanceToDelete = (instance) % MAX_EXPEDITED_ALARMS;
                        MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.ExpeditedEvent.")->Delete(instanceToDelete);
                        u32 newMibInstance = instanceToDelete;
                        MibRDN childRdn(MIB_OBJECT_CLASS_TR196_EXPEDITED_EVENT, newMibInstance);
                        mibCreateObjectReq1.reset(new MibCreateObjectReq(dn, childRdn, attr1));
                        dn.push_back(mibCreateObjectReq1->GetChildRdn());
                     }
                     else
                     {
                        // update the next available instance. 
                        dn.push_back(mibCreateObjectReq1->GetChildRdn());
                     }
                     // update the Mibdn with probable cause.  
                     m_raisedExpeditedAlarms[probableCause] = dn;
                     m_messenger.SendMessage( *mibCreateObjectReq1, ENTITY_MIB, ENTITY_TR069 );
                     // update Managed Object Instance
                     ostringstream manObjInst;
                     manObjInst << "Device.FaultMgmt.ExpeditedEvent." << (mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance()+1) <<".";
                     attr1.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, manObjInst.str() );
                     Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, attr1, ENTITY_TR069);
                  }
                  else
                  {
                     TRACE_PRINTF("Addition to Expedited failure.");
                  }
               }
                           // Addition to Queued alarms        
               if(reporting == ALARM_REPORTING_MECHANISM_QUEUED)
               {
                  shared_ptr<MibCreateObjectReq> mibCreateObjectReq1 = MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.QueuedEvent.")->New(attr1);

                  // Should not be possible to fail - suggests MIB provisioned incorrectly;
                  if(mibCreateObjectReq1)
                  {

                     MibDN dn = mibCreateObjectReq1->GetParentDn();
                     u32 instance = mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance();
                     TRACE_PRINTF("QUEUED current instance %d", instance);
                     if (instance >= MAX_QUEUED_ALARMS)
                     {
                        // If current instance is greater than max queued event entries,reset to the zero.
                        u32 instanceToDelete = (instance) % MAX_QUEUED_ALARMS;
                        MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.QueuedEvent.")->Delete(instanceToDelete);
                        u32 newMibInstance = instanceToDelete;
                        MibRDN childRdn(MIB_OBJECT_CLASS_QUEUED_EVENT, newMibInstance);
                        mibCreateObjectReq1.reset(new MibCreateObjectReq(dn, childRdn, attr1));
                        dn.push_back(mibCreateObjectReq1->GetChildRdn());
                     }
                     else
                     {
                        // update the next available instance. 
                        dn.push_back(mibCreateObjectReq1->GetChildRdn());
                     }
                     // update the Mibdn with probable cause.  
                     m_raisedQueuedAlarms[probableCause] = dn;
                     m_messenger.SendMessage( *mibCreateObjectReq1, ENTITY_MIB, ENTITY_TR069 );
                     // update Managed Object Instance
                     ostringstream manObjInst;
                     manObjInst << "Device.FaultMgmt.QueuedEvent." << (mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance()+1) <<".";
                     attr1.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, manObjInst.str() );
                     Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, attr1, ENTITY_TR069);
                  }
                  else
                  {
                     TRACE_PRINTF("Addition to Queued Alarm failure.");
                  }
               }
 
            }
            // Addition to History alarms 
            MibAttributeValues attr1;
            attr1.AddAttribute(PARAM_ID_ALARM_EVENT_TYPE, u32(alarmEvent.GetAlarmType()));
            attr1.AddAttribute(PARAM_ID_ALARM_PROBABLE_CAUSE, string(supportedAlarm.probableCause));
            attr1.AddAttribute(PARAM_ID_ALARM_SPECIFIC_PROBLEM, string(alarmEvent.GetAdditionalInfo()) );
            attr1.AddAttribute(PARAM_ID_ALARM_PERCEIVED_SEVERITY, u32(alarmEvent.GetSeverity()));
            attr1.AddAttribute(PARAM_ID_ALARM_IDENTIFIER, u32(alarmId->GetNumericAlarmId()));
            attr1.AddAttribute(PARAM_ID_ALARM_EVENT_TIME, u32(alarmEvent.GetObservationTime().GetUnixTime()));
            attr1.AddAttribute(PARAM_ID_ALARM_NOTIFICATION_TYPE, u32(NewAlarm));
            attr1.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, string("Unspecified Managed Object Instance") );
            attr1.AddAttribute(PARAM_ID_ALARM_ADDITIONAL_TEXT, addText );
            attr1.AddAttribute(PARAM_ID_ALARM_ADDITIONAL_INFORMATION, string(alarmEvent.GetAddtnlInfo()) );

            shared_ptr<MibCreateObjectReq> mibCreateObjectReq1 = MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.HistoryEvent.")->New(attr1);

            // Should not be possible to fail - suggests MIB provisioned incorrectly;
            if(mibCreateObjectReq1)
            {

               MibDN dn = mibCreateObjectReq1->GetParentDn();
               u32 instance = mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance();

               TRACE_PRINTF("History current instance %d", instance);
               if (instance >= MAX_HISTORY_ALARMS && instance != 0)
               {
                  // If current instance is greater than max history entries,reset to the zero.
                  u32 instanceToDelete = (instance) % MAX_HISTORY_ALARMS;
                  MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.HistoryEvent.")->Delete(instanceToDelete);
                  u32 newMibInstance = instanceToDelete;
                  MibRDN childRdn(MIB_OBJECT_CLASS_TR196_HISTORY_EVENT, newMibInstance);
                  mibCreateObjectReq1.reset(new MibCreateObjectReq(dn, childRdn, attr1));
                  dn.push_back(mibCreateObjectReq1->GetChildRdn());
               }
               else
               {
                  // update the next available instance. 
                  dn.push_back(mibCreateObjectReq1->GetChildRdn());
               }
               // update the Mibdn with probable cause.  
               m_raisedHistoryAlarms[probableCause] = dn;
               m_messenger.SendMessage( *mibCreateObjectReq1, ENTITY_MIB, ENTITY_TR069 );
               // update Managed Object Instance
               ostringstream manObjInst;
               manObjInst << "Device.FaultMgmt.HistoryEvent." << (mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance()+1) <<".";
               attr1.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, manObjInst.str() );
               Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, attr1, ENTITY_TR069);
            }
            else
            {
               TRACE_PRINTF("Addition of TRANSIENT alarm to HistoryEvent is failure.");
            }
         }
         else
         {
            // Alarm is generated again.  
            MibDN dn =  m_raisedCurrentAlarms[probableCause];
            MibAttributeValues attr1;
            attr1.AddAttribute(PARAM_ID_ALARM_CHANGED_TIME, u32(alarmEvent.GetObservationTime().GetUnixTime()));
            // Update the changedTime for the same current alarm.  
            Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, attr1, ENTITY_TR069);

            dn =  m_raisedHistoryAlarms[probableCause];
            MibAttributeValues attr;
            // Update the EventTime and Notification type for the same history alarm event.  
            attr.AddAttribute(PARAM_ID_ALARM_EVENT_TIME, u32(alarmEvent.GetObservationTime().GetUnixTime()));
            attr.AddAttribute(PARAM_ID_ALARM_NOTIFICATION_TYPE, u32(ChangedAlarm));
            Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, attr, ENTITY_TR069);

            dn =  m_raisedExpeditedAlarms[probableCause];
            if(reporting == ALARM_REPORTING_MECHANISM_EXPEDITED)
            {
               MibAttributeValues attr2;
               // Update the EventTime and Notification type for the same expedited event.  
               attr2.AddAttribute(PARAM_ID_ALARM_EVENT_TIME, u32(alarmEvent.GetObservationTime().GetUnixTime()));
               attr2.AddAttribute(PARAM_ID_ALARM_NOTIFICATION_TYPE, u32(ChangedAlarm));
               Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, attr2, ENTITY_TR069);
            }
            else
            {
               TRACE_PRINTF("Supported reporting mechanism is changed from Expedited so no need to notify the EventTime of Expedited alarm");
            }
         }
      }
      else
      {
         TRACE_PRINTF("Reporting mechanism is Disabled now, Fap Ignores the Alarm%d", reporting);
      }
   }

   void CurrentAlarmManager::ClearAlarm( const SupportedAlarm & supportedAlarm, const AlarmEvent & alarmEvent )
   {
      string probableCause(supportedAlarm.probableCause);
      map<string, MibDN >::iterator i = m_raisedCurrentAlarms.find( probableCause );

      shared_ptr<Tr069MultiInstanceObject> m_multiInstanceObject = MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.SupportedAlarm.");
      u32 reporting = 0;
      for(u32 idx = 0; idx < m_multiInstanceObject->GetNumberOfEntries(); idx++)
      {
         string cause;
         MibDN fap0 = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_TR196_SUPPORTED_ALARM, idx );
         if( m_mib.IsMibAttributePresent(fap0, PARAM_ID_ALARM_PROBABLE_CAUSE))
         {
            m_mib.GetMibAttribute(fap0, PARAM_ID_ALARM_PROBABLE_CAUSE, cause );
            TRACE_PRINTF("Supported probable cause is ...%s", cause.c_str());
         }
         if (cause.compare(supportedAlarm.probableCause) == 0)
         {
            m_mib.GetMibAttribute(fap0, PARAM_ID_ALARM_REPORTING_MECHANISM, reporting );
            TRACE_PRINTF("Supported reporting mechanism ...%d", reporting);
            break;
         }
      }

      if(reporting !=ALARM_REPORTING_MECHANISM_DISABLED)
      {
         if( i != m_raisedCurrentAlarms.end() )
         {
            shared_ptr<FapAlarmId> alarmId = dynamic_pointer_cast<FapAlarmId>(alarmEvent.GetAlarmId());

            u32 max_current_entries; 
            MibDN fap0 = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP, 0);
            m_mib.GetMibAttribute(fap0, PARAM_ID_ALARM_MAX_CURRENT_ENTRIES, max_current_entries );

            // Get the instance of current alarm, and delete from the mib.  
            u32 instance = i->second.back().GetMibObjectInstance();

            if (instance >= max_current_entries)
            {		
               u32 instanceToDelete = (instance) % max_current_entries;
               MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.CurrentAlarm.")->Delete(instanceToDelete);
            }
            else
            {
               // Delete current alarms
               MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.CurrentAlarm.")->Delete(instance);
            }
            m_raisedCurrentAlarms.erase(i);

            string addText = "CellId is ";
            u32 cId = u32(alarmId->GetNumericAlarmId())/(u32(FapAlarmId::MAX_ALARMS));
            stringstream ss;
            ss << (cId+1);
            addText +=ss.str();
            // Addition to History alarms
            MibAttributeValues attr1;
            attr1.AddAttribute(PARAM_ID_ALARM_EVENT_TYPE, u32(alarmEvent.GetAlarmType()));
            attr1.AddAttribute(PARAM_ID_ALARM_PROBABLE_CAUSE, string(supportedAlarm.probableCause));
            attr1.AddAttribute(PARAM_ID_ALARM_SPECIFIC_PROBLEM, string(alarmEvent.GetAdditionalInfo()) );
            attr1.AddAttribute(PARAM_ID_ALARM_PERCEIVED_SEVERITY, u32(alarmEvent.GetSeverity()));
            attr1.AddAttribute(PARAM_ID_ALARM_EVENT_TIME, u32(alarmEvent.GetObservationTime().GetUnixTime()));
            attr1.AddAttribute(PARAM_ID_ALARM_IDENTIFIER, u32(alarmId->GetNumericAlarmId()));
            attr1.AddAttribute(PARAM_ID_ALARM_NOTIFICATION_TYPE, u32(ClearedAlarm));
            attr1.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, addText );
            attr1.AddAttribute(PARAM_ID_ALARM_ADDITIONAL_TEXT, addText );
            attr1.AddAttribute(PARAM_ID_ALARM_ADDITIONAL_INFORMATION, string(alarmEvent.GetAddtnlInfo()) );

            shared_ptr<MibCreateObjectReq> mibCreateObjectReq1 = MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.HistoryEvent.")->New(attr1);
            // Should not be possible to fail - suggests MIB provisioned incorrectly;
            if(mibCreateObjectReq1)
            {

               MibDN dn = mibCreateObjectReq1->GetParentDn();
               u32 instance = mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance();

               TRACE_PRINTF("History current instance %d", instance);
               if (instance >= MAX_HISTORY_ALARMS)
               {
                  // If current instance is greater than max history entries,reset to the zero.
                  u32 instanceToDelete = (instance) % MAX_HISTORY_ALARMS;
                  MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.HistoryEvent.")->Delete(instanceToDelete);
                  u32 newMibInstance = instanceToDelete;
                  MibRDN childRdn(MIB_OBJECT_CLASS_TR196_HISTORY_EVENT, newMibInstance);
                  mibCreateObjectReq1.reset(new MibCreateObjectReq(dn, childRdn, attr1));
                  dn.push_back(mibCreateObjectReq1->GetChildRdn());
               }
               else
               {
                  // update the next available instance. 
                  dn.push_back(mibCreateObjectReq1->GetChildRdn());
               }
               // update the Mibdn with probable cause.  
               m_raisedHistoryAlarms[probableCause] = dn;
               m_messenger.SendMessage( *mibCreateObjectReq1, ENTITY_MIB, ENTITY_TR069 );
               // update Managed Object Instance
               ostringstream manObjInst;
               manObjInst << "Device.FaultMgmt.HistoryEvent." << (mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance()+1) <<".";
               attr1.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, manObjInst.str() );
               Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, attr1, ENTITY_TR069);
            }
            else
            {
               TRACE_PRINTF("Addition to HistoryEvent failure for cleared alarm.");
            }

            // Update Expedited alarms for cleared alarm
            if(reporting == ALARM_REPORTING_MECHANISM_EXPEDITED)
            {
               shared_ptr<MibCreateObjectReq> mibCreateObjectReq1 = MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.ExpeditedEvent.")->New(attr1);

               if(mibCreateObjectReq1)
               {
                  MibDN dn = mibCreateObjectReq1->GetParentDn();
                  u32 instance = mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance();
                  TRACE_PRINTF("Expedited current instance %d", instance);
                  if (instance >= MAX_EXPEDITED_ALARMS)
                  {
                     // If current instance is greater than max expedited event entries,reset to the zero.
                     u32 instanceToDelete = (instance) % MAX_EXPEDITED_ALARMS;
                     MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.ExpeditedEvent.")->Delete(instanceToDelete);
                     u32 newMibInstance = instanceToDelete;
                     MibRDN childRdn(MIB_OBJECT_CLASS_TR196_EXPEDITED_EVENT, newMibInstance);
                     mibCreateObjectReq1.reset(new MibCreateObjectReq(dn, childRdn, attr1));
                     dn.push_back(mibCreateObjectReq1->GetChildRdn());
                  }
                  else
                  {
                     // update the next available instance. 
                     dn.push_back(mibCreateObjectReq1->GetChildRdn());
                  }
                  // update the Mibdn with probable cause.  
                  m_raisedExpeditedAlarms[probableCause] = dn;
                  m_messenger.SendMessage( *mibCreateObjectReq1, ENTITY_MIB, ENTITY_TR069 );
                  // update Managed Object Instance
                  ostringstream manObjInst;
                  manObjInst << "Device.FaultMgmt.ExpeditedEvent." << (mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance()+1) <<".";
                  attr1.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, manObjInst.str() );
                  Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, attr1, ENTITY_TR069);
               }
               else
               {
                  TRACE_PRINTF("Addition to Expedited failure.");
               }
            }
               // Update queued alarms for cleared alarm
            if(reporting == ALARM_REPORTING_MECHANISM_QUEUED)
            {
               shared_ptr<MibCreateObjectReq> mibCreateObjectReq1 = MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.QueuedEvent.")->New(attr1);

               if(mibCreateObjectReq1)
               {

                  MibDN dn = mibCreateObjectReq1->GetParentDn();
                  u32 instance = mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance();
                  TRACE_PRINTF("Queued current instance %d", instance);
                  if (instance >= MAX_QUEUED_ALARMS)
                  {
                     // If current instance is greater than max queued event entries,reset to the zero.
                     u32 instanceToDelete = (instance) % MAX_QUEUED_ALARMS;
                     MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.QueuedEvent.")->Delete(instanceToDelete);
                     u32 newMibInstance = instanceToDelete;
                     MibRDN childRdn(MIB_OBJECT_CLASS_QUEUED_EVENT, newMibInstance);
                     mibCreateObjectReq1.reset(new MibCreateObjectReq(dn, childRdn, attr1));
                     dn.push_back(mibCreateObjectReq1->GetChildRdn());
                  }
                  else
                  {
                     // update the next available instance. 
                     dn.push_back(mibCreateObjectReq1->GetChildRdn());
                  }
                  // update the Mibdn with probable cause.  
                  m_raisedQueuedAlarms[probableCause] = dn;
                  m_messenger.SendMessage( *mibCreateObjectReq1, ENTITY_MIB, ENTITY_TR069 );
                  ostringstream manObjInst;
                  manObjInst << "Device.FaultMgmt.QueuedEvent." << (mibCreateObjectReq1->GetChildRdn().GetMibObjectInstance()+1) <<".";
                  attr1.AddAttribute(PARAM_ID_MANAGED_OBJECT_INSTANCE, manObjInst.str() );
                  Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn( dn, attr1, ENTITY_TR069);

               }
               else
               {
                  TRACE_PRINTF("Addition to Queued Event  failure.");
               }
            }

         }
      }
      else
      {
         TRACE_PRINTF("Reporting mechanism is Disabled now, Fap Ignores the Alarm clear %d", reporting);
      }
   }

   void CurrentAlarmManager::UpdateHighestSeverityAlarmStatus()
   {
      u32 highestSeverity = u32(ALARM_PERCEIVED_SEVERITY_CLEARED);

      for(map<string, MibDN >::iterator i = m_raisedCurrentAlarms.begin(); i != m_raisedCurrentAlarms.end(); ++i)
      {
         MibDN dn = i->second;

         if( m_mib.IsMibObjectPresent(dn) && m_mib.IsMibAttributePresent(dn,PARAM_ID_ALARM_PERCEIVED_SEVERITY))
         {
            u32 alarmSeverity;
            m_mib.GetMibAttribute(dn,PARAM_ID_ALARM_PERCEIVED_SEVERITY, alarmSeverity);

            if(    alarmSeverity >  highestSeverity
                  && alarmSeverity != ALARM_PERCEIVED_SEVERITY_WARNING)
            {
               highestSeverity = alarmSeverity;
            }
         }
      }

      MibDN fap0 = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP,0);
      bool updateAlarmStatus = false;

      if( m_mib.IsMibAttributePresent( fap0, PARAM_ID_TR069_ALARM_STATUS) )
      {
         u32 currentAlarmStatus;
         m_mib.GetMibAttribute( fap0, PARAM_ID_TR069_ALARM_STATUS, currentAlarmStatus);

         if( highestSeverity != currentAlarmStatus)
         {
            updateAlarmStatus = true;
         }
      }
      else
      {
         updateAlarmStatus = true;
      }

      if(updateAlarmStatus)
      {
         MibAttributeValues attr;
         attr.AddAttribute(PARAM_ID_TR069_ALARM_STATUS, highestSeverity);
         m_mib.SetMibAttributes(fap0, attr, ENTITY_TR069 );
      }
   }
}
