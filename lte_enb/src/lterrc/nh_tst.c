


/**********************************************************************
  
     Name:     RRC - test
  
     Type:     C source file
  
     Desc:     Sample C source code used to link RRC in a
               TRILLIUM development environment.

     File:     nh_tst.c
  
     Sid:      ni_tst.c@@/main/3 - Fri Jul  1 01:13:22 2011
  
     Prg:      st
  
**********************************************************************/
  
  
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="RRC";
static int RLOG_MODULE_ID=512;
static int RLOG_FILE_ID=102;

#ifdef NH_PT_BUILD

#ifdef DOS                 /* DOS environment */
#include <process.h>       /* DOS process */  
#endif /* DOS */

/* header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */

#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hashlist Defines */
#include "cm_mblk.h"       /* Common memory allocation library defines */
#include "cm_pasn.h"       /* Common Pasn Defines */

#include "cm_lte.h"        /* Common LTE defines */
#include "kwu.h"           /* KWU Interface defines */
#include "ckw.h"           /* CKW Interface defines */
#include "crg.h"           /* CRG Interface defines */
#include "cpj.h"           /* CPJ Interface defines */

#include "nhu.h"           /* NHU Interface defines */
#include "nhu_asn.h"       /* NHU ASN defines */
#include "lnh.h"           /* LNH Interface defines */
#include "pju.h"           /* PJU Interface defines */
#include "nh.h"            /* NH defines */

/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "cm5.x"           /* timer services */

#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_hash.x"       /* Common Hashlist Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_mblk.x"       /* Common memory allocation */
#include "cm_pasn.x"       /* Common Hashlist Definitions */


#include "cm_lte.x"        /* common LTE includes */
#include "kwu.x"           /* KWU Interface includes */
#include "ckw.x"           /* CKW Interface includes */
#include "crg.x"           /* CRG Interface includes */
#include "pju.x"           /* PJU Interface includes */
#include "cpj.x"           /* CDM Interface includes */

#include "nhu.x"           /* NHU Interface includes */
#include "nhu_asn.x"       /* NHU ASN includes */
#include "lnh.x"           /* LNH Interface includes */
#include "nh.x"            /* NH defines */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

EXTERN  int main ARGS((int argc,char **argv ));

EXTERN void exit ARGS((int status ));
  
#ifdef __cplusplus
}
#endif /* __cplusplus */
 
 
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
 *       File:  nh_tst.c
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
#endif /* ANSI */
{
   TRC1(main)

   UNUSED(argc);
   UNUSED(argv);

   exit(0);

   return(OK);
} /* end of main */
#endif /* NH_PT_BUILD */

  
/**********************************************************************
  
         End of file:     ni_tst.c@@/main/3 - Fri Jul  1 01:13:22 2011
  
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
/main/1      ---      st               1. RRC Initial Release.
/main/2      ---      ch               1. RRC Release 2.1.
/main/3      ---      sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
