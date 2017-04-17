
/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_lpjreg.c

     Sid:      pjac_lpjreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:59 2015

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
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_lpj.h"      /* CKW Acceptance defines */

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
#include "cpj.x"           /* CPJ */
#include "kwu.x"           /* KWU */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_lpj.x"      /* CKW Acceptance defines */

/************************************************************************
                    LPJ Interface Register Functions - XML Tags
************************************************************************/
PRIVATE CmXtaCmd kwAcLpjSimpleCmd[] =
{
   {"tapa.pj.directive", CMXTA_TYPE_DIR, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjDirective, NULLP,
      "Directives for TestCase"
   },
   {"tapa.lpj.gencfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjGenCfgReq, NULLP,
      "LPJ Config Request"
   },
   {"tapa.lpj.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjCfgCfm, NULLP,
      "LPJ Config Response"
   },
   {"tapa.lpj.sapcfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjSapCfgReq, NULLP,
      "LPJ Sap Config Request"
   },
   {"tapa.lpj.trccntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjTrcCntrlReq, NULLP,
      "LPJ Trace Control Request"
   },
   {"tapa.lpj.dbgcntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjDbgCntrlReq, NULLP,
      "LPJ debug control Request"
   },
   {"tapa.lpj.ustacntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjUStaCntrlReq, NULLP,
      "LPJ USta Control Request"
   },
   {"tapa.lpj.cntrlcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjCntrlCfm, NULLP,
      "LPJ Sap Control confirm"
   },
   {"tapa.lpj.stsreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjStsReq, NULLP,
      "LPJ Statistics Request"
   },
   {"tapa.lpj.stscfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjStsCfm, NULLP,
      "LPJ Statistics Confirm"
   },
   {"tapa.lpj.stareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjStaReq, NULLP,
      "LPJ Status Request"
   },
   {"tapa.lpj.stacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjStaCfm, NULLP,
      "LPJ Status Confirm"
   },
   {"tapa.lpj.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjStaInd, NULLP,
      "LPJ Status Indication"
   },
   {"tapa.lpj.trcind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjTrcInd, NULLP,
      "LPJ Trace Indication"
   },
   {"tapa.lpj.cntrlshutdown", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjSDCntrlReq, NULLP,
      "LPJ Shutdown Control Request"
   },
   {"tapa.lpj.sapcntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjSapCntrlReq, NULLP,
      "LPJ Sap Control Request"
   },
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   {"tapa.lpj.l2measreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjL2MeasReq, NULLP,
      "LPJ L2 Measurement request"
   },
   {"tapa.lpj.l2meascfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlLpjL2MeasCfm, NULLP,
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
PUBLIC S16 pjAcLpjInit
(
Void
)
#else
PUBLIC S16 pjAcLpjInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(pjAcLpjInit);

   cnt = sizeof(kwAcLpjSimpleCmd)/sizeof(kwAcLpjSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcLpjSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* pjAcLpjInit */

/** @details
    Call handler for command indication
@return 
   ROK
*/
#ifdef ANSI
PUBLIC S16 pjAcLpjDeInit
(
Void
)
#else
PUBLIC S16 pjAcLpjDeInit()
#endif
{
   TRC2(pjAcLpjDeInit);

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* pjAcLpjDeInit */


/********************************************************************30**
         End of file:     pjac_lpjreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:59 2015
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
/main/1      ---      gk    1. LTEPDCP Release 2.1.
*********************************************************************91*/

