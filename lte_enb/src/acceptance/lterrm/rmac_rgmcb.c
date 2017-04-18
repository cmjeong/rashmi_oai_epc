

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_rmucb.c 

     Sid:      rmac_rgmcb.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:27 2013

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
#include "rgm.h"
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
#include "rgm.x"
#include "rmac_acc.x"
#include "rmac_lrm.x"
#include "rmac_rgm.x"

/* Following functions are implemented

DmRgmGenCfgCfm
DmRgmUpSapCfgCfm
DmRgmCellCfgCfm
DmRgmEnbCfgCfm

*/
#ifdef RRM_UNUSED_FUNC
/*
*
*       Fun:   rmAcRgmTstCbFind
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
PUBLIC CmXtaTCCb*  rmAcRgmTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  rmAcRgmTstCbFind ()
#endif
{
   TRC2(rmAcRgmTstCbFind)

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
} /* rmAcRgmTstCbFind */



/*
*
*       Fun:   rmAcRgmSaveMsg
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
PRIVATE S16 rmAcRgmSaveMsg
(
Pst  *pst,
SuId suId,
SpId spId,
void *rgmInfo
)
#else
PRIVATE S16 rmAcRgmSaveMsg(pst, suId, spId, rgmInfo)
Pst  *pst;
SuId suId;
SpId spId;
void *rgmInfo;
#endif 
{
   CmXtaTCCb    *tcCb = NULLP;
   RmAccMsgQElm *rgmMsg = NULLP; 
   CmXtaMsgQElm   qElm;
   S16            ret;
   Mem            mem;
   RmMngmt    *resp;	

   TRC3(rmAcRgmSaveMsg);

   cmMemset( (U8* )&qElm, 0, sizeof(CmXtaMsgQElm));

   /*-- Allocate memory data --*/
   CMXTA_ALLOC(&rgmMsg, sizeof (RmAccMsgQElm));

   if (rgmMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcRgmSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   CMXTA_ALLOC(&resp, sizeof(RmMngmt));
   
   if(resp == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcRgmSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }	

 // (Void) cmMemcpy((U8 *)resp, (U8 *)lrmInfo, sizeof(RmMngmt)); 
 
   if(rgmInfo)
   	*resp = *((RmMngmt *)rgmInfo);

   switch (pst->event)
   {
      case EVTRGMBNDREQ:
         rgmMsg->u.rgmInfo.len = sizeof(RmMngmt);
	      rgmMsg->u.rgmInfo.data = (Void *)resp;	
         break;

      case EVTRGMCFGPRBRPRT:
         rgmMsg->u.rgmInfo.len = sizeof(RgmPrbRprtCfg);
	      rgmMsg->u.rgmInfo.data = (Void *)resp;	
         break;

	  default:
         CMXTA_DBG_INFO((_cmxtap, "rmAcRgmSaveMsg(): Unhandled event\n"));
         RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Usual mode --*/
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Fill the message in the queue structure --*/
   CMXTA_CPY((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   if ((tcCb = (CmXtaTCCb*)rmAcRgmTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "rmAcRgmSaveMsg(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   qElm.data = (Void *)rgmMsg;
   qElm.msgFreeFun = rmAcUtlRgmFreeCb;
   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ,(CmXtaMsgQElm *) &qElm);

   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rmAcRgmSaveMsg() */


/*
*
*       Fun:   RgUiRgmBndReq - RGM Bind Confirm 
*
*       Desc:  This function is used to present RGM Bind Confirm.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_rgmcb.c
*
*/


#ifdef ANSI
PUBLIC S16 RgUiRgmBndReq
(
Pst             *pst,          
SuId            suId,
SpId            spId
)
#else
PUBLIC S16 RgUiRgmBndReq (pst, suId, spId)
Pst             *pst;          /* post structure */
SuId            suId;
SpId            spId;
#endif
{
   TRC2(RgUiRgmBndReq);

   CMXTA_DBG_PARAM((_cmxtap, "RgUiRgmBndReq():\n"));

   /*-- Update Event --*/
   pst->event = EVTRGMBNDREQ;

   rmAcRgmSaveMsg(pst, suId, spId, (Void*)NULL);

   if(pst->selector == LRM_SEL_LWLC)	
	{
		//free the memory of cfgCfmInfo
		// SPutSBuf(pst->region, pst->pool, (Data *)cfgCfmInfo, sizeof(RmMngmt));
	}
   
   RETVALUE(ROK);
} /* end of RgUiRgmBndReq */


/*
*
*       Fun:   RgUiRgmCfgPrbRprt - RGM Prb cfg report
*
*       Desc:  This function is used to present RGM Prb cfg report.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_rgmcb.c
*
*/


#ifdef ANSI
PUBLIC S16 RgUiRgmCfgPrbRprt
(
Pst             *pst,          
SuId            suId,
RgmPrbRprtCfg   *prbRprtCfg
)
#else
PUBLIC S16 RgUiRgmCfgPrbRprt (pst, suId, *prbRprtCfg)
Pst             *pst;          /* post structure */
SuId            suId;
RgmPrbRprtCfg   *prbRprtCfg;
#endif
{
   TRC2(RgUiRgmCfgPrbRprt);

   CMXTA_DBG_PARAM((_cmxtap, "RgUiRgmCfgPrbRprt():\n"));

   /*-- Update Event --*/
   pst->event = EVTRGMCFGPRBRPRT;

   rmAcRgmSaveMsg(pst, suId, 0, (Void*)prbRprtCfg);

   if(pst->selector == LRM_SEL_LWLC)	
	{
		//free the memory of cfgCfmInfo
		// SPutSBuf(pst->region, pst->pool, (Data *)cfgCfmInfo, sizeof(RmMngmt));
	}
   
   RETVALUE(ROK);
} /* end of RgUiRgmCfgPrbRprt*/
#endif
