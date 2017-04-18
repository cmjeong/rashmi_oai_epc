

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_pjureg.c

     Sid:      pjac_pjureg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:06 2015

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
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "pju.h"           /* PJU defines */
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_pju.h"      /* PJU Acceptance defines */

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
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_pju.x"      /* PJU Acceptance defines */

PRIVATE CmXtaCmd pjAcPjuSimpleCmd[] =
{
   {"tapa.pju.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlPjuBndReq, NULLP,
      "PJU Bind Request"
   },
   {"tapa.pju.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlPjuBndCfm, NULLP,
      "PJU Bind Confirm"
   },
   {"tapa.pju.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlPjuUnBndReq, NULLP,
      "PJU Unbind Request"
   },
   {"tapa.pju.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlPjuDatReq, NULLP,
      "PJU Dat Request"
   },
   {"tapa.pju.datcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlPjuDatCfm, NULLP,
      "PJU Dat Confirm"
   },
   {"tapa.pju.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlPjuDatInd, NULLP,
      "PJU Dat Indication"
   },
   {"tapa.pju.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlPjuStaInd, NULLP,
      "PJU Status Indication"
   },
   {"tapa.pju.datfwdreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlPjuDatFwdReq, NULLP,
      "PJU Data Forward Request"
   },
   {"tapa.pju.datfwdind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlPjuDatFwdInd, NULLP,
      "PJU Data Forward Indication"
   },

   {"tapa.pjac.shutdown", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlPjuShutdown, NULLP,
      "PJAC XTA Shutdown"
   }
};

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 pjAcPjuInit
(
Void
)
#else
PUBLIC S16 pjAcPjuInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(pjAcPjuInit);

   cnt = sizeof(pjAcPjuSimpleCmd)/sizeof(pjAcPjuSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, pjAcPjuSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* pjAcPjuInit */

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 pjAcPjuDeInit
(
Void
)
#else
PUBLIC S16 pjAcPjuDeInit()
#endif
{
   TRC2(pjAcPjuDeInit);

   pjAcUtlPjuDatReqCQMakeNull(&(kwAcCb.pxPjuCb.datReq));

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* pjAcPjuDeInit */

/********************************************************************30**

         End of file:     pjac_pjureg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:06 2015

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
/main/1      ---       vb        1. LTE PDCP Release 2.1.
*********************************************************************91*/

