

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_kwucb.c

     Sid:      pjac_kwucb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:50 2015

     Prg:     Adarsh
*********************************************************************21*/

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
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_kwu.h"      /* CKW Acceptance defines */

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
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_kwu.x"      /* CKW Acceptance defines */


/**
@brief
@return CmXtaTCCb*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  pjAcKwuTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  pjAcKwuTstCbFind ()
#endif
{
   TRC2(pjAcKwuTstCbFind);

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change PJAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
} /* pjAcKwuTstCbFind */


/**
@brief utility function for sending the message to test engine
@param pst
@param suId
@param status
@param ptr
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcKwuSendMsg
(
Pst            *pst,
SpId           suId,
U8             status,
Void           *ptr,
Buffer         *mBuf
)
#else
PUBLIC S16 pjAcKwuSendMsg(pst, suId, status, ptr, mBuf)
Pst            *pst;
SpId           suId;
U8             status;
Void           *ptr;
Buffer         *mBuf;
#endif /* ANSI */
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   KwAcMsgQElm    *kwElm;
   KwAcKwuInfo    *kwuInfo;

   S16 ret = CMXTA_ERR_NONE;
 
   TRC3(pjAcKwuSendMsg);

   CMXTA_DBG_PARAM((_cmxtap, "pjAcKwuSendMsg())\n"));

   CMXTA_ZERO(&qElm, sizeof(CmXtaMsgQElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = pjAcKwuTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious
        message, drop it --*/
 
      /*-- Update debug prints --*/
      CMXTA_DBG_INFO((_cmxtap, "pjAcKwuTstCbFind is returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Check if any tapa directives set --*/
 
   /*-- Allocate KW memory data --*/
   kwElm = NULLP;
   CMXTA_ALLOC(&kwElm, sizeof (KwAcMsgQElm));
   if (kwElm == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcCkwSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)kwElm;
   qElm.msgFreeFun = pjAcUtlKwuFreeCb;
   
    /*** fill the suId in teh Q element****/
   kwuInfo = &(kwElm->u.kwuInfo);
   kwuInfo->cmInfo.suId = suId;
   kwuInfo->cmInfo.spId = status;

   switch (pst->event) 
   {
      case PJAC_KWU_EVT_BND_REQ:
      {
         break;
      }

      case PJAC_KWU_EVT_UBND_REQ:
      {
         kwuInfo->reason = status;
         break;
      }

      case PJAC_KWU_EVT_DAT_REQ:
      {
         kwuInfo->reason = status;
         kwuInfo->u.datReq = (KwuDatReqInfo*)ptr;
         kwElm->mBuf = mBuf;
         break;
      }

      case KWU_EVT_BND_CFM:
      {
         kwuInfo->u.status = status;
         break;
      }

      case KWU_EVT_DAT_IND:
      {
         kwuInfo->u.datInd = (KwuDatIndInfo*)ptr;
         kwElm->mBuf = mBuf; /* Take pointer of mBuf to Element */
         break;
      }

      case KWU_EVT_DAT_CFM:
      {
         kwuInfo->u.datCfm = (KwuDatCfmInfo*)ptr;
         break;
      }

      case KWU_EVT_STA_IND:
      {
         kwuInfo->u.staInd = (KwuStaIndInfo*)ptr;
         break;
      }
      /* kw005.201 added support for L2 measurement */
#ifdef LTE_L2_MEAS
      case KWU_EVT_DISC_SDU_CFM:
      {
         kwuInfo->u.discSduCfm = (KwuDiscSduInfo *)ptr;
         break;
      }
      case KWU_EVT_DAT_ACK_IND:
      {
         kwuInfo->u.datAckInd = (KwuDatAckInfo *)ptr;
         break;
      }
#endif
   }

   if( ret == ROK)
   {
      /*-- Test case found, queue the message for the tcCb --*/
       /* Push it onto the message queue --*/
       (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

       /*-- Check if the message has arrived in a TC fashion, this
            may happen if the test engine was sending a message and
            the layer sent a message back in TC fashion, do not
            trigger the test engine now in that case, the test engine
            will later have a look at the queued message --*/
       if (tcCb->busy == FALSE)
          cmXtaTCEngine(tcCb);
   }
   else
   {
      CMXTA_FREE(kwElm, sizeof(KwAcMsgQElm));
   }

   RETVALUE(ROK);
} /* pjAcKwuSendMsg */

/**
@brief Call handler for Bind confirmation 
@param pst
@param suId
@param status
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 NhLiKwuBndCfm
(
Pst *pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 NhLiKwuBndCfm(pst,suId,status)
Pst *pst;
SuId suId;
U8 status;
#endif
{
   TRC2(NhLiKwuBndCfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "NhLiKwuBndCfm():\n"));

   pst->event = KWU_EVT_BND_CFM;

   pjAcKwuSendMsg(pst, suId, status, NULLP, NULLP);

   RETVALUE(ROK);
} /* NhLiKwuBndCfm */


/**
@brief Call handler for Data Indication 
@param pst
@param suId
@param datInd
@param mBuf 
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 NhLiKwuDatInd
(
Pst            *pst,
SuId           suId,
KwuDatIndInfo  *datInd,
Buffer         *mBuf
)
#else
PUBLIC S16 NhLiKwuDatInd(pst, suId, datInd, mBuf)
Pst            *pst;
SuId           suId;
KwuDatIndInfo  *datInd;
Buffer         *mBuf;
#endif
{
   TRC2(NhLiKwuDatInd);
   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuDatInd():\n"));

   pst->event = KWU_EVT_DAT_IND;
   
   pjAcKwuSendMsg(pst, suId, 0, datInd, mBuf);
   RETVALUE(ROK); 
} /* NhLiKwuDatInd */


/**
 * @brief XTA Dedicated Channel Data Request for KWU interface.
 *
 * @details
 *
 *     Function : KwUiKwuDatReq
 *
 *     Enqueues the DatReq received from PDCP to XTA queue.
 *
 *  @param[in]  *pst
 *  @param[in]  spId
 *  @param[in]  *datReq
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 KwUiKwuDatReq
(
Pst            *pst,
SpId           spId,
KwuDatReqInfo   *datReq,
Buffer          *mBuf
)
#else
PUBLIC S16 KwUiKwuDatReq(pst, spId, datReq)
Pst            *pst;
SpId           spId;
KwuDatReqInfo   *datReq;
Buffer          *mBuf;
#endif
{
                                                                                                                                                                        
   TRC2(KwUiKwuDatReq);
                                                                                                                                                                        
   CMXTA_DBG_PARAM((_cmxtap, "KwUiKwuDDatReq():\n"));
                                                                                                                                                                        
   pst->event = PJAC_KWU_EVT_DAT_REQ;

   
   pjAcKwuSendMsg(pst, spId, 0, datReq, mBuf);
                                                                                                                                                                        
   RETVALUE(ROK);
} /* End of KwUiKwuDatReq */
                                                                                                                                                                        


/**
 * @brief XTA Bind Request for KWU interface.
 *
 * @details
 *
 *     Function : KwUiKwuBndReq
 *
 *     Enqueues the BndReq received from PDCP to XTA queue.
 *
 *  @param[in]  *pst
 *  @param[in]  suId
 *  @param[in]  spId
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 KwUiKwuBndReq
(
Pst            *pst,
SuId           suId,
SpId           spId
)
#else
PUBLIC S16 KwUiKwuBndReq(pst, suId, spId)
Pst            *pst;
SuId           suId;
SpId           spId;
#endif
{
                                                                                                                                                                        
   TRC2(KwUiKwuBndReq);
                                                                                                                                                                        
   CMXTA_DBG_PARAM((_cmxtap, "RgUiRguBndReq():\n"));
                                                                                                                                                                        
   pst->event = PJAC_KWU_EVT_BND_REQ;
                                                                                                                                                                        
   pjAcKwuSendMsg(pst, suId, spId, 0, NULLP);
                                                                                                                                                                        
   RETVALUE(ROK);
} /* End of KwUiKwuDatReq */
                                                                                                                                                                        


/**
 * @brief XTA Unbind Request Handler for KWU interface.
 *
 * @details
 *
 *     Function : KwUiKwuUbndReq
 *
 *     Enqueues the Bind Request received from PDCP to XTA queue.
 *
 *  @param[in]  *pst
 *  @param[in]  spId
 *  @param[in]  reason
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 KwUiKwuUbndReq
(
Pst            *pst,
SpId           spId,
Reason         reason
)
#else
PUBLIC S16 KwUiKwuUbndReq(pst, spId, reason)
Pst            *pst;
SpId           spId;
Reason         reason;
#endif
{
   TRC2(KwUiKwuUbndReq);
                                                                                                                                                                        
   CMXTA_DBG_PARAM((_cmxtap, "KwUiKwuUbndReq():\n"));
                                                                                                                                                                        
   pst->event = PJAC_KWU_EVT_UBND_REQ;
                                                                                                                                                                        
   pjAcKwuSendMsg(pst, 0, spId, reason, NULLP);
                                                                                                                                                                        
   RETVALUE(ROK);
} /* End of KwUiKwuUbndReq */
                                                                                                                                                                        

/**
 * @brief XTA Unbind Request Handler for KWU interface.
 *
 * @details
 *
 *     Function : KwUiKwuUbndReq
 *
 *     Enqueues the Discard Request received from PDCP to XTA queue.
 *
 *  @param[in]  *pst
 *  @param[in]  spId
 *  @param[in]  reason
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 KwUiKwuDiscSduReq
(
Pst              *pst,
SpId             spId,
KwuDiscSduInfo   *discSdu
)
#else
PUBLIC S16 KwUiKwuDiscSduReq(pst, spId, discSdu)
Pst              *pst;
SpId             spId;
KwuDiscSduInfo   *discSdu;
#endif
{
   TRC2(KwUiKwuDiscSduReq);
                                                                                                                                                                        
   CMXTA_DBG_PARAM((_cmxtap, "KwUiKwuDiscSduReq():\n"));
                                                                                                                                                                        
   pst->event = PJAC_KWU_EVT_DISC_SDU_REQ;
                                                                                                                                                                        
   pjAcKwuSendMsg(pst, 0, spId, 0, discSdu);
                                                                                                                                                                        
   RETVALUE(ROK);
} /* End of KwUiKwuDiscSduReq */



/********************************************************************30**

         End of file:     pjac_kwucb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:50 2015

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
/main/1      ---      av         1. Initial release.
*********************************************************************91*/

