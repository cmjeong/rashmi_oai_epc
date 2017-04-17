


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for the functions needed by CM XTA to execute 
               layer specific code. 
  
     File:     rgac_flag.c 
  
     Sid:      rgac_flag.c@@/main/3 - Sat Jul 30 02:20:55 2011
  
     Prg:     sm 
  
**********************************************************************/

/** @file rgac_flag.c.
@brief It has contains the array of flags and functions needed by CM XTA 
to handle compile time flags within test cases. 
*/

#include "rgac_acc.x"

Bool cmXtaFlag[CMXTA_MAX_FLAGS] = 
{
   FALSE,
   TRUE,
#ifdef TFU_TDD
   TRUE,
#else
   FALSE,
#endif
#ifdef RG_PHASE2_SCHED
   TRUE,
#else
   FALSE,
#endif
/* Changes for MIMO feature addition */
#ifdef LTEMAC_MIMO
   TRUE,
#else
   FALSE,
#endif
   /* Modified for SI Enhancement*/
#ifdef RGR_SI_SCH
   TRUE,
#else
   FALSE,
#endif
#ifdef TFU_UPGRADE
   TRUE,
#else
   FALSE,
#endif
   /* Added support for SPS*/
#ifdef LTEMAC_SPS
   TRUE,
#else
   FALSE,
#endif
#ifdef LTE_L2_MEAS
   TRUE,
#else
   FALSE,
#endif
#ifdef LTEMAC_HDFDD
   TRUE,
#else
   FALSE,
#endif
/* ADD Changes for Downlink UE Timing Optimization */
#ifdef LTEMAC_DLUE_TMGOPTMZ
   TRUE,
#else
   FALSE,
#endif
#ifdef LTEMAC_RGU_PAD
   TRUE,
#else
   FALSE,
#endif
#if ERRCLS_ADD_RES 
   TRUE,
#else
   FALSE,
#endif
#if ERRCLASS 
   TRUE,
#else
   FALSE,
#endif
#ifdef RGR_CQI_REPT
   TRUE,
#else
   FALSE,
#endif
#ifdef LTEMAC_DRX
   TRUE,
#else
   FALSE,
#endif
#ifdef LTEMAC_R9
   TRUE,
#else
   FALSE,
#endif
#ifdef DEBUGP 
   TRUE,
#else
   FALSE,
#endif
#ifdef RGR_V1 
   TRUE,
#else
   FALSE,
#endif
/* Changes for UL Scheduling at CRC Indication */
#ifdef RG_ULSCHED_AT_CRC
   TRUE,
#else
   FALSE,
#endif
#ifdef RGR_V2 
   TRUE,
#else
   FALSE,
#endif
#ifdef RG_PFS_STATS
   TRUE,
#else
   FALSE,
#endif
};

Txt  cmXtaFlagStr[CMXTA_MAX_FLAGS][50] =
{
   "Unknown Ifdef",
   "Unknown Ifndef",
   "TFU_TDD",
   "RG_PHASE2_SCHED",
   "LTEMAC_MIMO",
   "RGR_SI_SCH",
   "TFU_UPGRADE",
   "LTEMAC_SPS",
   "LTE_L2_MEAS",
   "LTEMAC_HDFDD",
   "LTEMAC_DLUE_TMGOPTMZ",
   "LTEMAC_RGU_PAD",
   "ERRCLS_ADD_RES",
   "ERRCLASS",
   "RGR_CQI_REPT",
   "LTEMAC_DRX",
   "LTEMAC_R9",
   "DEBUGP",
   "RGR_V1",
   "RG_ULSCHED_AT_CRC",
   "RGR_V2",
};
 


/**********************************************************************
 
         End of file:     rgac_flag.c@@/main/3 - Sat Jul 30 02:20:55 2011
 
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
/main/1      ---     sm   1. Initial Release.
*********************************************************************91*/



/**********************************************************************
 
         End of file:     rgac_flag.c@@/main/3 - Sat Jul 30 02:20:55 2011
 
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
/main/1      ---     sm   1. Initial Release.
/main/2      ---       apany 1. LTE MAC 2.1 release
             rg004.201 rnt 1. Modified for SI Enhancement
           rg007.201   ap  1. Added support for MIMO
           rg008.201 rsharon 1. Added support for SPS.
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
           rg002.301 dvasisht 1. Changes for ticket ccpu00118352
/main/4    rg003.301 ap       1. Added flag for test case execution.
$SID$       ---       rt      1. LTE MAC 4.1 release
*********************************************************************91*/
