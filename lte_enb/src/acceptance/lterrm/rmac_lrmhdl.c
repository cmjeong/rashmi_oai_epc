

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_rmuhdl.c

     Sid:      rmac_lrmhdl.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 18:22:29 2013

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
//#include "wrac_acc.h"
#include "rm.h"
#include <stdlib.h>        /* For atoi function */
#include <string.h>        /* for strlen */
#include "lrm.h"
#include "rmu.h"
#include "rgm.h"
#include "rmac_acc.h"
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
#include "rmac_lrm.x"

/*
*
*       Fun:   rmAcHdlLrmCpuLoadInd
*
*       Desc:  Call Handler for LRU CPU load Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmCpuLoadInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmCpuLoadInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{

	Pst           pst;
	//SuId          suId;             /* service user SAP identifier */
	//SpId          spId;             /* service user SAP identifier */
	//Bool          entity;
	//S16           error;
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	U8	           cpuLoad = 0;	
   RmMngmt     *enbStatusInfo;
   U8          coupling=LRM_SEL_LWLC;

	TRC2(rmAcHdlLrmCpuLoadInd);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCpuLoadInd(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCpuLoadInd(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from SM to RRM --*/
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTLRMENBSTAIND;
   pst.selector = coupling;

	//Get the CPU load from XML

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cpuLoad",  &(cpuLoad));

	if(ret == CMXTA_ERR_NO_VALUE)
    	{
       		CMXTA_DBG_INFO((_cmxtap,"rmAcHdlLrmCpuLoadInd(): default cpuLoad %d\n", cpuLoad));
    	}

	// Allocate the memory for MmeOvldStartInd msg

	CMXTA_ALLOC(&enbStatusInfo, sizeof(RmMngmt));

   if(enbStatusInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmCpuLoadInd(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

	enbStatusInfo->t.usta.bStaType = 1;
	enbStatusInfo->t.usta.u.stEnbStaInfo.enStaType = LRM_ENBSTATYPE_CPULOAD;
	enbStatusInfo->t.usta.u.stEnbStaInfo.u.bCpuLoad = cpuLoad;

  /* Send the indication to the RRM --*/
   if(CMXTA_ERR_NONE != RmMiLrmEnbStaInd(&pst, enbStatusInfo))
    {
       CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmCpuLoadInd(): Mapping returned FAILED\n"));
    }

    RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   rmAcHdlLrmCellUpInd
*
*       Desc:  Call Handler for LRM Cell Up Indication 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmCellUpInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmCellUpInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{

	Pst           pst;
	//SuId          suId;             /* service user SAP identifier */
	//SpId          spId;             /* service user SAP identifier */
	//Bool          entity;
	//S16           error;
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	U8	           cellId = 0;	
   RmMngmt     *enbStatusInfo;
   U8          coupling=LRM_SEL_LWLC;

	TRC2(rmAcHdlLrmCellUpInd);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCellUpInd(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCellUpInd(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from SM to RRM --*/
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTLRMENBSTAIND;
   pst.selector = coupling;

	//Get the CPU load from XML

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));

	if(ret == CMXTA_ERR_NO_VALUE)
    	{
       		CMXTA_DBG_INFO((_cmxtap,"rmAcHdlLrmCellUpInd(): default cpuLoad %d\n", cellId));
    	}

	// Allocate the memory for MmeOvldStartInd msg

	CMXTA_ALLOC(&enbStatusInfo, sizeof(RmMngmt));

   if(enbStatusInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmCellUpInd(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

	enbStatusInfo->t.usta.bStaType = 0;
	enbStatusInfo->t.usta.u.stEnbStaInfo.enStaType = LRM_ENBSTATYPE_CELLUP;
	enbStatusInfo->t.usta.u.stEnbStaInfo.u.bCellId= cellId;

  /* Send the indication to the RRM --*/
   if(CMXTA_ERR_NONE != RmMiLrmEnbStaInd(&pst, enbStatusInfo))
    {
       CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmCellUpInd(): Mapping returned FAILED\n"));
    }

    RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:   rmAcHdlLrmGenCfgReq
*
*       Desc:  Call Handler for LRM Generic config request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmGenCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmGenCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	//SuId          suId;             /* service user SAP identifier */
	//SpId          spId;             /* service user SAP identifier */
	//Bool          entity;
	//S16           error;
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	RmMngmt		*cfgReq;

   U8          coupling=LRM_SEL_LWLC;
   U8          rspCoupling= LRM_SEL_LWLC;

	TRC2(rmAcHdlLrmGenCfgReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmGenCfgReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmGenCfgReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from SM to RRM --*/
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTLRMCFGREQ;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));
   pst.selector = coupling; 
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rspCoupling", &(rspCoupling));
	// Allocate the memory for RmMngmt msg

	CMXTA_ALLOC(&cfgReq, sizeof(RmMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmGenCfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into cfgReq
	
	//Fill the header fields
	cfgReq->hdr.msgType				= TCFG;
	cfgReq->hdr.msgLen              = 0;
	cfgReq->hdr.entId.ent           = ENTRM;
	//cfgReq->hdr.entId.inst          = RM_INST_ZERO;
	cfgReq->hdr.entId.inst          = 0;
	cfgReq->hdr.elmId.elmnt         = STRMGEN;

   if(rspCoupling == LRM_SEL_TC)
	   cfgReq->hdr.response.selector   = LRM_SEL_TC;
   else if(rspCoupling == LRM_SEL_LWLC)
   	cfgReq->hdr.response.selector   = LRM_SEL_LWLC;

	// Fill the configuration parameters for RRM General Configuration. */
	//cfgReq->t.cfg.s.genCfg.lmPst.srcProcId = RM_SM_PROC;
	//cfgReq->t.cfg.s.genCfg.lmPst.dstProcId = RM_RM_PROC;

	cfgReq->t.cfg.s.genCfg.lmPst.srcProcId = CMXTA_DFLT_PROCID;
	cfgReq->t.cfg.s.genCfg.lmPst.dstProcId = CMXTA_DFLT_PROCID;
	//cfgReq->t.cfg.s.genCfg.lmPst.srcEnt = (Ent)ENTSM;
	//cfgReq->t.cfg.s.genCfg.lmPst.dstEnt = (Ent)ENTRM;
   
	cfgReq->t.cfg.s.genCfg.lmPst.srcEnt = (Ent)ENTRM;
	cfgReq->t.cfg.s.genCfg.lmPst.dstEnt = (Ent)ENTSM;

	cfgReq->t.cfg.s.genCfg.lmPst.srcInst = (Inst)0;
	cfgReq->t.cfg.s.genCfg.lmPst.dstInst = (Inst)0;
	cfgReq->t.cfg.s.genCfg.lmPst.prior = (Prior)0;
	cfgReq->t.cfg.s.genCfg.lmPst.route = (Route)RTESPEC;
	cfgReq->t.cfg.s.genCfg.lmPst.event = (Event)EVTNONE;
	cfgReq->t.cfg.s.genCfg.lmPst.region =  DFLT_REGION;
	//cfgReq->t.cfg.s.genCfg.lmPst.pool   =  RM_MEM_POOL;
	cfgReq->t.cfg.s.genCfg.lmPst.pool   =  0;
   if(coupling == LRM_SEL_TC)
   	cfgReq->t.cfg.s.genCfg.lmPst.selector = LRM_SEL_TC;
   else if (coupling == LRM_SEL_LWLC)
   	cfgReq->t.cfg.s.genCfg.lmPst.selector = LRM_SEL_LWLC;

	cfgReq->t.cfg.s.genCfg.mem.region = DFLT_REGION;
	cfgReq->t.cfg.s.genCfg.mem.pool   = 0;
	cfgReq->t.cfg.s.genCfg.maxRmuSaps = 2;

	cfgReq->t.cfg.s.genCfg.tmrRes = 1;

	/* Send the msg to the RRM --*/

   if(coupling == LRM_SEL_TC)
   {   
   	if(CMXTA_ERR_NONE != RmMiLrmCfgReq(&pst, cfgReq))
          {
              CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmGenCfgReq(): Mapping returned FAILED\n"));
          }
   }
   else if(coupling == LRM_SEL_LWLC)
   {   
      if(CMXTA_ERR_NONE != cmPkLwLcLrmCfgReq(&pst, cfgReq))
         {
            CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmGenCfgReq(): Mapping returned FAILED\n"));
         }
   }
    
   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   rmAcHdlLrmGenCfgCfm
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
PUBLIC S16 rmAcHdlLrmGenCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmGenCfgCfm(tcCb, spCb)
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

   U16       status = LCM_PRIM_OK;
   U16       reason = LCM_REASON_NOT_APPL;
   RmMngmt		*cfgCfm = NULLP;

   TRC2(rmAcHdlLrmGenCfgCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmGenCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmGenCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlLrmGenCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rmMsg = (RmAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "status",  &(status));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "reason",  &(reason));

   pst.event = EVTLRMCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);
   rmMsg = (RmAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (RmMngmt *)(rmMsg->u.lrmInfo.data);

	if(cfgCfm->cfm.status != status && cfgCfm->cfm.reason != reason )
	{
      		CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
                  status, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      		RETVALUE(CMXTA_ERR_INT);
	}

   RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   rmAcHdlLrmSapCfgReq
*
*       Desc:  Call Handler for LRM SAP config request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmSapCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmSapCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	//SuId          suId;             /* service user SAP identifier */
	//SpId          spId;             /* service user SAP identifier */
	//Bool          entity;
	//S16           error;
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	RmMngmt		*cfgReq;
   U8          coupling = LRM_SEL_LWLC;

	TRC2(rmAcHdlLrmSapCfgReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmSapCfgReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmSapCfgReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from SM to RRM --*/
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTLRMCFGREQ;


   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));

	// Allocate the memory for RmMngmt msg

	CMXTA_ALLOC(&cfgReq, sizeof(RmMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmSapCfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into cfgReq
	
	//Fill the header fields
	cfgReq->hdr.msgType				= TCFG;
	cfgReq->hdr.msgLen              = 0;
	cfgReq->hdr.entId.ent           = ENTRM;
	cfgReq->hdr.entId.inst          = RM_INST_ID;
	cfgReq->hdr.elmId.elmnt         = STRMUSAP;

   if(coupling == LRM_SEL_TC)
	  cfgReq->hdr.response.selector   = LRM_SEL_TC;
   else if(coupling == LRM_SEL_LWLC)
     cfgReq->hdr.response.selector   = LRM_SEL_LWLC;   

	cfgReq->t.cfg.s.rmuSap.spId	 = WR_RM_SPID;
	cfgReq->t.cfg.s.rmuSap.suId 	 = WR_RM_SUID;
	cfgReq->t.cfg.s.rmuSap.procId      = SM_RM_PROC;
	cfgReq->t.cfg.s.rmuSap.prior       = PRIOR0;
	cfgReq->t.cfg.s.rmuSap.route       = RTESPEC;

   if(coupling == LRM_SEL_TC)
   	cfgReq->t.cfg.s.rmuSap.selector    = RMU_SEL_TC;
   else if (coupling == LRM_SEL_LWLC)
      cfgReq->t.cfg.s.rmuSap.selector    = RMU_SEL_LWLC;

	cfgReq->t.cfg.s.rmuSap.ent         = ENTWR;
	cfgReq->t.cfg.s.rmuSap.inst        = 0;
	cfgReq->t.cfg.s.rmuSap.mem.pool    = 0;
	cfgReq->t.cfg.s.rmuSap.mem.region  = DFLT_REGION;

	/* Send the msg to the RRM --*/

   if(coupling == LRM_SEL_TC)
   {   
	     if(CMXTA_ERR_NONE != RmMiLrmCfgReq(&pst, cfgReq))
         {
            CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmSapCfgReq(): Mapping returned FAILED\n"));
         }
   }

   if(coupling == LRM_SEL_LWLC)
   {
      if(CMXTA_ERR_NONE != cmPkLwLcLrmCfgReq(&pst, cfgReq))
        {
             CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmGenCfgReq(): Mapping returned FAILED\n"));
        }
   }   

    RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:   rmAcHdlLrmSapCfgReqRgm
*
*       Desc:  Call Handler for LRM SAP config request for RGM interface
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmSapCfgReqRgm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmSapCfgReqRgm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	//SuId          suId;             /* service user SAP identifier */
	//SpId          spId;             /* service user SAP identifier */
	//Bool          entity;
	//S16           error;
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	RmMngmt		*cfgReq;
   U8          coupling = LRM_SEL_LWLC;

	TRC2(rmAcHdlLrmSapCfgReqRgm);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmSapCfgReqRgm(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmSapCfgReqRgm(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from SM to RRM --*/
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTLRMCFGREQ;


   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));

	// Allocate the memory for RmMngmt msg

	CMXTA_ALLOC(&cfgReq, sizeof(RmMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmSapCfgReqRgm(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into cfgReq
	
	//Fill the header fields
	cfgReq->hdr.msgType				= TCFG;
	cfgReq->hdr.msgLen              = 0;
	cfgReq->hdr.entId.ent           = ENTRM;
	cfgReq->hdr.entId.inst          = RM_INST_ID;
	cfgReq->hdr.elmId.elmnt         = STRGMSAP;

   if(coupling == LRM_SEL_TC)
	  cfgReq->hdr.response.selector   = LRM_SEL_TC;
   else if(coupling == LRM_SEL_LWLC)
     cfgReq->hdr.response.selector   = LRM_SEL_LWLC;   

   cfgReq->t.cntrl.action =   ABND;

	cfgReq->t.cfg.s.rgmSap.spId	 = RG_RM_SPID;
	cfgReq->t.cfg.s.rgmSap.suId 	 = RG_RM_SUID;
	cfgReq->t.cfg.s.rgmSap.procId      = RG_RM_PROC;
	cfgReq->t.cfg.s.rgmSap.prior       = PRIOR0;
	cfgReq->t.cfg.s.rgmSap.route       = RTESPEC;

   if(coupling == LRM_SEL_TC)
   	cfgReq->t.cfg.s.rgmSap.selector    = RGM_SEL_TC;
   else if (coupling == LRM_SEL_LWLC)
      cfgReq->t.cfg.s.rgmSap.selector    = RGM_SEL_LWLC;

	cfgReq->t.cfg.s.rgmSap.ent         = ENTRG;
	cfgReq->t.cfg.s.rgmSap.inst        = 0;
	cfgReq->t.cfg.s.rgmSap.mem.pool    = 0;
	cfgReq->t.cfg.s.rgmSap.mem.region  = DFLT_REGION;

	/* Send the msg to the RRM --*/

   if(coupling == LRM_SEL_TC)
   {   
	     if(CMXTA_ERR_NONE != RmMiLrmCfgReq(&pst, cfgReq))
         {
            CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmSapCfgReqRgm(): Mapping returned FAILED\n"));
         }
   }

   if(coupling == LRM_SEL_LWLC)
   {
      if(CMXTA_ERR_NONE != cmPkLwLcLrmCfgReq(&pst, cfgReq))
        {
             CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmSapCfgReqRgm(): Mapping returned FAILED\n"));
        }
   }   

    RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   rmAcHdlLrmCtrlReq
*
*       Desc:  Call Handler for LRM SAP config request for RGM interface
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmCtrlReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmCtrlReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	//SuId          suId;             /* service user SAP identifier */
	//SpId          spId;             /* service user SAP identifier */
	//Bool          entity;
	//S16           error;
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	RmMngmt		*cfgReq;
   U8          coupling = LRM_SEL_LWLC;
   U8          rspCoupling = LRM_SEL_LWLC;
   U8          choice = 1;

	TRC2(rmAcHdlLrmCtrlReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCtrlReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCtrlReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from SM to RRM --*/
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTLRMCNTRLREQ;


   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "choice", &(choice));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rspCoupling", &(rspCoupling));
   pst.selector = coupling;
	// Allocate the memory for RmMngmt msg

	CMXTA_ALLOC(&cfgReq, sizeof(RmMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmCtrlReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into cfgReq
	
	//Fill the header fields
	cfgReq->hdr.msgType				= TCFG;
	cfgReq->hdr.msgLen              = 0;
	cfgReq->hdr.entId.ent           = ENTRM;
	cfgReq->hdr.entId.inst          = RM_INST_ID;

    if(choice == 1)
	cfgReq->hdr.elmId.elmnt         = STRGMSAP;
    else
    	cfgReq->hdr.elmId.elmnt         = STRMGEN;

   if(rspCoupling == LRM_SEL_TC)
	  cfgReq->hdr.response.selector   = LRM_SEL_TC;
   else if(rspCoupling == LRM_SEL_LWLC)
     cfgReq->hdr.response.selector   = LRM_SEL_LWLC;   

   if( choice == 1)
   cfgReq->t.cntrl.action            = ABND;                       
   else
       cfgReq->t.cntrl.action            = LRM_RESET_CFG;                       

	/* Send the msg to the RRM --*/

   if(coupling == LRM_SEL_TC)
   {   
	     if(CMXTA_ERR_NONE != RmMiLrmCntrlReq(&pst, cfgReq))
         {
            CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmCtrlReq(): Mapping returned FAILED\n"));
         }
   }

   if(coupling == LRM_SEL_LWLC)
   {
      if(CMXTA_ERR_NONE != cmPkLwLcLrmCntrlReq(&pst, cfgReq))
        {
             CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmCtrlReq(): Mapping returned FAILED\n"));
        }
   }   

    RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   rmAcHdlLrmCtrlCfm
*
*       Desc:  Call Handler for LRM Ctrl Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmCtrlCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmCtrlCfm (tcCb, spCb)
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

   U16       status = LCM_PRIM_OK;
   U16       reason = LCM_REASON_NOT_APPL;
   RmMngmt		*cfgCfm;

   TRC2(rmAcHdlLrmCtrlCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCtrlCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCtrlCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlLrmCtrlCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rmMsg = (RmAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "status",  &(status));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "reason",  &(reason));

  // cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
  //                dstProcId, FALSE);

   pst.event = EVTLRMCNTRLCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

	rmMsg = (RmAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (RmMngmt *)(rmMsg->u.lrmInfo.data);

   if(cfgCfm->cfm.status == LCM_PRIM_OK_NDONE && cfgCfm->cfm.reason == LCM_REASON_NOT_APPL)
       RETVALUE(CMXTA_ERR_NONE);


	if(cfgCfm->cfm.status != status && cfgCfm->cfm.reason != reason )
	{
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
                  status, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      RETVALUE(CMXTA_ERR_INT);

	}

   /*-- free memory, use callback function --*/
   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   rmAcHdlLrmSapCfgCfm
*
*       Desc:  Call Handler for LRM SAP config Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmSapCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmSapCfgCfm(tcCb, spCb)
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
   RmMngmt		*cfgCfm;

   TRC2(rmAcHdlLrmSapCfgCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmSapCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmSapCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlLrmSapCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rmMsg = (RmAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLRMCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

	rmMsg = (RmAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (RmMngmt *)(rmMsg->u.lrmInfo.data);

	if(cfgCfm->cfm.status != retVal && cfgCfm->cfm.reason != reason )
	{
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
                  retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      RETVALUE(CMXTA_ERR_INT);

	}

   /*-- free memory, use callback function --*/
   RETVALUE(CMXTA_ERR_NONE);

}


/*
*	
*       Fun:   rmAcHdlLrmCellCfgCfm
*
*       Desc:  Call Handler for LRM Cell config Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmCellCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmCellCfgCfm(tcCb, spCb)
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

   U16       status = LCM_PRIM_OK;
   U16       reason = LCM_REASON_NOT_APPL;
   RmMngmt		*cfgCfm = NULL;

   TRC2(rmAcHdlLrmCellCfgCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCellCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCellCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlLrmCellCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "status",  &(status));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "reason",  &(reason));

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   rmMsg = (RmAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLRMCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);
   rmMsg = (RmAccMsgQElm *)msg->data;
   /* Compare the value in the message and the value provided from xml */

   rmMsg = (RmAccMsgQElm *)msg->data;
   cfgCfm = (RmMngmt *)(rmMsg->u.lrmInfo.data);

	if(cfgCfm->cfm.status != status && cfgCfm->cfm.reason != reason )
	{
      		CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
                	  status, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);
      		RETVALUE(CMXTA_ERR_INT);

	}

   /*-- free memory, use callback function --*/
 //  cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);	
   RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:   rmAcHdlLrmCellCfgReq
*
*       Desc:  Call Handler for LRM Cell config request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmCellCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmCellCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
	Pst           pst;
	//SuId          suId;             /* service user SAP identifier */
	//SpId          spId;             /* service user SAP identifier */
	//Bool          entity;
	//S16           error;
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	RmMngmt		*cfgReq;

	LrmCellBandwidth cellBandwidth;
	LrmCfgType       cfgType;
   LrmSrPrdcty       enSrPrdcty = 0;        
   LrmCqiPrdcty      enCqiPrdcty = 0;
   CmRrmDsrTransMax  enDsrTransMax;
	U8		action;
	U16	maxUlBandwidth;
	U16	maxDlBandwidth;
	U8		bNrbCqi;
	U8		bNcsAn;
	U8	   maxActiveUes;
   
   U8    dataAcbSpac;
   CmRrmAcBarringFactor dataAcbFactor;
   CmRrmAcBarringTime   dataAcbTime=0;
   U8    sigAcbSpac;
   CmRrmAcBarringFactor sigAcbFactor;
   CmRrmAcBarringTime   sigAcbTime=0;
   
   /* HCSG_DEV */
	U8	   maxCsgUes;
	U8	   maxNonCsgUes;
	U8	   maxExtraUes = 2;
	U8		maxSigUes;
	U8		dlfs;
	U8		waitTime;
	U8		acbForEmergency;
	U8		acbForSplClass;
	U8		cellId;
	U8 	rcmAlgoType;
	U8    numTxAnt;
   U8    coupling = LRM_SEL_LWLC;

   Bool  drxEnabled = FALSE;
   U8    drxOnDurTimer;
   U8    drxRetxTimer;
   Bool  bSimulAckNack = TRUE;
   U16   drxInactTimer;
   U16               usNumSrResPerTti = 0;
   U16               usNumCqiResPerTti = 0;
   U16               usN1Pucch = 0;
   Bool              isCaEnable = FALSE;
   U16               maxDlUePerTti = 1;

#ifdef LTE_TDD
   U8 enUlDlConfig;
   U8      enSplSfCfg;
#endif

   Bool spsEnabled = FALSE;
   U16  maxNumDlSpsUePerTti = 0;
   U16  maxNumUlSpsUePerTti = 0;
   U8   flagTransMode = 3; 

	TRC2(rmAcHdlLrmCellCfgReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCellCfgReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmCellCfgReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from SM to RRM --*/
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTLRMCFGREQ;

	//Get the parametres from XML

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "cellBandwidth",  &(cellBandwidth));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "action", &(action));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "maxUlBandwidth",  &(maxUlBandwidth));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "maxDlBandwidth",  &(maxDlBandwidth));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bNrbCqi",  &(bNrbCqi));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bNcsAn",  &(bNcsAn));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxActiveUes",  &(maxActiveUes));

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"dataAcbSpac",   &(dataAcbSpac));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32,"dataAcbTime",   &(dataAcbTime));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32,"dataAcbFactor",    &(dataAcbFactor));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"sigAcbSpac",   &(sigAcbSpac));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep,CMXTA_ATTRIB_ENUM_U32,"sigAcbTime",   &(sigAcbTime));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep,CMXTA_ATTRIB_ENUM_U32,"sigAcbFactor",   &(sigAcbFactor));
   /* HCSG_DEV */
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxCsgUes",  &(maxCsgUes));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxNonCsgUes",  &(maxNonCsgUes));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxExtraUes",  &(maxExtraUes));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxSigUes",  &(maxSigUes));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dlfs",  &(dlfs));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "waitTime",  &(waitTime));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "acbForEmergency",  &(acbForEmergency));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "acbForSplClass",  &(acbForSplClass));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rcmAlgoType", &(rcmAlgoType));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numTxAnt", &(numTxAnt));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "usNumSrResPerTti", &(usNumSrResPerTti));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "usNumCqiResPerTti", &(usNumCqiResPerTti));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "enSrPrdcty", &(enSrPrdcty));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "enCqiPrdcty", &(enCqiPrdcty));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "enDsrTransMax", &(enDsrTransMax));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "usN1Pucch", &(usN1Pucch));

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cellId",  &(cellId));

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "drxEnabled",  &(drxEnabled));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "drxOnDurTimer",  &(drxOnDurTimer));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "drxRetxTimer",  &(drxRetxTimer));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "drxInactTimer",  &(drxInactTimer));

	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "spsEnabled",  &(spsEnabled));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "maxDlSpsUePerTti",  &(maxNumDlSpsUePerTti));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "maxUlSpsUePerTti",  &(maxNumUlSpsUePerTti));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "bSimulAckNack",  &(bSimulAckNack));
#ifdef LTE_TDD
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "enUlDlConfig", &(enUlDlConfig));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "enSplSfCfg", &(enSplSfCfg));
#endif
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "flagTransMode", &(flagTransMode));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isCaEnable",  &(isCaEnable));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numDlUePerTti",  &(maxDlUePerTti));
	// Allocate the memory for RmMngmt msg

	CMXTA_ALLOC(&cfgReq, sizeof(RmMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmCellCfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }


   // Fill the data values into cfgReq
	
	//Fill the header fields
	cfgReq->hdr.msgType				= TCFG;
	cfgReq->hdr.msgLen              = 0;
	cfgReq->hdr.entId.ent           = ENTRM;
	//cfgReq->hdr.entId.inst          = SM_INST_ZERO;
	cfgReq->hdr.entId.inst          = 0;
	cfgReq->hdr.elmId.elmnt         = STRMPROTOCFG;

   if(coupling == LRM_SEL_TC)
   	cfgReq->hdr.response.selector   = LRM_SEL_TC;
   else if(coupling == LRM_SEL_LWLC)
      cfgReq->hdr.response.selector   = LRM_SEL_LWLC;

	cfgReq->t.protoCfg.bCfgType = LRM_CELL_CONFIG;
	cfgReq->t.protoCfg.u.stCellCfg.enCellAddModDel = action;
	//cfgReq->t.protoCfg.u.stCellCfg.enCellAddModDel = LRM_PROTOCFG_ADD_CELL;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bCellId = cellId;

	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.enCellDlBandWidth = cellBandwidth;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.usMaxUlBroadbandBw = maxUlBandwidth;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.usMaxDlBroadbandBw = maxDlBandwidth;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bNRbCqi = bNrbCqi;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bNCsAn = bNcsAn;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bMaxActiveUesServed = maxActiveUes;
   /* HCSG_DEV */
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.usMaxExtraUes = maxExtraUes;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.usMaxNonCsgUes = maxNonCsgUes;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.usMaxCsgUes = maxCsgUes;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bMaxSigUesServed = maxSigUes;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.flagDlfsScheduling = dlfs;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bWaitTime = waitTime;
	cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bRcmAlgoType = rcmAlgoType;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bNumTxAnt = numTxAnt;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.enSrPrdcty        = enSrPrdcty;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.enCqiPrdcty       = enCqiPrdcty;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.usNumSrResPerTti  = usNumSrResPerTti;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.usNumCqiResPerTti = usNumCqiResPerTti;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.usN1Pucch         = usN1Pucch;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.enDsrTransMax     = enDsrTransMax;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bSimulCqiAckNack  = bSimulAckNack;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.flagTransMode     = flagTransMode;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bIsCaEnabled = isCaEnable;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.usMaxDlUePerTti = maxDlUePerTti;

   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stRmCellDrxCfg.bIsDrxEnabled = drxEnabled;
  // cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stRmCellDrxCfg.bDrxOnDurTmr = drxOnDurTimer;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stRmCellDrxCfg.usDrxInactvTmr = drxInactTimer;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stRmCellDrxCfg.bDrxRetxTmr = drxRetxTimer;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stRmCellDrxCfg.usLongDrxCycleGbr = 1;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stRmCellDrxCfg.usLongDrxCycleNonGbr = 3;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stRmCellDrxCfg.bIsGbrDrxDis=1;
	/* Send the msg to the RRM --*/

   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stSpsCellCfg.bIsSpsEnabled = spsEnabled;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stSpsCellCfg.usMaxDlSpsUePerTti = maxNumDlSpsUePerTti;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stSpsCellCfg.usMaxUlSpsUePerTti = maxNumUlSpsUePerTti;
#ifdef LTE_TDD
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.enUlDlConfig  = enUlDlConfig;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.enSplSfCfg  = enSplSfCfg;
#endif

   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bMaxAvgGbrPrbUsage = 99;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.utNumOfPrbRpts = 10;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.utPrbRptInterval = 10;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bRbcQci1TmngReq = 20;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bRbcQci2TmngReq = 30;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bRbcQci3TmngReq = 30;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bRbcQci4TmngReq = 32;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bRbcQci4TmngReqEnable = 0;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bNumDlNewUesPerTti = 4;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bNumUlNewUesPerTti = 4;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bNumDlReTxUesPerTti = 1;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bNumUlReTxUesPerTti = 1;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.bDuplexMode = 1; /* 1- FDD */

   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoData = 0 ;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbTime = dataAcbTime;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = dataAcbFactor;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.bAcbForSpac = dataAcbSpac; /* barred all special access class */
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoSig = 0 ;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbTime = sigAcbTime;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = sigAcbFactor;
   cfgReq->t.protoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.bAcbForSpac = sigAcbSpac; /* barred all special access class */


   if(coupling == LRM_SEL_TC)
   {
	   if(CMXTA_ERR_NONE != RmMiLrmCfgReq(&pst, cfgReq))
      {
          CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmCellCfgReq(): Mapping returned FAILED\n"));
      }
   }

   if(coupling == LRM_SEL_LWLC)
   {
      if(CMXTA_ERR_NONE != cmPkLwLcLrmCfgReq(&pst, cfgReq))
       {
          CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmGenCfgReq(): Mapping returned FAILED\n"));
       }
   }   

   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   rmAcHdlLrmEnbCfgReq
*
*       Desc:  Call Handler for LRM eNB config request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmEnbCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmEnbCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{

	Pst           pst;
	//SuId          suId;             /* service user SAP identifier */
	//SpId          spId;             /* service user SAP identifier */
	//Bool          entity;
	//S16           error;
	S16           ret = 0;
	ProcId        srcProcId;
	ProcId        dstProcId;
	RmMngmt		*cfgReq;


	U8	cfgType = 0;
	U8  maxCells = 0;
	LrmCfgAction  lrmCfgAction;
	U16 mmeId = 0;
	U8  action = 0;
   U8  coupling = LRM_SEL_LWLC;

	TRC2(rmAcHdlLrmEnbCfgReq);

	#ifndef ALIGN_64BIT
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmEnbCfgReq(), tcId (%ld)\n", tcCb->tcId));
	#else
	   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmEnbCfgReq(), tcId (%d)\n", tcCb->tcId));
	#endif

    CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

    srcProcId   =   CMXTA_DFLT_PROCID;
    dstProcId   =   CMXTA_DFLT_PROCID;

	/*-- Get the Pst information here from SM to RRM --*/
    cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTRM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

	pst.event   = EVTLRMCFGREQ;

	//Get the parametres from XML

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "CfgType",  &(cfgType));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxCells",  &(maxCells));
   pst.selector = coupling;

	if(ret == CMXTA_ERR_NO_VALUE)
	{
		maxCells = 0;
	}
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "LrmCfgAction",  &(lrmCfgAction));

	if(ret == CMXTA_ERR_NO_VALUE)
	{
		lrmCfgAction = 0;		
	}

	//ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "LrmCfgAction",  &(action));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "mmeId",  &(mmeId));
	
        if(ret == CMXTA_ERR_NO_VALUE)
        {
                mmeId = 0;
        }


	// Allocate the memory for RmMngmt msg

	CMXTA_ALLOC(&cfgReq, sizeof(RmMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmEnbCfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   // Fill the data values into cfgReq

	//Fill the header fields
	cfgReq->hdr.msgType		= TCFG;
	cfgReq->hdr.msgLen              = 0;
	cfgReq->hdr.entId.ent           = ENTRM;
	//cfgReq->hdr.entId.inst          = SM_INST_ZERO;
	cfgReq->hdr.entId.inst          = 0;
	cfgReq->hdr.elmId.elmnt         = STRMPROTOCFG;

   if( coupling == LRM_SEL_TC)
   	cfgReq->hdr.response.selector   = LRM_SEL_TC;
   else if (coupling == LRM_SEL_LWLC)
   	cfgReq->hdr.response.selector   = LRM_SEL_LWLC;

	cfgReq->t.protoCfg.bCfgType = LRM_ENB_CONFIG;
	cfgReq->t.protoCfg.u.stEnbCfg.bCfgType = cfgType;	
	
	if( cfgType == 1)
		cfgReq->t.protoCfg.u.stEnbCfg.u.bMaxNumCells = maxCells;
	else
	{	
		cfgReq->t.protoCfg.u.stEnbCfg.u.stMmeCfg.enMmeAddModOrDel = lrmCfgAction;
		//cfgReq->t.protoCfg.u.stEnbCfg.u.stMmeCfg.enMmeAddModOrDel = action;
		cfgReq->t.protoCfg.u.stEnbCfg.u.stMmeCfg.usMmeId = mmeId;
	}

	/* Send the msg to the RRM --*/

   if( coupling == LRM_SEL_TC)
   { 
   	if(CMXTA_ERR_NONE != RmMiLrmCfgReq(&pst, cfgReq))
       {
          CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmEnbCfgReq(): Mapping returned FAILED\n"));
      } 
   }

   if( coupling == LRM_SEL_LWLC)
   {
      if(CMXTA_ERR_NONE != cmPkLwLcLrmCfgReq(&pst, cfgReq))
        {
          CMXTA_DBG_ERR((_cmxtap,"rmAcHdlLrmGenCfgReq(): Mapping returned FAILED\n"));
        }
   }

    RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   rmAcHdlLrmEnbCfgCfm
*
*       Desc:  Call Handler for eNB config Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  rmac_lrmhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcHdlLrmEnbCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 rmAcHdlLrmEnbCfgCfm(tcCb, spCb)
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
   U8          flag = 0;
   U16       retVal = LCM_PRIM_OK;
   U16       reason = LCM_REASON_NOT_APPL;
   RmMngmt		*cfgCfm;

   TRC2(rmAcHdlLrmEnbCfgCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmEnbCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rmAcHdlLrmEnbCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "rmAcHdlLrmEnbCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "retVal",  &(retVal));
	ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "reason",  &(reason));

   rmMsg = (RmAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTRM, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLRMCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "flag",  &(flag));

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);
	rmMsg = (RmAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (RmMngmt *)(rmMsg->u.lrmInfo.data);
   if(flag)
   {
       //Validate for failure response
       if(cfgCfm->cfm.status != LCM_PRIM_OK)
       {
            RETVALUE(CMXTA_ERR_NONE);
       }
    }

	if(cfgCfm->cfm.status != retVal && cfgCfm->cfm.reason != reason )
	{
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
                  retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      RETVALUE(CMXTA_ERR_INT);

	}

   /*-- free memory, use callback function --*/
   RETVALUE(CMXTA_ERR_NONE);
}


/*utility function begins*/

#ifdef ANSI
PUBLIC S16 rmAcUtlLrmFreeCb
(
CmXtaMsgQElm    *qElm
)
#else
PUBLIC S16 rmAcUtlLrmFreeCb(qElm)
CmXtaMsgQElm   *qElm;
#endif
{
   RmAccMsgQElm *rmMsg;

   TRC2(rmAcUtlLrmFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "rmAcUtlLrmFreeCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   rmMsg = (RmAccMsgQElm *)qElm->data;

   if(rmMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   if (rmMsg != NULLP)
   {
      if(rmMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(rmMsg->mBuf);
      if(rmMsg->u.lrmInfo.data != NULLP)
      {
         WRAC_RMUFREEBUF(rmMsg->u.lrmInfo.data, rmMsg->u.lrmInfo.len);
      }
      CMXTA_FREE(rmMsg, sizeof (RmAccMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/*utility function ends*/
