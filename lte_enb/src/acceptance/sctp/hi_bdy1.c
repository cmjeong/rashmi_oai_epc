

/********************************************************************20**

     Name:     hi_bdy1.c - Dummy lower layer for the SCTP.
               SCTP layer.
     Type:     C source file

     Desc:     C code for primitives destined for the lower layer.
               - Copy contents to the queue.
               - Display the results of the received primitive.

     File:     hi_bdy1.c

     Sid:      hi_bdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:09 2015

     Prg:      mrw

*********************************************************************21*/

/*

  hi_bdy1.c - Lower layer for the SCTP layer.

Following functions are provided in this file:
         HiUiHitBndReq         - Bind request
         HiUiHitServOpenReq    - Request to create new server
         HiUiHitUDatReq        - Unit data request
         HiUiHitDiscReq        - Disconnection request

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
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"      /* common DNS library */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb.h"            /* SCTP internal defines */
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
#include "cm_dns.x"      /* common DNS library */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#ifdef SB_ACC
#include "sb_acc.x"        /* typedefs for the SCTP test controller */
#endif /*SB_ACC*/


/* local defines */
#define STRTAG(x)                { x, #x }
#define NOT_FOUND                (-1)

#define SMSB_STRLEN(x, i)                                                     \
   {                                                                          \
      *i = 0;                                                                 \
      while (x[*i] != 0)                                                         \
      {                                                                       \
         (*i)++;                                                              \
      }                                                                       \
   }

/* local typedefs */
typedef struct hiSbStrTag
{
   S16      tag;
   Txt      *txt;
} HiSbStrTag;

/* forward references */

PUBLIC S16 hiSbActvInit ARGS((Ent ent, Inst inst, Region region,
   Reason reason));
PUBLIC Void hisbPrintCfm ARGS((SctStatus status, Reason reason));

/* public variable declarations */

/* public variable definitions */

/* private variable definitions */
PRIVATE Txt prntBuf[PRNTSZE];

PRIVATE HiSbStrTag statusTable[] =
{
   STRTAG(LCM_PRIM_OK),
   STRTAG(LCM_PRIM_NOK),
   STRTAG(NOT_FOUND)
};

PRIVATE HiSbStrTag reasonTable[] =
{
   STRTAG(LCM_REASON_NOT_APPL),
   STRTAG(LCM_REASON_INVALID_ELMNT),
   STRTAG(LCM_REASON_INVALID_SAP),
   STRTAG(LCM_REASON_INVALID_PAR_VAL),
   STRTAG(LCM_REASON_MEM_NOAVAIL),
   STRTAG(LCM_REASON_GENCFG_NOT_DONE),
   STRTAG(LCM_REASON_HASHING_FAILED),
   STRTAG(LCM_REASON_RECONFIG_FAIL),
   STRTAG(LCM_REASON_INVALID_ACTION),
   STRTAG(LCM_REASON_INVALID_SUBACTION),
   STRTAG(NOT_FOUND)
};


PRIVATE HiSbStrTag choiceTable[] =
{
   STRTAG(HI_USER_CON_ID),
   STRTAG(HI_PROVIDER_CON_ID),
   STRTAG(NOT_FOUND)
};

PRIVATE HiSbStrTag actionTable[] =
{
   STRTAG(HI_SHTDWN_RECV),
   STRTAG(HI_SHTDWN_SEND),
   STRTAG(HI_SHTDWN_BOTH),
   STRTAG(HI_CLOSE),
   STRTAG(HI_LEAVE_MCAST_GROUP),
   STRTAG(NOT_FOUND)
};

/* private function declarations */
PRIVATE Txt *hiSbTag2Str   ARGS((HiSbStrTag *tagArray, S16  tag));


/* private routines */

/*
 *
 *       Fun:    hiSbTag2Str
 *
 *       Desc:   Converts the tag to its string representation
 *
 *       Ret:    pointer to string representation
 *
 *       Notes:  None
 *
 *       File:   hi_bdy1.c
 *
 */

#ifdef ANSI
PRIVATE Txt *hiSbTag2Str
(
HiSbStrTag           *tagArray,
S16                  tag
)
#else
PRIVATE Txt *hiSbTag2Str(tagArray, tag)
HiSbStrTag           *tagArray;
S16                  tag;
#endif /* ANSI */
{
   U16 i;

   TRC3(hiSbTag2Str)
   for (i = 0; tagArray[i].tag != NOT_FOUND; i++)
   {
      if (tagArray[i].tag == tag)
      {
         break;
      }
   }

   RETVALUE(tagArray[i].txt);
} /* end of hiSbTag2Str */

/* public routines */

/*
 *
 *       Fun:    HiUiHitBndReq - Bind requestm
 *
 *       Desc:   prints the ID's of the two SAPs that will bind
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   hi_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 HiUiHitBndReq
(
Pst    *pst,
SuId   suId,
SpId   spId
)
#else
PUBLIC S16 HiUiHitBndReq(pst, suId, spId)
Pst    *pst;
SuId   suId;
SpId   spId;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   UNUSED(pst);

   TRC3(HiUiHitBndReq)
   UNUSED(pst);

#ifdef SB_ACC
   /* Pack primitive data in queue struchire */
   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_BND_REQ; /* Override pst->event */
   QElm.t.sbMsg.hi.suId = suId;
   QElm.t.sbMsg.hi.spId = spId;
   (Void) sbAccPushMsg(&QElm);

   #endif

   sprintf(prntBuf, "HitBndReq:  spId: %u, suId: %u\n",
   spId, suId );
   SPrint(prntBuf);

   RETVALUE(ROK);
} /* end of HiUiHitBndReq() */
/*
 *
 *       Fun:    HiUiHitServOpenReq - status confirm
 *
 *       Desc:   prints the status confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   hi_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 HiUiHitServOpenReq
(
Pst          *pst,
SpId         spId,
UConnId      servConId,
CmTptAddr    *servTAddr,
CmTptParam   *tPar,
CmIcmpFilter *icmpFilter,
U8           srvcType
)
#else
PUBLIC S16 HiUiHitServOpenReq(pst, spId, servConId, servTAddr, tPar, icmpFilter, srvcType)
Pst *pst;
SpId spId;
UConnId servConId;
CmTptAddr *servTAddr;
CmTptParam *tPar;
CmIcmpFilter *icmpFilter;
U8 srvcType;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(HiUiHitServOpenReq)
   UNUSED(pst);
   UNUSED(icmpFilter);
   UNUSED(tPar);

#ifdef SB_ACC
   /* Pack primitive data in queue struchire */
   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_SERVOPEN_REQ; /* Override pst->event */
   QElm.t.sbMsg.hi.spId = spId;
   QElm.t.sbMsg.hi.suConId = servConId;
   QElm.t.sbMsg.hi.srvcType = srvcType;


   (Void) cmMemcpy( (U8 *) &(QElm.t.sbMsg.hi.localTAddr),
                   (U8 *) servTAddr,
                   (PTR) sizeof(CmTptAddr) );

   (Void) sbAccPushMsg(&QElm);
#endif

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   sprintf(prntBuf, "HiUiHitServOpenReq(spId(%d), servConId(%d), addr(%d), port(%d)\n",
           spId, servConId, servTAddr->u.ipv4TptAddr.address, servTAddr->u.ipv4TptAddr.port );
#else
   sprintf(prntBuf, "HiUiHitServOpenReq(spId(%d), servConId(%ld), addr(%ld), port(%d)\n",
           spId, servConId, servTAddr->u.ipv4TptAddr.address, servTAddr->u.ipv4TptAddr.port );
#endif /* BIT_64 */

   SPrint(prntBuf);

   RETVALUE(ROK);
} /* end of HiUiHitServOpenReq() */

/*
 *
 *       Fun:    HiUiHitUDatReq - control confirm
 *
 *       Desc:   prints the control confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   hi_bdy1.c
 *
 */

#ifdef HI_REL_1_4
#ifdef ANSI
PUBLIC S16 HiUiHitUDatReq
(
Pst         *pst,
SpId        spId,
UConnId     spConId,
CmTptAddr   *remAddr,
CmTptAddr   *srcAddr,
CmIpHdrParm *hdrParm,
CmTptParam  *tPar,
Buffer      *mBuf
)
#else
PUBLIC S16 HiUiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, hdrParm, tPar, 
                          mBuf)
Pst         *pst;
SpId        spId;
UConnId     spConId;
CmTptAddr   *remAddr;
CmTptAddr   *srcAddr;
CmIpHdrParm *hdrParm;
CmTptParam  *tPar;
Buffer      *mBuf;
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 HiUiHitUDatReq
(
Pst         *pst,
SpId        spId,
UConnId     spConId,
CmTptAddr   *remAddr,
CmTptAddr   *srcAddr,
CmIpHdrParm *hdrParm,
Buffer      *mBuf
)
#else
PUBLIC S16 HiUiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, hdrParm, mBuf)
Pst         *pst;
SpId        spId;
UConnId     spConId;
CmTptAddr   *remAddr;
CmTptAddr   *srcAddr;
CmIpHdrParm *hdrParm;
Buffer      *mBuf;
#endif /* ANSI */
#endif /* HI_REL_1_4 */
{
#ifdef SB_ACC
SbAccMsgQElm QElm;
#endif

   TRC3(HiUiHitUDatReq)
   UNUSED(pst);

#ifdef SB_ACC
   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_UDAT_REQ; /* Override pst->event */
   QElm.t.sbMsg.hi.spId = spId;

   (Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.hi.peerTAddr),
                   (U8 *) (remAddr),
                   (PTR) sizeof(CmTptAddr));
   (Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.hi.localTAddr),
                   (U8 *) (srcAddr),
                   (PTR) sizeof(CmTptAddr));
   /* sb003.103:  parameter passing corrected during SATELLITE SCTP feature */ 
   (Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.hi.hdrParm),
                   (U8 *)(hdrParm),
                   (PTR) sizeof(CmIpHdrParm));

   if(mBuf != (Buffer *) NULLP ) /* check if buffer have been allocated */
   {
      SB_RLSMEM(QElm.t.sbMsg.hi.mBuf)
      SAddMsgRef(mBuf, DFLT_REGION, DFLT_POOL, &(QElm.t.sbMsg.hi.mBuf));
   } else {
      SPrint("Buffer not allocated \n\n");
   }

   (Void) sbAccPushMsg(&QElm);
#endif
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   sprintf(prntBuf, "HiUiHitUDatReq:  spId = %u, spConId = %d \n",
   spId, spConId );
#else
   sprintf(prntBuf, "HiUiHitUDatReq:  spId = %u, spConId = %ld \n",
   spId, spConId );
#endif /* BIT_64 */

   SPrint(prntBuf);
   /* RFC 4460 -- MLK fix */
   SB_RLSMEM(mBuf)

   RETVALUE(ROK);
} /* end of HiUiHitUDatReq() */

/*
 *
 *       Fun:    HiUiHitDiscReq - status indication
 *
 *       Desc:   prints the status indication (alarm)
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   hi_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 HiUiHitDiscReq
(
Pst        *pst,
SpId       spId,
U8         choice,
UConnId    conId,
Action     action,
CmTptParam *tPar
)
#else
PUBLIC S16 HiUiHitDiscReq(pst, spId, choice, conId, action, tPar)
Pst        *pst;
SpId       spId;
U8         choice;
UConnId    conId;
Action     action;
CmTptParam *tPar;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(HiUiHitDiscReq)
   UNUSED(pst);
   UNUSED(tPar);

#ifdef SB_ACC
   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_DISC_REQ; /* Override pst->event */
   QElm.t.sbMsg.hi.spId = spId;
   QElm.t.sbMsg.hi.choice = choice;
   QElm.t.sbMsg.hi.conId = conId;
   QElm.t.sbMsg.hi.action = action;
   (Void) sbAccPushMsg(&QElm);
#endif

   sprintf(prntBuf, "HitDiscReq: conId = %u choice = %s action = %s \n",
   (unsigned int)conId, hiSbTag2Str(choiceTable, choice), hiSbTag2Str(actionTable, action) );
   SPrint(prntBuf);
   RETVALUE(ROK);
} /* end of HiUiHitDiscReq() */


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
*       File:  hi_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 hiSbActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 hiSbActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(hiSbActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
} /* end of hiSbActvInit */


/*
 *
 *       Fun:    hisbPrintCfm - print common confirm struchires
 *
 *       Desc:
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *       File:   hi_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC Void hisbPrintCfm
(
SctStatus        status,
Reason           reason
)
#else
PUBLIC Void hisbPrintCfm(status, reason)
SctStatus           status;
Reason           reason;
#endif /* ANSI */
{
   TRC2(hisbPrintCfm)
     if (status != 0)
      {
         sprintf(prntBuf,
         "  Status = %s \n  ", hiSbTag2Str(statusTable, status));
         SPrint(prntBuf);
      }


      if (reason != 0)
      {
         sprintf(prntBuf,
         "  Reason = %s \n  ", hiSbTag2Str(reasonTable, reason));
         SPrint(prntBuf);
      }


   RETVOID;
} /* end of hisbPrintCfm() */


/********************************************************************30**

         End of file:     hi_bdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:09 2015

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
/main/3      ---      mrw    1.Initial version
 /main/3     ---      sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
            sb042.102 hl     1. Added change for SHT interface
            sb057.102 pr     1. Added change to HIT interface.
/main/4      ---   rsr/ag    1. Updated for Release of 1.3
            sb003.103 ag     1. Satellite SCTP feature:
                                fixed the parameter passing issue.
/main/4     sb030.103 krkX    1. Fixed the warnings during 64-BIT compilation.
*********************************************************************91*/
