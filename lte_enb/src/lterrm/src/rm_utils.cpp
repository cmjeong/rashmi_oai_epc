
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP source file

     Desc:     This file contains 
               

     File:     rm_utils.cpp

     Sid:      qf_utils.cpp@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:37 2013

     Prg:     hkrishna 

*********************************************************************21*/
static const char* RLOG_MODULE_NAME="RRM";
static int RLOG_MODULE_ID=128;
static int RLOG_FILE_ID=160;

/* header include files */
#include "rm_cmn.h"
#include "rm_utils.h"

U8 g_bQciToPriorityMap[RM_QCI_MAX_VALUE] =
{
	RM_QCI_PRIORITY_VAL2,
	RM_QCI_PRIORITY_VAL4,
	RM_QCI_PRIORITY_VAL3,
	RM_QCI_PRIORITY_VAL5,
	RM_QCI_PRIORITY_VAL1,
	RM_QCI_PRIORITY_VAL6,
	RM_QCI_PRIORITY_VAL7,
	RM_QCI_PRIORITY_VAL8,
	RM_QCI_PRIORITY_VAL9
};

U8	getQciPriority(U8 bQci)
{
	return  ((bQci > RM_QCI_MAX_VALUE) || (bQci == 0)) ? RM_LEAST_QCI_PRIORITY : (g_bQciToPriorityMap[bQci-1]);
}

/* Number of DL subframes present till a particular subframe 
 * rows are different config Mode , and columns are till now how many total 
 * Dl+SL subframes are available 
 **/
PUBLIC RmTddNumDlSubfrmTbl rmTddNumDlSubfrmTbl = {
        {1, 2, 2, 2, 2, 3, 4, 4, 4, 4},
        {1, 2, 2, 2, 3, 4, 5, 5, 5, 6},
        {1, 2, 2, 3, 4, 5, 6, 6, 7, 8},
        {1, 2, 2, 2, 2, 3, 4, 5, 6, 7},
        {1, 2, 2, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 2, 2, 2, 3, 4, 4, 4, 5}
};

/* Number of UL subframes present before a particular subframe 
 * rows are different config Mode , and columns are till now how many total 
 * UL subframes  
 */
PUBLIC RmTddNumUlSubfrmTbl rmTddNumUlSubfrmTbl = {
        {0, 0, 1, 2, 3, 3, 3, 4, 5, 6},
        {0, 0, 1, 2, 2, 2, 2, 3, 4, 4},
        {0, 0, 1, 1, 1, 1, 1, 2, 2, 2},
        {0, 0, 1, 2, 3, 3, 3, 3, 3, 3},
        {0, 0, 1, 2, 2, 2, 2, 2, 2, 2},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 2, 3, 3, 3, 4, 5, 5}
};

void getTotalNumberOfDlUlSubframes(LrmUlDlConfig cfgMode, 
                                   U32 timingReqInMs,
                                   U32 *totalNumDlSf,
                                   U32 *totalNumUlSf)
{
   /* stores the Dl plus special subframes per frame based on cfg mode*/
   U8  numOfDlPlusSpecialSfsPerFrame = rmTddNumDlSubfrmTbl[cfgMode][RM_NUM_SF_PER_SFN-1];
   /* stores number of Ul subframes per frame based on cfg mode*/
   U8  numOfUlSfsPerFrame = rmTddNumUlSubfrmTbl[cfgMode][RM_NUM_SF_PER_SFN-1];
   U8  numOfSubFramesLessThanFrame;
   
   /* stores the number of DL plus special sub-frames per frame based on timing
    * requirement*/
   *totalNumDlSf = numOfDlPlusSpecialSfsPerFrame * (timingReqInMs/RM_NUM_SF_PER_SFN);
   
   /* stores the number of UL sub-frames per frame based on timing
          * requirement*/
   *totalNumUlSf = numOfUlSfsPerFrame * (timingReqInMs/RM_NUM_SF_PER_SFN);
   
   /* number of subframes less than a frame <10 ms */
   numOfSubFramesLessThanFrame = timingReqInMs % RM_NUM_SF_PER_SFN;

   /* update total DL and UL subframes with number of sub frames < a frame */
   if(numOfSubFramesLessThanFrame != 0)
   {
      (*totalNumDlSf) += rmTddNumDlSubfrmTbl[cfgMode][numOfSubFramesLessThanFrame];    
      (*totalNumUlSf) += rmTddNumUlSubfrmTbl[cfgMode][numOfSubFramesLessThanFrame];    
   }
   return;
}

bool isGbrBearer(U32 bQci)
{
   return (bQci >= RM_RBC_GBR_MIN_QCI && bQci <= RM_RBC_GBR_MAX_QCI);
}

bool isValidQci(U32 bQci)
{
   return (bQci >= RM_RBC_GBR_MIN_QCI && bQci <= RM_RBC_MAX_QCI);
}

U32 getNumDlSubFramesPerFrame(U32 bCfgMode)
{
   return (rmTddNumDlSubfrmTbl[bCfgMode][RM_NUM_SF_PER_SFN-1]);
}

U32 getNumUlSubFramesPerFrame(U32 bCfgMode)
{
   return (rmTddNumUlSubfrmTbl[bCfgMode][RM_NUM_SF_PER_SFN-1]);
}

U8 getNumPrbs(LrmCellBandwidth enDlBw)
{
   U8 bNumRbs;

   switch(enDlBw)
   {
      case LRM_BANDWIDTH_25:
      {
         bNumRbs = 25;
      }
      break;

      case LRM_BANDWIDTH_50:
      {
         bNumRbs = 50;
      }
      break;

      case LRM_BANDWIDTH_75:
      {   
         bNumRbs = 75;
      }
      break; 

      case LRM_BANDWIDTH_100:
      {   
         bNumRbs = 100;
      }
      break;

      default:
      {
         RLOG1 (L_ERROR, "Invalid Bandwidth Configuration [%d]. "
               "Assuming MAX PRBS as 100", enDlBw);
         bNumRbs = 100;
         break;
      }
   }
   return bNumRbs;
}

RmuUErabAddModIe *getRbAddModIe(RmuErabConfigIe & stERAB, U8 bErabId)
{
   U32   uiRbIdx;
   for(uiRbIdx = 0; uiRbIdx < stERAB.usNoErabsToAddMod; uiRbIdx++)
   {
      if(stERAB.stErabAddModLst[uiRbIdx].bErabId == bErabId)
      {
         RETVALUE(&stERAB.stErabAddModLst[uiRbIdx]);
      }
   }
   RETVALUE(NULLP);
}


/********************************************************************30**

           End of file:     qf_utils.cpp@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:37 2013

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
*********************************************************************91*/
