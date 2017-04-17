
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    czac_lczhdl.c

     Sid:      czac_cztreg.c@@/main/2 - Tue Aug 30 18:35:45 2011

     Prg:     aj
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

#include "cz.h"            /* defines and macros for CZ */
#include "lcz.h"            /* defines and macros for CZ */
#include "sct.h"            /* defines and macros for CZ */
#include "czt.h"            /* defines and macros for CZ */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for CZ acceptance tests */
#include "cm_xta.h" 
#ifdef SB
#include "lsb.h"            /* SCTP layer managment defines */
#endif /*SB*/
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/

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

#include "cm_xta.x" 
#include "sct.x"           /* typedefs for STCP */
#include "lcz.x"           /* layer management typedefs for CZCP */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* typedefs for CZCP */
#include "cz.x"            /* typedefs for CZCP */
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#endif /*SB*/
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "czac_acc.x"      /* typedefs for CZCP acceptance tests */
#include "czac_czt.x"

/* cz001.101 : CR Fixes. */
PRIVATE CmXtaCmd czAcCztSimpleCmd[] =
{
   {"tapa.czt.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztBndReq, NULLP,
      "CZT Bind Request"
   },
 
   {"tapa.czt.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztBndCfm, NULLP,
      "CZT Bind Confirm"
   },
 
   {"tapa.czt.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztUbndReq, NULLP,
      "CZT Unbind Request"
   },

   {"tapa.czt.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztStaInd, NULLP,
    "CZT Status Indication"
   },

   {"tapa.czt.errind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztLclErrInd, NULLP,
    "CZT Error Indication"
   },


   {"tapa.czt.gperrind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztGpErrInd, NULLP,
    "CZT Error Indication"
   },

   {"tapa.czt.gperrreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztGpErrReq, NULLP,
    "Gp Error Request"
   },

   {"tapa.czt.bmpind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztBmpInd, NULLP,
    "Basic Mobility Req Indication"
   },

   {"tapa.czt.bmpreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztBmpReq, NULLP,
    "Basic Mobility Request"
   },

   {"tapa.czt.bmprsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztBmpRsp, NULLP,
    "Basic Mobility Response"
   },

   {"tapa.czt.bmpcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztBmpCfm, NULLP,
    "Basic Mobility Confirm "
   },
   {"tapa.czt.gpreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztGpReq, NULLP,
    "General Procedure Module Request"
   },
   {"tapa.czt.gpind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztGpInd, NULLP,
    "Associated Logical Connection Creation Indication"
   },

   {"tapa.czt.gprsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztGpRsp, NULLP,
    "Associated Logical Connection Creation Response"
   },

   {"tapa.czt.gpcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztGpCfm, NULLP,
    "Associated Logical Connection Creation Confirmation"
   },

   {
    "tapa.czt.gpretxreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,czAcHdlCztGpRetxReq , NULLP,
    "Gp Retransmission request"
   },
   {"tapa.czt.relreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztLclRelReq, NULLP,
    "Release Request"
   },

   {"tapa.czt.relcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztLclRelCfm, NULLP,
    "Release Confirmation"
   },

   {"tapa.czt.assocind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztPeerAssocInd, NULLP,
    "X2AP Peer Assoc Indication"
   },

   {"tapa.czt.assocrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztPeerAssocRsp, NULLP,
    "X2AP Peer Assoc Response"
   },

   {"tapa.czt.audreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztAudReq, NULLP,
    "X2AP  Audit Request"
   },

   {"tapa.czt.audcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlCztAudCfm, NULLP,
    "X2AP  Audit Confirmation"
   },

   {"tapa.cz.directive", CMXTA_TYPE_DIR, CMXTA_SUBTYPE_OTHER, czAcHdlDirective, NULLP,
    "X2AP  Directive"
   },
};


/*
*
*       Fun:   czAcCztInit
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
PUBLIC S16 czAcCztInit
(
Void
)
#else
PUBLIC S16 czAcCztInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(czAcCztInit);
 
   cnt = sizeof(czAcCztSimpleCmd)/sizeof(czAcCztSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, czAcCztSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* czAcCztInit */
 
/*
*
*       Fun:   czAcCztDeInit
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
PUBLIC S16 czAcCztDeInit
(
Void
)
#else
PUBLIC S16 czAcCztDeInit()
#endif
{
 
   TRC2(czAcCztDeInit);
 
   RETVALUE(ROK);
}/* czAcCztDeInit --*/


/********************************************************************30**

         End of file:     czac_cztreg.c@@/main/2 - Tue Aug 30 18:35:45 2011

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
/main/1      ---      aj       1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
