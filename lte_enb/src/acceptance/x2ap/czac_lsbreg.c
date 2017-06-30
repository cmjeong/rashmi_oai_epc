
/********************************************************************20**

     Name:    X2AP

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    czac_lsbreg.c

     Sid:      czac_lsbreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:28 2015

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
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "lcz.h"           /* layer management defines for X2AP */

#ifdef HI
#include "lhi.h"
#endif

#include "sct.h"           /* SB (SCTP) layer */
#ifdef SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h" 

#include "cz.h"            /* defines and macros for X2AP */
#include "czt.h"            /* defines and macros for X2AP */
#include "cz_err.h"        /* X2AP error defines */
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
#include "cm_pasn.x"       /* Common Asn.1 library           */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SB (SCTP) layer */
#ifdef SB
#include "lsb.x"
#endif    /* SB */

#ifdef HI
#include "lhi.x"
#endif

#include "cm_xta.x" 

#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* SCTP Interface Structures */
#include "lcz.x"           /* layer management typedefs for X2AP */
#include "cz.x"            /* typedefs for X2AP */
#include "czac_acc.x"        /* typedefs for X2AP acceptance tests */
#include "czac_lsb.x"

#ifdef SB

PRIVATE CmXtaCmd czAcLsbSimpleCmd[] =
{
   /*-- SCTP Cfg APIs --*/
   {"tapa.lsb.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbGenCfgReq, NULLP,
      "SCTP Gen Config Request"
   },

   {"tapa.lsb.cfg.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbTSapCfgReq, NULLP,
      "SCTP TSAP Config Request"
   },

   {"tapa.lsb.cfg.sctsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbSctSapCfgReq, NULLP,
      "SCTP SSAP Config Request"
   },

   {"tapa.lsb.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbCfgCfm, NULLP,
      "SCTP Config Confirm"
   },


   /*-- SCTP Control APIs --*/
   {"tapa.lsb.cntrl.usta",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbUstaCntrlReq, NULLP,
      "SCTP UnSolicited Control Request"
   },

   {"tapa.lsb.cntrl.trc",     CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbTrcCntrlReq, NULLP,
    "SCTP Trace Control Request"
    },

   {"tapa.lsb.cntrl.tsap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbTSapCntrlReq, NULLP,
      "SCTP TSAP Control Request"
   },

   {"tapa.lsb.cntrl.sctsap",  CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbSctSapCntrlReq, NULLP,
      "SCTP SSAP Control Request"
   },

   {"tapa.lsb.cntrl.debug",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbDebugCntrlReq, NULLP,
      "SCTP Debug Control Request"
   },

   {"tapa.lsb.cntrl.shutdown",CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbShutDownCntrlReq, NULLP,
      "SCTP Shutdown Control Request"
   },

   {"tapa.lsb.cntrlcfm",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbCntrlCfm, NULLP,
      "SCTP Control Confirm"
   },


   /*-- SCTP Statistics APIs --*/
   {"tapa.lsb.sts.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbGenStsReq, NULLP,
    "SCTP Gen Statistics Request"
   },

   {"tapa.lsb.sts.sctsap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbSctSapStsReq, NULLP,
    "SCTP SSAP Statistics Request"
   },

   {"tapa.lsb.sts.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbTSapStsReq, NULLP,
    "SCTP TSAP Statistics Request"
   },

   {"tapa.lsb.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbStsCfm, NULLP,
    "SCTP Statistics Confirm"
   },


   /*-- SCTP Status APIs --*/
   {"tapa.lsb.sta.sys",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbSysStaReq, NULLP,
    "SCTP System Status Request"
   },

   {"tapa.lsb.sta.sctsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbSctSapStaReq, NULLP,
    "SCTP SSAP Status Request"
   },

   {"tapa.lsb.sta.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbTSapStaReq, NULLP,
    "SCTP TSAP Status Request"
   },

   {"tapa.lsb.sta.gen",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbGenStaReq, NULLP,
    "SCTP Gen Status Request"
   },

   {"tapa.lsb.sta.assoc",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbAssocStaReq, NULLP,
    "SCTP Association Status Request"
   },

   {"tapa.lsb.sta.dta",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbDtaStaReq, NULLP,
    "SCTP Destination transport address Status Request"
   },

   {"tapa.lsb.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbStaCfm, NULLP,
    "SCTP Status Confirm"
   },

   /*-- SCTP Alarm APIs --*/
   {"tapa.lsb.staind",          CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbStaInd, NULLP,
    "SCTP Status Indication"
   },

   /*-- SCTP Trace Ind APIs --*/
   {"tapa.lsb.trcind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSbTrcInd, NULLP,
    "SCTP Trace Indication"
   },
};
/*
*
*       Fun:   czAcLsbInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  tq_aghdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcLsbInit
(
Void
)
#else
PUBLIC S16 czAcLsbInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(czAcLsbInit)

   cnt = sizeof(czAcLsbSimpleCmd)/sizeof(czAcLsbSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, czAcLsbSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* czAcLsbInit */

/*
*
*       Fun:   czAcLsbDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  tq_aghdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcLsbDeInit
(
Void
)
#else
PUBLIC S16 czAcLsbDeInit()
#endif
{
/*   Pst      pst;*/

/*   S16      ret;*/

   TRC2(czAcLsbDeInit)

   RETVALUE(ROK);
}/* czAcLsbDeInit */

#endif
/********************************************************************30**

         End of file:     czac_lsbreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:28 2015

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
