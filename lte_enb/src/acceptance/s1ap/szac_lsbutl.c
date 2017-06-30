
/********************************************************************20**

     Name:     S1AP

     Type:     C source file

     Desc:     C code for layer manager service provider primitives that
               are usually supplied by the customer.
               - Copy contents to the queue.
               - Display the results of the received primitive.

     File:     sz_lsbcb.c

     Sid:      szac_lsbutl.c@@/main/3 - Mon Jan 10 22:15:49 2011

     Prg:      mn

*********************************************************************21*/

/*

  smsbbdy1.c - Stack Manager for the SCTP layer.

Following functions are provided in this file:
         szAcSmMiLsbCfgCfm    - Configuration confirm
         szAcSmMiLsbStsCfm    - Statistics confirm
         szAcSmMiLsbStaCfm    - Status confirm
         szAcSmMiLsbCntrlCfm  - Control confirm
         szAcSmMiLsbStaInd    - Status indication
         szAcSmMiLsbTrcInd    - Trace indication
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
#include "cm_dns.h"         /* common DNS libraru defines */

#include "lsb.h"           /* layer management defines for SCTP */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer management defines for S1AP */

#include "hit.h"           /* HI layer */
#ifdef HI
#include "lhi.h"
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#include "sct.h"           /* SB (SCTP) layer */
#include "sb_mtu.h"
#include "sb.h"
#endif    /* SB */

#include "cm_pasn.h"
#include "cm_xta.h" 
#include "sz.h"            /* defines and macros for S1AP */
#include "szt.h"            /* defines and macros for S1AP */
/* sz006.301: Removed un-necessary include files  */
#include "szt_asn.h"
#include "sz_err.h"        /* SZ error defines */
#include "szac_acc.h"        /* defines for S1AP acceptance tests */
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

#include"szt_asn.x"        /* common ss7 */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCTP Interface Structures */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SCTP Interface Structures */
#include "lsb.x"           /* layer management defines for SCTP */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for S1AP */

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
#include "sz.x"            /* typedefs for S1AP */
#include "szac_acc.x"        /* typedefs for S1AP acceptance tests */
#include "szac_lsb.x"

/*
*
*       Fun:   szAcUtlLsbBldSctSapCfg
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
PUBLIC S16 szAcUtlLsbBldSctSapCfg
(
CmXtaTCCb     *tcCb,   /* tcCb data structure  */
CmXtaSpCb     *spCb,
SpId       spId,
SbMgmt     *cfg     /* Configuration structure */
)
#else
PUBLIC S16 szAcUtlLsbBldSctSapCfg(tcCb, spCb, spId, cfg)
CmXtaTCCb     *tcCb;   /* tcCb data structure  */
CmXtaSpCb     *spCb;
SpId       spId;
SbMgmt     *cfg;    /* Configuration structure */
#endif
{
   SbSctSapCfg   *sapCfg;
   Pst            entPst;
   S16            entity;
 

   TRC2(szAcUtlLsbBldSctSapCfg)

   sapCfg = &(cfg->t.cfg.s.sctSapCfg);

   entity = ENTSZ;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM, "entity",  &(entity));
   szAcGetPst(spCb, &entPst, ENTSB, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);

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
*       Fun:   szAcUtlLsbBldTSapCfg
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
PUBLIC S16 szAcUtlLsbBldTSapCfg
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb   *spCb,
SuId       suId,
SpId       spId,
SbMgmt     *cfg     /* Configuration structure */
)
#else
PUBLIC S16 szAcUtlLsbBldTSapCfg(tcCb, spCb, suId, spId, cfg)
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
   Pst   pst;
   U16   cnt;

   TRC2(szAcUtlLsbBldTSapCfg)

   tSapCfg = &(cfg->t.cfg.s.tSapCfg);

   /*-- Get the Pst information here --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID, ENTHI, CMXTA_INST_ID);

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
   tmpAddr.type = CM_TPTADDR_IPV4;
   tmpAddr.u.ipv4TptAddr.port = 2827;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,"port", &(tmpAddr.u.ipv4TptAddr.port));

   /* S1AP related changes       *
    * spId 0 is connected to ENB *
    * spId 1 is connected to MME */

   SZAC_GET_IPADDR(ipAddr, TRUE);
   tmpAddr.u.ipv4TptAddr.address = ntohl(ipAddr);

   tSapCfg->srcNAddrLst.nAddr[0].type = CM_NETADDR_IPV4;
   tSapCfg->srcNAddrLst.nAddr[0].u.ipv4NetAddr =  ntohl(ipAddr);
   tSapCfg->srcNAddrLst.nmb = 1;

   tSapCfg->reConfig.spId         = spId;
   tSapCfg->reConfig.tIntTmr      = 50;
   tSapCfg->reConfig.maxBndRetry  = 2;


   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   szAcUtlLsbBldGenCfg
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
PUBLIC S16 szAcUtlLsbBldGenCfg
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb   *spCb,
SbMgmt     *cfg      /* Configuration structure */
)
#else
PUBLIC S16 szAcUtlLsbBldGenCfg(tcCb, spCb, cfg)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb   *spCb;
SbMgmt     *cfg;      /* Configuration structure */
#endif
{
   SbGenCfg *genCfg;

   TRC2(szAcUtlLsbBldGenCfg)

   genCfg = &cfg->t.cfg.s.genCfg;

   genCfg->serviceType   = HI_SRVC_UDP; /*-- other values : HI_SRVC_RAW_SCTP --*/

   /*-- Get serviceType from command line, some param in szAccb --*/

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
   genCfg->maxNmbAssoc   = 100;
   genCfg->maxNmbEndp    = 300;
   genCfg->maxNmbDstAddr = 300;
   genCfg->maxNmbSrcAddr = 300;
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
   szAcGetPst(spCb, &(genCfg->smPst), ENTSB, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID);

   RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   szAcUtlLsbCb 
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
PUBLIC S16 szAcUtlLsbCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 szAcUtlLsbCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   SzAccMsgQElm  *szMsg;

   TRC2(szAcUtlLsbCb)

   szMsg = (SzAccMsgQElm *)qElm->data;

   if ((qElm->pst.event == LSB_EVTTRCIND) &&
       (szMsg->mBuf != NULLP))
   {
      CMXTA_FREEMBUF(szMsg->mBuf);
   }

   CMXTA_FREE(szMsg, sizeof (SzAccMsgQElm));

   RETVALUE(CMXTA_ERR_NONE);
} /* End of szAcUtlLsbCb() */

/* sz003.301: Updted for PSF-S1AP 3.1 release */

/*
*
*       Fun:   Activate Task - initialize
*
*       Desc:  Invoked by system services to initialize a task.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  szac_lsbutl.c
*
*/

#ifdef ANSI
PUBLIC S16 smSbActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 smSbActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(smSbActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
} /* end of smSbActvInit */
 

/********************************************************************30**

         End of file:     szac_lsbutl.c@@/main/3 - Mon Jan 10 22:15:49 2011

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/3      ---      pkaX  1. Updated for S1AP release 3.1
/main/3   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/3   sz006.301   ve    1. Removed un-necessary include files
/main/3   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
