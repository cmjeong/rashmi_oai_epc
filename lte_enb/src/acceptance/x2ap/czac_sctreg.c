
/********************************************************************20**

     Name:   S1AP Layer

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    czac_sctreg.c

     Sid:      czac_sctreg.c@@/main/2 - Tue Aug 30 18:35:54 2011

     Prg:     sy 

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

#include "sct.h"
#ifdef SB
#include "lsb.h"           /* SCTP layer managment structures */
#endif /*SB*/

#include "cm_xta.h"
#include "czac_acc.h"
#include "lcz.h"

#include "czt.h"
#include "sct.h"
#ifdef SB
#include "lsb.h"           /* SCTP layer managment structures */
#endif /*SB*/

#include "cm_xta.h"
#include "czac_acc.h"
#include "lcz.h"

#include "czt.h"
#include "sct.h"
#ifdef SB
#include "lsb.h"           /* SCTP layer managment structures */
#endif /*SB*/

#include "cm_xta.h"
#include "czac_acc.h"
#include "lcz.h"

#include "czt.h"


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

#include "sct.x"
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#endif /*SB*/

#include "cm_xta.h"
#include "czac_acc.h"
#include "lcz.h"

#include "czt.h"
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"
#include "lcz.x"
#include "cm_xta.x"
#include "czac_acc.x"
#include "czac_sct.x"

/* cz001.101 : CR Fixes. */
#ifdef DM
PRIVATE CmXtaCmd czAcSctSimpleCmd[] =
{
   {"tapa.sct.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctBndReq, NULLP,
      "SCT Bind Request"
   },

   {"tapa.sct.endpopenreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctEndpOpenReq, NULLP,
      "SCT Endpoint Open Request"
   },
   {"tapa.sct.endpclosereq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctEndpCloseReq, NULLP,
      "SCT Endpoint Close Request"
   },

   {"tapa.sct.assocreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctAssocReq, NULLP,
      "SCT Association Request"
   },


   {"tapa.sct.assocrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctAssocRsp, NULLP,
      "SCT Association Response"
   },

   {"tapa.sct.termreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctTermReq, NULLP,
      "SCT Termination Request"
   },

   {"tapa.sct.setprireq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctSetPriReq, NULLP,
      "SCT Set Primary Address Request"
   },

   {"tapa.sct.hbeatreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctHBeatReq, NULLP,
      "SCT Heart Beat Request"
   },

   {"tapa.sct.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctDatReq, NULLP,
    "SCT Sctp Data Request"
    },

   {"tapa.sct.stareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctStaReq, NULLP,
    "SCT Sctp Status Request"
    },

   {"tapa.sct.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctBndCfm, NULLP,
      "SCT Bind Confirm"
   },

   {"tapa.sct.endpopencfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctEndpOpenCfm, NULLP,
      "SCT Endpoint Open Confirm"
   },

   {"tapa.sct.endpclosecfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctEndpCloseCfm, NULLP,
      "SCT Endpoint Close Confirm"
   },

   {"tapa.sct.assocind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctAssocInd, NULLP,
      "SCT Association Indication"
   },

   {"tapa.sct.assoccfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctAssocCfm, NULLP,
      "SCT Association Confirm"
   },

   {"tapa.sct.termind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctTermInd, NULLP,
      "SCT Termination Indication"
   },

   {"tapa.sct.termcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctTermCfm, NULLP,
      "SCT Termination Confirm"
   },

   {"tapa.sct.setpricfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctSetPriCfm, NULLP,
      "SCT Set Primary Address Confirm"
   },

   {"tapa.sct.hbeatcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctHBeatCfm, NULLP,
      "SCT Heart Beat Confirm"
   },

   {"tapa.sct.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctDatInd, NULLP,
    "SCT Data Indication"
   },

   {"tapa.sct.stacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctStaCfm, NULLP,
    "SCT Sctp Status Confirm"
    },

   {"tapa.sct.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctStaInd, NULLP,
    "SCT Sctp Status Indication"
    },
   
   {"tapa.sct.flcind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctFlcInd, NULLP,
    "SCT Sctp Status Indication"
    },



   {"tapa.sct.assocind1", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, czAcHdlSctAssocInd1, NULLP,
      "SCT Association Indication"
   },

};

/*
*
*       Fun:   czAcSctInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_sctreg.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcSctInit
(
Void
)
#else
PUBLIC S16 czAcSctInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(czAcSctInit)

   cnt = sizeof(czAcSctSimpleCmd)/sizeof(czAcSctSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, czAcSctSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* czAcSctInit */

/*
*
*       Fun:   czAcSctDeInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_sctreg.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcSctDeInit
(
Void
)
#else
PUBLIC S16 czAcSctDeInit()
#endif
{
   TRC2(czAcSctDeInit)

   RETVALUE(ROK);
}/* czAcSctDeInit --*/
#endif

/********************************************************************30**

         End of file:     czac_sctreg.c@@/main/2 - Tue Aug 30 18:35:54 2011

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
/main/1      ---   sy                1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
