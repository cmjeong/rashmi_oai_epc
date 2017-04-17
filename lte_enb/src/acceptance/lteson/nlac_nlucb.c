

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     nlac_nlucb.c 

     Sid:      nlac_nlucb.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:05:02 2014

     Prg:      subhamay 

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "cm_xta.h"
//#include "wrac_acc.h"
#include "cm_pasn.h"
#include "nl.h"
#include "nlu.h"
#include "lnl.h"
#include "nlac_acc.h"
/* external headers */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
#include "cm_pasn.x"
#include "lnl.x"
#include "nlu.x"
#include "nlac_acc.x"
#include "nlac_nlu.x"

/* Following functions are implemented


*/

/*
*
*       Fun:   nlAcNluTstCbFind
*
*       Desc:  Call handler for finding the Test Case Control Block
*
*       Ret:   Test Case Control Block
*
*       Notes: None
*              
*       File:  nlac_nlucb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  nlAcNluTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  nlAcNluTstCbFind ()
#endif
{
   TRC2(nlAcNluTstCbFind);

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
} /* nlAcNluTstCbFind */



/*
*
*       Fun:   nlAcNluSaveMsg
*
*       Desc:  Function to push the message on queue 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nlac_nlucb.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcNluSaveMsg
(
Pst  *pst,
SuId suId,
SpId spId,
void *nluInfo
)
#else
PRIVATE S16 nlAcNluSaveMsg(pst, spId, suId, lnlInfo)
Pst  *pst;
SuId suId;
SpId spId;
void *nluInfo;
#endif 
{
   CmXtaTCCb    *tcCb = NULLP;
   NlAccMsgQElm *nluMsg = NULLP; 
   CmXtaMsgQElm   qElm;
   S16            ret;
   Mem            mem;

   TRC3(nlAcNluSaveMsg);

   cmMemset( (U8* )&qElm, 0, sizeof(CmXtaMsgQElm));

   CMXTA_DBG_PARAM((_cmxtap, "nlAcNluSaveMsg(): suId (%d))", suId));

   /*-- Allocate memory data --*/
   CMXTA_ALLOC(&nluMsg, sizeof (NlAccMsgQElm));
   if (nluMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "nlAcNluSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   nluMsg->u.nluInfo.suId = suId;
   nluMsg->u.nluInfo.data = nluInfo;

   switch (pst->event)
   {
      case EVTNLUBNDCFM :
      {
         nluMsg->u.nluInfo.len = sizeof(NlMngmt);
      }
      break;
      default:
      {


      }
      break;
#if 0
      case EVTRMUUEADMITRSP:
			rmuMsg->u.rmuInfo.len = sizeof(RmuUeAdmitRsp);
         break;

	 default:
         CMXTA_DBG_INFO((_cmxtap, "rmAcRmuSaveMsg(): Unhandled event\n"));
         RETVALUE(CMXTA_ERR_NONE);
#endif
   }

   /*-- Usual mode --*/
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Fill the message in the queue structure --*/
   CMXTA_CPY((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   if ((tcCb = (CmXtaTCCb*)nlAcNluTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "nlAcNluSaveMsg(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   qElm.data = (Void *)nluMsg;
   qElm.msgFreeFun = nlAcUtlNluFreeCb;
   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ,(CmXtaMsgQElm *) &qElm);

   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of nlAcNluSaveMsg() */


#ifdef ANSI
PUBLIC S16 WrLiNluBndCfm
(
Pst             *pst,
SuId            suId,
SpId            spId,
U8              status
)
#else
PUBLIC S16 WrLiNluBndCfm(pst, suId, spId, status)
Pst             *pst;          /* post structure */
SuId            suId;
SpId            spId;
U8              status;
#endif
{
   TRC2(WrLiNluBndCfm);

   CMXTA_DBG_PARAM((_cmxtap, "WrLiNluBndCfm():\n"));
   NlMngmt         *bndCfm = NULLP;
   CMXTA_ALLOC(&bndCfm, sizeof(NlMngmt));

   if(bndCfm == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"WrLiNluBndCfm(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
     
   bndCfm->cfm.status = (status -1);
   bndCfm->cfm.reason = LCM_REASON_NOT_APPL; 
   /*-- Update Event --*/
   pst->event = EVTNLUBNDCFM;

   nlAcNluSaveMsg(pst, suId, 0, bndCfm);

   RETVALUE(ROK);
}


