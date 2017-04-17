

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_pjureg.c

     Sid:      kwac_pjureg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:38 2014

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
#include "pju.h"           /* PJU defines */
#include "rgu.h"           /* RGU defines */
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_pju.h"      /* PJU Acceptance defines */

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
#include "pju.x"           /* PJU */
#include "rgu.x"           /* RGU */
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_pju.x"      /* PJU Acceptance defines */

#ifdef KW_PDCP
PRIVATE CmXtaCmd kwAcPjuSimpleCmd[] =
{
   {"tapa.pju.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlPjuBndReq, NULLP,
      "PJU Bind Request"
   },
   {"tapa.pju.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlPjuBndCfm, NULLP,
      "PJU Bind Confirm"
   },
   {"tapa.pju.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlPjuUnBndReq, NULLP,
      "PJU Unbind Request"
   },
   {"tapa.pju.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlPjuDatReq, NULLP,
      "PJU Dat Request"
   },
   {"tapa.pju.datcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlPjuDatCfm, NULLP,
      "PJU Dat Confirm"
   },
   {"tapa.pju.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlPjuDatInd, NULLP,
      "PJU Dat Indication"
   },
   {"tapa.pju.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlPjuStaInd, NULLP,
      "PJU Status Indication"
   },
   {"tapa.pju.datfwdreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlPjuDatFwdReq, NULLP,
      "PJU Data Forward Request"
   },
   {"tapa.pju.datfwdind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlPjuDatFwdInd, NULLP,
      "PJU Data Forward Indication"
   }
};

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcPjuInit
(
Void
)
#else
PUBLIC S16 kwAcPjuInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(kwAcPjuInit);

   cnt = sizeof(kwAcPjuSimpleCmd)/sizeof(kwAcPjuSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcPjuSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* kwAcPjuInit */

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcPjuDeInit
(
Void
)
#else
PUBLIC S16 kwAcPjuDeInit()
#endif
{
   TRC2(kwAcPjuDeInit);

   kwAcUtlPjuDatReqCQMakeNull(&(kwAcCb.pxPjuCb.datReq));

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* kwAcPjuDeInit */

#endif /* KW_PDCP */
/********************************************************************30**

         End of file:     kwac_pjureg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:38 2014

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
/main/1      ---   mn         1. LTERLC Release 2.1.
*********************************************************************91*/


