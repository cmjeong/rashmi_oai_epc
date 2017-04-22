
/********************************************************************20**

     Name:    RRC  

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhAc_ckwhdl.c

     Sid:      nhac_ckwhdl.c@@/main/3 - Fri Jul  1 01:12:56 2011

     Prg:     rer

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

#include "ckw.h"
#include "ckw.x"
#include "nhac_acc.x"
#include <stdlib.h>        /* For atoi function */

PUBLIC NhAcCkwCfgInfo gCkwCfgInf[25];
PRIVATE S16 nhAcCkwGetUnusedCfgIdx ARGS(( U8 *idx));
PRIVATE S16 nhAcCkwGetCfgIndx ARGS(( S16 ueCellid, U8 *idx, Bool ueOrCell));

/*
*
*       Fun:   nhAcHdlCkwBndReq
*
*       Desc:  Handler for Bind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ckwhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCkwBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCkwBndReq(tcCb, spCb)
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

   TRC2(nhAcHdlCkwBndReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwBndReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwBndReq(): tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCkwBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   rrcMsg = (NhAccMsgQElm *)msg->data;

   /*-- Validate if this is the msg for this function --*/
   /* modified acc. to latest prototype */
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);


   /* fill the Event TBD!!! */
   pst.event = CKW_EVT_BND_REQ;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCkwBndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spId --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (spId != rrcMsg->u.ckwInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.ckwInfo.cmInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCkwBndReq --*/


/*
*
*       Fun:  nhAcCkwGetUnusedCfgIdx 
*
*       Desc:  Returns the index of the first unused CfgInfo
*              structure from the array.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ckwhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nhAcCkwGetUnusedCfgIdx 
(
U8 *idx
)
#else
PRIVATE S16 nhAcCkwGetUnusedCfgIdx(idx)
U8 *idx;
#endif
{
   U8 i;
   for(i=0; i<25; i++)
   {
      if(gCkwCfgInf[i].used == FALSE)
      {
         *idx = i;
         gCkwCfgInf[i].used = TRUE;
         RETVALUE(ROK);
      }
   }
   RETVALUE(RFAILED);
}

/*
*       Fun: nhAcCkwGetCfgIndx 
*
*       Desc:  Returns the index of the first unused CfgInfo
*              structure from the array.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ckwhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nhAcCkwGetCfgIndx 
(
S16 ueCellid,
U8 *idx,
Bool ueOrCell
)
#else
PRIVATE S16 nhAcCkwGetCfgIndx(ueCellid, idx, ueOrCell)
S16 ueCellid;
U8  *idx;
Bool ueOrCell;
#endif
{
   U8 i;
   
   if(ueOrCell == 0)
   {
      for(i=0;i<25;i++)
      {
         if(gCkwCfgInf[i].ueId == ueCellid)
         {
            *idx = i;
            RETVALUE(ROK);
         }
      }
   }
   else
   {
      for(i=0;i<25;i++)
      {
         if(gCkwCfgInf[i].cellId == ueCellid)
         {
            *idx = i;
            RETVALUE(ROK);
         }
      }
   }
     
   RETVALUE(RFAILED);
}

/*
*
*       Fun:   nhAcHdlCkwUbndReq
*
*       Desc:  Unbind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ckwhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCkwUbndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCkwUbndReq(tcCb, spCb)
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

   TRC2(nhAcHdlCkwUbndReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));


#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCkwUbndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   pst.event = CKW_EVT_UBND_REQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCkwUbndReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.ckwInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.ckwInfo.cmInfo.spId),2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCkwUbndReq --*/

/*
*
*       Fun:   nhAcHdlCkwCfgReq
*
*       Desc:  RRC Cfg Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhAc_ckwhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCkwCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCkwCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret=ROK;
   SpId          spId=0;
   U8           use=0;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
   U8 idx=0;
   U8 i;
   U8 storeCfms=TRUE;
   
   TRC2(nhAcHdlCkwCfgReq);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCkwCfgReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg = (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif


   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);
   
   pst.event = CKW_EVT_CFG_REQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCkwCfgReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.ckwInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.ckwInfo.cmInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if(nhAccCb.valChk)
   {
      ret = nhAcCkwValidate(tcCb, spCb, &(rrcMsg->u.ckwInfo.cfgInfo));
      if(ret != ROK)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.ckwInfo.cmInfo.spId), 2);
         cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }


   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "use",  &(use));
   if (use)
   {
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "storeCfms",  &(storeCfms));
     if(storeCfms)
     {
        nhAcCkwGetUnusedCfgIdx(&idx);
        gCkwCfgInf[idx].transId = rrcMsg->u.ckwInfo.cfgInfo.transId;
        gCkwCfgInf[idx].ueId = rrcMsg->u.ckwInfo.cfgInfo.ueId;
        gCkwCfgInf[idx].cellId = rrcMsg->u.ckwInfo.cfgInfo.cellId;
        gCkwCfgInf[idx].numEnt = rrcMsg->u.ckwInfo.cfgInfo.numEnt;
        for(i=0;i<gCkwCfgInf[idx].numEnt;i++)
        {
        gCkwCfgInf[idx].rbId[i] = rrcMsg->u.ckwInfo.cfgInfo.entCfg[i].rbId;
        gCkwCfgInf[idx].rbType[i] = rrcMsg->u.ckwInfo.cfgInfo.entCfg[i].rbType;
        gCkwCfgInf[idx].cfgType = rrcMsg->u.ckwInfo.cfgInfo.entCfg[i].cfgType;
        }
     }
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCkwCfgReq --*/

/*
*
*       Fun:   nhAcHdlCkwCfgCfm
*
*       Desc:  RRC Cfg Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ckwhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlCkwCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCkwCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{

   Pst           pst;
   SuId          suId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   CkwCfgCfmInfo *cfmInfo = NULLP;
   U8            use=0;
   U8            change=0;
   U8            duplicate=0;
   U8 idx;
   Txt    msgStr[100];
   Txt    frstWrd[3];
   Txt    secWrd;
   U16    numFailedRb=0;
   U16    len=0;
   U16    rbVal=0;
   U8     rbType=0;
   U8     status = 0;
   S16    ueId = -1;
   S16    cellId = -1;
   U8     i;
   S16 ret=RFAILED;
   U8     cleanup= TRUE;
   U8      nullCfgCfm = 0;
   
   TRC2(nhAcHdlCkwCfgCfm)

   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(msgStr, sizeof(msgStr));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   pst.event = CKW_EVT_CFG_CFM;
   
   CMXTA_ALLOC(&cfmInfo, sizeof (CkwCfgCfmInfo));
   
   cmMemset((U8*)&nhAccCb.sndErrReq, 0 , sizeof(NhAcSndErrReq));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expMacErr",
                  &(nhAccCb.sndErrReq.expMacErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expRlcErr",
                  &(nhAccCb.sndErrReq.expRlcErr));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "expPdcpErr",
                  &(nhAccCb.sndErrReq.expPdcpErr));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "use",  &(use));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "duplicate",  &(duplicate));
   /* Verify */
   /* Store the SRB to be added into addModSrb */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "numFailedRb", &numFailedRb);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "failedRbIdStr", msgStr);

   /* Here get the status of failed RBs from XML. Only send status=failure 
      for only those RBs. Send Status=success for other RBs */
   
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "ueId",  &(ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "cellId", &(cellId));
   if (use)
   {
     if(ueId != -1)
     {
       ret = nhAcCkwGetCfgIndx(ueId, &idx, 0);
       if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CkwCfgCfm() Ue context not found\n"));
     }
     else if(cellId != -1)
     {
       ret = nhAcCkwGetCfgIndx(cellId, &idx, 1);
       if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CkwCfgCfm() Cell context not found\n"));
     }
     cfmInfo->transId = gCkwCfgInf[idx].transId;
     cfmInfo->ueId = gCkwCfgInf[idx].ueId;
     cfmInfo->cellId = gCkwCfgInf[idx].cellId;
     cfmInfo->numEnt = gCkwCfgInf[idx].numEnt;

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "change",
                     &(change));
      /* change is used to simulate lesser number of numEntities in cfgCfm
       * than in cfgReq.
       */ 
      if (change)
         cfmInfo->numEnt--;

      for (i=0; i < cfmInfo->numEnt; i++)
      {
         cfmInfo->entCfgCfm[i].rbId = gCkwCfgInf[idx].rbId[i];
         cfmInfo->entCfgCfm[i].rbType = gCkwCfgInf[idx].rbType[i];
         /* Fill Success by Default */
         cfmInfo->entCfgCfm[i].status.status = CKW_CFG_CFM_OK;
      }
         
      /* fill the failure status of RBs */
      len = 0;
      while(len < strlen(msgStr))
      {
         CMXTA_ZERO(frstWrd, sizeof(frstWrd));
         nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
         len = len + strlen(frstWrd) + 1;
         rbVal = atoi(frstWrd);
         CMXTA_ZERO(&secWrd, sizeof(secWrd));
         nhAcUtlStrToken(&msgStr[len], &secWrd, ',');
         len = len + strlen(&secWrd) + 1;
         rbType = atoi(&secWrd);

         for (i=0; i < cfmInfo->numEnt; i++)
         {
            if ( (cfmInfo->entCfgCfm[i].rbId == rbVal) &&
                  (cfmInfo->entCfgCfm[i].rbType == rbType) )
            {
               /*Failed config */
               cfmInfo->entCfgCfm[i].status.status = CKW_CFG_CFM_NOK;
            }
         }
      }
      if((gCkwCfgInf[idx].cfgType == CKW_CFG_DELETE_UE) ||
      (gCkwCfgInf[idx].cfgType == CKW_CFG_DELETE_CELL))
      {
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status",
               &(status));
         cfmInfo->numEnt = gCkwCfgInf[idx].numEnt;
         cfmInfo->entCfgCfm[0].status.status = status;
         cfmInfo->entCfgCfm[0].rbId = 0;
         cfmInfo->entCfgCfm[0].rbType = 0;
            
      }
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cleanup", &(cleanup));
      if(cleanup)
      {
         cmMemset((U8*)&gCkwCfgInf[idx], 0, sizeof(NhAcCkwCfgInfo));
         gCkwCfgInf[idx].used = FALSE;
      }
   }
   else if (duplicate)
   {
     if(ueId != -1)
     {
       ret = nhAcCkwGetCfgIndx(ueId, &idx, 0);
       if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CkwCfgCfm() Ue context not found\n"));
     }
     else if(cellId != -1)
     {
       ret = nhAcCkwGetCfgIndx(cellId, &idx, 1);
       if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CkwCfgCfm() Cell context not found\n"));
     }
     cfmInfo->transId = gCkwCfgInf[idx].transId;
     cfmInfo->ueId = gCkwCfgInf[idx].ueId;
     cfmInfo->cellId = gCkwCfgInf[idx].cellId;
     cfmInfo->numEnt = gCkwCfgInf[idx].numEnt;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "invalidTransId",
                          &cfmInfo->transId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidUeId",
                          &cfmInfo->ueId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidCellId", 
                             &cfmInfo->cellId);

      for (i=0; i < cfmInfo->numEnt; i++)
      {
         cfmInfo->entCfgCfm[i].rbId = gCkwCfgInf[idx].rbId[i];
         cfmInfo->entCfgCfm[i].rbType = gCkwCfgInf[idx].rbType[i];
         /* Fill Success by Default */
         cfmInfo->entCfgCfm[i].status.status = CKW_CFG_CFM_OK;
      }
      len = 0;
      while(len <= strlen(msgStr))
      {
         CMXTA_ZERO(frstWrd, sizeof(frstWrd));
         nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
         len = len + strlen(frstWrd) + 1;
         rbVal = atoi(frstWrd);
         CMXTA_ZERO(&secWrd, sizeof(secWrd));
         nhAcUtlStrToken(&msgStr[len], &secWrd, ',');
         len = len + strlen(&secWrd) + 1;
         rbType = atoi(&secWrd);

         for (i=0; i < cfmInfo->numEnt; i++)
         {
            if ( (cfmInfo->entCfgCfm[i].rbId == rbVal) &&
                  (cfmInfo->entCfgCfm[i].rbType == rbType) )
            {
               /*Failed config */
               cfmInfo->entCfgCfm[i].status.status = CKW_CFG_CFM_NOK;
            }
         }
      }

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cleanup", &(cleanup));
      if(cleanup)
      {
         cmMemset((U8*)&gCkwCfgInf[idx], 0, sizeof(NhAcCkwCfgInfo));
         gCkwCfgInf[idx].used = FALSE;
      }
   }
   /* Send Invalid TransId */
   else
   {
      cfmInfo->transId = nhAccCb.ckwTransId[nhAccCb.ckwInd];
      cfmInfo->ueId = nhAccCb.ckwCfgInfo[nhAccCb.ckwInd].ueId;
      cfmInfo->cellId = nhAccCb.ckwCfgInfo[nhAccCb.ckwInd].cellId;
      cfmInfo->numEnt = nhAccCb.ckwCfgInfo[nhAccCb.ckwInd].numEnt;

      for (idx=0; idx < cfmInfo->numEnt; idx++)
      {
         cfmInfo->entCfgCfm[idx].rbId = nhAccCb.ckwCfgInfo[nhAccCb.ckwInd].rbId[idx];
         cfmInfo->entCfgCfm[idx].rbType = nhAccCb.ckwCfgInfo[nhAccCb.ckwInd].rbType[idx];
         cfmInfo->entCfgCfm[idx].status.status = CKW_CFG_CFM_NOK;
      }
   }
  
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullCfgCfm",  &(nullCfgCfm));
   if (nullCfgCfm)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(cfmInfo, sizeof(CkwCfgCfmInfo));
         cfmInfo = NULLP;
      }
      else
      {
         CMXTA_FREE(cfmInfo, sizeof(CkwCfgCfmInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   if (CMXTA_ERR_NONE != KwUiCkwCfgCfm (&pst, suId, cfmInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCkwCfgCfm() : returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nhAcHdlCkwBndCfm
*
*       Desc:  CKW Bnd Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ckwhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCkwBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCkwBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst       pst;
   SuId      suId=0;
   ProcId    srcProcId=0;
   ProcId    dstProcId=0;
   U8        status = NHAC_BND_OK;

   TRC2(nhAcHdlCkwBndCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);
   pst.event = CKW_EVT_BND_CFM;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));

   if (CMXTA_ERR_NONE != KwUiCkwBndCfm(&pst, suId, status))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCkwBndCfm() : returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCkwBndCfm --*/


/*
*
*       Fun:   nhAcHdlCkwUeIdChgReq
*
*       Desc:  RRC UE Id change Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhAc_ckwhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCkwUeIdChgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCkwUeIdChgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret=ROK;
   SpId          spId=0;
   U8           use=0;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
   U8 idx;
   U8  storeCfms=TRUE;
   
   TRC2(nhAcHdlCkwUeIdChgReq);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwUeIdChgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwUeIdChgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCkwUeIdChgReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg = (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif


   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);
   
   pst.event = CKW_EVT_UEIDCHG_REQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCkwUeIdChgReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != rrcMsg->u.ckwInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:SpId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.ckwInfo.cmInfo.spId), 2);
      cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "use",  &(use));
   if (use)
   {
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "storeCfms",  &(storeCfms));
      if(storeCfms)
      {
         nhAcCkwGetUnusedCfgIdx(&idx);
         gCkwCfgInf[idx].transId = rrcMsg->u.ckwInfo.transId;
         gCkwCfgInf[idx].ueId = rrcMsg->u.ckwInfo.ueInfo.ueId;
         gCkwCfgInf[idx].newUeId = rrcMsg->u.ckwInfo.newUeInfo.ueId;
         gCkwCfgInf[idx].cellId = rrcMsg->u.ckwInfo.ueInfo.cellId;
         gCkwCfgInf[idx].cfgType = NH_RLC_CFG_UEID_CHNG;
     }
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ *)&(tcCb->msgQ), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCkwUeIdChgReq --*/


/*
*
*       Fun:   nhAcHdlCkwUeIdChgCfm
*
*       Desc:  RRC Cfg Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ckwhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcHdlCkwUeIdChgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCkwUeIdChgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId          suId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   CkwUeInfo     *ueInfo = NULLP;
   U8            use=0;
   U8            duplicate=0;
   CmStatus  status;
   U32       transId=0;
   S16 ueId=-1;
   U8 idx;
   U8 cleanup=TRUE;
   S16 ret=RFAILED;
   U8      nullCfgCfm = 0;
   U8      failCfm = 0;
   
   
   TRC2(nhAcHdlCkwUeIdChgCfm)

   CMXTA_ZERO(&pst, sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwUeIdChgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCkwUeIdChgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   pst.event = CKW_EVT_UEIDCHG_CFM;

   CMXTA_ALLOC(&ueInfo, sizeof (CkwUeInfo));
   
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "use",  &(use));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "duplicate",  &(duplicate));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "status",
            &(status.status));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "ueId", &ueId);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cleanup", &cleanup);
   if (use)
   {
     if(ueId != -1)
     {
       ret = nhAcCkwGetCfgIndx(ueId, &idx, 0);
       if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CkwUeidChgCfm() Ue context not found\n"));
     }
      transId = gCkwCfgInf[idx].transId;
      ueInfo->ueId = gCkwCfgInf[idx].ueId;
      ueInfo->cellId = gCkwCfgInf[idx].cellId;
      if(cleanup)
      cmMemset((U8*)&gCkwCfgInf[idx], 0, sizeof(NhAcCkwCfgInfo));
   }
   else if(duplicate)
   {
     if(ueId != -1)
     {
       ret = nhAcCkwGetCfgIndx(ueId, &idx, 0);
       if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CkwUeidChgCfm() Ue context not found\n"));
     }
      transId = gCkwCfgInf[idx].transId;
      ueInfo->ueId = gCkwCfgInf[idx].ueId;
      ueInfo->cellId = gCkwCfgInf[idx].cellId;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "invalidTransId",
                          &transId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidUeId",
                          &ueInfo->ueId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidCellId", 
                             &ueInfo->cellId);
      
      if(cleanup)
      cmMemset((U8*)&gCkwCfgInf[idx], 0, sizeof(NhAcCkwCfgInfo));
   }
  
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullCfgCfm",  &(nullCfgCfm));
   if (nullCfgCfm)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(ueInfo, sizeof(CkwUeInfo));
         ueInfo = NULLP;
      }
      else
      {
         CMXTA_FREE(ueInfo, sizeof(CkwUeInfo));
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

   if (CMXTA_ERR_NONE != KwUiCkwUeIdChgCfm (&pst, suId, transId, ueInfo, status))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCkwCfgCfm() : returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/**********************************************************************
         End of file:     nhac_ckwhdl.c@@/main/3 - Fri Jul  1 01:12:56 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rer              1. LTE RRC Initial Release.
/main/2      ---      ch               1. RRC Release 2.1.
/main/3      ---      sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
