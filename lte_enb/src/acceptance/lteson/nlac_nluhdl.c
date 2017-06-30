

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     nlac_nluhdl.c

     Sid:      nlac_nluhdl.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:05:05 2014

     Prg:      subhamay 

*********************************************************************21*/

#include <stdlib.h>        /* for atoi */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "cm_xta.h"
#include "nl.h"
#include <stdlib.h>        /* For atoi function */
#include <string.h>        /* for strlen */
#include "nlu.h"
#include "lnl.h"
#include "nlac_acc.h"
#include "nlac_nlu.h"
/* external headers */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"  
//#include "cm_pasn.x"
#include "lnl.x"
#include "nlu.x"
#include "nlac_acc.x"
#include "nlac_nlu.x"
#include "nlac_lnl.x"

/*
*
*       Fun:   nlAcHdlNluBndReq
*
*       Desc:  Call Handler for NLU Interface binding 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_nluhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlNluBndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlNluBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   SuId         suId;
   SpId         spId;
   U8           coupling;
   Pst          pst; 
   ProcId       srcProcId;
   ProcId       dstProcId;
   S16          ret;
   U8           readSpId;
   TRC2(nlAcHdlNluBndReq);
   
   suId = WR_NL_SUID;
   spId = WR_NL_SPID;
   coupling = 1;


#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   

   /*-- Get the Pst information here from eNB APP to SON --*/
   cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTNL, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event   = EVTNLUBNDREQ;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "spid", &(readSpId));
   suId = WR_NL_SUID;
   spId = readSpId;
   pst.selector = coupling;   
   if(coupling == 1)
   {
      if(CMXTA_ERR_NONE != NlUiNluBndReq(&pst, suId, spId))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluBndReq(): send to SON module FAILED\n"));
      }
   }

   if(coupling == 2)
   {
      if(CMXTA_ERR_NONE != cmPkNluBndReq(&pst, suId, spId))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluBndReq(): pack and send to SON module FAILED\n"));
      }
   }

   RETVALUE(CMXTA_ERR_NONE);

} /* end of nlAcHdlNluBndReq */

/*
*
*       Fun:   nlAcHdlNluBndCfm
*
*       Desc:  Call Handler for NLU Interface bind confimation 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_nluhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlNluBndCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlNluBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt       *cfgCfm;

   TRC2(nlAcHdlNluBndCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluCellCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluCellCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlNluCellCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   nlMsg = (NlAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTWR, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTNLUBNDCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);
   if(cfgCfm->cfm.status != retVal || cfgCfm->cfm.reason != reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
            retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      nlAcUtlNluFreeCb(msg);
      RETVALUE(CMXTA_ERR_INT);

   }
   /*-- free memory, use callback function --*/
   nlAcUtlNluFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);

} /* end of nlAcHdlNluBndCfm */


/*
*
*       Fun:   nlAcBuildEnbOneOneNghNghCellAdd
*
*       Desc:  build neighbor eNodeB one ngh ngh cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildEnbOneOneNghNghCellAdd
(
NluNghCellAddInfo *cellAddInfo,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildEnbOneOneNghNghCellAdd(cellAddInfo, tcCb, spCb)
NluNghCellAddInfo *cellAddInfo;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   NluNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildEnbOneOneNghNghCellAdd);
   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildEnbOneTwoNghNghCellAdd
*
*       Desc:  build neighbor eNodeB two ngh ngh cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildEnbOneTwoNghNghCellAdd
(
NluNghCellAddInfo *cellAddInfo,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildEnbOneTwoNghNghCellAdd(cellAddInfo, tcCb, spCb)
NluNghCellAddInfo *cellAddInfo;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   NluNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildEnbOneTwoNghNghCellAdd);
   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));

   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[1]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_1_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_1_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_1_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcBuildEnbZeroOneNghNghCellAdd
*
*       Desc:  build neighbor eNodeB one ngh ngh cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildEnbZeroOneNghNghCellAdd
(
NluNghCellAddInfo *cellAddInfo,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildEnbZeroOneNghNghCellAdd(cellAddInfo, tcCb, spCb)
NluNghCellAddInfo *cellAddInfo;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   NluNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildEnbZeroOneNghNghCellAdd);
   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_nghNgh_0_cellId", &(nghNghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_0_mcc_0",  &(nghNghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_0_mcc_1",  &(nghNghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_0_mcc_2",  &(nghNghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_0_mnc_0",  &(nghNghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_0_mnc_1",  &(nghNghCellInfo->ecgi.plmn.mnc[1]));
   nghNghCellInfo->ecgi.plmn.numMncDigits = 2;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildEnbZeroTwoNghNghCellAdd
*
*       Desc:  build neighbor eNodeB two ngh ngh cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildEnbZeroTwoNghNghCellAdd
(
NluNghCellAddInfo *cellAddInfo,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildEnbZeroTwoNghNghCellAdd(cellAddInfo, tcCb, spCb)
NluNghCellAddInfo *cellAddInfo;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   NluNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildEnbZeroTwoNghNghCellAdd);
   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_nghNgh_0_cellId", &(nghNghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_0_mcc_0",  &(nghNghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_0_mcc_1",  &(nghNghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_0_mcc_2",  &(nghNghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_0_mnc_0",  &(nghNghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_0_mnc_1",  &(nghNghCellInfo->ecgi.plmn.mnc[1]));
   nghNghCellInfo->ecgi.plmn.numMncDigits = 2;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));

   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[1]);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_nghNgh_1_cellId", &(nghNghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_1_mcc_0",  &(nghNghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_1_mcc_1",  &(nghNghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_1_mcc_2",  &(nghNghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_1_mnc_0",  &(nghNghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghNgh_1_mnc_1",  &(nghNghCellInfo->ecgi.plmn.mnc[1]));
   nghNghCellInfo->ecgi.plmn.numMncDigits = 2;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_1_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_1_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_1_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbOneOneServCellAdd
*
*       Desc:  build neighbor eNodeB one serv cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbOneOneServCellAdd
(
NluNghCellAdd     *cellAdd,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbOneOneServCellAdd(cellAdd, tcCb, spCb)
NluNghCellAdd     *cellAdd;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   NluNghCellAddInfo *cellAddInfo = NULLP;
   NluNghCellInfo    *nghCellInfo = NULLP;

   S16               ret = 0;
   TRC3(nlAcBuildNghEnbOneOneServCellAdd);
   cellAddInfo = &(cellAdd->nghCellAddInfo[0]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_0_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_numNghNgh",  &(cellAddInfo->numNghNgh));

   if(1 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbOneOneNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbOneTwoNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcBuildNghEnbZeroOneServCellAdd
*
*       Desc:  build neighbor eNodeB one serv cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellAdd
(
NluNghCellAdd     *cellAdd,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellAdd(cellAdd, tcCb, spCb)
NluNghCellAdd    *cellAdd;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   NluNghCellAddInfo *cellAddInfo = NULLP;
   NluNghCellInfo    *nghCellInfo = NULLP;

   S16               ret = 0;
   TRC3(nlAcBuildNghEnbZeroOneServCellAdd);
   cellAddInfo = &(cellAdd->nghCellAddInfo[0]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_numNghNgh",  &(cellAddInfo->numNghNgh));

   if(1 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbZeroOneNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbZeroTwoNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbOneTwoServCellCfg
*
*       Desc:  build neighbor eNodeB two serv cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbOneTwoServCellAdd
(
NluNghCellAdd     *cellAdd,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuilNghEnbOneTwoServCellAdd(cellAdd, tcCb, spCb)
NluNghCellAdd     *cellAdd;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   NluNghCellAddInfo *cellAddInfo = NULLP;
   NluNghCellInfo    *nghCellInfo = NULLP;
   NluNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbOneTwoServCellAdd);
   cellAddInfo = &(cellAdd->nghCellAddInfo[0]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_0_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_numNghNgh",  &(cellAddInfo->numNghNgh));

   if(1 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbOneOneNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbOneTwoNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }

   cellAddInfo = &(cellAdd->nghCellAddInfo[1]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_1_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_1_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_1_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_1_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_numNghNgh",  &(cellAddInfo->numNghNgh));
   if(1 == cellAddInfo->numNghNgh)
   {
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn)); 
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[1]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_1_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_1_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_1_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   }
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcBuildNghEnbZeroTwoServCellCfg
*
*       Desc:  build neighbor eNodeB two serv cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbZeroTwoServCellAdd
(
NluNghCellAdd     *cellAdd,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuilNghEnbZeroTwoServCellAdd(cellAdd, tcCb, spCb)
NluNghCellAdd     *cellAdd;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   NluNghCellAddInfo *cellAddInfo = NULLP;
   NluNghCellInfo    *nghCellInfo = NULLP;
   NluNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbZeroTwoServCellAdd);
   cellAddInfo = &(cellAdd->nghCellAddInfo[0]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_numNghNgh",  &(cellAddInfo->numNghNgh));

   if(1 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbZeroOneNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbZeroTwoNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }

   cellAddInfo = &(cellAdd->nghCellAddInfo[1]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_1_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_1_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_1_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_1_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_numNghNgh",  &(cellAddInfo->numNghNgh));
   if(1 == cellAddInfo->numNghNgh)
   {
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn)); 
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[1]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_1_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_1_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_1_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbOneOneServCellDel
*
*       Desc:  build neighbor eNodeB 1 cell delete config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbOneOneServCellDel
(
NluNghCellDel     *cellDel,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbOneOneServCellDel(cellDel, tcCb, spCb)
NluNghCellDel     *cellDel;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbOneOneServCellDel);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_del_0_cellId",  &(cellDel->ecgi[0].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_0",  &(cellDel->ecgi[0].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_1",  &(cellDel->ecgi[0].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_2",  &(cellDel->ecgi[0].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mnc_0",  &(cellDel->ecgi[0].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mnc_1",  &(cellDel->ecgi[0].plmn.mnc[1]));
   cellDel->ecgi[0].plmn.numMncDigits = 2;
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbOneTwoServCellDel
*
*       Desc:  build neighbor eNodeB 2 cell delete config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbOneTwoServCellDel
(
NluNghCellDel     *cellDel,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbOneTwoServCellDel(cellDel, tcCb, spCb)
NluNghCellDel     *cellDel;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbOneTwoServCellDel);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_del_0_cellId",  &(cellDel->ecgi[0].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_0",  &(cellDel->ecgi[0].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_1",  &(cellDel->ecgi[0].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_2",  &(cellDel->ecgi[0].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mnc_0",  &(cellDel->ecgi[0].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mnc_1",  &(cellDel->ecgi[0].plmn.mnc[1]));
   cellDel->ecgi[0].plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_del_1_cellId",  &(cellDel->ecgi[1].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_1_mcc_0",  &(cellDel->ecgi[1].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_1_mcc_1",  &(cellDel->ecgi[1].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_1_mcc_2",  &(cellDel->ecgi[1].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_1_mnc_0",  &(cellDel->ecgi[1].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_1_mnc_1",  &(cellDel->ecgi[1].plmn.mnc[1]));
   cellDel->ecgi[1].plmn.numMncDigits = 2;
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbOneOneServCellMod
*
*       Desc:  build neighbor eNodeB 1 cell modify config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbOneOneServCellMod
(
NluNghCellMod     *cellMod,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbOneOneServCellMod(cellMod, tcCb, spCb)
NluNghCellMod     *cellMod;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   NluNghCellModInfo *cellModInfo = NULLP;
   TRC3(nlAcBuildNghEnbOneOneServCellMod);
   cellModInfo = &(cellMod->nghCellModInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_mod_0_old_cellId",  &(cellModInfo->oldEcgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_old_mcc_0",  &(cellModInfo->oldEcgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_old_mcc_1",  &(cellModInfo->oldEcgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_old_mcc_2",  &(cellModInfo->oldEcgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_old_mnc_0",  &(cellModInfo->oldEcgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_old_mnc_1",  &(cellModInfo->oldEcgi.plmn.mnc[1]));
   cellModInfo->oldEcgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_mod_0_cellId",  &(cellModInfo->nghCellInfo.ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_mcc_0",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_mcc_1",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_mcc_2",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_mnc_0",  &(cellModInfo->nghCellInfo.ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_mnc_1",  &(cellModInfo->nghCellInfo.ecgi.plmn.mnc[1]));
   cellModInfo->nghCellInfo.ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_mod_0_pci",  &(cellModInfo->nghCellInfo.pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_mod_0_dlEarfcn",  &(cellModInfo->nghCellInfo.dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_mod_0_ulEarfcn",  &(cellModInfo->nghCellInfo.ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcBuildNghEnbZeroOneServCellDel
*
*       Desc:  build neighbor eNodeB 1 cell delete config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellDel
(
NluNghCellDel     *cellDel,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellDel(cellDel, tcCb, spCb)
NluNghCellDel     *cellDel;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbZeroOneServCellDel);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_del_0_cellId",  &(cellDel->ecgi[0].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_0",  &(cellDel->ecgi[0].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_1",  &(cellDel->ecgi[0].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_2",  &(cellDel->ecgi[0].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mnc_0",  &(cellDel->ecgi[0].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mnc_1",  &(cellDel->ecgi[0].plmn.mnc[1]));
   cellDel->ecgi[0].plmn.numMncDigits = 2;
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbZeroTwoServCellDel
*
*       Desc:  build neighbor eNodeB 2 cell delete config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbZeroTwoServCellDel
(
NluNghCellDel     *cellDel,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbZeroTwoServCellDel(cellDel, tcCb, spCb)
NluNghCellDel     *cellDel;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbZeroTwoServCellDel);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_del_0_cellId",  &(cellDel->ecgi[0].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_0",  &(cellDel->ecgi[0].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_1",  &(cellDel->ecgi[0].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_2",  &(cellDel->ecgi[0].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mnc_0",  &(cellDel->ecgi[0].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mnc_1",  &(cellDel->ecgi[0].plmn.mnc[1]));
   cellDel->ecgi[0].plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_del_1_cellId",  &(cellDel->ecgi[1].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_1_mcc_0",  &(cellDel->ecgi[1].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_1_mcc_1",  &(cellDel->ecgi[1].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_1_mcc_2",  &(cellDel->ecgi[1].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_1_mnc_0",  &(cellDel->ecgi[1].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_1_mnc_1",  &(cellDel->ecgi[1].plmn.mnc[1]));
   cellDel->ecgi[1].plmn.numMncDigits = 2;
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbZeroOneServCellMod
*
*       Desc:  build neighbor eNodeB 1 cell modify config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellMod
(
NluNghCellMod     *cellMod,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellMod(cellMod, tcCb, spCb)
NluNghCellMod     *cellMod;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   NluNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   NluNghCellModInfo *cellModInfo = NULLP;
   TRC3(nlAcBuildNghEnbZeroOneServCellMod);
   cellModInfo = &(cellMod->nghCellModInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_mod_0_old_cellId",  &(cellModInfo->oldEcgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_old_mcc_0",  &(cellModInfo->oldEcgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_old_mcc_1",  &(cellModInfo->oldEcgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_old_mcc_2",  &(cellModInfo->oldEcgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_old_mnc_0",  &(cellModInfo->oldEcgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_old_mnc_1",  &(cellModInfo->oldEcgi.plmn.mnc[1]));
   cellModInfo->oldEcgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_mod_0_cellId",  &(cellModInfo->nghCellInfo.ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_mcc_0",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_mcc_1",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_mcc_2",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_mnc_0",  &(cellModInfo->nghCellInfo.ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_mnc_1",  &(cellModInfo->nghCellInfo.ecgi.plmn.mnc[1]));
   cellModInfo->nghCellInfo.ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_pci",  &(cellModInfo->nghCellInfo.pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_dlEarfcn",  &(cellModInfo->nghCellInfo.dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_ulEarfcn",  &(cellModInfo->nghCellInfo.ulEarfcn));
   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_numNghNgh",  &(cellModInfo->numNghNgh));
   if(1 == cellModInfo->numNghNgh)
   {
      nghNghCellInfo = &(cellModInfo->nghNghCellInfo[0]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_cellId",  &(nghNghCellInfo->ecgi.cellId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_mcc_0",  &(nghNghCellInfo->ecgi.plmn.mcc[0]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_mcc_1",  &(nghNghCellInfo->ecgi.plmn.mcc[1]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_mcc_2",  &(nghNghCellInfo->ecgi.plmn.mcc[2]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_mnc_0",  &(nghNghCellInfo->ecgi.plmn.mnc[0]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_mnc_1",  &(nghNghCellInfo->ecgi.plmn.mnc[1]));
      nghNghCellInfo->ecgi.plmn.numMncDigits = 2;
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   }
   else if(2 == cellModInfo->numNghNgh)
   {
      nghNghCellInfo = &(cellModInfo->nghNghCellInfo[0]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_cellId",  &(nghNghCellInfo->ecgi.cellId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_mcc_0",  &(nghNghCellInfo->ecgi.plmn.mcc[0]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_mcc_1",  &(nghNghCellInfo->ecgi.plmn.mcc[1]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_mcc_2",  &(nghNghCellInfo->ecgi.plmn.mcc[2]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_mnc_0",  &(nghNghCellInfo->ecgi.plmn.mnc[0]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_mnc_1",  &(nghNghCellInfo->ecgi.plmn.mnc[1]));
      nghNghCellInfo->ecgi.plmn.numMncDigits = 2;
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));

      nghNghCellInfo = &(cellModInfo->nghNghCellInfo[1]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_1_cellId",  &(nghNghCellInfo->ecgi.cellId));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_1_mcc_0",  &(nghNghCellInfo->ecgi.plmn.mcc[0]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_1_mcc_1",  &(nghNghCellInfo->ecgi.plmn.mcc[1]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_1_mcc_2",  &(nghNghCellInfo->ecgi.plmn.mcc[2]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_1_mnc_0",  &(nghNghCellInfo->ecgi.plmn.mnc[0]));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_1_mnc_1",  &(nghNghCellInfo->ecgi.plmn.mnc[1]));
      nghNghCellInfo->ecgi.plmn.numMncDigits = 2;
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_1_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_1_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_nghNgh_1_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   }
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcBuildOneNghEnbCellCfg
*
*       Desc:  build neighbor eNodeB cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildOneNghEnbCellCfg
(
NluNeighborReport    *nghCellCfg,
CmXtaTCCb            *tcCb,
CmXtaSpCb            *spCb
)
#else
PRIVATE S16 nlAcBuildOneNghEnbCellCfg(nghCellCfg, tcCb, spCb)
NluNeighborReport    *nghCellCfg;
CmXtaTCCb            *tcCb;
CmXtaSpCb            *spCb;
#endif
{
   S16               ret = 0;
   NluNghEnbCellCfg *enbCfg = NULLP;
   NluNghCellAdd     *cellAdd = NULLP;
   NluNghCellMod     *cellMod = NULLP; 
   NluNghCellDel     *cellDel = NULLP;
   NluNghCellAddInfo *cellAddInfo = NULLP;
   NluNghCellInfo    *nghCellInfo = NULLP;
   NluNghCellInfo    *nghNghCellInfo = NULLP;
   TRC3(nlAcBuildOneNghEnbCellCfg);
   enbCfg = &(nghCellCfg->nghEnbCellCfg[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0",  &(enbCfg->nghEnbId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_cfgType",  &(enbCfg->nghCellParam.cfgType));
   if(NLU_NGH_ADD == enbCfg->nghCellParam.cfgType)
   {
      cellAdd = &(enbCfg->nghCellParam.u.nghCellAdd);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numAdd",  &(cellAdd->numNgh));
      if(1 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellAdd(cellAdd, tcCb, spCb);
      }
      else if(2 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbZeroTwoServCellAdd(cellAdd, tcCb, spCb);   
      }
   }
   else if(NLU_NGH_DEL == enbCfg->nghCellParam.cfgType)
   {
      cellDel = &(enbCfg->nghCellParam.u.nghCellDel);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numDel",  &(cellDel->numNgh));
      if(1 == cellDel->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellDel(cellDel, tcCb, spCb);
      }
      else if(2 == cellDel->numNgh)
      {
         nlAcBuildNghEnbZeroTwoServCellDel(cellDel, tcCb, spCb);
      }
   }
   else if(NLU_NGH_MOD == enbCfg->nghCellParam.cfgType)
   {
      cellMod = &(enbCfg->nghCellParam.u.nghCellMod);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numMod",  &(cellMod->numNgh));
      if(1 == cellMod->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellMod(cellMod, tcCb, spCb);
      }
      else if(2 == cellMod->numNgh)
      {


      }
   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildTwoNghEnbCellCfg
*
*       Desc:  build neighbor eNodeB cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildTwoNghEnbCellCfg
(
NluNeighborReport    *nghCellCfg,
CmXtaTCCb            *tcCb,
CmXtaSpCb            *spCb
)
#else
PRIVATE S16 nlAcBuildTwoNghEnbCellCfg(nghCellCfg, tcCb, spCb)
NluNeighborReport    *nghCellCfg;
CmXtaTCCb            *tcCb;
CmXtaSpCb            *spCb;
#endif
{
   S16               ret = 0;
   NluNghEnbCellCfg *enbCfg = NULLP;
   NluNghCellAdd     *cellAdd = NULLP;
   NluNghCellMod     *cellMod = NULLP; 
   NluNghCellDel     *cellDel = NULLP;
   NluNghCellAddInfo *cellAddInfo = NULLP;
   NluNghCellInfo    *nghCellInfo = NULLP;
   NluNghCellInfo    *nghNghCellInfo = NULLP;

   TRC3(nlAcBuildTwoNghEnbCellCfg);
   enbCfg = &(nghCellCfg->nghEnbCellCfg[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0",  &(enbCfg->nghEnbId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_cfgType",  &(enbCfg->nghCellParam.cfgType));
   if(LNL_NGH_ADD == enbCfg->nghCellParam.cfgType)
   {
      cellAdd = &(enbCfg->nghCellParam.u.nghCellAdd);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numAdd",  &(cellAdd->numNgh));
      if(1 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellAdd(cellAdd, tcCb, spCb);
      }
      else if(2 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbZeroTwoServCellAdd(cellAdd, tcCb, spCb);   
      }
   }
   else if(LNL_NGH_DEL == enbCfg->nghCellParam.cfgType)
   {
      cellDel = &(enbCfg->nghCellParam.u.nghCellDel);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numDel",  &(cellDel->numNgh));
      if(1 == cellDel->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellDel(cellDel, tcCb, spCb);
      }
      else if(2 == cellDel->numNgh)
      {
         nlAcBuildNghEnbZeroTwoServCellDel(cellDel, tcCb, spCb);
      }
   }
   else if(LNL_NGH_MOD == enbCfg->nghCellParam.cfgType)
   {
      cellMod = &(enbCfg->nghCellParam.u.nghCellMod);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numMod",  &(cellMod->numNgh));
      if(1 == cellMod->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellMod(cellMod, tcCb, spCb);
      }
      else if(2 == cellMod->numNgh)
      {


      }
   }

   enbCfg = &(nghCellCfg->nghEnbCellCfg[1]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1",  &(enbCfg->nghEnbId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_cfgType",  &(enbCfg->nghCellParam.cfgType));
   if(LNL_NGH_ADD == enbCfg->nghCellParam.cfgType)
   {
      cellAdd = &(enbCfg->nghCellParam.u.nghCellAdd);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_numAdd",  &(cellAdd->numNgh));
      if(1 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbOneOneServCellAdd(cellAdd, tcCb, spCb);
      }
      else if(2 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbOneTwoServCellAdd(cellAdd, tcCb, spCb);
      }
   }
   else if(LNL_NGH_DEL == enbCfg->nghCellParam.cfgType)
   {
      cellDel = &(enbCfg->nghCellParam.u.nghCellDel);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_numDel",  &(cellDel->numNgh));
      if(1 == cellDel->numNgh)
      {
         nlAcBuildNghEnbOneOneServCellDel(cellDel, tcCb, spCb);
      }
      else if(2 == cellDel->numNgh)
      {
         nlAcBuildNghEnbOneTwoServCellDel(cellDel, tcCb, spCb);
      }
   }
   else if(LNL_NGH_MOD == enbCfg->nghCellParam.cfgType)
   {
      cellMod = &(enbCfg->nghCellParam.u.nghCellMod);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_numMod",  &(cellMod->numNgh));
      if(1 == cellMod->numNgh)
      {
         nlAcBuildNghEnbOneOneServCellMod(cellMod, tcCb, spCb);
      }
      else if(2 == cellMod->numNgh)
      {


      }
   }

   RETVALUE(CMXTA_ERR_NONE);
}


#ifdef ANCI
PUBLIC S16 nlAcHdlNluBuildNghCellCfg
(
NluNeighborReport *newNgh,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PUBLIC S16 nlAcHdlNluBuildNghCellCfg(newNgh, tcCb, spCb)
NluNeighborReport *newNgh;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16              ret = 0;
   U8               cfgType;
   U8               count;
   U8               numAdd;
   NluNghEnbCellCfg *enbCfg = NULLP;
   NluNghCellAdd    *cellAdd = NULLP;
   NluNghCellAddInfo *cellAddInfo = NULLP;
   NluNghCellInfo    *nghCellInfo = NULLP;
   NluNghCellInfo    *nghNghCellInfo = NULLP;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "msgType",  &(newNgh->msgType));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "cellId",  &(newNgh->servCellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numNghEnb",  &(newNgh->numNghEnb));
   if(1 == newNgh->numNghEnb)
   {
      nlAcBuildOneNghEnbCellCfg(newNgh, tcCb, spCb);
   }
   else if(2 == newNgh->numNghEnb)
   {
      nlAcBuildTwoNghEnbCellCfg(newNgh, tcCb, spCb);
   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcHdlNluNewNeighborReq
*
*       Desc:  Call Handler for NLU new neighbor Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_nluhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlNluNghReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlNluNghReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SpId          spId;             /* service provider SAP identifier */ 
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U8            coupling = 1;
   NluNeighborReport *newNhbr;
   TRC2(nlAcHdlNluNghReq);

   suId = WR_NL_SUID;
   spId = WR_NL_SPID;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluNghReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluNghReq(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   /*-- Get the Pst information here from eNB APP to SON --*/
   cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTNL, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event   = EVTNLUNHBRREQ;
		
   /* Get the CRNTI from XML */

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling",  &(coupling));

   pst.selector = coupling;
   /* Allocate the memory for NluRemoveUeReport msg */

   CMXTA_ALLOC(&newNhbr, sizeof(NluNeighborReport));
	
   if(newNhbr == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluNghReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Fill the data values */
   nlAcHdlNluBuildNghCellCfg(newNhbr, tcCb, spCb);
   /* Send the msg to the SON --*/
   if(1 == coupling)
   {
      if(CMXTA_ERR_NONE != NlUiNluNeighborReq(&pst, suId, newNhbr))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluNghReq(): send to SON failed "));
      }
   }
   else if(2 == coupling)
   {
      if(CMXTA_ERR_NONE != cmPkNluNeighborReq(&pst, suId, newNhbr))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluNghReq(): packing and send to SON failed "));
      }

   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcHdlNluPciModIndCfm
*
*       Desc:  Call Handler for NLU PCI mod Ind Cfm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_nluhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlNluPciModIndCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlNluPciModIndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SpId          spId;             /* service provider SAP identifier */ 
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   U8            coupling = 1;
   NluPciModIndCfm *cfmInd = NULLP;
   TRC2(nlAcHdlNluPciModIndCfm);

   suId = WR_NL_SUID;
   spId = WR_NL_SPID;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluPciModIndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluPciModIndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   /*-- Get the Pst information here from eNB APP to SON --*/
   cmXtaGetPst(&pst, ENTWR, CMXTA_INST_ID, ENTNL, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event   = EVTNLUPCIMODINDCFM;
		
   /* Get the CRNTI from XML */

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling",  &(coupling));

   pst.selector = coupling;
   /* Allocate the memory for pci mod cfm ind  msg */

   CMXTA_ALLOC(&cfmInd, sizeof(NluPciModIndCfm));
	
   if(cfmInd == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluPciModIndCfm(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Fill the data values */
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "cellId",  &(cfmInd->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mcc_0",  &(cfmInd->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mcc_1",  &(cfmInd->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mcc_2",  &(cfmInd->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mnc_0",  &(cfmInd->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mnc_1",  &(cfmInd->ecgi.plmn.mnc[1]));
   cfmInd->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci",  &(cfmInd->pci));
   /* Send the msg to the SON --*/
   if(1 == coupling)
   {
      if(CMXTA_ERR_NONE != NlUiNluPciModIndCfm(&pst, suId, cfmInd))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluPciModIndCfm(): send to SON failed "));
      }
   }
   else if(2 == coupling)
   {
      if(CMXTA_ERR_NONE != cmPkNluPciModIndCfm(&pst, suId, cfmInd))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluPciModIndCfm(): packing and send to SON failed "));
      }
   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*utility function begins*/

#ifdef ANSI
PUBLIC S16 nlAcUtlNluFreeCb
(
CmXtaMsgQElm    *qElm
)
#else
PUBLIC S16 nlAcUtlNluFreeCb(qElm)
CmXtaMsgQElm   *qElm;
#endif
{
   NlAccMsgQElm *nlMsg;

   TRC2(nlAcUtlNluFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "nlAcUtlNluFreeCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   nlMsg = (NlAccMsgQElm *)qElm->data;

   if(nlMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   if (nlMsg != NULLP)
   {
      if(nlMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(nlMsg->mBuf);
      if(nlMsg->u.nluInfo.data != NULLP)
      {
         NLAC_NLUFREEBUF(nlMsg->u.nluInfo.data, nlMsg->u.nluInfo.len);
      }
      CMXTA_FREE(nlMsg, sizeof (NlAccMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/*utility function ends*/
