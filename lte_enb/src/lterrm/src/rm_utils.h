
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_utils.h

     Sid:      rm_utils.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:42 2013

     Prg:      vkorade

*********************************************************************21*/

/** @file rm_utils.h
 *  @brief This file contains utilities required for RRM
 */

#ifndef RM_UTILS_H_
#define RM_UTILS_H_
#include "rm_cmn.h"

#define RM_LEAST_QCI_PRIORITY   255        /*!< Least QCI Priority */
#define RM_ABS_VAL(_x,_y) ((_x > _y)?((_x) - (_y)):((_y) - (_x)))

/*!< It contains all possible QCI Priority Values */

typedef enum rmQciPriority
{
   RM_QCI_PRIORITY_VAL1 = 1,  /*!< QCI Priority 1 */
   RM_QCI_PRIORITY_VAL2,      /*!< QCI Priority 2 */
   RM_QCI_PRIORITY_VAL3,      /*!< QCI Priority 3 */
   RM_QCI_PRIORITY_VAL4,      /*!< QCI Priority 4 */
   RM_QCI_PRIORITY_VAL5,      /*!< QCI Priority 5 */
   RM_QCI_PRIORITY_VAL6,      /*!< QCI Priority 6*/
   RM_QCI_PRIORITY_VAL7,      /*!< QCI Priority 7*/
   RM_QCI_PRIORITY_VAL8,      /*!< QCI Priority 8*/
   RM_QCI_PRIORITY_VAL9,      /*!< QCI Priority 9*/ 
   RM_QCI_MAX_VALUE           /*!< Maximum QCI Priority Value*/
} RmQciPriority;

U8	getQciPriority(U8 bQci);

/* Number of DL subframes and Special subframes with DwPTS */
typedef U8 RmTddNumDlSubfrmTbl[LRM_UL_DL_CONFIG_MAX][RM_NUM_SF_PER_SFN];
EXTERN RmTddNumDlSubfrmTbl rmTddNumDlSubfrmTbl;

/* Number of UL subframes */
typedef U8 RmTddNumUlSubfrmTbl[LRM_UL_DL_CONFIG_MAX][RM_NUM_SF_PER_SFN];
EXTERN RmTddNumUlSubfrmTbl rmTddNumUlSubfrmTbl;

/**
 * @brief Function to get the total number of UL and DL subframes based on QCI
 *        timing requirement and configuration mode
 *
 * @details Function to get the total number of UL and DL subframes based on QCI
 *          timing requirement and configuration mode
 *
 * @param[in] cfgMode COnfiguration modes from 0 to 6
 * @param[in] timingReqInMs Timing requirements in milliseconds
 * @param[in/out] totalNumDlSf total number of DL subframes
 * @param[in/out] totalNumUlSf total number of UL subframes
 *
 * @return void
 */
void getTotalNumberOfDlUlSubframes(LrmUlDlConfig cfgMode, 
                                   U32 timingReqInMs,
                                   U32 *totalNumDlSf,
                                   U32 *totalNumUlSf);

/**
 * @brief The function to get number of Prbs
 *
 * @details The function to get number of Prbs
 *
 * @param[in] enDlBw holds the DL bandwidth
 *
 * @return U32
           returns the number of PRB's            
 */
U8 getNumPrbs(LrmCellBandwidth enDlBw);

/**
 * @brief function to get number of DL subframes per frame
 *
 * @details function to get number of DL subframes per frame
 *
 * @param[in] bCfgMode holds the configuration mode between 0 to 6
 *
 * @return U32
 *         returns the number of DL subrames in a given frame based on the
 *         configuration mode
 */
U32 getNumDlSubFramesPerFrame(U32 bCfgMode);

/**
 * @brief function to get number of UL subframes per frame
 *
 * @details function to get number of UL subframes per frame
 *
 * @param[in] bCfgMode holds the configuration mode
 *
 * @return U32
 *         returns the number of UL subframes in a given frame based on the
 *         configuration mode
 */
U32 getNumUlSubFramesPerFrame(U32 bCfgMode);

/**
 * @brief Function to fetch ERAB info corresponding to the ERAB id.
 *
 * @detail Function to fetch the ERAB add info from list of incoming ERABs 
 *         for the particular ERAB ID.
 *
 * @param[in]     stErab   List of incoming ERABs
 * @param[in]     bErabId  ERAB Identity
 *
 * @return  RmuUErabAddModIe *
 *          Returns address to ERAB add IE from list of incoming ERABs 
 *          for the corresponding ERAB ID
 */
RmuUErabAddModIe *getRbAddModIe(RmuErabConfigIe & stERAB, U8 bErabId);

/*!< True: if it is a GBR bearer; else False */
bool isGbrBearer(U32 qci);

/*!< True: if it is a valid QCI; else False */
bool isValidQci(U32 qci);

#endif /* RM_UTILS_H_ */
/********************************************************************30**

           End of file:     rm_utils.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:42 2013

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
