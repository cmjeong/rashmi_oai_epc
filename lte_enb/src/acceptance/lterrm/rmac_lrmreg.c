

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_rmureg.c

     Sid:      rmac_lrmreg.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:26 2013

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
#include "lrm.h"
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
#include "lrm.x"
//#include "wrac_acc.x"
#include "rmac_lrm.x"


PRIVATE CmXtaCmd rmAcLrmSimpleCmd[] =
{
   /* Bind Procedure */
/*
   {"tapa.lrm.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmBndReq, NULLP,
      "Bind Request"
   },

   {"tapa.lrm.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmBndCfm, NULLP,
      "Bind Confirm"
   },
*/
   
   {"tapa.lrm.genCfgReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmGenCfgReq, NULLP,
      "Generic Config Request"
   },

   {"tapa.lrm.genCfgCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmGenCfgCfm, NULLP,
      "Generic Config confirm"
   },
   
   {"tapa.lrm.sapCfgReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmSapCfgReq, NULLP,
      "SAP Config Request"
   },
   
   {"tapa.lrm.lsapCfgReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmSapCfgReqRgm, NULLP,
      "SAP Config Request"
   },
   
   {"tapa.lrm.sapCfgCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmSapCfgCfm, NULLP,
      "SAP Config Confirm"
   },

   {"tapa.lrm.cpuloadind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmCpuLoadInd, NULLP,
      "CPU load Indication"
   },

   {"tapa.lrm.enbCfgReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmEnbCfgReq, NULLP,
      "eNB Config Request"
   },
   
   {"tapa.lrm.enbCfgCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmEnbCfgCfm, NULLP,
      "eNB Config Confirm"
   },

   {"tapa.lrm.enbCtrlReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmCtrlReq, NULLP,
      "eNB Control Request"
   },
   
   {"tapa.lrm.enbCtrlCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmCtrlCfm, NULLP,
      "eNB Control Confirm"
   },

   {"tapa.lrm.cellcfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmCellCfgReq, NULLP,
      "Cell config Request"
   },

   {"tapa.lrm.cellUpInd", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmCellUpInd, NULLP,
      "Cell Up Indication"
   },

   {"tapa.lrm.cellcfgCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlLrmCellCfgCfm, NULLP,
      "Cell Config Confirm"
   }


};


/*
*
*       Fun:   rmAcLrmInit
*
*       Desc:  Initialization of RMU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rmac_rmureg.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcLrmInit
(
Void
)
#else
PUBLIC S16 rmAcLrmInit()
#endif
{
   U16   cnt = 0;
   S16   ret = 0;

   TRC2(rmAcLrmInit)

   cnt = sizeof(rmAcLrmSimpleCmd)/sizeof(rmAcLrmSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, rmAcLrmSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* rmAcLrmInit */

/*
*
*       Fun:   rmAcLrmDeInit
*
*       Desc:  De-Initialize RMU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rmac_rmureg.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcLrmDeInit
(
Void
)
#else
PUBLIC S16 rmAcLrmDeInit()
#endif
{

   TRC2(rmAcLrmDeInit)

   RETVALUE(ROK);
}/* rmAcLrmDeInit --*/

