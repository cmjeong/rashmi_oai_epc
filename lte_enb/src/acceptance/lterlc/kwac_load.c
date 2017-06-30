

/********************************************************************20**

     Name:    RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_load.c

     Sid:      kwac_load.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:33 2014

     Prg:     up 
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
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_ckw.h"      /* CKW Acceptance defines */

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
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_ckw.x"      /* CKW Acceptance defines */


/*
 *
 *       Fun:    cmXtaAppLoadFindnCreate
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaAppLoadFindnCreate
(
Void  *msg,
Bool  *newCall,
CmXtaLoadCb  **loadCb
)
#else
PUBLIC S16 cmXtaAppLoadFindnCreate(msg, newCall, loadCb)
Void  *msg;
Bool  *newCall;
CmXtaLoadCb  **loadCb;
#endif
{
   /* kw005.201 removed warning */
   UNUSED(msg);
   UNUSED(newCall);
   UNUSED(loadCb);
   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppLoadFindnCreate() */

/*
 *
 *       Fun:    cmXtaAppLoadFreeMsg
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaAppLoadFreeMsg
(
Void     *loadMsg
)
#else
PUBLIC S16 cmXtaAppLoadFreeMsg(loadMsg)
Void     *loadMsg;
#endif
{
   /* kw005.201 removed warning */
   UNUSED(loadMsg);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppLoadFreeMsg() */ 

/*
 *
 *       Fun:    cmXtaAppLoadDelete
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sotutl.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmXtaAppLoadDelete
(
CmXtaLoadCb  *loadCb,
Bool      fail
)
#else
PUBLIC S16 cmXtaAppLoadDelete(loadCb, fail)
CmXtaLoadCb  *loadCb;
Bool      fail;
#endif
{
   TRC2(cmXtaAppLoadDelete)
   /* kw005.201 removed warning */
   UNUSED(loadCb);
   UNUSED(fail);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaAppLoadDelete() */

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
PUBLIC S16 cmXtaAppLoadInit
(
)
#else
PUBLIC S16 cmXtaAppLoadInit()
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun: cmXtaAppLoadDeInit  
*
*       Desc:  Resume Add Command processing after response from line card.
*              Command : MGT_ADD
*              Event   : AG_CMD_EVT_LCRESP
*
*       Ret:   If success, return CMXTA_ERR_NONE 
*              If failure, return error Code
*
*       Notes: 
*
*       File:  ag_add.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppLoadDeInit
(
)
#else
PUBLIC S16 cmXtaAppLoadDeInit()
#endif
{
   TRC2(cmXtaAppLoadDeInit)

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun: cmXtaAppLoadGetCurStep  
*
*       Desc:  Resume Add Command processing after response from line card.
*              Command : MGT_ADD
*              Event   : AG_CMD_EVT_LCRESP
*
*       Ret:   If success, return CMXTA_ERR_NONE 
*              If failure, return error Code
*
*       Notes: 
*
*       File:  ag_add.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppLoadGetCurStep
(
Void  *loadMsg,
CmXtaLoadCb  *loadCb,
U16   *curLoadIndx,
U16   *retransLoadIndx
)
#else
PUBLIC S16 cmXtaAppLoadGetCurStep(loadMsg, loadCb, curLoadIndx, retransLoadIndx)
Void  *loadMsg;
CmXtaLoadCb  *loadCb;
U16   *curLoadIndx;
U16   *retransLoadIndx;
#endif
{
   TRC2(cmXtaAppLoadGetCurStep)

   /* kw005.201 removed warning */
   UNUSED(loadMsg);
   UNUSED(loadCb);
   UNUSED(curLoadIndx);
   UNUSED(retransLoadIndx);

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   
*
*       Desc:  Resume Add Command processing after response from line card.
*              Command : MGT_ADD
*              Event   : AG_CMD_EVT_LCRESP
*
*       Ret:   If success, return CMXTA_ERR_NONE 
*              If failure, return error Code
*
*       Notes: 
*
*       File:  ag_add.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaAppLoadEngine
(
CmXtaLoadCb    *loadCb,
Void        *loadMsg,
Bool        retransMode,
U16         curLoadIndx,
U16         retransLoadIndx
)
#else
PUBLIC S16 cmXtaAppLoadEngine(loadCb, loadMsg, retransMode, curLoadIndx, retransLoadIndx)
CmXtaLoadCb    *loadCb;
Void        *loadMsg;
Bool        retransMode;
U16         curLoadIndx;
U16         retransLoadIndx;
#endif
{
   /*-- Return end of processing --*/
   /* kw005.201 removed warning */
   UNUSED(loadMsg);
   UNUSED(loadCb);
   UNUSED(retransMode);
   UNUSED(curLoadIndx);
   UNUSED(retransLoadIndx);
   RETVALUE(CMXTA_ERR_NONE);
}

/********************************************************************30**

         End of file:     kwac_load.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:33 2014

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
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
/main/3      kw005.201 ap     1. Removed compilation warning.
*********************************************************************91*/

