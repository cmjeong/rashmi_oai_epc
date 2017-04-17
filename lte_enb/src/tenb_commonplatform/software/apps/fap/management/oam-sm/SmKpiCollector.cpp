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
// SmKpiCollector.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <stdio.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SmKpiCollector.h"
using namespace std;
using namespace threeway;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

SmKpiCollector::SmKpiCollector()
{
    ENTER ();
    EXIT ();
}
SmKpiCollector::~SmKpiCollector()
{
    ENTER ();
    EXIT ();
}
#ifdef THREE_G_KPI /*3G Code*/
void SmKpiCollector::UpdateRabAssignmentReqKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateRabAssignmentReqKpis with values : %d %d", Id, incVal);

        switch(Id)
        {
        case KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO:
                IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VIDEO);
            break;
        case KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE:
                IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_VOICE);
            break;
        case KPI_ID_ATTEMPTED_RAB_EST_CS_STREAMING:
            IncKpi(KPI_ID_ATTEMPTED_RAB_EST_CS_STREAMING);
            break;
        case KPI_ID_ATTEMPTED_RAB_EST_PS_CONVERSATIONAL:
            IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_CONVERSATIONAL);
            break;
        case KPI_ID_ATTEMPTED_RAB_EST_PS_STREAMING:
            IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_STREAMING);
            break;
        case KPI_ID_ATTEMPTED_RAB_EST_PS_INTERACTIVE:
            IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_INTERACTIVE);
            break;
        case KPI_ID_ATTEMPTED_RAB_EST_PS_BACKGROUND:
            IncKpi(KPI_ID_ATTEMPTED_RAB_EST_PS_BACKGROUND);
            break;

        default:
            RSYS_ASSERT("Invalid KPI supplied");
            break;
         }
    EXIT();
}

void SmKpiCollector::UpdateRabAssignmentRespKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateRabAssignmentRespKpis with values : %d %d", Id, incVal);

        switch(Id)
        {
        case KPI_ID_SUCCESSFUL_RAB_EST_CS_VIDEO:
                IncKpi(KPI_ID_SUCCESSFUL_RAB_EST_CS_VIDEO);
            break;
        case KPI_ID_SUCCESSFUL_RAB_EST_CS_VOICE:
                IncKpi(KPI_ID_SUCCESSFUL_RAB_EST_CS_VOICE);
            break;
        case KPI_ID_SUCCESSFUL_RAB_EST_CS_STREAMING:
            IncKpi(KPI_ID_SUCCESSFUL_RAB_EST_CS_STREAMING);
            break;
        case KPI_ID_SUCCESSFUL_RAB_EST_PS_CONVERSATIONAL:
            IncKpi(KPI_ID_SUCCESSFUL_RAB_EST_PS_CONVERSATIONAL);
            break;
        case KPI_ID_SUCCESSFUL_RAB_EST_PS_STREAMING:
            IncKpi(KPI_ID_SUCCESSFUL_RAB_EST_PS_STREAMING);
            break;
        case KPI_ID_SUCCESSFUL_RAB_EST_PS_INTERACTIVE:
            IncKpi(KPI_ID_SUCCESSFUL_RAB_EST_PS_INTERACTIVE);
            break;
        case KPI_ID_SUCCESSFUL_RAB_EST_PS_BACKGROUND:
            IncKpi(KPI_ID_SUCCESSFUL_RAB_EST_PS_BACKGROUND);
            break;

        default:
            RSYS_ASSERT("Invalid KPI supplied");
            break;
         }
    EXIT();
}

void SmKpiCollector::UpdateAttemptedRBEstKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateAttemptedRBEstKpis with values : %d %d", Id, incVal);

        switch(Id)
        {
        case KPI_ID_ATTEMPTED_RB_EST_R99:
                IncKpi(KPI_ID_ATTEMPTED_RB_EST_R99);
            break;
        case KPI_ID_ATTEMPTED_RB_EST_HSDPA:
                IncKpi(KPI_ID_ATTEMPTED_RB_EST_HSDPA);
            break;
        case KPI_ID_ATTEMPTED_RB_EST_HSUPA:
            IncKpi(KPI_ID_ATTEMPTED_RB_EST_HSUPA);
            break;
        
        default:
            RSYS_ASSERT("Invalid KPI supplied");
            break;
         }
    EXIT();
}

void SmKpiCollector::UpdateSuccessfulRBEstKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateSuccessfulRBEstKpis with values : %d %d", Id, incVal);

        switch(Id)
        {
        case KPI_ID_SUCCESSFUL_RB_EST_R99:
                IncKpi(KPI_ID_SUCCESSFUL_RB_EST_R99);
            break;
        case KPI_ID_SUCCESSFUL_RB_EST_HSDPA:
                IncKpi(KPI_ID_SUCCESSFUL_RB_EST_HSDPA);
            break;
        case KPI_ID_SUCCESSFUL_RB_EST_HSUPA:
            IncKpi(KPI_ID_SUCCESSFUL_RB_EST_HSUPA);
            break;
        
        default:
            RSYS_ASSERT("Invalid KPI supplied");
            break;
         }
    EXIT();
}

void SmKpiCollector::UpdateUnsuccessfulRBEstKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateUnsuccessfulRBEstKpis with values : %d %d", Id, incVal);

        switch(Id)
        {
           case KPI_ID_UNSUCCESSFUL_RB_EST_R99_PHY_FAILURE:
                   IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_R99_PHY_FAILURE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_R99_PROTO_ERROR:
                   IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_R99_PROTO_ERROR);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_R99_CELL_UPDATE:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_R99_CELL_UPDATE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_R99_CONFIG_FAILURE:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_R99_CONFIG_FAILURE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_R99_NO_REPLY:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_R99_NO_REPLY);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_R99_OTHER_CAUSE:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_R99_OTHER_CAUSE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_PHY_FAILURE:
                   IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_PHY_FAILURE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_PROTO_ERROR:
                   IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_PROTO_ERROR);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_CELL_UPDATE:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_CELL_UPDATE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_CONFIG_FAILURE:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_CONFIG_FAILURE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_NO_REPLY:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_NO_REPLY);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_OTHER_CAUSE:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSDPA_OTHER_CAUSE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_PHY_FAILURE:
                   IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_PHY_FAILURE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_PROTO_ERROR:
                   IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_PROTO_ERROR);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_CELL_UPDATE:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_CELL_UPDATE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_CONFIG_FAILURE:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_CONFIG_FAILURE);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_NO_REPLY:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_NO_REPLY);
               break;
           case KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_OTHER_CAUSE:
               IncKpi(KPI_ID_UNSUCCESSFUL_RB_EST_HSUPA_OTHER_CAUSE);
               break;

           default:
               RSYS_ASSERT("Invalid KPI supplied");
               break;
        }
    EXIT();
}

void SmKpiCollector::UpdateAttemptedRrcConnEstKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateAttemptedRrcConnEstKpis with values : %d %d", Id, incVal);

        switch(Id)
        {
        case KPI_ID_ATTEMPTED_RRC_CONN_EST:
                IncKpi(KPI_ID_ATTEMPTED_RRC_CONN_EST);
            break;
        
        default:
            RSYS_ASSERT("Invalid KPI supplied");
            break;
        }
    EXIT();
}
void SmKpiCollector::UpdateSuccessfulRrcConnEstKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateSuccessfulRrcConnEstKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_SUCCESSFUL_RRC_CONN_EST:
                  IncKpi(KPI_ID_SUCCESSFUL_RRC_CONN_EST);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateAttemptedAccessControlAuthKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateAttemptedAccessControlAuthKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_ATTEMPTED_ACCESS_CONTROL_AUTH:
                  IncKpi(KPI_ID_ATTEMPTED_ACCESS_CONTROL_AUTH);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateSuccessfulAccessControlAuthKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateSuccessfulAccessControlAuthKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_ATTEMPTED_ACCESS_CONTROL_AUTH:
                  IncKpi(KPI_ID_ATTEMPTED_ACCESS_CONTROL_AUTH);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}


void SmKpiCollector::UpdateUnsuccessfulAccessControlAuthKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateUnsuccessfulAccessControlAuthKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_UNSUCCESSFUL_ACCESS_CONTROL_AUTH:
                  IncKpi(KPI_ID_UNSUCCESSFUL_ACCESS_CONTROL_AUTH);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateIuReleaseCmdKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateIuReleaseCmdKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_IU_RELEASE_CMD_CS_CN:
                  IncKpi(KPI_ID_IU_RELEASE_CMD_CS_CN);
              break;
          case KPI_ID_IU_RELEASE_CMD_CS_NORMAL:
                  IncKpi(KPI_ID_IU_RELEASE_CMD_CS_NORMAL);
              break;
          case KPI_ID_IU_RELEASE_CMD_CS_UTRAN:
                  IncKpi(KPI_ID_IU_RELEASE_CMD_CS_UTRAN);
              break;
          case KPI_ID_IU_RELEASE_CMD_CS_OTHER:
                  IncKpi(KPI_ID_IU_RELEASE_CMD_CS_OTHER);
              break;
          case KPI_ID_IU_RELEASE_CMD_PS_CN:
                  IncKpi(KPI_ID_IU_RELEASE_CMD_PS_CN);
              break;
          case KPI_ID_IU_RELEASE_CMD_PS_NORMAL:
                  IncKpi(KPI_ID_IU_RELEASE_CMD_PS_NORMAL);
              break;
          case KPI_ID_IU_RELEASE_CMD_PS_UTRAN:
                  IncKpi(KPI_ID_IU_RELEASE_CMD_PS_UTRAN);
              break;
          case KPI_ID_IU_RELEASE_CMD_PS_OTHER:
                  IncKpi(KPI_ID_IU_RELEASE_CMD_PS_OTHER);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateIuReleaseReqKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateIuReleaseReqKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_IU_RELEASE_REQ_CS_CN:
                  IncKpi(KPI_ID_IU_RELEASE_REQ_CS_CN);
              break;
          case KPI_ID_IU_RELEASE_REQ_CS_NORMAL:
                  IncKpi(KPI_ID_IU_RELEASE_REQ_CS_NORMAL);
              break;
          case KPI_ID_IU_RELEASE_REQ_CS_UTRAN:
                  IncKpi(KPI_ID_IU_RELEASE_REQ_CS_UTRAN);
              break;
          case KPI_ID_IU_RELEASE_REQ_CS_OTHER:
                  IncKpi(KPI_ID_IU_RELEASE_REQ_CS_OTHER);
              break;
          case KPI_ID_IU_RELEASE_REQ_PS_CN:
                  IncKpi(KPI_ID_IU_RELEASE_REQ_PS_CN);
              break;
          case KPI_ID_IU_RELEASE_REQ_PS_NORMAL:
                  IncKpi(KPI_ID_IU_RELEASE_REQ_PS_NORMAL);
              break;
          case KPI_ID_IU_RELEASE_REQ_PS_UTRAN:
                  IncKpi(KPI_ID_IU_RELEASE_CMD_PS_UTRAN);
              break;
          case KPI_ID_IU_RELEASE_REQ_PS_OTHER:
                  IncKpi(KPI_ID_IU_RELEASE_REQ_PS_OTHER);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateAttemptedRrcConnReEstKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateAttemptedRrcConnReEstKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_ATTEMPTED_RRC_CONN_REEST:
                  IncKpi(KPI_ID_ATTEMPTED_RRC_CONN_REEST);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateSuccessfulRrcConnReEstKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateSuccessfulRrcConnReEstKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_SUCCESSFUL_RRC_CONN_REEST:
                  IncKpi(KPI_ID_SUCCESSFUL_RRC_CONN_REEST);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateUnsuccessfulRrcConnReEstKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateUnsuccessfulRrcConnReEstKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_UNSUCCESSFUL_RRC_CONN_REEST:
                  IncKpi(KPI_ID_UNSUCCESSFUL_RRC_CONN_REEST);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateIpLayerOctetsKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateIpLayerOctetsKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_IP_LAYER_OCTETS_TX:
                  IncKpi(KPI_ID_IP_LAYER_OCTETS_TX);
              break;
          case KPI_ID_IP_LAYER_OCTETS_RX:
                  IncKpi(KPI_ID_IP_LAYER_OCTETS_RX);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateCellUpdateKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateCellUpdateKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_CELL_UPDATE:
                  IncKpi(KPI_ID_CELL_UPDATE);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateAttemptedAccessControlIdKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateAttemptedAccessControlIdKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_ATTEMPTED_ACCESS_CONTROL_ID:
                  IncKpi(KPI_ID_ATTEMPTED_ACCESS_CONTROL_ID);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}

void SmKpiCollector::UpdateSuccessfulAccessControlIdKpis(u32 Id, u32 incVal)
{
    ENTER();
    TRACE_PRINTF("Entered SmKpiCollector::UpdateSuccessfulAccessControlIdKpis with values : %d %d", Id, incVal);
    switch(Id)
        {
          case KPI_ID_SUCCESSFUL_ACCESS_CONTROL_ID:
                  IncKpi(KPI_ID_SUCCESSFUL_ACCESS_CONTROL_ID);
              break;
        
          default:
              RSYS_ASSERT("Invalid KPI supplied");
              break;
        }

    EXIT();
}
#endif
