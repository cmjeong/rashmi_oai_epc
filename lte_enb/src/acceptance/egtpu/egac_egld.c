/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    egac_szld.c

     Sid:      egac_egld.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:27 2015

     Prg:     an
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
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "cm_xta.h"

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "cm_xta.x"

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
 *       File:   egac_egld.c
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
 *       File:   egac_egld.c
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
 *       File:   egac_egld.c
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

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   
*
*       Desc:  Resume Add Command processing after response from line card.
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
   RETVALUE(CMXTA_ERR_NONE);
}

/********************************************************************30**

         End of file:     egac_egld.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:27 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rkumar      1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
*********************************************************************91*/
