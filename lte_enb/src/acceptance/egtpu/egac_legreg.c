
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    egac_legreg.c

     Sid:      egac_legreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:35 2015

     Prg:     an
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
#include "cm_dns.h"         /* common DNS libraru defines */

#include "leg.h"           /* layer management defines for eGTP */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#include "cm_xta.h" 

#include "eg_edm.h"        /* EDM Module structures            */
#include "eg.h"            /* defines and macros for eGTP */
#include "egt.h"            /* defines and macros for eGTP */
#include "eg_err.h"        /* MG error defines */
#include "egac_acc.h"        /* defines for eGTP acceptance tests */

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
#include "cm_dns.x"        /* common DNS libraru defines */

#include "egt.x"           /* EGT Interface Structures */
#include "leg.x"           /* layer management typedefs for eGTP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif
/* eg004.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.x" 
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for eGTP */
#include "eg_tpt.x"            /* EGTP TPT module defines */

#include "egac_acc.x"      /* typedefs for eGTP acceptance tests */
#include "egac_leg.x"
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "lhw.x"
#include "hw.x"
#endif

   /*-- eg002.201: eg006.102 : Deleted egAccCb --*/
 
PRIVATE CmXtaCmd egAcLegSimpleCmd[] =
{
   /*-- eGTP Cfg APIs --*/
   {(Txt  *)"tapa.leg.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlGenCfgReq, NULLP,
    (Txt  *)"General Configuration Request for eGTP"               },
 
   {(Txt  *)"tapa.leg.cfg.lsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlLSapCfgReq, NULLP,
    (Txt  *)"Lower Sap Configuration Request for eGTP"                  },
 
   {(Txt  *)"tapa.leg.cfg.usap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlUSapCfgReq, NULLP,
    (Txt  *)"Upper Sap Configuration Request for eGTP"                  },
 
   {(Txt  *)"tapa.leg.cfg.tserver",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlTServerCfgReq, NULLP,
    (Txt  *)"Transport server Configuration Request for eGTP"                  },
 
   {(Txt  *)"tapa.leg.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlCfgCfm, NULLP,
    (Txt  *)"Configuration Confirmation from eGTP"                  },

#ifdef EGTP_U
   {(Txt  *)"tapa.leg.cfg.usap.egtpu",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egUAcHdlUSapCfgReq, NULLP,
    (Txt  *)"Upper Sap Configuration Request for eGTP-U"                  },
 
   {(Txt  *)"tapa.leg.cfg.ipAddr",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egUAcHdlIPAddrCfgReq, NULLP,
    (Txt  *)"IP Address Configuration Request for eGTP-U"                  },
#endif /* EGTP_ U*/ 
   /* -- eGTP Statistics API --*/ 
   {(Txt  *)"tapa.leg.sts.req",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlStsReq, NULLP,
    (Txt  *)" Statistics Request for eGTP"                   },
 
   {(Txt  *)"tapa.leg.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlStsCfm, NULLP,
    (Txt  *)"Statistics Confirmation from eGTP"                     },
 
   /* -- eGTP Status API --*/ 
   {(Txt  *)"tapa.leg.sta.req",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlStaReq, NULLP,
    (Txt  *)" Status Request for eGTP"                         },
 
   {(Txt  *)"tapa.leg.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlStaCfm, NULLP,
    (Txt  *)"Status Confirmation from eGTP"                         },
 
   /*-- eGTP Alarm APIs --*/
   {(Txt  *)"tapa.leg.staInd",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlStaInd, NULLP,
    (Txt  *)"Status Indication from eGTP"                           },
 
   /*-- eGTP Trace Ind APIs --*/
   {(Txt  *)"tapa.leg.trcInd",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlTrcInd, NULLP,
    (Txt  *)"Trace Indication from eGTP"                            },
 
   /*-- eGTP Control APIs --*/
   {(Txt  *)"tapa.leg.cntrl.gen",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlGenCntrlReq, NULLP,
    (Txt  *)"General Control Request for eGTP"                        },
 
   {(Txt  *)"tapa.leg.cntrl.usap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlUSapCntrlReq, NULLP,
    (Txt  *)"Upper Sap Control Request for eGTP"                        },
 
   {(Txt  *)"tapa.leg.cntrl.lsap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlLSapCntrlReq, NULLP,
    (Txt  *)"Lower Sap Control Request for eGTP"                        },
 
   {(Txt  *)"tapa.leg.cntrl.tptsrv", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlTServerCntrlReq, NULLP,
    (Txt  *)"Transport Server Control Request for eGTP"                        },
 
   {(Txt  *)"tapa.leg.cntrl.lsapTrc",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlLSapTrcCntrlReq, NULLP,
    (Txt  *)"Lower Sap Trace Control Request for eGTP"                        },
 
#ifdef DEBUGP
   {(Txt  *)"tapa.leg.cntrl.debug",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlDebugCntrlReq, NULLP,
    (Txt  *)"Debug Control Request for eGTP"                       },
#endif /* DEBUGP */
 
   /*-- eGTP Control APIs --*/
   {(Txt  *)"tapa.leg.cntrl.usta",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlUstaCntrlReq, NULLP,
    (Txt  *)"Unsloicited Status Control Request for eGTP"          },
 
   {(Txt  *)"tapa.leg.cntrlcfm",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlCntrlCfm, NULLP,
    (Txt  *)"Control Confirm from eGTP"          },
   /*-- eg003.201 : changes from eg009.102: handler to reset genCfg value to TRUE --*/
   {(Txt  *)"tapa.leg.cntrl.cfg",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlCfgCntrlReq, NULLP,
      (Txt  *)"Unsloicited Status Control Request for eGTP"          }, 

 
   {(Txt  *)"tapa.leg.cntrl.shutdown",CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egAcHdlShutDownCntrlReq, NULLP,
    (Txt  *)"ShutDown Control Request for eGTP"                    },
 
#ifdef EGTP_U
   {(Txt  *)"tapa.leg.cntrl.ipAddr", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, egUAcHdlIPAddrCntrlReq, NULLP,
    (Txt  *)"IP Address Control Request for eGTP-U"                        },
#endif /* EGTP_U */
 
};
 
 
/*
*
*       Fun:   egAcLegInit
*
*       Desc:  Function which initializes the Simple commands 
*              of layer manager of eGTP.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legreg.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcLegInit
(
Void
)
#else
PUBLIC S16 egAcLegInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   /*---- eg002.201 : TRC changes from eg006.102 --*/
   TRC2(egAcLegInit);
 
   cnt = 0;
   ret = 0;
 
   cnt = sizeof(egAcLegSimpleCmd)/sizeof(egAcLegSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, egAcLegSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* egAcLegInit */
 
/*
*
*       Fun:   egAcLegDeInit
*
*       Desc:  De-initialization of the Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  egac_legreg.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcLegDeInit
(
Void
)
#else
PUBLIC S16 egAcLegDeInit()
#endif
{
   TRC2(egAcLegDeInit);
 
   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* egAcLegDeInit */

/********************************************************************30**

         End of file:     egac_legreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:35 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3    eg002.201  psingh      1. Merged code from eg006.102 to Fix warnings
/main/3    eg003.201  psingh      1. Merged code from eg009.102: handler to
                                     reset genCfg value to TRUE
/main/3    eg004.201  magnihotri  1. Header files added for eGTP-C PSF
*********************************************************************91*/
