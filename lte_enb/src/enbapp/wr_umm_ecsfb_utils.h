
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm.h

     Sid:      wr_umm_ecsfb_utils.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:53:28 2014

     Prg:      Sriky 

*********************************************************************21*/



#ifndef __WR_UMM_ECSFB_UTILS_H__
#define __WR_UMM_ECSFB_UTILS_H__

#include "wr.h"
#include "wr_cmn.h"
#include "wr_umm_meas.h"
#include "wr_umm_anrmeas.h"
#include "wr_umm_csfb.h"
#include "wr_lwr.h"
#include "wr_smm_smallcell.h"
#include "wr_utils.h"
#include "wr_ifm_s1ap.h"
#include "wr_umm_trans.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct wrUmmS1UlTnMsgParams
{
   U32                  cdmaType;
   TknStrOSXL           *mainSecId;
   Bool                 hoReqdInd;
   U8                   numOfPilotLst;
   WrCdmaRttPilotLst    **PilotList;
   TknStrOSXL           *ulCdmaInfo;
   TknStrBSXL           *meId;
}WrUmmS1UlTnlMsgParams; 

EXTERN S16 wrUmmBuildAndSndCdmaDlInfTfr(WrUmmTransCb *transCb, TknStrOSXL *cdmaPdu,U32 ratTyp);

EXTERN S16 wrUmmRrcFillCdmaDlInfTfr
(
NhuDatReqSdus                *dlInfoTfrPdu,
TknStrOSXL                   *cdmaPdu,
U32                           ratTyp,
U8                            pdcpId
);

EXTERN Bool wrUmmUtilGetUeDualRx( WrUeCb *ueCb,U32 ratType);
EXTERN Bool wrUmmUtilsIsEcsfbSupported(WrUeCb *ueCb);

EXTERN S16 wrUmmFillCdmaRedirectionInfo(NhuRedirectedCarrierInfo *redirInfoIe,WrUmmRedirectInfo *cdmaRedirectInf);  

EXTERN S16 wrUmmRrcFillHoFrmEutraPrepReqInfo
(
   NhuDatReqSdus        *nhuDatReqSdu,
   WrUeCb               *ueCb,
   U8                   cdmaType,
   Bool                 isConCurrHoHrpd,
   TknStrOSXL           *mobilityParams,
   Bool                 sndDualRxTxRedirectInd  /*RRC Rel10 Upgrade*/
);

EXTERN S16 wrUmmRrcFillMobFrmEutraCmd
(
   NhuDatReqSdus            *nhuDatReqSdu,
   TknStrOSXL               *cdmaS1Pdu,
   U32                      ratTyp
);


EXTERN WrUmmRedirectInfo* wrUmmFillCdmaRedirectInfo( WrUeCb *ueCb, wrCsfbRatType ratPriority);

EXTERN S16 wrFillSrvccInfoIe
(
WrUeCb                       *ueCb,
WrUmmS1UlTnlMsgParams        *ulTnlMsgParams,
SztCdma2000OneXSRVCCInfo     *ie,
S1apPdu                      *ulCdmaPdu
);

EXTERN S16 wrFillPilotLstIe
(
   U8                            cellId,
   SztCdma2000OneXSRVCCInfo      *ie,
   WrUmmS1UlTnlMsgParams         *ulTnlMsgParams,
   S1apPdu                       *ulCdmaPdu
);
EXTERN S16 wrUmmS1apBldUlCdmaPdu
(
WrUeCb                       *ueCb,
WrUmmS1UlTnlMsgParams        *ulTnlMsgParams,
S1apPdu                      **pdu
);

EXTERN S16  wrEmmGetHighestPrioFreq(U32 bandClass, U32 *arfcn, WrCellId cellId);
EXTERN S16  wrEmmGetHighestPrioBand(WrUeCb *ueCb, U32 *bandClass);
#if 0
EXTERN S16 wrEmmAnrNumCdmaCell(U8 cdmaType,WrCellId cellId);
#endif
EXTERN Bool wrUmmIs1xCdmaBandSupported(WrUeCb *ueCb,U32 *bandClass);
EXTERN S16 wrEmmGetRatPriority(WrPlmnId *plmn, WrRatPriorityList *ratPriority, WrCellId cellId);
EXTERN Bool wrEmmIsDualRxSupported(WrCellId cellId);

EXTERN S16 wrUmmHdlAndPrcRabMsg
(
WrUmmTransCb              *incTrans,
WrUmmMsgCause             *cause
);

EXTERN S16 wrFillEcsfbMainSecId
(
TknStrOSXL                   *ptr,
U16                          len,
Data                         *val,
CmMemListCp                  *mem
);
EXTERN  S16 wrUmmGet1xRttNeighCell
(
   WrUeCb              *ueCb,
   WrCdmaRttPilotLst   **cdma1xRttPilotLst,
   U8                  ratPriority
);
EXTERN S16 wrEmmIsCsfbOrEcsfbMeasSup
(
WrCellId                    cellId, 
Bool                        csfbOrEcsfbSup,
U8                          *csfbFlag
);

EXTERN S16 wrEmmGetCdma1xRttTgtCell(
TknStrOSXL    **sectorIdPtr,
WrCellId      cellId
);

EXTERN S16 wrUmmChkOneBandAndFreq
(
 WrUeCb           *ueCb
);
/*RRC Rel10 Upgrade - start*/
EXTERN Bool wrUmmUtilGetUeDualRxTx(WrUeCb *ueCb, U32 ratPriority);
EXTERN Bool wrUmmUtilGetUeEcsfbAndDualRxTxSuppCfgs(WrUeCb *ueCb);
EXTERN Bool wrEmmIsDualRxTxSupported(WrCellId cellId);
/*RRC Rel10 Upgrade - end*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_UMM_ECSFB_UTILS_H__ */



/********************************************************************30**

           End of file:     wr_umm_ecsfb_utils.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:53:28 2014

*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
