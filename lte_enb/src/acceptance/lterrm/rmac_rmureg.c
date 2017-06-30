

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_rmureg.c

     Sid:      rmac_rmureg.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:29 2013

     Prg:      sck

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
#include "cm_dns.h"        /* common DNS libraru defines */
#include "cm_xta.h" 
#include "cm_pasn.h"
#include "rm.h"
#include "lrm.h"
#include "rmu.h"
#include "rmac_acc.h"
//#include "rmac_rmu.h"

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
#include "cm_xta.x" 
#include "cm_pasn.x"
#include "lrm.x"
#include "rmu.x"
#include "rmac_acc.x"
#include "rmac_rmu.x"


PRIVATE CmXtaCmd rmAcRmuSimpleCmd[] =
{
   /* Bind Procedure */

   {"tapa.rmu.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuBndReq, NULLP,
      "LRM Bind Request"
   },

   {"tapa.rmu.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuBndCfm, NULLP,
      "LRM Bind Confirm"
   },

   {"tapa.rmu.mmeovldstart", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuMmeOvldStartInd, NULLP,
      "MME Overload Start Indication"
   },

   {"tapa.rmu.mmeovldstop", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuMmeOvldStopInd, NULLP,
      "MME Overload Stop Indication"
   },

   {"tapa.rmu.ueadmitreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeAdmitReq, NULLP,
      "UE Admit Request"
   },

   {"tapa.rmu.ueadmitrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeAdmitRsp, NULLP,
      "UE Admit Response"
   },

   {"tapa.rmu.uehoreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeHoReq, NULLP,
      "UE Handover Request"
   },

   {"tapa.rmu.uehorsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeHoRsp, NULLP,
      "UE Handover Response"
   },

   {"tapa.rmu.initconextsetupreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeIcsReq, NULLP,
      "UE ICS Request"
   },

   {"tapa.rmu.erabrecfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeErabRecfgReq, NULLP,
      "UE ERAB Reconfiguration Request"
   },
	   
   {"tapa.rmu.uecaprecfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeCapRecfgReq, NULLP,
      "UE Capacity Reconfiguration Request"
   },
	   
   {"tapa.rmu.crntirecfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeCrntiRecfgReq, NULLP,
      "UE Crnti Reconfiguration Request"
   },
	   
   {"tapa.rmu.scellrecfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeScellRecfgReq, NULLP,
      "UE Scell Addition Reconfiguration Request"
   },

   {"tapa.rmu.uerecfgrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeRecfgRsp, NULLP,
      "UE Reconfiguration Response"
   },

   {"tapa.rmu.cellrecfgind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuCellReconfigInd, NULLP,
      "Cell Re-Configuration Indication"
   },

   {"tapa.rmu.fsmstatusind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuFsmStatusInd, NULLP,
      "FSM status Indication"
   },

   {"tapa.rmu.uerelind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeRelInd, NULLP,
      "UE Release Indication"
   },

   {"tapa.rmu.uerelreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeRelReq, NULLP,
      "UE Release Request"
   },

   {"tapa.rmu.uerelrsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuUeRelRsp, NULLP,
      "UE Release Response"
   },

   {"tapa.rmu.spsdisind", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rmAcHdlRmuSpsDisInd, NULLP,
      "SPS Disable Indication"
   }
};


/*
*
*       Fun:   rmAcRmuInit
*
*       Desc:  Initialization of RMU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rmac_rmureg.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcRmuInit
(
Void
)
#else
PUBLIC S16 rmAcRmuInit()
#endif
{
   U16   cnt = 0;
   S16   ret = 0;

   TRC2(rmAcRmuInit)

   cnt = sizeof(rmAcRmuSimpleCmd)/sizeof(rmAcRmuSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, rmAcRmuSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* rmAcRmuInit */

/*
*
*       Fun:   rmAcRmuDeInit
*
*       Desc:  De-Initialize RMU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rmac_rmureg.c
*
*/

#ifdef ANSI
PUBLIC S16 rmAcRmuDeInit
(
Void
)
#else
PUBLIC S16 rmAcRmuDeInit()
#endif
{

   TRC2(rmAcRmuDeInit)

   RETVALUE(ROK);
}/* rmAcRmuDeInit --*/


