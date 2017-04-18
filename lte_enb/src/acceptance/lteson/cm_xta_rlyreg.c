
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_rlyreg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:27 2015

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
#include "lry.h"
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
#include "lry.x"
#include "cm_xta.x"


PRIVATE CmXtaCmd cmXtaLrySimpleCmd[] =
{
   /*-- SCTP Cfg APIs --*/
   {"tapa.lry.cfg.gen",       CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaRlyGenCfgReq, NULLP,
      "Relay Gen Config Request"
   },


   {"tapa.lry.cfgcfm",        CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaRlyCfgCfm, NULLP,
      "Relay Config Confirm"
   },

   {"tapa.lry.channel.cfg",     CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, cmXtaRlyChannelCfgReq, NULLP,
    "Relay Channel Request"
    },


 };
/*
*
*       Fun:   cmXtaLryInit
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
PUBLIC S16 cmXtaLryInit
(
Void
)
#else
PUBLIC S16 cmXtaLryInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(cmXtaLryInit)

   cnt = sizeof(cmXtaLrySimpleCmd)/sizeof(cmXtaLrySimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, cmXtaLrySimpleCmd)) != ROK)
      RETVALUE(ret);

   RETVALUE(ROK);
}/*  cmXtaLshInit*/

/*
*
*       Fun:   cmXtaLryDeInit
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
PUBLIC S16 cmXtaLryDeInit
(
Void
)
#else
PUBLIC S16 cmXtaLryDeInit()
#endif
{
/*   Pst      pst;*/

/*   S16      ret;*/

   TRC2(cmXtaLryDeInit)

   RETVALUE(ROK);
}/* soAcLryDeInit */
/********************************************************************30**

         End of file:     cm_xta_rlyreg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:27 2015

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
/main/1      ----     up  1. Main release
*********************************************************************91*/
