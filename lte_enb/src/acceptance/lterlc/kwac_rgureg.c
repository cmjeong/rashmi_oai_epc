

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing
  
     File:     kwac_rgureg.c 
  
     Sid:      kwac_rgureg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:42 2014
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_rgureg.c
@brief This file contains the XTA RGU interface leaf command registration and
leaf command mapping to respective handler functions.
*/


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
#include "kwac_rgu.h"      /* CKW Acceptance defines */

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
#include "kwac_rgu.x"      /* CKW Acceptance defines */


/************************************************************************
                             RGU Interface XML Tags
************************************************************************/
PRIVATE CmXtaCmd kwAcRguSimpleCmd[] =
{
   {"tapa.dummy.rgu.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguBndReq, NULLP,
      "RGU Bind Request"
   },
 
   {"tapa.dummy.rgu.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguBndCfm, NULLP,
      "RGU Bind Confirm"
   },
 
   {"tapa.dummy.rgu.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguUbndReq, NULLP,
      "RGU Unbind Request"
   },
 
   {"tapa.dummy.rgu.cstarsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguCStaRsp, NULLP,
    "RGU Common Channel Status Response"
   },

   {"tapa.dummy.rgu.dstarsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguDStaRsp, NULLP,
    "RGU Dedicated Channel Status Response"
   },

   {"tapa.dummy.rgu.cstaind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguCStaInd, NULLP,
    "RGU Common Channel Status Indication"
   },

   {"tapa.dummy.rgu.dstaind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguDStaInd, NULLP,
    "RGU Dedicated Channel Status Indication"
   },

   {"tapa.dummy.rgu.cdatreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguCDatReq, NULLP,
      "RGU Common Channel Data Request"
   },

   {"tapa.dummy.rgu.ddatreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguDDatReq, NULLP,
      "RGU Dedicated Channel Data Request"
   },

   {"tapa.dummy.rgu.cdatind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguCDatInd, NULLP,
      "RGU Common Channel Data Indication"
   },

   {"tapa.dummy.rgu.ddatind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguDDatInd, NULLP,
      "RGU Dedicated Channel Data Indication"
   },

#ifdef KW_PDCP
   {"tapa.dummy.rgu.rxPdcpPduCreate", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguRxPdcpPduCreate, NULLP,
    "RGU Recieving side PDU creation along with PDCP PDU"
   },
#else
   {"tapa.dummy.rgu.rxsducreate", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguRxSduCreate, NULLP,
    "RGU Recieving side SDU creation"
   },

   {"tapa.dummy.rgu.rxPduCreate", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguRxPduCreate, NULLP,
    "RGU Recieving side PDU creation"
   },
#endif /* KW_PDCP */

   {"tapa.kwac.shutdown", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlShutdown, NULLP,
    "KWAC XTA Shutdown"
   },

   {"tapa.kwac.chkvar", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlChkVar, NULLP,
    "KWAC XTA Check Variables State"
   },
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   {"tapa.dummy.rgu.hqstaind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguHqStaInd, NULLP,
      "RGU Harq status Indication"
   },
#ifdef LTE_RLC_R9
   {"tapa.dummy.rgu.L2MUlThMeasReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguL2MUlThrpMeasReq, NULLP,
      "RGU L2 Measurement UL Throughput request"
   },
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS */

   {"SKIP", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlRguSkipValidation, NULLP,
    "SKIP Validation for the Latest interface primitive"
   }
};
 


/**
 * @brief XTA Leaf command registration for RGU interface 
 *
 * @details
 *
 *     Function : kwAcRguInit 
 *     
 *     XTA Leaf command registration for RGU interface 
 *     
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 kwAcRguInit
(
Void
)
#else
PUBLIC S16 kwAcRguInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(kwAcRguInit);
 
   cnt = sizeof(kwAcRguSimpleCmd)/sizeof(kwAcRguSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcRguSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* kwAcRguInit */
 


/**
 * @brief XTA Leaf command De-registration for RGU interface 
 *
 * @details
 *
 *     Function : kwAcRguDeInit 
 *     
 *     XTA Leaf command De-registration for RGU interface 
 *     
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 kwAcRguDeInit
(
Void
)
#else
PUBLIC S16 kwAcRguDeInit()
#endif
{
   TRC2(kwAcRguDeInit);
 
   kwAcUtlRguDStaIndCQMakeNull(&(kwAcCb.rguCb.dStaInd));
   kwAcUtlRguCDatReqCQMakeNull(&(kwAcCb.rguCb.cDatReq));
   kwAcUtlRguDDatReqCQMakeNull(&(kwAcCb.rguCb.dDatReq));
   kwAcUtlRguCDatIndCQMakeNull(&(kwAcCb.rguCb.cDatInd));
   kwAcUtlRguDDatIndCQMakeNull(&(kwAcCb.rguCb.dDatInd));

   RETVALUE(ROK);
}/* kwAcRguDeInit --*/



/**********************************************************************
 
         End of file:     kwac_rgureg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:42 2014
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       sm     1. Initial Release.
/main/2      ---       gk     1. LTE RLC Release 2.1.
/main/3     kw005.201  ap     1. Added support for L2 Measurement.
*********************************************************************91*/

