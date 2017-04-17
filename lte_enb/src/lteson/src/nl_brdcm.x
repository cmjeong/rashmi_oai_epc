/********************************************************************20**

     Name:     LTE SON Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     nl.x

     Sid:      nl_brdcm.x@@/main/tenb_main_ccb/1 - Thu Jan 21 17:51:23 2016

     Prg:      subhamay 

*********************************************************************21*/
/** @file nl_brdcm.x
 *  @brief This file contains the data structures used for the integration
 *         of BRDCM SON algorithms
 **/
#ifndef NL_BRDCMX_
#define NL_BRDCMX_

typedef enum nlBrdcmSonTimer
{
   NL_UE_CQI_RPT_IND_TIMER = 0,
   NL_UE_MEAS_RPT_IND_TIMER,
}NlBrdcmSonTimer;

/**
 * @details
   This structure contains UE related information stored in SON. 
   BIT MAP received from BRDCM-SON for 16 UE will be mapped to each entry.
   This structure also is the data node for crntiUeInfoMapLst hash table.
   */
typedef struct nlUeInfo
{
   CmHashListEnt   ueInfoEnt;        /*!< hash Node entry information*/
   U16             crnti;            /*!< UE identity, Invalid CRNTI value 
                                         indicates UE is not attached with eNB*/
   NluEcgi         ecgi;             /*!< ECGI*/     
   U32             noNghCell;        /*!< number of neighbor cell reported by UE*/
   NluNghCellMeasRpt nghCellMeasRpt[NLU_MAX_NGH_CELL_INFO]; /*!< neighbor cells measurement report*/
   S16             strongNghCellRsrp;  /*!< strongest neighbor cell RSRP*/ 
   S16             servCellRsrp;     /*!< serv cell RSRP*/
   S8              servCellRsrq;     /*!< serv cell RSRQ*/
   U8              avgWideBandCqi;   /*!< average wideband CQI reports*/
   U8              subbandCount;  /*!< count for sub bands*/
   U8              avgSubbandCqi[SONAPI_MAX_SUB_BAND_CQI_CNT];  /*!< average subband CQI reports*/
   Bool            isNewUe;          /*!< True when the UE is added, made false on 
                                          sending the first report to BRDCM ICIC */
}NlUeInfo;

/**
 * @struct NlBrdcmSonDB
   This structure contains the BRDCM-SON configuration information as well as 
   UE data base */

typedef struct nlBrdcmSonDB
{
   NlUeInfo                    brdcmUeDB[SONAPI_MAX_UE_CNT]; /*!< max 16 UE information 
                               will be stored in SON, each entry will be used as hash Node.
                               BITMAP from BRDCM-SON for 16 UEs will be mapped to corresponding 
                               index*/
   CmHashListCp                crntiUeInfoMap;  /*!< hash list for UE attached with eNB*/
   U8                          cqiAvgCoeff[2];   /*!< CQI averaging coefficients exponent. 
                                 Not UE specific. Index 0 for wide-band CQI and index 1 for sub-band CQI */
   SONAPI_CQI_AVERAGE_TYPE_T   cqiAvgType;   /*!< Indicate how RSYS-SON will calculate
                               the avegare CQI value*/
   U32                         ueMeasRptCount;  /*!<0..65535. the count of periodical UE measurement report 
                                requested from BRDCM-SON, 0 means infinite*/
   U32                         ueMeasRptSent;   /*!< store the number of UE measurement report 
                                sent to broadcomm SON*/
   U32                         paLevelPerPrb[110];
   U32                         pa;
   U32                         paHigh;
   U32                         paLow;
   U32                         remScanInterval; /*!< 0..65535. in seconds, around 1s to 18 hours.
                                                 0 means no more REM scan is needed */
   U32                         remScanCount;   /*!< 0..65535. the count of REM scan requested,
                                                    0 means infinite */
#if 0
   U16      selfPci;
   U8       numNeighbors; /*!< only own operator neighbors are counted */
#endif
}NlBrdcmSonDB;

EXTERN NlBrdcmSonDB   brdcmSonDB;

/**
 * @struct NlBrdcmSonTimers
   This structure contains the timers required for BRDCM-SON
 */

typedef struct nlBrdcmSonTimers 
{
   CmTimer                     ueCqiRptIndTimer;   /*!< timer for sending UE report indication to BRDCM-SON.
                               Once this timer expired RSYS-SON will send the average 
                               CQI reports to BRDCM-SON*/
   U16                         ueCqiRptIndInterval;   /*!< timer configuration for how
                                 frequently RSYS SON sends CQI report to BRDCM-SON in second*/

   CmTimer                     ueMeasRptIndTimer;   /*!< timer for sending UE report indication to BRDCM-SON.
                               Once this timer expired RSYS-SON will send the average 
                               measurement reports to BRDCM-SON*/
   U16                         ueMeasRptIndInterval;   /*!< timer configuration for how
                                 frequently RSYS SON sends measurement report to BRDCM-SON in second*/

}NlBrdcmSonTimers;

EXTERN NlBrdcmSonTimers  brdcmSonTimers;
#if 0

/**
 * @struct NlBrdcmCfg
   This structure contains informaton about the scheduler configuratons from BRDCM-SON.*/

typedef struct nlBrdcmSchdCfg
{
   NlBrdcmUeInfo                ueCfg[SONAPI_MAX_UE_CNT];          /*!< MAX 16 UE related Cfg from BRDCM SON*/
   LnlSonPrbPaLevelCfg          paLevelPerPrb[SONAPI_MAX_PRB_CNT]; /*!< PA level for each PRB*/
   LnlSonPaCfg                  pa;                                /*!< Pa value used to calculate PDSCH power for reuse 1 region*/
   LnlSonPaCfg                  paLow;                             /*!< Pa value used to calculate PDSCH power for low power in the FFR region*/
   LnlSonPaCfg                  paHigh;                            /*!< Pa value used to calculate PDSCH power for high power in the FFR region*/
   U8                           pb;                                /*!< PDSCH Pb values*/
}NlBrdcmSchdCfg;

/**
 * @struct nlBrdcmCb
   This structure contains informaton about the configuratons received 
   from BRDCM-SON.*/
typedef struct nlBrdcmCb
{
   //NlBrdcmSchdCfg              schdCfg;   /*!< configuration related to scheduler*/
   U16                         measRptTimerCfg;   /*!< timer configuration for how
                                 frequently RSYS SON sends measuremnt report as well 
                                 as CQI report to BRDCM-SON */
   U8                          wideBandCqiCoeff[13];
   U8                          subBandCqiCoeff[13]; 
   SONAPI_CQI_AVERAGE_TYPE_T   cqiAvgType;   /*!< Indicate how RSYS-SON will calculate
                               the avegare CQI value*/
   NlBrdcmSonDB                brdcmSonDB;
}NlBrdcmCb;
#endif

EXTERN Bool nlIsUePresentInDB   ARGS((
U16       crnti,
NlUeInfo  **ueInfo
));

EXTERN S16 nlModifyUeInfoInDB   ARGS((
NlUeInfo    *dbUeInfo,
NluUeInfo   *ueInfo
));

EXTERN Void nlDeleteUeFromDB   ARGS((
U16       crnti
));

EXTERN S16 nlGetFreeDBIdx   ARGS((
U32       *freeIdx
));

EXTERN S16 nlInsertUeIntoDB   ARGS((
U16       crnti,
NluEcgi   ecgi
));

EXTERN Void nlInitUeInfo   ARGS((
NlUeInfo  *ueInfo
));

EXTERN Void nlInitUeInfo   ARGS((
NlUeInfo  *ueInfo
));

EXTERN S16 NlMiLnlBrdcmSonCfgInd   ARGS((
Pst         *pst,     /*!< post structure */
LnlSonCfg   *sonCfg   /*!< BRDCM-SON config structure */
));

EXTERN S16 nlVendorDSonIMCfgCfm   ARGS((
Void    *imCfgCfm
));

EXTERN S16 nlHandleUeCqiRptIndTmrExpiry   ARGS((
PTR   timerCb
));

EXTERN S16 nlHandleUeMeasRptIndTmrExpiry   ARGS((
PTR   timerCb
));

EXTERN S16 ReportNumNghToBrdcmSon   ARGS((
U16   numNgh
));

EXTERN Void nlCalcAndUpdateAvgWidebandCqi   ARGS((
NluUeCqiRpt   *cqiRptMsg,
NlUeInfo      *dbUeInfo
));

EXTERN Void nlCalcAndUpdateAvgSubbandCqi   ARGS((
NluUeCqiRpt   *cqiRptMsg,
NlUeInfo      *dbUeInfo
));

EXTERN S16 nlVendorDSonUeRptInd ARGS((
Void    *ueRpt
));

EXTERN S16 nlVendorDSonAnrInfoInd   ARGS((
Void    *anrInfo
));

EXTERN S16 nlVendorDSonRptCfgCfm   ARGS((
Void   *rptCfm
));

EXTERN S16 nlVendorDSonStopReq   ARGS((
Void    *stopReq
));

#endif /* NL_BRDCM_X_ */
/********************************************************************30**

           End of file:     nl_brdcm.x@@/main/tenb_main_ccb/1 - Thu Jan 21 17:51:23 2016

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

