

/********************************************************************20**

     Name:    MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source

     File:    rgac_crgcb.c

     Sid:      rgac_crgcb.c@@/main/2 - Sat Jul 30 02:20:51 2011

     Prg:     ns 
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
#include "rgr.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_crg.h"
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
#include "rgr.x"           /* RGR Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"
#include "rgac_crg.x"        /* MAC error defines */


/*
*
*       Fun:   NhLiCrgBndCfm
*       
*       Desc:  Call handler for Bind Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_crgcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 NhLiCrgBndCfm
(
Pst            *pst,
SuId           suId,
U8             status
)
#else
PUBLIC S16 NhLiCrgBndCfm(pst, suId, status)
Pst            *pst;
SuId           suId;
U8             status;
#endif
{
   TRC2(NhLiCrgBndCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCrgBndCfm():\n"));

   pst->event = RGAC_CRG_EVTBNDCFM;
 
   rgAcCrgSendMsg(pst, suId, status, NULLP);    

   RETVALUE(ROK);
} /* End of NhLiCrgBndCfm*/
/*
*
*       Fun:   NhLiCrgCfgCfm
*       
*       Desc:  Call handler for Config Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  rgac_crgcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 NhLiCrgCfgCfm
(
Pst                  *pst,
SuId                 suId,
CrgCfgTransId        transId,
U8                   status
)
#else
PUBLIC S16 NhLiCrgCfgCfm(pst, suId, transId, status)
Pst            *pst;
SuId           suId;
CrgCfgTransId  transId;
U8             status;
#endif
{
   TRC2(NhLiCrgCfgCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCrgCfgCfm():\n"));

   pst->event = RGAC_CRG_EVTCFGCFM;
 
   rgAcCrgSendMsg(pst, suId, status, NULLP);    

   RETVALUE(ROK);
} /* End of NhLiCrgCfgCfm*/


/*
*
*       Fun:   rgAcCrgSendMsg 
*
*       Desc:  Call handler for Saving Message
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  rgac_crgcb.c
*
*/
#ifdef ANSI
PUBLIC S16 rgAcCrgSendMsg
(
Pst            *pst,
SpId           suId,
U8             reason,
Void           *ptr
)
#else
PUBLIC S16 rgAcCrgSendMsg(pst, suId, reason, ptr)
Pst            *pst;
SpId           suId;
U8             reason;
Void           *ptr;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   RgAccMsgQElm *rgMsg;
   RgAcCrgInfo  *crgInfo;
   S16 ret = ROK;
 
   TRC2(rgAcCrgSendMsg);
 
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the asmgciated test case */
   if ((tcCb = (CmXtaTCCb *)rgAcCrgTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped RGAC_ENHANCE: may be Sts Ind etc...\n"));
      RETVALUE(ROK);
   }

   rgMsg = NULLP;
   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcCrgSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)rgMsg;
   qElm.msgFreeFun = rgAcUtlFreeCrgCb;
   crgInfo = &(rgMsg->u.crgInfo);

   /*** fill the suId in the Q element****/
   crgInfo->suId = suId;

   switch (pst->event) 
   {
      case RGAC_CRG_EVTBNDCFM:
      {
         crgInfo->status = reason;
         break;
      }
      case RGAC_CRG_EVTCFGCFM:
      {
         crgInfo->status = reason;
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
} /* end of rgAcCrgSendMsg() */


/*
*
*       Fun:   rgAcCrgTstCbFind
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  rgac_crgcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  rgAcCrgTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  rgAcCrgTstCbFind ()
#endif
{
   TRC2(rgAcCrgTstCbFind);
 
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
} /* End of rgAcCrgTstCbFind */

/**
 * @brief XTA Function to free resources aquired by the interface messages
 * received from MAC to Dummy-RRC.
 *
 * @details
 *
 *     Function : rgAcUtlFreeCrgCb
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
PUBLIC S16 rgAcUtlFreeCrgCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 rgAcUtlFreeCrgCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   RgAccMsgQElm *rgMsg;
   RgAcCrgInfo  *crgInfo = NULLP; 
 
   TRC2(rgAcUtlFreeCrgCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "rgAcUtlFreeCrgCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   rgMsg = (RgAccMsgQElm *)qElm->data;
  
   if(rgMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   crgInfo = &(rgMsg->u.crgInfo);
   
   if (rgMsg != NULLP)
   {
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of rgAcUtlFreeCrgCb() */




/********************************************************************30**

         End of file:     rgac_crgcb.c@@/main/2 - Sat Jul 30 02:20:51 2011

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
           rg003.201 ns  1. Trace added for function.
/main/2      ---   asehgal 1. Updated for LTE MAC Release 3.1
$SID$        ---     rt    1. LTE MAC 4.1 release
*********************************************************************91*/
