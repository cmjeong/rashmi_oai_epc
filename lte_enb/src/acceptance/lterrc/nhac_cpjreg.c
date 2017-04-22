/********************************************************************20**

     Name:    
             

     Type:    C source file

     Desc:    CPJ Interface functions

     File:    nhac_cpjreg.c

     Sid:      nhac_cpjreg.c@@/main/3 - Fri Jul  1 01:12:58 2011

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
using namespace NH_LTERRC_REL11;
#include "nhac_nhu.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"
#include "nhac_acc_cpj.x"

PRIVATE CmXtaCmd nhAcCpjSimpleCmd[]=
{
   {"tapa.dummy.cpj.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjBndReq,\
      NULLP,"CPJ Bind Request"
   },
   {"tapa.dummy.cpj.unbndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, \
      nhAcHdlCpjUbndReq, NULLP, "CPJ UnBind Request"
   },
   {"tapa.dummy.cpj.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, \
      nhAcHdlCpjBndCfm, NULLP,"CPJ Bind Confirm"
   },
   {"tapa.dummy.cpj.cfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjCfgReq, \
         NULLP, "CPJ Config Request"
   },
   {"tapa.dummy.cpj.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjCfgCfm, \
        NULLP, "CPJ Config Confirm"
   },
   {"tapa.dummy.cpj.ueidchngreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,
     nhAcHdlCpjUeIdChgReq, NULLP, "CPJ UE ID Change Request"
   },
   {"tapa.dummy.cpj.ueidchngcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,
     nhAcHdlCpjUeIdChgCfm, NULLP, "CPJ UE ID Change Confirm"
   },

   {"tapa.dummy.cpj.reestreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjReEstReq,\
      NULLP,"CPJ Reestablishment Request"
   },
   {"tapa.dummy.cpj.reestcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjReEstCfm,\
      NULLP,"CPJ Reestablishment Confirm"
   },
   {"tapa.dummy.cpj.seccfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjSecCfgReq,\
      NULLP,"CPJ Security Request"
   },
   {"tapa.dummy.cpj.seccfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjSecCfgCfm,\
      NULLP,"CPJ Security Confirm"
   },
   {"tapa.dummy.cpj.cntreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjCountReq,\
      NULLP,"CPJ Count Request"
   },
   {"tapa.dummy.cpj.cntcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjCountCfm,\
      NULLP,"CPJ Count Confirm"
   },
   {"tapa.dummy.cpj.sdustareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjSduStaReq,\
      NULLP,"CPJ SDU Status Request"
   },
   {"tapa.dummy.cpj.sdustacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjSduStaCfm,\
      NULLP,"CPJ SDU Status Confirm"
   },
   {"tapa.dummy.cpj.pdcpdatafwdreq",CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlCpjDataFwdReq,\
     NULLP,"CPJ Data forward Request "
   }

  
   /* TODO any other handlers pending*/
};


/*
*
*       Fun:   nhAcCpjInit
*
*       Desc:  Initialization of CPJ Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_cpjreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcCpjInit
(
Void
)
#else
PUBLIC S16 nhAcCpjInit()
#endif
{
    U16   cnt = 0;
    S16   ret = 0;

    TRC2(nhAcCpjInit)

    cnt = sizeof(nhAcCpjSimpleCmd)/sizeof(nhAcCpjSimpleCmd[0]);

    if ((ret = cmXtaXmlLoadSimpleCmd(cnt, nhAcCpjSimpleCmd)) != ROK)
       RETVALUE(ret);
    
    nhAccCb.cpjInd = 0;
    nhAccCb.taCb.pdcpId = 0; 
    
    RETVALUE(ROK);
}/* nhAcCpjInit */

/*
*
*       Fun:   nhAcCpjDeInit
*
*       Desc:  De-Initialize CPJ Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_cpjreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcCpjDeInit
(
Void
)
#else
PUBLIC S16 nhAcCpjDeInit()
#endif
{

   TRC2(nhAcCpjDeInit)

   RETVALUE(ROK);
}/* nhAcCpjDeInit --*/


/**********************************************************************
         End of file:     nhac_cpjreg.c@@/main/3 - Fri Jul  1 01:12:58 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    dm               1. LTE RRC Initial Release.
/main/2      ---    ch               1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

