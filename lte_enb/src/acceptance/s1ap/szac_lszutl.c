
/********************************************************************20**

     Name:    S1AP- acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    szac_lszutl.c

     Sid:      szac_lszutl.c@@/main/4 - Mon Jan 10 22:15:54 2011

     Prg:     pk 
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

#include "sct.h"           /* SB (SCTP) layer */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA 
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer management defines for MGCP */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#include "sb_mtu.h"
#include "sb.h"
#endif    /* SB */

#include "cm_pasn.h"
#include "cm_xta.h" 
#include "sz.h"            /* defines and macros for MGCP */
#include "szt.h"            /* defines and macros for MGCP */
/* sz006.301: Removed un-necessary include files  */
#include "szac_asn.h"
#include "sz_err.h"        /* MG error defines */
#include "szac_acc.h"        /* defines for MGCP acceptance tests */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
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

#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCTP Interface Structures */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SCTP Interface Structures */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA 
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for MGCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#include "sb_mtu.x"
#include "sb.x"
#endif    /* SB */

#include "cm_pasn.x"
#include "cm_xta.x" 
#include "sz.x"            /* typedefs for MGCP */
#include "szac_acc.x"        /* typedefs for MGCP acceptance tests */
#include "szac_lsz.x"

/*
*  
*       Fun:   szAcUtlBuildGenCfgReq
*  
*       Desc:  Utility Function to Build General Configuration Req*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildGenCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
SzMngmt     *szMngmt
)
#else
PUBLIC Void szAcUtlBuildGenCfgReq(tcCb,spCb,szMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
SzMngmt    *szMngmt;
#endif
{
   /* local variables */
   SzGenCfg    *cfg;
   Pst          lmPst;              /* Post for layer manager */
 
   TRC2(szAcUtlBuildGenCfgReq)
 
   cfg   = &(szMngmt->u.cfg.u.gen);
   CMXTA_ZERO(cfg , sizeof (SzGenCfg));
 
  /*----------- Fill General Configuration Parameters ---------*/
 
   cfg->nmbSztSaps = (S16)SZAC_LSZ_MAX_SZTSAP;
   cfg->nmbSctSaps = (S16)SZAC_LSZ_MAX_SCTSAP;
   cfg->nmbConn = (U32)SZAC_LSZ_MAX_CONN;
   cfg->nmbPeer = (U32)SZAC_LSZ_MAX_PEER;
   cfg->timeRes = (Ticks)SZAC_LSZ_TIMERES;
#ifdef SZ_MME
   cfg->dynamPeerFlag = TRUE;
#endif
 
   szAcGetPst(spCb, &lmPst, ENTSZ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

 
   /* Layer Manager post structure */
   cmMemcpy((U8 *) &(cfg->lmPst), (U8 *) &(lmPst), (PTR) sizeof(Pst));
 

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "nmbSztSaps", &(cfg->nmbSztSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "nmbSctSaps", &(cfg->nmbSctSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nmbConn", &(cfg->nmbConn));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nmbPeer", &(cfg->nmbPeer));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "timeRes", &(cfg->timeRes));
#ifdef SZ_MME
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dynamicPeer", &(cfg->dynamPeerFlag));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "DefaultSapId", &(cfg->defDPeerUSapId));
#endif

   RETVOID;
} /* szAcUtlBuildGenCfgReq() */
 
 
 
/*
*
*       Fun:   szAcUtlBuildLSapCfgReq
*
*       Desc:  Utility Function to Build TSAP Configuration Req
*
*       Ret:   ROK
*
*       Notes: 1. Lower Interface is assumed to be Trillium SCTP by default.
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildLSapCfgReq
(
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
SzMngmt    *szMngmt
)
#else
PUBLIC Void szAcUtlBuildLSapCfgReq(tcCb,spCb,szMngmt)
CmXtaTCCb *tcCb;    /* tcCb data structure  */
CmXtaSpCb *spCb;
SzMngmt   *szMngmt;
#endif
{
   /* local variables */
   SzSctSapCfg  *cfg;
   Pst          entPst;
   U16          provType = ENTSB;
#ifdef LSZV1
   U16          numAddr = 1;
   U8           peerNode = 0;
   U8           ipAddrType = 0;
   S8           ipAddrString[20]= SZAC_LSZ_IPADDR;
   S8           dispString[20];
   U16          i;
   CmInetIpAddr ipAddr = 0;
#endif /* LSZV1 */
                           
 
   TRC2 (szAcUtlBuildLSapCfgReq)
 
   cfg   = &(szMngmt->u.cfg.u.sctSap);

   CMXTA_ZERO(cfg, sizeof (SzSctSapCfg));

   cfg->suId   = SZAC_LSZ_DFLT_SPID;
   cfg->spId   = SZAC_LSZ_DFLT_SUID;

#ifdef SZAC_LKSCTP
   provType =  ENTHI;
#endif
     
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U16,"provType",&provType);

   szAcGetPst(spCb, &entPst, ENTSZ, CMXTA_INST_ID, (Ent) provType, CMXTA_INST_ID);
#ifdef DM 
   if(provType == SZAC_SCTP_DM)
      szAcGetPst(spCb, &entPst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);
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
   cfg->tBndTmr.val = SZAC_LSZ_VAL_10;
   cfg->maxBndRetry = SZAC_LSZ_VAL_3;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(cfg->suId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(cfg->spId));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "tBndTmr.enb",  &(cfg->tBndTmr.enb));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , "tBndTmr.val",  &(cfg->tBndTmr.val));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , "maxBndRetry",  &(cfg->maxBndRetry));

#ifdef LSZV1
   SZAC_GET_IPADDR(ipAddr, TRUE);
   cfg->srcAddr.ipAddr.nmb  =   1;
   cfg->srcAddr.ipAddr.nAddr[0].type  =   CM_IPV4ADDR_TYPE;
   cfg->srcAddr.ipAddr.nAddr[0].u.ipv4NetAddr   =  ntohl(ipAddr);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "peerNode", &(peerNode));
   if(peerNode == SZAC_LSZ_ENB_PRC0)
   {
      cfg->srcAddr.sctPort = SZAC_LSZ_MME_SCTPORT;
   }
   else if(peerNode == SZAC_LSZ_MME_PRC1)
   {
      cfg->srcAddr.sctPort =   SZAC_LSZ_ENB_SCTPORT;
   }
   else if(peerNode == SZAC_LSZ_GW_PRC2)
   {
      if(cfg->suId == 0)
         cfg->srcAddr.sctPort = SZAC_LSZ_GW_SCTPORT2;
      else
         cfg->srcAddr.sctPort = SZAC_LSZ_GW_SCTPORT1;
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16 , "nmbOfAddr",  &(numAddr));
   cfg->srcAddr.ipAddr.nmb   =  (U8)numAddr;

   for(i =1; i < numAddr; i++)
   {
      ipAddrType  = CM_IPV4ADDR_TYPE;

      sprintf(dispString,"ipAddrType_%d_",i);
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8 , dispString, &(ipAddrType));
      sprintf(dispString,"ipAddr_%d_",i);
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT , dispString, &(ipAddrString));

      cfg->srcAddr.ipAddr.nAddr[i].type  = (U8)ipAddrType;

      if(ROK == cmInetAddr(ipAddrString,&ipAddr))
      {
         if(ipAddrType == CM_IPV4ADDR_TYPE)
         {
            cfg->srcAddr.ipAddr.nAddr[i].u.ipv4NetAddr   =  ntohl(ipAddr);
         }
#ifdef SB_IPV6_SUPPORTED
         else if(ipAddrType == CM_IPV6ADDR_TYPE)
         {
            cfg->srcAddr.ipAddr.nAddr[i].u.ipv6NetAddr   =  ntohl(ipAddr);
         }
#endif
      }
   }
#endif /* LSZV1 */

   RETVOID;
}/* szAcUtlBuildLSapCfgReq()*/

/*    
*        
*       Fun:   szAcUtlBuildUSapCfgReq
*     
*       Desc:  Utility Function to Build SSAP Configuration Req
*  
*       Ret:   ROK
*     
*       Notes: None
*              
*       File:  szac_lszutl.c
*  
*/ 
#ifdef ANSI
PUBLIC Void szAcUtlBuildUSapCfgReq 
(        
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
SzMngmt    *szMngmt
)
#else
PUBLIC Void szAcUtlBuildUSapCfgReq(tcCb,spCb,szMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
SzMngmt     *szMngmt;
#endif
{
 
   Pst      entPst;
   SzSztSapCfg    *cfg;

   cfg = &(szMngmt->u.cfg.u.sztSap);
   CMXTA_ZERO(cfg, sizeof (SzSztSapCfg));
   
   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &entPst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);
 
   cfg->spId = SZAC_LSZ_DFLT_SPID;
   cfg->selector = entPst.selector;
   cfg->mem.region = entPst.region;
   cfg->mem.pool = entPst.pool;
   cfg->priority = entPst.prior;
   cfg->route = entPst.route;
 

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "sapId",  &(cfg->spId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "selector",  &(cfg->selector));

 
   RETVOID;
}/* szAcUtlBuildUSapCfgReq()*/
 
/*
*  
*       Fun:   szAcUtlBuildProtCfgReq
*                   
*       Desc:  Utility Function to Build Protocol Configuration Req
*  
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*  
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildProtCfgReq
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb     *spCb,
SzMngmt    *szMngmt
)
#else
PUBLIC Void szAcUtlBuildProtCfgReq(tcCb, spCb, szMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
SzMngmt   *szMngmt;
#endif
{
#ifndef LSZV1
   S8             ipAddrString[20]= SZAC_LSZ_IPADDR;
   S8             dispString[20];
   CmInetIpAddr   ipAddr = 0;
   U16            numAddr = 1;
   U16            ipAddrType;
   U16            i;
#endif /* LSZV1 */
   U8             protNode;
   SzProtCfg     *protCfg;


   protCfg = &(szMngmt->u.cfg.u.prot);
   CMXTA_ZERO(protCfg, sizeof (SzProtCfg));

   /* Default initialisations */
   protNode = NULLD;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "protNode", &(protNode));

#ifndef LSZV1
   SZAC_GET_IPADDR(ipAddr, TRUE);
   protCfg->srcAddr.ipAddr.nmb  =   1;
   protCfg->srcAddr.ipAddr.nAddr[0].type  =   CM_IPV4ADDR_TYPE;
   protCfg->srcAddr.ipAddr.nAddr[0].u.ipv4NetAddr   =  ntohl(ipAddr);
#endif /* LSZV1 */

   if(protNode == SZAC_LSZ_ENB_PRC0)
   {
#ifdef SZ_ENB
      protCfg->nodeType =   LSZ_NODE_ENB;
      protCfg->u.eNbId     =   SZAC_LSZ_ENB_PRC0;
#ifndef LSZV1
      protCfg->srcAddr.sctPort =   SZAC_LSZ_ENB_SCTPORT;

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "sctPort", &(protCfg->srcAddr.sctPort));
#endif /* LSZV1 */
#endif
   }
   else if(protNode == SZAC_LSZ_MME_PRC1)
   {
#ifdef SZ_MME
      protCfg->nodeType =   LSZ_NODE_MME;
      protCfg->u.mmeId.mmeCode[0]     =   SZAC_LSZ_MME_PRC1;
#ifndef LSZV1
      protCfg->srcAddr.sctPort =   SZAC_LSZ_MME_SCTPORT;
#endif /* LSZV1 */
#endif
   }
   else if(protNode == SZAC_LSZ_GW_PRC2)
   {
#ifdef SZ_ENB
      protCfg->nodeType =   LSZ_NODE_GW;
      protCfg->u.eNbId     =   SZAC_LSZ_ENB_PRC0;
#ifndef LSZV1
      protCfg->srcAddr.sctPort =   SZAC_LSZ_ENB_SCTPORT;

#endif /* LSZV1 */
#endif /* SZ_ENB */
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "nodeType",
                                                   &(protCfg->nodeType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nodeTypeErr",
                                                   &(protCfg->nodeType));

#ifndef LSZV1
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16 , "nmbOfAddr",  &(numAddr));
   protCfg->srcAddr.ipAddr.nmb   =  (U8)numAddr;

   for(i =1; i < numAddr; i++)
   {
      ipAddrType  = CM_IPV4ADDR_TYPE;

      sprintf(dispString,"ipAddrType_%d_",i);
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8 , dispString, &(ipAddrType));
      sprintf(dispString,"ipAddr_%d_",i);
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT , dispString, &(ipAddrString));

      protCfg->srcAddr.ipAddr.nAddr[i].type  = (U8)ipAddrType;

      if(ROK == cmInetAddr(ipAddrString,&ipAddr))
      {
         if(ipAddrType == CM_IPV4ADDR_TYPE)
         {
            protCfg->srcAddr.ipAddr.nAddr[i].u.ipv4NetAddr   =  ntohl(ipAddr);
         }
#ifdef SB_IPV6_SUPPORTED
         else if(ipAddrType == CM_IPV6ADDR_TYPE)
         {
            protCfg->srcAddr.ipAddr.nAddr[i].u.ipv6NetAddr   =  ntohl(ipAddr);
         }
#endif
      }
   }
#endif /* LSZV1 */

#ifdef SZ_ENB
   if(protCfg->nodeType == LSZ_NODE_ENB)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "eNbId",      &(protCfg->u.eNbId));
   }
#endif

#ifdef SZ_MME
   if(protCfg->nodeType == LSZ_NODE_ENB)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "mmeCode", &(protCfg->u.mmeId.mmeCode[0]));
   }
#endif

   RETVOID;
}/* szAcUtlBuildProtCfgReq()*/
 
 
/*
*
*       Fun:   szAcUtlBuildPeerCfgReq
*
*       Desc:  Utility Function to Build Entity Configuration Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildPeerCfgReq
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb     *spCb,
SzMngmt    *szMngmt
)
#else
PUBLIC Void szAcUtlBuildPeerCfgReq(tcCb, spCb, szMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
SzMngmt    *szMngmt;
#endif
{
   SzPeerCfg      *cfg = NULLP;
   S8             ipAddrString[20]=SZAC_LSZ_IPADDR;
   S8             dispString[30];
   CmInetIpAddr   ipAddr = 0;
   U16            i, j, numAddr;
   U16            ipAddrType;
   U8             peerNodeCfg = 0;
   SzAssocCfg     *asCfg;
   U8             pool = 0;
   U8             region = 0;
#ifdef LSZV1
   U32           skipUeSm = FALSE;
#endif /* LSZV1 */
 
   TRC2 (szAcUtlBuildPeerCfgReq);
 
   cfg = &(szMngmt->u.cfg.u.peer);
   CMXTA_ZERO(cfg, sizeof (SzPeerCfg));
 
   /* Default configurations */
   peerNodeCfg    =  NULLP;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "peerNodeCfg",  &(peerNodeCfg));

   cfg->nmbPeers = (U32)SZAC_LSZ_NUM_PEERS;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "nmbPeers",  &(cfg->nmbPeers));
   if(cfg->nmbPeers > 0)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "region", &(region));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "pool", &(pool));

      if(region != 0 && pool != 0)
      {
         if((SGetSBuf(region, pool, (Data **) &cfg->peerInfo, (sizeof(SzPeerInfo)* cfg->nmbPeers))) == ROK)
         cmMemset((U8 *)(&cfg->peerInfo), 0, (sizeof(SzPeerInfo)* cfg->nmbPeers));
      }

      else
      {
         CMXTA_ALLOC(&cfg->peerInfo, sizeof(SzPeerInfo)* cfg->nmbPeers); 
      }
   }

   if(peerNodeCfg == SZAC_LSZ_ENB_PRC0)
   {
      cfg->peerInfo[0].type      =  LSZ_NODE_ENB;   
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "nodeType",  &(cfg->peerInfo[0].type));

      cfg->peerInfo[0].peerId.pres   =  TRUE; 
      cfg->peerInfo[0].peerId.val    =  SZAC_LSZ_ENB_PRC0; 
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "PeerId",  &(cfg->peerInfo[0].peerId.val));
      cfg->peerInfo[0].uSapId     =  1;  
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "uSapId",  &(cfg->peerInfo[0].uSapId));
      cfg->peerInfo[0].sapId     =  1;  
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "sapId",  &(cfg->peerInfo[0].sapId));
      cfg->peerInfo[0].assocCfg.locOutStrms        =  SZAC_LSZ_OUT_STRMS;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "locOutStrms", 
                                                    &(cfg->peerInfo[0].assocCfg.locOutStrms));

      SZAC_GET_IPADDR(ipAddr, FALSE)
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "Ipaddr",  &(ipAddr));
      cfg->peerInfo[0].assocCfg.priDstAddr.type    =  CM_IPV4ADDR_TYPE;
      cfg->peerInfo[0].assocCfg.priDstAddr.u.ipv4NetAddr   =  ntohl(ipAddr);
      cfg->peerInfo[0].assocCfg.dstAddrLst.nmb     =  1;
      cfg->peerInfo[0].assocCfg.dstAddrLst.nAddr[0].type   =  CM_IPV4ADDR_TYPE;
      cfg->peerInfo[0].assocCfg.dstAddrLst.nAddr[0].u.ipv4NetAddr   =  ntohl(ipAddr);

      cfg->peerInfo[0].assocCfg.dstPort            =  SZAC_LSZ_ENB_SCTPORT;
      cfg->peerInfo[0].assocCfg.nmbRetry           =  SZAC_LSZ_VAL_3;
      cfg->peerInfo[0].assocCfg.tmrAssocRecov.enb  =  TRUE;
      cfg->peerInfo[0].assocCfg.tmrAssocRecov.val  =  SZAC_LSZ_VAL_50;

#ifdef LSZV1
      /* Bypass the UE state machine */
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "skipUeSm", &(skipUeSm));
      cfg->peerInfo[0].skipUeSm = skipUeSm;
      if(skipUeSm)
      {
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(cfg->peerInfo[0].peerId.val));
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "port", &(cfg->peerInfo[0].assocCfg.dstPort));
      }
#endif /* LSZV1 */
      /* Return from function */
      RETVOID;
   }
   else if(peerNodeCfg == SZAC_LSZ_MME_PRC1)
   {
      cfg->peerInfo[0].type      =  LSZ_NODE_MME;   
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "nodeType",  &(cfg->peerInfo[0].type));

      cfg->peerInfo[0].peerId.pres   =  TRUE; 
      cfg->peerInfo[0].peerId.val    =  SZAC_LSZ_MME_PRC1; 
      cfg->peerInfo[0].uSapId     =  0;  
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "uSapId",  &(cfg->peerInfo[0].uSapId));
      cfg->peerInfo[0].sapId     =  0;  
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "sapId",  &(cfg->peerInfo[0].sapId));
      cfg->peerInfo[0].assocCfg.locOutStrms        =  SZAC_LSZ_OUT_STRMS;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "locOutStrms", 
                                                    &(cfg->peerInfo[0].assocCfg.locOutStrms));

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "comProcStrmPres",  &(cfg->peerInfo[0].assocCfg.comProcStrm.pres));
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "comProcStrmVal",  &(cfg->peerInfo[0].assocCfg.comProcStrm.val));

      SZAC_GET_IPADDR(ipAddr, FALSE);
      cfg->peerInfo[0].assocCfg.priDstAddr.type    =  CM_IPV4ADDR_TYPE;
      cfg->peerInfo[0].assocCfg.priDstAddr.u.ipv4NetAddr   =  ntohl(ipAddr);
      cfg->peerInfo[0].assocCfg.dstPort            =  SZAC_LSZ_MME_SCTPORT;
      cfg->peerInfo[0].assocCfg.dstAddrLst.nmb     =  1;
      cfg->peerInfo[0].assocCfg.dstAddrLst.nAddr[0].type   =  CM_IPV4ADDR_TYPE;
      cfg->peerInfo[0].assocCfg.dstAddrLst.nAddr[0].u.ipv4NetAddr   =  ntohl(ipAddr);

      cfg->peerInfo[0].assocCfg.nmbRetry           =  SZAC_LSZ_VAL_3;
      cfg->peerInfo[0].assocCfg.tmrAssocRecov.enb  =  TRUE;
      cfg->peerInfo[0].assocCfg.tmrAssocRecov.val  =  SZAC_LSZ_VAL_50;

      /* Bypass the UE state machine */
#ifdef LSZV1
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "skipUeSm", &(skipUeSm));
      cfg->peerInfo[0].skipUeSm = skipUeSm;

      if(skipUeSm)
      {
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(cfg->peerInfo[0].peerId.val));
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "port", &(cfg->peerInfo[0].assocCfg.dstPort));
      }
#endif /* LSZV1 */
      /* Return from function */
      RETVOID;
   }

   /* Do some manual configuration */

   /* SAlloc allocate memory for VX workks.  */
   
   for(i = 0;i < cfg->nmbPeers; i++)
   {
      CMXTA_ZERO(&cfg->peerInfo[i], sizeof (SzPeerInfo));

      sprintf(dispString,"peerInfo_%d_.type",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, dispString,  &(cfg->peerInfo[i].type));

      sprintf(dispString,"peerInfo_%d_.peerId",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, dispString,  &(cfg->peerInfo[i].peerId));

      sprintf(dispString,"peerInfo_%d_.sapId",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, dispString,  &(cfg->peerInfo[i].sapId));

      /* assoc config details */
      asCfg =  &cfg->peerInfo[i].assocCfg;

      sprintf(dispString,"peerInfo_%d_.locOutStrms",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, dispString,  &(asCfg->locOutStrms));

      sprintf(dispString,"peerInfo_%d_.comProcStrm.pres",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, dispString,  &(asCfg->comProcStrm.pres));

      sprintf(dispString,"peerInfo_%d_.comProcStrm.spare1",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, dispString,  &(asCfg->comProcStrm.spare1));

      sprintf(dispString,"peerInfo_%d_.comProcStrm.val",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, dispString,  &(asCfg->comProcStrm.val));

#ifdef ALIGN_64
      sprintf(dispString,"peerInfo_%d_.comProcStrm.spare2",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, dispString,  &(asCfg->comProcStrm.spare2));
#endif

      sprintf(dispString,"peerInfo_%d_.priDstAddr.type",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, dispString,  &(ipAddrType));

      asCfg->priDstAddr.type  = (U8)ipAddrType;

      sprintf(dispString,"peerInfo_%d_.priDstAddr.addr",i);
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

      sprintf(dispString,"peerInfo_%d_.dstPort",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, dispString, &(asCfg->dstPort));

      sprintf(dispString,"peerInfo_%d_.nmbOfAddr",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16 , dispString,  &(numAddr));
      asCfg->dstAddrLst.nmb   =  (U8)numAddr;

      for(j =0; j < numAddr; j++)
      {
         ipAddrType  = CM_IPV4ADDR_TYPE;

         sprintf(dispString,"peerInfo_%d_.dstAddr_%d_.type",i,j);
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8 , dispString, &(ipAddrType));

         sprintf(dispString,"peerInfo_%d_.dstAddr_%d_.ipAddr",i, j);
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

      sprintf(dispString,"peerInfo_%d_.nmbRetry",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16 , dispString,  &(asCfg->nmbRetry));

      asCfg->tmrAssocRecov.enb = FALSE;
      asCfg->tmrAssocRecov.val = 20;

      sprintf(dispString,"peerInfo_%d_.tmrAssocRecov.enb",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16 , dispString,  &(asCfg->tmrAssocRecov.enb));

      sprintf(dispString,"peerInfo_%d_.tmrAssocRecov.val",i);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16 , dispString,  &(asCfg->tmrAssocRecov.val));

      /* Bypass the UE state machine */
#ifdef LSZV1
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "skipUeSm", &(skipUeSm));
      cfg->peerInfo[i].skipUeSm = skipUeSm;
#endif /* LSZV1 */
   }
 
   RETVOID;
}/* szAcUtlBuildPeerCfgReq()*/

/*
*
*       Fun:   szAcUtlBuildUSapCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildUSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
SzMngmt   *szMngmt
)
#else
PUBLIC Void szAcUtlBuildUSapCntrlReq(tcCb, spCb, szMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
SzMngmt   *szMngmt;
#endif
{
 
   SzCntrl *cntrl;
 
   TRC2(szAcUtlBuildUSapCntrlReq)
 
   cntrl = &szMngmt->u.cntrl;
 
   cntrl->action        = ADEL;
   cntrl->subAction     = NULLD;
   cntrl->u.sap.id      = SZAC_LSZ_DFLT_SPID;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "uSapId",  &(cntrl->u.sap.id));
 
   RETVOID;
}/* szAcUtlBuildUSapCntrlReq()*/

/*
*
*       Fun:   szAcUtlBuildLSapCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildLSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
SzMngmt   *szMngmt
)
#else
PUBLIC Void szAcUtlBuildLSapCntrlReq(tcCb, spCb, szMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
SzMngmt   *szMngmt;
#endif
{
 
   SzCntrl *cntrl;
 
   TRC2(szAcUtlBuildLSapCntrlReq)
 
   cntrl = &szMngmt->u.cntrl;
 
   cntrl->action        = ABND_ENA;
   cntrl->subAction     = 0;
   cntrl->u.sap.id      = SZAC_LSZ_DFLT_SPID;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "lSapId",  &(cntrl->u.sap.id));
 
   RETVOID;
}/* szAcUtlBuildLSapCntrlReq()*/

/*
*
*       Fun:   szAcUtlBuildLSapTrcCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildLSapTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
SzMngmt   *szMngmt
)
#else
PUBLIC Void szAcUtlBuildLSapTrcCntrlReq(tcCb, spCb, szMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
SzMngmt   *szMngmt;
#endif
{
 
   SzCntrl *cntrl;
 
   TRC2(szAcUtlBuildLSapTrcCntrlReq)
 
   cntrl = &szMngmt->u.cntrl;
 
   cntrl->action        = AENA;
   cntrl->subAction     = SATRC;
   cntrl->u.lSapTrc.lSapId      = SZAC_LSZ_DFLT_SPID;
   cntrl->u.lSapTrc.trcMask      = 0;
   cntrl->u.lSapTrc.trcLen      = 8;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "lSapId",  &(cntrl->u.lSapTrc.lSapId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "trcMask",  &(cntrl->u.lSapTrc.trcMask));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "trcLen",  &(cntrl->u.lSapTrc.trcLen));
 
   RETVOID;
}/* szAcUtlBuildLSapTrcCntrlReq()*/

/*
*
*       Fun:   szAcUtlBuildPNodeTrcCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildPNodeTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
SzMngmt   *szMngmt
)
#else
PUBLIC Void szAcUtlBuildPNodeTrcCntrlReq(tcCb, spCb, szMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
SzMngmt   *szMngmt;
#endif
{
 
   SzCntrl *cntrl;
 
   TRC2(szAcUtlBuildPNodeTrcCntrlReq)
 
   cntrl = &szMngmt->u.cntrl;
 
   cntrl->action        = AENA;
   cntrl->subAction     = SATRC;
   cntrl->u.pNodeTrc.peerId.pres    = TRUE;
   cntrl->u.pNodeTrc.peerId.val     = SZAC_LSZ_PEERID;
   cntrl->u.pNodeTrc.trcMask    = 0xFF;
   cntrl->u.pNodeTrc.trcLen     = 8;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",  &(cntrl->u.pNodeTrc.peerId.val));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U32, "trcMask", &(cntrl->u.pNodeTrc.trcMask));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "trcLen",  &(cntrl->u.pNodeTrc.trcLen));
 
   RETVOID;
}/* szAcUtlBuildPNodeTrcCntrlReq()*/

/*
*
*       Fun:   szAcUtlBuildTrcCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
SzMngmt   *szMngmt
)
#else
PUBLIC Void szAcUtlBuildTrcCntrlReq(tcCb, spCb, szMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
SzMngmt   *szMngmt;
#endif
{
 
   SzCntrl *cntrl;
 
   TRC2(szAcUtlBuildTrcCntrlReq)
 
   cntrl = &szMngmt->u.cntrl;
 
   cntrl->action        = AENA;
   cntrl->subAction     = SATRC;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
 
   RETVOID;
}/* szAcUtlBuildTrcCntrlReq()*/

/*
*
*       Fun:   szAcUtlBuildPeerCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildPeerCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
SzMngmt   *szMngmt
)
#else
PUBLIC Void szAcUtlBuildPeerCntrlReq(tcCb, spCb, szMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
SzMngmt   *szMngmt;
#endif
{
 
   SzCntrl *cntrl;
   U16    i;
   Txt   dispString[20];
 
   TRC2(szAcUtlBuildPeerCntrlReq)
 
   cntrl = &szMngmt->u.cntrl;
 
   cntrl->action        = ADEL;
   cntrl->subAction     = SAELMNT;
   cntrl->u.peer.nmbPeers = SZAC_LSZ_NUM_PEERS;

   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "nmbPeers",  &(cntrl->u.peer.nmbPeers));

   if(cntrl->action != ADEL)
   {
      cntrl->u.peer.nmbPeers = 0;
   }

   if (cntrl->u.peer.nmbPeers > 0)
   {
      CMXTA_ALLOC(&cntrl->u.peer.peerId, (sizeof(TknU32) * cntrl->u.peer.nmbPeers)); 

      cntrl->u.peer.peerId[0].pres = TRUE;
      cntrl->u.peer.peerId[0].val = SZAC_LSZ_PEERID;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(cntrl->u.peer.peerId[0].val));
   }
 

   for (i = 0; i < cntrl->u.peer.nmbPeers; i++)
   {
      sprintf(dispString, "peerId_%d",i);
      cntrl->u.peer.peerId[i].pres = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, dispString, &(cntrl->u.peer.peerId[i].val));
   }
 
   RETVOID;
}/* szAcUtlBuildPeerCntrlReq()*/

/*
*
*       Fun:   szAcUtlBuildUstaCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
SzMngmt   *szMngmt
)
#else
PUBLIC Void szAcUtlBuildUstaCntrlReq(tcCb, spCb, szMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
SzMngmt   *szMngmt;
#endif
{
 
   SzCntrl *cntrl;
 
   TRC2(szAcUtlBuildUstaCntrlReq)
 
   cntrl = &szMngmt->u.cntrl;
 
   cntrl->action        = AENA;
   cntrl->subAction     = SAUSTA;
 
   /* Getting these values from TA*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "action",  &(cntrl->action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "subaction",  &(cntrl->subAction));
 
   RETVOID;
}/* szAcUtlBuildUstaCntrlReq()*/

#ifdef DEBUGP
/*
*
*       Fun:   szAcUtlBuildDebugCntrlReq
*
*       Desc:  Utility Function to Build Debug Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildDebugCntrlReq
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb     *spCb,
SzMngmt    *szMngmt
)
#else
PUBLIC Void szAcUtlBuildDebugCntrlReq(tcCb, spCb,szMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
SzMngmt   *szMngmt;
#endif
{
   SzCntrl *cntrl;
 
   TRC2(szAcUtlBuildDebugCntrlReq);
 
   cntrl = &szMngmt->u.cntrl;

   cntrl->action  = ADISIMM;
   cntrl->subAction   = SADBG;
   cntrl->u.dbg.dbgMask    = 0xFFFFFFFF;

   if(cmXtaCb.dbgMask >= SZAC_SZ_DBG)
      cntrl->action  = AENA;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16 , "action",  &(cntrl->action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32 , "dbgMask", &(cntrl->u.dbg.dbgMask));
 
   RETVOID;
}/* szAcUtlBuildDebugCntrlReq()*/

#endif /* ifdef DEBUGP */

/*
*
*       Fun:   szAcUtlBuildShutdownCntrlReq
*
*       Desc:  Utility Function to Build Entity Control Req
*
*       Ret:   ROK
*
*      
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI
PUBLIC Void szAcUtlBuildShutdownCntrlReq
(
SzMngmt     *szMngmt
)
#else
PUBLIC Void szAcUtlBuildShutdownCntrlReq(szMngmt)
SzMngmt     *szMngmt;
#endif
{
   SzCntrl *cntrl;
 
   TRC2(szAcUtlBuildShutdownCntrlReq);
 
   cntrl = &szMngmt->u.cntrl;
 
   cntrl->action        = ASHUTDOWN;
   cntrl->subAction    = SAELMNT;
 
   RETVOID;
}/* szAcUtlBuildShutdownCntrlReq()*/

/*
*
*       Fun:   szAcGetProc
*
*       Desc:  Utility Function to Get the ProcId
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI 
PUBLIC ProcId szAcGetProc
(
CmXtaSpCb  *spCb,
Ent ent,
Inst inst
)
#else
PUBLIC ProcId szAcGetProc(spCb, ent, inst)
CmXtaSpCb  *spCb;
Ent ent;
Inst inst;
#endif
{
   ProcId procId = 0;
   switch(ent)
   {
      case ENTSM:
      case ENTUZ:
      {
         procId = szAccCb.directives.xtaProcId;
      }
      break;
      case ENTSB:
      {
         if(inst == CMXTA_INST_ID)
         {
            procId = szAccCb.directives.eNbProcId;
#ifdef SZAC_INTG_TEST
            {
               U16 sbType = SZAC_ENB_PROC;
               /* sz003.301: Made procId as U16 as it is required to have procId
                * greater than 200 */
               cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "procId", &(sbType));
               procId = (sbType == SZAC_ENB_PROC)? ( szAccCb.directives.eNbProcId):( szAccCb.directives.mmeProcId);
            }
#endif /* SZAC_INTG_TEST */
            /* sz003.301: Updted for PSF-S1AP 3.1 release. Added Transport
             * layer procId assignment */
#ifdef CMXTA_FTHA_INTEGRATED
            procId = szAccCb.directives.tptProcId;
#endif /* CMXTA_FTHA_INTEGRATED */
         }
         else   /* Dummy SCTP */
         {
            procId = szAccCb.directives.xtaProcId;
         }
      }
      break;
      case ENTHI:
      {
         procId = szAccCb.directives.eNbProcId;
#ifdef SZAC_INTG_TEST
         {
            U16 hiType = SZAC_ENB_PROC;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "procId", &(hiType));
            procId = (hiType == SZAC_ENB_PROC)? ( szAccCb.directives.eNbProcId):( szAccCb.directives.mmeProcId);
         }
#endif /* SZAC_INTG_TEST */
         /* sz003.301: Updted for PSF-S1AP 3.1 release. Added Transport
          * layer procId assignment */
#ifdef CMXTA_FTHA_INTEGRATED
            procId = szAccCb.directives.tptProcId;
#endif /* CMXTA_FTHA_INTEGRATED */
      }
      break;
      case ENTSZ:
      {
         /* sz003.301: Made procId as U16 as it is required to have procId
          * greater than 200 */
         U16 szType = SZAC_ENB_PROC;
         procId   =  szAccCb.directives.eNbProcId;
         /* sz003.301: Made procId as U16 as it is required to have procId
          * greater than 200 */
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "procId", &(szType));
         switch(szType)
         {
            case SZAC_ENB_PROC:
               procId = szAccCb.directives.eNbProcId;
               break;
            case SZAC_MME_PROC:
               procId = szAccCb.directives.mmeProcId;
               break;
            case SZAC_SBY_PROC:
               procId = szAccCb.directives.sbyProcId;
               break;
         }
         /* procId = (szType == SZAC_ENB_PROC)? ( szAccCb.directives.eNbProcId):( szAccCb.directives.mmeProcId); */
      }
      break;
      default:
      break;
   }
   RETVALUE(procId);
} /* szAcGetProc */

/*
*
*       Fun:   szAcGetPst
*
*       Desc:  Utility Function to Get the Pst
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_lszutl.c
*
*/
#ifdef ANSI 
PUBLIC Void szAcGetPst
(
CmXtaSpCb  *spCb,
Pst  *pst,
Ent srcEnt,
Inst srcInst,
Ent  dstEnt,
Inst dstInst
)
#else
PUBLIC Void szAcGetPst(spCb, pst, srcEnt, srcInst, dstEnt, dstInst)
CmXtaSpCb  *spCb;
Pst  *pst;
Ent srcEnt;
Inst srcInst;
Ent  dstEnt;
Inst dstInst;
#endif
{
   ProcId srcProcId     = 0;
   ProcId dstProcId     = 0;
   Bool   matchProc     = FALSE;

   /* sz003.301: Updted for PSF-S1AP 3.1 release. Added CMXTA FT/HA
    * integrated flag */
#if (defined(SS_MULTIPLE_PROCS) || defined(SZAC_INTG_TEST) || defined (CMXTA_FTHA_INTEGRATED))
   srcProcId   =  szAcGetProc(spCb, srcEnt, srcInst);
   dstProcId   =  szAcGetProc(spCb, dstEnt, dstInst);
   matchProc   =  TRUE;
#endif

   cmXtaGetPst(pst, srcEnt, srcInst, dstEnt, dstInst, srcProcId, dstProcId, matchProc);
}
/********************************************************************30**

         End of file:     szac_lszutl.c@@/main/4 - Mon Jan 10 22:15:54 2011

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
/main/4      ---      pkaX  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
