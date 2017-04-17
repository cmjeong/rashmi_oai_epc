
/**********************************************************************
    Name:   LTE-MAC Test Engine 
  
    Type:    C Source File 
  
    Desc:    C Source LTE MAC Test Engine - Registration Functions for 
             CRG Interface
             
    File:    rgac_crgreg.c 

    Sid:      rgac_crgreg.c@@/main/3 - Sat Jul 30 02:20:53 2011

    Prg:     nsadar 

**********************************************************************/

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
#include "rgac_crg.h"

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
#include "rgac_crg.x"        /* MAC error defines */

PRIVATE CmXtaCmd rgAcCrgSimpleCmd[] =
{
   {"tapa.crg.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgBndReq,
      NULLP, "CRG Bind Request"},

   {"tapa.crg.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgBndCfm,
      NULLP, "CRG Bind Confirm"},

   {"tapa.crg.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgUbndReq,
      NULLP, "CRG UnBind Request"},

   {"tapa.crg.cfgreq.cfg.cell", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgCellCfgReq,
      NULLP, "CRG CELL Cfg Request"},
   
   {"tapa.crg.cfgreq.recfg.cell", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgCellReCfgReq,
      NULLP, "CRG CELL Re Cfg Request"},

   {"tapa.crg.cfgreq.cfg.ue", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgUeCfgReq,
      NULLP, "CRG UE Cfg Request"},
   
   {"tapa.crg.cfgreq.recfg.ue", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgUeReCfgReq,
      NULLP, "CRG UE Re Cfg Request"},

   {"tapa.crg.cfgreq.cfg.lch", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgLchCfgReq,
      NULLP, "CRG Logical Channel Cfg Request"},
   
   {"tapa.crg.cfgreq.recfg.lch", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgLchReCfgReq,
      NULLP, "CRG Logical Channel Re Cfg Request"},
   
   {"tapa.crg.cfgreq.del", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgDelReq,
      NULLP, "CRG Delete Request"},

   {"tapa.crg.cfgreq.UeReset", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgRstReq,
      NULLP, "CRG UE Reset Request"},

   {"tapa.crg.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCrgCfgCfm,
      NULLP, "CRG Cfg Confirm"},
};

/**
 * @brief This function loads all the xml commands and corresponding handlers
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcCrgInit 
(
 Void
)
#else
PUBLIC S16 rgAcCrgInit ()
#endif
{
   U16 count;
   S16 ret;

   TRC2(rgAcCrgInit);

   count = sizeof(rgAcCrgSimpleCmd)/sizeof(rgAcCrgSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd (count, rgAcCrgSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);

} /* end of rgAcCrgInit */

/**
 * @brief This function DeInits CRG xml commands and corresponding handlers
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcCrgDeInit 
(
 Void
 )
#else
PUBLIC S16 rgAcCrgDeInit ()
#endif
{
   TRC2(rgAcCrgDeInit)

   RETVALUE(ROK);
} /* end of rgAcCrgDeInit */


/**********************************************************************
 
         End of file:     rgac_crgreg.c@@/main/3 - Sat Jul 30 02:20:53 2011
 
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
/main/1      ---     ns              1. Initial Release.
/main/2      ---     ns              1. LTE MAC 2.1 release
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
$SID$        ---     rt    1. LTE MAC 4.1 release
*********************************************************************91*/
