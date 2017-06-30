

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_lkwreg.c

     Sid:      kwac_lkwreg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:32 2014

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
#include "kwac_lkw.h"      /* CKW Acceptance defines */

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
#include "kwac_lkw.x"      /* CKW Acceptance defines */

  
/************************************************************************
                    LKW Interface Register Functions - XML Tags
************************************************************************/
PRIVATE CmXtaCmd kwAcLkwSimpleCmd[] =
{
   {"tapa.lkw.gencfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwGenCfgReq, NULLP,
      "LKW Config Request"
   },
   {"tapa.lkw.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwCfgCfm, NULLP,
      "LKW Config Response"
   },
   {"tapa.lkw.sapcfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwSapCfgReq, NULLP,
      "LKW Sap Config Request"
   },
   {"tapa.lkw.trccntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwTrcCntrlReq, NULLP,
      "LKW Trace Control Request"
   },
   {"tapa.lkw.dbgcntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwDbgCntrlReq, NULLP,
      "LKW debug control Request"
   },
   {"tapa.lkw.ustacntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwUStaCntrlReq, NULLP,
      "LKW USta Control Request"
   },
   {"tapa.lkw.sapcntrlreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwSapCntrlReq, NULLP,
      "LKW Sap control Request"
   },
   {"tapa.lkw.cntrlcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwCntrlCfm, NULLP,
      "LKW Sap Control confirm"
   },
   {"tapa.lkw.stsreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwStsReq, NULLP,
      "LKW Statistics Request"
   },
   {"tapa.lkw.stscfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwStsCfm, NULLP,
      "LKW Statistics Confirm"
   },
   {"tapa.lkw.stareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwStaReq, NULLP,
      "LKW Status Request"
   },
   {"tapa.lkw.stacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwStaCfm, NULLP,
      "LKW Status Confirm"
   },
   {"tapa.lkw.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwStaInd, NULLP,
      "LKW Status Indication"
   },
   {"tapa.lkw.trcind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwTrcInd, NULLP,
      "LKW Trace Indication"
   },
   {"tapa.lkw.cntrlshutdown", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwSDCntrlReq, NULLP,
      "LKW Shutdown Control Request"
   },
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   {"tapa.lkw.l2measreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwL2MeasReq, NULLP,
      "LKW L2 Measurement request"
   },
   {"tapa.lkw.l2meascfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlLkwL2MeasCfm, NULLP,
      "LKW L2 Measurement confirm"
   },
#endif
};



/** @details
    Call handler for command indication
@return 
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcLkwInit
(
Void
)
#else
PUBLIC S16 kwAcLkwInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(kwAcLkwInit);

   cnt = sizeof(kwAcLkwSimpleCmd)/sizeof(kwAcLkwSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcLkwSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* kwAcLkwInit */

/** @details
    Call handler for command indication
@return 
   ROK
*/
#ifdef ANSI
PUBLIC S16 kwAcLkwDeInit
(
Void
)
#else
PUBLIC S16 kwAcLkwDeInit()
#endif
{
   TRC2(kwAcLkwDeInit);

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* kwAcLkwDeInit */




/********************************************************************30**
         End of file:     kwac_lkwreg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:32 2014
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
/main/1      ---    cp      1. Initial release.
/main/2      ---    gk      1. LTE RLC Release 2.1.
/main/3   kw005.201 ap      1. Added support for L2 Measurement.
*********************************************************************91*/


