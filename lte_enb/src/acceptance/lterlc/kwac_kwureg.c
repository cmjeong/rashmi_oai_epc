

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_kwureg.c

     Sid:      kwac_kwureg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:27 2014

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
#include "kwac_kwu.h"      /* KWU Acceptance defines */

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
#include "kwac_kwu.x"      /* KWU Acceptance defines */

PRIVATE CmXtaCmd kwAcKwuSimpleCmd[] =
{
   {"tapa.kwu.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlKwuBndReq, NULLP,
      "KWU Bind Request"
   },
   {"tapa.kwu.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlKwuBndCfm, NULLP,
      "KWU Bind Confirm"
   },
   {"tapa.kwu.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlKwuUnBndReq, NULLP,
      "KWU Unbind Request"
   },
   {"tapa.kwu.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlKwuDatReq, NULLP,
      "KWU Dat Request"
   },
   {"tapa.kwu.datcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlKwuDatCfm, NULLP,
      "KWU Dat Confirm"
   },
   {"tapa.kwu.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlKwuDatInd, NULLP,
      "KWU Dat Indication"
   },
   {"tapa.kwu.discsdu", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlKwuDiscSduReq, NULLP,
      "KWU Discard SDU Request"
   },
   /* kw005.201, added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   {"tapa.kwu.datackind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlKwuDatAckInd, NULLP,
      "KWU Data Ack Indication"
   },
   {"tapa.kwu.discsducfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlKwuDiscSduCfm, NULLP,
      "KWU Discard SDU confirm"
   },
#endif
   {"tapa.kwu.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlKwuStaInd, NULLP,
      "KWU Status Indication"
   }
};

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcKwuInit
(
Void
)
#else
PUBLIC S16 kwAcKwuInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(kwAcKwuInit);

   cnt = sizeof(kwAcKwuSimpleCmd)/sizeof(kwAcKwuSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcKwuSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* kwAcKwuInit */

/** @details
    Call handler for command indication
@return
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcKwuDeInit
(
Void
)
#else
PUBLIC S16 kwAcKwuDeInit()
#endif
{
   TRC2(kwAcKwuDeInit);

   kwAcUtlKwuDatReqCQMakeNull(&(kwAcCb.nhKwuCb.datReq));
#ifndef KW_PDCP
   kwAcUtlKwuDatReqCQMakeNull(&(kwAcCb.pjKwuCb.datReq));
#endif /* KW_PDCP */

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* kwAcKwuDeInit */






/********************************************************************30**

         End of file:     kwac_kwureg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:27 2014

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
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
/main/3     kw005.201 ap      1. Added support for L2 Measurement.
*********************************************************************91*/


