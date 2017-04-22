/********************************************************************20**

     Name:    RRC - acc test file

     Type:    C Include file

     Desc:   File to register commands with XTA 

     File:   nhac_ctfreg.c

     Sid:      nhac_ctfreg.c@@/main/2 - Fri Jul  1 01:13:00 2011
 
     Prg:    yk 

*********************************************************************21*/

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
using namespace NH_LTERRC_REL11;
#include "nhac_nhu.x"

#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"
#include "nhac_acc_ctf.x"


EXTERN NhAccCb nhAccCb;

#ifdef RRC_PHY_CFG_SUPP

PRIVATE CmXtaCmd nhAcCtfSimpleCmd[] =
{
   {"tapa.dummy.ctf.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCtfBndReq, NULLP,
      "CTF Bind Request"
   },

   {"tapa.dummy.ctf.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCtfUbndReq, NULLP,
      "CTF Unbind Request"
   },

   {"tapa.dummy.ctf.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCtfBndCfm, NULLP,
      "CTF Bind Confirm"
   },

   {"tapa.dummy.ctf.cfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCtfCfgReq, NULLP,
      "CTF Config Request"
   },

   {"tapa.dummy.ctf.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCtfCfgCfm, NULLP,
      "CTF Config Confirm"
   },

   {"tapa.dummy.ctf.ueidchngreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,
     nhAcHdlCtfUeIdChgReq, NULLP, "CTF UE ID Change Request"
   },
   {"tapa.dummy.ctf.ueidchngcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,
     nhAcHdlCtfUeIdChgCfm, NULLP, "CTF UE ID Change Confirm"
   },


};

/*
*
*       Fun:   nhAcCtfInit 
*
*       Desc:  Initialization of CTF Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_ctfreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcCtfInit
(
Void
)
#else
PUBLIC S16 nhAcCtfInit()
#endif
{
   U16   cnt = 0;
   S16   ret = 0;

   TRC2(nhAcCtfInit)

   cnt = sizeof(nhAcCtfSimpleCmd)/sizeof(nhAcCtfSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, nhAcCtfSimpleCmd)) != ROK)
      RETVALUE(ret);

#ifdef RRC_PHY_CFG_SUPP
   nhAccCb.taCb.phyId = 1;  /* initially taken 1 without any thought */
#endif
   nhAccCb.ctfInd = 0;
   
   RETVALUE(ROK);
}/* nhAcCtfInit */

/*
*
*       Fun:   nhAcCtfDeInit
*
*       Desc:  De-Initialize CTF Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_ctfreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcCtfDeInit
(
Void
)
#else
PUBLIC S16 nhAcCtfDeInit()
#endif
{

   TRC2(nhAcCtfDeInit)

   RETVALUE(ROK);
}/* nhAcCtfDeInit --*/
#endif /* RRC_PHY_CFG_SUPP */

/**********************************************************************
         End of file:     nhac_ctfreg.c@@/main/2 - Fri Jul  1 01:13:00 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    yk               1. LTE RRC Initial Release.
/main/2      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
