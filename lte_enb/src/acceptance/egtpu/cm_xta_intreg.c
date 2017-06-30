
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_intreg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:17 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta.h"
/* cm_xta_intreg_c_001.main_4 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"
/* cm_xta_intreg_c_001.main_4 Removed cm_xta_app.x for Psf-Diameter 1.1 */

PRIVATE CmXtaCmd cmXtaIntSimpleCmd[] =
{
   {"tapa.re",           CMXTA_TYPE_LEAF,   CMXTA_SUBTYPE_RE,        NULLP,        NULLP,
    "Validate Regular Expression"                            },

   {"tapa.send",           CMXTA_TYPE_INT,   CMXTA_SUBTYPE_SEND,        cmXtaHdlIntSend,        NULLP,
    "Send"                            },

/*-- cm_xta_intreg_c_001.main_2 loop changes starts--*/
   {"tapa.repeat.start",          CMXTA_TYPE_INT,   CMXTA_SUBTYPE_REPEAT_START,       cmXtaHdlIntRepeatStart,        NULLP,
    "Repeat Start"                            },

   {"tapa.repeat.end",          CMXTA_TYPE_INT,   CMXTA_SUBTYPE_REPEAT_END,       cmXtaHdlIntRepeatEnd,        NULLP,
    "Repeat End"                            },
   /*-- cm_xta_intreg_c_001.main_2 loop changes starts--*/
   {"tapa.repeat.start.lch.cfg",          CMXTA_TYPE_INT,   CMXTA_SUBTYPE_REPEAT_START,       cmXtaHdlIntRepeatStartLchCfg,        NULLP,
    "Repeat Start"                            },

/*-- cm_xta_intreg_c_001.main_2 loop changes ends--*/

   {"tapa.expect",         CMXTA_TYPE_INT,   CMXTA_SUBTYPE_EXPECT,      cmXtaHdlIntExpect,      NULLP,
    "Expect"                          },

   {"tapa.expseq",         CMXTA_TYPE_INT,   CMXTA_SUBTYPE_EXPSEQ,      cmXtaHdlIntExpSeq,      NULLP,
    "Expect a sequence of"            },

   {"tapa.expopt",         CMXTA_TYPE_INT,   CMXTA_SUBTYPE_EXPOPT,      cmXtaHdlIntExpOpt,      NULLP,
    "Expect Optional"            },

   {"tapa.expset",         CMXTA_TYPE_INT,   CMXTA_SUBTYPE_EXPSET,      cmXtaHdlIntExpSet,      NULLP,
    "Exp Set"                    },

   {"tapa.timeout",        CMXTA_TYPE_INT,   CMXTA_SUBTYPE_TIMEOUT,     cmXtaHdlIntTimeout,     NULLP,
    "Expect    : No message"          },

   {"tapa.delay",          CMXTA_TYPE_INT,   CMXTA_SUBTYPE_DELAY,       cmXtaHdlIntDelay,       NULLP,
    "Delay"               },

   {"tapa.directive",      CMXTA_TYPE_DIR,   CMXTA_SUBTYPE_OTHER,       cmXtaHdlIntDirective,   NULLP,
    "Directive : Set"                    },

   {"tapa.global.directive",      CMXTA_TYPE_DIR,   CMXTA_SUBTYPE_OTHER,       cmXtaHdlIntGlobalDirective,   NULLP,
    "Global Directive : Set"                    },

   {"tapa.comment",        CMXTA_TYPE_DIR,   CMXTA_SUBTYPE_OTHER,       cmXtaHdlIntDummy,       NULLP,
    "Comment"                            },

   {"tapa.invalid",        CMXTA_TYPE_LEAF,  CMXTA_SUBTYPE_OTHER,       cmXtaHdlIntInvalid,       NULLP,
    "Invalid Command"                            },

/* cm_xta_intreg_c_001.main_3: Updated for SIP Realease 2.3 */
   {"tapa.memShow",  CMXTA_TYPE_DIR,  CMXTA_SUBTYPE_OTHER, cmXtaHdlIntSRegInfoShow, NULLP, 
    "SSI memory information: memInfo"      },

   {"tapa.memLeak",  CMXTA_TYPE_DIR,  CMXTA_SUBTYPE_OTHER, cmXtaHdlIntSLogMemLk, NULLP,
    "Memory leak information: memLeakInfo"     },
};

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaIntInit
(
Void
)
#else
PUBLIC S16 cmXtaIntInit()
#endif
{
   U16   cnt;
   S16   ret;

   TRC2(cmXtaIntInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaIntInit(): Init\n"));

   /*-- Load internal simple commands --*/
   cnt = sizeof(cmXtaIntSimpleCmd)/sizeof(cmXtaIntSimpleCmd[0]);

   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, cmXtaIntSimpleCmd)) != ROK)
      RETVALUE(ret);

   /*-- Init global flags --*/
   /*-- Init the flags associated with the TA --*/
   if ((ret = cmXtaDirectiveInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaIntInit(): Init done\n"));

   RETVALUE(ROK);
}/* cmXtaIntInit */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaDirectiveInit
(
Void
)
#else
PUBLIC S16 cmXtaDirectiveInit()
#endif
{
   S16 ret;

   TRC2(cmXtaDirectiveInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaDirectiveInit(): Init\n"));

   /*-- ignoreMsg flag --*/
   cmXtaCb.directives.ignoreMsg = FALSE;

   /*-- logAlarm flag --*/
   cmXtaCb.directives.logAlarm = FALSE;

   /*-- logTrc flag --*/
   cmXtaCb.directives.logTrc = FALSE;

   /*-- Capture Alarm flag --*/
   cmXtaCb.directives.capAlarm = FALSE;

   /*-- ignoreMsg flag --*/
   cmXtaCb.directives.capTrc = FALSE;

   /*-- delayTest flag --*/
   cmXtaCb.directives.delayTest = FALSE;

   /*-- Init global flags --*/
   /*-- Init the flags associated with the TA --*/
   if ((ret = cmXtaAppDirectiveInit()) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaDirectiveInit(): Init done\n"));

   RETVALUE(ROK);
}/* cmXtaDirectiveInit */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaIntDeInit
(
Void
)
#else
PUBLIC S16 cmXtaIntDeInit()
#endif
{
   TRC2(cmXtaIntDeInit)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaIntDeInit(): shutdown initiated\n"));

   CMXTA_DBG_INFO((_cmxtap, "cmXtaIntDeInit(): shutdown done\n"));

   RETVALUE(ROK);
}/* cmXtaIntDeInit */

/********************************************************************30**

         End of file:     cm_xta_intreg.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:17 2015

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
/main/2      ----     up  1. Main release
/main/3      ---      mn   ROHC compliance upgrade
/main/4      ---  cm_xta_intreg_c_001.main_3    ve   1. Updated for SIP 
                                                        Realease 2.3
/main/5      ---- cm_xta_intreg_c_001.main_4 jj 1. Updated for Psf-Diameter 1.1
                                            release Removed cm_xta_app.[hx]
*********************************************************************91*/
