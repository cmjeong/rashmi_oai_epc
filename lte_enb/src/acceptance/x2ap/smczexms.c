
/********************************************************************20**
  
     Name:     smczexms.c - Layer manager for X2AP - external interface for loose
               coupling
  
     Type:     C source file
  
     Desc:     C code for smCzActvTsk - layer manager activation function for
               X2AP
  
     File:     smczexms.c
  
     Sid:      smczexms.c@@/main/2 - Tue Aug 30 18:36:08 2011
  
     Prg:      sy
  
*********************************************************************21*/

/*

  smczexms.c - external interface for loose coupling in CZ->SM direction

Following functions are provided in this file:
         prUnpkMiLprCfgReq    - Unpack configuration request
*/

/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000XXX                      X2AP v 1.1
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
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* CZT Interface Structures */
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
#include "czac_acc.x"        /* typedefs for CZCP acceptance tests */
#include "czac_lcz.x"

/* local defines */

/* local typedefs */

/* forward references */

/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */
/*
 *
 *       Fun:    smCzActvTsk - SM task activation for CZ->SM
 *
 *       Desc:   calls SmMiLczXXXCfm/Ind based on post->event
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smczexms.c
 *
 */

#ifdef ANSI
PUBLIC S16 smCzActvTsk
(
Pst      *post,
Buffer   *mBuf
)
#else
PUBLIC S16 smCzActvTsk(post, mBuf)
Pst      *post;
Buffer   *mBuf;
#endif /* ANSI */
{
   TRC3(smCzActvTsk)
   if (post == (Pst *)NULLP)
   {
      CZ_FREEMBUF(mBuf);
      RETVALUE(RFAILED);
   }
   switch (post->event)
   {
#ifdef LCSMCZMILCZ
      case EVTLCZSTAIND:             /* Status Indication */
      {
         (Void)cmUnpkLczStaInd(SmMiLczStaInd, post, mBuf);
         break;
      }
      case EVTLCZTRCIND:
      {
         (Void)cmUnpkLczTrcInd(SmMiLczTrcInd, post, mBuf);
         break;
      }
      case EVTLCZCFGCFM:
      {
         (Void)cmUnpkLczCfgCfm(SmMiLczCfgCfm, post, mBuf);
         break;
      }
      case EVTLCZCNTRLCFM:
      {
         (Void)cmUnpkLczCntrlCfm(SmMiLczCntrlCfm, post, mBuf);
         break;
      }
      case EVTLCZSTACFM:
      {
         (Void)cmUnpkLczStaCfm(SmMiLczStaCfm, post, mBuf);
         break;
      }
      case EVTLCZSTSCFM:
      {
         (Void)cmUnpkLczStsCfm(SmMiLczStsCfm, post, mBuf);
         break;
      }
#endif
      default:
      {
         CZ_FREEMBUF(mBuf);
         break;
      }
   }
   SExitTsk();
   RETVALUE(ROK);
} /* end of smCzActvTsk() */

/********************************************************************30**
  
         End of file:     smczexms.c@@/main/2 - Tue Aug 30 18:36:08 2011
  
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
/main/1      ----     sy         1. LTE-X2AP Initial release
/main/2      ---      pt         1. LTE-X2AP 3.1 release.
*********************************************************************91*/
