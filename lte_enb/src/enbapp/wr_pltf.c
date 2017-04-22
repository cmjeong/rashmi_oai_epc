
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_pltf.c

     Sid:      fc_pltf.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:50:50 2016

     Prg:      spoovali 

*********************************************************************21*/

/* header includes */
 
#include "wr.h" 
#include "wr_cmn.h" 
#include "wr_smm_smallcell.h"
#include "wr_emm.h" 
#include "wr_ifm_dam.h"
#include "wr_emm_pbm.h"
#include "wr_ifm_rrc.h"
#include "wr_ifm_l1.h"
#include "wr_ifm_schd.h"
#include "wr_ifm_rrm.h"

#ifdef LTE_PAL_ENB
/*
 *       Fun:     wrGetPfVersion
 *
 *       Desc:    This will return Platform verion string to caller.
 *
 *       Ret:     ROK   - OK / RFAILED - Failure
 *
 *       Notes :  None.
 */
const char * wrPfVersion = "PAL";
PUBLIC const char * wrGetPfVersion
(
)
{
   RETVALUE(wrPfVersion);
}
#endif

/********************************************************************30**

           End of file:     fc_pltf.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:50:50 2016

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
/main/0        ---      spoovali         1. T3K code cleanup
*********************************************************************91*/



