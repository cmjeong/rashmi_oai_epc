


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing
  
     File:     rgac_lrgreg.c 
  
     Sid:      rgac_lrgreg.c@@/main/3 - Sat Jul 30 02:20:58 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_lrgreg.c
@brief This file contains the XTA LRG interface leaf command registration and
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
#include "rgm.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_acc.h"        /* MAC error defines */
#include "rgac_lrg.h"        /* MAC error defines */
#include <stdlib.h>

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
#include "rgm.x"           /* RGR Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"        /* MAC error defines */
#include "rgac_lrg.x"        /* MAC error defines */
#include "rgac_rgm.x"        /* MAC error defines */


PRIVATE CmXtaCmd rgAcLrgSimpleCmd[] =
{
   /*-- LTE MAC Config APIs --*/
   {"tapa.lrg.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgGenCfgReq, NULLP,
    "General Configuration Request for LTE MAC"},
 
   {"tapa.lrg.cfg.tfusap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgTfuSapCfgReq, NULLP,
    "Tfu SAP Configuration Request for LTE MAC"},
 
   {"tapa.lrg.cfg.rgusap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgRguSapCfgReq, NULLP,
    "RGU SAP Configuration Request for LTE MAC"},
 
   {"tapa.lrg.cfg.crgsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgCrgSapCfgReq, NULLP,
    "CRG SAP Configuration Request for LTE MAC"},
 
   {"tapa.lrg.cfg.rgrsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgRgrSapCfgReq, NULLP,
    "RGR SAP Configuration Request for LTE MAC"},
   
   {"tapa.lrg.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgCfgCfm, NULLP,
    "Configuration Confirmation for LTE MAC"},

   {"tapa.lrg.cfg.schins",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgSchInsCfgReq, NULLP,
    "Scheduler Instance Configuration Request for LTE MAC (Scheduler Instance)"},
 
   {"tapa.lrg.schcfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgSchCfgCfm, NULLP,
    "Configuration Confirmation for LTE MAC"},
 
   /*-- LTE MAC Control APIs --*/
   {"tapa.lrg.cntrlreq",     CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgCntrlReq, NULLP,
    "Control Request Handling for LTE MAC"                       },
 
   {"tapa.lrg.cntrlcfm",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgCntrlCfm, NULLP,
    "Control Confirmation for LTE MAC"                        },

   {"tapa.lrg.schcntrlreq",     CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgSchCntrlReq, NULLP,
    "Scheduler Control Request Handling for Scheduler"                       },
 
   {"tapa.lrg.schcntrlcfm",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgSchCntrlCfm, NULLP,
    "Scheduler Control Confirmation for LTE MAC"                        },
   /*-- LTE MAC L2 Measurement APIs -- */
#ifdef LTE_L2_MEAS
   {"tapa.lrg.schL2measreq",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgSchL2MeasReq, NULLP,
    "L2 Measurement Request"                        },

   {"tapa.lrg.schL2meascfm",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgSchL2MeasCfm, NULLP,
    "L2 Measurement Confirm"                        },
/*Anshika Start */   
   {"tapa.lrg.schL2sendmeasreq",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgSchSendL2MeasReq, NULLP,
    "L2 Measurement Request"                        },
   
   {"tapa.lrg.schL2stopmeasreq",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgSchStopL2MeasReq, NULLP,
    "L2 Measurement Request"                        },
   
   {"tapa.lrg.schL2stopmeascfm",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgSchL2StopMeasCfm, NULLP,
    "L2 Measurement Confirm"                        },
/* Anshika Stop */   
#endif
 
   /*-- LTE MAC Statistics APIs --*/
   {"tapa.lrg.stsreq",      CMXTA_TYPE_LEAF,
   CMXTA_SUBTYPE_OTHER, rgAcHdlLrgStsReq, NULLP,
    "Statistics Request for LTE MAC"                     },
 
   {"tapa.lrg.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgStsCfm, NULLP,
    "Statistics Confirmation for LTE MAC"                     },
 
   /*-- LTE MAC Status APIs --*/
   {"tapa.lrg.stareq",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgStaReq, NULLP,
    "Status Request for LTE MAC"                         },
 
   {"tapa.lrg.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgStaCfm, NULLP,
    "Status Confirmation for LTE MAC"                         },
 
   /*-- LTE MAC Alarm APIs --*/
   {"tapa.lrg.staind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgStaInd, NULLP,
    "Status Indication for LTE MAC"                           },
   
   {"tapa.lrg.sch.staind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgSchStaInd, NULLP,
    "Status Indication for LTE MAC"                           },
 
   /*-- LTE MAC Trace Ind APIs --*/
   {"tapa.lrg.trcind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgTrcInd, NULLP,
    "Trace Indication for LTE MAC"                            },
 
   /*-- Command to set TC level settings --*/
   {"tapa.lrg.directive",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlLrgDirective, NULLP,
    "Command to set TC level settings"                        }

};
 


/**
 * @brief XTA Leaf command registration for LRG interface 
 *
 * @details
 *
 *     Function : rgAcLrgInit 
 *     
 *     XTA Leaf command registration for LRG interface 
 *     
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgAcLrgInit
(
Void
)
#else
PUBLIC S16 rgAcLrgInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(rgAcLrgInit);
 
   cnt = sizeof(rgAcLrgSimpleCmd)/sizeof(rgAcLrgSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, rgAcLrgSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* rgAcLrgInit */
 


/**
 * @brief XTA Leaf command De-registration for LRG interface 
 *
 * @details
 *
 *     Function : rgAcLrgDeInit 
 *     
 *     XTA Leaf command De-registration for LRG interface 
 *     
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 rgAcLrgDeInit
(
Void
)
#else
PUBLIC S16 rgAcLrgDeInit()
#endif
{
   TRC2(rgAcLrgDeInit);
 
   RETVALUE(ROK);
}/* rgAcLrgDeInit --*/



/**********************************************************************
 
         End of file:     rgac_lrgreg.c@@/main/3 - Sat Jul 30 02:20:58 2011
 
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
/main/3      ---     dvasisht          1. Updated for LTE MAC Release 3.1          
$SID$        ---       rt              1. LTE MAC 4.1 release
*********************************************************************91*/
