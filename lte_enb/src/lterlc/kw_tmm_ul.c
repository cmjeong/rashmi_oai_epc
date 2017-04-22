


/**********************************************************************

     Name:     LTE-RLC Layer 
  
     Type:     C file
  
     Desc:     Source code for RLC Transparent mode assembly and
               reassembly.This file contains following functions
                
                  --kwTmmQSdu
                  --kwTmmSndToLi
                  --kwTmmRcvFrmLi
                  --kwTmmReEstablish 

     File:     gp_tmm_ul.c

     Sid:      gp_tmm_ul.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:44 2016

     Prg:      vp 

**********************************************************************/
static const char* RLOG_MODULE_NAME="TMM";
static int RLOG_MODULE_ID=2048;
static int RLOG_FILE_ID=201;

/** @file gp_tmm_ul.c
@brief RLC Transparent Mode module
*/

/*
 *      This software may be combined with the following TRILLIUM
 *      software:
 *
 *      part no.                      description
 *      --------    ----------------------------------------------
 *      1000372     LTE-MAC
 *      1000369     LTE-RRC
 */

/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "kw_env.h"        /* RLC environment options */

#include "kw.h"            /* RLC defines */
#include "kw_err.h"            /* RLC defines */
#include "kw_ul.h"

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */

#include "kw.x"
#include "kw_ul.x"

/** @addtogroup tmmode */
/*@{*/

#define KW_MODULE (KW_DBGMASK_TM | KW_DBGMASK_UL)

/**
 * @brief
 *    Handler to process the Data Indication from the lower layer and send the 
 *    SDU to upper layer.
 *
 * @details
 *    This function processes the PDU receivied from the lower layer and sends 
 *    the same pdu as SDU to the upper layer.It sends CRNTI along with the SDU 
 *    for CCCH.
 *            
 * @param[in] gCb     RLC Instance Control Block
 * @param[in] rbCb    RB control block. 
 * @param[in] tCrnti  TCRNTI  
 * @param[in] pdu     PDU
 * 
 * @return  S16
 *    -# ROK 
 *    -# RFAILED 
 */
#ifdef CCPU_OPT
#ifdef ANSI
PUBLIC Void kwTmmRcvFrmLi
(
KwCb        *gCb,
KwUlRbCb    *rbCb,  
CmLteRnti   tCrnti,  
Buffer      *pdu      
)
#else
PUBLIC Void kwTmmRcvFrmLi(gCb,rbCb, tCrnti, pdu)
KwCb        *gCb;
KwUlRbCb    *rbCb;  
CmLteRnti   tCrnti; 
Buffer      *pdu;  
#endif
#else
#ifdef ANSI
PUBLIC Void kwTmmRcvFrmLi
(
KwCb       *gCb,
KwUlRbCb   *rbCb,         
Buffer     *pdu            
)
#else
PUBLIC Void kwTmmRcvFrmLi(gCb,rbCb, pdu)
KwCb       *gCb;
KwUlRbCb   *rbCb;         
Buffer     *pdu;         
#endif
#endif 
{
   KwuDatIndInfo   *datIndInfo;   /* Data Indication Information */
   MsgLen          msgLen;
 
   TRC2(kwTmmRcvFrmLi) 

   /* Creating static memory for KwuDatIndInfo. #else will be 
    * removed once the sanity testing is performed for all platforms */
#if 1
   KwuDatIndInfo datIndInfoTmp;
   datIndInfo = &datIndInfoTmp;
#else
   KW_SHRABL_STATIC_BUF_ALLOC(gCb->u.ulCb->kwuUlSap->pst.region,
         gCb->u.ulCb->kwuUlSap->pst.pool, datIndInfo, sizeof(KwuDatIndInfo));
#endif
#if (ERRCLASS & ERRCLS_ADD_RES)
   if ( datIndInfo == NULLP )
   {   
      RLOG_ARG2(L_FATAL,DBG_RBID,rbCb->rlcId.rbId,
            "Memory Allocation failed UEID:%d CELLID:%d",
            rbCb->rlcId.ueId,
            rbCb->rlcId.cellId);   
      RETVOID;
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
   KW_MEM_CPY(&(datIndInfo->rlcId),&(rbCb->rlcId),sizeof(CmLteRlcId));
#ifdef CCPU_OPT 
   if ( rbCb->lch.lChType == CM_LTE_LCH_CCCH ) 
   {
      datIndInfo->tCrnti = tCrnti;
   }
#endif 
   gCb->genSts.pdusRecv++;
   SFndLenMsg(pdu, &msgLen);
   gCb->genSts.bytesRecv += msgLen;
   /* If trace flag is enabled send the trace indication */
   if(gCb->init.trc == TRUE)
   {
      /* Populate the trace params */
      kwLmmSendTrc(gCb,KWU_EVT_DAT_IND, pdu);
   }
   KwUiKwuDatInd( &gCb->u.ulCb->kwuUlSap->pst, 
                  gCb->u.ulCb->kwuUlSap->suId, 
                  datIndInfo, pdu);
   
   RETVOID;
}

/**
 * @brief 
 *    Handler to process the re-establishment request received from the upper 
 *    layer. It is just a hook for future enhancement. 
 *
 *            
 * @param[in] gCb   RLC Instance Control Block
 * @param[in] rbCb  RB control block. 
 *
 * @return  S16
 *    -# ROK 
 *       
 **/
#ifdef ANSI
PUBLIC Void kwTmmUlReEstablish
(
KwCb        *gCb,
KwUlRbCb    *rbCb        
)
#else
PUBLIC Void kwTmmUlReEstablish(rbCb)
KwCb        *gCb;
KwRbCb      *rbCb;          
#endif
{
   TRC2(kwUlTmmReEstablish)

   RLOG_ARG0(L_DEBUG,DBG_RBID,rbCb->rlcId.rbId,"do nothing for TMM for ReEstablish");
   RETVOID;
}

#ifdef _cplusplus
}
#endif
/*@}*/
/********************************************************************30**
         End of file:     gp_tmm_ul.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:44 2016
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
/main/1      ---       vp   1. initial release.
*********************************************************************91*/
