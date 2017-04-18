/********************************************************************20**
  
        Name:     LTE RLC file 
    
        Type:     C include file
  
        Desc:     This file contains the constants required for LTE-RLC.
                  The defines in this file need to be changed by the customer 
                  to reflect the software architecture needed to run under the 
                  target system hardware architecture.

        File:     kw_env.h

        Sid:      kw_env_t2k.h@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:43:24 2014
  
        Prg:      nm 
  
*********************************************************************21*/
/** @file kw_env.h
@brief RLC Hash definitions
*/

#ifndef __KWENVH__
#define __KWENVH__

#define KW_MAX_RLC_INSTANCES            2
#define KW_MAX_LI                       KWU_MAX_STA_IND_SDU

#define KW_MAX_DL_LI                   28 
#define KW_MAX_NEW_DL_PDU              2
/* kw003.201 Adding new environment variables */
/* This parameter is utilized when KW_BG_DL_PROC enbled. This parameter */
/* defines how many PDUs may be released in one go without affecting    */
/* TTI response time                                                    */
/* kw004.201 modifed the value from 20 to 15 */
#define KW_AM_MAX_PDUS_RLS              1
/* This parameter governs maximum number of PDUs to processed at a      */
/* given point when KW_BG_UL_PROC is enabled.                           */
/* kw004.201 modifed the value from 20 to 5 */
#define KW_AM_MAX_UL_PDUS               1 

#define KW_AM_UM_MAX_UL_SDUS            1
#define KW_AM_UM_MAX_DL_SDUS            300

#ifdef SPLIT_RLC_DL_TASK
#define KW_MAX_TO_BE_FREED              60
#else
#define KW_MAX_TO_BE_FREED              10
#endif

/* Number of packets queued in SDU Q after which overload 
 * START is signalled to PDCP for an UM bearer */
#define KW_UM_RB_OVERLOAD_HIGH_THRES   512
/* Number of packets queued in SDU Q after which overload 
 * STOP is signalled to PDCP for an UM bearer */
#define KW_UM_RB_OVERLOAD_LOW_THRES  300 

/* Value of this macro can be in the range of 1 to RGU_MAX_PDU */
#define KW_MAX_PDU                      2

#ifdef LTE_L2_MEAS
/* This value is decided on the assumption that there will be maximum 3 active DRB at a time */
#define KW_MAX_ACTV_DRB                2
/* Assumption is that all UEs wont have all RBs with max SDU: if greater, will be ignored */
#define KW_L2MEAS_SDUIDX               ((KW_MAX_DL_LI/4)*KW_MAX_ACTV_DRB)
/* Number of out standing SDUS in one RbCb : This would be sufficient but anything more will be discarded for counters */
#define KW_L2MEAS_MAX_OUTSTNGSDU       31
#endif


#endif /* __KWENVH__ */
  
/********************************************************************30**
  
         End of file:     kw_env_t2k.h@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:43:24 2014
  
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
*********************************************************************91*/
