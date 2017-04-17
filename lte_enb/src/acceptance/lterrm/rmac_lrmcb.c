

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_rmucb.c 

     Sid:      rmac_lrmcb.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:25 2013

     Prg:      sck

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

//#include "ckw.h"            /* C-RLC interface */
//#include "kwu.h"            /* D-RLC interface */
//#include "crg.h"            /* C-MAC interface */
//#include "cpj.h"            /* C-PDCP interface */
//#include "pju.h"            /* D-PDCP interface */
//#include "nhu.h"           /* RRC Upper Interface */
//#include "nh.h"
//#include "lnh.h"

#include "cm_xta.h"
#include "rmac_acc.h"
#include "cm_pasn.h"
#include "rm.h"
#include "lrm.h"
#include "rmu.h"
#include "rmac_acc.h"
//#include "rmac_lrm.h"
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
#if 0
//#include "ckw.x"            /* C-RLC interface */
//#include "kwu.x"            /* D-RLC interface */
//#include "crg.x"            /* C-MAC interface */
//#include "cpj.x"            /* C-PDCP interface */
//#include "pju.x"            /* D-PDCP interface */
//#include "nhu.x"           /* RRC Upper Interface */
//#include "nhu_asn.x"
//#include "lnh.x"
//#include "nh.x"
#endif
#include "cm_pasn.x"
#include "lrm.x"
#include "rmu.x"
#include "rmac_acc.x"
#include "rmac_lrm.x"

/* Following functions are implemented

DmLrmGenCfgCfm
DmLrmUpSapCfgCfm
DmLrmCellCfgCfm
DmLrmEnbCfgCfm

*/

/*
*
*       Fun:   rmAcLrmTstCbFind
*
*       Desc:  Call handler for finding the Test Case Control Block
*
*       Ret:   Test Case Control Block
*
*       Notes: None
*              
*       File:  rmac_lrmcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  rmAcLrmTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  rmAcLrmTstCbFind ()
#endif
{
   TRC2(rmAcLrmTstCbFind)

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
} /* rmAcLrmTstCbFind */



/*
*
*       Fun:   rmAcLrmSaveMsg
*
*       Desc:  Function to push the message on queue 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rmac_rmucb.c
*
*/

#ifdef ANSI
PRIVATE S16 rmAcLrmSaveMsg
(
Pst  *pst,
SpId spId,
void *lrmInfo
)
#else
PRIVATE S16 rmAcLrmSaveMsg(pst, spId, lrmInfo)
Pst  *pst;
SpId spId;
void *lrmInfo;
#endif 
{
   CmXtaTCCb    *tcCb = NULLP;
   RmAccMsgQElm *lrmMsg = NULLP; 
   CmXtaMsgQElm   qElm;
/* S16            ret;
   Mem            mem;*/
   RmMngmt    *resp;	

   TRC3(rmAcLrmSaveMsg);

   cmMemset( (U8* )&qElm, 0, sizeof(CmXtaMsgQElm));

   /*-- Allocate memory data --*/
   CMXTA_ALLOC(&lrmMsg, sizeof (RmAccMsgQElm));

   if (lrmMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcLrmSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   CMXTA_ALLOC(&resp, sizeof(RmMngmt));
   
   if(resp == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcLrmSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }	

 // (Void) cmMemcpy((U8 *)resp, (U8 *)lrmInfo, sizeof(RmMngmt)); 
	*resp = *((RmMngmt *)lrmInfo);

   switch (pst->event)
   {
      case EVTLRMCFGCFM:
         lrmMsg->u.lrmInfo.len = sizeof(RmMngmt);
	 lrmMsg->u.lrmInfo.data = (Void *)resp;	
         break;

      case EVTLRMCNTRLCFM:
          lrmMsg->u.lrmInfo.len = sizeof(RmMngmt);
          lrmMsg->u.lrmInfo.data = (Void *)resp;
          break;

	  default:
         CMXTA_DBG_INFO((_cmxtap, "rmAcLrmSaveMsg(): Unhandled event\n"));
         RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Usual mode --*/
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Fill the message in the queue structure --*/
   CMXTA_CPY((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   if ((tcCb = (CmXtaTCCb*)rmAcLrmTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "rmAcLrmSaveMsg(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   qElm.data = (Void *)lrmMsg;
   qElm.msgFreeFun = rmAcUtlLrmFreeCb;
   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ,(CmXtaMsgQElm *) &qElm);

   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   /* MEM LEAK FIX */
   if(pst->selector == LRM_SEL_LWLC)
	{
		//free the memory of response
		SPutSBuf(pst->region, pst->pool, (Data *)resp, sizeof(RmMngmt));
	}

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rmAcLrmSaveMsg() */


/*
*
*       Fun:   DmLrmCfgCfm - LRM Config Confirm 
*
*       Desc:  This function is used to present LRM Config Confirm.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_lrmcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLrmCfgCfm
(
Pst             *pst,          
RmMngmt			*cfgCfmInfo           
)
#else
PUBLIC S16 SmMiLrmCfgCfm (pst, cfgCfmInfo)
Pst             *pst;          /* post structure */
RmMngmt			*cfgCfmInfo;
#endif
{
   TRC2(SmMiLrmCfgCfm);

   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrmCfgCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTLRMCFGCFM;

   rmAcLrmSaveMsg(pst, 0, (Void*)cfgCfmInfo);

   if(pst->selector == LRM_SEL_LWLC)	
	{
		//free the memory of cfgCfmInfo
		// SPutSBuf(pst->region, pst->pool, (Data *)cfgCfmInfo, sizeof(RmMngmt));
	}
   
   RETVALUE(ROK);
} /* end of DmLrmCfgCfm */


/*
*
*       Fun:   SmMiLrmCntrlCfm - LRM Control Confirm 
*
*       Desc:  This function is used to present LRM Config Confirm.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_lrmcb.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLrmCntrlCfm
(
Pst             *pst,          
RmMngmt			*cfgCfmInfo           
)
#else
PUBLIC S16 SmMiLrmCfgCfm (pst, cfgCfmInfo)
Pst             *pst;          /* post structure */
RmMngmt			*cfgCfmInfo;
#endif
{
   TRC2(SmMiLrmCntrlCfm);

   CMXTA_DBG_PARAM((_cmxtap, "SmMiLrmCntrlCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTLRMCNTRLCFM;

   rmAcLrmSaveMsg(pst, 0, (Void*)cfgCfmInfo);

   if(pst->selector == LRM_SEL_LWLC)	
	{
		//free the memory of cfgCfmInfo
		SPutSBuf(pst->region, pst->pool, (Data *)cfgCfmInfo, sizeof(RmMngmt));
	}
   
   RETVALUE(ROK);
} /* end of SmMiLrmCntrlCfm*/

/*
*
*       Fun:   DmLrmGenCfgCfm - LRM Generic Config Confirm 
*
*       Desc:  This function is used to present LRM Generic Config Confirm.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_lrmcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmLrmGenCfgCfm
(
Pst             *pst,          
RmMngmt			*genCfgCfmInfo           
)
#else
PUBLIC S16 DmLrmGenCfgCfm (pst,genCfgCfmInfo)
Pst             *pst;          /* post structure */
RmMngmt			*genCfgCfmInfo;
#endif
{
   TRC2(DmLrmGenCfgCfm);

   CMXTA_DBG_PARAM((_cmxtap, "DmLrmGenCfgCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTLRMCFGCFM;

   rmAcLrmSaveMsg(pst, 0, (Void*)genCfgCfmInfo);
   RETVALUE(ROK);
} /* end of DmLrmGenCfgCfm */


/*
*
*       Fun:   DmLrmUpSapCfgCfm - LRM UpSap Config Confirm 
*
*       Desc:  This function is used to present LRM UpSap Config Confirm.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_lrmcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmLrmUpSapCfgCfm
(
Pst             *pst,          
RmMngmt			*usapCfgCfmInfo           
)
#else
PUBLIC S16 DmLrmUpSapCfgCfm (pst,usapCfgCfmInfo)
Pst             *pst;          /* post structure */
RmMngmt			*usapCfgCfmInfo;
#endif
{
   TRC2(DmLrmGenCfgCfm);

   CMXTA_DBG_PARAM((_cmxtap, "DmLrmUpSapCfgCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTLRMCFGCFM;

   rmAcLrmSaveMsg(pst, 0, (Void*)usapCfgCfmInfo);
   RETVALUE(ROK);
} /* end of DmLrmUpSapCfgCfm */


/*
*
*       Fun:   DmLrmCellCfgCfm - LRM Cell Config Confirm 
*
*       Desc:  This function is used to present LRM Cell Config Confirm.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_lrmcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmLrmCellCfgCfm
(
Pst             *pst,          
RmMngmt			*cellCfgCfmInfo           
)
#else
PUBLIC S16 DmLrmCellCfgCfm (pst,cellCfgCfmInfo)
Pst             *pst;          /* post structure */
RmMngmt			*cellCfgCfmInfo;
#endif
{
   TRC2(DmLrmGenCfgCfm);

   CMXTA_DBG_PARAM((_cmxtap, "DmLrmCellCfgCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTLRMCFGCFM;

   rmAcLrmSaveMsg(pst, 0, (Void*)cellCfgCfmInfo);
   RETVALUE(ROK);
} /* end of DmLrmCellCfgCfm */

/*
*
*       Fun:   DmLrmEnbCfgCfm - LRM eNB Config Confirm 
*
*       Desc:  This function is used to present LRM eNB Config Confirm.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_lrmcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmLrmEnbCfgCfm
(
Pst             *pst,          
RmMngmt			*enbCfgCfmInfo           
)
#else
PUBLIC S16 DmLrmEnbCfgCfm (pst,enbCfgCfmInfo)
Pst             *pst;          /* post structure */
RmMngmt			*enbCfgCfmInfo;
#endif
{
   TRC2(DmLrmGenCfgCfm);

   CMXTA_DBG_PARAM((_cmxtap, "DmLrmEnbCfgCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTLRMCFGCFM;

   rmAcLrmSaveMsg(pst, 0, (Void*)enbCfgCfmInfo);
   RETVALUE(ROK);
} /* end of DmLrmEnbCfgCfm */

