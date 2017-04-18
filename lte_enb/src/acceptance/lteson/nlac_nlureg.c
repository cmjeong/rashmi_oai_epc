

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     nlac_nlureg.c

     Sid:      nlac_nlureg.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:05:07 2014

     Prg:      subhamay 

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
#include "nl.h"
#include "lnl.h"
#include "nlu.h"
#include "nlac_acc.h"
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
#include "lnl.x"
#include "nlu.x"
#include "nlac_acc.x"
#include "nlac_nlu.x"


PRIVATE CmXtaCmd nlAcNluSimpleCmd[] =
{

   {"tapa.nlu.bndReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlNluBndReq, NULLP,
      "Bind Request"
   },

   {"tapa.nlu.bndCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlNluBndCfm, NULLP,
      "Bind Confirm"
   },

   {"tapa.nlu.nghReq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlNluNghReq, NULLP,
      "Neighbor Request"
   },
   
   {"tapa.nlu.pciModIndCfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, nlAcHdlNluPciModIndCfm, NULLP,
      "Pci Modification Ind Cfm"
   },

};


/*
*
*       Fun:   nlAcNluInit
*
*       Desc:  Initialization of NLU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nlac_nlureg.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcNluInit
(
Void
)
#else
PUBLIC S16 nlAcNluInit()
#endif
{
   U16   cnt = 0;
   S16   ret = 0;

   TRC2(nlAcNluInit)

   cnt = sizeof(nlAcNluSimpleCmd)/sizeof(nlAcNluSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, nlAcNluSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/* nlAcNluInit */

/*
*
*       Fun:   nlAcNluDeInit
*
*       Desc:  De-Initialize NLU Simple Commands
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nlac_nlureg.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcNluDeInit
(
Void
)
#else
PUBLIC S16 nlAcNluDeInit()
#endif
{

   TRC2(nlAcNluDeInit)

   RETVALUE(ROK);
}/* nlAcNluDeInit --*/


