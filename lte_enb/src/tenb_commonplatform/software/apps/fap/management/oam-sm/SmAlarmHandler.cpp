/********************************************************************16**

            (c) Copyright 2012 by RadiSys Corporation. All rights reserved.

     This software is confidential and proprietary to RadiSys Corporation.
     No part of this software may be reproduced, stored, transmitted, 
     disclosed or used in any form or by any means other than as expressly
     provided by the written Software License Agreement between Radisys 
     and its licensee.

     Radisys warrants that for a period, as provided by the written
     Software License Agreement between Radisys and its licensee, this
     software will perform substantially to Radisys specifications as
     published at the time of shipment, exclusive of any updates or 
     upgrades, and the media used for delivery of this software will be 
     free from defects in materials and workmanship.  Radisys also warrants 
     that has the corporate authority to enter into and perform under the 
     Software License Agreement and it is the copyright owner of the software 
     as originally delivered to its licensee.

     RADISYS MAKES NO OTHER WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
     WITHOUT LIMITATION WARRANTIES OF MERCHANTABILITY OR FITNESS FOR
     A PARTICULAR PURPOSE WITH REGARD TO THIS SOFTWARE, SERVICE OR ANY RELATED
     MATERIALS.

     IN NO EVENT SHALL RADISYS BE LIABLE FOR ANY INDIRECT, SPECIAL,
     CONSEQUENTIAL DAMAGES, OR PUNITIVE DAMAGES IN CONNECTION WITH OR ARISING
     OUT OF THE USE OF, OR INABILITY TO USE, THIS SOFTWARE, WHETHER BASED
     ON BREACH OF CONTRACT, TORT (INCLUDING NEGLIGENCE), PRODUCT
     LIABILITY, OR OTHERWISE, AND WHETHER OR NOT IT HAS BEEN ADVISED
     OF THE POSSIBILITY OF SUCH DAMAGE.

                       Restricted Rights Legend:

     This software and all related materials licensed hereby are
     classified as "restricted computer software" as defined in clause
     52.227-19 of the Federal Acquisition Regulation ("FAR") and were
     developed entirely at private expense for nongovernmental purposes,
     are commercial in nature and have been regularly used for
     nongovernmental purposes, and, to the extent not published and
     copyrighted, are trade secrets and confidential and are provided
     with all rights reserved under the copyright laws of the United
     States.  The government's rights to the software and related
     materials are limited and restricted as provided in clause
     52.227-19 of the FAR.

                    IMPORTANT LIMITATION(S) ON USE

     The use of this software is limited to the use set
     forth in the written Software License Agreement between Radisys and
     its Licensee. Among other things, the use of this software
     may be limited to a particular type of Designated Equipment, as 
     defined in such Software License Agreement.
     Before any installation, use or transfer of this software, please
     consult the written Software License Agreement or contact Radisys at
     the location set forth below in order to confirm that you are
     engaging in a permissible use of the software.

                    RadiSys Corporation
                    Tel: +1 (858) 882 8800
                    Fax: +1 (858) 777 3388
                    Email: support@trillium.com
                    Web: http://www.radisys.com 
 
*********************************************************************17*/

///////////////////////////////////////////////////////////////////////////////
//
// SmAlarmHandler.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <system/Trace.h>
#include <system/AlarmId.h>
#include <system/AlarmEvent.h>
#include <platform/FapAlarmId.h>
#include <platform/RadisysFapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SmApplication.h"
#include "SmAlarmHandler.h"
using namespace std;
using namespace threeway;
using namespace boost;

SmAlarmHandler* SmAlarmHandler::s_instance = NULL;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

SmAlarmHandler::SmAlarmHandler()
{
   ENTER ();
   m_messenger = Sm::SmApplication::GetInstance().GetSmMessenger();

   EXIT ();
}
SmAlarmHandler::~SmAlarmHandler()
{
   ENTER ();
   EXIT ();
}
SmAlarmHandler& SmAlarmHandler::GetInstance()
{
   ENTER ();
   if(s_instance == NULL)
   {
      s_instance = new SmAlarmHandler();
   }
   RETURN (*s_instance);
}

bool SmAlarmHandler::SendMessage(const Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingEntity sourceEntity) const
{
   RSYS_ASSERT_PRINTF(m_messenger != NULL, "Message=%s Src=%s Dest=%s", messageToSend.ToString().c_str(), MessagingEntityToString(sourceEntity), MessagingEntityToString(destinationEntity));

   return(m_messenger->SendMessage(messageToSend, sourceEntity, destinationEntity));
}

void SmAlarmHandler::UpdateAlarmEvent(u32 id, u8 alarmSeverity, string info)
{
   ENTER();

   TRACE_MSG("Start handling alarm event");
   string spfProblem, addInfo;
   std::string::size_type prev_pos = 0, pos = 0;
   if((pos = info.find(',', pos)) != std::string::npos )
        {
            spfProblem = info.substr(prev_pos,pos);
            addInfo = info.substr(++pos,info.length());
   	     }else
   	     {
   	     	spfProblem = info;
   	     }
		 TRACE_PRINTF("spfProblem=%s, addInfo=%s",spfProblem.c_str(),addInfo.c_str());
   
     AlarmEvent::AlarmSeverity severity = AlarmEvent::ALARM_SEVERITY_CLEARED;

   switch(alarmSeverity)
   {
      case ALARM_SEVERITY_CLEARED:
         severity = AlarmEvent::ALARM_SEVERITY_CLEARED;
         break;

      case ALARM_SEVERITY_WARNING:
         severity = AlarmEvent::ALARM_SEVERITY_WARNING;
         break;

      case ALARM_SEVERITY_MINOR:
         severity = AlarmEvent::ALARM_SEVERITY_MINOR;
         break;

      case ALARM_SEVERITY_MAJOR:
         severity = AlarmEvent::ALARM_SEVERITY_MAJOR;
         break;

      case ALARM_SEVERITY_CRITICAL:
         severity = AlarmEvent::ALARM_SEVERITY_CRITICAL;
         break;

      default:
         TRACE_PRINTF("Invalid Alarm severity received");
         break;
   }
            shared_ptr<AlarmId> alarmId (new FapAlarmId( FapAlarmId::INVALID)); 
            alarmId->SetNumericAlarmId(id);

   switch(id%MAX_ALARMS)
   {
      case S1_SETUP_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_COMMUNICATIONS);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }

      case X2_SETUP_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_COMMUNICATIONS);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }

      case LTE_MEMORY_ALLOCATION_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_EQUIPMENT);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }

      case SCTP_LINK_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_COMMUNICATIONS);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }

      case TNL_SETUP_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_TRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_COMMUNICATIONS);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }

      case S1_ERROR_IND:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_TRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_COMMUNICATIONS);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }

      case S1_RESET:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_COMMUNICATIONS);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }

      case X2_ERROR_IND:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_TRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_COMMUNICATIONS);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }

      case X2_RESET:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_COMMUNICATIONS);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SOCKET_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SCTP_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case S1AP_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case EGTP_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case X2AP_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case RRM_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case APP_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case RRC_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case PDCPUL_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case PDCPDL_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case RLCUL_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case RLCDL_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case MAC_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case CL_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case CELLUP_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case ADMIN_STATE_CHANGE_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case GENERIC_PRAMS_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case MME_IP_PRAMS_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case CELL_CONFIG_PRAMS_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case ENBIP_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case MIB_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case PRACH_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case RACH_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case PDSCH_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SRS_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case PUSCH_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case ULPOWER_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case ULFREQ_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case PUCCH_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case UETMRCONS_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SIB1_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SIB2_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SIB3_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SIB4_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SIB6_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SIB9_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case ANR_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case MEAS_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case EAID_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SIBSCHED_CFG_FAIL:
         {	

            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case RABPOLICY_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case TIMER_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case RRM_CELL_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case ULSCHD_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case DLSCHD_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case NEIGH_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case NEIGH_CELL_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case NEIGH_FREQ_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case NEIGH_BAND_CLASS_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case ENB_PROTO_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case UTRANEIFREQ_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case EUTRANEIFREQ_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case UTRANEICELL_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case EUTRANEICELL_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case UTRANEILIST_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case EUTRANEILIST_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case RABSRB1_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case RABSRB2_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case EVNT_NEIGH_ENB_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case SMCELL_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
      case PROCTMR_CFG_FAIL:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
	   case CFG_FAIL_FROM_SON:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  info,
                  AlarmEvent::ALARM_TYPE_PROCESSING);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
	   case PCI_COLLISION:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  spfProblem,
                  AlarmEvent::ALARM_TYPE_PROCESSING,
                  addInfo);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }
	   case PCI_CONFUSION:
         {	
            AlarmEvent alarmEvent(alarmId,
                  AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                  severity,
                  spfProblem,
                  AlarmEvent::ALARM_TYPE_PROCESSING,
                  addInfo);
            SendMessage(alarmEvent, ENTITY_OAM, ENTITY_SM);
            break;
         }

      default:
         TRACE_PRINTF("Invalid Alarm id received");
         break;
   }
   return;
}
