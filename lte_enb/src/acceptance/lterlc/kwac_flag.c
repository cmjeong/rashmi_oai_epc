

/********************************************************************20**

     Name:    RLC - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    kwac_flag.c

     Sid:      kwac_flag.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:26 2014

     Prg:     cp 
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
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */

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
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */


Bool cmXtaFlag[KWAC_MAX_FLAGS] = 
{
   FALSE,
   TRUE,
#ifdef KW_PDCP
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

Txt  cmXtaFlagStr[KWAC_MAX_FLAGS][50] =
{
   "Unknown Ifdef",
   "Unknown Ifndef",
#ifdef KW_PDCP
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

         End of file:     kwac_flag.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:26 2014

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
/main/1      ---       cp         1. Initial release.
/main/2      ---       gk         1. LTE RLC PDCP Release 2.1.
/main/3  kw005.201     rd         1. Added 2 flags for L2M feature
                                  2. Added LTEMAC_R9 flag as well.
*********************************************************************91*/

