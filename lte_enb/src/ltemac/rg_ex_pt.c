



/**********************************************************************
  
     Name:     LTE-MAC
  
     Type:     C file
  
     Desc:     Functions required for scheduling and initialization
  
     File:     rg_ex_pt.c
  
     Sid:      gk_ex_pt.c@@/main/2 - Sat Jul 30 02:21:29 2011
  
     Prg:      st
  
**********************************************************************/


/* header include files (.h) */

#include "envopt.h"           /* environment options      */
#ifdef RG_PT_BUILD
#include "envdep.h"           /* environment dependent    */
#include "envind.h"           /* environment independent  */
#include "gen.h"              /* general layer            */
#include "ssi.h"              /* system service interface */
 
/* header/extern include files (.x)     */
#include "gen.x"              /* general layer            */
#include "ssi.x"              /* system service interface */
   
  
 
/* local externs */
EXTERN S16 rgActvTsk  ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 rgInitExt  ARGS((Void));
  



/*
*
*       Fun:    initialize external
*
*       Desc:   Initializes variables used to interface with Upper/Lower
*               Layer  
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   rg_ex_pt.c
*
*/
  
#ifdef ANSI
PUBLIC S16 rgInitExt
(
void
)
#else
PUBLIC S16 rgInitExt()
#endif
{
   TRC2(rgInitExt)
   RETVALUE(ROK);
} /* end of rgInitExt */



/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from Upper/Lower Layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   rg_ex_pt.c
*
*/
  
#ifdef ANSI
PUBLIC S16 rgActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 rgActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC3(rgActvTsk)
   UNUSED(pst);
   UNUSED(mBuf);
   SExitTsk();
   RETVALUE(ROK);
} /* end of rgActvTsk */
#endif /* RG_PT_BUILD */

  
/**********************************************************************
  
         End of file:     gk_ex_pt.c@@/main/2 - Sat Jul 30 02:21:29 2011
  
**********************************************************************/


/**********************************************************************
  
        Notes:
  
**********************************************************************/
   
/**********************************************************************
  
        Revision history:
  
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     st   1. LTE-MAC Initial Release.
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1
$SID$        ---     rt      1. LTE MAC 4.1 release
*********************************************************************91*/
