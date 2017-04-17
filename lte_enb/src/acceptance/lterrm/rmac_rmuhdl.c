

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_rmuhdl.c

     Sid:      rmac_rmuhdl.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:45:39 2013

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
#include "rmac_acc.x"
#include "rmac_rmu.x"


PUBLIC S16 smWrActvTsk()
{
   return 0;
}   

/**
 * @brief XTA Bind Request Handler for RMU interface. 
 *
 * @details
 *
 *     Function : rmAcHdlRmuBndReq
 *     
 *     Issues a bindrequest from RMU to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/
#ifdef ANSI
PUBLIC S16 rmAcHdlRmuBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rmAcHdlRmuBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId = 0;             /* service user SAP identifier */
   SpId          spId = 0;             /* service user SAP identifier */
   U8            coupling=RMU_SEL_LWLC;
   ProcId        srcProcId;
   ProcId        dstProcId;
   S16           ret = RFAILED;

   
   TRC2(rmAcHdlRmuBndReq);
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuBndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

   cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));
   pst.selector = coupling; 
   
   pst.event = EVTRMUBNDREQ;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Send the request to the GCP --*/
   WrLiRmuBndReq(&pst, suId, spId);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rmAcHdlRmuBndReq --*/


/**
 * @brief XTA Bind Confirm Handler for RMU interface. 
 *
 * @details
 *
 *     Function : rmAcHdlRmuBndCfm 
 *     
 *     Validates a Bind Confirm from MAC to RMU. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_FATAL 
 *      -# CMXTA_ERR_NOMATCH 
 *      -# CMXTA_ERR_INT 
 **/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 rmAcHdlRmuBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   RmAccMsgQElm  *rmMsg = NULLP;
   Pst           pst;
   SpId          suId = 0;
   Status        status = CM_BND_OK;
	ProcId        srcProcId;
	ProcId        dstProcId;
   U8            coupling=RMU_SEL_LWLC;
   S16           ret = RFAILED;
 
   TRC2(rmAcHdlRmuBndCfm);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlRmuBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from FSM to RRM --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));
   pst.selector = coupling; 

   pst.event = EVTRMUBNDCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcHdlRmuUeAdmitRsp() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }



   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlRmuBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rmMsg = (RmAccMsgQElm *)msg->data;

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != rmMsg->u.rmuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, rmMsg->u.rmuInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));
 
   if (status != rmMsg->u.rmuInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, rmMsg->u.rmuInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- rmAcHdlRmuBndCfm --*/

#if 0
/**
 * @brief XTA UnBind Request Handler for RMU interface. 
 *
 * @details
 *
 *     Function : rmAcHdlRmuUbndReq 
 *     
 *     Issues an Un-Bind request from RMU to MAC. 
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 **/ 

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   Reason         reason = 0;
   
   TRC2(rmAcHdlRmuUbndReq);
   
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cmXtaGetPst(&pst, RMAC_RMU_USERENT, RMAC_RMU_USERINST, RMAC_RMU_PROVENT, RMAC_RMU_PROVINST + 1, RMAC_RMU_SRCPROC, RMAC_RMU_DSTPROC, RMAC_RMU_MATCHPROC);
   cmXtaGetPst(&pst, RMAC_RMU_USERENT, RMAC_RMU_USERINST,RMAC_RMU_PROVENT,RMAC_RMU_PROVINST + 1, RMAC_RMU_SRCPROC, RMAC_RMU_DSTPROC, RMAC_RMU_MATCHPROC);
   
   
   pst.event = RMAC_RMU_EVTUBNDREQ;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
 
   /* Send the request to the MAC --*/
   RMAC_RMU_UBNDREQ(&pst, spId, reason);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- rmAcHdlRmuUbndReq --*/

#endif


/*
*
*       Fun:   rmAcHdlRmuMmeOvldStartInd
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
PUBLIC S16 rmAcHdlRmuMmeOvldStartInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuMmeOvldStartInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
/*	SpId          spId;              service user SAP identifier 
	Bool          entity;
	S16           error;*/
	S16           ret = 0; 
	ProcId        srcProcId;
	ProcId        dstProcId;
/*	U8			  cellId = 0;*/	
	U16           mmeId = 0;
	RmuMmeOvldStartInd* startInfo;
	RmuMmeOvldStatus ovrldStatus;

	TRC2(rmAcHdlRmuMmeOvldStartInd);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuMmeOvldStartInd(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuMmeOvldStartInd(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;


	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTRMUOVLDSTRTIND;
		
	// Get the RmuMmeOvldStatus, MME-ID and CellId from XML

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "ovrldStatus",  &(ovrldStatus));

	if(ret == CMXTA_ERR_NO_VALUE)
    {
       CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuMmeOvldStartInd(): default ovrldStatus %d\n", ovrldStatus));
    }

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mmeId",  &(mmeId));

	if(ret == CMXTA_ERR_NO_VALUE)
    {
       CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuMmeOvldStartInd(): default mmeId %d\n", mmeId));
    }

	// Allocate the memory for MmeOvldStartInd msg

	CMXTA_ALLOC(&startInfo, sizeof(RmuMmeOvldStartInd));
	
   if(startInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuMmeOvldStartInd(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into startInfo

	startInfo->enMmeOvldStatus = ovrldStatus;
	startInfo->usMmeId = mmeId;

	/* Send the indication to the RRM --*/

	if(CMXTA_ERR_NONE != WrLiRmuMmeOvldStartInd(&pst, suId, startInfo))
    {
       CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuMmeOvldStartInd(): Mapping returned FAILED\n"));
    }

    RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:   rmAcHdlRmuFsmStatusInd
*
*       Desc:  Call Handler for RMU FSM status Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuFsmStatusInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuFsmStatusInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   /*	SpId          spId;              service user SAP identifier 
      Bool          entity;
      S16           error; */
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   /*	U8			  cellId = 0;*/	
   U16           mmeId = 0;
   U8            cellId = 0;
   RmuFsmStatusInd* statusInfo;
   S16            status = RMU_FSM_STATUS_MME;
   RmuMmeStatus mmeStatus;
   RmuEnbStatus enbStatus;

   TRC2(rmAcHdlRmuMmeOvldStartInd);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuFsmStatusInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuFsmStatusInd(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   suId = 0;


   /*-- Get the Pst information here from FSM to RRM --*/
   cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
         dstProcId, FALSE);

   pst.event   = EVTRMUFSMSTAIND;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "status",  &(status));
   // Get the RmuMmeOvldStatus, MME-ID and CellId from XML
   if(status == RMU_FSM_STATUS_MME)
   {
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "mmeStatus",  &(mmeStatus));
      if(ret == CMXTA_ERR_NO_VALUE)
      {
         CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuFsmStatusInd(): default mmeStatus %d\n", mmeStatus));
      }
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mmeId",  &(mmeId));
      if(ret == CMXTA_ERR_NO_VALUE)
      {
         CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuFsmStatusInd(): default mmeId %d\n", mmeId));
      }
   }
   else
   {
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "enbStatus",  &(enbStatus));
      if(ret == CMXTA_ERR_NO_VALUE)
      {
         CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuFsmStatusInd(): default enbStatus %d\n", enbStatus));
      }
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
      if(ret == CMXTA_ERR_NO_VALUE)
      {
         CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuFsmStatusInd(): default cellId %d\n", cellId));
      }
   }

   // Allocate the memory for RmuFsmStatusInd msg

   CMXTA_ALLOC(&statusInfo, sizeof(RmuFsmStatusInd));

   if(statusInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuFsmStatusInd(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into startInfo

   statusInfo->enStatusType = status;
   if(statusInfo->enStatusType == RMU_FSM_STATUS_MME)
   {
      statusInfo->u.stMmeStatusInd.enMmeStatus = mmeStatus;
      statusInfo->u.stMmeStatusInd.usMmeId = mmeId;
   }
   else 
   {
      statusInfo->u.stEnbStatusInd.enEnbStatus = enbStatus;
      statusInfo->u.stEnbStatusInd.bCellId = cellId;

   }
   /* Send the indication to the RRM --*/

   if(CMXTA_ERR_NONE != WrLiRmuFsmStatusInd(&pst, suId, statusInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuFsmStatusInd(): Mapping returned FAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}    

/*
*
*       Fun:   rmAcHdlRmuCellReconfigInd
*
*       Desc:  Call Handler for Cell Reconfig Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuCellReconfigInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuCellReconfigInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{

	CmXtaMsgQElm    *msg = NULLP;
	RmAccMsgQElm    *rmMsg = NULLP;
	Pst              pst;
	S16              ret = 0;
/*	SuId             suId;*/
	ProcId           srcProcId;
	ProcId           dstProcId;
/*	RmuConEstCause   estCause;*/
	RmuCellRecfgInd  *cellRecfgInfo;

	U8			  cellId = 0;	
   U8         isEmergencyBarred;
   U8         isMoSigBarred;
   U8         isMoDataBarred;
   U8         acbSplClassSig=0;
   CmRrmAcBarringFactor acbFactorSig;
   CmRrmAcBarringTime acbTimeSig=0;

   U8         acbSplClassData=0;
   CmRrmAcBarringFactor    acbFactorData=0;
   CmRrmAcBarringTime  acbTimeData=0;

	TRC2(rmAcHdlRmuCellReconfigInd);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuCellReconfigInd(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuCellReconfigInd(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from FSM to RRM --*/
    /*cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);*/

	/*-- Get the data from XML --*/
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isEmergencyBarred",  &(isEmergencyBarred));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isMoSigBarred",  &(isMoSigBarred));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isMoDataBarred",  &(isMoDataBarred));

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "acbSplClassSig",  &(acbSplClassSig));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "acbFactorSig",  &(acbFactorSig));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "acbTimeSig",  &(acbTimeSig));

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "acbSplClassData",  &(acbSplClassData));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "acbFactorData",  &(acbFactorData));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "acbTimeData",  &(acbTimeData));

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlRmuCellReconfigInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rmMsg = (RmAccMsgQElm *)msg->data;
   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTRMUCELLRECFGIND;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcHdlRmuCellReconfigInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /* Compare the value in the message and the value provided from xml */

   cellRecfgInfo = (RmuCellRecfgInd *)(rmMsg->u.rmuInfo.data);

   if(cellRecfgInfo->bCellId != cellId && cellRecfgInfo->enCellRecfgType != RMU_CELL_RECFG_ACB_IND )
	{
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expCellId (%d) rcvdCellId (%d)"
                                  " expRcfgType (%d) rcvdRecfgType (%d) ",
                  cellId, cellRecfgInfo->bCellId, RMU_CELL_RECFG_ACB_IND, cellRecfgInfo->enCellRecfgType ), 2);
      RETVALUE(CMXTA_ERR_INT);
   }   

   if(cellRecfgInfo->stAcbParamInd.stAcbInfo.bAcBarringEmergency != isEmergencyBarred)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expAcBarringEmergency(%d) rcvdAcBarringEmergency(%d)",isEmergencyBarred, cellRecfgInfo->stAcbParamInd.stAcbInfo.bAcBarringEmergency ), 2);
      RETVALUE(CMXTA_ERR_INT);
   }
   
   if(cellRecfgInfo->stAcbParamInd.stAcbInfo.bIsacBarringMoSig != isMoSigBarred)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expAcBarringMoSig(%d) rcvdAcBarringMoSig(%d)",isMoSigBarred, cellRecfgInfo->stAcbParamInd.stAcbInfo.bIsacBarringMoSig ), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if(isMoSigBarred)
   {
      if(cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoSig.enAcbFactor != acbFactorSig)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expAcbFactorSig(%d) rcvdAcbFactorSig(%d)",acbFactorSig, cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoSig.enAcbFactor ), 2);
         RETVALUE(CMXTA_ERR_INT);
      }

      if(cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoSig.enAcbTime != acbTimeSig )
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expAcbTimeSig(%d) rcvdAcbTimeSig(%d)",acbTimeSig, cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoSig.enAcbTime ), 2);
         RETVALUE(CMXTA_ERR_INT);
      }

      if(cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoSig.bAcbForSpac != acbSplClassSig )
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expAcbSplClassSig(%d) rcvdAcbSplClassSig(%d)",acbSplClassSig, cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoSig.bAcbForSpac  ), 2);
         RETVALUE(CMXTA_ERR_INT);
      }  
   }

   if(cellRecfgInfo->stAcbParamInd.stAcbInfo.bIsacBarringMoData != isMoDataBarred)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expAcBarringMoData(%d) rcvdAcBarringMoData(%d)", isMoDataBarred, cellRecfgInfo->stAcbParamInd.stAcbInfo.bIsacBarringMoData ), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if(isMoDataBarred)
   {
      if(cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoData.enAcbFactor !=  acbFactorData)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expAcbFactorData(%d) rcvdAcbFactorData(%d)", acbFactorData, cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoData.enAcbFactor ), 2);
         RETVALUE(CMXTA_ERR_INT);
      }

      if(cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoData.enAcbTime !=  acbTimeData)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expAcbTimeData(%d) rcvdAcbTimeData(%d)",acbTimeData, cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoSig.enAcbTime ), 2);
         RETVALUE(CMXTA_ERR_INT);
      }

      if(cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoData.bAcbForSpac != acbSplClassData)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expAcbSplClassData(%d) rcvdAcbSplClassData(%d)",acbSplClassData, cellRecfgInfo->stAcbParamInd.stAcbInfo.stAcBarringMoSig.bAcbForSpac ), 2);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

    RETVALUE(CMXTA_ERR_NONE);
}    

/*
*
*       Fun:   rmAcHdlRmuUeRelInd
*
*       Desc:  Call Handler for UE Release Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeRelInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeRelInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{

	CmXtaMsgQElm    *msg = NULLP;
	RmAccMsgQElm    *rmMsg = NULLP;
	Pst              pst;
	S16              ret = 0;
/*	SuId             suId;*/
	ProcId           srcProcId;
	ProcId           dstProcId;
	RmuUeRelInd      *ueRelInfo;

	U8			  cellId = 0;	
   U16        crnti = 0;

	TRC2(rmAcHdlRmuCellReconfigInd);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRelInd(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRelInd(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from FSM to RRM --*/
    /*cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);*/

	/*-- Get the data from XML --*/
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "crnti",  &(crnti));


   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlRmuUeRelInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rmMsg = (RmAccMsgQElm *)msg->data;
   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTRMUUERELIND;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcHdlRmuUeRelInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /* Compare the value in the message and the value provided from xml */

   ueRelInfo = (RmuUeRelInd*)(rmMsg->u.rmuInfo.data);

   //if(ueRelInfo->bCellId != cellId && ueRelInfo->usCrnti != crnti)
   /* HCSG DEV */
   if(ueRelInfo->bCellId != cellId || ueRelInfo->usCrnti != crnti)
	{
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expCellId (%d) rcvdCellId (%d)"
                                  " expCrnti (%d) rcvdCrnti (%d) ",
                  cellId, ueRelInfo->bCellId, crnti, ueRelInfo->usCrnti), 2);
      RETVALUE(CMXTA_ERR_INT);
   }   

   switch(ueRelInfo->enRelCause)
   {
      case RMU_CAUSE_MAX_UE_REACHED:
                           CMXTA_DBG_CALLIND((_cmxtap, "UE # %d on cell %d released .. Max UE Cap reached\n",
                                    ueRelInfo->usCrnti,ueRelInfo->bCellId),2);
                           break;

      case RMU_CAUSE_OUT_OF_RESOURCE:
                           CMXTA_DBG_CALLIND((_cmxtap, "UE # %d on cell %d released .. Out of Resource\n",
                                    ueRelInfo->usCrnti,ueRelInfo->bCellId),2);
                           break;
      
      case RMU_CAUSE_OTHER:
                           CMXTA_DBG_CALLIND((_cmxtap, "UE # %d on cell %d released .. Reason other\n",
                                    ueRelInfo->usCrnti,ueRelInfo->bCellId),2);
                           break;   

/* HCSG_DEV start */
      case RMU_CAUSE_MAX_CSG_UE_REACHED:
                           CMXTA_DBG_CALLIND((_cmxtap, "\nUE # %d on cell %d released .. Reason max CSG UEs reached\n",
                                    ueRelInfo->usCrnti,ueRelInfo->bCellId),2);
                           break;   

      case RMU_CAUSE_MAX_NON_CSG_UE_REACHED:
                           CMXTA_DBG_CALLIND((_cmxtap, "\nUE # %d on cell %d released .. Reason max non-CSG UEs reached\n",
                                    ueRelInfo->usCrnti,ueRelInfo->bCellId),2);
                           break;   

      case RMU_CAUSE_MAX_EXTRA_UE_REACHED:
                           CMXTA_DBG_CALLIND((_cmxtap, "\nUE # %d on cell %d released .. Reason max Extra UEs reached\n",
                                    ueRelInfo->usCrnti,ueRelInfo->bCellId),2);
                           break;
/* HCSG_DEV end */

      default:
                           CMXTA_DBG_CALLIND((_cmxtap, "UE # %d on cell %d released .. Unknown reason",
                                    ueRelInfo->usCrnti,ueRelInfo->bCellId),2);
   }  


    RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   rmAcHdlRmuMmeOvldStopInd
*
*       Desc:  Call Handler for RMU MME Overload Stop Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuMmeOvldStopInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuMmeOvldStopInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
/*	SpId          spId;              service user SAP identifier 
	Bool          entity;
	S16           error;*/
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	U8			  cellId = 0;	
	U16           mmeId = 0;
	RmuMmeOvldStopInd* stopInfo;

	TRC2(rmAcHdlRmuMmeOvldStopInd);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuMmeOvldStopInd(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuMmeOvldStopInd(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;

	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTRMUOVLDSTPIND;
		
	// Get the MME-ID and CellId from XML

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));

	if(ret == CMXTA_ERR_NO_VALUE)
    {
       CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuMmeOvldStopInd(): default cellId %d\n", cellId));
    }

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mmeId",  &(mmeId));

	if(ret == CMXTA_ERR_NO_VALUE)
    {
       CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuMmeOvldStopInd(): default mmeId %d\n", mmeId));
    }

	// Allocate the memory for MmeOvldStopInd msg

	CMXTA_ALLOC(&stopInfo, sizeof(RmuMmeOvldStopInd));
	
   if(stopInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuMmeOvldStopInd(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into stopInfo

	stopInfo->usMmeId = mmeId;
	//stopInfo->usCellId = cellId;

	/* Send the indication to the RRM --*/

	if(CMXTA_ERR_NONE != WrLiRmuMmeOvldStopInd(&pst, suId, stopInfo))
    {
       CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuMmeOvldStopInd(): Mapping returned FAILED\n"));
    }

    RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   rmAcHdlRmuUeAdmitReq
*
*       Desc:  Call Handler for RMU UE Admit Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeAdmitReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeAdmitReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
/*	SpId          spId;              service user SAP identifier 
	Bool          entity;
	S16           error;*/
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	U8			  cellId = 0;	
	U16           tCrnti = 0;
	U32			  transId = 0;
	RmuConEstCause connEstCause;	
	RmuUeAdmitReq* ueAdmitInfo;
   U8            coupling=RMU_SEL_LWLC;

	TRC2(rmAcHdlRmuUeAdmitReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeAdmitReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeAdmitReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;

	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);
   pst.selector = coupling;
	pst.event   = EVTRMUUEADMITREQ;
		
	// Get the CellId, CRNTI, TransactionId and ConnEstalishmentCause from XML


	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));

	if(ret == CMXTA_ERR_NO_VALUE)
    {
       CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuUeAdmitReq(): default cellId %d\n", cellId));
    }

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));

	if(ret == CMXTA_ERR_NO_VALUE)
    {
       CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuUeAdmitReq(): default tCrnti %d\n", tCrnti));
    }

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));

	if(ret == CMXTA_ERR_NO_VALUE)
    {
       CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuUeAdmitReq(): default transId %ld\n", transId));
    }

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "connEstCause",  &(connEstCause));

	if(ret == CMXTA_ERR_NO_VALUE)
    {
       CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuUeAdmitReq(): default connEstCause %d\n", connEstCause));
    }

	// Allocate the memory for RmuUeAdmitReq msg

	CMXTA_ALLOC(&ueAdmitInfo, sizeof(RmuUeAdmitReq));
	
   if(ueAdmitInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeAdmitReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into ueAdmitInfo

	ueAdmitInfo->bCellId = cellId;
	ueAdmitInfo->usCrnti = tCrnti;
	ueAdmitInfo->uiTransId = transId;
	ueAdmitInfo->enConEstabCause = connEstCause;

	/* Send the msg to the RRM --*/

	if(CMXTA_ERR_NONE != WrLiRmuUeAdmitReq(&pst, suId, ueAdmitInfo))
    {
       CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeAdmitReq(): Mapping returned FAILED\n"));
    }

    RETVALUE(CMXTA_ERR_NONE);
	
}


U8 rmAcRmuhdlVldtRadRes
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
RmuUeRadioResCfg *pstUeRadioResCfg
)
{

   RmuPcqiFormatInd		cqiFormatIndex;
   RmuPucchReportMode	pucchReportMode;
   U16				      cqiResourceIndex;
   U16				      cqiConfigIndex;
   U16				      riConfigIndex;
	S16                  ret = 0;
   U8				         simulAckNackCqi;
   U8				         retFlag = 0;
   U8                   erabCount=1;
   U8                   i;

   U16                  srResourceIndex = 0;
   U16                  srConfigIndex = 0;
   U32                  bPhyCfgDedResBitMap = 0;
   U8                   bRadioResDedBitMap = 0;
   U8                   bMacMainCfgBitMap = 0;
   CmRrmDsrTransMax     enDsrTransMax = DSR_TRANS_N4;



   Bool  drxEnabled = FALSE;
   U8    drxOnDurTimer;
   U8    drxRetxTimer;
   U16   drxInactTimer;

   Bool              dlSpsEnabled = FALSE;
   RmuSpsIntervalDl  spsIntervalDl;
   U16               explctRelAftr;
   U8                numOfConfSpsProc;
   U8                numN1Pucch;
   Txt               n1PucchRes[20], *n1PucchResTokMain, *n1PucchResTokSub, *tok1;
   U8                idx;
   U16               n1PucchResVal;

   Bool                 ulSpsEnabled = FALSE;
   RmuSpsIntervalUl     spsIntervalUl;
   RmuSpsImplctRelAftr  implctRelAftr;

   U8 n1ResLstCount = 0;
   U8 n1Tb1ResCount = 0;
   U8 n1Tb2ResCount = 0;
   U8 n1Tb1ResLst[4]={0,};
   U8 n1Tb2ResLst[4]={0,};
   U8 count = 0;


   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bRadioResDedBitMap",  &(bRadioResDedBitMap));

   if(bRadioResDedBitMap == pstUeRadioResCfg->bRadioResDedBitMap)
   {
      if(bRadioResDedBitMap & RM_RCM_PHY_DED_RES_CFG)
      {
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bPhyCfgDedResBitMap",  &(bPhyCfgDedResBitMap));

         if(bPhyCfgDedResBitMap == pstUeRadioResCfg->stPhyCfgDed.bPhyCfgDedResBitMap)
         {
            if(bPhyCfgDedResBitMap & RM_RCM_PHY_DED_RES_CFG_CQI) 
            {
               //Valiate PCQI strct members
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "CqiFormatIndex",  &(cqiFormatIndex));
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "PucchReportMode",  &(pucchReportMode));
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CqiResourceIndex",  &(cqiResourceIndex));
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CqiConfigIndex",  &(cqiConfigIndex));
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "RiConfigIndex",  &(riConfigIndex));
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "SimulAckNackCqi",  &(simulAckNackCqi));

               RmuPCqiReportCfg *pstPrdCqiRepCfg = &pstUeRadioResCfg->stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg;

               if( pstPrdCqiRepCfg->enCqiFormatInd != cqiFormatIndex)
               {
                  CMXTA_DBG_INFO((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in CqiFormatIndex exp (%d) rcvd(%d) \n", 
                           cqiFormatIndex, pstPrdCqiRepCfg->enCqiFormatInd));
                  retFlag = 1;
               }

               if( pstPrdCqiRepCfg->enPucchReportMode != pucchReportMode)
               {
                  CMXTA_DBG_INFO((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in PucchReportMode exp (%d) rcvd(%d) \n", 
                           pucchReportMode, pstPrdCqiRepCfg->enPucchReportMode));
                  retFlag = 1;
               }

               if( pstPrdCqiRepCfg->usCqiResourceIndex != cqiResourceIndex)
               {
                  CMXTA_DBG_INFO((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in CqiResourceIndex exp (%d) rcvd(%d) \n", 
                           cqiResourceIndex, pstPrdCqiRepCfg->usCqiResourceIndex));
                  retFlag = 1;
               }

               if( pstPrdCqiRepCfg->usCqiConfigIndex != cqiConfigIndex)
               {
                  CMXTA_DBG_INFO((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in CqiConfigIndex exp (%d) rcvd(%d) \n",
                           cqiConfigIndex, pstPrdCqiRepCfg->usCqiConfigIndex));			
                  retFlag = 1;
               }

               if((pstPrdCqiRepCfg->riConfigIndex.bPres == TRUE) || (riConfigIndex ))
               {    
                  if( pstPrdCqiRepCfg->riConfigIndex.usRiConfigIndex != riConfigIndex)
                  {
                     CMXTA_DBG_INFO((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in RiConfigIndex exp (%d) rcvd(%d) \n", 
                              riConfigIndex, pstPrdCqiRepCfg->riConfigIndex.usRiConfigIndex));			
                     retFlag = 1;
                  }
               }

               if( pstPrdCqiRepCfg->bSimulAckNackCqi != simulAckNackCqi)
               {
                  CMXTA_DBG_INFO((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in SimulAckNackCqi exp (%d) rcvd(%d) \n", 
                           simulAckNackCqi, pstPrdCqiRepCfg->bSimulAckNackCqi));			
                  retFlag = 1;
               }
            }
            if(bPhyCfgDedResBitMap & RM_RCM_PHY_DED_RES_CFG_SR) 
            {
               //Valiate SR strct members
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "srResourceIndex",  &(srResourceIndex));
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "srConfigIndex",  &(srConfigIndex));
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "enDsrTransMax",  &(enDsrTransMax));

               RmuUeSrCfg *pRcvdSrCfg = &pstUeRadioResCfg->stPhyCfgDed.stSrCfg;

               if( pRcvdSrCfg->usSrIdx != srConfigIndex)
               {
                  CMXTA_DBG_INFO((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in srConfigIndex exp (%d) rcvd(%d) \n", 
                           srConfigIndex, pRcvdSrCfg->usSrIdx));
                  retFlag = 1;
               }

               if( pRcvdSrCfg->usSrResIdx != srResourceIndex)
               {
                  CMXTA_DBG_INFO((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in srResourceIndex exp (%d) rcvd(%d) \n", 
                           srResourceIndex, pRcvdSrCfg->usSrResIdx));
                  retFlag = 1;
               }

               if( pRcvdSrCfg->enDsrTransMax != enDsrTransMax)
               {
                  CMXTA_DBG_INFO((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in enDsrTransMax exp (%d) rcvd(%u) \n", 
                           enDsrTransMax, pRcvdSrCfg->enDsrTransMax));			
                  retFlag = 1;
               }
            }
            if(bPhyCfgDedResBitMap & RM_RCM_PHY_DED_RES_CFG_SCELL_ACK_N1_RES) 
            {
               RmuUePucchCfg *pucchCfg = &pstUeRadioResCfg->stPhyCfgDed.pucchCfgDed;

               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "n1Tb1ResCount",  &(n1Tb1ResCount));

               if(n1Tb1ResCount != pucchCfg->sCellAckN1ResTb1Count)
               {
                  CMXTA_DBG_ERR((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in n1ResTb1Count exp (%d) rcvd(%u) \n", 
                           n1Tb1ResCount, pucchCfg->sCellAckN1ResTb1Count));			
                  retFlag = 1;
               }
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "n1Tb2ResCount",  &(n1Tb2ResCount));
               if(n1Tb2ResCount != pucchCfg->sCellAckN1ResTb2Count)
               {
                  CMXTA_DBG_ERR((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in n1ResTb1Count exp (%d) rcvd(%u) \n", 
                           n1Tb2ResCount, pucchCfg->sCellAckN1ResTb2Count));			
                  retFlag = 1;
               }

               cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"n1ResTb1Lst", n1Tb1ResLst, 
                     &count);
               if(pucchCfg->sCellAckN1ResTb1Count != count)
               {
                  CMXTA_DBG_ERR((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in n1ResTb1Count from xml cfgd (%d) rcvd(%d) \n", 
                           count, pucchCfg->sCellAckN1ResTb1Count));			
                  retFlag = 1;
               }
               for(U8 idx = 0 ; idx < count; idx++)
               {
                  if(pucchCfg->sCellAckN1ResTb1[idx] != n1Tb1ResLst[idx])
                  {
                     CMXTA_DBG_ERR((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in n1Res for Tb1(%d) rcvd(%d) \n", 
                              n1Tb1ResLst[idx], pucchCfg->sCellAckN1ResTb1[idx]));			
                     retFlag = 1;
                  }
               }

               cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,"n1ResTb2Lst", n1Tb2ResLst, 
                     &count);
               if(pucchCfg->sCellAckN1ResTb2Count != count)
               {
                  CMXTA_DBG_ERR((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in n1ResTb1Count from xml cfgd for TB2 (%d) rcvd(%d) \n", 
                           count, pucchCfg->sCellAckN1ResTb2Count));			
                  retFlag = 1;
               }
               for(idx = 0 ; idx < count; idx++)
               {
                  if(pucchCfg->sCellAckN1ResTb2[idx] != n1Tb2ResLst[idx])
                  {
                     CMXTA_DBG_ERR((_cmxtap,"rmAcRmuhdlVldtRadRes(): Mismatch in n1Res for Tb1(%d) rcvd(%d) \n", 
                              n1Tb2ResLst[idx], pucchCfg->sCellAckN1ResTb2[idx]));			
                     retFlag = 1;
                  }
               }

            }
         }
         else
         {
            /* Error */
            CMXTA_DBG_INFO((_cmxtap,"Phy Dedicated Bitmap Map Mismated.. Expected [%d], Received [%d]\n",
                     bPhyCfgDedResBitMap, pstUeRadioResCfg->stPhyCfgDed.bPhyCfgDedResBitMap));
            retFlag = 1;

         }
      }
      if(bRadioResDedBitMap & RM_RCM_MAC_MAIN_CFG)
      {
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bMacMainCfgBitMap",  &(bMacMainCfgBitMap));

         if(bMacMainCfgBitMap == pstUeRadioResCfg->stMacMainCfg.bMacMainCfgBitMap)
         {
            if(bMacMainCfgBitMap & RM_RCM_MAC_MAIN_CFG_DRX) 
            {
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "drxEnabled",  &(drxEnabled));
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "drxOnDurTimer",  &(drxOnDurTimer));
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "drxRetxTimer",  &(drxRetxTimer));
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "drxInactTimer",  &(drxInactTimer));

               if(pstUeRadioResCfg->stMacMainCfg.stRmDrxCfg.bIsDrxEnabled == drxEnabled)
               {
                  if(pstUeRadioResCfg->stMacMainCfg.stRmDrxCfg.bIsDrxEnabled)
                  {

                     if(pstUeRadioResCfg->stMacMainCfg.stRmDrxCfg.bDrxOnDurTmr!= drxOnDurTimer)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expDrxOnDurTimer (%d) rcvdDrxOnDurTimer (%d)",
                                 drxOnDurTimer, pstUeRadioResCfg->stMacMainCfg.stRmDrxCfg.bDrxOnDurTmr), 2);
                        retFlag = 1;
                     }   

                     if(pstUeRadioResCfg->stMacMainCfg.stRmDrxCfg.bDrxRetxTmr!= drxRetxTimer)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expDrxRetxTimer (%d) rcvdDrxRetxTimer (%d)",
                                 drxRetxTimer, pstUeRadioResCfg->stMacMainCfg.stRmDrxCfg.bDrxRetxTmr), 2);
                        retFlag = 1;
                     }   

                     if(pstUeRadioResCfg->stMacMainCfg.stRmDrxCfg.usDrxInactvTmr!= drxInactTimer)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expDrxInactTimer (%d) rcvdDrxInactTimer (%d)",
                                 drxInactTimer, pstUeRadioResCfg->stMacMainCfg.stRmDrxCfg.usDrxInactvTmr), 2);
                        retFlag = 1;
                     }   
                  }
               }
               else
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expDrxEnb (%d) rcvdDrxEnb (%d)",
                           drxEnabled, pstUeRadioResCfg->stMacMainCfg.stRmDrxCfg.bIsDrxEnabled), 2);
                  retFlag = 1;
               }   

            }
         }
         else
         {
            /* Error */
            CMXTA_DBG_INFO((_cmxtap,"Phy Dedicated Bitmap Map Mismated.. Expected [%d], Received [%d]\n",
                     bMacMainCfgBitMap, pstUeRadioResCfg->stMacMainCfg.bMacMainCfgBitMap));
            retFlag = 1;

         }

      }
      if(bRadioResDedBitMap & RM_RCM_DL_SPS_CFG)
      {
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "dlSpsEnabled",  &(dlSpsEnabled));
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "spsIntervalDl",  &(spsIntervalDl));
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "explctRelAftr",  &(explctRelAftr));
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numOfConfSpsProc",  &(numOfConfSpsProc));
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numN1Pucch",  &(numN1Pucch));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "n1PucchRes", &(n1PucchRes));

         if(dlSpsEnabled == pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.bIsSpsEnabled)
         {
            if(pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.bIsSpsEnabled == TRUE)
            {
               if(pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.eSpsIntervalDl != spsIntervalDl)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: eSpsIntervalDl (%d) rcvdSpsIntervalDl (%d)",
                           spsIntervalDl, pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.eSpsIntervalDl), 2);
                  retFlag = 1;
               }   
               if(pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.usExplctRelAftr != explctRelAftr)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: explctRelAftr (%d) rcvdExplctRelAftr (%d)",
                           explctRelAftr, pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.usExplctRelAftr), 2);
                  retFlag = 1;
               }   
               if(pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.usNumOfConfSpsProc != numOfConfSpsProc)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: numOfConfSpsProc (%d) rcvdNumOfConfSpsProc (%d)",
                           numOfConfSpsProc, pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.usNumOfConfSpsProc), 2);
                  retFlag = 1;
               }   
               if(pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.usNumN1Pucch != numN1Pucch)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: numN1Pucch (%d) rcvdNumN1Pucch (%d)",
                           numN1Pucch, pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.usNumN1Pucch), 2);
                  retFlag = 1;
               }   

               n1PucchResTokMain = n1PucchRes;
               for(n1PucchResTokMain, idx = 0; idx < RM_RCM_SPS_MAX_N1_PUCCH; idx++, n1PucchResTokMain=NULLP)
               {
                  if ((n1PucchResTokSub =(Txt *)strtok_r(n1PucchResTokMain,":",&tok1)) == NULLP)
                     break;

                  n1PucchResVal = atoi(n1PucchResTokSub);

                  if(pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.usN1Pucch[idx] != n1PucchResVal)
                  {
                     CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: n1PucchRes (%d) rcvdN1PucchRes (%d)",
                              n1PucchResVal, pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.usN1Pucch[idx]), 2);
                     retFlag = 1;
                  }   
               }

               if(pstUeRadioResCfg->stSpsCfg.stSpsConfigDl.usN1Pucch[0] != n1PucchRes)   
               {
               }   
            }   
         }   
      }
      if(bRadioResDedBitMap & RM_RCM_UL_SPS_CFG)
      {
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ulSpsEnabled",  &(ulSpsEnabled));
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "spsIntervalUl",  &(spsIntervalUl));
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "implctRelAftr",  &(implctRelAftr));

         if(ulSpsEnabled == pstUeRadioResCfg->stSpsCfg.stSpsConfigUl.bIsSpsEnabled)
         {
            if(pstUeRadioResCfg->stSpsCfg.stSpsConfigUl.bIsSpsEnabled == TRUE)
            {
               if(pstUeRadioResCfg->stSpsCfg.stSpsConfigUl.eSpsIntervalUl != spsIntervalUl)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: eSpsIntervalUl (%d) rcvdSpsIntervalUl (%d)",
                           spsIntervalUl, pstUeRadioResCfg->stSpsCfg.stSpsConfigUl.eSpsIntervalUl), 2);
                  retFlag = 1;
               }
               if(pstUeRadioResCfg->stSpsCfg.stSpsConfigUl.eImplctRelAftr != implctRelAftr)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: explctRelAftr (%d) rcvdExplctRelAftr (%d)",
                           implctRelAftr, pstUeRadioResCfg->stSpsCfg.stSpsConfigUl.eImplctRelAftr), 2);
                  retFlag = 1;
               }
            }
         }
      }    
   }
   else
   {
      /* Error */
      CMXTA_DBG_INFO((_cmxtap,"Radio Res Config Bitmap Map Mismated.. Expected [%d], Received [%d]\n",
               bRadioResDedBitMap, pstUeRadioResCfg->bRadioResDedBitMap));
      retFlag = 1;
   }

   return retFlag;
}





/*
*
*       Fun:   rmAcHdlRmuUeAdmitRsp
*
*       Desc:  Handler for Rmu UE admit response 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeAdmitRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeAdmitRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{

	CmXtaMsgQElm    *msg = NULLP;
	RmAccMsgQElm    *rmMsg = NULLP;
	Pst              pst;
	S16              ret = 0;
/*	SuId             suId;*/
	ProcId           srcProcId;
	ProcId           dstProcId;
/*	RmuConEstCause   estCause;*/
	RmuUeAdmitRsp *admitRspinfo;

	U8			      cellId = 0;	
   RmuStatus      status = RMU_SUCCESS;
	U16            tCrnti = 0;
	U32			   transId = 0;
   U8             retFlag = 0;
   S16            retVal = RMU_SUCCESS;


	TRC2(rmAcHdlRmuUeAdmitRsp);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeAdmitRsp(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeAdmitRsp(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from FSM to RRM --*/
    /*cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);*/

	/*-- Get the data from XML --*/
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "status",  &(status));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));


   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlRmuUeAdmitRsp(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rmMsg = (RmAccMsgQElm *)msg->data;
   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTRMUUEADMITRSP;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcHdlRmuUeAdmitRsp() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /* Compare the value in the message and the value provided from xml */

   admitRspinfo = (RmuUeAdmitRsp *)(rmMsg->u.rmuInfo.data);

   if(admitRspinfo->bCellId != cellId || admitRspinfo->usCrnti != tCrnti || admitRspinfo->uiTransId != transId )
	{
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expCellId (%ld) rcvdCellId (%ld)"
                                  " expCrnti (%d) rcvdCrnti (%d) "
								  " expTransId (%d) rcvdTransId (%d) ",
                  cellId, admitRspinfo->bCellId, tCrnti, admitRspinfo->usCrnti, transId, admitRspinfo->uiTransId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
	}

   //Validate the Response Status to the expectyed value
   if(admitRspinfo->stStatusInfo.enStatus != status)
   {
       CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuUeAdmitRsp(): Mismatch in Admit Response Status exp (%d) rcvd(%d) \n", 
                status, admitRspinfo->stStatusInfo.enStatus));
      retFlag = 1;
   }

   if(admitRspinfo->stStatusInfo.enStatus == RMU_SUCCESS)
   {
      retFlag = rmAcRmuhdlVldtRadRes(tcCb, spCb, &admitRspinfo->stUeRadioResCfg);
   }
   else 
	{
		switch(admitRspinfo->stStatusInfo.enCause)
		{
			case RMU_CAUSE_CELLID_UNKNOWN :
											CMXTA_DBG_CALLIND((_cmxtap, "AdmitReq faild : Unknown CellId"), 2);
											break;

         case RMU_CAUSE_UEID_ALREADY_EXISTS :
                                 CMXTA_DBG_CALLIND((_cmxtap, "AdmitReq faild : UEID already exists"), 2);
                                 break;

         case RMU_CAUSE_UEID_UNKNOWN :
											CMXTA_DBG_CALLIND((_cmxtap, "AdmitReq faild : Unknown UeId"), 2);
											break;

			case RMU_CAUSE_OUT_OF_RESOURCE:
											CMXTA_DBG_CALLIND((_cmxtap, "AdmitReq faild : Out of resouces"), 2);
											break;

			case RMU_CAUSE_MAX_UE_REACHED:
											CMXTA_DBG_CALLIND((_cmxtap, "AdmitReq faild : Max UE limit reached"), 2);
											break;
			
			case RMU_CAUSE_OTHER:
											CMXTA_DBG_CALLIND((_cmxtap, "AdmitReq faild : Other"), 2);
											break;
		}
	}

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

   if(retFlag != 1)
   {
      RETVALUE(CMXTA_ERR_NONE);
   }
   else
   {
	   RETVALUE(CMXTA_ERR_INT);
   }
}


/*
*
*       Fun:   rmAcHdlRmuUeRelReq
*
*       Desc:  Call Handler for RMU UE Release Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeRelReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeRelReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
/*	SpId          spId;              service user SAP identifier 
	Bool          entity;
	S16           error;*/
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	
	U32			  transId;
	U16			  tCrnti;
	U8			  cellId;	
	RmuUeRelReq   *ueRelReqInfo;

	TRC2(rmAcHdlRmuUeRelReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRelReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRelReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;

	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTRMUUERELREQ;
		
	// Get the CellId, CRNTI, TransactionId from XML

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));

	// Allocate the memory for rmAcHdlRmuUeRelReq msg

	CMXTA_ALLOC(&ueRelReqInfo, sizeof(RmuUeRelReq));
	
   if(ueRelReqInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeRelReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into ueRelReqInfo

	ueRelReqInfo->bCellId = cellId;
	ueRelReqInfo->usCrnti = tCrnti;
	ueRelReqInfo->uiTransId = transId;

	/* Send the msg to the RRM --*/

	if(CMXTA_ERR_NONE != WrLiRmuUeRelReq(&pst, suId, ueRelReqInfo))
    {
       CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeRelReq(): Mapping returned FAILED\n"));
    }

    RETVALUE(CMXTA_ERR_NONE);	

}


/*
*
*       Fun:   rmAcHdlRmuUeRelRsp
*
*       Desc:  Handler for Rmu UE release response 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeRelRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeRelRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	CmXtaMsgQElm    *msg = NULLP;
	RmAccMsgQElm    *rmMsg = NULLP;
	Pst              pst;
	S16              ret = 0;
/*	SuId             suId;*/
	ProcId           srcProcId;
	ProcId           dstProcId;
/*	RmuConEstCause   estCause;*/
	RmuUeRelRsp *releaseRspInfo;

	U8			  cellId = 0;	
	U16           tCrnti = 0;
	U32			  transId = 0;

	TRC2(rmAcHdlRmuUeRelRsp);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRelRsp(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRelRsp(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from FSM to RRM --*/
    /*cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);*/

	/*-- Get the data from XML --*/
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlRmuUeRelRsp(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rmMsg = (RmAccMsgQElm *)msg->data;
   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTRMUUERELRSP;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcHdlRmuUeRelRsp() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /* Compare the value in the message and the value provided from xml */

   releaseRspInfo = (RmuUeRelRsp *)(rmMsg->u.rmuInfo.data);

   if((releaseRspInfo->bCellId != cellId) || (releaseRspInfo->usCrnti != tCrnti) || (releaseRspInfo->uiTransId != transId ))
	{
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expCellId (%ld) rcvdCellId (%ld)"
                                  " expCrnti (%d) rcvdCrnti (%d) "
								  " expTransId (%d) rcvdTransId (%d) ",
                  cellId, releaseRspInfo->bCellId, tCrnti, releaseRspInfo->usCrnti, transId, releaseRspInfo->uiTransId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
	}

	if( releaseRspInfo->stStatusInfo.enStatus != RMU_SUCCESS )
	{
		switch(releaseRspInfo->stStatusInfo.enCause)
		{
			case RMU_CAUSE_CELLID_UNKNOWN :
											CMXTA_DBG_CALLIND((_cmxtap, "ReleseReq faild : Unknown CellId"), 2);
											break;
			case RMU_CAUSE_UEID_UNKNOWN :
											CMXTA_DBG_CALLIND((_cmxtap, "ReleseReq faild : Unknown UeId"), 2);
											break;
			case RMU_CAUSE_OTHER:
											CMXTA_DBG_CALLIND((_cmxtap, "ReleseReq faild : Other"), 2);
											break;
		}
	      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
	      RETVALUE(CMXTA_ERR_INT);
	}

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   rmAcHdlRmuUeRecfgReq
*
*       Desc:  Call Handler for RMU UE Reconfig Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeRecfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeRecfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{

	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
/*	SpId          spId;              service user SAP identifier 
	Bool          entity;
	S16           error;*/
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	
	U32			  transId;
	U16			  tCrnti;
	U16			  nCrnti;
	U8			  cellId;	

	U32			  ueCategory;
	U32			  grpIndicator;
        U8                        recfgBitmap;


	RmuUeRecfgReq   *ueRecfgReqInfo;

	TRC2(rmAcHdlRmuUeRelReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRelReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRelReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;

	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTRMUUERECFGREQ;
		
	// Get the param values from XML

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "recfgBitmap",  &(recfgBitmap));
	
		if(recfgBitmap == 1)
		{
			
		}

		if(recfgBitmap == 2)
		{
			ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ueCategory",  &(ueCategory));
			ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "grpIndicator",  &(grpIndicator));
		}

		if(recfgBitmap == 4)
		{
			ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nCrnti",  &(nCrnti));
		}



	// Allocate the memory for RmuUeRecfgReq msg

	CMXTA_ALLOC(&ueRecfgReqInfo, sizeof(RmuUeRecfgReq));
	
   if(ueRecfgReqInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmSapCfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   RETVALUE(ret);

}

/*
*
*       Fun:   rmAcHdlRmuUeIcsReq
*
*       Desc:  Call Handler for RMU UE Initial context setup Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeIcsReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeIcsReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
/*	SpId          spId;              service user SAP identifier 
	Bool          entity;
	S16           error;*/
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	
	U32			  transId;
	U16			  tCrnti;
	U8			  cellId;

	RmuErabAction  erabAction;
	U8			ambrPresent;
	U8			erabId;
	U8			erabPriority = 5;
	Bool		erabPreemptCap = TRUE;
	Bool		erabPreemptVul = TRUE;
	U8		 	erabQci;

	U32			ueCategory;
	U32			grpIndicator;
   RmuAccessStratumRls ueAccessStratumRls;

	U8			  recfgBitmap;
	U8			  ueSubBand = 0;
   U8         qciValue = 1;
   U8          erabCount = 1;
   U8          i;
   U8            coupling=RMU_SEL_LWLC;
   /* HCSG_DEV */
   U8         isMember = 0;
	
/*	RmuS1apCause	cause = RMU_CAUSE_UNSPECIFIED;*/
	RmuUeRecfgReq   *ueRecfgReqInfo;

	TRC2(rmAcHdlRmuUeErabRecfgReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeErabRecfgReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeErabRecfgReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;

	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTRMUUERECFGREQ;
   pst.selector = coupling;
		
	// Get the param values from XML

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "recfgBitmap",  &(recfgBitmap));

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "erabAction",  &(erabAction));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ambrPresent",  &(ambrPresent));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabId",  &(erabId));

     
	  ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "qciValue",  &(qciValue));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ueCategory",  &(ueCategory));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "grpIndicator",  &(grpIndicator));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueSubBand",  &(ueSubBand));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "eUeAccessStratumRls",  &(ueAccessStratumRls));

		ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabQci",  &(erabQci));

		ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabCount",  &(erabCount));
      /* HCSG_DEV */
		ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isMember",  &(isMember));

	// Allocate the memory for RmuUeRecfgReq msg

	CMXTA_ALLOC(&ueRecfgReqInfo, sizeof(RmuUeRecfgReq));
	
   if(ueRecfgReqInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeErabRecfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

	//Fill the values recvd from xml

	//Fill ERAB configurations
	ueRecfgReqInfo->bCellId = cellId;
	ueRecfgReqInfo->uiTransId = transId;
	ueRecfgReqInfo->usCrnti = tCrnti;
	ueRecfgReqInfo->bRecfgBitMap = recfgBitmap;		// Should be 3 for ICS

   /* HCSG_DEV */
   ueRecfgReqInfo->isMember = isMember;

	ueRecfgReqInfo->stErabConfInfo.bIsUeAmbrPres	= ambrPresent;
	ueRecfgReqInfo->stErabConfInfo.stUeAmbrInfo.uiAggUEMaxBitRateUL = 104857600;		// 10 MB
	ueRecfgReqInfo->stErabConfInfo.stUeAmbrInfo.uiAggUEMaxBitRateDL = 104857600;		// 10 MB

	ueRecfgReqInfo->stErabConfInfo.enErabAction = erabAction;
    ueRecfgReqInfo->stErabConfInfo.bNoErabsToRel = 0;
	ueRecfgReqInfo->stErabConfInfo.usNoErabsToAddMod = erabCount;	

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabPriority",  &(erabPriority));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "erabPreemptCap",  &(erabPreemptCap));
    ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "erabPreemptVul",  &(erabPreemptVul));

    for ( i=0; i< erabCount; i++)
    {
    
	   ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].stErabQosInfo.stErabArpInfo.bErabPrioLvl = erabPriority;
   	ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].stErabQosInfo.stErabArpInfo.bErabPreemptCap = erabPreemptCap;
   	ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].stErabQosInfo.stErabArpInfo.bErabPreemptVul = erabPreemptVul;
      ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].stErabQosInfo.bErabQCI = qciValue;
   	ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].bErabId = erabId+i;
   	ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].stErabQosInfo.bErabQCI = erabQci+i;
    }

	//ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPrioLvl = erabPriority;
	//ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPreemptCap = erabPreemptCap;
	//ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPreemptVul = erabPreemptVul;
   //ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.bErabQCI = qciValue;
	//ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[0].bErabId = erabId;
	//ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.bErabQCI = erabQci;

	//Fill UE cap config

   ueRecfgReqInfo->stUeCapInfo.stEutraCapInfo.uiFeatureGrpIndicator = 0x18000000;

   if((ueAccessStratumRls == RMU_ACCESS_STRATUM_REL9) || 
        (ueAccessStratumRls == RMU_ACCESS_STRATUM_REL8) ||
        (ueAccessStratumRls == RMU_ACCESS_STRATUM_REL9HIGHER))
   {
      ueRecfgReqInfo->stUeCapInfo.stEutraCapInfo.uiFeatureGrpIndicator = grpIndicator;
   }

   if(ueSubBand)
   {
      ueRecfgReqInfo->stUeCapInfo.stEutraCapInfo.uiFeatureGrpIndicator |= 0x40000000;
   }
   

	ueRecfgReqInfo->stUeCapInfo.stEutraCapInfo.uiUeCategory = ueCategory;
	ueRecfgReqInfo->stUeCapInfo.stEutraCapInfo.uiUeAccessStratumRls = ueAccessStratumRls;

   /* Send the UeReconfig request to the RRM --*/
   if(CMXTA_ERR_NONE != WrLiRmuUeRecfgReq(&pst, suId, ueRecfgReqInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeErabRecfgReq(): Mapping returned FAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   rmAcHdlRmuUeErabRecfgReq
*
*       Desc:  Call Handler for RMU UE Erab Reconfig Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeErabRecfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeErabRecfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
/*	SpId          spId;              service user SAP identifier 
	Bool          entity;
	S16           error;*/
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	
	U32			  transId;
	U16			  tCrnti;
	U8			  cellId;

	RmuErabAction  erabAction;
	U8			ambrPresent;
	U8			erabId;
	U8			erabPriority = 5;
	Bool		erabPreemptCap = TRUE;
	Bool		erabPreemptVul = TRUE;

	U8			  recfgBitmap;
   U8       erabCount  = 1;
   U8       i;
	
   Txt      qciVal[20], *qciValTokMain, *qciValTokSub, *tok1;
   U8       erabQci;
   
	RmuS1apCause	cause = RMU_CAUSE_UNSPECIFIED;
	RmuUeRecfgReq   *ueRecfgReqInfo;

	TRC2(rmAcHdlRmuUeErabRecfgReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeErabRecfgReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeErabRecfgReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;

	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTRMUUERECFGREQ;
		
	// Get the param values from XML

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "recfgBitmap",  &(recfgBitmap));

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "erabAction",  &(erabAction));
	  ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ambrPresent",  &(ambrPresent));
	  ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabId",  &(erabId));
	  ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabCount",  &(erabCount));


	// Allocate the memory for RmuUeRecfgReq msg

	CMXTA_ALLOC(&ueRecfgReqInfo, sizeof(RmuUeRecfgReq));
	
   if(ueRecfgReqInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeErabRecfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

	//Fill the values recvd from xml

	ueRecfgReqInfo->bCellId = cellId;
	ueRecfgReqInfo->uiTransId = transId;
	ueRecfgReqInfo->usCrnti = tCrnti;
	ueRecfgReqInfo->bRecfgBitMap = recfgBitmap;

	ueRecfgReqInfo->stErabConfInfo.bIsUeAmbrPres	= ambrPresent;
	ueRecfgReqInfo->stErabConfInfo.stUeAmbrInfo.uiAggUEMaxBitRateUL = 104857600;		// 10 MB
	ueRecfgReqInfo->stErabConfInfo.stUeAmbrInfo.uiAggUEMaxBitRateDL = 104857600;		// 10 MB

	if( erabAction == RMU_DEL_ERAB )
	{
		ueRecfgReqInfo->stErabConfInfo.enErabAction = erabAction;
	    ueRecfgReqInfo->stErabConfInfo.bNoErabsToRel = 1;
	    ueRecfgReqInfo->stErabConfInfo.usNoErabsToAddMod = 0;

        ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "cause",  &(cause));

		ueRecfgReqInfo->stErabConfInfo.stErabRelLst[0].enErabRelCause = cause;
		ueRecfgReqInfo->stErabConfInfo.stErabRelLst[0].bErabId = erabId;
	}

	else
	{
		ueRecfgReqInfo->stErabConfInfo.enErabAction = erabAction;
	   ueRecfgReqInfo->stErabConfInfo.bNoErabsToRel = 0;
		ueRecfgReqInfo->stErabConfInfo.usNoErabsToAddMod = erabCount;	

		ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabPriority",  &(erabPriority));
		ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "erabPreemptCap",  &(erabPreemptCap));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "erabPreemptVul",  &(erabPreemptVul));
		ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabCount",  &(erabCount));

      for( i = 0; i< erabCount; i++)
      {
		   ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].stErabQosInfo.stErabArpInfo.bErabPrioLvl = erabPriority;
   		ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].stErabQosInfo.stErabArpInfo.bErabPreemptCap = erabPreemptCap;
   		ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].stErabQosInfo.stErabArpInfo.bErabPreemptVul = erabPreemptVul;
   		ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].bErabId = erabId+i;
      }

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "qciVal", &(qciVal));
      qciValTokMain = qciVal;
      for(qciValTokMain, i = 0; i < erabCount; i++, qciValTokMain=NULLP)
      {
         if ((qciValTokSub =(Txt *)strtok_r(qciValTokMain,":",&tok1)) == NULLP)
            break;

         erabQci = atoi(qciValTokSub);
         ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[i].stErabQosInfo.bErabQCI = erabQci;
      } 

		//ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPrioLvl = erabPriority;
		//ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPreemptCap = erabPreemptCap;
		//ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPreemptVul = erabPreemptVul;
		//ueRecfgReqInfo->stErabConfInfo.stErabAddModLst[0].bErabId = erabId;
	}
			

   /* Send the UeReconfig request to the RRM --*/
   if(CMXTA_ERR_NONE != WrLiRmuUeRecfgReq(&pst, suId, ueRecfgReqInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeErabRecfgReq(): Mapping returned FAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:   rmAcHdlRmuUeCapRecfgReq
*
*       Desc:  Call Handler for RMU UE Cap Reconfig Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeCapRecfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeCapRecfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
/*	SpId          spId;              service user SAP identifier 
	Bool          entity;
	S16           error;*/
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	
	U32			  transId;
	U16			  tCrnti;
/*	U16			  nCrnti;*/
	U8			  cellId;
	U32			  ueCategory;
	U32			  grpIndicator;
	U8			  recfgBitmap;

	RmuUeRecfgReq   *ueRecfgReqInfo;

	TRC2(rmAcHdlRmuUeCapRecfgReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeCapRecfgReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeCapRecfgReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;

	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTRMUUERECFGREQ;
		
	// Get the param values from XML

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "recfgBitmap",  &(recfgBitmap));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ueCategory",  &(ueCategory));
	  ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "grpIndicator",  &(grpIndicator));

	// Allocate the memory for RmuUeRecfgReq msg

	CMXTA_ALLOC(&ueRecfgReqInfo, sizeof(RmuUeRecfgReq));
	
   if(ueRecfgReqInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeCapRecfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

	//Fill the values recvd from xml

	ueRecfgReqInfo->bCellId = cellId;
	ueRecfgReqInfo->uiTransId = transId;
	ueRecfgReqInfo->usCrnti = tCrnti;
	ueRecfgReqInfo->bRecfgBitMap = recfgBitmap;
	ueRecfgReqInfo->stUeCapInfo.stEutraCapInfo.uiFeatureGrpIndicator = grpIndicator;
	ueRecfgReqInfo->stUeCapInfo.stEutraCapInfo.uiUeCategory = ueCategory;

   /* Send the UeReconfig request to the RRM --*/
   if(CMXTA_ERR_NONE != WrLiRmuUeRecfgReq(&pst, suId, ueRecfgReqInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeCapRecfgReq(): Mapping returned FAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:   rmAcHdlRmuUeCrntiRecfgReq
*
*       Desc:  Call Handler for RMU UE Crnti Reconfig Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeCrntiRecfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeCrntiRecfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
/*	SpId          spId;              service user SAP identifier 
	Bool          entity;
	S16           error;*/
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	
	U32			  transId;
	U16			  tCrnti;
	U16			  nCrnti;
	U8			  cellId;
	U8			  recfgBitmap;
   Bool       isMember = FALSE;

	RmuUeRecfgReq   *ueRecfgReqInfo;

	TRC2(rmAcHdlRmuUeCrntiRecfgReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeCrntiRecfgReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeCrntiRecfgReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;

	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTRMUUERECFGREQ;
		
	// Get the param values from XML

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "recfgBitmap",  &(recfgBitmap));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nCrnti",  &(nCrnti));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isMember",  &(isMember));

	// Allocate the memory for RmuUeRecfgReq msg

	CMXTA_ALLOC(&ueRecfgReqInfo, sizeof(RmuUeRecfgReq));
	
   if(ueRecfgReqInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeCrntiRecfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

	//Fill the values recvd from xml

	ueRecfgReqInfo->bCellId = cellId;
	ueRecfgReqInfo->uiTransId = transId;
	ueRecfgReqInfo->usCrnti = tCrnti;
	ueRecfgReqInfo->bRecfgBitMap = recfgBitmap;
	ueRecfgReqInfo->usUeNewCrnti = nCrnti;
	ueRecfgReqInfo->isMember  = isMember;

   /* Send the UeReconfig request to the RRM --*/
   if(CMXTA_ERR_NONE != WrLiRmuUeRecfgReq(&pst, suId, ueRecfgReqInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeCrntiRecfgReq(): Mapping returned FAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
	
}
#ifdef LTE_ADV
/*
*
*       Fun:   rmAcHdlRmuUeScellRecfgReq 
*
*       Desc:  Call Handler for RMU UE Scell Addtion Reconfig Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeScellRecfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeScellRecfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U32			  transId;
   U16			  tCrnti;
   U16			  nCrnti;
   U8			  cellId;
   U8			  recfgBitmap;

   RmuUeRecfgReq   *ueRecfgReqInfo;

   TRC2(rmAcHdlRmuUeScellRecfgReq);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeScellRecfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeScellRecfgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   suId = 0;

   /*-- Get the Pst information here from FSM to RRM --*/
   cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
         dstProcId, FALSE);

   pst.event   = EVTRMUUERECFGREQ;

   // Get the param values from XML

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "recfgBitmap",  &(recfgBitmap));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nCrnti",  &(nCrnti));

   // Allocate the memory for RmuUeRecfgReq msg

   CMXTA_ALLOC(&ueRecfgReqInfo, sizeof(RmuUeRecfgReq));

   if(ueRecfgReqInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeScellRecfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   //Fill the values recvd from xml

   ueRecfgReqInfo->bCellId = cellId;
   ueRecfgReqInfo->uiTransId = transId;
   ueRecfgReqInfo->usCrnti = tCrnti;
   ueRecfgReqInfo->bRecfgBitMap = recfgBitmap;
   ueRecfgReqInfo->usUeNewCrnti = nCrnti;

   U8 isScellPres = FALSE;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isScellPres",  &(isScellPres));
   if (isScellPres)
   {
      U8 sCellIdx = 1;
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sCellIdx",  &(sCellIdx));
      U8 sCellId = 1;
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sCellId",  &(sCellId));
      ueRecfgReqInfo->stSCellInfoReq.numOfScell = 1;
      ueRecfgReqInfo->stSCellInfoReq.sCellIInfo[0].action = RMU_SCELL_ADD;
      ueRecfgReqInfo->stSCellInfoReq.sCellIInfo[0].sCellIdx = sCellIdx;
      ueRecfgReqInfo->stSCellInfoReq.sCellIInfo[0].sCellId = sCellId;
   }
#if 0
   if ( ueRecfgReqInfo->bRecfgBitMap & RMU_RECFG_REQ_UE_CAP)
   {
      U8 ueCategory = 3;
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ueCategory",  &(ueCategory));
      ueRecfgReqInfo->stUeCapInfo.stEutraCapInfo.uiUeCategory = ueCategory;
   }
#endif
   /* Send the UeReconfig request to the RRM --*/
   if(CMXTA_ERR_NONE != WrLiRmuUeRecfgReq(&pst, suId, ueRecfgReqInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeScellRecfgReq(): Mapping returned FAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);

}
#endif

/*
*
*       Fun:   rmAcHdlRmuUeRecfgRsp
*
*       Desc:  Handler for Rmu UE recfg response 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeRecfgRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeRecfgRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	CmXtaMsgQElm    *msg = NULLP;
	RmAccMsgQElm    *rmMsg = NULLP;
	Pst              pst;
	S16              ret = 0;
	SuId             suId;
	ProcId           srcProcId;
	ProcId           dstProcId;
	RmuConEstCause   estCause;
	RmuUeRecfgRsp	 *recfgRspInfo;

	U8			  cellId = 0;	
	U16           tCrnti = 0;
	U32			  transId = 0;
	U32			 i;
	U8			  recfgBitmap;
	U8			  erabId;


	U8				retFlag = 0;
   U8          erabCount=1;

   U8          spsErabId;
   U16 status = RMU_SUCCESS; 


	TRC2(rmAcHdlRmuUeRecfgRsp);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRecfgRsp(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRecfgRsp(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;


	/*-- Get the data from XML --*/
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "status",  &(status));


   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rmMsg = (RmAccMsgQElm *)msg->data;
   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTRMUUERECFGRSP;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcHdlRmuUeRecfgRsp() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /* Compare the value in the message and the value provided from xml */	
   recfgRspInfo = (RmuUeRecfgRsp *)(rmMsg->u.rmuInfo.data);

   if(recfgRspInfo->bCellId != cellId && recfgRspInfo->usCrnti != tCrnti && recfgRspInfo->uiTransId != transId )
	{
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expCellId (%ld) rcvdCellId (%ld)"
                                  " expCrnti (%d) rcvdCrnti (%d) "
								  " expTransId (%d) rcvdTransId (%d) ",
                  cellId, recfgRspInfo->bCellId, tCrnti, recfgRspInfo->usCrnti, transId, recfgRspInfo->uiTransId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
	}

   if(recfgRspInfo->stStatusInfo.enStatus !=status )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expenStatus (%d) rcvdenStatus (%d)",
                  status,recfgRspInfo->stStatusInfo.enStatus), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);

   }
   if(recfgRspInfo->stStatusInfo.enStatus == RMU_SUCCESS)
   {
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "recfgBitmap",  &(recfgBitmap));

      if((recfgBitmap == recfgRspInfo->bRecfgBitMap))
      {
         if((recfgBitmap & RMU_RECFG_RSP_ERAB_CONFIG))
         {
            ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabCount",  &(erabCount));
            //Verify number of accepted bearers = 1
            if( recfgRspInfo-> bNoErabsAccepted == erabCount)
            {
               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabId",  &(erabId));

               //Verify number of accepted / modified / released bearers = 1
               if( recfgRspInfo-> bNoErabsAccepted != erabCount)
               {
                  CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): NoErabsAccepted exp (1) rcvd (%d)\n", 
                           recfgRspInfo-> bNoErabsAccepted));
                  retFlag = 1;
               }

               ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "spsErabId",  &(spsErabId));
               for(i=0; i<erabCount; i++)
               {   
                  //Verify the bearerId matches
                  if( erabId+i != recfgRspInfo-> stErabAcceptLst[i].bErabId)
                  {
                     CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): Mismatch in erabId exp (%d) rcvd (%d)\n", 
                              erabId+i, recfgRspInfo-> stErabAcceptLst[i].bErabId));
                     retFlag = 1;
                  }

                  if((recfgRspInfo->stErabAcceptLst[i].bIsDlSpsEnabled == TRUE) ||
                     (recfgRspInfo->stErabAcceptLst[i].bIsUlSpsEnabled == TRUE)) 
                  {
                     if(recfgRspInfo-> stErabAcceptLst[i].bErabId != spsErabId)
                     {
                        CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): Mismatch in SPS erabId exp (%d) rcvd (%d)\n", 
                                 spsErabId, recfgRspInfo-> stErabAcceptLst[i].bErabId));
                        retFlag = 1;
                     }

                  }
               }  

            }
            else
            {
               CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): Mismatch NoErabsAccepted exp (1) rcvd (%d)\n", 
                        recfgRspInfo-> bNoErabsAccepted));
               retFlag = 1;
            }

         }

         if((retFlag != 1) && (recfgBitmap & RMU_RECFG_RSP_ERAB_CONFIG))
         {
            retFlag = rmAcRmuhdlVldtRadRes(tcCb, spCb, & recfgRspInfo->stUeRadioResCfg);
         }
#ifdef LTE_ADV
         if((recfgBitmap & RMU_RECFG_REQ_SCELL_CONFIG))
         {
            U8    cqiResIdx = 0;
            U8    cqiCfgIdx = 0;
            U8    riCfgIdx  = 0;
            U8    riPres    = FALSE;
            U8    chkApcqi  = FALSE;
            U8    apcqiPres = FALSE;
            U32   acqiMode  = 0;
            
            
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cqiResIdx",  &(cqiResIdx));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cqiCfgIdx",  &(cqiCfgIdx));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "riPres",  &(riPres));
            if (recfgRspInfo->stUeSCellResCfg.sCellDedInfo[0].stCqiRepCfg.stPrdCqiRepCfg.usCqiResourceIndex != cqiResIdx) 
            {
                  CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): CQI Res Idx not matched exp (%d) rcvd (%d)\n", 
                           cqiResIdx,recfgRspInfo->stUeSCellResCfg.sCellDedInfo[0].stCqiRepCfg.stPrdCqiRepCfg.usCqiResourceIndex));
                  retFlag = 1;
            }  
            if (recfgRspInfo->stUeSCellResCfg.sCellDedInfo[0].stCqiRepCfg.stPrdCqiRepCfg.usCqiConfigIndex != cqiCfgIdx) 
            {
                  CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): CQI Cfg Idx not matched exp (%d) rcvd (%d)\n", 
                           cqiCfgIdx,recfgRspInfo->stUeSCellResCfg.sCellDedInfo[0].stCqiRepCfg.stPrdCqiRepCfg.usCqiConfigIndex));
                  retFlag = 1;
            }
            if (riPres)
            {  
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "riCfgIdx",  &(riCfgIdx));
               if ( recfgRspInfo->stUeSCellResCfg.sCellDedInfo[0].stCqiRepCfg.stPrdCqiRepCfg.riConfigIndex.usRiConfigIndex != riCfgIdx ) 
               {
                  CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): Ri Cfg Idx not Matched exp (%d) rcvd (%d)\n", 
                           riCfgIdx,recfgRspInfo->stUeSCellResCfg.sCellDedInfo[0].stCqiRepCfg.stPrdCqiRepCfg.riConfigIndex.usRiConfigIndex));
                  retFlag = 1;
               }
            } 
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "chkApcqi",  &(chkApcqi));
            if (chkApcqi)
            {
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "apcqiPres",  &(apcqiPres));
               if ( recfgRspInfo->stUeSCellResCfg.sCellDedInfo[0].stCqiRepCfg.stAPrdCqiRepCfg.enbld != apcqiPres) 
               {
                  CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): APCQI Present not Matched exp (%d) rcvd (%d)\n", 
                           apcqiPres,recfgRspInfo->stUeSCellResCfg.sCellDedInfo[0].stCqiRepCfg.stAPrdCqiRepCfg.enbld));
                  retFlag = 1;
               }
               if (apcqiPres)
               {
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "acqiMode",  &(acqiMode));
                  if ( recfgRspInfo->stUeSCellResCfg.sCellDedInfo[0].stCqiRepCfg.stAPrdCqiRepCfg.enPuschReportMode != acqiMode ) 
                  {
                     CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): APCQI Mode not Matched exp (%d) rcvd (%d)\n", 
                              acqiMode,recfgRspInfo->stUeSCellResCfg.sCellDedInfo[0].stCqiRepCfg.stAPrdCqiRepCfg.enPuschReportMode));
                     retFlag = 1;
                  }
               }
            } 
         }
#endif
      }
      else
      {
         CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): Mismatch Ue Recfg Bit Map exp (%d) rcvd (%d)\n", 
                  recfgBitmap, recfgRspInfo->bRecfgBitMap));
         retFlag = 1;
      }

   }
   else 
   {
      switch(recfgRspInfo->stStatusInfo.enCause)
      {
         case RMU_CAUSE_CELLID_UNKNOWN :
            CMXTA_DBG_INFO((_cmxtap, "ReleseReq faild : Unknown CellId"));
            break;
         case RMU_CAUSE_UEID_UNKNOWN :
            CMXTA_DBG_INFO((_cmxtap, "ReleseReq faild : Unknown UeId"));
            break;
         case RMU_CAUSE_OTHER:
            CMXTA_DBG_INFO((_cmxtap, "ReleseReq faild : Other"));
            break;
      }

   }


      /*-- free memory, use callback function --*/
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

      if(retFlag != 1)
      {
         RETVALUE(CMXTA_ERR_NONE);
      }
      else
      {
         RETVALUE(CMXTA_ERR_INT);
      }
   }


/*
*
*       Fun:   rmAcHdlRmuUeHoReq
*
*       Desc:  Call Handler for RMU UE HO Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeHoReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeHoReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
/*	SpId          spId;              service user SAP identifier 
	Bool          entity;
	S16           error;*/
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	
	U32			  transId;
	U16			  tCrnti;
	U8			  cellId;

	RmuErabAction  erabAction;
	U8			ambrPresent;
	U8			erabId;
	U8			erabPriority = 5;
	Bool		erabPreemptCap = TRUE;
	Bool		erabPreemptVul = TRUE;

	U32			ueCategory;
	U32			grpIndicator;

   U8         qciValue;
	
	RmuS1apCause	s1ApCause ;
   RmuHandOverType hoType;

   RmuPcqiFormatInd     cqiFormatIndex;
   RmuPucchReportMode      pucchReportMode;
   U16            cqiResourceIndex;
   U16            cqiConfigIndex;
   U16            riConfigIndex;
   U8          simulAckNackCqi;
   U8          phyCfgDedResBitMap;
   U8          radioResDedBitMap;

   RmuUeHoReq *ueHoReqInfo;
   RmuAccessStratumRls ueAccessStratumRls;
   /* HCSG DEV */
   U8                        isEmrgncyBrersPsnt = 0;
   U8                        isMember = 0;

	TRC2(rmAcHdlRmuUeHoReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeHoReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeHoReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;

	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	 pst.event = EVTRMUUEHOREQ;
		
	// Get the param values from XML

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "s1ApCause",  &(s1ApCause));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "hoType",  &(hoType));

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "erabAction",  &(erabAction));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ambrPresent",  &(ambrPresent));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabId",  &(erabId));

	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "qciValue",  &(qciValue));

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ueCategory",  &(ueCategory));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "grpIndicator",  &(grpIndicator));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "eUeAccessStratumRls",  &(ueAccessStratumRls));
      /* HCSG DEV */
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isEmrgncyBrersPsnt",  &(isEmrgncyBrersPsnt));
	   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "isMember",  &(isMember));


	// Allocate the memory for RmuUeRecfgReq msg

	CMXTA_ALLOC(&ueHoReqInfo, sizeof(RmuUeHoReq));
	
   if(ueHoReqInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeHoReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

	//Fill the values recvd from xml
   /* HCSG DEV */
   ueHoReqInfo->isEmrgncyBrersPsnt = isEmrgncyBrersPsnt;
   ueHoReqInfo->isMember = isMember;

	//Fill ERAB configurations
	ueHoReqInfo->bCellId = cellId;
	ueHoReqInfo->uiTransId = transId;
	ueHoReqInfo->usCrnti = tCrnti;

   ueHoReqInfo->enHoS1apCause = s1ApCause;
   ueHoReqInfo->enHoType = hoType;

   //Fill UE ERAB Config
	ueHoReqInfo->stErabConfInfo.bIsUeAmbrPres	= ambrPresent;
	ueHoReqInfo->stErabConfInfo.stUeAmbrInfo.uiAggUEMaxBitRateUL = 104857600;		// 10 MB
	ueHoReqInfo->stErabConfInfo.stUeAmbrInfo.uiAggUEMaxBitRateDL = 104857600;		// 10 MB

	ueHoReqInfo->stErabConfInfo.enErabAction = erabAction;
   ueHoReqInfo->stErabConfInfo.bNoErabsToRel = 0;
	ueHoReqInfo->stErabConfInfo.usNoErabsToAddMod = 2;	

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabPriority",  &(erabPriority));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "erabPreemptCap",  &(erabPreemptCap));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "erabPreemptVul",  &(erabPreemptVul));

	ueHoReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPrioLvl = erabPriority;
	ueHoReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPreemptCap = erabPreemptCap;
	ueHoReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPreemptVul = erabPreemptVul;
   ueHoReqInfo->stErabConfInfo.stErabAddModLst[0].stErabQosInfo.bErabQCI = qciValue;
	ueHoReqInfo->stErabConfInfo.stErabAddModLst[0].bErabId = erabId;

	ueHoReqInfo->stErabConfInfo.stErabAddModLst[1].stErabQosInfo.stErabArpInfo.bErabPrioLvl = erabPriority;
	ueHoReqInfo->stErabConfInfo.stErabAddModLst[1].stErabQosInfo.stErabArpInfo.bErabPreemptCap = erabPreemptCap;
	ueHoReqInfo->stErabConfInfo.stErabAddModLst[1].stErabQosInfo.stErabArpInfo.bErabPreemptVul = erabPreemptVul;
   ueHoReqInfo->stErabConfInfo.stErabAddModLst[1].stErabQosInfo.bErabQCI = qciValue+1;
	ueHoReqInfo->stErabConfInfo.stErabAddModLst[1].bErabId = erabId+1;


	//Fill UE cap config
	ueHoReqInfo->stUeCapInfo.stEutraCapInfo.uiUeCategory = ueCategory;
   ueHoReqInfo->stUeCapInfo.stEutraCapInfo.uiFeatureGrpIndicator = grpIndicator;
	ueHoReqInfo->stUeCapInfo.stEutraCapInfo.uiUeAccessStratumRls = ueAccessStratumRls;

   //Fill UE Radio resourse config
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "phyCfgDedResBitMap",  &(phyCfgDedResBitMap));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "radioResDedBitMap",  &(radioResDedBitMap));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "CqiFormatIndex",  &(cqiFormatIndex));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "PucchReportMode",  &(pucchReportMode));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CqiResourceIndex",  &(cqiResourceIndex));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "CqiConfigIndex",  &(cqiConfigIndex));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "RiConfigIndex",  &(riConfigIndex));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "SimulAckNackCqi",  &(simulAckNackCqi));
   
   ueHoReqInfo->stUeRadioResCfg.bRadioResDedBitMap = radioResDedBitMap;
   ueHoReqInfo->stUeRadioResCfg.stPhyCfgDed.bPhyCfgDedResBitMap = phyCfgDedResBitMap;
   ueHoReqInfo->stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.enCqiFormatInd = cqiFormatIndex;
   ueHoReqInfo->stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.enPucchReportMode = pucchReportMode;
   ueHoReqInfo->stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.usCqiResourceIndex = cqiResourceIndex;
   ueHoReqInfo->stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.usCqiConfigIndex = cqiConfigIndex;
   ueHoReqInfo->stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.riConfigIndex.usRiConfigIndex = riConfigIndex;
   ueHoReqInfo->stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.bFactorK = 0;
   ueHoReqInfo->stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.bSimulAckNackCqi = simulAckNackCqi;

   /* Send the Ue HO request to the RRM --*/
   if(CMXTA_ERR_NONE != WrLiRmuUeHoReq(&pst, suId, ueHoReqInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuUeHoReq(): Mapping returned FAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:  rmAcHdlRmuUeHoRsp 
*
*       Desc:  Handler for Rmu UE HO response 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 rmAcHdlRmuUeHoRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuUeHoRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm    *msg = NULLP;
   RmAccMsgQElm    *rmMsg = NULLP;
   Pst              pst;
   S16              ret = 0;
   /*	SuId             suId;*/
   ProcId           srcProcId;
   ProcId           dstProcId;
   /*	RmuConEstCause   estCause;*/
   RmuUeHoRsp       *hoRspInfo;

   U8			   cellId = 0;	
   U16         tCrnti = 0;
   U32			transId = 0;
   U8			   erabId = 0;
   U8          spsErabId;
   U8				retFlag = 0;

   U8          i = 0;
   U8          status = RMU_SUCCESS;
   U8          erabCount = 2;

   TRC2(rmAcHdlRmuUeHoRsp);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeHoRsp(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeHoRsp(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;


   /*-- Get the data from XML --*/
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "status",  &(status));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(transId));


   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlRmuUeHoRsp(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rmMsg = (RmAccMsgQElm *)msg->data;
   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
         dstProcId, FALSE);

   pst.event = EVTRMUUEHORSP;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcHdlRmuUeHoRsp() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /* Compare the value in the message and the value provided from xml */	
   hoRspInfo = (RmuUeHoRsp *)(rmMsg->u.rmuInfo.data);

   if(hoRspInfo->bCellId != cellId && hoRspInfo->usCrnti != tCrnti && hoRspInfo->uiTransId != transId )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expCellId (%ld) rcvdCellId (%ld)"
               " expCrnti (%d) rcvdCrnti (%d) "
               " expTransId (%d) rcvdTransId (%d) ",
               cellId, hoRspInfo->bCellId, tCrnti, hoRspInfo->usCrnti, transId, hoRspInfo->uiTransId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   //Validate the Response Status to the expectyed value
   if(hoRspInfo->stStatusInfo.enStatus != status)
   {
      CMXTA_DBG_INFO((_cmxtap,"rmAcHdlRmuUeAdmitRsp(): Mismatch in Admit Response Status exp (%d) rcvd(%d) \n", 
               status, hoRspInfo->stStatusInfo.enStatus));
      retFlag = 1;
   }


   if( hoRspInfo->stStatusInfo.enStatus == RMU_SUCCESS )
   {

      //Verify number of Admitted bearers
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabCount",  &(erabCount));
      if( hoRspInfo-> bNoErabsAdmitted == erabCount)
      {
         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabId",  &(erabId));

         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "spsErabId",  &(spsErabId));
         //Verify number of accepted bearers 
         for(i=0; i<erabCount; i++)
         {   
            //Verify the bearerId matches
            if( erabId+i != hoRspInfo->stErabAdmitLst[i].bErabId)
            {
               CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeHoRsp(): Mismatch in erabId exp (%d) rcvd (%d)\n", 
                        erabId+i, hoRspInfo-> stErabAdmitLst[i].bErabId));
               retFlag = 1;
            }

            if((hoRspInfo->stErabAdmitLst[i].bIsDlSpsEnabled == TRUE) ||
               (hoRspInfo->stErabAdmitLst[i].bIsUlSpsEnabled == TRUE)) 
            {
               if(hoRspInfo-> stErabAdmitLst[i].bErabId != spsErabId)
               {
                  CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): Mismatch in SPS erabId exp (%d) rcvd (%d)\n", 
                           spsErabId, hoRspInfo-> stErabAdmitLst[i].bErabId));
                  retFlag = 1;
               }

            } 
         }  
      }
      else
      {
         CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuUeHoRsp(): Mismatch NoErabsAccepted exp (1) rcvd (%d)\n", 
                  hoRspInfo-> bNoErabsAdmitted));
         retFlag = 1;
      }

      //Verify number of Admitted bearers
      U8 erabRejectCount = 0;

      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabRejectCount",  &(erabRejectCount));
      //Verify number of Rejected bearers 
      if( hoRspInfo-> bNoErabsRejected == erabRejectCount)
      {
         //Verify the bearerId matches
         U8 erabIdx;
         U8 erabIdReject;

         ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "erabIdReject",  &(erabIdReject));

         for(erabIdx = 0; erabIdx < hoRspInfo-> bNoErabsRejected; erabIdx++)
         {
            if (erabIdReject+erabIdx   == hoRspInfo->stErabRejectLst[erabIdx].bErabId)
            {
               printf("\n Rejected ERAB#%d", hoRspInfo->stErabRejectLst[erabIdx].bErabId);
            }
            else
            {
               CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeHoRsp(): Mismatch in erabId Not in  Reject List (%d) rcvd (%d)\n", 
                        erabId+i, hoRspInfo->stErabRejectLst[i].bErabId));
               retFlag = 1;
            }
         }

      }
      else
      {
         CMXTA_DBG_INFO((_cmxtap, "rmAcHdlRmuUeRecfgRsp(): NoErabsRejected exp (%d) rcvd (%d)\n", 
                  erabRejectCount, hoRspInfo-> bNoErabsRejected));
         retFlag = 1;
      }

      if(retFlag != 1)
      {
         retFlag = rmAcRmuhdlVldtRadRes(tcCb, spCb, & hoRspInfo->stUeRadioResCfg);
      }
   }
   else
   {
      printf("\n\nrmAcHdlRmuUeHoRsp() :  Cause = %d \n\n", hoRspInfo->stStatusInfo.enCause);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

   if(retFlag != 1)
   {
      RETVALUE(CMXTA_ERR_NONE);
   }
   else
   {
      RETVALUE(CMXTA_ERR_INT);
   }
}


/*utility function begins*/

#ifdef ANSI
PUBLIC S16 rmAcUtlRmuFreeCb
(
CmXtaMsgQElm    *qElm
)
#else
PUBLIC S16 rmAcUtlRmuFreeCb(qElm)
CmXtaMsgQElm   *qElm;
#endif
{
   RmAccMsgQElm *rmMsg;

   TRC2(rmAcUtlRmuFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "rmAcUtlRmuFreeCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   rmMsg = (RmAccMsgQElm *)qElm->data;

   if(rmMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   if (rmMsg != NULLP)
   {
      if(rmMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(rmMsg->mBuf);
      if(rmMsg->u.rmuInfo.data != NULLP)
      {
         WRAC_RMUFREEBUF(rmMsg->u.rmuInfo.data, rmMsg->u.rmuInfo.len);
      }
      CMXTA_FREE(rmMsg, sizeof (RmAccMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   rmAcHdlRmuSpsDisInd
*
*       Desc:  Call Handler for RMU SPS Disable Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_rmuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlRmuSpsDisInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlRmuSpsDisInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	SuId          suId;             /* service user SAP identifier */
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	
	U16			  tCrnti;
	U8  			  cellId;

   RmuUeSpsDisInd   *ueSpsDisInd;

	TRC2(rmAcHdlRmuSpsDisInd);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuSpsDisInd(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlRmuSpsDisInd(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

    suId = 0;

	/*-- Get the Pst information here from FSM to RRM --*/
    cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTRMUUESPSDISIND;
		
	CMXTA_ALLOC(&ueSpsDisInd, sizeof(RmuUeSpsDisInd));
	
   if(ueSpsDisInd == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlRmuSpsDisInd(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

	// Get the param values from XML

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tCrnti",  &(tCrnti));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));

   ueSpsDisInd->cellId = cellId;
   ueSpsDisInd->usCrnti = tCrnti;

   /* Send the UeReconfig request to the RRM --*/
   if(CMXTA_ERR_NONE != WrLiRmuUeSpsDisInd(&pst, suId, ueSpsDisInd))
   {
      CMXTA_DBG_ERR((_cmxtap,"WrLiRmuUeSpsDisInd(): Mapping returned FAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);

}
/*utility function ends*/
