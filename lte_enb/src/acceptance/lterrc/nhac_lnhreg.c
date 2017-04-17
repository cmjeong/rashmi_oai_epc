
/********************************************************************20**

     Name:    LTE-RRC 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_lnhreg.c

     Sid:      nhac_lnhreg.c@@/main/3 - Fri Jul  1 01:13:04 2011

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

PRIVATE CmXtaCmd nhAcNhSimpleCmd[] =
{
   /*-- LTE-RRC Config APIs --*/
   {"tapa.lnh.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhGenCfgReq, NULLP,
    "General Configuration Request for LTE-RRC"                  },

   {"tapa.lnh.cfg.lsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhLsapCfgReq, NULLP,
    "Lower SAP Configuration Request for LTE-RRC"                  },

   {"tapa.lnh.cfg.usap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhUsapCfgReq, NULLP,
    "Upper SAP Configuration Request for LTE-RRC"                  },

   {"tapa.lnh.cfg.prot",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhProtCfgReq, NULLP,
    "Protocol Configuration Request for LTE-RRC"                  },

   {"tapa.lnh.cfg.cfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhCfgCfm, NULLP,
    "Configuration Confirmation for LTE-RRC"                  },
    

   /*-- LTE-RRC Control APIs --*/
   {"tapa.lnh.cntrl.lsap",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhLsapCntrlReq, NULLP,
    "Lsap Control Request for LTE-RRC"                    },

   {"tapa.lnh.cntrl.usap",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhUsapCntrlReq, NULLP,
    "Usap Control Request for LTE-RRC"                    },
   {"tapa.lnh.cntrl.debug",   CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhDebugCntrlReq, NULLP,
    "Debug Control Request for LTE-RRC"                    },
 
   {"tapa.lnh.cntrl.shutdown",CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhShutDownCntrlReq, NULLP,
    "ShutDown Control Request for LTE-RRC"                    },

   {"tapa.lnh.cntrl.start",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhStartCntrlReq, NULLP,
    "Start Control Request for LTE-RRC"                    },

   {"tapa.lnh.cntrl.usta",    CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhUstaCntrlReq, NULLP,
    "Start Control Request for LTE-RRC"                    },

   {"tapa.lnh.cntrlcfm",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhCntrlCfm, NULLP,
    "Control Confirmation for LTE-RRC"                    },


   /*-- LTE-RRC Statistics APIs --*/
   {"tapa.lnh.sts.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhGenStsReq, NULLP,
    "General Statistics Request for LTE-RRC"                    },

   {"tapa.lnh.sts.cell",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhCellStsReq, NULLP,
    "Cell Statistics Request for LTE-RRC"                    },

   {"tapa.lnh.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhStsCfm, NULLP,
    "Statistics Confirmation for LTE-RRC"                    },

   {"tapa.lnh.sts.peer",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhPnodeStsReq, NULLP,
    "Statistics Confirmation for LTE-RRC"                    },

   /*-- LTE-RRC Soliciated Status APIs --*/
   {"tapa.lnh.sta.sys",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhSysStaReq, NULLP,
    "System ID Status Request for LTE-RRC"                  },

   {"tapa.lnh.sta.usap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhUsapStaReq, NULLP,
    "Upper Sap Status Request for LTE-RRC"                    },

   {"tapa.lnh.sta.gen",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhGenStaReq, NULLP,
    "General Status Request for LTE-RRC"                    },

   {"tapa.lnh.sta.lsap",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhLsapStaReq, NULLP,
    "Lower Sap Status Request for LTE-RRC"                    },
   
   {"tapa.lnh.stacfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhStaCfm, NULLP,
    "Status Confirmation for LTE-RRC"                    },


   /*-- LTE-RRC Alarm APIs --*/
   {"tapa.lnh.staind",          CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhStaInd, NULLP,
    "Status Indication for LTE-RRC"                   },


   /*-- LTE-RRC Trace Ind APIs --*/
   {"tapa.lnh.trcind",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nhAcHdlNhTrcInd, NULLP,
    "Trace Indication for LTE-RRC"                   }

};


/*
*
*       Fun:   nhAcLnhInit
*
*       Desc:  Function to Initialize the Lnh interface Commands 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhreg.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcLnhInit
(
Void
)
#else
PUBLIC S16 nhAcLnhInit()
#endif
{
   U16   cnt = 0;
   S16   ret = 0;

   TRC2(nhAcLnhInit)

   cnt = sizeof(nhAcNhSimpleCmd)/sizeof(nhAcNhSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, nhAcNhSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* nhAcLnhInit */

/*
*
*       Fun:   nhAcLnhDeInit
*
*       Desc:  Function to De-Initialize the Lnh Commands 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhAc_lnhreg.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcLnhDeInit
(
Void
)
#else
PUBLIC S16 nhAcLnhDeInit()
#endif
{
   TRC2(nhAcLnhDeInit)

   /*-- Empty function at present --*/
   RETVALUE(ROK);
}/* nhAcLnhDeInit */

/********************************************************************30**
         End of file:     nhac_lnhreg.c@@/main/3 - Fri Jul  1 01:13:04 2011
*********************************************************************31*/
/********************************************************************60**
        Revision history:
*********************************************************************61*/
/********************************************************************90**
   ver       pat     init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     rer              1. LTE RRC Initial Release.
/main/2      ---     chebli           1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
