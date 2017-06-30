///////////////////////////////////////////////////////////////////////////////
//
// StaticDecode.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "StaticDecode.h"

/* We need all the message declarations since we will construct classes
 *  (via the Serialisable::DeSerialise() template).
 */

#include "system/SetParameterAttribute.h"
#include "mobnet/FapId.h"
#include "mib-common/MibAttrValidationFailure.h"
#include "mib-common/messages/MibCreateObjectReq.h"
#include "mib-common/messages/MibCreateObjectCnf.h"
#include "mib-common/messages/MibDeleteObjectReq.h"
#include "mib-common/messages/MibDeleteObjectCnf.h"
#include "mib-common/messages/MibValidateAttributesReq.h"
#include "mib-common/messages/MibValidateAttributesCnf.h"
#include "mib-common/messages/MibSetAttributesReq.h"
#include "mib-common/messages/MibSetAttributesCnf.h"
#include "mib-common/messages/MibDeleteAttributesReq.h"
#include "mib-common/messages/MibDeleteAttributesCnf.h"
#include "mib-common/messages/MibSubscribeAttributesReq.h"
#include "mib-common/messages/MibSubscribeAttributesInd.h"
#include "mib-common/messages/MibSubscribeAttributesDeleteInd.h"
#include "mib-common/messages/MibDeleteAttributesCnf.h"
#include "mib-common/messages/MibUnsubscribeReq.h"
#include "mib-common/messages/MibUnsubscribeCnf.h"
#include "mib-common/messages/MibGetAttributesReq.h"
#include "mib-common/messages/MibGetAttributesCnf.h"
#include "messaging/messages/carb/CarbLedSetReq.h"
#include "messaging/messages/carb/CarbOscDacWriteReq.h"
#include "messaging/messages/carb/CarbTemperatureCnf.h"
#include "messaging/messages/carb/CarbTemperatureReq.h"
#include "messaging/messages/cli/CliExecuteCmdCnf.h"
#include "messaging/messages/cli/CliExecuteCmdInd.h"
#include "messaging/messages/cli/CliExecuteCmdProgressInd.h"
#include "messaging/messages/cli/CliExecuteCmdReq.h"
#include "messaging/messages/common/ActivateUpdateCnf.h"
#include "messaging/messages/common/ActivateUpdateReq.h"
#include "messaging/messages/common/ApplyUpdateCnf.h"
#include "messaging/messages/common/ApplyUpdateReq.h"
#include "messaging/messages/common/FtpAbort.h"
#include "messaging/messages/common/FtpCnf.h"
#include "messaging/messages/common/FtpCompleteInd.h"
#include "messaging/messages/common/FtpGetCnf.h"
#include "messaging/messages/common/FtpGetReq.h"
#include "messaging/messages/common/FtpPutCnf.h"
#include "messaging/messages/common/FtpPutReq.h"
#include "messaging/messages/common/FtpReq.h"
#include "messaging/messages/common/UploadLogReq.h"
#include "messaging/messages/common/AutonomousTransferComp.h"
#include "messaging/messages/common/GsmRemScanCnf.h"
#include "messaging/messages/common/GsmRemScanReq.h"
#include "messaging/messages/common/InstallUpdateCnf.h"
#include "messaging/messages/common/InstallUpdateReq.h"
#include "messaging/messages/common/KpiConfigureReq.h"
#include "messaging/messages/common/KpiReadCnf.h"
#include "messaging/messages/common/KpiReadReq.h"
#include "messaging/messages/common/KpiRegisterReq.h"
#include "messaging/messages/common/MessagingConnectionConf.h"
#include "messaging/messages/common/MessagingConnectionRef.h"
#include "messaging/messages/common/MessagingConnectionReq.h"
#include "messaging/messages/common/MessagingDataInd.h"
#include "messaging/messages/common/MessagingReleaseConf.h"
#include "messaging/messages/common/MessagingReleaseReq.h"
#include "messaging/messages/common/MessagingRouteInd.h"
#include "messaging/messages/common/MfOpStateInformInd.h"
#include "messaging/messages/common/MfSetAdminStateCnf.h"
#include "messaging/messages/common/MfSetAdminStateReq.h"
#include "messaging/messages/common/OamActionCnf.h"
#include "messaging/messages/common/OamActionReq.h"
#include "messaging/messages/common/RegisterEntityCnf.h"
#include "messaging/messages/common/RegisterEntity.h"
#include "messaging/messages/common/RegisterEntityReq.h"
#include "messaging/messages/common/RemCnf.h"
#include "messaging/messages/common/RemGsmRemDACEstimateInd.h"
/* Added NlmCoscReq and NlmCoscCnf for freq-sync changes */
#include "messaging/messages/common/NlmCoscReq.h"
#include "messaging/messages/common/NlmCoscCnf.h"

#include "messaging/messages/common/RemReq.h"
#include "messaging/messages/common/RemScanCnf.h"
#include "messaging/messages/common/RemScanReq.h"
#include "messaging/messages/common/RequestStartInd.h"
#include "messaging/messages/common/RequestStartRsp.h"
#include "messaging/messages/common/RevertUpdateCnf.h"
#include "messaging/messages/common/RevertUpdateReq.h"
#include "messaging/messages/common/SetTraceMasksReq.h"
#include "messaging/messages/common/StopRemScanReq.h"
#include "messaging/messages/common/KpiCollectionReq.h"
#include "messaging/messages/common/L2TimerNotify.h"
#include "messaging/messages/common/InitConfigComplete.h"
#include "messaging/messages/common/EventNotify.h"
#include "messaging/messages/common/UpdateInUseUtraCellList.h"
#include "messaging/messages/common/UpdateInUseEutraCellList.h"

#include "messaging/messages/cphy/CPhy_clog.h"
#include "messaging/messages/cphy/CPhyHwConfigCnf.h"
#include "messaging/messages/cphy/CPhyHwConfigReq.h"
#include "messaging/messages/cphy/CPhyMessage.h"
#include "messaging/messages/cphy/CPhyModeChangeCnf.h"
#include "messaging/messages/cphy/CPhyModeChangeReq.h"
#include "messaging/messages/cphy/CPhyNodeBCctrchCnf.h"
#include "messaging/messages/cphy/CPhyNodeBCctrchRemoveCnf.h"
#include "messaging/messages/cphy/CPhyNodeBCctrchRemoveReq.h"
#include "messaging/messages/cphy/CPhyNodeBCctrchSetupReq.h"
#include "messaging/messages/cphy/CPhyNodeBCompressedModeReq.h"
#include "messaging/messages/cphy/CPhyNodeBConfigCnf.h"
#include "messaging/messages/cphy/CPhyNodeBConfigReq.h"
#include "messaging/messages/cphy/CPhyNodeBOutOfSyncInd.h"
#include "messaging/messages/cphy/CPhyNodeBPchAddCnf.h"
#include "messaging/messages/cphy/CPhyNodeBPchAddReq.h"
#include "messaging/messages/cphy/CPhyNodeBPchRemoveCnf.h"
#include "messaging/messages/cphy/CPhyNodeBPchRemoveReq.h"
#include "messaging/messages/cphy/CPhyNodeBRachConfigReq.h"
#include "messaging/messages/cphy/CPhyNodeBSccpchConfigCnf.h"
#include "messaging/messages/cphy/CPhyNodeBSccpchConfigReq.h"
#include "messaging/messages/cphy/CPhyNodeBSibMessage.h"
#include "messaging/messages/cphy/CPhyNodeBStatInd.h"
#include "messaging/messages/cphy/CPhyNodeBSyncInd.h"
#include "messaging/messages/cphy/CPhyNodeBTxDpchEnableCnf.h"
#include "messaging/messages/cphy/CPhyNodeBTxDpchEnableReq.h"
#include "messaging/messages/cphy/CPhyNodeBTxEnableCnf.h"
#include "messaging/messages/cphy/CPhyNodeBTxEnableReq.h"
#include "messaging/messages/cphy/CPhyRemGsmBcchDecodeInd.h"
#include "messaging/messages/cphy/CPhyRemGsmFindCellCnf.h"
#include "messaging/messages/cphy/CPhyRemGsmFindCellReq.h"
#include "messaging/messages/cphy/CPhyRemGsmRssiScanCnf.h"
#include "messaging/messages/cphy/CPhyRemGsmRssiScanReq.h"
#include "messaging/messages/cphy/CPhyRemGsmStopBcchDecodeCnf.h"
#include "messaging/messages/cphy/CPhyRemGsmStopBcchDecodeReq.h"
#include "messaging/messages/cphy/CPhyRemSibDecodeCnf.h"
#include "messaging/messages/cphy/CPhyRemSibDecodeInd.h"
#include "messaging/messages/cphy/CPhyRemSibDecodeReq.h"
#include "messaging/messages/cphy/CPhyRemSibDecodeComplete.h"
#include "messaging/messages/cphy/CPhyRemWcdmaCoarseFreqLockCnf.h"
#include "messaging/messages/cphy/CPhyRemWcdmaCoarseFreqLockReq.h"
#include "messaging/messages/cphy/CPhyRemWcdmaFindCellCnf.h"
#include "messaging/messages/cphy/CPhyRemWcdmaFindCellReq.h"
#include "messaging/messages/cphy/CPhyRemWcdmaFreqOffsetMeasCnf.h"
#include "messaging/messages/cphy/CPhyRemWcdmaFreqOffsetMeasReq.h"
#include "messaging/messages/cphy/CPhyTypes.h"
/* Added NlmCoscReq and NlmCoscCnf for freq-sync changes */
#include "messaging/messages/cphy/CPhyNlmCoscReq.h"
#include "messaging/messages/cphy/CPhyNlmCoscCnf.h"
#include "messaging/messages/cphy/CPhyNlmErrInd.h"
#include "messaging/messages/fntp/FNTPGetFrequencyOffsetCnf.h"
#include "messaging/messages/fntp/FNTPGetFrequencyOffsetInd.h"
#include "messaging/messages/fntp/FNTPGetFrequencyOffsetReq.h"
#include "messaging/messages/fntp/FNTPInitCnf.h"
#include "messaging/messages/fntp/FNTPInitReq.h"
#include "messaging/messages/fntp/FNTPIsAliveInd.h"
#include "messaging/messages/fntp/FNTPSetSampleModeCnf.h"
#include "messaging/messages/fntp/FNTPSetSampleModeReq.h"
#include "messaging/messages/fntp/FreqSyncIsAliveInd.h"
#include "messaging/messages/fntp/FreqSyncSetFakeDac.h"
#include "messaging/messages/ike/HwCryptoAvailableInd.h"
#include "messaging/messages/ike/IkeTunnelConnectInd.h"
#include "messaging/messages/ike/IkeTunnelCreateCnf.h"
#include "messaging/messages/ike/IkeTunnelCreateReq.h"
#include "messaging/messages/ike/IkeTunnelDeleteCnf.h"
#include "messaging/messages/ike/IkeTunnelDeleteReq.h"
#include "messaging/messages/ike/IkeTunnelDisconnectInd.h"
#include "messaging/messages/oam/LedInfo.h"
#include "messaging/messages/oam/OamLedStateInformInd.h"
#include "messaging/messages/tenpin/TenpinDnsServerAddCnf.h"
#include "messaging/messages/tenpin/TenpinDnsServerAddReq.h"
#include "messaging/messages/tenpin/TenpinFirewallCloseCnf.h"
#include "messaging/messages/tenpin/TenpinFirewallCloseReq.h"
#include "messaging/messages/tenpin/TenpinFirewall.h"
#include "messaging/messages/tenpin/TenpinFirewallOpenCnf.h"
#include "messaging/messages/tenpin/TenpinFirewallOpenReq.h"
#include "messaging/messages/tenpin/TenpinSignatureVerifyCnf.h"
#include "messaging/messages/tenpin/TenpinSignatureVerifyReq.h"
#include "messaging/messages/up-mgmt/IuCsRouteMgmtMessage.h"
#include "messaging/messages/up-mgmt/IuCsUpInitialisationFailure.h"
#include "messaging/messages/up-mgmt/IuCsUpInitialisationSuccess.h"
#include "messaging/messages/up-mgmt/IuPsRouteMgmtMessage.h"
#include "messaging/messages/watchdog/WatchdogAddPidReq.h"
#include "messaging/messages/watchdog/WatchdogKickReq.h"
#include "messaging/messages/watchdog/WatchdogKickStopReq.h"
#include "messaging/messages/watchdog/WatchdogRemovePidReq.h"
#include "messaging/transport/ApplicationWithMessaging.h"
#include "messaging/transport/ApplicationWithParamCache.h"
#include "messaging/transport/AppMibAttributeCache.h"
#include "messaging/transport/AppWithAttrCache_fsm.h"
#include "messaging/transport/AppWithAttrCacheFsmImpl.h"
#include "messaging/transport/AppWithAttrCache_fsm_interface.h"
#include "messaging/transport/CliHandler.h"
#include "messaging/transport/ConnectionOrientatedMessageManager.h"
#include "messaging/transport/DeviceMessenger.h"
#include "messaging/transport/KpiMessageManager.h"
#include "messaging/transport/MessageHandler.h"
#include "messaging/transport/MessageRouteEntry.h"
#include "messaging/transport/MessageRoutingTable.h"
#include "messaging/transport/MessageSerialisedData.h"
#include "messaging/transport/MessagingEntity.h"
#include "messaging/transport/Messenger.h"
#include "messaging/transport/MibAccessInterface.h"
#include "messaging/transport/SingleThreadedApplicationWithMessaging.h"
#include "messaging/transport/SingleThreadedAppWithAttrCache.h"
#include "messaging/transport/SubscriptionDescriptor.h"
#include "messaging/transport/ThreadlessUdpMessenger.h"
#include "messaging/transport/UdpMessenger.h"

//REM path

#ifdef LTE_REM
#include "messaging/messages/rem/rem_msgs.h"
#endif

namespace threeway
{

shared_ptr<Serialisable> DeserialiseMessage(shared_ptr<SerialisedData> message)
{
    #define SERID_GENERATE

    #undef  ENUM_START
    #define ENUM_START(s) \
        switch(message->GetSerialisationId())

    #undef  SERID_ENUM_ELEMENT_VAL
    #define SERID_ENUM_ELEMENT_VAL(sERiD, cLASS, nUM) \
                SERID_ENUM_ELEMENT(sERiD, cLASS)

    #undef  SERID_ENUM_ELEMENT
    #define SERID_ENUM_ELEMENT(sERiD, cLASS) \
                case sERiD: return Serialisable::DeSerialise<cLASS>(message);

    #undef  ENUM_ELEMENT
    #define ENUM_ELEMENT(a)

    #undef  ENUM_ELEMENT_VAL
    #define ENUM_ELEMENT_VAL(a, b)

    #undef  ENUM_END
    #define ENUM_END(s)

    #include "system/SerialisationIds.h"

    #undef SERID_GENERATE

    return shared_ptr<Serialisable>();
}


shared_ptr<Serialisable> DeserialiseMessageBytes(u32 serId, const u8 *data, u32 length)
{
    shared_ptr<threeway::SerialisedData> sd(new threeway::SerialisedData(serId, data, length));

    return DeserialiseMessage(sd);
}

}

// END OF FILE
