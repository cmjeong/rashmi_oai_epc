



/********************************************************************20**
  
     Name:     s1ap - test
  
     Type:     C source file
  
     Desc:     Sample C source code used to link s1ap in a
               TRILLIUM development environment.

     File:     sq_tst.c
  
     Sid:      sq_tst.c@@/main/4 - Tue May  8 16:04:55 2012
  
     Prg:      sn
  
*********************************************************************21*/
  
  
/* header include files (.h) */

#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#ifdef DOS                 /* dos environment */
#include <process.h>       /* dos - process */  
#endif /* DOS */

/* header/extern include files (.x), if any */
  
/* local defines, if any */
  
/* local typedefs, if any */
  
/* local externs, if any */
  
/* forward references, if any */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

EXTERN  int main ARGS((int argc,char **argv ));
EXTERN  void exit ARGS((int status ));
  
#ifdef __cplusplus
}
#endif /* __cplusplus */

/* functions in other modules, if any */
  
/* public variable declarations, if any */
  
/* private variable declarations, if any */
  
/* functions */
  
/*
 *
 *       Fun:   Main
 *
 *       Desc:  Program execution starts here.
 *
 *       Ret:   None
 *
 *       Notes: None
 *
 *       File:  ra_tst.c
 *
 */
  
#ifdef ANSI
int main
(
int argc,                   /* argument count */
char **argv                 /* argument values */
)
#else /* ANSI */
int main(argc, argv)
int argc;                   /* argument count */
char **argv;                /* argument values */
#endif  /* ANSI */
{
   TRC1(main)

   UNUSED(argc);
   UNUSED(argv);

   exit(0);

   return(OK);
} /* end of main */

/********************************************************************30**
  
         End of file:     sq_tst.c@@/main/4 - Tue May  8 16:04:55 2012
  
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
/main/4      ---      va    1. Updated for S1AP release 4.1
*********************************************************************91*/
