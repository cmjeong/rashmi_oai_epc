
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc test code

     File:    szac_flag.c

     Sid:      szac_flag.c@@/main/4 - Mon Jan 10 22:15:40 2011

     Prg:     mn
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
/* sz006.301: Removed un-necessary include files  */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"             /* System Agent */
#endif /* SZ_FTHA */
#include "sct.h"           /* SB (SCTP) layer */
#include "szt.h"           /* szt defines */
#include "szac_asn.h"
#include "lsz.h"           /* layer management defines for SZT */

#ifdef HI
#include "lhi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h" 
#include "cm_pasn.h"

#include "sz.h"            /* defines and macros for S1AP */
#include "sz_err.h"        /* S1AP error defines */
#include "szac_acc.h"        /* defines for S1AP acceptance tests */
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
#include "szt.x"           /* szt types */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"             /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for S1AP */

#ifdef HI
#include "lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_pasn.x"
#include "cm_xta.x" 
#include "sz.x"            /* typedefs for S1AP */
#include "szac_acc.x"        /* typedefs for S1AP acceptance tests */

#ifdef DM
#include "szac_sct.x"
#endif /*DM*/


Bool cmXtaFlag[SZAC_MAX_FLAGS] = 
{
   FALSE,
   TRUE,

#ifdef DEBUGP
   TRUE,
#else
   FALSE,
#endif
#ifdef LCLSZ
   TRUE,
#else
   FALSE,
#endif
#ifdef SZAC_LKSCTP
   TRUE,
#else
   FALSE,
#endif
#ifndef SZAC_LKSCTP
   TRUE,
#else
   FALSE,
#endif
#ifdef SZ_MME
   TRUE,
#else
   FALSE,
#endif
#ifdef SZAC_INTG_TEST
   TRUE,
#else
   FALSE,
#endif
#ifdef SZ_ENB
   TRUE,
#else
   FALSE,
#endif
#ifdef SZ_MME
   TRUE,
#else
   FALSE,
#endif
#ifdef SZAC_VXWORKS
   TRUE,
#else
   FALSE,
#endif
#ifdef SZ_ACC_TST_ESC_FUNC
   TRUE,
#else 
   FALSE,
#endif 
#ifdef LSZV1
   TRUE,
#else
   FALSE,
#endif
#ifdef CM_PASN_CRIT_HANDL
   TRUE,
#else
   FALSE,
#endif
/* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_RUG
   TRUE,
#else
   FALSE,
#endif
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
   TRUE,
#else
   FALSE,
#endif
/* sz005.301: Added for S1 abort request */
#ifdef SZTV2
   TRUE,
#else
   FALSE,
#endif
/* sz008.301: support for Source RNC to Target RNC */
#ifdef SZTV3
   TRUE,
#else
   FALSE,
#endif

};

/* sz003.301: Updted for PSF-S1AP 3.1 release */
Txt  cmXtaFlagStr[SZAC_MAX_FLAGS][50] =
{
   "Unknown Ifdef",
   "Unknown Ifndef",
   "SZ_DBG",
   "SZAC_LSZ_LC",
   "SZ_KSCTP",
   "SZ_SCTP",
   "SZAC_DYN_PEER",
   "SZAC_INTG_TEST",
   "SZAC_ENB",
   "SZAC_MME",
   "SZAC_VXWORKS",
   "SZ_ACC_TST_ESC_FUNC",
   "LSZV1",
   "CM_PASN_CRIT_HANDL",
   "SZ_RUG",
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
   "SZTV1",
#endif /* SZTV1 */
/* sz005.301: Added for S1 abort request */
#ifdef SZTV2
   "SZTV2"
#endif /* SZTV2 */
/* sz008.301: support for Source RNC to Target RNC */
#ifdef SZTV3
   "SZTV3"
#endif /* SZTV3 */
};


/********************************************************************30**

         End of file:     szac_flag.c@@/main/4 - Mon Jan 10 22:15:40 2011

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
/main/4      ---      vvashishth  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz004.301   va    1. Updated for Transparent Container Enc/Dec 
/main/4   sz005.301   va    1. Updated for S1 abort request from application 
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
