
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_lshreg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:24 2015

     Prg:     up 

*********************************************************************21*/

/* header include files (.h) */

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


PRIVATE CmXtaCmd cmXtaLshSimpleCmd[] =
{
   /*-- SCTP Cfg APIs --*/
   {"tapa.lsh.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlLshCfgReq, NULLP,
      "System Agent Gen Config Request"
   },


   {"tapa.lsh.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlLshCfgCfm, NULLP,
      "System Agent Config Confirm"
   },

   {"tapa.lsh.cntrl.trc",     CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlLshTrcCntrlReq, NULLP,
    "System Agent Trace Control Request"
    },


   {"tapa.lsh.cntrlcfm",      CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlLshCntrlCfm, NULLP,
      "System Agent Control Confirm"
   },


   /*-- SCTP Statistics APIs --*/
   {"tapa.lsh.sts.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaHdlLshStsReq, NULLP,
    "System Agent Gen Statistics Request"
   },


#if 0
   {"tapa.lsh.stscfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER,  cmXtaHdlLshStsCfm, NULLP,
    "System Agent Statistics Confirm"
   },
#endif


 };
/*
*
*       Fun:   cmXtaLshInit
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
PUBLIC S16 cmXtaLshInit
(
Void
)
#else
PUBLIC S16 cmXtaLshInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(soAcLshInit)

   cnt = sizeof(cmXtaLshSimpleCmd)/sizeof(cmXtaLshSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, cmXtaLshSimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/*  cmXtaLshInit*/

/*
*
*       Fun:   cmXtaLshDeInit
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
PUBLIC S16 cmXtaLshDeInit
(
Void
)
#else
PUBLIC S16 cmXtaLshDeInit()
#endif
{
/*   Pst      pst;*/

/*   S16      ret;*/

   TRC2(cmXtaLshDeInit)

   RETVALUE(ROK);
}/* soAcLsbDeInit */
/********************************************************************30**

         End of file:     cm_xta_lshreg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:24 2015

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
/main/1      ----     aj  1. Main release
*********************************************************************91*/
