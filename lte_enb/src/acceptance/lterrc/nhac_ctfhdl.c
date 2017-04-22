
/********************************************************************20**

     Name:    RRC  

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_ctfhdl.c 

     Sid:      nhac_ctfhdl.c@@/main/2 - Fri Jul  1 01:13:00 2011
 
     Prg:     yk 

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
using namespace NH_LTERRC_REL11;
#include "nhac_nhu.x"

#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"
#include "nhac_acc_ctf.x"


EXTERN NhAccCb nhAccCb;

#ifdef RRC_PHY_CFG_SUPP

PUBLIC NhAcCtfCfgInfo gCtfCfgInfo[5];

/*
*
*       Fun:   nhAcHdlCtfBndReq
*
*       Desc:  Handler for Bind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCtfBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCtfBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   SpId          spId = 0;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
   Bool matchProc = FALSE;

   TRC2(nhAcHdlCtfBndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCtfBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
   
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTTF, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCTFBNDREQ;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCtfBndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spId --*/
   /*spId = nhAcGetSapIdFromProt(LNH_SAP_TYPE_CTF);*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.ctfInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.ctfInfo.cmInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCtfBndReq --*/


/*
*
*       Fun:   nhAcHdlCtfUbndReq
*
*       Desc:  Unbind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCtfUbndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCtfUbndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   SpId          spId = 0;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
   Bool          matchProc = FALSE;

   TRC2(nhAcHdlCtfUbndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif


   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCtfUbndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTTF, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCTFUBNDREQ;
   
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCtfUbndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   /*spId = nhAcGetSapIdFromProt ( LNH_SAP_TYPE_CTF);*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.ctfInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.ctfInfo.cmInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCtfUbndReq --*/

/*
*
*       Fun:   nhAcHdlCtfCfgReq
*
*       Desc:  RRC Cfg Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCtfCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCtfCfgReq(tcCb, spCb)
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
   CtfCfgReqInfo *cfg;
   U8             idx;
   U16            tIdx;
   U8 storeCfms=TRUE;

   TRC2(nhAcHdlCtfCfgReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCtfCfgReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId = CMXTA_DFLT_PROCID;
   dstProcId = CMXTA_DFLT_PROCID;
   rrcMsg = (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTTF, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCTFCFGREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCtfCfgReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   if(nhAccCb.valChk)
   {
     ret = nhAcCtfValidate(tcCb, spCb, &(rrcMsg->u.ctfInfo.cfgInfo));
     if (ret != ROK)
     {
        CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCtfCfgReq() : CgInfo mismatch\n"));
        RETVALUE(CMXTA_ERR_NOMATCH);
     }
   }
   
   cfg = &(rrcMsg->u.ctfInfo.cfgInfo);
  
    

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"store_tid",&store_tid);
   /*-- free memory, use callback function --*/
   if ( store_tid )
   {
    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "storeCfms",  &(storeCfms));
    if(storeCfms)
    {
      if(cfg->cfgType == CTF_CONFIG)
      {
         if(cfg->u.cfg.cfgElem == CTF_UE_CFG)
         {
           nhAcCtfGetCfgIndx(cfg->u.cfg.u.dedCfg.ueId, &idx, 0);
           gCtfCfgInfo[idx].cellId = cfg->u.cfg.u.dedCfg.cellId;
           gCtfCfgInfo[idx].ueId = cfg->u.cfg.u.dedCfg.ueId;
         } 
         if(cfg->u.cfg.cfgElem == CTF_CELL_CFG)
         {
           nhAcCtfGetCfgIndx(cfg->u.cfg.u.cellCfg.cellId, &idx, 1);
           gCtfCfgInfo[idx].cellId = cfg->u.cfg.u.cellCfg.cellId;
         }
      }
      else if(cfg->cfgType == CTF_RECONFIG)
      {
         if(cfg->u.reCfg.cfgElem == CTF_UE_CFG)
         {
           nhAcCtfGetCfgIndx(cfg->u.reCfg.u.dedRecfg.ueId, &idx, 0);
           gCtfCfgInfo[idx].cellId = cfg->u.reCfg.u.dedRecfg.cellId;
           gCtfCfgInfo[idx].ueId = cfg->u.reCfg.u.dedRecfg.ueId;
         }
         if(cfg->u.reCfg.cfgElem == CTF_CELL_CFG)
         {
            nhAcCtfGetCfgIndx(cfg->u.reCfg.u.cellRecfg.cellId, &idx, 1);
            gCtfCfgInfo[idx].cellId = cfg->u.reCfg.u.cellRecfg.cellId;
         }

      }
      else if(cfg->cfgType == CTF_DELETE)
      {
         if(cfg->u.release.cfgElem == CTF_UE_CFG)
         {
           nhAcCtfGetCfgIndx(cfg->u.release.u.dedRel.ueId, &idx, 0);
           gCtfCfgInfo[idx].cellId = cfg->u.release.u.dedRel.cellId;
           gCtfCfgInfo[idx].ueId = cfg->u.release.u.dedRel.ueId;
         }
         if(cfg->u.release.cfgElem == CTF_CELL_CFG)
         {
            nhAcCtfGetCfgIndx(cfg->u.release.u.cellRel.cellId, &idx, 1);
            gCtfCfgInfo[idx].cellId = cfg->u.release.u.cellRel.cellId;
         }
      }
      tIdx = gCtfCfgInfo[idx].numTrans;
      cmMemcpy((U8*)&(gCtfCfgInfo[idx].ctfTransId[tIdx]),\
            (U8*)&(rrcMsg->u.ctfInfo.transId),sizeof(CtfCfgTransId));
      gCtfCfgInfo[idx].numTrans++;
     }
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   /*spId = nhAcGetSapIdFromProt(LNH_SAP_TYPE_CTF);*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.ctfInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.ctfInfo.cmInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* call utl function to validate further the buffer */
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCtfCfgReq --*/



/*
*
*       Fun:   nhAcHdlCtfBndCfm
*
*       Desc:  CTF Bnd Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCtfBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCtfBndCfm(tcCb, spCb)
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

   TRC2(nhAcHdlCtfBndCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTTF, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);

   suId = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));

   if(CMXTA_ERR_NONE != TfUiCtfBndCfm(&pst, suId, status))
   {
     CMXTA_DBG_ERR((_cmxtap,"TfUiCtfBndCfm  RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCtfBndCfm --*/

/*
*
*       Fun:   nhAcHdlCtfCfgCfm
*
*       Desc:  RRC Cfg Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCtfCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCtfCfgCfm(tcCb, spCb)
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
   CtfCfgTransId transId; 
   U8            stored_tid=0;
   U8            duplicate_tid=0;
   U8            status = 0; 
   Bool          matchProc = FALSE;
   S16           cellId = NHAC_INVALID_CELLID;
   S16           ueId = NHAC_INVALID_UEID;
   U32           intransId; 
   U8            idx;
   U16           tIdx;
   U8            cleanup=TRUE;

   TRC2(nhAcHdlCtfCfgCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTTF, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);


   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "stored_tid",  &(stored_tid));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "duplicate_tid",  &(duplicate_tid));
   
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "ueId",  &(ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "cellId",  &(cellId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cleanup",  &(cleanup));
   if (stored_tid)
   {
      if(ueId != NHAC_INVALID_UEID)
      {
        ret = nhAcCtfGetCfgIndx(ueId, &idx, 0);
        if(ret != ROK)
           CMXTA_DBG_ERR((_cmxtap,"CtfCfgCfm() Ue context not found\n"));
      }
      else if(cellId != NHAC_INVALID_CELLID)
      {
        ret = nhAcCtfGetCfgIndx(cellId, &idx,1);
        if(ret != ROK)
           CMXTA_DBG_ERR((_cmxtap,"CtfCfgCfm() Cell context not found\n"));
      }

      if (gCtfCfgInfo[idx].numTrans)
      {
        tIdx = gCtfCfgInfo[idx].numTrans - 1;
        cmMemcpy((U8*)&transId,
            (U8*)&(gCtfCfgInfo[idx].ctfTransId[tIdx]),sizeof(CtfCfgTransId));
      }

      if(cleanup)
      {
        gCtfCfgInfo[idx].numTrans--;
         if(gCtfCfgInfo[idx].numTrans == 0)
           cmMemset((U8*)&gCtfCfgInfo[idx], 0 , sizeof(NhAcCtfCfgInfo));
      }
   }
   else if (duplicate_tid)
   {
      if(ueId != NHAC_INVALID_UEID)
      {
        ret = nhAcCtfGetCfgIndx(ueId, &idx, 0);
        if(ret != ROK)
           CMXTA_DBG_ERR((_cmxtap,"CtfCfgCfm() Ue context not found\n"));
      }
      else if(cellId != NHAC_INVALID_CELLID)
      {
        ret = nhAcCtfGetCfgIndx(cellId, &idx,1);
        if(ret != ROK)
           CMXTA_DBG_ERR((_cmxtap,"CtfCfgCfm() Cell context not found\n"));
      }
      if (gCtfCfgInfo[idx].numTrans)
      {
        tIdx = gCtfCfgInfo[idx].numTrans - 1;
        cmMemcpy((U8*)&transId, (U8*)&(gCtfCfgInfo[idx].ctfTransId[tIdx]),
           sizeof(CtfCfgTransId));
      }
      if(cleanup)
      { 
         gCtfCfgInfo[idx].numTrans--;
         if(gCtfCfgInfo[idx].numTrans == 0)
           cmMemset((U8*)&gCtfCfgInfo[idx], 0 , sizeof(NhAcCtfCfgInfo));
      }
   }
   else
   {
       cmMemcpy((U8*)&transId, (U8*)&(nhAccCb.ctfTransId[nhAccCb.ctfInd]),
           sizeof(CtfCfgTransId));
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

   if(CMXTA_ERR_NONE != TfUiCtfCfgCfm(&pst, suId, transId,status))
   {
     CMXTA_DBG_ERR((_cmxtap,"TfUiCtfCfgCfm  FAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCtfCfgCfm --*/
 
/*
*
*       Fun:   nhAcHdlCtfUeIdChgReq
*
*       Desc:  RRC UeId Change Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCtfUeIdChgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
)
#else
PUBLIC S16 nhAcHdlCtfUeIdChgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret=ROK;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   U8            use=0;
   U8            cfgType;
   U8            action;
   Bool          matchProc = FALSE;
   SpId          spId = 0;
   U8            idx;
   U8 storeCfms=TRUE;
   U16           tIdx;
   
   TRC2(nhAcHdlCtfUeIdChgReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfUeIdChgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfUeIdChgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCtfUeIdChgReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTTF, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCTFUEIDCHGREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCtfUeIdChgReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.ctfInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.ctfInfo.cmInfo.spId), 2);

      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* initialize before GetVal */
   cfgType = 0;
   action = 0;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cfgType",  &(cfgType));
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8,"use",&use);
  
   if (use)
   {
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "storeCfms",  &(storeCfms));
     if(storeCfms)
     {
        nhAcCtfGetUnusedCfgIdx(&idx);
        tIdx = gCtfCfgInfo[idx].numTrans;
        cmMemcpy((U8*)&(gCtfCfgInfo[idx].ctfTransId[tIdx]),
            (U8*)&(rrcMsg->u.ctfInfo.transId),sizeof(CtfCfgTransId));
        gCtfCfgInfo[idx].ueId = rrcMsg->u.ctfInfo.ueInfo.ueId;
        gCtfCfgInfo[idx].newUeId = rrcMsg->u.ctfInfo.newUeInfo.ueId;
        gCtfCfgInfo[idx].cellId = rrcMsg->u.ctfInfo.ueInfo.cellId;
        gCtfCfgInfo[idx].numTrans++;
     }
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCtfUeIdChgReq --*/

/*
*
*       Fun:   nhAcHdlCtfUeIdChgCfm
*
*       Desc:  UeId Change Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCtfUeIdChgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
)
#else
PUBLIC S16 nhAcHdlCtfUeIdChgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   Pst           pst;
   SuId          suId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   CtfUeInfo     *ueInfo = NULLP;
   CtfCfgTransId transId;
   CmStatus      status;
   U8            use=0;
   U8            duplicate=0;
   Bool          matchProc = FALSE;
   U8            idx;
   S16           ueId=0;
   U8            cleanup= TRUE;
   S16           ret=RFAILED;
   U16            tIdx;
   U8            nullCfgCfm = 0;
   U8            failCfm = 0;

   
   TRC2(nhAcHdlCtfUeIdChgCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfUeIdChgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCtfUeIdChgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTTF, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   CMXTA_ALLOC(&ueInfo, sizeof (CtfUeInfo));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "status",
         &(status.status));
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "use",&use);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "duplicate",&duplicate);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "cleanup",&cleanup);

   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "ueId",  &(ueId));
   if (use)
   {
      if(ueId != -1)
      {
        ret = nhAcCtfGetCfgIndx(ueId, &idx, 0);
        if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CtfUeIdChgCfm() Ue context not found\n"));
      }
      tIdx = gCtfCfgInfo[idx].numTrans-1;
      cmMemcpy((U8*)&transId, (U8*)&(gCtfCfgInfo[idx].ctfTransId[tIdx]),
            sizeof(CtfCfgTransId));
      ueInfo->ueId = gCtfCfgInfo[idx].ueId;
      ueInfo->cellId = gCtfCfgInfo[idx].cellId;
      gCtfCfgInfo[idx].numTrans--;
      if(cleanup)
      cmMemset((U8*)&gCtfCfgInfo[idx], 0, sizeof(NhAcCtfCfgInfo));
   }
   else if (duplicate)
   {
      if(ueId != -1)
      {
        ret = nhAcCtfGetCfgIndx(ueId, &idx, 0);
        if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CtfUeIdChgCfm() Ue context not found\n"));
      }
      tIdx = gCtfCfgInfo[idx].numTrans;
      cmMemcpy((U8*)&transId, (U8*)&(gCtfCfgInfo[idx].ctfTransId[tIdx]),
            sizeof(CtfCfgTransId));
      ueInfo->ueId = gCtfCfgInfo[idx].ueId;
      ueInfo->cellId = gCtfCfgInfo[idx].cellId;
      gCtfCfgInfo[idx].numTrans--;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "invalidTransId",
                          &transId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidUeId",
                          &ueInfo->ueId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidCellId", 
                          &ueInfo->cellId);

      if(cleanup)
      {
        cmMemset((U8*)&gCtfCfgInfo[idx], 0, sizeof(NhAcCtfCfgInfo));
      }
   }
   else
   {
      cmMemcpy((U8*)&transId, (U8*)&(nhAccCb.ctfTransId[nhAccCb.ctfInd]),
            sizeof(CtfCfgTransId));
      ueInfo->ueId = nhAccCb.ctfCfgInfo[nhAccCb.ctfInd].ueId;
      ueInfo->cellId = nhAccCb.ctfCfgInfo[nhAccCb.ctfInd].cellId;
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullCfgCfm",  &(nullCfgCfm));
   if (nullCfgCfm)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(ueInfo, sizeof (CtfUeInfo));
         ueInfo = NULLP;
      }
      else
      {
         CMXTA_FREE(ueInfo, sizeof (CtfUeInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

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

   if (CMXTA_ERR_NONE != TfUiCtfUeIdChgCfm (&pst, suId, transId, ueInfo, status))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCtfUeIdChgCfm() : returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCtfCfgCfm  --*/

#endif /* RRC_PHY_CFG_SUPP */


/**********************************************************************
         End of file:     nhac_ctfhdl.c@@/main/2 - Fri Jul  1 01:13:00 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      yk               1. LTE RRC Initial Release.
/main/2      ---      sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
