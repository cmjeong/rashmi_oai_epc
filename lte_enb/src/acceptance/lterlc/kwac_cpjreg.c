

/********************************************************************20**
  
        Name:    CPJ user interface
    
        Type:    C file
  
        Desc:    This file Contains the Acceptance Register code
                  for CPJ Interface
 
        File:    kwac_cpjreg.c

        Sid:      kwac_cpjreg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:25 2014
  
        Prg:     chakrapani
  
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
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CPJ defines */
#include "cpj.h"           /* CPJ defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_cpj.h"      /* CPJ Acceptance defines */

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
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CPJ */
#include "cpj.x"           /* CPJ */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_cpj.x"      /* CPJ Acceptance defines */


#ifdef KW_PDCP
PRIVATE CmXtaCmd kwAcCpjSimpleCmd[] =
{
   {"tapa.cpj.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjBndReq, NULLP,
      "CPJ Bind Request"
   },
 
   {"tapa.cpj.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjBndCfm, NULLP,
      "CPJ Bind Confirm"
   },
 
   {"tapa.cpj.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjUbndReq, NULLP,
      "CPJ Unbind Request"
   },
 
   {"tapa.cpj.cfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjCfgReq, NULLP,
      "CPJ Configuration Request"
   },
 
   {"tapa.cpj.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjCfgCfm, NULLP,
      "CPJ Configuration Confirm"
   },
 
   {"tapa.cpj.reestreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjReEstReq, NULLP,
      "CPJ Re-establishment Request"
   },
 
   {"tapa.cpj.reestcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjReEstCfm, NULLP,
      "CPJ Re-establishment Confirm"
   },
 
   {"tapa.cpj.seccfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjSecCfgReq, NULLP,
      "CPJ Security Configuration Request"
   },
 
   {"tapa.cpj.seccfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjSecCfgCfm, NULLP,
      "CPJ Security Configuration Confirm"
   },
 
   {"tapa.cpj.ueidchgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjUeIdChgReq, NULLP,
      "CPJ Configuration Request"
   },
 
   {"tapa.cpj.ueidchgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjUeIdChgCfm, NULLP,
      "CPJ Configuration Confirm"
   },
 
   {"tapa.cpj.countreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjCountReq, NULLP,
      "CPJ Count Report Request"
   },
 
   {"tapa.cpj.countcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjCountCfm, NULLP,
      "CPJ Count Report Confirm"
   },
 
   {"tapa.cpj.sdustareq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjSduStaReq, NULLP,
      "CPJ SDU Status Report Request"
   },
 
   {"tapa.cpj.sdustacfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCpjSduStaCfm, NULLP,
      "CPJ SDU Status Report Confirm"
   },
 
};
 
/*
*
*       Fun:   kwAcCpjInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  kwac_cpjreg.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcCpjInit
(
Void
)
#else
PUBLIC S16 kwAcCpjInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(kwAcCpjInit);
 
   cnt = sizeof(kwAcCpjSimpleCmd)/sizeof(kwAcCpjSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcCpjSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* kwAcCpjInit */
 
/*
*
*       Fun:   kwAcCpjDeInit
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
PUBLIC S16 kwAcCpjDeInit
(
Void
)
#else
PUBLIC S16 kwAcCpjDeInit()
#endif
{
   TRC2(kwAcCpjDeInit);
 
   kwAcUtlCpjCQMakeNull(&(kwAcCb.nhCpjCb.cfgReq));

   RETVALUE(ROK);
}/* kwAcCpjDeInit --*/

#endif /* KW_PDCP */

  
/********************************************************************30**
         End of file:     kwac_cpjreg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:25 2014
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
/main/1      ---   gk         1. LTERLC Release 2.1.
*********************************************************************91*/

