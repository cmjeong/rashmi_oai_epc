
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_s1srcho.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_UMM_S1SRCHO_H__
#define __WR_UMM_S1SRCHO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "wr.h"
#include "wr_cmn.h"
#include "wr_umm_trans.h"
/*UE History info - start*/
#include "cm_pasn.h"
#include "cm_pasn.x"
/*UE History info - end*/

#define WR_UMM_S1_SRC_HANDLE_HO_FAIL(_transCb)\
{\
   _transCb->ueCb->hoTransId = 0;\
   _transCb->ueCb->hoType = WR_HO_TYPE_NONE;\
   _transCb->ueCb->mobCtrlState = WR_HO_NORMAL;\
}
/*SRVCC to GERAN changes start*/
#define WR_UMM_TLV_PK_TAGIE(_val1, _val2)\
{\
   _val2 = _val1;\
}

#define WR_UMM_TLV_PK_LI(_val1, _val2 )\
{\
   _val2 = _val1;\
}
#define WR_UMM_TLV_PK_RXLEV(_val1, _val2 )\
{\
   _val2 = _val1;\
}
#define WR_UMM_OLD_BSS_TO_NEW_BSS_IE 0x3A
#define WR_UMM_IRAT_HO_TGT_RAD_INFO 0x03
#define WR_UMM_LEN_IRAT 3
#define WR_UMM_LEN_IRAT_HO_TGT_RAD_INFO 1
/*SRVCC to GERAN changes ends*/
   
/* Function Prototypes */

EXTERN S16 wrUmmS1HoFillCause(SztCause *transCause, SztCause *cause);
EXTERN S16 wrUmmS1SrcHoOvrallTmrExp(WrUeCb  *ueCb);
EXTERN S16 wrUmmS1SrcHoFillPLMNId(S1apPdu   *pdu,WrPlmnId  *plmnId, SztPLMNidentity   *plmnIe);
EXTERN S16 wrEmmMmeSztFillLAC(U16 lac, SztLAC *lAC);


typedef struct wrUmmS1SrcHoRabInfo
{
   U8                        erabId;
   U8                        rbId;
   U8                        rbDir;
   U8                        qci;
   U8                        tnlCfgState;
   U8                        expectedTnlRsp;
   /* Indicates that Data forwarding is available or not */
   Bool                      dlFwding;
   /* Data Forwarding tunnel info */
   CmTptAddr                 peerAddr;
   U32                       locTunId;
   U32                       datFwdUlRemTunId; /* UL Local tunnel id */
   U32                       datFwdDlRemTunId; /* DL Local tunnel id */
   U32                       datFwdUlLclTunId; /* UL Local tunnel id */
   U32                       datFwdDlLclTunId; /* DL Local tunnel id */
   Bool                     isULDatFwdReq; /* Set to TRUE only if UL_GTP Tnl Info is rcvd in HovrCmd */
} WrUmmS1SrcHoRabInfo;
/* IRAT_HO */
typedef struct wrUmmIntraLteHoInfo
{
   U16                      eNBType;        /* Fill at the time of transaction creation.*/
   WrEcgi                   ecgi;
   U16                      tac;            /* Fill at the time of transaction creation.*/
   Bool                     isDirectPathAvl; /* Whether direct Path with the Tgt exists or not */
} WrUmmIntraLteHoInfo;

typedef struct wrUmmIRatGeranHoInfo
{
  Bool                          psSrvcNotAvlbl;  
  U8                            bsic;
  U16                           cId;         
  U16                           lac;         
  U8                            rac;         
  U8                            rxLev;
  U8                            bandIndicator;/* BandInc IE for MobilityFromUtraCmd */
} WrUmmIRatGeranInfo;

typedef struct wrUmmIRatUtraHoInfo
{
  U16                           psc;
  U16                           rncId;         
  U16                           cId;         
  U16                           lac;         
  U8                            rac;         
  TknStrOSXL                    utraUeCapContainer; 
} WrUmmIRatUtraInfo;

typedef struct wrUmmS1SrcHoTrans
{
  U8                  X2Presence; 
 U8                       state;
   U32                      crnti;          /* Filled at the time of transaction creation*/
   U32                      cellId;         /* Filled at the time of transaction creation.*/
#if 0
   /* Removing as these params are not used */ 
   U32                      mme_Ue_S1ap_Id;
   U32                      enb_Ue_S1ap_Id;
#endif
   U8                       numOfRbInfo;
   SztCause                 *sztCause;      /* Fill at the time of transaction creation.*/
   WrUmmMsgCause            *Cause;
   SztHovrTyp               *sztHovrTyp;    /* Fill at the time of transaction creation.*/
   WrPlmnId                 plmnId;         /* Fill at the time of transaction creation.*/
   WrUmmS1SrcHoRabInfo      *rbInfo;
   SztE_RABLst              sztE_RABLst;    /* Release List from MME.*/
   TknStrOSXL               srcToTgtCntr;
   TknStrOSXL               rrcCont;
   TknStrOSXL               *tgtToSrcCont;  /* Received From target eNB.*/
   WrUmmTimer               s1RelocTmr;/* Timer used at Source to reset L2 */
   WrUmmTimer               s1CancelTmr;
   Buffer                   *hoCmd;
   /* CSG_DEV start */
   U32                      csgId; /* CSG ID */
   U8                       csgCellAccessMode; /* CSG Access Mode */
   U16                      tgtPci;
   TknStrOSXL               nasSecParamFrmEutran;
   TknU32                   srvccHoInd; /* SRVCC handover presence flag for interrat and geran */
   /* CSG_DEV end */
   union {
     WrUmmIntraLteHoInfo intraLteInfo; /* Contains parameters specific to intra LTE HO */ 
     WrUmmIRatUtraInfo   interRatInfo; /* Contains parameters specific to inter RAT HO to UTRA */
     WrUmmIRatGeranInfo  interRatGeranInfo; /* Contains parameters specific to inter RAT HO to GERAN */
   }t;
} WrUmmS1SrcHoTrans;

EXTERN S16 wrUmmS1SrcHoOvrallTmrExp(WrUeCb  *ueCb);
EXTERN S16 wrUmmS1SrcHoRelocTmrExp(WrUeCb  *ueCb);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* end of __WR_UMM_S1SRCHO_H__ */



/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
