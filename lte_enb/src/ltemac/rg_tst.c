



/**********************************************************************
  
     Name:     LTE-MAC - test
  
     Type:     C source file
  
     Desc:     Sample C source code used to link LTE-MAC in a
               TRILLIUM development environment.

     File:     rg_tst.c
  
     Sid:      gk_tst.c@@/main/2 - Sat Jul 30 02:21:56 2011
  
     Prg:      st
  
**********************************************************************/
  
  
/* header include files (.h) */

#include "envopt.h"        /* environment options */  
#ifdef RG_PT_BUILD
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#ifdef DOS                 /* dos environment */
#include <process.h>       /* dos - process */  
#endif

#ifdef __cplusplus
extern "C" {
#endif

EXTERN  int main ARGS((int argc,char **argv ));
EXTERN  void exit ARGS((int status ));
  
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
 *       File:  rg_tst.c
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
  /* Stack Crash Problem for TRACE5 Changes. Added return below */
  RETVALUE(OK);
} /* end of main */
#endif /* RG_PT_BUILD */

  
/**********************************************************************
  
         End of file:     gk_tst.c@@/main/2 - Sat Jul 30 02:21:56 2011
  
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
/main/1      ---     st   1. LTE MAC 2.1 release
/main/2   rg008.201  rsharon   1.Fixed TRACE5 issue.
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1           
$SID$        ---     rt   1. LTE MAC 4.1 release
*********************************************************************91*/
