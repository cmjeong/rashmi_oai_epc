

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_lpkreg.c

     Sid:      pjac_lpkreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:02 2015

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
#include "kwu.h"           /* KWU defines */
#include "pju.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPK defines */
#include "lpk.h"           /* LPK defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */
#include "pk.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_lpk.h"      /* CKW Acceptance defines */

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
#include "pju.x"           /* KWU */
#include "rgu.x"           /* RGU */
#include "lpj.x"           /* LPK */
#include "lpk.x"           /* LPK */
#include "kw.x"
#include "pk.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_lpk.x"      /* CKW Acceptance defines */

/************************************************************************
                    LPK Interface Register Functions - XML Tags
************************************************************************/
PRIVATE CmXtaCmd kwAcLpkSimpleCmd[] =
{
   {"tapa.pk.directive", CMXTA_TYPE_DIR, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkDirective, NULLP,
      "Directives for TestCase"
   },
   {"tapa.lpk.gencfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkGenCfgReq, NULLP,
      "LPK Config Request"
   },
   {"tapa.lpk.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkCfgCfm, NULLP,
      "LPK Config Response"
   },
   {"tapa.lpk.sapcfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkSapCfgReq, NULLP,
      "LPK Sap Config Request"
   },
   {"tapa.lpk.trccntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkTrcCntrlReq, NULLP,
      "LPK Trace Control Request"
   },
   {"tapa.lpk.dbgcntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkDbgCntrlReq, NULLP,
      "LPK debug control Request"
   },
   {"tapa.lpk.ustacntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkUStaCntrlReq, NULLP,
      "LPK USta Control Request"
   },
   {"tapa.lpk.cntrlcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkCntrlCfm, NULLP,
      "LPK Sap Control confirm"
   },
   {"tapa.lpk.stsreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkStsReq, NULLP,
      "LPK Statistics Request"
   },
   {"tapa.lpk.stscfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkStsCfm, NULLP,
      "LPK Statistics Confirm"
   },
   {"tapa.lpk.stareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkStaReq, NULLP,
      "LPK Status Request"
   },
   {"tapa.lpk.stacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkStaCfm, NULLP,
      "LPK Status Confirm"
   },
   {"tapa.lpk.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkStaInd, NULLP,
      "LPK Status Indication"
   },
   {"tapa.lpk.trcind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkTrcInd, NULLP,
      "LPK Trace Indication"
   },
   {"tapa.lpk.cntrlshutdown", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkSDCntrlReq, NULLP,
      "LPK Shutdown Control Request"
   },
   {"tapa.lpk.sapcntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkSapCntrlReq, NULLP,
      "LPK Sap Control Request"
   },
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   {"tapa.lpk.l2measreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkL2MeasReq, NULLP,
      "LPK L2 Measurement request"
   },
   {"tapa.lpk.l2meascfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLpkL2MeasCfm, NULLP,
      "LPK L2 Measurement confirm"
   },
#endif
};


/** @details
    Call handler for command indication
@return 
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcLpkInit
(
Void
)
#else
PUBLIC S16 kwAcLpkInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(kwAcLpkInit);

   cnt = sizeof(kwAcLpkSimpleCmd)/sizeof(kwAcLpkSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcLpkSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* kwAcLpkInit */

/** @details
    Call handler for command indication
@return 
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcLpkDeInit
(
Void
)
#else
PUBLIC S16 kwAcLpkDeInit()
#endif
{
   TRC2(kwAcLpkDeInit);

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* kwAcLpkDeInit */


/********************************************************************30**
         End of file:     pjac_lpkreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:02 2015
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
/main/1      ---      vb    1. LTE PDCP Release 2.1.
*********************************************************************91*/

