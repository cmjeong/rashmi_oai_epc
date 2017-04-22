

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_lpjreg.c

     Sid:      kwac_lpjreg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:35 2014

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
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_lpj.h"      /* CKW Acceptance defines */

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
#include "cpj.x"           /* CPJ */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_lpj.x"      /* CKW Acceptance defines */

  
#ifdef KW_PDCP
/************************************************************************
                    LPJ Interface Register Functions - XML Tags
************************************************************************/
PRIVATE CmXtaCmd kwAcLpjSimpleCmd[] =
{
   {"tapa.pj.directive", CMXTA_TYPE_DIR, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjDirective, NULLP,
      "Directives for TestCase"
   },
   {"tapa.lpj.gencfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjGenCfgReq, NULLP,
      "LPJ Config Request"
   },
   {"tapa.lpj.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjCfgCfm, NULLP,
      "LPJ Config Response"
   },
   {"tapa.lpj.sapcfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjSapCfgReq, NULLP,
      "LPJ Sap Config Request"
   },
   {"tapa.lpj.trccntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjTrcCntrlReq, NULLP,
      "LPJ Trace Control Request"
   },
   {"tapa.lpj.dbgcntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjDbgCntrlReq, NULLP,
      "LPJ debug control Request"
   },
   {"tapa.lpj.ustacntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjUStaCntrlReq, NULLP,
      "LPJ USta Control Request"
   },
   {"tapa.lpj.cntrlcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjCntrlCfm, NULLP,
      "LPJ Sap Control confirm"
   },
   {"tapa.lpj.stsreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjStsReq, NULLP,
      "LPJ Statistics Request"
   },
   {"tapa.lpj.stscfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjStsCfm, NULLP,
      "LPJ Statistics Confirm"
   },
   {"tapa.lpj.stareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjStaReq, NULLP,
      "LPJ Status Request"
   },
   {"tapa.lpj.stacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjStaCfm, NULLP,
      "LPJ Status Confirm"
   },
   {"tapa.lpj.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjStaInd, NULLP,
      "LPJ Status Indication"
   },
   {"tapa.lpj.trcind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjTrcInd, NULLP,
      "LPJ Trace Indication"
   },
   {"tapa.lpj.cntrlshutdown", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjSDCntrlReq, NULLP,
      "LPJ Shutdown Control Request"
   },
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   {"tapa.lpj.l2measreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjL2MeasReq, NULLP,
      "LPJ L2 Measurement request"
   },
   {"tapa.lpj.l2meascfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpjL2MeasCfm, NULLP,
      "LPJ L2 Measurement confirm"
   },
#endif
};


/** @details
    Call handler for command indication
@return 
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcLpjInit
(
Void
)
#else
PUBLIC S16 kwAcLpjInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(kwAcLpjInit);

   cnt = sizeof(kwAcLpjSimpleCmd)/sizeof(kwAcLpjSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcLpjSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* kwAcLpjInit */

/** @details
    Call handler for command indication
@return 
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcLpjDeInit
(
Void
)
#else
PUBLIC S16 kwAcLpjDeInit()
#endif
{
   TRC2(kwAcLpjDeInit);

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* kwAcLpjDeInit */

#endif /* KW_PDCP */

/********************************************************************30**
         End of file:     kwac_lpjreg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:35 2014
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
/main/1      ---      gk    1. LTERLC Release 2.1.
/main/2   kw005.201   ap    1. Added support for L2 Measurement.
*********************************************************************91*/


