
/********************************************************************20**

     Name:    X2AP

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    czac_lczhdl.c

     Sid:      rs_ex_ms.c@@/main/2 - Tue Aug 30 18:36:07 2011

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
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "lcz.h"           /* layer management defines for CZCP */
#include "cz.h"            /* defines and macros for CZ */
#include "czt.h"            /* defines and macros for CZ */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for CZ acceptance tests */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#include "../../sctp/sb_mtu.h"
#include "../../sctp/sb.h"
#endif    /* SB */

#include "cm_xta.h" 


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
#include "czt_asn.x"           /* CZT Interface Structures */
#include "czt.x"           /* CZT Interface Structures */
#include "lcz.x"           /* layer management typedefs for CZCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#include "../../sctp/sb_mtu.x"
#include "../../sctp/sb.x"
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for CZCP */
#include "rs.x"            /* typedefs for CZCP */
#include "czac_acc.x"        /* typedefs for CZCP acceptance tests */
#include "czac_lcz.x"

/* cz001.101 : CR Fixes */
/*
 *
 *       Fun:    rsActvInit - X2AP user initialization function
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   rs_ex_ms.c
 *
 */
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 rsActvInit
(
ProcId   procId,
Ent      ent,                 /* entity */
Inst     inst,                /* instance */
Region   region,              /* region */
Reason   reason,               /* reason */
Void   **xxCb               /* xxCb pointer */
)
#else
PUBLIC S16 rsActvInit(procId, ent, inst, region, reason, xxCb)
ProcId   procId;
Ent      ent;                 /* entity */
Inst     inst;                /* instance */
Region   region;              /* region */
Reason   reason;              /* reason */
Void   **xxCb;
#endif /*ANSI*/
#else /*SS_MULTIPLE_PROCS*/
#ifdef ANSI
PUBLIC S16 rsActvInit
(
Ent      ent,                 /* entity */
Inst     inst,                /* instance */
Region   region,              /* region */
Reason   reason               /* reason */
)
#else
PUBLIC S16 rsActvInit(ent, inst, region, reason)
Ent      ent;                 /* entity */
Inst     inst;                /* instance */
Region   region;              /* region */
Reason   reason;              /* reason */
#endif /* ANSI */
#endif /*SS_MULTIPLE_PROCS */
{
   TRC3(rsActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   (Void)rsInitExt();
   RETVALUE(ROK);
} /* end of rsActvInit() */

/*
 *
 *       Fun:    rsInitExt - external initialization
 *
 *       Desc:   performs additional initializations as required
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  to be changed by the customer if required
 *
         File:   rs_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 rsInitExt
(
void
)
#else
PUBLIC S16 rsInitExt()
#endif /* ANSI */
{
   TRC2(rsInitExt)
   RETVALUE(ROK);
} /* end of rsInitExt()*/


/*
 *
 *       Fun:    rsActvTsk - X2AP user activation
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   rs_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 rsActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else
PUBLIC S16 rsActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
   Mem sMem;

   TRC3(rsActvTsk)
#if (ERRCLASS & ERRCLS_DEBUG)
   if (pst == (Pst *)NULLP)
   {
      if (mBuf != (Buffer *)NULLP)
      {
         (Void)SPutMsg(mBuf);
      }
      RETVALUE(RFAILED);
   }
   if (mBuf == (Buffer *)NULLP)
   {
      CZLOGERROR(ERRCLS_DEBUG, ECZXXX, ERRZERO, 
         "Null mBuf in rsActvTsk\n");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   sMem.region = DFLT_REGION;
   sMem.pool = DFLT_POOL;

   switch (pst->event)
   {
#if ((defined(LCRSLICZT)) || ((defined(LWLCRSLICZT))))
      case EVTCZTBNDCFM:
      {
         (Void)cmUnpkCztBndCfm(RsLiCztBndCfm, pst, mBuf);
         break;
      }

      case EVTCZTGPIND:
      {
         (Void)cmUnpkCztGpInd(RsLiCztGpInd, pst, mBuf); 
         break;
      }

      case EVTCZTGPCFM:
      {
         (Void)cmUnpkCztGpCfm(RsLiCztGpCfm, pst, mBuf); 
         break;
      }

      case EVTCZTBMPIND:
      {
         (Void)cmUnpkCztBmpInd(RsLiCztBmpInd, pst, mBuf); 
         break;
      }
     case EVTCZTBMPCFM:
      {
         (Void)cmUnpkCztBmpCfm(RsLiCztBmpCfm, pst, mBuf); 
         break;
      }
      case EVTCZTGPERRIND:
      {
         (Void)cmUnpkCztGpErrInd(RsLiCztGpErrInd, pst, mBuf); 
         break;
      }
      case EVTCZTERRIND:
      {
         (Void)cmUnpkCztLclErrorInd(RsLiCztLclErrorInd, pst, mBuf); 
         break;
      }

      case EVTCZTSTAIND:
      {
         (Void)cmUnpkCztStatusInd(RsLiCztStatusInd, pst, mBuf);
         break;
      }
      case EVTCZTPEERASSOCIND:
      {
         (Void)cmUnpkCztDynamPeerAssocInd(RsLiCztDynamPeerAssocInd, pst, mBuf);
         break;
      }
 
      case EVTCZTLOCALRELCFM:
      {
         (Void)cmUnpkCztRelCfm(RsLiCztRelCfm, pst, mBuf);
         break;
      }
 
      case EVTCZTAUDCFM:
      {
         (Void)cmUnpkCztAudCfm(RsLiCztAudCfm, pst, mBuf);
         break;
      }
 
#endif /* LCRSLICZT */
      default:
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         CZLOGERROR(ERRCLS_DEBUG, ECZXXX, ERRZERO, 
            "invalid pst->event in rsActvTsk\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
         (Void)SPutMsg(mBuf);
         break;
      }
   }
   (Void)SExitTsk();
   RETVALUE(ROK);
} /* end of rsActvTsk() */

/********************************************************************30**

         End of file:     rs_ex_ms.c@@/main/2 - Tue Aug 30 18:36:07 2011
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
/main/1      ---        sy       1. Updated for Release X2AP
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---      pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
