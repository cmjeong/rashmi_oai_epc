
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc test code

     File:    czac_flag.c

     Sid:      czac_flag.c@@/main/2 - Tue Aug 30 18:35:46 2011

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
#include "cm_pasn.h"
#include "cm_dns.h"         /* common DNS libraru defines */

#include "cz.h"            /* defines and macros for CZ */
#include "lcz.h"            /* defines and macros for CZ */
#include "sct.h"            /* defines and macros for CZ */
#include "czt.h"            /* defines and macros for CZ */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for CZ acceptance tests */
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
#include "cm_pasn.x"
#include "cm_dns.x"         /* common DNS libraru defines */
#ifdef SB
#include "lsb.h"            /* SCTP layer managment defines */
#endif /*SB*/
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/

#include "cm_xta.x" 
#include "sct.x"           /* typedefs for STCP */
#include "lcz.x"           /* layer management typedefs for CZCP */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* typedefs for CZCP */
#include "cz.x"            /* typedefs for CZCP */
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#endif /*SB*/
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for X2AP */
#include "czac_acc.x"        /* typedefs for X2AP acceptance tests */

#ifdef DM
#include "czac_sct.x"
#endif /*DM*/



Bool cmXtaFlag[CZAC_MAX_FLAGS] = 
{
   FALSE,
   TRUE,

#ifdef CZ_DBG
   TRUE,
#else
   FALSE,
#endif
#ifdef LCLCZ
   TRUE,
#else
   FALSE,
#endif
#ifdef CZAC_LKSCTP
   TRUE,
#else
   FALSE,
#endif
#ifdef CZAC_SCTP
   TRUE,
#else
   FALSE,
#endif
#ifdef DEBUGP
   TRUE,
#else
   FALSE,
#endif
#ifdef DM
   TRUE,
#else
   FALSE,
#endif
#if defined(CZAC_SCTP) || defined(CZAC_LKSCTP)
   TRUE,
#else
   FALSE,
#endif


};

Txt  cmXtaFlagStr[CZAC_MAX_FLAGS][50] =
{
   "Unknown Ifdef",
   "Unknown Ifndef",
   "CZ_DBG",
   "LCLCZ",
   "CZAC_LKSCTP",
   "CZAC_SCTP",
   "DEBUGP",
   "DM",
   "CZAC_INTSCTP"
};


/********************************************************************30**

         End of file:     czac_flag.c@@/main/2 - Tue Aug 30 18:35:46 2011

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
/main/1      ---     sy       1. LTE-X2AP Initial  Release.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
