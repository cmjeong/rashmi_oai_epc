
/********************************************************************20**

     Name:    S1AP

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    szac_lsbreg.c

     Sid:      szac_lsbreg.c@@/main/3 - Mon Jan 10 22:15:48 2011

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

#include "lsb.h"           /* layer management defines for SCTP */
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

#ifdef SB
#include "lsb.h"
#include "sct.h"           /* SB (SCTP) layer */
#include "sb_mtu.h"
#include "sb.h"
#endif    /* SB */

#include "cm_xta.h" 
#include "cm_pasn.h"

#include "sz.h"            /* defines and macros for S1AP */
#include "szt.h"            /* defines and macros for S1AP */
/* sz006.301: Removed un-necessary include files  */
#include "szt_asn.h"
#include "sz_err.h"        /* S1AP error defines */
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
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */ 

#ifdef SB
#include "sct.x"           /* SB (SCTP) layer */
#include "sb_mtu.x"
#include "lsb.x"
#include "sb.x"
#endif    /* SB */

#ifdef HI
#include "lhi.x"
#include "hit.x"           /* HI layer */
#include "hi.x"
#endif

#include"szt_asn.x"        /* common ss7 */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */
#include "cm_xta.x" 

#include "cm_pasn.x"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SCTP Interface Structures */
#include "lsz.x"           /* layer management typedefs for S1AP */
#include "sz.x"            /* typedefs for S1AP */
#include "szac_acc.x"        /* typedefs for S1AP acceptance tests */
#include "szac_lsb.x"


PRIVATE CmXtaCmd szAcLsbSimpleCmd[] =
{
   /*-- SCTP Cfg APIs --*/
   {"tapa.lsb.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbGenCfgReq, NULLP,
      "SCTP Gen Config Request"
   },

   {"tapa.lsb.cfg.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbTSapCfgReq, NULLP,
      "SCTP TSAP Config Request"
   },

   {"tapa.lsb.cfg.sctsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbSctSapCfgReq, NULLP,
      "SCTP SSAP Config Request"
   },

   {"tapa.lsb.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbCfgCfm, NULLP,
      "SCTP Config Confirm"
   },


   /*-- SCTP Control APIs --*/
   {"tapa.lsb.cntrl.usta",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbUstaCntrlReq, NULLP,
      "SCTP UnSolicited Control Request"
   },

   {"tapa.lsb.cntrl.trc",     CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbTrcCntrlReq, NULLP,
    "SCTP Trace Control Request"
    },

   {"tapa.lsb.cntrl.tsap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbTSapCntrlReq, NULLP,
      "SCTP TSAP Control Request"
   },

   {"tapa.lsb.cntrl.sctsap",  CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbSctSapCntrlReq, NULLP,
      "SCTP SSAP Control Request"
   },

   {"tapa.lsb.cntrl.debug",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbDebugCntrlReq, NULLP,
      "SCTP Debug Control Request"
   },

   {"tapa.lsb.cntrl.shutdown",CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbShutDownCntrlReq, NULLP,
      "SCTP Shutdown Control Request"
   },

   {"tapa.lsb.cntrlcfm",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbCntrlCfm, NULLP,
      "SCTP Control Confirm"
   },


   /*-- SCTP Statistics APIs --*/
   {"tapa.lsb.sts.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbGenStsReq, NULLP,
    "SCTP Gen Statistics Request"
   },

   {"tapa.lsb.sts.sctsap",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbSctSapStsReq, NULLP,
    "SCTP SSAP Statistics Request"
   },

   {"tapa.lsb.sts.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbTSapStsReq, NULLP,
    "SCTP TSAP Statistics Request"
   },

   {"tapa.lsb.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbStsCfm, NULLP,
    "SCTP Statistics Confirm"
   },


   /*-- SCTP Status APIs --*/
   {"tapa.lsb.sta.sys",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbSysStaReq, NULLP,
    "SCTP System Status Request"
   },

   {"tapa.lsb.sta.sctsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbSctSapStaReq, NULLP,
    "SCTP SSAP Status Request"
   },

   {"tapa.lsb.sta.tsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbTSapStaReq, NULLP,
    "SCTP TSAP Status Request"
   },

   {"tapa.lsb.sta.gen",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbGenStaReq, NULLP,
    "SCTP Gen Status Request"
   },

   {"tapa.lsb.sta.assoc",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbAssocStaReq, NULLP,
    "SCTP Association Status Request"
   },

   {"tapa.lsb.sta.dta",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbDtaStaReq, NULLP,
    "SCTP Destination transport address Status Request"
   },

   {"tapa.lsb.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbStaCfm, NULLP,
    "SCTP Status Confirm"
   },

   /*-- SCTP Alarm APIs --*/
   {"tapa.lsb.staind",          CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbStaInd, NULLP,
    "SCTP Status Indication"
   },

   /*-- SCTP Trace Ind APIs --*/
   {"tapa.lsb.trcind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSbTrcInd, NULLP,
    "SCTP Trace Indication"
   },
};
/*
*
*       Fun:   szAcLsbInit
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
PUBLIC S16 szAcLsbInit
(
Void
)
#else
PUBLIC S16 szAcLsbInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(szAcLsbInit)

   cnt = sizeof(szAcLsbSimpleCmd)/sizeof(szAcLsbSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, szAcLsbSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* szAcLsbInit */

/*
*
*       Fun:   szAcLsbDeInit
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
PUBLIC S16 szAcLsbDeInit
(
Void
)
#else
PUBLIC S16 szAcLsbDeInit()
#endif
{
/*   Pst      pst;*/

/*   S16      ret;*/

   TRC2(szAcLsbDeInit)

   RETVALUE(ROK);
}/* szAcLsbDeInit */


/********************************************************************30**

         End of file:     szac_lsbreg.c@@/main/3 - Mon Jan 10 22:15:48 2011

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
