

/********************************************************************20**
  
        Name:    Common LTE
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures for Common LTE
 
        File:    cm_lte.x

        Sid:      cm_lte.x@@/main/2 - Fri Nov 13 14:09:17 2009
  
        Prg:     chakrapani
  
*********************************************************************21*/

#ifndef __CM_LTE_X__
#define __CM_LTE_X__

/* Packing Defines */
#define cmPkLteRbId              SPkU8
#define cmPkLteRnti              SPkU16
#define cmPkLteCellId            SPkU16
#define cmPkLteRlcMode           SPkU8
#define cmPkLteLcId              SPkU8
#define cmPkLteLcType            SPkU8
#define cmPkLteAggrLvl           SPkU32

/* Unpacking Defines */
#define cmUnpkLteRbId            SUnpkU8
#define cmUnpkLteRnti            SUnpkU16
#define cmUnpkLteCellId          SUnpkU16
#define cmUnpkLteRlcMode         SUnpkU8
#define cmUnpkLteLcId            SUnpkU8
#define cmUnpkLteLcType          SUnpkU8
#define cmUnpkLteAggrLvl         SUnpkU32

#ifdef PACK_STRUCT
#define CM_PACK_STRUCT __attribute__((packed))
#else
#define CM_PACK_STRUCT
#endif




#ifdef __cplusplus
EXTERN "C" {
#endif  /*__cplusplus*/

/** @file cm_lte.x
    @brief CM_LTE Interface File (cm_lte.x)
*/
 
/* definitions for Common LTE */

/** @brief Radio Bearer ID */
typedef U8    CmLteRbId;

/** @brief Cell ID */
typedef U16   CmLteCellId;

/** @brief RNTI */
typedef U16   CmLteRnti;

/** @brief Mode Type TM/UM/AM */
typedef U8    CmLteRlcMode;

/** @brief Logical Channel ID */
typedef U8    CmLteLcId;         

/** @brief Logical Channel Type */
typedef U8    CmLteLcType;         

/** @brief Transport Channel Type */
typedef U8    CmLteTrchType;         

/** @brief Contention Resolution ID */
typedef U8 CmLteContResId[6];

/** @brief RLC ID */
typedef struct cmLteRlcId
{
  CmLteRbId     rbId;   /*!< Radio Bearer ID */
  U8            rbType; /*!< RB Type */
  CmLteRnti     ueId;   /*!< UE ID */
  CmLteCellId   cellId; /*!< Cell ID */
}CmLteRlcId;

/** @brief LTE Timing Info */
typedef struct cmLteTimingInfo
{
   U16 sfn;                  /*!< System Frame Number */
   U8  subframe;             /*!< Subframe number */
} CmLteTimingInfo;

/** @brief PDCP ID */
typedef struct cmLtePdcpId
{
   CmLteCellId   cellId;      /*!< Cell ID */
   CmLteRnti     ueId;        /*!< UE ID */
   CmLteRbId     rbId;        /*!< PDCP Instance ID */
   U8            rbType;      /*!< RB type */
} CmLtePdcpId;

/** @brief Counter Statistics */
typedef U32  CntrSts;

/** @brief Aggregation Level */
typedef enum cmLteAggrLvl
{
   CM_LTE_AGGR_LVL1 = 1,  /*!< Aggregation level 1 */
   CM_LTE_AGGR_LVL2 = 2,  /*!< Aggregation level 2 */
   CM_LTE_AGGR_LVL4 = 3,  /*!< Aggregation level 3 */
   CM_LTE_AGGR_LVL8 = 4   /*!< Aggregation level 4 */
} CmLteAggrLvl;

/** @brief UE Category */
typedef enum cmLteUeCategory
{
   CM_LTE_UE_CAT_1 = 1,
   CM_LTE_UE_CAT_2,
   CM_LTE_UE_CAT_3,
   CM_LTE_UE_CAT_4,
   CM_LTE_UE_CAT_5,
   CM_LTE_UE_CAT_6,
   CM_LTE_UE_CAT_7, /* RRC-REL10-Upgrade */
   CM_LTE_UE_CAT_8
} CmLteUeCategory;

/****************************************************************************
 *                         PACK/UNPACK Functions
 ***************************************************************************/
/* Packing Functions */
EXTERN S16 cmPkLteRlcId ARGS ((
CmLteRlcId *param,
Buffer *mBuf
));

EXTERN S16 cmPkLteTimingInfo ARGS ((
CmLteTimingInfo *param,
Buffer *mBuf
));

EXTERN S16 cmPkLtePdcpId ARGS ((
CmLtePdcpId *param,
Buffer *mBuf
));

/* Unpack Function */
EXTERN S16 cmUnpkLteRlcId ARGS ((
CmLteRlcId *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkLteTimingInfo ARGS ((
CmLteTimingInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkLtePdcpId ARGS ((
CmLtePdcpId *param,
Buffer *mBuf
));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CM_LTE_X__ */

/********************************************************************30**
  
         End of file:     cm_lte.x@@/main/2 - Fri Nov 13 14:09:17 2009
  
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
----------- -------- ---- -----------------------------------------------
/main/1      ---      cp   1. initial release.
*********************************************************************91*/
