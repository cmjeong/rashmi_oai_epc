
/********************************************************************20**

     Name:    MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source

     File:    rgac_rgmcb.c

     Sid:      rgac_rgmcb.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Thu May 23 19:17:22 2013

     Prg:     nsadar 
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_lte.h"        /* Common LTE Defines */
#include "cm_xta.h"        /* Common LTE Defines */
#include "rg_env.h"        /* MAC Environment Defines */
#include "crg.h"           /* CRG Interface defines */
#include "rgm.h"           /* RGM Interface defines */
#include "rgm.h"           /* RGM Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_rgm.h"
#include "rgac_acc.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_xta.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */
#include "rgm.x"           /* RGM Interface includes */
#include "rgm.x"           /* RGM Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"
#include "rgac_rgm.x"        /* MAC error defines */

/*
*
*       Fun:   rgAcRgmTstCbFind
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  rgac_rgmcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  rgAcRgmTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  rgAcRgmTstCbFind ()
#endif
{
   TRC2(rgAcRgmTstCbFind);
 
   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change SOAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif
 
   RETVALUE(NULLP);
} /* End of rgAcRgmTstCbFind */

/**
 * @brief XTA Function to free resources aquired by the interface messages
 * received from MAC to RRM Layer.
 *
 * @details
 *
 *     Function : rgAcUtlFreeRgmCb
 *     
 *     A pointer to this function is registered with each 
 *     Queue element that gets enqueued as part of its call
 *     handler functionality. After the interface primitive 
 *     validation is done by the validation handler, the queue
 *     element is flushed, this function gets invoked as part
 *     of this flushing. Based on type of primitive, the memory
 *     freeing takes place.
 *     
 *  @param[in]  *qElm 
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/

#ifdef ANSI
PUBLIC S16 rgAcUtlFreeRgmCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 rgAcUtlFreeRgmCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   RgAccMsgQElm *rgMsg;
   RgAcRgmInfo  *rgmInfo = NULLP; 
 
   TRC2(rgAcUtlFreeRgmCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "rgAcUtlFreeRgmCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   rgMsg = (RgAccMsgQElm *)qElm->data;
  
   if(rgMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   rgmInfo = &(rgMsg->u.rgmInfo);

   /* Anshika: ccpu00134393 */
   switch (rgmInfo->event) 
   {
      case RGAC_RGM_EVTBNDCFM:
      {
         break;
      }

      case RGAC_RGM_EVTCFGPRBREPRTIND:
      {
         SPutSBuf(0, 0, (Data *)(rgmInfo->u.prbRprtInd),sizeof(RgmPrbRprtInd));
         break;
      }
      default:
         RETVALUE(CMXTA_ERR_INT);
   }/* end of switch */

   if (rgMsg != NULLP)
   {
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of rgAcUtlFreeRgmCb() */




/*
*
*       Fun:   rgAcRgmSendMsg 
*
*       Desc:  Call handler for Saving Message
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  rgac_rgmcb.c
*
*/
#ifdef ANSI
PUBLIC S16 rgAcRgmSendMsg
(
Pst            *pst,
SpId           suId,
U8             reason,
Void           *ptr
)
#else
PUBLIC S16 rgAcRgmSendMsg(pst, suId, reason, ptr)
Pst            *pst;
SpId           suId;
U8             reason;
Void           *ptr;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   RgAccMsgQElm *rgMsg;
   RgAcRgmInfo  *rgmInfo;
   S16 ret = ROK;
 
   TRC3(rgAcRgmSendMsg);
 
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the asmgciated test case */
   if ((tcCb = (CmXtaTCCb *)rgAcRgmTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped RGAC_ENHANCE: may be Sts Ind etc...\n"));
      RETVALUE(ROK);
   }

   rgMsg = NULLP;
   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcRgmSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)rgMsg;
   qElm.msgFreeFun = rgAcUtlFreeRgmCb;
   rgmInfo = &(rgMsg->u.rgmInfo);

   /*** fill the suId in the Q element****/
   rgmInfo->suId = suId;

   switch (pst->event) 
   {
      case RGAC_RGM_EVTBNDCFM:
      {
         rgmInfo->status = reason; 
         break;
      }

      case RGAC_RGM_EVTCFGPRBREPRTIND:
      {
         /* ccpu00134393 */
   
         rgmInfo->u.prbRprtInd = (RgmPrbRprtInd *)ptr;
         rgmInfo->event = pst->event;

         break;
      }
      default:
         ret = RFAILED;
   }/* end fo switch */

   if( ret == ROK)
   {
      /*-- Test case found, queue the message for the tcCb --*/
      /* Push it onto the message queue --*/
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
 
      /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will RGAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   } 
   else
   {
      CMXTA_FREE(rgMsg, sizeof(RgAccMsgQElm));
   }
 
   RETVALUE(ret);
} /* end of rgAcRgmSendMsg() */



/*
*
*       Fun:   RmLiRgmBndCfm
*       
*       Desc:  Call handler for Bind Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_rgmcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RmLiRgmBndCfm
(
Pst            *pst,
SuId           suId,
U8             status
)
#else
PUBLIC S16 RmLiRgmBndCfm(pst, suId, status)
Pst            *pst;
SuId           suId;
U8             status;
#endif
{
   TRC2(RmLiRgmBndCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "RmLiRgmBndCfm():\n"));

   pst->event = RGAC_RGM_EVTBNDCFM;
 
   rgAcRgmSendMsg(pst, suId, status, NULLP);    

   RETVALUE(ROK);
} /* End of RmLiRgmBndCfm */

 
/*
*
*       Fun:   RmLiRgmPrbRprtInd
*       
*       Desc:  Call handler for Report Indiaction
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_rgmcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RmLiRgmPrbRprtInd
(
Pst            *pst,
SuId           suId,
RgmPrbRprtInd  *prbRprtInd
)
#else
PUBLIC S16 RmLiRgmPrbRprtInd(pst, suId, prbRprtInd)
Pst            *pst;
SuId           suId;
RgmPrbRprtInd  *prbRprtInd
#endif
{
   TRC2(RmLiRgmPrbRprtInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "RmLiRgmPrbRprtInd():\n"));

   pst->event = RGAC_RGM_EVTCFGPRBREPRTIND;
 
   /* ccpu00134393 */
   rgAcRgmSendMsg(pst, suId, NULLP, prbRprtInd);    
   RETVALUE(ROK);
} /* End of RmLiRgmBndCfm */       

/*
*
*       Fun:   RmLiRgmTransModeInd
*       
*       Desc:  Call handler for Report Indiaction
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_rgmcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RmLiRgmTransModeInd
(
Pst               *pst,
SuId              suId,
RgmTransModeInd   *txModeChgInd
)
#else
PUBLIC S16 RmLiRgmTransModeInd(pst, suId, txModeChgInd)
Pst               *pst;
SuId              suId;
RgmTransModeInd   *txModeChgInd
#endif
{
   TRC2(RmLiRgmTransModeInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "RmLiRgmTransModeInd():\n"));

   pst->event = RGAC_RGM_EVTCFGTRANSMODEIND;
 
   /* ccpu00134393 */
   rgAcRgmSendMsg(pst, suId, NULLP, txModeChgInd);    
   RETVALUE(ROK);
} 
/********************************************************************30**

         End of file:     rgac_rgmcb.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Thu May 23 19:17:22 2013

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
/main/1      ---     ns  1. Initial Release.
            rg001.201 sm 1. Added TTI indication towards RGM user.
            rg004.201 rnt 1. Modified for SI Enhancement
/main/2      ---        dvasisht          1. Updated for LTE MAC Release 3.1
*********************************************************************91*/
