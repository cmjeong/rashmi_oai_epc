
/********************************************************************20**

     Name:    RRC  

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_crghdl.c 

     Sid:      nhac_crghdl.c@@/main/3 - Fri Jul  1 01:12:59 2011
 
     Prg:     chebli 

*********************************************************************21*/

/* header include files (.h) */
/* header include files (.h) */
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
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "ctf.h"           /* PHY Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
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
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#include "nhac_asn.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"


EXTERN NhAccCb nhAccCb;
PUBLIC NhAcCrgCfgInfo gCrgCfgInfo[25];

PRIVATE S16 nhAcCrgGetUnusedCfgIdx ARGS(( U8 *idx));
PRIVATE S16 nhAcCrgGetCfgIndx ARGS(( S16 ueId, S16 cellId, U8 *idx, Bool ueOrCell));

/*
*
*       Fun:  nhAcCrgGetUnusedCfgIdx
*
*       Desc:  Returns the index of the first unused CfgInfo
*              structure from the array.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_crghdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nhAcCrgGetUnusedCfgIdx
(
U8 *idx
)
#else
PRIVATE S16 nhAcCrgGetUnusedCfgIdx(idx)
U8 *idx;
#endif
{
   U8 i;
   for(i=0; i<25; i++)
   {
      if(gCrgCfgInfo[i].used == FALSE)
      {
         *idx = i;
         gCrgCfgInfo[i].used = TRUE;
         RETVALUE(ROK);
      }
   }
   RETVALUE(RFAILED);
}


/*
*       Fun: nhAcCrgGetCfgIndx
*
*       Desc:  Returns the index of the first unused CfgInfo
*              structure from the array.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_crghdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nhAcCrgGetCfgIndx
(
S16 ueId,
S16 cellId,
U8 *idx,
Bool ueOrCell
)
#else
PRIVATE S16 nhAcCrgGetCfgIndx(ueId, cellId, idx, ueOrCell)
S16 ueId;
S16 cellId;
U8 *idx;
Bool ueOrCell;
#endif
{
   U8 i;
   Bool found = FALSE;

   if(ueOrCell == 0)
   {
      for(i=0;i<25;i++)
      {
         if (cellId == -1)
         {
            if(gCrgCfgInfo[i].ueId == ueId)
            {
               found = TRUE;
               *idx = i;
                RETVALUE(ROK);
            }
         }
         else
         {
            if((gCrgCfgInfo[i].ueId == ueId) &&
               (gCrgCfgInfo[i].cellId == cellId))
            {
               found = TRUE;
               *idx = i;
                RETVALUE(ROK);
            }
         }
      }
   }
  else
   {
      for(i=0;i<25;i++)
      {
         if(gCrgCfgInfo[i].cellId == cellId)
         {
            found = TRUE;
            *idx = i;
             RETVALUE(ROK);
         }
      }
   }
   if(found == FALSE)
   {
     /*context for this does not exist create one*/
     if(nhAcCrgGetUnusedCfgIdx(idx) == ROK)
        RETVALUE(ROK);
     else
        RETVALUE(RFAILED);
   }

   RETVALUE(RFAILED);
}


/*
*
*       Fun:   nhAcHdlCrgBndReq
*
*       Desc:  Handler for Bind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_crghdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCrgBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCrgBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SpId          spId = 0;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
   Bool matchProc = FALSE;

   TRC2(nhAcHdlCrgBndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCrgBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCrgBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCrgBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
   
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCRGBNDREQ;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCrgBndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spId --*/
   /*spId = nhAcGetSapIdFromProt(LNH_SAP_TYPE_CRG);*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.crgInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.crgInfo.cmInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCrgBndReq --*/


/*
*
*       Fun:   nhAcHdlCrgUbndReq
*
*       Desc:  Unbind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_crghdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCrgUbndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCrgUbndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = 0;
   SpId          spId = 0;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
   Bool          matchProc = FALSE;

   TRC2(nhAcHdlCrgUbndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCrgUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCrgUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif


   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCrgUbndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCRGUBNDREQ;
   
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCrgUbndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   /*spId = nhAcGetSapIdFromProt ( LNH_SAP_TYPE_CRG);*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.crgInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.crgInfo.cmInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCrgUbndReq --*/

/*
*
*       Fun:   nhAcHdlCrgCfgReq
*
*       Desc:  RRC Cfg Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_crghdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCrgCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCrgCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret=ROK;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   U16           store_tid=0;
   Bool          matchProc=FALSE;
   SpId          spId = 0;
   CrgCfgReqInfo *cfg;
   U8             idx;
   U16            tIdx;
   U8 storeCfms=TRUE;

   TRC2(nhAcHdlCrgCfgReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCrgCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCrgCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCrgCfgReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   rrcMsg = (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCRGCFGREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCrgCfgReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if(nhAccCb.valChk)
   {
   ret = nhAcCrgValidate(tcCb, spCb, &(rrcMsg->u.crgInfo.cfgInfo));
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCrgCfgReq() : CgInfo mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   }
   
   cfg = &(rrcMsg->u.crgInfo.cfgInfo);
  
    

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"store_tid",&store_tid);
   /*-- free memory, use callback function --*/
   if ( store_tid )
   {
    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "storeCfms",  &(storeCfms));
    if(storeCfms)
    {
      if(cfg->action == CRG_CONFIG)
      {
         if(cfg->u.cfgInfo.cfgType == CRG_UE_CFG)
         {
           nhAcCrgGetCfgIndx(cfg->u.cfgInfo.u.ueCfg.crnti, 
                             cfg->u.cfgInfo.u.ueCfg.cellId, &idx, 0);
           gCrgCfgInfo[idx].cellId = cfg->u.cfgInfo.u.ueCfg.cellId;
           gCrgCfgInfo[idx].ueId = cfg->u.cfgInfo.u.ueCfg.crnti;
         } 
         if(cfg->u.cfgInfo.cfgType == CRG_LCH_CFG)
         {
            if (cfg->u.cfgInfo.u.lchCfg.crnti != 0)
               nhAcCrgGetCfgIndx(cfg->u.cfgInfo.u.lchCfg.crnti, 
                                 cfg->u.cfgInfo.u.ueCfg.cellId, &idx, 0);
            else
               nhAcCrgGetCfgIndx(cfg->u.cfgInfo.u.lchCfg.cellId,
                                 cfg->u.cfgInfo.u.lchCfg.cellId, &idx, 1);
            gCrgCfgInfo[idx].cellId = cfg->u.cfgInfo.u.lchCfg.cellId;
            gCrgCfgInfo[idx].ueId = cfg->u.cfgInfo.u.lchCfg.crnti;
         }
         if(cfg->u.cfgInfo.cfgType == CRG_CELL_CFG)
         {
            nhAcCrgGetCfgIndx(cfg->u.cfgInfo.u.lchCfg.cellId,
                              cfg->u.cfgInfo.u.cellCfg.cellId, &idx, 1);
            gCrgCfgInfo[idx].cellId = cfg->u.cfgInfo.u.cellCfg.cellId;
         }
      }
      else if(cfg->action == CRG_RECONFIG)
      {
         if(cfg->u.recfgInfo.recfgType == CRG_UE_CFG)
         {
            nhAcCrgGetCfgIndx(cfg->u.recfgInfo.u.ueRecfg.newCrnti, 
                              cfg->u.recfgInfo.u.ueRecfg.cellId, &idx, 0);
            gCrgCfgInfo[idx].cellId = cfg->u.recfgInfo.u.ueRecfg.cellId;
            gCrgCfgInfo[idx].ueId = cfg->u.recfgInfo.u.ueRecfg.newCrnti;
         }
         if(cfg->u.recfgInfo.recfgType == CRG_LCH_CFG)
         {
            nhAcCrgGetCfgIndx(cfg->u.recfgInfo.u.lchRecfg.crnti,
                              cfg->u.recfgInfo.u.lchRecfg.cellId, &idx, 0);
            gCrgCfgInfo[idx].cellId = cfg->u.recfgInfo.u.lchRecfg.cellId;
            gCrgCfgInfo[idx].ueId = cfg->u.recfgInfo.u.lchRecfg.crnti;
         }
         if(cfg->u.recfgInfo.recfgType == CRG_CELL_CFG)
         {
            nhAcCrgGetCfgIndx(cfg->u.recfgInfo.u.cellRecfg.cellId,
                              cfg->u.recfgInfo.u.cellRecfg.cellId, &idx, 1);
            gCrgCfgInfo[idx].cellId = cfg->u.recfgInfo.u.cellRecfg.cellId;
         }

      }
      else if(cfg->action == CRG_DELETE)
      {
         if(cfg->u.delInfo.delType == CRG_UE_CFG)
         {
            nhAcCrgGetCfgIndx(cfg->u.delInfo.u.ueDel.crnti, 
                              cfg->u.delInfo.u.ueDel.cellId, &idx, 0);
            gCrgCfgInfo[idx].cellId = cfg->u.delInfo.u.ueDel.cellId;
            gCrgCfgInfo[idx].ueId = cfg->u.delInfo.u.ueDel.crnti;
         }
         if(cfg->u.delInfo.delType == CRG_LCH_CFG)
         {
            nhAcCrgGetCfgIndx(cfg->u.delInfo.u.lchDel.crnti, 
                              cfg->u.delInfo.u.lchDel.cellId, &idx, 0);
            gCrgCfgInfo[idx].cellId = cfg->u.delInfo.u.lchDel.cellId;
            gCrgCfgInfo[idx].ueId = cfg->u.delInfo.u.lchDel.crnti;
         }
         if(cfg->u.delInfo.delType == CRG_CELL_CFG)
         {
            nhAcCrgGetCfgIndx(cfg->u.delInfo.u.cellDel.cellId,
                              cfg->u.delInfo.u.cellDel.cellId, &idx, 1);
            gCrgCfgInfo[idx].cellId = cfg->u.delInfo.u.cellDel.cellId;
         }
      }
      else if(cfg->action == CRG_RESET)
      {
         /*reset is only for UE configuration*/
         nhAcCrgGetCfgIndx(cfg->u.rstInfo.crnti, cfg->u.rstInfo.cellId, &idx, 0);
         gCrgCfgInfo[idx].cellId = cfg->u.rstInfo.cellId;
         gCrgCfgInfo[idx].ueId = cfg->u.rstInfo.crnti;
      }
      tIdx = gCrgCfgInfo[idx].numTrans;
      cmMemcpy((U8*)&(gCrgCfgInfo[idx].crgTransId[tIdx]),\
            (U8*)&(rrcMsg->u.crgInfo.transId),sizeof(CrgCfgTransId));
      gCrgCfgInfo[idx].numTrans++;
     }
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   /*spId = nhAcGetSapIdFromProt(LNH_SAP_TYPE_CRG);*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.crgInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.crgInfo.cmInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* call utl function to validate further the buffer */
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCrgCfgReq --*/



/*
*
*       Fun:   nhAcHdlCrgBndCfm
*
*       Desc:  CRG Bnd Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_crghdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCrgBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCrgBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   /* S16           ret=ROK; */
   SuId          suId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   U8            status = 0;
   Bool          matchProc = FALSE;

   TRC2(nhAcHdlCrgBndCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCrgBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCrgBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTRG, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);

   suId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));

    if(CMXTA_ERR_NONE != RgUiCrgBndCfm(&pst, suId, status))
    {
       CMXTA_DBG_ERR((_cmxtap,"RgUiCrgBndCfm  RFAILED\n"));
    }

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCrgBndCfm --*/

/*
*
*       Fun:   nhAcHdlCrgCfgCfm
*
*       Desc:  RRC Cfg Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_crghdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCrgCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCrgCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   /* CmXtaMsgQElm  *msg = NULLP; */
   Pst           pst;
    S16           ret=RFAILED;
   SuId          suId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   CrgCfgTransId transId; 
   U8            stored_tid=0;
   U8            duplicate_tid=0;
   U8            status = 0; 
   Bool          matchProc = FALSE;
   S16           cellId=-1;
   S16           ueId=-1;
   U32           intransId; 
   U8            idx;
   U16           tIdx;
   U8            cleanup=TRUE;
   U8            failCfm=0;

   TRC2(nhAcHdlCrgCfgCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCrgCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCrgCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTRG, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);


   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "stored_tid",  &(stored_tid));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "duplicate_tid",  &(duplicate_tid));
   
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "ueId",  &(ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "cellId",  &(cellId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cleanup",  &(cleanup));
   if (stored_tid)
   {
      if(ueId != -1)
      {
      ret = nhAcCrgGetCfgIndx(ueId, cellId, &idx, 0);
      if(ret != ROK)
         CMXTA_DBG_ERR((_cmxtap,"CrgCfgCfm() Ue context not found\n"));
      }
      else if(cellId != -1)
      {
      ret = nhAcCrgGetCfgIndx(ueId, cellId, &idx,1);
      if(ret != ROK)
         CMXTA_DBG_ERR((_cmxtap,"CrgCfgCfm() Cell context not found\n"));
      }
      tIdx = gCrgCfgInfo[idx].numTrans - 1;
      cmMemcpy((U8*)&transId,\
            (U8*)&(gCrgCfgInfo[idx].crgTransId[tIdx]),sizeof(CrgCfgTransId));
      gCrgCfgInfo[idx].numTrans--;
      if(cleanup)
      {
         if(gCrgCfgInfo[idx].numTrans == 0)
           cmMemset((U8*)&gCrgCfgInfo[idx], 0 , sizeof(NhAcCrgCfgInfo));
      }
   }
   else if (duplicate_tid)
   {
      if(ueId != -1)
      {
      ret = nhAcCrgGetCfgIndx(ueId, cellId, &idx, 0);
      if(ret != ROK)
         CMXTA_DBG_ERR((_cmxtap,"CrgCfgCfm() Ue context not found\n"));
      }
      else if(cellId != -1)
      {
      ret = nhAcCrgGetCfgIndx(ueId, cellId, &idx,1);
      if(ret != ROK)
         CMXTA_DBG_ERR((_cmxtap,"CrgCfgCfm() Cell context not found\n"));
      }
      tIdx = gCrgCfgInfo[idx].numTrans - 1;
      cmMemcpy((U8*)&transId, (U8*)&(gCrgCfgInfo[idx].crgTransId[tIdx]),\
           sizeof(CrgCfgTransId));
      if(cleanup)
      {
         if(gCrgCfgInfo[idx].numTrans == 0)
           cmMemset((U8*)&gCrgCfgInfo[idx], 0 , sizeof(NhAcCrgCfgInfo));
      }
   }
   else
   {
      cmMemcpy((U8*)&transId, (U8*)&(nhAccCb.crgTransId[nhAccCb.crgInd]),\
           sizeof(CrgCfgTransId));
       cellId = 0;
       cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "invalidCellId", &cellId);
       if(cellId)
          cmMemcpy((U8*)transId.trans, (CONSTANT U8*)&cellId, sizeof(U16));
       ueId = 0;
       cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "invalidUeId", &ueId);
       if(ueId)
          cmMemcpy((U8*)&transId.trans[2], (CONSTANT U8*)&ueId, sizeof(U16));
       intransId = 0;
       cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "invalidTransId", &intransId);
       if(intransId)
          cmMemcpy((U8*)&transId.trans[4], (CONSTANT U8*)&intransId, sizeof(U32));
   }
   
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "failCfm",
         &(failCfm));

   if (failCfm)
   {
      nhAccCb.makeCfmFail = TRUE;
   }
   else
   {
      nhAccCb.makeCfmFail = FALSE;
   }

    if(CMXTA_ERR_NONE != RgUiCrgCfgCfm(&pst, suId, transId,status))
    {
       CMXTA_DBG_ERR((_cmxtap,"RgUiCrgCfgCfm  FAILED\n"));
    }

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCrgCfgCfm --*/
 



/**********************************************************************
         End of file:     nhac_crghdl.c@@/main/3 - Fri Jul  1 01:12:59 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     chebli           1. LTE RRC Initial Release.
/main/2      ---     ch               1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
