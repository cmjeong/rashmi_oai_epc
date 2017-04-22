

/**********************************************************************
  
     Name:     LTE MAC Convergence Layer 
  
     Type:     C file
  
     Desc:     Functions required for scheduling and initialization.
  
     File:     ys_ex_pt.c
  
     Sid:      yw_ex_pt.c@@/main/2 - Thu Dec  2 02:27:26 2010
  
     Prg:      st
  
**********************************************************************/


/* Header include files (.h) */

#include "envopt.h"           /* Environment options      */
#include "envdep.h"           /* Environment dependent    */
#include "envind.h"           /* Environment independent  */
#include "gen.h"              /* General layer            */
#include "ssi.h"              /* System service interface */
 
/* Header/extern include files (.x)     */
#include "gen.x"              /* General layer            */
#include "ssi.x"              /* System service interface */
   
  
 
/* Local externs */
EXTERN S16 ysActvTsk  ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 ysInitExt  ARGS((Void));
  



/*
*
*       Fun:    Initialize external
*
*       Desc:   Initializes variables used to interface with Upper/Lower
*               Layer.  
*
*       Ret:    ROK - OK
*
*       Notes:  None
*
*       File:   ys_ex_pt.c
*
*/
  
#ifdef ANSI
PUBLIC S16 ysInitExt
(
void
)
#else
PUBLIC S16 ysInitExt()
#endif
{
   TRC2(ysInitExt)
   RETVALUE(ROK);
} /* end of ysInitExt */



/*
*
*       Fun:    Activate task
*
*       Desc:   Processes received event from Upper/Lower Layer.
*
*       Ret:    ROK - OK
*
*       Notes:  None
*
*       File:   ys_ex_pt.c
*
*/
  
#ifdef ANSI
PUBLIC S16 ysActvTsk
(
Pst *pst,                   /* Post */
Buffer *mBuf                /* Message buffer */
)
#else
PUBLIC S16 ysActvTsk(pst, mBuf)
Pst *pst;                   /* Post */
Buffer *mBuf;               /* Message buffer */
#endif
{
   TRC3(ysActvTsk)
   UNUSED(pst);
   UNUSED(mBuf);
   SExitTsk();
   RETVALUE(ROK);
} /* end of ysActvTsk */

  
/**********************************************************************
  
         End of file:     yw_ex_pt.c@@/main/2 - Thu Dec  2 02:27:26 2010
  
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
/main/2      ---     sgm                   1. eNodeB 1.2 release
*********************************************************************91*/
