


/**********************************************************************
 
    Name:   LTE MAC layer
 
    Type:   C include file
 
    Desc:   Defines required by RGU interface of XTA LTE MAC
 
    File:   rgac_rgu.x
 
    Sid:      rgac_rgu.x@@/main/3 - Sat Jul 30 02:21:06 2011
 
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


#ifndef __RGAC_RGUX__
#define __RGAC_RGUX__

#ifdef __cplusplus
extern "C" {
#endif


/**** RGU reg fucntion prototypes***********/


/**** RGU hdl fucntion prototypes***********/

EXTERN S16 rgAcHdlRguBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlRguBndCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlRguUbndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlRguCDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlRguDDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlRguCDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlRguDDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlRguCStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

#ifndef RGU_INF_OPTIMIZATION
EXTERN S16 rgAcHdlRguDStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#else
EXTERN S16 rgAcHdlRguConsolidatedDStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#endif

EXTERN S16 rgAcHdlRguCStaRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcHdlRguDStaRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

#ifdef LTE_L2_MEAS
EXTERN S16  rgAcHdlRguHqStaInd  ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#ifdef LTEMAC_R9
EXTERN S16  rgAcHdlRguL2MUlThrpMeasReq  ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#endif
#endif
/**** RGU utl fucntion prototypes***********/

EXTERN S16 rgAcUtlRguGenCDatReq ARGS((
RguCDatReqInfo  *datReq,
CmLteCellId     cellId,
CmLteLcId       lcId,
CmLteLcType       lcType,
CmLteTimingInfo *timingInfo,
CmLteRnti       rnti,
U32             bufSize,
U32             transId,
Bool            sendNoMatter,
U8              bcchIdx
));
#ifdef LTE_L2_MEAS
EXTERN S16 rgAcUtlRguGenDDatReq ARGS((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
RguDDatReqInfo  *datReqInfo,
CmLteCellId     cellId,
U8              ueId,
CmLteRnti       rnti,
U32             transId,
U8              numLch,
RguLchDatReq    *lchData,
U8              sndLess,
U8              isMeasTypeDlTpt
));
#else
EXTERN S16 rgAcUtlRguGenDDatReq ARGS((
RguDDatReqInfo *datReqInfo,
CmLteCellId     cellId,
U8              ueId,
CmLteRnti       rnti,
U32             transId,
U8              numLch,
RguLchDatReq    *lchData,
U8              sndLess
));
#endif
EXTERN S16 rgAcHdlRguSkipValidation ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 rgAcRguSendMsg ARGS((
Pst            *pst,
SpId           suId,
Reason         reason,
Void           *ptr
));
#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __RGAC_RGUX_ */


/**********************************************************************
         End of file:     rgac_rgu.x@@/main/3 - Sat Jul 30 02:21:06 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm            1. Initial Release.
/main/2      ---     sm            1. LTE MAC 2.1 release
/main/3      ---     dvasisht      1. Updated for LTE MAC Release 3.1
$SID$        ---     rt            1. LTE MAC 4.1 release
*********************************************************************91*/
