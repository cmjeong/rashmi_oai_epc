
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_flag.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:14 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta.h"
/* cm_xta_flag_c_001.main_2 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"
/* cm_xta_flag_c_001.main_2 Removed cm_xta_app.x for Psf-Diameter 1.1 */
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
PUBLIC S16 cmXtaFlInit
(
)
#else
PUBLIC S16 cmXtaFlInit()
#endif /* ANSI */
{
   TRC2(cmXtaFlInit)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaFlInit(): \n"));

   RETVALUE(CMXTA_ERR_NONE);
} /* end of cmXtaFlInit() */


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
PUBLIC Bool cmXtaFlIsSet
(
U16 flag
)
#else
PUBLIC Bool cmXtaFlIsSet(flag)
U16 flag;
#endif /* ANSI */
{
   TRC2(cmXtaFlIsSet)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaFlIsSet(): flag (%d)\n", flag));

   if (flag < CMXTA_MAX_FLAGS)
      RETVALUE(cmXtaFlag[flag]);
   else
      RETVALUE(FALSE);

} /* end of cmXtaFlIsSet() */

/********************************************************************30**

         End of file:     cm_xta_flag.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:14 2015

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
/main/2      ----     up  1. Main release
/main/3      ---- cm_xta_flag_c_001.main_2 jj 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx]
*********************************************************************91*/
