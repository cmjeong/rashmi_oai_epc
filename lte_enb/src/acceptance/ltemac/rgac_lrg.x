


/**********************************************************************
 
    Name:   LTE MAC layer
 
    Type:   C include file
 
    Desc:   Defines required by LRG interface of XTA LTE MAC
 
    File:   rgac_lrg.x
 
    Sid:      rgac_lrg.x@@/main/3 - Sat Jul 30 02:20:58 2011
 
    Prg:    sm 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000372       LTE MAC
*
*/


#ifndef __RGAC_LRGX__
#define __RGAC_LRGX__

#ifdef __cplusplus
extern "C" {
#endif


/**** LRG reg fucntion prototypes***********/


/**** LRG hdl fucntion prototypes***********/

EXTERN S16 rgAcHdlLrgGenCfgReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgTfuSapCfgReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgRguSapCfgReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgCrgSapCfgReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgRgrSapCfgReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgRgmSapCfgReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 rgAcHdlLrgCfgCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgSchInsCfgReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgSchCfgCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgCntrlReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgCntrlCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgSchCntrlReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgSchCntrlCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgStsReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgStsCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgStaReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgStaCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgSchStaCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgSchStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgTrcInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgDirective ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgSkipValidation ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#ifdef LTE_L2_MEAS
EXTERN S16 rgAcHdlLrgSchL2MeasReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 rgAcHdlLrgSchL2MeasCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgSchL2StopMeasCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 rgAcHdlLrgSchSendL2MeasReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlLrgSchStopL2MeasReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#endif
/**** LRG utl fucntion prototypes***********/

EXTERN S16 rgAcUtlLrgCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,    /* spCb data structure  */
RgCntrl         *cntrl,
U8              action,
U8              subAction
));
EXTERN S16 rgAcLrgSendMsg ARGS((
Pst            *pst,
RgMngmt        *cfm
));

EXTERN S16 rgAcUtlFreeLrgCb ARGS((
CmXtaMsgQElm   *qElm
));
EXTERN CmXtaTCCb*  rgAcLrgTstCbFind ARGS((
Void
));
#ifdef LTE_L2_MEAS
EXTERN S16 rgAcUtlLrgSchL2MeasReq ARGS((
CmXtaTCCb           *tcCb,
CmXtaSpCb           *spCb,
LrgSchMeasReqInfo   *measInfo
));
EXTERN S16 rgAcLrgSchL2SendMsg ARGS((
Pst               *pst,
LrgSchMeasCfmInfo *cfm
));
EXTERN S16 rgAcUtlLrgSchValL2MeasCfm ARGS((
CmXtaTCCb           *tcCb,
CmXtaSpCb           *spCb,
LrgSchMeasCfmInfo   *measInfo
));
#endif
#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __RGAC_LRGX_ */


/**********************************************************************
         End of file:     rgac_lrg.x@@/main/3 - Sat Jul 30 02:20:58 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm            1. Initial Release.
/main/2      ---     sm            1. LTE MAC 2.1 release
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
$SID$        ---    rt     1. LTE MAC 4.1 release
*********************************************************************91*/
