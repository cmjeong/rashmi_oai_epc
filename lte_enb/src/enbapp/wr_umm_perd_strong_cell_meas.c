
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_umm_perd_strong_cell_meas.c

     Prg:      Vmahanka 

*********************************************************************21*/

/* header include files (.h) */
static const char* RLOG_MODULE_NAME="UMM";
static int RLOG_FILE_ID=142;


static int RLOG_MODULE_ID=32;

#include "wr.h"
#include "wr_utils.h"
#include "wr_umm.h"
#include "wr_umm_rrc_msg.h"
#include "wr_umm_trans.h"
#include "wr_umm_sch_msg.h"
#include "wr_umm_l1_msg.h"
#include "wr_ifm_schd.h"
#include "wr_ifm_rrc.h"
#include "nhu_asn.x"
#include "wr_lwr.h"
#include "wr_umm_meas_fun.h"
#include "wr_umm_drx.h"
#include "wr_umm_perd_strong_cell_meas.h"
#include "wr_ifm_son.h"

#ifdef __cplusplus
extern "C" {
#endif

PRIVATE Void wrUmmCreatePerdMeasStrongCellList
(
 WrUmmMeasObjInfo             *measObjInfo,
 NhuMeasResults               *measRprt,
 WrUmmTransCb                 *transCb
);

/** @brief This function is responsible for Handling periodic strong cell measurement report
 * received from UE.
 *
 * @param[in]  transCb pointer to Transaction control block
 * @param[in]  measRprt pointer to Measurement report
 * @return S16
 *       SUCCESS : ROK
 *       FAILED  : RFAILED
 */
 PRIVATE S16 wrUmmPerdStrongCellMeasHdlMeasRpt
 (
  WrUmmTransCb                 *transCb,
  NhuMeasResults               *measRprt
 )
 {
    U8                           measId;
    U8                           measObjId;
    U8                           rptCfgId;
    U32                          recvMeasId;
    WrMeasRptCfgType             rptCfgTyp;
    WrMeasIdNode                 *measIdObj = NULLP;
    WrMeasUeCb                   *measUeCb;
    WrUmmAnrMeasTransInfo        *measTransCb;
    WrUmmMeasObjInfo             measObjInfo;
    WrUeCb                       *ueCb;

    TRC2(wrUmmPerdStrongCellMeasHdlMeasRpt)

    ueCb = transCb->ueCb;
    measUeCb = ueCb->measCfg;
    measTransCb = &transCb->u.anrMeasTrans;

    recvMeasId = measRprt->measId.val;
    if(RFAILED == wrUmmMeasGetMeasIdObj(recvMeasId, &measIdObj, &ueCb->measCfg->measIdLst))
    {
       RLOG0(L_ERROR, "MeasId Object not found from UE Cb");
       RETVALUE(RFAILED);
    }

    measId = measIdObj->measID;
    measObjId = measIdObj->measObjID;
    rptCfgId = measIdObj->rptCfgID;

    /* get measurement object and Type*/
    if(ROK !=  wrUmmMeasFindMeasObjAndTyp(&measObjInfo,measObjId,ueCb->measCfg))
    {
       RLOG0(L_ERROR, "Measurement object not found");
       /*Print error message*/
       RETVALUE(RFAILED);
    }

    if( ROK != wrUmmMeasFindRptCfgTyp(rptCfgId, &rptCfgTyp, &measUeCb->rptCfgLst))
    {
       RLOG0(L_ERROR, "report config object not found");
       RETVALUE(RFAILED);
    }

    switch (rptCfgTyp)
    {
       case WR_UMM_MEAS_STRONG_CELL:
       {
          RLOG_ARG0(L_INFO, DBG_CRNTI, ueCb->crnti,"Received report for "
                "strongest cell");
          /* Store the received strong cell Information */
          wrUmmCreatePerdMeasStrongCellList(&measObjInfo,measRprt, transCb);
          break;
       }
       default:
       RLOG_ARG0(L_ERROR, DBG_CRNTI, ueCb->crnti,"Received invalid report type");
       break;
    }
    RETVALUE(ROK);
 }

/** @brief This function is responsible for Processing RRC message during Periodic Strong Cell
 *  measurement transaction
 *
 *  @param[in]  transCb: pointer to the Transaction control block.
 *  @return S16
 *       SUCCESS : ROK
 *       FAILED  : RFAILED
 */
 
 PRIVATE S16 wrUmmPerdStrongCellMeasPrcRrcMsg
 (
   WrUmmTransCb                 *transCb
 )
 {
    NhuUlDcchMsg                          *ulDcch = &transCb->msg->u.uuIndPdu->sdu.m.ulDcchMsg;
    NhuUL_DCCH_MsgTypc1                   *c1;
    NhuMeasurementReport                  *measRpt;
    NhuMeasurementReportcriticalExtnsc1   *measRptC1;
    NhuMeasResults                        *measRes;

    c1 = &ulDcch->dcchMsg.message.val.c1;
    switch(c1->choice.val)
    {
       case C1_MEASUREMENTREPORT:
       {
          measRpt = &c1->val.measurementReport;
          measRptC1 = &measRpt->criticalExtns.val.c1;
          measRes = &measRptC1->val.measurementReport_r8.measResults;

          wrUmmPerdStrongCellMeasHdlMeasRpt(transCb, measRes);
          break;
       }
       case C1_RRCCONRECFGNCOMPL:
       {
          /* TODO */
          break;
       }
       default:
       {
          RLOG0(L_ERROR, "Invalid Message received");
          RETVALUE(RFAILED);
       }
    }
    RETVALUE(ROK);
 }

/** @brief This function is responsible for processing  Periodic Strong Cell Measurement related 
 * messages which is received from UE.
 *
 *  @param[in]  transCb: pointer to the Transaction control block.
 *  @return S16
 *       SUCCESS : ROK
 *       FAILED  : RFAILED
 *
 */
PUBLIC S16 wrUmmPerdStrongCellMeasProcessor
(
 WrUmmTransCb                 *transCb
)
{
   WrUmmIncMsg                  *msg       = transCb->msg;

   TRC2(wrUmmPerdStrongCellMeasProcessor);

   switch(msg->msgTyp)
   {
      case WR_UMM_UU_IND_PDU:
      {
         wrUmmPerdStrongCellMeasPrcRrcMsg(transCb);
         break;
      }
      default:
      {
         RLOG1(L_ERROR, "Received invalid message[%d]",msg->msgTyp);
         RETVALUE(RFAILED);
      } 
   }

   RETVALUE(ROK);
}


 /** @brief This function is responsible for deallocate transaction related
 * information after transaction complete.
 *
 *  @param[in]  transCb: pointer to the Transaction control block.
 *  @return S16
 *       SUCCESS : ROK
 *       FAILED  : RFAILED
 */
PUBLIC S16 wrUmmPerdStrongCellMeasTransRel
(
 WrUmmTransCb *transCb
)
{
   TRC2(wrUmmPerdStrongCellMeasTransRel)

   wrUmmStopTransTimers(transCb);
   /*transCb->ueCb->anrMeasTransId = 0;*/
   RETVALUE(ROK);
}

/** @brief This function is called when a new Transaction is created for any
 * other procedure. The new transaction is passed to this function and this
 * function determines the next course of action based on the new transaction
 *
 * @param[in]  transCb    : transaction information
 * @param[in]  incTrans   : incoming transaction information
 * @return S16
 *  -#Success : ROK
 *  -#Failure : RFAILED
 */

PUBLIC S16 wrUmmPerdStrongCellMeasNewTransProcessor 
(
 WrUmmTransCb                *transCb,
 WrUmmTransCb                *incTrans
 )
{
   WrUeCb                    *ueCb = transCb->ueCb;

   TRC2(wrUmmPerdStrongCellMeasNewTransProcessor)

   switch(incTrans->transTyp)
   {
      case WR_UMM_RRC_REESTAB_TRANS:
      {
         RLOG0(L_ERROR, "Reestablishment received so closing Periodic "
               "Strong Cell Measurement transaction");
         U8 idVal;
         U8 measIdCnt;
         U8 measId;
         WrMeasUeCb  *measUeCb;

         measUeCb = ueCb->measCfg;
         measIdCnt = transCb->u.perdStrongCellMeasTrans.measTransCfg.addMeasInfo.measIdCnt;

         for(idVal = 0;idVal < measIdCnt; idVal++)
         {
            measId = ueCb->perdStrongCellMeasInfo.measIdLst[idVal];
            wrUmmMeasRmvMeaIdInUeCb(measId, &measUeCb->measIdLst);
            wrUmmMeasSetFreeMeasId(measUeCb, measId);
         }
         
         cmMemset((U8*)&ueCb->perdStrongCellMeasInfo, 0, sizeof(WrUmmMeasAddInfo));
         wrUmmTransComplete(transCb);
         break; 
      }
      case WR_UMM_ERAB_SETUP_TRANS:
      {
         /* TODO */
         break;
      }
   }

   RETVALUE(WR_UMM_TRANS_OK);
}

/** @brief This function is responsible for storing periodic strong cell
 *  measurement report information(pci,rsrp,rsrq) 
 *
 *  @param[in]  measObjInfo: pointer to the measurement object info.
 *  @param[in]  measRprt: pointer to the measurement report info.
 *  @param[in]  transCb: pointer to the Transaction control block.
 *  @return S16
 *       SUCCESS : ROK
 *       FAILED  : RFAILED
 */
PRIVATE Void wrUmmCreatePerdMeasStrongCellList
(
 WrUmmMeasObjInfo             *measObjInfo,
 NhuMeasResults               *measRprt,
 WrUmmTransCb                 *transCb
)
{
   NhuMeasResultLstEUTRA        *measRsultLstEutra;

   TRC2(wrUmmFindNewPciFrmAnrMeasRpt)
   switch(measObjInfo->nrType)
   {
      case WR_UMM_MEAS_INTRA_FREQ:
      {
         measRsultLstEutra = &measRprt->measResultNeighCells.val.measResultLstEUTRA;
         break;
      }
      default:
      {
         RETVOID;
      }
   }


   wrIfmSonUeMeasReportInd(transCb->ueCb, measRprt);

   RETVOID;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
/********************************************************************30**

           End of file:     fc_umm_perd_strong_cell_meas.c@@/main/tenb_main_ccb/1 - Thu Jan 21 17:51:25 2016

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
        ---      Vmahanka         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
