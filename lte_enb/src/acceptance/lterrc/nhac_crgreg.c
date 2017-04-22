/********************************************************************20**

     Name:    RRC - acc test file

     Type:    C Include file

     Desc:   File to register commands with XTA 

     File:   nhac_crgreg.c

     Sid:      nhac_crgreg.c@@/main/3 - Fri Jul  1 01:12:59 2011
 
     Prg:    chebli 

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
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"


EXTERN NhAccCb nhAccCb;

PRIVATE CmXtaCmd nhAcCrgSimpleCmd[] =
{
   {"tapa.dummy.crg.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCrgBndReq, NULLP,
      "CRG Bind Request"
   },

   {"tapa.dummy.crg.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCrgUbndReq, NULLP,
      "CRG Unbind Request"
   },

   {"tapa.dummy.crg.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCrgBndCfm, NULLP,
      "CRG Bind Confirm"
   },

   {"tapa.dummy.crg.cfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCrgCfgReq, NULLP,
      "CRG Config Request"
   },

   {"tapa.dummy.crg.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCrgCfgCfm, NULLP,
      "CRG Config Confirm"
   },

};

/*
*
*       Fun:   nhAcCrgInit
*
*       Desc:  Initialization of CRG Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_crgreg.c
*
*/

#ifdef ANSI
PUBLIC S16 initRrcXtaAccCb
(
Void
)
#else
PUBLIC S16 initRrcXtaAccCb()
#endif
{
   nhAccCb.crgInd = 0;
 RETVALUE(ROK);
}

/*
*
*       Fun:   nhAcCrgInit 
*
*       Desc:  Initialization of CRG Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_crgreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcCrgInit
(
Void
)
#else
PUBLIC S16 nhAcCrgInit()
#endif
{
   U16   cnt = 0;
   S16   ret = 0;

   TRC2(nhAcCrgInit)

   cnt = sizeof(nhAcCrgSimpleCmd)/sizeof(nhAcCrgSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, nhAcCrgSimpleCmd)) != ROK)
      RETVALUE(ret);

   nhAccCb.taCb.macId = 1;  /* initially taken 1 without any thought */
   
   initRrcXtaAccCb();
   
   RETVALUE(ROK);
}/* nhAcCrgInit */

/*
*
*       Fun:   nhAcCrgDeInit
*
*       Desc:  De-Initialize CRG Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_crgreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcCrgDeInit
(
Void
)
#else
PUBLIC S16 nhAcCrgDeInit()
#endif
{

   TRC2(nhAcCrgDeInit)

   RETVALUE(ROK);
}/* nhAcCrgDeInit --*/

/**********************************************************************
         End of file:     nhac_crgreg.c@@/main/3 - Fri Jul  1 01:12:59 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    chebli           1. LTE RRC Initial Release.
/main/2      ---    ch               1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
