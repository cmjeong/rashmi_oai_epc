/********************************************************************20**

     Name:    RRC - acc test file

     Type:    C file

     Desc:    

     File:    nhac_ckwreg.c

     Sid:      nhac_ckwreg.c@@/main/3 - Fri Jul  1 01:12:56 2011

     Prg:     rer

*********************************************************************21*/


/* header include files (.h) */
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "ctf.h"           /* PHY Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
/* external headers */


/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#include "nhac_asn.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"

PRIVATE CmXtaCmd nhAcCkwSimpleCmd[] =
{
   {"tapa.dummy.ckw.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCkwBndReq, NULLP,
      "CKW Bind Request"
   },

   {"tapa.dummy.ckw.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCkwBndCfm, NULLP,
      "CKW Bind Confirm"
   },

   {"tapa.dummy.ckw.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCkwUbndReq, NULLP,
      "CKW Unbind Request"
   },

   {"tapa.dummy.ckw.cfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCkwCfgReq, NULLP,
      "CKW Config Request"
   },

   {"tapa.dummy.ckw.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCkwCfgCfm, NULLP,
      "CKW Config Confirm"
   },

   {"tapa.dummy.ckw.ueidchngreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,
      nhAcHdlCkwUeIdChgReq, NULLP, "CKW UE ID Change Request"
   },

   {"tapa.dummy.ckw.ueidchngcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,
      nhAcHdlCkwUeIdChgCfm, NULLP, "CKW UE ID Change Confirm"
   },

};

/*
*
*       Fun:   nhAcCkwInit
*
*       Desc:  Initialization of CKW Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_ckwreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcCkwInit
(
Void
)
#else
PUBLIC S16 nhAcCkwInit()
#endif
{
    U16   cnt = 0;
    S16   ret = 0;

    TRC2(nhAcCkwInit)

    cnt = sizeof(nhAcCkwSimpleCmd)/sizeof(nhAcCkwSimpleCmd[0]);

    if ((ret = cmXtaXmlLoadSimpleCmd(cnt, nhAcCkwSimpleCmd)) != ROK)
       RETVALUE(ret);
    nhAccCb.taCb.macId = 1;  /* initially taken 1 without any thought */
    nhAccCb.taCb.rlcId = 1;  /* initially taken 1 without any thought */
    nhAccCb.ckwInd = 0;

    RETVALUE(ROK);
}/* nhAcCkwInit */

/*
*
*       Fun:   nhAcCkwDeInit
*
*       Desc:  De-Initialize CKW Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_ckwreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcCkwDeInit
(
Void
)
#else
PUBLIC S16 nhAcCkwDeInit()
#endif
{

   TRC2(nhAcCkwDeInit)

   RETVALUE(ROK);
}/* nhAcCmkDeInit --*/

/**********************************************************************
         End of file:     nhac_ckwreg.c@@/main/3 - Fri Jul  1 01:12:56 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    rer              1. LTE RRC Initial Release.
/main/2      ---    ch               1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

