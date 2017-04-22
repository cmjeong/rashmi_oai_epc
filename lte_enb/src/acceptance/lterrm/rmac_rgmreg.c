

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_rmureg.c

     Sid:      rmac_rgmreg.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:28 2013

     Prg:      sck

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS libraru defines */
#include "cm_xta.h" 
#include "cm_pasn.h"
#include "rm.h"
#include "rgm.h"
//#include "wrac_acc.h"
//#include "rmac_lrm.h"

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */
#include "cm_xta.x" 
#include "cm_pasn.x"
#include "rgm.x"
//#include "wrac_acc.x"
#include "rmac_rgm.x"

#ifdef RRM_UNUSED_FUNC
PRIVATE CmXtaCmd rmAcRgmSimpleCmd[] =
{

   {"tapa.rgm.bndReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRgmBndReq, NULLP,
      "Bind Request"
   },

   {"tapa.rgm.bndCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRgmBndCfm, NULLP,
      "Bind Confirm"
   },

   {"tapa.rgm.prbCfgReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRgmPrbRprtCfg, NULLP,
      "PRB report config request"
   },

   {"tapa.rgm.prbind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRgmPrbRprtInd, NULLP,
      "PRB Usage Indication"
   }

};


/*
*
*       Fun:   rmAcRgmInit
*
*       Desc:  Initialization of RGM Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rmac_rgmreg.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcRgmInit
(
Void
)
#else
PUBLIC S16 rmAcRgmInit()
#endif
{
   U16   cnt = 0;
   S16   ret = 0;

   TRC2(rmAcRgmInit)

   cnt = sizeof(rmAcRgmSimpleCmd)/sizeof(rmAcRgmSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, rmAcRgmSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* rmAcRgmInit */

/*
*
*       Fun:   rmAcRgmDeInit
*
*       Desc:  De-Initialize RGM Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rmac_rmureg.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcRgmDeInit
(
Void
)
#else
PUBLIC S16 rmAcRgmDeInit()
#endif
{

   TRC2(rmAcRgmDeInit)

   RETVALUE(ROK);
}/* rmAcRgmDeInit --*/
#endif
