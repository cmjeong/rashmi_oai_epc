

/********************************************************************20**

     Name:     it_bdy1.c - Dummy Upper layer for the SCTP layer.
     Type:     C source file

     Desc:     C code for upper layer primitives destined for the service user.
               - Copy contents to the queue.
               - Display the results of the received primitive.

     File:     it_bdy1.c

     Sid:      it_bdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:09 2015

     Prg:      mrw

*********************************************************************21*/

/*

  it_bdy1.c - Upper layer to the SCTP layer.

Following public functions are provided in this file:
         ItLiSctBndCfm                -  Bind confirm
         ItLiSctEndpOpenCfm           -  Open endpoint confirm
         ItLiSctEndpCloseCfm          -  Close endpoint confirm
         ItLiSctAssocInd              -  Association Establish indication
         ItLiSctAssocCfm              -  Association Establish confirm
         ItLiSctTermInd               -  Association Termination indication
         ItLiSctTermCfm               -  Association Termination confirm
         ItLiSctSetPriCfm             -  Set Primary Destination Network Address confirm
         ItLiSctHBeatCfm              -  Enable/Disable Heartbeat confirm
         ItLiSctDatInd                -  Data indication
         ItLiSctStaInd                -  Status indication

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
#ifdef SB_INOP 
#include "cm_os.h"       /* common hashing */
#endif
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */
#include "sb_acc.h"
#ifdef SB_INOP 
#include "sb_ibdy.h"
#endif


/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#ifdef SB_INOP 
#include "cm_os.x"       /* common hashing */
#endif
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#include "sb_acc.x"
#ifdef SB_INOP
#include "sb_ibdy.x"        /* typedefs for the SCTP test controller */
#ifdef SB_PRFM_RCVR
#include <sys/time.h>
#endif
#endif


/* local defines */
#define STRTAG(x)                { x, #x }
#define NOT_FOUND                (-1)
#define ACC_REASON_NOTUSED  255
#define ACC_CAUSE_NOTUSED   255
#define ACC_STATUS_NOTUSED  255
#define ACC_RESULT_NOTUSED  255


/* local typedefs */
/* forward references */

EXTERN U8  filedata;

PUBLIC S16 itSbActvInit ARGS((Ent ent, Inst inst, Region region,
   Reason reason));
PUBLIC Void itsbPrintCfm ARGS((SctStatus status, SctCause cause, SctResult result, Reason reason));

/* public variable declarations */

/* public variable definitions */
PUBLIC Txt filename[50];

/* private variable definitions */
PRIVATE Txt prntBuf[PRNTSZE];

PUBLIC U32 pktCount=0;
PUBLIC U32 pktThousand=0;

typedef struct itSbStrTag
{
   S16      tag;
   Txt      *txt;
} ItSbStrTag;

PRIVATE ItSbStrTag statusCfmTable[] =
{
   STRTAG(SCT_GET_ASSOC_INFO),          /* StaCfm status */
   STRTAG(SCT_GET_ADDR_INFO),
   STRTAG(SCT_GET_RTRV_INFO),
   STRTAG(NOT_FOUND)
};

PRIVATE ItSbStrTag statusIndTable[] =
{
   STRTAG(SCT_STATUS_COMM_UP),          /* StaInd status */
   STRTAG(SCT_STATUS_NET_UP),
   STRTAG(SCT_STATUS_NET_DOWN),
   STRTAG(SCT_STATUS_SND_FAIL),
   STRTAG(SCT_STATUS_ABRT),
   STRTAG(SCT_STATUS_SHUTDOWN),
   STRTAG(SCT_STATUS_INV),
   STRTAG(SCT_STATUS_COMM_LOST),
   STRTAG(NOT_FOUND)
};

PRIVATE ItSbStrTag statusTable[] =
{

   STRTAG(SCT_GET_ASSOC_INFO),          /* StaCfm status */
   STRTAG(SCT_GET_ADDR_INFO),
   STRTAG(SCT_GET_RTRV_INFO),
   STRTAG(SCT_STATUS_COMM_UP),          /* StaInd status */
   STRTAG(SCT_STATUS_NET_UP),
   STRTAG(SCT_STATUS_NET_DOWN),
   STRTAG(SCT_STATUS_SND_FAIL),
   STRTAG(SCT_STATUS_ABRT),
   STRTAG(SCT_STATUS_SHUTDOWN),
   STRTAG(SCT_STATUS_INV),
   STRTAG(SCT_STATUS_COMM_LOST),
 /* sb008.103: Adding new values for the  status field */
#ifdef SCT_ENHANCED_TERMIND
   STRTAG(SCT_STATUS_MAX_INIT_SENT),
   STRTAG(SCT_STATUS_ABORT_SENT),
   STRTAG(SCT_STATUS_NOUSR_DATA),
#endif
   STRTAG(NOT_FOUND)
};
PRIVATE ItSbStrTag hBeatStaTable[] =
{  STRTAG(SCT_HBEAT_ENB_ASSOC),         /* Heartbeat status */
   STRTAG(SCT_HBEAT_DIS_ASSOC),
   STRTAG(SCT_HBEAT_ENB_DTA),
   STRTAG(SCT_HBEAT_DIS_DTA),
};

PRIVATE ItSbStrTag reasonTable[] =
{
   STRTAG(SCT_FLC_START),                 /* FlcInd reason */
   STRTAG(SCT_FLC_DROP),
   STRTAG(SCT_FLC_STOP),
   STRTAG(SCT_FLC_ACTIVE),
   STRTAG(SCT_FLC_INACTIVE),
   STRTAG(NOT_FOUND)
};


PRIVATE ItSbStrTag causeTable[] =
{
   STRTAG(SCT_CAUSE_NOT_APPL),
   STRTAG(SCT_CAUSE_ENDP_OPEN),
   STRTAG(SCT_CAUSE_TERM_FAILED),
   STRTAG(SCT_CAUSE_OUTRES),
   STRTAG(SCT_CAUSE_EXCEED_CONF_VAL),
   STRTAG(SCT_CAUSE_REM_UNREACH),
   STRTAG(SCT_CAUSE_INIT_FAILED),
   STRTAG(SCT_CAUSE_INV_STATE),
   STRTAG(SCT_CAUSE_QFULL),
   STRTAG(SCT_CAUSE_LTIME_EXPIRE),
   STRTAG(SCT_CAUSE_SHUTDOWN_PRGS),
   STRTAG(SCT_CAUSE_INV_PAR_VAL),
   STRTAG(SCT_CAUSE_UNKNOWN),
   STRTAG(NOT_FOUND)
};

PRIVATE ItSbStrTag assocIdTypeTable[] =
{
   STRTAG(SCT_ASSOCID_SP),
   STRTAG(SCT_ASSOCID_SU),
   STRTAG(NOT_FOUND)
};


PRIVATE ItSbStrTag resultTable[] =
{
   STRTAG(SCT_OK),
   STRTAG(SCT_NOK),
   STRTAG(NOT_FOUND)
};

PRIVATE ItSbStrTag bindResultTable[] =
{
   STRTAG(CM_BND_OK),
   STRTAG(CM_BND_NOK),
   STRTAG(NOT_FOUND)
};

#ifdef SB_ACC
PRIVATE ItSbStrTag datatypeTable[] =
{
   STRTAG(SCT_PEER_DAT),
   STRTAG(SCT_UNORDER_DAT),
   STRTAG(SCT_UNSENT_DAT),
   STRTAG(SCT_UNACK_DAT),
   STRTAG(SCT_UNDEL_DAT),
   STRTAG(SCT_PARTIAL_DAT),
   STRTAG(NOT_FOUND)
};
#endif /* SB_ACC */


PRIVATE ItSbStrTag boolTable[] =
{
   STRTAG(TRUE),
   STRTAG(FALSE),
   STRTAG(NOT_FOUND)
};

 PRIVATE ItSbStrTag assocstateTable[] =
{
   STRTAG(SB_ST_CLOSED),
   STRTAG(SB_ST_OPEN),
   STRTAG(SB_ST_COOKIE_WAIT),
   STRTAG(SB_ST_ESTABLISHED),
   STRTAG(SB_ST_COOKIE_SENT),
   STRTAG(SB_ST_SDOWN_PEND),
   STRTAG(SB_ST_SDOWN_SENT),
   STRTAG(SB_ST_SDOWN_RCVD),
   STRTAG(NOT_FOUND)
};

/* private routines */

/*
 *
 *       Fun:    itSbTag2Str
 *
 *       Desc:   Converts the tag to its string representation
 *
 *       Ret:    pointer to string representation
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PRIVATE Txt *itSbTag2Str
(
ItSbStrTag           *tagArray,
S16                  tag
)
#else
PRIVATE Txt *itSbTag2Str(tagArray, tag)
ItSbStrTag           *tagArray;
S16                  tag;
#endif /* ANSI */
{
   U16 i;

   TRC3(itSbTag2Str)


   for (i = 0; tagArray[i].tag != NOT_FOUND; i++)
   {
      if (tagArray[i].tag == tag)
      {
         break;
      }
   }

   RETVALUE(tagArray[i].txt);
} /* end of itSbTag2Str */

/* public routines */

/*
 *
 *       Fun:    ItLiSctBndCfm - Bind confirm
 *
 *       Desc:   prints the bind confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctBndCfm
(
Pst         *pst,
SuId        suId,
SctResult   result
)
#else
PUBLIC S16 ItLiSctBndCfm(pst, suId, result)
Pst         *pst;
SuId        suId;
SctResult   result;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(ItLiSctBndCfm)
   UNUSED(pst);

#ifdef SB_ACC
   /* Pack primitive data in queue structure */
   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_BND_CFM; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.result = result;
   (Void) sbAccPushMsg(&QElm);
#endif

   SPrint("SctBndReq: " );
   sprintf(prntBuf, "%s \n", itSbTag2Str(bindResultTable, result) );
   SPrint(prntBuf);

   RETVALUE(ROK);
} /* end of ItLiSctBndCfm() */

/*
 *
 *       Fun:    ItLiSctEndpOpenCfm - Open endpoint confirm
 *
 *       Desc:   prints the EndpOpen confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctEndpOpenCfm
(
Pst                  *pst,
SuId                 suId,
UConnId              suEndpId,
UConnId              spEndpId,
SctResult            result,
SctCause             cause
)
#else
PUBLIC S16 ItLiSctEndpOpenCfm(pst, suId, suEndpId, spEndpId, result, cause)
Pst                  *pst;
SuId                 suId;
UConnId              suEndpId;
UConnId              spEndpId;
SctResult            result;
SctCause             cause;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#else  /* SB_INOP */
   SctStatus    status;
   Reason       reason;
   U16 i;
#endif /* SB_ACC || SB_INOP */

   TRC3(ItLiSctEndpOpenCfm)
   UNUSED(pst);

#ifdef SB_ACC

   /* Pack primitive data in queue structure */
   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_ENDPOPEN_CFM; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.suEndpId = suEndpId;
   QElm.t.sbMsg.it.spEndpId = spEndpId;
   QElm.t.sbMsg.it.result = result;
   QElm.t.sbMsg.it.cause = cause;
   (Void) sbAccPushMsg(&QElm);

#else

   status = 0;
   reason = 0;
   for(i=0;i<MAXBLOCKS;i++)
   {
     if (endp[i].suEndpId == suEndpId)
     {
        if ((endp[i].occupied) && (result == SCT_OK))
        {
           osPrintf("\nCF :Endp Cfm Received For Block %d\n",i);
           endp[i].spEndpId = spEndpId;
           endp[i].cfgDone = TRUE;
           break;
        }
        else
        {
           endp[i].occupied = FALSE;
        }
     }
   }

#endif /* SB_ACC || SB_INOP */

   SPrint("SctEndpOpenCfm: ");
   itsbPrintCfm(ACC_STATUS_NOTUSED, cause, result, ACC_REASON_NOTUSED);

   RETVALUE(ROK);
} /* end of ItLiSctEndpOpenCfm() */

/*
 *
 *       Fun:    ItLiSctEndpCloseCfm - status confirm
 *
 *       Desc:   prints the status confirm Endpoint close
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctEndpCloseCfm
(
Pst                  *pst,
SuId                 suId,
UConnId              suEndpId,
SctResult            result,
SctCause             cause
)
#else
PUBLIC S16 ItLiSctEndpCloseCfm(pst, suId, suEndpId, result, cause)
Pst                  *pst;
SuId                 suId;
UConnId              suEndpId;
SctResult            result;
SctCause             cause;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#else /*  SB_INOP */
   U16   i;
#endif /* SB_ACC || SB_INOP */
   SctStatus       status;
   Reason          reason;

   TRC3(ItLiSctEndpCloseCfm)
   UNUSED(pst);

   status = 0;
   reason = 0;

#ifdef SB_ACC

   /* Pack primitive data in queue structure */
   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_ENDPCLOSE_CFM; /*  Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.suEndpId = suEndpId;
   QElm.t.sbMsg.it.result = result;
   QElm.t.sbMsg.it.cause = cause;
   (Void) sbAccPushMsg(&QElm);

#else /* SB_INOP */

   for(i=0;i<MAXBLOCKS;i++)
   {
     if((endp[i].occupied) && (suEndpId == endp[i].suEndpId))
     {
        osPrintf("\nCF :Endp Close Cfm Received with cause  %d \n",cause);
        endp[i].cfgDone = FALSE;
        endp[i].occupied = FALSE;
        break;
     }
   }

#endif /* SB_ACC || SB_INOP */

   SPrint("SctEndpCloseCfm: ");
   itsbPrintCfm(status, cause, result, reason);

   RETVALUE(ROK);
} /* end of ItLiSctEndpCloseCfm() */

/*
 *
 *       Fun:    ItLiSctAssocInd - Association establishment confirm
 *
 *       Desc:   prints the association establish parameters
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctAssocInd
(
Pst                *pst,
SuId               suId,
UConnId            suEndpId,
SctAssocIndParams  *assocParams,
Buffer             *vsInfo           /* VsInfo - not used any more */
)
#else
PUBLIC S16 ItLiSctAssocInd(pst, suId, suEndpId, assocParams, vsInfo)
Pst                *pst;
SuId               suId;
UConnId            suEndpId;
SctAssocIndParams  *assocParams;
Buffer             *vsInfo;          /* VsInfo - not used any more */
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#else /* SB_INOP */
   U16    i;
   U16    endpIdx;
   U16    assocIdx;
#endif /* SB_ACC || SB_INOP */

   TRC3(ItLiSctAssocInd)
   UNUSED(pst);
   UNUSED(vsInfo);

   SPrint("ItLiSctAssocInd: ");
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   sprintf(prntBuf, "  suId = %u suEndpId = %u \n", suId, suEndpId);
#else
   sprintf(prntBuf, "  suId = %u suEndpId = %lu \n", suId, suEndpId);
#endif /* BIT_64 */

   SPrint(prntBuf);

#ifdef SB_ACC

   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_ASSOC_IND; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.suEndpId = suEndpId;
   (Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.it.assocParams),
                   (U8 *) assocParams,
                   (PTR) sizeof(SctAssocIndParams) );
   /* Vendor specific info not used */
   (Void) sbAccPushMsg(&QElm);

#else /*  SB_INOP */

   osPrintf("\n AssocInd Received with suEndpId %d \n",suEndpId);
   for(assocIdx=0;assocIdx<MAXBLOCKS;assocIdx++)
   {
     if(assocReq[assocIdx].occupied)
       continue;
     else
       break;
   }
   if(assocIdx == MAXBLOCKS)
   {
     osPrintf("\nCF: AssocInd Received - Could not find  Empty Assoc Block \n");
     return(ROK);
   }
  for(i=0;i<MAXBLOCKS;i++)
  {
    if((endp[i].occupied) && (suEndpId == endp[i].suEndpId))
    {
       endpIdx = i;
       osPrintf("\nCF : Client Node : Endp matched for AssocInd \n");

       if(assocParams->type == SCT_ASSOC_IND_COOKIE)
       {
          osPrintf("\nCF : AssocInd With Cookie Parameters \n");
          assocReq[assocIdx].node = ASSOC_SERVER;
          assocReq[assocIdx].suAssocId = assocParams->t.cookieParams.suAssocId;
          assocReq[assocIdx].spAssocId = assocParams->t.cookieParams.spAssocId;
          assocReq[assocIdx].endpIdx = i;
          assocReq[assocIdx].occupied = TRUE;
          assocReq[assocIdx].assocDone = TRUE;
          assocReq[assocIdx].suEndId = suEndpId;
          assocReq[assocIdx].dstPort = assocParams->t.cookieParams.peerPort;
  
          cmMemcpy((U8 *)&assocReq[assocIdx].dstNAddrLst,
                   (U8 *)&assocParams->t.cookieParams.peerAddrLst,
                   sizeof(SctNetAddrLst));
  
          /* Copy the first address in dstNetAddr */
          cmMemcpy((U8 *)&assocReq[assocIdx].dstNetAddr,
                   (U8 *)&assocParams->t.cookieParams.peerAddrLst.nAddr[0],
                   sizeof(CmNetAddr));
        }
        else
        {
          assocReq[assocIdx].outStrms = assocParams->t.initParams.outStrms;
          assocReq[assocIdx].inStrms = assocParams->t.initParams.inStrms;
          osPrintf("\nCF : AssocInd With Init Parameters \n");
        }
     }
   }
/* sb060.102: TOS changes */
#ifdef SCT3
  ItLiSctAssocRsp(&endp[endpIdx].pst, assocReq[assocIdx].spId,
                  assocReq[assocIdx].spEndId, assocParams, SB_ACC_SCT_TOS,
                  SCT_OK,(Buffer*)NULLP);
#else   
  ItLiSctAssocRsp(&endp[endpIdx].pst, assocReq[assocIdx].spId,
              assocReq[assocIdx].spEndId, assocParams, SCT_OK, (Buffer*)NULLP);
#endif /* SCT3 */

#endif /* SB_ACC || SB_INOP */

   RETVALUE(ROK);
} /* end of ItLiSctAssocInd() */

/*
 *
 *       Fun:    ItLiSctAssocCfm - Association Establish confirm
 *
 *       Desc:   prints the association establishment confirmation
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef SCT2
#ifdef ANSI
PUBLIC S16 ItLiSctAssocCfm
(
Pst           *pst,
SuId          suId,
UConnId       suAssocId,
UConnId       spAssocId,
SctNetAddrLst *dstNAddrLst,
SctStrmId     inStrms,
SctPort       dstPort,
SctStrmId     outStrms,
Buffer        *vsInfo           /* VsInfo - not used any more */
)
#else
PUBLIC S16 ItLiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst,inStrms, dstPort, 
                           outStrms, vsInfo)
Pst           *pst;
SuId          suId;
UConnId       suAssocId;
UConnId       spAssocId;
SctNetAddrLst *dstNAddrLst;
SctStrmId     inStrms;
SctPort       dstPort;
SctStrmId     outStrms;
Buffer        *vsInfo;          /* VsInfo - not used any more */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 ItLiSctAssocCfm
(
Pst           *pst,
SuId          suId,
UConnId       suAssocId,
UConnId       spAssocId,
SctNetAddrLst *dstNAddrLst,
SctPort       dstPort,
SctStrmId     outStrms,
Buffer        *vsInfo           /* VsInfo - not used any more */
)
#else
PUBLIC S16 ItLiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, dstPort, 
           outStrms, vsInfo)
Pst           *pst;
SuId          suId;
UConnId       suAssocId;
UConnId       spAssocId;
SctNetAddrLst *dstNAddrLst;
SctPort       dstPort;
SctStrmId     outStrms;
Buffer        *vsInfo;          /* VsInfo - not used any more */
#endif /* ANSI */
#endif /* SCT2 */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#else /*  SB_INOP */
   U16 i;
#endif /* SB_ACC || SB_INOP */

   TRC3(ItLiSctAssocCfm)
   UNUSED(pst);
   UNUSED(vsInfo);

   SPrint("SctAssocCfm: ");
   sprintf(prntBuf, "  suAssocId = %u spAssocId = %u \n",   (unsigned int)suAssocId, (unsigned int)spAssocId);
   SPrint(prntBuf);

#ifdef SB_ACC

   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_ASSOC_CFM; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.suAssocId = suAssocId;
   QElm.t.sbMsg.it.spAssocId = spAssocId;
   QElm.t.sbMsg.it.peerPort = dstPort;
   QElm.t.sbMsg.it.outStrms = outStrms;
   (Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.it.peerNAddrLst),
                   (U8 *) (dstNAddrLst),
                   (PTR)sizeof(SctNetAddrLst) );
    /* Vendor specific info ignored */
   (Void) sbAccPushMsg(&QElm);

#else /* SB_INOP */

   for (i=0;i<MAXBLOCKS;i++)
   {
     if((assocReq[i].occupied) && (suAssocId == assocReq[i].suAssocId))
     {
       osPrintf("\nCF :AssocCfm Received  For Block %d\n",i);
       assocReq[i].spAssocId = spAssocId;
       assocReq[i].assocDone = TRUE;
       assocReq[i].node  = ASSOC_CLIENT;
       assocReq[i].outStrms = outStrms;
       cmMemcpy((U8 *)&assocReq[i].dstNAddrLst,
               (U8 *)dstNAddrLst, sizeof(SctNetAddrLst));
       break;
     }
   }

#endif /* SB_ACC || SB_INOP */

   RETVALUE(ROK);
} /* end of ItLiSctAssocCfm() */

/*
 *
 *       Fun:    ItLiSctTermInd - Association Termination indication
 *
 *       Desc:   print the Termation indication cause/status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctTermInd
(
Pst                  *pst,
SuId                 suId,
UConnId              assocId,
U8                   assocIdType,
SctStatus            status,
SctCause             cause,
SctRtrvInfo          *rtrvInfo
)
#else
PUBLIC S16 ItLiSctTermInd(pst, suId, assocId, assocIdType, status, cause, rtrvInfo)
Pst                  *pst;
SuId                 suId;
UConnId              assocId;
U8                   assocIdType;
SctStatus            status;
SctCause             cause;
SctRtrvInfo          *rtrvInfo;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#else /*  SB_INOP */
   U16 i;
#endif /* SB_ACC || SB_INOP */

   TRC3(ItLiSctTermInd)
   UNUSED(pst);

   sprintf(prntBuf, " SctTermInd:  suId = %u assocId = %u assocIdType = %s \n",
        (unsigned int)suId, (unsigned int) assocId,
        itSbTag2Str(assocIdTypeTable, assocIdType) );
   SPrint(prntBuf);
   itsbPrintCfm(status, cause, ACC_RESULT_NOTUSED, ACC_REASON_NOTUSED);

#ifdef SB_ACC

   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_TERM_IND; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.assocId = assocId;
   QElm.t.sbMsg.it.assocIdType = assocIdType;
   QElm.t.sbMsg.it.status = status;
   QElm.t.sbMsg.it.cause = cause;
   (Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.it.rtrvInfo),
                   (U8 *) (rtrvInfo),
                   (PTR) sizeof(SctRtrvInfo) );
   (Void) sbAccPushMsg(&QElm);

#else  /*  SB_INOP */

   for(i=0;i<MAXBLOCKS;i++)
   {
     if( assocIdType == SCT_ASSOCID_SP)
     {
       if((assocReq[i].occupied) && (assocId == assocReq[i].spAssocId))
       {
         osPrintf("\nCF : Termintaion Indcation Received Block %d  with cause %d \n",i, cause);
         assocReq[i].assocDone = FALSE;
         assocReq[i].occupied = FALSE;
         break;
       }
     }
     else
     {
       if((assocReq[i].occupied) && (assocId == assocReq[i].suAssocId))
       {
          osPrintf("\nCF : Termintaion Indcation Received Block %d  with cause %d \n",i, cause);
          assocReq[i].assocDone = FALSE;
          assocReq[i].occupied = FALSE;
          break;
       }
     }
   }

#endif /* SB_ACC || SB_INOP */

   RETVALUE(ROK);
} /* end of ItLiSctTermInd() */

/*
 *
 *       Fun:    ItLiSctTermCfm - Association Termination confirmation
 *
 *       Desc:   print the Termation confirmation cause/status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctTermCfm
(
Pst                  *pst,
SuId                 suId,
UConnId              suAssocId,
SctResult            result,
SctCause             cause
)
#else
PUBLIC S16 ItLiSctTermCfm(pst, suId, suAssocId, result, cause )
Pst                  *pst;
SuId                 suId;
UConnId              suAssocId;
SctResult            result;
SctCause             cause;
#endif /* ANSI */
{

#ifdef SB_ACC
   SbAccMsgQElm QElm;
#else  /* SB_INOP */
   U16 i;
#endif /* SB_ACC || SB_INOP */

   TRC3(ItLiSctTermCfm)
   UNUSED(pst);

   SPrint("SctTermCfm: ");
   itsbPrintCfm(ACC_STATUS_NOTUSED, cause, result, ACC_REASON_NOTUSED);

#ifdef SB_ACC

   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_TERM_CFM; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.suAssocId = suAssocId;
   QElm.t.sbMsg.it.result = result;
   QElm.t.sbMsg.it.cause = cause;
   (Void) sbAccPushMsg(&QElm);

#else  /*  SB_INOP */

   for(i=0;i<MAXBLOCKS;i++)
   {
     if((assocReq[i].occupied) && (suAssocId == assocReq[i].suAssocId))
     {
       assocReq[i].assocDone = FALSE;
       osPrintf("\nCF :AssocTermination Received Block %d  cause %d \n",i,cause);
       assocReq[i].spAssocId = -1;
       assocReq[i].suAssocId = -1;
       assocReq[i].occupied = FALSE;
       break;
     }
   }

#endif /* SB_ACC || SB_INOP */

   RETVALUE(ROK);
} /* end of ItLiSctTermCfm() */

/*
 *
 *       Fun:    ItLiSctSetPriCfm - Set Primary Address confirmation
 *
 *       Desc:   print the Set Primary Address result/cause
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctSetPriCfm
(
Pst                  *pst,
SuId                 suId,
UConnId              suAssocId,
SctResult            result,
SctCause             cause
)
#else
PUBLIC S16 ItLiSctSetPriCfm(pst, suId, suAssocId, result, cause )
Pst                  *pst;
SuId                 suId;
UConnId              suAssocId;
SctResult            result;
SctCause             cause;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(ItLiSctSetPriCfm)
   UNUSED(pst);

#ifdef SB_ACC

   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_SETPRI_CFM; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.suAssocId = suAssocId;
   QElm.t.sbMsg.it.result = result;
   QElm.t.sbMsg.it.cause = cause;
   (Void) sbAccPushMsg(&QElm);

#endif /* SB_ACC */

   SPrint("SctSetPriCfm: ");
   itsbPrintCfm(ACC_STATUS_NOTUSED, cause, result, ACC_REASON_NOTUSED);

   RETVALUE(ROK);
} /* end of ItLiSctSetPriCfm() */

/*
 *
 *       Fun:    ItLiSctHBeatCfm - Heartbeat enable/disable confirmation
 *
 *       Desc:   print the Termation confirmation cause/status/result
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctHBeatCfm
(
Pst                  *pst,
SuId                 suId,
UConnId              suAssocId,
CmNetAddr            *dstNAddr,
SctStatus            status,
SctResult            result,
SctCause             cause
)
#else
PUBLIC S16 ItLiSctHBeatCfm(pst, suId, suAssocId, dstNAddr, status, result, cause )
Pst                  *pst;
SuId                 suId;
UConnId              suAssocId;
CmNetAddr            *dstNAddr;
SctStatus            status;
SctResult            result;
SctCause             cause;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(ItLiSctHBeatCfm)
   UNUSED(pst);

#ifdef SB_ACC

   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_HBEAT_CFM; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.suAssocId = suAssocId;
   QElm.t.sbMsg.it.status = status;
   QElm.t.sbMsg.it.result = result;
   QElm.t.sbMsg.it.cause = cause;
   (Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.it.peerNAddr),
                   (U8 *) (dstNAddr),
                   (PTR)sizeof(CmNetAddr) );
   (Void) sbAccPushMsg(&QElm);

#endif /* SB_ACC */

   sprintf(prntBuf, "\nSctHBeatCfm: HeartBeat Cfm Received with cause %d \n",cause);
   SPrint(prntBuf);
   itsbPrintCfm(ACC_STATUS_NOTUSED, cause, result, ACC_REASON_NOTUSED);
   sprintf(prntBuf, "Hbeat status: %s  \n",
           itSbTag2Str(hBeatStaTable, status) );
   SPrint(prntBuf);

   RETVALUE(ROK);
} /* end of ItLiSctHBeatCfm() */

/*
 *
 *       Fun:    ItLiSctDatInd - Data indication
 *
 *       Desc:   print the data buffer
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctDatInd
(
Pst                  *pst,
SuId                 suId,
UConnId              suAssocId,
SctStrmId            strmId,
SctDatIndType        *indType,
U32                  protId,
Buffer               *mBuf
)
#else
PUBLIC S16 ItLiSctDatInd(pst, suId, suAssocId, strmId, indType, protId, mBuf )
Pst                  *pst;
SuId                 suId;
UConnId              suAssocId;
SctStrmId            strmId;
SctDatIndType        *indType;
U32                  protId;
Buffer               *mBuf;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#else  /*  SB_INOP */
   MsgLen mLen;
   U8  *strng;
   U8 type;
   OsFile *cfin;
   U32  len;
   Data header;
   U8   idx;
   S16  ret;
   PRIVATE U32 Cnt=0;
#endif /* SB_ACC || SB_INOP */

   TRC3(ItLiSctDatInd)
   UNUSED(pst);

#ifdef SB_ACC

   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_DAT_IND; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.suAssocId = suAssocId;
   QElm.t.sbMsg.it.strmId = strmId;
   (Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.it.indType),
                   (U8 *) (indType),
                   (PTR)sizeof(SctDatIndType) );
   if(mBuf != (Buffer *) NULLP ) /* check if buffer have been allocated */
   {
     
      SAddMsgRef(mBuf, DFLT_REGION, DFLT_POOL, &(QElm.t.sbMsg.it.mBuf));
      /* RFC 4460 -- MLK fix */
      SB_RLSMEM(mBuf);
   }
   else
   {
      SPrint("Received buffer zero \n");
   }
   (Void) sbAccPushMsg(&QElm);
   sprintf(prntBuf, " SctDatInd: suId = %d suAssocId = %d \n",  (unsigned int)suId, (unsigned int)suAssocId);
   SPrint(prntBuf);
   sprintf(prntBuf, "data type: %s tsn: %u sequence num: %u last: %s \n",
           itSbTag2Str(datatypeTable, indType->type), (unsigned int)indType->tsn, indType->seqNum,
           itSbTag2Str(boolTable, indType->last));
   SPrint(prntBuf);

#else

   if(strmId == 9)
   {
      SRemPreMsg(&header, mBuf);
      SFndLenMsg(mBuf,&mLen);

      ret = SGetSBuf(DFLT_REGION, DFLT_POOL,(Data**)&strng, mLen); 
      if ( ret == ROK )
      {  
       cmMemset((U8*)strng, 0, mLen);  
      }
      (Void)SRemPreMsgMult(strng,(MsgLen)mLen,mBuf);
      if(header == FILE_START)
      {
         cmMemset((U8 *)filename, 0, 50);
         cmMemcpy((U8*)filename, strng, cmStrlen(strng)+1);
         printf("filename is %s\n",filename);
      }
      else
      {
        if ((cfin = (OsFile*)osFopen(filename, "a")) == (S32)NULLP)
        {
          osPrintf("%s:  Can't open file for write ,File=:%s\n", "SCTP", filename);
          SPutMsg(mBuf);
          (Void) SPutSBuf(DFLT_REGION, DFLT_POOL,(Data*)strng, mLen); 
          RETVALUE(RFAILED);
        }
#ifdef SS_LINUX
        if ((len = osFwrite(strng, 1, mLen, cfin)) != mLen)
#else
        if ((len = osFwrite(strng, mLen, 1,  cfin)) != mLen)
#endif /* SS_LINUX */
        {
          osPrintf("%s:  File write error ,File=:%s\n", "SCTP", filename);
          SPutMsg(mBuf);
          (Void) SPutSBuf(DFLT_REGION, DFLT_POOL,(Data*)strng, mLen); 
          RETVALUE(RFAILED);
        }
        osFclose(cfin);
      }
      SPutMsg(mBuf);

      (Void) SPutSBuf(DFLT_REGION, DFLT_POOL,(Data*)strng, mLen); 
      RETVALUE(ROK);
   }
  
   (Void)SRemPreMsg(&type,mBuf);

   if(type == PKTCNT_DATA)
   {

     SFndLenMsg(mBuf,&mLen);

#ifdef SB_PRFM_RCVR 

  if( (Cnt == 0 ) || ((Cnt >= 9999) && (Cnt <= 10001) )) 
  {
     struct timeval tp;
     cmMemset((U8 *)&tp, 0, sizeof(struct timeval));
     gettimeofday(&tp, NULL);
     printf(" IT_DAT_TIME : %ld.%06ld\n",tp.tv_sec,tp.tv_usec);
     printf("Tsn is %lu - Seq %lu",indType->tsn, indType->seqNum);
  }
  Cnt++;
  if(Cnt == 10000 )
    Cnt=0;

#endif
        if(pktCount++ == 1000)
        { 
          pktCount = 0;
          osPrintf("%d Thousand packets received of Size : %d \n", ++pktThousand,mLen);
        }
        SPutMsg(mBuf);
        RETVALUE(ROK);
   }

   if(type == PING_REQ)
   {
   /*   SAddPreMsg(PING_CFM, mBuf); */

        for(idx=0;idx<MAXBLOCKS;idx++)
        {
           if ( (assocReq[idx].occupied) && (assocReq[idx].suAssocId == suAssocId ))
             break;
        }

        SFndLenMsg(mBuf,&mLen);
        
        (Void) SAddPreMsg(PING_CFM,mBuf);
        ItLiSctDatReq(&endp[assocReq[idx].endpIdx].pst, assocReq[idx].spId,
                       assocReq[idx].spAssocId, &assocReq[idx].dstNetAddr, strmId,
                       FALSE, FALSE, 10, protId, mBuf);

       osPrintf("Received ping request, Send Ping Response %d Bytes  \n", mLen);
       RETVALUE(ROK);
   }
   if(type == PING_CFM)
   {
      osPrintf("Received PING Response %d Bytes \n", mLen);
      SPutMsg(mBuf);
      RETVALUE(ROK);
   }
   
   SFndLenMsg(mBuf,&mLen);
   ret = SGetSBuf(DFLT_REGION, DFLT_POOL,(Data**)&strng, mLen); 
   if ( ret == ROK )
   {  
     cmMemset((U8*)strng, 0, mLen);  
   }

   (Void)SRemPreMsgMult(strng,(MsgLen)mLen,mBuf);
   if (!filedata)
   {
      if (mLen < 20)
      {
         sprintf(prntBuf, "*** (StrmId - %d ) Received Data : %d  : %s\n *** ", strmId, mLen, strng);
         SPrint(prntBuf);
      }
      else
      {
         sprintf(prntBuf, "*** (StrmId - %d ) Received Data Len: %d\n *** ", strmId, mLen);
         SPrint(prntBuf);
      }
   }
   else
   {
       sprintf(prntBuf, "***FileWrite Data:(StrmId - %d)Received Data Len: %d\n ***", strmId, mLen);
       SPrint(prntBuf);

       if ((cfin = (OsFile*)osFopen("datarx.file", "a")) == (S32)NULLP)
       {
         osPrintf("%s:  Can't open file for write ,File=:%s\n", "SCTP", "datarx.file");
        (Void) SPutSBuf(DFLT_REGION, DFLT_POOL,(Data*)strng, mLen); 
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
       }
#ifdef SS_LINUX
       if ((len = osFwrite(strng, 1, mLen, cfin)) != mLen)
#else
       if ((len = osFwrite(strng, mLen, 1, cfin)) != mLen)
#endif /* SS_LINUX */
       {
         osPrintf("%s: File write error ,File=:%s \n", "SCTP", "datarx.file");
        (Void) SPutSBuf(DFLT_REGION, DFLT_POOL,(Data*)strng, mLen); 
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
       }
       if ((len = osFwrite("\n", 1, 1, cfin)) != 1)
       {
         osPrintf("%s: File write error ,File=:%s \n", "SCTP", "datarx.file");
         (Void) SPutSBuf(DFLT_REGION, DFLT_POOL,(Data*)strng, mLen); 
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
       }
       osFclose(cfin);
   }
   SPutMsg(mBuf);
   (Void) SPutSBuf(DFLT_REGION, DFLT_POOL,(Data*)strng, mLen); 

#endif /* SB_ACC || SB_INOP */

   RETVALUE(ROK);
} /* end of ItLiSctDatInd() */

 /*
 *
 *       Fun:    ItLiSctStaCfm - Status  confirmation
 *
 *       Desc:   print the status confirmation results.
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctStaCfm
(
Pst                  *pst,
SuId                 suId,
UConnId              suAssocId,
CmNetAddr            *dstNAddr,
SctResult            result,
SctCause             cause,
SctStaInfo           *staInfo
)
#else
PUBLIC S16 ItLiSctStaCfm(pst, suId, suAssocId, dstNAddr, result, cause,
                         staInfo)
Pst                  *pst;
SuId                 suId;
UConnId              suAssocId;
CmNetAddr            *dstNAddr;
SctResult            result;
SctCause             cause;
SctStaInfo           *staInfo;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#else /* SB_INOP */
   U32  netAddr;
   U16  idx;
#endif /* SB_ACC || SB_INOP */

   TRC3(ItLiSctStaCfm)
   UNUSED(pst);

   SPrint("SctStaCfm: ");
   sprintf(prntBuf, "  suId = %u suAssocId = %u  status Type: %s \n", \
           (unsigned int) suId, (unsigned int)suAssocId,
           itSbTag2Str(statusCfmTable, staInfo->staType) );
   SPrint(prntBuf);
   sprintf(prntBuf, "  cause: %s \n", \
          itSbTag2Str(causeTable, cause) );
   SPrint(prntBuf);
   sprintf(prntBuf, "Result = %d Cause = %s  Status Type = %s\n", result, \
           itSbTag2Str(causeTable, cause), itSbTag2Str(statusTable, staInfo->staType));
   SPrint(prntBuf);

   sprintf(prntBuf, "assocInfo:  rwnd = %u connSta = %s \n",
          (unsigned int) staInfo->u.assocInfo.rwnd, itSbTag2Str(assocstateTable, \
          staInfo->u.assocInfo.connSta));
   SPrint(prntBuf);
   sprintf(prntBuf, "addrInfo:  rtt = %u cwnd = %u rto = %u  active = %s \n",
           (unsigned int) staInfo->u.addrInfo.rtt, \
           (unsigned int)staInfo->u.addrInfo.cwnd,
            (unsigned int)staInfo->u.addrInfo.rto, \
           itSbTag2Str(boolTable, staInfo->u.addrInfo.active));
   SPrint(prntBuf);
   sprintf(prntBuf, "rtrvInfo: nmbUnsentDgm = \
                     %u  nmbUnackDgm = %u nmbUndelDgm = %u \n \
                     lastAckTsn = %u lastSentTsn = %u \n",
           (unsigned int)staInfo->u.rtrvInfo.nmbUnsentDgms,(unsigned int)\
           staInfo->u.rtrvInfo.nmbUnackDgms,
           (unsigned int)staInfo->u.rtrvInfo.nmbUndelDgms, (unsigned int)\
           staInfo->u.rtrvInfo.lastAckTsn,
           (unsigned int)staInfo->u.rtrvInfo.lastSentTsn);
   SPrint(prntBuf);

#ifdef SB_ACC

   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_STA_CFM; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.suAssocId = suAssocId;
   QElm.t.sbMsg.it.staType = staInfo->staType;
   QElm.t.sbMsg.it.result = result;
   QElm.t.sbMsg.it.cause = cause;
   (Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.it.peerNAddr),
                   (U8 *) (dstNAddr),
                   (PTR) sizeof(CmNetAddr));
   (Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.it.staInfo),
                   (U8 *) (staInfo),
                   (PTR) sizeof(SctStaInfo));
   (Void) sbAccPushMsg(&QElm);

#else /* SB_INOP */

   netAddr = 0;
   if (dstNAddr)
   {
      netAddr = dstNAddr->u.ipv4NetAddr;
   }
   switch (staInfo->staType)
   {
      case SCT_GET_ASSOC_INFO:
         sprintf(prntBuf, "rwnd = %ld connSta = %s Primary dstAddr = 0x%lx dstPort = %d\n",
          staInfo->u.assocInfo.rwnd,
          itSbTag2Str(assocstateTable, staInfo->u.assocInfo.connSta),
          staInfo->u.assocInfo.priDstAddr.u.ipv4NetAddr,
          staInfo->u.assocInfo.dstPort);
         SPrint(prntBuf);

         sprintf(prntBuf, "Other dstAddrs = ");
         SPrint(prntBuf);
         for (idx = 0; idx < staInfo->u.assocInfo.dstAddrLst.nmb; idx++)
         {
            sprintf(prntBuf, "0x%lx ", staInfo->u.assocInfo.dstAddrLst.nAddr[idx].u.ipv4NetAddr);
            SPrint(prntBuf);
         }
         SPrint("\n");
         break;

      case SCT_GET_ADDR_INFO:
         sprintf(prntBuf, "rtt = %d cwnd = %ld rto = %ld  active = %s\n",
                 staInfo->u.addrInfo.rtt,
                 staInfo->u.addrInfo.cwnd,
                 staInfo->u.addrInfo.rto,
                 itSbTag2Str(boolTable, staInfo->u.addrInfo.active));
         SPrint(prntBuf);
         break;

      case SCT_GET_RTRV_INFO:
         sprintf(prntBuf, "nmbUnsentDgm = %ld  nmbUnackDgm = %ld nmbUndelDgm = %ld\n",
                 staInfo->u.rtrvInfo.nmbUnsentDgms,
                 staInfo->u.rtrvInfo.nmbUnackDgms,
                 staInfo->u.rtrvInfo.nmbUndelDgms);
         SPrint(prntBuf);
         sprintf(prntBuf, "lastAckTsn = %lu lastSentTsn = %lu\n",
                 staInfo->u.rtrvInfo.lastAckTsn,
                 staInfo->u.rtrvInfo.lastSentTsn);
         SPrint(prntBuf);
         break;
   }

#endif /* SB_ACC || SB_INOP */

   RETVALUE(ROK);
} /* end of ItLiSctStaCfm() */

/*
 *
 *       Fun:    ItLiSctStaInd - Status indication
 *
 *       Desc:   print the status indication results
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *

 *
 *       File:   it_bdy1.c
 *
 */
/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
#ifdef ANSI
PUBLIC S16 ItLiSctStaInd
(
 Pst                  *pst,
 SuId                 suId,
 UConnId              suAssocId,
 UConnId              spAssocId,
 CmNetAddr            *dstNAddr,
 SctStatus            status,
 SctCause             cause,
 U32                  protId,
 Buffer               *mBuf
 )
#else
PUBLIC S16 ItLiSctStaInd(pst, suId, suAssocId, spAssocId, dstNAddr, status, cause, protId, mBuf)
Pst                  *pst;
SuId                 suId;
UConnId              suAssocId;
UConnId              spAssocId;
CmNetAddr            *dstNAddr;
SctStatus            status;
SctCause             cause;
U32                  protId;
Buffer               *mBuf;
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 ItLiSctStaInd
(
 Pst                  *pst,
 SuId                 suId,
 UConnId              suAssocId,
 UConnId              spAssocId,
 CmNetAddr            *dstNAddr,
 SctStatus            status,
 SctCause             cause,
 Buffer               *mBuf
)
#else
PUBLIC S16 ItLiSctStaInd(pst, suId, suAssocId, spAssocId, dstNAddr, status, cause, mBuf)
Pst                  *pst;
SuId                 suId;
UConnId              suAssocId;
UConnId              spAssocId;
CmNetAddr            *dstNAddr;
SctStatus            status;
SctCause             cause;
Buffer               *mBuf;
#endif /* ANSI */
#endif /* SCT7 */
{
#ifdef SB_ACC
	SbAccMsgQElm QElm;
#endif

	TRC3(ItLiSctStaInd)
		UNUSED(pst);

	SPrint("SctStaInd: ");
	itsbPrintCfm(ACC_STATUS_NOTUSED, cause, ACC_RESULT_NOTUSED, ACC_REASON_NOTUSED);
	sprintf(prntBuf, " status = %s,  suId = %d suAssocId = %d  spAssocId = %d \n",
			itSbTag2Str(statusIndTable, status),(unsigned int) suId, (unsigned int)suAssocId,
			(unsigned int) spAssocId );
	SPrint(prntBuf);

#ifdef SB_ACC

	SB_ZERO(&QElm, (S32)sizeof(QElm));
	QElm.evntType = ACC_EVT_STA_IND; /* Override pst->event */
	QElm.t.sbMsg.it.suId = suId;
	QElm.t.sbMsg.it.suAssocId = suAssocId;
	QElm.t.sbMsg.it.spAssocId = spAssocId;
	QElm.t.sbMsg.it.status = status;
	QElm.t.sbMsg.it.cause = cause;
	/* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
	QElm.t.sbMsg.it.protId = protId;
#endif
	(Void) cmMemcpy((U8 *) &(QElm.t.sbMsg.it.peerNAddr),
					(U8 *) (dstNAddr),
					(PTR) sizeof(CmNetAddr) );
	if(mBuf != (Buffer *) NULLP ) /* check if buffer have been allocated */
	{
		SAddMsgRef(mBuf, DFLT_REGION, DFLT_POOL, &(QElm.t.sbMsg.it.mBuf));
		/* RFC 4460 -- MLK fix */
		SB_RLSMEM(mBuf);
	}
	(Void) sbAccPushMsg(&QElm);

#else /*  SB_INOP */

	if(cause == SCT_CAUSE_OUTRES)
		FLCpause = TRUE;
	if (mBuf != NULLP)
		SPutMsg(mBuf);

#endif /* SB_ACC || SB_INOP */

	RETVALUE(ROK);
} /* end of ItLiSctStaInd() */

/*
 *
 *       Fun:    ItLiSctFlcInd - Flow control Indication
 *
 *       Desc:   print the flow control results
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC S16 ItLiSctFlcInd
(
Pst                  *pst,
SuId                 suId,
UConnId              suAssocId,
Reason               reason
)
#else
PUBLIC S16 ItLiSctFlcInd(pst, suId, suAssocId, reason )
Pst                  *pst;
SuId                 suId;
UConnId              suAssocId;
Reason               reason;
#endif /* ANSI */
{
#ifdef SB_ACC
   SbAccMsgQElm QElm;
#endif

   TRC3(ItLiSctFlcInd)
   UNUSED(pst);

#ifdef SB_ACC

   SB_ZERO(&QElm, (S32)sizeof(QElm));
   QElm.evntType = ACC_EVT_FLC_IND; /* Override pst->event */
   QElm.t.sbMsg.it.suId = suId;
   QElm.t.sbMsg.it.reason = reason;
   QElm.t.sbMsg.it.suAssocId = suAssocId;
   (Void) sbAccPushMsg(&QElm);

#else /*  SB_INOP */

   if ((reason == SCT_FLC_START) || (reason == SCT_FLC_ACTIVE) || (reason == SCT_FLC_DROP))
   {
      FLCpause = TRUE;
   }
   else
   {
      FLCpause = FALSE;
   }

#endif /* SB_ACC || SB_INOP */

   SPrint("SctFlcInd: ");
   itsbPrintCfm(ACC_STATUS_NOTUSED, ACC_STATUS_NOTUSED, ACC_RESULT_NOTUSED, reason);

   RETVALUE(ROK);
} /* end of ItLiSctFlcInd() */

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
*       File:  it_bdy1.c
*
*/

#ifdef ANSI
PUBLIC S16 itSbActvInit
(
Ent ent,                      /* entity */
Inst inst,                    /* instance */
Region region,                /* region */
Reason reason                 /* reason */
)
#else
PUBLIC S16 itSbActvInit(ent, inst, region, reason)
Ent ent;                      /* entity */
Inst inst;                    /* instance */
Region region;                /* region */
Reason reason;                /* reason */
#endif
{
   TRC3(itSbActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
} /* end of itSbActvInit */

/*
 *
 *       Fun:    itsbPrintCfm - print common confirm structures
 *
 *       Desc:
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *       File:   it_bdy1.c
 *
 */

#ifdef ANSI
PUBLIC Void itsbPrintCfm
(
SctStatus        status,
SctCause         cause,
SctResult        result,
Reason           reason
)
#else
PUBLIC Void itsbPrintCfm(status, cause, result, reason)
SctStatus        status;
SctCause         cause;
SctResult        result;
Reason           reason;
#endif /* ANSI */
{
   TRC2(itsbPrintCfm)
     if (status != 255)
      {
         sprintf(prntBuf, "Status = %s ", itSbTag2Str(statusTable, status));
         SPrint(prntBuf);
      }

      if (cause != 255)
      {
         sprintf(prntBuf, "Cause = %s\n", itSbTag2Str(causeTable, cause));
         SPrint(prntBuf);
      }

      if (result != 255)
      {
         sprintf(prntBuf, "Result = %s ", itSbTag2Str(resultTable, result));
         SPrint(prntBuf);
      }

      if (reason != 255)
      {
         sprintf(prntBuf, "Reason = %s\n", itSbTag2Str(reasonTable, reason));
         SPrint(prntBuf);
      }


   RETVOID;
} /* end of itsbPrintCfm() */


/********************************************************************30**

         End of file:     it_bdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:09 2015

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
1.1          ---      nhn  1. Initial version
/main/3      ---      sb   1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000.
            sb042.102 hl   1. Added change for SHT interface
            sb060.102 pr   1. TOS changes.
/main/4      ---      rsr/ag   1. Updated for Release of 1.3
	    sb008.103 nuX      1. Added new values for the  status field.
/main/4 sb024.103 ajainx   1. Included protId parameter in status indication.  
/main/4 sb030.103 krkX   1. Fixed the warnings during 64-BIT compilation.
*********************************************************************91*/


