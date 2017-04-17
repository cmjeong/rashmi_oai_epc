
/**********************************************************************
  
     Name:     LTE MAC Convergence Layer - test
  
     Type:     C source file
  
     Desc:     Sample C source code used to link CL in a
               TRILLIUM development environment.

     File:     ys_tst.c
  
     Sid:      yw_tst.c@@/main/2 - Thu Dec  2 02:27:27 2010
  
     Prg:      hsingh 
  
**********************************************************************/
  
  
/* header include files (.h) */

/* header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#ifdef DOS                 /* DOS environment */
#include <process.h>       /* DOS process */  
#endif

/* header/extern include files (.x) */


#ifdef __cplusplus
extern "C" {
#endif

EXTERN  int main ARGS((int argc,char **argv ));

EXTERN void exit ARGS((int status ));
  
#ifdef __cplusplus
}
#endif
 
 
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
 *       File:  ys_tst.c
 *
 */
  
#ifdef ANSI
int main
(
int argc,                   /* argument count */
char **argv                 /* argument values */
)
#else
int main(argc, argv)
int argc;                   /* argument count */
char **argv;                /* argument values */
#endif
{
   TRC1(main)

   UNUSED(argc);
   UNUSED(argv);

   exit(0);

   return(OK);
} /* end of main */

  
/********************************************************************30**
  
         End of file:     yw_tst.c@@/main/2 - Thu Dec  2 02:27:27 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm                   1. eNodeB 1.2 release
*********************************************************************91*/
