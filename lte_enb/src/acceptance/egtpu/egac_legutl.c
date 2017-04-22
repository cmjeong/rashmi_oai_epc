
/********************************************************************20**

     Name:    eGTP- acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    egac_legutl.c

     Sid:      egac_legutl.c@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:44:33 2014

     Prg:     kc
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "leg.h"           /* layer management defines for MGCP */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#include "eg_edm.h"        /* EDM Module structures            */
#include "cm_xta.h" 
#include "eg.h"            /* defines and macros for MGCP */
#include "egt.h"            /* defines and macros for MGCP */
#include "eg_err.h"        /* MG error defines */
#include "egac_acc.h"        /* defines for MGCP acceptance tests */
#if 0
#include "eg_dbs11.h"           /* Egtpeter Upper Interface */
#endif
/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "egt.x"           /* SCTP Interface Structures */
#include "leg.x"           /* layer management typedefs for MGCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif
/* eg004.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.x" 
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for MGCP */
#include "egac_acc.x"        /* typedefs for MGCP acceptance tests */
#include "egac_leg.x"
#if 0
#include "eg_dbutl.x"           /* Egtpeter Upper Interface */
#include "eg_dbs11.x"           /* Egtpeter Upper Interface */
#include "eg_dbs5.x"           /* Egtpeter Upper Interface */
#endif
#include "eg_util.x"

/*
*  
*       Fun:   egAcUtlBuildGenCfgReq
*  
*       Desc:  Utility Function to Build General Configuration Req*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egAcUtlBuildGenCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
EgMngmt     *egMngmt
)
#else
PUBLIC Void egAcUtlBuildGenCfgReq(tcCb,spCb,egMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
EgMngmt    *egMngmt;
#endif
{
   /* local variables */
   EgGenCfg     *cfg;
   Pst          lmPst;              /* Post for layer manager */
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
#ifdef EGTP_U_MULTI_THREADED
   U8            thrdIndx = 0;
   S16           ret = 0; 
#endif
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildGenCfgReq)
 
   cfg   = &(egMngmt->u.cfg.s.gen);
   CMXTA_ZERO(cfg , sizeof (EgGenCfg));
 
  /*----------- Fill General Configuration Parameters ---------*/
 
#ifdef EGTP_C 
   cfg->nodeType     = (U8)EGAC_LEG_DFLT_NODE_TYPE;
   cfg->nmbIntfs     = (U8)EGAC_LEG_DFLT_NMB_INTFS;
   cfg->nmbMaxTnls   = (U32)EGAC_LEG_DFLT_MAX_TUNNELS;
   cfg->maxTunlArrSz = (U32)EGAC_LEG_DFLT_TUN_ARRAY_SIZE;
   cfg->n3Requests   = (U8)EGAC_LEG_DFLT_N3_REQUESTS;
   /* eg012.201 : added pbTmr value */
#ifdef LEGV5
   cfg->timeToWaitPbTmr.enb      = (U8)TRUE;
   cfg->timeToWaitPbTmr.val      = (U16)5000;
#endif
#endif
	/* eg001.102 1. EGTP_C Path management functionality is introduced. */
#ifdef EGTP_C_PTH_MGT   
   cfg->pathT3Timer.enb           = (U8)TRUE;
   cfg->pathT3Timer.val           = (U8)0;
   cfg->pathN3Retries             = (U8)EGAC_LEG_DFLT_NMB_TRIES;
   cfg->pathTmr.enb               = (U8)FALSE;
   cfg->pathTmr.val               = (U16)0;
   /* eg006.201: Seq Num Start & End vals will updated to 32 bit --*/
   cfg->echoSeqNumStart           = (U32)EGAC_LEG_DFLT_ECHO_SEQ_NUM_START;
   cfg->echoSeqNumEnd             = (U32)EGAC_LEG_DFLT_ECHO_SEQ_NUM_END;

   cfg->rstCnt                    = (U8)0;
#endif
   cfg->nmbUSaps     = (U16)EGAC_LEG_DFLT_MAX_USAPS;
   cfg->maxNmbTSaps  = (U16)EGAC_LEG_DFLT_MAX_TSAPS;
   cfg->nmbSrvs      = (U16)EGAC_LEG_DFLT_NMB_SRVS;
   cfg->timerRes     = (U16)EGAC_LEG_DFLT_TMR_RES;
   cfg->resThreshUpper=(Status)EGAC_LEG_DFLT_UPPER_THRES;
   cfg->resThreshLower=(Status)EGAC_LEG_DFLT_LOWER_THRES;
   cfg->lmPst.dstProcId  = EGAC_LEG_DFLT_LMPST_DST_PID_CFG;
   cfg->lmPst.srcProcId  = EGAC_LEG_DFLT_LMPST_SRC_PID_CFG;
   cfg->lmPst.dstEnt     = EGAC_LEG_DFLT_LMPST_DST_ENT_CFG;
   cfg->lmPst.srcEnt     = EGAC_LEG_DFLT_LMPST_SRC_ENT_CFG;
   cfg->lmPst.dstInst    = EGAC_LEG_DFLT_LMPST_DST_INST_CFG;
   cfg->lmPst.srcInst    = EGAC_LEG_DFLT_LMPST_SRC_INST_CFG;
   cfg->lmPst.prior      = EGAC_LEG_DFLT_LMPST_PRIOR_CFG;
   cfg->lmPst.route      = EGAC_LEG_DFLT_LMPST_ROUTE_CFG;
   cfg->lmPst.event      = EGAC_LEG_DFLT_LMPST_EVENT_CFG;
   cfg->lmPst.region     = EGAC_LEG_DFLT_LMPST_REGION_CFG;
   cfg->lmPst.pool       = EGAC_LEG_DFLT_LMPST_POOL_CFG;
   cfg->lmPst.selector   = EGAC_LEG_DFLT_LMPST_SEL_CFG;
/*eg004.201 Added for eGTP-C PSF*/
#ifdef HW
#ifdef LEGV3

   cfg->conventionalNode   = TRUE;
#endif
#endif

#ifdef EGTP_U
   cfg->eguT3Timer.enb           = (U8)EGAC_LEG_DFLT_T3_TMR_ENB;
   cfg->eguT3Timer.val           = (U8)EGAC_LEG_DFLT_T3_TMR_VAL;
   cfg->nmbRetries               = (U8)EGAC_LEG_DFLT_NMB_TRIES;
   cfg->echoTmr.enb              = (U8)EGAC_LEG_DFLT_ECHO_TMR_ENB;
   cfg->echoTmr.val              = (U16)EGAC_LEG_DFLT_ECHO_TMR_VAL;
   cfg->reOrderTmr.enb           = (U8)EGAC_LEG_DFLT_REORD_TMR_ENB;
   cfg->reOrderTmr.val           = (U16)EGAC_LEG_DFLT_REORD_TMR_VAL;
   cfg->pvtExtId                 = (U32)EGAC_LEG_DFLT_ECHO_REQ_PVTEXT;
   cfg->pduWindSize              = (U32)EGAC_LEG_DFLT_REORDER_WINSIZE;
   cfg->maxNumOfIp               = (U32)EGAC_LEG_DFLT_NMB_IP;
   cfg->nodeArch                 = (U32)EGAC_LEG_DFLT_NODE_ARCH;
   /*-- eg003.201 : TRC changes from eg009.102 : Setting Echo req to local port as TRUE --*/
   cfg->lclEchoSup               = TRUE;

#ifdef EGTP_U_MULTI_THREADED
   cfg->nmbWorkerThread          = (U8)EGAC_LEG_DFLT_NMB_WORK_THRD;
   cfg->loadDistTmr.enb           = (U8)EGAC_LEG_DFLT_THR_ASSGN_TMR_ENB;
   cfg->loadDistTmr.val           = (U16)EGAC_LEG_DFLT_THR_ASSGN_TMR_VAL;
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */

#ifdef EGTP_C_PTH_MGT   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, 
                  (Txt  *)"pathT3TmrEnb", &(cfg->pathT3Timer.enb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, 
                  (Txt  *)"pathT3TmrVal", &(cfg->pathT3Timer.val));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, 
                  (Txt  *)"pathTmrEnb", &(cfg->pathTmr.enb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, 
                  (Txt  *)"pathTmrVal", &(cfg->pathTmr.val));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, 
                  (Txt  *)"rstCnt", &(cfg->rstCnt));
#endif /* EGTP_C_PTH_MGT */
 
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);
   cmXtaGetPst(&lmPst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId, MATCH_PROCID);
#else
   cmXtaGetPst(&lmPst, ENTEG, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   /* Layer Manager post structure */
   cmMemcpy((U8 *) &(cfg->lmPst), (U8 *) &(lmPst), (PTR) sizeof(Pst));
 

#ifdef EGTP_C 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"nodeType", 
                                                                     &(cfg->nodeType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,  (Txt  *)"nmbIntfs", &(cfg->nmbIntfs));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"nmbMaxTnls", &(cfg->nmbMaxTnls));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"maxTunlArrSz", &(cfg->maxTunlArrSz));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,  (Txt  *)"n3Requests", &(cfg->n3Requests));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"nmbUSaps", &(cfg->nmbUSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"nmbSrvs", &(cfg->nmbSrvs));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"nmbTsap", &(cfg->maxNmbTSaps));
/*eg004.201 Repetition of timerRes parameter removed*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"resThreshUpper",  &(cfg->resThreshUpper));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"resThreshLower",  &(cfg->resThreshLower));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"timerRes", &(cfg->timerRes));

#ifdef EGTP_U
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, 
                  (Txt  *)"eguT3TimerEnb", &(cfg->eguT3Timer.enb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, 
                  (Txt  *)"eguT3TimerVal", &(cfg->eguT3Timer.val));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt  *)"nmbRetries", &(cfg->nmbRetries));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt  *)"echoTmrEnb", &(cfg->echoTmr.enb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, 
                  (Txt  *)"echoTmrVal", &(cfg->echoTmr.val));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt  *)"reOrderTmrEnb", &(cfg->reOrderTmr.enb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, 
                  (Txt  *)"reOrderTmrVal", &(cfg->reOrderTmr.val));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, 
                  (Txt  *)"pvtExtId", &(cfg->pvtExtId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, 
                  (Txt  *)"pduWindSize", &(cfg->pduWindSize));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, 
                  (Txt  *)"maxNumIp", &(cfg->maxNumOfIp));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, 
                  (Txt  *)"nodeArch", &(cfg->nodeArch));
   /*-- eg003.201 : TRC changes from eg009.102 : Obtain Echo req to local port --*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
         (Txt  *)"lclEchoSup", &(cfg->lclEchoSup)); 
#ifdef EGTP_U_MULTI_THREADED
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt  *)"nmbWorkerThread", &(cfg->nmbWorkerThread));

   if ((ret = SGetSBuf(cfg->lmPst.region, cfg->lmPst.pool, (Data**)&(cfg->thrdInfo), 
                           (Size)(sizeof(EgThrdInfo) * cfg->nmbWorkerThread))) !=
                           CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,
      "egAcUtlBuildGenCfgReq() : Unable to allocate memory for worker thread for EGTP-U GenCfg \n"));
      RETVOID;
   } /* end of if  */

   for (thrdIndx = 0; thrdIndx < cfg->nmbWorkerThread; thrdIndx++)
   {
       cfg->thrdInfo[thrdIndx].regionId = (U8)EGAC_LEG_DFLT_THR_REGID;
       cfg->thrdInfo[thrdIndx].pool     = (U8)EGAC_LEG_DFLT_THR_POOL;
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt  *)"gbThrAssgnTmrEnb", &(cfg->loadDistTmr.enb));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, 
                  (Txt  *)"gbThrAssgnTmrVal", &(cfg->loadDistTmr.val));
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */

   RETVOID;
} /* egAcUtlBuildGenCfgReq() */
 
 
 
/*
*
*       Fun:   egAcUtlBuildLSapCfgReq
*
*       Desc:  Utility Function to Build TSAP Configuration Req
*
*       Ret:   ROK
*
*       Notes: Lower Interface is assumed to be Trillium TUCL by default.
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egAcUtlBuildLSapCfgReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
EgMngmt    *egMngmt
)
#else
PUBLIC Void egAcUtlBuildLSapCfgReq(tcCb,spCb,egMngmt)
CmXtaTCCb *tcCb;    /* tcCb data structure  */
CmXtaSpCb *spCb;
EgMngmt   *egMngmt;
#endif
{
   /* local variables */
   EgTSapCfg   *cfg;
   EgTSapReCfg *reCfg;
   Pst          entPst;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2 (egAcUtlBuildLSapCfgReq)
 
   cfg   = &(egMngmt->u.cfg.s.tSap);
   reCfg = &(egMngmt->u.cfg.r.tSapReCfg);

   CMXTA_ZERO(cfg, sizeof (EgTSapCfg ));

   /* Default transport type is TUCL */
   cfg->tptType  = LEG_TSAP_TYPE_TUCL;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,(Txt  *)"type",&(cfg->tptType));

#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);

   if(cfg->tptType == LEG_TSAP_TYPE_DTUCL)
   {
      srcProcId   =   CMXTA_DFLT_PROCID;
      dstProcId   =   egAccCb.directives.xtaProcId;
      cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID + 5,srcProcId,dstProcId,MATCH_PROCID);
   }
   else
      cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   if(cfg->tptType == LEG_TSAP_TYPE_DTUCL)
   {
      cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID + 5, 0, 0,FALSE);
   }
   else
   {
      cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID, 0, 0, FALSE);
   }
#endif /* SS_MULTIPLE_PROCS */

   cfg->tSapId       = EGAC_DFLT_SUID_LCFG;
   cfg->spId         = EGAC_DFLT_SPID_LCFG;
   cfg->tptType      = EGAC_DFLT_INTF_TYPE;
   cfg->selector     = entPst.selector;
   /*cfg->selector     = EGAC_DFLT_SEL_LCFG; */
   cfg->mem.region   = EGAC_DFLT_MEMID_REG_LCFG;
   cfg->mem.pool     = EGAC_DFLT_MEMID_POOL_LCFG;
   cfg->priority     = EGAC_DFLT_PRIOR_LCFG;
   cfg->route        = EGAC_DFLT_ROUTE_LCFG;
#ifdef NOT_USED   
   cfg->dstProcId    = EGAC_DFLT_DST_PROC_ID_LCFG;
   cfg->dstEnt       = EGAC_DFLT_DST_ENT_ID_LCFG;
   cfg->dstInst      = EGAC_DFLT_DST_INST_ID_LCFG;
#endif /* NOT_USED */

   cfg->selector     = entPst.selector;
   cfg->dstProcId    = entPst.dstProcId;
   cfg->dstEnt       = entPst.dstEnt;
   cfg->dstInst      = entPst.dstInst;

   cfg->tInitTmr.enb = TRUE;
   cfg->tInitTmr.val = EGAC_DFLT_INIT_TMR_VAL_LCFG;

   cfg->tptParam.type = EGAC_DFLT_TPT_PAR_TYPE;
   cfg->tptParam.u.sockParam.listenQSize = EGAC_DFLT_SOC_LIS_QSIZE;
   cfg->tptParam.u.sockParam.numOpts     = EGAC_DFLT_SOC_NUM_OPTS;

   reCfg->tPar.type = EGAC_DFLT_TPT_PAR_TYPE;
   reCfg->tPar.u.sockParam.listenQSize = EGAC_DFLT_SOC_LIS_QSIZE;
   reCfg->tPar.u.sockParam.numOpts     = EGAC_DFLT_SOC_NUM_OPTS;
   reCfg->maxBndRetry  = EGAC_DFLT_BND_RETRY_CNT;
   reCfg->bndTmCfg.enb = TRUE;
   reCfg->bndTmCfg.val = EGAC_DFLT_BND_TMRVAL;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"suId",  &(cfg->tSapId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"spId",  &(cfg->spId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"tptType",  &(cfg->tptType));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"selector",  &(cfg->selector));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"region",  &(cfg->mem.region));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"pool",  &(cfg->mem.pool));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"priority",  &(cfg->priority));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"route",  &(cfg->route));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"dstEnt",  &(cfg->dstEnt));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"dstInst",  &(cfg->dstInst));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"dstProcId",  &(cfg->dstProcId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"tInitTmr.enb",  &(cfg->tInitTmr.enb));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , (Txt  *)"tInitTmr.val",  &(cfg->tInitTmr.val));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"tptParam.type", &(cfg->tptParam.type));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"sockParam.listenQSize", 
                                                          &(cfg->tptParam.u.sockParam.listenQSize));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"sockParam.numOpts", 
                                                          &(cfg->tptParam.u.sockParam.numOpts));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"tPar.type", &(reCfg->tPar.type));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"tPar.sockParam.listenQSize", 
                                                          &(reCfg->tPar.u.sockParam.listenQSize));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"tPar.sockParam.numOpts", 
                                                          &(reCfg->tPar.u.sockParam.numOpts));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"maxBndRetry",  &(reCfg->maxBndRetry));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"bndTmCfg.enb",  &(reCfg->bndTmCfg.enb));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16 , (Txt  *)"bndTmCfg.val",  &(reCfg->bndTmCfg.val));

   RETVOID;
}/* egAcUtlBuildLSapCfgReq()*/

/*    
*        
*       Fun:   egAcUtlBuildUSapCfgReq
*     
*       Desc:  Utility Function to Build SSAP Configuration Req
*  
*       Ret:   ROK
*     
*       Notes: None
*              
*       File:  egac_legutl.c
*  
*/ 
#ifdef ANSI
PUBLIC Void egAcUtlBuildUSapCfgReq 
(        
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
EgMngmt    *egMngmt
)
#else
PUBLIC Void egAcUtlBuildUSapCfgReq(tcCb,spCb,egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
EgMngmt     *egMngmt;
#endif
{
   Pst          entPst;
   EgUSapCfg    *cfg;
    U8          diffPeerCfg = FALSE;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildUSapCfgReq)

   cfg = &(egMngmt->u.cfg.s.uSap);
   CMXTA_ZERO(cfg, sizeof (EgUSapCfg));
   
   /*-- Get the Pst information here --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   /* dstProcId   =   egAccCb.directives.xtaProcId; */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);

   cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   cfg->sapId      = EGAC_DFLT_SPID_UCFG;

#ifdef EGTP_C
   cfg->echo       = EGAC_DFLT_ECHO_UCFG;
   cfg->intfType   = EGAC_DFLT_INTF_TYPE_UCFG;
#endif
   cfg->selector   = entPst.selector;
   cfg->mem.region = EGAC_DFLT_MEMID_REG_UCFG;
   cfg->mem.pool   = EGAC_DFLT_MEMID_POOL_UCFG;
   cfg->priority   = EGAC_DFLT_PRIOR_UCFG;
   cfg->route      = EGAC_DFLT_ROUTE_UCFG;
   cfg->dstProcId  = entPst.dstProcId;
   cfg->dstEnt     = entPst.dstEnt;
   cfg->dstInst    = entPst.dstInst;
   /*-- eg003.201 : changes from eg009.102 : set config flag acc to GTP Profile --*/
#ifdef EGTP_C
   cfg->flag       = EGAC_LEG_DFLT_GTP_C_ON;
#else
   cfg->flag       = EGAC_LEG_DFLT_GTP_PROT_FLG;
#endif


   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"sapId",  &(cfg->sapId));
#ifdef EGTP_C
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"echo",  &(cfg->echo));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"intfType",  &(cfg->intfType));
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"selector",  &(cfg->selector));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"region",  &(cfg->mem.region));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"pool",  &(cfg->mem.pool));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"priority",  &(cfg->priority));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"route",  &(cfg->route));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"dstEnt",  &(cfg->dstEnt));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"dstInst",  &(cfg->dstInst));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"dstProcId",  &(cfg->dstProcId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"gtpProtFlg",  &(cfg->flag));

   /* might be useful in the case of iterop testing   */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"diffPeerCfg",  &(diffPeerCfg));
   
#ifdef EGTP_C   
   /* Populate the ie and GM Config in the TA */
   populateIeConfigInTA(tcCb,spCb, diffPeerCfg);

   populateGmConfigInTA(tcCb, spCb, cfg->intfType, diffPeerCfg);
#endif

   RETVOID;
}/* egAcUtlBuildUSapCfgReq()*/


/*    
*        
*       Fun:   egAcUtlBuildTServerCfgReq
*     
*       Desc:  Utility Function to Build Transport Server Configuration Req
*  
*       Ret:   ROK
*     
*       Notes: None
*              
*       File:  egac_legutl.c
*  
*/ 
#ifdef ANSI
PUBLIC Void egAcUtlBuildTServerCfgReq 
(        
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
EgMngmt    *egMngmt
)
#else
PUBLIC Void egAcUtlBuildTServerCfgReq(tcCb,spCb,egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
EgMngmt     *egMngmt;
#endif
{
   Pst          entPst;
   EgTptSrvCfg  *cfg;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif
   Txt          ipAddr[50];
   S16          ret = 0;
   U16        port;
   char       ipStr[100];

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildTServerCfgReq)
   cfg = &(egMngmt->u.cfg.s.tptSrv);
   CMXTA_ZERO(cfg, sizeof (EgTptSrvCfg));
   CMXTA_ZERO(ipAddr, (sizeof(Txt)* 50));

   /*-- Get the Pst information here --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);

   cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   cfg->tptSrvId                         = EGAC_DFLT_TPT_SRV_ID; /* 0 */
   cfg->tSapId                           = EGAC_DFLT_SUID_LCFG;
   cfg->uSapId                           = EGAC_DFLT_SPID_LCFG;
   cfg->tptAddr.type                     = EGAC_DFLT_ADDR_TYPE;
   cfg->tptAddr.u.ipv4TptAddr.port       = EGAC_DFLT_PORT; /* 0 */
   cfg->tptParam.u.sockParam.numOpts     = EGAC_DFLT_SOC_NUM_OPTS; /* 0 */
   cfg->tptParam.u.sockParam.listenQSize = EGAC_DFLT_SOC_LIS_QSIZE; /* 5 */
   cfg->opnSrvRetryCnt                   = EGAC_DFLT_OPNSRV_RETRY_CNT;
   cfg->opnSrvTmr.enb                    = TRUE;
   cfg->opnSrvTmr.val                    = EGAC_DFLT_OPNSRV_TMR_VAL;
#ifdef EGTP_C
   cfg->isDfltSrv                        = FALSE;
#endif
   cfg->hostName.pres                    = FALSE;
   cfg->hostName.len                     = (PTR) cmStrlen((CONSTANT U8 *) EGAC_DFLT_HOST_NAME);
   cfg->gtp_C_Or_U                       = EGAC_LEG_DFLT_GTP_C_ON; 

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"tptSrvId",  &(cfg->tptSrvId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"tSapId",  &(cfg->tSapId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"uSapId",  &(cfg->uSapId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,  (Txt  *)"type", &(cfg->tptAddr.type));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"port", &(port));

   if(cfg->tptAddr.type == CM_TPTADDR_IPV4)
   {
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"address",&(ipAddr));
      if(ret == CMXTA_ERR_NO_VALUE)
      {
           cmInetAddr ((S8 *)EGAC_DFLT_ADDR, &(cfg->tptAddr.u.ipv4TptAddr.address));
      }
      else
      {
           cmInetAddr ( (S8 *)ipAddr, &(cfg->tptAddr.u.ipv4TptAddr.address));
            inet_ntop (AF_INET, &cfg->tptAddr.u.ipv4TptAddr.address,ipStr, INET_ADDRSTRLEN);
      }     
      cfg->tptAddr.u.ipv4TptAddr.port = port;
      cfg->tptAddr.u.ipv4TptAddr.address = CM_INET_NTOH_U32(cfg->tptAddr.u.ipv4TptAddr.address); 
   }
#ifdef IPV6_SUPPORTED               
   else
   {
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"address",&(ipAddr));
      if(ret == CMXTA_ERR_NO_VALUE)
      {
           cmInetPton6((S8 *)EGAC_DFLT_ADDR_IPV6, 
                   &(cfg->tptAddr.u.ipv6TptAddr.ipv6NetAddr));
      }
      else
      {
           /* strcpy ((char *)cfg->tptAddr.u.ipv6TptAddr.ipv6NetAddr, (S8 *)ipAddr); */
           cmInetPton6 (&cfg->tptAddr.u.ipv6TptAddr.ipv6NetAddr, ipAddr);
            inet_ntop (AF_INET6, &cfg->tptAddr.u.ipv6TptAddr.ipv6NetAddr, ipStr, INET6_ADDRSTRLEN);
      }     

      cfg->tptAddr.u.ipv6TptAddr.port = port;
   }
#endif   

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"sockParam.listenQSize",
                                                          &(cfg->tptParam.u.sockParam.listenQSize));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"sockParam.numOpts",
                                                          &(cfg->tptParam.u.sockParam.numOpts));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"opnSrvRetryCnt", &(cfg->opnSrvRetryCnt));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"opnSrvTmr.enb", &(cfg->opnSrvTmr.enb));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"opnSrvTmr.val", &(cfg->opnSrvTmr.val));
#ifdef EGTP_C
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"isDfltSrv", &(cfg->isDfltSrv));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,  (Txt  *)"hostName.pres", &(cfg->hostName.pres));

   if(cfg->hostName.pres == TRUE)
   {
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,  (Txt  *)"hostName.len", &(cfg->hostName.len));

     if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&cfg->hostName.val,
                              (cfg->hostName.len)) != ROK))
     {
         CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildServerCfgReq():unable to allocate memory for the hostName\n"));
         RETVOID; /* RETVALUE(CMXTA_ERR_INT); */
     }
     cmMemset ( (U8*)cfg->hostName.val, 0, cfg->hostName.len);
     cmMemcpy((U8 *)cfg->hostName.val,
              (CONSTANT U8 *) EGAC_DFLT_HOST_NAME,
              (PTR) cfg->hostName.len);
   }
#endif /* EGTP_U */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,  (Txt  *)"protType", &(cfg->gtp_C_Or_U));
  
   RETVOID;
}


/*
*
*       Fun:   egAcUtlBuildGenCntrlReq
*
*       Desc:  Utility Function to Build General Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egAcUtlBuildGenCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
EgMngmt   *egMngmt
)
#else
PUBLIC Void egAcUtlBuildGenCntrlReq(tcCb, spCb, egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
EgMngmt   *egMngmt;
#endif
{
   EgCntrl *cntrl;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildGenCntrlReq)

   cntrl = &egMngmt->u.cntrl;
 
   cntrl->action        = ADEL;
   cntrl->subAction     = NULLD;
   cntrl->s.sap.sapId   = EGAC_LEG_DFLT_SPID;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"uSapId",  &(cntrl->s.sap.sapId));
   /* eg007.201: update SapId with tSapId as param too*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"tSapId",  &(cntrl->s.sap.sapId));
 
   RETVOID;
}/* egAcUtlBuildGenCntrlReq()*/



/*
*
*       Fun:   egAcUtlBuildUSapCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egAcUtlBuildUSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
EgMngmt   *egMngmt
)
#else
PUBLIC Void egAcUtlBuildUSapCntrlReq(tcCb, spCb, egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
EgMngmt   *egMngmt;
#endif
{
 
   EgCntrl *cntrl;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildUSapCntrlReq)
 
   cntrl = &egMngmt->u.cntrl;
 
   cntrl->action        = AUBND_DIS;
   cntrl->flag          = LEG_EGTP_C;
   cntrl->subAction     = NULLD;
   cntrl->s.sap.sapId   = EGAC_DFLT_SPID_UCFG;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"action",  &(cntrl->action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"uSapId",  &(cntrl->s.sap.sapId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"flag",  &(cntrl->flag));
 
   RETVOID;
}/* egAcUtlBuildUSapCntrlReq()*/

/*
*
*       Fun:   egAcUtlBuildLSapCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egAcUtlBuildLSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
EgMngmt   *egMngmt
)
#else
PUBLIC Void egAcUtlBuildLSapCntrlReq(tcCb, spCb, egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
EgMngmt   *egMngmt;
#endif
{

   EgCntrl *cntrl;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildLSapCntrlReq)
 
   cntrl = &egMngmt->u.cntrl;
 

   cntrl->action        = AUBND_DIS;
   cntrl->subAction     = NULLD;
   cntrl->flag          = LEG_EGTP_C;
   cntrl->s.sap.sapId   = EGAC_DFLT_SPID_LCFG;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"action",  &(cntrl->action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"lSapId",  &(cntrl->s.sap.sapId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"flag",  &(cntrl->flag));

   RETVOID;
}/* egAcUtlBuildLSapCntrlReq()*/


/*
*
*       Fun:   egAcUtlBuildTServerCntrlReq
*
*       Desc:  Utility Function to Build Transport Server Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egAcUtlBuildTServerCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
EgMngmt   *egMngmt
)
#else
PUBLIC Void egAcUtlBuildTServerCntrlReq(tcCb, spCb, egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
EgMngmt   *egMngmt;
#endif
{
   EgCntrl *cntrl;
   Txt     ipAddr[50];
   S16     ret = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildTServerCntrlReq)

   cntrl = &egMngmt->u.cntrl;

#ifdef LEGV5
   /* eg007.201: update TSapId with default value */
   cntrl->s.server.tSapId = EGAC_DFLT_SPID_LCFG;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"lSapId",  &(cntrl->s.server.tSapId));
#endif

   cntrl->action        = AENA;
   cntrl->subAction     = NULLD;
   cntrl->flag          = LEG_EGTP_C;
   cntrl->s.server.type = EGAC_DFLT_TSRVPAR_TYPE;


   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"action",  &(cntrl->action));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"type",
                                               &(cntrl->s.server.type));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"flag",  &(cntrl->flag));

   if(cntrl->s.server.type == LEG_TSRV_ID)
   {
      cntrl->s.server.t.tptSrvId = EGAC_DFLT_TPT_SRV_ID; /* 0 */
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"tptSrvId",
                                                            &(cntrl->s.server.t.tptSrvId));
   }
   else if(cntrl->s.server.type == LEG_TSRV_ADDR)
   {
     cntrl->s.server.t.tptAddr.type = EGAC_DFLT_ADDR_TYPE;
     cntrl->s.server.t.tptAddr.u.ipv4TptAddr.port = EGAC_DFLT_PORT;

     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"port",
                                             &(cntrl->s.server.t.tptAddr.u.ipv4TptAddr.port));
     if(cntrl->s.server.t.tptAddr.type == CM_TPTADDR_IPV4)
     {
        ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_TXT,(Txt  *)"address",&(ipAddr));

        if(ret == CMXTA_ERR_NO_VALUE)
        {
           cmInetAddr ((S8 *)EGAC_DFLT_ADDR, &(cntrl->s.server.t.tptAddr.u.ipv4TptAddr.address));
        }
        else
        {
           cmInetAddr ( (S8 *)ipAddr, &(cntrl->s.server.t.tptAddr.u.ipv4TptAddr.address));
        }
        cntrl->s.server.t.tptAddr.u.ipv4TptAddr.address =
                             CM_INET_HTON_U32(cntrl->s.server.t.tptAddr.u.ipv4TptAddr.address);
     }
   }
   else
   {
       CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildLSapCntrlReq() Invalid Element Type \n"));
   }

   RETVOID;
}

/*
*
*       Fun:   egAcUtlBuildLSapTrcCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egAcUtlBuildLSapTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
EgMngmt   *egMngmt
)
#else
PUBLIC Void egAcUtlBuildLSapTrcCntrlReq(tcCb, spCb, egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
EgMngmt   *egMngmt;
#endif
{
   EgCntrl *cntrl;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildLSapTrcCntrlReq)
 
   cntrl = &egMngmt->u.cntrl;

   cntrl->action        = ADISIMM;
   cntrl->subAction     = SATRC;
   cntrl->flag          = LEG_EGTP_C;
   cntrl->s.trcCntrl.t.tSapId    = EGAC_DFLT_SPID_LCFG;
   cntrl->s.trcCntrl.trcMask     = EGAC_LEG_DFLT_TRCMASK;
   cntrl->s.trcCntrl.trcLen      = EGAC_LEG_DFLT_TRCLEN;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"lSapId",  &(cntrl->s.trcCntrl.t.tSapId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"trcLen",  &(cntrl->s.trcCntrl.trcLen));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"trcMask",&(cntrl->s.trcCntrl.trcMask));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"flag",  &(cntrl->flag));

   RETVOID;
}/* egAcUtlBuildLSapTrcCntrlReq()*/

/*
*
*       Fun:   egAcUtlBuildTrcCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egAcUtlBuildTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
EgMngmt   *egMngmt
)
#else
PUBLIC Void egAcUtlBuildTrcCntrlReq(tcCb, spCb, egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
EgMngmt   *egMngmt;
#endif
{
   EgCntrl *cntrl;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildTrcCntrlReq)
 
   cntrl = &egMngmt->u.cntrl;

   /* eg007.201: update TSapId with default value */
 
   cntrl->action        = AENA;
   cntrl->subAction     = SATRC;
   cntrl->flag          = LEG_EGTP_C;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"flag",  &(cntrl->flag));
#ifdef LEGV5
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"tSapId",  &(cntrl->s.trcCntrl.t.tSapId));
#endif

   RETVOID;
}/* egAcUtlBuildTrcCntrlReq()*/

/*
*
*       Fun:   egAcUtlBuildUstaCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egAcUtlBuildUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
EgMngmt   *egMngmt
)
#else
PUBLIC Void egAcUtlBuildUstaCntrlReq(tcCb, spCb, egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
EgMngmt   *egMngmt;
#endif
{
   EgCntrl *cntrl;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildUstaCntrlReq)
 
   cntrl = &egMngmt->u.cntrl;

   cntrl->action        = AENA;
   cntrl->subAction     = SAUSTA;
   cntrl->flag          = LEG_EGTP_C;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"action",  &(cntrl->action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"flag",  &(cntrl->flag));

   RETVOID;
}/* egAcUtlBuildUstaCntrlReq()*/

#ifdef DEBUGP
/*
*
*       Fun:   egAcUtlBuildDebugCntrlReq
*
*       Desc:  Utility Function to Build Debug Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egAcUtlBuildDebugCntrlReq
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb     *spCb,
EgMngmt    *egMngmt
)
#else
PUBLIC Void egAcUtlBuildDebugCntrlReq(tcCb, spCb,egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
EgMngmt   *egMngmt;
#endif
{
   EgCntrl *cntrl;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildDebugCntrlReq);
 
   cntrl = &egMngmt->u.cntrl;

   cntrl->action      = AENA;
   cntrl->subAction   = SADBG;
   cntrl->flag        = LEG_EGTP_C;
   cntrl->s.dbgCntrl.genDbgMask    = LEG_DBGMASK_DBG|LEG_DBGMASK_INFO| LEG_DBGMASK_ERROR;

   if(cmXtaCb.dbgMask >= EGAC_DBG_MASK)
      cntrl->action  = AENA;

#ifdef NOT_USED
    cntrl->s.dbgCntrl.genDbgMask = 
      (U32)(LEG_DBGMASK_FLOW|LEG_DBGMASK_DBG|LEG_DBGMASK_INFO| LEG_DBGMASK_ERROR|
            LEG_DBGMASK_PARAM| LEG_DBGMASK_BUF | LEG_DBGMASK_MSG |LEG_DBGMASK_TRC |
            LEG_DBGMASK_WARN | LEG_DBGMASK_FATAL | LEG_DBGMASK_MEM);
#endif /* NOT_USED */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8 , (Txt  *)"action",  &(cntrl->action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8 , (Txt  *)"subaction",  &(cntrl->subAction));
/*   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, (Txt  *)"dbgMask", &(cntrl->s.dbgCntrl.genDbgMask)); */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, (Txt  *)"dbgMask", &(cntrl->s.dbgCntrl.genDbgMask));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"flag",  &(cntrl->flag));

   RETVOID;
}/* egAcUtlBuildDebugCntrlReq()*/

#endif /* ifdef DEBUGP */
/*
*
*       Fun:   egAcUtlBuildShutdownCntrlReq
*
*       Desc:  Utility Function to Build Entity Control Req
*
*       Ret:   ROK
*
*      
*              
*       File:  egac_legutl.c
*
*/
/*eg004.201 Function Prototype Modified by introducing a new parameter 'MemRelflag'
 *This flag is boolean and is set to TRUE by defaault.This controls the release
 *of memory for gmDictionary alloacted for all procs.
 */
#ifndef HW
#ifdef ANSI
PUBLIC Void egAcUtlBuildShutdownCntrlReq
(
EgMngmt     *egMngmt
)
#else
PUBLIC Void egAcUtlBuildShutdownCntrlReq(egMngmt)
EgMngmt     *egMngmt;
#endif
#else
#ifdef ANSI
PUBLIC Void egAcUtlBuildShutdownCntrlReq
(
EgMngmt     *egMngmt,
U16         MemRelflag
)
#else
PUBLIC Void egAcUtlBuildShutdownCntrlReq(egMngmt,MemRelflag)
EgMngmt     *egMngmt;
U16         MemRelflag;
#endif
#endif
{
   EgCntrl *cntrl;
   U16 idx, msgCnt, nmbIe, nmbIe2, pos;
   LegIeEntry  *ieEntry=NULLP;
 
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildShutdownCntrlReq);
 
   cntrl = &egMngmt->u.cntrl;

   cntrl->action        = ASHUTDOWN;
   cntrl->subAction    = SAELMNT;
#ifdef LEG_EGTP_U
   cntrl->flag          = LEG_EGTP_U;
#else
   cntrl->flag          = LEG_EGTP_C;
#endif
#ifdef HW 
   if(!MemRelflag)
      RETVOID;
#endif

   /* free selfGmMsgCfg structures */
   for(idx=0;idx < MAX_APP_INTERFACES;idx++)
   {
      if(egAccCb.intfTypeMap[idx] == 0)
      {
         break;
      }

      /* eg009.201: no processing if gmEntry is NULL */
      if (!egAccCb.selfGmMsgCfg[idx].gmEntry )
      {
         continue;
      }

      for (msgCnt=0; msgCnt < egAccCb.selfGmMsgCfg[idx].nmbMsg; msgCnt++)
      {

         for (nmbIe=0; nmbIe < egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].nmbIeProp;nmbIe++)
         {
            ieEntry = NULLP;
            pos= egAccCb.selfIeCfg.posIdx[egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].ieProperties[nmbIe].ieType];
            if ( pos!=0)
               ieEntry = &(egAccCb.selfIeCfg.ieEntry[pos-1]);
            if ( ieEntry && ieEntry->dataType == EG_GROUPED)
				{
				  /*****************************************
					* If there is a second level grouped IE *
					****************************************/
				  for(nmbIe2=0;nmbIe2< egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].ieProperties[nmbIe].groupedIe->nmbGrpIe;nmbIe2++)
				  {
                 if( egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].ieProperties[nmbIe].groupedIe->ieProperties[nmbIe2].groupedIe != NULLP)
                 {
                    SPutSBuf(DFLT_REGION, DFLT_POOL,
                          (Data *) egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].ieProperties[nmbIe].groupedIe->ieProperties[nmbIe2].groupedIe->ieProperties,
                          (sizeof(LegIeProperties) *
                           egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].ieProperties[nmbIe].groupedIe->nmbGrpIe));

                    SPutSBuf(DFLT_REGION, DFLT_POOL,
                          (Data *) egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].ieProperties[nmbIe].groupedIe->ieProperties[nmbIe2].groupedIe,
                          (sizeof(LegGroupedIe)));

                 }
				  }

               SPutSBuf(DFLT_REGION, DFLT_POOL,
                     (Data *)(egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].
                              ieProperties[nmbIe].groupedIe->ieProperties)
                     ,(sizeof(LegIeProperties) *
                        (egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].
                         ieProperties[nmbIe].groupedIe->nmbGrpIe)));
               egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].
                  ieProperties[nmbIe].groupedIe->ieProperties = NULLP;

				   SPutSBuf(DFLT_REGION, DFLT_POOL,
                     (Data *)(egAccCb.selfGmMsgCfg[idx].gmEntry[msgCnt].
                              ieProperties[nmbIe].groupedIe),sizeof(LegGroupedIe));

            }
         }
      }
      SPutSBuf(DFLT_REGION, DFLT_POOL, (Data* )egAccCb.selfGmMsgCfg[idx].gmEntry,
            (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
      egAccCb.selfGmMsgCfg[idx].gmEntry = NULLP;
      egAccCb.intfTypeMap[idx] = 0;
   }
   RETVOID;
}/* egAcUtlBuildShutdownCntrlReq()*/

#ifdef EGTP_U
/*    
*        
*       Fun:   egUAcUtlBuildUSapCfgReq
*     
*       Desc:  Utility Function to Build USAP Configuration Req for eGTP-U
*  
*       Ret:   ROK
*     
*       Notes: None
*              
*       File:  egac_legutl.c
*  
*/ 
#ifdef ANSI
PUBLIC Void egUAcUtlBuildUSapCfgReq 
(        
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
EgMngmt    *egMngmt
)
#else
PUBLIC Void egUAcUtlBuildUSapCfgReq(tcCb,spCb,egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
EgMngmt     *egMngmt;
#endif
{
   Pst          entPst;
   EgUSapCfg    *cfg;
    U8          diffPeerCfg = FALSE;
#ifdef SS_MULTIPLE_PROCS
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
#endif

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egUAcUtlBuildUSapCfgReq);

   cfg = &(egMngmt->u.cfg.s.uSap);
   CMXTA_ZERO(cfg, sizeof (EgUSapCfg));

   /*-- Get the Pst information here --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   /* dstProcId   =   egAccCb.directives.xtaProcId; */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);

   cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTEU, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */
 
   cfg->sapId      = EGAC_DFLT_SPID_UCFG;
   cfg->selector   = entPst.selector;
   cfg->mem.region = EGAC_DFLT_MEMID_REG_UCFG;
   cfg->mem.pool   = EGAC_DFLT_MEMID_POOL_UCFG;
   cfg->priority   = EGAC_DFLT_PRIOR_UCFG;
   cfg->route      = EGAC_DFLT_ROUTE_UCFG;
   cfg->dstProcId  = entPst.dstProcId;
   cfg->dstEnt     = entPst.dstEnt;
   cfg->dstInst    = entPst.dstInst;
   cfg->flag       = EGAC_LEG_DFLT_GTP_PROT_FLG;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"sapId",  &(cfg->sapId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"selector",  &(cfg->selector));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"region",  &(cfg->mem.region));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"pool",  &(cfg->mem.pool));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"priority",  &(cfg->priority));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"route",  &(cfg->route));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"dstEnt",  &(cfg->dstEnt));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"dstInst",  &(cfg->dstInst));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"dstProcId",  &(cfg->dstProcId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"gtpProtFlg",  &(cfg->flag));

   /* might be useful in the case of iterop testing   */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"diffPeerCfg",  &(diffPeerCfg));
   
   /* Populate the ie and GM Config in the TA */
  /* populateIeConfigInTA(tcCb,spCb, diffPeerCfg); */

/*   populateGmUConfigInTA(tcCb, spCb, diffPeerCfg); */

   RETVOID;
}/* egUAcUtlBuildUSapCfgReq()*/

/*
*
*       Fun:   egUAcUtlBuildIPAddrCntrlReq
*
*       Desc:  Utility Function to Build IP Address Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legutl.c
*
*/
#ifdef ANSI
PUBLIC Void egUAcUtlBuildIPAddrCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
EgMngmt   *egMngmt
)
#else
PUBLIC Void egUAcUtlBuildIPAddrCntrlReq(tcCb, spCb, egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
EgMngmt   *egMngmt;
#endif
{
   EgCntrl *cntrl;
   Txt     ipAddr[50];
   S16     ret = 0;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egUAcUtlBuildIPAddrCntrlReq)

   cntrl = &egMngmt->u.cntrl;

   cntrl->action                = AENA;
   cntrl->subAction             = NULLD;
   cntrl->flag                  = LEG_EGTP_U;
   cntrl->s.ipAddress.fromSpId  = 0;
   cntrl->s.ipAddress.toSpId    = 1;

   /* Getting these values from TA */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"action",  &(cntrl->action));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, (Txt  *)"flag",  &(cntrl->flag));

     cntrl->s.ipAddress.ipAddr.type               = EGAC_LEG_DFLT_ADDR_TYPE;
     cntrl->s.ipAddress.ipAddr.u.ipv4TptAddr.port = EGAC_LEG_DFLT_EGTPU_PORT;

     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"port",
                                             &(cntrl->s.ipAddress.ipAddr.u.ipv4TptAddr.port));

     if(cntrl->s.ipAddress.ipAddr.type == CM_TPTADDR_IPV4)
     {
        ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_TXT,(Txt  *)"address", &(ipAddr));

        if(ret == CMXTA_ERR_NO_VALUE)
        {
           cmInetAddr ((S8 *)EGAC_DFLT_ADDR, &(cntrl->s.ipAddress.ipAddr.u.ipv4TptAddr.address));
        }
        else
        {
           cmInetAddr ( (S8 *)ipAddr, &(cntrl->s.ipAddress.ipAddr.u.ipv4TptAddr.address));
        }
        cntrl->s.ipAddress.ipAddr.u.ipv4TptAddr.address =
                             CM_INET_HTON_U32(cntrl->s.ipAddress.ipAddr.u.ipv4TptAddr.address);
     
   }
   else
   {
       CMXTA_DBG_ERR((_cmxtap,"egUAcUtlBuildIPAddrCntrlReq() Invalid Element Type \n"));
   }
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"fromSpId",  &(cntrl->s.ipAddress.fromSpId));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, (Txt  *)"toSpId",  &(cntrl->s.ipAddress.toSpId));

   RETVOID;
} /* End of egUAcUtlBuildIPAddrCntrlReq */

/*    
*        
*       Fun:   egUAcUtlBuildIPAddrCfgReq
*     
*       Desc:  Utility Function to Build IP Address Configuration Req
*  
*       Ret:   ROK
*     
*       Notes: None
*              
*       File:  egac_legutl.c
*  
*/ 
#ifdef ANSI
PUBLIC S16 egUAcUtlBuildIPAddrCfgReq 
(        
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
EgMngmt    *egMngmt
)
#else
PUBLIC S16 egUAcUtlBuildIPAddrCfgReq(tcCb,spCb,egMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
EgMngmt     *egMngmt;
#endif
{
   Pst          entPst;
   EgIpAddrCfg *cfg;
#ifdef SS_MULTIPLE_PROCS
   ProcId       srcProcId = 0;
   ProcId       dstProcId = 0;
#endif
   S16          ret = 0;
   S16          idx = 0;
   char         ipStr[100];
   #if 0
#ifndef IPV6_SUPPORTED               
#else
   U8          tmpAddrLst[15];
   Txt          tmpAddr[100];
#endif
#endif
   Txt          tmpAddrLst[15][EGUAC_MAX_TXT_LEN];
   U8           nmbAddr = 0;
   U8           tmpNmb = 0;
   SpId         tmpSpId[15];
   SpId         tmpNodeType[15];
   U8           ipAddrType[15];
   Txt          tmpEchoReqPvtExtVal[15][EGUAC_MAX_TXT_LEN];
   Txt          tmpEchoRspPvtExtVal[15][EGUAC_MAX_TXT_LEN];
   Txt          tmpErrIndPvtExtVal[15][EGUAC_MAX_TXT_LEN];
   Txt  parseStr[1000];

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcUtlBuildIPAddrCfgReq)

   cfg = &(egMngmt->u.cfg.s.ipAddr);

   CMXTA_ZERO(cfg, sizeof(EgIpAddrCfg));
   CMXTA_ZERO((U8 *)tmpSpId, (sizeof(SpId) * 15));
   CMXTA_ZERO(tmpNodeType, (sizeof(SpId) * 15));
   for(idx = 0; idx < 15; idx++)
   {
#if 0
#ifndef IPV6_SUPPORTED               
      CMXTA_ZERO((U8 *)tmpAddrLst[idx], EGUAC_MAX_TXT_LEN);
#else
      CMXTA_ZERO((U8 *)&(tmpAddrLst[idx]), sizeof(U8));
#endif
#endif
      CMXTA_ZERO((U8 *)tmpAddrLst[idx], EGUAC_MAX_TXT_LEN);

      CMXTA_ZERO(tmpEchoReqPvtExtVal[idx], EGUAC_MAX_TXT_LEN);
      CMXTA_ZERO(tmpEchoRspPvtExtVal[idx], EGUAC_MAX_TXT_LEN);
      CMXTA_ZERO(tmpErrIndPvtExtVal[idx], EGUAC_MAX_TXT_LEN);
   }

   /*-- Get the Pst information here --*/
#ifdef SS_MULTIPLE_PROCS
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   egAccCb.directives.xtaProcId;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&srcProcId);

   cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID,srcProcId,dstProcId,MATCH_PROCID);
#else
   cmXtaGetPst(&entPst, ENTEG, CMXTA_INST_ID, ENTEG, CMXTA_INST_ID, 0, 0, FALSE);
#endif /* SS_MULTIPLE_PROCS */

   cfg->nmbIpAddr = EGAC_LEG_DFLT_NMB_IP_ADDR; /* 1 */

   if ( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&cfg->ipInfo, 
        (EGAC_LEG_DFLT_NMB_IP_ADDR * sizeof(EgIpInfo))) != ROK))
   {
     CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildIPAddrCfgReq():unable to allocate memory for the hostName\n"));
     RETVALUE(CMXTA_ERR_INT);
   }


   CMXTA_ZERO((U8 *)cfg->ipInfo, (EGAC_LEG_DFLT_NMB_IP_ADDR * sizeof(EgIpInfo)));

   cfg->ipInfo[0].srcIpAddr.type                     = EGAC_DFLT_ADDR_TYPE;
   cmInetAddr ((S8 *)EGAC_DFLT_ADDR, &(cfg->ipInfo[0].srcIpAddr.u.ipv4TptAddr.address));
   cfg->ipInfo[0].srcIpAddr.u.ipv4TptAddr.port       = 0; /* 0 */
   cfg->ipInfo[0].spId                                = EGAC_DFLT_SPID_UCFG;
   cfg->ipInfo[0].nodeType                            = TRUE;
   cfg->ipInfo[0].cfmStatus                           = FALSE;
   cfg->ipInfo[0].echoReqPvtExtVal.length             = 1;
   cfg->ipInfo[0].echoReqPvtExtVal.buff[0]            = 0x01;
   cfg->ipInfo[0].echoRspPvtExtVal.length             = 1;
   cfg->ipInfo[0].echoRspPvtExtVal.buff[0]            = 0x07;
   cfg->ipInfo[0].errIndPvtExtVal.length              = 1;
   cfg->ipInfo[0].errIndPvtExtVal.buff[0]             = 0x05;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"nmbIpAddr", &(cfg->nmbIpAddr));

   if( ret != CMXTA_ERR_NO_VALUE)
   {
      if( (SPutSBuf(DFLT_REGION, DFLT_POOL, (Data *)cfg->ipInfo, EGAC_LEG_DFLT_NMB_IP_ADDR))!= ROK)
      {
          CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildIPAddrCfgReq() : Unable to De-allocate memory\n"));
          RETVALUE(CMXTA_ERR_INT);
      }

      if ( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&cfg->ipInfo, 
                    (cfg->nmbIpAddr * sizeof(EgIpInfo))) != ROK))
      {
           CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildIPAddrCfgReq():unable to allocate memory for the hostName\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      CMXTA_ZERO((U8 *)cfg->ipInfo, (cfg->nmbIpAddr * sizeof(EgIpInfo)));
#if 0
#ifndef IPV6_SUPPORTED               
      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,
                       CMXTA_SEP_COLON, "ipAddress", tmpAddrLst, &nmbAddr);
#else
      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,
                       CMXTA_SEP_COLON, "ipAddress", tmpAddrLst, &nmbAddr);
#endif
#endif
      EGAC_XML_GET_VALLIST_TXT (parseStr, "ipAddress", ",", tmpAddrLst, ret, nmbAddr);

      if(nmbAddr < cfg->nmbIpAddr)
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildIPAddrCfgReq(): Ip Address provided is less than configured number of Ip Address\n"));
         RETVALUE(CMXTA_ERR_INT);
      }   

      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON, "ipAddrtype", ipAddrType, &tmpNmb);

      if(tmpNmb < cfg->nmbIpAddr)
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildIPAddrCfgReq(): Number of Ip Address type provided is less than configured number of Ip Address\n"));
         RETVALUE(CMXTA_ERR_INT);
      }   

      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, CMXTA_SEP_COLON,
                           "uSapId", tmpSpId, &tmpNmb);

      if(tmpNmb < cfg->nmbIpAddr)
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildIPAddrCfgReq(): USapId provided is less than configured number of Ip Address\n"));
         RETVALUE(CMXTA_ERR_INT);
      }   

      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, CMXTA_SEP_COLON,
                           (Txt  *)"nodeType", tmpNodeType, &tmpNmb);

      if(tmpNmb < cfg->nmbIpAddr)
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildIPAddrCfgReq(): Node types provided is less than configured number of Ip Address\n"));
         RETVALUE(CMXTA_ERR_INT);
      }   

      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, CMXTA_SEP_COLON,
                               "echoReqPvtExtVal", tmpEchoReqPvtExtVal, &tmpNmb);
      if(tmpNmb < cfg->nmbIpAddr)
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildIPAddrCfgReq(): Number of Echo Req. Private extension values provided is less than configured number of Ip Address\n"));
         RETVALUE(CMXTA_ERR_INT);
      }   

      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, CMXTA_SEP_COLON,
                                        "echoRspPvtExtVal", tmpEchoRspPvtExtVal, &tmpNmb);
      if(tmpNmb < cfg->nmbIpAddr)
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildIPAddrCfgReq(): Number of Echo Rsp. Private extension values provided is less than configured number of Ip Address\n"));
         RETVALUE(CMXTA_ERR_INT);
      }   

      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, CMXTA_SEP_COLON,
                                        "errIndPvtExtVal", tmpErrIndPvtExtVal, &tmpNmb);
      if(tmpNmb < cfg->nmbIpAddr)
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcUtlBuildIPAddrCfgReq(): Number of Echo Rsp. Private extension values provided is less than configured number of Ip Address\n"));
         RETVALUE(CMXTA_ERR_INT);
      }   

      for (idx = 0; idx < cfg->nmbIpAddr; idx++)
      {

         cfg->ipInfo[idx].srcIpAddr.type = ipAddrType[idx];

         if( ipAddrType[idx] == CM_TPTADDR_IPV4)
         {
            cmInetAddr ( (S8 *)tmpAddrLst[idx], &(cfg->ipInfo[idx].srcIpAddr.u.ipv4TptAddr.address));
            cfg->ipInfo[idx].srcIpAddr.u.ipv4TptAddr.address = CM_INET_NTOH_U32(cfg->ipInfo[idx].srcIpAddr.u.ipv4TptAddr.address);
         }
#ifdef IPV6_SUPPORTED
         if( ipAddrType[idx] == CM_TPTADDR_IPV6)
         {
            
               cmInetPton6 (&cfg->ipInfo[idx].srcIpAddr.u.ipv6TptAddr.ipv6NetAddr, (S8*)tmpAddrLst[idx]);
         }
#endif
         if (ipAddrType[idx] == CM_TPTADDR_IPV4)
         {
            inet_ntop (AF_INET, &cfg->ipInfo[idx].srcIpAddr.u.ipv4TptAddr.address, ipStr, INET_ADDRSTRLEN);
            /*printf ("Manju: ipaddr cfg:srcIp = %s\n", ipStr);*/
         }
         else
         {
            inet_ntop (AF_INET6, &cfg->ipInfo[idx].srcIpAddr.u.ipv6TptAddr.ipv6NetAddr, ipStr, INET6_ADDRSTRLEN);
            /*printf ("Manju: ipaddr cfg:srcIp = %s\n", ipStr);*/
         }
         cfg->ipInfo[idx].spId                                = tmpSpId[idx];
         cfg->ipInfo[idx].nodeType                            = tmpNodeType[idx];
         cfg->ipInfo[idx].echoReqPvtExtVal.length = cmStrlen((CONSTANT U8 *)tmpEchoReqPvtExtVal[idx]);
         cmMemcpy((U8*)cfg->ipInfo[idx].echoReqPvtExtVal.buff, (U8*)tmpEchoReqPvtExtVal[idx],
                           cfg->ipInfo[idx].echoReqPvtExtVal.length);

         cfg->ipInfo[idx].echoRspPvtExtVal.length = cmStrlen((CONSTANT U8 *)tmpEchoRspPvtExtVal[idx]); 
         cmMemcpy((U8*)cfg->ipInfo[idx].echoRspPvtExtVal.buff, (U8*)tmpEchoRspPvtExtVal[idx],
                           cfg->ipInfo[idx].echoRspPvtExtVal.length);

         cfg->ipInfo[idx].errIndPvtExtVal.length = cmStrlen((CONSTANT U8 *)tmpErrIndPvtExtVal[idx]); 
         cmMemcpy((U8*)cfg->ipInfo[idx].errIndPvtExtVal.buff, (U8*)tmpErrIndPvtExtVal[idx],
                           cfg->ipInfo[idx].errIndPvtExtVal.length);
      }
   }
   RETVALUE(ROK); 
}/* end of egUAcUtlBuildIPAddrCfgReq */
#endif

/********************************************************************30**

         End of file:     egac_legutl.c@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:44:33 2014

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rkumar      1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced. 
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3      eg003.201    psingh            1. Merged code from eg006.102 to 
                                               fix TRACE5 macro related issue
                                            2. eg009.102: Setting Echo req to local port as TRUE
                                            3. eg009.102: Setting config flag according to gen 
/main/3      eg004.201    magnihotri        1. Header files added for eGTP-C PSF
                                            2. Function Prototype Modified by introducing a new parameter 'MemRelflag'
                                               This flag is boolean and is set to TRUE by defaault.This controls the release
                                               of memory for gmDictionary alloacted for all procs.
                                            3. Repetition of timerRes parameter removed
/main/3      eg006.201    psingh            1. Seq Num Start & End vals updated for 32bit values
/main/3      eg007.201    psingh            1. Accept tSapId from user to index TSAP Cb list
/main/3      eg009.201    asaurabh          1. Put NULL ptr check on gmEntry
/main/3      eg012.201    shpandey          1. Added timeToWaitPbTmr value in GenCfg
*********************************************************************91*/
