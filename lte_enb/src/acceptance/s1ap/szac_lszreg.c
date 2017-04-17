
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    szac_lszreg.c

     Sid:      szac_lszreg.c@@/main/3 - Mon Jan 10 22:15:53 2011

     Prg:     mn
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

#include "sct.h"           /* SB (SCTP) layer */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA 
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer management defines for S1AP */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#include "sb_mtu.h"
#include "sb.h"
#endif    /* SB */

#include "cm_pasn.h"
#include "cm_xta.h" 

/* sz006.301: Removed un-necessary include files  */
#include "szac_asn.h"
#include "sz.h"            /* defines and macros for S1AP */
#include "szt.h"            /* defines and macros for S1AP */
#include "sz_err.h"        /* MG error defines */
#include "szac_acc.h"        /* defines for S1AP acceptance tests */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

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

#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCTP Interface Structures */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SCTP Interface Structures */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA 
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for S1AP */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#include "sct.x"           /* SB (SCTP) layer */
#include "sb_mtu.x"
#include "sb.x"`
#endif    /* SB */

#include "cm_pasn.x"
#include "cm_xta.x" 
#include "sz.x"            /* typedefs for S1AP */
#include "szac_acc.x"        /* typedefs for S1AP acceptance tests */
#include "szac_lsz.x"

 
PRIVATE CmXtaCmd szAcSzSimpleCmd[] =
{
   /*-- S1AP Cfg APIs --*/
   {"tapa.sz.sct.delay",       CMXTA_TYPE_INT, CMXTA_SUBTYPE_DELAY, szAcHdlSctDelay, NULLP,
    "Delay at the SCT interface if it is loosely coupled"               },
};
 
PRIVATE CmXtaCmd szAcLszSimpleCmd[] =
{
   /*-- S1AP Cfg APIs --*/
   {"tapa.lsz.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlGenCfgReq, NULLP,
    "General Configuration Request for S1AP"               },
 
   {"tapa.lsz.cfg.lsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlLSapCfgReq, NULLP,
    "Sct Sap Configuration Request for S1AP"                  },
 
   {"tapa.lsz.cfg.usap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlUSapCfgReq, NULLP,
    "Szt Sap Configuration Request for S1AP"                  },
 
   {"tapa.lsz.cfg.prot",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlProtCfgReq, NULLP,
    "Protocol Configuration Request for S1AP"                },
 
   {"tapa.lsz.cfg.peer",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlPeerCfgReq, NULLP,
    "Peer Configuration Request for S1AP"                },
 
   {"tapa.lsz.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlCfgCfm, NULLP,
    "Configuration Confirmation from S1AP"                  },
 
   {"tapa.lsz.sts.req",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlStsReq, NULLP,
    " Statistics Request for S1AP"                   },
 
   {"tapa.lsz.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlStsCfm, NULLP,
    "Statistics Confirmation from S1AP"                     },
 
   {"tapa.lsz.sta.req",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlStaReq, NULLP,
    " Status Request for S1AP"                         },
 
   {"tapa.lsz.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlStaCfm, NULLP,
    "Status Confirmation from S1AP"                         },
 
   /*-- S1AP Alarm APIs --*/
   {"tapa.lsz.staInd",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlStaInd, NULLP,
    "Status Indication from S1AP"                           },
 
   /*-- S1AP Trace Ind APIs --*/
   {"tapa.lsz.trcInd",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlTrcInd, NULLP,
    "Trace Indication from S1AP"                            },
 
   {"tapa.lsz.cntrl.uSap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlUSapCntrlReq, NULLP,
    "Szt Sap Control Request for S1AP"                        },
 
   {"tapa.lsz.cntrl.lSap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlLSapCntrlReq, NULLP,
    "Sct Sap Control Request for S1AP"                        },
 
   {"tapa.lsz.cntrl.lSapTrc",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlLSapTrcCntrlReq, NULLP,
    "Sct Sap Trace Control Request for S1AP"                        },
 
   {"tapa.lsz.cntrl.pNodeTrc",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlPNodeTrcCntrlReq, NULLP,
    "Peer Trace Control Request for S1AP"                        },
 
#ifdef DEBUGP
   {"tapa.lsz.cntrl.debug",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlDebugCntrlReq, NULLP,
    "Debug Control Request for S1AP"                       },
#endif /* DEBUGP */
 
   {"tapa.lsz.cntrl.peer",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlPeerCntrlReq, NULLP,
    "Peer Control Request for S1AP"                       },
 
   /*-- S1AP Control APIs --*/
   {"tapa.lsz.cntrl.usta",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlUstaCntrlReq, NULLP,
    "Unsloicited Status Control Request for S1AP"          },
 
   {"tapa.lsz.cntrlcfm",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlCntrlCfm, NULLP,
    "Control Confirm from S1AP"          },
 
   {"tapa.lsz.cntrl.shutdown",CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlShutDownCntrlReq, NULLP,
    "ShutDown Control Request for S1AP"                    },
 
};
 
 
/*
*
*       Fun:   szAcLszInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  mgac_lszreg.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcLszInit
(
Void
)
#else
PUBLIC S16 szAcLszInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(szAcLszInit);
 
   cnt = sizeof(szAcSzSimpleCmd)/sizeof(szAcSzSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, szAcSzSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   cnt = sizeof(szAcLszSimpleCmd)/sizeof(szAcLszSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, szAcLszSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* szAcLszInit */
 
/*
*
*       Fun:   szAcLszDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  mgac_lszreg.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcLszDeInit
(
Void
)
#else
PUBLIC S16 szAcLszDeInit()
#endif
{
   TRC2(szAcLszDeInit);
 
   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* szAcLszDeInit */
/********************************************************************30**

         End of file:     szac_lszreg.c@@/main/3 - Mon Jan 10 22:15:53 2011

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
/main/3      ---      pkaX  1. Updated for S1AP release 3.1
/main/3   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/3   sz006.301   ve    1. Removed un-necessary include files
/main/3   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
