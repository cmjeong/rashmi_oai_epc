
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP include file

     Desc:     This file contains 
               
     File:     rm_uecontext.h

     Sid:      rm_uecontext.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:45:37 2013

     Prg:      hkrishna 

*********************************************************************21*/
#ifndef _RRM_UECONTEXT_H_
#define _RRM_UECONTEXT_H_
#include <sys/time.h>
#include <list>
#include "rm_cmn.h"
#include "cm_lte_rrm.x"

   /* This Macro is used to reach the LONG DRX Bit in the
    * UE Feature Group Indicator. LONG DRX Bit is 5th Most 
    * significant Bit of Feature Group Indicator */   
#define RM_RCM_LONG_DRX_BIT_SET           (1 << 27)
#define RM_RCM_SHORT_DRX_BIT_SET          (1 << 28)

#define RM_RCM_SPS_REL9_BIT_SET           (1 << 3)
#define RM_RCM_SPS_REL8_BIT_SET           (1 << 29)
#define RM_RCM_UM_MODE_BIT_SET            (1 << 25)

class CRmCellController;
typedef struct timeval  RmTimeVal;

/*!< Contains causes because of which the ERAB was preempted */
enum RmPremptionCause
{
   RM_NOT_PREEMPTED = 1,     /*!< ERAB is not preempted */
   RM_PREEMPTION_CAUSE_QCI,  /*!< Prempted due to QCI */
   RM_PREEMPTION_CAUSE_PRB,   /*!< Prempted due to PRB */
   RM_PREEMPTION_CAUSE_PRB_CONG   /*!< Prempted due to PRB Congestion*/
};

/** @brief This structure contains the parameters of the UE, defining the status
 *         of the UE for running the algorithm
 -  U8   bDopEst;      This holds the doppler Estimation received from the PHY
 -  U8   bGbrLvl;      This indicates the GBR level of the UE's total GBR
 -  U8   bQciLvl;      This indicates the QCI level of the UE's highest QCI
 -  U8   bPrdctyLvl;   This indicates the Periodicity level of the CQI
                      Periodicity configured
 -  U8   bCqiLvl;      This indicates the CQI Level of the, Wideband CQI
                      value received by UE or the CQI level of the
                      difference between the Wide Band CQI value and
                      the max value of CQI of a Subband
 -  U8   bWCqi;        This holds the Wide Band CQI received from the UE
 -  U8   bSbCqiMax;    This contains max of the CQI value among all subband
                      cqi values
 -  U8   bDiffWbSbCqi; This holds the difference between the Wide Band CQI
                      value and the max value of CQI of a Subband
 -  U8   bUeSpdLvl;    This indicates the speed level of the UE for the
                      doppler shift received
 -  U32  uiTotalGbr;     This Indicates the Total GBR (Summation of GBR's
                      of all GBR bearer's) of the UE
 **/
typedef struct rmRcmUeStats
{
   U32                        uiTotalGbr;
   U8                         bDopEst;
   U8                         bWCqi;
   U8                         bSbCqiMax;
   U8                         bDiffWbSbCqi;
   U8                         bTxnMode;
   U8                         bUeSpdLvl;
   U8                         bGbrLvl;
   U8                         bQciLvl;
   U8                         bPrdctyLvl;
   U8                         bCqiLvl;
} RmRcmUeStats;

typedef struct rmRcmScellInfo
{
   U8                sCellIdx;
   RmuUeSCellDedInfo sCellDedInfo;
}RmRcmScellInfo;

typedef RmuUErabAddModIe RmERabInfo;

class CERABInfo
{
 public:
    U8 getERABId() { return (m_stERAB.bErabId); };
    U8 getQci() { return (m_stERAB.stErabQosInfo.bErabQCI); };
    U8 getArp() { return (m_stERAB.stErabQosInfo.stErabArpInfo.bErabPrioLvl); };
    U32 getUlGBR() { return (m_stERAB.stErabQosInfo.stErabGbrInfo.uiErabUlGbr); };
    U32 getDlGBR() { return (m_stERAB.stErabQosInfo.stErabGbrInfo.uiErabDlGbr); };
    U32 getDlGBRPrb() { return (m_uiDlPrbRequired); };
    U32 getUlGBRPrb() { return (m_uiUlPrbRequired); };
    void updateReqDlPrb(U32 reqDlPrb) { m_uiDlPrbRequired = reqDlPrb; };
    void updateReqUlPrb(U32 reqUlPrb) { m_uiUlPrbRequired = reqUlPrb; };
    void setIsPrempted(bool isPreempted) { m_bIsPreEmpted = isPreempted; };
    bool getIsPrempted() { return m_bIsPreEmpted; };
    bool isNonPreEmptableRab() { return (m_stERAB.stErabQosInfo.stErabArpInfo.bErabPreemptVul == 0) ;};
    U8 getQciPriority();
    void modifyERAB(RmERabInfo & stERAB);
    void setPremptedCause(RmPremptionCause cause) { m_PreemptCause = cause; };
    RmPremptionCause getPremptedCause() { return m_PreemptCause; };

   /**
    * @brief Function to find a ERAB is pre-emptable or not.
    * 
    * @details Function to find the ERAB is pre-emptable or not.
    *      
    * @return bool
    *         Returns true if the ERAB is pre-emptable ERAB; 
    *         else returns false
    */
   bool isPreEmptableRab() { return ((m_stERAB.stErabQosInfo.stErabArpInfo.bErabPreemptVul) &&
         (m_stERAB.stErabQosInfo.stErabArpInfo.bErabPrioLvl != 15)); };
  
   /**
    * @brief Function to find the ERAB is pre-emption capable or not.
    * 
    * @details Function to find the ERAB is pre-emption capable or not. 
    *      
    * @return bool 
    *         Returns true in case of ERAB is pre-emption capable;
    *         else retruns false
    */
   bool isPreEmptionCapableRab() { return ((m_stERAB.stErabQosInfo.stErabArpInfo.bErabPreemptCap) &&
         (m_stERAB.stErabQosInfo.stErabArpInfo.bErabPrioLvl != MAX_ARP_VAL)); };
   
   /**
    * @brief Function to update the CRNTI of the UE in ERAB.
    * 
    * @details Function to update the CRNTI of the UE in the ERAB.
    *      
    * @param[in] usCRNTI CRNTI of the UE for which this ERAB belongs to.
    *
    * @return void 
    */
   void setRabCrnti(U16 usCRNTI) { m_usCRNTI = usCRNTI;};
   
   /**
    * @brief Function to set the flag in ERAB object.
    * 
    * @details Function to set the flag as  ERAB pre-emption is in progress.
    *          This is to identify that the ERAB is already pre-empted, not to
    *          pre-empt again.
    *      
    * @param[in] bIsPreEmpted  TRUE for if ERAB is pre-emption is in progress. 
    * @return void 
    */
   void setPreEmptionIsInProgress(bool bIsPreEmpted) { m_bIsPreEmpted = bIsPreEmpted;};
   
   /**
    * @brief Function to identify the ERAB pre-epmtion is in progress.
    * 
    * @details Function to identify the ERAB pre-emption is in progress.
    *          This is to identify that the ERAB is already pre-empted, not to
    *          pre-empt again.
    * 
    * @return bool
    *         Returns true in case of the ERAB pre-eption is in progress.
    *         else returns false.
    */
   bool isPreEmptionIsInProgress() { return m_bIsPreEmpted;};

   /**
    * @brief Function to get the CRNTI of the ERAB, for which UE this ERAB belongs
    *        to.
    * 
    * @details Function to get the CRNTI of the UE ERAB.
    *      
    * @return U16
    *         Returns of the CRNTI of the UE's ERAB.
    */
   U16 getRabCrnti() { return m_usCRNTI;};

   /**
    * @brief Function to update the requested ERAB information and CRNTI of the
    *        UE into the ERAB object.
    * 
    * @details Function to update the ERABs object with the ERABs inforation and
    *        CRNTI of the UE.
    *      
    * @param[in] stERAB  Reference to the ERAB inforamtion. 
    * @param[in] usCRNTI CRNTI of the UE's ERAB.       
    * @return void 
    */
   void updateERABInfo(RmERabInfo &stERAB, U16 usCRNTI);

 private:
   /*!< ERAB information like QoS, ERAB ID */
   RmERabInfo   m_stERAB;
   
   /*!< CRNTI of the UE's ERAB */
   U16          m_usCRNTI;

   /*!< Is this ERAB pre-emption is in progress or not */
   bool         m_bIsPreEmpted;

   /*!< Cause for preemption (either for QCI or PRB reasons) */
   RmPremptionCause m_PreemptCause;

   /*!< Number of DL PRBs required */
   U32          m_uiDlPrbRequired;

   /*!< Number of UL PRBs required */
   U32          m_uiUlPrbRequired;
};

/*!< ERAB info list  */
typedef std::list<CERABInfo*> CERABInfoLst;

/*!< Radio Bearer controller class farward declaration */
class CRBearerController;

class CUEContext
{
public:
   CUEContext();
   
   /**
    * @brief Function to add new ERAB into the UE's ERAB list.
    * 
    * @details Function to add the new ERAB into the UE's ERAB list. 
    *      
    * @param[in] pObjErab  Pointer to the ERAB object which need to be add to
    *                      this UE's ERAB list. 
    * @return void 
    */
   void addERAB(CERABInfo *pObjERab);
 
   /**
    * @brief Function to remove the ERAB form UE's RAB list. 
    * 
    * @details Function to remove the ERAB from UE's RAB list.
    *      
    * @param[in] pObjERab Pointer to the ERAB object which need to be removed.
    * @return void 
    */
   void releaseERAB(CERABInfo *pObjERab);
   
   /**
    * @brief Function to remove the first ERAB in the UE's ERAB List.
    * 
    * @details Function to remove the first ERAB in the UEs ERAB list. 
    *      
    * @return CERABInfo*
    *         Returns pointer to object of ERAB which is removed from ERAB list
    *         of the UE. Retunrs NULL in case of RAB list is empty.
    */
   CERABInfo*  removeFirstERabFrmUeRabList();
   
   /**
    * @brief Function to 
    * 
    * @details Function to 
    *      
    * @param[in] 
    * @return void 
    */
   U32 getNumRabsPresentInUE() { return (m_tlERABList.size()); };
   
   /**
    * @brief Function of friend of CRBearerController class, used to update the
    *        CSG membership modification of an UE need to update into the GBR 
    *        ERABs multimap table.
    * 
    * @details Function to update the key of the ERABs of this UE to access from
    *          GBR ERABs table when there is a modification of CSG memebership
    *          status.
    *      
    * @param[in] pUE           Pointer to the object of the UE for accessing the
    *                          all ERABs of the UE.
    * @param[in] ObjRbc        Object of the RBC class to access the Pre-emption
    *                          finder class object.
    * @param[in] bIsCSGMember  The modified CSG membership.
    * @return void 
    */
   friend void updateCsgMemberShip(CUEContext* pUE, 
                                   CRBearerController &ObjRbc,
                                   bool bIsCSGMember);
   /**
    * @brief Function to set the CRNTI in the UE's all ERAB obects.
    * 
    * @details Function to set the CRNTI in the UE's all ERAB obects.which is used
    *        during Re-establishment scenario to update the CRNTI in all ERABs
    *        of this UE.
    *      
    * @param[in] usCRNTI   CRNTI of the UE.
    * @return void 
    */
   void setRabsCRNTI(U16 usCRNTI);
  
   /**
    * @brief Function to increment the UE inactivity timer expiry count.
    * 
    * @details Function to increment the UE inactivity timer expiry count on
    *          reception of RMU_NO_DATA event on the RMU interface.
    *      
    * @return void 
    */
   void incrementUeInactivityTimerExpiryCount() {m_uiInactiveCount++;};

   /**
    * @brief Function to reset the UE inactivity timer expiry count.
    * 
    * @details Function to reset the UE inactivity timer expiry count on
    *          reception of RMU_DATA event on the RMU interface.
    *      
    * @return void 
    */
   void resetUeInactivityTimerExpiryCount() {m_uiInactiveCount = 0;};
   
   /**
    * @brief Function to return the UE inactivity timer expiry count.
    * 
    * @details Function to return the UE inactivity timer expiry count 
    *      
    * @return U32
    *        value of UE inactivity timer expiry count 
    */
   U32 getInactivityTimerExpiryCount() { return m_uiInactiveCount;};

   void updateHighPriorityQosParams();
   void releaseUE();
   CERABInfo *findERAB(U8 bERABId);
   static const std::list<CERABInfo*> & getGlobalERABList();
#ifdef LTE_ADV
   U8  m_sCellIdx2CellIdMap[RMU_MAX_SCELL_PER_UE]; /*Scell Idx to CellId Map*/
#endif

    /* set functions */
   void setUeCapInfo(RmuUeCapInfoIe & stUECapability);
   void setCRNTI(U16 usCRNTI) {  m_usCRNTI = usCRNTI; };
   void setEstablishmentCause(U8 bEstablishmentCause) { m_bEstablishmentCause = bEstablishmentCause; };
   void setHighestQciPriorityOfUe(U8 bMaxQciPriority);
   void setMaxArpOfUe(U8 bMaxArp);
   void setNonPreEmptableRabforUe(bool bHaveNonPremptableERAB);
   void setActiveUEFlag(bool bIsActiveUe);
   void resetUePCqiRprtInfo(){m_stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.type = FALSE;};
   void setUeCqiRprtInfo();
   void setUePeriodicCqi(RmuPucchReportMode mode);
   void setUeAperiodicCqi(RmuPuschReportMode mode);
   void setUePCqiFormat(RmuPcqiFormatInd enCqiFormatInd);
   void setUeCqiPmiIdxResIdx(U16 usCqiPmiIdx, U16 usCqiResIdx);
   void setUeCqiFactorK(U32 uiFactorK){ m_stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.bFactorK = uiFactorK; };
   inline void setSubbandCQIPeriodicityFactor(RmuSubbandCqiPeriodicityFactor periodicityFactor){ m_stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.sBCqiPeriodicityFactor = periodicityFactor; };
   void setUeCqiRiIndex(U32 uiRiCfgIdx, Bool pres);
   void setSimCqiAckSupp(Bool bSimulAckNackCqi) { m_stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.bSimulAckNackCqi = bSimulAckNackCqi; };
   void setUlUeAmbr(U32 uiUlUeAmbr) { m_uiUlUeAmbr = uiUlUeAmbr;};
   void setDlUeAmbr(U32 uiDlUeAmbr) {m_uiDlUeAmbr = uiDlUeAmbr;};
   void setUeIdx(U8 ueIdx) {m_bUeIdx = ueIdx;};
   Bool isRiCfgDone(){return m_stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.riConfigIndex.bPres;};

    /* get functions */
   U8 getEstablishmentCause() { return m_bEstablishmentCause; };
   bool isActiveUE() { return m_bIsActiveUE;};
   U8 getHighestQciPriorityOfUe() const;
   U8 getMaxArpQciPriorityOfUe() const;
   U8 getMaxArpOfUe() const;
   bool isNonPreemptableUE() const;
   U32  getFgi() { return m_stUECapability.stEutraCapInfo.uiFeatureGrpIndicator; };
   bool getSimCqiAckSupp() { return (m_stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.bSimulAckNackCqi); };
   bool getUePcqiSubbandSupp();
   RmuPCqiReportCfg & getPCQIReport(){ return m_stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg; };
   RmuUeCqiReportCfg & getCqiReport() { return m_stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg; };
   U16 getCqiPmiCfgIdx(){return m_stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.usCqiConfigIndex; };
   RmuRiConfigIndex & getUeCqiRiIdx(){return m_stUeRadioResCfg.stPhyCfgDed.stCqiRepCfg.stPrdCqiRepCfg.riConfigIndex;};
   void setUeTxnMode(U8 bTxnMode);
   U8 getUeTxnMode() { return m_bTxnMode; };
   U8 getUeRadioDedResAllocBitMap() { return m_radioResAllocBitMap; };
   U16 getCRNTI() { return m_usCRNTI; };
   CmLteUeCategory getUeCategory();
#if 0
   RmTimeVal  getSetupTime() { return m_stSetupTime;};
   void setSetupTIme() { gettimeofday(&m_stSetupTime, NULL);};
#endif
   bool operator == (const CUEContext &rhs)
   {
      return (rhs.m_usCRNTI == m_usCRNTI);
   }
   U16 getUeIdx() {return m_bUeIdx;};

   void setDrxCfg(CmRrmDrxCfg &stRmDrxCfg);
   void relDrxCfg();
   CmRrmDrxCfg getDrxCfg(){return m_stRmDrxCfg;};
   RmuUeSrCfg  &getSrCfg(){return m_stUeRadioResCfg.stPhyCfgDed.stSrCfg;};
   void setSrCfg(U16 usSrIdx, U16 usSrResIdx, CmRrmDsrTransMax enDsrTransMax);
   U16 getDrxLongCycle(){return m_stRmDrxCfg.stDrxLongCycleOffst.usLongDrxCycle;};
   Bool   isUeSupportsDRX();
   Bool   isUeSupportsSPS();
   void setSpsParam(U8 erabId);
   void relSpsParam();
   void setSpsCfg(RmuUeSpsCfg &stRmSpsCfg);
   S32 relSpsCfg();
   U8 getSpsErabId(){return m_bQciOneErabId;};
   RmuUeSpsCfg getSpsCfg(){return m_stRmSpsCfg;};

   void setUeRiOffset(U16 usRiOffset) {m_usRiOffset = usRiOffset;};
   U16 getUeRiOffset() {return m_usRiOffset;};
   inline Bool isTxnModeChng() {return m_bIsTxnModeChng;};
   inline void setTxnModeChng(Bool bIsTxnModeChng) {m_bIsTxnModeChng = bIsTxnModeChng;};
   Bool isGbrQciExisForAnr()
   {
      if(m_bDrxDisBrrCnt)
      {
         return TRUE;
      }
      else
      {
         return FALSE;
      }
   };
#ifdef LTE_ADV
   inline RmuUeCqiReportCfg & getScellCqiReport(U8 idx) { return m_scellInfo[idx].sCellDedInfo.stCqiRepCfg; };
   void setUeScellCqiPmiIdxResIdx(U8 sCellIdx,U16 usCqiPmiIdx, U16 usCqiResIdx);
   void setUeScellPeriodicCqi(U8 sCellIdx, RmuPucchReportMode mode);
   void setUeScellCqiRiIndex(U8 sCellIdx, U32 uiRiCfgIdx, Bool pres);
   void setUeScellCqi(U8 sCellIdx);
   inline void incUeScellNum(){m_numOfScell++;};
   void resetUeScellPCqiRprtInfo(U8 idx){m_scellInfo[idx].sCellDedInfo.stCqiRepCfg.stPrdCqiRepCfg.type = FALSE;};
   inline U8 getScellCount(){return m_numOfScell;};
   void setUeScellAperiodicCqi(RmuPuschReportMode mode,U8 sCellIdx);
   inline U8 getCellIdFromScellIdx(U8 sCellIdx) {return m_sCellIdx2CellIdMap[sCellIdx];};
   inline void setScellIdx(U8 idx,U8 sCellIdx) {m_scellInfo[idx].sCellIdx = sCellIdx;};

   inline bool getUeCaCap(){return (m_bIsUeCaCap);};
   inline void setUeCaCap(bool isUeCaCap){m_bIsUeCaCap = isUeCaCap;};
#endif
   void setMemberShip(U8 bMemberShip) { m_bIsMember = bMemberShip; };
   Bool isCsgMember() { return m_bIsMember; };
   void setCsgMeberShipIdentified(bool bisIdentified) {m_bIsUeMemberShipIdentified = bisIdentified;};
   bool isCsgMemberShipIdentifed() {return m_bIsUeMemberShipIdentified;};

   /**
    * @brief Function to set that an emergency bearer is present.
    * 
    * @details Function to set the emergency bearer present flag.
    *      
    * @return bool 
    */
   void setIsEmrgBrPrst(bool bIsEmrgncyBr) {m_bIsEmrgncyBrPrsnt = bIsEmrgncyBr;};
   /**
    * @brief Function to get if any emergency bearer is present.
    * 
    * @details Function to return the emergency bearer present flag.
    *      
    * @return bool 
    */
   bool getIsEmrgBrPrst() {return m_bIsEmrgncyBrPrsnt;};

   /**
    * @brief Function to set the flag if emergency bearer is present for UE.
    * 
    * @details Function to set the flag in UE control block whether a bearer
    *          with emergency ARP value is present or not.
    *          This flag will be used during UE admission control.
    *      
    * @param[in] pUE          UE Control Block
    * @param[in] uEmrgncyArp  Emergency ARP value
    *
    * @return void 
    */
   void updateEmrgncyBrPrsnt(CUEContext *pUE, U32 uEmrgncyArp);

private:
   RmuUeCapInfoIe    m_stUECapability;
   RmRcmUeStats      m_stUeStats;
   CmRrmDrxCfg       m_stRmDrxCfg;
   U16               m_usCRNTI;
   bool              m_bHaveNonPremptableERAB;
   U32               m_uiMAXGBR;
   U32               m_uiUlUeAmbr;
   U32               m_uiDlUeAmbr;
   U8                m_bMaxARP;
   U8                m_bMaxArpQciPriority;
   U8                m_bHighestQciPriority;
   U8                m_bEstablishmentCause;
   U8                m_radioResAllocBitMap;
   U8                m_bTxnMode;
   bool              m_bIsActiveUE;
   bool					m_bIsUeMemberShipIdentified;
   U8                m_numQciThreeRab;
#if 0
   RmTimeVal         m_stSetupTime;
#endif
   /*!< List of ERABs belongs to this UE */
   std::list<CERABInfo*> m_tlERABList;
   
   /*!< UE Inactivity timer expiry count */
   U32               m_uiInactiveCount;

   RmuUeRadioResCfg  m_stUeRadioResCfg;
   U16               m_bUeIdx;
   U8                m_bDrxDisBrrCnt;
   U16               m_usRiOffset;
   RmuUeSpsCfg       m_stRmSpsCfg;    
   U8                m_bQciOneBrrAdmit;
   U8                m_bQciOneErabId;
   Bool              m_bIsMember;
   Bool              m_bIsTxnModeChng; 
   /*!< Flag to indicate if bearer with Emergency ARP is present or not */
   Bool              m_bIsEmrgncyBrPrsnt;
#ifdef LTE_ADV
   bool              m_bIsUeCaCap;
   U8                m_numOfScell;     /*!<  numOfSCells */
   RmRcmScellInfo    m_scellInfo[RMU_MAX_SCELL_PER_UE];  /*!<  sCell Dedicated Info */
#endif
};

#endif /* _RRM_UECONTEXT_H_ */
/********************************************************************30**

           End of file:     rm_uecontext.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:45:37 2013

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
