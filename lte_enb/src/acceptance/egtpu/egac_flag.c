
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc test code

     File:    egac_flag.c

     Sid:      egac_flag.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:31 2015

     Prg:     an
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
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "egt.h"           /* egt defines */
#include "leg.h"           /* layer management defines for SZT */

#ifdef HI
#include "lhi.h"
#endif

#include "cm_xta.h" 

#include "eg_edm.h"        /* EDM Module structures            */
#include "eg.h"            /* defines and macros for S1AP */
#include "eg_err.h"        /* S1AP error defines */
#include "egac_acc.h"        /* defines for S1AP acceptance tests */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "egt.x"           /* egt types */
#include "leg.x"           /* layer management typedefs for S1AP */

#ifdef HI
#include "lhi.x"
#endif
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.x" 
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for eGTP */
#include "egac_acc.x"      /* typedefs for eGTP acceptance tests */


Bool cmXtaFlag[EGAC_MAX_FLAGS] = 
{
   FALSE,
   TRUE,

#ifdef DEBUGP
   TRUE,
#else
   FALSE,
#endif

#ifdef IPV6_SUPPORTED
   TRUE,
#else
   FALSE,
#endif

#ifdef EGTP_C
   TRUE,
#else
   FALSE,
#endif

#ifdef EGTP_U
   TRUE,
#else
   FALSE,
#endif

#ifdef EGTP_U_MULTI_THREADED 
   TRUE,
#else
   FALSE,
#endif

/* eg001.201 Define EGTP_U_REL_9 flag */
#ifdef EGTP_U_REL_9
   TRUE,
#else
   FALSE,
#endif

#ifdef SS_MT_CB
   TRUE,
#else
   FALSE,
#endif

#ifdef EG_IPV6_SUPPORTED
   TRUE,
#else
   FALSE,
#endif

#ifdef EGTP_C_PTH_MGT
   TRUE,
#else
   FALSE,
#endif

/* eg004.201 Feature flags added*/
#ifdef CM_MIN_UPD_MSG
   TRUE,
#else
   FALSE,
#endif 

#ifdef DEBUGP
   TRUE,
#else
   FALSE,
#endif 
	
#ifdef LCSMHWMILHW
   TRUE,
#else
   FALSE,
#endif 

/* eg007.201 New flags added for multi-IP */
#ifdef EG_MULTI_IP
   TRUE,
#else
   FALSE,
#endif
/* eg009.201 - New Flag added for S2B */
#ifdef EG_S2B_SUPP
   TRUE,
#else
   FALSE,
#endif

/* eg009.201 - New Flag added for S2A */
#ifdef EG_S2A_SUPP
   TRUE,
#else
   FALSE,
#endif
/* eg010.201 - New Flag added for Outgoing Piggyback support */
#ifdef EG_PIGGYBACK_SUPP
   TRUE,
#else
   FALSE,
#endif

};

/* eg001.102 1. Multithreaded performance changes  */
Txt  cmXtaFlagStr[EGAC_MAX_FLAGS][50] =
{
   "Unknown Ifdef",
   "Unknown Ifndef",
    "EG_DEBUGP",
    "IPV6_SUPPORTED",
    "EGTP_C",
    "EGTP_U",
    "EGTP_U_MULTI_THREADED",
/* eg001.201 Define EGTP_U_REL_9 flag */
    "EGTP_U_REL_9",
    "SS_MT_CB",
    "EG_IPV6_SUPPORTED",
    "EGTP_C_PTH_MGT",
/* eg004.201 New flags added for eGTPC PSF feature support */
    "CM_MIN_UPD_MSG",
    "DEBUGP",
    "LCSMHWMILHW",
/* eg009.201 - New Flag added for S2B */
    "EG_S2B_SUPP",
/* eg009.201 - New Flag added for S2A */
    "EG_S2A_SUPP",
/* eg010.201 - New Flag added for Piggyback support */
    "EG_PIGGYBACK_SUPP",
};


/********************************************************************30**

         End of file:     egac_flag.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:31 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/2      eg001.102    rss     1. Multithreaded performance changes .
/main/3      ---    pmacharla   1. Initial for eGTP release 2.1
/main/3      eg001.201 asaurabh    1. Define EGTP_U_REL_9 flag 
/main/3      eg004.201 magnihotri  1. Header files added for eGTP-C PSF
                                   2. New flags added for eGTPC PSF feature support
/main/3      eg007.201 psingh      1. Defined flag for multi ip as EG_MULTI_IP
/main/3      eg009.201 asaurabh    1. New Flag added for S2A
                                   2. New Flag added for S2B
/main/3      eg010.201 asaurabh    1. New Flag added for Outgoing Piggyback support
*********************************************************************91*/
