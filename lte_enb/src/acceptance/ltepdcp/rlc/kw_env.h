

/********************************************************************20**
  
        Name:     LTE RLC file 
    
        Type:     C include file
  
        Desc:     This file contains the constants required for LTE-RLC.
                  The defines in this file need to be changed by the customer 
                  to reflect the software architecture needed to run under the 
                  target system hardware architecture.

        File:     kw_env.h

        Sid:      kw_env.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:46 2014
  
        Prg:      nm 
  
*********************************************************************21*/
/** @file kw_env.h
@brief RLC Hash definitions
*/

#ifndef __KWENVH__
#define __KWENVH__

#define KW_MAX_RLC_INSTANCES            2
#define KW_MAXIMUM_LI                   10
/* kw003.201 Adding new environment variables */
/* This parameter is utilized when KW_BG_DL_PROC enbled. This parameter */
/* defines how many PDUs may be released in one go without affecting    */
/* TTI response time                                                    */
/* kw004.201 modifed the value from 20 to 15 */
/* kw006.201 CR ccpu00111716 */
#define KW_AM_MAX_PDUS_RLS              15
/* This parameter governs maximum number of PDUs to processed at a      */
/* given point when KW_BG_UL_PROC is enabled in both AM and UM modes.   */
/* kw004.201 modifed the value from 20 to 5 */
/* kw006.201 CR ccpu00117290 */
#define KW_AM_UM_MAX_UL_PDUS            5 

#define PJ_MAX_PDCP_INSTANCES   2
#endif /* __KWENVH__ */
  
/********************************************************************30**
  
         End of file:     kw_env.h@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:46 2014
  
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
/main/1      ---       nm   1. Initial release.
/main/2      ---       nm   1. LTERLC Release 2.1
/main/3      kw003.201 vp   1. Fixes for re-segmentation, segement offset
                               value and optimization 
/main/4      kw004.201 ap   1. Modified the values of KW_AM_MAX_PDUS_RLS and
                               KW_AM_MAX_UL_PDUS
/main/5      kw006.201 rd   1. Changed the name of KW_AM_MAX_UL_PDUS to 
                               KW_AM_UM_MAX_UL_PDUS.
*********************************************************************91*/

