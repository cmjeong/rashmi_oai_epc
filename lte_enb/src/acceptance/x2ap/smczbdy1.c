
/********************************************************************20**
  
     Name:     smczbdy1.c - Sample layer manager file
  
     Type:     C source file
  
     Desc:     C code for sample layer manager functions
  
     File:     smczbdy1.c
  
     Sid:      smczbdy1.c@@/main/tenb_main_ccb/1 - Wed Jul 22 20:08:44 2015
  
     Prg:      sy
  
*********************************************************************21*/

/*

  smmgbdy1.c - dummy stack manager functions for MGCP v 1.1

Following functions are provided in this file:

Primitives:

         SmMiLmgCfgCfm              -  configuration confirm
         SmMiLmgStaCfm              -  status confirm
         SmMiLmgStsCfm              -  statistics confirm
         SmMiLmgCntrlCfm            -  control confirm
         SmMiLmgStaInd              -  status indication (alarm)
         SmMiLmgTrcInd              -  trace indication

Support functions:

         smmgPrntCfm                -  print CmStatus
         smmgPrntDateTime           -  print DateTime
         smmgGetAlarmInfoField      -  find alarmInfo union field type
         smmgPrntSrvSta             -  print server status
         smmgPrntPeerSta            -  print peer status
         smmgPrntSsapSta            -  print SSAP status
*/

/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000XXX                      MGCP v 1.1
 */
 
/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* Hash library */
#include "cm_llist.h"      /* Doubly Linked List library */
#include "cm_inet.h"       /* Common Sockets Library */
#include "cm_tpt.h"        /* Common Transport Defines */
#include "cm_tkns.h"       /* Common Tokens Defines */
#include "cm_sdp.h"        /* Session Description Protocol Defines */
#include "cm_mblk.h"       /* Common Memory Manager Defines */
#include "cm_abnf.h"       /* Common ABNF  Defines */
#include "cm_dns.h"        /* common DNS library */

#include "hit.h"           /* HI layer */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_sdp.h"        /* SDP related defines */
#include "cm_dns.h"         /* common DNS libraru defines */
#ifdef ZG
#include "cm_ftha.h"       /* common FTHA defines */
#include "cm_psfft.h"      /* common PSF defines */
#endif /* ZG */
#if (defined(MG_FTHA) || defined(MG_RUG))
#include "sht.h"           /* SHT Interface header file */
#endif /* MG_FTHA || MG_RUG */

#ifdef    GCP_PROV_SCTP
#include "sct.h"           /* SCTP Interface Defines */
#endif    /* GCP_PROV_SCTP */

#ifdef    GCP_PROV_MTP3
#include "cm_ss7.h"        /* Common SS7 Defines */
#include "snt.h"           /* MTP3 Interface Defines */
#endif    /* GCP_PROV_MTP3 */


#include "mgt.h"           /* upper interface defines for MGCP */

#ifdef    GCP_PROV_SCTP
#include "lsb.h"           /* layer management defines for SCTP */
#endif    /* GCP_PROV_SCTP */

#include "lmg.h"           /* layer management defines for MGCP */
#include "mg.h"            /* defines and macros for MGCP */
#include "smmg_err.h"      /* layer management error defines for MGCP */
#include "mg_err.h"        /* MG error defines */
#ifdef GCP_ACC_TESTS
#include "lhi.h"
#include "mgt.h"           /* MGT defines */
#ifdef ZG_ACC_TEST
#include "mrs.h"           /* Message Router defines */  
#include "zgrvupd.h"       /* Reverse update defines */
#include "lzg.h"           /* PSF Layer Management */
#include "zg.h"            /* PSF Defines */
#include "zg_acc.h"        /* PSF Acceptance test defines */
#endif /* ZG_ACC_TEST */
#ifndef CMXTA_MASTER
#include "mg_acc.h"        /* defines for MGCP acceptance tests */
#endif /* CMXTA_MASTER */
#ifdef GCP_PERF_ACC
#include "mg_perf.h"
#endif
#endif /* GCP_ACC_TESTS */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* Hash library */
#include "cm_llist.x"      /* Doubly Linked List library */
#include "cm_inet.x"       /* Common Sockets Library */
#include "cm_tpt.x"        /* Common Transport Definitions */
#include "cm_tkns.x"       /* Common Tokens Defines */
#include "cm_lib.x"        /* Common library functions */
#include "cm_sdp.x"        /* Session Description Protocol Defines */
#include "cm_mblk.x"       /* Common Memory Manager Defines */
#include "cm_abnf.x"       /* Common ABNF  Defines */
#include "cm_dns.x"        /* common dns library */
#ifdef ZG
#include "cm_ftha.x"       /* common FTHA typedefs */
#include "cm_psfft.x"      /* common PSF typedefs */
#endif /* ZG */
#if (defined(MG_FTHA) || defined(MG_RUG))
#include "sht.x"           /* SHT Interface typedef's  */
#endif /* MG_FTHA || MG_RUG */
#include "hit.x"           /* HI layer */

#ifdef    GCP_PROV_SCTP
#include "sct.x"           /* SCTP Interface Structures */
#endif    /* GCP_PROV_SCTP */

#ifdef   GCP_PROV_MTP3
#include "cm_ss7.x"        /* Common SS7 structure */
#include "snt.x"           /* MTP3 Interface Structure */
#endif   /* GCP_PROV_MTP3 */


#include "mgt.x"           /* upper layer typedefs for MGCP */

#ifdef    GCP_PROV_SCTP
#include "lsb.x"           /* layer management defines for SCTP */
#endif    /* GCP_PROV_SCTP */

#include "lmg.x"           /* layer management typedefs for MGCP */
#ifdef GCP_ACC_TESTS
#include "lhi.x"
#include "mg.x"            /* typedefs for MGCP */
#ifdef ZG_ACC_TEST
#include "mrs.x"           /* Message Router typedefs */ 
#include "zgrvupd.x"       /* Reverse update structures */
#include "lzg.x"           /* PSF Layer Management */
#include "zg.x"            /* PSF Data Structures */
#include "zg_acc.x"        /* PSF Acceptance test typedefs */
#endif /* ZG_ACC_TEST */
#ifndef CMXTA_MASTER
#include "mg_acc.x"        /* typedefs for MGCP acceptance tests */
#endif /* CMXTA_MASTER */
#ifdef GCP_PERF_ACC
#include "mg_perf.x"
#endif
#endif /* GCP_ACC_TESTS */


/* mg008.105: Added support for new test architecture */
#ifdef GCP_COMBINED_ARC

#define SmMiLmgCfgCfm MgAccSmMiLmgCfgCfm
#define SmMiLmgStaCfm MgAccSmMiLmgStaCfm
#define SmMiLmgStsCfm MgAccSmMiLmgStsCfm
#define SmMiLmgCntrlCfm MgAccSmMiLmgCntrlCfm  
#define SmMiLmgStaInd MgAccSmMiLmgStaInd
#define SmMiLmgTrcInd MgAccSmMiLmgTrcInd
#define smmgPrntCfm MgAccsmmgPrntCfm
#define smmgPrntDateTime MgAccsmmgPrntDateTime
#define smmgGetAlarmInfoField MgAccsmmgGetAlarmInfoField
#define smmgPrntSrvSta MgAccsmmgPrntSrvSta
#define smmgPrntPeerSta MgAccsmmgPrntPeerSta
#define smmgPrntSsapSta MgAccsmmgPrntSsapSta
#define smmgPrntPeerInfo MgAccsmmgPrntPeerInfo

#endif /* GCP_COMBINED_ARC */

/* 
 *  Since Acceptence test have been modified to work with MTP3B only so acceptence test
 *  code with GCP_PROV_MTP3 flag has is not required to build the product with M3UA 
 */
#ifdef   IT
#ifdef   GCP_PROV_MTP3
#undef   GCP_PROV_MTP3
#endif   /* GCP_PROV_MTP3 */
#endif   /* IT */



/* local defines */
/* For MgAlarmInfo */
#define SMMG_UNKNOWNFIELD     0
#define SMMG_PEERINFO         1
#define SMMG_SAPID            2
#define SMMG_MEM              3
#define SMMG_SRVSTA           4
#define SMMG_PEERSTA          5
#define SMMG_SSAPSTA          6
#define SMMG_PARID            7
#define SMMG_NOT_APPL         8

/* local typedefs */

/* forward references */
PUBLIC Void smmgPrntCfm             ARGS((MgMngmt *mgt));
PUBLIC Void smmgPrntDateTime        ARGS((DateTime *dt));
PUBLIC U16 smmgGetAlarmInfoField    ARGS((MgUsta *usta));
PUBLIC Void smmgPrntSrvSta          ARGS((MgTptSrvSta *sta));
PUBLIC Void smmgPrntPeerSta         ARGS((MgPeerSta *sta));
PUBLIC Void smmgPrntSsapSta         ARGS((MgSSAPSta *sta));
PUBLIC Void smmgPrntPeerInfo        ARGS((MgPeerInfo *peerInfo));


#ifndef CMXTA_MASTER
/* public variable declarations */
#ifdef GCP_ACC_TESTS
EXTERN MgAccCb                      mgAccCb;
#endif /* GCP_ACC_TESTS */

/* public variable definitions */

/* private variable definitions */

/* public routines */

/*
 *
 *       Fun:    SmMiLmgCfgCfm - configuration confirm
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLmgCfgCfm
(
Pst         *post,
MgMngmt     *cfg
)
#else
PUBLIC S16 SmMiLmgCfgCfm(post, cfg)
Pst         *post;
MgMngmt     *cfg;
#endif /* ANSI */
{
#ifdef GCP_ACC_TESTS
   MgAccQEntry entry;
#endif /* GCP_ACC_TESTS */

   TRC3(SmMiLmgCfgCfm)

   SPrint("SMMG CfgCfm: ");
   smmgPrntCfm(cfg);
#ifdef GCP_ACC_TESTS
   entry.type = MGACC_LMGCFGCFM;
   entry.u.cfgCfm.hdr = cfg->hdr;
   entry.u.cfgCfm.cfm = cfg->cfm;
   (Void)mgAccEnQ(&mgAccCb.q, &entry);
#endif /* GCP_ACC_TESTS */
   RETVALUE(ROK);
} /* end of SmMiLmgCfgCfm() */

/*
 *
 *       Fun:    SmMiLmgStaCfm - status confirm
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLmgStaCfm
(
Pst         *post,
MgMngmt     *sta
)
#else
PUBLIC S16 SmMiLmgStaCfm(post, sta)
Pst         *post;
MgMngmt     *sta;
#endif /* ANSI */
{
   Txt prBuf[PRNTSZE];
#ifdef GCP_ACC_TESTS
   MgAccQEntry entry;
#endif /* GCP_ACC_TESTS */

   TRC3(SmMiLmgStaCfm)

   SPrint("SMMG StaCfm: ");
   smmgPrntCfm(sta);
   SPrint("received ");
   smmgPrntDateTime(&sta->t.ssta.dt);
   switch (sta->hdr.elmId.elmnt)
   {
      case STSID:
         SPrint("System ID:\n");
         sprintf(prBuf, "main version %4d, main revision %4d\n",
            (int)(sta->t.ssta.s.systemId.mVer),
            (int)(sta->t.ssta.s.systemId.mRev));
         SPrint(prBuf);
         sprintf(prBuf, "branch version %4d, branch revision %4d\n",
            (int)(sta->t.ssta.s.systemId.bVer),
            (int)(sta->t.ssta.s.systemId.bRev));
         SPrint(prBuf);
         SPrint("Part number ");
         SPrint(sta->t.ssta.s.systemId.ptNmb);
         SPrint("\n");
         break;

      case STSSAP:
         smmgPrntSsapSta(&sta->t.ssta.s.mgSSAPSta);
         break;

      case STTSAP:
         SPrint("TSAP status:\n");
         sprintf(prBuf, "state = %d, number of listeners %u\n",
            (int)(sta->t.ssta.s.mgTSAPSta.state),
            (unsigned int)(sta->t.ssta.s.mgTSAPSta.numServers));
         SPrint(prBuf);
         break;

      case STGCPENT: /* ??? for peer status */
         smmgPrntPeerSta(&sta->t.ssta.s.mgPeerSta);
         break;

      case STSERVER:
         SPrint("Server status:\n");
         smmgPrntSrvSta(&sta->t.ssta.s.mgTptSrvSta);
         break;

      default:
      {
         SPrint("Unknown element type\n");
         break;
      }
   }
#ifdef GCP_ACC_TESTS
   entry.type = MGACC_LMGSTACFM;
   entry.u.staCfm.hdr = sta->hdr;
   entry.u.staCfm.cfm = sta->cfm;
   entry.u.staCfm.elmnt = sta->hdr.elmId.elmnt;
   entry.u.staCfm.ssta = sta->t.ssta;
   (Void)mgAccEnQ(&mgAccCb.q, &entry);
#endif /* GCP_ACC_TESTS */
   RETVALUE(ROK);
} /* end of SmMiLmgStaCfm() */

/*
 *
 *       Fun:    SmMiLmgStsCfm - statistics confirm
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLmgStsCfm
(
Pst         *post,
MgMngmt     *sts
)
#else
PUBLIC S16 SmMiLmgStsCfm(post, sts)
Pst         *post;
MgMngmt     *sts;
#endif /* ANSI */
{
   Txt prBuf[PRNTSZE];
#ifdef GCP_ACC_TESTS
   MgAccQEntry entry;
#endif /* GCP_ACC_TESTS */

   TRC3(SmMiLmgStsCfm)

   SPrint("SMMG StsCfm: ");
   smmgPrntCfm(sts);
   SPrint("received ");
   smmgPrntDateTime(&sts->t.sts.dt);
   switch (sts->hdr.elmId.elmnt)
   {
      case STTSAP:
      {
         SPrint("TSAP statistics:\nDNS statistics:\n");
         sprintf(prBuf, "numAQueryTx = %lu, numAQueryFailed = %lu\n",
            (unsigned long)(sts->t.sts.s.mgTSAPSts.dnsSts.numAQueryTx),
            (unsigned long)(sts->t.sts.s.mgTSAPSts.dnsSts.numAQueryFailed));
         SPrint(prBuf);
         break;
      }
      case STGCPENT: /* ??? for peer statistics */
      {
         /* 
          * Invoke the new function for printing the MgPeerInfo &
          * delete all print code here 
          */
         smmgPrntPeerInfo(&(sts->t.sts.s.mgPeerEntSts.peerInfo));

            {
               SPrint("Gateway statistics\n");
               sprintf(prBuf, "connected to SSAP %d\n",
                  (int)(sts->t.sts.s.mgPeerEntSts.peerSts.sSAPId));
               SPrint(prBuf);
               sprintf(prBuf, "Number of transactions transmitted = %lu\n",
                  (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numMsgTx));
               SPrint(prBuf);
               sprintf(prBuf, "Number of good messages received = %lu\n",
                  (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numMsgRx));
               SPrint(prBuf);
               sprintf(prBuf, "Number of good responses received = %lu\n",
            (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numRespRx));
               SPrint(prBuf);
               sprintf(prBuf, "Number of bad responses received = %lu\n",
            (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numRespFailedRx));
               SPrint(prBuf);
#ifdef GCP_MGCP  /* MGCP specific stats */
            sprintf(prBuf, "Number of NonStandard commands transmitted = %lu\n",
               (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numNonStdTx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of EP config commands transmitted = %lu\n",
                  (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numEpcfTx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of Create conn commands transmitted = %lu\n",
               (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numCreateTx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of Modify conn commands transmitted = %lu\n",
               (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numModifyTx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of Delete conn commands transmitted = %lu\n",
               (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numDeleteTx));
               SPrint(prBuf);
         sprintf(prBuf, "Number of Request notify commands transmitted = %lu\n",
                  (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numRqntTx));
               SPrint(prBuf);
         sprintf(prBuf, "Number of Notify commands transmitted = %lu\n",
               (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numNotifyTx));
               SPrint(prBuf);
               sprintf(prBuf, "Number of Audit EP commands transmitted = %lu\n",
            (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numAuditEndPtTx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of Audit conn commands transmitted = %lu\n",
            (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numAuditConnTx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of Restart commands transmitted = %lu\n",
            (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numRsipTx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of responses transmitted = %lu\n",
            (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numRespTx));
               SPrint(prBuf);
               SPrint("\n");
            sprintf(prBuf, "Number of NonStandard commands received = %lu\n",
               (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numNonStdRx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of EP config commands received = %lu\n",
                  (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numEpcfRx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of Create conn commands received = %lu\n",
               (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numCreateRx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of Modify conn commands received = %lu\n",
               (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numModifyRx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of Delete conn commands received = %lu\n",
               (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numDeleteRx));
               SPrint(prBuf);
         sprintf(prBuf, "Number of Request notify commands received = %lu\n",
                  (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numRqntRx));
               SPrint(prBuf);
         sprintf(prBuf, "Number of Notify commands received = %lu\n",
               (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numNotifyRx));
               SPrint(prBuf);
               sprintf(prBuf, "Number of Audit EP commands received = %lu\n",
            (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numAuditEndPtRx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of Audit conn commands received = %lu\n",
            (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numAuditConnRx));
               SPrint(prBuf);
            sprintf(prBuf, "Number of Restart commands received = %lu\n",
            (unsigned long)(sts->t.sts.s.mgPeerEntSts.peerSts.numRsipRx));
               SPrint(prBuf);
#endif /* GCP_MGCP */
            }
         break;
      }
   }
#ifdef GCP_ACC_TESTS
   entry.type = MGACC_LMGSTSCFM;
   entry.u.stsCfm.hdr = sts->hdr;
   entry.u.stsCfm.cfm = sts->cfm;
   entry.u.stsCfm.elmnt = sts->hdr.elmId.elmnt;
   entry.u.stsCfm.sts = sts->t.sts;
   (Void)mgAccEnQ(&mgAccCb.q, &entry);
#endif /* GCP_ACC_TESTS */
   RETVALUE(ROK);
} /* end of SmMiLmgStsCfm() */

/*
 *
 *       Fun:    SmMiLmgCntrlCfm - control confirm
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLmgCntrlCfm
(
Pst         *post,
MgMngmt     *cntrl
)
#else
PUBLIC S16 SmMiLmgCntrlCfm(post, cntrl)
Pst         *post;
MgMngmt     *cntrl;
#endif /* ANSI */
{
#ifdef GCP_ACC_TESTS
   MgAccQEntry entry;
#endif /* GCP_ACC_TESTS */
   TRC3(SmMiLmgCntrlCfm)

   SPrint("SMMG CntrlCfm: ");
   smmgPrntCfm(cntrl);
#ifdef GCP_ACC_TESTS
   entry.type = MGACC_LMGCNTRLCFM;
   entry.u.cntrlCfm.hdr = cntrl->hdr;
   entry.u.cntrlCfm.cfm = cntrl->cfm;

   if(MGACC_SHTDWN_TRANSID != cntrl->hdr.transId)
   {
       (Void)mgAccEnQ(&mgAccCb.q, &entry);
   }
   else
   {
       SPrint("GCP Stack SHUTDOWN CONF received \n");
#ifdef GCP_PERF_ACC
       perfTstmps.takeTimeStamp = FALSE;
       mgAccPrintPerfResults(mg_perf_msgType);
#endif /* GCP_PERF_ACC */

#ifndef L4
      if (FALSE == mgAccCb.doNotShtdwnPrv)
      {
#ifdef GCP_PROV_SCTP     
         if (mgAccCb.transportType == LMG_TPT_SCTP)
             mgAccSbShutDwn();
#endif
#ifdef GCP_PROV_MTP3     
         if (mgAccCb.transportType == LMG_TPT_MTP3)
         {
             mgAccSnShutDwn();
             mgAccSdShutDwn();
         }
         else
#endif   /* GCP_PROV_MTP3 */
            mgAccHiShutDwn();
      }
#endif

#ifndef NOCMDLINE
       if( (TRUE == mgAccCb.cmdLineTst) && (TRUE == mgAccCb.shutEnd) )
       {
           MGACC_GOTO_SHUTDOWN_STATE();
       }
#endif
   }
#endif /* GCP_ACC_TESTS */
   RETVALUE(ROK);
} /* end of SmMiLmgCntrlCfm() */

/*
 *
 *       Fun:    SmMiLmgStaInd - status indication (alarm)
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLmgStaInd
(
Pst         *post,
MgMngmt     *usta
)
#else
PUBLIC S16 SmMiLmgStaInd(post, usta)
Pst         *post;
MgMngmt     *usta;
#endif /* ANSI */
{
   U16 ret;
   Txt prBuf[PRNTSZE];
   Bool toEnQ;
#ifdef GCP_ACC_TESTS
   MgAccQEntry entry;
#endif /* GCP_ACC_TESTS */

   TRC3(SmMiLmgStaInd);

   toEnQ = FALSE;
   SPrint("SMMG StaInd: received ");
   smmgPrntDateTime(&usta->t.usta.alarm.dt);
   sprintf(prBuf,"\nCategory = %d, Event = %d, Cause = %d\n",
      usta->t.usta.alarm.category, usta->t.usta.alarm.event, 
      usta->t.usta.alarm.cause);
   SPrint(prBuf);
   SPrint("Category: ");
   switch (usta->t.usta.alarm.category)
   {
      case LCM_CATEGORY_PROTOCOL:
      {
         sprintf(prBuf, "protocol related");
         break;
      }
      case LCM_CATEGORY_INTERFACE:
      {
         sprintf(prBuf, "interface related");
         break;
      }
      case LCM_CATEGORY_INTERNAL:
      {
         sprintf(prBuf, "internal ");
         break;
      }
      case LCM_CATEGORY_RESOURCE:
      {
         sprintf(prBuf, "system resources related");
         break;
      }
      case LCM_CATEGORY_PSF_FTHA:
      {
         sprintf(prBuf, "fault tolerance / high availability PSF related");
         break;
      }
      case LCM_CATEGORY_LYR_SPECIFIC:
      {
         sprintf(prBuf, "MGCP related");
         break;
      }
      default:
      {
         sprintf(prBuf, "unknown: %d", (int)(usta->t.usta.alarm.category));
         break;
      }
   }
   SPrint(prBuf);
   SPrint(", event ");
   switch (usta->t.usta.alarm.event)
   {
      case LMG_EVENT_TSAP_RECVRY_SUCCESS:
      {
         sprintf(prBuf, "TSAP recovery success");
         break;
      }
      case LMG_EVENT_TSAP_RECVRY_FAILED:
      {
         sprintf(prBuf, "TSAP recovery failed");
         break;
      }
      case LCM_EVENT_UI_INV_EVT:
      {
         sprintf(prBuf, "upper interface invalid event");
         break;
      }
      case LCM_EVENT_LI_INV_EVT:
      {
         sprintf(prBuf, "lower interface invalid event");
         break;
      }
      case LCM_EVENT_PI_INV_EVT:
      {
         sprintf(prBuf, "peer interface invalid event");
         break;
      }
      case LCM_EVENT_INV_EVT:
      {
         sprintf(prBuf, "general invalid event");
         break;
      }
      case LCM_EVENT_INV_STATE:
      {
         sprintf(prBuf, "invalid internal state");
         break;
      }
      case LCM_EVENT_INV_TMR_EVT:
      {
         sprintf(prBuf, "invalid timer event");
         break;
      }
      case LCM_EVENT_MI_INV_EVT:
      {
         sprintf(prBuf, "management interface invalid event");
         break;
      }
      case LCM_EVENT_BND_FAIL:
      {
         sprintf(prBuf, "bind failure");
         break;
      }
      case LCM_EVENT_NAK:
      {
         sprintf(prBuf, "destination nack");
         break;
      }
      case LCM_EVENT_TIMEOUT:
      {
         sprintf(prBuf, "timeout");
         break;
      }
      case LCM_EVENT_BND_OK:
      {
         sprintf(prBuf, "bind ok");
         break;
      }
      case LCM_EVENT_SMEM_ALLOC_FAIL:
      {
         sprintf(prBuf, "static memory allocation failed");
         break;
      }
      case LCM_EVENT_DMEM_ALLOC_FAIL:
      {
         sprintf(prBuf, "dynamic mmemory allocation failed");
         break;
      }
      case LCM_EVENT_LYR_SPECIFIC:
      {
         sprintf(prBuf, "MGCP specific");
         break;
      }
      default:
      {
         sprintf(prBuf, "unknown event %d", (int)(usta->t.usta.alarm.event));
         break;
      }
      case LMG_EVENT_HIT_BNDCFM:
      {
         sprintf(prBuf, "HIT bind confirm");
         break;
      }
      case LMG_EVENT_HIT_CONCFM:
      {
         sprintf(prBuf, "HIT connect confirm");
         break;
      }
      case LMG_EVENT_HIT_DISCIND:
      {
         sprintf(prBuf, "HIT disconnect indication");
         break;
      }
      case LMG_EVENT_HIT_UDATIND:
      {
         sprintf(prBuf, "HIT unit data indication");
         break;
      }
      case LMG_EVENT_MGT_BNDREQ:
      {
         sprintf(prBuf, "MGT bind request");
         toEnQ = TRUE;
         break;
      }
      case LMG_EVENT_PEER_CFG_FAIL:
      {
         sprintf(prBuf, "Peer Configuration Failed");
         toEnQ = TRUE;
         break;
      }
      case LMG_EVENT_MGT_UBNDREQ:
      {
         sprintf(prBuf, "MGT unbind request");
         break;
      }
      case LMG_EVENT_MGT_MGCPTXNREQ:
      {
         sprintf(prBuf, "MGT MGCP transaction request");
         toEnQ = TRUE;
         break;
      }
      case LMG_EVENT_MGT_MGCPTXNIND:
      {
         sprintf(prBuf, "MGT MGCP transaction indication");
         break;
      }

      case LMG_EVENT_PEER_ENABLED:
      {
         sprintf(prBuf, "gateway enabled");
         toEnQ = TRUE;
         break;
      }
      case LMG_EVENT_PEER_DISCOVERED:
      {
         sprintf(prBuf, "gateway discovered , notified entity");
         toEnQ = TRUE;
         break;
      }
      case LMG_EVENT_PEER_REMOVED:
      {
         sprintf(prBuf, "gateway removed");
         toEnQ = TRUE;
         break;
      }
      case LMG_EVENT_RES_CONG_ON:
      {
         sprintf(prBuf, "resource congestion ON");
         break;
      }
      case LMG_EVENT_RES_CONG_OFF:
      {
         sprintf(prBuf, "resource congestion OFF");
         break;
      }
      case LMG_EVENT_TPTSRV:
      {
         sprintf(prBuf, "transport service");
         break;
      }
      case LMG_EVENT_SSAP_ENABLED:
      {
         sprintf(prBuf, "SSAP enabled");
         toEnQ = TRUE;
         break;
      }
      case LMG_EVENT_NS_NOT_RESPONDING:
      {
         sprintf(prBuf, "name server not responding");
         break;
      }
      case LMG_EVENT_TPT_FAILED:
      {
         sprintf(prBuf, "transport failure");
         break;
      }
   }
   SPrint(prBuf);
   SPrint(", cause ");
   switch (usta->t.usta.alarm.cause)
   {
      case LCM_CAUSE_UNKNOWN:
      {
         sprintf(prBuf, "unknown");
         break;
      }
      case LCM_CAUSE_OUT_OF_RANGE:
      {
         sprintf(prBuf, "out of range");
         break;
      }
      case LCM_CAUSE_INV_SAP:
      {
         sprintf(prBuf, "NULL/unknown sap");
         break;
      }
      case LCM_CAUSE_INV_SPID:
      {
         sprintf(prBuf, "invalid service provider");
         break;
      }
      case LCM_CAUSE_INV_SUID:
      {
         sprintf(prBuf, "invalid service user");
         break;
      }
      case LCM_CAUSE_INV_NETWORK_MSG:
      {
         sprintf(prBuf, "invalid network message");
         break;
      }
      case LCM_CAUSE_DECODE_ERR:
      {
         sprintf(prBuf, "message decoding problem");
         break;
      }
      case LCM_CAUSE_USER_INITIATED:
      {
         sprintf(prBuf, "user initiated");
         break;
      }
      case LCM_CAUSE_MGMT_INITIATED:
      {
         sprintf(prBuf, "management initiated");
         break;
      }
      case LCM_CAUSE_INV_STATE: /* cause and event! */
      {
         sprintf(prBuf, "invalid state");
         break;
      }
      case LCM_CAUSE_TMR_EXPIRED: /* cause and event! */
      {
         sprintf(prBuf, "timer expired");
         break;
      }
      case LCM_CAUSE_INV_MSG_LENGTH:
      {
         sprintf(prBuf, "invalid message length");
         break;
      }
      case LCM_CAUSE_PROT_NOT_ACTIVE:
      {
         sprintf(prBuf, "protocol layer not active");
         break;
      }
      case LCM_CAUSE_INV_PAR_VAL:
      {
         sprintf(prBuf, "invalid parameter value");
         break;
      }
      case LCM_CAUSE_NEG_CFM:
      {
         sprintf(prBuf, "negative confirmation");
         break;
      }
      case LCM_CAUSE_MEM_ALLOC_FAIL:
      {
         sprintf(prBuf, "memory allocation failure");
         break;
      }
      case LCM_CAUSE_HASH_FAIL:
      {
         sprintf(prBuf, "hashing failure");
         break;
      }
      case LCM_CAUSE_LYR_SPECIFIC:
      {
         sprintf(prBuf, "MGCP specific");
         break;
      }
      default:
      {
         sprintf(prBuf, "unknown %d", (int)(usta->t.usta.alarm.cause));
         break;
      }
      case LMG_CAUSE_TPT_FAILURE: /* make up your mind - cause or event? */
      {
         sprintf(prBuf, "transport failure");
         break;
      }
      case LMG_CAUSE_NS_NOT_RESPONDING:
      {
         sprintf(prBuf, "name server not responding");
         break;
      }
   }
   SPrint(prBuf);
   SPrint("\nAlarm parameters: ");
   ret = smmgGetAlarmInfoField(&usta->t.usta);
   switch (ret)
   {
      case SMMG_UNKNOWNFIELD:
      {
         sprintf(prBuf, "invalid\n");
         SPrint(prBuf);
         break;
      }
      case SMMG_PEERINFO:
      {
         /* 
          * Invoke the new function for printing the MgPeerInfo &
          * delete all print code here 
          */
         smmgPrntPeerInfo(&(usta->t.usta.alarmInfo.u.peerInfo));
         break;
      }
      case SMMG_SAPID:
      {
         sprintf(prBuf, "SAP ID %d\n", (int)(usta->t.usta.alarmInfo.u.sapId));
         SPrint(prBuf);
         break;
      }
      case SMMG_MEM:
      {
         sprintf(prBuf, "memory region %d pool %d\n",
            (int)(usta->t.usta.alarmInfo.u.mem.region),
            (int)(usta->t.usta.alarmInfo.u.mem.pool));
         SPrint(prBuf);
         break;
      }
      case SMMG_SRVSTA:
      {
         smmgPrntSrvSta(&usta->t.usta.alarmInfo.u.srvSta);
         break;
      }
      case SMMG_PEERSTA:
      {
         smmgPrntPeerSta(&usta->t.usta.alarmInfo.u.peerSta);
         break;
      }
      case SMMG_SSAPSTA:
      {
         smmgPrntSsapSta(&usta->t.usta.alarmInfo.u.ssapSta);
         break;
      }
      case SMMG_PARID:
      {
         SPrint("parameter type: ");
         switch (usta->t.usta.alarmInfo.u.parId.parType)
         {
            case LMG_PAR_TPTADDR: sprintf(prBuf, "transport address"); break;
            case LMG_PAR_MBUF:    sprintf(prBuf, "message buffer"); break;
            case LMG_PAR_CHOICE:  sprintf(prBuf, "choice"); break;
            case LMG_PAR_SPID:    sprintf(prBuf, "spId"); break;
            default:              sprintf(prBuf, "unknown"); break;
         }
         SPrint(prBuf);
         sprintf(prBuf, ", value %d\n", 
            (int)(usta->t.usta.alarmInfo.u.parId.u.sapId));
         SPrint(prBuf);
         break;
      }
      case SMMG_NOT_APPL:
      {
         SPrint("not applicable\n");
         break;
      }
   }
#ifdef GCP_ACC_TESTS
   if(toEnQ)
   {
      SPrint("\nAlarm enqueued\n\n");
      entry.type = MGACC_LMGSTAIND;
      entry.u.lmStaInd.hdr = usta->hdr;
      entry.u.lmStaInd.usta = usta->t.usta;
      (Void)mgAccEnQ(&mgAccCb.q, &entry);
   }
   else
   {
      SPrint("\nAlarm NOT enqueued\n\n");
   }
#endif /* GCP_ACC_TESTS */
   RETVALUE(ROK);
} /* end of SmMiLmgStaInd() */

/*
 *
 *       Fun:    SmMiLmgTrcInd - trace indication
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLmgTrcInd
(
Pst         *post,
MgMngmt     *trc,
Buffer      *mBuf
)
#else
PUBLIC S16 SmMiLmgTrcInd(post, trc, mBuf)
Pst         *post;
MgMngmt     *trc;
Buffer      *mBuf;
#endif /* ANSI */
{
   Txt prBuf[PRNTSZE];

   TRC3(SmMiLmgTrcInd)

   SPrint("SMMG TrcInd: received ");
   smmgPrntDateTime(&trc->t.trc.dt);
   sprintf(prBuf, "For TSAP %d, peer ", (int)(trc->t.trc.sapId));
   SPrint(prBuf);
   /* 
    * Invoke the new function for printing the MgPeerInfo &
    * delete all print code here 
    */
   smmgPrntPeerInfo(&(trc->t.trc.peerInfo));
   sprintf(prBuf, ": event = %s\n",
      (trc->t.trc.evnt == LMG_TRC_EVENT_MGCPTX ?
       "transmitted MGCP PDU" :
       trc->t.trc.evnt == LMG_TRC_EVENT_MGCPRX ?
       "received MGCP PDU" : "unknown"));
   SPrint(prBuf);
   SPrntMsg(mBuf, 0, 0);
   (Void)mgPutMsg(mBuf);
   RETVALUE(ROK);
} /* end of SmMiLmgTrcInd() */
#endif /* CMXTA_MASTER */

/*
 *
 *       Fun:    smmgPrntCfm - print confirm status and reason
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC Void smmgPrntCfm
(
MgMngmt  *mgt
)
#else
PUBLIC Void smmgPrntCfm(mgt)
MgMngmt  *mgt;
#endif /* ANSI */
{
   Txt prBuf[PRNTSZE];

   TRC2(smmgPrntCfm)
   
   switch (mgt->cfm.status)
   {
      case LCM_PRIM_OK:
      {
         SPrint("Status: successful\n");
         break;
      }
      case LCM_PRIM_OK_NDONE:
      {
         SPrint("Status: deferred processing\n");
         break;
      }
      default:
      {
         SPrint("Status: unknown\n");
         break;
      }
      case LCM_PRIM_NOK:
      {
         SPrint("Status: failed, reason: ");
         switch (mgt->cfm.reason)
         {
            case LCM_REASON_NOT_APPL: 
               SPrint("not applicable"); break;
            case LCM_REASON_INVALID_ENTITY:
               SPrint("invalid entity"); break;
            case LCM_REASON_INVALID_INSTANCE:
               SPrint("invalid instance"); break;
            case LCM_REASON_INVALID_MSGTYPE:
               SPrint("invalid message type"); break;
            case LCM_REASON_MEM_NOAVAIL:
               SPrint("memory not available"); break;
            case LCM_REASON_INVALID_ELMNT:
               SPrint("invalid element in hdr.elmId"); break;
            case LCM_REASON_RECONFIG_FAIL:
               SPrint("reconfiguration failed"); break;
            case LCM_REASON_REGTMR_FAIL:
               SPrint("timer registration failed"); break;
            case LCM_REASON_GENCFG_NOT_DONE:
               SPrint("general configuration not done"); break;
            case LCM_REASON_INVALID_ACTION:
               SPrint("invalid action"); break;
            case LCM_REASON_INVALID_SUBACTION:
               SPrint("invalid subaction"); break;
            case LCM_REASON_INVALID_STATE:
               SPrint("invalid state"); break;
            case LCM_REASON_INVALID_SAP:
               SPrint("invalid sap identifier"); break;
            case LCM_REASON_INVALID_PAR_VAL:
               SPrint("invalid parameter value"); break;
            case LCM_REASON_QINIT_FAIL:
               SPrint("queue initialization failed"); break;
            case LCM_REASON_NEG_CFM:
               SPrint("negative confirmation"); break;
            case LCM_REASON_UPDTMR_EXPIRED:
               SPrint("update timer expired"); break;
            case LCM_REASON_MISC_FAILURE:
               SPrint("miscellaneous failures"); break;
            case LCM_REASON_EXCEED_CONF_VAL:
               SPrint("configured value exceeded"); break;
            case LCM_REASON_HASHING_FAILED:
               SPrint("hashing failed"); break;
            case LCM_REASON_PEERCFG_NOT_DONE:
               SPrint("peer sap not configured"); break;
            case LCM_REASON_PRTLYRCFG_NOT_DONE:
               SPrint("portable layer not configured"); break;
            default:
               sprintf(prBuf, "%d", mgt->cfm.reason);
               SPrint(prBuf); break;
         }
         SPrint("\n");
         break;
      }
   }
   RETVOID;
} /* end of smmgPrntCfm() */

/*
 *
 *       Fun:    smmgPrntDateTime - print date and time
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC Void smmgPrntDateTime
(
DateTime *dt
)
#else
PUBLIC Void smmgPrntDateTime(dt)
DateTime *dt;
#endif /* ANSI */
{
   Txt prBuf[PRNTSZE];

   TRC2(smmgPrntDateTime)
   sprintf(prBuf, "%02d:%02d:%02d.%1d %02d/%02d/%04d\n",
      (int)(dt->hour), (int)(dt->min), (int)(dt->sec), (int)(dt->tenths),
      (int)(dt->month), (int)(dt->day), (int)(dt->year) + 1900);
   SPrint(prBuf);
   RETVOID;
} /* end of smmgPrntDateTime() */

/*
 *
 *       Fun:    smmgGetAlarmInfoField - find field in alarmInfo
 *
 *       Desc:   based on alarm category+event+cause, returns the index of the
 *               union field of MgAlarmInfo.
 *
 *       Ret:    field index
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC U16 smmgGetAlarmInfoField
(
MgUsta *usta
)
#else
PUBLIC U16 smmgGetAlarmInfoField(usta)
MgUsta *usta;
#endif /* ANSI */
{
   U16 ret;

   TRC2(smmgGetAlarmInfoField)

   switch (usta->alarm.category)
   {
      case LCM_CATEGORY_INTERFACE:
      {
         switch (usta->alarm.event)
         {
            case LMG_EVENT_MGT_BNDREQ:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_INV_PAR_VAL:   ret = SMMG_PARID; break;
                  case LCM_CAUSE_INV_SAP:       ret = SMMG_SAPID; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LMG_EVENT_MGT_UBNDREQ:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_INV_PAR_VAL:   ret = SMMG_PARID; break;
                  case LCM_CAUSE_INV_SAP:       ret = SMMG_SAPID; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LMG_EVENT_MGT_MGCPTXNREQ:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_INV_PAR_VAL:   ret = SMMG_PARID; break;
                  case LCM_CAUSE_INV_SAP:       ret = SMMG_SAPID; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LMG_EVENT_MGT_MGCPTXNIND:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_INV_PAR_VAL:   ret = SMMG_PARID; break;
                  case LCM_CAUSE_INV_SAP:       ret = SMMG_SAPID; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LMG_EVENT_HIT_BNDCFM:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_INV_PAR_VAL:   ret = SMMG_PARID; break;
                  case LCM_CAUSE_INV_SAP:       ret = SMMG_SAPID; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LMG_EVENT_HIT_CONCFM:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_INV_PAR_VAL:   ret = SMMG_PARID; break;
                  case LCM_CAUSE_INV_SAP:       ret = SMMG_SAPID; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LMG_EVENT_HIT_DISCIND:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_INV_PAR_VAL:   ret = SMMG_PARID; break;
                  case LCM_CAUSE_INV_SAP:       ret = SMMG_SAPID; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LMG_EVENT_HIT_UDATIND:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_INV_PAR_VAL:   ret = SMMG_PARID; break;
                  case LCM_CAUSE_INV_SAP:       ret = SMMG_SAPID; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            default:
            {
               ret = SMMG_UNKNOWNFIELD; break;
            }
         }
         break;
      }
      case LCM_CATEGORY_RESOURCE:
      {
         switch (usta->alarm.event)
         {
            case LCM_EVENT_DMEM_ALLOC_FAIL:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_UNKNOWN:       ret = SMMG_MEM; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LCM_EVENT_SMEM_ALLOC_FAIL:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_UNKNOWN:       ret = SMMG_MEM; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }

            case LMG_EVENT_RES_CONG_ON:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_UNKNOWN:       ret = SMMG_SAPID; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LMG_EVENT_RES_CONG_OFF:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_UNKNOWN:       ret = SMMG_SAPID; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            default:
            {
               ret = SMMG_UNKNOWNFIELD; break;
            }
         }
         break;
      }
      case LCM_CATEGORY_PROTOCOL:
      {
         switch (usta->alarm.event)
         {
            case LMG_EVENT_PEER_ENABLED:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_MGMT_INITIATED:ret = SMMG_PEERSTA; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LMG_EVENT_TPTSRV:
            {
               switch (usta->alarm.cause)
               {
                  case LMG_CAUSE_TPT_FAILURE:   ret = SMMG_SRVSTA; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LMG_EVENT_PEER_REMOVED:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_UNKNOWN:       ret = SMMG_PEERINFO; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            case LCM_EVENT_LI_INV_EVT:
            {
               switch (usta->alarm.cause)
               {
                  case LCM_CAUSE_DECODE_ERR:    ret = SMMG_NOT_APPL; break;
                  default:                      ret = SMMG_UNKNOWNFIELD; break;
               }
               break;
            }
            default:
            {
               ret = SMMG_UNKNOWNFIELD; break;
            }
         }
         break;
      }
      default:
      {
         ret = SMMG_UNKNOWNFIELD; break;
      }
   }
   RETVALUE(ret);
} /* end of smmgGetAlarmInfoField() */

/*
 *
 *       Fun:    smmgPrntSrvSta - print server status
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC Void smmgPrntSrvSta
(
MgTptSrvSta *sta
)
#else
PUBLIC Void smmgPrntSrvSta(sta)
MgTptSrvSta *sta;
#endif /* ANSI */
{
   U32 j;
   Txt prBuf[PRNTSZE];

   TRC2(smmgPrntSrvSta)
   sprintf(prBuf, "\n    server status: state %d, ",
      (int)(sta->state));
   SPrint(prBuf);
   SPrint("transport address:\n    ");
   switch (sta->tptAddr.type)
   {
      case CM_TPTADDR_NOTPRSNT:
      {
         SPrint("none");
         break;
      }
      case CM_TPTADDR_IPV4:
      {
         sprintf(prBuf, "IPv4 IP address #%lu, port %u",
            (unsigned long)(sta->tptAddr.u.ipv4TptAddr.address),
            (unsigned int)(sta->tptAddr.u.ipv4TptAddr.port));
         SPrint(prBuf);
         break;
      }
      case CM_TPTADDR_IPV6:
      {
         SPrint("IPv6 IP address ");
         sprintf(prBuf, "%2x", sta->tptAddr.u.ipv6TptAddr.ipv6NetAddr[0]);
         SPrint(prBuf);
         for (j = 1; j < CM_IPV6ADDR_SIZE; j++)
         {
            sprintf(prBuf, ":%2x", sta->tptAddr.u.ipv6TptAddr.ipv6NetAddr[j]);
            SPrint(prBuf);
         }
         sprintf(prBuf, " port %u", 
            (unsigned int)(sta->tptAddr.u.ipv6TptAddr.port));
         SPrint(prBuf);
         break;
      }
#ifdef CM_AAL
      case CM_TPTADDR_AAL:
      {
         sprintf(prBuf, "VC %u:%u", 
            (unsigned int)(sta->tptAddr.u.aalTptAddr.vpi),
            (unsigned int)(sta->tptAddr.u.aalTptAddr.vci));
         SPrint(prBuf);
         break;
      }
#endif /* CM_AAL */
      default:
      {
         SPrint("unknown");
         break;
      }
   }
   SPrint("\n");
   RETVOID;
} /* end of smmgPrntSrvSta() */

/*
 *
 *       Fun:    smmgPrntPeerSta - print peer status
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC Void smmgPrntPeerSta
(
MgPeerSta   *sta
)
#else
PUBLIC Void smmgPrntPeerSta(sta)
MgPeerSta   *sta;
#endif /* ANSI */
{
   /*
    * Added another local variable
    */
   U16 j, i;
   Txt prBuf[PRNTSZE];

   TRC2(smmgPrntPeerSta)

   /*
    * Modify this function to reflect changes for modified MgPeerSta structure
    */

   if (sta->peerId.pres != NOTPRSNT)
   {
      sprintf(prBuf, "ID %d, ", (int)(sta->peerId.val));
      SPrint(prBuf);
   }
   else
   {
      SPrint("ID <unknown>, ");
   }
   /* 
    * Print domain name only if it is present.
    */
   if(PRSNT_NODEF == sta->namePres.pres)
   {
      sprintf(prBuf, "%s\n", (char *)(sta->name));
      SPrint(prBuf);
   }
   else
   {
      SPrint("Domain Name <Not Present>, ");
   }

   /* 
    * Print all IP addresses in the IP addr table
    */
   for(i=0; i<sta->peerAddrTbl.count; i++)
   {
      switch (sta->peerAddrTbl.netAddr[i].type)
      {
         case CM_NETADDR_IPV4:
         {
            SPrint("IP V4 address :");
            sprintf(prBuf, "#%lu\n", (unsigned long)
               (sta->peerAddrTbl.netAddr[i].u.ipv4NetAddr));
            SPrint(prBuf);
            break;
         }
         case CM_NETADDR_IPV6:
         {
            SPrint("IP V6 address :");
            sprintf(prBuf, "%2x", (unsigned int)
               (sta->peerAddrTbl.netAddr[i].u.ipv6NetAddr[0]));
            SPrint(prBuf);
            for (j = 1; j < CM_IPV6ADDR_SIZE; j++)
            {
               sprintf(prBuf, ":%2x", (unsigned int)
                  (sta->peerAddrTbl.netAddr[i].u.ipv6NetAddr[j]));
               SPrint(prBuf);
            }
            SPrint("\n");
            break;
         }
         default:
         {
            SPrint("\n");
            break;
         }
      }
   } /* End of for */

   SPrint("Num of pending outgoing transactions : ");
   sprintf(prBuf,"%lu\n",(unsigned long)(sta->numPendOgTxn));
   SPrint(prBuf);

   SPrint("Num of pending incoming transactions : ");
   sprintf(prBuf,"%lu\n",(unsigned long)(sta->numPendIcTxn));
   SPrint(prBuf);

   SPrint("Round trip estimate of time :");
   sprintf(prBuf,"%lu\n",(unsigned long)(sta->rttEstimate));
   SPrint(prBuf);

   switch(sta->protocol)
   {
      case LMG_PROTOCOL_MGCP:
         SPrint("Peer Protocol Type Supported = MGCP \n");
         break;

      case LMG_PROTOCOL_MGCO:
         SPrint("Peer Protocol Type Supported = MEGACO \n");
         break;

      case LMG_PROTOCOL_NONE:
         SPrint("Peer Protocol Type Supported = MGCP/MEGACO \n");
         break;

      default:
         SPrint("Invalid protocol type value\n");
         break;
   }
   switch(sta->transportType)
   {
      case LMG_TPT_UDP:
         SPrint("Peer Transport Type Supported = UDP\n");
         break;

      case LMG_TPT_TCP:
         SPrint("Peer Transport Type Supported = TCP\n");
         break;

      case LMG_TPT_NONE:
         SPrint("Peer Transport Type Supported = UDP/TCP\n");
         break;

      default:
         SPrint("Invalid transport type value\n");
         break;
   }

#ifdef GCP_MGCO
   switch(sta->encodingScheme)
   {
      case LMG_ENCODE_BIN:
         SPrint("Encoding Type Supported = BINARY \n");
         break;

      case LMG_ENCODE_TXT:
         SPrint("Encoding Type Supported = TEXT\n");
         break;

      case LMG_ENCODE_NONE:
         SPrint("Encoding Type Supported = TEXT/BINARY\n");
         break;

      default:
         SPrint("Invalid Encoding type value\n");
         break;
   }

   if(LMG_VER_PROF_MGCO_H248_1_0 == sta->version)
      SPrint("MGCO Version number = H.248, Ver 1.0 \n");
   else
   if(LMG_VER_PROF_MGCO_H248_2_0 == sta->version)
      SPrint("MGCO Version number = H.248, Ver 2.0 \n");
   else
      SPrint("Invalid Version value\n");
#endif
   
   RETVOID;
} /* end of smmgPrntPeerSta() */

/*
 *
 *       Fun:    smmgPrntSsapSta - print SSAP status
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC Void smmgPrntSsapSta
(
MgSSAPSta   *sta
)
#else
PUBLIC Void smmgPrntSsapSta(sta)
MgSSAPSta   *sta;
#endif /* ANSI */
{
   U16 i;
   Txt prBuf[PRNTSZE];

   TRC2(smmgPrntSsapSta)

   sprintf(prBuf, "SSAP status for SAP %d\n", (int)(sta->sapId));
   SPrint(prBuf);
   sprintf(prBuf, "state = %d, number of peers = %u\n", (int)(sta->state),
      (unsigned int)(sta->numAssocPeer));
   SPrint(prBuf);
   SPrint("Peers are:\n");
   for (i = 0; i < sta->numAssocPeer; i++)
   {
      /* 
       * Invoke the new function for printing the MgPeerInfo &
       * delete all print code here 
       */
      smmgPrntPeerInfo(&(sta->peerInfo[i]));
   }
   sprintf(prBuf, "number of listeners %u\n", (unsigned int)(sta->numServers));
   SPrint(prBuf);
   RETVOID;
} /* end of smmgPrntSsapSta() */


/* 
 * Add a function for printing MgPeerInfo 
 */

/*
 *
 *       Fun:    smmgPrntPeerInfo - print MgPeerInfo
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
         File:   smmgbdy1.c
 *
 */

#ifdef ANSI
PUBLIC Void smmgPrntPeerInfo
(
MgPeerInfo  *peerInfo
)
#else
PUBLIC Void smmgPrntPeerInfo(peerInfo)
MgPeerInfo  *peerInfo;
#endif /* ANSI */
{
   Txt prBuf[PRNTSZE];

   TRC2(smmgPrntPerInfo)
   if (peerInfo->id.pres != NOTPRSNT)
   {
      sprintf(prBuf, "ID %d, ", (int)(peerInfo->id.val));
      SPrint(prBuf);
   }
   else
   {
      SPrint("ID <unknown>, ");
   }

#ifdef GCP_MGCP
   if(peerInfo->dname.namePres.pres == PRSNT_NODEF)
   {
      SPrint("Domain Name of the Peer is: ");
      sprintf(prBuf, "%s\n", (char *)(peerInfo->dname.name));
      SPrint(prBuf);
   }

   if (peerInfo->dname.netAddr.type == CM_NETADDR_IPV4)
   {
      SPrint("IPV4 Address of the Peer is: ");

      sprintf(prBuf, "%lx\n", (U32)(peerInfo->dname.netAddr.u.ipv4NetAddr));
      SPrint(prBuf);
   }
   if (peerInfo->dname.netAddr.type == CM_NETADDR_IPV6)
   {
      U8 i;
      SPrint("IPV6 Address of the Peer is: ");

      for (i = 0; i < 16; i++)
      {
         sprintf(prBuf, "%02x", peerInfo->dname.netAddr.u.ipv6NetAddr[i]);
         SPrint(prBuf);
         if (i%2 == 1)
         {
            sprintf(prBuf, ":");
            SPrint(prBuf);
         }
      }
      sprintf(prBuf, "\n");
      SPrint(prBuf);
   }

#endif /* GCP_MGCP */
#ifdef GCP_MGCO
   if (PRSNT_NODEF == peerInfo->mid.pres)
   {
      SPrint("MID of the Peer is: ");
      sprintf(prBuf, "%s\n", (char *)(peerInfo->mid.val));
      SPrint(prBuf);
   }
#endif /* GCP_MGCO */
   SPrint("\n");
 
   RETVOID;
} /* end of smmgPrntPeerInfo() */

/********************************************************************30**
  
         End of file:     smczbdy1.c@@/main/tenb_main_ccb/1 - Wed Jul 22 20:08:44 2015
  
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
----------- -------- ---- -----------------------------------------------
/main/1      ----     sy               1. LTE-X2AP Initial release.
/main/2      ---      pt               1. LTE-X2AP 3.1 release.
*********************************************************************91*/
