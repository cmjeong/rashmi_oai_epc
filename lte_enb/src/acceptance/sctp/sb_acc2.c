/********************************************************************20**

     Name:     sb_acc2.c - Acceptance Tests Support Functions for the SCTP layer

     Type:     C source file

     Desc:     C code for configuration and checks required by the
               SCTP layer acceptance tests

     File:     sb_acc2.c

     Sid:      sb_acc2.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:06 2015

     Prg:      nct

*********************************************************************21*/

/*

  sb_acc2.c - Acceptance Tests Support Functions for the SCTP layer

Following functions are provided in this file:
         tst                  - main test function

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
#include "cm_dns.h"        /* common DNS defines */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sb_mtu.h"        /* mtu defines */
#include "sb_port.h"       /* sb_port defines */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */
#include "sb_acc.h"        /* defines for SCTP layer */



/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* common DNS */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sb_mtu.h"        /* mtu defines */
#include "sb_mtu.x"        /* mtu typedefs */
#include "sb_port.x"       /* sb_port typedefs */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#include "sb.x"            /* sctp layer typedefs */
#include "sb_acc.x"        /* defines for SCTP layer */

/* local defines */
#define STDP_BASE_ADDR       0x04700000  /* DPRAM base address */
#define SBAC_SYSCLK           80000000  /* CPM clock frequency */

/* local typedefs */
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
typedef struct sbStrTag
{
   S16      tag;
   Txt      *txt;
} SbStrTag;


/* forward references */

/* public variable declarations */

/* Public variables */
PUBLIC U32 peerNAddrLst_1[] =
{/* Address starting with 192.168.4.1 and incrementing */
      ACC_ASSOC1_DEST_1,
      ACC_ASSOC1_DEST_2,
      ACC_ASSOC1_DEST_3,
      ACC_ASSOC1_DEST_4,
      ACC_ASSOC1_DEST_5
};  /* end peerNAddrLst_1 */

PUBLIC CmIpv4NetAddr peerNAddrLst_2[] =
{ /* Address starting with 192.169.4.1 and incrementing */
      ACC_ASSOC2_DEST_1,
      ACC_ASSOC2_DEST_2,
      ACC_ASSOC2_DEST_3,
      ACC_ASSOC2_DEST_4,
      ACC_ASSOC2_DEST_5
};  /* end peerNAddrLst_2 */

/* sb012.103: Non-Unicast Address list */
PUBLIC CmIpv4NetAddr peerNAddrLst_3[] =
{ /* Non-Unicast Address 224.0.0.1 & 239.0.0.1 */
      ACC_ASSOC3_DEST_1,
      ACC_ASSOC3_DEST_2
};  /* end localAddrLst_3 */

PUBLIC CmIpv4NetAddr localNAddrLst_1[] =
{ /* Address starting with 192.167.4.1 and incrementing */
      ACC_ASSOC1_LOCAL_1,
      ACC_ASSOC1_LOCAL_2
};  /* end localAddrLst_1 */

PUBLIC CmIpv4NetAddr localNAddrLst_2[] =
{ /* Address starting with 192.166.4.1 and incrementing */
      ACC_ASSOC2_LOCAL_1,
      ACC_ASSOC2_LOCAL_2
};  /* end localAddrLst_2 */


PRIVATE SbStrTag chunkTable[] =
{
   STRTAG(SB_ID_DATA),
   STRTAG(SB_ID_INIT),
   STRTAG(SB_ID_INITACK),
   STRTAG(SB_ID_SACK),
   STRTAG(SB_ID_HBEAT),
   STRTAG(SB_ID_HBEATACK),
   STRTAG(SB_ID_ABORT),
   STRTAG(SB_ID_SDOWN),
   STRTAG(SB_ID_SDOWNACK),
   STRTAG(SB_ID_COOKIE),
   STRTAG(SB_ID_ERROR),
   STRTAG(SB_ID_COOKIEACK),
/* sb003.103: SATELLITE SCTP feature */ 
   STRTAG(SB_ID_ECNE),
   STRTAG(SB_ID_CWR),
   STRTAG(NOT_FOUND)
};

/* private function declarations */
PRIVATE Txt *sbTag2Str  ARGS((SbStrTag *tagArray, S16 tag));

/* SB_VER13 - Added */
PUBLIC CmInetIpAddr  loopBkAddr = (CmInetIpAddr)0x7F000001;

/* private variable definitions */
PRIVATE Txt prntBuf[PRNTSZE];

/* private routines */

/*
 *
 *       Fun:    sbTag2Str
 *
 *       Desc:   Converts the tag to its string representation
 *
 *       Ret:    pointer to string representation
 *
 *       Notes:  None
 *
 *       File:   sb_acc2.c
 *
 */

#ifdef ANSI
PRIVATE Txt *sbTag2Str
(
SbStrTag           *tagArray,
S16                  tag
)
#else
PRIVATE Txt *sbTag2Str(tagArray, tag)
SbStrTag           *tagArray;
S16                  tag;
#endif /* ANSI */
{
   U16 i;

   TRC3(sbTag2Str)
   for (i = 0; tagArray[i].tag != NOT_FOUND; i++)
   {
      if (tagArray[i].tag == tag)
      {
         break;
      }
   }

   RETVALUE(tagArray[i].txt);
} /* end of sbTag2Str */

  /* sb058.102 : Added to remove compilation warning */
#ifdef SB_CHECKSUM_CRC

/*
 *
 *       Fun:    sbCheckCRCChecksum
 *
 *       Desc:   Checks the CRC Checksum 
 *
 *       Ret:    The Checksum 
 *
 *       Notes:  None
 *
 *       File:   sb_acc2.c
 *
 */

#ifdef ANSI
PRIVATE U32 sbCheckCRCChecksum
(
Buffer              *mBuf1,
U16                 len
)
#else
PRIVATE U32 sbCheckCRCChecksum(mBuf1, len)
Buffer               *mBuf1;
U16                  len;
#endif /* ANSI */
{
   Data *msgbuf1;
   S16 ret;
   /* sb028.103: Purify fix */
   U32 ret1; 
   MsgLen cnt;
   U32    checksum;

   /* sb058.102 : Added to remove compilation warning */
   checksum = 0;
   SB_GETSBUF(len, msgbuf1, ret);
   SCpyMsgFix(mBuf1, 0, len, (Data*)msgbuf1, &cnt);
   for(cnt=8; cnt<12; cnt++)
   {
      msgbuf1[cnt]=(U8)0x00;
   }
   ret1 = sbChecksum32(checksum, (Data*)msgbuf1, len, SB_CRC32);
   /* sb028.103: Purify fix */
   SB_FREE(sizeof(msgbuf1), msgbuf1);
   RETVALUE(ret1);
} /* end of sbChekcCRCChecksum */

#endif /* SB_CHECKSUM_CRC */
/* public routines */

/*
*
*       Fun:   setBit
*
*       Desc:  Set a bit
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC void setBit
(
U8 *bitVar,
U8 bitMask
)
#else
PUBLIC void setBit(bitVar, bitMask)
U8 *bitVar;
U8 bitMask;
#endif
{
   *bitVar |= bitMask;
} /* end setBit */


/*
*
*       Fun:   isBitSet
*
*       Desc:  Check if a bit is set
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC U8 isBitSet
(
U8 bitVar,
U8 bitMask
)
#else
PUBLIC U8 isBitSet(bitVar, bitMask)
U8 bitVar;
U8 bitMask;
#endif
{
   return (U8)((bitVar & bitMask) == bitMask);
} /* end isBitSet */


/*
*
*       Fun:    sbGetPacket - get a packet using specified method
*
*       Desc:
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16 sbGetPacket
(
Buffer               **mBuf,
U16                  action,
MsgLen               mLen
)
#else
PUBLIC S16 sbGetPacket(mBuf, action, mLen)
Buffer               **mBuf;
U16                  action;
MsgLen               mLen;
#endif /* ANSI */
{
   Random            rnd;
   MsgLen            size;

   TRC1(sbGetPacket)

   size = mLen;

   switch (action)
   {
      case SBUT_TXPKTRANDSIZE:      /* get new packet of random size */
         SRandom(&rnd);
         size = (S16)((rnd % MAX_PKT_SIZE) + 1);
         /* fall through to next case */
      case SBUT_TXPKTFIXEDSIZE:     /* get new packet of fixed size */
         if (size < 1)
         {
            RETVALUE(RFAILED);
         }
         if (SGetMsg(DFLT_REGION, DFLT_POOL, mBuf) != ROK)
         {
            RETVALUE(RFAILED);
         }

         /* Add bytes at the end of message */
         if (SGetPstMsgMult(size, *mBuf) != ROK)
         {
            RETVALUE(RFAILED);
         }

         /* Place a value at position 0 in buffer */
         SRepMsg((Data)0x55, *mBuf, 0);

         break;
      default:
         RETVALUE(RFAILED);
   }

   /* Add header informative to beginning of packet */
   /*
   Ticks sysTime;
   SGetSysTime(&sysTime);
   cmPkMsgLen(size, *mBuf);
   cmPkTicks(sysTime, *mBuf);
   */

   RETVALUE(ROK);
} /* end of sbGetPacket() */

/*
*
*       Fun:   sbSctChkCfm
*
*       Desc:  Remove all the SCT messages off the queue and verify
*              the parameter values.
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbSctChkCfm
(
SbOperQElm  *sbMsg,
SbMgmtQElm  *mgmtMsg,
U8          evnt,
SctStatus   *status,
Reason      *reason
)
#else
PUBLIC  S16 sbSctChkCfm(sbMsg, mgmtMsg, evnt, status, reason)
SbOperQElm  *sbMsg;
SbMgmtQElm  *mgmtMsg;
U8          evnt;
SctStatus   *status;
Reason      *reason;
#endif
{
   SbAccMsgQElm    *msg;
   Data            data, dataRec;
   U16             i;
   MsgLen          len, lenRec;

   TRC2(sbSctChkCfm);
   UNUSED(reason);
   UNUSED(mgmtMsg);

   if (sbAccPopMsg(&msg) != ROK)
   {
      *status = PRIMITIVE_NOT_RECV;
      RETVALUE(RFAILED);
   }

   if (msg->evntType == evnt)
   {
      *status = PRIMITIVE_SUCCEED;

      if(evnt == ACC_EVT_STA_CFM)
      {
         /* verify staType */
         if(msg->t.sbMsg.it.staType != sbMsg->it.staType)
         {
            *status = INC_STATUS;
            RETVALUE(RFAILED);
         }
         if(msg->t.sbMsg.it.result != sbMsg->it.result)
         {
            *status = INC_RESULT;
            RETVALUE(RFAILED);
         }

         if(msg->t.sbMsg.it.cause != sbMsg->it.cause)
         {
            *status = INC_CAUSE;
            RETVALUE(RFAILED);
         }

         (Void) cmMemcpy((U8 *) &(sbMsg->it.staInfo),\
                        (U8 *) &(msg->t.sbMsg.it.staInfo),\
                        (PTR)sizeof(SctStaInfo) );
      }

      if(evnt == ACC_EVT_DAT_IND)
      {
         /* verify indType */
         if(msg->t.sbMsg.it.indType.type != sbMsg->it.indType.type )
         {
            *status = INC_INDTYPE;
            RETVALUE(RFAILED);
         }
      }

      if(evnt == ACC_EVT_TERM_IND)
      {
         /* verify assocIdType */
         if(msg->t.sbMsg.it.assocIdType == SCT_ASSOCID_SP)
         {
            /* verify suAssocId */
            if(msg->t.sbMsg.it.assocId != sbMsg->it.spAssocId)
            {
               *status = INC_ASSOC_ID;
               RETVALUE(RFAILED);
            }
         }
         else if (msg->t.sbMsg.it.assocIdType == SCT_ASSOCID_SU)
         {
            /* verify suAssocId */
            if(msg->t.sbMsg.it.assocId != sbMsg->it.suAssocId)
            {
               *status = INC_ASSOC_ID;
               RETVALUE(RFAILED);
            }
         }
      }

      if( (evnt == ACC_EVT_DAT_IND) || (evnt == ACC_EVT_STA_IND ) )
      {
         /* verify mBuf */
         if((sbAccCb.curTst.gmBuf != (Buffer *)NULLP) && \
            (msg->t.sbMsg.it.mBuf != (Buffer *)NULLP) )
         {
            SB_SCTMSGCMP(msg->t.sbMsg.it.mBuf, sbAccCb.curTst.gmBuf)
            SB_RLSMEM(sbAccCb.curTst.gmBuf)
         }
      }

      if( (evnt == ACC_EVT_HBEAT_CFM) ||(evnt == ACC_EVT_TERM_IND) ||\
          (evnt == ACC_EVT_STA_IND))
      {
         /* verify status */
         if(msg->t.sbMsg.it.status != sbMsg->it.status)
         {
            *status = INC_STATUS;
            RETVALUE(RFAILED);
         }
      }

      if( (evnt == ACC_EVT_ENDPOPEN_CFM) || (evnt == ACC_EVT_ENDPCLOSE_CFM) )
      {
         /* verify suEndpId */
         if(msg->t.sbMsg.it.suEndpId != sbMsg->it.suEndpId)
         {
            *status = INC_ENDP_ID;
            RETVALUE(RFAILED);
         }

         /* verify result.1 */
         if(msg->t.sbMsg.it.result != sbMsg->it.result)
         {
            *status = INC_RESULT;
            RETVALUE(RFAILED);
         }

         /* verify cause.1 */
         if(msg->t.sbMsg.it.cause != sbMsg->it.cause)
         {
            *status = INC_CAUSE;
            RETVALUE(RFAILED);
         }

      }

	  if( (evnt == ACC_EVT_TERM_IND) || (evnt == ACC_EVT_STA_IND) )
	  {
		  /* verify cause.2 */
		  if(msg->t.sbMsg.it.cause != sbMsg->it.cause)
		  {
			  *status = INC_CAUSE;
			  RETVALUE(RFAILED);
		  }
		  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7 
		  if((msg->t.sbMsg.it.status == SCT_STATUS_SND_FAIL) &&
				  (msg->t.sbMsg.it.protId != sbMsg->it.protId))
		  {
			  *status = INV_PROT;
			  RETVALUE(RFAILED);
		  }
#endif /* SCT7 */
	  }

      if( (evnt == ACC_EVT_BND_CFM) )
      {
         /* verify result.3 */
         if(msg->t.sbMsg.it.result != sbMsg->it.result)
         {
            *status = INC_RESULT;
            RETVALUE(RFAILED);
         }
      }

      if( (evnt == ACC_EVT_TERM_CFM) || (evnt == ACC_EVT_HBEAT_CFM)\
          ||(evnt == ACC_EVT_SETPRI_CFM) )
      {
         /* verify result.2 */
         if(msg->t.sbMsg.it.result != sbMsg->it.result)
         {
            *status = INC_RESULT;
            RETVALUE(RFAILED);
         }

         /* verify cause.3 */
         if (msg->t.sbMsg.it.cause != sbMsg->it.cause)
         {
            *status = INC_CAUSE;
            RETVALUE(RFAILED);
         }
      }

      if( (evnt == ACC_EVT_ENDPOPEN_CFM) )
      {/* Save the received spEndpId */
         if ( (msg->t.sbMsg.it.suEndpId == sbMsg->it.suEndpId) )
         {
            sbMsg->it.spEndpId = msg->t.sbMsg.it.spEndpId;
         }
      }

      if( (evnt == ACC_EVT_ASSOC_CFM) )
      {
         if ( (msg->t.sbMsg.it.suAssocId == sbMsg->it.suAssocId) )
         {  /* Save the received spAssocId */
            sbMsg->it.spAssocId = msg->t.sbMsg.it.spAssocId;
         }
      }

      if ( (evnt == ACC_EVT_ASSOC_IND) )
      {
         if ( msg->t.sbMsg.it.assocParams.type != sbMsg->it.assocParams.type )
         {
            *status = INC_INDTYPE;
            RETVALUE(RFAILED);
         }
         if ( msg->t.sbMsg.it.assocParams.type == SCT_ASSOC_IND_INIT )
         {
            U16      tmpU16;
            if ( msg->t.sbMsg.it.assocParams.t.initParams.iTag !=\
                 sbMsg->it.assocParams.t.initParams.iTag )
            {
               *status = INV_VERTAG;
               RETVALUE(RFAILED);
            }
            if ( msg->t.sbMsg.it.assocParams.t.initParams.a_rwnd != \
                 sbMsg->it.assocParams.t.initParams.a_rwnd )
            {
               *status = INC_RWND;
               RETVALUE(RFAILED);
            }
            if ( msg->t.sbMsg.it.assocParams.t.initParams.outStrms != \
                 sbMsg->it.assocParams.t.initParams.outStrms )
            {
               *status = INC_STRM;
               RETVALUE(RFAILED);
            }
            if ( msg->t.sbMsg.it.assocParams.t.initParams.inStrms != \
                 sbMsg->it.assocParams.t.initParams.inStrms )
            {
               *status = INC_STRM;
               RETVALUE(RFAILED);
            }
            if ( msg->t.sbMsg.it.assocParams.t.initParams.iTsn != \
                 sbMsg->it.assocParams.t.initParams.iTsn )
            {
               *status = INC_TSN;
               RETVALUE(RFAILED);
            }
            if ( msg->t.sbMsg.it.assocParams.t.initParams.peerPort != \
                 sbMsg->it.assocParams.t.initParams.peerPort )
            {
               *status = INC_PORT;
               RETVALUE(RFAILED);
            }
            if ( msg->t.sbMsg.it.assocParams.t.initParams.localPort !=\
                 sbMsg->it.assocParams.t.initParams.localPort )
            {
               *status = INC_PORT;
               RETVALUE(RFAILED);
            }

            (Void) cmMemcpy((U8 *) &(sbMsg->it.assocParams),\
                            (U8 *) &(msg->t.sbMsg.it.assocParams),\
                            (PTR)sizeof(SctAssocIndParams) );
            /* swap the streams */
            tmpU16 = sbMsg->it.assocParams.t.initParams.outStrms;
            sbMsg->it.assocParams.t.initParams.outStrms =\
               sbMsg->it.assocParams.t.initParams.inStrms;
            sbMsg->it.assocParams.t.initParams.inStrms = tmpU16;
         }
         else   /* SCT_ASSOC_IND_COOKIE */
         {
            if ( (msg->t.sbMsg.it.assocParams.t.cookieParams.peerPort !=\
                  sbMsg->it.assocParams.t.cookieParams.peerPort) )
            {
               *status = INC_PORT;
               RETVALUE(RFAILED);
            }
            (Void) cmMemcpy((U8 *) &(sbMsg->it.assocParams),\
                            (U8 *) &(msg->t.sbMsg.it.assocParams),\
                            (PTR)sizeof(SctAssocIndParams) );
         }
      }

      if( (evnt == ACC_EVT_DAT_IND) || (evnt == ACC_EVT_STA_IND) ||\
          (evnt == ACC_EVT_STA_CFM) )
      {
         /* verify suAssocId.1 */
         if(msg->t.sbMsg.it.suAssocId != sbMsg->it.suAssocId)
         {
            *status = INC_ASSOC_ID;
            RETVALUE(RFAILED);
         }
      }

        if ( (evnt == ACC_EVT_HBEAT_CFM) || (evnt == ACC_EVT_SETPRI_CFM) ||\
             (evnt == ACC_EVT_TERM_CFM) )
      {
         /* verify suAssocId.2 */
         if(msg->t.sbMsg.it.suAssocId != sbMsg->it.suAssocId)
         {
            *status = INC_ASSOC_ID;
            RETVALUE(RFAILED);
         }
      }

      if ( (evnt == ACC_EVT_HBEAT_CFM) )
      {
          if( msg->t.sbMsg.it.peerNAddr.u.ipv4NetAddr !=\
              sbMsg->it.peerNAddr.u.ipv4NetAddr )
          {
            *status = INC_ADDR;
            RETVALUE(RFAILED);
          }
      }

      /* verify suId for all confirms*/
      if(msg->t.sbMsg.it.suId != sbMsg->it.suId)
      {
         *status = INC_SUID;
         RETVALUE(RFAILED);
      }

      /*correct event type */
   }
   else
   {
      /* end if(msg->evntType == evnt) */
      *status =  INC_EVNTTYPE;
      RETVALUE(RFAILED);
   } /* end else */

   SB_RLSMEM(msg->t.sbMsg.it.mBuf)  /*release memory */
   /*-- RFC 4460 -- MLK Fix --*/
   SB_RLSMEM(sbAccCb.curTst.gmBuf);    /* release memory */
   RETVALUE(ROK);
} /* end sbSctChkCfm */

/*
*
*       Fun:   sbHitChkReq
*
*       Desc:  Checking the requests for all the lower layer primitives
*              but UDatReq.
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbHitChkReq
(
SbOperQElm  *sbMsg,
SbMgmtQElm  *mgmtMsg,
U8          evnt,
SctStatus   *status,
Reason      *reason
)
#else
PUBLIC  S16 sbHitChkReq(sbMsg, mgmtMsg, evnt, status, reason)
SbOperQElm  *sbMsg;
SbMgmtQElm  *mgmtMsg;
U8          evnt;
SctStatus   *status;
Reason      *reason;
#endif
{
   SbAccMsgQElm *msg;

   TRC2(sbHitChkReq)
   UNUSED(reason);
   UNUSED(mgmtMsg);

   if (sbAccPopMsg(&msg) != ROK)
   {
      *status = PRIMITIVE_NOT_RECV;
      RETVALUE(RFAILED);
   }

   if( (msg->evntType == evnt)  )
   {
      *status = PRIMITIVE_SUCCEED;

      if(evnt == ACC_EVT_BND_REQ)
      {   /* verify suId */
          if(msg->t.sbMsg.hi.suId != sbMsg->hi.suId)
          {
             *status = INC_SUID;
             RETVALUE(RFAILED);
          }
      }


      if(evnt == ACC_EVT_DISC_REQ)
      {   /* verify choice */
         if(msg->t.sbMsg.hi.choice == HI_PROVIDER_CON_ID)
         {  /* save conId for DiscCfm */
            sbAccCb.curTst.suConId = msg->t.sbMsg.hi.conId;
            sbAccCb.curTst.spConId = sbAccCb.curTst.suConId;
         } else if ( msg->t.sbMsg.hi.choice == HI_USER_CON_ID) {
            sbAccCb.curTst.suConId = msg->t.sbMsg.hi.conId;
            sbAccCb.curTst.spConId = sbAccCb.curTst.suConId;
         }
      }    /*end DISC_REQ */
      /* verify spId for all requests */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      if((evnt != ACC_EVT_SERVOPEN_REQ) && (msg->t.sbMsg.hi.spId != sbMsg->hi.spId))
#else
      if(msg->t.sbMsg.hi.spId != sbMsg->hi.spId)
#endif
      {
         *status = INC_SPID;
          RETVALUE(RFAILED);
      }
      else
      {
         if (evnt == ACC_EVT_SERVOPEN_REQ)
         {
            SPrint("  ===SERVER OPEN REQ===\n");
            sbAccCb.curTst.suConId =   msg->t.sbMsg.hi.suConId;
              /* save the suConId received from the SCTP */
            sbAccCb.curTst.spConId =   sbAccCb.curTst.suConId;
            (Void) cmMemcpy((U8 *) &(sbAccCb.curTst.localTAddr),\
                            (U8 *) &(msg->t.sbMsg.hi.localTAddr),\
                            (PTR)sizeof(CmTptAddr));
         }
      }

     } /* end if(msg->evntType == evnt) */
   else
   {
      *status = INC_EVNTTYPE;
      RETVALUE(RFAILED);
   } /* end else */

   RETVALUE(ROK);

} /* end sbHitChkReq */

/*
*
*       Fun:   sbHitChkUDatReq
*
*       Desc:  Check the chunk of the UDatReq.
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbHitChkUDatReq
(
SbOperQElm     *sbMsg,
SbMgmtQElm     *mgmtMsg,
SbAccChunkBld  *buildPar,
SbAccAssoc     *assoc,
SctStatus      *status
)
#else
PUBLIC  S16 sbHitChkUDatReq(sbMsg, mgmtMsg, buildPar, assoc, status)
SbOperQElm        *sbMsg;
SbMgmtQElm        *mgmtMsg;
SbAccChunkBld     *buildPar;
SbAccAssoc        *assoc;
SctStatus         *status;
#endif
{
   SbAccMsgQElm *msg;
   S16           ret;
   U8            pkArray[20];
   U8            idx;
   U32           i;
   Buffer       *mBuf;
   U32           chunkChecksum;
   U32           checksum;
   MsgLen        len;
   U8            tmpU8;
   U8            ID;
   Txt           pb[256];

   TRC2(sbHitChkUDatReq)
   UNUSED(mgmtMsg);

   if (sbAccPopMsg(&msg) != ROK)
   {
      *status = PRIMITIVE_NOT_RECV;
      RETVALUE(RFAILED);
   }

   if(msg->evntType == ACC_EVT_UDAT_REQ)
   {
      buildPar->status = PRIMITIVE_SUCCEED;
      *status = PRIMITIVE_SUCCEED;
      ret = ROK;

      /* verify spId for all requests */
      if(msg->t.sbMsg.hi.spId != sbMsg->hi.spId)
      {
         *status = INC_SPID;
         RETVALUE(RFAILED);
      }

      (Void) cmMemcpy((U8 *) &(sbMsg->hi.peerTAddr  ),
                      (U8 *) &( msg->t.sbMsg.hi.peerTAddr),
                      (PTR) sizeof(CmTptAddr) );

      /* do the Checksum thing */
      mBuf = msg->t.sbMsg.hi.mBuf;

      /* read the checksum value from the header */
      for ( i = 0; i < 4; i++ )
      {
         (Void) SExamMsg(&pkArray[i], mBuf, (MsgLen)(8+i));
      }

      /* write it into the temporary variable */
      idx = 0;
      chunkChecksum = 0;
      SB_UNPKU32(chunkChecksum);

      /* zero the checksum value in the buffer's header */
      for ( i = 8; i < 12; i++ )
      {
         (Void) SRepMsg(0x0, mBuf, (MsgLen)i);
      }

      len = 0;
      if ( mBuf != (Buffer *) NULLP )
      {
         SFndLenMsg( mBuf, &len );
      }
      else
      {
         *status = BUFF_EMPTY;
         RETVALUE(RFAILED);
      }

      checksum = 0;
     
#ifdef SB_CHECKSUM 
      /* determine the Checksum thingy */
      checksum = 1L;
      for ( i = 0; i < (U32)len; i++ )
      {
         SExamMsg((Data *)&tmpU8, mBuf, (MsgLen)i );
         checksum = sbChecksum32( checksum, &tmpU8, 1, SB_ADLER32 );
      }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC 
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

      if ( checksum != chunkChecksum )
      {
         *status = INC_ADLER;
         SB_RLSMEM(mBuf);
         RETVALUE(RFAILED);
      }

      SExamMsg(&ID, mBuf, 12);
      if ( ID != buildPar->chunkId )
      {
         sprintf(pb,"The received chunk ID = %s and the expected is = %s\n",\
                 sbTag2Str(chunkTable,ID),\
                 sbTag2Str(chunkTable, buildPar->chunkId) );
         SPrint(pb);
         *status = INV_CHUNK_RECV;
         SB_RLSMEM(mBuf);
         RETVALUE(RFAILED);
      }

      /* verify mBuf + release buffer */
      if( (buildPar->chunkId) == SB_ID_INIT)
      {
         /*Special request for additional lifetime parameters */
         ret = chkInitChunk(mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ( buildPar->chunkId == SB_ID_INITACK )
      {
         ret=chkInitAckChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ((buildPar->chunkId) == SB_ID_SACK)
      {
         ret=chkSackChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ((buildPar->chunkId) == SB_ID_ABORT)
      {
         ret=chkAbortErrChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ((buildPar->chunkId) == SB_ID_SDOWN)
      {
         ret=chkShutdwnChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ((buildPar->chunkId) == SB_ID_SDOWNACK)
      {
         ret=chkShutdwnAckChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ((buildPar->chunkId) == SB_ID_ERROR)
      {
         ret=chkAbortErrChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ((buildPar->chunkId) == SB_ID_COOKIE)
      {
         ret=chkCookieChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ((buildPar->chunkId) == SB_ID_COOKIEACK)
      {
         ret=chkCookieAckChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ((buildPar->chunkId) == SB_ID_DATA)
      {
         ret=chkDataChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ((buildPar->chunkId) == SB_ID_HBEAT)
      {
         ret=chkHBeatChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      if ((buildPar->chunkId) == SB_ID_HBEATACK)
      {
         ret=chkHBeatAckChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
      /*-- RFC 4460 -- MLK Fix */
      if ((buildPar->chunkId) == SB_ID_SDOWNCMPLT)
      {
          SB_RLSMEM(mBuf);
      }

/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_ECN      
      if ((buildPar->chunkId) == SB_ID_ECNE)
      {
         ret=chkEcneChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }

      if ((buildPar->chunkId) == SB_ID_CWR)
      {
         ret=chkCwrChunk(msg->t.sbMsg.hi.mBuf, buildPar, assoc);
         *status = buildPar->status;
      }
#endif /* SB_ECN */      

     if(ret == RFAILED)
     {
        RETVALUE(RFAILED);
     }

     } /* end if(msg->evntType == evnt) */
   else
   {
      *status = INC_EVNTTYPE;
      RETVALUE(RFAILED);
   } /* end else */

   RETVALUE(ROK);

} /* end sbHitChkUDatReq */

/*
*
*       Fun:   sbHitChkMuxUDatReq
*
*       Desc:  Check the chunk of the UDatReq, that may be multiplexed.
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbHitChkMuxUDatReq
(
SbOperQElm     *sbMsg,
SbMgmtQElm     *mgmtMsg,
SbAccChunkBld  *buildPar,
SbAccAssoc     *assoc,
SctStatus      *status
)
#else
PUBLIC  S16 sbHitChkMuxUDatReq(sbMsg, mgmtMsg, buildPar, assoc, status)
SbOperQElm        *sbMsg;
SbMgmtQElm        *mgmtMsg;
SbAccChunkBld     *buildPar;
SbAccAssoc        *assoc;
SctStatus         *status;
#endif
{
   SbAccMsgQElm *msg;
   S16           ret;
   U8            pkArray[SB_MAX_LEN];
   U8            idx;
   U32           i;
   Buffer       *mBuf = NULLP; /* RFC 4460 -- RTR -- windows warnings */
   U32           chunkChecksum;
   U32           checksum;
   MsgLen        len;
   U8            tmpU8 = 0;
   Txt           pb[256];
   U16           srcPort;
   U16           dstPort;
   U32           verTag;
   U8            chunkId;
   U8            chunkFlg;
   U16           chunkLeng;
   U16           pad;
   Data          dataRec;
   MsgLen        lenRec;


   TRC2(sbHitChkMuxUDatReq);
   UNUSED(mgmtMsg);

   if (sbAccPopMsg(&msg) != ROK)
   {
      *status = PRIMITIVE_NOT_RECV;
      RETVALUE(RFAILED);
   }

   if(msg->evntType == ACC_EVT_UDAT_REQ)
   {
      ret = ROK;
      buildPar->status = PRIMITIVE_SUCCEED;
      *status = PRIMITIVE_SUCCEED;

      /* verify spId for all requests */
      if(msg->t.sbMsg.hi.spId != sbMsg->hi.spId)
      {
         *status = INC_SPID;
   /*-- RFC 4460 -- MLK Fix --*/
   SB_RLSMEM(sbAccCb.curTst.gmBuf);    /* release memory */
         RETVALUE(RFAILED);
      }
/* sb003.103 - addition - check for ECT bit in the IP header of satellite
 * feature is enabled.
 */
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_ECN      
      if((msg->t.sbMsg.hi.hdrParm.u.hdrParmIpv4.tos.pres) && 
            ((buildPar->chunkId == SB_ID_INIT) || (buildPar->chunkId ==
                                                   SB_ID_INITACK)))
      {
         if(!(msg->t.sbMsg.hi.hdrParm.u.hdrParmIpv4.tos.val&0x02)) 
            RETVALUE(RFAILED);
         sprintf(prntBuf, " ECT bit set in the IP header ");
         SPrint(prntBuf);
      }
#endif       

      (Void) cmMemcpy((U8 *) &(sbMsg->hi.peerTAddr  ),\
                      (U8 *) &( msg->t.sbMsg.hi.peerTAddr),\
                      (PTR) sizeof(CmTptAddr) );
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
       sprintf(prntBuf, "Received address: %d \n",\
                       msg->t.sbMsg.hi.peerTAddr.u.ipv4TptAddr.address);
#else
        sprintf(prntBuf, "Received address: %ld \n",\
                       msg->t.sbMsg.hi.peerTAddr.u.ipv4TptAddr.address); 
#endif
       SPrint(prntBuf);

      /* do the Checksum thing */
      mBuf = msg->t.sbMsg.hi.mBuf;


      /* read the checksum value from the header */
      for ( i = 0; i < 4; i++ )
      {
         (Void) SExamMsg(&pkArray[i], mBuf, (MsgLen)(8+i));
      }

      /* write it into the temporary variable */
      idx = 0;
      chunkChecksum = 0;
      SB_UNPKU32(chunkChecksum);

      /* zero the checksum value in the buffer's header */
      for ( i = 8; i < 12; i++ )
      {
         (Void) SRepMsg(0x0, mBuf, (MsgLen)i);
      }

      len = 0;
      if ( mBuf != (Buffer *) NULLP )
      {
         SFndLenMsg( mBuf, &len );
      }
      else
      {
         *status = BUFF_EMPTY;
   /*-- RFC 4460 -- MLK Fix --*/
   SB_RLSMEM(sbAccCb.curTst.gmBuf);    /* release memory */
         RETVALUE(RFAILED);
      }

      checksum = 0;
#ifdef SB_CHECKSUM
      /* determine the Checksum thingy */
      checksum = 1L;
      for ( i = 0; i < (U32)len; i++ )
      {
         SExamMsg((Data *)&tmpU8, mBuf, (MsgLen)i );
         checksum = sbChecksum32( checksum, &tmpU8, 1,SB_ADLER32 );
      }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

      if ( checksum != chunkChecksum )
      {
         *status = INC_ADLER;
   /*-- RFC 4460 -- MLK Fix --*/
   SB_RLSMEM(sbAccCb.curTst.gmBuf);    /* release memory */
         SB_RLSMEM(mBuf);
         RETVALUE(RFAILED);
      }

      idx = 0;
      SRemPreMsgMult(&pkArray[0], 12, mBuf);

      /* Initialize local variables */
      srcPort = 0;
      dstPort = 0;
      verTag = 0;
      checksum = 0;

      /* unpack the common header */
      SB_UNPKU16(srcPort);
      SB_UNPKU16(dstPort);
      SB_UNPKU32(verTag);
      SB_UNPKU32(checksum);

      if ( verTag != assoc->verTagLoc )
      {
         buildPar->status = INV_VERTAG;
   /*-- RFC 4460 -- MLK Fix --*/
   SB_RLSMEM(sbAccCb.curTst.gmBuf);    /* release memory */
         SB_RLSMEM(mBuf)     /* release memory */
         RETVALUE(RFAILED);  /* Invalid verification Tag and/or chunk ID*/
      }

      len = (S16)(len - idx);
      while ( len > 0 )
      {
         /* Initialize local variables */
         idx = 0;
         chunkId = 0;
         chunkFlg = 0;
         chunkLeng = 0;

         SRemPreMsgMult(&pkArray[0], 4, mBuf);
         SB_UNPKU8(chunkId);

         sprintf(pb,"The chunkId received  = %s \n ",\
                 sbTag2Str(chunkTable, chunkId) );
         SPrint(pb);

         SB_UNPKU8(chunkFlg);
         buildPar->chunkFlg = chunkFlg;
         SB_UNPKU16(chunkLeng);
         buildPar->chunkLeng = chunkLeng;

         len -= 4;

         /* padding */
         if ( (chunkLeng % 4) != 0 )
         {
         pad = (U16)(4 - (chunkLeng % 4));
         }
         else
         {
            pad = 0;
         }

         switch (chunkId)
         {
            case SB_ID_DATA:  /* Payload data */
               ret = chkDataChunk(mBuf, buildPar, assoc);
               *status = buildPar->status;
               break;
            case SB_ID_SACK: /* SACK */
               ret = chkSackChunk(mBuf, buildPar, assoc);
               *status = buildPar->status;
               break;
            case SB_ID_SDOWN: /* Shutdown */
               ret = chkShutdwnChunk(mBuf, buildPar, assoc);
               *status = buildPar->status;
               break;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_ECN               
            case SB_ID_ECNE: /* ECNE */
               ret = chkEcneChunk(mBuf, buildPar, assoc);
               *status = buildPar->status;
               break;
            case SB_ID_CWR: /* CWR */
               ret = chkCwrChunk(mBuf, buildPar, assoc);
               *status = buildPar->status;
               break;
#endif /* SB_ECN */               
            default:
               ret = 1;
               *status = INV_CHUNK_RECV;
               break;
         } /* end of switch */

           /* lose the padding */
         for ( i = 0; i < pad; i++ )
         {
            idx = 0;
            SRemPreMsgMult(&pkArray[0], 1, mBuf);
            SB_UNPKU8(tmpU8);
         }

         /* adjust message size */
         len = (S16)(len - (pad + chunkLeng));
      } /* while len > 0 */

      if ( ((buildPar->chunkFlg & 3) == 3) || ((buildPar->chunkFlg & 3) == 1) )
      {
         /* Unbundled data or last piece of segmented chunk */
         SB_HITMSGCMP(sbAccCb.curTst.datRcv, sbAccCb.curTst.gmBuf, ret )
         sbAccCb.curTst.datRcvLen = 0;
         SB_RLSMEM(sbAccCb.curTst.gmBuf)    /* release memory */
      }  /* ready to test data */

      if ( ret != ROK )
      {
         if(ret == RFAILED)
         {
            SB_RLSMEM(sbAccCb.curTst.gmBuf);    /* release memory */
            SB_RLSMEM(mBuf);                    /* release memory */
            RETVALUE(RFAILED);
         } /* RFAILED */
      }  /* ret not equal to ROK */

   } else { /* end if(msg->evntType == evnt) */
      *status = INC_EVNTTYPE;
   /*-- RFC 4460 -- MLK Fix --*/
   SB_RLSMEM(sbAccCb.curTst.gmBuf);    /* release memory */
   SB_RLSMEM(mBuf)                    /* release memory */
      RETVALUE(RFAILED);
   } /* end else */

   /*-- RFC 4460 -- MLK Fix --*/
   SB_RLSMEM(sbAccCb.curTst.gmBuf);    /* release memory */
   SB_RLSMEM(mBuf)                    /* release memory */

   RETVALUE(ROK);

} /* end sbHitChkMuxUDatReq */


/*
*
*       Fun:   sbLsbChkCfm
*
*       Desc:  Remove all the SCT messages off the queue and verify
*              the parameter values.
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbLsbChkCfm
(
SbMgmtQElm  *mgmtMsg,
SctStatus   *status,
Reason      *reason,
U8          evnt
)
#else
PUBLIC  S16 sbLsbChkCfm(mgmtMsg, status, reason, evnt)
SbMgmtQElm  *mgmtMsg;
SctStatus   *status;
Reason      *reason;
U8          evnt;
#endif
{
   SbAccMsgQElm  *msg;
   Buffer        *mBuf;
   MsgLen         len;
   MsgLen         lenRec;
   U8             ret;
   U16            i;
   Data           dataRec;
   SbAccChunkBld *buildPar;
   SbAccChunkBld  bP;

   ret = ROK;
   buildPar = &bP;

   TRC2(sbLsbChkCfm)

   if (sbAccPopMsg(&msg) != ROK)
   {
      *status = PRIMITIVE_NOT_RECV;
      *reason = 0;
      RETVALUE(RFAILED);
   }
   if( (msg->evntType == evnt)  )
   {
      if ( (msg->t.mgmtMsg.transId == mgmtMsg->transId) || \
           (msg->evntType == ACC_EVT_STA_IND)||\
           (msg->evntType == ACC_EVT_TRC_IND)  )
      {
         *status = PRIMITIVE_SUCCEED;
         *reason = 0;

         if ( evnt == ACC_EVT_CNTRL_CFM )
         {
            SPrint("  ===CNTRL CFM===\n");
         }

         if( (evnt == ACC_EVT_CFG_CFM) ||  (evnt == ACC_EVT_STA_CFM) || 
             /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
             (evnt == ACC_EVT_SHT_CNTRL_CFM) || 
#endif /*SB_RUG */
#ifdef SB_FTHA
             (evnt == ACC_EVT_SHT_CNTRL_CFM) ||
#endif /*SB_FTHA */
             (evnt == ACC_EVT_CNTRL_CFM) ||(evnt == ACC_EVT_STS_CFM) )

         {    /* verify status (Not reason - informative only) */
            if (msg->t.mgmtMsg.cfm.status != mgmtMsg->cfm.status)
            {
               *status = INC_STATUS;
               *reason = msg->t.mgmtMsg.cfm.reason;
               RETVALUE(RFAILED);
            }
            if (msg->t.mgmtMsg.cfm.reason != mgmtMsg->cfm.reason)
            {
               *status = INC_REASON;
               *reason = msg->t.mgmtMsg.cfm.reason;
               RETVALUE(RFAILED);
            }
         }

         if( (evnt == ACC_EVT_TRC_IND) )
         {    /* verify TSAP Id */
            if (msg->t.mgmtMsg.s.trc.sapId != mgmtMsg->s.trc.sapId)
            {
               *status = INC_SPID;
               *reason = msg->t.mgmtMsg.cfm.reason;
               RETVALUE(RFAILED);
            }

            SB_SETUP_DAT_REQ(mBuf)
            SB_RLSMEM(mBuf)
            (Void) cmMemcpy( (U8 *) &(mgmtMsg->s.trc.evntParm),\
                   (U8 *)&(msg->t.mgmtMsg.s.trc.evntParm[28]),\
                   (PTR)  (msg->t.mgmtMsg.s.trc.len - 28) );

            sbAccCb.curTst.datRcvLen = (S16)(msg->t.mgmtMsg.s.trc.len - 28);
            SB_HITMSGCMP(mgmtMsg->s.trc.evntParm, sbAccCb.curTst.gmBuf, ret )
            SB_RLSMEM(sbAccCb.curTst.gmBuf)    /* release memory */
            sbAccCb.curTst.datRcvLen = 0;
            if (ret == RFAILED)
            {
               *status = INC_DATA;
               *reason = msg->t.mgmtMsg.cfm.reason;
               RETVALUE(RFAILED);
            }
         }

         switch (msg->t.mgmtMsg.elmId.elmnt)
         {
         case STSBGEN:
            (Void) cmMemcpy((U8 *) &(mgmtMsg->s.sts.u.genSts),
                            (U8 *) &(msg->t.mgmtMsg.s.sts.u.genSts),
                            (PTR) sizeof(SbGenSts) );
         break;
         case STSBSCTSAP:
           (Void) cmMemcpy((U8 *) &(mgmtMsg->s.sts.u.sctSts),
                           (U8 *) &(msg->t.mgmtMsg.s.sts.u.sctSts),
                           (PTR) sizeof(SbSctSapSts));

         break;
         case STSBTSAP:
         (Void) cmMemcpy((U8 *) &(mgmtMsg->s.sts.u.tSts),
                         (U8 *) &(msg->t.mgmtMsg.s.sts.u.tSts),
                         (PTR) sizeof(SbTSapSts) );
         break;
         }

         if( (evnt == ACC_EVT_STA_CFM) )
         {    /* verify TSAP Id */
            switch (msg->t.mgmtMsg.elmId.elmnt)
            {
               case STSBGEN:

                  (Void) cmMemcpy((U8 *) &(mgmtMsg->s.ssta.s.genSta),
                                  (U8 *)  &(msg->t.mgmtMsg.s.ssta.s.genSta),
                                  (PTR)sizeof(SbGenSta) );
                  break;
               case STSBTSAP:
               case STSBSCTSAP:
                  (Void) cmMemcpy((U8 *) &(mgmtMsg->s.ssta.s.sapSta),
                                  (U8 *)  &(msg->t.mgmtMsg.s.ssta.s.sapSta),
                                  (PTR)sizeof(SbSapSta) );
                  break;
               case STSBSID:
                  (Void) cmMemcpy((U8 *) &(mgmtMsg->s.ssta.s.sysId),
                                  (U8 *)  &(msg->t.mgmtMsg.s.ssta.s.sysId),
                                  (PTR)sizeof(SystemId) );
                  break;
               case STSBDTA:
                  (Void) cmMemcpy((U8 *) &(mgmtMsg->s.ssta.s.dtaSta),
                                  (U8 *)  &(msg->t.mgmtMsg.s.ssta.s.dtaSta),
                                  (PTR)sizeof(SbDtaSta) );
                  break;
               case STSBASSOC:
                  (Void) cmMemcpy((U8 *) &(mgmtMsg->s.ssta.s.assocSta),
                                  (U8 *)  &(msg->t.mgmtMsg.s.ssta.s.assocSta),
                                  (PTR)sizeof(SbAssocSta) );
                  break;
            }
         }

         if( (evnt == ACC_EVT_STA_IND) )
         {    /* verify alarm event */
            if(msg->t.mgmtMsg.s.usta.event != mgmtMsg->s.usta.event)
            {
               *status = INC_EVNT;
               *reason = msg->t.mgmtMsg.cfm.reason;
               RETVALUE(RFAILED);
            }

            /* verify alarm cause */
            if(msg->t.mgmtMsg.s.usta.cause != mgmtMsg->s.usta.cause)
            {
               *status = INC_CAUSE;
               *reason = msg->t.mgmtMsg.cfm.reason;
               RETVALUE(RFAILED);
            }
         }
      }
   } else { /* end if(msg->evntType == evnt) */
       /* Incorrect primitive */
      if (msg->evntType != evnt)
      {
         *status = INC_EVNTTYPE;
         *reason = 0;
      } else {
         if ( (msg->evntType != ACC_EVT_STA_IND)||\
              (msg->evntType != ACC_EVT_TRC_IND)  )
         {
            if (msg->t.mgmtMsg.transId != mgmtMsg->transId)
            {
              *status = INC_TRANSID;
              *reason = 0;
            }
         }
      }
      RETVALUE(RFAILED);
   } /* end else */

   RETVALUE(ROK);

} /* end sbLsbChkCfm */

/* sb012.103: Placed the function under the flag LSB12 */
#ifdef LSB12
/*
*
*       Fun:   sbLsbChkTmr
*
*       Desc:  Remove all the SCT messages off the queue and
*              verify the parameter values.
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbLsbChkTmr
(
SbMgmtQElm  *mgmtMsg,
SctStatus   *status,
Reason      *reason,
U8          tmrType,
Bool        state
)
#else
PUBLIC  S16 sbLsbChkTmr(mgmtMsg, status, reason, tmrType, state)
SbMgmtQElm  *mgmtMsg;
SctStatus   *status;
Reason      *reason;
U8          tmrType;
Bool        state;
#endif          /* start of function */
{
   SbAccMsgQElm *msg;

   TRC2(sbLsbChkTmr)

   if (sbAccPopMsg(&msg) != ROK)
   {
      *status = PRIMITIVE_NOT_RECV;
      *reason = 0;

      RETVALUE(RFAILED);
   }

   if( msg->evntType == ACC_EVT_STA_CFM )
   {
      *status = PRIMITIVE_SUCCEED;
      *reason = 0;

      /* verify status (Not reason - informative only) */
      if (msg->t.mgmtMsg.cfm.status != mgmtMsg->cfm.status)
      {
         *status = PRIMITIVE_FAILED;
         *reason = msg->t.mgmtMsg.cfm.reason;
         RETVALUE(RFAILED);
      }

      if ( state == STOPPED)  /*check that timer is switched off */
      {
         if( (tmrType ==  ACC_T1_COOKIE) &&\
             (msg->t.mgmtMsg.s.ssta.s.tmrSta.cookieTmr == RUNNING ) )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }

         if( (tmrType ==  ACC_T2_SDOWN ) &&\
             (msg->t.mgmtMsg.s.ssta.s.tmrSta.t2Shutdown == RUNNING ) )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }

         if( ( tmrType ==  ACC_T1_INIT ) &&\
             (msg->t.mgmtMsg.s.ssta.s.tmrSta.t1InitTmr == RUNNING )  )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }

         if( ( tmrType ==  ACC_TINT ) && \
             (msg->t.mgmtMsg.s.ssta.s.tmrSta.tIntTmr == RUNNING ) )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }
         if( ( tmrType ==  ACC_T3RTX ) &&\
             (msg->t.mgmtMsg.s.ssta.s.tmrSta.t3rtx == RUNNING ) )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }
         if((  tmrType ==  ACC_HBEAT   ) &&\
            (msg->t.mgmtMsg.s.ssta.s.tmrSta.hBeat == RUNNING ) )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }
      }
      else if (state == RUNNING)
      {     /* State = RUNNING */
         if( (tmrType ==  ACC_T1_COOKIE )  && \
             (msg->t.mgmtMsg.s.ssta.s.tmrSta.cookieTmr == STOPPED ) )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }

         if( (tmrType ==  ACC_T2_SDOWN )  && \
             (msg->t.mgmtMsg.s.ssta.s.tmrSta.t2Shutdown == STOPPED ) )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }
         if( ( tmrType ==  ACC_T1_INIT ) &&\
             (msg->t.mgmtMsg.s.ssta.s.tmrSta.t1InitTmr == STOPPED )  )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }
         if( (tmrType ==  ACC_TINT )  && \
             (msg->t.mgmtMsg.s.ssta.s.tmrSta.tIntTmr == STOPPED ) )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }
         if( ( tmrType ==  ACC_T3RTX ) &&\
             (msg->t.mgmtMsg.s.ssta.s.tmrSta.t3rtx == STOPPED ) )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }
         if(( tmrType ==  ACC_HBEAT   ) && \
            (msg->t.mgmtMsg.s.ssta.s.tmrSta.hBeat == STOPPED ) )
         {
            *status = INC_TMRSTATE;
            *reason = msg->t.mgmtMsg.cfm.reason;
            RETVALUE(RFAILED);
         }
      }   /* end false ELSE */

   } /* end if(msg->evntType == evnt) */
   else   /* Incorrect primitive */
   {
      *status = INC_EVNTTYPE;
      *reason = 0;
      RETVALUE(RFAILED);
   } /* end else */

   RETVALUE(ROK);

} /* end sbLsbChkTmr */
#endif /* LSB12 */


/*
*
*       Fun:   doCleanup
*
*       Desc:  This do cleanup after a test or subtest was executed
*              The configuration is deleted.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC void doCleanup
(
)
#else
PUBLIC void doCleanup(void)
#endif
{
   if (sbAccCb.curTst.bConfigDeleted == FALSE)
   {
      sbShutdownOper();
   }
   else  /* Done with cleanup */
   {
      sbAccCb.curTst.bBusyCleanup = FALSE;
      sbAccCb.curTst.bConfigDeleted = FALSE;

      /* Check if all subtests were executed */
      if (sbAccCb.curTst.bTestsCompleted == TRUE)
         sbAccCb.curTst.bCompleted = TRUE;  /* Done with this test */
      else  /* Continue with next test */
      {
         /* Reset masks and pre-test config must be done. */
         sbAccCb.curTst.state = 0;
         sbAccCb.curTst.subTest = 1;
         sbAccCb.curTst.subTestsPass = 0;
         sbAccCb.curTst.subTestsFail = 0;
         sbAccCb.curTst.bBusyPreTestConf = TRUE;
         sbAccCb.curTst.bConfigMask = 0;
         sbAccCb.curTst.bSctSapCfgMask = 0;
         sbAccCb.curTst.bTSapCfgMask   = 0;
         sbAccCb.curTst.bSapMask    = 0;
         sbAccCb.curTst.bAssocMask  = 0;;
         sbAccCb.curTst.bTSapMask = 0;
         sbAccCb.curTst.bEndpMask = 0;
         sbAccCb.curTst.bAssocMask = 0;
         sbAccCb.curTst.bAssocSetupMask = 0;
         sbAccCb.curTst.bSapMask = 0;
         sbAccCb.curTst.bTraceMask = 0;
         sbAccCb.curTst.bDebugPMask = 0;
         sbAccCb.curTst.bTickMask  = 0;
         sbAccCb.curTst.delay = 0;
         sbAccCb.curTst.state = 0;
         sbAccCb.curTst.tickLstDoneFlg = TRUE;
         SB_RLSMEM(sbAccCb.curTst.gmBuf)  /*  release memory */
         SB_ZERO(&sbAccCb.curTst.datRcv, (S32)sizeof(sbAccCb.curTst.datRcv));
         sbAccCb.curTst.datRcvLen = 0;
         }
     }
}  /* end doCleanup */

/*
*
*       Fun:   sbShutdownOper
*
*       Desc:  Shutdown the operations.
*              SCTP deallocates all the allocated resources.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC void sbShutdownOper
(
)
#else
PUBLIC void sbShutdownOper(void)
#endif
{
   SbAccMsgQElm   *msg;
   PRIVATE        SbMgmtQElm     mgmt;
   PRIVATE        SbMgmt         sbMgmt;
   SctStatus      status;
   Reason         reason;
   S16            ret;
   /*-- RFC 4460: MLK fix*/
   U8             ID;

   TRC2(sbShutdownOper);
   ret = ROK;
   reason = LCM_REASON_NOT_APPL;

   switch(sbAccCb.curTst.state)
   {
      case 0:  /* Send control request */
         setResponse(&sbMgmt.hdr.response);
         sbMgmt.hdr.elmId.elmnt = STSBGEN;
         sbMgmt.t.cntrl.action = ASHUTDOWN;
         sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 3300;  /* TransId */
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE         
         sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif
         (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
         sbAccCb.curTst.state++;
         break;
      case 1:  /* Confirm for control request */
          /* verify if msg in queue */
         sbAccVfyMsg(&status);
         if(status == WAIT)
         {  /* wait for message to reach the queue */
            RETVOID;
         } else if(status == TIMEOUT) {
            sbAccDispErrTstRslt("sbShutdownOper", 0,
                                 ACC_EVT_CNTRL_CFM, TIMEOUT_ON_PRIM, 0);
            sbAccCb.curTst.bCompleted = TRUE;  /* Problem */
         }
         else
         {  /* primitive received */
            /* fill the mgmt */
            sbAccPeekMsg(&msg);
            if (msg->evntType == ACC_EVT_CNTRL_CFM) {
               mgmt.transId = sbAccCb.curTst.curTransId;
               mgmt.cfm.status = LCM_PRIM_OK;
               mgmt.cfm.reason = LCM_REASON_NOT_APPL;
               ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
            }
            else
            {
               sbAccPopMsg(&msg);  /* pop unwanted closedown from the stack */
               /*RFC 4460 --- MLK fix (drop Abort)*/
               if(msg->t.sbMsg.hi.mBuf != NULLP)
               {
                SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                if ( ID == SB_ID_ABORT )
                {
                    SB_RLSMEM(msg->t.sbMsg.hi.mBuf);
                }
               }
            }

            if(ret == RFAILED)
            {
               sbAccDispErrTstRslt("sbShutdownOper", 0,
                                    ACC_EVT_CNTRL_CFM, status, reason);
               sbAccCb.curTst.bCompleted = TRUE;  /* Problem */
            }
         } /* end primitive received */
         sbAccCb.curTst.delay = 1;
         sbAccCb.curTst.state++;
         break;
      case 2:  /* Confirm for control request */
          /* verify if msg in queue */
         sbAccVfyMsg(&status);
         if(status == WAIT)
         {  /* wait for message to reach the queue */
            RETVOID;
         } else if(status == TIMEOUT) {
            sbAccCb.curTst.bConfigDeleted = TRUE;
         }
         else
         {
            sbAccPopMsg(&msg);  /* pop unwanted closedown from the stack */
               /*RFC 4460 --- MLK fix (drop Abort)*/
               if(msg->t.sbMsg.hi.mBuf != NULLP)
               {
                SExamMsg(&ID, msg->t.sbMsg.hi.mBuf, 12);
                if ( ID == SB_ID_ABORT )
                {
                    SB_RLSMEM(msg->t.sbMsg.hi.mBuf);
                }
               }
         }
   } /* end switch */
   RETVOID;
} /* end sbShutdownOper */

/*
*
*       Fun:   setResponse
*
*       Desc:  Fill in Resp structure
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC void setResponse
(
Resp *resp
)
#else
PUBLIC void setResponse(resp)
Resp *resp;
#endif
{

#ifdef LCSBMILSB
   resp->selector = (U8)(sbAccCb.tcFlg == TRUE ? SEL_TC : SEL_LC);
#else
   resp->selector = SEL_TC;
#endif

   resp->prior = PRIOR0;
   resp->route = RTESPEC;
   resp->mem.region  = DFLT_REGION;
   resp->mem.pool = DFLT_POOL;
   RETVOID;
}

/*
*
*       Fun:   sbStdGenCfg
*
*       Desc:  Fill in the general configuration structure
*
*       Ret:   None
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/

#ifdef ANSI
PUBLIC  Void sbStdGenCfg
(
SbMgmt *sbCfgPtr   /* configuration structure received from test routine */
)
#else
PUBLIC  Void sbStdGenCfg(sbCfgPtr)
SbMgmt *sbCfgPtr;   /* configuration structure received from test routine */
#endif
{
   SbGenCfg *genCfg;
   SbGenReCfg *genreCfg;

   TRC2(sbStdGenCfg)

   setResponse(&sbCfgPtr->hdr.response);
   sbCfgPtr->hdr.elmId.elmnt = STSBGEN;
   genCfg = &(sbCfgPtr->t.cfg.s.genCfg);
   genreCfg = &(sbCfgPtr->t.cfg.s.genCfg.reConfig);
   /* Keep separate for reconfiguration */

   /* set configuration parameters */
#ifdef SB_IPV6_SUPPORTED   /* sb032.102 : IPV6 Support Added */
   genCfg->ipv6SrvcReqdFlg = TRUE;
#endif
   genCfg->serviceType = HI_SRVC_RAW_SCTP;  /* use packectized TCP data */
   genCfg->maxNmbSctSaps = 4;
   genCfg->maxNmbTSaps = 3;
   genCfg->maxNmbAssoc = 5;
   genCfg->maxNmbEndp = 3;
   genCfg->maxNmbDstAddr = 10;
   genCfg->maxNmbSrcAddr = 10;
   genCfg->maxNmbTxChunks = 10;
   genCfg->maxNmbRxChunks = 20;
   genCfg->maxNmbInStrms = 10;
   genCfg->maxNmbOutStrms = 10;
   genCfg->initARwnd =  ACC_ARWND_INIT;
   genCfg->mtuInitial = ACC_MTU_INIT;
   genCfg->mtuMinInitial = ACC_MTU_INIT;
   genCfg->mtuMaxInitial = ACC_MTU_INIT;
   genCfg->performMtu = FALSE;
/* sb014.103: Function to calculate timeRes */
   genCfg->timeRes = sbAccCalcTicks(100); 
/* sb003.103: Moved from GenCfg to General reConfig structure */ 
/* sb004.103: Protected under compile-time flag */
#ifdef LSB9
   sbGetLmPst(&genreCfg->smPst);
#else
   sbGetLmPst(&genCfg->smPst);
#endif
    /*  SB_VER13 - Added for version 13 */
   /* sb003.103 - modification - changed the domain name to CCPU from Trillium
    */ 
/* sb003.103: SATELLITE SCTP feature */ 
   cmMemcpy(genCfg->hostname,(CONSTANT U8 *)"www.ccpu.com", 
                            cmStrlen((CONSTANT U8 *)"www.ccpu.com"));
   genCfg->useHstName = FALSE;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE         
   genCfg->maxNmbPathProfs = 5;
#endif   

   genreCfg->maxInitReTx = 8;
   /* sb071.102 Adjusted the value */
   genreCfg->maxAssocReTx = 3;
   genreCfg->maxPathReTx = 2;
   genreCfg->altAcceptFlg = TRUE;
   genreCfg->keyTm = 5000;  /* initial value for MD 5key expiry timer */
   genreCfg->alpha = 12;
   genreCfg->beta = 25;
   /* sb003.103 - addition - max Path profiles added in gen config. */
/* SATELLITE SCTP feature */ 
#ifdef SB_ECN
   genreCfg->ecnFlg = TRUE;
#endif /* SB_ECN */   

   RETVOID;
} /* end of sbStdGenCfg */

/*
*
*       Fun:   sbStdSctSapCfg
*
*       Desc:  Fill in the Sap Sct configuration structure
*
*       Ret:   None
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/

#ifdef ANSI
PUBLIC  Void sbStdSctSapCfg
(
SbMgmt *sbCfgPtr,   /* configuration structure received from test routine */
U8      specCfg      /* Number of the specific configuration */
)
#else
PUBLIC  Void sbStdSctSapCfg(sbCfgPtr, specCfg)
SbMgmt *sbCfgPtr;   /* configuration structure received from test routine */
U8      specCfg;     /* Number of the specific configuration */
#endif
{
   SbSctSapCfg *sctSapCfg;
   SbSctSapReCfg *sctSapReCfg;

   TRC2(sbStdSctSapCfg)

   setResponse(&sbCfgPtr->hdr.response);
   sbCfgPtr->hdr.elmId.elmnt = STSBSCTSAP;
   sctSapCfg = &(sbCfgPtr->t.cfg.s.sctSapCfg);
   sctSapReCfg = &(sbCfgPtr->t.cfg.s.sctSapCfg.reConfig);


   /* set configuration parameters */
   sctSapCfg->swtch = LSB_SW_RFC_REL0;
#ifdef LCITLISCT
   sctSapCfg->sel = sbAccCb.tcFlg == TRUE ? SEL_TC : SEL_LC;
#else
   sctSapCfg->sel = SEL_TC;
#endif
   sctSapCfg->memId.region = DFLT_REGION;
   sctSapCfg->memId.pool = DFLT_POOL;
   sctSapCfg->prior = PRIOR0;
   sctSapCfg->route = RTESPEC;
   
   /* we make this slightly longer than the recommended 200ms since
      debug printing might slow the layer down a bit */
   sctSapReCfg->maxAckDelayTm = 5;       /* Equivalent of 500 ms */
   sctSapReCfg->maxAckDelayDg = 2;
   sctSapReCfg->rtoInitial = ACC_RTO_INIT;
   sctSapReCfg->rtoMin = ACC_RTO_INIT;
   sctSapReCfg->rtoMax = ACC_RTO_INIT;
   sctSapReCfg->cookieLife = 30000;        /* 1000ms = 1 second */
   sctSapReCfg->intervalTm = 15;   
   sctSapReCfg->freezeTm = 15;  
   
   sctSapReCfg->hBeatEnable = FALSE; /* SB_VER13-hBeatEnable added */
  /* RFC 4460 upgrade -- changed from 3-> 5 */
   sctSapReCfg->flcUpThr = 5;

   sctSapReCfg->flcLowThr = 2;

  /* RFC 4460 upgrade -- introduced new reconfig parameters */
   sctSapReCfg->maxBurst = 4;
   sctSapReCfg->maxHbBurst = 1;
   sctSapReCfg->t5SdownGrdTm = 5 * sctSapReCfg->rtoMax;

#ifdef SB_ETSI
   sctSapReCfg->maxDataSize = 1000;
#endif /* SB_ETSI */

/* SB_SCTP_3 */
#ifdef SB_CHECKSUM_DUAL
   sctSapReCfg->checksumType = SB_ADLER32;
#endif /* SB_CHECKSUM_DUAL */

   /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
   sctSapReCfg->remIntfValid = TRUE;
   sctSapReCfg->remIntfVer = SCTIFVER;
#endif /* SB_RUG */

            switch(specCfg)
            {
             case SAP_1:
                sctSapCfg->spId = SPID_0;
                sctSapReCfg->negAbrtFlg = FALSE;
                sctSapReCfg->handleInitFlg = TRUE;
                break;
             case SAP_2:
                sctSapCfg->spId = SPID_1;
                sctSapReCfg->negAbrtFlg = TRUE;
                sctSapReCfg->handleInitFlg = FALSE;
                break;
             case SAP_3:
                sctSapCfg->spId = SPID_2;
                sctSapReCfg->negAbrtFlg = FALSE;
                sctSapReCfg->handleInitFlg = TRUE;
                break;
             /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
             case SAP_4:
                sctSapCfg->spId = SPID_0;
                sctSapReCfg->negAbrtFlg = FALSE;
                sctSapReCfg->handleInitFlg = TRUE;
                sctSapReCfg->remIntfValid = TRUE;
                sctSapReCfg->remIntfVer = SCTIFVER;
                break;
             case SAP_5:
                sctSapCfg->spId = SPID_0;
                sctSapReCfg->negAbrtFlg = FALSE;
                sctSapReCfg->handleInitFlg = TRUE;
                sctSapReCfg->remIntfValid = TRUE;
                sctSapReCfg->remIntfVer = SCTIFVER-1;
                break;
#endif /* SB_RUG */
             default:
                break;
            }
   RETVOID;
} /* end of sbStdSctSapCfg */

/*
*
*       Fun:   sbStdTSapCfg
*
*       Desc:  Fill in the TUCL SAP configuration structure
*
*       Ret:   None
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/

#ifdef ANSI
PUBLIC  Void sbStdTSapCfg
(
SbMgmt      *sbCfgPtr,/* configuration structure received from test routine */
U8          specCfg   /* Number of the specific configuration */
)
#else
PUBLIC  Void sbStdTSapCfg(sbCfgPtr, specCfg)
SbMgmt      *sbCfgPtr;/* configuration structure received from test routine */
U8          specCfg;  /* Number of the specific configuration */
#endif
{
   SbTSapCfg      *tSapCfg;
   SbTSapReCfg    *tSapReCfg;
   SctNetAddrLst  *srcNAddrLst;
   U8             i;

   TRC2(sbStdTSapCfg)
   setResponse(&sbCfgPtr->hdr.response);
   sbCfgPtr->hdr.elmId.elmnt = STSBTSAP;
   tSapCfg = &(sbCfgPtr->t.cfg.s.tSapCfg);
   tSapReCfg = &(sbCfgPtr->t.cfg.s.tSapCfg.reConfig);
   srcNAddrLst = &(sbCfgPtr->t.cfg.s.tSapCfg.srcNAddrLst);

   /* set configuration parameters */
   tSapCfg->swtch = LSB_SW_RFC_REL0;
#ifdef LCHIUIHIT
   tSapCfg->sel = sbAccCb.tcFlg == TRUE ? SEL_TC : SEL_LC;
#else
   tSapCfg->sel = SEL_TC;
#endif

   tSapCfg->ent = ENTHI;
   tSapCfg->inst = TSTINST_0;
   tSapCfg->procId = SFndProcId();
   tSapCfg->memId.region = TSTREG;
   tSapCfg->memId.pool = TSTPOOL;
   tSapCfg->prior = PRIOR0;
   tSapCfg->route = RTESPEC;

   /*set reconfiguration parameters*/
   tSapReCfg->tIntTmr = 10;     /* Depend on timer tick*/
   tSapReCfg->maxBndRetry = 3;

   /* SB_VER13 - Parameter added for DNS interface */
   tSapReCfg->sbDnsCfg.dnsAddr.type = CM_NETADDR_IPV4;
   tSapReCfg->sbDnsCfg.dnsAddr.u.ipv4TptAddr.port = 53;
   tSapReCfg->sbDnsCfg.dnsAddr.u.ipv4TptAddr.address = loopBkAddr;

   /* sb044.102: added for changes in protocol layer. Now DNS open request *
    * will be called if DNS is configured in TSAP                          */
   if (sbAccCb.useDnsFlag == TRUE)
   {
      tSapReCfg->sbDnsCfg.useDnsLib = TRUE;
   }
   else
      tSapReCfg->sbDnsCfg.useDnsLib = FALSE;

   tSapReCfg->sbDnsCfg.dnsTmOut    = 3;
   tSapReCfg->sbDnsCfg.maxRtxCnt   = 3;

   /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
   tSapReCfg->remIntfValid = TRUE;
   tSapReCfg->remIntfVer = HITIFVER;
#endif /* SB_RUG */

   switch(specCfg)
   {
      case SAP_1:
         tSapReCfg->spId = SPID_0;
         tSapCfg->suId = SUID_0;
         tSapCfg->srcNAddrLst.nmb = 2;
         /* sb032.102 : IPV6 Support Added */
         if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4) 
         {
            for (i = 0; (i < tSapCfg->srcNAddrLst.nmb ); i++)
            {
                /* IPV4 addresses  */
               tSapCfg->srcNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;
               tSapCfg->srcNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_1[i];
            }
         }
         else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
         {
            for (i = 0; (i < tSapCfg->srcNAddrLst.nmb ); i++)
            {
                /* IPV4 addresses  */
               tSapCfg->srcNAddrLst.nAddr[i].type = CM_TPTADDR_IPV6;
               CPY_ACC_ASSOC1_LOCAL_IPV6((U8 *)&tSapCfg->srcNAddrLst.nAddr[i].u.ipv6NetAddr, i)
            }
         }
         break;

      case SAP_2:
         tSapReCfg->spId = SPID_1;
         tSapCfg->suId = SUID_1;
         tSapCfg->srcNAddrLst.nmb = 2;

  if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
  {
            for (i = 0; (i < tSapCfg->srcNAddrLst.nmb); i++)
            {  /* IPV4 addresses  */
               tSapCfg->srcNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;
               tSapCfg->srcNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_2[i];
            }
   }
         break;

/* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
      case SAP_6:
         tSapReCfg->spId = SPID_0;
         tSapCfg->suId = SUID_0;
         tSapCfg->srcNAddrLst.nmb = 4;
         if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4) 
         {
            for (i = 0; (i < 2 ); i++)
            {
                /* IPV4 addresses  */
               tSapCfg->srcNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;
               tSapCfg->srcNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_1[i];
            }
            for (i = 2; (i < 4 ); i++)
            {
                /* IPV4 addresses  */
               tSapCfg->srcNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;
               tSapCfg->srcNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_2[i-2];
            }
         }
         else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
         {
            for (i = 0; (i < tSapCfg->srcNAddrLst.nmb ); i++)
            {
                /* IPV4 addresses  */
               tSapCfg->srcNAddrLst.nAddr[i].type = CM_TPTADDR_IPV6;
               CPY_ACC_ASSOC1_LOCAL_IPV6((U8 *)&tSapCfg->srcNAddrLst.nAddr[i].u.ipv6NetAddr, i)
            }
         }
         break;
#endif /* SCT_ENDP_MULTI_IPADDR */


   } /* end switch */
   RETVOID;
} /* end of sbStdTSapCfg */

/* sb003.103 - addition - function to fill path profile configuration structure. */
/* SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE
/*
*
*       Fun:   sbStdPathProfCfg
*
*       Desc:  Fill in the Path Profile configuration structure
*
*       Ret:   None
*
*       Notes: None
*
*       File:  sb_acc2.c
*
*/

#ifdef ANSI
PUBLIC  Void sbStdPathProfCfg
(
SbMgmt      *sbCfgPtr   /* configuration structure received from test routine */
)
#else
PUBLIC  Void sbStdPathProfCfg(sbCfgPtr)
SbMgmt      *sbCfgPtr;  /* configuration structure received from test routine */
#endif
{
   SbPathProfCfg      *pathProfCfg;
   SbPathProfReCfg    *pathProfReCfg;

   TRC2(sbStdPathProfCfg)

   setResponse(&sbCfgPtr->hdr.response);
   sbCfgPtr->hdr.elmId.elmnt = STSBPATHPROF;

   pathProfCfg = &(sbCfgPtr->t.cfg.s.pathProfCfg);
   pathProfReCfg = &(sbCfgPtr->t.cfg.s.pathProfCfg.reConfig);

   /* set configuration parameters */
   pathProfCfg->profId = PROFID_0;

   /*set reconfiguration parameters*/
   pathProfReCfg->initCwnd = 4;
   pathProfReCfg->initSsthresh = 4;
   pathProfReCfg->rtoInitial = 150;
   pathProfReCfg->rtoMin = 150;
   pathProfReCfg->rtoMax = 150;
   pathProfReCfg->alpha = 12;
   pathProfReCfg->beta = 25;
   pathProfReCfg->intervalTm = 15;
#ifdef LSB4
   pathProfReCfg->bundleTm = ACC_RTO_SHORT;
#endif
   pathProfReCfg->bcl = 2;
   pathProfReCfg->idleCwndRate = 2;
   pathProfReCfg->frCwndRate = 2;
   pathProfReCfg->rtrCwndRate = 2;
   pathProfReCfg->hBeatEnable = FALSE;
   pathProfReCfg->maxPathReTx = 2;
   pathProfReCfg->minOutStrms = 10;

   RETVOID;
} /* end of sbStdPathProfCfg */

/* sbxxx.103 - addition - function to fill destination address configuration structure. */
/*
*
*       Fun:   sbStdDstAddrCfg
*
*       Desc:  Fill in the destination address configuration structure
*
*       Ret:   None
*
*       Notes: None
*
*       File:  sb_acc2.c
*
*/

#ifdef ANSI
PUBLIC  Void sbStdDstAddrCfg
(
SbMgmt      *sbCfgPtr   /* configuration structure received from test routine */
)
#else
PUBLIC  Void sbStdDstAddrCfg(sbCfgPtr)
SbMgmt      *sbCfgPtr;  /* configuration structure received from test routine */
#endif
{
   SbDstAddrCfg      *dstAddrCfg;

   TRC2(sbStdDstAddrCfg)

   setResponse(&sbCfgPtr->hdr.response);
   sbCfgPtr->hdr.elmId.elmnt = STSBDSTADDR;

   dstAddrCfg = &(sbCfgPtr->t.cfg.s.dstAddrCfg);

   /* set configuration parameters */
   dstAddrCfg->profId = PROFID_0;

   dstAddrCfg->dstAddr.type = CM_NETADDR_IPV4;
   dstAddrCfg->dstAddr.u.ipv4NetAddr = ACC_ASSOC1_DEST_3;

   RETVOID;
} /* end of sbStdDstAddrCfg */
#endif /* SB_SATELLITE */
/*
*
*       Fun:   sbSendConfigReq
*
*       Desc:  Send a configuration request and
*              checks that the confirm succeeds
*
*       Ret:   None
*
*       Notes: Used as pretest
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void sbSendConfigReq
(
SbMgmt  *sbCfgPtr,  /* configuration structure received from test routine */
U8       type,             /* gen, sctsap, tsap */
U8       specCfg           /* specific configuration */
)
#else
PUBLIC  void sbSendConfigReq(sbCfgPtr, type, specCfg)
SbMgmt   *sbCfgPtr;  /* configuration structure received from test routine */
U8        type;            /* gen, sctsap, tsap */
U8        specCfg;         /* specific configuration */
#endif
{
   PRIVATE     SbMgmtQElm  mgmt;
   SctStatus   status;
   Reason      reason;
   S16         ret;

   TRC2(sbSendConfigReq)

   ret = ROK;

   /* enter configuration */
   switch (sbAccCb.curTst.state)
   {
      case 0:  /* Configure configuration */
      {
         reason = LCM_REASON_NOT_APPL;
         status = 0;
         /* Set transId */
         switch (type)
         {
            case STSBGEN:
               sbCfgPtr->hdr.transId = sbAccCb.curTst.curTransId = 1101;
               break;
            case STSBSCTSAP:
               switch (specCfg)
               {
                  case SAP_1:
                  /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
                  case SAP_4:
                  case SAP_5:
#endif /* SB_RUG */
                      sbCfgPtr->hdr.transId = sbAccCb.curTst.curTransId = 1102;
                     break;
                  case SAP_2:
                     sbCfgPtr->hdr.transId = sbAccCb.curTst.curTransId = 1103;
                     break;
                  case SAP_3:
                     sbCfgPtr->hdr.transId = sbAccCb.curTst.curTransId = 1104;
                     break;
               }
               break;
            case STSBTSAP:
               switch (specCfg)
               {
                  case SAP_1:
                  /* sb046.102: Multiple IP address per Endp */
                  case SAP_6:
                     sbCfgPtr->hdr.transId = sbAccCb.curTst.curTransId = 1105;
                     break;
                  case SAP_2:
                     sbCfgPtr->hdr.transId = sbAccCb.curTst.curTransId = 1106;
                     break;
               }
               break;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE
            case STSBPATHPROF:   
               sbCfgPtr->hdr.transId = sbAccCb.curTst.curTransId = 1107;
               break;
            case STSBDSTADDR:
               sbCfgPtr->hdr.transId = sbAccCb.curTst.curTransId = 1108;
               break;
#endif
            default:
               sbAccDispErrTstRslt("sbSendConfigReq", type,
                                    ACC_EVT_CFG_CFM, status, reason);
               /* Problem - do cleanup */
               SB_SUBTESTFAIL()
               break;
         }  /* end switch */
         setResponse(&sbCfgPtr->hdr.response);
         (Void) SmMiLsbCfgReq(&sbAccCb.smPst, sbCfgPtr);
         sbAccCb.curTst.state++;
         break;
      }

      case 1:  /* Confirm for config */
      {
         /* verify if msg in queue */
         sbAccVfyMsg(&status);
         if (status == WAIT)
         {
            /* wait for message to reach the queue */
            RETVOID;
         }
         else if (status == TIMEOUT)
         {
            sbAccDispErrTstRslt("sbSendConfigReq", type,
                                 ACC_EVT_CFG_CFM, TIMEOUT_ON_PRIM, 0);
            /* Problem - do cleanup */
            SB_SUBTESTFAIL()
         }
         else
         {
            /*primitive received */
            /* fill the mgmt */
            mgmt.transId = sbAccCb.curTst.curTransId;
            mgmt.cfm.status = LCM_PRIM_OK;
            mgmt.cfm.reason = LCM_REASON_NOT_APPL;
            ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CFG_CFM);

            if (ret == RFAILED)
            {
               sbAccDispErrTstRslt("sbSendConfigReq", type,
                                    ACC_EVT_CFG_CFM, status, reason);

               /* Problem - do cleanup */
               SB_SUBTESTFAIL()
            }
            else
            {
               /* primitive successful */
               switch (type)
               {
                  case STSBGEN:
                     if(specCfg == GEN)
                     {
                        setBit(&sbAccCb.curTst.bConfigMask, BIT0);
                     }
                     break;
                  case STSBSCTSAP:
                     switch (specCfg)
                     {
                        case SAP_1:
                        /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
                        case SAP_4:
                        case SAP_5:
#endif /* SB_RUG */
                           setBit(&sbAccCb.curTst.bSctSapCfgMask, BIT0);
                           break;
                        case SAP_2:
                           setBit(&sbAccCb.curTst.bSctSapCfgMask, BIT1);
                           break;
                        case SAP_3:
                           setBit(&sbAccCb.curTst.bSctSapCfgMask, BIT2);
                           break;
                        default:
                           break;
                     }
                     if( (isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT0) == TRUE)&&
                         ( isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT1) == TRUE)&&
                         ( isBitSet(sbAccCb.curTst.bSctSapCfgMask, BIT2) == TRUE) )
                     {
                        setBit(&sbAccCb.curTst.bConfigMask, BIT1);
                     }
                     break;
                  case STSBTSAP:
                        /* sb046.102: Multiple IP address per Endp */
                     if ((specCfg == SAP_1) || (specCfg == SAP_6))
                     {
                        setBit(&sbAccCb.curTst.bTSapCfgMask, BIT0);
                     }
                     else if (specCfg == SAP_2)
                     {
                        setBit(&sbAccCb.curTst.bTSapCfgMask, BIT1);
                     }
                     /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
                     else if ((specCfg == SAP_4) || (specCfg == SAP_4))
                     {
                        setBit(&sbAccCb.curTst.bTSapCfgMask, BIT0);
                     }
#endif /* SB_RUG */
                     if( (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT0) == TRUE)&&
                         (isBitSet(sbAccCb.curTst.bTSapCfgMask, BIT1) == TRUE) )
                     {
                        setBit(&sbAccCb.curTst.bConfigMask, BIT2);
                     }
                     break;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE                     
                  case STSBPATHPROF:   
                     setBit(&sbAccCb.curTst.bConfigMask, BIT1);
                     break;
                  case STSBDSTADDR:
                     setBit(&sbAccCb.curTst.bConfigMask, BIT2);
                     break;
#endif                     
                  default:
                     sbAccDispErrTstRslt("sbSendConfigReq", type,
                                          ACC_EVT_CFG_CFM, status, reason);
                     SB_SUBTESTFAIL()    /* Problem - do cleanup */
                     break;
               }  /* end switch */
            } /* end primitive successful */
         } /*end primitive received */
         sbAccCb.curTst.subTest = 1;
         sbAccCb.curTst.state = 0;   /* Reset for next subtests*/
         break;
      }
   } /* end switch */
   RETVOID;
} /* end sbSendConfigReq */

/*
*
*       Fun:   sbSendSctBindReq
*
*       Desc:  Send a bind request and checks that
*              the confirm succeeds.                          .
*
*       Ret:   None
*
*       Notes: Used as pretest
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void sbSendSctBndReq
(
SuId suId,     /* Service user Id */
SpId spId     /* Service provider Id - SAP Id */
)
#else
PUBLIC  void sbSendSctBndReq(suId, spId)
SuId suId;     /* Service user Id */
SpId spId;     /* Service provider Id - SAP Id */
#endif
{
   PRIVATE  SbOperQElm  oper;
   PRIVATE  SctStatus   status;
   Reason      reason;
   S16         ret;
   PRIVATE  SbMgmtQElm  mgmt;

   TRC2(sbSendSctBndReq)

      ret = ROK;


   switch (sbAccCb.curTst.state)
   {
      case 0:  /* Send a BndReq */
         ItLiSctBndReq(&sbAccCb.itPst, suId, spId);
         sbAccCb.curTst.state++;
         break;
      case 1:  /* Dequeue BndCfm and verify the parameters */
         sbAccVfyMsg(&status);
         if (status == WAIT)
         {
            /* wait for message to reach the queue */
            RETVOID;
         }
         else if (status == TIMEOUT)
         {
            sbAccDispErrTstRslt("sbSendSctBndReq", (U8)spId,
                                ACC_EVT_BND_CFM, TIMEOUT_ON_PRIM, 0);
            SB_SUBTESTFAIL()   /* Problem - do cleanup */
         }
         else
         {
            /*receive result */
            /* fill the oper */
            oper.it.suId = suId;
            oper.it.result = CM_BND_OK;
            ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_BND_CFM, &status, &reason);
            if (ret == RFAILED)
            {
               sbAccDispErrTstRslt("sbSendSctBndReq", (U8)spId,
                                   ACC_EVT_BND_CFM, status, reason);
               SB_SUBTESTFAIL()   /* Problem - do cleanup */
            }
            else /* successfully received primitive */
            {
               /* Set bit to indicate which SAP bound successfully */
               switch (spId)
               {
                  case SPID_0:
                     setBit(&sbAccCb.curTst.bSapMask, BIT0);
                     break;
                  case SPID_1:
                     setBit(&sbAccCb.curTst.bSapMask, BIT1);
                     break;
                  case SPID_2:
                     setBit(&sbAccCb.curTst.bSapMask, BIT2);
                     break;
                  default:
                     sbAccDispErrTstRslt("sbSendSctBndReq ", (U8)spId,
                                         ACC_EVT_BND_CFM, status, reason);
                     SB_SUBTESTFAIL()   /* Problem - do cleanup */
                     break;
               }  /* end switch */
            } /* end else of if(ret == RFAILED) */
          }    /* end else: received result  */
          sbAccCb.curTst.state = 0;   /* Reset for subtests*/
          sbAccCb.curTst.subTest = 1;
          break;
   } /* end switch */

   RETVOID;
} /* end sbSendSctBndReq */

/*
*       Fun:   sbSendHitBndReq
*
*       Desc:  Binding a specific TSAP and Initializing IP server connection
*       Ret:   ROK
*
*       Group: Binding/Unbinding
*
*       Notes: Used as pretest.
*
*       File:  sb_act2.c
*
*/

#ifdef ANSI
PUBLIC  void sbSendHitBndReq
(
SuId suId,     /* Service user Id */
SpId spId     /* Service provider Id - SAP Id */
)
#else
PUBLIC  void sbSendHitBndReq(suId, spId)
SuId suId;     /* Service user Id */
SpId spId;     /* Service provider Id - SAP Id */
#endif
{
   SbAccMsgQElm   *msg;
   PRIVATE        SbOperQElm     oper;
   SctStatus      status;
   S16            ret;
   PRIVATE        SbMgmt         sbMgmt;
   PRIVATE        SbMgmtQElm     mgmt;
   Reason         reason;

   TRC2(sbSendHitBndReq)

      ret = ROK;
   /* Do test */
   switch(sbAccCb.curTst.state)   /* Switch #1 */
   {   /* strt switch(state) */
      case 0:
         sbMgmt.hdr.elmId.elmnt =  STSBTSAP;
         sbMgmt.t.cntrl.action =  ABND_ENA;

         switch (sbAccCb.curTst.subTest)
         {
            case 1:
               if (( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == FALSE)&&
                   ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == FALSE))
               {
                  sbMgmt.t.cntrl.sapId =  suId;
                  sbMgmt.hdr.transId = 10101;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE         
         sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif
                  sbAccCb.curTst.curTransId = sbMgmt.hdr.transId;
                  setResponse(&sbMgmt.hdr.response);
                  (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
                   /* reply event expected */
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
               }
               break;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
	case 2:
               (Void) HiUiHitBndCfm(&sbAccCb.hiPst, suId, CM_BND_OK);
	       if ( sbAccCb.useDnsFlag == TRUE)
               {
                 sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;
	       }
               else
               {
                  sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
	       }
         break;
         case 3:
	       if ( sbAccCb.useDnsFlag == TRUE)
               {
                 (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                    suId, sbAccCb.curTst.suConId,\
                                    sbAccCb.curTst.spConId,\
                                    &sbAccCb.curTst.localTAddr);
                 sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;
	      }
	break;
#else
            case 2:
               (Void) HiUiHitBndCfm(&sbAccCb.hiPst, suId, CM_BND_OK);
               sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;
                                       /* reply event expected */
               break;
            case 3:
               (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                    suId, sbAccCb.curTst.suConId,\
                                    sbAccCb.curTst.spConId,\
                                    &sbAccCb.curTst.localTAddr);
           if(sbAccCb.curTst.localTAddr.type == CM_NETADDR_IPV4)
           {
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
                  sprintf(prntBuf, "HiUiConCfm(addr(%u), port(%u))\n",
                          sbAccCb.curTst.localTAddr.u.ipv4TptAddr.address,
                          sbAccCb.curTst.localTAddr.u.ipv4TptAddr.port);
#else
                  sprintf(prntBuf, "HiUiConCfm(addr(%lu), port(%u))\n",
                          sbAccCb.curTst.localTAddr.u.ipv4TptAddr.address,
                          sbAccCb.curTst.localTAddr.u.ipv4TptAddr.port);
#endif                  
                  SPrint(prntBuf);
           }
           else if(sbAccCb.curTst.localTAddr.type == CM_NETADDR_IPV6)
           {
                  sprintf(prntBuf, "HiUiConCfm(port(%u))\n",
                          sbAccCb.curTst.localTAddr.u.ipv6TptAddr.port);
                  SPrint(prntBuf);
           }
               sbAccCb.curTst.evtType = ACC_EVT_SERVOPEN_REQ;
                                        /* expected result */
               break;
#endif
            default:
               sbAccDispErrTstRslt("O.102.01: ", 0,0, NO_SUBTEST,0);
               SB_SUBTESTFAIL()
               break;
         }     /* end switch (subtest) */
         sbAccCb.curTst.state++;
         break;    /* end case 0*/

         /* Dequeue response and test */
         case 1:

            sbAccVfyMsg(&status);
            if(status == WAIT)
            {
               /* wait for message to reach the queue */
               RETVOID;
            }
            else if (status == TIMEOUT)
            {
               sbAccDispErrTstRslt("Pretest: HitBind ", sbAccCb.curTst.subTest,
                                   sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               SB_SUBTESTFAIL()   /* Problem - do cleanup */
            }
            else
            {
               reason = LCM_REASON_NOT_APPL;
               /* strt primitive received */
               switch (sbAccCb.curTst.subTest)
               {
                  case 1:
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_BND_REQ)
                     {
                        oper.hi.suId =  suId;
                        oper.hi.spId =  spId;
                        ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_BND_REQ,\
                                          &status, &reason);
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                     }
                     else if (msg->evntType == ACC_EVT_CNTRL_CFM)
                     {
                        mgmt.cfm.status = LCM_PRIM_OK_NDONE;
                        mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                        mgmt.transId = sbAccCb.curTst.curTransId;
                        ret = sbLsbChkCfm(&mgmt, &status, &reason, \
                                          ACC_EVT_CNTRL_CFM);
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     break;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
	case 2:
	       if ( sbAccCb.useDnsFlag == TRUE)
	       {
		  oper.hi.spId = spId;
                  ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ,\
                                       &status, &reason);
		}
	   break;
	case 3:
                  mgmt.cfm.status = LCM_PRIM_OK;
                  mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                  ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                       ACC_EVT_CNTRL_CFM);
                  setBit(&sbAccCb.curTst.bTickMask, BIT0); 
                  setBit(&sbAccCb.curTst.bTickMask, BIT1);
	  break;
#else
                  case 2:
                     oper.hi.spId = spId;
                     ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ,\
                                       &status, &reason);
                     break;
                  case 3:
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                     {
                        oper.hi.spId = spId;
                        ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ,\
                                          &status, &reason);
                        /* assoc_1.suConId = sbAccCb.curTst.suConId;*/
                     }
                     if (msg->evntType == ACC_EVT_CNTRL_CFM)
                     {
                        mgmt.cfm.status = LCM_PRIM_OK;
                        mgmt.cfm.reason = LCM_REASON_NOT_APPL;
                        ret = sbLsbChkCfm(&mgmt, &status, &reason,\
                                          ACC_EVT_CNTRL_CFM);
                        setBit(&sbAccCb.curTst.bTickMask, BIT0);
                        setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     }
                     break;
#endif
               }/* end case curtstnum #2 */

               if(ret == RFAILED)
               {
                  /* error in received primitive */
                  sbAccDispErrTstRslt("HitBndReq: ", sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  SB_SUBTESTFAIL()   /* Problem - do cleanup */
               }
               else
               {
                  /*strt success*/
                  if ( (sbAccCb.curTst.subTest==2)||
                       ( (isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&
                         (isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) ) )
                  {

                     sbAccCb.curTst.subTest++;
                     sbAccCb.curTst.bTickMask = 0;

                     if ( (sbAccCb.curTst.subTest == 4) )
                     {
                        switch (suId)
                        {     /* document the bound TSAPs */
                           case 0:
                              setBit(&sbAccCb.curTst.bTSapMask, BIT0);
                              break;
                           case 1:
                              setBit(&sbAccCb.curTst.bTSapMask, BIT1);
                              break;
                        }
                        sbAccCb.curTst.subTest = 1;
                     }
                  } /*end incr subtest */
               } /* end success */
            }  /* end primitive received */
            sbAccCb.curTst.state = 0;   /* For delete config to work */
            break;    /* case 1 */

   } /* end switch(state) */

   RETVOID;
}  /* end sbSendHitBndReq */

/*
*
*       Fun:   sbSendEndpOpenReq
*
*       Desc:  Send a opening of an endpoint request and
*              checks that the confirm succeeds
*
*       Ret:   None
*
*       Notes: Used as pretest
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void sbSendEndpOpenReq
(
SbAccAssoc        *assoc                 /* copy the association structure */
)
#else
PUBLIC  void sbSendEndpOpenReq(assoc)
SbAccAssoc       *assoc;                 /* copy the association structure */
#endif
{
   PRIVATE   SbMgmtQElm  mgmt;
   PRIVATE   SbOperQElm  oper;
   SctStatus   status;
   Reason      reason;
/*sb033.103 : Initialized ret by FALSE to remove a warning for 64 bit compilation*/   
   S16         ret = ROK;
   /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
   PRIVATE     SctNetAddrLst intfNAddrLst;
#endif
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SbAccMsgQElm    *msg;
#endif

   TRC2(sbSendEndpOpenReq)

   switch(sbAccCb.curTst.state)   /* Switch #1 */
   {   /* strt switch(state) */
      case 0:
         switch (sbAccCb.curTst.subTest)
         {
            case 1:
#ifdef SCT_ENDP_MULTI_IPADDR
              intfNAddrLst.nmb = 1;
              SB_CPY_NADDR(&(intfNAddrLst.nAddr[0]), &(assoc->localNAddr))
             (Void) ItLiSctEndpOpenReq(&sbAccCb.itPst, \
                                    assoc->spId, assoc->suEndpId,\
                                    assoc->localPort, &intfNAddrLst);
#else
             (Void) ItLiSctEndpOpenReq(&sbAccCb.itPst, \
                                    assoc->spId, assoc->suEndpId,\
                                    assoc->localPort, &assoc->localNAddr);
#endif /* SCT_ENDP_MULTI_IPADDR */
	     break;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
             case 2:
		   (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                    assoc->suId, sbAccCb.curTst.suConId,\
                                    sbAccCb.curTst.spConId,\
                                    &sbAccCb.curTst.localTAddr);

               break;
#endif
            default:
               SB_SUBTESTFAIL()
               break;
         }     /* end switch (subtest) */
         sbAccCb.curTst.state++;
         break;    /* end case 0*/


         /* Dequeue response and test */
     case 1:

            sbAccVfyMsg(&status);
            if(status == WAIT)
            {
               /* wait for message to reach the queue */
               RETVOID;
            }
            else if (status == TIMEOUT)
            {
               sbAccDispErrTstRslt("Pretest: EndpOpen ", sbAccCb.curTst.subTest,
                                   sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
               SB_SUBTESTFAIL()   /* Problem - do cleanup */
            }
            else
            {
               reason = LCM_REASON_NOT_APPL;
               /* strt primitive received */
               switch (sbAccCb.curTst.subTest)
               {
                  case 1:
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                     sbAccPeekMsg(&msg);
                     if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                     {
		      ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                                         , &status, &reason);
                     }
                     break;
                  case 2:
#endif
       		    reason = 0;
                    ret = ROK;
                    oper.it.suId = assoc->suId;
                    oper.it.suEndpId = assoc->suEndpId;
                    oper.it.result = SCT_OK;
                    oper.it.cause = SCT_CAUSE_NOT_APPL;
                    ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ENDPOPEN_CFM,\
                                                        &status, &reason);
                   /* save the endpoint ID received from the SCTP */
                  assoc->spEndpId = oper.it.spEndpId;
                     break;
               }/* end case curtstnum #2 */

               if(ret == RFAILED)
               {
                  /* error in received primitive */
                  sbAccDispErrTstRslt("EndpOpenReq: ", sbAccCb.curTst.subTest,
                                       sbAccCb.curTst.evtType, status, reason);
                  SB_SUBTESTFAIL()   /* Problem - do cleanup */
               }
               else
               {
                  /*strt success*/
                     sbAccCb.curTst.subTest++;
                     sbAccCb.curTst.bTickMask = 0;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                     if ( (sbAccCb.curTst.subTest == 3) )
#else
                     if ( (sbAccCb.curTst.subTest == 2) )
#endif
                     {
		       switch (assoc->suEndpId)
                       {
                         case SUENDPID_0:
                           setBit(&sbAccCb.curTst.bEndpMask, BIT0);
                           break;
                         case SUENDPID_1:
                           setBit(&sbAccCb.curTst.bEndpMask, BIT1);
                           break;
                         case SUENDPID_2:
                           setBit(&sbAccCb.curTst.bEndpMask, BIT3);
                           break;
                        default:
                          sbAccDispErrTstRslt("sbSendEndpOpenReq: Non-defined endpoint ", 0,
							ACC_EVT_ENDPOPEN_CFM,status,reason);
                     break;
                    }  /* end switch */

                        sbAccCb.curTst.subTest = 1;
                }
              } /* end success */
            }  /* end primitive received */
            sbAccCb.curTst.state = 0;   /* For delete config to work */
            break;    /* case 1 */
   } /* end switch(state) */

   RETVOID;
} /* end sbSendEndpOpenReq */

/* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
/*
*
*       Fun:   sbSendMulEndpOpenReq
*
*       Desc:  Send a opening of an endpoint request and
*              checks that the confirm succeeds
*
*       Ret:   None
*
*       Notes: Used as pretest
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void sbSendMulEndpOpenReq
(
SbAccAssoc        *assoc,                /* copy the association structure */
U8                endpId
)
#else
PUBLIC  void sbSendMulEndpOpenReq(assoc, endpId)
SbAccAssoc       *assoc;                 /* copy the association structure */
U8                endpId;
#endif
{
   PRIVATE   SbMgmtQElm  mgmt;
   PRIVATE   SbOperQElm  oper;
   SctStatus   status;
   Reason      reason;
   S16         ret;
   PRIVATE     SctNetAddrLst intfNAddrLst;
   U8          i;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SbAccMsgQElm    *msg;
#endif

   TRC2(sbSendMulEndpOpenReq)

   /* enter MulEndpOpenuration */
   switch (sbAccCb.curTst.state)
   {
      case 0:  /* Snd EndpOpen request */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
       	 switch (sbAccCb.curTst.subTest)
         {
	  case 1:
#endif
             intfNAddrLst.nmb = 2;
             if (endpId == 1)
             {
                for (i = 0; (i < 2 ); i++)
                {
                  /* IPV4 addresses  */
                 intfNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;
                 intfNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_1[i];
                }
               (Void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                       assoc->spId, assoc->suEndpId,
                                       assoc->localPort, &intfNAddrLst);
             }
             else if (endpId == 2)
             {
               for (i = 0; (i < 2 ); i++)
               {
                   /* IPV4 addresses  */
                  intfNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;
                  intfNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_2[i];
               }
               (Void) ItLiSctEndpOpenReq(&sbAccCb.itPst,
                                         assoc->spId, assoc->suEndpId,
                                         assoc->localPort, &intfNAddrLst);
            }
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         break;
         case 2:
	    (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                  assoc->suId, sbAccCb.curTst.suConId,\
                                  sbAccCb.curTst.spConId,\
                                  &sbAccCb.curTst.localTAddr);

            break;
	 case 3:
	    (Void) HiUiHitConCfm(&sbAccCb.hiPst, \
                                 assoc->suId, sbAccCb.curTst.suConId,\
                                 sbAccCb.curTst.spConId,\
                                 &sbAccCb.curTst.localTAddr);
	   break;
        }
#endif
        sbAccCb.curTst.state++;
        break;

      case 1:  /* Confirm for EndpOpen */
         /* verify if msg in queue */
         sbAccVfyMsg(&status);
         if (status == WAIT)
         {
            /* wait for message to reach the queue */
            RETVOID;
         }
         else if (status == TIMEOUT)
         {
            sbAccDispErrTstRslt("sbSendMulEndpOpenReq", 0,
                                 ACC_EVT_ENDPOPEN_CFM, TIMEOUT_ON_PRIM, 0);
            SB_SUBTESTFAIL()   /* Problem - do cleanup */
         }
         else
         {
            /*primitive received */
            /* fill the oper */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT 
	    switch (sbAccCb.curTst.subTest)
           {
             case 1:
                 sbAccPeekMsg(&msg);
                 if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                 {
                    ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                                       , &status, &reason);
                 }
                 break;
             case 2:
                 sbAccPeekMsg(&msg);
                 if (msg->evntType == ACC_EVT_SERVOPEN_REQ)
                 {
                    ret = sbHitChkReq(&oper, &mgmt, ACC_EVT_SERVOPEN_REQ\
                                                      , &status, &reason);
                 }
                 break;
	    case 3:
#endif
               reason = 0;
               ret = ROK;
               oper.it.suId = assoc->suId;
               oper.it.suEndpId = assoc->suEndpId;
               oper.it.result = SCT_OK;
               oper.it.cause = SCT_CAUSE_NOT_APPL;
               ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ENDPOPEN_CFM,\
                                &status, &reason);
              /* save the endpoint ID received from the SCTP */
              assoc->spEndpId = oper.it.spEndpId;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT 
	      break;
	   }
#endif

           if (ret == RFAILED)
           {
              sbAccDispErrTstRslt("sbSendMulEndpOpenReq", 0,
                                   ACC_EVT_ENDPOPEN_CFM,status,reason);
              SB_SUBTESTFAIL()   /* Problem - do cleanup */
           }
           else
           {
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
               sbAccCb.curTst.subTest++;
               sbAccCb.curTst.bTickMask = 0;
              /* Set bit to indicate which endpoint was opened successfully */
              if( sbAccCb.curTst.subTest == 4)
	      { 
#endif        
                 switch (oper.it.suEndpId)
                 {
                    case SUENDPID_0:
                       setBit(&sbAccCb.curTst.bEndpMask, BIT0);
                       break;
                    case SUENDPID_1:
                       setBit(&sbAccCb.curTst.bEndpMask, BIT1);
                       break;
                    case SUENDPID_2:
                       setBit(&sbAccCb.curTst.bEndpMask, BIT3);
                      break;
                    default:
                       sbAccDispErrTstRslt("sbSendMulEndpOpenReq: Non-defined endpoint ", 0,
                                            ACC_EVT_ENDPOPEN_CFM,status,reason);
                       break;
                 }  /* end switch */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
              sbAccCb.curTst.subTest = 1;
              }
#endif
            } /* primitive successfully received */
         }  /* primitive received */
         sbAccCb.curTst.state = 0;   /* For delete config to work */
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT 
         sbAccCb.curTst.subTest = 1;
#endif
         break;
   } /* end switch */

   RETVOID;
} /* end sbSendMulEndpOpenReq */
#endif /* SCT_ENDP_MULTI_IPADDR */

/*
*
*       Fun:   setupAssoc
*
*       Desc:  Setup the association parameters
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC void setupAssoc
(
SbAccAssoc *assoc,
U8         assocNum
)
#else
PUBLIC void setupAssoc(assoc, assocNum)
SbAccAssoc *assoc;
U8         assocNum;
#endif
{
   /*SbGenCfg *genCfg; */
   U8       i;
   U8       ipv6NAddrCount;
   /* ASSOC_1 */
   if ( ( isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == FALSE ) &&
        (assocNum == ASSOC_1) )
   {
      /* SCT parameters */
      assoc->spId = SPID_0;
      assoc->suId = SUID_0;
      SB_BIND_SCTSAP(assoc->suId, assoc->spId, BIT0)

      if (isBitSet(sbAccCb.curTst.bSapMask, BIT0) == TRUE)
      {
         assoc->suEndpId = SUENDPID_0;
         if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
         {
            SB_SETUP_CMNETADDR(assoc->localNAddr,  localNAddrLst_1[0])
         }
         else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
         {
             assoc->localNAddr.type = CM_NETADDR_IPV6;
            CPY_ACC_ASSOC1_LOCAL_IPV6(assoc->localNAddr.u.ipv6NetAddr, 0)
         }
         assoc->localPort = LOCALPORT_0;
         SB_OPEN_ENDP(assoc, BIT0)
         if (isBitSet(sbAccCb.curTst.bEndpMask, BIT0) == TRUE)
         {
            assoc->suAssocId =  SUASSOCID_0;
            assoc->peerPort =  PEERPORT_0;
            /* RFC 4460 -- IPW fix*/
            assoc->outStrms = 3;
        if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
        {
               SB_SETUP_CMNETADDR((assoc->priPeerNAddr), peerNAddrLst_1[2] )
               SB_SETUP_SCTNETADDRLST(assoc->peerNAddrLst, peerNAddrLst_1)
        }
        else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
        {
           assoc->priPeerNAddr.type = CM_NETADDR_IPV6;
           CPY_ACC_ASSOC1_PEER_IPV6(assoc->priPeerNAddr.u.ipv6NetAddr, 2)
           assoc->peerNAddrLst.nmb = 5;
           for(ipv6NAddrCount=0; ipv6NAddrCount<5; ipv6NAddrCount++)
           {
              assoc->peerNAddrLst.nAddr[ipv6NAddrCount].type = CM_NETADDR_IPV6;
              CPY_ACC_ASSOC1_PEER_IPV6(assoc->peerNAddrLst.nAddr[ipv6NAddrCount].u.ipv6NetAddr, ipv6NAddrCount)
           }
       }
            /*SB_SETUP_SCTNETADDRLST(assoc->localNAddrLst, localNAddrLst_1)*/

            assoc->localNAddrLst.nmb = 2;
        if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
        {
               for (i = 0; (i < 2); ++i) /* SB_VER13  fixed the bug of i<=2 */
               {
                  assoc->localNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;  /* IPV4 addresses  */
                  assoc->localNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_1[i];
               }
        }
        else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
        {
               for (i = 0; (i < 2); ++i) /* SB_VER13  fixed the bug of i<=2 */
               {
                  assoc->localNAddrLst.nAddr[i].type = CM_TPTADDR_IPV6;  /* IPV6 addresses  */
                  CPY_ACC_ASSOC1_LOCAL_IPV6(assoc->localNAddrLst.nAddr[i].u.ipv6NetAddr, i)
               }
        }
        if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
        {
               SB_SETUP_CMTPTADDR(assoc->localTAddr,\
                                 (assoc->localNAddr.u.ipv4NetAddr),\
                                 assoc->localPort)
               SB_SETUP_CMTPTADDR(assoc->peerTAddr,\
                                  (assoc->priPeerNAddr.u.ipv4NetAddr),\
                                  assoc->peerPort) 
#ifdef LOCAL_INTF
          assoc->localIf.intfPrsnt = TRUE;   /*IPV6 change */
          assoc->localIf.localIf = 1;
          assoc->localIf.localIfAddr.type = CM_NETADDR_IPV4;
          assoc->localIf.localIfAddr.u.ipv4NetAddr = assoc->localNAddr.u.ipv4NetAddr;
#endif
        }
        else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
        {
               SB_SETUP_CMTPTADDR(assoc->localTAddr,\
                                 (assoc->localNAddr.u.ipv6NetAddr),\
                                 assoc->localPort)
               SB_SETUP_CMTPTADDR(assoc->peerTAddr,\
                                  (assoc->priPeerNAddr.u.ipv6NetAddr),\
                                  assoc->peerPort)
#ifdef LOCAL_INTF
            assoc->localIf.intfPrsnt = TRUE;    /*IPV6 change */
            assoc->localIf.localIf = 2;
            assoc->localIf.localIfAddr.type = CM_NETADDR_IPV6;
            cmMemcpy((U8*)assoc->localIf.localIfAddr.u.ipv6NetAddr,(U8*)assoc->localNAddr.u.ipv6NetAddr, CM_IPV6ADDR_SIZE);
#endif
         }
            assoc->suConId = SUCONID_0;
            assoc->spConId = SPCONID_0;
            setBit(&sbAccCb.curTst.bAssocSetupMask, BIT0);
         }  /* end bEndpMask if */
      } /* end bSapMask if */
   } /* end ASSOC_1 if */

   /* ASSOC_2 */
   if ( ( isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT1) == FALSE ) &&
        (assocNum == ASSOC_2) )
   {
      assoc->spId = SPID_1;
      assoc->suId = SUID_1;
      assoc->suEndpId = SUENDPID_1;
      assoc->localPort =  LOCALPORT_1;
      assoc->peerPort =  PEERPORT_1;
      assoc->suAssocId =  SUASSOCID_1;
            /* RFC 4460 -- IPW fix*/
      assoc->outStrms = 3;
      /* assoc->verTag = ACC_INIT_LOCTAG;*/

      SB_SETUP_CMNETADDR(assoc->priPeerNAddr, peerNAddrLst_2[2] )
      SB_SETUP_CMNETADDR(assoc->localNAddr,  localNAddrLst_2[1] )
      SB_SETUP_SCTNETADDRLST(assoc->peerNAddrLst, peerNAddrLst_2)
      /*SB_SETUP_SCTNETADDRLST(assoc->localNAddrLst, localNAddrLst_2)*/

      assoc->localNAddrLst.nmb = 2;
      for (i = 0; (i < 2); ++i)    /* modifed after insure compilation "=" removed  */
      {
         assoc->localNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;  /* IPV4 addresses  */
         assoc->localNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_2[i];
      }

      /* set up transport addresses for the HIT primitives */
      SB_SETUP_CMTPTADDR(assoc->localTAddr,\
                         (assoc->localNAddr.u.ipv4NetAddr),\
                         assoc->localPort)
      SB_SETUP_CMTPTADDR(assoc->peerTAddr,\
                         (assoc->priPeerNAddr.u.ipv4NetAddr),\
                         assoc->peerPort)
#ifdef LOCAL_INTF
      assoc->localIf.intfPrsnt = TRUE;   /*IPV6 change */
      assoc->localIf.localIf = 1;
      assoc->localIf.localIfAddr.type = CM_NETADDR_IPV4;
      assoc->localIf.localIfAddr.u.ipv4NetAddr = assoc->localNAddr.u.ipv4NetAddr;
#endif
      assoc->spConId = SPCONID_1;

      SB_BIND_SCTSAP(assoc->suId, assoc->spId, BIT1)
      assoc->suConId = SUCONID_1;

      if (isBitSet(sbAccCb.curTst.bSapMask, BIT1) == TRUE)
      {
         SB_OPEN_ENDP(assoc, BIT1)
         if (isBitSet(sbAccCb.curTst.bEndpMask, BIT1) == TRUE)
         {
            setBit(&sbAccCb.curTst.bAssocSetupMask, BIT1);
         }
      }
   } /* end ASSOC_2 if */

   /* ASSOC_3 */
   if ( ( isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT3) == FALSE ) &&
        (assocNum == ASSOC_3) )
   {
      /* SCT parameters */
      assoc->spId = SPID_0;
      assoc->suId = SUID_0;

      if (isBitSet(sbAccCb.curTst.bSapMask, BIT0) == TRUE)
      {
         assoc->suEndpId = SUENDPID_2;
         SB_SETUP_CMNETADDR(assoc->localNAddr,  localNAddrLst_1[1])
         assoc->localPort = LOCALPORT_0;
         SB_OPEN_ENDP(assoc, BIT3)

         if (isBitSet(sbAccCb.curTst.bEndpMask, BIT3) == TRUE)
         {
            assoc->suAssocId =  SUASSOCID_2;
            assoc->peerPort =  PEERPORT_1;
            /* RFC 4460 -- IPW fix*/
            assoc->outStrms = 3;
            SB_SETUP_CMNETADDR((assoc->priPeerNAddr), peerNAddrLst_2[2] )
            SB_SETUP_SCTNETADDRLST(assoc->peerNAddrLst, peerNAddrLst_2)

            assoc->localNAddrLst.nmb = 2;
            for (i = 0; (i < 2); ++i) /* SB_VER13  fixed the bug of i<=2 */
            {
               assoc->localNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;  /* IPV4 addresses  */
               assoc->localNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_1[i];
            }

            /* set up transport addresses for the HIT primitives */
            SB_SETUP_CMTPTADDR(assoc->localTAddr,\
                               (assoc->localNAddr.u.ipv4NetAddr),\
                               assoc->localPort)
            SB_SETUP_CMTPTADDR(assoc->peerTAddr,\
                               (assoc->priPeerNAddr.u.ipv4NetAddr),\
                               assoc->peerPort)
#ifdef LOCAL_INTF
            assoc->localIf.intfPrsnt = TRUE;    /*IPV6 change */
            assoc->localIf.localIf = 1;
            assoc->localIf.localIfAddr.type = CM_NETADDR_IPV4;
            assoc->localIf.localIfAddr.u.ipv4NetAddr = assoc->localNAddr.u.ipv4NetAddr;
#endif
            assoc->suConId = SUCONID_1;
            assoc->spConId = SPCONID_1;
            setBit(&sbAccCb.curTst.bAssocSetupMask, BIT3);
         }  /* end bEndpMask if */
      } /* end bSapMask if */
   } /* end ASSOC_3 if */

   /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
   /* ASSOC_4 */
   if ( ( isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT0) == FALSE ) &&
        (assocNum == ASSOC_4) )
   {
      /* SCT parameters */
      assoc->spId = SPID_0;
      assoc->suId = SUID_0;
      SB_BIND_SCTSAP(assoc->suId, assoc->spId, BIT0)

      if (isBitSet(sbAccCb.curTst.bSapMask, BIT0) == TRUE)
      {
         assoc->suEndpId = SUENDPID_0;
         if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
         {
            SB_SETUP_CMNETADDR(assoc->localNAddr,  localNAddrLst_1[0])
         }
         else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
         {
             assoc->localNAddr.type = CM_NETADDR_IPV6;
            CPY_ACC_ASSOC1_LOCAL_IPV6(assoc->localNAddr.u.ipv6NetAddr, 0)
         }
         assoc->localPort = LOCALPORT_0;
         if((isBitSet(sbAccCb.curTst.bEndpMask, BIT0) == FALSE ))
         {
            sbSendMulEndpOpenReq(assoc, 1);
         }

         if (isBitSet(sbAccCb.curTst.bEndpMask, BIT0) == TRUE)
         {
            assoc->suAssocId =  SUASSOCID_0;
            assoc->peerPort =  PEERPORT_0;
            /* RFC 4460 -- IPW fix*/
            assoc->outStrms = 3;
        if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
        {
               SB_SETUP_CMNETADDR((assoc->priPeerNAddr), peerNAddrLst_1[2] )
               SB_SETUP_SCTNETADDRLST(assoc->peerNAddrLst, peerNAddrLst_1)
        }
        else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
        {
           assoc->priPeerNAddr.type = CM_NETADDR_IPV6;
           CPY_ACC_ASSOC1_PEER_IPV6(assoc->priPeerNAddr.u.ipv6NetAddr, 2)
           assoc->peerNAddrLst.nmb = 5;
           for(ipv6NAddrCount=0; ipv6NAddrCount<5; ipv6NAddrCount++)
           {
              assoc->peerNAddrLst.nAddr[ipv6NAddrCount].type = CM_NETADDR_IPV6;
              CPY_ACC_ASSOC1_PEER_IPV6(assoc->peerNAddrLst.nAddr[ipv6NAddrCount].u.ipv6NetAddr, ipv6NAddrCount)
           }
       }
            /*SB_SETUP_SCTNETADDRLST(assoc->localNAddrLst, localNAddrLst_1)*/

            assoc->localNAddrLst.nmb = 2;
        if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
        {
               for (i = 0; (i < 2); ++i) /* SB_VER13  fixed the bug of i<=2 */
               {
                  assoc->localNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;  /* IPV4 addresses  */
                  assoc->localNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_1[i];
               }
        }
        else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
        {
               for (i = 0; (i < 2); ++i) /* SB_VER13  fixed the bug of i<=2 */
               {
                  assoc->localNAddrLst.nAddr[i].type = CM_TPTADDR_IPV6;  /* IPV6 addresses  */
                  CPY_ACC_ASSOC1_LOCAL_IPV6(assoc->localNAddrLst.nAddr[i].u.ipv6NetAddr, i)
               }
        }
        if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
        {
               SB_SETUP_CMTPTADDR(assoc->localTAddr,\
                                 (assoc->localNAddr.u.ipv4NetAddr),\
                                 assoc->localPort)
               SB_SETUP_CMTPTADDR(assoc->peerTAddr,\
                                  (assoc->priPeerNAddr.u.ipv4NetAddr),\
                                  assoc->peerPort)
#ifdef LOCAL_INTF
          assoc->localIf.intfPrsnt = TRUE;   /*IPV6 change */
          assoc->localIf.localIf = 1;
          assoc->localIf.localIfAddr.type = CM_NETADDR_IPV4;
          assoc->localIf.localIfAddr.u.ipv4NetAddr = assoc->localNAddr.u.ipv4NetAddr;
#endif
        }
        else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
        {
               SB_SETUP_CMTPTADDR(assoc->localTAddr,\
                                 (assoc->localNAddr.u.ipv6NetAddr),\
                                 assoc->localPort)
               SB_SETUP_CMTPTADDR(assoc->peerTAddr,\
                                  (assoc->priPeerNAddr.u.ipv6NetAddr),\
                                  assoc->peerPort)
#ifdef LOCAL_INTF
            assoc->localIf.intfPrsnt = TRUE;    /*IPV6 change */
            assoc->localIf.localIf = 2;
            assoc->localIf.localIfAddr.type = CM_NETADDR_IPV6;
            cmMemcpy((U8*)assoc->localIf.localIfAddr.u.ipv6NetAddr,(U8*)assoc->localNAddr.u.ipv6NetAddr, CM_IPV6ADDR_SIZE);
#endif
         }
            assoc->suConId = SUCONID_0;
            assoc->spConId = SPCONID_0;
            setBit(&sbAccCb.curTst.bAssocSetupMask, BIT0);
         }  /* end bEndpMask if */
      } /* end bSapMask if */
   } /* end ASSOC_4 if */

   /* ASSOC_5 */
   if ( ( isBitSet(sbAccCb.curTst.bAssocSetupMask, BIT1) == FALSE ) &&
        (assocNum == ASSOC_5) )
   {
      /* SCT parameters */
      assoc->spId = SPID_0;
      assoc->suId = SUID_0;

      if (isBitSet(sbAccCb.curTst.bSapMask, BIT0) == TRUE)
      {
         assoc->suEndpId = SUENDPID_1;
         if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
         {
            SB_SETUP_CMNETADDR(assoc->localNAddr,  localNAddrLst_2[0])
         }
         else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
         {
             assoc->localNAddr.type = CM_NETADDR_IPV6;
            CPY_ACC_ASSOC1_LOCAL_IPV6(assoc->localNAddr.u.ipv6NetAddr, 0)
         }
         assoc->localPort = LOCALPORT_0;
         if((isBitSet(sbAccCb.curTst.bEndpMask, BIT1) == FALSE ))
         {
            sbSendMulEndpOpenReq(assoc, 2);
         }

         if (isBitSet(sbAccCb.curTst.bEndpMask, BIT1) == TRUE)
         {
            assoc->suAssocId =  SUASSOCID_0+1;
            assoc->peerPort =  PEERPORT_0;
            /* RFC 4460 -- IPW fix*/
            assoc->outStrms = 3;
        if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
        {
               SB_SETUP_CMNETADDR((assoc->priPeerNAddr), peerNAddrLst_1[2] )
               SB_SETUP_SCTNETADDRLST(assoc->peerNAddrLst, peerNAddrLst_1)
        }
        else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
        {
           assoc->priPeerNAddr.type = CM_NETADDR_IPV6;
           CPY_ACC_ASSOC1_PEER_IPV6(assoc->priPeerNAddr.u.ipv6NetAddr, 2)
           assoc->peerNAddrLst.nmb = 5;
           for(ipv6NAddrCount=0; ipv6NAddrCount<5; ipv6NAddrCount++)
           {
              assoc->peerNAddrLst.nAddr[ipv6NAddrCount].type = CM_NETADDR_IPV6;
              CPY_ACC_ASSOC1_PEER_IPV6(assoc->peerNAddrLst.nAddr[ipv6NAddrCount].u.ipv6NetAddr, ipv6NAddrCount)
           }
       }
            /*SB_SETUP_SCTNETADDRLST(assoc->localNAddrLst, localNAddrLst_1)*/

            assoc->localNAddrLst.nmb = 2;
        if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
        {
               for (i = 0; (i < 2); ++i) /* SB_VER13  fixed the bug of i<=2 */
               {
                  assoc->localNAddrLst.nAddr[i].type = CM_TPTADDR_IPV4;  /* IPV4 addresses  */
                  assoc->localNAddrLst.nAddr[i].u.ipv4NetAddr = localNAddrLst_2[i];
               }
        }
        else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
        {
               for (i = 0; (i < 2); ++i) /* SB_VER13  fixed the bug of i<=2 */
               {
                  assoc->localNAddrLst.nAddr[i].type = CM_TPTADDR_IPV6;  /* IPV6 addresses  */
                  CPY_ACC_ASSOC1_LOCAL_IPV6(assoc->localNAddrLst.nAddr[i].u.ipv6NetAddr, i)
               }
        }
        if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
        {
               SB_SETUP_CMTPTADDR(assoc->localTAddr,\
                                 (assoc->localNAddr.u.ipv4NetAddr),\
                                 assoc->localPort)
               SB_SETUP_CMTPTADDR(assoc->peerTAddr,\
                                  (assoc->priPeerNAddr.u.ipv4NetAddr),\
                                  assoc->peerPort)
#ifdef LOCAL_INTF
          assoc->localIf.intfPrsnt = TRUE;   /*IPV6 change */
          assoc->localIf.localIf = 1;
          assoc->localIf.localIfAddr.type = CM_NETADDR_IPV4;
          assoc->localIf.localIfAddr.u.ipv4NetAddr = assoc->localNAddr.u.ipv4NetAddr;
#endif
        }
        else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
        {
               SB_SETUP_CMTPTADDR(assoc->localTAddr,\
                                 (assoc->localNAddr.u.ipv6NetAddr),\
                                 assoc->localPort)
               SB_SETUP_CMTPTADDR(assoc->peerTAddr,\
                                  (assoc->priPeerNAddr.u.ipv6NetAddr),\
                                  assoc->peerPort)
#ifdef LOCAL_INTF
            assoc->localIf.intfPrsnt = TRUE;    /*IPV6 change */
            assoc->localIf.localIf = 2;
            assoc->localIf.localIfAddr.type = CM_NETADDR_IPV6;
            cmMemcpy((U8*)assoc->localIf.localIfAddr.u.ipv6NetAddr,(U8*)assoc->localNAddr.u.ipv6NetAddr, CM_IPV6ADDR_SIZE);
#endif
         }
            assoc->suConId = SUCONID_1;
            assoc->spConId = SPCONID_1;
            setBit(&sbAccCb.curTst.bAssocSetupMask, BIT1);
         }  /* end bEndpMask if */
      } /* end bSapMask if */
   } /* end ASSOC_4 if */
#endif /* SCT_ENDP_MULTI_IPADDR */

   RETVOID;
} /* end setupAssoc */

/*
*       Fun:   setupAssocSnd
*
*       Desc:  Setup an association for the sending endpoint.
*       Ret:   ROK
*
*       Group: Association
*
*       Notes:
*
*       File:  sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void setupAssocSnd
(
SbAccAssoc    *assoc,
SbAccChunkBld *buildPar
)
#else
PUBLIC  void setupAssocSnd(assoc, buildPar)
SbAccAssoc    *assoc;
SbAccChunkBld *buildPar;
#endif
{
   SbAccMsgQElm  *msg;
   PRIVATE       SbMgmtQElm    mgmt;
   PRIVATE       SbOperQElm    oper;
   SctStatus     status;
   Reason        reason;
   S16           ret;
   Buffer        *mBuf;
   CmIpHdrParm   hdrParm;
   U16           tmp;

   TRC2(setupAssocSnd)
   /* Do test */
   switch(sbAccCb.curTst.state)   /* Switch #1 */
   {
      case 0:
         switch( sbAccCb.curTst.subTest)
         {
            case 1:
/* sb060.102: TOS changes. */
#ifdef SCT3
               (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc->spId,\
                                      assoc->spEndpId, assoc->suAssocId,\
                                      &assoc->priPeerNAddr,assoc->peerPort,\
                                      assoc->outStrms,&assoc->peerNAddrLst, \
                                      &assoc->localNAddrLst, SB_ACC_SCT_TOS, \
                                      (Buffer*)NULLP);
#else
               (void) ItLiSctAssocReq(&sbAccCb.itPst, assoc->spId,\
                                      assoc->spEndpId, assoc->suAssocId,\
                                      &assoc->priPeerNAddr,assoc->peerPort,\
                                      assoc->outStrms,&assoc->peerNAddrLst, \
                                      &assoc->localNAddrLst, (Buffer*)NULLP);
#endif /* SCT3 */
               sbAccCb.curTst.evtType = ACC_EVT_UDAT_REQ;
               /*expected results */
               break;
            case 2:    /* INIT_ACK chunk */
               SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
               tmp = buildPar->outStrms;
               buildPar->outStrms = buildPar->inStrms;
               buildPar->inStrms = tmp;
               buildPar->arwnd = ACC_ARWND_INIT; /* O.401.10 < zero window was hit > */
               buildInitAckChunk(mBuf, buildPar, assoc);
               SB_SETUP_IPHDR_PAR(NOFRAGM)
               (void) HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,\
                                      assoc->suConId, &assoc->peerTAddr,\
                                      &assoc->localTAddr,&hdrParm ,
#ifdef LOCAL_INTF
                                      &assoc->localIf,
#endif
                                      mBuf );
               sbAccCb.curTst.evtType = ACC_EVT_UNKNOWN;  /*expected results */
               break;
            case 3:    /* COOKIE_ACK chunk */
               SGetMsg(DFLT_REGION, DFLT_POOL, (Buffer **) &mBuf);
               buildCookieAckChunk(mBuf, buildPar, assoc);
               SB_SETUP_IPHDR_PAR(NOFRAGM)
               (void)  HiUiHitUDatInd(&sbAccCb.hiPst, SUID_0,\
                                      assoc->suConId, &assoc->peerTAddr,\
                                      &assoc->localTAddr,&hdrParm, 
#ifdef LOCAL_INTF
                                      &assoc->localIf,
#endif
                                      mBuf);
               sbAccCb.curTst.evtType = ACC_EVT_STA_IND;  /*expected results */
               break;
         }
         sbAccCb.curTst.state++;
         break;
         /* Dequeue response and test */
      case 1:
         sbAccVfyMsg(&status);
         if(status == WAIT)
         {
            /* wait for message to reach the queue */
            RETVOID;
         }
         else if (status == TIMEOUT)
         {
            sbAccDispErrTstRslt("AssocSndTst: ", sbAccCb.curTst.subTest,
                                sbAccCb.curTst.evtType, TIMEOUT_ON_PRIM, 0);
            SB_SUBTESTFAIL()   /* Problem - do cleanup */
         }
         else
         {
            ret = ROK;
            reason = LCM_REASON_NOT_APPL;
            /*primitive received */
            switch( sbAccCb.curTst.subTest)
            {
               case 1:
                  /* Check INIT chunk */
                  oper.hi.spId = SPID_0; 
                  buildPar->chunkId = SB_ID_INIT;
                  buildPar->extLifetimeFlg = FALSE;
                  ret = sbHitChkUDatReq(&oper, &mgmt, buildPar,\
                                        assoc, &status);
                  break;
               case 2:
                  sbAccPeekMsg(&msg);
                  if (msg->evntType == ACC_EVT_ASSOC_CFM)
                  {
                     oper.it.suId = assoc->suId;
                     oper.it.suAssocId = assoc->suAssocId;
                     oper.it.peerPort = assoc->peerPort;
                     oper.it.outStrms = assoc->outStrms;
                     ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_ASSOC_CFM,\
                                       &status, &reason);
                     assoc->spAssocId = oper.it.spAssocId;
                     setBit(&sbAccCb.curTst.bTickMask, BIT1);
                  }
                  else if (msg->evntType == ACC_EVT_UDAT_REQ)
                  {
                     /* Check COOKIE chunk */
                     oper.hi.spId = SPID_0;
                     buildPar->chunkId = SB_ID_COOKIE;
                     ret = sbHitChkUDatReq(&oper, &mgmt, buildPar, \
                                           assoc, &status);
                     setBit(&sbAccCb.curTst.bTickMask, BIT0);
                  }
                  else
                  {
                     status = INC_EVNTTYPE;
                     setBit(&sbAccCb.curTst.bTickMask, BIT1);
                     setBit(&sbAccCb.curTst.bTickMask, BIT0);
                     ret = RFAILED;
                  }
                  break;
               case 3:
                  /* Communication Up */
                  oper.it.suId = assoc->suId;
                  oper.it.suAssocId = assoc->suAssocId;
                  oper.it.spAssocId = assoc->spAssocId;
                  oper.it.status = SCT_STATUS_COMM_UP;
                  oper.it.cause = SCT_CAUSE_NOT_APPL;
                  ret = sbSctChkCfm(&oper, &mgmt, ACC_EVT_STA_IND,\
                                    &status, &reason);
                  break;
            } /*end switch */

            if(ret == RFAILED)
            {
               sbAccDispErrTstRslt("AssocSendPreTest :", \
                                   sbAccCb.curTst.subTest,\
                                    sbAccCb.curTst.evtType, status, reason);
               /* Problem - do cleanup */
               SB_SUBTESTFAIL()
            }
            else     /* Subtest successful */
            {
               if (sbAccCb.curTst.subTest == 3 )
               {
                  switch (assoc->suAssocId)
                  {
                     case SUASSOCID_0:
                        setBit(&sbAccCb.curTst.bAssocMask, BIT0);
                        break;
                     case SUASSOCID_1:
                        setBit(&sbAccCb.curTst.bAssocMask, BIT1);
                        break;
                     default:
                        sbAccDispErrTstRslt("sbSendEndpOpenReq: Non-defined endpoint ", 0,
                                            sbAccCb.curTst.evtType,status,\
                                            reason);
                        break;
                  }  /* end switch */
               } /* end subTest == 3 */
            }  /* end Subtest successful */
         } /* end primitive received */
         if (sbAccCb.curTst.subTest == 2)
         {
            if (  ( isBitSet(sbAccCb.curTst.bTickMask, BIT0) == TRUE)&&\
                  ( isBitSet(sbAccCb.curTst.bTickMask, BIT1) == TRUE) )
            {
               sbAccCb.curTst.subTest++;
               sbAccCb.curTst.state = 0;
               sbAccCb.curTst.bTickMask = 0;
            }
         }
         else
         {
            sbAccCb.curTst.subTest++;
            sbAccCb.curTst.state = 0;
            if (sbAccCb.curTst.subTest == 4)
            {
               sbAccCb.curTst.subTest = 1;
            }
         }

         break;
   } /* end switch #1*/

   RETVOID;
}  /* end setupAssocSnd */

/*
*
*       Fun:   sbDisAbleTrace
*
*       Desc:  Send a control request and check the confirm to verify
*              that the message tracing has been disabled.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void sbDisAbleTrace
(
SbMgmt   *sbStaPtr/* configuration structure received from test routine */
)
#else
PUBLIC  void sbDisAbleTrace(sbStaPtr)
SbMgmt   *sbStaPtr;/* configuration structure received from test routine */
#endif
{
   PRIVATE     SbMgmtQElm  mgmt;
   SctStatus   status;
   Reason      reason;
   S16         ret;

   TRC2(sbDisAbleTrace)

   /* enter configuration */
   switch (sbAccCb.curTst.state)
   {
      case 0:  /* Configure configuration */
         sbStaPtr->hdr.transId = sbAccCb.curTst.curTransId = 1100;
         sbStaPtr->t.cntrl.action = ADISIMM;
         sbStaPtr->t.cntrl.subAction = SATRC;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE         
         sbStaPtr->t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif
         sbStaPtr->hdr.elmId.elmnt = STSBGEN;
          setResponse(&sbStaPtr->hdr.response);
         (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, sbStaPtr);
         sbAccCb.curTst.state++;
         break;
      case 1:  /* Confirm for config */
         /* verify if msg in queue */
         sbAccVfyMsg(&status);
         if(status == WAIT)
         {  /* wait for message to reach the queue */
            RETVOID;
         } else if(status == TIMEOUT) {
            sbAccDispErrTstRslt("sbDisAbleTrace", 0,
                                 ACC_EVT_CNTRL_CFM, TIMEOUT_ON_PRIM, 0);
            /* Problem - do cleanup */
            SB_SUBTESTFAIL()
         }
         else
         { /* primitive received */
            /* fill the mgmt */
            ret = ROK;
            mgmt.transId = sbAccCb.curTst.curTransId;
            mgmt.cfm.status = LCM_PRIM_OK;
            mgmt.cfm.reason = LCM_REASON_NOT_APPL;
            ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
            if(ret == RFAILED)
            {
               sbAccDispErrTstRslt("sbDisAbleTrace", 0,
                                    ACC_EVT_CNTRL_CFM, status, reason);
               SB_SUBTESTFAIL()   /* Problem - do cleanup */
            }
            else
            {
               /* message trace is disabled */
               setBit(&sbAccCb.curTst.bTraceMask, BIT0);
            }
             sbAccCb.curTst.subTest = 1;   /* Reset for subtests*/
             sbAccCb.curTst.state = 0;   /* Reset for subtests*/
         } /*end if */
         break;
   } /* end switch */
   RETVOID;
} /* end sbDisAbleTrace */

/*
*
*       Fun:   sbEnableDebugP
*
*       Desc:  Send a control request and check the confirm to verify
*              that the debug printing have been enabled.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void sbEnableDebugP
(
U32      dbgMask           /* debug message */
)
#else
PUBLIC  void sbEnableDebugP(dbgMask)
U32      dbgMask;           /* debug message */
#endif
{
   PRIVATE     SbMgmtQElm  mgmt;
   PRIVATE     SbMgmt      sbMgmt;
   SctStatus   status;
   Reason      reason;
   S16         ret;

   TRC2(sbEnableDebugP)
   /* enter configuration */
   switch (sbAccCb.curTst.state)
   {
      case 0:  /* Configure configuration */
         setResponse(&sbMgmt.hdr.response);
         sbMgmt.hdr.transId = sbAccCb.curTst.curTransId = 15000;/* Trans  Id */
         sbMgmt.t.cntrl.action = AENA;
         sbMgmt.t.cntrl.subAction = SADBG;
#ifdef DEBUGP
         sbMgmt.t.cntrl.dbgMask =  dbgMask;
#else
         UNUSED(dbgMask);
#endif
         sbMgmt.hdr.elmId.elmnt = STSBGEN;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_SATELLITE         
         sbMgmt.t.cntrl.dstAddr.type = CM_NETADDR_NOTPRSNT; 
#endif
         setResponse(&sbMgmt.hdr.response);
         (Void) SmMiLsbCntrlReq(&sbAccCb.smPst, &sbMgmt);
         sbAccCb.curTst.state++;
         break;
      case 1:  /* Confirm for config */
         reason = 0;
         /* verify if msg in queue */
         sbAccVfyMsg(&status);
         if(status == WAIT)
         {  /* wait for message to reach the queue */
            RETVOID;
         } else if(status == TIMEOUT) {
            sbAccDispErrTstRslt("sbEnableDebugP", 0,
                                 ACC_EVT_CNTRL_CFM, TIMEOUT_ON_PRIM, 0);
            /* Problem - do cleanup */
            SB_SUBTESTFAIL()
         } else { /*primitive received */
            /* fill the mgmt */
            ret = ROK;
            mgmt.transId = sbAccCb.curTst.curTransId;
            mgmt.cfm.status = LCM_PRIM_OK;
            mgmt.cfm.reason = LCM_REASON_NOT_APPL;
            ret = sbLsbChkCfm(&mgmt, &status, &reason, ACC_EVT_CNTRL_CFM);
            if(ret == RFAILED)
            {
               sbAccDispErrTstRslt("sbEnableDebugP", 0,
                                    ACC_EVT_CNTRL_CFM, status, reason);

               /* Problem - do cleanup */
               SB_SUBTESTFAIL()
             } else {/* message trace is successfully disabled */
                setBit(&sbAccCb.curTst.bDebugPMask, BIT0);
            }
         } /*end primitive received*/
         sbAccCb.curTst.subTest = 1;
         sbAccCb.curTst.state = 0;   /* Reset for subtests*/
         break;
   } /* end switch */
   RETVOID;
} /* end sbEnableDebugP */

/* Building and checking the chunks */

/*
*
*       Fun:   chkInitChunk
*
*       Desc:  Check that the INIT chunk, received from the sending
*              endpoint is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkInitChunk
(
Buffer         *mBuf,          /* Data received from the SCTP */
SbAccChunkBld  *buildPar,      /* Information for checking the chunks */
SbAccAssoc     *assoc          /* Assocciation structure */
)
#else
PUBLIC  S16 chkInitChunk(mBuf, buildPar, assoc)
Buffer         *mBuf;          /* Data received from the SCTP */
SbAccChunkBld  *buildPar;      /* Information for checking the chunks */
SbAccAssoc     *assoc;         /* Assocciation structure */
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
   U32         adler;
   U16         inStrms;
   U32         initTsn;
   MsgLen      len;
   U8          pkArray[80];
   U16         idx;
   U8          tmpU8;
   U32         tmpU32;
   U16         parSize;
   U16         parType;
   U16         pad;
   U32         i;
#if SB_PRNTSTUFF
   Txt         pb[200];
#endif

   TRC2(chkInitChunk)
   SPrint("Unpacking and Checking the INIT chunk\n");

   idx = 0;
   len = 0;
   if ( mBuf != (Buffer *) NULLP )
   {
      SFndLenMsg(mBuf, &len);
   }
   SRemPreMsgMult(&pkArray[0], len, mBuf);

   /* unpack the common header */
   SB_UNPKU16(srcPort);
   SB_UNPKU16(dstPort);
   SB_UNPKU32(verTag);
   SB_UNPKU32(adler);

   /* unpack the first chunk header, there is only one chunk */
   SB_UNPKU8(chunkId);
   SB_UNPKU8(chunkFlg);
   SB_UNPKU16(chunkLeng);

   if ( ( chunkId != SB_ID_INIT)||(verTag != 0) )
   {
      buildPar->status = INV_VERTAG;
      SB_RLSMEM(mBuf)            /* release memory */
      RETVALUE(RFAILED);         /* Invalid verification Tag and/or chunk ID*/
   }
   /* unpack the fixed parameters */
   SB_UNPKU32(initTag);
   assoc->verTagPeer = initTag;
   SB_UNPKU32(arwnd);
   buildPar->arwnd = arwnd;
   SB_UNPKU16(outStrms);
   buildPar->outStrms = outStrms;
   SB_UNPKU16(inStrms);
   buildPar->inStrms = inStrms;
   SB_UNPKU32(initTsn);
   buildPar->tsn = initTsn;

#if SB_PRNTSTUFF
   SPrint(         "  ========================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)  \n", srcPort, dstPort); \
   SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu) \n", verTag); SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | checksum(%lu) \n", adler); SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | INIT | flag(%d) | chunkLength(%d)\n", chunkFlg, \
           chunkLeng); SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | iTag(%lu) \n",initTag); SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | A_rwnd(%lu) \n",arwnd); SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | outStrm(%d) | inStrm(%d)   \n",outStrms, inStrms);\
   SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | iTSN(%lu) \n",initTsn); SPrint(pb);
#endif

   /* unpack the optional parameters */
   len = (S16)(len - idx);
   /*i = 0;*/

   while ( len > 0 )
   {
      SB_UNPKU16(parType);                 /* opt. param. type */
      SB_UNPKU16(parSize);                 /* opt. param. size */
      len -= 4;
      parSize -= 4;

      /* padding */
      if ( (parSize % 4) != 0 )
      {
         pad = (U16)(4 - (parSize % 4));
      }
      else
      {
         pad = 0;
      }

      switch ( parType )
      {
         case SB_ID_PAR_IPV4:                  /* IPv4 */
            SB_UNPKU32(tmpU32);

#ifdef SB_PRNTSTUFF
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | IPV4 | parSize(%d)\n", parSize+4); SPrint(pb);
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | Address(%lu)\n",tmpU32); SPrint(pb);
#endif
            break;

         case SB_ID_PAR_IPV6:                  /* IPv6 */
            for ( i = 0; i < CM_IPV6ADDR_SIZE; i++ )
            {
               SB_UNPKU8(tmpU8);
            }

#ifdef SB_PRNTSTUFF
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | IPV6 | parSize(%d)\n", parSize+4); SPrint(pb);
            SPrint(         "  -------------------------------------\n");
            SPrint(         "  | Address\n");
#endif
            break;

         case SB_ID_PAR_COOKIE_PRESERVE:       /* Cookie Preservative */
            SB_UNPKU32(tmpU32);

#ifdef SB_PRNTSTUFF
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | COOKIE PRESERVE | parSize(%d)\n", parSize+4);\
            SPrint(pb);
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | cookie preserve(%lu)\n", tmpU32); SPrint(pb);
#endif
            break;
/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_ECN            
         case SB_ID_PAR_ECN:                  /* ECN */
            SPrint("  Received ECN parameter in INIT \n");
            break;
#endif            

         default:
            for ( i = 0; i < parSize; i++ )   /* lose the message */
            {
               SB_UNPKU8(tmpU8);
            }
            break;

      } /* end of switch */

      /* lose the padding */
      for ( i = 0; i < pad; i++ )
      {
         SB_UNPKU8(tmpU8);
      }

      /* adjust message size */
      len = (S16)(len - (pad + parSize));
      /*   i++; */
   } /* end while */

#ifdef SB_PRNTSTUFF
   SPrint(         "  ========================================\n\n");
#endif

   SB_RLSMEM(mBuf)                    /* release memory */
   RETVALUE(ROK);
} /* end chkInitChunk */

/*
*
*       Fun:   chkInitAckChunk
*
*       Desc:  Check that the INIT_ACK chunk, received from the sending
*              endpoint is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkInitAckChunk
(
Buffer         *mBuf,           /* Data received from the SCTP */
SbAccChunkBld  *buildPar,       /* Information for checking the chunks */
SbAccAssoc     *assoc           /* Assocciation structure */
)
#else
PUBLIC  S16 chkInitAckChunk(mBuf,buildPar,assoc)
Buffer         *mBuf;            /* Data received from the SCTP */
SbAccChunkBld  *buildPar;       /* Information for checking the chunks */
SbAccAssoc     *assoc;           /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U32         initTag;
   U32         rwnd;
   U16         outStrms;
   U16         inStrms;
   U32         initTsn;
   U32         adler;   /* the adler checksum received in the datagram */
   MsgLen      len;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U8          tmpU8;
   U32         tmpU32;
   U16         parSize;
   U16         parType;
   U16         pad;
   U16         pad2;
   U32         i;
   U32         j;
   U16         unrecsize;
   U16         unrectype;
#if SB_PRNTSTUFF
   Txt         pb[200];
#endif

   TRC2(chkInitAckChunk)

   /* NB: DO NOT REMOVE THE UNRECOG PARAM STUFF */

   SPrint("chkInitAckChunk: unpacking the INIT ACK chunk\n");

   idx = 0;
   buildPar->unrecogParFound = FALSE;
   /* RFC 4460: Acceptance Test */
   buildPar->ipv4AddrFound = FALSE;
   buildPar->ipv6AddrFound = FALSE;

   SFndLenMsg(mBuf, &len);
   SRemPreMsgMult(&pkArray[0], len, mBuf);

   /* unpack the common header */
   SB_UNPKU16(srcPort);
   SB_UNPKU16(dstPort);
   SB_UNPKU32(verTag);
   SB_UNPKU32(adler);
   /* RFC 4460: Acceptance Test */
   buildPar->peerPort = srcPort;

   /* unpack the first chunk header, there is only one chunk */

   SB_UNPKU8(chunkId);
   SB_UNPKU8(chunkFlg);
   SB_UNPKU16(chunkLeng);

   if ( ( chunkId != SB_ID_INITACK) || (verTag != assoc->verTagLoc) )
   {
      buildPar->status = INV_VERTAG;
      SB_RLSMEM(mBuf)                    /* release memory */
      RETVALUE(RFAILED);  /* Invalid verification Tag and/or chunk ID*/
   }

   /* unpack the fixed parameters */
   SB_UNPKU32(initTag);
   /* RFC 4460: Acceptance Test */
   buildPar->vTag = initTag;
   assoc->verTagPeer = initTag;
   SB_UNPKU32(rwnd);          /* Pop receiver window credit */
   SB_UNPKU16(outStrms);      /* Pop outStrms */
   SB_UNPKU16(inStrms);       /* Pop inStrms */
   buildPar->outStrms = outStrms;
   buildPar->inStrms = inStrms;

   SB_UNPKU32(initTsn);       /* Pop initial TSN */

#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",srcPort, dstPort);\
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu)\n", verTag); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%ld)\n", adler); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | INIT ACK | flags[%d] | length(%d)\n", chunkFlg,\
           chunkLeng); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | iTag(%lu)\n", initTag); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | aRwnd(%lu)\n", rwnd); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | outStrm(%u) | inStrm(%u)\n",outStrms, inStrms);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | iTsn(%lu)\n", initTsn); SPrint(pb);
#endif

   /* unpack the optional parameters */
   len = (S16)(len - idx);
   while ( len > 0 )
   {
      SB_UNPKU16(parType);                 /* opt. param. type */
      SB_UNPKU16(parSize);                 /* opt. param. size */
      len -= 4;
      parSize -= 4;

      /* padding */
      if ( (parSize % 4) != 0 )
      {
         pad = (U16)(4 - (parSize % 4));
      }
      else
      {
         pad = 0;
      }
      switch ( parType )
      {
         case SB_ID_PAR_COOKIE:                    /* encryption cookie */
#ifdef SB_PRNTSTUFF
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | COOKIE | parSize(%d)\n", parSize+4);
            SPrint(pb);
            SPrint(         "  -------------------------------------\n");
            SPrint(         "  |      state cookie        \n");
#endif
            for ( i = 0; i < parSize; i++ )
            {
               SB_UNPKU8(assoc->cookie[i]);
            }
            assoc->cookieLeng = parSize;
            break;

         case SB_ID_PAR_IPV4:                  /* IPv4 */
            SB_UNPKU32(tmpU32);

#ifdef SB_PRNTSTUFF
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | IPV4 | parSize(%d)\n", parSize+4); SPrint(pb);
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | Address(%lu)\n",tmpU32); SPrint(pb);
#endif
            /* RFC 4460: Acceptance Test */
            buildPar->ipv4AddrFound = TRUE;
            break;

         case SB_ID_PAR_IPV6 :                  /* IPv6 */
#ifdef SB_PRNTSTUFF
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | IPV6 | parSize(%d)\n", parSize+4); SPrint(pb);
            SPrint(         "  -------------------------------------\n");
            SPrint(         "  | Address\n");
#endif

            for ( i = 0; i < CM_IPV6ADDR_SIZE; i++ )
            {
               SB_UNPKU8(tmpU8);
            }
            /* RFC 4460: Acceptance Test */
            buildPar->ipv6AddrFound = TRUE;
            break;

         case SB_ID_PAR_UNRECOG:                   /* Unrecognised Parameter */
            SB_UNPKU16(unrectype);
            SB_UNPKU16(unrecsize);
            unrecsize -= 4;

#ifdef SB_PRNTSTUFF
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | UNRECOG | parSize(%d)\n", parSize+4);
            SPrint(pb);
            SPrint(         "  -------------------------------------\n");
            sprintf(pb,     "  | type(%d) | length(%d)\n", unrectype,\
                    unrecsize+4); SPrint(pb);
            SPrint(         "  -------------------------------------\n");
            SPrint(         "  | unrecognised data\n");
            SPrint(         "  | ");
#endif
            for ( i = 0; i < unrecsize; i++ )
            {
               SB_UNPKU8(tmpU8);
#ifdef SB_PRNTSTUFF
               sprintf(pb, "%x ", tmpU8); SPrint(pb);
#endif
            }

            SPrint("\n");
            pad2 = 0;
            if ( unrecsize%4 != 0 )
            {
               pad2 = (U16)(4 - (unrecsize%4));
               for ( j = 0; j < pad2; j++ )
               {
                  SB_UNPKU8(tmpU8);
               }
            }
            buildPar->unrecogParFound = TRUE;

            break;

         default:
            for ( i = 0; i < parSize; i++ )   /* lose the message */
            {
               SB_UNPKU8(tmpU8);
            }
            break;

      } /* end of switch */
      /* lose the padding */
      for ( i = 0; i < pad; i++ )
      {
         SB_UNPKU8(tmpU8);
      }

      /* adjust message size */
      len = (S16)(len - (pad + parSize));
   }
   SPrint(         "  =====================================\n\n");

   SB_RLSMEM(mBuf)                    /* release memory */
   RETVALUE(ROK);
} /* end chkInitAckChunk */

/*
*
*       Fun:   chkCookieChunk
*
*       Desc:  Check that the COOKIE chunk is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkCookieChunk
(
Buffer         *mBuf,           /* Data received from the SCTP */
SbAccChunkBld  *buildPar,      /* Information for checking the chunks */
SbAccAssoc     *assoc           /* Assocciation structure */
)
#else
PUBLIC  S16 chkCookieChunk(mBuf, buildPar, assoc)
Buffer         *mBuf;           /* Data received from the SCTP */
SbAccChunkBld  *buildPar;      /* Information for checking the chunks */
SbAccAssoc     *assoc;          /* Assocciation structure */
#endif
{
   U16         srcPort;         /* source port */
   U16         dstPort;         /* dest. port */
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   Data        cookieRcv[MSG_SIZE];
   U32         adler;
   U8          i;
   MsgLen      len;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U8          tmpU8;
#if SB_PRNTSTUFF
   Txt         pb[200];
#endif

   TRC2(chkCookieChunk)

   SPrint("chkCookieChunk: unpacking the COOKIE chunk\n");

   idx = 0;

   SFndLenMsg(mBuf, &len);
   SRemPreMsgMult(&pkArray[0], len, mBuf);

   /* Initialize local variables */
   srcPort = 0;
   dstPort = 0;
   verTag = 0;
   adler = 0;
   chunkId = 0;
   chunkFlg = 0;
   chunkLeng = 0;

   /* unpack the common header */
   SB_UNPKU16(srcPort);
   SB_UNPKU16(dstPort);
   SB_UNPKU32(verTag);
   SB_UNPKU32(adler);

   /* unpack the first chunk header, COOKIE may be bundled with DATA */
   SB_UNPKU8(chunkId);
   SB_UNPKU8(chunkFlg);
   SB_UNPKU16(chunkLeng);

   if ( (chunkId != SB_ID_COOKIE) || (verTag != assoc->verTagLoc) )
   {
      buildPar->status = INV_VERTAG;
      SB_RLSMEM(mBuf)                    /* release memory */
      RETVALUE(RFAILED);                 /* Invalid verification Tag */
   }

   len = (S16)(len - idx);

   /* unpack the cookie */
   for ( i = 0; i < len; i++)
   {
      SB_UNPKU8(tmpU8);
      cookieRcv[i] = tmpU8;
      if ( cookieRcv[i] != assoc->cookie[i])
      {
         /*CC When Unknown parameter is found we should exit */
         if ( buildPar->pkUnknownPar == TRUE )
         {
            buildPar->pkUnknownPar = FALSE;
            break;
         }
         buildPar->status = INV_COOKIE;
         SB_RLSMEM(mBuf)                    /* release memory */
         RETVALUE(RFAILED);
      }
   }

#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",srcPort, dstPort);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu)\n", verTag); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%lu)\n", adler); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | COOKIE | flags[%d] | length(%d)\n", chunkFlg,\
           chunkLeng); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   SPrint(         "  | state cookie\n");
   SPrint(         "  =====================================\n\n");
#endif

   SB_RLSMEM(mBuf)                    /* release memory */
   RETVALUE(ROK);
} /* end chkCookieChunk */

/*
*
*       Fun:   chkSackChunk
*
*       Desc:  Check that the SACK chunk, received from the receiving
*              endpoint is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkSackChunk
(
Buffer         *mBuf,        /* Data received from the SCTP */
SbAccChunkBld  *buildPar,   /* Information for checking the chunks */
SbAccAssoc     *assoc        /* Assocciation structure */
)
#else
PUBLIC  S16 chkSackChunk(mBuf, buildPar, assoc)
Buffer         *mBuf;        /* Data received from the SCTP */
SbAccChunkBld  *buildPar;   /* Information for checking the chunks */
SbAccAssoc     *assoc;       /* Assocciation structure */
#endif
{
   U32         cumTsn;
   U32         aRwnd;
   U16         nmbFrag;
   U16         nmbDup;
   U8          pkArray[32];
   U16         idx;
   MsgLen      len;
   U32         i;
   U16         fragStrt;
   U16         fragEnd;
   U32         dupTsn;

   TRC2(chkSackChunk);

   UNUSED(assoc);

   /* Initialize local variables */
   aRwnd = 0;
   nmbFrag = 0;
   nmbDup = 0;
   cumTsn = 0;

   if (mBuf != (Buffer *)NULLP)
   {
      /* Initialize local variables */
      idx = 0;

      SRemPreMsgMult(&pkArray[0], 12, mBuf);
      SPrint("Unpack SACK \n ");

      /* Get the cumulative TSN */
      SB_UNPKU32(cumTsn);
      {
         Txt pb[64];
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
         sprintf(pb, "  received cumTsn = %u  expected cumTsn = %u\n",
                 cumTsn, buildPar->cumTsn);
#else
         sprintf(pb, "  received cumTsn = %lu  expected cumTsn = %lu\n",
                 cumTsn, buildPar->cumTsn);
#endif
         SPrint(pb);
      }
      if (cumTsn != buildPar->cumTsn)
      {
         buildPar->status = INC_TSN;
         RETVALUE(RFAILED);
      }


      /* Get the advertised receiver window credit */
      SB_UNPKU32(aRwnd);
      /* Get the number of fragments (N) */
      SB_UNPKU16(nmbFrag);
      /* Get the number of duplicate TSNs */
      SB_UNPKU16(nmbDup);
      idx = 0;
      len = (S16)(4*(nmbFrag + nmbDup));
      if (len != 0)
         SRemPreMsgMult(&pkArray[0], len ,mBuf);

      for (i = 0; i<nmbFrag; i++)
      {
         SB_UNPKU16(fragStrt);
         SB_UNPKU16(fragEnd);
         if ( (fragStrt != buildPar->fragStart[i+1]) ||\
              (fragEnd != buildPar->fragEnd[i+1]) )
         {
           buildPar->status = INC_SACKFRAG;
           RETVALUE(RFAILED);
         }
      }

      for (i = 0; i<nmbDup; i++)
      {
         SB_UNPKU32(dupTsn);
      }

      /* release memory: release memory in chkmux... */
   }
   RETVALUE(ROK);
} /* end chkSackChunk */

/*
*
*       Fun:   chkAbortErrChunk
*
*       Desc:  Check that the ABORT or ERROR chunk is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkAbortErrChunk
(
Buffer         *mBuf,        /* Data received from the SCTP */
SbAccChunkBld  *buildPar,    /* Information for checking the chunks */
SbAccAssoc     *assoc        /* Assocciation structure */
)
#else
PUBLIC  S16 chkAbortErrChunk(mBuf, buildPar, assoc)
Buffer         *mBuf;        /* Data received from the SCTP */
SbAccChunkBld  *buildPar;   /* Information for checking the chunks */
SbAccAssoc     *assoc;           /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U16         errType;       /* type of error conditions being reported */
   U16         errLen;        /* size of cause parameters in octets */
   U16         streamId;      /* stream ID */
   U16         reserved;      /* reserved parameter */
   U32         numMisPar;     /* number of missing parameters */
   U16         misPar;        /* missing parameter of the INIT/ INITACK  */
   U32         measStale;     /* measure of staleness in mioroseconds  */
   U32         adler;         /* adler received with datagram */
   U8          i;             /* index to for-loop */
   U8          pkArray[100];
   U16         idx;
   U16         causeParLen;
   U16         causeParType;
   U8          hstName[64];
   U32         abortReason;     /* Abort reason */

   TRC2(chkAbortErrChunk)
   SPrint("ABORT / ERROR chunk received\n");
   idx = 0;

   SRemPreMsgMult(&pkArray[0], 16, mBuf);

   /* unpack the common header */
   SB_UNPKU16(srcPort);
   SB_UNPKU16(dstPort);
   SB_UNPKU32(verTag);
   SB_UNPKU32(adler);

   /* unpack the first chunk header, there is only one chunk */
   SB_UNPKU8(chunkId);
   SB_UNPKU8(chunkFlg);
   SB_UNPKU16(chunkLeng);

   /* RFC 4460: Acceptance test */
   buildPar->vTag = verTag;
   buildPar->chunkFlg = chunkFlg;

   if ( (chunkId != buildPar->chunkId ) && (verTag != assoc->verTagLoc) )
   {
      buildPar->status = INV_VERTAG;
      SB_RLSMEM(mBuf);
      RETVALUE(RFAILED);
   }

   if ( chunkLeng == 4 )
   {
      /* no error causes */
      SB_RLSMEM(mBuf)                    /* release memory */
      RETVALUE(ROK);
   }

   idx = 0;
   SRemPreMsgMult(&pkArray[0], 4, mBuf);

   SB_UNPKU16(errType);                  /* error type */
   SB_UNPKU16(errLen);                   /* error length */
 
   if(errType != buildPar->cause)
   {
      buildPar->status = INC_CAUSE;
      SB_RLSMEM(mBuf);
      RETVALUE(RFAILED);  /* Incorrect cause */
   }

   switch ( errType )
   {
      case SB_CHUNK_ERROR_STREAM:
         SPrint("ABORT with stream error received\n");
         SRemPreMsgMult(&pkArray[0], 4, mBuf);
         SB_UNPKU16(streamId);
         SB_UNPKU16(reserved);
         break;

      case SB_CHUNK_ERROR_PARAM:
         SRemPreMsgMult(&pkArray[0], 2, mBuf);
         SB_UNPKU16(numMisPar);

         for (i = 0; i < numMisPar; i++)
         {
            SRemPreMsgMult(&pkArray[0], 2, mBuf);
            SB_UNPKU16(misPar);
         }
         break;

      case SB_CHUNK_ERROR_STALE:
         SRemPreMsgMult(&pkArray[0], 4, mBuf);
         SB_UNPKU32(measStale);
         break;

      case SB_CHUNK_ERROR_RES:
         break;
      case SB_CHUNK_ERROR_UNRECOG_PAR:
         break;
      case SB_CHUNK_ERROR_NO_USR_DATA:
         SPrint("ABORT with SB_CHUNK_ERROR_NO_USR_DATA\n");
         break;


     /* SB_VER13 - New codes added for version 13 */

      case SB_CHUNK_ERROR_INVAL_MAND_PAR:
         SPrint("ABORT with invalid mandatory parameter received\n");
         break;

      case SB_CHUNK_ERROR_UNRSLV_ADDR :    /* Unresolved Address */
         
            SPrint("sbAsRcvAbort: ABORT with unresolved Address \n");

            if(errLen != SB_CHUNK_HEADER_SIZE)
            {
                SRemPreMsgMult(&pkArray[0], 4, mBuf);
               
               idx=0; 
               SB_UNPKU16(causeParType);                  /* parameter  type */
               SB_UNPKU16(causeParLen);                   /* parameter length */
       
               causeParLen -= SB_CHUNK_HEADER_SIZE;
             
               if(causeParType != SB_ID_PAR_HSTNAME_ADDR)
               {
                   SPrint("sbAsRcvAbort: Cause Parameter is not correct \n");
               }
               else
               {
                   Txt pb[64];
                   SRemPreMsgMult(&pkArray[0], causeParLen, mBuf);
                   idx = 0;

                   for(i=0; i<causeParLen; i++)
                     SB_UNPKU8( hstName[i] );

                   sprintf(pb, " Abort hostname is (%s)\n", hstName);
                   SPrint(pb);
                }
              }
              break;

      case SB_CHUNK_ERROR_UNRECOG_CHUNK:
    SPrint("\n Error messgae received with SB_CHUNK_ERROR_UNRECOG_CHUNK \n");
         break;

      case SB_CHUNK_ERROR_RESTART_ASSOC_NEW_ADDR:
    SPrint("\n Error messgae received with SB_CHUNK_ERROR_RESTART_ASSOC_NEW_ADDR \n");
         break;
      /* RFC 4460 upgrade -- Introduced new case to support user initiated ABORT */
      case SB_CHUNK_ERROR_USR_INITIATED_ABORT:
         idx = 0;
         SRemPreMsgMult(&pkArray[0], 4, mBuf);
         SB_UNPKU32(abortReason);
    SPrint("\n Error messgae received with SB_CHUNK_ERROR_USR_INITIATED_ABORT\n");
         /* RFC 4460: Acceptance Tests */
         if(abortReason != 0) /* abortReason 0 is hard coded right now in user initiated abort */
            buildPar->status = INC_REASON;
         break;

      default:
         buildPar->status = INC_CAUSE;
         SB_RLSMEM(mBuf);
         RETVALUE(RFAILED);  /* Incorrect cause */
         break;
   }

   SB_RLSMEM(mBuf)                    /* release memory */
   RETVALUE(ROK);
} /* end chkAbortErrChunk */

/*
*
*       Fun:   chkShutdwnChunk
*
*       Desc:  Check that the SHUTDOWN chunk is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkShutdwnChunk
(
Buffer         *mBuf,           /* Data received from the SCTP */
SbAccChunkBld  *buildPar,       /* Information for checking the chunks */
SbAccAssoc     *assoc           /* Assocciation structure */
)
#else
PUBLIC  S16 chkShutdwnChunk(mBuf, buildPar, assoc)
Buffer         *mBuf;           /* Data received from the SCTP */
SbAccChunkBld  *buildPar;      /* Information for checking the chunks */
SbAccAssoc     *assoc;           /* Assocciation structure */
#endif
{
   U32         cumTsn;
   U8          pkArray[20];
   U16         idx;
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U32         adler;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
#if SB_PRNTSTUFF
   Txt         pb[200];
#endif

   TRC2(chkShutdwnChunk)

   idx = 0;

   SRemPreMsgMult(&pkArray[0], 16, mBuf);

   /* unpack the common header */
   SB_UNPKU16(srcPort);
   SB_UNPKU16(dstPort);
   SB_UNPKU32(verTag);
   SB_UNPKU32(adler);

   /* unpack the first chunk header, there is only one chunk */
   SB_UNPKU8(chunkId);
   SB_UNPKU8(chunkFlg);
   SB_UNPKU16(chunkLeng);

   if ( (chunkId != buildPar->chunkId ) && (verTag != assoc->verTagLoc) )
   {
      buildPar->status = INV_VERTAG;
      SB_RLSMEM(mBuf);
      RETVALUE(RFAILED);
   }

   SB_UNPKU32(cumTsn);

#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",srcPort, dstPort);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu)\n", verTag); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%lu)\n", adler); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | SHUTDOWN | flags[%d] | length(%d)\n", chunkFlg,\
           chunkLeng); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | cumulative TSN(%lu)\n", cumTsn); SPrint(pb);
   SPrint(         "  =====================================\n\n");
#endif

   SB_RLSMEM(mBuf);
   RETVALUE(ROK);
} /* end chkShutdwnChunk */
/*
*
*       Fun:   chkShutdwnAckChunk
*
*       Desc:  Check that the SHUTDOWN_ACK chunk is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkShutdwnAckChunk
(
Buffer         *mBuf,           /* Data received from the SCTP */
SbAccChunkBld  *buildPar,      /* Information for checking the chunks */
SbAccAssoc     *assoc           /* Assocciation structure */
)
#else
PUBLIC  S16 chkShutdwnAckChunk(mBuf, buildPar, assoc)
Buffer         *mBuf;           /* Data received from the SCTP */
SbAccChunkBld  *buildPar;      /* Information for checking the chunks */
SbAccAssoc     *assoc;           /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U32         adler;    /* adler received with datagram */
   U8          pkArray[16];
   U16         idx;

   TRC2(chkShutdwnAckChunk)
   UNUSED(assoc);

   idx = 0;
   SRemPreMsgMult(&pkArray[0], 16, mBuf);

   /* unpack the common header */
   SB_UNPKU16(srcPort);
   SB_UNPKU16(dstPort);
   SB_UNPKU32(verTag);
   SB_UNPKU32(adler);

   /* unpack the first chunk header, there is only one chunk */
   SB_UNPKU8(chunkId);
   SB_UNPKU8(chunkFlg);
   SB_UNPKU16(chunkLeng);

   if ( (chunkId != SB_ID_SDOWNACK) || (verTag != assoc->verTagLoc) )
   {
      buildPar->status = INV_VERTAG;
      SB_RLSMEM(mBuf)                    /* release memory */
      RETVALUE(RFAILED);  /* Invalid verification Tag and/or chunk ID*/
   }

   SB_RLSMEM(mBuf)                    /* release memory */
   RETVALUE(ROK);
} /* end chkShutdwnAckChunk */

/*
*
*       Fun:   chkHBeatChunk
*
*       Desc:  Check that the HBEAT chunk is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkHBeatChunk
(
Buffer         *mBuf,           /* Data received from the SCTP */
SbAccChunkBld  *buildPar,      /* Information for checking the chunks */
SbAccAssoc     *assoc           /* Assocciation structure */
)
#else
PUBLIC  S16 chkHBeatChunk(mBuf, buildPar, assoc)
Buffer         *mBuf;           /* Data received from the SCTP */
SbAccChunkBld  *buildPar;      /* Information for checking the chunks */
SbAccAssoc     *assoc;           /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U32         adler;    /* adler received with datagram */
   U8          i;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;

   TRC2(chkHBeatChunk)

   idx = 0;

   SRemPreMsgMult(&pkArray[0], 16, mBuf);

   /* unpack the common header */
   SB_UNPKU16(srcPort);
   SB_UNPKU16(dstPort);
   SB_UNPKU32(verTag);
   SB_UNPKU32(adler);

   /* unpack the first chunk header, there may be more DATA */
   SB_UNPKU8(chunkId);
   SB_UNPKU8(chunkFlg);
   SB_UNPKU16(chunkLeng);

   if ( (chunkId != SB_ID_HBEAT) || (verTag != assoc->verTagLoc) )
   {                                       /* start if #1 */
      buildPar->status = INV_VERTAG;
      SB_RLSMEM(mBuf);
      RETVALUE(RFAILED);
   }

   SRemPreMsgMult(&pkArray[0], (S16)(chunkLeng-4), mBuf);
   idx = 0;
   buildPar->hBeatInfoLen = (U16)(chunkLeng - 4);

   for ( i = 0; i < (chunkLeng-4); i++ )
   {
      SB_UNPKU8(buildPar->hBeatInfo[i]);
   }

   SB_RLSMEM(mBuf)                    /* release memory */
   RETVALUE(ROK);
} /* end chkHBeatChunk */

/* sb003.103 - addition - new function to check the ECNE chunk */
#ifdef SB_ECN
/* SATELLITE SCTP feature */ 
/*
*
*       Fun:   chkEcneChunk
*
*       Desc:  Check that the ECNE chunk is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkEcneChunk
(
Buffer         *mBuf,           /* Data received from the SCTP */
SbAccChunkBld  *buildPar,      /* Information for checking the chunks */
SbAccAssoc     *assoc           /* Assocciation structure */
)
#else
PUBLIC  S16 chkEcneChunk(mBuf, buildPar, assoc) 
Buffer         *mBuf;           /* Data received from the SCTP */
SbAccChunkBld  *buildPar;      /* Information for checking the chunks */
SbAccAssoc     *assoc;           /* Assocciation structure */
#endif
{
   U32         tsn;                     /* tsn number */
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   Txt         pb[64];

   TRC2(chkEcneChunk)
   SPrint("  unpacking ECNE chunk\n");
   UNUSED(assoc);

   idx = 0;
   SRemPreMsgMult(&pkArray[0], 4, mBuf);

   SB_UNPKU32(tsn);         /* Pop TSN */
   sprintf(pb, "  received Tsn = %lu  \n", tsn);
   SPrint(pb);
   
   buildPar->lowestTsn = tsn;

   if (buildPar->expectEcne == TRUE)
      RETVALUE(ROK);
   else
   {
      sprintf(pb, " Unexpected ECNE chunk received \n");
      SPrint(pb);
      RETVALUE(RFAILED);
   }
} /* end chkEcneChunk */

/* sb003.103 - addition - new function to check the CWR chunk */
/* SATELLITE SCTP feature */ 
/*
*
*       Fun:   chkCwrChunk
*
*       Desc:  Check that the CWR chunk is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkCwrChunk
(
Buffer         *mBuf,           /* Data received from the SCTP */
SbAccChunkBld  *buildPar,      /* Information for checking the chunks */
SbAccAssoc     *assoc           /* Assocciation structure */
)
#else
PUBLIC  S16 chkCwrChunk(mBuf, buildPar, assoc) 
Buffer         *mBuf;           /* Data received from the SCTP */
SbAccChunkBld  *buildPar;      /* Information for checking the chunks */
SbAccAssoc     *assoc;           /* Assocciation structure */
#endif
{
   U32         tsn;                     /* tsn number */
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   Txt         pb[64];

   TRC2(chkCwrChunk)
   SPrint("  unpacking CWR chunk\n");
   UNUSED(assoc);

   idx = 0;
   SRemPreMsgMult(&pkArray[0], 4, mBuf);

   SB_UNPKU32(tsn);  /* Pop TSN */
   buildPar->lowestTsn = tsn;

   sprintf(pb, " received Tsn = %lu  \n", tsn);
   SPrint(pb);

   if (buildPar->expectCwr == TRUE)
      RETVALUE(ROK);
   else
   {
      sprintf(pb, " Unexpected CWR chunk received \n");
      SPrint(pb);
      RETVALUE(RFAILED);
   }

} /* end chkCwrChunk */
#endif /* SB_ECN */

/* RFC 4460 -- SB_RFC_5 */
/*
*
*       Fun:   chkHBeatAckChunk
*
*       Desc:  Check that the HBEAT_ACK chunk is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkHBeatAckChunk
(
Buffer         *mBuf,           /* Data received from the SCTP */
SbAccChunkBld  *buildPar,      /* Information for checking the chunks */
SbAccAssoc     *assoc           /* Assocciation structure */
)
#else
PUBLIC  S16 chkHBeatAckChunk(mBuf, buildPar, assoc) 
Buffer         *mBuf;           /* Data received from the SCTP */
SbAccChunkBld  *buildPar;      /* Information for checking the chunks */
SbAccAssoc     *assoc;           /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U32         adler;    /* adler received with datagram */
   U8          i;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;

   TRC2(chkHBeatAckChunk)

   idx = 0;

   SRemPreMsgMult(&pkArray[0], 16, mBuf);

   /* unpack the common header */
   SB_UNPKU16(srcPort);
   SB_UNPKU16(dstPort);
   SB_UNPKU32(verTag);
   SB_UNPKU32(adler);

   /* unpack the first chunk header, there may be more DATA */
   SB_UNPKU8(chunkId);
   SB_UNPKU8(chunkFlg);
   SB_UNPKU16(chunkLeng);

   if ( (chunkId != SB_ID_HBEATACK) || (verTag != assoc->verTagLoc) )
   {                                       /* start if #1 */
      buildPar->status = INV_VERTAG;
      SB_RLSMEM(mBuf);
      RETVALUE(RFAILED);
   }

   SRemPreMsgMult(&pkArray[0], (S16)(chunkLeng-4), mBuf);
   idx = 0;
   buildPar->hBeatInfoLen = (U16)(chunkLeng - 4);

   for ( i = 0; i < (chunkLeng-4); i++ )
   {
      SB_UNPKU8(buildPar->hBeatInfo[i]);
   }

   SB_RLSMEM(mBuf)                    /* release memory */
   RETVALUE(ROK);
} /* end chkHBeatAckChunk */

/*
*
*       Fun:   chkCookieAckChunk
*
*       Desc:  Check that the COOKIEACK chunk is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkCookieAckChunk
(
Buffer         *mBuf,           /* Data received from the SCTP */
SbAccChunkBld  *buildPar,       /* Information for checking the chunks */
SbAccAssoc     *assoc           /* Assocciation structure */
)
#else
PUBLIC  S16 chkCookieAckChunk(mBuf, buildPar, assoc)
Buffer         *mBuf;           /* Data received from the SCTP */
SbAccChunkBld  *buildPar;      /* Information for checking the chunks */
SbAccAssoc     *assoc;          /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U32         adler;    /* adler received with datagram */
   U8          pkArray[32];
   U16         idx;
   MsgLen      len;
#if SB_PRNTSTUFF
   Txt         pb[200];
#endif

   TRC2(chkCookieAckChunk)
   SPrint("chkCookieAckChunk: unpacking the COOKIE ACK chunk\n");

   idx = 0;
   SFndLenMsg(mBuf, &len);
   SRemPreMsgMult(&pkArray[0], len, mBuf);

   /* unpack the common header */
   SB_UNPKU16(srcPort);
   SB_UNPKU16(dstPort);
   SB_UNPKU32(verTag);
   SB_UNPKU32(adler);

   /* unpack the first chunk header, there may be more DATA */
   SB_UNPKU8(chunkId);
   SB_UNPKU8(chunkFlg);
   SB_UNPKU16(chunkLeng);

   if ( (chunkId != SB_ID_COOKIEACK) || (verTag != assoc->verTagLoc) )
   {
      buildPar->status = INV_VERTAG;
      SB_RLSMEM(mBuf);
      RETVALUE(RFAILED);  /* Invalid verification Tag and/or chunk ID*/
   }

#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",srcPort, dstPort);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu)\n", verTag); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%lu)\n", adler); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | COOKIE ACK | flags[%d] | length(%d)\n", chunkFlg,\
           chunkLeng); SPrint(pb);
   SPrint(         "  =====================================\n\n");
#endif


   SB_RLSMEM(mBuf)     /* Release memory */
   RETVALUE(ROK);
} /* end chkCookieAckChunk */

/*
*
*       Fun:   chkDataChunk
*
*       Desc:  Check that the DATA chunk is valid.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  S16 chkDataChunk
(
Buffer         *mBuf,            /* Data received from the SCTP */
SbAccChunkBld  *buildPar,       /* Information for checking the chunks */
SbAccAssoc     *assoc            /* Assocciation structure */
)
#else
PUBLIC  S16 chkDataChunk(mBuf, buildPar, assoc)
Buffer         *mBuf;            /* Data received from the SCTP */
SbAccChunkBld  *buildPar;       /* Information for checking the chunks */
SbAccAssoc     *assoc;           /* Assocciation structure */
#endif
{
   U16         streamId;                /* stream identifier */
   U32         tsn;                     /* tsn number */
   U16         seqNr;                   /* stream sequence number */
   U32         protId;
   MsgLen      len;                     /* length of the data buffer */
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U32         oldRcvLen;
   Data        tmp[MSG_SIZE];

   TRC2(chkDataChunk)
   SPrint("  unpacking DATA chunk\n");
   UNUSED(assoc);

   idx = 0;
   SRemPreMsgMult(&pkArray[0], 12, mBuf);

   /* Initialize local variables */
   tsn = 0;
   streamId = 0;
   seqNr = 0;
   protId = 0;

   /* unpack the common header */

   SB_UNPKU32(tsn);         /* Pop TSN */
   buildPar->cumTsn = tsn;   /* Use the tsn as cumTsn in buildSack */
   SB_UNPKU16(streamId);    /* Pop stream identifier */
   SB_UNPKU16(seqNr);       /* Pop stream sequence number */
   SB_UNPKU32(protId);      /* Pop protocol identifier */
/*sb033.103 : Modified code base to remove warning for 64 bit compilation */
#ifdef BIT_64      
   sprintf(prntBuf, "tsn of data: %u\n", tsn);
#else
   sprintf(prntBuf, "tsn of data: %lu\n", tsn);
#endif
   SPrint(prntBuf);
   len = (S16)((buildPar->chunkLeng) - 16);
   sprintf(prntBuf, "Length of data: %u\n", len);
   SPrint(prntBuf);

   idx = 0;
   SRemPreMsgMult(&pkArray[0], len, mBuf);

   if ( ( (buildPar->chunkFlg & 3) == 3 ) )
   {
      /* unsegmented message  */
      oldRcvLen = sbAccCb.curTst.datRcvLen;
      (Void) cmMemcpy((U8 *) &(tmp), 
                      (U8 *) &(sbAccCb.curTst.datRcv),
                      (PTR) oldRcvLen );
      (Void) cmMemcpy((U8 *) &(tmp[oldRcvLen]),
                      (U8 *) &(pkArray),
                      (PTR) len );
      (Void) cmMemcpy((U8 *) &(sbAccCb.curTst.datRcv),
                      (U8 *) &(tmp),   
                      (PTR) (len+oldRcvLen) );
      sbAccCb.curTst.datRcvLen = (S16)(len +oldRcvLen);
   }
   else if ( ( (buildPar->chunkFlg & 3) == 2) )
   {
      /* First chunk of segmented message */
      SPrint("First segmentation piece \n ");
      (Void) cmMemcpy((U8 *) &(sbAccCb.curTst.datRcv),
                      (U8 *) &(pkArray),
                      (PTR) len );
      sbAccCb.curTst.datRcvLen = len;
   }
   else if ( ( (buildPar->chunkFlg & 3) == 0) ||
             ( (buildPar->chunkFlg & 3) == 1) )
   {
      /* middle or last piece of segmented message */
      SPrint("Middle segmentation piece \n ");
      oldRcvLen = sbAccCb.curTst.datRcvLen;
      (Void) cmMemcpy((U8 *) &(tmp),  
                      (U8 *) &(sbAccCb.curTst.datRcv),
                      (PTR) oldRcvLen );
      (Void) cmMemcpy((U8 *) &(tmp[oldRcvLen]),
                      (U8 *) &(pkArray), 
                      (PTR) len );
      (Void) cmMemcpy((U8 *) &(sbAccCb.curTst.datRcv),
                      (U8 *) &(tmp),
                      (PTR) (len+oldRcvLen) );
      sbAccCb.curTst.datRcvLen = (S16)(len +oldRcvLen);
   }

   /* release memory in chkMux... */
   RETVALUE(ROK);
} /* end chkDataChunk */

/*
*
*       Fun:   buildInitChunk
*
*       Desc:  Build an INIT chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void buildInitChunk
(
Buffer           *mBuf,        /* Data received from the SCTP */
SbAccChunkBld    *buildPar,
SbAccAssoc       *assoc
)
#else
PUBLIC  void buildInitChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;        /* Data received from the SCTP */
SbAccChunkBld    *buildPar;
SbAccAssoc       *assoc;
#endif
{
   U8          chunkId;
   U8          chunkFlg;
   U32         initTag;
   U32         arwnd;
   U16         outStrms;
   U16         inStrms;
   U32         initTsn;
   U32         srcAddr1;
   U32         srcAddr2;
   U32         checksum;
   /* sb035.103: Changed limit of pkArray */
   U8          pkArray[512];
   U16         length;
   U16         idx;
   U8          tmpU8;
   MsgLen      len;
   U16         i;
   U16         align;
   S16         cnt;
   U16         hstNameLen;
#if SB_PRNTSTUFF
   Txt         pb[200];
#endif
   U8          srcIpv6Addr1[16];
   U8          srcIpv6Addr2[16];
   U8          byteCount;
   TRC2(buildInitChunk)
   /* sb058.102 : Added to remove compilation warning */
      length = 0;
      idx = 0;
      len = 0;

   SPrint("buildInitChunk: building INIT chunk\n");

   chunkId =  SB_ID_INIT;             /* Init chunk */
   chunkFlg = 0;
   /* chunkLeng will still be determined */

   arwnd =  ACC_ARWND_INIT;      /* choose arbitrary value */
   outStrms = buildPar->outStrms;/* Choose number smaller than that configured */
   inStrms =  buildPar->inStrms;    /* Max numb of streams the peer may have in reply to Init: Use configured value */
   /* RFC 4460: Acceptance Test */
   if(buildPar->usrITag == TRUE)
   {
      initTag = buildPar->iTag;
   }
   else
   {
      if ( buildPar->newITag == TRUE )
      {
         initTag = ACC_INIT_PEERTAG + 11;
      }
      else
      {
         initTag = ACC_INIT_PEERTAG;
      }
   }
   initTsn = ACC_INIT_TSN;
   assoc->verTagLoc = initTag;

   hstNameLen = cmStrlen(buildPar->hostName);

   if ( (buildPar->hstNamePrsnt == TRUE) && (hstNameLen != 0 ))
   {
     idx = 0;

     if (((hstNameLen+1) & 0x03) == 0 )
     {
       align = 0;
     }
     else
     {
        align = 4 - ((hstNameLen+1) & 0x03);
        for ( cnt = 0; cnt < align; cnt++)
        {
          SB_PKU8(0x00);
        }
      }
      /* Pack Null Character */
      SB_PKU8('\0');

     for(cnt=(hstNameLen-1);cnt >= 0 ;cnt--)
        SB_PKU8(buildPar->hostName[cnt]);

     SB_PKU16(hstNameLen+1+SB_CHUNK_HEADER_SIZE);
     SB_PKU16(SB_ID_PAR_HSTNAME_ADDR);
   }
   else
   {
     if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
     {
     if ( assoc->spId == SPID_1 )
     {
        srcAddr1 = peerNAddrLst_2[2];
     }
     /* RFC 4460 -- */
     else if ( TRUE == buildPar->newAddr )
     {
        srcAddr1 = peerNAddrLst_2[0];
     }
     else
     {
        srcAddr1 = peerNAddrLst_1[2];    /* Primitive originated at primary destination
                                          addres of receiving endpoint */
     }

     if ( assoc->spId == SPID_1 )
     {
        srcAddr2 = peerNAddrLst_2[3];
     }
     else
     {
        srcAddr2 = peerNAddrLst_1[3];    /* Primitive originated at primary
                                            destination addres of receiving endpoint */
     }
     idx = 0;

     /* pack in an IPV4 nr 1*/
     SB_PKU32(srcAddr1);
     SB_PKU16(SB_SZ_PAR_IPV4);
     if ( buildPar->misChunk == TRUE )
     {
        SPrint("  inserting dubious optional parameter\n");

        /* sb074.102 : change the parameter type as handling logic of highest bit for 
     parameter type of INIT is changed */
        SB_PKU16(0xc00d);
     }
     else
     {
        SB_PKU16(SB_ID_PAR_IPV4);
     }
  
     /* pack in an IPV4 nr 1*/
     SB_PKU32(srcAddr2);
     SB_PKU16(SB_SZ_PAR_IPV4);
     SB_PKU16(SB_ID_PAR_IPV4);
     /* RFC 4460: Acceptance Test */
     if(buildPar->multAddrTypes == TRUE)
     {
        if ( assoc->spId == SPID_1 )
        {
           CPY_ACC_ASSOC2_PEER_IPV6(srcIpv6Addr1, 2);
        }
        else
        {
           CPY_ACC_ASSOC1_PEER_IPV6(srcIpv6Addr1, 2);
        }

        if ( assoc->spId == SPID_1 )
        {
           CPY_ACC_ASSOC2_PEER_IPV6(srcIpv6Addr2, 3);
        }
        else
        {
           CPY_ACC_ASSOC1_PEER_IPV6(srcIpv6Addr2, 3);
        }
        idx = 0;

        /* pack in an IPV6 nr 1*/
        for(byteCount=0; byteCount<CM_IPV6ADDR_SIZE; byteCount++)
        {
           SB_PKU8(srcIpv6Addr1[CM_IPV6ADDR_SIZE-1-byteCount]);
        }
        SB_PKU16(SB_SZ_PAR_IPV6);
        if ( buildPar->misChunk == TRUE )
        {
           SPrint("  inserting dubious optional parameter\n");
           SB_PKU16(SB_ID_PAR_IPV4 + 100);
        }
        else
        {
           SB_PKU16(SB_ID_PAR_IPV6);
        }
  
        /* pack in an IPV6 nr 1*/
        for(byteCount=0; byteCount<CM_IPV6ADDR_SIZE; byteCount++)
        {
           SB_PKU8(srcIpv6Addr2[CM_IPV6ADDR_SIZE-1-byteCount]);
        }
        SB_PKU16(SB_SZ_PAR_IPV6);
        SB_PKU16(SB_ID_PAR_IPV6);
     }
    }
    else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
    {
     if ( assoc->spId == SPID_1 )
     {
        CPY_ACC_ASSOC2_PEER_IPV6(srcIpv6Addr1, 2);
     }
     else
     {
        CPY_ACC_ASSOC1_PEER_IPV6(srcIpv6Addr1, 2);
     }

     if ( assoc->spId == SPID_1 )
     {
        CPY_ACC_ASSOC2_PEER_IPV6(srcIpv6Addr2, 3);
     }
     else
     {
        CPY_ACC_ASSOC1_PEER_IPV6(srcIpv6Addr2, 3);
     }
     idx = 0;

     /* pack in an IPV6 nr 1*/
     for(byteCount=0; byteCount<CM_IPV6ADDR_SIZE; byteCount++)
     {
        SB_PKU8(srcIpv6Addr1[CM_IPV6ADDR_SIZE-1-byteCount]);
     }
     SB_PKU16(SB_SZ_PAR_IPV6);
     if ( buildPar->misChunk == TRUE )
     {
        SPrint("  inserting dubious optional parameter\n");
        SB_PKU16(SB_ID_PAR_IPV4 + 100);
     }
     else
     {
        SB_PKU16(SB_ID_PAR_IPV6);
     }
  
     /* pack in an IPV6 nr 1*/
     for(byteCount=0; byteCount<CM_IPV6ADDR_SIZE; byteCount++)
     {
        SB_PKU8(srcIpv6Addr2[CM_IPV6ADDR_SIZE-1-byteCount]);
     }
     SB_PKU16(SB_SZ_PAR_IPV6);
     SB_PKU16(SB_ID_PAR_IPV6);
    }
   }

   /* RFC 4460: Acceptance Tests */
   if(buildPar->suppAddrTypes != 0)
   {
      if(buildPar->suppAddrTypes == 2)
      {
         SB_PKU16(0x00);  /* Pad */
         SB_PKU16(SB_SUP_ADDRS_IPV6);
         SB_PKU16(0x06);
         SB_PKU16(SB_ID_PAR_SUP_ADDRS);
      }
   }

   /* RFC 4460: Acceptance Tests */
   if(buildPar->pkUnrecogPar == TRUE)
   {
         SB_PKU32(0x01); /* value */
         SB_PKU16(8); /* length */
         SB_PKU16(SB_ID_PAR_UNRECOG);
   }
   if(buildPar->pkUnknownPar == TRUE)
   {
         SB_PKU32(0x77); /* value */
         SB_PKU16(8); /* length */
         SB_PKU16(0x7BBB);
   }

   /* Pack the mandatory variables */
   SB_PKU32(initTsn);
   SB_PKU16(inStrms);
   SB_PKU16(outStrms);
   SB_PKU32(arwnd);
   SB_PKU32(initTag);

   length = (U16)(idx + 4); 
   SB_PKU16(length);   /* chunklength */
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(0x0);
   SB_PKU16(assoc->localPort);        /* peerPort */
   SB_PKU16(assoc->peerPort);       /* srcPort */
   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   /* determine Checksum value to insert */
   if ( mBuf != (Buffer *) NULLP )
   {
      (Void) SFndLenMsg(mBuf, &len);
   }

   checksum = 0;
#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }

#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",assoc->peerPort,\
           assoc->localPort); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   SPrint(         "  | vTag(0)\n");
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%ld)\n",checksum); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | INIT | flags[00000000] | length(%d)\n", length);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | iTag(%ld)\n",initTag); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | a_Rwnd(%ld)\n",arwnd); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | outStrm(%d) | inStrm(%d)\n",outStrms, inStrms);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | iTSN(%ld)\n",initTsn); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   if ( buildPar->misChunk == TRUE )
   {
      SPrint(         "  | dubious param | parSize(8)\n");
      SPrint(         "  -------------------------------------\n");
      sprintf(pb,     "  | data(%lX)\n",srcAddr1); SPrint(pb);
      SPrint(         "  -------------------------------------\n");
   }
   else
   {
      SPrint(         "  | IPV4 | parSize(8)\n");
      SPrint(         "  -------------------------------------\n");
      sprintf(pb,     "  | Address(%lu)\n",srcAddr1); SPrint(pb);
      SPrint(         "  -------------------------------------\n");
   }
   SPrint(         "  | IPV4 | parSize(8)\n");
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | Address(%lu)\n",srcAddr2); SPrint(pb);
   SPrint(         "  =====================================\n\n");

#endif
   RETVOID;
} /* end buildInitChunk */

/* sb012.103: Added function to build init with non-unicast address 
 * bundled in chunk 
 */

/*
*
*       Fun:   buildInitChunkUnicast
*
*       Desc:  Build an INIT chunk bundled with Non-Unicast address .
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void buildInitChunkUnicast
(
Buffer           *mBuf,        /* Data received from the SCTP */
SbAccChunkBld    *buildPar,
SbAccAssoc       *assoc
)
#else
PUBLIC  void buildInitChunkUnicast(mBuf, buildPar, assoc)
Buffer           *mBuf;        /* Data received from the SCTP */
SbAccChunkBld    *buildPar;
SbAccAssoc       *assoc;
#endif
{
   U8          chunkId;
   U8          chunkFlg;
   U32         initTag;
   U32         arwnd;
   U16         outStrms;
   U16         inStrms;
   U32         initTsn;
   U32         srcAddr1;
   U32         srcAddr2;
   U32         checksum;
   U8          pkArray[128];
   U16         length;
   U16         idx;
   U8          tmpU8;
   MsgLen      len;
   U16         i;
   U16         align;
   S16         cnt;
   U16         hstNameLen;
#if SB_PRNTSTUFF
   Txt         pb[200];
#endif
   U8          srcIpv6Addr1[16];
   U8          srcIpv6Addr2[16];
   U8          byteCount;
   TRC2(buildInitChunkUnicast)
      length = 0;
      idx = 0;
      len = 0;

   SPrint("buildInitChunkUnicast: building INIT chunk \n");

   chunkId =  SB_ID_INIT;             /* Init chunk */
   chunkFlg = 0;
   /* chunkLeng will still be determined */

   arwnd =  ACC_ARWND_INIT;      /* choose arbitrary value */
   outStrms = buildPar->outStrms;/* Choose number smaller than that configured */
   inStrms =  buildPar->inStrms;    /* Max numb of streams the peer may have in reply to Init: Use configured value */
   /* RFC 4460: Acceptance Test */
   if(buildPar->usrITag == TRUE)
   {
      initTag = buildPar->iTag;
   }
   else
   {
      if ( buildPar->newITag == TRUE )
      {
         initTag = ACC_INIT_PEERTAG + 11;
      }
      else
      {
         initTag = ACC_INIT_PEERTAG;
      }
   }
   initTsn = ACC_INIT_TSN;
   assoc->verTagLoc = initTag;

   hstNameLen = cmStrlen(buildPar->hostName);

   if ( (buildPar->hstNamePrsnt == TRUE) && (hstNameLen != 0 ))
   {
     idx = 0;

     if (((hstNameLen+1) & 0x03) == 0 )
     {
       align = 0;
     }
     else
     {
        align = 4 - ((hstNameLen+1) & 0x03);
        for ( cnt = 0; cnt < align; cnt++)
        {
          SB_PKU8(0x00);
        }
      }
      /* Pack Null Character */
      SB_PKU8('\0');

     for(cnt=(hstNameLen-1);cnt >= 0 ;cnt--)
        SB_PKU8(buildPar->hostName[cnt]);

     SB_PKU16(hstNameLen+1+SB_CHUNK_HEADER_SIZE);
     SB_PKU16(SB_ID_PAR_HSTNAME_ADDR);
   }
   else
   {
     if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
     {
     if ( assoc->spId == SPID_1 )
     {
        srcAddr1 = peerNAddrLst_2[2];
     }
     /* RFC 4460 -- */
     else if ( TRUE == buildPar->newAddr )
     {
        srcAddr1 = peerNAddrLst_2[0];
     }
     else
     {
        srcAddr1 = peerNAddrLst_1[2];    /* Primitive originated at primary destination
                                          addres of receiving endpoint */
     }

     if ( assoc->spId == SPID_1 )
     {
	/* Bundle one non-unicast address */
        srcAddr2 = peerNAddrLst_3[1];
     }
     else
     {
        srcAddr2 = peerNAddrLst_3[1];    /* Primitive originated at primary
                                            destination addres of receiving endpoint */
     }
     idx = 0;

     /* pack in an IPV4 nr 1*/
     SB_PKU32(srcAddr1);
     SB_PKU16(SB_SZ_PAR_IPV4);
     if ( buildPar->misChunk == TRUE )
     {
        SPrint("  inserting dubious optional parameter\n");

        SB_PKU16(0xc00d);
     }
     else
     {
        SB_PKU16(SB_ID_PAR_IPV4);
     }
  
     /* pack in an IPV4 nr 1*/
     SB_PKU32(srcAddr2);
     SB_PKU16(SB_SZ_PAR_IPV4);
     SB_PKU16(SB_ID_PAR_IPV4);
     /* RFC 4460: Acceptance Test */
     if(buildPar->multAddrTypes == TRUE)
     {
        if ( assoc->spId == SPID_1 )
        {
           CPY_ACC_ASSOC2_PEER_IPV6(srcIpv6Addr1, 2);
        }
        else
        {
           CPY_ACC_ASSOC1_PEER_IPV6(srcIpv6Addr1, 2);
        }

        if ( assoc->spId == SPID_1 )
        {
	/* Bundle one non-unicast address */
           CPY_ACC_ASSOC2_PEER_IPV6(srcIpv6Addr2, 5);
        }
        else
        {
           CPY_ACC_ASSOC1_PEER_IPV6(srcIpv6Addr2, 5);
        }
        idx = 0;

        /* pack in an IPV6 nr 1*/
        for(byteCount=0; byteCount<CM_IPV6ADDR_SIZE; byteCount++)
        {
           SB_PKU8(srcIpv6Addr1[CM_IPV6ADDR_SIZE-1-byteCount]);
        }
        SB_PKU16(SB_SZ_PAR_IPV6);
        if ( buildPar->misChunk == TRUE )
        {
           SPrint("  inserting dubious optional parameter\n");
           SB_PKU16(SB_ID_PAR_IPV4 + 100);
        }
        else
        {
           SB_PKU16(SB_ID_PAR_IPV6);
        }
  
        /* pack in an IPV6 nr 1*/
        for(byteCount=0; byteCount<CM_IPV6ADDR_SIZE; byteCount++)
        {
           SB_PKU8(srcIpv6Addr2[CM_IPV6ADDR_SIZE-1-byteCount]);
        }
        SB_PKU16(SB_SZ_PAR_IPV6);
        SB_PKU16(SB_ID_PAR_IPV6);
     }
    }
    else if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
    {
     if ( assoc->spId == SPID_1 )
     {
        CPY_ACC_ASSOC2_PEER_IPV6(srcIpv6Addr1, 2);
     }
     else
     {
        CPY_ACC_ASSOC1_PEER_IPV6(srcIpv6Addr1, 2);
     }

     if ( assoc->spId == SPID_1 )
     {  
	/* Bundle one non-unicast address */
        CPY_ACC_ASSOC2_PEER_IPV6(srcIpv6Addr2, 5);
     }
     else
     {
        CPY_ACC_ASSOC1_PEER_IPV6(srcIpv6Addr2, 5);
     }
     idx = 0;

     /* pack in an IPV6 nr 1*/
     for(byteCount=0; byteCount<CM_IPV6ADDR_SIZE; byteCount++)
     {
        SB_PKU8(srcIpv6Addr1[CM_IPV6ADDR_SIZE-1-byteCount]);
     }
     SB_PKU16(SB_SZ_PAR_IPV6);
     if ( buildPar->misChunk == TRUE )
     {
        SPrint("  inserting dubious optional parameter\n");
        SB_PKU16(SB_ID_PAR_IPV4 + 100);
     }
     else
     {
        SB_PKU16(SB_ID_PAR_IPV6);
     }
  
     /* pack in an IPV6 nr 1*/
     for(byteCount=0; byteCount<CM_IPV6ADDR_SIZE; byteCount++)
     {
        SB_PKU8(srcIpv6Addr2[CM_IPV6ADDR_SIZE-1-byteCount]);
     }
     SB_PKU16(SB_SZ_PAR_IPV6);
     SB_PKU16(SB_ID_PAR_IPV6);
    }
   }

   /* RFC 4460: Acceptance Tests */
   if(buildPar->suppAddrTypes != 0)
   {
      if(buildPar->suppAddrTypes == 2)
      {
         SB_PKU16(0x00);  /* Pad */
         SB_PKU16(SB_SUP_ADDRS_IPV6);
         SB_PKU16(0x06);
         SB_PKU16(SB_ID_PAR_SUP_ADDRS);
      }
   }

   /* RFC 4460: Acceptance Tests */
   if(buildPar->pkUnrecogPar == TRUE)
   {
         SB_PKU32(0x01); /* value */
         SB_PKU16(8); /* length */
         SB_PKU16(SB_ID_PAR_UNRECOG);
   }
   if(buildPar->pkUnknownPar == TRUE)
   {
         SB_PKU32(0x77); /* value */
         SB_PKU16(8); /* length */
         SB_PKU16(0x7BBB);
   }

   /* Pack the mandatory variables */
   SB_PKU32(initTsn);
   SB_PKU16(inStrms);
   SB_PKU16(outStrms);
   SB_PKU32(arwnd);
   SB_PKU32(initTag);

   length = (U16)(idx + 4); 
   SB_PKU16(length);   /* chunklength */
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(0x0);
   SB_PKU16(assoc->localPort);        /* peerPort */
   SB_PKU16(assoc->peerPort);       /* srcPort */
   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   /* determine Checksum value to insert */
   if ( mBuf != (Buffer *) NULLP )
   {
      (Void) SFndLenMsg(mBuf, &len);
   }

   checksum = 0;
#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }

#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",assoc->peerPort,\
           assoc->localPort); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   SPrint(         "  | vTag(0)\n");
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%ld)\n",checksum); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | INIT | flags[00000000] | length(%d)\n", length);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | iTag(%ld)\n",initTag); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | a_Rwnd(%ld)\n",arwnd); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | outStrm(%d) | inStrm(%d)\n",outStrms, inStrms);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | iTSN(%ld)\n",initTsn); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   if ( buildPar->misChunk == TRUE )
   {
      SPrint(         "  | dubious param | parSize(8)\n");
      SPrint(         "  -------------------------------------\n");
      sprintf(pb,     "  | data(%lX)\n",srcAddr1); SPrint(pb);
      SPrint(         "  -------------------------------------\n");
   }
   else
   {
      SPrint(         "  | IPV4 | parSize(8)\n");
      SPrint(         "  -------------------------------------\n");
      sprintf(pb,     "  | Address(%lu)\n",srcAddr1); SPrint(pb);
      SPrint(         "  -------------------------------------\n");
   }
   SPrint(         "  | IPV4 | parSize(8)\n");
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | Address(%lu)\n",srcAddr2); SPrint(pb);
   SPrint(         "  =====================================\n\n");

#endif
   RETVOID;
} /* end buildInitChunkUnicast */

/*
*
*       Fun:   buildInitAckChunk
*
*       Desc:  Build an INIT_ACK chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void buildInitAckChunk
(
Buffer           *mBuf,        /* Data received from the SCTP */
SbAccChunkBld    *buildPar,
SbAccAssoc       *assoc       /* Assocciation structure */
)
#else
PUBLIC  void buildInitAckChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;        /* Data received from the SCTP */
SbAccChunkBld    *buildPar;
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U32         initTag;
   U32         rwnd;
   U32         initTsn;
   Data        cookie[MSG_SIZE];
   U16         inStrms;
   U16         outStrms;
   U32         srcAddr1;
   U32         srcAddr2;
   U8          srcIpv6Addr1[16];
   U8          srcIpv6Addr2[16];
   S16         i;
   U32         checksum;
   /* sb035.103: Changed limit of pkArray */
   U8          pkArray[512];
   U16         idx;
   U8          tmpU8;
   MsgLen      len;
   U16         align;
   S16         cnt;
   U16         hstNameLen;
   S32         byteCount;
#if SB_PRNTSTUFF
   Txt         pb[200];
#endif

   TRC2(buildInitAckChunk)
   /* sb058.102 : Added to remove compilation warning */
      idx = 0;
      len = 0;
   SPrint("  building INIT ACK chunk\n");

   chunkId =  SB_ID_INITACK;
   initTag = ACC_INIT_PEERTAG;
   assoc->verTagLoc = initTag;
   verTag = assoc->verTagPeer;
   chunkFlg = 0;

   inStrms = buildPar->inStrms;
   outStrms = buildPar->outStrms;
   initTsn = ACC_INIT_TSN;
   rwnd = buildPar->arwnd;

   hstNameLen = cmStrlen(buildPar->hostName);

     idx = 0;

   if(buildPar->pkUnknownPar == TRUE)
   {
         SB_PKU32(0x77); /* value */
         SB_PKU16(8); /* length */
         SB_PKU16(0xCBBB);
   }

   if ( (buildPar->hstNamePrsnt == TRUE) && (hstNameLen != 0 ))
   {

     if (((hstNameLen+1) & 0x03) == 0 )
     {
       align = 0;
     }
     else
     {
        align = 4 - ((hstNameLen+1) & 0x03);
        for ( cnt = 0; cnt < align; cnt++)
        {
          SB_PKU8(0x00);
        }
      }
      /* Pack Null Character */
      SB_PKU8('\0');

     for(cnt=(hstNameLen-1);cnt >= 0 ;cnt--)
        SB_PKU8(buildPar->hostName[cnt]);

     SB_PKU16(hstNameLen+1+SB_CHUNK_HEADER_SIZE);
     SB_PKU16(SB_ID_PAR_HSTNAME_ADDR);
   }
   else
   {
     if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4)
     {
        if ( assoc->spId == SPID_1 )
        {
           srcAddr1 = peerNAddrLst_2[2];
        }
        else
        {/* Primitive come from  primary destination addres of receiving endpoint */
           srcAddr1 = peerNAddrLst_1[2];
        }

        if ( assoc->spId == SPID_1 )
        {
           srcAddr2 = peerNAddrLst_2[3];
        }
        else
        {
           srcAddr2 = peerNAddrLst_1[3];    /* Primitive originated at primary
                                          destination addres of receiving endpoint */
        }

/* sb003.103: SATELLITE SCTP feature */ 
#ifdef SB_ECN
        /* Check the General Configuration Flag */
        if (sbGlobalCb.genCfg.reConfig.ecnFlg)
        {
           SB_PKU16(0x04);
           SB_PKU16(SB_ID_PAR_ECN);
        }
#endif /* SB_ECN */

        /* pack in an IPV4 nr 1*/
        SB_PKU32(srcAddr1);
        SB_PKU16(SB_SZ_PAR_IPV4);
        SB_PKU16(SB_ID_PAR_IPV4);

        /* pack in an IPV4 nr 1*/
        SB_PKU32(srcAddr2);
        SB_PKU16(SB_SZ_PAR_IPV4);
        SB_PKU16(SB_ID_PAR_IPV4);
     } 
     if(sbAccCb.curTst.addrType == CM_NETADDR_IPV6)
     {
        if ( assoc->spId == SPID_1 )
        {
           CPY_ACC_ASSOC2_PEER_IPV6(srcIpv6Addr1, 2)
        }
        else
        {/* Primitive come from  primary destination addres of receiving endpoint */
           CPY_ACC_ASSOC1_PEER_IPV6(srcIpv6Addr1, 2)
        }

        if ( assoc->spId == SPID_1 )
        {
           CPY_ACC_ASSOC2_PEER_IPV6(srcIpv6Addr2, 3)
        }
        else
        {
           CPY_ACC_ASSOC1_PEER_IPV6(srcIpv6Addr2, 3)
        }


        /* pack in an IPV6 nr 1*/
        for(byteCount=0; byteCount<CM_IPV6ADDR_SIZE; byteCount++)
        {
           SB_PKU8(srcIpv6Addr1[CM_IPV6ADDR_SIZE-1-byteCount]);
        }
        SB_PKU16(SB_SZ_PAR_IPV6);
        SB_PKU16(SB_ID_PAR_IPV6);

        /* pack in an IPV6 nr 1*/
        for(byteCount=0; byteCount<CM_IPV6ADDR_SIZE; byteCount++)
        {
           SB_PKU8(srcIpv6Addr2[CM_IPV6ADDR_SIZE-1-byteCount]);
        }
        SB_PKU16(SB_SZ_PAR_IPV6);
        SB_PKU16(SB_ID_PAR_IPV6);
     } 
   }

   if ( buildPar->misChunk != TRUE )
   {
      len = 8;
      for ( i = 0; i < len; i++)
      {
         cookie[i] = (U8)(i+2);
         assoc->cookie[i] = cookie[i];
      }

      for ( i = (S16)(len-1); i >= 0; i-- )
      {
         SB_PKU8(cookie[i]);
      }

      SB_PKU16(len+4);
      SB_PKU16(SB_ID_PAR_COOKIE);
   }


   SB_PKU32(initTsn);
   SB_PKU16(inStrms);                 /* IN  */
   SB_PKU16(outStrms);                /* OUT */

   SB_PKU32(rwnd);
   SB_PKU32(initTag);

   chunkLeng = (U16)(idx + SB_IFL_SZ);
   SB_PKU16(chunkLeng);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(verTag);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

      /* determine Checksum value to insert */
   if ( mBuf != (Buffer *) NULLP )
   {
      (Void) SFndLenMsg(mBuf, &len);
   } else{
      SPrint("Buffer not allocated \n");
   }

   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }

#ifdef SB_PRNTSTUFF
   SPrint(         "  ========================================\n");
   sprintf(pb,     "  | srcPort(%u) | dstPort(%u)   \n",srcPort, dstPort);
   SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   SPrint(         "  | vTag \n");
   SPrint(         "  ----------------------------------------\n");
   SPrint(         "  | checksum\n" );
   SPrint(         "  ----------------------------------------\n");
   SPrint(         "  |   INIT_ACK  | flag(0) | length\n");
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | iTag(%lu) \n",initTag); SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | outStrm(%d) | inStrm(%d) \n",outStrms, inStrms);
   SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | iTSN(%lu) \n",initTsn); SPrint(pb);
   SPrint(         "  ----------------------------------------\n");
   SPrint(         "  | Cookie ID | length \n");
   SPrint(         "  ----------------------------------------\n");
   SPrint(         "  | state cookie \n");
   SPrint(         "  ----------------------------------------\n");
   SPrint(         "  | IPV4/6 | length(8) \n");
   SPrint(         "  ----------------------------------------\n");
   sprintf(pb,     "  | address(%lu) \n",srcAddr1); SPrint(pb);
   SPrint(         "  ========================================\n");
#endif
   RETVOID;
} /* end buildInitAckChunk */

/*
*
*       Fun:   buildCookieChunk
*
*       Desc:  Build an COOKIE chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  void buildCookieChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  void buildCookieChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         chunkSize;
   U16         i;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U32         checksum;
   U16         pad;
   U8          tmpU8;
   MsgLen      len;
#if SB_PRNTSTUFF
   Txt         pb[64];
#endif

   TRC2(buildCookieChunk);
   UNUSED(buildPar);
   len = 0;
   SPrint("buildCookieChunk: building COOKIE chunk\n");
   idx = 0;

   /* Pack the COOKIE */
   /* first the padding */
   pad = 0;
   if ( (assoc->cookieLeng & 0x03) != 0 )
   {
      pad = (U16)(4 - (assoc->cookieLeng & 0x03));
      for ( i = 0; i < pad; i++ )
      {
         SB_PKU8(0x00);
      }
      SAddPreMsgMult(&pkArray[0], idx, mBuf);
   }

   /* then the stored cookie */
   idx = 0;
   for ( i = 0; i < assoc->cookieLeng; i++ )
   {
      SB_PKU8(assoc->cookie[assoc->cookieLeng - 1 - i]);
   }

   chunkSize = (U16)(idx + SB_IFL_SZ);
   SB_PKU16(chunkSize);   /* chunklength */
   SB_PKU8(0x0);
   SB_PKU8(SB_ID_COOKIE);

   SB_PKU32(0x0);                     /* checksum */
   SB_PKU32(assoc->verTagPeer);        /* vTag */
   SB_PKU16(assoc->localPort);        /* peerPort */
   SB_PKU16(assoc->peerPort);         /* srcPort */

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   /* determine Checksum value to insert */
   if ( mBuf != (Buffer *) NULLP )
   {
      (Void) SFndLenMsg(mBuf, &len);
   } else {
      SPrint("Buffer not allocates \n ");
   }

   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }

#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",assoc->peerPort,\
           assoc->localPort); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu)\n", assoc->verTagPeer); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%lu)\n",checksum); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | COOKIE | flags[00000000] | length(%d)\n", chunkSize);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   SPrint(         "  | state cookie\n");
   SPrint(         "  =====================================\n\n");
#endif

   RETVOID;
} /* end buildCookieChunk */

/*     sb028.103: Added a new function to process tha data chunk bundled
*                 with cookie chunk .
*
*
*       Fun:   buildCookieWitDatChunk
*
*       Desc:  Build a COOKIE chunk with DATA chunk to send to the
*              receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/

#ifdef ANSI
PUBLIC  void buildCookieWitDatChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  void buildCookieWitDatChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         chunkSize;
   U16         i;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U32         checksum;
   U16         pad;
   U8          tmpU8;
   MsgLen      len;
#if SB_PRNTSTUFF
   Txt         pb[64];
#endif
   U8          chunkId;                 /* chunk identifier */
   U8          chunkFlg;                /* chunk flag */
   U16         chunkLeng;               /* chunk length */
   U16         streamId;
   U16         seqNr;
   Buffer      *datInd;
   U32          tsn;
   Data        data[64];


   TRC2(buildCookieWitDatChunk);
   SPrint("buildCookieWitDatChunk: building COOKIE chunk with DATA\n");

   idx = 0;
   streamId = buildPar->streamId;
   chunkId =  SB_ID_DATA;
   chunkFlg = buildPar->chunkFlg;
   tsn = buildPar->tsn;
   seqNr = buildPar->seqNr;
   len = 64;

   SB_SETUP_DAT_REQ(datInd);
   for ( (i = 1); (i <= len); i++)
   {
      SExamMsg(&data[(len - i)], datInd, (S16)(len-i) );
      SB_PKU8(data[(len - i)]);     /* pack data in reversed order*/
   }
   SB_PKU32(0x00);
   SB_PKU16(seqNr);
   SB_PKU16(streamId);
   SB_PKU32(tsn);
   chunkLeng = (U16)(16 + len);  /* data entries of type U8 */
   SB_PKU16(chunkLeng);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   printf("\n chunk len = %d, idx = %d\n\n",chunkLeng,idx);
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   if(buildPar->noBundleFlg == FALSE)
   {
      idx = 0;
      SB_SETUP_DAT_REQ(datInd);
      for ( (i = 1); (i <= len); i++)
      {
         SExamMsg(&data[(len - i)], datInd, (S16)(len-i) );
         SB_PKU8(data[(len - i)]);     /* pack data in reversed order*/
      }
      SB_PKU32(0x00);
      SB_PKU16(seqNr+1);
      SB_PKU16(streamId);
      SB_PKU32(tsn+1);
      chunkLeng = (U16)(16 + len);  /* data entries of type U8 */
      SB_PKU16(chunkLeng);
      SB_PKU8(chunkFlg);
      SB_PKU8(chunkId);
      printf("\n chunk len = %d, idx = %d\n\n",chunkLeng,idx);
      (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   }

   UNUSED(buildPar);
   len = 0;
   idx = 0;

   /* Pack the COOKIE */
   /* first the padding */
   pad = 0;
   if ( (assoc->cookieLeng & 0x03) != 0 )
   {
      pad = (U16)(4 - (assoc->cookieLeng & 0x03));
      for ( i = 0; i < pad; i++ )
      {
         SB_PKU8(0x00);
      }
      SAddPreMsgMult(&pkArray[0], idx, mBuf);
   }

   /* then the stored cookie */
   idx = 0;
   for ( i = 0; i < assoc->cookieLeng; i++ )
   {
      SB_PKU8(assoc->cookie[assoc->cookieLeng - 1 - i]);
   }
   chunkSize = (U16)(idx + SB_IFL_SZ);
   SB_PKU16(chunkSize);   /* chunklength */
   SB_PKU8(0x0);
   SB_PKU8(SB_ID_COOKIE);

   SB_PKU32(0x0);                     /* checksum */
   SB_PKU32(assoc->verTagPeer);        /* vTag */
   SB_PKU16(assoc->localPort);        /* peerPort */
   SB_PKU16(assoc->peerPort);         /* srcPort */

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   /* determine Checksum value to insert */
   if ( mBuf != (Buffer *) NULLP )
   {
      (Void) SFndLenMsg(mBuf, &len);
   } else {
      SPrint("Buffer not allocates \n ");
   }

   checksum = 0;
#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
   checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",assoc->peerPort,\
         assoc->localPort); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu)\n", assoc->verTagPeer); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%lu)\n",checksum); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | COOKIE | flags[00000000] | length(%d)\n", chunkSize);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   SPrint(         "  | state cookie\n");
   SPrint(         "  =====================================\n\n");
#endif

   RETVOID;
} /* end buildCookieWitDatChunk */


/*     sb030.103: Added new function to process the ABORT chunk bundled
*                 with cookie chunk .
*
*
*       Fun:   buildCookieWithAbortChunk
*
*       Desc:  Build a COOKIE chunk with ABORT chunk to send to the
*              receiving end. COOKIE chunk is the first chunk.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/

#ifdef ANSI
PUBLIC  void buildCookieWithAbortChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  void buildCookieWithAbortChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         chunkSize;
   U16         i;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U32         checksum;
   U16         pad;
   U8          tmpU8;
   MsgLen      len;
#if SB_PRNTSTUFF
   Txt         pb[64];
#endif
   U8          chunkId;                 /* chunk identifier */
   U8          chunkFlg;                /* chunk flag */

   TRC2(buildCookieWithAbortChunk);

   SPrint("buildCookieWithAbortChunk: building COOKIE chunk with ABORT\n");

   idx = 0;
   chunkId =  0x06;     /* could be either ABORT or ERROR chunk */
   chunkFlg = 0;
   SB_PKU16(SB_IFL_SZ);   /* chunklength */
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);


   UNUSED(buildPar);
   len = 0;
   idx = 0;

   /* Pack the COOKIE */
   /* first the padding */
   pad = 0;
   if ( (assoc->cookieLeng & 0x03) != 0 )
   {
      pad = (U16)(4 - (assoc->cookieLeng & 0x03));
      for ( i = 0; i < pad; i++ )
      {
         SB_PKU8(0x00);
      }
      SAddPreMsgMult(&pkArray[0], idx, mBuf);
   }

   /* then the stored cookie */
   idx = 0;
   for ( i = 0; i < assoc->cookieLeng; i++ )
   {
      SB_PKU8(assoc->cookie[assoc->cookieLeng - 1 - i]);
   }
   chunkSize = (U16)(idx + SB_IFL_SZ);
   SB_PKU16(chunkSize);   /* chunklength */
   SB_PKU8(0x0);
   SB_PKU8(SB_ID_COOKIE);

   SB_PKU32(0x0);                     /* checksum */
   SB_PKU32(assoc->verTagPeer);        /* vTag */
   SB_PKU16(assoc->localPort);        /* peerPort */
   SB_PKU16(assoc->peerPort);         /* srcPort */

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   /* determine Checksum value to insert */
   if ( mBuf != (Buffer *) NULLP )
   {
      (Void) SFndLenMsg(mBuf, &len);
   } else {
      SPrint("Buffer not allocates \n ");
   }

   checksum = 0;
#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
   checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",assoc->peerPort,\
         assoc->localPort); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu)\n", assoc->verTagPeer); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%lu)\n",checksum); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | COOKIE | flags[00000000] | length(%d)\n", chunkSize);
   SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   SPrint(         "  | state cookie\n");
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | ABORT | flags[00000000] | length(%d)\n",SB_IFL_SZ);
   SPrint(pb);
   SPrint(         "  =====================================\n\n");  
#endif

   RETVOID;
} /* end buildCookieWithAbortChunk */

/*
*
*       Fun:   buildCookieAckChunk
*
*       Desc:  Build an COOKIE_ACK chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildCookieAckChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildCookieAckChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U8          pkArray[20];
   U8          idx;
   U32         checksum;
   MsgLen      len;
   U32         i;
   U8          tmpU8;

   TRC2(buildCookieAckChunk)
   UNUSED(buildPar);
   len = 0;

   idx = 0;
   chunkId =  SB_ID_COOKIEACK;
   chunkLeng = 4;  /* Length of the CookieAck chunk fixed */
   chunkFlg = 0;
   verTag = assoc->verTagPeer;

   SB_PKU16(chunkLeng);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(verTag);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);
       /* determine Checksum value to insert */
    if ( mBuf != (Buffer *) NULLP )
    {
       (Void) SFndLenMsg(mBuf, &len);
    } else {
       SPrint("Buffer not allocates \n");
    }
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }

   RETVOID;
} /* end buildCookieAckChunk */

/*
*
*       Fun:   buildUnrecogChunk
*
*       Desc:  
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildUnrecogChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildUnrecogChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U8          pkArray[20];
   U8          idx;
   U32         checksum;
   MsgLen      len;
   U32         i;
   U8          tmpU8;

   TRC2(buildUnrecogChunk)
   UNUSED(buildPar);
   len = 0;

   idx = 0;
   chunkId =  0x7B;
   chunkLeng = 4;  /* Length of the CookieAck chunk fixed */
   chunkFlg = 0;
   verTag = assoc->verTagPeer;

   SB_PKU16(chunkLeng);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(verTag);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);
       /* determine Checksum value to insert */
    if ( mBuf != (Buffer *) NULLP )
    {
       (Void) SFndLenMsg(mBuf, &len);
    } else {
       SPrint("Buffer not allocates \n");
    }
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }

   RETVOID;
} /* end buildUnrecgChunk */

/*
*
*       Fun:   buildShutdwnChunk
*
*       Desc:  Build a SHUTDOWN chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildShutdwnChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildShutdwnChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U32         cumTsn;
   U16         chunkLeng;
   U8          pkArray[20];
   U16         idx;
   U32         checksum;
   /* sb034.103: Initialized the len variable to zero */
   MsgLen      len = 0;
   U16         i;
   U8          tmpU8;
#if SB_PRNTSTUFF
   Txt         pb[64];
#endif


   TRC2(buildShutdwnChunk)
   UNUSED(buildPar);
   SPrint("buildShutDownChunk: building SHUTDOWN chunk\n");

   chunkLeng = 8;                 /* Length of the Shutdwn chunk fixed */

   cumTsn = buildPar->cumTsn;

   /*Pack the parameters */
   idx = 0;
   SB_PKU32(cumTsn);

   SB_PKU16(chunkLeng);
   SB_PKU8(0x0);
   SB_PKU8(SB_ID_SDOWN);

   SB_PKU32(0x0);                     /* checksum */
   SB_PKU32(assoc->verTagPeer);       /* vTag */
   SB_PKU16(assoc->localPort);        /* peerPort */
   SB_PKU16(assoc->peerPort);         /* srcPort */

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   /* determine Checksum value to insert */
   if ( mBuf != (Buffer *) NULLP )
   {
      (Void) SFndLenMsg(mBuf, &len);
   } else {
      SPrint("Buffer not allocates \n ");
      len = 0;
   }
   
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }

#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",assoc->peerPort,\
           assoc->localPort); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu)\n", assoc->verTagPeer); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%lu)\n",checksum); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | SHUTDOWN | flags(0)00000000] | length(%d)\n", \
           chunkLeng); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | cumTSN(%lu)\n",cumTsn); SPrint(pb);
   SPrint(         "  =====================================\n\n");
#endif

   RETVOID;
} /* end buildShutdwnChunk */

/*
*
*       Fun:   buildShutdwnChunk
*
*       Desc:  Build a SHUTDOWN chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildShutdwnCmplChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildShutdwnCmplChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
/* sb058.102 : Added to remove compilation warning */
#ifdef SB_PRNTSTUFF
   U32         cumTsn;
#endif
   U16         chunkLeng;
   U8          pkArray[20];
   U16         idx;
   U32         checksum;
   MsgLen      len;
   U16         i;
   U8          tmpU8;
#if SB_PRNTSTUFF
   Txt         pb[64];
#endif


   TRC2(buildShutdwnCmplChunk)
   UNUSED(buildPar);
   SPrint("buildShutDownCmplChunk: building SHUTDOWN chunk\n");

   chunkLeng = 4;                 /* Length of the Shutdwn chunk fixed */

   /*Pack the parameters */
   idx = 0;

   SB_PKU16(chunkLeng);
   /* sb030.103: Packing the chunk flag from buildPar. */
   SB_PKU8(buildPar->chunkFlg);
   SB_PKU8(SB_ID_SDOWNCMPLT);

   SB_PKU32(0x0);                     /* checksum */
   SB_PKU32(assoc->verTagPeer);       /* vTag */
   SB_PKU16(assoc->localPort);        /* peerPort */
   SB_PKU16(assoc->peerPort);         /* srcPort */

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   /* determine Checksum value to insert */
   if ( mBuf != (Buffer *) NULLP )
   {
      (Void) SFndLenMsg(mBuf, &len);
   } else {
      SPrint("Buffer not allocates \n ");
      len = 0;
   }
   
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */
   
   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);                      
  for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }

#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",assoc->peerPort,\
           assoc->localPort); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu)\n", assoc->verTagPeer); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%lu)\n",checksum); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | SHUTDOWNCOMP | flags(0)00000000] | length(%d)\n", \
           chunkLeng); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | cumTSN(%lu)\n",cumTsn); SPrint(pb);
   SPrint(         "  =====================================\n\n");
#endif

   RETVOID;
} /* end buildShutdwnComplChunk */    


/*
*
*       Fun:   buildShutdwnAckChunk
*
*       Desc:  Build an SHUTDOWN_ACK chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildShutdwnAckChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildShutdwnAckChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U8          tmpU8;
   U16         chunkSize;
   U8          pkArray[16];
   U8          idx;
   U32         checksum;
#if SB_PRNTSTUFF
   Txt         pb[200];
#endif
   /* sb034.103: Initialized len variable to zero */
   MsgLen      len = 0;
   U32         i;

   TRC2(buildShutdwnAckChunk)
   UNUSED(buildPar);
   SPrint("  Building SHUTDOWN_ACK chunk\n");

   idx = 0;
   chunkSize = SB_IFL_SZ;
   SB_PKU16(chunkSize);   /* chunklength */
   SB_PKU8(0x0);
   SB_PKU8(SB_ID_SDOWNACK);

   SB_PKU32(0x0);                     /* checksum */
   SB_PKU32(assoc->verTagPeer);        /* vTag */
   SB_PKU16(assoc->localPort);        /* peerPort */
   SB_PKU16(assoc->peerPort);         /* srcPort */

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   /* determine Checksum value to insert */
   (Void) SFndLenMsg(mBuf, &len);
   
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }

#ifdef SB_PRNTSTUFF
   SPrint(         "  =====================================\n");
   sprintf(pb,     "  | srcPort(%d) | dstPort(%d)\n",assoc->peerPort, \
           assoc->localPort); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | vTag(%lu)\n", assoc->verTagPeer); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | checksum(%ld)\n",checksum); SPrint(pb);
   SPrint(         "  -------------------------------------\n");
   sprintf(pb,     "  | SHUTDOWN ACK | flags[00000000] | length(%d)\n",\
           chunkSize); SPrint(pb);
   SPrint(         "  =====================================\n\n");
#endif

   RETVOID;
} /* end buildShutdwnAckChunk */

/* RFC 4460 -- SB_RFC_5 */
/*
*
*       Fun:   buildHBeatChunk
*
*       Desc:  Build an HBEAT chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildHBeatChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildHBeatChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   MsgLen      len;
   U8          i;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U32         checksum;
   U8          tmpU8;

   TRC2(buildHBeatChunk)

   idx = 0;

   len = 8;
   if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4) 
   {
      SB_PKU32(peerNAddrLst_1[2]);
      SB_PKU16(0x0008);
      SB_PKU16(SB_ID_PAR_IPV4);
      len += 8;
   }

   SB_PKU32(0x12345678);
   SB_PKU16(len);
   SB_PKU16(0x0001);

   if ( buildPar->multHBParam )
   {
      if(sbAccCb.curTst.addrType == CM_NETADDR_IPV4) 
      {
         SB_PKU32(peerNAddrLst_1[3]);
         SB_PKU16(0x0008);
         SB_PKU16(SB_ID_PAR_IPV4);
         len += 8;
      }
      SB_PKU32(0x87654321);
      SB_PKU16(len);
      SB_PKU16(0x0001);
      len += 8;
   }
   len += 4; 

   SB_PKU16(len);
   SB_PKU8(0x00);
   SB_PKU8(SB_ID_HBEAT);


   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(assoc->verTagPeer);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

         /* determine Checksum value to insert */
   (Void) SFndLenMsg(mBuf, &len);
   
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
   RETVOID;
} /* end buildHBeatChunk */

 /*
*
*       Fun:   buildHBeatAckChunk
*
*       Desc:  Build an HBEAT_ACK chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildHBeatAckChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildHBeatAckChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U16         chunkLeng;
   U8          chunkFlg;
   MsgLen      len;
   U8          i;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U32         checksum;
   U8          tmpU8;

   TRC2(buildHBeatAckChunk)

   idx = 0;
   len =  buildPar->hBeatInfoLen;
   chunkLeng = (U16)(4 + len);

   for((i = 1); (i <= len); i++)
   {
      SB_PKU8(buildPar->hBeatInfo[(len-i)]);      /* Pop data buffer */
   }  /* end for  */

   chunkId =  SB_ID_HBEATACK;
   chunkFlg = 0;
   verTag = assoc->verTagPeer;

   SB_PKU16(chunkLeng);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(verTag);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

         /* determine Checksum value to insert */
   (Void) SFndLenMsg(mBuf, &len);
   
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
   RETVOID;
} /* end buildHBeatAckChunk */

/*
*
*       Fun:   buildAbortErrChunk
*
*       Desc:  Build an ABORT or ERROR chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildAbortErrChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildAbortErrChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;        /* Assocciation structure */
#endif
{
   U32         checksum;        /* adler checksum */
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLength;
   U16         causeCode;        /* code of cause */
   U16         causeLength;      /* length of cause  */
   U16         reserved;         /* reserved byte */
   U32         numMisPar;        /* number of missing parameters */
   U32         measStale;        /* measure of staleness */
   U16         streamId;
   U16         i;
   U8          tmpU8;
   MsgLen      len;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   S32         cnt;
   /* sb035.103: Changed limit of hostName and data type of hostnameLen */
   U8          hostname[512];
   U16         hostnameLen;
   U8          align;

   TRC2(buildAbortErrChunk)

   idx = 0;
   chunkId =  buildPar->chunkId;     /* could be either ABORT or ERROR chunk */
/* sb030.103: Take chunkFlg from buildPar instead of hard coding to zero. */
   chunkFlg = buildPar->chunkFlg;
   causeCode = buildPar->causeCode;

   switch (causeCode )
   {
      case SB_CHUNK_ERROR_STREAM:
         streamId = ACC_STREAMID;
         SB_PKU16(streamId);
         reserved = ACC_RESERVED;
         SB_PKU16(reserved);
         causeLength = 8;
         SB_PKU16(causeLength);
         break;

      case SB_CHUNK_ERROR_PARAM:
         SB_PKU32("0x00");
         numMisPar = buildPar->numMisPar;
         SB_PKU32(numMisPar);
         causeLength = (U16)(8 + (2*numMisPar));
         SB_PKU16(causeLength);
         break;

      case SB_CHUNK_ERROR_STALE:
         measStale = ACC_MEAS_STALE;
         SB_PKU32(measStale);
         causeLength = 8;
         SB_PKU16(causeLength);
         break;
      case SB_CHUNK_ERROR_RES:
         causeLength = 4;
         SB_PKU16(causeLength);
         break;
      case SB_CHUNK_ERROR_UNRSLV_ADDR:
         cmMemcpy(hostname,(CONSTANT U8 *)"www.trillium.com", 
                            cmStrlen((CONSTANT U8 *)"www.trillium.com"));
         /* sb035.103: Set hostnameLen to 260 for test case O.201.26 */
         if (buildPar->pkUnknownPar == TRUE)
         hostnameLen = 260; 
         else
         /* RFC 4460 -- RTR -- windows warning  */ 
         hostnameLen = (U8)cmStrlen((CONSTANT U8 *)"www.trillium.com"); 

         if (((hostnameLen+1) & 0x03) == 0 )
         {
           align = 0;
         }
         else
         {
            align = 4 - ((hostnameLen+1) & 0x03);
            for ( cnt = 0; cnt < align; cnt++)
            {
              SB_PKU8(0x00);
            }
          }
          /* Pack Null Character */
          SB_PKU8('\0');

         for(cnt=(hostnameLen-1);cnt >= 0 ;cnt--)
            SB_PKU8(hostname[cnt]);

         SB_PKU16(hostnameLen+1+4);
         SB_PKU16(SB_ID_PAR_HSTNAME_ADDR);
         SB_PKU16(4 + hostnameLen + 1 + 4);
         break;
      case SB_CHUNK_ERROR_NO_USR_DATA: /* for O.205.14  */
         SB_PKU32(buildPar->cumTsn);
         causeLength = 8;
         SB_PKU16(causeLength);
         break;
      case SB_CHUNK_ERROR_USR_INITIATED_ABORT: /* for O.205.15  */
         SB_PKU32(0x00); /* Abort reason is hard coded to 0x00 */
         causeLength = 8;
         SB_PKU16(causeLength);
         break;
      default:
         RETVOID;  /* Incorrect cause */
    }

   SB_PKU16(causeCode);

   chunkLength = (U16)(idx + SB_IFL_SZ);
   SB_PKU16(chunkLength);   /* chunklength */
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(assoc->verTagPeer);        /* vTag */
   SB_PKU16(assoc->localPort);        /* peerPort */
   SB_PKU16(assoc->peerPort);       /* srcPort */

   /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

   /* determine Checksum value to insert */
   (Void) SFndLenMsg(mBuf, &len);

   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }

   RETVOID;
} /* end buildAbortErrChunk */

/*
*
*       Fun:   buildSackChunk
*
*       Desc:  Build an ABORT chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildSackChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildSackChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;        /* Assocciation structure */
#endif
{
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U32         awnd;
   U32         cumTsn;
   U16         numFrag;        /* number of fragments */
   U8          i;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U32         checksum;
   U16         nmbDup;
   /* sb034.103: Initialized len variable to zero */
   MsgLen      len = 0;
   U8          tmpU8;

   TRC2(buildSackChunk)

   idx = 0;

   numFrag = buildPar->numFrag;
   for (i = 1; i <= numFrag; i++)
   {
      SB_PKU16( buildPar->fragEnd[(numFrag + 1 - i )] );
      SB_PKU16( buildPar->fragStart[(numFrag + 1 - i )] );
   } /* end for */

   chunkId =  SB_ID_SACK;
   chunkLeng = (U16)(16 + (4*numFrag));
   chunkFlg = 0;
   nmbDup = 0;
   verTag = assoc->verTagPeer;

   SB_PKU16(nmbDup);
   SB_PKU16(numFrag);
   awnd = buildPar->arwnd;
   SB_PKU32(awnd);
   cumTsn = buildPar->cumTsn;
   SB_PKU32(cumTsn);

   SB_PKU16(chunkLeng);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(verTag);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);

  /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

      /* determine Checksum value to insert */
   (Void) SFndLenMsg(mBuf, &len);
   
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
   RETVOID;
} /* end buildSackChunk */

/* sb003.103 - addition - new function to build SACK and ECNE chunk */
#ifdef SB_ECN
/* SATELLITE SCTP feature */ 
/*
*
*       Fun:   buildSackEcneChunk
*
*       Desc:  Build an SACK and ECNE chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildSackEcneChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildSackEcneChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;        /* Assocciation structure */
#endif
{
   U32         tsn;                     /* tsn number */
   U16         srcPort;
   U16         dstPort;
   U32         verTag;
   U8          chunkId;
   U8          chunkFlg;
   U16         chunkLeng;
   U32         awnd;
   U32         cumTsn;
   U16         numFrag;        /* number of fragments */
   U8          i;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U32         checksum;
   U16         nmbDup;
   MsgLen      len;
   U8          tmpU8;

   TRC2(buildSackEcneChunk)

   idx = 0;

   SPrint("Building SACK and ECNE chunk");
   
   numFrag = buildPar->numFrag;
   for (i = 1; i <= numFrag; i++)
   {
      SB_PKU16( buildPar->fragEnd[(numFrag + 1 - i )] );
      SB_PKU16( buildPar->fragStart[(numFrag + 1 - i )] );
   } /* end for */

   chunkId =  SB_ID_SACK;
   chunkLeng = (U16)(16 + (4*numFrag));
   chunkFlg = 0;
   nmbDup = 0;
   verTag = assoc->verTagPeer;

   SB_PKU16(nmbDup);
   SB_PKU16(numFrag);
   awnd = buildPar->arwnd;
   SB_PKU32(awnd);
   cumTsn = buildPar->cumTsn;
   SB_PKU32(cumTsn);

   SB_PKU16(chunkLeng);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);

   chunkId =  SB_ID_ECNE;
   chunkFlg = 0;
   tsn = ACC_INIT_TSN;
   len = 8;

   SB_PKU32(tsn);
   SB_PKU16(len);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);

   /* build the SCTP common header */
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(verTag);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);

  /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

      /* determine Checksum value to insert */
   (Void) SFndLenMsg(mBuf, &len);
   
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */

   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
   RETVOID;
} /* end buildSackEcneChunk */

/* sb014.103: New function to build ECNE chunk */
/*
*
*       Fun:   buildEcneChunk
*
*       Desc:  Build an ECNE chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildEcneChunk
(
Buffer           *mBuf,         /* Data received from the SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildEcneChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;         /* Data received from the SCTP */
SbAccChunkBld    *buildPar;     /* Parameters for building the chunks */
SbAccAssoc       *assoc;        /* Assocciation structure */
#endif
{
   U32         tsn;                     /* tsn number */
   U16         srcPort;
   U16         dstPort;
   U8          chunkId;
   U8          chunkFlg;
   U8          i;
   U8          pkArray[SB_MAX_LEN];
   U16         idx;
   U32         checksum;
   MsgLen      len;
   U8          tmpU8;
                                                                                                                        
   TRC2(buildEcneChunk)
   idx = 0;
   SPrint("\nBuilding ECNE chunk\n");

   chunkId =  SB_ID_ECNE;
   chunkFlg = 0;
   tsn = ACC_INIT_TSN;
   len = 8;
                                                                                                                        
   SB_PKU32(tsn);
   SB_PKU16(len);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
                                                                                                                        
   /* build the SCTP common header */
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(assoc->verTagPeer);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);
                                                                                                                        
  /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);
                                                                                                                        
      /* determine Checksum value to insert */
   (Void) SFndLenMsg(mBuf, &len);
                                                                                                                        
   checksum = 0;
#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */
                                                                                                                        
#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */
                                                                                                                        
   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
   RETVOID;
} /* end buildEcneChunk */
#endif /* SB_ECN */
/*
*
*       Fun:   buildDataChunk
*
*       Desc:  Build an ABORT chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildDataChunk
(
Buffer           *mBuf,         /* Data to be send to SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildDataChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;       /* Data to be send to SCTP */
SbAccChunkBld    *buildPar;    /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         srcPort;                 /* source port */
   U16         dstPort;                 /* destination port */
   U32         verTag;                  /* verification tag */
   U8          chunkId;                 /* chunk identifier */
   U8          chunkFlg;                /* chunk flag */
   U16         chunkLeng;               /* chunk length */
   U16         streamId;                /* stream identifier */
   U32         tsn;                     /* tsn number */
   U16         seqNr;                   /* stream sequence number */
   U16         protId;
   MsgLen      len;
   Buffer      *datInd;
   Data        data[MSG_SIZE];
   U8          pkArray[SB_MAX_LEN];
   U8          i;
   U16         idx;
   U32         checksum;
   U8          tmpU8;
   Buffer      *tmpBuf;

   TRC2(buildDataChunk)

   SPrint("Building DATA chunk");
   streamId = buildPar->streamId;
   chunkId =  SB_ID_DATA;
   chunkFlg = buildPar->chunkFlg;
   tsn = buildPar->tsn;
   seqNr = buildPar->seqNr;
   protId = ACC_PROT_ID;
   verTag = assoc->verTagPeer;
   len = 64;
   if ( (chunkFlg & 3) == 2 ) /* first piece of a segmented message */
   {
      /* Setup data buffer if there is two pieces in segmentation */
      SB_SETUP_BUNDLDAT_REQ(datInd)
   }
   else
   {
        SB_SETUP_DAT_REQ(datInd)
   }

   idx = 0;
   if ( TRUE != buildPar->noData )
   {
   for ( (i = 1); (i <= len); i++)
   {
     SExamMsg(&data[(len - i)], datInd, (S16)(len-i) );
     SB_PKU8(data[(len - i)]);     /* pack data in reversed order*/
   }
   }
   SB_PKU32(protId);
   SB_PKU16(seqNr);
   SB_PKU16(streamId);
   SB_PKU32(tsn);

   chunkLeng = (U16)(16 + len);  /* data entries of type U8 */

   if ( TRUE == buildPar->noData )
   {
      chunkLeng = (U16)(16);  /* data entries of type U8 */
   }
   SB_PKU16(chunkLeng);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(verTag);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);

  /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

      /* determine Checksum value to insert */
   (Void) SFndLenMsg(mBuf, &len);
   
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */
   
   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
   /*RFC 4460 -- MLK Fix*/
   SB_RLSMEM(datInd);

   RETVOID;
} /* end buildDataChunk */

/* sb013.103: Added new function to Build Data Chunk with size 512 */
/*
*
*       Fun:   buildLargeDataChunk
*
*       Desc:  Build an Data chunk to send to the receiving end with size 512.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildLargeDataChunk
(
Buffer           *mBuf,         /* Data to be send to SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildLargeDataChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;       /* Data to be send to SCTP */
SbAccChunkBld    *buildPar;    /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         srcPort;                 /* source port */
   U16         dstPort;                 /* destination port */
   U32         verTag;                  /* verification tag */
   U8          chunkId;                 /* chunk identifier */
   U8          chunkFlg;                /* chunk flag */
   U16         chunkLeng;               /* chunk length */
   U16         streamId;                /* stream identifier */
   U32         tsn;                     /* tsn number */
   U16         seqNr;                   /* stream sequence number */
   U16         protId;
   MsgLen      len;
   Buffer      *datInd;
   Data        data[MSG_SIZE_MAX];
   U8          pkArray[SB_MAX_LEN];
   U16          i;
   U16         idx;
   U32         checksum;
   U8          tmpU8;
   Buffer      *tmpBuf;

   TRC2(buildLargeDataChunk)

   SPrint("Building DATA chunk in buildLargeDataChunk");
   streamId = buildPar->streamId;
   chunkId =  SB_ID_DATA;
   chunkFlg = buildPar->chunkFlg;
   tsn = buildPar->tsn;
   seqNr = buildPar->seqNr;
   protId = ACC_PROT_ID;
   verTag = assoc->verTagPeer;
   len = MSG_SIZE_MAX;
   if ( (chunkFlg & 3) == 2 ) /* first piece of a segmented message */
   {
      /* Setup data buffer if there is two pieces in segmentation */
      SB_SETUP_BUNDLDAT_REQ(datInd)
   }
   else
   {
        SB_SETUP_DAT_REQ(datInd)
   }

   idx = 0;
   if ( TRUE != buildPar->noData )
   {
   for ( (i = 1); (i <= len); i++)
   {
     SExamMsg(&data[(len - i)], datInd, (S16)(len-i) );
     SB_PKU8(data[(len - i)]);     /* pack data in reversed order*/
   }
   }
   SB_PKU32(protId);
   SB_PKU16(seqNr);
   SB_PKU16(streamId);
   SB_PKU32(tsn);

   chunkLeng = (U16)(16 + len);  /* data entries of type U8 */

   if ( TRUE == buildPar->noData )
   {
      chunkLeng = (U16)(16);  /* data entries of type U8 */
   }
   SB_PKU16(chunkLeng);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(verTag);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);

  /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

      /* determine Checksum value to insert */
   (Void) SFndLenMsg(mBuf, &len);
   
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */
   
   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
   /*RFC 4460 -- MLK Fix*/
   SB_RLSMEM(datInd);

   RETVOID;
} /* end buildLargeDataChunk */

/* sb003.103 - addition - new function to form Data and Cwr chunk */
#ifdef SB_ECN
/* SATELLITE SCTP feature */ 
/*
*
*       Fun:   buildDataCwrChunk
*
*       Desc:  Build an Data and Cwr chunk to send to the receiving end.
*
*       Ret:   None
*
*       Notes:
*
*       File:  Sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC  Void buildDataCwrChunk
(
Buffer           *mBuf,         /* Data to be send to SCTP */
SbAccChunkBld    *buildPar,     /* Parameters for building the chunks */
SbAccAssoc       *assoc         /* Assocciation structure */
)
#else
PUBLIC  Void buildDataCwrChunk(mBuf, buildPar, assoc)
Buffer           *mBuf;       /* Data to be send to SCTP */
SbAccChunkBld    *buildPar;    /* Parameters for building the chunks */
SbAccAssoc       *assoc;       /* Assocciation structure */
#endif
{
   U16         srcPort;                 /* source port */
   U16         dstPort;                 /* destination port */
   U32         verTag;                  /* verification tag */
   U8          chunkId;                 /* chunk identifier */
   U8          chunkFlg;                /* chunk flag */
   U16         chunkLeng;               /* chunk length */
   U16         streamId;                /* stream identifier */
   U32         tsn;                     /* tsn number */
   U16         seqNr;                   /* stream sequence number */
   U16         protId;
   MsgLen      len;
   Buffer      *datInd;
   Data        data[MSG_SIZE];
   U8          pkArray[SB_MAX_LEN];
   U8          i;
   U16         idx;
   U32         checksum;
   U8          tmpU8;
   Buffer      *tmpBuf;

   TRC2(buildDataCwrChunk)

   SPrint("Building DATA and CWR chunk");
   streamId = buildPar->streamId;
   chunkId =  SB_ID_DATA;
   chunkFlg = buildPar->chunkFlg;
   tsn = buildPar->tsn;
   seqNr = buildPar->seqNr;
   protId = ACC_PROT_ID;
   verTag = assoc->verTagPeer;
   len = 64;

   if ((chunkFlg & 3) == 2)  /* first piece of a segmented message */
   {
      /* Setup data buffer if there is two pieces in segmentation */
      SB_SETUP_BUNDLDAT_REQ(datInd)
   }
   else
   {
      SB_SETUP_DAT_REQ(datInd)
   }

   idx = 0;
   if (TRUE != buildPar->noData)
   {
      for ((i = 1); (i <= len); i++)
      {
         SExamMsg(&data[(len - i)], datInd, (S16)(len-i) );
         SB_PKU8(data[(len - i)]);     /* pack data in reversed order*/
      }
   }
   SB_PKU32(protId);
   SB_PKU16(seqNr);
   SB_PKU16(streamId);
   SB_PKU32(tsn);

   chunkLeng = (U16)(16 + len);  /* data entries of type U8 */

   if (TRUE == buildPar->noData)
   {
      chunkLeng = (U16)(16);  /* data entries of type U8 */
   }
   SB_PKU16(chunkLeng);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);

   chunkId =  SB_ID_CWR;
   chunkFlg = 0;
   tsn = ACC_INIT_TSN;
   len = 8;

   SB_PKU32(tsn);
   SB_PKU16(len);
   SB_PKU8(chunkFlg);
   SB_PKU8(chunkId);

   /* build the SCTP common header */
   SB_PKU32(0x0);    /* checksum */
   SB_PKU32(verTag);
   dstPort = assoc->localPort;
   srcPort = assoc->peerPort;
   SB_PKU16(dstPort);
   SB_PKU16(srcPort);

  /* pack into buffer */
   (Void) SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);

      /* determine Checksum value to insert */
   (Void) SFndLenMsg(mBuf, &len);
   
   checksum = 0;

#ifdef SB_CHECKSUM
   checksum = 1L;
   for ( i = 0; i < (U32)len; i++ )
   {
      (Void) SExamMsg(&tmpU8, mBuf, (S16)i);
      checksum = sbChecksum32(checksum, &tmpU8, 1,SB_ADLER32);
   }
#endif /* SB_CHECKSUM */

#ifdef SB_CHECKSUM_CRC
     checksum = sbCheckCRCChecksum(mBuf, len);
#endif /* SB_CHECKSUM_CRC */
   
   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
   SB_RLSMEM(datInd);

   RETVOID;
} /* end buildDataCwrChunk */
#endif 

/* SB_VER13 - Added functions for version 13 */

/*
*
*       Fun:  sbInetGetHostByName
*
*       Desc: Get the list of IP address corrosponding to hostname.
*
*       Ret: None
*
*       Notes:
*
*       File:  sb_acc2.c
*
*/
#ifdef ANSI
PUBLIC S16  sbInetGetHostByName
(
S8               *hostName,     /* hostname */
CmInetIpAddrTbl  *addrTbl      /* Address Table */
)
#else
PUBLIC S16  sbInetGetHostByName(hostName, addrTbl)
S8               *hostName;      /* hostname */
CmInetIpAddrTbl  *addrTbl;      /* Address Table */
#endif
{

  U16          len;
  TRC2(sbInetGetHostByName)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* error check on parameters */
  if ((hostName == NULLP) || (addrTbl == NULLP))
  {
        RETVALUE(RFAILED);
  }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

  /* Initialise */
  addrTbl->count = 0;
  len  = cmStrlen((CONSTANT U8 *)hostName);

   if ((cmMemcmp ((U8 *)hostName, (CONSTANT U8 *)"www.trillium.com", len)) == 0)
   {
     addrTbl->netAddr[addrTbl->count++] =0x0A0A0A01;
     RETVALUE(ROK);
   }
   else
   if ((cmMemcmp ((U8 *)hostName, (CONSTANT U8 *)"www.trillium1.com", len)) == 0)
   {
       addrTbl->netAddr[addrTbl->count++] =  peerNAddrLst_2[2];
       addrTbl->netAddr[addrTbl->count++] =  peerNAddrLst_2[3];
       RETVALUE(ROK);
   }
   else
   if ((cmMemcmp((U8 *)hostName, (CONSTANT U8 *)"www.trillium2.com", len)) == 0)
   {
       addrTbl->netAddr[addrTbl->count++] =  peerNAddrLst_1[2];
       addrTbl->netAddr[addrTbl->count++] =  peerNAddrLst_1[3];
       RETVALUE(ROK);
   }

   RETVALUE(RFAILED);

} /* end  sbInetGetHostByName */


/* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
/*
 *
 *       Fun:   sbShtCntrlReq
 *
 *       Desc:  Issue control request from SH
 *
 *       Ret:   ROK   - ok
 *
 *       Notes : The interface with the SH is always LC.
 *
 *       File:  sb_acc2.c
 *
 */
#ifdef ANSI
PUBLIC S16 sbShtCntrlReq
(
U8      reqType,         /* Enable/disable    */
U8      grpType,         /* grouping criteria */
ProcId  procId,          /* Dest. procId      */
Ent     ent,             /* dest. entity      */
Inst    inst,            /* dest. instance    */
CmIntfId  intfId,        /* interface ID      */
CmIntfVer intfVer       /* interface Version */
)
#else
PUBLIC S16 sbShtCntrlReq(reqType, grpType, procId, ent, inst, intfId, intfVer)
U8      reqType;         /* Enable/disable    */
U8      grpType;         /* grouping criteria */
ProcId  procId;          /* Dest. procId      */
Ent     ent;             /* dest. entity      */
Inst    inst;            /* dest. instance    */
CmIntfId  intfId;        /* interface ID      */
CmIntfVer intfVer;       /* interface Version */
#endif
{
   ShtCntrlReqEvnt  reqInfo;

   reqInfo.reqType = reqType;
   reqInfo.hdr.transId = 1010;
   setResponse(&reqInfo.hdr.response);

   switch (reqType)
   {
      case SHT_REQTYPE_BND_ENA:
         reqInfo.s.bndEna.grpType     = grpType;
         reqInfo.s.bndEna.dstProcId   = procId;
         reqInfo.s.bndEna.dstEnt.ent  = ent;         /* entity */
         reqInfo.s.bndEna.dstEnt.inst = inst;     /* instance */
         break;
     
      case SHT_REQTYPE_UBND_DIS:
         reqInfo.s.ubndDis.grpType     = grpType;
         reqInfo.s.ubndDis.dstProcId   = procId;
         reqInfo.s.ubndDis.dstEnt.ent  = ent;         /* entity */
         reqInfo.s.ubndDis.dstEnt.inst = inst;     /* instance */
         break;
     
      case SHT_REQTYPE_SETVER:
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         reqInfo.s.svReq.grpType      = grpType;
         reqInfo.s.svReq.dstProcId    = procId;
         reqInfo.s.svReq.dstEnt.ent   = ent;
         reqInfo.s.svReq.dstEnt.inst  = inst;
         reqInfo.s.svReq.intf.intfId  = intfId;
         reqInfo.s.svReq.intf.intfVer = intfVer;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
         break;

      case SHT_REQTYPE_GETVER:
         break;
   }

   /* send an sht request primitive*/
   cmPkMiShtCntrlReq(&sbAccCb.shtPst, &reqInfo);
   RETVALUE(ROK);
} /* sbShtCntrlReq*/
#endif /* SB_RUG */

/* sb014.103: Function to calculate Ticks */
/*
 *
 *       Fun:   sbAccCalcTicks
 *
 *       Desc:  Calculate the number of ticks required.
 *
 *       Ret:   No. of ticks  - ok
 *              RFAILED       - failuer
 *
 *       Notes :
 *
 *       File:  sb_acc2.c
 *
 */
#ifdef ANSI
PUBLIC S16 sbAccCalcTicks
(
S16      resTime  /* Resolution time */
)
#else
PUBLIC S16 sbAccCalcTicks(resTime)
S16      resTime; /* Resolution time */
#endif
{
    S16      ticks = -1;

    switch(SS_TICKS_SEC)
       {
           case SS_100MS:
                         if((resTime % 100) != 0)
                             SPrint("Invalid resolution time\n");
                         else
                             ticks = resTime/100;
                         break;
           case SS_10MS:
                         if((resTime % 10) != 0)
                             SPrint("Invalid resolution time\n");
                         else
                            ticks = resTime/10;
                         break;
           case SS_1MS:
                         ticks = resTime;
                         break;
           default :
                     SPrint("Invalid system resolution time\n");
                     break;
       }
    RETVALUE(ticks);

}/* sbAccCalcTicks */

/********************************************************************30**
         End of file:     sb_acc2.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:06 2015

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
/main/3      ---      nh  1. Initial version
/main/3      ---      sb  1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000.
/main/3     sb039.102 rs  1. CRC Checksum and no Checksum tests modified.
            sb042.102 hl  1. Added change for SHT interface and Rolling
                             Up Grade
            sb044.102 rs  1. DNS Call conditioned.
            sb046.102 hl  1. Multiple IP address per endpoint support
            sb058.102 pr  1. Removed compilation warning. 
            sb060.102 pr  1. TOS changes.
            sb071.102 kp  1. Adjusted the value for maxPathReTx and 
                             maxAssocReTx 
            sb074.102 kp  1. Change the parameter type as handling 
                             logic of highest bit for INIT is changed.
/main/4      ---  rsr/ag   1. Updated for Release of 1.3
            sb003.103 ag   1. Satellite SCTP feature (under compile-time
                              flags SB_ECN & SB_SATELLITE).
                           2. Moved the smPst structure from genCfg to 
                              reConfig structure of general configuration.
            sb004.103 ag   1. Protected the changes for making smPst structure
                              reconfigurable under a new compile time flag LSB9.
            sb009.103 nuX  1. Changes made for SOL10 upgrade, and changes are under
                              SB_SOL10_MULTIPORT flag
	    sb012.103 pkaX 1. Non-Unicast Address Fix: Added non-unicast address list
			      and new function to build Init chunk.
                           2. Placed the sbLsbChkTmr() function under LSB12 flag.
            sb013.103 pkaX 1. a_rwnd Fix: New function to build data chunk.
            sb014.103 pkaX 1. Memory leak Fix: Added new function to build ECNE chunk.
                           2. New function to calculate number of ticks (timeRes).
/main/4     sb024.103 ajainx 1. Included protId parameter in status indication.
/main/4     sb028.103 ajainx 1. Added a new function to process tha data
                                chunk bundled with cookie chunk.
                             2. Purify fix.
/main/4     sb030.103 krkX   1. Added function to process abort chunk bundled
                                with cookie chunk.
                             2. Added packing of chunk flag parameter in
                                SHUTDOWN complete chunk.
                             3. Take chunkFlg from buildPar instead of hard
                                coding to zero while building the ABORT chunk.
/main/4     sb033.103 sdey   1. Initialized ret by FALSE and modified code base to 
                                remove  warning for 64 bit compilation.
/main/4     sb034.103 vsk    1. Initialized some of the uninitialized variables
                                to zero in primitive's buildShutdwnChunk,
                                buildShutdwnAckChunk and buildSackChunk to fix 
                                compilation errors on VxWorks-6.7.  
/main/4     sb035.103 vsk    1. Modified pkarray to 512 in functions 
                                buildInitChunk and buildInitAckChunk.
                             2. Modified hostName array length to 512 and 
                                hostnameLen datatype to U16 in function 
                                buildAbortErrChunk.
*********************************************************************91*/
