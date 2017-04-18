


/**********************************************************************

    Name:   Test file for CL Module which hosts the convergence layer

    Type:   CPP source file

    Desc:

    File:   test_qu_RsysCLMod.cpp 

    Sid:      test_rm_admissioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:47 2016

    Prg:

**********************************************************************/
#include <limits.h>
#include "gtest/gtest.h"

// File with class that is being tested
#include "rm_admissioncontroller.h"
#include "rm_uemanager.h"
#include "rm.h"
#include "test_rm.h"
#include <math.h>

/* The below lines need to be in some common place and not inside the test code
 * */
#ifdef _cplusplus
extern "C" {
   S16 tst();
}
#endif

S16 tst()
{
   printf("We are inside the entry tst function\n");
   return 0;
}

CUEManager* createUEManager(U32 maxActiveUes, U32 maxSignalingUes,
      U32 maxCsgUes, U32 maxNonCsgUes, U32 maxExtraUes)
{
   LrmCellConfigData cellConfigData;
   cellConfigData.bMaxActiveUesServed = maxActiveUes;
   cellConfigData.bMaxSigUesServed = maxSignalingUes;
   cellConfigData.usMaxCsgUes = maxCsgUes;
   cellConfigData.usMaxNonCsgUes = maxNonCsgUes;
   cellConfigData.usMaxExtraUes = maxExtraUes;

   return new CUEManager(cellConfigData);
}

CAdmissionController* createAdmissionController(U32 waitTime,
                                                U32 cellId,
                                                CUEManager& ueMgr)
{
   LrmCellConfigData cellCfg;
   cellCfg.bWaitTime = waitTime;
   cellCfg.bCellId = cellId;

   return new CAdmissionController(cellCfg, ueMgr);
}

void createAdmitReq(RmuUeAdmitReq *ptrAdmitReq,
                    RmuConEstCause   enConEstabCause,
                    U32  uiTransId,
                    U16  usCrnti,
                    U8  bCellId)
{
   if(NULL == ptrAdmitReq)
   {
      return;
   }
   ptrAdmitReq->enConEstabCause = enConEstabCause;
   ptrAdmitReq->uiTransId = uiTransId;
   ptrAdmitReq->bCellId = bCellId;
   ptrAdmitReq->usCrnti = usCrnti;
   return;
}

void createUeRelReq(RmuUeRelReq *ptrRelReq,
                    U32  uiTransId,
                    U8  bCellId,
                    U16  usCrnti)
{
   if(NULL == ptrRelReq)
   {
      return;
   }
   ptrRelReq->uiTransId = uiTransId;
   ptrRelReq->bCellId = bCellId;
   ptrRelReq->usCrnti = usCrnti;
   return;
}

void updateHoReqWithCrnti(RmuUeHoReq *ptrHoReq,
                          U32  uiTransId,         /* Transaction ID */
                          U16  usCrnti,            /* Crnti value     */   
                          U8   bCellId)
{
   if(NULL == ptrHoReq)
   {
      return;
   }
   memset(ptrHoReq, 0, sizeof(RmuUeHoReq));
   ptrHoReq->uiTransId = uiTransId;
   ptrHoReq->bCellId = bCellId;
   ptrHoReq->usCrnti = usCrnti;
   return;
}
/* class used to test CL Module functions */
class CAdmissionControllerTest : public ::testing::Test
{
public:
   CAdmissionController *admController;
   CUEManager* act32Sig16UeMgr;
   
protected:
   virtual void SetUp()
   {
      PRNT_TEST_NAME();
      act32Sig16UeMgr = createUEManager(MAX_ACT_UES, MAX_SIG_UES, MAX_CSG_UES,
            MAX_NON_CSG_UES, (U32)MAX_EXT_UES);
      admController = createAdmissionController(64, 123, *act32Sig16UeMgr);
#if 0
      Addr  =(uint32_t)malloc(0x9000000);
      extern uint32_t g_payloadRegionBaseAddr;
      g_payloadRegionBaseAddr  =Addr;
      SInit();
      mainProc()->get<IpcFifoMod>(Qcom::IPC_FIFO_MOD_HIGH)->m_setRegLocalAgentIdToZero();
#endif
   }

   virtual void TearDown()
   {
      delete act32Sig16UeMgr;
      delete admController;
#if 0
     ssdSetModuleId();
     free((void *)Addr);
     SDeInit();
#endif
   }
private:
   uint32_t Addr;
};
TEST_F(CAdmissionControllerTest, handleUEAdmission_withCause_MoSignalling) 
{
   RmuUeAdmitReq  admitReq;
   RmuUeAdmitRsp  admitRsp;
   CUEContext     *pUE = NULL;


   admitRsp.bWaitTime =100;
   admitRsp.stStatusInfo.enStatus = RMU_FAILURE;

   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, 1, 61);

   pUE = admController->handleUEAdmission(admitReq, &admitRsp);

   EXPECT_NE(pUE, (CUEContext*)NULL);
   EXPECT_EQ(admitRsp.stStatusInfo.enStatus, RMU_SUCCESS);
   EXPECT_EQ(admitRsp.stStatusInfo.enCause, RMU_CAUSE_NOT_APP);
   EXPECT_EQ(admitRsp.bWaitTime, 100);
}

TEST_F(CAdmissionControllerTest, handleUEAdmission_withCause_Emergency) 
{
   RmuUeAdmitReq  admitReq;
   RmuUeAdmitRsp  admitRsp;
   CUEContext     *pUE = NULL;


   admitRsp.bWaitTime =100;
   admitRsp.stStatusInfo.enStatus = RMU_FAILURE;

   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 1, 61);

   pUE = admController->handleUEAdmission(admitReq, &admitRsp);

   EXPECT_NE(pUE, (CUEContext*)NULL);
   EXPECT_EQ(admitRsp.stStatusInfo.enStatus, RMU_SUCCESS);
   EXPECT_EQ(admitRsp.stStatusInfo.enCause, RMU_CAUSE_NOT_APP);
   EXPECT_EQ(admitRsp.bWaitTime, 100);
}

TEST_F(CAdmissionControllerTest, handleUEAdmission_withCause_default) 
{
   RmuUeAdmitReq  admitReq;
   RmuUeAdmitRsp  admitRsp;
   CUEContext     *pUE = NULL;

   admitRsp.bWaitTime =100;
   admitRsp.stStatusInfo.enStatus = RMU_FAILURE;

   createAdmitReq(&admitReq, RMU_EST_CAUSE_HO_REQ, 1, 1, 61);

   pUE = admController->handleUEAdmission(admitReq, &admitRsp);

   EXPECT_EQ(pUE, (CUEContext*)NULL);
   EXPECT_EQ(admitRsp.stStatusInfo.enStatus, RMU_FAILURE);
   EXPECT_EQ(admitRsp.stStatusInfo.enCause, RMU_CAUSE_OTHER);
   EXPECT_EQ(admitRsp.bWaitTime, 64); /* 64 is intialized as wait time in this test class */
}
TEST_F(CAdmissionControllerTest, handleUEAdmission_withCause_MoData_DataMaxReached) 
{
   RmuUeAdmitReq  admitReq;
   RmuUeAdmitRsp  admitRsp;
   CUEContext     *pUE = NULL;
   int            crnti = 61;


   admitRsp.bWaitTime =100;
   admitRsp.stStatusInfo.enStatus = RMU_FAILURE;

   /* maxActiveUes is configured as 32 */   
   for(int idx = 0; idx < (MAX_ACT_UES + MAX_EXT_UES); idx++)
   {    
      crnti += idx;
      createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, crnti,1);
      pUE = admController->handleUEAdmission(admitReq, &admitRsp);
      
      EXPECT_NE(pUE, (CUEContext*)NULL);
      EXPECT_EQ(admitRsp.stStatusInfo.enStatus, RMU_SUCCESS);
      EXPECT_EQ(admitRsp.stStatusInfo.enCause, RMU_CAUSE_NOT_APP);
      EXPECT_EQ(admitRsp.bWaitTime, 100);
   }

   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, ++crnti,1);
   pUE = admController->handleUEAdmission(admitReq, &admitRsp);

   EXPECT_EQ(pUE, (CUEContext*)NULL);
   EXPECT_EQ(admitRsp.stStatusInfo.enStatus, RMU_REDIRECT);
   EXPECT_EQ(admitRsp.stStatusInfo.enCause, RMU_CAUSE_MAX_UE_REACHED);
   EXPECT_EQ(admitRsp.bWaitTime, 100); 
}

TEST_F(CAdmissionControllerTest, handleUEAdmission_withCause_MoSig_SigMaxReached) 
{
   RmuUeAdmitReq  admitReq;
   RmuUeAdmitRsp  admitRsp;
   CUEContext     *pUE = NULL;
   int            crnti = 61;


   admitRsp.bWaitTime =100;
   admitRsp.stStatusInfo.enStatus = RMU_FAILURE;
  
   /* maxSignalingUes is 16 UEs */
   for(int idx = 0; idx < MAX_SIG_UES; idx++)
   {    
      crnti += idx;
      createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, crnti,1);
      pUE = admController->handleUEAdmission(admitReq, &admitRsp);
      
      EXPECT_NE(pUE, (CUEContext*)NULL);
      EXPECT_EQ(admitRsp.stStatusInfo.enStatus, RMU_SUCCESS);
      EXPECT_EQ(admitRsp.stStatusInfo.enCause, RMU_CAUSE_NOT_APP);
      EXPECT_EQ(admitRsp.bWaitTime, 100);
   }

   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, ++crnti,1);
   pUE = admController->handleUEAdmission(admitReq, &admitRsp);

   EXPECT_EQ(pUE, (CUEContext*)NULL);
   EXPECT_EQ(admitRsp.stStatusInfo.enStatus, RMU_REDIRECT);
   EXPECT_EQ(admitRsp.stStatusInfo.enCause, RMU_CAUSE_MAX_UE_REACHED);
   EXPECT_EQ(admitRsp.bWaitTime, 100); 
}

TEST_F(CAdmissionControllerTest, handleUEHOAdmission_successCase) 
{
   RmuUeHoReq     ueHoReq;
   RmuUeHoRsp     ueHoRsp;
   CUEContext     *pUE = NULL;
   int            crnti = 61;


   ueHoRsp.stStatusInfo.enStatus = RMU_FAILURE;

   updateHoReqWithCrnti(&ueHoReq, 1, ++crnti,1);
   pUE = admController->handleUEHOAdmission(ueHoReq, &ueHoRsp);

   EXPECT_NE(pUE, (CUEContext*)NULL);
   EXPECT_EQ(ueHoRsp.stStatusInfo.enStatus, RMU_SUCCESS);
   EXPECT_EQ(ueHoRsp.stStatusInfo.enCause, RMU_CAUSE_NOT_APP);
}


TEST_F(CAdmissionControllerTest, handleUEHOAdmission_ActiveUEMaxReached) 
{
   RmuUeAdmitReq  admitReq;
   RmuUeAdmitRsp  admitRsp;
   RmuUeHoReq     ueHoReq;
   RmuUeHoRsp     ueHoRsp;
   CUEContext     *pUE = NULL;
   int            crnti = 61;


   admitRsp.bWaitTime =100;
   admitRsp.stStatusInfo.enStatus = RMU_FAILURE;
   ueHoRsp.stStatusInfo.enStatus = RMU_SUCCESS;

   /* maxActiveUes is configured as 32 */   
   for(int idx = 0; idx < (MAX_ACT_UES + MAX_EXT_UES); idx++)
   {    
      crnti += idx;
      createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, crnti,1);
      pUE = admController->handleUEAdmission(admitReq, &admitRsp);

      EXPECT_NE(pUE, (CUEContext*)NULL);
      EXPECT_EQ(admitRsp.stStatusInfo.enStatus, RMU_SUCCESS);
      EXPECT_EQ(admitRsp.stStatusInfo.enCause, RMU_CAUSE_NOT_APP);
      EXPECT_EQ(admitRsp.bWaitTime, 100);
   }

   updateHoReqWithCrnti(&ueHoReq, 1, ++crnti,1);
   pUE = admController->handleUEHOAdmission(ueHoReq, &ueHoRsp);

   EXPECT_EQ(pUE, (CUEContext*)NULL);
   EXPECT_EQ(ueHoRsp.stStatusInfo.enStatus, RMU_FAILURE);
   EXPECT_EQ(ueHoRsp.stStatusInfo.enCause, RMU_CAUSE_MAX_UE_REACHED);
}



#if 0
TEST_F(CAdmissionControllerTest, admitMoDataAndMtAccessCall_allScenarios) 
{
   RmuStatusInfo statusInfo={(RmuRrcCause)0,(RmuStatus)0};
   // check when maxActiveUeLimit is reached
   bool ret = admController->admitMoDataAndMtAccessCall(statusInfo);
   EXPECT_EQ(ret, true);
   EXPECT_EQ(statusInfo.enStatus, 0);
   EXPECT_EQ(statusInfo.enCause, 0);

   // let us populate the UEmanager with lots of UEs to get a admissionFailure
   for(int i = 0; i < 35; i++)
   {
      act32Sig16UeMgr->admitUE(i+1, RMU_EST_CAUSE_MO_DATA);
   }

   ret = admController->admitMoDataAndMtAccessCall(statusInfo);
   EXPECT_EQ(ret, false);
   EXPECT_EQ(statusInfo.enStatus, RMU_REDIRECT);
   EXPECT_EQ(statusInfo.enCause, RMU_CAUSE_MAX_UE_REACHED);
   
#if 0
   RsysCLMod rsysCLMod(Qcom::RSYS_MOD2);
   
   /* local agent ID is not set */
   EXPECT_EQ(mainProc()->get<IpcFifoMod>(Qcom::IPC_FIFO_MOD_HIGH)->m_getRegLocalAgentId(),0);

   rsysCLMod.init(Qcom::PRE_PROVISION);
   
   /* local agent ID is registered */
   EXPECT_EQ(mainProc()->get<IpcFifoMod>(Qcom::IPC_FIFO_MOD_HIGH)->m_getRegLocalAgentId(),1);
#endif
}
#endif /* AMIT */
#if 0
/* test case to check the init of CL Module for POST_PROVISION */
TEST_F(RsysCLModTest, init_receivedPOST_PROVISION) 
{
   RsysCLMod rsysCLMod(Qcom::RSYS_MOD2);
   
   /* local agent ID is not set */
   EXPECT_EQ(mainProc()->get<IpcFifoMod>(Qcom::IPC_FIFO_MOD_HIGH)->m_getRegLocalAgentId(),0);

   rsysCLMod.init(Qcom::POST_PROVISION);
   
   /* local agent ID is not set */
   EXPECT_EQ(mainProc()->get<IpcFifoMod>(Qcom::IPC_FIFO_MOD_HIGH)->m_getRegLocalAgentId(),0);
}

/* test case to check the init of CL Module for wrong init stage*/
TEST_F(RsysCLModTest, init_receivedUnexpectedInitStage) 
{
   RsysCLMod rsysCLMod(Qcom::RSYS_MOD2);

   /* local agent ID is not set */
   EXPECT_EQ(mainProc()->get<IpcFifoMod>(Qcom::IPC_FIFO_MOD_HIGH)->m_getRegLocalAgentId(),0);

   rsysCLMod.init(Qcom::InitStage(10));
   
   /* local agent ID is not set */
   EXPECT_EQ(mainProc()->get<IpcFifoMod>(Qcom::IPC_FIFO_MOD_HIGH)->m_getRegLocalAgentId(),0);
}

/* test case to check the proc message for processing the remote agent registration indication message */
TEST_F(RsysCLModTest, procMsg_handlingRemoteAgentRegistration) 
{
   RsysCLMod rsysCLMod(Qcom::RSYS_MOD2);
   Qcom::IpcMessage ipcMsgPtr(Qcom::IpcMessage::PROTO_IPC_FIFO, Qcom::IpcFifoBase::IPC_FIFO_REMOTE_AGENT_REG_IND);

   rsysCLMod.procMsg(Qcom::RSYS_MOD2, &ipcMsgPtr);
}

/* test case to check the proc message for processing the read indication message */
TEST_F(RsysCLModTest, procMsg_handlingReadIndication) 
{
   RsysCLMod rsysCLMod(Qcom::RSYS_MOD2);
   Qcom::IpcMessage ipcMsgPtr(Qcom::IpcMessage::PROTO_IPC_FIFO, Qcom::IpcFifoBase::IPC_FIFO_READ_IND);

   rsysCLMod.procMsg(Qcom::RSYS_MOD2, &ipcMsgPtr);
}

/* test case to check the proc message for processing the invalid message */
TEST_F(RsysCLModTest, procMsg_handlingInvalidMessage) 
{
   RsysCLMod rsysCLMod(Qcom::RSYS_MOD2);
   Qcom::IpcMessage ipcMsgPtr(Qcom::IpcMessage::PROTO_IPC_FIFO, Qcom::IpcFifoBase::IPC_FIFO_WRITE_IND);

   rsysCLMod.procMsg(Qcom::RSYS_MOD2, &ipcMsgPtr);
}

/* test case to check the proc message for processing the invalid protocol */
TEST_F(RsysCLModTest, procMsg_handlingInvalidProtocol) 
{
   RsysCLMod rsysCLMod(Qcom::RSYS_MOD2);
   Qcom::IpcMessage ipcMsgPtr(Qcom::IpcMessage::PROTO_NONE, Qcom::IpcFifoBase::IPC_FIFO_READ_IND);

   rsysCLMod.procMsg(Qcom::RSYS_MOD2, &ipcMsgPtr);
}

/* test case to check the function ipcRemoteAgentRegIndHandler */
TEST_F(RsysCLModTest, ipcRemoteAgentRegIndHandler_handlingRemoteAgentRegMsg) 
{
   RsysCLMod rsysCLMod(Qcom::RSYS_MOD2);
   IpcFifo::IpcAgentName agentname;
   
   memcpy((void *)agentname.str_, (void *)"FAPI_CONV_AGENT",32);

   Qcom::IpcFifoRemoteAgentRegInd msgPtr(agentname,(IpcFifo::IpcAgentId)0);

   rsysCLMod.ipcRemoteAgentRegIndHandler(&msgPtr); 
}

/* test case to check the function ipcRemoteAgentRegIndHandler when agent name is different */
TEST_F(RsysCLModTest, ipcRemoteAgentRegIndHandler_handlingRemoteAgentRegMsgWithInvalidAgentName) 
{
   RsysCLMod rsysCLMod(Qcom::RSYS_MOD2);
   IpcFifo::IpcAgentName agentname;
   
   memcpy((void *)agentname.str_, (void *)"FAPI_CONV_AGENT_INVALID",32);

   Qcom::IpcFifoRemoteAgentRegInd msgPtr(agentname,(IpcFifo::IpcAgentId)0);

   rsysCLMod.ipcRemoteAgentRegIndHandler(&msgPtr); 
}

/* test case to check the proc message for processing the received invalid message */
TEST_F(RsysCLModTest, ipcReadIndHandler_handlingMsgReceivedOnFifo) 
{
   RsysCLMod rsysCLMod(Qcom::RSYS_MOD2);
   char message[13] = "test message";

   Qcom::IpcFifoReadInd fifoMsg(0);

   Qcom::IpcFifoReadIndPtr msgPtr = &fifoMsg;
   msgPtr->insertReadMsg((uint8_t *)message, 12, 0);
   msgPtr->insertReadMsg((uint8_t *)message, 12, 0);
   msgPtr->insertReadMsg((uint8_t *)message, 12, 0);

   rsysCLMod.ipcReadIndHandler(msgPtr); 
}

/* test case to check the sending of message to phy */
TEST_F(RsysCLModTest, SendMsgToPhy_writingMsgOnFifo) 
{
   char message[20] = "send message to phy";

   SendMsgToPhy((uint8_t *)message);

   EXPECT_EQ(mainProc()->get<IpcFifoMod>(Qcom::IPC_FIFO_MOD_HIGH)->m_getMsgType(), Qcom::IpcFifoBase::IPC_FIFO_WRITE_IND);
   EXPECT_EQ(mainProc()->get<IpcFifoMod>(Qcom::IPC_FIFO_MOD_HIGH)->m_getBufLen(), 4);
}
#endif
/**********************************************************************
         End of file:     test_rm_admissioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:47 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     usagara     1.QCOM SSI Phase-1 Intial release
*********************************************************************91*/
