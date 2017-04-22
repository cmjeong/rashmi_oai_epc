
  
/********************************************************************20**
  
     Name:     X2AP
  
     Type:     C file
  
     Desc:     Functions required for scheduling and initialization
  
     File:     cz_ex_pt.c
  
     Sid:      tr_ex_pt.c@@/main/2 - Tue Aug 30 18:36:11 2011
  
     Prg:      sy
  
*********************************************************************21*/

/* header include files (.h) */

#include "envopt.h"                             /* environment options      */
#include "envdep.h"                             /* environment dependent    */
#include "envind.h"                             /* environment independent  */
#include "gen.h"                                /* general layer            */
#include "ssi.h"                                /* system service interface */
#include "cz.h"
 
/* header/extern include files (.x)     */
#include "gen.x"                                /* general layer            */
#include "ssi.x"                                /* system service interface */
   
/* local defines */
  
/* local typedefs */
  
/* local externs */
EXTERN S16 czActvTsk  ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 czInitExt  ARGS((Void));
  
/* cz001.101 : CR fixes */
/* forward references */

/* functions in other modules */

/* public variable declarations */
  
/* private variable declarations */
  
/*
*     support functions
*/

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
*       File:   cz_ex_pt.c
*
*/
  
#ifdef ANSI
PUBLIC S16 czInitExt
(
void
)
#else
PUBLIC S16 czInitExt()
#endif
{
   CZ_TRC2(czInitExt)
   CZ_RETVALUE(ROK);
} /* end of czInitExt */



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
*       File:   cz_ex_pt.c
*
*/
  
#ifdef ANSI
PUBLIC S16 czActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 czActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   CZ_TRC3(czActvTsk)
   UNUSED(pst);
   UNUSED(mBuf);
   SExitTsk();
   CZ_RETVALUE(ROK);
} /* end of czActvTsk */

  
/********************************************************************30**
  
         End of file:     tr_ex_pt.c@@/main/2 - Tue Aug 30 18:36:11 2011
  
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
/main/1      ---      sy            1. LTE-X2AP Initial Release.
           cz001.101  mm            1. CR Fixes, Memory Leak fixes.
/main/2      ---      pt            1. LTE-X2AP 3.1 release.
*********************************************************************91*/
