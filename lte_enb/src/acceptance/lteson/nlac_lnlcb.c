

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     nlac_lnlcb.c 

     Sid:      nlac_lnlcb.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:04:04 2014

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
#include "nlac_acc.h"
#include "cm_pasn.h"
#include "nl.h"
#include "lnl.h"
#include "nlu.h"
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
#include "nlac_lnl.x"

/* Following functions are implemented

DmLrmGenCfgCfm
DmLrmUpSapCfgCfm

*/

/*
*
*       Fun:   nlAcLnlTstCbFind
*
*       Desc:  Call handler for finding the Test Case Control Block
*
*       Ret:   Test Case Control Block
*
*       Notes: None
*              
*       File:  nlac_lnlcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  nlAcLnlTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  nlAcLnlTstCbFind ()
#endif
{
   TRC2(nlAcLnlTstCbFind)

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
} /* nlAcLnlTstCbFind */



/*
*
*       Fun:   nlAcLnlSaveMsg
*
*       Desc:  Function to push the message on queue 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nlac_lnlcb.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcLnlSaveMsg
(
Pst  *pst,
SpId spId,
void *lnlInfo
)
#else
PRIVATE S16 nlAcLnlSaveMsg(pst, spId, lnlInfo)
Pst  *pst;
SpId spId;
void *lnlInfo;
#endif 
{
   CmXtaTCCb        *tcCb = NULLP;
   NlAccMsgQElm     *lnlMsg = NULLP; 
   CmXtaMsgQElm     qElm;
   NlMngmt          *resp = NULLP;	
   NlCfgUpdateInd   *cfgUpdateInd = NULLP;
   TRC3(nlAcLnlSaveMsg);

   cmMemset( (U8* )&qElm, 0, sizeof(CmXtaMsgQElm));

   /*-- Allocate memory data --*/
   CMXTA_ALLOC(&lnlMsg, sizeof (NlAccMsgQElm));

   if (lnlMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "nlAcLnlSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   switch (pst->event)
   {
      case EVTLNLCFGCFM:
      case EVTLNLCNTRLCFM:
      case EVTLNLSTAIND:
         {
            CMXTA_ALLOC(&resp, sizeof(NlMngmt));
            if(resp == NULLP)
            {
               CMXTA_DBG_ERR((_cmxtap, "nlAcLnlSaveMsg(): resource error\n"));
               RETVALUE(CMXTA_ERR_RSRC);
            }
            *resp = *((NlMngmt *)lnlInfo);
            lnlMsg->u.lnlInfo.len = sizeof(NlMngmt);
	    lnlMsg->u.lnlInfo.data = (Void *)resp;
         }	
         break;
      case EVTLNLCFGUPDATEIND:
         {
            CMXTA_ALLOC(&cfgUpdateInd, sizeof(NlCfgUpdateInd));
            if(cfgUpdateInd == NULLP)
            {
               CMXTA_DBG_ERR((_cmxtap, "nlAcLnlSaveMsg(): resource error\n"));
               RETVALUE(CMXTA_ERR_RSRC);
            }
            *cfgUpdateInd = *((NlCfgUpdateInd *)lnlInfo);
            lnlMsg->u.lnlInfo.len = sizeof(NlCfgUpdateInd);
            lnlMsg->u.lnlInfo.data = (Void *)cfgUpdateInd;
         }
         break;
      default:
      CMXTA_DBG_INFO((_cmxtap, "nlAcLnlSaveMsg(): Unhandled event\n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Usual mode --*/
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Fill the message in the queue structure --*/
   CMXTA_CPY((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   if ((tcCb = (CmXtaTCCb*)nlAcLnlTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "nlAcLnlSaveMsg(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   qElm.data = (Void *)lnlMsg;
   qElm.msgFreeFun = nlAcUtlLnlFreeCb;
   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ,(CmXtaMsgQElm *) &qElm);

   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of nlAcLnlSaveMsg() */


/*
*
*       Fun:   SmLnlCfgCfm - LNL Config Confirm 
*
*       Desc:  This function is used to present LNL Config Confirm.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nlac_lnlcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLnlCfgCfm
(
Pst             *pst,          
NlMngmt		*cfgCfmInfo           
)
#else
PUBLIC S16 SmMiLnlCfgCfm (pst, cfgCfmInfo)
Pst             *pst;          /* post structure */
NlMngmt		*cfgCfmInfo;
#endif
{
   TRC2(SmMiLnlCfgCfm);

   CMXTA_DBG_PARAM((_cmxtap, "SmMiLnlCfgCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTLNLCFGCFM;

   nlAcLnlSaveMsg(pst, 0, (Void*)cfgCfmInfo);

   /*free the memory of cfgCfmInfo*/
   SPutSBuf(pst->region, pst->pool, (Data *)cfgCfmInfo, sizeof(NlMngmt));
   
   RETVALUE(ROK);
} /* end of SmLnlCfgCfm */


/*
*
*       Fun:   SmLnlCntrlCfm - LNL Control Confirm 
*
*       Desc:  This function is used to present LNL Control Confirm.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nlac_lnlcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLnlCntrlCfm
(
Pst             *pst,          
NlMngmt		*cntrlCfmInfo           
)
#else
PUBLIC S16 SmMiLnlCntrlCfm (pst, cntrlCfmInfo)
Pst             *pst;          /* post structure */
NlMngmt		*cntrlCfmInfo;
#endif
{
   TRC2(SmMiLnlCntrlCfm);

   CMXTA_DBG_PARAM((_cmxtap, "SmMiLnlCntrlCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTLNLCNTRLCFM;

   nlAcLnlSaveMsg(pst, 0, (Void*)cntrlCfmInfo);

   /*free the memory of cfgCfmInfo*/
   SPutSBuf(pst->region, pst->pool, (Data *)cntrlCfmInfo, sizeof(NlMngmt));
   
   RETVALUE(ROK);
} /* end of SmLnlCntrlCfm */

/*
*
*       Fun:   SmMiLnlCfgUpdateInd - LNL radio pci/EARFCN/PRACH config indication
*
*       Desc:  This function is used to config the PCI/EARFCN/PRACH
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nlac_lnlcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLnlCfgUpdateInd
(
Pst                  *pst,
NlCfgUpdateInd       *cfgUpdateInd
)
#else
PUBLIC S16 SmMiLnlCfgUpdateInd (pst, cfgUpdateInd)
Pst                  *pst;
NlCfgUpdateInd       *cfgUpdateInd;
#endif
{
   TRC2(SmMiLnlCfgUpdateInd);

   CMXTA_DBG_PARAM((_cmxtap, "SmMiLnlCfgUpdateInd():\n"));

   /*-- Update Event --*/
   pst->event = EVTLNLCFGUPDATEIND;

   nlAcLnlSaveMsg(pst, 0, (Void*)cfgUpdateInd);

   /*free the memory of cfgCfmInfo*/
   SPutSBuf(pst->region, pst->pool, (Data *)cfgUpdateInd, sizeof(NlCfgUpdateInd));

   RETVALUE(ROK);
}

/*       Fun:   SmMiLnlStatInd - LNL Status/Alarm indication
*
*       Desc:  This function is used handle alarm
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nlac_lnlcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLnlStatInd
(
Pst                     *pst,
NlMngmt                 *mngmt
)
#else
PUBLIC S16 SmMiLnlStatInd (pst, mngmt)
Pst                     *pst;          /* post structure */
NlMngmt                 *mngmt;
#endif
{
   TRC2(SmMiLnlStatInd);

   CMXTA_DBG_PARAM((_cmxtap, "SmMiLnlStatInd():\n"));

   /*-- Update Event --*/
   pst->event = EVTLNLSTAIND;

   nlAcLnlSaveMsg(pst, 0, (Void*)mngmt);

   /*free the memory of cfgCfmInfo*/
   SPutSBuf(pst->region, pst->pool, (Data *)mngmt, sizeof(NlMngmt));
   RETVALUE(ROK);
}

/*       Fun:   SmMiLnlStatInd - LNL Status/Alarm indication
*
*       Desc:  This function is used handle alarm
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nlac_lnlcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLnlSonCfgInd
(
Pst                     *pst,
LnlSonCfg               *sonCfg
)
#else
PUBLIC S16 SmMiLnlSonCfgInd (pst, sonCfg)
Pst                     *pst;          /* post structure */
LnlSonCfg               *sonCfg;
#endif
{
   TRC2(SmMiLnlSonCfgInd);

   CMXTA_DBG_PARAM((_cmxtap, "SmMiLnlSonCfgInd():\n"));

   /*-- Update Event --*/
   pst->event = EVTLNLSONCFGIND;

   nlAcLnlSaveMsg(pst, 0, (Void*)sonCfg);

   /*free the memory of cfgCfmInfo*/
   SPutSBuf(pst->region, pst->pool, (Data *)sonCfg, sizeof(LnlSonCfg));
   RETVALUE(ROK);
}
