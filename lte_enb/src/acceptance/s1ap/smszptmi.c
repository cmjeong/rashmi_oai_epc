
/********************************************************************20**
  
     Name:     smszptmi.c - Layer Management Interface for S1AP
  
     Type:     C source file
  
     Desc:     C code for SmMiLszXxxReq functions
  
      File:    smszptmi.c
  
     Sid:      smszptmi.c@@/main/4 - Mon Jan 10 22:16:47 2011
  
     Prg:      pk
  
*********************************************************************21*/
/*

  smszptmi.c - Layer Management Interface for S1AP - SmMiLszXxxReq functions

Following functions are provided in this file:
         prUnpkMiLprCfgReq    - Unpack configuration request
*/
/*
 *     this software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *     1000XXX                      S1AP v 1.1
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
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer management defines for SZCP */
#include "sz.h"            /* defines and macros for SZ */
#include "szt.h"            /* defines and macros for SZ */
/* sz006.301: Removed un-necessary include files  */
#include "szac_asn.h"
#include "sz_err.h"        /* SZ error defines */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#include "sb_mtu.h"
#include "sb.h"
#endif    /* SB */
#include "cm_pasn.h"

#include "smsz_err.h"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

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
#include "cm_dns.x"         /* common DNS libraru defines */
#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCTP Interface Structures */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SZT Interface Structures */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for SZCP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#include "sb_mtu.x"
#include "sb.x"
#endif    /* SB */
#include "cm_pasn.x"

#include "sz.x"            /* typedefs for SZCP */

/*local defines */
#define SM_MAX_SZ_SEL 4

/*local typedefs */

/*forward references */

PUBLIC S16 PtMiLszCfgReq      ARGS((Pst *post, SzMngmt *cfg));
PUBLIC S16 PtMiLszStsReq      ARGS((Pst *post, Action action, SzMngmt *sts));
PUBLIC S16 PtMiLszStaReq      ARGS((Pst *post, SzMngmt *ssta));
PUBLIC S16 PtMiLszCntrlReq    ARGS((Pst *post, SzMngmt *cntrl));

/* public variable declarations */

/* public variable definitions */

/* private variable definitions */

/* public routines */

/* Following matrices define the mapping between the primitives called by the
 * layer manager (as SmMiLszXXXReq) and the corresponding primitives of the 
 * S1AP layer (layer management service provider) (as SzMiLszXXXReq).
 * Each primitive is mapped to one of SM_MAX_SZ_SEL functions in the array.
 * The mapping is based on post->selector.
 * Selector          #define     Coupling      Primitive
 * 0 (SEL_LC_NEW)   LCSMSZMILSZ  loose         cmPkMiLszXXXReq
 * 1                 MG          tight         SzMiLszXXXReq
 * 2+                            tight         PtMiLszXXXReq
 */

PRIVATE LszCfgReq smMiLszCfgReqMt[] =
{
#ifdef LCSMSZMILSZ
   cmPkLszCfgReq,
#else
   PtMiLszCfgReq,
#endif

#ifdef SZ
   SzMiLszCfgReq,
#else
   PtMiLszCfgReq,
#endif

};


PRIVATE LszStsReq smMiLszStsReqMt[] =
{
#ifdef LCSMSZMILSZ
   cmPkLszStsReq,
#else
   PtMiLszStsReq,
#endif

#ifdef SZ
   SzMiLszStsReq,
#else
   PtMiLszStsReq,
#endif

};


PRIVATE LszStaReq smMiLszStaReqMt[] =
{
#ifdef LCSMSZMILSZ
   cmPkLszStaReq,
#else
   PtMiLszStaReq,
#endif

#ifdef SZ
   SzMiLszStaReq,
#else
   PtMiLszStaReq,
#endif

};


PRIVATE LszCntrlReq smMiLszCntrlReqMt[] =
{
#ifdef LCSMSZMILSZ
   cmPkLszCntrlReq,
#else
   PtMiLszCntrlReq,
#endif

#ifdef SZ
   SzMiLszCntrlReq,
#else
   PtMiLszCntrlReq,
#endif

};


/*
 *
 *       Fun:    SmMiLszCfgReq - Configuration request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smszptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszCfgReq
(
Pst     *post,       /* post structure */
SzMngmt *cfg        /* management structure */
)
#else
PUBLIC S16 SmMiLszCfgReq(post, cfg)
Pst     *post;       /* post structure */
SzMngmt *cfg;       /* management structure */
#endif
{

   TRC3(SmMiLszCfgReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_SZ_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLszCfgReqMt[post->selector]))(post, cfg));
} /* end of SmMiLszCfgReq() */

/*
 *
 *       Fun:    SmMiLszStsReq - Statistics request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smszptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszStsReq
(
Pst     *post,       /* post structure */
Action action,
SzMngmt *sts        /* management structure */
)
#else
PUBLIC S16 SmMiLszStsReq(post, action, sts)
Pst     *post;       /* post structure */
Action action;
SzMngmt *sts;       /* management structure */
#endif
{
   TRC3(SmMiLszStsReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_SZ_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLszStsReqMt[post->selector]))(post, action, sts));
} /* end of SmMiLszStsReq() */

/*
 *
 *       Fun:    SmMiLszStaReq - Status request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smszptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszStaReq
(
Pst     *post,       /* post structure */
SzMngmt *ssta        /* management structure */
)
#else
PUBLIC S16 SmMiLszStaReq(post, ssta)
Pst     *post;       /* post structure */
SzMngmt *ssta;       /* management structure */
#endif
{
   TRC3(SmMiLszStaReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_SZ_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLszStaReqMt[post->selector]))(post, ssta));
} /* end of SmMiLszStaReq() */

/*
 *
 *       Fun:    SmMiLszCntrlReq - Control request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smszptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLszCntrlReq
(
Pst     *post,       /* post structure */
SzMngmt *cntrl        /* management structure */
)
#else
PUBLIC S16 SmMiLszCntrlReq(post, cntrl)
Pst     *post;       /* post structure */
SzMngmt *cntrl;       /* management structure */
#endif
{
   TRC3(SmMiLszCntrlReq)

#if (ERRCLASS & ERRCLS_DEBUG)
   if (post == (Pst *) NULLP || post->selector >= SM_MAX_SZ_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE((*(smMiLszCntrlReqMt[post->selector]))(post, cntrl));
} /* end of SmMiLszCntrlReq() */

/*
 *
 *       Fun:    PtMiLszCfgReq - portable configuration request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smszptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLszCfgReq
(
Pst     *post,       /* post structure */
SzMngmt *cfg        /* management structure */
)
#else
PUBLIC S16 PtMiLszCfgReq(post, cfg)
Pst     *post;       /* post structure */
SzMngmt *cfg;       /* management structure */
#endif
{
   TRC3(PtMiLszCfgReq)

   UNUSED(post);
   UNUSED(cfg);
   RETVALUE(RFAILED);
} /* end of PtMiLszCfgReq() */

/*
 *
 *       Fun:    PtMiLszStsReq - portable statistics request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smszptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLszStsReq
(
Pst     *post,       /* post structure */
Action action,
SzMngmt *sts        /* management structure */
)
#else
PUBLIC S16 PtMiLszStsReq(post, action, sts)
Pst     *post;       /* post structure */
Action action;
SzMngmt *sts;       /* management structure */
#endif
{
   TRC3(PtMiLszStsReq)

   UNUSED(post);
   UNUSED(action);
   UNUSED(sts);
   RETVALUE(RFAILED);
} /* end of PtMiLszStsReq() */

/*
 *
 *       Fun:    PtMiLszStaReq - portable status request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smszptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLszStaReq
(
Pst     *post,       /* post structure */
SzMngmt *ssta        /* management structure */
)
#else
PUBLIC S16 PtMiLszStaReq(post, ssta)
Pst     *post;       /* post structure */
SzMngmt *ssta;       /* management structure */
#endif
{
   TRC3(PtMiLszStaReq)

   UNUSED(post);
   UNUSED(ssta);
   RETVALUE(RFAILED);
} /* end of PtMiLszStaReq() */

/*
 *
 *       Fun:    PtMiLszCntrlReq - portable control request
 *
 *       Desc:  
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   smszptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtMiLszCntrlReq
(
Pst     *post,       /* post structure */
SzMngmt *cntrl        /* management structure */
)
#else
PUBLIC S16 PtMiLszCntrlReq(post, cntrl)
Pst     *post;       /* post structure */
SzMngmt *cntrl;       /* management structure */
#endif
{
   TRC3(PtMiLszCntrlReq)

   UNUSED(post);
   UNUSED(cntrl);
   RETVALUE(RFAILED);
} /* end of PtMiLszCntrlReq() */

/********************************************************************30**
  
         End of file:     smszptmi.c@@/main/4 - Mon Jan 10 22:16:47 2011
  
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
/main/4      ---      vvashishth  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301   akaranth 1. Support for source RNC to target RNC.
*********************************************************************91*/
