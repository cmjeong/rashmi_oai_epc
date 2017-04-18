
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    szac_lszhdl.c

     Sid:      szac_sztreg.c@@/main/4 - Mon Jan 10 22:16:01 2011

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
#include "cm_xta.h" 
#include "cm_pasn.h"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* Sytem Agent */
#endif /* SZ_FTHA */
#include "lsz.h"            /* defines and macros for SZ */
#include "sct.h"            /* defines and macros for SZ */
#include "szt.h"            /* defines and macros for SZ */
/* sz006.301: Removed un-necessary include files  */
#include "szac_asn.h"
#include "sz.h"            /* defines and macros for SZ */
#include "sz_err.h"        /* SZ error defines */
#include "szac_acc.h"        /* defines for SZ acceptance tests */
#ifdef SB
#include "lsb.h"            /* SCTP layer managment defines */
#endif /*SB*/
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
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
#include "cm_pasn.x"
#include "cm_xta.x" 

/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* Sytem Agent */
#endif /* SZ_FTHA */
#include "szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* typedefs for STCP */
#include "lsz.x"           /* layer management typedefs for SZCP */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* typedefs for SZCP */
#include "sz.x"            /* typedefs for SZCP */
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#endif /*SB*/
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "szac_acc.x"      /* typedefs for SZCP acceptance tests */
#include "szac_szt.x"

PRIVATE CmXtaCmd szAcSztSimpleCmd[] =
{
   {"tapa.szt.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztBndReq, NULLP,
      "SZT Bind Request"
   },
 
   {"tapa.szt.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztBndCfm, NULLP,
      "SZT Bind Confirm"
   },
 
   {"tapa.szt.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztUbndReq, NULLP,
      "SZT Unbind Request"
   },
   {"tapa.szt.audreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztAuditReq, NULLP,
      "SZT Audit Request"
   },

   {"tapa.szt.audcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztAuditCfm, NULLP,
      "SZT Audit Confirm"
   },

   {"tapa.szt.flcind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztFlcInd, NULLP,
      "SZT Flow Control Indication"
   },

   {"tapa.szt.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztStaInd, NULLP,
    "SZT Status Indication"
   },

   {"tapa.szt.errind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztErrInd, NULLP,
    "SZT Error Indication"
   },

   {"tapa.szt.udatreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztUDatReq, NULLP,
    "Connection-less Data Request"
   },

   {"tapa.szt.udatind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztUDatInd, NULLP,
    "Connection-less Data Indication"
   },

   {"tapa.szt.conreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztConReq, NULLP,
    "Associated Logical Connection Creation Request"
   },

   {"tapa.szt.conind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztConInd, NULLP,
    "Associated Logical Connection Creation Indication"
   },

   {"tapa.szt.conrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztConRsp, NULLP,
    "Associated Logical Connection Creation Response"
   },

   {"tapa.szt.concfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztConCfm, NULLP,
    "Associated Logical Connection Creation Confirmation"
   },

   {"tapa.szt.relreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztRelReq, NULLP,
    "Associated Logical Connection Release Request"
   },

   {"tapa.szt.relind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztRelInd, NULLP,
    "Associated Logical Connection Release Indication"
   },

   {"tapa.szt.relrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztRelRsp, NULLP,
    "Associated Logical Connection Release Reply"
   },

   {"tapa.szt.relcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztRelCfm, NULLP,
    "Associated Logical Connection Release Confirmation"
   },

   {"tapa.szt.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztDatReq, NULLP,
    "Associated Signalling Data Request"
   },

   {"tapa.szt.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztDatInd, NULLP,
    "Associated Signalling Data Indication"
   },

   {"tapa.szt.encreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztEncReq, NULLP,
    "Encode S1AP Message Request"
   },

   {"tapa.szt.enccfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztEncDecCfm, NULLP,
    "Encode S1AP Message Confirmation"
   },

   {"tapa.szt.decreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztDecReq, NULLP,
    "Decode S1AP Message Request"
   },

   {"tapa.szt.deccfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztEncDecCfm, NULLP,
    "Decode S1AP Message Confirmation"
   },
 
/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
   {"tapa.szt.aborts1req", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztAbortS1Req, NULLP,
    "Abort the S1 Setup Request"
   },

   {"tapa.szt.aborts1cfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztAbortS1Cfm, NULLP,
    "Abort the S1 Setup Confirmation"
   },
#endif /* SZTV2 */

#ifdef SZ_MME
   {"tapa.szt.assocind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztPeerAssocInd, NULLP,
    "S1AP Peer Assoc Indication"
   },

   {"tapa.szt.assocrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, szAcHdlSztPeerAssocRsp, NULLP,
    "S1AP Peer Assoc Response"
   },
#endif

};


/*
*
*       Fun:   szAcSztInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  mgac_mgtreg.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcSztInit
(
Void
)
#else
PUBLIC S16 szAcSztInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(szAcSztInit);
 
   cnt = sizeof(szAcSztSimpleCmd)/sizeof(szAcSztSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, szAcSztSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* szAcSztInit */
 
/*
*
*       Fun:   szAcSztDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  mgac_mgtreg.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcSztDeInit
(
Void
)
#else
PUBLIC S16 szAcSztDeInit()
#endif
{
 
   TRC2(szAcSztDeInit);
 
   RETVALUE(ROK);
}/* szAcSztDeInit --*/


/********************************************************************30**

         End of file:     szac_sztreg.c@@/main/4 - Mon Jan 10 22:16:01 2011

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/4      ---      vvashishth  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz005.301   va    1. Updated for S1 Abort request support by UI
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
