

/********************************************************************20**

     Name:     smsbbdy1.c - Dummy Stack Manager (Layer Manager) for the
               SCTP layer.
     Type:     C source file

     Desc:     C code for layer manager service provider primitives that
               are usually supplied by the customer.
               - Copy contents to the queue.
               - Display the results of the received primitive.

     File:     smsbbdy1.c

     Sid:      smsbbdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:10 2015

     Prg:      wvdl

*********************************************************************21*/

/*

  smsbbdy1.c - Stack Manager for the SCTP layer.

Following functions are provided in this file:
         SmMiLsbCfgCfm    - Configuration confirm
         SmMiLsbStsCfm    - Statistics confirm
         SmMiLsbStaCfm    - Status confirm
         SmMiLsbCntrlCfm  - Control confirm
         SmMiLsbStaInd    - Status indication
         SmMiLsbTrcInd    - Trace indication
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
#include "cm5.h"           /* timer defines */
#include "cm_hash.h"       /* common hashing */
#ifdef SB_INOP
#include "cm_os.h"
#endif
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "hit.h"
#include "sct.h"
#include "lsb.h"           /* layer management defines for SCTP layer */
#include "sb_mtu.h"
#include "sb.h"            /* defines and macros for SCTP layer */
#include "sb_err.h"        /* error defines for SCTP layer */
/* sb067.102 moved acceptance file under SB_ACC flag */
#ifdef SB_ACC
#include "sb_acc.h"      /* acceptance test */
#endif /* SB_ACC */
#ifdef SIG_INT
#include "cm_ss7.h"
#include "snt.h"
#include "lhi.h"
#include "lsb.h"
#include "lit.h"
#include "lsi.h"
#include "sig_int.h"
#endif
/*sb002.103: GCP acceptance changes */
#ifdef MGAC_ACC
#include "cm_tkns.h"       /* common tokens */
#include "cm_sdp.h"        /* common SDP */
#include "cm_mblk.h"       /* common memory allocation */
#include "cm_dns.h"
#include "mgt.h"           /* MGT defines */
#include "lmg.h"           /* layer management defines for MGCP */
#include "cm_xta.h"
#include "mgacc.h"        /* defines for MGCP acceptance tests */
#endif /* MGAC_ACC */



/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* timer typedefs */
#include "cm_lib.x"        /* common library functions typedefs */
#include "cm_hash.x"       /* common hashing */
#ifdef SB_INOP
#include "cm_os.x"
#endif
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_tpt.x"           /* common transport address */
#include "cm_dns.x"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "hit.x"
#include "sct.x"
#include "lsb.x"           /* layer management typedefs for SCTP layer */
#include "sb_mtu.x"
#include "sb.x"            /* typedefs for SCTP layer */
/* sb067.102 moved acceptance file under SB_ACC flag */
#ifdef SB_ACC
#include "sb_acc.x"     /*  acceptance test */
#endif /* SB_ACC */
#ifdef SIG_INT
#include "cm_ss7.x"
#include "snt.x"
#include "lhi.x"
#include "lsb.x"
#include "lit.x"
#include "lsi.x"
#include "sig_int.x"
#endif
/*sb082.102: changes for SIP*/
#ifdef SO_ACC22
#include "cm_xta.h"
#include "cm_xta.x"
#include "soac_acc.x"
#endif

/*sb002.103: GCP acceptance changes */
#ifdef MGAC_ACC
#include "cm_lib.x"        /* common library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_sdp.x"        /* common SDP */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_dns.x"
#include "cm_xta.x"
#include "mgac_lsb.x"
#endif /* MGAC_ACC */

/* sb016.103 Updated for S1AP release 1.1 */
#ifdef SZ
#include "cm_xta.h"
#include "cm_xta.x"
#include "szac_lsb.x"
#endif


/* local defines */
#define STRTAG(x)                { x, #x }
#define NOT_FOUND                (-1)

#define SMSB_STRLEN(x, i)                                                     \
   {                                                                          \
      *i = 0;                                                                 \
      while (x[*i] != 0)                                                      \
      {                                                                       \
         (*i)++;                                                              \
      }                                                                       \
   }

/* local typedefs */

/* sb018.102 Heartbeat statistics added */
/* sb052.102 Abort statistics added */
/* sb068.102 Error statistics added */
/* sb082.102 Non-ANSI compilation */

#ifdef UNUSED_CODE /* RFC 4460 -- To remove compilation error */

#if  (LSB3 || LSB6)
#define SMSB_DUMPCHUNKSTS(x)                                                  \
   {                                                                          \
   sprintf(prntBuf,                                                           \
   "noInitTx = %10ld        noInitReTx = %10ld     \nnoInitRx = %10ld\n", \
      x.noInitTx,                                                             \
      x.noInitReTx,                                                           \
      x.noInitRx);                                                            \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                   \
   "noIAckTx = %10ld        noIAckRx = %10ld\n",         \
      x.noIAckTx,                                   \
      x.noIAckRx);                                  \
   SPrint(prntBuf);                                 \
                                                    \
   sprintf(prntBuf,                                                           \
   "noShDwnTx = %10ld       noShDwnReTx = %10ld      \n noShDwnRx = %10ld\n",    \
      x.noShDwnTx,                                                            \
      x.noShDwnReTx,                                                          \
      x.noShDwnRx);                                                           \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                                           \
   "noShDwnAckTx = %10ld    noShDwnAckRx = %10ld\n", \
      x.noShDwnAckTx,                                                         \
      x.noShDwnAckRx);                                                        \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                                           \
   "noCookieTx = %10ld      noCookieReTx = %10ld      \nnoCookieRx = %10ld\n",   \
      x.noCookieTx,                                                           \
      x.noCookieReTx,                                                         \
      x.noCookieRx);                                                          \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                                            \
   "noCkAckTx = %10ld       noCkAckRx = %10ld\n",  \
      x.noCkAckTx,                                                            \
      x.noCkAckRx);                                                           \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,  \
   "noDataTx = %10ld        noDataReTx = %10ld        \nnoDataRx = %10ld\n",  \
      x.noDataTx,                                                             \
      x.noDataReTx,                        \
      x.noDataRx);                                                            \
   SPrint(prntBuf);                        \
                                                                              \
   sprintf(prntBuf,                                                           \
   "noDAckTx = %10ld        noDAckRx = %10ld\n",   \
      x.noDAckTx,                                                             \
      x.noDAckRx);                                                            \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                                           \
   "noHBeatTx = %10ld        noHBeatRx = %10ld\n",   \
      x.noHBeatTx,                                                            \
      x.noHBeatRx);                                                           \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                                           \
   "noHBAckTx = %10ld        noHBAckRx = %10ld\n",   \
      x.noHBAckTx,                                                            \
      x.noHBAckRx);                                                           \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                                           \
   "noAbortTx = %10ld        noAbortRx = %10ld\n",   \
      x.noAbortTx,                                                            \
      x.noAbortRx);                                                           \
   SPrint(prntBuf);                                                         \
                                 \
   sprintf(prntBuf,                                                           \
   "noErrorTx = %10ld        noErrorRx = %10ld\n",   \
      x.noErrorTx,                                                            \
      x.noErrorRx);                                                           \
   SPrint(prntBuf);                                                           \
                                 \
   }                                                                          \

#else

#define SMSB_DUMPCHUNKSTS(x)                                                  \
   {                                                                          \
   sprintf(prntBuf,                                                           \
   "noInitTx = %10ld        noInitReTx = %10ld     \nnoInitRx = %10ld\n", \
      x.noInitTx,                                                             \
      x.noInitReTx,                                                           \
      x.noInitRx);                                                            \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                   \
   "noIAckTx = %10ld        noIAckRx = %10ld\n",         \
      x.noIAckTx,                                   \
      x.noIAckRx);                                  \
   SPrint(prntBuf);                                 \
                                                    \
   sprintf(prntBuf,                                                           \
   "noShDwnTx = %10ld       noShDwnReTx = %10ld      \n noShDwnRx = %10ld\n",    \
      x.noShDwnTx,                                                            \
      x.noShDwnReTx,                                                          \
      x.noShDwnRx);                                                           \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                                           \
   "noShDwnAckTx = %10ld    noShDwnAckRx = %10ld\n", \
      x.noShDwnAckTx,                                                         \
      x.noShDwnAckRx);                                                        \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                                           \
   "noCookieTx = %10ld      noCookieReTx = %10ld      \nnoCookieRx = %10ld\n",   \
      x.noCookieTx,                                                           \
      x.noCookieReTx,                                                         \
      x.noCookieRx);                                                          \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,                                                            \
   "noCkAckTx = %10ld       noCkAckRx = %10ld\n",  \
      x.noCkAckTx,                                                            \
      x.noCkAckRx);                                                           \
   SPrint(prntBuf);                                                           \
                                                                              \
   sprintf(prntBuf,  \
   "noDataTx = %10ld        noDataReTx = %10ld        \nnoDataRx = %10ld\n",  \
      x.noDataTx,                                                             \
      x.noDataReTx,                        \
      x.noDataRx);                                                            \
   SPrint(prntBuf);                        \
                                                                              \
   sprintf(prntBuf,                                                           \
   "noDAckTx = %10ld        noDAckRx = %10ld\n",   \
      x.noDAckTx,                                                             \
      x.noDAckRx);                                                            \
   SPrint(prntBuf);                                                           \
   }                                                                          \

#endif
#endif /* UNUSED_CODE */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
#define SMSB_DUMPBYTESTS(x)                                                   \
   {                                                                          \
    sprintf(prntBuf,                                                          \
   "bytesTx = %10d         bytesRx = %10d\n", x.bytesTx, x.bytesRx);        \
   SPrint(prntBuf);                                                           \
   }


#define SMSB_DUMPDNSSTS(x)                                                    \
   {                                                                          \
    sprintf(prntBuf,                                                          \
   "noDnsQueryTx = %10d  noDnsQueryReTx = %10d  noDnsQueryRspRx = %10d\n", \
        x.noQueryTx,  x.noQueryReTx, x.noQueryRspRx );                        \
   SPrint(prntBuf);                                                           \
   }
#else /* BIT_64 */
#define SMSB_DUMPBYTESTS(x)                                                   \
   {                                                                          \
    sprintf(prntBuf,                                                          \
   "bytesTx = %10ld         bytesRx = %10ld\n", x.bytesTx, x.bytesRx);        \
   SPrint(prntBuf);                                                           \
   }


#define SMSB_DUMPDNSSTS(x)                                                    \
   {                                                                          \
    sprintf(prntBuf,                                                          \
   "noDnsQueryTx = %10ld  noDnsQueryReTx = %10ld  noDnsQueryRspRx = %10ld\n", \
        x.noQueryTx,  x.noQueryReTx, x.noQueryRspRx );                        \
   SPrint(prntBuf);                                                           \
   }

#endif /* BIT_64 */

typedef struct smSbStrTag
{
   S16      tag;
/* sb028.103: Fix for compilation warnings */
   CONSTANT Txt      *txt;
} SmSbStrTag;

/* forward references */

PUBLIC S16 smSbActvInit ARGS((Ent ent, Inst inst, Region region,
                              Reason reason));
PUBLIC S16 smHiActvInit ARGS((Ent ent, Inst inst, Region region, Reason reason));
PUBLIC S16 smHiActvTsk  ARGS((Pst *pst, Buffer *mBuf));
PUBLIC S16 smItActvInit ARGS((Ent ent, Inst inst, Region region, Reason reason));
PUBLIC S16 smItActvTsk  ARGS((Pst *pst, Buffer *mBuf));

PUBLIC Void smsbPrintCfm ARGS((SbMgmt *mgt));
PUBLIC Void dumpChunkSts ARGS(( SbChunkSts x ));


/* public variable declarations */

/* public variable definitions */

/* private variable definitions, Replace with imported lists from interface header files, TBD*/
PRIVATE Txt prntBuf[PRNTSZE];

PRIVATE SmSbStrTag statusTable[] =
{
   STRTAG(LCM_PRIM_OK),
   STRTAG(LCM_PRIM_NOK),
   STRTAG(LCM_PRIM_OK_NDONE),
   STRTAG(NOT_FOUND)
};

PRIVATE SmSbStrTag reasonTable[] =
{
   STRTAG(LCM_REASON_NOT_APPL),
   STRTAG(LCM_REASON_INVALID_ELMNT),
   STRTAG(LSB_REASON_MAX_BND_TRY),
   STRTAG(LCM_REASON_INVALID_SAP),
   STRTAG(LCM_REASON_INVALID_STATE),
   STRTAG(LCM_REASON_INVALID_PAR_VAL),
   STRTAG(LCM_REASON_MEM_NOAVAIL),
   STRTAG(LCM_REASON_REGTMR_FAIL),
   STRTAG(LCM_REASON_GENCFG_NOT_DONE),
   STRTAG(LCM_REASON_HASHING_FAILED),
   STRTAG(LCM_REASON_RECONFIG_FAIL),
   STRTAG(LCM_REASON_INVALID_ACTION),
   STRTAG(LCM_REASON_INVALID_SUBACTION),
   STRTAG(NOT_FOUND)
};

/*sb082.102: changes for SIP*/
#ifdef SB_ACC
PRIVATE SmSbStrTag categoryTable[] =
{
   STRTAG(LCM_CATEGORY_PROTOCOL),
   STRTAG(LCM_CATEGORY_INTERFACE),
   STRTAG(LCM_CATEGORY_INTERNAL),
   STRTAG(LCM_CATEGORY_RESOURCE),
   STRTAG(NOT_FOUND)
};

PRIVATE SmSbStrTag eventTable[] =
{
   STRTAG(LCM_EVENT_UI_INV_EVT),
   STRTAG(LCM_EVENT_LI_INV_EVT),
   STRTAG(LCM_EVENT_MI_INV_EVT),
   STRTAG(LCM_EVENT_TIMEOUT),
   STRTAG(LCM_EVENT_BND_FAIL),
   STRTAG(LSB_MSG_RECVD),
   STRTAG(LSB_MSG_TXED),
   STRTAG(NOT_FOUND)
};

PRIVATE SmSbStrTag causeTable[] =
{
   STRTAG(LCM_CAUSE_UNKNOWN),
   STRTAG(LCM_CAUSE_INV_SAP),
   STRTAG(LCM_CAUSE_INV_SPID),
   STRTAG(LCM_CAUSE_INV_SUID),
   STRTAG(LSB_CAUSE_SAP_UBND),
   STRTAG(LSB_CAUSE_INV_ASSOCID),
   STRTAG(LSB_CAUSE_INV_PRIADDR),
   STRTAG(LSB_CAUSE_INV_DSTADDR),
   STRTAG(LSB_CAUSE_INV_SRCADDR),
   STRTAG(LSB_CAUSE_INV_STREAMS),
   STRTAG(NOT_FOUND)
};

PRIVATE SmSbStrTag elementTable[] =
{
   STRTAG(STSBGEN),
   STRTAG(STSBSCTSAP),
   STRTAG(STSBTSAP),
   STRTAG(STSBSID),
   STRTAG(STSBASSOC),
   STRTAG(STSBDTA),
   STRTAG(STSBTMR),
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE
   STRTAG(STSBPATHPROF),
   STRTAG(STSBDSTADDR),
#endif   
   STRTAG(NOT_FOUND)
};


PRIVATE SmSbStrTag assocstateTable[] =
{
   STRTAG(SB_ST_OPEN),
   STRTAG(SB_ST_CLOSED),
   STRTAG(SB_ST_COOKIE_WAIT),
   STRTAG(SB_ST_COOKIE_SENT),
   STRTAG(SB_ST_ESTABLISHED),
   STRTAG(SB_ST_SDOWN_PEND),
   STRTAG(SB_ST_SDOWN_SENT),
   STRTAG(SB_ST_SDOWN_RCVD),
   STRTAG(NOT_FOUND)
};

PRIVATE SmSbStrTag dtastateTable[] =
{
   STRTAG(SCT_PATH_ACTIVE),
   STRTAG(SCT_PATH_INACTIVE),
   STRTAG(NOT_FOUND)
};

PRIVATE SmSbStrTag sapstateTable[] =
{
   STRTAG(SB_SAPSTATE_BND),
   STRTAG(SB_SAPSTATE_UBND),
   STRTAG(NOT_FOUND)
};

/* sb012.103: Placed under flag LSB12 */
#ifdef LSB12
PRIVATE SmSbStrTag tmrstateTable[] =
{
   STRTAG(STOPPED),
   STRTAG(RUNNING),
   STRTAG(NOT_FOUND)
};
#endif /* LSB12 */
#endif /* SB_ACC */

#ifdef SB_INOP

/* Table for chunk type in trace */
PRIVATE Keys chunkTypeTbl[]=
{
   {"Payload Data (DATA)",                0},
   {"Initiation (INIT)",                  1},
   {"Initiation Ack (INIT ACK)",          2},
   {"Selective Ack (SACK)",               3},
   {"Heartbeat Request (HEARTBEAT)",      4},
   {"Heartbeat Ack (HEARTBEAT ACK)",      5},
   {"Abort (ABORTa)",                     6},
   {"Shutdown (SHUTDOWN)",                7},
   {"Shutdown Ack (SHUTDOWN ACK)",        8},
   {"Operation Error (ERROR)",            9},
   {"State Cookie (COOKIE ECHO)",         10},
   {"Cookie Ack (COOKIE ACK)",            11},
   {"ECNE",                               12},
   {"CWR",                                13},
   {"Shutdown Complete(SHUTDOWN COMPLETE)",14}                        
}; 

PRIVATE Keys errorCauseTbl[]=
{
   {"Not defined",                      0},
   {"Invalid Stream Identifier",        1},
   {"Missing Mandatory Parameter",      2},
   {"Stale Cookie Error",               3},
   {"Out of Resource",                  4},
   {"Unresolvable Address",             5},
   {"Unrecongnized Chunk Type",         6},
   {"Invalid Mandatory Parameter",      7},
   {"Unrecognized Parameters",          8},
   {"No User Data",                     9},
   {"Cookie Received While Shutting Down",10}
};

PRIVATE SmSbStrTag trcevtTable[] =
{
   STRTAG(LSB_MSG_RECVD),
   STRTAG(LSB_MSG_TXED),
   STRTAG(NOT_FOUND)
};

#endif /* SB_INOP */


/* private routines */

/*
 *
 *       Fun:    smSbTag2Str
 *
 *       Desc:   Converts the tag to its string representation
 *
 *       Ret:    pointer to string representation
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

/* sb028.103: Fix for compilation warnings */
#ifdef ANSI
PRIVATE CONSTANT Txt *smSbTag2Str
(
SmSbStrTag           *tagArray,
S16                  tag
)
#else
PRIVATE CONSTANT Txt *smSbTag2Str(tagArray, tag)
SmSbStrTag           *tagArray;
S16                  tag;
#endif /* ANSI */
{
   U16 i;

   TRC3(smSbTag2Str)

   for (i = 0; tagArray[i].tag != NOT_FOUND; i++)
   {
      if (tagArray[i].tag == tag)
      {
         break;
      }
   }

   RETVALUE(tagArray[i].txt);
} /* end of smSbTag2Str */

/* public routines */

/*
 *
 *       Fun:    SmMiLsbCfgCfm - configuration confirm
 *
 *       Desc:   prints the config confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbCfgCfm
(
Pst         *pst,
SbMgmt     *cfg
)
#else
PUBLIC S16 SmMiLsbCfgCfm(pst, cfg)
Pst         *pst;
SbMgmt     *cfg;
#endif /* ANSI */
{

#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   UNUSED(pst);

   TRC3(SmMiLsbCfgCfm)

#ifdef SB_ACC
   /* Pack primitive data in queue structure */
   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_CFG_CFM; /* Override pst->event */
   QElm.t.mgmtMsg.transId = cfg->hdr.transId;
   QElm.t.mgmtMsg.cfm.status = cfg->cfm.status;
   QElm.t.mgmtMsg.cfm.reason = cfg->cfm.reason;
   QElm.t.mgmtMsg.elmId.elmnt = cfg->hdr.elmId.elmnt;

   (Void) sbAccPushMsg(&QElm);
#endif

#ifdef SIG_INT
   {
      IntMsgQElm qElm;
      qElm.msgType = INT_MSGTYPE_LSBCFGCFM;
      qElm.cfm = cfg->cfm;
      intPushMsg(&qElm);
   }
#endif
/*sb082.102: changes for SIP*/
#ifdef SB_ACC
   sprintf(prntBuf, "SMSB: CfgCfm: %s ",
   smSbTag2Str(elementTable, cfg->hdr.elmId.elmnt));
   SPrint(prntBuf);
   smsbPrintCfm(cfg);
   SPrint(" \n ");
#endif
#ifdef SO_ACC22
   soAcSmMiLsbCfgCfm(pst, cfg);
#endif /*-- SO_ACC22 --*/
/* sb001.103: GCP Acceptance related changes */
#if (defined(MGAC_ACC) &&  defined(GCP_PROV_SCTP))
   mgAcSmMiLsbCfgCfm(pst, cfg);
#endif /*--defined(MGAC_ACC) &&  defined(GCP_PROV_SCTP) --*/
/* sb016.103 Updated for S1AP release 1.1 */
#ifdef SZ
   szAcSmMiLsbCfgCfm(pst, cfg);
#endif 

   RETVALUE(ROK);
} /* end of SmMiLsbCfgCfm() */

/*
 *
 *       Fun:    SmMiLsbStsCfm - statistics confirm
 *
 *       Desc:   prints the statistics confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbStsCfm
(
Pst                  *pst,
SbMgmt               *sts
)
#else
PUBLIC S16 SmMiLsbStsCfm(pst, sts)
Pst                  *pst;
SbMgmt               *sts;
#endif /* ANSI */
{

#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(SmMiLsbStsCfm)
   UNUSED(pst);

#ifdef SB_ACC
   /* Pack primitive data in queue structure */
   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_STS_CFM; /* Override pst->event */
   QElm.t.mgmtMsg.transId = sts->hdr.transId;
   QElm.t.mgmtMsg.cfm.status = sts->cfm.status;
   QElm.t.mgmtMsg.cfm.reason = sts->cfm.reason;
   QElm.t.mgmtMsg.elmId.elmnt = sts->hdr.elmId.elmnt;


   /* statistics should all be zero - but here's the copy procedure anyway */
   switch (sts->hdr.elmId.elmnt)
   {
      case STSBGEN:
         (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.sts.u.genSts), 
                         (U8 *) &(sts->t.sts.u.genSts),
                         (PTR) PRNTSZE);
         break;
      case STSBSCTSAP:
        (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.sts.u.sctSts), 
                        (U8 *) &(sts->t.sts.u.sctSts),
                        (PTR)PRNTSZE);

         break;
      case STSBTSAP:
         (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.sts.u.tSts), 
                         (U8 *) &(sts->t.sts.u.tSts),
                         (PTR) PRNTSZE);
         break;
   }

   (Void) sbAccPushMsg(&QElm);
#endif /* SB_ACC */

  /*sb082.102: changes for SIP*/
#ifdef SB_ACC
   sprintf(prntBuf, "SMSB: StsCfm: %s ",
   smSbTag2Str(elementTable, sts->hdr.elmId.elmnt));
   SPrint(prntBuf);
   smsbPrintCfm(sts);

   switch (sts->hdr.elmId.elmnt)
   {
      case STSBGEN:
         dumpChunkSts(sts->t.sts.u.genSts.sbChunkSts);
         SMSB_DUMPBYTESTS(sts->t.sts.u.genSts.sbByteSts)
         SMSB_DUMPDNSSTS(sts->t.sts.u.genSts.sbDnsSts)
         break;
      case STSBSCTSAP:
          SMSB_DUMPBYTESTS(sts->t.sts.u.sctSts.sbByteSts)
         break;
      case STSBTSAP:
         dumpChunkSts(sts->t.sts.u.tSts.sbChunkSts);
         SMSB_DUMPBYTESTS(sts->t.sts.u.tSts.sbByteSts)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         sprintf(prntBuf, "Bind retries: %u \n",sts->t.sts.u.tSts.nmbBndRetry);
#else

         sprintf(prntBuf, "Bind retries: %lu \n",sts->t.sts.u.tSts.nmbBndRetry);
#endif /* BIT_64 */
         SPrint(prntBuf);

         break;
   }
#endif /* SB_ACC */

/*sb082.102: changes for SIP*/
#ifdef SO_ACC22
   soAcSmMiLsbStsCfm(pst, sts);
#endif /*-- SO_ACC22 --*/
/* sb001.103: GCP Acceptance related changes */
#if (defined(MGAC_ACC) &&  defined(GCP_PROV_SCTP))
   mgAcSmMiLsbStsCfm(pst, sts);
#endif /*-- MGAC_ACC --*/
/* sb016.103 Updated for S1AP release 1.1 */
#ifdef SZ
   szAcSmMiLsbStsCfm(pst, sts);
#endif 

   RETVALUE(ROK);
} /* end of SmMiLsbStsCfm() */

/*
 *
 *       Fun:    SmMiLsbStaCfm - status confirm
 *
 *       Desc:   prints the status confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbStaCfm
(
Pst                  *pst,
SbMgmt               *ssta
)
#else
PUBLIC S16 SmMiLsbStaCfm(pst, ssta)
Pst                  *pst;
SbMgmt               *ssta;
#endif /* ANSI */
{

#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(SmMiLsbStaCfm)
   UNUSED(pst);

#ifdef SB_ACC
   /* Pack primitive data in queue structure */
   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_STA_CFM; /* Override pst->event */
   QElm.t.mgmtMsg.transId = ssta->hdr.transId;
   QElm.t.mgmtMsg.cfm.status = ssta->cfm.status;
   QElm.t.mgmtMsg.cfm.reason = ssta->cfm.reason;
   QElm.t.mgmtMsg.elmId.elmnt = ssta->hdr.elmId.elmnt;

   switch (ssta->hdr.elmId.elmnt)
   {
      case STSBSID:
         (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.ssta.s.sysId), 
                         (U8 *) &(ssta->t.ssta.s.sysId),
                         (PTR) PRNTSZE);
         break;
      case STSBSCTSAP:
      case STSBTSAP:
         (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.ssta.s.sapSta), 
                         (U8 *) &(ssta->t.ssta.s.sapSta),
                         (PTR) PRNTSZE);
         break;
      case STSBGEN:
         (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.ssta.s.genSta), 
                         (U8 *) &(ssta->t.ssta.s.genSta),
                         (PTR) PRNTSZE);
         break;
      case STSBASSOC:
         (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.ssta.s.assocSta), 
                         (U8 *) &(ssta->t.ssta.s.assocSta),
                         (PTR)PRNTSZE);
         break;
      case STSBDTA:
         (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.ssta.s.dtaSta), 
                         (U8 *) &(ssta->t.ssta.s.dtaSta),
                         (PTR)PRNTSZE);
         break;
/* sb012.103: placed under flag LSB12 */
#ifdef LSB12
      case STSBTMR:
         (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.ssta.s.tmrSta), 
                         (U8 *) &(ssta->t.ssta.s.tmrSta),
                         (PTR) PRNTSZE);
         break;
#endif /* LSB12 */
   }

   (Void) sbAccPushMsg(&QElm);

#endif /* SB_ACC */

/*sb082.102: Changes for SIP*/
#ifdef SB_ACC
   sprintf(prntBuf, "SMSB: StaCfm: %s ",
      smSbTag2Str(elementTable, ssta->hdr.elmId.elmnt));
   SPrint(prntBuf);
   smsbPrintCfm(ssta);

   switch (ssta->hdr.elmId.elmnt)
   {
       case STSBSID:
         sprintf(prntBuf,
            "  mVer = %d mRev = %d bVer = %d bRev = %d ptNmb = %s\n",
            ssta->t.ssta.s.sysId.mVer,
            ssta->t.ssta.s.sysId.mRev,
            ssta->t.ssta.s.sysId.bVer,
            ssta->t.ssta.s.sysId.bRev,
            ssta->t.ssta.s.sysId.ptNmb);
            SPrint(prntBuf);
         break;

      case STSBSCTSAP:
         sprintf(prntBuf,
            "SCTSAP:   %s\n",
            smSbTag2Str(sapstateTable, ssta->t.ssta.s.sapSta.hlSt));
            SPrint(prntBuf);
         break;
      case STSBTSAP:
            sprintf(prntBuf,
            "TSAP:     %s\n",
            smSbTag2Str(sapstateTable, ssta->t.ssta.s.sapSta.hlSt));
            SPrint(prntBuf);
         break;
      case STSBGEN:
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         sprintf(prntBuf,
            " memSize = %u, memAlloc = %u, nmbAssoc = %u, nmbEndp = %u \n",
            ssta->t.ssta.s.genSta.memSize,
            ssta->t.ssta.s.genSta.memAlloc,
            ssta->t.ssta.s.genSta.nmbAssoc,
            ssta->t.ssta.s.genSta.nmbEndp);
#else
         sprintf(prntBuf,
            " memSize = %lu, memAlloc = %lu, nmbAssoc = %u, nmbEndp = %u \n",
            ssta->t.ssta.s.genSta.memSize,
            ssta->t.ssta.s.genSta.memAlloc,
            ssta->t.ssta.s.genSta.nmbAssoc,
            ssta->t.ssta.s.genSta.nmbEndp);
#endif /* BIT_64 */
            SPrint(prntBuf);
         break;
      case STSBASSOC:
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         sprintf(prntBuf,
            "AssocId =  %u  Assoc state:%s, Dst. port = %u, Src port = %u\n",
            ssta->t.ssta.s.assocSta.assocId,
            smSbTag2Str(assocstateTable, ssta->t.ssta.s.assocSta.assocState),
            ssta->t.ssta.s.assocSta.dstPort,
            ssta->t.ssta.s.assocSta.srcPort );
#else
         sprintf(prntBuf,
            "AssocId =  %lu  Assoc state:%s, Dst. port = %u, Src port = %u\n",
            ssta->t.ssta.s.assocSta.assocId,
            smSbTag2Str(assocstateTable, ssta->t.ssta.s.assocSta.assocState),
            ssta->t.ssta.s.assocSta.dstPort,
            ssta->t.ssta.s.assocSta.srcPort );
#endif /* BIT_64 */
            SPrint(prntBuf);
         break;
      case STSBDTA:
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         sprintf(prntBuf,
            "DTA state =  %s, assocId = %u, mtu = %u, rto = %u  \n",
            smSbTag2Str(dtastateTable, ssta->t.ssta.s.dtaSta.state),
            ssta->t.ssta.s.dtaSta.assocId,
            ssta->t.ssta.s.dtaSta.mtu,
            ssta->t.ssta.s.dtaSta.rto);
#else
         sprintf(prntBuf,
            "DTA state =  %s, assocId = %lu, mtu = %u, rto = %u  \n",
            smSbTag2Str(dtastateTable, ssta->t.ssta.s.dtaSta.state),
            ssta->t.ssta.s.dtaSta.assocId,
            ssta->t.ssta.s.dtaSta.mtu,
            ssta->t.ssta.s.dtaSta.rto);
#endif /*BIT_64*/
            SPrint(prntBuf);
            break;
      case STSBTMR:
/* sb012.103: Replaced SB_ACC flag with LSB12 */
#ifdef LSB12
         sprintf(prntBuf,
            "t1InitTmr: %s, t2Shutdown: %s, tIntTmr: %s, t3rtx: %s, hBeat: %s \n",
            smSbTag2Str(tmrstateTable, ssta->t.ssta.s.tmrSta.t1InitTmr),
            smSbTag2Str(tmrstateTable, ssta->t.ssta.s.tmrSta.t2Shutdown),
            smSbTag2Str(tmrstateTable, ssta->t.ssta.s.tmrSta.tIntTmr),
            smSbTag2Str(tmrstateTable, ssta->t.ssta.s.tmrSta.t3rtx),
            smSbTag2Str(tmrstateTable, ssta->t.ssta.s.tmrSta.hBeat));
            SPrint(prntBuf);
#endif /* LSB12 */ 
           break;

   }
#endif /* SB_ACC */

#ifdef SO_ACC22
   soAcSmMiLsbStaCfm(pst, ssta);
#endif /*-- SO_ACC22 --*/
/* sb001.103: GCP Acceptance related changes */
#if (defined(MGAC_ACC) &&  defined(GCP_PROV_SCTP))
   mgAcSmMiLsbStaCfm(pst, ssta);
#endif /*-- MGAC_ACC --*/
/* sb016.103 Updated for S1AP release 1.1 */
#ifdef SZ
   szAcSmMiLsbStaCfm(pst, ssta);
#endif 

   RETVALUE(ROK);
} /* end of SmMiLsbStaCfm() */

/*
 *
 *       Fun:    SmMiLsbCntrlCfm - control confirm
 *
 *       Desc:   prints the control confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbCntrlCfm
(
Pst         *pst,
SbMgmt     *cntrl
)
#else
PUBLIC S16 SmMiLsbCntrlCfm(pst, cntrl)
Pst         *pst;
SbMgmt     *cntrl;
#endif /* ANSI */
{

#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(SmMiLsbCntrlCfm)
   UNUSED(pst);

#ifdef SB_ACC
   SB_ZERO(&QElm, (S32)sizeof(QElm)); 
   QElm.evntType = ACC_EVT_CNTRL_CFM; /* Override pst->event */
   QElm.t.mgmtMsg.transId = cntrl->hdr.transId;
   QElm.t.mgmtMsg.cfm.status = cntrl->cfm.status;
   QElm.t.mgmtMsg.cfm.reason = cntrl->cfm.reason;

   QElm.t.mgmtMsg.s.cntrl.sapId = cntrl->t.cntrl.sapId;
   /* RFC 4460 -- RTR -- windows warnings, typecasting is done */
   QElm.t.mgmtMsg.s.cntrl.action = (U8)cntrl->t.cntrl.action;
   QElm.t.mgmtMsg.s.cntrl.subAction =  (U8)cntrl->t.cntrl.subAction;

#ifdef DEBUGP
    QElm.t.mgmtMsg.s.cntrl.sbDbg = cntrl->t.cntrl.dbgMask;
#endif
 
    (Void) sbAccPushMsg(&QElm);
#endif  /*SB_ACC */

#ifdef SIG_INT
   {
      IntMsgQElm qElm;
      qElm.msgType = INT_MSGTYPE_LSBCNTRLCFM;
      qElm.cfm = cntrl->cfm;
      intPushMsg(&qElm);
   }
#endif

/*sb082.102: Changes for SIP*/
#ifdef SB_ACC
   SPrint("SMSB: CntrlCfm:");
   smsbPrintCfm(cntrl);
#endif

#ifdef SO_ACC22
   soAcSmMiLsbCntrlCfm(pst, cntrl);
#endif /*-- SO_ACC22 --*/
/* sb001.103: GCP Acceptance related changes */
#if (defined(MGAC_ACC) &&  defined(GCP_PROV_SCTP))
   mgAcSmMiLsbCntrlCfm(pst, cntrl);
#endif /*-- MGAC_ACC --*/
/* sb016.103 Updated for S1AP release 1.1 */
#ifdef SZ
   szAcSmMiLsbCntrlCfm(pst, cntrl);
#endif 

   RETVALUE(ROK);
} /* end of SmMiLsbCntrlCfm() */

/* sb042.102 - Added change for rolling upgrade */
#ifdef SB_FTHA
/* sb067.102 - moved ShMiShtCntrlCfm under SB_ACC flag */
#ifdef SB_ACC

/*
 *
 *       Fun:    ShMiShtCntrlCfm - control confirm
 *
 *       Desc:   prints the control confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ShMiShtCntrlCfm
(
Pst                 *pst,
ShtCntrlCfmEvnt     *cntrl
)
#else
PUBLIC S16 ShMiShtCntrlCfm(pst, cntrl)
Pst                 *pst;
ShtCntrlCfmEvnt     *cntrl;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(ShMiShtCntrlCfm)
   UNUSED(pst);

#if (ERRCLS & ERRCLS_INT_PAR)
   if ((cntrl->transId != (SIACC_TRANSID1)) ||
       (cntrl->status.status != LCM_PRIM_OK))
   {
      sprintf(prntBuf,"transaction is with wrong ID or status is wrong \n");
      SPrint(prntBuf);
   }
#endif

#ifdef SB_ACC
   SB_ZERO(&QElm, (S32)sizeof(QElm)); 
   QElm.evntType = ACC_EVT_SHT_CNTRL_CFM; /* Override pst->event */
   QElm.t.mgmtMsg.transId = cntrl->transId;
   QElm.t.mgmtMsg.cfm.status = cntrl->status.status;
   QElm.t.mgmtMsg.cfm.reason = cntrl->status.reason;

   /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
   switch(cntrl->reqType)
   {
      case SHT_REQTYPE_GETVER:
         if ((cntrl->t.gvCfm.numUif != 1) ||
             (cntrl->t.gvCfm.uifList[0].intfId != SCTIF) ||
             (cntrl->t.gvCfm.uifList[0].intfVer != SCTIFVER) ||
             (cntrl->t.gvCfm.numLif != 1) ||
             (cntrl->t.gvCfm.lifList[0].intfId != HITIF) ||
             (cntrl->t.gvCfm.lifList[0].intfVer != HITIFVER))
         {
            sprintf(prntBuf,"ShtCntrlCfm: GetVer failed \n");
            SPrint(prntBuf);

            (Void) sbAccPushMsg(&QElm);
            RETVALUE(RFAILED);
         }
         else
         {
            sprintf(prntBuf,"ShtCntrlCfm: GetVer check pass \n");
            SPrint(prntBuf);
         }
         break;
      case SHT_REQTYPE_SETVER:
         /* verification procedure */
         break;
   }
#endif

    (Void) sbAccPushMsg(&QElm);
#endif  /*SB_ACC */


   sprintf(prntBuf, " SMSB: ShtCntrlCfm : Status = %s Reason = %s\n",
                    smSbTag2Str(statusTable, cntrl->status.status),
                    smSbTag2Str(reasonTable, cntrl->status.reason));
   SPrint(prntBuf);
   
#ifdef DEBUGP
   sprintf(prntBuf,"*[SHTSB] ShtCntrlCfm: \n");
   SPrint(prntBuf);
#endif

   RETVALUE(ROK);
} /* end of ShMiShtCntrlCfm() */
#endif /* SB_ACC */
#endif /* SB_FTHA */

/*
 *
 *       Fun:    SmMiLsbStaInd - status indication
 *
 *       Desc:   prints the status indication (alarm)
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbStaInd
(
Pst         *pst,
SbMgmt     *usta
)
#else
PUBLIC S16 SmMiLsbStaInd(pst, usta)
Pst         *pst;
SbMgmt     *usta;
#endif /* ANSI */
{

#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(SmMiLsbStaInd)
   UNUSED(pst);

#ifdef SB_ACC
   SB_ZERO(&QElm, (S32)sizeof(QElm));   
   QElm.evntType = ACC_EVT_STA_IND; /* Override pst->event */
   QElm.t.mgmtMsg.transId = usta->hdr.transId;
   QElm.t.mgmtMsg.cfm.status = usta->cfm.status;
   QElm.t.mgmtMsg.cfm.reason = usta->cfm.reason;

   QElm.t.mgmtMsg.s.usta.event = usta->t.usta.alarm.event;
   QElm.t.mgmtMsg.s.usta.category = usta->t.usta.alarm.category;
   QElm.t.mgmtMsg.s.usta.cause = usta->t.usta.alarm.cause;

   /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
   (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.usta.pst), (U8 *) pst,
                   (PTR) PRNTSZE);
#endif /* SB_RUG */

  (Void) sbAccPushMsg(&QElm);


   SPrint("SMSB: StaInd:\n");
   sprintf(prntBuf,
      "  DateTime = %04d/%02d/%02d %02d:%02d:%02d\n",
      usta->t.usta.alarm.dt.year + 1900, usta->t.usta.alarm.dt.month, usta->t.usta.alarm.dt.day, usta->t.usta.alarm.dt.hour,
      usta->t.usta.alarm.dt.min, usta->t.usta.alarm.dt.sec);
   SPrint(prntBuf);
   sprintf(prntBuf,
      "  Category = %s Event = %s Cause = %s\n",
      smSbTag2Str(categoryTable, usta->t.usta.alarm.category),
      smSbTag2Str(eventTable, usta->t.usta.alarm.event),
      smSbTag2Str(causeTable, usta->t.usta.alarm.cause));
   SPrint(prntBuf);
#endif /* SB_ACC */

/*sb082.102: Changes for SIP*/
#ifdef SO_ACC22
   soAcSmMiLsbStaInd(pst, usta);
#endif /*-- SO_ACC22 --*/
/* sb001.103: GCP Acceptance related changes */
#if (defined(MGAC_ACC) &&  defined(GCP_PROV_SCTP))
   mgAcSmMiLsbStaInd(pst, usta);
#endif /*-- MGAC_ACC --*/
/* sb016.103 Updated for S1AP release 1.1 */
#ifdef SZ
   szAcSmMiLsbStaInd(pst, usta);
#endif 

   RETVALUE(ROK);
} /* end of SmMiLsbStaInd() */

/*
 *
 *       Fun:    SmMiLsbTrcInd - trace indication
 *
 *       Desc:   prints the trace indication
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLsbTrcInd
(
Pst                  *pst,
SbMgmt               *trc
)
#else
PUBLIC S16 SmMiLsbTrcInd(pst, trc)
Pst                  *pst;
SbMgmt               *trc;
#endif /* ANSI */
{

#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif
   U16               i = 0;
   U16               col = 0;
#ifdef SB_INOP
   OsFile             *cfin;
   U16                     len;
#endif

   U8 chunkType = 0;
   U16 errorCause = 0;

   TRC3(SmMiLsbTrcInd)
   UNUSED(pst);

#ifdef SB_ACC
   UNUSED(chunkType);
   UNUSED(errorCause);
   UNUSED(col);
   UNUSED(i);
   SB_ZERO(&QElm, (S32)sizeof(QElm));   
   QElm.evntType = ACC_EVT_TRC_IND; /* Override pst->event */
   QElm.t.mgmtMsg.transId = trc->hdr.transId;
   QElm.t.mgmtMsg.cfm.status = trc->cfm.status;
   QElm.t.mgmtMsg.cfm.reason = trc->cfm.reason;

   QElm.t.mgmtMsg.s.trc.sapId = trc->t.trc.sapId;
   /* RFC 4460 -- RTR -- window warnings -- typecasting is done */
   QElm.t.mgmtMsg.s.trc.evnt = (U8) trc->t.trc.evnt;
   QElm.t.mgmtMsg.s.trc.len = trc->t.trc.len;
   (Void) cmMemcpy((U8 *) &(QElm.t.mgmtMsg.s.trc.evntParm),
                   (U8 *) &(trc->t.trc.evntParm),
                   (PTR) PRNTSZE);

   (Void) sbAccPushMsg(&QElm);

#endif /* SB_ACC */

#ifdef SB_INOP

   if ((cfin = (OsFile*)osFopen("trace.log", "a+")) == (S32)NULLP)
   {
      osPrintf("%s:  Can't open file for write ,File=:%s\n", "smsbbdy1.c", "trace.log");
      RETVALUE(RFAILED);
   }

   sprintf(prntBuf,
      " DateTime = %04d/%02d/%02d %02d:%02d:%02d\n Event = %s \n",
      trc->t.trc.dt.year + 1900, trc->t.trc.dt.month, trc->t.trc.dt.day, trc->t.trc.dt.hour,
      trc->t.trc.dt.min, trc->t.trc.dt.sec, smSbTag2Str(trcevtTable, trc->t.trc.evnt));

   if ((len = osFwrite(prntBuf, 1, cmStrlen((CONSTANT U8*)prntBuf), cfin)) !=
                   cmStrlen((CONSTANT U8*)prntBuf))
   {
      osPrintf("%s:  File write error ,File=:%s\n", "smsbbdy1.c", "trace.log");
      RETVALUE(RFAILED);
   }
   sprintf(prntBuf, 
       " Source Port = 0x%02X%02X\tDestination Port = 0x%02X%02X",
       trc->t.trc.evntParm[0],trc->t.trc.evntParm[1],trc->t.trc.evntParm[2],trc->t.trc.evntParm[3]);
   if ((len = osFwrite(prntBuf, 1, cmStrlen((CONSTANT U8*)prntBuf), cfin)) !=
                   cmStrlen((CONSTANT U8*)prntBuf))
   {
      osPrintf("%s:  File write error ,File=:%s\n", "smsbbdy1.c", "trace.log");
      RETVALUE(RFAILED);
   }

   chunkType = trc->t.trc.evntParm[12];
   if(chunkType == 6 || chunkType == 9)
   {
      errorCause = trc->t.trc.evntParm[17];
      errorCause <<= 8;
      errorCause |= trc->t.trc.evntParm[18];
      sprintf(prntBuf, "\n Chunk Type = %s\tError Cause = %s\n Data:\n",chunkTypeTbl[chunkType].kw,errorCauseTbl[errorCause].kw);
   }
   else
      sprintf(prntBuf, "\n Chunk Type = %s\n Data:\n",chunkTypeTbl[chunkType].kw);
   if ((len = osFwrite(prntBuf, 1, cmStrlen((CONSTANT U8*)prntBuf), cfin)) != 
                   cmStrlen((CONSTANT U8*)prntBuf))
   {
      osPrintf("%s:  File write error ,File=:%s\n", "smsbbdy1.c", "trace.log");
      RETVALUE(RFAILED);
   }

   col = 0;
   for (i = 0; i < trc->t.trc.len; i++)
   {
      sprintf(prntBuf, " %02X", trc->t.trc.evntParm[i]);

      if ((len = osFwrite(prntBuf, 1, cmStrlen((CONSTANT U8*)prntBuf), cfin)) !=
                      cmStrlen((CONSTANT U8*)prntBuf)) 
      {
         osPrintf("%s:  File write error ,File=:%s\n", "smsbbdy1.c", "trace.log");
         RETVALUE(RFAILED);
      }


      col += 3;

      if (col >= 70)
      {
         if ((len = osFwrite("\n", 1, 1, cfin) != 1))
         {
            osPrintf("%s:  File write error ,File=:%s\n", "smsbbdy1.c", "trace.log");
            RETVALUE(RFAILED);
         }

         col = 0;
      }
   }
   sprintf(prntBuf, "\n SapId = %u\n\n******************\n\n", trc->t.trc.sapId);
   if ((len = osFwrite(prntBuf, 1, cmStrlen((CONSTANT U8*)prntBuf), cfin)) !=
                   cmStrlen((CONSTANT U8*)prntBuf))
   {
      osPrintf("%s:  File write error ,File=:%s\n", "smsbbdy1.c", "trace.log");
      RETVALUE(RFAILED);
   }

   osFclose(cfin);

#endif /* SB_INOP */

/*sb082.102: changes for SIP*/
#ifdef SO_ACC22
   soAcSmMiLsbTrcInd(pst, trc);
#endif /*-- SO_ACC22 --*/
/* sb001.103: GCP Acceptance related changes */
#if (defined(MGAC_ACC) &&  defined(GCP_PROV_SCTP))
   mgAcSmMiLsbTrcInd(pst, trc);
#endif /*-- MGAC_ACC --*/
/* sb016.103 Updated for S1AP release 1.1 */
#ifdef SZ
   UNUSED(chunkType);
   UNUSED(errorCause);
   UNUSED(col);
   UNUSED(i);
   szAcSmMiLsbTrcInd(pst, trc);
#endif 

   RETVALUE(ROK);

} /* end of SmMiLsbTrcInd() */


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
*       File:  smsbbdy1.c
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

#ifdef SB_ACC
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
*       File:  smsbbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 smHiActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 smHiActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(smHiActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
} /* end of smHiActvInit */

/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from TUCL layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   smsbexms.c
*
*/

#ifdef ANSI
PUBLIC S16 smHiActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smHiActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC3(smHiActvTsk)


   SExitTsk();
   RETVALUE(ROK);
} /* end of smHiActvTsk */
#endif /* SB_ACC */

#if (SB_INOP) || (SB_ACC)
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
*       File:  smsbbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 smItActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 smItActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(smItActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
} /* end of smItActvInit */

/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from IT layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   smsbbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 smItActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smItActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC3(smItActvTsk)


   SExitTsk();
   RETVALUE(ROK);
} /* end of smItActvTsk */
#endif /* SB_INOP || SB_ACC */



/*
 *
 *       Fun:    smsbPrintCfm - print common confirm structures
 *
 *       Desc:
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */

#ifdef ANSI
PUBLIC Void smsbPrintCfm
(
SbMgmt              *mgt
)
#else
PUBLIC Void smsbPrintCfm(mgt)
SbMgmt              *mgt;
#endif /* ANSI */
{
   TRC2(smsbPrintCfm)

      sprintf(prntBuf,
      "  Status = %s Reason = %s\n",
      smSbTag2Str(statusTable, mgt->cfm.status),
      smSbTag2Str(reasonTable, mgt->cfm.reason));
   SPrint(prntBuf);

   RETVOID;
} /* end of smsbPrintCfm() */

/*
 *
 *       Fun:    SMSB_DUMPCHUNKSTS - 
 *
 *       Desc:
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *       File:   smsbbdy1.c
 *
 */
#ifdef ANSI
PUBLIC Void dumpChunkSts
(
SbChunkSts x 
)
#else
PUBLIC Void dumpChunkSts(x)                                      
SbChunkSts x;
#endif
{
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   sprintf(prntBuf,                                                     
   "noInitTx = %10d        noInitReTx = %10d     \nnoInitRx = %10d\n",
      x.noInitTx,                           
      x.noInitReTx,                          
      x.noInitRx);                           
   SPrint(prntBuf);                            

   sprintf(prntBuf,                             
   "noIAckTx = %10d        noIAckRx = %10d\n", 
      x.noIAckTx,                                 
      x.noIAckRx);                                 
   SPrint(prntBuf);                                 

   sprintf(prntBuf,                                                          
   "noShDwnTx = %10d       noShDwnReTx = %10d      \n noShDwnRx = %10d\n",   
      x.noShDwnTx,                              
      x.noShDwnReTx,                             
      x.noShDwnRx);                               
   SPrint(prntBuf);                                

   sprintf(prntBuf,                                 
   "noShDwnAckTx = %10d    noShDwnAckRx = %10d\n", 
      x.noShDwnAckTx,                                                     
      x.noShDwnAckRx);                                                  
   SPrint(prntBuf);                                                         

   sprintf(prntBuf,                                                          
   "noCookieTx = %10d      noCookieReTx = %10d      \nnoCookieRx = %10d\n",  
      x.noCookieTx,                          
      x.noCookieReTx,                         
      x.noCookieRx);                           
   SPrint(prntBuf);                             

   sprintf(prntBuf,                              
   "noCkAckTx = %10d       noCkAckRx = %10d\n", 
      x.noCkAckTx, 
      x.noCkAckRx);
   SPrint(prntBuf);

   sprintf(prntBuf, 
   "noDataTx = %10d        noDataReTx = %10d        \nnoDataRx = %10d\n", 
      x.noDataTx,                     
      x.noDataReTx,                    
      x.noDataRx);                      
   SPrint(prntBuf);                      

   sprintf(prntBuf,                           
   "noDAckTx = %10d        noDAckRx = %10d\n",
      x.noDAckTx,                               
      x.noDAckRx);                            
   SPrint(prntBuf);                              

#ifdef LSB2
   sprintf(prntBuf,                               
   "noHBeatTx = %10d        noHBeatRx = %10d\n", 
      x.noHBeatTx,                             
      x.noHBeatRx);                             
   SPrint(prntBuf);                              
                                                  
   sprintf(prntBuf,                                
   "noHBAckTx = %10d        noHBAckRx = %10d\n",  
      x.noHBAckTx,                            
      x.noHBAckRx);                           
   SPrint(prntBuf);                             
#endif
                                                 
#ifdef LSB3
   sprintf(prntBuf,                               
   "noAbortTx = %10d        noAbortRx = %10d\n", 
      x.noAbortTx,                             
      x.noAbortRx);                             
   SPrint(prntBuf);                              
#endif

#ifdef LSB6
   sprintf(prntBuf,      
   "noErrorTx = %10d        noErrorRx = %10d\n",   
      x.noErrorTx,                                  
      x.noErrorRx);                                
   SPrint(prntBuf);                               
#endif
#else /*else of BIT_64 */

   sprintf(prntBuf,                                                     
   "noInitTx = %10ld        noInitReTx = %10ld     \nnoInitRx = %10ld\n",
      x.noInitTx,                           
      x.noInitReTx,                          
      x.noInitRx);                            
   SPrint(prntBuf);                            

   sprintf(prntBuf,                             
   "noIAckTx = %10ld        noIAckRx = %10ld\n", 
      x.noIAckTx,                                 
      x.noIAckRx);                                 
   SPrint(prntBuf);                                 

   sprintf(prntBuf,                                                          
   "noShDwnTx = %10ld       noShDwnReTx = %10ld      \n noShDwnRx = %10ld\n",   
      x.noShDwnTx,                              
      x.noShDwnReTx,                             
      x.noShDwnRx);                               
   SPrint(prntBuf);                                

   sprintf(prntBuf,                                 
   "noShDwnAckTx = %10ld    noShDwnAckRx = %10ld\n", 
      x.noShDwnAckTx,                                                     
      x.noShDwnAckRx);                                                     
   SPrint(prntBuf);                                                         

   sprintf(prntBuf,                                                          
   "noCookieTx = %10ld      noCookieReTx = %10ld      \nnoCookieRx = %10ld\n",  
      x.noCookieTx,                          
      x.noCookieReTx,                         
      x.noCookieRx);                           
   SPrint(prntBuf);                             

   sprintf(prntBuf,                              
   "noCkAckTx = %10ld       noCkAckRx = %10ld\n", 
      x.noCkAckTx, 
      x.noCkAckRx); 
   SPrint(prntBuf);

   sprintf(prntBuf, 
   "noDataTx = %10ld        noDataReTx = %10ld        \nnoDataRx = %10ld\n", 
      x.noDataTx,                     
      x.noDataReTx,                    
      x.noDataRx);                      
   SPrint(prntBuf);                      

   sprintf(prntBuf,                           
   "noDAckTx = %10ld        noDAckRx = %10ld\n",
      x.noDAckTx,                               
      x.noDAckRx);                             
   SPrint(prntBuf);                              

#ifdef LSB2
   sprintf(prntBuf,                               
   "noHBeatTx = %10ld        noHBeatRx = %10ld\n", 
      x.noHBeatTx,                             
      x.noHBeatRx);                             
   SPrint(prntBuf);                              
                                                  
   sprintf(prntBuf,                                
   "noHBAckTx = %10ld        noHBAckRx = %10ld\n",  
      x.noHBAckTx,                            
      x.noHBAckRx);                            
   SPrint(prntBuf);                             
#endif
                                                 
#ifdef LSB3
   sprintf(prntBuf,                               
   "noAbortTx = %10ld        noAbortRx = %10ld\n", 
      x.noAbortTx,                             
      x.noAbortRx);                             
   SPrint(prntBuf);                              
#endif

#ifdef LSB6
   sprintf(prntBuf,      
   "noErrorTx = %10ld        noErrorRx = %10ld\n",   
      x.noErrorTx,                                  
      x.noErrorRx);                                
   SPrint(prntBuf);                               
#endif
#endif /* BIT_64 */
}


/********************************************************************30**

         End of file:     smsbbdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:10 2015

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
1.1          ---      wvdl 1. Initial version.
1.2          ---      hnh  2. Second version.
/main/3      ---      sb   1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000.
            sb018.102 ab   1. Heartbeat statistics added.
            sb042.102 hl   1. Added change for SHT interface and Rolling
                              Up Grade
            sb052.102 ag   1. Abort Statistics added.
            sb067.102 kp   1. Acceptance files and ShMiShtCntrlCfm
                              moved under SB_ACC compile flag.  
            sb068.102 kp   1. Error Statistics added. 
            sb082.102 kp   1. Non-ANSI compilation changes.
/main/4      ---   rsr/ag  1. Updated for Release of 1.3
            sb001.103 ag   1. GCP Acceptance related changes
            sb002.103 rsr  1. GCP Acceptance related changes -
                              Header files included
            sb003.103 ag   1. Satellite SCTP feature (under compile-time flag
                             SB_SATELLITE)
            sb012.103 pkaX 1. Placed timer test related code under LSB12 flag.
            sb016.103 hsingh 1. Updated for S1AP release 1.1.
/main/4     sb028.103 ajainx 1. Fix for compilation warnings. 
/main/4     sb030.103 krkx 1. Fixed the warnings during 64-BIT compilation.
*********************************************************************91*/
