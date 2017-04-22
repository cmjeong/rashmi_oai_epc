

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     nlac_lnlreg.c

     Sid:      nlac_lnlreg.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:04:12 2014

     Prg:      subhamay 

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
#include "nl.h"
#include "lnl.h"
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
#include "lnl.x"
//#include "wrac_acc.x"
#include "nlac_lnl.x"


PRIVATE CmXtaCmd nlAcLnlSimpleCmd[] =
{
   
   {"tapa.lnl.genCfgReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlGenCfgReq, NULLP,
      "Generic Config Request"
   },

   {"tapa.lnl.genCfgCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlGenCfgCfm, NULLP,
      "Generic Config confirm"
   },
   
   {"tapa.nlu.sapCfgReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlNluSapCfgReq, NULLP,
      "SAP Config Request"
   },
   
   {"tapa.nlu.sapCfgCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlNluSapCfgCfm, NULLP,
      "SAP Config Confirm"
   },

   {"tapa.nlu.sapCfgFail", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlNluSapCfgFail, NULLP,
      "SAP Config Fail"
   },

   {"tapa.lnl.cellCfgReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlCellCfgReq, NULLP,
      "Cell Config Request"
   },

   {"tapa.lnl.cellCfgCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlCellCfgCfm, NULLP,
      "Cell Config Confirm"
   },
   
   {"tapa.lnl.cellCfgFail", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlCellCfgFail, NULLP,
      "Cell Config Fail"
   },

   {"tapa.lnl.nghCellCfgReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlNghCellCfgReq, NULLP,
      "Neighbor Cell Config Request"
   },
   
   {"tapa.lnl.nghCellCfgCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlNghCellCfgCfm, NULLP,
      "Neighbor Cell Config Confirm"
   },

   {"tapa.lnl.nghCellCfgFail", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlNghCellCfgFail, NULLP,
      "Neighbor Cell Config Fail"
   },
   
   {"tapa.lnl.cellReCfgReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlCellReCfgReq, NULLP,
      "Cell ReConfig Request"
   },

   {"tapa.lnl.cellReCfgCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlCellReCfgCfm, NULLP,
      "Cell ReConfig Confirm"
   },

   {"tapa.lnl.cellReCfgFail", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlCellReCfgFail, NULLP,
      "Cell ReConfig Fail"
   },

   {"tapa.lnl.shutdownReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlShutdownReq, NULLP,
      "Shutdown Report Request"
   },

   {"tapa.lnl.shutdownCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlShutdownCfm, NULLP,
      "Shutdown Report Confirm"
   },
   
   {"tapa.lnl.cfgUpdateInd", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlCfgUpdateInd, NULLP,
      "Configuration Update Indication"
   },
   
   {"tapa.lnl.statusInd", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlLnlStatusInd, NULLP,
      "Status Indication"
   },

};


/*
*
*       Fun:   nlAcLnlInit
*
*       Desc:  Initialization of LNL Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nlac_lnlreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcLnlInit
(
Void
)
#else
PUBLIC S16 nlAcLnlInit()
#endif
{
   U16   cnt = 0;
   S16   ret = 0;

   TRC2(nlAcLnlInit)

   cnt = sizeof(nlAcLnlSimpleCmd)/sizeof(nlAcLnlSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, nlAcLnlSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* nlAcLnlInit */

/*
*
*       Fun:   nlAcLnlDeInit
*
*       Desc:  De-Initialize LNL Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nlac_lnlreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcLnlDeInit
(
Void
)
#else
PUBLIC S16 nlAcLnlDeInit()
#endif
{

   TRC2(nlAcLnlDeInit)

   RETVALUE(ROK);
}/* nlAcLnlDeInit --*/

