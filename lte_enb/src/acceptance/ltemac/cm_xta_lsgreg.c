
/********************************************************************20**

     Name:    SIP 

     Type:    C source file

     Desc:    C code for Layer manager interface for System Manager

     File:    cm_xta_lsgreg.c

     Sid:      cm_xta_lsgreg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:22 2015

     Prg:     ad 

*********************************************************************21*/

/* header/extern include files (.x) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta_app.h"
#include "cm_ftha.h"
#include "lmr.h"
#include "lmr.h"
#include "lsh.h"
#include "lsg.h"
#include "cm_xta.h"

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta_app.x"
#include "cm_ftha.x"
#include "lmr.x"
#include "lsh.x"
#include "lsg.x"
#include "cm_xta.x"


PRIVATE CmXtaCmd cmXtaSgSimpleCmd[] =
{
   /*-- System Manager Cfg APIs --*/
   {"tapa.lsg.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgGenCfgReq, NULLP,
    "General Configuration Request for System Manager"                  },

   {"tapa.lsg.cfg.entity",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgEntCfgReq, NULLP,
    "Entity Configuration Request for System Manager"                  },

   {"tapa.lsg.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgCfgCfm, NULLP,
    "Configuration Confirmation for System Manager"                  },


   /*-- System Manager Control APIs --*/
   {"tapa.lsg.cntrl.enablenode",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgEnableNode, NULLP,
    "Enable Node Control Request for System Manager"                  },

   {"tapa.lsg.cntrl.disablenode",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgDisableNode, NULLP,
    "Disable Node Control Request for System Manager"                  },

   {"tapa.lsg.cntrl.swapnode",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgSwapNode, NULLP,
    "Swap Node Control Request for System Manager"                  },

   {"tapa.lsg.cntrl.abort",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgAbort, NULLP,
    "Abort Control Request for System Manager"                  },

#if 0
   {"tapa.lsg.cntrl.usta",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgUstaCntrlReq, NULLP,
    "Unsloicited Status Control Request for System Manager"                  },

   {"tapa.lsg.cntrl.trc",     CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgTrcCntrlReq, NULLP,
    "Trace Control Request for System Manager"                  },
#endif

   /* cm_xta_lsgreg_c_001.main_1: Added the debug control request handler. 
    * Other handlers are kept commented and in case if anyone need it, can
    * un-comment this and add the corresponding handler function */
   {"tapa.lsg.cntrl.debug",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgDebugCntrlReq, NULLP,
    "Debug Control Request for System Manager"                    },

   {"tapa.lsg.cntrlcfm",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgCntrlCfm, NULLP,
    "Control Confirmation for System Manager"                    },
#if 0

   /*-- System Manager Statistics APIs --*/
   {"tapa.lsg.sts.entity",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgEntityStsReq, NULLP,
    "Entity Statistics Request for System Manager"                    },

   {"tapa.lsg.sts.node",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgNodeStsReq, NULLP,
    "Node Statistics Request for System Manager"                    },

   {"tapa.lsg.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgStsCfm, NULLP,
    "Statistics Confirmation for System Manager"                    },


   /*-- System Manager Status APIs --*/
   {"tapa.lsg.sta.entity",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgEntityStaReq, NULLP,
    "Entity Status Request for System Manager"                  },

   {"tapa.lsg.sta.node",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgNodeStaReq, NULLP,
    "Node Status Request for System Manager"                  },

   {"tapa.lsg.sta.sid",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgSidStaReq, NULLP,
    "Version Status Request for System Manager"                  },

   {"tapa.lsg.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgStaCfm, NULLP,
    "Status Confirmation for System Manager"                    },

   /*-- System Manager Alarm APIs --*/
   {"tapa.lsg.staind",          CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgStaInd, NULLP,
    "Status Indication for System Manager"                   },

   /*-- System Manager Trace Ind APIs --*/
   {"tapa.lsg.trcind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlSgTrcInd, NULLP,
    "Trace Indication for System Manager"                   },
#endif

};


/*
*
*       Fun:   cmXtaLsgInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  xx_sohdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaLsgInit
(
Void
)
#else
PUBLIC S16 cmXtaLsgInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(cmXtaLsgInit)

   cnt = sizeof(cmXtaSgSimpleCmd)/sizeof(cmXtaSgSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, cmXtaSgSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* cmXtaLsgInit */

/*
*
*       Fun:   cmXtaLsgDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  xx_sohdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaLsgDeInit
(
Void
)
#else
PUBLIC S16 cmXtaLsgDeInit()
#endif
{
   TRC2(cmXtaLsgDeInit)

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* cmXtaLsgDeInit */

/********************************************************************30**

         End of file:     cm_xta_lsgreg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:22 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      sk       1. Updated for PSF-SIP 1.1 Release
/main/2      ---      cm_xta_lsgreg_c_001.main_1 pka 1. Added the handler for debug control.
*********************************************************************91*/
