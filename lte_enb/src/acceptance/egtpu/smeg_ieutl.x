

/***********************************************************************

    Name: typedef file for LM configuration

    Type: C Source

    Desc: 

    File: smeg_ieutl.x

    Sid:      smeg_ieutl.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:19:09 2015

    Prg: an

************************************************************************/

#ifdef EGTP_C

EXTERN Void  makeAndAddRecoveryIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddPvtExtnIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddTadIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddDelayIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddApnRestIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddBrerCtrlModeIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddCauseIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddAmbrIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddPCOIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddFlowQosIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddPTidIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddGreKeyIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddCsidIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddTrcIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddImsiIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddMeiIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void makeAndAddUsrLocInfoIe  ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void makeAndAddMsisdnIe  ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddBearerFlgIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddUnknownIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo
));

EXTERN Void  makeAndAddEbiIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddBQosIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddBTFTIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));
EXTERN Void  makeAndAddChargCharIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddChargIdIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddBrerCntxIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddServNwIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddRatTypeIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb, 
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddMaxApnRestIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddIndicationIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddAccessPntNameIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddFTeidIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddSelModeIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddPdnTypeIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));
EXTERN Void  makeAndAddPaaIe  ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddEmbdCauseIe  ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddPortIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddHopCntrIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddAuthQuadrupIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddAuthQuintupIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddGsmKeyTripIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddUmtsKeyCiphQuinIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddGsmKeyCiphQuinIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddUmtsKeyQuinIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddEpsSecQdQtIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddPdnConnIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddCntxtPriorIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddBearerIdLstIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddFContainerIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddTargetIdIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddFCauseIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddCellIdIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddSelPlmnIdIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddIpAddrIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddCngRptActIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddGutiIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddPTmsiIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddPTmsiSigIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddCompReqMsgIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddTmsiIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddApnIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddSrcRncPdcpCtxIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddUeNtwrkCapbIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddRfspIdIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddCsgIdIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddMbmsDistAckIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddCmiIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddMbmsFlowIdIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddMbmsServAreaIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddMbmsSessIdIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddMbmsIpMultDistIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddChnlNeededIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddEmlppPriorIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddProcedureTidIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddNodeTypeIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddCsgInfoRepActIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddServIndIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddBearerCntxIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddSrcIdIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddBearerQosIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddGblCnIdIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddPduNumberIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddRabContextIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddS1UDatFwIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddS103PdnFwInfoIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddUeTimeZoneIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddTraceRefIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddUliIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddUmtsKeyQuadQuinIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddMbmsSessDurationIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddUciIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddTmgIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));


EXTERN Void  makeAndAddFqdnIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
));
/* eg009.201 - Added for S2B and S2A */
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
EXTERN Void  makeAndAddLdnIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));
EXTERN Void  makeAndAddApcoIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

#endif/*EG_S2b_SUPP*/

#endif
/********************************************************************30**

         End of file:     smeg_ieutl.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:19:09 2015

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      an                1. Initial Release
/main/1      ---      rss               1. Initial for eGTP 1.2 Release
/main/2      ---      pmacharla         Initial for eGTP release 2.1
           eg009.201  asaurabh          1.  Added for S2B and S2A.
*********************************************************************91*/

