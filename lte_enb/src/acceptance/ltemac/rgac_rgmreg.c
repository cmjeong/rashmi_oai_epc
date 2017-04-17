/**********************************************************************
    Name:   LTE-MAC Test Engine 
  
    Type:    C Source File 
  
    Desc:    C Source LTE MAC Test Engine - Registration Functions for 
             RGM Interface
             
    File:    rgac_rgmreg.c 

    Sid:      rgac_rgmreg.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Thu May 23 19:17:23 2013

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
#include "rgr.h"           /* RGM Interface defines */
#include "rgm.h"           /* RGM Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_rgm.h"
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
#include "rgr.x"           /* RGM Interface includes */
#include "rgm.x"           /* RGM Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"
#include "rgac_rgm.x"        /* MAC error defines */

PRIVATE CmXtaCmd rgAcRgmSimpleCmd[] =
{
   {"tapa.rgm.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgmBndReq,
      NULLP, "RGM Bind Request"},
   {"tapa.rgm.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgmBndCfm,
      NULLP, "RGM Bind Confirm"},
   {"tapa.rgm.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlRgmUbndReq,
      NULLP, "RGM Bind Confirm"},
   {"tapa.rgm.cfgprdrprt", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCfgPrdRprt,
      NULLP, "RGM Config periodic reporting"},
   {"tapa.rgm.cfgprdrprtind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlCfgPrdRprtInd,
      NULLP, "RGM Config periodic reporting Indication"}
};

/**
 * @brief This function loads all the xml commands and corresponding handlers
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcRgmInit 
(
 Void
)
#else
PUBLIC S16 rgAcRgmInit ()
#endif
{
   U16 count;
   S16 ret;

   TRC2(rgAcRgmInit);
#if 1
   count = sizeof(rgAcRgmSimpleCmd)/sizeof(rgAcRgmSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd (count, rgAcRgmSimpleCmd)) != ROK)
      RETVALUE(ret);
#endif
   RETVALUE(ROK);

} /* end of rgAcRgmInit */

/**
 * @brief This function DeInits RGM xml commands and corresponding handlers
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcRgmDeInit 
(
 Void
 )
#else
PUBLIC S16 rgAcRgmDeInit ()
#endif
{
   TRC2(rgAcRgmDeInit)

   RETVALUE(ROK);
} /* end of rgAcRgmDeInit */


/**********************************************************************
 
         End of file:     rgac_rgmreg.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Thu May 23 19:17:23 2013
 
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
                                        RGM user.
             rg004.201 rnt           1. Modified for SI Enhancement
/main/3      ---        dvasisht          1. Updated for LTE MAC Release 3.1
*********************************************************************91*/
