

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_kwureg.c

     Sid:      pjac_kwureg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:51 2015

     Prg:     adarsh
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
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_kwu.h"      /* KWU Acceptance defines */

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
#include "pjac_kwu.x"      /* KWU Acceptance defines */

PRIVATE CmXtaCmd kwAcKwuSimpleCmd[] =
{
   {"tapa.dummy.kwu.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuBndReq, NULLP,
      "KWU Bind Request"
   },
   {"tapa.dummy.kwu.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuBndCfm, NULLP,
      "KWU Bind Confirm"
   },
   {"tapa.dummy.kwu.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuUnBndReq, NULLP,
      "KWU Unbind Request"
   },
   {"tapa.dummy.kwu.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuDatReq, NULLP,
      "KWU Dat Request"
   },
   {"tapa.dummy.kwu.datcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuDatCfm, NULLP,
      "KWU Dat Confirm"
   },
   {"tapa.dummy.kwu.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuDatInd, NULLP,
      "KWU Dat Indication"
   },
/*   
   {"tapa.dummy.kwu.discsdu", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuDiscSduReq, NULLP,
      "KWU Discard SDU Request"
   },  */ 
   {"tapa.dummy.kwu.reestcmpind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuReEstCmpInd, NULLP,
      "PJU ReEst Complete Indication"
   },
   /* kw005.201, added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   {"tapa.dummy.kwu.datackind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuDatAckInd, NULLP,
      "KWU Data Ack Indication"
   },
#endif
   {"tapa.dummy.kwu.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuStaInd, NULLP,
      "KWU Status Indication"
   },
   {"tapa.dummy.kwu.shutdown", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuShutdown, NULLP,
      "KWU Shut Down"
   },
   {"tapa.dummy.kwu.discsducfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlKwuDiscSduCfm, NULLP,
      "KWU Discard SDU confirm"
   }
};

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 pjAcKwuInit
(
Void
)
#else
PUBLIC S16 pjAcKwuInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(pjAcKwuInit);

   cnt = sizeof(kwAcKwuSimpleCmd)/sizeof(kwAcKwuSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcKwuSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* pjAcKwuInit */

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 pjAcKwuDeInit
(
Void
)
#else
PUBLIC S16 pjAcKwuDeInit()
#endif
{
   TRC2(pjAcKwuDeInit);

   pjAcUtlKwuDatReqCQMakeNull(&(kwAcCb.pjKwuCb.datReq));

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* pjAcKwuDeInit */






/********************************************************************30**

         End of file:     pjac_kwureg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:51 2015

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
/main/1      ---      av         1. LTE PDCP Initial release 2.1
*********************************************************************91*/

