
/********************************************************************20**

     Name:   S1AP Layer

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    szac_sctreg.c

     Sid:      szac_sctreg.c@@/main/3 - Mon Jan 10 22:15:58 2011

     Prg:     ms 

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_tpt.h"         /* Transport  header file       */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_dns.h"
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
                 
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */ 
/* sz006.301: Removed un-necessary include files  */
#include "cm_xta.h"
#include "szac_acc.h"
#include "lsz.h"
#include "sct.h"
#include "szt.h"           /* defines and macros for SZ */
#include "szac_asn.h"
#ifdef SB
#include "lsb.h"           /* SCTP layer managment structures */
#include "sb.h"             /* SCTP */
#include "sb_mtu.h"         /* SCTP */
#endif /* SB */ 
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif
 

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_tpt.x"         /* Transport  header file       */
#include "cm_llist.x"      /* common link list */
#include "cm_dns.x"
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
 
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */ 

#include "sct.x"
#ifdef SB
#include "sb_mtu.x"         /* SCTP */
#endif /*SB*/
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#include "sb.x"             /* SCTP */
#endif /*SB*/


#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"
#include "lsz.x"
#include "cm_xta.x"
#include "szac_acc.x"
#include "szac_sct.x"

PRIVATE CmXtaCmd szAcSctSimpleCmd[] =
{
   {"tapa.sct.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctBndReq, NULLP,
      "SCT Bind Request"
   },

   {"tapa.sct.endpopenreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctEndpOpenReq, NULLP,
      "SCT Endpoint Open Request"
   },
   {"tapa.sct.endpclosereq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctEndpCloseReq, NULLP,
      "SCT Endpoint Close Request"
   },

   {"tapa.sct.assocreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctAssocReq, NULLP,
      "SCT Association Request"
   },


   {"tapa.sct.assocrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctAssocRsp, NULLP,
      "SCT Association Response"
   },

   {"tapa.sct.termreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctTermReq, NULLP,
      "SCT Termination Request"
   },

   {"tapa.sct.setprireq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctSetPriReq, NULLP,
      "SCT Set Primary Address Request"
   },

   {"tapa.sct.hbeatreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctHBeatReq, NULLP,
      "SCT Heart Beat Request"
   },

   {"tapa.sct.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctDatReq, NULLP,
    "SCT Sctp Data Request"
    },

   {"tapa.sct.stareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctStaReq, NULLP,
    "SCT Sctp Status Request"
    },

   {"tapa.sct.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctBndCfm, NULLP,
      "SCT Bind Confirm"
   },

   {"tapa.sct.endpopencfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctEndpOpenCfm, NULLP,
      "SCT Endpoint Open Confirm"
   },

   {"tapa.sct.endpclosecfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctEndpCloseCfm, NULLP,
      "SCT Endpoint Close Confirm"
   },

   {"tapa.sct.assocind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctAssocInd, NULLP,
      "SCT Association Indication"
   },

   {"tapa.sct.assoccfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctAssocCfm, NULLP,
      "SCT Association Confirm"
   },

   {"tapa.sct.termind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctTermInd, NULLP,
      "SCT Termination Indication"
   },

   {"tapa.sct.termcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctTermCfm, NULLP,
      "SCT Termination Confirm"
   },

   {"tapa.sct.setpricfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctSetPriCfm, NULLP,
      "SCT Set Primary Address Confirm"
   },

   {"tapa.sct.hbeatcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctHBeatCfm, NULLP,
      "SCT Heart Beat Confirm"
   },

   {"tapa.sct.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctDatInd, NULLP,
    "SCT Data Indication"
   },

   {"tapa.sct.stacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctStaCfm, NULLP,
    "SCT Sctp Status Confirm"
    },

   {"tapa.sct.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctStaInd, NULLP,
    "SCT Sctp Status Indication"
    },

   {"tapa.sct.flcind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctFlcInd, NULLP,
    "SCT Sctp Flowcontrol Indication"
    },

   {"tapa.sct.assocind1", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSctAssocInd1, NULLP,
      "SCT Association Indication"
   },

};

/*
*
*       Fun:   szAcSctInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sctreg.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcSctInit
(
Void
)
#else
PUBLIC S16 szAcSctInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(szAcSctInit)

   cnt = sizeof(szAcSctSimpleCmd)/sizeof(szAcSctSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, szAcSctSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* szAcSctInit */

/*
*
*       Fun:   szAcSctDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sctreg.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcSctDeInit
(
Void
)
#else
PUBLIC S16 szAcSctDeInit()
#endif
{
   TRC2(szAcSctDeInit)

   RETVALUE(ROK);
}/* szAcSctDeInit --*/


/********************************************************************30**

         End of file:     szac_sctreg.c@@/main/3 - Mon Jan 10 22:15:58 2011

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
