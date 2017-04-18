

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_libreg.c

     Sid:      pjac_libreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:56 2015

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
#include "pju.h"           /* PJU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_lib.h"      /* LIB Acceptance defines */
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
#include "pju.x"           /* PJU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_lib.x"      /* LIB Acceptance defines */
#include "pjac_acc.x"      /* Acceptance defines */


PRIVATE CmXtaCmd kwAcObdSimpleCmd[] =
{
   {"tapa.obd.directive", CMXTA_TYPE_DIR, CMXTA_SUBTYPE_OTHER, pjAcLibHdlDirective, NULLP,
      "Directives for OBD"
   },
#ifdef PJ_SEC_ASYNC
   {"tapa.obd.intProt.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcLibHdlIntProtOut, NULLP,
      "OBD Integrity Protect"
   },
   {"tapa.obd.intVer.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcLibHdlIntVerOut, NULLP,
      "OBD Integrity Verification "
   },
   {"tapa.obd.cipher.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcLibHdlCipherOut, NULLP,
      "OBD Cipher Text"
   },
   {"tapa.obd.decipher.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcLibHdlDecipherOut, NULLP,
      "OBD Decipher Text"
   },
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
   {"tapa.obd.comp.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcLibHdlCompOut, NULLP,
      "OBD Cipher Text"
   },
   {"tapa.obd.decomp.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcLibHdlDecmpOut, NULLP,
      "OBD Decipher Text"
   },
#endif /* PJ_CMP_ASYNC */
};

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 pjAcObdInit
(
Void
)
#else
PUBLIC S16 pjAcObdInit()
#endif
{
   U16   cnt = 0;
   S16   ret = ROK;

   TRC2(pjAcObdInit);

   cnt = sizeof(kwAcObdSimpleCmd)/sizeof(kwAcObdSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcObdSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* pjAcObdInit */

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 pjAcObdDeInit
(
Void
)
#else
PUBLIC S16 pjAcObdDeInit()
#endif
{
   TRC2(pjAcObdDeInit);


   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* pjAcObdDeInit */


/********************************************************************30**

         End of file:     pjac_libreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:56 2015

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
/main/1      ---      vb         1. LTE PDCP Initial Release 2.1
*********************************************************************91*/

