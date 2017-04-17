
/**********************************************************************
    Name:   LTE-MAC Test Engine 
  
    Type:    C Source File 
  
    Desc:    C Source LTE MAC Test Engine - Registration Functions for 
             RGR Interface
             
    File:    rgac_rgrreg.c 

    Sid:      rgac_rgrreg.c@@/main/3 - Sat Jul 30 02:21:02 2011

    Prg:     nsadar 

**********************************************************************/

/* header include files (.h) */

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
#include "rgac_rgr.h"
#include "rgac_acc.h"

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
#include "rgac_rgr.x"        /* MAC error defines */

PRIVATE CmXtaCmd rgAcRgrSimpleCmd[] =
{
   {"tapa.rgr.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrBndReq,
      NULLP, "RGR Bind Request"},

   {"tapa.rgr.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrBndCfm,
      NULLP, "RGR Bind Confirm"},

   {"tapa.rgr.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrUbndReq,
      NULLP, "RGR UnBind Request"},

   {"tapa.rgr.cfgreq.cfg.cell", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrCellCfgReq,
      NULLP, "RGR Cell Cfg Request"},

   {"tapa.rgr.cfgreq.recfg.cell", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrCellReCfgReq,
      NULLP, "RGR Cell ReCfg Request"},

   {"tapa.rgr.cfgreq.cfg.ue", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrUeCfgReq,
      NULLP, "RGR UE Cfg Request"},
   
   {"tapa.rgr.cfgreq.recfg.ue", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrUeReCfgReq,
      NULLP, "RGR UE Re Cfg Request"},

   {"tapa.rgr.cfgreq.cfg.lch", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrLchCfgReq,
      NULLP, "RGR Logical Channel Cfg Request"},
   
   {"tapa.rgr.cfgreq.recfg.lch", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrLchReCfgReq,
      NULLP, "RGR Logical Channel Re Cfg Request"},
   
   {"tapa.rgr.cfgreq.cfg.lcg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrLcgCfgReq,
      NULLP, "RGR Logical Channel Group Cfg Request"},
   
   {"tapa.rgr.cfgreq.recfg.lcg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrLcgReCfgReq,
      NULLP, "RGR Logical Channel Group Re Cfg Request"},
   
   {"tapa.rgr.cfgreq.del", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrDelReq,
      NULLP, "RGR Delete Request"},

   {"tapa.rgr.cfgreq.UeReset", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrRstReq,
      NULLP, "Rgr UE Reset Request"},
   
   {"tapa.rgr.cfgCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrCfgCfm,
      NULLP, "RGR Cfg Confirm"},

   /* Added for sending TTI tick to RRM */
#ifdef RGR_RRM_TICK
   {"tapa.rgr.tti.ind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrTtiInd,
      NULLP, "RGR TTI Indication"},
#endif
/* Added for SI Enhancement*/
#ifdef RGR_SI_SCH
   {"tapa.rgr.sicfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrSiCfgReq,
      NULLP, "RGR SI Cfg Request"},
   
   {"tapa.rgr.sicfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrSiCfgCfm,
      NULLP, "RGR SI Cfg Confirm"},
    {"tapa.rgr.warningsicfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrWarningSiCfgReq,
       NULLP, "RGR Warning SI Cfg Request"},

   {"tapa.rgr.warningsicfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrWarningSiCfgCfm,
      NULLP, "RGR Warning SI Cfg Confirm"},

   {"tapa.rgr.warningsistopreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrWarningSiStopReq,
      NULLP, "RGR Warning SI Stop Req"},

#endif
#ifdef RGR_CQI_REPT
   {"tapa.rgr.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrStaInd,
      NULLP, "Status Indication"},
#endif
   {"tapa.rgr.uestaind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrUeStaInd,
      NULLP, "UE Status Indication"},
   /* LTE_ADV_FLAG_REMOVED_START */
   {"tapa.rgr.loadInfReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrLoadInfReq,
      NULLP, "RGR LoadInfo Request"},
   
   {"tapa.rgr.loadInfInd", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrLoadInfInd,
	   NULLP,"RGR LoadInfo Indication"},
#ifdef LTE_ADV
   {"tapa.rgr.actDeact.scell", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrSCellActDeactReq,
	   NULLP,"RGR SCell activation deactivation Request"},
#endif
   {"tapa.rgr.cfgreq.cfg.enb", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgrEnbCfgReq,
      NULLP, "RGR Enb Cfg Request"}
   /* LTE_ADV_FLAG_REMOVED_END */
};

/**
 * @brief This function loads all the xml commands and corresponding handlers
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcRgrInit 
(
 Void
)
#else
PUBLIC S16 rgAcRgrInit ()
#endif
{
   U16 count;
   S16 ret;

   TRC2(rgAcRgrInit);

   count = sizeof(rgAcRgrSimpleCmd)/sizeof(rgAcRgrSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd (count, rgAcRgrSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);

} /* end of rgAcRgrInit */

/**
 * @brief This function DeInits RGR xml commands and corresponding handlers
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcRgrDeInit 
(
 Void
 )
#else
PUBLIC S16 rgAcRgrDeInit ()
#endif
{
   TRC2(rgAcRgrDeInit)

   RETVALUE(ROK);
} /* end of rgAcRgrDeInit */


/**********************************************************************
 
         End of file:     rgac_rgrreg.c@@/main/3 - Sat Jul 30 02:21:02 2011
 
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
             rg001.201 sm            1. Added TTI indication towards 
                                        RGR user.
             rg004.201 rnt           1. Modified for SI Enhancement
/main/3      ---        dvasisht          1. Updated for LTE MAC Release 3.1
$SID$        ---        rt           1. LTE MAC 4.1 release
*********************************************************************91*/
