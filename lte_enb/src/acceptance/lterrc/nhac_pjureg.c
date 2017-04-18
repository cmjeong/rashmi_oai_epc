/********************************************************************20**

     Name:    
             

     Type:    C source file

     Desc:    PJU Interface functions

     File:    nhac_pjureg.c

     Sid:      nhac_pjureg.c@@/main/3 - Fri Jul  1 01:13:08 2011

     Prg:     dm 

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

PRIVATE CmXtaCmd nhAcPjuSimpleCmd[]=
{
   {"tapa.dummy.pju.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlPjuBndReq,\
      NULLP,"PJU Bind Request"
   },
   {"tapa.dummy.pju.unbndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, \
      nhAcHdlPjuUbndReq, NULLP, "PJU UnBind Request"
   },
   {"tapa.dummy.pju.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, \
      nhAcHdlPjuBndCfm, NULLP,"PJU Bind Confirm"
   },
   {"tapa.dummy.pju.datreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlPjuDatReq, \
         NULLP, "PJU Data Request"
   },
   {"tapa.dummy.pju.datind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlPjuDatInd, \
         NULLP, "PJU Data Indication"
   },
   {"tapa.dummy.pju.datcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlPjuDatCfm, \
         NULLP, "PJU Data Confirm"
   },
   {"tapa.dummy.pju.staind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlPjuStaInd, \
         NULLP, "PJU Status Indication"
   }
  
   /* TODO any other handlers pending*/
};


/*
*
*       Fun:   nhAcPjuInit
*
*       Desc:  Initialization of PJU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_pjureg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcPjuInit
(
Void
)
#else
PUBLIC S16 nhAcPjuInit()
#endif
{
    U16   cnt = 0;
    S16   ret = 0;

    TRC2(nhAcPjuInit)

    cnt = sizeof(nhAcPjuSimpleCmd)/sizeof(nhAcPjuSimpleCmd[0]);

    if ((ret = cmXtaXmlLoadSimpleCmd(cnt, nhAcPjuSimpleCmd)) != ROK)
       RETVALUE(ret);

    RETVALUE(ROK);
}/* nhAcPjuInit */

/*
*
*       Fun:   nhAcPjuDeInit
*
*       Desc:  De-Initialize PJU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_pjureg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcPjuDeInit
(
Void
)
#else
PUBLIC S16 nhAcPjuDeInit()
#endif
{

   TRC2(nhAcPjuDeInit)

   RETVALUE(ROK);
}/* nhAcPjuDeInit --*/

/**********************************************************************
         End of file:     nhac_pjureg.c@@/main/3 - Fri Jul  1 01:13:08 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    dm               1. LTE RRC Initial Release.
/main/2      ---    chebli           1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

