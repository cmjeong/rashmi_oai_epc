#include "rm.h"
#include "rgm.x"
#include "rmu.h"
#include "rmu.x"
#include "lrm.h"
#include "lrm.x"
#include "rm_uecontext.h"
#include "rm_cellmanager.h"
#include "rm_prbbasedadmissioncontroller.h"
#include "rm_qcibasedadmissioncontroller.h"

#ifndef __TEST_RM__
#define __TEST_RM__

#define MAX_CELL_CONFIG_DATA 35
#define MAX_ACT_UES      32
#define MAX_SIG_UES      16
#define MAX_EXT_UES      (ceil(MAX_ACT_UES * 0.25))
#define MAX_CSG_UES      MAX_ACT_UES
#define MAX_NON_CSG_UES  MAX_ACT_UES

struct UeAdmitRspExpInfo
{
   RmuStatusInfo          stStatusInfo;
   RmuUeRadioResCfg       stUeRadioResCfg;
   U32                    uiTransId;      /* Transaction ID   */
   U16                    usCrnti;        /* UE Crnti value     */   
   U8                     bCellId;        /* Cell Identifier */
   U8                     bWaitTime;      /* In case of Status is FAILURE, The Wait time
                                                  should include in RRC Connection Reject message */
};

struct UeRecfgExpInfo 
{
   RmuErabAdmitted            stErabAcceptLst[RMU_MAX_NUM_ERABS];
   RmuErabRejected            stErabRejectLst[RMU_MAX_NUM_ERABS];
   RmuUeRadioResCfg           stUeRadioResCfg;
   RmuStatusInfo              stStatusInfo;
   U32                        uiTransId;            /* Transaction ID  */
   U16                        usCrnti;              /* Crnti value     */   
   U8                         bCellId;              /* Cell Identifier */
   U8                         bRecfgBitMap;         /* Indicates the reconfig info
                                                       included in this structure */
   U8                         bNoErabsAccepted;     /* Number of ERABs that are admitted at RRM */
   U8                         bNoErabsRejected;     /* Number of ERABs that are Rejected at RRM */
   Bool                       isGBRBearerExists;
};

struct UeHoAdmitRspExpInfo
{
   RmuErabAdmitted             stErabAdmitLst[RMU_MAX_NUM_ERABS];
   RmuErabRejected             stErabRejectLst[RMU_MAX_NUM_ERABS];
   RmuUeRadioResCfg            stUeRadioResCfg;
   RmuStatusInfo               stStatusInfo;           /* Response is failure or success */
   U32                         uiTransId;          /* Transaction ID   */
   U16                         usCrnti;             /* Crnti value      */   
   U8                          bCellId;            /* Cell Identifier  */
   U8                          bNoErabsAdmitted;    /* Number of ERABs that are admitted at RRM */
   U8                          bNoErabsRejected;     /* Number of ERABs that are Rejected at RRM */
   Bool                        isGBRBearerExists;
};

struct AcbInfo
{
   bool isEnable; /*!< Is barring info is available */
   CmRrmAcBarringTime time; /*!< Barring Time */
   CmRrmAcBarringFactor factor; /*!< Barring Factor */
   U8  spAc; /*!< Barring info for Special access class */
};

struct CellRecfgAcbInfo
{
   bool emergency;
   AcbInfo moSig;
   AcbInfo moData;
};

struct CellRecfgIndExpInfo
{
   union
   {
      CellRecfgAcbInfo acbExpInfo;
   }u;
};

extern void resetEnv();
extern bool isStartPrbReportCfg;
extern bool isStopPrbReportCfg;
extern bool isUeAdmitRspExpInfoSet;
extern bool isHoUeAdmitRspExpInfoSet;
extern bool isUeRecfgExpInfoSet;
extern bool isUeErabRelIndExpected;
extern bool isUeErabRelIndRcvd;
extern bool memAllocFail;
extern bool isUeRelIndExpected;
extern bool isUeRelIndRcvd;
extern bool isCellRecfgIndExpected;

extern UeAdmitRspExpInfo ueAdmitRspExp;
extern UeRecfgExpInfo ueRecfgExp;
extern UeHoAdmitRspExpInfo ueHoAdmitRspExp;
extern RmuUeRelInd   ueRelIndExp;
extern CellRecfgIndExpInfo cellRecfgIndExp;

extern S16 sendRmGenCfg();
extern S16 configRmuUSap(SpId spId);
extern S16 configRmuLSapCfg (SuId suId, SpId spId);
extern S16 sendEnbStatus(U8 status);

extern CCellManager *getNewCellObj(LrmCellConfigData *stCellConfigData);
extern void freeCellManagerObj(CCellManager *pstCellManagerObj);

extern RmuUErabAddModIe stRabSetupConfig[];

extern void fillPrbUsage(RgmPrbRprtInd *usageInfo, int i);

extern void fillErabConfigRequest(RmuErabConfigIe *stRabConfig, 
                                  U8 numRabsToAdd,
                                  U8 qci,
                                  U8 index,
                                  RmuErabAction enErabAction = RMU_ADD_ERAB);

extern CUEContext *createUeCb();

extern CUEManager* createUEManager(U32 maxActiveUes, 
                                   U32 maxSignalingUes,
                                   U32 maxCsgUes, 
                                   U32 maxNonCsgUes, 
                                   U32 maxExtraUes);

extern CAdmissionController* createAdmissionController(U32 waitTime,
                                                       U32 cellId,
                                                       CUEManager& ueMgr);


extern void freeUeCb(CUEContext *pUE);

extern void fillCellConfigDataForSpecificConfig(
                                  LrmCellConfigData *cellConfigData,
                                  U8 configType);

extern CPRBBasedAdmissionController *getPrbAdmCntrlObj(
                                  LrmCellConfigData &cellConfigData);

extern void freePrbAdmCntrlObj(CPRBBasedAdmissionController *objPrbAdmCntlr);

extern CQCIBasedAdmissionController *getQciAdmCntrlObj(
                                      LrmCellConfigData &stCellConfigData);

extern void freeQciAdmCntrlObj(CQCIBasedAdmissionController *objQciAdmCntlr);

extern void createAdmitReq(RmuUeAdmitReq *ptrAdmitReq,
                           RmuConEstCause   enConEstabCause,
                           U32  uiTransId,
                           U16  usCrnti,
                           U8  bCellId);

extern void createUeRecfgReq(RmuUeRecfgReq *ptrRecfgReq,
                    U32  uiTransId,
                    U8   bCellId,
                    U16  usCrnti,
                    U32  bRecfgBitMap,
                    bool isMember,
                    U16  newCrnti);

extern void createUeRelReq(RmuUeRelReq *ptrRelReq,
                    U32  uiTransId,
                    U8  bCellId,
                    U16  usCrnti);

extern void updatePrbRprt(CCellManager *cellMngr,
                          U32 prbUsgMask, 
                          U32 qci, 
                          U32 dl, 
                          U32 ul);

extern void intializeRlog();
extern void flushData(int sig);
#if 1
#define PRNT_TEST_NAME(){\
   static const char* RLOG_MODULE_NAME="RRM";\
   static int RLOG_MODULE_ID=256;\
   static int RLOG_FILE_ID=161;\
   const ::testing::TestInfo* const test_info =\
      ::testing::UnitTest::GetInstance()->current_test_info();\
   RLOG_STR(L_ALWAYS, "TestCaseName: %s", test_info->name());\
}
#else
extern void printTestCaseName();
#endif

#endif
