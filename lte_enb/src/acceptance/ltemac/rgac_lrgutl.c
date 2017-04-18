


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     rgac_lrgutl.c 
  
     Sid:      rgac_lrgutl.c@@/main/2 - Sat Jul 30 02:20:58 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_lrgutl.c
@brief This file contains the definitions for utility functions required 
by the handlers of XTA LRG interface
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
#include "rgac_acc.h"        /* MAC error defines */
#include "rgac_lrg.h"        /* MAC error defines */
#include <stdlib.h>

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
#include "rgac_acc.x"        /* MAC error defines */
#include "rgac_lrg.x"        /* MAC error defines */

EXTERN Void SResetTtiCount(Void);

/**
 * @brief XTA Utility function to build a Layer manager
 *        Control request primitive. 
 *
 * @details
 *
 *     Function : rgAcUtlLrgCntrlReq
 *     
 *     Forms a Control Request Primitive. 
 *     
 *  @param[out] RgCntrl  *cntrl 
 *  @param[in] U8  action 
 *  @param[in] U8  subAction
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlLrgCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,    /* spCb data structure  */
RgCntrl         *cntrl,
U8              action,
U8              subAction
)
#else
PUBLIC S16 rgAcUtlLrgCntrlReq(tcCb, spCb, cntrl, action, subAction)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
RgCntrl         *cntrl;
U8              action;
U8              subAction;
#endif    
{

   TRC2(rgAcUtlLrgCntrlReq);
   
   cntrl->action = action;
   cntrl->subAction = subAction;

  switch(action)
   {
      case AENA:
         switch(subAction)
         {
            case SATRC:
               {
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, \
                                 "trcLen",  &(cntrl->s.trcLen));
               }
               break;
            case SAUSTA:
               break;
            case SADBG:
               {
                  cntrl->s.rgDbgCntrl.dbgMask = 0xffffffff;
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32 , "dbgMask",
                   &(cntrl->s.rgDbgCntrl.dbgMask));
               }
               break;
         }
         break;
      case ADISIMM:
         switch(subAction)
         {
            case SATRC:
               break;
            case SAUSTA:
               break;
            case SADBG:
               {
                  cntrl->s.rgDbgCntrl.dbgMask = 0xffffffff;
                  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U32 , "dbgMask",
                   &(cntrl->s.rgDbgCntrl.dbgMask));
               }
               break;
         }
         break;
      case ASHUTDOWN:
         SResetTtiCount();
         break;
      case ABND:
      case AUBND:
         cntrl->s.rgSapCntrl.spId = 0;
         cntrl->s.rgSapCntrl.suId = 0;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",
         &(cntrl->s.rgSapCntrl.spId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",
         &(cntrl->s.rgSapCntrl.suId));
         break;
   }
         
   RETVALUE(ROK);
 
}/*-- rgAcUtlLrgCntrlReq --*/

#ifdef LTE_L2_MEAS

/**
 * @brief XTA Utility function to build a Layer manager
 *        L2 Measurement request primitive. 
 *
 * @details
 *
 *     Function : rgAcUtlLrgSchValL2MeasCfm
 *     
 *      validates the L2 Measurement confirm 
 *  @param[in]  CmXtaTCCb  *tcCb   
 *  @param[in]  CmXtaSpCb  *spCb
 *  @param[out] LrgSchMeasCfmInfo *measInfo
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlLrgSchValL2MeasCfm
(
CmXtaTCCb           *tcCb,    /* tcCb data structure  */
CmXtaSpCb           *spCb,    /* spCb data structure  */
LrgSchMeasCfmInfo   *measInfo /* measInfo data structure */
)
#else
PUBLIC S16 rgAcUtlLrgSchValL2MeasCfm(tcCb, spCb, measInfo)
CmXtaTCCb           *tcCb;    /* tcCb data structure  */
CmXtaSpCb           *spCb;    /* spCb data structure  */
LrgSchMeasCfmInfo   *measInfo; /* measInfo data structure */
#endif    
{
   U8          prbPercDl;
   U8          prbPercUl;
   U16         dedPreambles;
   U16         preLowRange;
   U16         preHighRange;
   U8          numDlQci;
   U8          numUlQci;
   U8          numDlActvQci;
   U8          numUlActvQci;
   U32         dlTbCnt;
   U32         ulTbCnt;
   U32         dlTbFaulty;
   U32         ulTbFaulty;
   U8          idx;
   U8          qci[LRG_MAX_QCI_PER_REQ];
   U8          actvUe[LRG_MAX_QCI_PER_REQ];
   CmLteCellId cellId;
   U32         transId;

   TRC2(rgAcUtlLrgSchValidateL2MeasCfm);

   cellId = RG_ACC_CELLID;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));
   if(cellId != measInfo->cellId)
   {
      RETVALUE(RFAILED);
   }
   
   transId = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",
                 &(transId));
   if(transId != measInfo->hdr.transId)
   {
      RETVALUE(RFAILED);
   }

   if(measInfo->measType & LRG_L2MEAS_AVG_PRB_DL)
   {
      prbPercDl = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "prbPercDl",
                     &(prbPercDl));
      if(measInfo->avgPrbDl.prbPerc != prbPercDl)
      {
         RETVALUE(RFAILED);
      }
   }
   if(measInfo->measType & LRG_L2MEAS_AVG_PRB_UL)
   {
      prbPercUl = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "prbPercUl",
                     &(prbPercUl));
      if(measInfo->avgPrbUl.prbPerc != prbPercUl)
      {
         RETVALUE(RFAILED);
      }
   }
   if(measInfo->measType & LRG_L2MEAS_RA_PREAMBLE)
   {
      dedPreambles  = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dedPreambles",
                     &(dedPreambles));
      preLowRange = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "preLowRange",
                     &(preLowRange));
      preHighRange = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "preHighRange",
                     &(preHighRange));
      if((measInfo->raPrmbsCfm.dedPreambles!= dedPreambles) ||
         (measInfo->raPrmbsCfm.randSelPreLowRange!= preLowRange) ||
         (measInfo->raPrmbsCfm.randSelPreHighRange!= preHighRange))
      {
         RETVALUE(RFAILED);
      }
   }
   if(measInfo->measType & LRG_L2MEAS_AVG_PRB_PER_QCI_DL)
   {
      numDlQci = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numDlQci",
                     &(numDlQci));
      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
            "avgPrbPercQciDl", qci, &numDlQci);
      for(idx = 0; idx < numDlQci; idx++)
      {
         if(qci[idx] != measInfo->avgPrbQciDlCfm.prbPercQci[idx].prbPercQci)
         {
            RETVALUE(RFAILED);
         }
      }
   }
   if(measInfo->measType & LRG_L2MEAS_AVG_PRB_PER_QCI_UL)
   {
      numUlQci = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numUlQci",
                     &(numUlQci));
      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
            "avgPrbPercQciUl", qci, &numUlQci);
      for(idx = 0; idx < numUlQci; idx++)
      {
         if(qci[idx] != measInfo->avgPrbQciUlCfm.prbPercQci[idx].prbPercQci)
         {
            RETVALUE(RFAILED);
         }
      }
   }
   if(measInfo->measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL)
   {
      numDlActvQci = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numDlActvQci",
                     &(numDlActvQci));
      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
            "actvUeDl", actvUe, &numDlActvQci);
      for(idx = 0; idx < numDlActvQci; idx++)
      {
         if(actvUe[idx] != measInfo->numUeQciDlCfm.numActvUeQci[idx].numActvUeQci)
         {
            RETVALUE(RFAILED);
         }
      }
   }
   if(measInfo->measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL)
   {
      numUlActvQci = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numUlActvQci",
                     &(numUlActvQci));
      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
            "actvUeUl", actvUe, &numUlActvQci);
      for(idx = 0; idx < numUlActvQci; idx++)
      {
         if(actvUe[idx] != measInfo->numUeQciUlCfm.numActvUeQci[idx].numActvUeQci)
         {
            RETVALUE(RFAILED);
         }
      }
   }
   if(measInfo->measType & LRG_L2MEAS_TB_TRANS_DL_COUNT)
   {
      dlTbCnt = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlTbCnt",
            &(dlTbCnt));
      if(measInfo->tbTransDlTotalCnt != dlTbCnt)
      {
         RETVALUE(RFAILED);
      }
   }  
   if(measInfo->measType & LRG_L2MEAS_TB_TRANS_UL_COUNT)
   {
      ulTbCnt = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ulTbCnt",
            &(ulTbCnt));
      if(measInfo->tbTransUlTotalCnt != ulTbCnt)
      {
         RETVALUE(RFAILED);
      }
   }  
   if(measInfo->measType & LRG_L2MEAS_TB_TRANS_DL_FAULTY_COUNT)
   {
     dlTbFaulty = 0;
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlTbFaulty",
                 &(dlTbFaulty));
     if(measInfo->tbTransDlFaulty != dlTbFaulty)
     {
        RETVALUE(RFAILED);
     }
   }  
   if(measInfo->measType & LRG_L2MEAS_TB_TRANS_UL_FAULTY_COUNT)
   {
     ulTbFaulty = 0;
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ulTbFaulty",
                 &(ulTbFaulty));
     if(measInfo->tbTransUlFaulty != ulTbFaulty)
     {
        RETVALUE(RFAILED);
     }
   }  
   RETVALUE(ROK);
}/*-- rgAcUtlLrgSchValidateL2MeasCfm --*/

/**
 * @brief XTA Utility function to build a Layer manager
 *        L2 Measurement request primitive. 
 *
 * @details
 *
 *     Function : rgAcUtlLrgSchL2MeasReq
 *     
 *     Forms a L2 Measurement Request Primitive. 
 *  @param[in]  CmXtaTCCb  *tcCb   
 *  @param[in]  CmXtaSpCb  *spCb
 *  @param[out] LrgSchMeasReqInfo   *measInfo
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlLrgSchL2MeasReq
(
CmXtaTCCb           *tcCb,    /* tcCb data structure  */
CmXtaSpCb           *spCb,    /* spCb data structure  */
LrgSchMeasReqInfo   *measInfo /* measInfo data structure */
)
#else
PUBLIC S16 rgAcUtlLrgSchL2MeasReq(tcCb, spCb, measInfo)
CmXtaTCCb           *tcCb;    /* tcCb data structure  */
CmXtaSpCb           *spCb;    /* spCb data structure  */
LrgSchMeasReqInfo   *measInfo; /* measInfo data structure */
#endif    
{
  
  U8       idx;
  U8       qci[LRG_MAX_QCI_PER_REQ];
  U8       numQci;
  
  TRC2(rgAcUtlLrgSchL2MeasReq);

  numQci = 0;

  if((measInfo->measType & LRG_L2MEAS_AVG_PRB_PER_QCI_DL))
  {
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numQci",
                    &(measInfo->avgPrbQciDl.numQci));
     cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
            "qci", &(qci), &numQci);
     for(idx = 0; idx < measInfo->avgPrbQciDl.numQci; idx++)
     {
       measInfo->avgPrbQciDl.qci[idx] = qci[idx];
     }
  }
  if((measInfo->measType & LRG_L2MEAS_AVG_PRB_PER_QCI_UL))
  {
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numQci",
                    &(measInfo->avgPrbQciUl.numQci));
     cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
            "qci", &(qci), &numQci);
     for(idx = 0; idx < measInfo->avgPrbQciUl.numQci; idx++)
     {
       measInfo->avgPrbQciUl.qci[idx] = qci[idx];
     }
  }
  if((measInfo->measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL))
  {
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numQci",
                     &(measInfo->nmbActvUeQciDl.numQci));
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sampPrd",
                     &(measInfo->nmbActvUeQciDl.sampPrd));
     cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
            "qci", &(qci), &numQci);
     for(idx = 0; idx < measInfo->nmbActvUeQciDl.numQci; idx++)
     {
       measInfo->nmbActvUeQciDl.qci[idx] = qci[idx];
     }
  }
  if((measInfo->measType & LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL))
  {
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numQci",
                     &(measInfo->nmbActvUeQciUl.numQci));
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sampPrd",
                     &(measInfo->nmbActvUeQciUl.sampPrd));
     cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
            "qci", &(qci), &numQci);
     for(idx = 0; idx < measInfo->nmbActvUeQciUl.numQci; idx++)
     {
       measInfo->nmbActvUeQciUl.qci[idx] = qci[idx];
     }
  }
   
  RETVALUE(ROK);
 
}/*-- rgAcUtlLrgSchL2MeasReq --*/
#endif


/**********************************************************************
 
         End of file:     rgac_lrgutl.c@@/main/2 - Sat Jul 30 02:20:58 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm                1. Initial Release.
/main/2      ---     dvasisht          1. Updated for LTE MAC Release 3.1          
$SID$        ---       rt              1. LTE MAC 4.1 release
*********************************************************************91*/
