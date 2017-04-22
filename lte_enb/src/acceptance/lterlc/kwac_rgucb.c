

/************************************************************************
 
     Name:     LTE-RLC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     kwac_rgucb.c 
  
     Sid:      kwac_rgucb.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:41 2014
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_rgucb.c
@brief This file contains the definitions for XTA RGU interface call 
handler functions. These functions are called from function defined in
rgac_rguhdl.c
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
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_rgu.h"      /* CKW Acceptance defines */

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
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_rgu.x"      /* CKW Acceptance defines */


/************************************************************************
                             RGU Interface Callback Functions
************************************************************************/
/**
 * @brief XTA Function to test case association for a received message.
 *
 * @details
 *
 *     Function : kwAcRguTstCbFind
 *     
 *     Whenever a message is received from RLC to Dummy-MAC, this 
 *     function is called to check if this is associated to a running 
 *     test case. If test case shut down is done, then any message
 *     received there after is discarded as a spurious message.
 *     
 *  @return  CmXtaTCCb*
 *      -# NULLP
 *      -# CmXtaTCCb*
 **/
#ifdef ANSI
PUBLIC CmXtaTCCb*  kwAcRguTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  kwAcRguTstCbFind ()
#endif
{
   TRC2(kwAcRguTstCbFind);
 
   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change SOAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP) &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif
 
   RETVALUE(NULLP);
} /* End of kwAcRguTstCbFind */


/**
 * @brief XTA Function to enqueue a interface primitive to Test Engine Queue.
 *
 * @details
 *
 *     Function : kwAcRguSendMsg
 *     
 *     Allocates a queue element data structure and fills in
 *     the appropriate primitive with additional information
 *     like free function pointer and enqueue it to the XTA queue. 
 *     
 *  @param[in]  *pst 
 *  @param[in]  suId 
 *  @param[in]  reason 
 *  @param[in]  *ptr 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 kwAcRguSendMsg
(
Pst            *pst,
SuId           suId,
SpId           spId,
Reason         reason,
Void           *ptr
)
#else
PUBLIC S16 kwAcRguSendMsg(pst, suId, spId, reason, ptr)
Pst            *pst;
SuId           suId;
SpId           spId;
Reason         reason;
Void           *ptr;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   KwAcMsgQElm *kwElm;
   KwAcRguInfo  *rguInfo;
   S16 ret = CMXTA_ERR_NONE;
 
   TRC3(kwAcRguSendMsg);
 
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcRguTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped KWAC_ENHANCE: may be Sts Ind etc...\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   kwElm = NULLP;
   CMXTA_ALLOC(&kwElm, sizeof (KwAcMsgQElm));
   if (kwElm == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcRguSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)kwElm;
   qElm.msgFreeFun = kwAcUtlFreeRguCb;
   rguInfo = &(kwElm->u.rguInfo);

   /*** fill the suId in the Q element****/
   rguInfo->suId = suId;
   rguInfo->spId = spId;

   switch (pst->event) 
   {
      case KWAC_RGU_EVT_BND_REQ: 
      {
         break;
      }
      case KWAC_RGU_EVT_UBND_REQ: 
      {
         rguInfo->reason   = reason;
         break;
      }
      case KWAC_RGU_EVT_CSTA_RSP:
      {
         rguInfo->u.cStaRsp = (RguCStaRspInfo *)ptr; 
         break;
      }
      case KWAC_RGU_EVT_DSTA_RSP: 
      {
        /* optimization for 4uepertti: dStaInd in rlc has been changed from 
         *  pointer to structure hence guInfo->u.dStaRsp needs be allocated
         *before posting to xta queue*/ 
         SGetSBuf(0,0, &(rguInfo->u.dStaRsp),  sizeof(RguDStaRspInfo));
         cmMemcpy(rguInfo->u.dStaRsp,ptr,sizeof(RguDStaRspInfo));
         break;
      }
      case KWAC_RGU_EVT_CDAT_REQ:
      {
         rguInfo->u.cDatReq = (RguCDatReqInfo *)ptr; 
         break;
      }
      case KWAC_RGU_EVT_DDAT_REQ: 
      {
         rguInfo->u.dDatReq = (RguDDatReqInfo *)ptr; 
         break;
      }
      /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
      case KWAC_RGU_EVT_L2MULTHR_REQ: 
      {
         rguInfo->u.l2mUlThrpMeasReq = (RguL2MUlThrpMeasReqInfo * )ptr;
         break;
      }
#endif
#endif
      default:
         ret = CMXTA_ERR_INT;
   }/* end fo switch */

   if( ret == CMXTA_ERR_NONE)
   {
      /*-- Test case found, queue the message for the tcCb --*/
      /* Push it onto the message queue --*/
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
 
      /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will KWAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   } 
   else
   {
      CMXTA_FREE(kwElm, sizeof(KwAcMsgQElm));
   }
 
   RETVALUE(ret);
} /* end of kwAcRguSendMsg() */


/**
 * @brief XTA Bind Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : RgUiRguBndReq
 *     
 *     Enqueues the Bind Request received from RLC to XTA queue. 
 *     
 *  @param[in]  *pst 
 *  @param[in]  suId 
 *  @param[in]  spId
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 RgUiRguBndReq
(
Pst            *pst,
SuId           suId,
SpId           spId
)
#else
PUBLIC S16 RgUiRguBndReq(pst, suId, spId)
Pst            *pst;
SuId           suId;
SpId           spId;
#endif
{
   TRC2(RgUiRguBndReq);
 
   CMXTA_DBG_PARAM((_cmxtap, "RgUiRguBndReq():\n"));

   pst->event = KWAC_RGU_EVT_BND_REQ;
 
   kwAcRguSendMsg(pst, suId, spId, 0, NULLP);    

   RETVALUE(ROK);
} /* End of RgUiRguBndReq */


/**
 * @brief XTA Unbind Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : RgUiRguUbndReq
 *     
 *     Enqueues the Bind Request received from RLC to XTA queue. 
 *     
 *  @param[in]  *pst 
 *  @param[in]  spId 
 *  @param[in]  reason
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 RgUiRguUbndReq
(
Pst            *pst,
SpId           spId,
Reason         reason
)
#else
PUBLIC S16 RgUiRguUbndReq(pst, spId, reason)
Pst            *pst;
SpId           spId;
Reason         reason;
#endif
{
   TRC2(RgUiRguUbndReq);
 
   CMXTA_DBG_PARAM((_cmxtap, "RgUiRguUbndReq():\n"));

   pst->event = KWAC_RGU_EVT_UBND_REQ;
 
   kwAcRguSendMsg(pst, 0, spId, reason, NULLP);    

   RETVALUE(ROK);
} /* End of RgUiRguUbndReq */


/**
 * @brief RLC Common Channel Status Response for RGU interface.
 *
 * @details
 *
 *     Function : RgUiRguCStaRsp
 *     
 *     Enqueues the CStaRsp received from RLC to XTA queue. 
 *     
 *  @param[in]  *pst 
 *  @param[in]  spId 
 *  @param[in]  *staRsp 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 RgUiRguCStaRsp
(
Pst            *pst,
SpId           spId,
RguCStaRspInfo *staRsp
)
#else
PUBLIC S16 RgUiRguCStaRsp(pst, spId, staRsp)
Pst            *pst;
SpId           spId;
RguCStaRspInfo *staRsp;
#endif
{
   TRC2(RgUiRguCStaRsp);
 
   CMXTA_DBG_PARAM((_cmxtap, "RgUiRguCStaRsp():\n"));

   pst->event = KWAC_RGU_EVT_CSTA_RSP;
 
   kwAcRguSendMsg(pst, 0, spId, 0, staRsp);    

   RETVALUE(ROK);
} /* End of RgUiRguCStaRsp */


/**
 * @brief XTA Dedicated Channel Status Response for RGU interface.
 *
 * @details
 *
 *     Function : RgUiRguDStaRsp
 *     
 *     Enqueues the DStaRsp received from RLC to XTA queue. 
 *     
 *  @param[in]  *pst 
 *  @param[in]  spId 
 *  @param[in]  *staRsp 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 RgUiRguDStaRsp
(
Pst            *pst,
SpId           spId,
RguDStaRspInfo *staRsp
)
#else
PUBLIC S16 RgUiRguDStaRsp(pst, spId, staRsp)
Pst            *pst;
SpId           spId;
RguDStaRspInfo *staRsp;
#endif
{
   TRC2(RgUiRguDStaRsp);
 
   CMXTA_DBG_PARAM((_cmxtap, "RgUiRguDStaRsp():\n"));

   pst->event = KWAC_RGU_EVT_DSTA_RSP;
 
   kwAcRguSendMsg(pst, 0, spId, 0, staRsp);    

   RETVALUE(ROK);
} /* End of RgUiRguDStaRsp */


/**
 * @brief XTA Common Channel Data Request for RGU interface.
 *
 * @details
 *
 *     Function : RgUiRguCDatReq
 *     
 *     Enqueues the CDatReq received from RLC to XTA queue. 
 *     
 *  @param[in]  *pst 
 *  @param[in]  spId 
 *  @param[in]  *datReq 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 RgUiRguCDatReq
(
Pst            *pst,
SpId           spId,
RguCDatReqInfo *datReq
)
#else
PUBLIC S16 RgUiRguCDatReq(pst, spId, datReq)
Pst            *pst;
SpId           spId;
RguCDatReqInfo *datReq;
#endif
{
   TRC2(RgUiRguCDatReq);
 
   CMXTA_DBG_PARAM((_cmxtap, "RgUiRguCDatReq():\n"));

   pst->event = KWAC_RGU_EVT_CDAT_REQ;
 
   kwAcRguSendMsg(pst, 0, spId, 0, datReq);    

   RETVALUE(ROK);
} /* End of RgUiRguCDatReq */


/**
 * @brief XTA Dedicated Channel Data Request for RGU interface.
 *
 * @details
 *
 *     Function : RgUiRguDDatReq
 *     
 *     Enqueues the DDatReq received from RLC to XTA queue. 
 *     
 *  @param[in]  *pst 
 *  @param[in]  spId 
 *  @param[in]  *datReq 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 RgUiRguDDatReq
(
Pst            *pst,
SpId           spId,
RguDDatReqInfo *datReq
)
#else
PUBLIC S16 RgUiRguDDatReq(pst, spId, datReq)
Pst            *pst;
SpId           spId;
RguDDatReqInfo *datReq;
#endif
{

   TRC2(RgUiRguDDatReq);
 
   CMXTA_DBG_PARAM((_cmxtap, "RgUiRguDDatReq():\n"));

   pst->event = KWAC_RGU_EVT_DDAT_REQ;
 
   kwAcRguSendMsg(pst, 0, spId, 0, datReq);    

   RETVALUE(ROK);
} /* End of RgUiRguDDatReq */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9

/**
 * @brief XTA  L2 Measurement UL IP Throughput meas req in RGU interface.
 *
 * @details
 *
 *     Function : RgUiRguL2MUlThrpMeasReq 
 *     
 *     Enqueues the L2MeasReq for ULIP Throughput  received from RLC to XTA queue.
 *     
 *  @param[in]  *pst 
 *  @param[in]  spId 
 *  @param[in]  *l2mUlThrpMeasReq
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 RgUiRguL2MUlThrpMeasReq
(
Pst            *pst,
SpId           spId,
RguL2MUlThrpMeasReqInfo *l2mUlThrpMeasReq
)
#else
PUBLIC S16 RgUiRguL2MUlThrpMeasReq (pst, spId, l2mUlThrpMeasReq)
Pst            *pst;
SpId           spId;
RguL2MUlThrpMeasReqInfo *l2mUlThrpMeasReq;
#endif
{

   TRC2(RgUiRguL2MUlThrpMeasReq);
 
   CMXTA_DBG_PARAM((_cmxtap, "RgUiRguL2MUlThrpMeasReq():\n"));

   pst->event = KWAC_RGU_EVT_L2MULTHR_REQ;
 
   kwAcRguSendMsg(pst, 0, spId, 0, l2mUlThrpMeasReq);    

   RETVALUE(ROK);
} /* End of RgUiRguL2MUlThrpMeasReq */
#endif
#endif

/**********************************************************************
 
         End of file:     kwac_rgucb.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:41 2014
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm        1. Initial Release.
/main/2      ---     gk        1. LTE RLC Release 2.1.
/main/3   kw005.201  ap        1. Added support for L2 Measurement.
*********************************************************************91*/

