

/********************************************************************20**

     Name:    PDCP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    pjac_flag.c

     Sid:      pjac_flag.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:47 2015

     Prg:     Adarsh 
*********************************************************************21*/


/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */


#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */

#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */


Bool cmXtaFlag[PJAC_MAX_FLAGS] = 
{
   FALSE,
   TRUE,
/*#ifdef KW_PDCP*/
#ifndef KW_PDCP
#ifdef PJ_SEC_ASYNC
   TRUE,
#else
   FALSE,
#endif
#ifdef PJ_CMP_ASYNC
   TRUE,
#else
   FALSE,
#endif
#ifdef CCPU_OPT
   TRUE,
#else
   FALSE,
#endif
   /* kw005.201 added support for R9 and L2 Measurement */
   FALSE,
   TRUE,
   TRUE,
#else /* KW_PDCP */
   FALSE,
   TRUE,
   TRUE,
   TRUE,
   TRUE,
   TRUE,
#endif /* KW_PDCP */
#ifdef LTE_L2_MEAS  /* kw005.201 added support for L2 Measurement */
   TRUE,
#else
   FALSE,
#endif/* LTE_L2_MEAS */
#ifdef LTE_RLC_R9
   TRUE,
#else
   FALSE,
#endif /* LTE_RLC_R9 */
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
   FALSE,
#ifdef LTEMAC_R9  /*LTEMAC_R9=16 in cm_xta_py.py*/
   TRUE,
#else
   FALSE,
#endif /* LTEMAC_R9 */
};

Txt  cmXtaFlagStr[PJAC_MAX_FLAGS][50] =
{
   "Unknown Ifdef",
   "Unknown Ifndef",
/*#ifdef KW_PDCP*/
#ifndef KW_PDCP
   "PJ_SEC_ASYNC",
   "PJ_CMP_ASYNC",
   "CCPU_OPT",
   "Unknown Ifdef",
   "Unknown Ifdef",
#else
   "Unknown Ifdef",
   "Unknown Ifdef",
   "Unknown Ifdef",
   "Unknown Ifdef",
   "Unknown Ifdef",
#endif /* KW_PDCP */
   "LTE_L2_MEAS",    /* kw005.201 added support for L2 Measurement */
   "LTE_RLC_R9",
   "Unknown Ifdef",
   "Unknown Ifdef",
   "Unknown Ifdef",
   "Unknown Ifdef",
   "Unknown Ifdef",
   "Unknown Ifdef",
   "LTEMAC_R9",
};

/********************************************************************30**

         End of file:     pjac_flag.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:47 2015

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
/main/1      ---      vb         1. LTE PDCP Initial release 2.1
*********************************************************************91*/
