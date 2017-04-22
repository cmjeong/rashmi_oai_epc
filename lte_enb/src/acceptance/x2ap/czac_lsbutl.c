
/********************************************************************20**

     Name:     X2AP

     Type:     C source file

     Desc:     C code for layer manager service provider primitives that
               are usually supplied by the customer.
               - Copy contents to the queue.
               - Display the results of the received primitive.

     File:     cz_lsbcb.c

     Sid:      czac_lsbutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:28 2015

     Prg:      sy

*********************************************************************21*/

/*

  smsbbdy1.c - Stack Manager for the SCTP layer.

Following functions are provided in this file:
         czAcSmMiLsbCfgCfm    - Configuration confirm
         czAcSmMiLsbStsCfm    - Statistics confirm
         czAcSmMiLsbStaCfm    - Status confirm
         czAcSmMiLsbCntrlCfm  - Control confirm
         czAcSmMiLsbStaInd    - Status indication
         czAcSmMiLsbTrcInd    - Trace indication
         smSbActvInit     - Stack Manager initialization
*/

/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000163                      SCTP layer
 */

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
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "lcz.h"           /* layer management defines for X2AP */

#ifdef HI
#include "lhi.h"
#endif

#include "sct.h"           /* SB (SCTP) layer */
#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h" 
#include "cz.h"            /* defines and macros for X2AP */
#include "czt.h"            /* defines and macros for X2AP */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for X2AP acceptance tests */

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
#include "cm_pasn.x"       /* Common Asn.1 library           */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SCTP Interface Structures */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* SCTP Interface Structures */
#include "lcz.x"           /* layer management typedefs for X2AP */

#ifdef HI
#include "lhi.x"
#endif

#include "sct.x"           /* SB (SCTP) layer */
#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for X2AP */
#include "czac_acc.x"        /* typedefs for X2AP acceptance tests */
#include "czac_lsb.x"

/* cz001.101 : CR Fixes. */
#ifdef SB
/*
*
*       Fun:   czAcUtlLsbBldSctSapCfg
*
*       Desc:  Function for building SSAP configuration for SCTP interface
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  xx_sbhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlLsbBldSctSapCfg
(
CmXtaTCCb     *tcCb,   /* tcCb data structure  */
CmXtaSpCb     *spCb,
SpId       spId,
SbMgmt     *cfg     /* Configuration structure */
)
#else
PUBLIC S16 czAcUtlLsbBldSctSapCfg(tcCb, spCb, spId, cfg)
CmXtaTCCb     *tcCb;   /* tcCb data structure  */
CmXtaSpCb     *spCb;
SpId       spId;
SbMgmt     *cfg;    /* Configuration structure */
#endif
{
   SbSctSapCfg   *sapCfg;
   Pst            entPst;
   S16            entity;
 

   TRC2(czAcUtlLsbBldSctSapCfg)

   sapCfg = &(cfg->t.cfg.s.sctSapCfg);

   entity = ENTCZ;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "entity",  &(entity));
   czAcGetPst(spCb, &entPst, ENTSB, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);

   sapCfg->sel = entPst.selector;

   sapCfg->swtch         = LSB_SW_RFC_REL0;
   sapCfg->memId.region = DFLT_REGION;
   sapCfg->memId.pool   = DFLT_POOL;
   sapCfg->prior        = PRIOR0;
   sapCfg->route        = RTESPEC;
   sapCfg->spId         = spId;
   sapCfg->reConfig.maxAckDelayTm = 10;  /* increased from 2;
                                         Equivalent of 200 ms, TBD*/
   sapCfg->reConfig.maxAckDelayDg = 2;
   sapCfg->reConfig.rtoInitial = 100;
   sapCfg->reConfig.rtoMin     = 5;
   sapCfg->reConfig.rtoMax     = 40;
   sapCfg->reConfig.cookieLife = 5000;   /* increased from 500 */
   sapCfg->reConfig.intervalTm = 50;
   sapCfg->reConfig.freezeTm   = 15;
   sapCfg->reConfig.flcUpThr   = 200;    /* number of packets */
   sapCfg->reConfig.flcLowThr  = 150;
   sapCfg->reConfig.negAbrtFlg = TRUE;
   sapCfg->reConfig.handleInitFlg = FALSE; /* SCTP layer will handle the init */
#ifdef LSB4
   sapCfg->reConfig.bundleTm = 2;
#endif /* LSB4 */
#ifdef LSB8
   sapCfg->reConfig.maxBurst = 4;
   sapCfg->reConfig.maxHbBurst = 1;
   sapCfg->reConfig.t5SdownGrdTm = 5 * sapCfg->reConfig.rtoMax;
#endif /* LSB8 */

   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   czAcUtlLsbBldTSapCfg
*
*       Desc:  Function for building TSAP configuration for SCTP interface
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  xx_sbhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlLsbBldTSapCfg
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb   *spCb,
SuId       suId,
SpId       spId,
SbMgmt     *cfg     /* Configuration structure */
)
#else
PUBLIC S16 czAcUtlLsbBldTSapCfg(tcCb, spCb, suId, spId, cfg)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb   *spCb;
SuId       suId;
SpId       spId;
SbMgmt     *cfg;     /* Configuration structure */
#endif
{
   SbTSapCfg      *tSapCfg;
   CmTptAddr      tmpAddr;
   CmInetIpAddr   ipAddr = 0;
#ifdef SCT_ENDP_MULTI_IPADDR
   CmInetIpAddr   ipAddr2 = 0;
#endif
   Pst   pst;
   U16   cnt;

   TRC2(czAcUtlLsbBldTSapCfg)

   tSapCfg = &(cfg->t.cfg.s.tSapCfg);

   /*-- Get the Pst information here --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

   tSapCfg->sel = pst.selector;

   tSapCfg->ent            = ENTHI;
   tSapCfg->swtch          = LSB_SW_RFC_REL0;
   tSapCfg->inst           = pst.dstInst;
   tSapCfg->procId         = pst.dstProcId;
   tSapCfg->memId.region   = DFLT_REGION;
   tSapCfg->memId.pool     = DFLT_POOL;
   tSapCfg->prior          = PRIOR0;
   tSapCfg->route          = RTESPEC;
   tSapCfg->suId           = suId;

   /*--
   tSapCfg->srcNAddrLst.nmb = 1;
   tSapCfg->srcNAddrLst.nAddr[0].type = CM_NETADDR_IPV4;
   tSapCfg->srcNAddrLst.nAddr[0].u.ipv4NetAddr = CM_INET_INADDR_ANY;
   --*/

   tSapCfg->srcNAddrLst.nmb = 0;
   cnt = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,"nmbAddrLst", &cnt);

   /*fill the tpt address*/
#ifdef SB_IPV6_SUPPORTED
   tmpAddr.type = CM_TPTADDR_IPV6;
   tmpAddr.u.ipv6TptAddr.port = 2827;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,"port", &(tmpAddr.u.ipv6TptAddr.port));
#else
   tmpAddr.type = CM_TPTADDR_IPV4;
   tmpAddr.u.ipv4TptAddr.port = 2827;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,"port", &(tmpAddr.u.ipv4TptAddr.port));
#endif
   /* X2AP related changes       *
    * spId 0 is connected to ENB *
    * spId 1 is connected to MME */
/*
#ifndef WIN32
   CZAC_GET_IPADDR(ipAddr, TRUE);
#else
--*/
#ifdef SB_IPV6_SUPPORTED
   tSapCfg->srcNAddrLst.nAddr[0].type = CM_NETADDR_IPV6;
   cmInetPton6(tSapCfg->srcNAddrLst.nAddr[0].u.ipv6NetAddr, "::1");
   tSapCfg->srcNAddrLst.nmb = 1;
#else
   cmInetAddr("127.0.0.1", &ipAddr);
#ifdef SCT_ENDP_MULTI_IPADDR
   cmInetAddr(IPADDR_2, &ipAddr2);
#endif
   tmpAddr.u.ipv4TptAddr.address = ntohl(ipAddr);

   tSapCfg->srcNAddrLst.nAddr[0].type = CM_NETADDR_IPV4;
   tSapCfg->srcNAddrLst.nAddr[0].u.ipv4NetAddr = ntohl(ipAddr);
#ifdef SCT_ENDP_MULTI_IPADDR
   tSapCfg->srcNAddrLst.nAddr[1].type = CM_NETADDR_IPV4;
   tSapCfg->srcNAddrLst.nAddr[1].u.ipv4NetAddr =  ntohl(ipAddr2);
   tSapCfg->srcNAddrLst.nmb = 2;
#else
   tSapCfg->srcNAddrLst.nmb = 1;
#endif
#endif /*-- SB_IPV6_SUPPORTED --*/
/*-- #endif--*/

   tSapCfg->reConfig.spId         = spId;
   tSapCfg->reConfig.tIntTmr      = 50;
   tSapCfg->reConfig.maxBndRetry  = 2;


   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   czAcUtlLsbBldGenCfg
*
*       Desc:  Function for building TSAP configuration for SCTP interface
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  xx_sbhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlLsbBldGenCfg
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb   *spCb,
SbMgmt     *cfg      /* Configuration structure */
)
#else
PUBLIC S16 czAcUtlLsbBldGenCfg(tcCb, spCb, cfg)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb   *spCb;
SbMgmt     *cfg;      /* Configuration structure */
#endif
{
   SbGenCfg *genCfg;

   TRC2(czAcUtlLsbBldGenCfg)

   genCfg = &cfg->t.cfg.s.genCfg;

   genCfg->serviceType   = 0; /*HI_SRVC_UDP;*/ /*-- other values : HI_SRVC_RAW_SCTP --*/

   /*-- Get serviceType from command line, some param in czAccb --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "serviceType",
            &(cfg->t.cfg.s.genCfg.serviceType));

#ifdef LSB5
   genCfg->srcUdpPort = 9898;
   genCfg->dstUdpPort = 9898;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "port",
            &(genCfg->srcUdpPort));
   genCfg->dstUdpPort = genCfg->srcUdpPort;
#endif /*LSB5*/

   genCfg->maxNmbSctSaps = 5;
   genCfg->maxNmbTSaps   = 5;
   genCfg->maxNmbAssoc   = 10;
   genCfg->maxNmbEndp    = 4;
   genCfg->maxNmbDstAddr = 5;
   genCfg->maxNmbSrcAddr = 5;
   genCfg->maxNmbTxChunks = 200;
   genCfg->maxNmbRxChunks = 200;
   genCfg->maxNmbInStrms  = 50;
   genCfg->maxNmbOutStrms = 50;
   genCfg->initARwnd      = 16384;
   genCfg->mtuInitial        = 512;
   genCfg->mtuMinInitial     = 512;
   genCfg->mtuMaxInitial     = 512;
   genCfg->performMtu        = FALSE;
   genCfg->timeRes           = 1;
   genCfg->reConfig.maxInitReTx   = 8;
   genCfg->reConfig.maxAssocReTx  = 20;
   genCfg->reConfig.maxPathReTx   = 2;
   genCfg->reConfig.altAcceptFlg  = TRUE;
   genCfg->reConfig.keyTm         = 5000;
   genCfg->reConfig.alpha         = 12;
   genCfg->reConfig.beta          = 25;

   /* Layer Manager post structure */
   czAcGetPst(spCb, &(genCfg->smPst), ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   czAcUtlLsbCb 
*
*       Desc:  This function is used to 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  xx_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlLsbCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 czAcUtlLsbCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   CzAccMsgQElm  *czMsg;

   TRC2(czAcUtlLsbCb)

   czMsg = (CzAccMsgQElm *)qElm->data;

   if ((qElm->pst.event == LSB_EVTTRCIND) &&
       (czMsg->mBuf != NULLP))
   {
      CMXTA_FREEMBUF(czMsg->mBuf);
   }

   CMXTA_FREE(czMsg, sizeof (CzAccMsgQElm));

   RETVALUE(CMXTA_ERR_NONE);
} /* End of czAcUtlLsbCb() */

#endif /* ifdef SB */
/********************************************************************30**

         End of file:     czac_lsbutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:28 2015

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
/main/1      ---       sy       1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
