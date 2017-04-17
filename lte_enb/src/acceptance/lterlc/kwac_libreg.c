

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_obdreg.c

     Sid:      kwac_libreg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:30 2014

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
#include "pju.h"           /* PJU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_lib.h"      /* LIB Acceptance defines */
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
#include "pju.x"           /* PJU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_lib.x"      /* LIB Acceptance defines */
#include "kwac_acc.x"      /* Acceptance defines */


#ifdef KW_PDCP

PRIVATE CmXtaCmd kwAcObdSimpleCmd[] =
{
   {"tapa.obd.directive", CMXTA_TYPE_DIR, CMXTA_SUBTYPE_OTHER, kwAcLibHdlDirective, NULLP,
      "Directives for OBD"
   },
#ifdef PJ_SEC_ASYNC
   {"tapa.obd.intProt.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcLibHdlIntProtOut, NULLP,
      "OBD Integrity Protect"
   },
   {"tapa.obd.intVer.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcLibHdlIntVerOut, NULLP,
      "OBD Integrity Verification "
   },
   {"tapa.obd.cipher.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcLibHdlCipherOut, NULLP,
      "OBD Cipher Text"
   },
   {"tapa.obd.decipher.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcLibHdlDecipherOut, NULLP,
      "OBD Decipher Text"
   },
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
   {"tapa.obd.comp.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcLibHdlCompOut, NULLP,
      "OBD Cipher Text"
   },
   {"tapa.obd.decomp.out", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcLibHdlDecmpOut, NULLP,
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
PUBLIC S16 kwAcObdInit
(
Void
)
#else
PUBLIC S16 kwAcObdInit()
#endif
{
   U16   cnt = 0;
   S16   ret = ROK;

   TRC2(kwAcObdInit);

   cnt = sizeof(kwAcObdSimpleCmd)/sizeof(kwAcObdSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcObdSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* kwAcObdInit */

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcObdDeInit
(
Void
)
#else
PUBLIC S16 kwAcObdDeInit()
#endif
{
   TRC2(kwAcObdDeInit);


   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* kwAcObdDeInit */

#endif /* KW_PDCP */


/********************************************************************30**

         End of file:     kwac_libreg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:30 2014

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
/main/1      ---   mn         1. Initial Release.
*********************************************************************91*/


