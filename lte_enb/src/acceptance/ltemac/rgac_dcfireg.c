
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

PRIVATE CmXtaCmd rgAcDcfiStubSimpleCmd[] =
{
   {"tapa.dcfi.stub", CMXTA_TYPE_DIR, CMXTA_SUBTYPE_OTHER, rgAcDcfiStubExec,
      NULLP, "DCFI UT Stub"}
};

/**
 * @brief This function loads all the xml commands and corresponding handlers
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcDcfiStubSimpleCmdInit 
(
 Void
)
#else
PUBLIC S16 rgAcDcfiStubSimpleCmdInit ()
#endif
{
   U16 count;
   S16 ret;

   TRC2(rgAcDcfiStubSimpleCmdInit);

   count = sizeof(rgAcDcfiStubSimpleCmd)/sizeof(rgAcDcfiStubSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd (count, rgAcDcfiStubSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);

} /* end of rgAcDcfiStubSimpleCmdInit */

/**
 * @brief This function DeInits RGR xml commands and corresponding handlers
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcDcfiStubSimpleCmdDeInit 
(
 Void
 )
#else
PUBLIC S16 rgAcDcfiStubSimpleCmdDeInit ()
#endif
{
   TRC2(rgAcDcfiStubSimpleCmdDeInit)

   RETVALUE(ROK);
} /* end of rgAcDcfiStubSimpleCmdDeInit */


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
