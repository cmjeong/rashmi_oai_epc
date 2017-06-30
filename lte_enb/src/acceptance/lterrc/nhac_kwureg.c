
/********************************************************************20**

     Name:    
             

     Type:    C source file

     Desc:    

     File:    nhac_kwureg.c

     Sid:      nhac_kwureg.c@@/main/3 - Fri Jul  1 01:13:03 2011

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
/*#include "nh.x"*/
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"

PUBLIC NhAccCb nhAccCb;

PRIVATE CmXtaCmd nhAcKwuSimpleCmd[]=
{
   {"tapa.dummy.kwu.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlKwuBndReq,\
      NULLP,"KWU Bind Request"
   },
   {"tapa.dummy.kwu.unbndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, \
      nhAcHdlKwuUbndReq, NULLP, "KWU UnBind Request"
   },
   {"tapa.dummy.kwu.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, \
      nhAcHdlKwuBndCfm, NULLP,"KWU Bind Confirm"
   },
   {"tapa.dummy.kwu.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, \
      nhAcHdlKwuDatReq, NULLP,  "KWU Data Request"
   },
   {"tapa.dummy.kwu.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, \
      nhAcHdlKwuDatInd, NULLP, "KWU Data Indication to RRC"
   }

   /* TODO any other handlers pending*/
};


/*
*
*       Fun:   nhAcKwuInit
*
*       Desc:  Initialization of KWU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_kwureg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcKwuInit
(
Void
)
#else
PUBLIC S16 nhAcKwuInit()
#endif
{
    U16   cnt = 0;
    S16   ret = 0;

    TRC2(nhAcKwuInit)

    cnt = sizeof(nhAcKwuSimpleCmd)/sizeof(nhAcKwuSimpleCmd[0]);

    if ((ret = cmXtaXmlLoadSimpleCmd(cnt, nhAcKwuSimpleCmd)) != ROK)
       RETVALUE(ret);
    nhAccCb.taCb.macId = 1;  /* initially taken 1 without any thought */

    RETVALUE(ROK);
}/* nhAcCmkInit */

/*
*
*       Fun:   nhAcKwuDeInit
*
*       Desc:  De-Initialize KWU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_kwureg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcKwuDeInit
(
Void
)
#else
PUBLIC S16 nhAcKwuDeInit()
#endif
{

   TRC2(nhAcKwuDeInit)

   RETVALUE(ROK);
}/* nhAcCmkDeInit --*/



/**********************************************************************
         End of file:     nhac_kwureg.c@@/main/3 - Fri Jul  1 01:13:03 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

    ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     rer              1. LTE RRC Initial Release.
/main/2      ---     chebli           1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

