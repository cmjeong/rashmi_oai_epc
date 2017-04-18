

/********************************************************************20**

     Name:     sb_dbdy1.c - M3UA to SCTP interface functions

     Type:     C source file

     Desc:     C code for the APIs implemented for a dummy sctp layer, viz.
               IT  (for M3UA)
               SSI (for system services)

     File:     sb_dbdy1.c

     Sid:      sb_dbdy1.c@@/main/5 - Thu Jul 26 07:53:07 2007

     Prg:      jdb

*********************************************************************21*/

/*

  sb_dbdy1.c - SCTP interface functions implemented in SCTP

Following functions are provided in this file for M3UA:
         SbUiSctBndReq            - Bind request
         SbUiSctEndpOpenReq       - Open endpoint request
         SbUiSctEndpCloseReq      - Close endpoint request
         SbUiSctAssocReq          - Association Establish request
         SbUiSctAssocRsp          - Association Establish response
         SbUiSctTermReq           - Association Termination request
         SbUiSctSetPriReq         - Set Primary Destination Network Address request
         SbUiSctHBeatReq          - Enable/Disable Heartbeat request
         SbUiSctDatReq            - Data request
         SbUiSctStaReq            - Status request

Following functions are provided in this file for SSI:
         sbActvInit       - driver initialization
         sbActvTmr0       - driver timer callback (for instance 0)
*/

/*

Following functions should be provided in sctp's portable upper
interface file (sb_ptui.c):

         SbUiSctBndCfm            - Bind confirm
         SbUiSctEndpOpenCfm       - Open endpoint confirm
         SbUiSctEndpCloseCfm      - Close endpoint confirm
         SbUiSctAssocCfm          - Association Establish confirm
         SbUiSctAssocInd          - Association Establish indication
         SbUiSctTermInd           - Association Termination indication
         SbUiSctTermCfm           - Association Termination confirm
         SbUiSctSetPriCfm         - Set Primary Destination Network Address confirm
         SbUiSctHBeatCfm          - Enable/Disable Heartbeat confirm
         SbUiSctDatCfm            - Data confirm
         SbUiSctStaCfm            - Status confirm
         SbUiSctStaInd            - Status indication
         SbUiSctFlcInd            - Flow control indication

Following functions should be provided in the system services service provider
files:
         ### List of S-functions called by SCTP

*/

/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 */


/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "sb_port.h"       /* sb port defines */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb.h"            /* SCTP internal defines */
#include "sb_mtu.h"        /* MTU defines */
#include "sb_err.h"        /* SCTP error */
#ifdef SB_ACC
#include "sb_acc.h"
#endif /*SB_ACC*/

/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
#include "sb_port.x"       /* sb_port typedefs */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#include "sb_mtu.x"        /* MTU typedefs */
#include "sb.x"            /* SCTP typedefs */
#ifdef SB_ACC
#include "sb_acc.x"        /* typedefs for the SCTP test controller */
#endif /*SB_ACC*/



/* local defines */
/*#define NO_TEST_RUN*/
/*#define TEST_RUN_M300*/
/*#define TEST_RUN_M301*/
/*#define TEST_RUN_M302*/
/*#define TEST_RUN_M303*/
/* local typedefs */


#define REV_POST(evnt)                                            \
   {                                                               \
   rev.srcProcId = sbGlobalCb.sbInit.procId;                       \
   rev.srcEnt = sbGlobalCb.sbInit.ent;                             \
   rev.srcInst = sbGlobalCb.sbInit.inst;                           \
   rev.dstProcId = pst->srcProcId;                                 \
   rev.dstEnt = pst->srcEnt;                                       \
   rev.dstInst = pst->srcInst;                                     \
   rev.selector = SEL_LC; /*0->LC, 1->IT (tightly coupled)*/       \
   rev.prior = PRIOR0;                                             \
   rev.route = RTESPEC;                                            \
   rev.region = TSTREG;                                            \
   rev.pool = TSTPOOL;                                             \
   rev.event = evnt;                                               \
   }

/* forward references */

/* public variable declarations */

/* public variable definitions */

PUBLIC SbGlobalCb  sbGlobalCb;  /* SCTP control block */
PRIVATE Txt prntBuf[PRNTSZE];

/* public routines */

/* private routines */
PRIVATE  void switchInit2InitAck  ARGS(( Buffer *mBuf, SbAccAssoc  *assoc));

/* Functions for system services interface */

/*
 *
 *       Fun:    sbActvInit - activated at initialization time
 *
 *       Desc:   first function to be called after registration
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   sb_dbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 sbActvInit
(
Ent ent,                   /* ent */
Inst inst,                 /* instance */
Region region,             /* region */
Reason reason              /* reason */
)
#else
PUBLIC S16 sbActvInit(ent, inst, region, reason)
Ent ent;                   /* ent */
Inst inst;                 /* instance */
Region region;             /* region */
Reason reason;             /* reason */
#endif /* ANSI */
{

   TRC2(sbActvInit)

   SBDBGP(DBGMASK_SI, (sbGlobalCb.sbInit.prntBuf,
          "sbActvInit(Ent(%d), Inst(%d), Region(%d), Reason(%d))\n",
           ent, inst, region, reason));

   /* Initialize the SCTP control block */
   SB_ZERO(&sbGlobalCb, sizeof(sbGlobalCb));

   sbGlobalCb.sbInit.ent = ent;
   sbGlobalCb.sbInit.inst = inst;
   sbGlobalCb.sbInit.region = region;
   sbGlobalCb.sbInit.reason = reason;
   sbGlobalCb.sbInit.cfgDone = FALSE;
   /* Pool Id is obtained after SGetSMem in general configuration */
   sbGlobalCb.sbInit.pool = TSTPOOL; /* use test pool */
   sbGlobalCb.sbInit.procId = SFndProcId();
   sbGlobalCb.sbInit.acnt = FALSE;
   sbGlobalCb.sbInit.usta = TRUE;
   sbGlobalCb.sbInit.trc = FALSE;

#ifdef DEBUGP
   sbGlobalCb.sbInit.dbgMask = 0xFFFF; /* enable all debug messages by default */
#endif /* DEBUGP */

   /* sbInit.lmPst is initialised in general configuration */
   /* perform external initialization, if needed */
   /*sbInitExt();*/

   RETVALUE(ROK);
} /* end of sbActvInit() */

/*
 *
 *       Fun:    sbActvTmr - task activation because of a timer event
 *
 *       Desc:   called by system services when a timer event occurs
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   sb_dbdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 sbActvTmr
(
void
)
#else
PUBLIC S16 sbActvTmr()
#endif /* ANSI */
{
   TRC3(sbActvTmr)

   SExitTsk();

   RETVALUE(ROK);
} /* end of sbActvTmr() */



/****************************************************************************/
/* SCT upper interface primitives                                           */
/****************************************************************************/

/*
*
*       Fun:   SbUiSctBndReq
*
*       Desc:  Bind Request Primitive
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function binds a User to the SCTP Layer.
*              The SCTP Layer allocates a service access point for this
*              bind and records the identity of the service user. If the
*              SAP is already bound then it is first unbound and then rebound.
*              It also issues a SbUiSctBndCfm to the service user
*              after completing a successful bind.
*
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctBndReq
(
Pst        *pst,              /* Post structure */
SuId        suId,             /* service user id */
SpId        spId              /* service provider id */
)
#else
PUBLIC S16 SbUiSctBndReq(pst, suId, spId)
Pst        *pst;              /* Post Structure */
SuId        suId;             /* service user id */
SpId        spId;             /* service provider id */
#endif
{
   Pst rev;

   TRC3(SbUiSctBndReq)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctBndReq(pst, suId(%d), spId(%d))\n", suId, spId));

   /* Reverse post */
   REV_POST(ACC_EVT_BND_CFM)

   (Void) SbUiSctBndCfm(&rev, suId, CM_BND_OK);

   RETVALUE(ROK);
} /* end SbUiSctBndReq */

/*
*
*       Fun:   SbUiSctEndpOpenReq
*
*       Desc:  Primitive to Open an Endpoint Server.
*
*       Ret:   ROK
*              ROKDUP
*              RFAILED
*
*       Notes: This function opens an endpoint on the SCTP Layer. An unused
*              spEndpId is found and the necessary structures are created
*              and initialised.
*
*              ACC: suId = spId, spEndpId = suEndpId
*
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctEndpOpenReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        suEndpId,         /* Service user Endpoint ID */
SctPort        port,             /* Port number */
CmNetAddr     *intfNAddr         /* Interface IP address */
)
#else
PUBLIC S16 SbUiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddr)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        suEndpId;         /* Service user Endpoint ID */
SctPort        port;             /* Port number */
CmNetAddr     *intfNAddr;        /* Interface IP address */
#endif
{
   /* local parameters */
   UConnId        spEndpId;
   SuId           suId;
   Pst            rev;

   TRC3(SbUiSctEndpOpenReq)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctEndpOpenReq(pst, spId(%d), suEndpId(%d), port(%d), intfNAddr)\n",
          (unsigned int) spId, (unsigned int)suEndpId, port));

   /* Reverse post */
   REV_POST(ACC_EVT_ENDPOPEN_CFM);

   suId = spId;
   spEndpId = suEndpId;

   (Void) SbUiSctEndpOpenCfm( &rev, suId, suEndpId,
                             spEndpId, SCT_OK, SCT_CAUSE_NOT_APPL);

   RETVALUE(ROK);
} /* end SbUiSctEndpOpenReq */


/*
*
*       Fun:   SbUiSctEndpCloseReq
*
*       Desc:  Primitive to Close an Endpoint Server.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function closes an endpoint on the SCTP Layer.
*       ACC:
*       suId = spId, suEndpId = spEndpId
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctEndpCloseReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        spEndpId          /* Service provider Endpoint ID */
)
#else
PUBLIC S16 SbUiSctEndpCloseReq(pst, spId, spEndpId)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        spEndpId;         /* Service provider Endpoint ID */
#endif
{
   /* local parameters */
   SuId           suId;
   Pst            rev;
   UConnId        suEndpId;

   TRC3(SbUiSctEndpCloseReq)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctEndpCloseReq(pst, spId(%d), spEndpId, )\n", spId));

   /* Reverse post */
   REV_POST(ACC_EVT_ENDPCLOSE_CFM);

   suId = spId;
   suEndpId = spEndpId;
   (Void) SbUiSctEndpCloseCfm( &rev, suId, suEndpId,
                        SCT_OK, SCT_CAUSE_NOT_APPL);

   RETVALUE(ROK);
} /* end SbUiSctEndpCloseReq */


/*
*
*       Fun:   SbUiSctAssocReq
*
*       Desc:  Primitive to Open an Association
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function tries to establish an association with a peer.
*              Termination indications are sent if something goes wrong.
*
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctAssocReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        spEndpId,         /* Service provider Endpoint ID */
UConnId        suAssocId,        /* Service user Association ID */
CmNetAddr     *priDstNAddr,      /* Primary destination network address */
SctPort        dstPort,          /* Destination port number */
SctStrmId      outStrms,         /* no. outgoing streams */
SctNetAddrLst *dstNAddrLst,      /* destination network address list */
SctNetAddrLst *srcNAddrLst,      /* source network address list */
Buffer        *vsInfo            /* vendor specific info */
)
#else
PUBLIC S16 SbUiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr,
                           dstPort, outStrms, dstNAddrLst, srcNAddrLst, vsInfo)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        spEndpId;         /* Service provider Endpoint ID */
UConnId        suAssocId;        /* Service user Association ID */
CmNetAddr     *priDstNAddr;      /* Primary destination network address */
SctPort        dstPort;          /* Destination port number */
SctStrmId      outStrms;         /* no. outgoing streams */
SctNetAddrLst *dstNAddrLst;      /* destination network address list */
SctNetAddrLst *srcNAddrLst;      /* source network address list */
Buffer        *vsInfo;           /* vendor specific info */
#endif
{
   /* local parameters */
   UConnId        spAssocId;
   SuId           suId;
   Pst            rev;

   TRC3(SbUiSctAssocReq)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "SbUiSctAssocReq(pst, spId(%d), spEndpId, suAssocId, priDstNAddr, dstPort, outStrms, dstNAddrLst, srcNAddrLst, vsInfo)\n",
          spId));

   /* Reverse post */
   REV_POST(ACC_EVT_ASSOC_CFM);

   suId = spId;
   spAssocId = suAssocId;


   /* inform the upper layer */
   SbUiSctAssocCfm(&rev, suId, suAssocId,
                   spAssocId, dstNAddrLst, dstPort,
                   outStrms, (Buffer *) vsInfo);

   RETVALUE(ROK);
} /* end SbUiSctAssocReq */

/*
*
*       Fun:   SbUiSctAssocRsp
*
*       Desc:  Primitive to Respond to an Open an Association Indication
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function tries to establish an association with a peer.
*              Termination indications are sent if something goes wrong.
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctAssocRsp
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spEndpId,         /* Service provider endpoint ID */
SctAssocIndParams    *assocIndParams,   /* interface specific params */
SctResult             result,           /* result */
Buffer               *vsInfo            /* vendor specific info */
)
#else
PUBLIC S16 SbUiSctAssocRsp(pst, spId, spEndpId, assocIndParams, result, vsInfo)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spEndpId;         /* Service provider endpoint ID */
SctAssocIndParams    *assocIndParams;   /* interface specific params */
SctResult             result;           /* result */
Buffer               *vsInfo;           /* vendor specific info */
#endif
{
  /* local parameters */

   TRC3(SbUiSctAssocRsp)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctAssocRsp(pst, spId(%d), spAssocId, dstNAddr)\n", spId));

   RETVALUE(ROK);
}/* SbUiSctAssocRsp() */
/*
*
*       Fun:   SbUiSctTermReq
*
*       Desc:  Primitive to Request Termination of an Association
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: This function tries to terminate an association with a peer.
*              Termination confirmation is sent on successful completion with
*              positive status, and with negative status if something went
*              wrong. The termination procedure can be graceful or ungraceful.
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctTermReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               assocId,          /* Association ID */
U8                    assocIdType,      /* Association ID type */
Bool                  abortFlg          /* Termination type */
)
#else
PUBLIC S16 SbUiSctTermReq(pst, spId, assocId, assocIdType, abortFlg)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               assocId;          /* Association ID */
U8                    assocIdType;      /* Association ID type */
Bool                  abortFlg;         /* Termination type */
#endif
{
   Pst      rev;
   SuId     suId;
   UConnId  suAssocId;
   UConnId  spAssocId;

   TRC3(SbUiSctTermCfm)
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctSetPriReq(pst, spId(%d), spAssocId, dstNAddr)\n", spId));

   REV_POST(ACC_EVT_TERM_CFM);

   suId = spId;
   suAssocId = assocId;
   spAssocId = assocId;

   SbUiSctTermCfm(&rev, suId, suAssocId,  SCT_OK, SCT_CAUSE_NOT_APPL);
   RETVALUE(ROK);
}/* SbUiSctTermReq() */

/*
*
*       Fun:   SbUiSctSetPriReq
*
*       Desc:  Primitive to Set a New Primary Address on an Association
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <none>
*
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctSetPriReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr          /* New primary network address */
)
#else
PUBLIC S16 SbUiSctSetPriReq(pst, spId, spAssocId, dstNAddr)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
#endif
{
   /* local parameters */
   SuId           suId;
   UConnId        suAssocId;
   Pst            rev;

   TRC3(SbUiSctSetPriReq)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctSetPriReq(pst, spId(%d), spAssocId, dstNAddr)\n", spId));

   REV_POST(ACC_EVT_SETPRI_CFM);

   suId = spId;
   suAssocId = spAssocId;

   SbUiSctSetPriCfm(&rev, suId, suAssocId,  SCT_OK, SCT_CAUSE_NOT_APPL);
   RETVALUE(ROK);
}/* SbUiSctSetPriReq() */

/*
*
*       Fun:   SbUiSctHBeatReq
*
*       Desc:  Primitive to Request enable/disable Heartbeat Information.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: Heartbeat can be enabled/disabled per association or per
*              destination address.
*
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctHBeatReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr,         /* New primary network address */
U16                   intervalTime,     /* heartbeat periodicity value */
SctStatus             status            /* Type of request to process */
)
#else
PUBLIC S16 SbUiSctHBeatReq(pst, spId, spAssocId, dstNAddr, intervalTime, status)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
U16                   intervalTime;     /* heartbeat periodicity value */
SctStatus             status;           /* Type of request to process */
#endif
{
   /* local parameters */
   SuId                 suId;
   UConnId              suAssocId;
   Pst                  rev;
   SbAccAssoc           assoc_1;

   TRC3(SbUiSctHBeatReq)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctHBeatReq(pst, spId(%d), spAssocId, dstNAddr, intervalTime, \
       status)\n", spId));

   REV_POST(ACC_EVT_HBEAT_CFM);

   suId = spId;
   suAssocId = spAssocId;

   SbUiSctHBeatCfm(&rev, suId, suAssocId, assoc_1.intfNAddr, status, SCT_OK, SCT_CAUSE_NOT_APPL);
   RETVALUE(ROK);
}/* SbUiSctHBeatReq() */
/*
*
*       Fun:   SbUiSctDatReq
*
*       Desc:  Primitive Request to send Data to a peer.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <none>
*
*       File:  sb_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctDatReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr,         /* New primary network address */
SctStrmId             strmId,           /* Stream ID */
Bool                  unorderFlg,       /* unordered delivery */
Bool                  nobundleFlg,      /* no bundling  */
U16                   lifeTime,         /* datagram lifetime value */
U32                   protId,           /* Protocol ID */
Buffer               *mBuf              /* message buffer */
)
#else
PUBLIC S16 SbUiSctDatReq(pst, spId, spAssocId, dstNAddr, strmId, unorderFlg,
                         nobundleFlg, lifeTime, protId, mBuf)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
SctStrmId             strmId;           /* Stream ID */
Bool                  unorderFlg;       /* unordered delivery */
Bool                  nobundleFlg;      /* no bundling  */
U16                   lifeTime;         /* datagram lifetime value */
U32                   protId;           /* Protocol ID */
Buffer               *mBuf;             /* message buffer */
#endif
{

  /* local parameters */

   TRC3(SbUiSctDatReq)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctHBeatReq(pst, spId(%d), spAssocId, dstNAddr, intervalTime, \
       status)\n", spId));


   RETVALUE(ROK);
}/* SbUiSctDatReq() */

/*
*
*       Fun:   SbUiSctStaReq
*
*       Desc:  Primitive Request for Status Information.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <none>
*
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbUiSctStaReq
(
Pst                  *pst,              /* Post structure */
SpId                  spId,             /* Service provider SAP ID */
UConnId               spAssocId,        /* Service provider association ID */
CmNetAddr            *dstNAddr,         /* New primary network address */
U8                    staType           /* Status type */
)
#else
PUBLIC S16 SbUiSctStaReq(pst, spId, spAssocId, dstNAddr, staType)
Pst                  *pst;              /* Post structure */
SpId                  spId;             /* Service provider SAP ID */
UConnId               spAssocId;        /* Service provider association ID */
CmNetAddr            *dstNAddr;         /* New primary network address */
U8                    staType;          /* Status type */
#endif
{
   /* local parameters */
   SuId                  suId;             /* Service user SAP ID */
   UConnId               suAssocId;        /* Service user association ID */
   SctStaInfo            *staInfo;          /* Status information */
   Pst                   rev;             /* Post structure */

   TRC3(SbUiSctStaReq)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
       "SbUiSctStaReq(pst, spId(%d), spAssocId, dstNAddr, staType)\n", spId));

   REV_POST(ACC_EVT_STA_CFM)

   suId = spId;
   suAssocId = spAssocId;

   SB_ZERO(&staInfo, sizeof(SctStaInfo));

   switch ( staType )
   {
      case SCT_RTRV_UNSENT_DGMS:
         break;

      case SCT_RTRV_UNACK_DGMS:
         break;

      case SCT_RTRV_UNDEL_DGMS:
         break;

      case SCT_GET_ASSOC_INFO:
         SbUiSctStaCfm(&rev, suId, suAssocId,
                       dstNAddr, SCT_OK, SCT_CAUSE_NOT_APPL,
                       staInfo);
         break;

      case SCT_GET_ADDR_INFO:
         SbUiSctStaCfm(&rev, suId, suAssocId,
                       dstNAddr, SCT_OK, SCT_CAUSE_NOT_APPL,
                       staInfo);
         break;

      case SCT_GET_RTRV_INFO:
         SbUiSctStaCfm(&rev, suId, suAssocId,
                       dstNAddr, SCT_OK, SCT_CAUSE_NOT_APPL,
                       staInfo);
         break;

      case SCT_GET_FLC_INFO:
            SbUiSctFlcInd(&rev, suId, suAssocId,
                          SCT_FLC_ACTIVE);
         break;

      default:
         SbUiSctStaCfm(&rev, suId, suAssocId,
                       dstNAddr,SCT_NOK, SCT_CAUSE_INV_STATE,
                       (SctStaInfo *) NULLP);
        break;
   }
   RETVALUE(ROK);
}/* SbUiSctStaReq() */


/****************************************************************************/
/* Layer manager interface primitives                                       */
/****************************************************************************/


/*
*
*       Fun:   Configuration request
*
*       Desc:  This receives the config request and returns the cfgCfm.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbCfgReq
(
Pst *pst,                 /* post structure */
SbMgmt *cfg              /* configure */
)
#else
PUBLIC S16 SbMiLsbCfgReq(pst, cfg)
Pst *pst;                 /* post structure */
SbMgmt *cfg;             /* configure */
#endif
{
   Pst      rev;

   TRC3(SbMiLsbCfgReq)
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
       "SbMiLsbCfgReq(pst, cfg) \n" ));

   REV_POST(ACC_EVT_CFG_REQ)
      /* scanf("status: %u",(unsigned int *) &cfg->cfm.status); */
   cfg->cfm.status =  LCM_PRIM_OK;
   /* scanf("reason: %u",(unsigned int *) &cfg->cfm.reason); */
   cfg->cfm.reason = LCM_REASON_NOT_APPL;

   SbMiLsbCfgCfm(&rev, cfg);

   RETVALUE(ROK);
} /* end of SbMiLsbCfgReq */


/*
*
*       Fun:   Status request
*
*       Desc:  This receives the status request and returns the StaCfm.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbStaReq
(
Pst *pst,                 /* post structure */
SbMgmt *sta              /* status */
)
#else
PUBLIC S16 SbMiLsbStaReq(pst, sta)
Pst *pst;                 /* post structure */
SbMgmt *sta;             /* status */
#endif
{
   Pst    rev;
   TRC3(SbMiLsbStaReq)
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
       "SbMiLsbStaReq(pst, sta) \n" ));

   REV_POST(ACC_EVT_STA_REQ)
   sta->cfm.status = LCM_PRIM_OK;
   sta->cfm.reason = LCM_REASON_NOT_APPL;

   /*Look at header and fill required parameters */

   SbMiLsbStaCfm(&rev, sta);


   RETVALUE(ROK);
} /* end of SbMiLsbStaReq */

/*
*
*       Fun:   Control request
*
*       Desc:  This function is used to send control request to SCTP layer
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbCntrlReq
(
Pst *pst,                 /* post structure */
SbMgmt *cntrl            /* control */
)
#else
PUBLIC S16 SbMiLsbCntrlReq(pst, cntrl)
Pst *pst;                 /* post structure */
SbMgmt *cntrl;           /* control */
#endif
{
   Pst   rev;
   TRC3(SbMiLsbCntrlReq)
    SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
       "SbMiLsbCntrlReq(pst, cntrl) \n" ));

   REV_POST(ACC_EVT_STA_REQ)
   cntrl->cfm.status = LCM_PRIM_OK;
   cntrl->cfm.reason = LCM_REASON_NOT_APPL;

   SbMiLsbCntrlCfm(&rev, cntrl);
   RETVALUE(ROK);
} /* end of SbMiLsbCntrlReq */

/*
*
*       Fun:   Statistics request
*
*       Desc:  This function is used to request statistics from SCTP layer
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sb_dbdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 SbMiLsbStsReq
(
Pst *pst,                 /* post structure */
Action action,
SbMgmt *sts              /* statistics */
)
#else
PUBLIC S16 SbMiLsbStsReq(pst, action, sts)
Pst *pst;                 /* post structure */
Action action;
SbMgmt *sts;             /* statistics */
#endif
{
   TRC3(SbMiLsbStsReq)
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
       "SbMiLsbStsReq(pst, sts) \n" ));
   RETVALUE(ROK);
} /* end of SbMiLsbStsReq */


 /****************************************************************************/
/* Lower layer interface primitives                                       */
/****************************************************************************/


/*
*
*       Fun:   Unit data indication
*
*       Desc:  This function is used to deliver incoming data to the service user
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitUDatInd
(
Pst *pst,                  /* post struchire */
SuId suId,                 /* service user SAP ID */
UConnId suConId,           /* service user's connection ID */
CmTptAddr *srcAddr,        /* source transport address */
CmTptAddr *destAddr,       /* source transport address */
CmIpHdrParm *hdrParm,      /* header parameters */
Buffer *mBuf               /* message buffer */
)
#else
PUBLIC S16 SbLiHitUDatInd(pst, suId, suConId, srcAddr, destAddr, hdrParm, mBuf)
Pst *pst;                  /* post struchire */
SuId suId;                 /* service user SAP ID */
UConnId suConId;           /* service user's connection ID */
CmTptAddr *srcAddr;        /* source transport address */
CmTptAddr *destAddr;       /* source transport address */
CmIpHdrParm *hdrParm;      /* header parameters */
Buffer *mBuf;              /* message buffer */
#endif

{
   SpId        spId;
   Pst         rev;
   CmTptAddr   *remAddr;
   UConnId     spConId;
   SbAccAssoc  assoc_1;

   TRC3(SbLiHitUDatInd)
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
       "SbLiHitUDatInd  \n") );
   REV_POST(ACC_EVT_UDAT_IND)

    (Void) cmMemcpy((U8 *)&(remAddr), (U8 *) &(srcAddr), (S32)PRNTSZE);
    (Void) cmMemcpy((U8 *) &(srcAddr), (U8 *) &(destAddr), (S32)PRNTSZE);
   spConId = suConId;
   spId = suId;

   /* Have to unpack mBuf, change parameters to match next expected chunk and pack again */

   switchInit2InitAck(mBuf, &assoc_1);
   SbLiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, hdrParm, mBuf);
   SB_RLSMEM(mBuf)                    /* release memory */
   RETVALUE(ROK);
} /* end of SbLiHitUDatInd */

/*
*
*       Fun:   Bind Confirm
*
*       Desc:  This function is used to confirm a bind request from the SCTP layer
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitBndCfm
(
Pst *pst,                 /* post structure */
SuId suId,                /* service user SAP ID */
U8 status                 /* status */
)
#else
PUBLIC S16 SbLiHitBndCfm(pst, suId, status)
Pst *pst;                 /* post structure */
SuId suId;                /* service user SAP ID */
U8 status;                /* status */
#endif
{
   TRC3(SbLiHitBndCfm)

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
       "SbLiHitBndCfm \n") );
   RETVALUE(ROK);
} /* end of SbLiHitBndCfm */

/*
*
*       Fun:   Disconnection Indication
*
*       Desc:  This function is used to inform the service user that the socket is being
*              closed by the TUCL.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitDiscInd
(
Pst *pst,                 /* post strauchire */
SuId suId,                /* service user SAP ID */
U8 choice,                /* choice parameter */
UConnId conId,            /* connection ID */
Reason  reason            /* reason */
)
#else
PUBLIC S16 SbLiHitDiscInd(pst, suId, choice, conId, reason)
Pst *pst;                 /* post strauchire */
SuId suId;                /* service user SAP ID */
U8 choice;                /* choice parameter */
UConnId conId;            /* connection ID */
Reason  reason;           /* reason */
#endif
{
   TRC3(SbLiHitDiscInd)
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
       "SbLiHitDiscInd \n") );   
   RETVALUE(ROK);
} /* end of SbLiHitDiscInd */

/*
*
*       Fun:   Disconnection Confirm
*
*       Desc:  This function is used to indicate that the disconnect request was successful.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitDiscCfm
(
Pst *pst,                 /* post strauchire */
SuId suId,                /* service user SAP ID */
U8 choice,                /* choice parameter */
UConnId conId,            /* connection ID */
Action action             /* action */
)
#else
PUBLIC S16 SbLiHitDiscCfm(pst, suId, choice, conId, action)
Pst *pst;                 /* post strauchire */
SuId suId;                /* service user SAP ID */
U8 choice;                /* choice parameter */
UConnId conId;            /* connection ID */
Action action;            /* action */
#endif
{
   TRC3(SbLiHitDiscCfm)
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
       "SbLiHitDiscCfm \n") );
   RETVALUE(ROK);
} /* end of SbLiHitDiscCfm */

/*
*
*       Fun:   Connect confirm
*
*       Desc:  This function is used to confirm that the listener socket has been opened.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitConCfm
(
Pst *pst,                 /* post structure */
SuId suId,                /* service user Id */
UConnId suConId,          /* service user's connection Id */
UConnId spConId,          /* service provider's connection Id */
CmTptAddr *localAddr     /* local transport address */
)
#else
PUBLIC S16 SbLiHitConCfm(pst, suId, suConId, spConId, localAddr)
Pst *pst;                 /* post structure */
SuId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
UConnId spConId;          /* service provider's connection Id */
CmTptAddr *localAddr;    /* local transport address */
#endif
{
   TRC3(SbLiHitConCfm)
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf, "SbLiHitConCfm \n") );
   RETVALUE(ROK);
} /* end of SbLiHitConCfm */

/*
*
*       Fun:   Connect Indication
*
*       Desc:  Used with TCP..
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitConInd
(
Pst *pst,                 /* post structure */
SuId suId,                /* service user Id */
UConnId suConId,          /* service user's connection Id */
UConnId spConId,          /* service provider's connection Id */
CmTptAddr *localAddr     /* local transport address */
)
#else
PUBLIC S16 SbLiHitConInd(pst, suId, suConId, spConId, localAddr)
Pst *pst;                 /* post structure */
SuId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
UConnId spConId;          /* service provider's connection Id */
CmTptAddr *localAddr;    /* local transport address */
#endif
{
   TRC3(SbLiHitConInd)
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf, "SbLiHitConInd \n") );
   RETVALUE(ROK);
} /* end of SbLiHitConInd */

/*
*
*       Fun:   Data indication.
*
*       Desc:  Used with the TCP.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitDatInd
(
Pst *pst,                 /* post structure */
SuId suId,                /* service user Id */
UConnId suConId,          /* service user's connection Id */
Buffer   *mBuf
)
#else
PUBLIC S16 SbLiHitDatInd(pst, suId, suConId, mBuf)
Pst *pst;                 /* post structure */
SuId suId;                /* service user Id */
UConnId suConId;          /* service user's connection Id */
Buffer   *mBuf;
#endif
{
   TRC3(SbLiHitDatInd)
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf, "SbLiHitDatInd \n") );
   RETVALUE(ROK);
} /* end of SbLiHitDatInd */

/*
*
*       Fun:   Flow control indication
*
*       Desc:  Used with TCP.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  hi_phii.c
*
*/

#ifdef ANSI
PUBLIC S16 SbLiHitFlcInd
(
Pst *pst,                 /* post structure */
SuId suId,                /* service user Id */
Reason reason 
)
#else
PUBLIC S16 SbLiHitFlcInd(pst, suId, reason)
Pst *pst;                 /* post structure */
SuId suId;                /* service user Id */
Reason reason;
#endif
{
   TRC3(SbLiHitFlcInd)
   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf, "SbLiHitFlcInd \n") );
   RETVALUE(ROK);
} /* end of SbLiHitFlcInd */
/*
*
*       Fun:   switchInit2InitAck
*
*       Desc:  Unpack mBuf containing INIT chunk, change contents to that of INIT_ACK and pack again to get new mBuf.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void switchInit2InitAck
(
Buffer         *mBuf,
SbAccAssoc     *assoc       /* Assocciation structure */
)
#else
PUBLIC  void switchInit2InitAck(mBuf, assoc)
Buffer         *mBuf;
SbAccAssoc     *assoc;       /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U32         initTag;
   U32         arwnd;
   U16         outStrms;
   U16         inStrms;
   U32         initTsn;
   U32         srcNAddr;
   U32         adlerRcv;   /* the adler checksum received in the datagram */
   Data        cookie[MSG_SIZE];
   SbAccChunkBld *buildPar;
   U32         rwnd;
   U8          len;
   U32         adler;
   U8          i;


   TRC2(switchInit2InitAck)

   SB_UNPACK_CM()   /* Perform unpacking functions common to all the chunks */
   SUnpkU32(&initTag, mBuf);
   assoc->verTagPeer = initTag;
   SUnpkU32(&initTag, mBuf);
   SUnpkU32(&arwnd, mBuf);
   SUnpkU16(&outStrms, mBuf);
   SUnpkU16(&inStrms, mBuf);
   SUnpkU32(&initTsn, mBuf);
   SUnpkU32(&srcNAddr, mBuf);
   initTag = ACC_INIT_PEERTAG;
   verTag = initTag;
   outStrms = buildPar->inStrms;
   inStrms = buildPar->outStrms;
   initTsn = ACC_INIT_TSN;
   rwnd = ACC_ARWND_INIT;
   srcNAddr =  dstNAddrLst_1[3]; /* Primitive originated at primary destination addres of receiving endpoint */

   (Void) cmMemcpy((U8 *) &(cookie), (U8 *) &(assoc->cookie), (S32)PRNTSZE);

   len = sizeof (cookie);
   chunkLeng =  24 + len;

   adler = (U32) 1;
   SB_BUILD_CM()             /*Initialize common parameters and calculate their Adler checksum */

   /* Calculate remaining adler checksum of datagram */
   adler = sbAdler32(adler,(U8 *) &initTag, sizeof(initTag) );
   adler = sbAdler32(adler,(U8 *) &rwnd, sizeof(rwnd) );
   adler = sbAdler32(adler,(U8 *) &outStrms, sizeof(outStrms) );
   adler = sbAdler32(adler,(U8 *) &inStrms, sizeof(inStrms) );
   adler = sbAdler32(adler,(U8 *) &initTsn, sizeof(initTsn) );
   adler = sbAdler32(adler, cookie, len );
   adler = sbAdler32(adler,(U8 *) &srcNAddr, sizeof(srcNAddr) );

   sbGetPacket(&mBuf, SBUT_TXPKTFIXEDSIZE, chunkLeng);
   SPkU32(srcNAddr, mBuf);


   chunkLeng = 16 + len;  /* data entries of type U8 */

   for ( (i = (len-1)); (i = 0); i-- ) {
      SPkU8(cookie[i], mBuf );
   }    /* End For */

   SPkU32(initTsn, mBuf);
   SPkU16(inStrms, mBuf);
   SPkU16(outStrms, mBuf);
   SPkU32(rwnd, mBuf);
   SPkU32(initTag, mBuf);

   /* Pack the parameters */
   SB_PACK_CM()                   /* Perform packing functions common to all the chunks */

   RETVOID;
} /* end switchInit2InitAck */



/********************************************************************30**

         End of file:     sb_dbdy1.c@@/main/5 - Thu Jul 26 07:53:07 2007

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
1.1          ---      mrw  1. Initial version
1.2          ---      jdb  2. Updated for dummy driver
/main/2      ---      hnh  3. Updates for sctp dummy
/main/4      ---      sb   1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000.
/main/5      ---   rsr/ag  1. Updated for Release of 1.3
*********************************************************************91*/

