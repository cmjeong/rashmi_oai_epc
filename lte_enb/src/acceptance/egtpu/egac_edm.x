

/********************************************************************20**

     Name:     eGTP Layer

     Type:     C interface file

     Desc:     Interface file which defines the structures

     File:     egac_edm.x

     Sid:      egac_edm.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:27 2015

     Prg:      an

*********************************************************************21*/
#ifndef __EG_ACC_EDM_X__
#define __EG_ACC_EDM_X__

#ifdef __cplusplus
extern "C" {
#endif



PUBLIC S16 egEdmInitDb ARGS
((
Void
));
/*************************************************************
 *      handlers for the EDM STUB ****************************
*************************************************************/
PUBLIC S16 egAcHdlEdmSigReq ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

PUBLIC S16 egAcHdlEdmErrInd ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

PUBLIC S16 egAcUtlEgBuildGmCfgReq ARGS
((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
EgMngmt     *egMngmt
));

PUBLIC S16 EuLiEdmShutdown ARGS (( U8 intfType ));

PUBLIC S16 egAcHdlEdmShutDownReq ARGS
((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb
));

PUBLIC S16 egAcHdlEdmCfgCfm ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

PUBLIC S16 egAcHdlEdmSigRsp ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

PUBLIC S16 egAcHdlEdmSigInd ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

PUBLIC S16 egAcHdlEdmMsgCfg ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

PUBLIC S16 egAcHdlEdmMsgInd ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

PUBLIC S16 egAcHdlEdmMsgReq ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

#ifdef EGTP_C

PUBLIC S16 egAcSndErrMsgToApp ARGS
((
EgEvnt   *eventMsg      /* event message */
));

PUBLIC S16 egAcUtlEdmBuildMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg      **egMsg
));

PUBLIC S16 egAcUtlDEdmBuildMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg      **egMsg
));

PUBLIC Void  egDEdmBuildEgMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
U8                msgType,
EgMsg           **egMsg
));

PUBLIC S16 egAcUtlEdmValidateGmMessage ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg       *egMsg
));

PUBLIC S16 egAcEdmSaveMsg ARGS
((
U8   event,
EgMsg *egMsg,
EgErrEvnt errEvnt,
CmStatus status
));

PUBLIC S16 egAcUtlEdmMakeEvntMsg ARGS
((
EgEvnt **eventMsg,
EgMsg   *egMsg,
U8  intfType,
Buffer  *mBuf,
U8  eventType
));

#endif /* EGTP_C */

PUBLIC CmXtaTCCb*  egAcEdmTstCbFind ARGS
((
Void
));


PUBLIC S16 egAcHdlEdmSigCfm ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));


PUBLIC S16 egAcUtlDEdmValidateMsg ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
Buffer     *mBuf
));


PUBLIC S16 egAcUtlEdmValidateMsg ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
U8            apiType
));

PUBLIC S16 egAcUtlEdmValidateErrIndMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgErrEvnt   *eguErrIndEvt
));

PUBLIC S16 EuLiEdmLmCfm ARGS
((
CmStatus   status
));

PUBLIC S16 egAcEdmInit ARGS
((
Void
));

PUBLIC S16 egAcEdmDeInit ARGS
((
Void
));

PUBLIC S16 EuLiEdmGmCfg ARGS
((
EgGmDictCfg *cfg        /* Ie Cfg structure for ieDb */
));

PUBLIC S16 EuLiEdmIeCfg ARGS
((
EgIeDictCfg *cfg        /* Ie Cfg structure for ieDb */
));

#ifdef EGTP_C
PUBLIC S16 EuLiEdmDecReq ARGS
((
EgEvnt *evntMsg        /* Event structure having the egMsg */
));

PUBLIC S16 EuLiEdmEncPthReq ARGS
((
EgEvnt *evntMsg        /* Event structure having the egMsg */
));
PUBLIC S16 EuLiEdmDecPthReq ARGS
((
EgEvnt *evntMsg        /* Event structure having the egMsg */
));

PUBLIC S16 EuLiEdmEncReq ARGS
((
EgEvnt *evntMsg        /* Event structure having the egMsg */
));

PUBLIC S16 EuLiEdmGmSigInd ARGS
((
EgMsg *egMsg
));

PUBLIC S16 EuLiEdmErrInd ARGS
((
EgErrEvnt errEvnt
));

PUBLIC S16 EuLiEdmGmSigCfm ARGS
((
EgMsg *egMsg
));

/*-- eg003.201 : changes from eg006.102 : Deleted egTptProcessMsg --*/
#endif /* EGTP_C */

#ifdef EGTP_U
PUBLIC S16  egUDEdmBuildEgMsg ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
U8                 msgType,
EgUMsg           **eguMsg
));

/*-- eg003.201 : changes from eg006.102 : Deleted egUAcUtlDEdmBuildMsg --*/

PUBLIC S16 egUAcUtlValidateMsg ARGS
((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
Buffer     *mBuf
));


#endif

PUBLIC S16 EuLiEdmTptMsg ARGS
((
U8  intfType,
Buffer *mBuf
));


PUBLIC S16 edActvInit ARGS
((
Ent      ent,                 /* entity */
Inst     inst,                /* instance */
Region   region,              /* region */
Reason   reason               /* reason */
));

PUBLIC S16 edActvTsk ARGS
((
Pst    *pst,               /* post structure */
Buffer *mBuf                /* message buffer */
));

#ifdef __cplusplus
}
#endif   /* __cplusplus */

#endif   /* __EG_ACC_EDM_X__ */


/**********************************************************************

         End of file:     egac_edm.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:27 2015

**********************************************************************/

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
------------ -------- ---- ----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rkumar      1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3   eg003.201   psingh      1. Fixed warnings 
*********************************************************************91*/
