

/********************************************************************20**
  
        Name:    CPJ user interface
    
        Type:    C file
  
        Desc:    This file Contains the Acceptance Register code
                  for CPJ Interface
 
        File:    pjac_cpjreg.c

        Sid:      pjac_cpjreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:45 2015
  
        Prg:     Adarsh
  
*********************************************************************21*/


/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "cpj.h"           /* CPJ defines */
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* PDCP environment options */
#include "pj.h"            /* PDCP defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_cpj.h"      /* CPJ Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "cpj.x"           /* CPJ */
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_cpj.x"      /* CPJ Acceptance defines */


/* Venki */
#ifndef KW_PDCP
PRIVATE CmXtaCmd kwAcCpjSimpleCmd[] =
{
   {"tapa.cpj.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjBndReq, NULLP,
      "CPJ Bind Request"
   },
 
   {"tapa.cpj.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjBndCfm, NULLP,
      "CPJ Bind Confirm"
   },
 
   {"tapa.cpj.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjUbndReq, NULLP,
      "CPJ Unbind Request"
   },
 
   {"tapa.cpj.cfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjCfgReq, NULLP,
      "CPJ Configuration Request"
   },
 
   {"tapa.cpj.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjCfgCfm, NULLP,
      "CPJ Configuration Confirm"
   },
 
   {"tapa.cpj.reestreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjReEstReq, NULLP,
      "CPJ Re-establishment Request"
   },
 
   {"tapa.cpj.reestcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjReEstCfm, NULLP,
      "CPJ Re-establishment Confirm"
   },
 
   {"tapa.cpj.seccfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjSecCfgReq, NULLP,
      "CPJ Security Configuration Request"
   },
 
   {"tapa.cpj.seccfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjSecCfgCfm, NULLP,
      "CPJ Security Configuration Confirm"
   },
 
   {"tapa.cpj.ueidchgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjUeIdChgReq, NULLP,
      "CPJ Configuration Request"
   },
 
   {"tapa.cpj.ueidchgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjUeIdChgCfm, NULLP,
      "CPJ Configuration Confirm"
   },
 
   {"tapa.cpj.countreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjCountReq, NULLP,
      "CPJ Count Report Request"
   },
 
   {"tapa.cpj.countcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjCountCfm, NULLP,
      "CPJ Count Report Confirm"
   },
 
   {"tapa.cpj.sdustareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjSduStaReq, NULLP,
      "CPJ SDU Status Report Request"
   },
 
   {"tapa.cpj.sdustacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjSduStaCfm, NULLP,
      "CPJ SDU Status Report Confirm"
   },
   {"tapa.cpj.datresumereq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjDatResumeReq, NULLP,
      "CPJ Data Resume Request"
   },
   {"tapa.cpj.datresumecfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjDatResumeCfm, NULLP,
      "CPJ Data Resume Confirm"
   },
   {"tapa.cpj.datforwardreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, pjAcHdlCpjDatForwardReq, NULLP,
      "CPJ Data Resume Request"
   },
 
};
 
/*
*
*       Fun:   pjAcCpjInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  pjac_cpjreg.c
*
*/
#ifdef ANSI
PUBLIC S16 pjAcCpjInit
(
Void
)
#else
PUBLIC S16 pjAcCpjInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(pjAcCpjInit);
 
   cnt = sizeof(kwAcCpjSimpleCmd)/sizeof(kwAcCpjSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcCpjSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* pjAcCpjInit */
 
/*
*
*       Fun:   pjAcCpjDeInit
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  kwac_cpjreg.c
*
*/
#ifdef ANSI
PUBLIC S16 pjAcCpjDeInit
(
Void
)
#else
PUBLIC S16 pjAcCpjDeInit()
#endif
{
   TRC2(pjAcCpjDeInit);
 
   pjAcUtlCpjCQMakeNull(&(kwAcCb.nhCpjCb.cfgReq));

   RETVALUE(ROK);
}/* pjAcCpjDeInit --*/

#endif /* KW_PDCP */

  
/********************************************************************30**
         End of file:     pjac_cpjreg.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:45 2015
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
/main/1      ---      vb         1. LTE PDCP Initial Release 2.1.
*********************************************************************91*/
