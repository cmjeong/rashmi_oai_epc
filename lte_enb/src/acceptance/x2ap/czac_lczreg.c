
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    czac_lczreg.c

     Sid:      czac_lczreg.c@@/main/2 - Tue Aug 30 18:35:47 2011

     Prg:     sy
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
#include "cm_pasn.h"        /* common transport types */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "lcz.h"           /* layer management defines for X2AP */

#ifdef HI
#include "lhi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h" 

#include "cz.h"            /* defines and macros for X2AP */
#include "czt.h"            /* defines and macros for X2AP */
#include "cz_err.h"        /* MG error defines */
#include "czac_acc.h"        /* defines for X2AP acceptance tests */

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
#include "cm_pasn.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SCTP Interface Structures */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* SCTP Interface Structures */
#include "lcz.x"           /* layer management typedefs for X2AP */

#ifdef HI
#include "lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for X2AP */
#include "czac_acc.x"        /* typedefs for X2AP acceptance tests */
#include "czac_lcz.x"

/* cz001.101 : CR Fixes. */
 
PRIVATE CmXtaCmd czAcCzSimpleCmd[] =
{
   /*-- X2AP Cfg APIs --*/
   {"tapa.cz.sct.delay",       CMXTA_TYPE_INT, CMXTA_SUBTYPE_DELAY, czAcHdlSctDelay, NULLP,
    "Delay at the SCT interface if it is loosely coupled"               },
};
 
PRIVATE CmXtaCmd czAcLczSimpleCmd[] =
{
   /*-- X2AP Cfg APIs --*/
   {"tapa.lcz.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlGenCfgReq, NULLP,
    "General Configuration Request for X2AP"               },
 
   {"tapa.lcz.cfg.lsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlLSapCfgReq, NULLP,
    "Sct Sap Configuration Request for X2AP"                  },
 
   {"tapa.lcz.cfg.usap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlUSapCfgReq, NULLP,
    "Czt Sap Configuration Request for X2AP"                  },
 
   {"tapa.lcz.cfg.prot",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlProtCfgReq, NULLP,
    "Protocol Configuration Request for X2AP"                },
 
   {"tapa.lcz.cfg.peer",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlPeerCfgReq, NULLP,
    "Peer Configuration Request for X2AP"                },
 
   {"tapa.lcz.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCfgCfm, NULLP,
    "Configuration Confirmation from X2AP"                  },
 
   {"tapa.lcz.sts.req",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlStsReq, NULLP,
    " Statistics Request for X2AP"                   },
 
   {"tapa.lcz.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlStsCfm, NULLP,
    "Statistics Confirmation from X2AP"                     },
 
   {"tapa.lcz.sta.req",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlStaReq, NULLP,
    " Status Request for X2AP"                         },
 
   {"tapa.lcz.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlStaCfm, NULLP,
    "Status Confirmation from X2AP"                         },
 
   /*-- X2AP Alarm APIs --*/
   {"tapa.lcz.staInd",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlStaInd, NULLP,
    "Status Indication from X2AP"                           },
 
   /*-- X2AP Trace Ind APIs --*/
   {"tapa.lcz.trcind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlTrcInd, NULLP,
    "Trace Indication from X2AP"                            },
 
   {"tapa.lcz.cntrl.usap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlUSapCntrlReq, NULLP,
    "Czt Sap Control Request for X2AP"                        },
 
   {"tapa.lcz.cntrl.lSap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlLSapCntrlReq, NULLP,
    "Sct Sap Control Request for X2AP"                        },
 
   {"tapa.lcz.cntrl.lsaptrc",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlLSapTrcCntrlReq, NULLP,
    "Sct Sap Trace Control Request for X2AP"                        },
 
   {"tapa.lcz.cntrl.pNodeTrc",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlPNodeTrcCntrlReq, NULLP,
    "Peer Trace Control Request for X2AP"                        },
 
#ifdef DEBUGP
   {"tapa.lcz.cntrl.debug",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlDebugCntrlReq, NULLP,
    "Debug Control Request for X2AP"                       },
#endif /* DEBUGP */
 
   {"tapa.lcz.cntrl.peer",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlPeerCntrlReq, NULLP,
    "Peer Control Request for X2AP"                       },
 
   /*-- X2AP Control APIs --*/
   {"tapa.lcz.cntrl.usta",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlUstaCntrlReq, NULLP,
    "Unsloicited Status Control Request for X2AP"          },
 
   {"tapa.lcz.cntrl.assoc",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlAssocCntrlReq, NULLP,
    "Assoc Control Request for X2AP"          },
   
   {"tapa.lcz.cntrl.endPt",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlEndPtCntrlReq, NULLP,
    "End Point Control Request for X2AP"          },
 
 
   {"tapa.lcz.cntrlcfm",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCntrlCfm, NULLP,
    "Control Confirm from X2AP"          },
 
   {"tapa.lcz.cntrl.shutdown",CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlShutDownCntrlReq, NULLP,
    "ShutDown Control Request for X2AP"                    }
 
};
 
 
/*
*
*       Fun:   czAcLczInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  mgac_lczreg.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcLczInit
(
Void
)
#else
PUBLIC S16 czAcLczInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(czAcLczInit);
 
   cnt = sizeof(czAcCzSimpleCmd)/sizeof(czAcCzSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, czAcCzSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   cnt = sizeof(czAcLczSimpleCmd)/sizeof(czAcLczSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, czAcLczSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* czAcLczInit */
 
/*
*
*       Fun:   czAcLczDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  mgac_lczreg.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcLczDeInit
(
Void
)
#else
PUBLIC S16 czAcLczDeInit()
#endif
{
   TRC2(czAcLczDeInit);
 
   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* czAcLczDeInit */

/********************************************************************30**

         End of file:     czac_lczreg.c@@/main/2 - Tue Aug 30 18:35:47 2011

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
/main/1      ---     sy        1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
