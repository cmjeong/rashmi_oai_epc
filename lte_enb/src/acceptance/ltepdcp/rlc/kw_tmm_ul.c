

/**********************************************************************

     Name:     LTE-RLC Layer 
  
     Type:     C file
  
     Desc:     Source code for RLC Transparent mode assembly and
               reassembly.This file contains following functions
                
                  --kwTmmQSdu
                  --kwTmmSndToLi
                  --kwTmmRcvFrmLi
                  --kwTmmReEstablish 

     File:     gp_tmm.c

     Sid:      kw_tmm_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:49 2014

     Prg:      vp 

**********************************************************************/
/** @file gp_tmm.c
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

/**
 * @brief
 *
 *        Handler to process the Data Indication from the lower layer and send the SDU to upper layer.
 *
 * @b Description:
 *
 *        This function processes the PDU receivied from the 
 *        lower layer and sends the same pdu as SDU to the 
 *        upper layer.It sends CRNTI along with the SDU for
 *        CCCH.
 *            
 *  @param[in] rbCb    RB control block. 
 *  @param[in] tCrnti  TCRNTI  
 *  @param[in] pdu     PDU
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef CCPU_OPT
#ifdef ANSI
PUBLIC S16 kwTmmRcvFrmLi
(
KwCb      *gCb,
KwUlRbCb    *rbCb,                /* Rb Control Block */
CmLteRnti  tCrnti,              /* Pdu  data and related information */
Buffer    *pdu                  /* PDU */
)
#else
PUBLIC S16 kwTmmRcvFrmLi(gCb,rbCb, tCrnti, pdu)
KwCb      *gCb;
KwUlRbCb    *rbCb;                /* Rb Control Block */
CmLteRnti  tCrnti;              /* Pdu  data and related information */
Buffer    *pdu;                 /* PDU */
#endif
#else
#ifdef ANSI
PUBLIC S16 kwTmmRcvFrmLi
(
KwCb      *gCb,
KwUlRbCb    *rbCb,                /* Rb Control Block */
Buffer    *pdu                  /* PDU */
)
#else
PUBLIC S16 kwTmmRcvFrmLi(gCb,rbCb, pdu)
KwCb      *gCb;
KwUlRbCb  *rbCb;                /* Rb Control Block */
Buffer    *pdu;                 /* PDU */
#endif
#endif /* CCPU_OPT */
{
   KwKwuSapCb *kwKwSap;         /* SAP Information */
   KwuDatIndInfo *datIndInfo;   /* Data Indication Information */
   /* kw005.201 ccpu00117318, updating the statistics */
   MsgLen     msgLen;
 
   TRC2(kwTmmRcvFrmLi) 
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_TM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL), (gCb->init.prntBuf,
           "kwTmmRcvFrmLi(rbCb, pdu)\n")); 
#endif 
   KW_ALLOC(gCb,datIndInfo,sizeof(KwuDatIndInfo));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if ( datIndInfo == NULLP )
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW202, (ErrVal) RFAILED,
                       "KW_ALLOC failed for datIndInfo.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
   kwKwSap = gCb->u.ulCb->kwuUlSap;    
   cmMemcpy((U8 *)&(datIndInfo->rlcId), (U8 *)&(rbCb->rlcId), sizeof(CmLteRlcId));
/*   KW_MEM_CPY(&(datIndInfo->rlcId),&(rbCb->rlcId),sizeof(CmLteRlcId));*/
#ifdef CCPU_OPT 
   if ( rbCb->lch.lChType == CM_LTE_LCH_CCCH ) 
   {
      datIndInfo->tCrnti = tCrnti;
   }
#endif 
   /* kw005.201 ccpu00117318, updating the statistics */
   gCb->genSts.pdusRecv++;
   SFndLenMsg(pdu, &msgLen);
   gCb->genSts.bytesRecv += msgLen;
   /* If trace flag is enabled send the trace indication */
   if(gCb->init.trc == TRUE)
   {
      /* Populate the trace params */
      kwLmmSendTrc(gCb,KWU_EVT_DAT_IND, pdu);
   }

   KwUiKwuDatInd( &kwKwSap->pst, kwKwSap->suId, datIndInfo, pdu);
   
   RETVALUE(ROK); 
}

/**
 *
 * @brief 
 * 
 *        Handler to process the re-establishment request received from the upper layer. 
 *
 * @b Description: 
 *
 *        This function empties the SDU queue for the RB in the downlink.
 *            
 *  @param[in] rbCb  RB control block. 
 *
 *  @return  S16
 *      -# ROK 
 *       
 **************************************************************************************/
#ifdef ANSI
PUBLIC S16 kwTmmUlReEstablish
(
KwCb        *gCb,
KwUlRbCb    *rbCb         /* RB Control Block */
)
#else
PUBLIC S16 kwTmmUlReEstablish(rbCb)
KwCb        *gCb;
KwRbCb *rbCb;            /* RB Control Block */
#endif
{

   TRC2(kwUlTmmReEstablish)
#ifdef DEBUGP  
   KWDBGP(gCb,(KW_DBGMASK_TM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwTmmReEstablish(rbCb)\n"));
#endif
   RETVALUE(ROK);
}

#ifdef _cplusplus
}
#endif
/*@}*/
/********************************************************************30**
         End of file:     kw_tmm_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:49 2014
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
/main/2      ---       nm   1. LTERLC Release 2.1
/main/3      kw002.201 vp   1. Patch for optimization,fixes for multi-region
                               and retransmission.
/main/4      kw005.201 ap   1. Updating the statistics.                       
*********************************************************************91*/

