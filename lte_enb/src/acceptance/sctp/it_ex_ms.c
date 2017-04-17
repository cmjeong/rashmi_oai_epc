

/********************************************************************20**

     Name:     it_ex_ms.c - Upper layer - interface with SCTP layer

     Type:     C source file

     Desc:     Sample C source code for the upper layer.
               - SCTP layer interface primitives.
               - Functions required for unpacking upper layer
                  service provider primitives in loosely coupled systems.

     File:     it_ex_ms.c

     Sid:      it_ex_ms.c@@/main/4 - Thu Jul 26 07:53:48 2007

     Prg:      hnh

*********************************************************************21*/

/*

  it_ex_ms.c -

Following functions are provided in this file:  */
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
#include "cm_os.h"       /* common Os files */
#endif
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */
#include "hit.h"
#ifdef SB_ACC 
#include "sb_acc.h"
#endif
#ifdef SB_INOP
#include "sb_ibdy.h"     /* Interop files */
#endif


/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#ifdef SB_INOP
#include "cm_os.x"       /* common Os files */
#endif
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#ifdef SB_ACC 
#include "sb_acc.x"
#endif
#ifdef SB_INOP
#include "sb_ibdy.x"     /* Interop files */
#endif

/* local defines */

/* local typedefs */

/* forward references */


/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */


/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from SCTP layer.
*               - Unpack the post structure
*               - Pass parameters to procedure in it_bdy1.c
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   It_ex_ms.c
*
*/

#ifdef ANSI
PUBLIC S16 itSbActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 itSbActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;

   TRC3(itSbActvTsk)

   ret = ROK;

   switch(pst->event)
   {
#ifdef LCITLISCT
      case SCT_EVTBNDCFM:             /* Bind confirm */
         ret = cmUnpkSctBndCfm(ItLiSctBndCfm, pst, mBuf);
         break;
      case SCT_EVTASSOCIND:            /* Assoc. Establishment indication */
         ret = cmUnpkSctAssocInd(ItLiSctAssocInd, pst, mBuf);
         break;
      case SCT_EVTASSOCCFM:            /* Assoc. Establishment confirmation */
         ret = cmUnpkSctAssocCfm(ItLiSctAssocCfm, pst, mBuf);
         break;
      case SCT_EVTTERMIND:             /* Association Termination indication */
         ret = cmUnpkSctTermInd(ItLiSctTermInd, pst, mBuf);
         break;
      case SCT_EVTTERMCFM:             /* Assoc. Termination confirmation */
         ret = cmUnpkSctTermCfm(ItLiSctTermCfm, pst, mBuf);
         break;
      case SCT_EVTSETPRICFM:           /* Set Primary confirmation */
         ret = cmUnpkSctSetPriCfm(ItLiSctSetPriCfm, pst, mBuf);
         break;
      case SCT_EVTHBEATCFM:            /*Set heartbeat confirmation */
         ret = cmUnpkSctHBeatCfm(ItLiSctHBeatCfm, pst, mBuf);
         break;
      case SCT_EVTDATIND:              /* Data Indication */
         ret = cmUnpkSctDatInd(ItLiSctDatInd, pst, mBuf);
         break;
      case SCT_EVTSTACFM:              /* Status confirm */
         ret = cmUnpkSctStaCfm(ItLiSctStaCfm, pst, mBuf);
         break;
      case SCT_EVTSTAIND:              /* Status Indication */
         ret = cmUnpkSctStaInd(ItLiSctStaInd, pst, mBuf);
         break;
      case SCT_EVTENDPOPENCFM:         /* Endpoint open confirmation */
         ret = cmUnpkSctEndpOpenCfm(ItLiSctEndpOpenCfm, pst, mBuf);
         break;
      case SCT_EVTENDPCLOSECFM:        /* Endpoint close confirmation */
         ret = cmUnpkSctEndpCloseCfm(ItLiSctEndpCloseCfm, pst, mBuf);
         break;
      case SCT_EVTFLCIND:        /* Flow control indication */
         ret = cmUnpkSctFlcInd(ItLiSctFlcInd, pst, mBuf);
         break;

#endif  /* LCITLISCT */
      default:
         SPutMsg(mBuf);
         ret = RFAILED;
         break;
   }
   SExitTsk();
   RETVALUE(ret);
} /* end of itSbActvTsk */


/********************************************************************30**

         End of file:     it_ex_ms.c@@/main/4 - Thu Jul 26 07:53:48 2007

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
/main/3      ---      sb   1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000.
            sb042.102 hl   1. Added change for SHT interface
/main/4      ---   rsr/ag  1. Updated for Release of 1.3
*********************************************************************91*/
