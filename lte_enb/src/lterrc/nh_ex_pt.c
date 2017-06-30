


/**********************************************************************
  
     Name:     RRC
  
     Type:     C file
  
     Desc:     Functions required for scheduling and initialization.
  
     File:     nh_ex_pt.c
  
     Sid:      ni_ex_pt.c@@/main/4 - Fri Jul  1 01:13:18 2011
  
     Prg:      st
  
**********************************************************************/


/* Header include files (.h) */
static const char* RLOG_MODULE_NAME="RRC";
static int RLOG_MODULE_ID=512;
static int RLOG_FILE_ID=101;

#include "envopt.h"           /* Environment options      */
#ifdef NH_PT_BUILD
#include "envdep.h"           /* Environment dependent    */
#include "envind.h"           /* Environment independent  */
#include "gen.h"              /* General layer            */
#include "ssi.h"              /* System service interface */
 
/* Header/extern include files (.x)     */
#include "gen.x"              /* General layer            */
#include "ssi.x"              /* System service interface */
   
  
 
/* Local externs */
EXTERN S16 nhActvTsk  ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 nhInitExt  ARGS((Void));
  



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
*       File:   nh_ex_pt.c
*
*/
  
#ifdef ANSI
PUBLIC S16 nhInitExt
(
void
)
#else /* ANSI */
PUBLIC S16 nhInitExt()
#endif /* ANSI */
{
   TRC2(nhInitExt)
   RETVALUE(ROK);
} /* end of nhInitExt */



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
*       File:   nh_ex_pt.c
*
*/
  
#ifdef ANSI
PUBLIC S16 nhActvTsk
(
Pst *pst,                   /* Post */
Buffer *mBuf                /* Message buffer */
)
#else /* ANSI */
PUBLIC S16 nhActvTsk(pst, mBuf)
Pst *pst;                   /* Post */
Buffer *mBuf;               /* Message buffer */
#endif /* ANSI */
{
   TRC3(nhActvTsk)
   UNUSED(pst);
   UNUSED(mBuf);
   SExitTsk();
   RETVALUE(ROK);
} /* end of nhActvTsk */
#endif /* NH_PT_BUILD */

  
/**********************************************************************
  
         End of file:     ni_ex_pt.c@@/main/4 - Fri Jul  1 01:13:18 2011
  
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
/main/2      ---      st               1. RRC Initial Release.
/main/3      ---      ch               1. RRC Release 2.1.
/main/4      ---      sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
