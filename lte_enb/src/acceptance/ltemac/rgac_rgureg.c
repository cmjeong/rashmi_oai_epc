


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing
  
     File:     rgac_rgureg.c 
  
     Sid:      rgac_rgureg.c@@/main/3 - Sat Jul 30 02:21:05 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_rgureg.c
@brief This file contains the XTA RGU interface leaf command registration and
leaf command mapping to respective handler functions.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_lte.h"        /* Common LTE Defines */
#include "cm_xta.h"        /* Common LTE Defines */
#include "rg_env.h"        /* MAC Environment Defines */
#include "crg.h"           /* CRG Interface defines */
#include "rgr.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_acc.h"  
#include "rgac_rgu.h"        /* MAC error defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_xta.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */
#include "rgr.x"           /* RGR Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"  
#include "rgac_rgu.x"        /* MAC error defines */

PRIVATE CmXtaCmd rgAcRguSimpleCmd[] =
{
   {"tapa.rgu.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguBndReq, NULLP,
      "RGU Bind Request"
   },
 
   {"tapa.rgu.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguBndCfm, NULLP,
      "RGU Bind Confirm"
   },
 
   {"tapa.rgu.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguUbndReq, NULLP,
      "RGU Unbind Request"
   },
 
   {"tapa.rgu.cdatreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguCDatReq, NULLP,
      "RGU Common Channel Data Request"
   },

   {"tapa.rgu.ddatreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguDDatReq, NULLP,
      "RGU Dedicated Channel Data Request"
   },

   {"tapa.rgu.cdatind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguCDatInd, NULLP,
      "RGU Common Channel Data Indication"
   },

   {"tapa.rgu.ddatind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguDDatInd, NULLP,
      "RGU Dedicated Channel Data Indication"
   },

   {"tapa.rgu.cstaind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguCStaInd, NULLP,
    "RGU Common Channel Status Indication"
   },

#ifndef RGU_INF_OPTIMIZATION
   {"tapa.rgu.dstaind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguDStaInd, NULLP,
    "RGU Dedicated Channel Status Indication"
   },
#else
   {"tapa.rgu.dstaind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguConsolidatedDStaInd, NULLP,
    "RGU Dedicated Channel Status Indication"
   },
#endif
#ifdef LTE_L2_MEAS
   {"tapa.rgu.hqstaind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguHqStaInd, NULLP,
    "RGU HARQ Status Indication"
   },
#ifdef LTEMAC_R9
   {"tapa.rgu.ulthrpmeasreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguL2MUlThrpMeasReq, NULLP,
    "RGU UL Throughput Measurement Request"
   },
#endif
#endif
   {"tapa.rgu.cstarsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguCStaRsp, NULLP,
    "RGU Common Channel Status Response"
   },

   {"tapa.rgu.dstarsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguDStaRsp, NULLP,
    "RGU Dedicated Channel Status Response"
   },

   {"SKIP", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRguSkipValidation, NULLP,
    "SKIP Validation for the Latest interface primitive"
   }
};
 


/**
 * @brief XTA Leaf command registration for RGU interface 
 *
 * @details
 *
 *     Function : rgAcRguInit 
 *     
 *     XTA Leaf command registration for RGU interface 
 *     
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgAcRguInit
(
Void
)
#else
PUBLIC S16 rgAcRguInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(rgAcRguInit);
 
   cnt = sizeof(rgAcRguSimpleCmd)/sizeof(rgAcRguSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, rgAcRguSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* rgAcRguInit */
 


/**
 * @brief XTA Leaf command De-registration for RGU interface 
 *
 * @details
 *
 *     Function : rgAcRguDeInit 
 *     
 *     XTA Leaf command De-registration for RGU interface 
 *     
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 rgAcRguDeInit
(
Void
)
#else
PUBLIC S16 rgAcRguDeInit()
#endif
{
   TRC2(rgAcRguDeInit);
 
   RETVALUE(ROK);
}/* rgAcRguDeInit --*/



/**********************************************************************
 
         End of file:     rgac_rgureg.c@@/main/3 - Sat Jul 30 02:21:05 2011
 
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
/main/1      ---     sm                1. Initial Release.
/main/2      ---     sm                1. LTE MAC 2.1 release
/main/3      ---     nu                1. Updated for release LTE-MAC 3.1
$SID$        ---     rt                1. LTE MAC 4.1 release
*********************************************************************91*/
