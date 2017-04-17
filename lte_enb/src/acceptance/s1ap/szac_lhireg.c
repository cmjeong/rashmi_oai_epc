
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc sourse code

     File:    szac_lhireg.c

     Sid:      szac_lhireg.c@@/main/Tenb_Intg_Branch_CC/1 - Mon Jan  7 19:23:23 2013

     Prg:     pk 
*********************************************************************21*/

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
/* sz006.301: Removed un-necessary include files  */
#include "cm_pasn.h"
#include "cm_xta.h"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#endif /* SZ_FTHA */

#include "sct.h"           /* SB (SCTP) layer */
#include "lsz.h"           /* layer management defines for S1AP */

#ifdef HI
#include "lhi.h"
#include "hit.h"           /* HI layer */
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "szt.h"           /* S1AP user */
#include "szt_asn.h"
#include "sz.h"            /* defines and macros for S1AP */
#include "sz_err.h"        /* S1AP error defines */
#include "szac_acc.h"         /* defines for S1AP acceptance tests */
#include <stdlib.h>
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
#include "cm_xta.x"
#include "cm_pasn.x"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */ 
#endif /* SZ_FTHA */

#include "sct.x"           /* SB (SCTP) layer */
#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include"szt_asn.x"        /* common ss7 */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SCTP Interface Structures */
#include "lsz.x"           /* LSZ types */
#include "sz.x"            /* typedefs for S1AP */
#include "szac_acc.x"        /* typedefs for S1AP acceptance tests */
#include "szac_lhi.x"




PRIVATE CmXtaCmd szAcHiSimpleCmd[] =
{
   /*-- TUCL Cfg APIs --*/
   {"tapa.lhi.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiGenCfgReq, NULLP,
      "General Configuration Request for TUCL" },

   {"tapa.lhi.cfg.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiTSapCfgReq, NULLP,
    "Tsap Configuration Request for TUCL"
   },

   {"tapa.lhi.cfg.ctxt",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiCtxtCfgReq, NULLP,
    "Context Configuration Request for TUCL" },

   {"tapa.lhi.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiCfgCfm, NULLP,
    "Configuration Confirmation for TUCL" },

   /*-- TUCL Control APIs --*/
   {"tapa.lhi.cntrl.usta",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiUstaCntrlReq, NULLP,
    "Unsolicited Status Control Request for TUCL"                        },

   {"tapa.lhi.cntrl.trc",     CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiTrcCntrlReq, NULLP,
    "Trace Control Request for TUCL"                    },

   {"tapa.lhi.cntrl.tsap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiTsapCntrlReq, NULLP,
    "TSAP Control Request for TUCL"                    },

   {"tapa.lhi.cntrl.debug",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiDbgCntrlReq, NULLP,
    "Debug Control Request for TUCL"                    },

   {"tapa.lhi.cntrl.shutdown",CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiShutDownCntrlReq, NULLP,
    "Shutdown Control Request for TUCL"                    },

   {"tapa.lhi.cntrlcfm",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiCntrlCfm, NULLP,
    "Control Confirmation for TUCL"                    },

   /*-- TUCL Statistics APIs --*/
   {"tapa.lhi.sts.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiGenStsReq, NULLP,
    "General Statistics for TUCL"                    },

   {"tapa.lhi.sts.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiTsapStsReq, NULLP,
    "TSAP Statistics for TUCL"                    },

   {"tapa.lhi.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiStsCfm, NULLP,
    "Statistics Confirmation for TUCL"                    },

   /*-- TUCL Status APIs --*/
   {"tapa.lhi.sta.sys",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiSysStaReq, NULLP,
    "System Status Request for TUCL"                    },

   {"tapa.lhi.sta.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiTsapStaReq, NULLP,
    "TSAP Status Request for TUCL"                    },

   {"tapa.lhi.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     szAcHdlHiStaCfm, NULLP,
    "Status Confirmation for TUCL"                    },


   /*-- TUCL Alarm APIs --*/
   {"tapa.lhi.staind",          CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlHiStaInd, NULLP,
    "Unsolicited Indication for TUCL "                    },

   /*-- TUCL Trace Ind APIs --*/
   {"tapa.lhi.trcind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlHiTrcInd, NULLP,
    "Trace Indication for TUCL"                    },
};

/*
*
*       Fun:   szAcLhiInit
*
*       Desc:  Initialize LHI Simple Commands 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  aqac_lhireg.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcLhiInit
(
Void
)
#else
PUBLIC S16 szAcLhiInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(szAcLhiInit)

   cnt = sizeof(szAcHiSimpleCmd)/sizeof(szAcHiSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, szAcHiSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* szAcLhiInit */

/*
*
*       Fun:   szAcLhiDeInit
*
*       Desc:  De-initialize LHI Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szAc_lhireg.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcLhiDeInit
(
Void
)
#else
PUBLIC S16 szAcLhiDeInit()
#endif
{
   TRC2(szAcLhiDeInit)

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* szAcLhiDeInit */

/********************************************************************30**

         End of file:     szac_lhireg.c@@/main/Tenb_Intg_Branch_CC/1 - Mon Jan  7 19:23:23 2013

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
/main/3      ---      vvashishth  1. Updated for S1AP release 3.1
/main/3   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/3   sz006.301   ve    1. Removed un-necessary include files
/main/3   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
