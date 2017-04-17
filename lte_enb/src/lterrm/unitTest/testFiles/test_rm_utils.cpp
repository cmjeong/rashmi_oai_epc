#include "gtest/gtest.h"
#include "test_rm.h"

#define WR_RM_SPID 0
void intializeRlog()
{
   rlSetLogPath(".");
   rlSetLogFile("dbglog.txt");
   rlSetNumOfLogFiles(5);
   rlSetLogFileSizeLimit(5);
   rlSetLogLevel(L_MAX_LOG_LEVEL);
   rlSetLogPort(9999);
   rlSetRemoteLoggingFlag(0);
   rlSetCircularBufferSize(100);
   rlEnableDisableCore(1);
   rlSetModuleMask(0);
   rlInitLog(4);

}

S16 sendRmGenCfg()
{
   RmMngmt       rmMngmtObj;
   RmMngmt       *rmMngmt = &rmMngmtObj;
   RmGenCfg      *genCfg=NULLP;
   Pst           pst;

#if 0
   rmMngmt = NULLP;
   /*Allocate memory for the message. This is done since we are using LWLC*/
   SGetSBuf(0, 0, (Data**)&rmMngmt, sizeof(RmMngmt));
   if(NULLP == rmMngmt)
   {
     printf("RM Gen Cfg allocation failure\n");
     RETVALUE(RFAILED);
   }
#endif

   memset(rmMngmt, 0, sizeof(RmMngmt));
   memset(&pst, 0, sizeof(Pst));

   genCfg = &(rmMngmt->t.cfg.s.genCfg);
   genCfg->maxRmuSaps = 2;
   genCfg->lmPst.dstProcId = 0;
   genCfg->lmPst.srcProcId = 0;
   genCfg->lmPst.dstEnt    = ENTSM;
   genCfg->lmPst.dstInst   = 0;
   genCfg->lmPst.srcEnt    = ENTRM;
   genCfg->lmPst.srcInst   = 0;
   genCfg->lmPst.prior     = PRIOR0;
   genCfg->lmPst.route     = RTESPEC;
   genCfg->lmPst.region    = 0;
   genCfg->lmPst.pool      = 0;
   genCfg->lmPst.selector  = 2;

   genCfg->mem.region      = 0;
   genCfg->mem.pool        = 0;
   genCfg->tmrRes          = 10; /*Timer resolution*/ 


   /* Fill Header */
   rmMngmt->hdr.msgType             = TCFG;
   rmMngmt->hdr.msgLen              = 0;
   rmMngmt->hdr.entId.ent           = ENTRM;
   rmMngmt->hdr.entId.inst          = 0;
   rmMngmt->hdr.elmId.elmnt         = STGEN;
   rmMngmt->hdr.seqNmb              = 0;
   rmMngmt->hdr.version             = 0;
   rmMngmt->hdr.transId             = 0;

   rmMngmt->hdr.response.prior      = PRIOR0;
   rmMngmt->hdr.response.route      = RTESPEC;
   rmMngmt->hdr.response.mem.region = 0;
   rmMngmt->hdr.response.mem.pool   = 0;
   rmMngmt->hdr.response.selector   = 2;

   /* Fill Pst */
   pst.selector  = 2;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRM;
   pst.dstProcId = 0;
   pst.srcProcId = 0;
   pst.dstInst   = 0;
   pst.region    = 0;
   pst.pool      = 0;

   printf("RM Gen Cfg Req sent\n");

   /* Send the request to RM */
   RmMiLrmCfgReq(&pst, rmMngmt);

   RETVALUE(ROK);
}

S16 configRmuUSap(SpId spId)
{
   RmMngmt       rmMngmtObj;
   RmMngmt       *rmMngmt = &rmMngmtObj;
   RmUSapCfg     *usap=NULLP;
   Pst           pst;

#if 0
   rmMngmt = NULLP;
   /*Allocate memory for the message. This is done since we are using LWLC*/
   SGetSBuf(0, 0, (Data**)&rmMngmt, sizeof(RmMngmt));
   if(NULLP == rmMngmt)
   {
      printf("[RRM GT] Send RMU SAP Cfg allocation failure\n");
      RETVALUE(RFAILED);
   }
#endif
   memset(rmMngmt, 0, sizeof(RmMngmt));
   memset(&pst, 0, sizeof(Pst));

   usap   = &(rmMngmt->t.cfg.s.rmuSap);

   usap->spId        = spId;
   usap->procId      = 0;
   usap->prior       = PRIOR0;
   usap->route       = RTESPEC;
   usap->selector    = RMU_SEL_TC;
   usap->ent         = ENTWR;
   usap->inst        = 0;
   usap->mem.region  = 0;
   usap->mem.pool    = 0;

   /* Fill Header */
   rmMngmt->hdr.msgType             = TCFG;
   rmMngmt->hdr.msgLen              = 0;
   rmMngmt->hdr.entId.ent           = ENTRM;
   rmMngmt->hdr.entId.inst          = 0;
   rmMngmt->hdr.elmId.elmnt         = STRMUSAP;
   rmMngmt->hdr.seqNmb              = 0;
   rmMngmt->hdr.version             = 0;
   rmMngmt->hdr.transId             = 0;

   rmMngmt->hdr.response.prior      = PRIOR0;
   rmMngmt->hdr.response.route      = RTESPEC;
   rmMngmt->hdr.response.mem.region = 0;
   rmMngmt->hdr.response.mem.pool   = 0;
   rmMngmt->hdr.response.selector   = 1;//SM_SELECTOR_LWLC;

   /* Fill Pst */
   pst.event = EVTLRMCFGREQ;
   pst.selector  = 2;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTRM;
   pst.dstProcId = 0;
   pst.srcProcId = 0;
   pst.dstInst   = 0;
   pst.region    = 0;
   pst.pool      = 0;

   //RLOG0(L_EVENT,"RRM rmu Sap Cfg Req sent");

   /* Send the request to the RRM */
   RmMiLrmCfgReq(&pst, rmMngmt);

   RETVALUE(ROK);
}

S16 sendEnbStatus(U8 status)
{
   Pst pst;
   RmuFsmStatusInd *enbStatusInd;
   SGetSBuf(0, 0, (Data**)&enbStatusInd, sizeof(RmuFsmStatusInd));
   enbStatusInd->enStatusType = RMU_FSM_STATUS_ENB;
   enbStatusInd->u.stEnbStatusInd.bCellId = 1;
   enbStatusInd->u.stEnbStatusInd.enEnbStatus = (RmuEnbStatus)status;

   pst.event = EVTRMUFSMSTAIND;
   RmUiRmuFsmStatusInd(&pst, 0, enbStatusInd);
   RETVALUE(ROK);
}

S16 configRmuLSapCfg (SuId suId, SpId spId)
{
   RmMngmt       rmMngmtObj;
   RmMngmt       *rmMngmt = &rmMngmtObj;
   RmLSapCfg     *lsap=NULLP;
   Pst           pst;

   TRC2(smBuildRmRgmLSapCfg)

#if 0
   rmMngmt = NULLP;
   /*Allocate memory for the message. This is done since we are using LWLC*/
   SGetSBuf(0, 0, (Data**)&rmMngmt, sizeof(RmMngmt));
   if(NULLP == rmMngmt)
   {
     RETVALUE(RFAILED);
   }
#endif
   memset(rmMngmt, 0, sizeof(RmMngmt));
   memset(&pst, 0, sizeof(Pst));

   lsap   = &(rmMngmt->t.cfg.s.rgmSap);

   lsap->suId        = suId;
   lsap->spId        = spId;

   lsap->procId      = 0;
   lsap->prior       = PRIOR0;
   lsap->route       = RTESPEC;
   lsap->selector    = RGM_SEL_TC;
   lsap->ent         = ENTRG;
   lsap->inst        = 0;
   lsap->mem.region  = 0;
   lsap->mem.pool    = 0;

   /* Fill Header */
   rmMngmt->hdr.msgType             = TCFG;
   rmMngmt->hdr.msgLen              = 0;
   rmMngmt->hdr.entId.ent           = ENTRM;
   rmMngmt->hdr.entId.inst          = 0;
   rmMngmt->hdr.elmId.elmnt         = STRGMSAP;
   rmMngmt->hdr.seqNmb              = 0;
   rmMngmt->hdr.version             = 0;
   rmMngmt->hdr.transId             = 0;
  
   rmMngmt->hdr.response.prior      = PRIOR0;
   rmMngmt->hdr.response.route      = RTESPEC;
   rmMngmt->hdr.response.mem.region = 0;
   rmMngmt->hdr.response.mem.pool   = 0;
   rmMngmt->hdr.response.selector   = 1;
   
   /* Fill Pst */
   pst.event = EVTLRMCFGREQ;
   pst.selector  = 1;
   pst.srcProcId = 0;
   pst.srcEnt    = ENTSM;
   pst.dstProcId = 0;
   pst.dstEnt    = ENTRM;
   pst.dstInst   = 0;
   pst.region    = 0;
   pst.pool      = 0;

   //RLOG0(L_EVENT, "RRM rmu Sap Cfg Req sent");

   /* Send the request to the RRM */
   RmMiLrmCfgReq(&pst, rmMngmt);

   RETVALUE(ROK);
}

