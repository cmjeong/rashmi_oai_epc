
///////////////////////////////////////////////////////////////////////////////
//
// OamFsmHandlers.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <system/Trace.h>
#include <system/TimerEngine.h>
#include <mobnet/RemScanStatusId.h>
#include <messaging/messages/cphy/CPhyNodeBTxEnableReq.h>
#include <messaging/messages/cphy/CPhyModeChangeReq.h>
#include <messaging/messages/ike/IkeTunnelCreateReq.h>
#include <messaging/messages/ike/HwCryptoAvailableInd.h>
#include <messaging/messages/common/MfSetAdminStateReq.h>
#include <messaging/messages/common/MfOpStateInformInd.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "OamUserApplication.h"
#include "managed-objects/FapMO.h"
#include "oam_env.h"
#include "MibHelper.h"

using namespace std;
using namespace threeway;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
void OamUserApplication::InitialisingExit()
{
    // Compare this list to that in OamUserApplication::ProcessEntityReadyStatesAndFireEmUpIfAllStarted()
    // TODO - surely there must be a neater way!

    // First do those generic to all builds.
    SendRequestStartRsp(ENTITY_SW_UPDATE);
    SendRequestStartRsp(ENTITY_SM);

    if(oamEnv_isProductHbs2Iu() || oamEnv_isProductGeneric())
    {
        StartTr069();
        SendRequestStartRsp(ENTITY_TENPIN); // May have already been started if TPM is in use but it is safe to send this twice.
    }
    else if(oamEnv_isProductHbs2Sip())
    {
        SendRequestStartRsp(ENTITY_CS_USER_PLANE);
        SendRequestStartRsp(ENTITY_GGSN);
    }
    else if(oamEnv_isProductHbs2Factory())
    {
        // E.g. factory build.
        SendRequestStartRsp(ENTITY_CS_USER_PLANE);
        SendRequestStartRsp(ENTITY_GGSN);
        SendRequestStartRsp(ENTITY_TENPIN); // May have already been started if TPM is in use but it is safe to send this twice.
    }
    else if(oamEnv_isProductHbs2Rrc())
    {
        // Nothing to do.
    }

    //InitFreqSyncEntity();

    // start any other apps that registered but don't need specific handling
    std::vector<MessagingEntity>:: iterator it;
    for (it = m_otherEntitiesToStart.begin(); it != m_otherEntitiesToStart.end(); it++)
    {
        SendRequestStartRsp(*it);
    }
}

void OamUserApplication::StartExit()
{
    SendRequestStartRsp(ENTITY_OAM);
//    SendCPhyHwConfigReq();
}

void OamUserApplication::RemScanInProgressEntry()
{
    /*
    MibAttributeValues attrs;
    attrs.AddAttribute(PARAM_ID_REM_SCAN_IN_PROGRESS, (u32)1);
    GetMibCache().SetMibAttributes(attrs, ENTITY_OAM);
    */

    MibAttributeValues attrs;
    u32 status = u32(REM_SCAN_STATUS_IN_PROGRESS);
    attrs.AddAttribute(PARAM_ID_LTE_REM_SCAN_STATUS, GetStatusAsString(status));
    GetMibCache().SetMibAttributes(attrs, ENTITY_OAM);

}

void OamUserApplication::RemScanInProgressExit()
{
    /*
    MibAttributeValues attrs;
    attrs.AddAttribute(PARAM_ID_REM_SCAN_IN_PROGRESS, (u32)0);
    GetMibCache().SetMibAttributes(attrs, ENTITY_OAM);
    */

    TimeWrap now;
    MibAttributeValues attrs;
    u32 status = u32(REM_SCAN_STATUS_SUCCESS);
    attrs.AddAttribute(PARAM_ID_LTE_REM_SCAN_STATUS, GetStatusAsString(status));
    attrs.AddAttribute(PARAM_ID_LTE_LAST_REM_SCAN_TIME, now.ToString() );
    GetMibCache().SetMibAttributes(attrs, ENTITY_OAM);

    MfOpStateInformInd opStateInform(MF_REM_SCAN, ManagedObject::OP_STATE_DISABLED, 0, "Rem Scan Ended");
    SendMessage(opStateInform, ENTITY_OAM, ENTITY_OAM);
}

void OamUserApplication::WaitingForFullScanCompleteEntry()
{
    SendRemScanReq();

    MfOpStateInformInd opStateInform(MF_REM_SCAN, ManagedObject::OP_STATE_ENABLED, 0, "Full Scan Started");
    SendMessage(opStateInform, ENTITY_OAM, ENTITY_OAM);
}
