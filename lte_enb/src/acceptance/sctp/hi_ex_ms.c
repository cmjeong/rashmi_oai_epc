

/********************************************************************20**

     Name:     hi_ex_ms.c - Upper layer - interface with SCTP layer

     Type:     C source file

     Desc:     Sample C source code for the lower layer.
               - SCTP layer interface primitives.
               - Functions required for unpacking layer management
                 service provider primitives in loosely coupled systems.

     File:     hi_ex_ms.c

     Sid:      hi_ex_ms.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:09 2015

     Prg:      mrw

*********************************************************************21*/

/*

  hi_ex_ms.c -

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
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS library */
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
#include "cm_dns.x"        /* common DNS library */
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
*       Desc:   Processes received event from SCTP layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   Hi_ex_ms.c
*
*/

#ifdef ANSI
PUBLIC S16 hiSbActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 hiSbActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;
   /* sb032.102 :  IPV6 Support Added */
#ifdef IPV6_OPTS_SUPPORTED
   Mem memInfo;
#endif

   TRC3(hiSbActvTsk)

   ret = ROK;
   switch(pst->event)
   {
#ifdef LCHIUIHIT     /* LCHIUIHIT #2 */
      case EVTHITBNDREQ:             /* Bind request */
         ret = cmUnpkHitBndReq(HiUiHitBndReq, pst, mBuf);
         break;
      case EVTHITSRVOPENREQ:         /* ServOpen request */
         ret = cmUnpkHitServOpenReq(HiUiHitServOpenReq, pst, mBuf);
         break;
      case EVTHITDISCREQ:            /* Disconnect request */
         ret = cmUnpkHitDiscReq(HiUiHitDiscReq, pst, mBuf);
         break;
      case EVTHITUDATREQ:            /* Disconnect request */
   /* sb032.102 :  IPV6 Support Added */
#ifdef IPV6_OPTS_SUPPORTED
         memInfo.region = pst->region;
         memInfo.pool = pst->pool;
         ret = cmUnpkHitUDatReq(HiUiHitUDatReq, pst, mBuf, &memInfo);
#else
         ret = cmUnpkHitUDatReq(HiUiHitUDatReq, pst, mBuf);
#endif
         break;
#endif      /* LCHIUIHIT #2 */
      default:
         SPutMsg(mBuf);
         ret = RFAILED;
         break;
   }
   SExitTsk();
   RETVALUE(ret);
} /* end of hiSbActvTsk */


/********************************************************************30**

         End of file:     hi_ex_ms.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:09 2015

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
/main/3      ---      mrw    1. Initial version
 /main/3     ---      sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
            sb042.102 hl     1. Added change for SHT interface
/main/4      ---   rsr/ag    1. Updated for Release of 1.3
*********************************************************************91*/
