


/********************************************************************20**
  
     Name:     LTE-RLC
  
     Type:     C source file
  
     Desc:     Sample C source code used to link RLC in 
               a TRILLIUM development environment.
  
     File:     kw_tst.c
  
     Sid:      kw_tst.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:23:17 2015
  
     Prg:      cp 
  
*********************************************************************21*/

  
/* header include files (.h) */
  
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#ifdef DOS                 /* dos environment */
#include <process.h>       /* dos - process */  
#endif

/* header/extern include files (.x) */
  
  
/* local defines, if any */
  
/* local typedefs, if any */
  
/* local externs, if any */
  
/* forward references, if any */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

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
*       File:  kw_tst.c
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
   exit(0);
   RETVALUE(OK);
} /* end of main */

  

/********************************************************************30**

         End of file:     kw_tst.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:23:17 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**
 
    ver       pat    init                  description
------------ -------- ---- -----------------------------------------------
/main/1      ---   nm         1. Initial release.
/main/2      ---      gk   1. LTERLC Release 2.1
*********************************************************************91*/
