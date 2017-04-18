

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_rmuhdl.c

     Sid:      rmac_rgmhdl.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:27 2013

     Prg:       

*********************************************************************21*/

#include <stdlib.h>        /* for atoi */
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
#include "rmac_acc.h"
#include "rm.h"
#include <stdlib.h>        /* For atoi function */
#include <string.h>        /* for strlen */
#include "rmu.h"
#include "lrm.h"
#include "rgm.h"
#include "rmac_rmu.h"
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
//#include "cm_pasn.x"
#include "lrm.x"
#include "rmu.x"
#include "rgm.x"
#include "rmac_acc.x"
#include "rmac_rgm.x"


#ifdef RRM_UNUSED_FUNC
/*
*
*       Fun:   rmAcHdlRgmPrbRprtInd
*
*       Desc:  Call Handler for RMU MME Overload Start Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRgmPrbRprtInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRgmPrbRprtInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
	SpId          spId;             /* service user SAP identifier */
	Bool          entity;
	S16           error;
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	U8			  cellId = 0;	
	U8			  avgPrbUlUsage = 0;	
	U8			  avgPrbDlUsage = 0;	
	RgmPrbRprtInd* prbInfo;

	TRC2(rmAcHdlRgmPrbRprtInd);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRgmPrbRprtInd(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRgmPrbRprtInd(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;


	/*-- Get the Pst information here from RGM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTRGMPRBRPRTIND;
		
	// Get the param values from XML

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "avgPrbUlUsage",  &(avgPrbUlUsage));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "avgPrbDlUsage",  &(avgPrbDlUsage));


	// Allocate the memory for MmeOvldStartInd msg

	CMXTA_ALLOC(&prbInfo, sizeof(RgmPrbRprtInd));
	
   if(prbInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRgmPrbRprtInd(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into startInfo

   prbInfo->bCellId = cellId;
   prbInfo->bAvgPrbUlUsage = avgPrbUlUsage;
   prbInfo->bAvgPrbDlUsage = avgPrbDlUsage;


	/* Send the indication to the RRM --*/

	if(CMXTA_ERR_NONE != RmLiRgmPrbRprtInd(&pst, suId, prbInfo))
    {
       CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRgmPrbRprtInd(): Mapping returned FAILED\n"));
    }

    RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:  rmAcHdlRgmPrbRprtCfg
*
*       Desc:  Call Handler for RGM Prb Report Cfg
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRgmPrbRprtCfg
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRgmPrbRprtCfg (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RmAccMsgQElm  *rmMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16       retVal = LCM_PRIM_OK;
   U16       reason = LCM_REASON_NOT_APPL;
   RmMngmt		*bndCfm = NULLP;

   TRC2(rmAcHdlRgmPrbRprtCfg);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRgmPrbRprtCfg(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRgmPrbRprtCfg(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlRgmPrbRprtCfg(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rmMsg = (RmAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTRGMCFGPRBRPRT;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);
   rmMsg = (RmAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */
   /*
   bndCfm = (RmMngmt *)(rmMsg->u.rgmInfo.data);

	if(bndCfm->cfm.status != retVal && bndCfm->cfm.reason != reason )
	{
      		CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
                  retVal, bndCfm->cfm.status, reason, bndCfm->cfm.reason), 2);

      		RETVALUE(CMXTA_ERR_INT);
	}
   */
   RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:  rmAcHdlRgmBndReq 
*
*       Desc:  Call Handler for LRM Bind Req
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRgmBndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRgmBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RmAccMsgQElm  *rmMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16       retVal = LCM_PRIM_OK;
   U16       reason = LCM_REASON_NOT_APPL;
   RmMngmt		*bndCfm = NULLP;

   TRC2(rmAcHdlRgmBndReq);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRgmBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRgmBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlRgmBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rmMsg = (RmAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTRGMBNDREQ;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);
   rmMsg = (RmAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */
   /*
   bndCfm = (RmMngmt *)(rmMsg->u.rgmInfo.data);

	if(bndCfm->cfm.status != retVal && bndCfm->cfm.reason != reason )
	{
      		CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
                  retVal, bndCfm->cfm.status, reason, bndCfm->cfm.reason), 2);

      		RETVALUE(CMXTA_ERR_INT);
	}
   */
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   rmAcHdlRgmBndCfm
*
*       Desc:  Call Handler for LRM Generic config Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRgmBndCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRgmBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RmAccMsgQElm  *rmMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SuId          suId = 0;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U8            status = CM_BND_OK;

   U16       retVal = LCM_PRIM_OK;
   U16       reason = LCM_REASON_NOT_APPL;
   RmMngmt		*bndCfm = NULLP;

   TRC2(rmAcHdlRgmBndCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRgmBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRgmBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTRGMBNDCFM;


   /* Send the indication to the RRM --*/

  if(CMXTA_ERR_NONE != RmLiRgmBndCfm(&pst, suId, status))
  {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRgmBndCfm(): Mapping returned FAILED\n"));
  }
  

   RETVALUE(CMXTA_ERR_NONE);
}

/*utility function begins*/

#ifdef ANSI
PUBLIC S16 rmAcUtlRgmFreeCb
(
CmXtaMsgQElm    *qElm
)
#else
PUBLIC S16 rmAcUtlRgmFreeCb(qElm)
CmXtaMsgQElm   *qElm;
#endif
{
   RmAccMsgQElm *rmMsg;

   TRC2(rmAcUtlRgmFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "rmAcUtlRgmFreeCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   rmMsg = (RmAccMsgQElm *)qElm->data;

   if(rmMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   if (rmMsg != NULLP)
   {
      if(rmMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(rmMsg->mBuf);
      if(rmMsg->u.rgmInfo.data != NULLP)
      {
         WRAC_RMUFREEBUF(rmMsg->u.rgmInfo.data, rmMsg->u.rgmInfo.len);
      }
      CMXTA_FREE(rmMsg, sizeof (RmAccMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/*utility function ends*/
#endif
