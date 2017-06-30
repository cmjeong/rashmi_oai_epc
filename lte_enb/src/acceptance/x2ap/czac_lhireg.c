
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc sourse code

     File:    czac_lhireg.c

     Sid:      czac_lhireg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:25 2015
     
     Prg:     sy 
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
#include "cm_pasn.h"       /* Common Asn.1 library           */
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
#include "czt.h"           /* X2AP user */
#include "cz.h"            /* defines and macros for X2AP */
#include "cz_err.h"        /* X2AP error defines */
#include "czac_acc.h"         /* defines for X2AP acceptance tests */
#include <stdlib.h>

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
#include "cm_pasn.x"       /* Common Asn.1 library           */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SB (SCTP) layer */
#ifdef HI
#include "lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_xta.x"

#include "lcz.x"           /* LCZ types */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* typedefs for CZCP */
#include "cz.x"            /* typedefs for X2AP */
#include "czac_acc.x"        /* typedefs for X2AP acceptance tests */
#include "czac_lhi.x"


#ifdef HI

PRIVATE CmXtaCmd czAcHiSimpleCmd[] =
{
   /*-- TUCL Cfg APIs --*/
   {"tapa.lhi.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiGenCfgReq, NULLP,
      "General Configuration Request for TUCL" },

   {"tapa.lhi.cfg.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiTSapCfgReq, NULLP,
    "Tsap Configuration Request for TUCL"
   },

   {"tapa.lhi.cfg.ctxt",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiCtxtCfgReq, NULLP,
    "Context Configuration Request for TUCL" },

   {"tapa.lhi.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiCfgCfm, NULLP,
    "Configuration Confirmation for TUCL" },

   /*-- TUCL Control APIs --*/
   {"tapa.lhi.cntrl.usta",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiUstaCntrlReq, NULLP,
    "Unsolicited Status Control Request for TUCL"                        },

   {"tapa.lhi.cntrl.trc",     CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiTrcCntrlReq, NULLP,
    "Trace Control Request for TUCL"                    },

   {"tapa.lhi.cntrl.tsap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiTsapCntrlReq, NULLP,
    "TSAP Control Request for TUCL"                    },

   {"tapa.lhi.cntrl.debug",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiDbgCntrlReq, NULLP,
    "Debug Control Request for TUCL"                    },

   {"tapa.lhi.cntrl.shutdown",CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiShutDownCntrlReq, NULLP,
    "Shutdown Control Request for TUCL"                    },

   {"tapa.lhi.cntrlcfm",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiCntrlCfm, NULLP,
    "Control Confirmation for TUCL"                    },

   /*-- TUCL Statistics APIs --*/
   {"tapa.lhi.sts.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiGenStsReq, NULLP,
    "General Statistics for TUCL"                    },

   {"tapa.lhi.sts.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiTsapStsReq, NULLP,
    "TSAP Statistics for TUCL"                    },

   {"tapa.lhi.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiStsCfm, NULLP,
    "Statistics Confirmation for TUCL"                    },

   /*-- TUCL Status APIs --*/
   {"tapa.lhi.sta.sys",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiSysStaReq, NULLP,
    "System Status Request for TUCL"                    },

   {"tapa.lhi.sta.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiTsapStaReq, NULLP,
    "TSAP Status Request for TUCL"                    },

   {"tapa.lhi.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,     czAcHdlHiStaCfm, NULLP,
    "Status Confirmation for TUCL"                    },


   /*-- TUCL Alarm APIs --*/
   {"tapa.lhi.staind",          CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlHiStaInd, NULLP,
    "Unsolicited Indication for TUCL "                    },

   /*-- TUCL Trace Ind APIs --*/
   {"tapa.lhi.trcind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlHiTrcInd, NULLP,
    "Trace Indication for TUCL"                    },
};

/*
*
*       Fun:   czAcLhiInit
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
PUBLIC S16 czAcLhiInit
(
Void
)
#else
PUBLIC S16 czAcLhiInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(czAcLhiInit)

   cnt = sizeof(czAcHiSimpleCmd)/sizeof(czAcHiSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, czAcHiSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* czAcLhiInit */

/*
*
*       Fun:   czAcLhiDeInit
*
*       Desc:  De-initialize LHI Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czAc_lhireg.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcLhiDeInit
(
Void
)
#else
PUBLIC S16 czAcLhiDeInit()
#endif
{
   TRC2(czAcLhiDeInit)

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* czAcLhiDeInit */
#endif /* ifdef HI */
/********************************************************************30**

         End of file:     czac_lhireg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:25 2015

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
/main/1      ---        sy        1. LTE-X2AP Initial Release.
/main/2      ---        pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
