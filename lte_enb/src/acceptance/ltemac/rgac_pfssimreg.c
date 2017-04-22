


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing
  
     File:     rgac_rgureg.c 
  
     Sid:      rgac_pfssimreg.c@@/main/tenb_ca_rib_msm/2 - Thu Apr 28 12:32:43 2016
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_rgureg.c
@brief This file contains the XTA RGU interface leaf command registration and
leaf command mapping to respective handler functions.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_lte.h"        /* Common LTE Defines */
#include "cm_xta.h"        /* Common LTE Defines */
#include "rg_env.h"        /* MAC Environment Defines */
#include "crg.h"           /* CRG Interface defines */
#include "rgr.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_acc.h"  
#include "rgac_rgu.h"        /* MAC error defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_xta.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */
#include "rgr.x"           /* RGR Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"  
#include "rgac_rgu.x"        /* MAC error defines */
#include "rg.h"
#include "rg_env.h"
#include "rgac_acc.x"
#include "rgac_acc.h"
#include "rg_sch_err.h"
#include "rg_sch_inf.h"
#include "rg_sch.h"
#include "rg_sch_cmn.h"
#include "rg_sch_inf.x"
#include "rg_sch.x"


U32 totPfsSimTime;
U32 gSimTti;
U16 tcNo;
PUBLIC LchData lchData[9]; 
PUBLIC Bool    isPfsSim;
char pfsFileName[100];
FILE *pfsSimFileptr;
EXTERN U8 numLc;

EXTERN S16 rgAcHdlPfsSimDStaRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
);
EXTERN S16 rgAcHdlPfsSimCqiRpt
(
 CmXtaTCCb    *tcCb,
 CmXtaSpCb    *spCb
);
EXTERN S16 rgAcStartPfsSim
(
 CmXtaTCCb    *tcCb,
 CmXtaSpCb    *spCb
);

EXTERN S16 rgAcHdlPfsSimLchDataCfg
(
 CmXtaTCCb    *tcCb,
 CmXtaSpCb    *spCb
);

EXTERN S16 rgAcHdlPfsSimPrint
(
 CmXtaTCCb    *tcCb,
 CmXtaSpCb    *spCb
);

EXTERN Void rgSchPfsSimCpyStat
(
   TfuTtiIndInfo      *ttiInd,
   U8                 schInst,
   FILE               *pfsSimFileptr
);
/* Global Array to Verify PFS SIM Start */
Bool startPfsSim;

/* Array to store Instance Id for RGU interface for all configured Cells */
U8 rguInstId[5]={0,1,2,3,4};
U8 tfuInstId[5]={5,5,5,5,5};
U8 tfuSuId[5]={0,1,2,3,4};
PRIVATE CmXtaCmd rgAcPfsSimSimpleCmd[] =
{
   {"tapa.pfssim.dstarsp", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlPfsSimDStaRsp, NULLP,
      "PFS simulator DSta Response"
   },
   {"tapa.rg.pfssim.cqiCfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlPfsSimCqiRpt, NULLP,
      "PFS simulator CQI report"
   },
   {"tapa.rg.pfssim.boUpdt", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlPfsSimDStaRsp, NULLP,
      "PFS Simulator Send BO Update"
   },
   {"tapa.rg.pfssim.startsim", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcStartPfsSim, NULLP,
      "PFS Simulator START"
   },
   {"tapa.rg.pfsSim.lcData.cfg", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlPfsSimLchDataCfg, NULLP,
      "PFS simulator LCH Dat configuration"
   },
   {"tapa.rg.pfsSim.print", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, rgAcHdlPfsSimPrint, NULLP,
      " "
   },
};
 


/**
 * @brief XTA Leaf command registration for PFS Simulator
 *
 * @details
 *
 *     Function : rgAcPfsSimSimpleCmdInit 
 *     
 *     XTA Leaf command registration for PFS simulator 
 *     
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgAcPfsSimSimpleCmdInit
(
Void
)
#else
PUBLIC S16 rgAcPfsSimSimpleCmdInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(rgAcPfsSimSimpleCmdInit);
 
   cnt = sizeof(rgAcPfsSimSimpleCmd)/sizeof(rgAcPfsSimSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, rgAcPfsSimSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* rgAcPfsSimSimpleCmdInit */
 


/**
 * @brief XTA Leaf command De-registration for PFS simulator 
 *
 * @details
 *
 *     Function : rgAcPfsSimSimpleCmdDeInit 
 *     
 *     XTA Leaf command De-registration for PFS simulator
 *     
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 rgAcPfsSimSimpleCmdDeInit
(
Void
)
#else
PUBLIC S16 rgAcPfsSimSimpleCmdDeInit()
#endif
{
   TRC2(rgAcPfsSimSimpleCmdDeInit);
 
   RETVALUE(ROK);
}/* rgAcPfsSimSimpleCmdDeInit --*/

PUBLIC S16 rgAcBldAndSendDStaRsp
(
	RgAcBoUpdtCb *boUpdt, 
	RgAcUeLst    *ueCb
)
{
   RguDStaRspInfo dStaRsp;
   Pst            pst={0};
   SpId           spId = 0;
   S32            remBo = 0;

   dStaRsp.cellId      = boUpdt->cellId;
   dStaRsp.rnti        = rgAccCb.acUeCb[ueCb->ueId].crnti;
   dStaRsp.lcId        = boUpdt->lcId;
   /* Get RemBo from previous StaInd */
   if(gSimTti)
   {
      remBo = ueCb->remData - (rgAccCb.acUeCb[ueCb->ueId].lcs[boUpdt->lcId].schdBo - 15);
   }
   else
   {
      ueCb->remData =0;
   }

   ueCb->sduArrvlTime = SGetTtiCount(); 
   printf("\nUeId=%u LCID %u sduArrvlTime=%lu remData=%ld schdBo=%ld remBo=%d boData=%ld\n",ueCb->ueId, boUpdt->lcId, ueCb->sduArrvlTime, \
         ueCb->remData, rgAccCb.acUeCb[ueCb->ueId].lcs[boUpdt->lcId].schdBo, remBo, boUpdt->boData);
   dStaRsp.boReport.bo = boUpdt->boData + remBo;
   dStaRsp.boReport.oldestSduArrTime = ueCb->sduArrvlTime;
   /* Since Latest Data is sent to MAC, so reset the schdBo */
   rgAccCb.acUeCb[ueCb->ueId].lcs[boUpdt->lcId].schdBo = 0;
   ueCb->remData = dStaRsp.boReport.bo;
   printf("\n TTICount=%d\t Sending BO for UE=%d\t Bodata=%d\n",gSimTti, ueCb->ueId, dStaRsp.boReport.bo);
/*
   cmXtaGetPst(&pst, RGAC_RGU_USERENT, RGAC_RGU_USERINST, RGAC_RGU_PROVENT, 
   instId, RGAC_RGU_SRCPROC, RGAC_RGU_DSTPROC, RGAC_RGU_MATCHPROC); */

   printf("\nTTICount::%d DStaRsp sent for CellId::%u UeId::%u LcId::%u Bo::%ld \n", gSimTti,dStaRsp.cellId, ueCb->ueId, dStaRsp.lcId,  dStaRsp.boReport.bo);
   pst.srcProcId = CMXTA_PROCID_MASTER;  
   pst.dstProcId = CMXTA_PROCID_MASTER;
   pst.srcEnt  =  0; 
   pst.srcInst =  0;
   pst.dstEnt  =  0;
   pst.dstInst = rguInstId[dStaRsp.cellId - 3];

   RgUiRguDStaRsp(&pst, spId, &dStaRsp);
}

PUBLIC S16 rgAcUtlPfsSimSendBoUpdt()
{
   CmLListCp       *lst;
   CmLList         *lnk = NULLP;
   RgAcBoUpdtCb    *boUpdt = NULLP;
   U32             cellIdx, numUe;
   U16             idx;
   U16             currBoIdx = 0;

   currBoIdx = gSimTti % 320;

   for(cellIdx = 0; cellIdx<5; cellIdx++)
   {
      lst = &(rgAccCb.boUpdtLst[cellIdx][currBoIdx]);
      if(lst->count != 0)
      {
         lnk = lst->first;

         while(lnk != NULLP)
         {
            boUpdt = (RgAcBoUpdtCb *)lnk->node;
            for(numUe=0; numUe< boUpdt->numOfUe;numUe++)
            {
               rgAcBldAndSendDStaRsp(boUpdt, &boUpdt->ueLst[numUe]);
            }
            lnk = lnk->next;
            /*remove the Boupdt node once all Ue are served at that index */
            //cmLListDelFrm(&rgAccCb.boUpdtLst[cellIdx][currBoIdx],&boUpdt->boLstEnt);
            cmLListDelFrm(lst,&boUpdt->boLstEnt);
            /*add this node to white list*/

            idx = (gSimTti + boUpdt->ttiInterval)% 320;
            cmLListAdd2Tail(&rgAccCb.boUpdtLst[cellIdx][idx], &boUpdt->boLstEnt);
         }
      }
   } 

}/* End of rgAcUtlPfsSimSendBoUpdt */

PUBLIC U8 rgAcPfsSimGetCqiValue
(
 RgAcCqiCb    *cqiRpt,
 U8           *cqiIdx
)
{
   U8 idx;

   for(idx=0; idx<cqiRpt->numOfPattern; idx++)
   {
      if(gSimTti < cqiRpt->cqiPatternPer[idx])
      {
         if(cqiRpt->cqiVal[idx].currCqiIndx < 
               cqiRpt->cqiVal[idx].numOfCqiVal)
         {
            *cqiIdx = idx;
            RETVALUE(cqiRpt->cqiVal[idx].cqiBits[cqiRpt->cqiVal[idx].currCqiIndx]);
         }
         else
         {
            cqiRpt->cqiVal[idx].currCqiIndx =0;
            *cqiIdx = idx;
            RETVALUE(cqiRpt->cqiVal[idx].cqiBits[cqiRpt->cqiVal[idx].currCqiIndx]);
         }
      }
   }

}
PUBLIC S16 rgAcBldAndSendCqiRpt
(
	RgAcCqiCb    *cqiRpt, 
	U8           ueId,
   U8           *cqiIdx,
   Bool         sndCqi,
   Bool         sndRi
)
{
   TfuDlCqiIndInfo *dlCqiIndInfo;
   Pst            pst={0};
   TfuDlCqiRpt    dlCqiRpt;
   TfuDlCqiPucch  dlCqiPucch;

   //cmAllocEvnt(sizeof(TfuDlCqiIndInfo), 512,(Ptr *)&dlCqiRpti, );
   rgAcUtlAllocEvnt ((Data**)&dlCqiIndInfo, sizeof(TfuDlCqiIndInfo));
   cmLListInit(&(dlCqiIndInfo->dlCqiRptsLst));

   dlCqiIndInfo->cellId = cqiRpt->cellId;
  // cmGetMem(&dlCqiIndInfo->memCp, sizeof(TfuDlCqiRpt),(Ptr*)&dlCqiRpt);
   dlCqiRpt.rnti                 = rgAccCb.acUeCb[ueId].crnti;
   dlCqiRpt.isPucchInfo          = TRUE;

   dlCqiRpt.dlCqiInfo.pucchCqi.cellIdx =  cqiRpt->sCellIdx;
   dlCqiRpt.dlCqiInfo.pucchCqi.mode =  TFU_PUCCH_CQI_MODE10;
   dlCqiRpt.dlCqiInfo.pucchCqi.u.mode10Info.type = TFU_RPT_CQI; 

   if(sndRi)
   {
      dlCqiRpt.dlCqiInfo.pucchCqi.u.mode10Info.type = TFU_RPT_RI; 
      dlCqiRpt.dlCqiInfo.pucchCqi.u.mode10Info.u.ri = 2;
   }   
   else
   {   
      if(sndCqi)
      {
         dlCqiRpt.dlCqiInfo.pucchCqi.u.mode10Info.u.cqi = cqiRpt->cqiVal[0].cqiBits[0];
      }
      else
      {   
         dlCqiRpt.dlCqiInfo.pucchCqi.u.mode10Info.u.cqi = rgAcPfsSimGetCqiValue(cqiRpt, cqiIdx);
      }
   }

   dlCqiRpt.lnk.node = (PTR)&dlCqiRpt;
   cmLListAdd2Tail(&(dlCqiIndInfo->dlCqiRptsLst), &(dlCqiRpt.lnk));


   pst.srcProcId = CMXTA_PROCID_MASTER;  
   pst.selector  = 1;
   pst.dstProcId = CMXTA_PROCID_MASTER;
   pst.srcEnt  =  0; 
   pst.srcInst =  0;
   pst.dstEnt  =  0;
   pst.dstInst = tfuInstId[cqiRpt->cellId - 3];
   RgLiTfuDlCqiInd(&pst, tfuSuId[cqiRpt->cellId - 3], dlCqiIndInfo);
}/* End of rgAcBldAndSendCqiRpt */ 

PUBLIC S16 rgAcUtlPfsSimSendCqiRpt()
{
   CmLListCp       *lst;
   CmLList         *lnk     = NULLP;
   RgAcCqiCb       *rgacCqi = NULLP;
   U32             cellId, numUe;
   U16             idx;
   U8              cqiIdx;
   U16             currCqiIdx = 0;


   currCqiIdx = gSimTti % 320;
   for(cellId = 0; cellId<5; cellId++)
   {
      lst = &(rgAccCb.rgacCqiLst[cellId][currCqiIdx]);
      if(lst->count != 0)
      {
         lnk = lst->first;

         while(lnk != NULLP)
         {
            rgacCqi = (RgAcCqiCb *)lnk->node;
            for(numUe=0; numUe< rgacCqi->numOfUe;numUe++)
            {
               rgAcBldAndSendCqiRpt(rgacCqi, rgacCqi->ueLst[numUe].ueId, &cqiIdx, FALSE, FALSE);
            }
            rgacCqi->cqiVal[cqiIdx].currCqiIndx++;
            /*remove the Boupdt node once all Ue are served at that index */
            //cmLListDelFrm(&rgAccCb.rgacCqiLst[cellId][currCqiIdx],&rgacCqi->cqiEnt);
            lnk = lnk->next;
            cmLListDelFrm(lst,&rgacCqi->cqiEnt);
            /*add this node to white list*/

            /*idx = (gSimTti + rgacCqi->ttiInterval) % 320;*/
            idx = (gSimTti + 80) % 320;
            cmLListAdd2Tail(&rgAccCb.rgacCqiLst[cellId][idx], &rgacCqi->cqiEnt);
         }
      }
   } 

}/* End of rgAcUtlPfsSimSendBoUpdt */


#ifdef ANSI
PRIVATE S16 rgSchSimMultInstTTi
(
 CmXtaTCCb  *tcCb,
 CmXtaSpCb  *spCb,
 U16        numCells
 )
#else
PRIVATE S16 rgSchSimMultInstTTi(tcCb, spCb, numCells)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
U16          numCells;
#endif
{
   S16               ret;
   S16               instIdx;
   U16               cellIdx;
   U16               startCellId = 3;
   TfuTtiIndInfo     ttiInd;
   TfuTtiIndInfo     schTtiInd;
   U8                numInst = 1;


   if (rgAcTfCb.crntTime.subframe > RG_NUM_SUB_FRAMES)
   {
      CMXTA_ZERO(&(rgAcTfCb.crntTime), sizeof(CmLteTimingInfo));
   }
   else
   {
      RGADDTOCRNTTIME(rgAcTfCb.crntTime, rgAcTfCb.crntTime, 1);
   }
   for(cellIdx = 0; cellIdx < numCells; cellIdx++)
   {   
      schTtiInd.cells[cellIdx].schTickDelta  = 0;
      schTtiInd.cells[cellIdx].dlBlankSf     = 0;
      schTtiInd.cells[cellIdx].ulBlankSf     = 0;
      schTtiInd.cells[cellIdx].isDummyTti    = 0;
      schTtiInd.cells[cellIdx].cellId        = startCellId + cellIdx;

      RGCPYTIMEINFO(rgAcTfCb.crntTime, schTtiInd.cells[cellIdx].timingInfo);
      if (schTtiInd.cells[cellIdx].timingInfo.subframe > RG_NUM_SUB_FRAMES)
         schTtiInd.cells[cellIdx].timingInfo.subframe = 0;
   }
   schTtiInd.numCells = numCells;
   rgSCHTomTtiInd(&schTtiInd, 0);
   /*Calling function to copy stats in File */
#ifdef RG_PFS_STATS
  rgSchPfsSimCpyStat(&schTtiInd, 0, pfsSimFileptr);
#endif
   for(instIdx = 0; instIdx < numCells; instIdx++)
   {   
      schTtiInd.numCells = 1;
      schTtiInd.cells[0].cellId        = startCellId + instIdx;
      rgTOMTtiInd(instIdx, &schTtiInd);
   }

}



/**
 * @brief XTA Function initiates the PFS Simulator 
 *
 * @details
 *
 *     Function : rgAcStartPfsSim  
 *     
 *     Issues a PFS Simulator Start  
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcStartPfsSim
(
 CmXtaTCCb    *tcCb,
 CmXtaSpCb    *spCb
)
#else
PUBLIC S16  rgAcStartPfsSim(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst             pst;
   SpId            spId = 0;
   TfuTtiIndInfo   ttiInd;
   TfuTtiIndInfo   schTtiInd;
   RgSchCellCb     *cell; 
   U8              cellIdx;
   U8              testCase;
   char              *str;
   TRC2(rgAcStartPfsSim);
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ttiTime",  &(totPfsSimTime));
   startPfsSim = TRUE;
   for(; gSimTti < totPfsSimTime; gSimTti++)
   {
      if(!pfsSimFileptr)
      {
         strcpy(pfsFileName, "TeNB_PFS_SIM");;
         str= (pfsFileName+strlen(pfsFileName));
         sprintf(str,"%c%d",'_',tcNo);
         tcNo++;
         strcat(pfsFileName, ".csv");
         pfsSimFileptr= fopen(pfsFileName, "w+");
      }

      rgAcUtlPfsSimSendCqiRpt();
      rgAcUtlPfsSimSendBoUpdt();
      /* for all the configured cells send 
       * 1. Send TTI Ind to SCH instance 
       * 2. TTI Ind to all MAC instances */
       rgSchSimMultInstTTi(tcCb, spCb, 5);

   }

#ifdef RG_PFS_STATS
   for(cellIdx = 3; cellIdx < CM_LTE_MAX_CELLS; cellIdx++)
   {
      cell = rgSchCb[0].cells[cellIdx];
      /* Validate the cell */
      if (cell == NULLP) 
      {
         continue;
      }

      rgSCHPfsPrint(cell); 
   }   
#endif

   fclose(pfsSimFileptr);
   pfsSimFileptr=0;
   startPfsSim = FALSE;
   isPfsSim    = FALSE;
   gSimTti     = 0;
   RETVALUE(CMXTA_ERR_NONE);
}/* End of rgAcStartPfsSim */



/**
 * @brief XTA Dedicated Channel Data Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlPfsSimCqiRpt  
 *     
 *     Issues a Ddat request from Dummy RLC to MAC. This handler 
 *     Considers data that tester has provided and also the data
 *     that the test engine has cached from the previous status
 *     response and indication. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlPfsSimCqiRpt
(
 CmXtaTCCb    *tcCb,
 CmXtaSpCb    *spCb
)
#else
PUBLIC S16  rgAcHdlPfsSimCqiRpt(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst             pst;
   SpId            spId = 0;
   CmLteCellId     cellId = RG_ACC_CELLID;
#if 0
   U32             gttiCnt = 0;
   U8              ttiCount = 0;
   U8              currTtiCnt = 0;
#endif
   U8              numOfUe, num;
   CmLteRnti       ueLst[RG_ACC_MAX_UE];
   Txt             cqiPat[256];
   U8              cqiPatternPer[256];
   RgAcCqiCb       *rgacCqi = NULLP;
   U8               idx=0,i;
   U16              tokCount = 0;
   Txt              *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt              *holdSub, *tokSub = NULLP, *tok2 = NULLP; 
   U16              scellIdx;
   Bool             sndCqi = 0;
   Bool             sndRi = 0;
   
   TRC2(rgAcHdlPfsSimCqiRpt);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlPfsSimCqiRpt(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlPfsSimCqiRpt(), tcId (%d)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));	
	cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "sCellIdx", &(scellIdx));	
	cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ttiTime", &(totPfsSimTime));	
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "sndCqi" ,&sndCqi);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "sndRi" ,&sndRi);
   
   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
                (Data **)&rgacCqi, sizeof(RgAcCqiCb)) != ROK)
   {
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
                  CMXTA_SEP_COLON,"cqiPattern", cqiPatternPer, &num);

   rgacCqi->cqiEnt.node = (PTR)rgacCqi;
   rgacCqi->cellId       = cellId;
   rgacCqi->sCellIdx     = scellIdx;
   rgacCqi->numOfPattern = num;
   for(idx=0; idx<num; idx++)
   {
      if(idx)
      {
         rgacCqi->cqiPatternPer[idx] = (rgacCqi->cqiPatternPer[idx-1] + (totPfsSimTime * cqiPatternPer[idx])/100);
      }
      else
      {
         rgacCqi->cqiPatternPer[idx] = (totPfsSimTime * cqiPatternPer[idx])/100;
      }
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "cqiConfigPattern", &(cqiPat));
   for (holdMain = cqiPat, idx = 0; idx < num; idx++, holdMain=NULLP)
   {
      tokMain = (Txt *)strtok_r(holdMain, ";", &tok1);

      if (tokMain == NULLP)
      {
         break;
      }
      /* process each cfmdata */
      for (holdSub = tokMain, i = 0; i < 10; i++, holdSub=NULLP)
      {
         if ((tokSub=strtok_r(holdSub,":",&tok2)) == NULLP)
         {
            break;
         }
         rgacCqi->cqiVal[idx].cqiBits[i]=atoi(tokSub);
      }/* end of for holdMain */ 
      rgacCqi->cqiVal[idx].numOfCqiVal = i;
      rgacCqi->cqiVal[idx].currCqiIndx = 0;
   }
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                  CMXTA_SEP_COLON,"ueLst", ueLst, &numOfUe);
   rgacCqi->numOfUe   = numOfUe;
   for(idx=0; idx<rgacCqi->numOfUe; idx++)
   {
      rgacCqi->ueLst[idx].ueId = ueLst[idx];
   }
   /*
   gttiCnt = gSimTti % 320;
   currTtiCnt= gttiCnt + (ttiCount - gttiCnt % ttiCount); */
    /* Use the [cellId][currTtiCnt] as index to store in the boUpdt */ 
   if(sndCqi || sndRi)
   {
      rgAcBldAndSendCqiRpt(rgacCqi, rgacCqi->ueLst[0].ueId, &idx, sndCqi, sndRi);

      if (SPutSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
               (Data *)rgacCqi, sizeof(RgAcCqiCb)) != ROK)
      {
         RETVALUE(CMXTA_ERR_FATAL);
      }
   }
   else
   {    
      cmLListAdd2Tail(&rgAccCb.rgacCqiLst[cellId-3][0], &rgacCqi->cqiEnt);
   }
 
   RETVALUE(CMXTA_ERR_NONE);
}/* End of rgAcHdlPfsSimCqiRpt */ 

/**
 * @brief XTA Dedicated Channel Data Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlPfsSimCqiRpt
 *     
 *     Issues a CQI report from CL to Scheduler. This handler 
 *     response and indication. 
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlPfsSimDStaRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  rgAcHdlPfsSimDStaRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   SpId            spId = 0;
   U32             gttiCnt = 0;
   U32             boInterv = 0;
   U8              currTtiCnt = 0;
   U8              numOfUe, num;
   CmLteRnti       ueLst[RG_ACC_MAX_UE];
   U16             boUpdt[4];
   RgAcBoUpdtCb    *rgacBoUpdt = NULLP;
   U32             idx =0;
   RgAcUeCb        *ueCb=NULLP;

   TRC2(rgAcHdlPfsSimDStaRsp);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlPfsSimDStaRsp(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlPfsSimDStaRsp(), tcId (%d)\n", tcCb->tcId));
#endif
 
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                  CMXTA_SEP_COLON,"dataRateToSend", boUpdt, &num);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                  CMXTA_SEP_COLON,"ueLst", ueLst, &numOfUe);

   if (SGetSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
                (Data **)&rgacBoUpdt, sizeof(RgAcBoUpdtCb)) != ROK)
   {
      RETVALUE(CMXTA_ERR_FATAL);
   }

   rgacBoUpdt->boLstEnt.node = (PTR)rgacBoUpdt;

   rgacBoUpdt->cellId    = boUpdt[idx++];
   rgacBoUpdt->lcId      = boUpdt[idx++];
   rgacBoUpdt->boData    = boUpdt[idx++];
   boInterv             = boUpdt[idx++];
   rgacBoUpdt->ttiInterval = boInterv;
   
   rgacBoUpdt->numOfUe   = numOfUe;
   for(idx=0; idx<rgacBoUpdt->numOfUe; idx++)
   {
	 rgacBoUpdt->ueLst[idx].ueId = ueLst[idx];
   }

   ueCb = &rgAccCb.acUeCb[rgacBoUpdt->ueLst[0].ueId];
   rgacBoUpdt->boData =  ((ueCb->lcs[rgacBoUpdt->lcId].mbr) * (rgacBoUpdt->ttiInterval))/1000;
   rgacBoUpdt->boData += 100;
   printf("\nUeId::%d GBR=%lu\t MBR=%lu \tTTIInterval=%d\t boData=%ld\n",rgacBoUpdt->ueLst[0].ueId, ueCb->lcs[rgacBoUpdt->lcId].gbr, \
         ueCb->lcs[rgacBoUpdt->lcId].mbr, rgacBoUpdt->ttiInterval ,rgacBoUpdt->boData);

   //gttiCnt = gSimTti % 320;
   //currTtiCnt= (gttiCnt + (boInterv - gttiCnt % boInterv)) % 320;
    /* Use the [cellId][currTtiCnt] as index to store in the boUpdt */ 
   //cmLListAdd2Tail(&rgAccCb.boUpdtLst[rgacBoUpdt->cellId-3][currTtiCnt], &rgacBoUpdt->boLstEnt);
   cmLListAdd2Tail(&rgAccCb.boUpdtLst[rgacBoUpdt->cellId-3][0], &rgacBoUpdt->boLstEnt);
 
   RETVALUE(CMXTA_ERR_NONE);
}

/**
 * @brief XTA Dedicated Channel Data Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlPfsSimLchDataCfg
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlPfsSimLchDataCfg
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  rgAcHdlPfsSimLchDataCfg(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   U8               lcIdx, i; 
   Txt              lchDataStr[256];
   U16              tokCount = 0;
   Txt              *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt              *holdSub, *tokSub = NULLP, *tok2 = NULLP; 

   TRC2(rgAcHdlPfsSimLchDataCfg);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlPfsSimLchDataCfg(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlPfsSimLchDataCfg(), tcId (%d)\n", tcCb->tcId));
#endif
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isPfsSim" ,&isPfsSim);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchData", &(lchDataStr));

   for (holdMain = lchDataStr, lcIdx = 0; lcIdx < 9; lcIdx++, holdMain=NULLP)
   {
      tokMain = (Txt *)strtok_r(holdMain, ";", &tok1);

      if (tokMain == NULLP)
      {
         break;
      }
      /* process each cfmdata */
      for (holdSub = tokMain, i = 0; i < 6; i++, holdSub=NULLP)
      {
         if ((tokSub=strtok_r(holdSub,":",&tok2)) == NULLP)
         {
            break;
         }
         switch(i)
         {
            case 0:
               {  /* LCID */
                  lchData[lcIdx].lcId = atoi(tokSub);
                  break;
               }
            case 1:
               { /* QCI*/ 
                  lchData[lcIdx].qci = atoi(tokSub);
                  break;
               }
            case 2:
               { /* DIR*/ 
                  lchData[lcIdx].dir = atoi(tokSub);
                  break;
               }
            case 3:
               { /* LC TYPE */ 
                  lchData[lcIdx].lcType = atoi(tokSub);
                  break;
               }
            case 4:
               { /* GBR */ 
                  lchData[lcIdx].gbr = atoi(tokSub);
                  break;
               }
            case 5:
               { /* MBR */ 
                  lchData[lcIdx].mbr = atoi(tokSub);
                  break;
               }
            default:
               break;
         }/* end of switch i */
      }/* End of holdSub */
   }/* end of for holdMain */ 

   numLc = lcIdx;

   RETVALUE(CMXTA_ERR_NONE);
} 

/**
 * @brief XTA Dedicated Channel Data Request Handler for RGU interface. 
 *
 * @details
 *
 *     Function : rgAcHdlPfsSimPrint
 *     
 *  @param[in] CmXtaTCCb  *tcCb 
 *  @param[in] CmXtaSpCb  *spCb 
 *  @return  S16
 *      -# CMXTA_ERR_NONE 
 *      -# CMXTA_ERR_INT 
 **/
#ifdef ANSI
PUBLIC S16 rgAcHdlPfsSimPrint
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16  rgAcHdlPfsSimPrint(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   U8          ueId = 0;
   U16         cellId = 0;
   Bool        cfgStart;


   TRC2(rgAcHdlPfsSimPrint);
 
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlPfsSimPrint(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcHdlPfsSimPrint(), tcId (%d)\n", tcCb->tcId));
#endif
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
         &(cellId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueId", 
         &(ueId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "cfgStart" ,&cfgStart);

   if(cfgStart)
   {
      printf("\n\n*******************UE CFG START for UEID(%d), cellId(%d)********************* \n\n", 
            ueId, cellId);
   }
   else
   {   
      printf("\n\n*******************UE CFG END for UEID(%d), cellId(%d)********************* \n\n",
            ueId, cellId);
   }

   /* Resetting the isPfsSim parameter */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isPfsSim" ,&isPfsSim);
    
   RETVALUE(CMXTA_ERR_NONE);
}

/********************************************************************30**

         End of file:     rgac_pfssimreg.c@@/main/tenb_ca_rib_msm/2 - Thu Apr 28 12:32:43 2016

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
/main/1      ---     ns  1. Initial Release.
/main/2      ---     ns  1. LTE MAC 2.1 release
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
*********************************************************************91*/
