
/********************************************************************20**

     Name:    X2AP- acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    czac_lczutl.c

     Sid:      czac_lczutl.c@@/main/2 - Tue Aug 30 18:35:48 2011

     Prg:     sy 
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
#include "cm_pasn.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "lcz.h"           /* layer management defines for MGCP */

#ifdef HI
#include "lhi.h"
#endif /* HI */

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h" 
#include "cz.h"            /* defines and macros for MGCP */
#include "czt.h"            /* defines and macros for MGCP */
#include "cz_err.h"        /* MG error defines */
#include "czac_acc.h"        /* defines for MGCP acceptance tests */

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
#include "cm_pasn.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SCTP Interface Structures */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* SCTP Interface Structures */
#include "lcz.x"           /* layer management typedefs for MGCP */

#ifdef HI
#include "lhi.x"
#endif /* HI */

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for MGCP */
#include "czac_acc.x"        /* typedefs for MGCP acceptance tests */
#include "czac_lcz.x"

/* cz001.101 : CR Fixes.*/
/*
*  
*       Fun:   czAcUtlBuildGenCfgReq
*  
*       Desc:  Utility Function to Build General Configuration Req*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildGenCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CzMngmt     *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildGenCfgReq(tcCb,spCb,czMangmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
CzMngmt    *czMangmt;
#endif /* ANSI */
{
   /* local variables */
   CzGenCfg    *cfg;
   CzGenReCfg    *reCfg;
   Pst          lmPst;              /* Post for layer manager */
 
   TRC2(czAcUtlBuildGenCfgReq)
 
   cfg   = &(czMangmt->t.cfg.u.gen);
   reCfg   = &(czMangmt->t.cfg.r.genReCfg);
   CMXTA_ZERO(cfg , sizeof (CzGenCfg));
   CMXTA_ZERO(reCfg , sizeof (CzGenReCfg));
 
  /*----------- Fill General Configuration Parameters ---------*/
   
   cfg->nmbCztSaps = (S16)CZAC_LCZ_MAX_CZTSAP;
   cfg->nmbSctSaps = (S16)CZAC_LCZ_MAX_SCTSAP;
   cfg->memUpperThr =CMXTA_CZ_RES_THR_UP;
   cfg->memLowerThr = CMXTA_CZ_RES_THR_LOW;
   cfg->maxNmbPeer = (U32)CZAC_LCZ_MAX_PEER;
   cfg->timeRes = (Ticks)CZAC_LCZ_TIMERES;
#ifdef DEBUGP
   cfg->dbgMask = 0x00;
   if(cmXtaCb.dbgMask > CZAC_DBGLEVEL_CZ)
   {
      cfg->dbgMask = 0xFFFFFFFF;
   }
#endif /* DEBUGP */

   
czAcGetPst(spCb, &lmPst, ENTCZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

 
   /* Layer Manager post structure */
   cmMemcpy((U8 *) &(cfg->lmPst), (U8 *) &(lmPst), (PTR) sizeof(Pst));
 

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "nmbCztSaps", &(cfg->nmbCztSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "nmbSctSaps", &(cfg->nmbSctSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "memUpperThr", &(cfg->memUpperThr));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "memLowerThr", &(cfg->memLowerThr));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "maxNmbPeer", &(cfg->maxNmbPeer));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "timeRes", &(cfg->timeRes));

/* Initialize  the reconfigration parameters */
   reCfg->timeRes = (Ticks)CZAC_LCZ_TIMERES;
#ifdef DEBUGP
   reCfg->dbgMask = 0x00;
   if(cmXtaCb.dbgMask > CZAC_DBGLEVEL_CZ)
   {
      reCfg->dbgMask = 0xFFFFFFFF;
   }
#endif /* DEBUGP */  
   reCfg->memUpperThr =CMXTA_CZ_RES_THR_UP;
   reCfg->memLowerThr = CMXTA_CZ_RES_THR_LOW; 
#ifdef DEBUGP
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dbgMsk", &(cfg->dbgMask));
#endif /* DEBUGP */

/* read the reconfigration parameters from TA */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "timeRes", &(reCfg->timeRes));
#ifdef DEBUGP
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dbgMsk", &(reCfg->dbgMask));
#endif /* DEBUGP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "memUpperThr", &(reCfg->memUpperThr));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "memLowerThr", &(reCfg->memLowerThr));
   
  RETVOID;
} /* czAcUtlBuildGenCfgReq() */
 
 
 
/*
*
*       Fun:   czAcUtlBuildLSapCfgReq
*
*       Desc:  Utility Function to Build TSAP Configuration Req
*
*       Ret:   ROK
*
*       Notes: 1. Lower Interface is assumed to be Trillium SCTP by default.
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildLSapCfgReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
CzMngmt    *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildLSapCfgReq(tcCb,spCb,czMangmt)
CmXtaTCCb *tcCb;    /* tcCb data structure  */
CmXtaSpCb *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
   /* local variables */
   CzSctSapCfg  *cfg;
   Pst          entPst;
   U16          provType = ENTSB;
 
   TRC2 (czAcUtlBuildLSapCfgReq)
 
   cfg   = &(czMangmt->t.cfg.u.sctSap);

   CMXTA_ZERO(cfg, sizeof (CzSctSapCfg));

   cfg->suId   = CZAC_LCZ_DFLT_SPID;
   cfg->spId   = CZAC_LCZ_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(cfg->spId));

#ifdef CZAC_LKSCTP
 if( (cfg->spId==2 || cfg->spId==3))
   provType =  ENTHI;
#endif /* CZAC_LKSCTP */
     
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,"provType",&provType);

   czAcGetPst(spCb, &entPst, (Ent)ENTCZ, CMXTA_INST_ID, (Ent)provType, CMXTA_INST_ID);/* window's warnings fix typecat as per gen.x*/
#ifdef DM 
   if(provType == CZAC_SCTP_DM)
      czAcGetPst(spCb, &entPst, (Ent)ENTCZ, CMXTA_INST_ID, (Ent)ENTSB, CMXTA_INST_ID + 5);/* window's warnings fix changed data typr to Ent frm u8 */
#endif /* DM */

   cfg->selector     = entPst.selector;
   cfg->mem.region   = entPst.region;
   cfg->mem.pool     = entPst.pool;
   cfg->priority     = entPst.prior;
   cfg->route        = entPst.route;
   cfg->dstProcId    = entPst.dstProcId;
   cfg->dstEntId     = entPst.dstEnt;
   cfg->dstInstId    = entPst.dstInst;
   
   cfg->tBndTmr.enb = TRUE;
   cfg->tBndTmr.val = CZAC_LCZ_VAL_10;
   cfg->maxBndRetry = CZAC_LCZ_VAL_3;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(cfg->suId));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "tBndTmr.enb",  &(cfg->tBndTmr.enb));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , "tBndTmr.val",  &(cfg->tBndTmr.val));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , "maxBndRetry",  &(cfg->maxBndRetry));

   RETVOID;
}/* czAcUtlBuildLSapCfgReq()*/

/*    
*        
*       Fun:   czAcUtlBuildUSapCfgReq
*     
*       Desc:  Utility Function to Build SSAP Configuration Req
*  
*       Ret:   ROK
*     
*       Notes: None
*              
*       File:  czac_lczutl.c
*  
*/ 
#ifdef ANSI
PUBLIC Void czAcUtlBuildUSapCfgReq 
(        
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
CzMngmt    *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildUSapCfgReq(tcCb,spCb,czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
CzMngmt     *czMangmt;
#endif /* ANSI */
{
 
   Pst      entPst;
   CzCztSapCfg    *cfg;
   
   TRC2(czAcUtlBuildUSapCfgReq)

   cfg = &(czMangmt->t.cfg.u.cztSap);
   CMXTA_ZERO(cfg, sizeof (CzCztSapCfg));
   
   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &entPst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);
 
   cfg->spId = CZAC_LCZ_DFLT_SPID;
   cfg->selector = entPst.selector;
   cfg->mem.region = entPst.region;
   cfg->mem.pool = entPst.pool;
   cfg->priority = entPst.prior;
   cfg->route = entPst.route;
#ifdef CZAC_LKSCTP 
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP)
   cfg->spId = CZAC_LCZ_KSCTP_SPID;
#endif /* CZAC_LKSCTP */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "sapId",  &(cfg->spId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "selector",  &(cfg->selector));

 
   RETVOID;
}/* czAcUtlBuildUSapCfgReq()*/
 
/*
*  
*       Fun:   czAcUtlBuildProtCfgReq
*                   
*       Desc:  Utility Function to Build Protocol Configuration Req
*  
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*  
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildProtCfgReq
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb     *spCb,
CzMngmt    *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildProtCfgReq(tcCb, spCb, czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
   S8             ipAddrString[20]= CZAC_LCZ_IPADDR;
   S8             dispString[20];
   CmInetIpAddr   ipAddr = 0;
   U16            ipAddrType;
   U16            i,indx;
   CzProtCfg     *protCfg;
   CzProtReCfg     *protReCfg;
   U16            srcProcId=100;
   U8             nmbAddr = 0;  /* windows warning fixed by changing from U16 to U8 */
   Bool            addrPresent = 1;

   TRC2(czAcUtlBuildProtCfgReq)

   protCfg = &(czMangmt->t.cfg.u.prot);
   protReCfg = &(czMangmt->t.cfg.r.protReCfg);
   CMXTA_ZERO(protCfg, sizeof (CzProtCfg));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "procId", &(srcProcId));
   CZ_GET_PEERPROF_INDEX(srcProcId, indx);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16 , "nmbOfAddr",  &nmbAddr);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8 , "addrPres",  &addrPresent);
     cmMemcpy((U8 *) protCfg, (U8 *) &(czENodeB[indx].protCfg), (PTR) sizeof(CzProtCfg));
     if(addrPresent == 0)
         protCfg->srcAddr.ipAddr.nmb = 0;
   if(nmbAddr > 0)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "sctPort", &(protCfg->srcAddr.sctPort));
         
      protCfg->srcAddr.ipAddr.nmb = nmbAddr;

      for(i =0; i < protCfg->srcAddr.ipAddr.nmb; i++)
      {
#ifdef SB_IPV6_SUPPORTED
         ipAddrType  = CM_IPV6ADDR_TYPE;
#else /* SB_IPV6_SUPPORTED */
         ipAddrType  = CM_IPV4ADDR_TYPE;
#endif /* SB_IPV6_SUPPORTED */

         sprintf(dispString,"ipAddrType_%d_",i);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8 , dispString, &(ipAddrType));
         sprintf(dispString,"ipAddr_%d_",i);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT , dispString, &(ipAddrString));

         protCfg->srcAddr.ipAddr.nAddr[i].type  = (U8)ipAddrType;

         if(ipAddrType == CM_IPV4ADDR_TYPE)
         {
            if(ROK == cmInetAddr(ipAddrString,&ipAddr))
            {
               protCfg->srcAddr.ipAddr.nAddr[i].u.ipv4NetAddr   =  ntohl(ipAddr);
            }
         }
#ifdef SB_IPV6_SUPPORTED
         else if(ipAddrType == CM_IPV6ADDR_TYPE)
         {
            /*- IPV6 Change -*/
            cmInetPton6(&protCfg->srcAddr.ipAddr.nAddr[i].u.ipv6NetAddr, ipAddrString);
         }
#endif /* SB_IPV6_SUPPORTED */
      }
   }

      
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "eNbId",      &(protCfg->eNbId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tRELOCprep", &(protCfg->tRELOCprep));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tX2RELOCOverall", &(protCfg->tX2RELOCOverall));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "timeToWait", &(protCfg->timeToWait));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "dynamPeerFlag", &(protCfg->dynamPeerFlag));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dynamUSapId",
            &(protCfg->defDPeerUSapId));

      protReCfg->tRELOCprep=CMXTA_CZ_500_MSECONDS;
      protReCfg->tX2RELOCOverall=CMXTA_CZ_4_SECONDS;
      protReCfg->timeToWait = CMXTA_CZ_4_SECONDS;
      protReCfg->dynamPeerFlag=FALSE;

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tRELOCprep", &(protReCfg->tRELOCprep));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tX2RELOCOverall", &(protReCfg->tX2RELOCOverall));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "timeToWait", &(protReCfg->timeToWait));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "dynamPeerFlag", &(protReCfg->dynamPeerFlag));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dynamUSapId",
            &(protReCfg->defDPeerUSapId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
 {
  protCfg->defDPeerUSapId= CZAC_LCZ_KSCTP_SPID;
  protReCfg->defDPeerUSapId= CZAC_LCZ_KSCTP_SPID;
}
#endif /* CZAC_LKSCTP */
   RETVOID;
}/* czAcUtlBuildProtCfgReq()*/
 
 
/*
*
*       Fun:   czAcUtlBuildPeerCfgReq
*
*       Desc:  Utility Function to Build Entity Configuration Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildPeerCfgReq
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb     *spCb,
CzMngmt    *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildPeerCfgReq(tcCb, spCb, czMangmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
CzMngmt    *czMangmt;
#endif /* ANSI */
{
   CzPeerLstCfg      *cfg = NULLP;
   U8             indx;
   ProcId            dstProcId =100; 
   TRC2 (czAcUtlBuildPeerCfgReq);
 
   cfg = &(czMangmt->t.cfg.u.peerLst);
   CMXTA_ZERO(cfg, sizeof (CzPeerLstCfg)); /* klockwork fix */
   /*
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "peerProcId", &(dstProcId));
   */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "ProcId", &(dstProcId));
   CZ_GET_PEERPROF_INDEX(dstProcId, indx);
   cfg->nmbPeers = (U32)CZAC_LCZ_NUM_PEERS;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "nmbPeers",  &(cfg->nmbPeers));
   if(cfg->nmbPeers > 0)
   {
      CMXTA_ALLOC(&cfg->peerCfg, sizeof(CzPeerCfg)* cfg->nmbPeers); 
   }
  else 
   {
      RETVOID;
   }
   
   /* klockwork fix */ 
   if (cfg->peerCfg == NULLP)
   {
      RETVOID;
   }
 
 cmMemcpy((U8 *)cfg->peerCfg, (U8 *) &(czENodeB[indx].peerCfg), (PTR) sizeof(CzPeerCfg));

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "PeerId",  &(cfg->peerCfg[0].peerId));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "uSapId",  &(cfg->peerCfg[0].uSapId));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "tSapId",  &(cfg->peerCfg[0].tSapId));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "eAValue",  &(cfg->peerCfg[0].eAValue));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "iPAValue",  &(cfg->peerCfg[0].iPAValue));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "locOutStrms", 
                                                    &(cfg->peerCfg[0].assocCfg.locOutStrms));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "globalProcStrmPres",  &(cfg->peerCfg[0].globalProcStrmId.pres));
  cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "globalProcStrmId", 
                                                    &(cfg->peerCfg[0].globalProcStrmId.val));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP)
{   
   cfg->peerCfg[0].tSapId=1;
   cfg->peerCfg[0].uSapId=1;
}
#endif /* CZAC_LKSCTP */ 

/*
      if(cfg->nmbPeers==CZAC_LCZ_NUM_PEERS)
         RETVOID;
   for(i = 0;i < cfg->nmbPeers; i++)
   {
      CMXTA_ZERO(&cfg->peerCfg[i], sizeof (CzPeerCfg));


      sprintf(dispString,"peerCfg_%d_.peerId",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, dispString,  &(cfg->peerCfg[i].peerId));
      sprintf(dispString,"peerCfg_%d_.eAValue",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, dispString,  &(cfg->peerCfg[i].eAValue));
      sprintf(dispString,"peerCfg_%d_.iPAValue",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, dispString,  &(cfg->peerCfg[i].iPAValue));


      sprintf(dispString,"peerCfg_%d_.sapId",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, dispString,  &(cfg->peerCfg[i].uSapId));

      asCfg =  &cfg->peerCfg[i].assocCfg;

      sprintf(dispString,"peerCfg_%d_.locOutStrms",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, dispString,  &(asCfg->locOutStrms));

      sprintf(dispString,"peerCfg_%d_.globalProcStrmId.pres",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, dispString,  &(cfg->peerCfg[i].globalProcStrmId.pres));

      sprintf(dispString,"peerCfg_%d_.globalProcStrmId.spare1",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, dispString,  &(cfg->peerCfg[i].globalProcStrmId.spare1));

      sprintf(dispString,"peerCfg_%d_.globalProcStrmId.val",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, dispString,  &(cfg->peerCfg[i].globalProcStrmId.val));

#ifdef ALIGN_64
      sprintf(dispString,"peerCfg_%d_.globalProcStrmId.spare2",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, dispString,  &(cfg->peerCfg[i].globalProcStrmId.spare2));
#endif

      sprintf(dispString,"peerCfg_%d_.priDstAddr.type",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, dispString,  &(ipAddrType));

      asCfg->priDstAddr.type  = (U8)ipAddrType;

      sprintf(dispString,"peerCfg_%d_.priDstAddr.addr",i);
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT , dispString, &(ipAddr));

      if(ROK == cmInetAddr(ipAddrString,&ipAddr))
      {
         if(ipAddrType == CM_IPV4ADDR_TYPE)
         {
            asCfg->priDstAddr.u.ipv4NetAddr   =  ntohl(ipAddr);
         }
#ifdef SB_IPV6_SUPPORTED
         else if(ipAddrType == CM_IPV6ADDR_TYPE)
         {
            asCfg->priDstAddr.u.ipv6NetAddr   =  ntohl(ipAddr);
         }
#endif
      }

      sprintf(dispString,"peerCfg_%d_.dstPort",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, dispString, &(asCfg->dstPort));

      sprintf(dispString,"peerCfg_%d_.nmbOfAddr",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16 , dispString,  &(numAddr));
      asCfg->dstAddrLst.nmb   =  (U8)numAddr;

      for(j =0; j < numAddr; j++)
      {
         ipAddrType  = CM_IPV4ADDR_TYPE;

         sprintf(dispString,"peerCfg_%d_.dstAddr_%d_.type",i,j);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8 , dispString, &(ipAddrType));

         sprintf(dispString,"peerCfg_%d_.dstAddr_%d_.ipAddr",i, j);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT , dispString, &(ipAddrString));

         asCfg->dstAddrLst.nAddr[j].type  = (U8)ipAddrType;

         if(ROK == cmInetAddr(ipAddrString,&ipAddr))
         {
            if(ipAddrType == CM_IPV4ADDR_TYPE)
            {
               asCfg->dstAddrLst.nAddr[j].u.ipv4NetAddr   =  ntohl(ipAddr);
            }
#ifdef SB_IPV6_SUPPORTED
            else if(ipAddrType == CM_IPV6ADDR_TYPE)
            {
               asCfg->srcSctpAddr.nAddr[j].u.ipv6NetAddr   =  ntohl(ipAddr);
            }
#endif
         }
      }


   }
*/  
   RETVOID;
}/* czAcUtlBuildPeerCfgReq()*/

/*
*
*       Fun:   czAcUtlBuildUSapCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildUSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CzMngmt   *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildUSapCntrlReq(tcCb, spCb, czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
 
   CzCntrl *cntrl;
 
   TRC2(czAcUtlBuildUSapCntrlReq)
 
   cntrl = &czMangmt->t.cntrl;
 
   cntrl->action        = ADEL;
   cntrl->subAction     = NULLD;
   cntrl->u.sap.id      = CZAC_LCZ_DFLT_SPID;
#ifdef CZAC_LKSCTP 
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP)
    cntrl->u.sap.id = CZAC_LCZ_KSCTP_SPID;
#endif /* CZAC_LKSCTP */
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "uSapId",  &(cntrl->u.sap.id));
 
   RETVOID;
}/* czAcUtlBuildUSapCntrlReq()*/

/*
*
*       Fun:   czAcUtlBuildLSapCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildLSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CzMngmt   *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildLSapCntrlReq(tcCb, spCb, czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
 
   CzCntrl *cntrl;
 
   TRC2(czAcUtlBuildLSapCntrlReq)
 
   cntrl = &czMangmt->t.cntrl;
 
   cntrl->action        = ABND_ENA;
   cntrl->subAction     = SAELMNT;
   cntrl->u.sap.id      = CZAC_LCZ_DFLT_SPID;
#ifdef CZAC_LKSCTP 
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP)
    cntrl->u.sap.id = CZAC_LCZ_KSCTP_SPID;
#endif /* CZAC_LKSCTP */
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "lSapId",  &(cntrl->u.sap.id));
 
   RETVOID;
}/* czAcUtlBuildLSapCntrlReq()*/

/*
*
*       Fun:   czAcUtlBuildAssocCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildAssocCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CzMngmt   *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildAssocCntrlReq(tcCb, spCb, czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
 
   CzCntrl *cntrl;
 
   S8             ipAddrString[20]= CZAC_LCZ_IPADDR;
   CmInetIpAddr   ipAddr = 0;
   TRC2(czAcUtlBuildAssocCntrlReq)
 
   cntrl = &czMangmt->t.cntrl;
 
   cntrl->action        = AMODIFY;
   cntrl->subAction     = 0;
   cntrl->u.modPriAddrCntrl.peerId      = 1;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",  &(cntrl->u.modPriAddrCntrl.peerId));
   cntrl->u.modPriAddrCntrl.priDstAddr.type = CM_IPV4ADDR_TYPE; 
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,"ipAddrType", &cntrl->u.modPriAddrCntrl.priDstAddr.type);
    cntrl->u.modPriAddrCntrl.priDstAddr.u.ipv4NetAddr   =  ntohl(czAccCb.directives.baseIp);
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT , "ipAddress", &(cntrl->u.modPriAddrCntrl.priDstAddr.u.ipv4NetAddr));
     if(cntrl->u.modPriAddrCntrl.priDstAddr.type == CM_IPV4ADDR_TYPE)
     {
        if(ROK == cmInetAddr(ipAddrString,&ipAddr))
        {
           cntrl->u.modPriAddrCntrl.priDstAddr.u.ipv4NetAddr   =  ntohl(ipAddr);
        }
     }
#ifdef SB_IPV6_SUPPORTED
     else if(cntrl->u.modPriAddrCntrl.priDstAddr.type == CM_IPV6ADDR_TYPE)
     {
        cmInetPton6(&cntrl->u.modPriAddrCntrl.priDstAddr.u.ipv6NetAddr, ipAddrString);
     }
#endif /* SB_IPV6_SUPPORTED */


   RETVOID;
}/* czAcUtlBuildAssocCntrlReq()*/

/*
*
*       Fun:   czAcUtlBuildEndPtCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildEndPtCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CzMngmt   *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildEndPtCntrlReq(tcCb, spCb, czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
 
   CzCntrl *cntrl;
 
   TRC2(czAcUtlBuildEndPtCntrlReq)
 
   cntrl = &czMangmt->t.cntrl;
 
   cntrl->action        =AENA;
   cntrl->subAction     = 0;
   cntrl->u.endPtCntrl.endPtId      = 1;
   cntrl->u.endPtCntrl.tsapId      = CZAC_LCZ_DFLT_SPID;
 
#ifdef CZAC_LKSCTP 
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP)
   cntrl->u.endPtCntrl.tsapId = CZAC_LCZ_KSCTP_SPID;
#endif /* CZAC_LKSCTP */

   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subAction",  &(cntrl->subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "endPtId",  &(cntrl->u.endPtCntrl.endPtId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "tSapId",  &(cntrl->u.endPtCntrl.tsapId));
 
 
   RETVOID;
}/* czAcUtlBuildEndPtCntrlReq()*/


/*
*
*       Fun:   czAcUtlBuildLSapTrcCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildLSapTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CzMngmt   *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildLSapTrcCntrlReq(tcCb, spCb, czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
 
   CzCntrl *cntrl;
 
   TRC2(czAcUtlBuildLSapTrcCntrlReq)
 
   cntrl = &czMangmt->t.cntrl;
 
   cntrl->action        = AENA;
   cntrl->subAction     = SATRC;
   cntrl->u.lSapTrc.lSapId      = CZAC_LCZ_DFLT_SPID;
#ifdef CZAC_LKSCTP 
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP)
    cntrl->u.lSapTrc.lSapId = CZAC_LCZ_KSCTP_SPID;
#endif /* CZAC_LKSCTP */
   cntrl->u.lSapTrc.trcMask      = 0;
   cntrl->u.lSapTrc.trcLen      = 8;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "lSapId",  &(cntrl->u.lSapTrc.lSapId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "trcMask",  &(cntrl->u.lSapTrc.trcMask));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "trcLen",  &(cntrl->u.lSapTrc.trcLen));
 
   RETVOID;
}/* czAcUtlBuildLSapTrcCntrlReq()*/

/*
*
*       Fun:   czAcUtlBuildPNodeTrcCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildPNodeTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CzMngmt   *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildPNodeTrcCntrlReq(tcCb, spCb, czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
 
   CzCntrl *cntrl;
 
   TRC2(czAcUtlBuildPNodeTrcCntrlReq)
 
   cntrl = &czMangmt->t.cntrl;
 
   cntrl->action        = AENA;
   cntrl->subAction     = SATRC;
   cntrl->u.pNodeTrc.peerId     = CZAC_LCZ_PEERID;
   cntrl->u.pNodeTrc.trcMask    = 0xFF;
   cntrl->u.pNodeTrc.trcLen     = 8;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",  &(cntrl->u.pNodeTrc.peerId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "trcMask", &(cntrl->u.pNodeTrc.trcMask));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "trcLen",  &(cntrl->u.pNodeTrc.trcLen));
 
   RETVOID;
}/* czAcUtlBuildPNodeTrcCntrlReq()*/

/*
*
*       Fun:   czAcUtlBuildTrcCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CzMngmt   *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildTrcCntrlReq(tcCb, spCb, czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
 
   CzCntrl *cntrl;
 
   TRC2(czAcUtlBuildTrcCntrlReq)
 
   cntrl = &czMangmt->t.cntrl;
 
   cntrl->action        = AENA;
   cntrl->subAction     = SATRC;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
 
   RETVOID;
}/* czAcUtlBuildTrcCntrlReq()*/

/*
*
*       Fun:   czAcUtlBuildPeerCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildPeerCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CzMngmt   *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildPeerCntrlReq(tcCb, spCb, czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
 
   CzCntrl *cntrl;
 
   TRC2(czAcUtlBuildPeerCntrlReq)
 
   cntrl = &czMangmt->t.cntrl;
 
   cntrl->action        = ADEL;
   cntrl->subAction     = SAELMNT;

   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));

   cntrl->u.peer.peerId = CZAC_LCZ_PEERID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(cntrl->u.peer.peerId));
 
   RETVOID;
}/* czAcUtlBuildPeerCntrlReq()*/

/*
*
*       Fun:   czAcUtlBuildUstaCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
CzMngmt   *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildUstaCntrlReq(tcCb, spCb, czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
 
   CzCntrl *cntrl;
 
   TRC2(czAcUtlBuildUstaCntrlReq)
 
   cntrl = &czMangmt->t.cntrl;
 
   cntrl->action        = AENA;
   cntrl->subAction     = SAUSTA;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
 
   RETVOID;
}/* czAcUtlBuildUstaCntrlReq()*/

#ifdef DEBUGP
/*
*
*       Fun:   czAcUtlBuildDebugCntrlReq
*
*       Desc:  Utility Function to Build Debug Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildDebugCntrlReq
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb     *spCb,
CzMngmt    *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildDebugCntrlReq(tcCb, spCb,czMangmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
CzMngmt   *czMangmt;
#endif /* ANSI */
{
   CzCntrl *cntrl;
 
   TRC2(czAcUtlBuildDebugCntrlReq);
 
   cntrl = &czMangmt->t.cntrl;

   cntrl->action  = ADISIMM;
   cntrl->subAction   = SADBG;
   cntrl->u.dbg.dbgMask    = 0xFFFFFFFF;

   if(cmXtaCb.dbgMask >= CZAC_CZ_DBG)
      cntrl->action  = AENA;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16 , "action",  &(cntrl->action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16 , "subAction",  &(cntrl->subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32 , "dbgMask", &(cntrl->u.dbg.dbgMask));
 
   RETVOID;
}/* czAcUtlBuildDebugCntrlReq()*/

#endif /* ifdef DEBUGP */

/*
*
*       Fun:   czAcUtlBuildShutdownCntrlReq
*
*       Desc:  Utility Function to Build Entity Control Req
*
*       Ret:   ROK
*
*      
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI
PUBLIC Void czAcUtlBuildShutdownCntrlReq
(
CzMngmt     *czMangmt
)
#else /* ANSI */
PUBLIC Void czAcUtlBuildShutdownCntrlReq(czMangmt)
CzMngmt     *czMangmt;
#endif /* ANSI */
{
   CzCntrl *cntrl;
 
   TRC2(czAcUtlBuildShutdownCntrlReq);
 
   cntrl = &czMangmt->t.cntrl;
 
   cntrl->action        = ASHUTDOWN;
   cntrl->subAction    = SAELMNT;
 
   RETVOID;
}/* czAcUtlBuildShutdownCntrlReq()*/

/*
*
*       Fun:   czAcGetProc
*
*       Desc:  Utility Function to Get the ProcId
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI 
PUBLIC ProcId czAcGetProc
(
CmXtaSpCb  *spCb,
Ent ent,
Inst inst
)
#else /* ANSI */
PUBLIC ProcId czAcGetProc(spCb, ent, inst)
CmXtaSpCb  *spCb;
Ent ent;
Inst inst;
#endif /* ANSI */
{
   ProcId srcProcId = 0;
   
   TRC2(czAcGetProc)

   switch(ent)
   {
      case ENTSM:
      case ENTRS:
      {
         srcProcId = czAccCb.directives.xtaProcId;
      }
      break;
      case ENTSB:
      {
         #ifdef CMXTA_MASTER
         srcProcId = CMXTA_PROCID_SLAVE;
         #else /* CMXTA_MASTER */
         srcProcId = czAccCb.directives.xtaProcId;
         #endif /* CMXTA_MASTER */
         if(inst == (CMXTA_INST_ID + 5))
            srcProcId = CMXTA_PROCID_MASTER;
      }
      break;
      case ENTHI:
      {
         #ifdef CMXTA_MASTER
         srcProcId = CMXTA_PROCID_SLAVE;
         #else /* CMXTA_MASTER */
         /* Changes done for KSCTP */
         srcProcId = czAccCb.directives.xtaProcId;
         #endif /* CMXTA_MASTER */
      }
      break;
      case ENTCZ:
      {
         srcProcId   =  czAccCb.directives.eNb1ProcId;
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "procId", &(srcProcId));
      }
      break;
      default:
      break;
   }
   RETVALUE(srcProcId);
} /* czAcGetProc */

/*
*
*       Fun:   czAcGetPst
*
*       Desc:  Utility Function to Get the Pst
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_lczutl.c
*
*/
#ifdef ANSI 
PUBLIC Void czAcGetPst
(
CmXtaSpCb  *spCb,
Pst  *pst,
Ent srcEnt,
Inst srcInst,
Ent  dstEnt,
Inst dstInst
)
#else /* ANSI */
PUBLIC Void czAcGetPst(spCb, pst, srcEnt, srcInst, dstEnt, dstInst)
CmXtaSpCb  *spCb;
Pst  *pst;
Ent srcEnt;
Inst srcInst;
Ent  dstEnt;
Inst dstInst;
#endif /* ANSI */
{
   ProcId srcProcId     = 0;
   ProcId dstProcId     = 0;
   Bool   matchProc     = FALSE;

   TRC2(czAcGetPst)

#if (defined(SS_MULTIPLE_PROCS) || defined(CZAC_INTG_TEST))
   srcProcId   =  czAcGetProc(spCb, srcEnt, srcInst);
   dstProcId   =  czAcGetProc(spCb, dstEnt, dstInst);
   matchProc   =  TRUE;
#endif /* (defined(SS_MULTIPLE_PROCS) || defined(CZAC_INTG_TEST)) */

   cmXtaGetPst(pst, srcEnt, srcInst, dstEnt, dstInst, srcProcId, dstProcId, matchProc);

   RETVOID;

}
/********************************************************************30**

         End of file:     czac_lczutl.c@@/main/2 - Tue Aug 30 18:35:48 2011

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
/main/1      ---     sy        1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
