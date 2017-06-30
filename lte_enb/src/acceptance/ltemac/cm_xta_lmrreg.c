
/********************************************************************20**
  
     Name:     psf-sip
  
     Type:     C source file
  
     Desc:      
  
     File:     cm_xta_lmrreg.c
  
     Sid:      cm_xta_lmrreg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:20 2015
  
     Prg:      sk
  
*********************************************************************21*/

/* header/extern include files (.x) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta_app.h"
#include "cm_ftha.h"
#include "lmr.h"
#include "lmr.h"
#include "lsh.h"
#include "lsg.h"
#include "cm_xta.h"

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta_app.x"
#include "cm_ftha.x"
#include "lmr.x"
#include "lsh.x"
#include "lsg.x"
#include "cm_xta.x"


/* cm_xta_lmrreg_c_001.main_1: Corrected the discription */
PRIVATE CmXtaCmd cmXtaMrSimpleCmd[] =
{
   /* MR Cfg APIs */
   {"tapa.lmr.cfg.gen",  CMXTA_TYPE_LEAF,  CMXTA_SUBTYPE_OTHER,  cmXtaHdlMrGenCfgReq,  NULLP,
      "General Configuration Request for MR"         },

   {"tapa.lmr.cfgcfm",  CMXTA_TYPE_LEAF,  CMXTA_SUBTYPE_OTHER,  cmXtaHdlMrCfgCfm,  NULLP,
      "Configuration Confirmation for MR"            },

   /* MR Control APIs */
   {"tapa.lmr.cntrl.shutdown",  CMXTA_TYPE_LEAF,  CMXTA_SUBTYPE_OTHER,  cmXtaHdlMrShutDownCntrlReq,  NULLP,
      "Shutdown Control Request for MR"              },

   {"tapa.lmr.cntrlcfm",  CMXTA_TYPE_LEAF,  CMXTA_SUBTYPE_OTHER,  cmXtaHdlMrCntrlCfm,  NULLP,
      "Control Confirmation for MR"                  },

};

/*
*
*       Fun:   cmXtaLmrInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lmrreg.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaLmrInit
(
Void
)
#else
PUBLIC S16 cmXtaLmrInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(cmXtaLmrInit)

   cnt = sizeof(cmXtaMrSimpleCmd)/sizeof(cmXtaMrSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, cmXtaMrSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/*  cmXtaLmrInit*/

/*
*
*       Fun:   cmXtaLmrDeinit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  tq_aghdlr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaLmrDeinit
(
Void
)
#else
PUBLIC S16 cmXtaLmrDeinit()
#endif
{
/*   Pst      pst;*/

/*   S16      ret;*/

   TRC2(cmXtaLmrDeinit)

   RETVALUE(ROK);
}/* cmXtaLmrDeinit */

/********************************************************************30**

         end of file:     cm_xta_lmrreg.c@@/main/1 - wed jun 27 16:21:27 2007

*********************************************************************31*/


/********************************************************************40**

        notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ----      aj      1. main release
/main/2      ---      cm_xta_lmrreg_c_001.main_1 pka 1. Corrected the discription
*********************************************************************91*/
