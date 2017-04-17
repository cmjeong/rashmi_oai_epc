
/********************************************************************20**

     Name:    RRC  

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_cpjhdl.c

     Sid:      nhac_cpjhdl.c@@/main/3 - Fri Jul  1 01:12:57 2011

     Prg:     dm

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
#include "nhac_acc_cpj.x"

#include <stdlib.h>        /* For atoi function */

PUBLIC NhAcCpjCfgInfo gCpjCfgInfo[25];
PRIVATE S16 nhAcCpjGetCfgIndx ARGS(( S16 ueId, S16 cellId, U8 *idx, Bool ueOrCell));
PRIVATE S16 nhAcCpjGetUnusedCfgIdx ARGS(( U8 *idx));
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
PRIVATE S16 nhAcCpjGetUnusedCfgIdx
(
U8 *idx
)
#else
PRIVATE S16 nhAcCpjGetUnusedCfgIdx(idx)
U8 *idx;
#endif
{
   U8 i;
   for(i=0; i<25; i++)
   {
      if(gCpjCfgInfo[i].used == FALSE)
      {
         *idx = i;
         gCpjCfgInfo[i].used = TRUE;
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
PRIVATE S16 nhAcCpjGetCfgIndx
(
S16 ueId,
S16 cellId,
U8 *idx,
Bool ueOrCell
)
#else
PRIVATE S16 nhAcCpjGetCfgIndx(ueId, cellId, idx, ueOrCell)
S16 ueId;
S16 cellId;
U8 *idx;
Bool ueOrCell;
#endif
{
   U8 i;

   if(ueOrCell == 0)
   {
      for(i=0;i<25;i++)
      {
         if (cellId == -1)
         {
            if(gCpjCfgInfo[i].ueId == ueId)
            {
               *idx = i;
               RETVALUE(ROK);
            }
         }
         else
         {
            if ((gCpjCfgInfo[i].ueId == ueId) &&
                (gCpjCfgInfo[i].cellId == cellId))
            {
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
         if(gCpjCfgInfo[i].cellId == cellId)
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
*       Fun:   nhAcHdlCpjBndReq
*
*       Desc:  Handler for Bind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_cpjhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 nhAcHdlCpjBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = 0;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
   Bool          matchProc = FALSE;
   SpId          spId = 0;

   TRC2(nhAcHdlCpjBndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;
#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
   
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCPJBNDREQ;

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCpjBndReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);


   /*-- Set default value & validate for spId --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.cpjInfo.cmInfo.spId)
   {
      CMXTA_DBG_ERR((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.cpjInfo.cmInfo.spId));

      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCpjBndReq  --*/


/*
*
*       Fun:   nhAcHdlCpjUbndReq
*
*       Desc:  Unbind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_cpjhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjUbndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
)
#else
PUBLIC S16 nhAcHdlCpjUbndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   NhAccMsgQElm  *rrcMsg = NULLP;
   CmXtaMsgQElm  *msg = NULLP;
   Pst           pst;
   S16           ret = 0;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;
   Bool          matchProc = FALSE;
   SpId          spId = 0;

   TRC2(nhAcHdlCpjUbndReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjUbndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjUbndReq(), tcId (%d)\n", tcCb->tcId));
#endif


   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjUbndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCPJUBNDREQ;
   
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCpjUbndReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.cpjInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.cpjInfo.cmInfo.spId), 2);

      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCpjUbndReq --*/

/*
*
*       Fun:   nhAcHdlCpjCfgReq
*
*       Desc:  RRC Cfg Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_cpjhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
)
#else
PUBLIC S16 nhAcHdlCpjCfgReq(tcCb, spCb)
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
   U8            i;
   U8  storeCfms=TRUE;
   
   TRC2(nhAcHdlCpjCfgReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjCfgReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCPJCFGREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCpjCfgReq() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.cpjInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.cpjInfo.cmInfo.spId), 2);

      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if(nhAccCb.valChk)
   {
     nhAcUtlCpjVal(tcCb, spCb, &(rrcMsg->u.cpjInfo.cfgInfo));
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
        nhAcCpjGetUnusedCfgIdx(&idx);
        gCpjCfgInfo[idx].cpjTransId = rrcMsg->u.cpjInfo.transId;
        gCpjCfgInfo[idx].ueId = rrcMsg->u.cpjInfo.cfgInfo.ueId;
        gCpjCfgInfo[idx].cellId = rrcMsg->u.cpjInfo.cfgInfo.cellId;
        gCpjCfgInfo[idx].numEnt = rrcMsg->u.cpjInfo.cfgInfo.numEnt;
        for(i=0;i<gCpjCfgInfo[idx].numEnt;i++)
        {
           gCpjCfgInfo[idx].rbType[i] = rrcMsg->u.cpjInfo.cfgInfo.cfgEnt[i].rbType;
           gCpjCfgInfo[idx].rbId[i] = rrcMsg->u.cpjInfo.cfgInfo.cfgEnt[i].rbId;
        }
     }
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCpjCfgReq --*/

/*
*
*       Fun:   nhAcHdlCpjBndCfm
*
*       Desc:  CPJ Bnd Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_cpjhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
)
#else
PUBLIC S16 nhAcHdlCpjBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   Pst           pst;
   SuId          suId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;

   U8            status = CM_BND_OK;
   Bool          matchProc = FALSE;

   TRC2(nhAcHdlCpjBndCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status",  &(status));

 
   PjUiCpjBndCfm(&pst, suId, status); 

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCpjBndCfm  --*/

/*
*
*       Fun:   nhAcHdlCpjCfgCfm
*
*       Desc:  CPJ Cfg Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_cpjhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
)
#else
PUBLIC S16 nhAcHdlCpjCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   Pst           pst;
   SuId          suId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   CpjCfgCfmInfo *cfmInfo = NULLP;
   CmLtePdcpId pdcpId;
   U8            secFail = 0;
   U8 use=0;
   U8 duplicate=0;
   Bool           matchProc = FALSE;
   Txt    msgStr[100];
   Txt    frstWrd[3];
   U16    len=0;
   U16    rbVal=0;
   U8     idx;
   U8     change = 0;
   S16    ueId = -1;
   S16    cellId = -1;
   U8     i;
   S16 ret=RFAILED;
   U8     cleanup = TRUE;
   U8     nullCfgCfm = 0;
   U8     fillWrngRbId = 0;
   U8     cfmFail = 0;

   
   TRC2(nhAcHdlCpjCfgCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));
   cmMemset((U8*)&pdcpId, 0 , sizeof(CmLtePdcpId)); 
   cmMemset((U8*)&msgStr, 0 , 100); 

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "secFail", &(secFail));
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "use",&use);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "duplicate",&duplicate);

 /* Store the SRB to be added into addModPdcpId */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "failedRbIdStr", msgStr);


   CMXTA_ALLOC(&cfmInfo, sizeof (CpjCfgCfmInfo));


   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "ueId",  &(ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "cellId",  &(cellId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U8, "fillWrngRbId",  &(fillWrngRbId));
   /* This need to be modified for handling cfm for MTCH */
   if (use)
   {

      if(ueId != -1)
      {
        ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
       if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CpjCfgCfm() Ue context not found\n"));        
      }
      cfmInfo->transId = gCpjCfgInfo[idx].cpjTransId;
      cfmInfo->ueId    = gCpjCfgInfo[idx].ueId;
      cfmInfo->cellId  = gCpjCfgInfo[idx].cellId;
      cfmInfo->numEnt  = gCpjCfgInfo[idx].numEnt;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "change",
                  &(change));
      /* change is used to simulate lesser number of numEntities in cfgCfm
       * than in cfgReq.
       */ 
      if (change)
         cfmInfo->numEnt--;

      for (i=0; i < cfmInfo->numEnt; i++)
      {
         cfmInfo->cfmEnt[i].rbId = gCpjCfgInfo[idx].rbId[i];
         cfmInfo->cfmEnt[i].rbType = gCpjCfgInfo[idx].rbType[i];
         /* Fill Success by Default */
         cfmInfo->cfmEnt[i].status = CPJ_CFG_CFM_OK;
      }
      if (fillWrngRbId)
      {
         cfmInfo->numEnt++;
         cfmInfo->cfmEnt[i].rbId = fillWrngRbId;
         cfmInfo->cfmEnt[i].rbType = CM_LTE_DRB;
      }
      cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "cleanup",&cleanup);
      if(cleanup)
      cmMemset((U8*)&gCpjCfgInfo[idx], 0, sizeof(NhAcCpjCfgInfo));

      /* Used only for security configuration failure */
      if(secFail)
      {
         cfmInfo->cfmEnt[0].status = CPJ_CFG_CFM_NOK;
      }
      
      /* fill the failure status of RBs */
      len = 0;
      while(len < strlen(msgStr))
      {
         CMXTA_ZERO(frstWrd, sizeof(frstWrd));
         nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
         len = len + strlen(frstWrd) + 1;
         rbVal = atoi(frstWrd);
         for (i=0; i < cfmInfo->numEnt; i++)
         {
            if (cfmInfo->cfmEnt[i].rbId == rbVal)
            {
               /*Failed config */
               cfmInfo->cfmEnt[i].status = CPJ_CFG_CFM_NOK;
            }
         }
      }
   }
   else if (duplicate)
   {
      if(ueId != -1)
      {
        ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
       if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CpjCfgCfm() Ue context not found\n"));
      }
      cfmInfo->transId = gCpjCfgInfo[idx].cpjTransId;
      cfmInfo->ueId    = gCpjCfgInfo[idx].ueId;
      cfmInfo->cellId  = gCpjCfgInfo[idx].cellId;
      cfmInfo->numEnt  = gCpjCfgInfo[idx].numEnt;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "invalidTransId",
                          &cfmInfo->transId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidUeId",
                          &cfmInfo->ueId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidCellId", 
                             &cfmInfo->cellId);

      for (i=0; i < cfmInfo->numEnt; i++)
      {
         cfmInfo->cfmEnt[i].rbId = gCpjCfgInfo[idx].rbId[i];
         cfmInfo->cfmEnt[i].rbType = gCpjCfgInfo[idx].rbType[i];
         /* Fill Success by Default */
         cfmInfo->cfmEnt[i].status = CPJ_CFG_CFM_OK;
      }
      cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "cleanup",&cleanup);
      if(cleanup)
      cmMemset((U8*)&gCpjCfgInfo[idx], 0, sizeof(NhAcCpjCfgInfo));
      len = 0;
      while(len <= strlen(msgStr))
      {
         CMXTA_ZERO(frstWrd, sizeof(frstWrd));
         nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
         len = len + strlen(frstWrd) + 1;
         rbVal = atoi(frstWrd);

         for (i=0; i < cfmInfo->numEnt; i++)
         {
            if (cfmInfo->cfmEnt[i].rbId == rbVal)
            {
               /*Failed config */
               cfmInfo->cfmEnt[i].status = CPJ_CFG_CFM_NOK;
            }
         }
      }
   
   }
   else
   {
      cfmInfo->transId = NHAC_INVALID_TRANSID;
      cfmInfo->ueId = NHAC_INVALID_TRANSID;
      cfmInfo->cellId = NHAC_INVALID_TRANSID;
      cfmInfo->numEnt = nhAccCb.cpjCfgInfo[nhAccCb.cpjInd].numEnt;

      for (idx=0; idx < cfmInfo->numEnt; idx++)
      {
         cfmInfo->cfmEnt[idx].rbId = nhAccCb.cpjCfgInfo[nhAccCb.cpjInd].rbId[idx];
         cfmInfo->cfmEnt[idx].rbType = nhAccCb.cpjCfgInfo[nhAccCb.cpjInd].rbType[idx];
         cfmInfo->cfmEnt[idx].status = CPJ_CFG_CFM_NOK;
      }
   
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullCfgCfm",  &(nullCfgCfm));
   if (nullCfgCfm)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(cfmInfo, sizeof(CpjCfgCfmInfo));
         cfmInfo = NULLP;
      }
      else
      {
         CMXTA_FREE(cfmInfo, sizeof(CpjCfgCfmInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cfmFail",
                                                            &cfmFail);

   if (cfmFail)
   {
      nhAccCb.makeCfmFail = TRUE;
   }
   else
   {
      nhAccCb.makeCfmFail = FALSE;
   }


   if (CMXTA_ERR_NONE != PjUiCpjCfgCfm (&pst, suId, cfmInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjCfgCfm() : returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCpjCfgCfm  --*/


/*
*
*       Fun:   nhAcHdlCpjUeIdChgReq
*
*       Desc:  RRC Cfg Req
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_cpjhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjUeIdChgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
)
#else
PUBLIC S16 nhAcHdlCpjUeIdChgReq(tcCb, spCb)
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
   
   TRC2(nhAcHdlCpjUeIdChgReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjUeIdChgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjUeIdChgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjUeIdChgReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCPJUEIDCHGREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCpjUeIdChgReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.cpjInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.cpjInfo.cmInfo.spId), 2);

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
     nhAcCpjGetUnusedCfgIdx(&idx);
     gCpjCfgInfo[idx].cpjTransId = rrcMsg->u.cpjInfo.transId;
     gCpjCfgInfo[idx].ueId = rrcMsg->u.cpjInfo.ueInfo.ueId;
     gCpjCfgInfo[idx].newUeId = rrcMsg->u.cpjInfo.newUeInfo.ueId;
     gCpjCfgInfo[idx].cellId = rrcMsg->u.cpjInfo.ueInfo.cellId;
     }
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCpjUeIdChgReq --*/

/*
*
*       Fun:   nhAcHdlCpjUeIdChgCfm
*
*       Desc:  CPJ Cfg Cfm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_cpjhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjUeIdChgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
)
#else
PUBLIC S16 nhAcHdlCpjUeIdChgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   Pst           pst;
   SuId          suId=0;
   ProcId        srcProcId=0;
   ProcId        dstProcId=0;
   CpjUeInfo     *ueInfo = NULLP;
   U32           transId;
   CmStatus      status;
   U8            use=0;
   U8            duplicate=0;
   Bool          matchProc = FALSE;
   U8            idx;
   S16           ueId=-1;
   S16           cellId=-1;
   U8            cleanup= TRUE;
   S16           ret=RFAILED;
   U8           nullCfgCfm = 0;
   U8            cfmFail = 0;

   
   TRC2(nhAcHdlCpjUeIdChgCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjUeIdChgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjUeIdChgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   CMXTA_ALLOC(&ueInfo, sizeof (CpjUeInfo));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, "status",
         &(status.status));
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "use",&use);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "duplicate",&duplicate);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "cleanup",&cleanup);

   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "ueId",  &(ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "cellId",  &(cellId));
   if (use)
   {
      if(ueId != -1)
      {
        ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
       if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CpjUeIdChgCfm() Ue context not found\n"));
      }
      transId = gCpjCfgInfo[idx].cpjTransId;
      ueInfo->ueId = gCpjCfgInfo[idx].ueId;
      ueInfo->cellId = gCpjCfgInfo[idx].cellId;
      if(cleanup)
      cmMemset((U8*)&gCpjCfgInfo[idx], 0, sizeof(NhAcCpjCfgInfo));
   }
   else if (duplicate)
   {
      if(ueId != -1)
      {
        ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
       if(ret == RFAILED)
          CMXTA_DBG_ERR((_cmxtap,"CpjUeIdChgCfm() Ue context not found\n"));
      }
      transId = gCpjCfgInfo[idx].cpjTransId;
      ueInfo->ueId = gCpjCfgInfo[idx].ueId;
      ueInfo->cellId = gCpjCfgInfo[idx].cellId;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "invalidTransId",
                          &transId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidUeId",
                          &ueInfo->ueId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidCellId", 
                          &ueInfo->cellId);

      if(cleanup)
      cmMemset((U8*)&gCpjCfgInfo[idx], 0, sizeof(NhAcCpjCfgInfo));
   }
   else
   {
      transId = nhAccCb.cpjTransId[nhAccCb.cpjInd];
      ueInfo->ueId = nhAccCb.cpjCfgInfo[nhAccCb.cpjInd].ueId;
      ueInfo->cellId = nhAccCb.cpjCfgInfo[nhAccCb.cpjInd].cellId;
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullCfgCfm",  &(nullCfgCfm));
   if (nullCfgCfm)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(ueInfo, sizeof (CpjUeInfo));
         ueInfo = NULLP;
      }
      else
      {
         CMXTA_FREE(ueInfo, sizeof (CpjUeInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cfmFail",
                                                            &cfmFail);

   if (cfmFail)
   {
      nhAccCb.makeCfmFail = TRUE;
   }
   else
   {
      nhAccCb.makeCfmFail = FALSE;
   }


   if (CMXTA_ERR_NONE != PjUiCpjUeIdChgCfm (&pst, suId, transId, ueInfo, status))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjUeIdChgCfm() : returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/*-- nhAcHdlCpjCfgCfm  --*/

/*
   *
   *       Fun:   nhAcHdlCpjReEstReq
   *
   *       Desc:  CPJ RRC Connection Reestablishment Configuration Request
   *
   *       Ret:   ROK
   *
   *       Notes: None
   *
   *       File:  nhac_cpjhdl.c
   *
   */

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjReEstReq
(
 CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
 CmXtaSpCb    *spCb     /* spCb data structcre  */
 )
#else
PUBLIC S16 nhAcHdlCpjReEstReq(tcCb, spCb)
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
   Bool          matchProc = FALSE;
   SpId          spId = 0;
   U8            idx;

   TRC2(nhAcHdlCpjReEstReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjReEstReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjReEstReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjReEstReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCPJREESTREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCpjReEstReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.cpjInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.cpjInfo.cmInfo.spId), 2);

      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* initialize before GetVal */
   use = 0;

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8,"use",&use);

   if (use)
   {
     nhAcCpjGetUnusedCfgIdx(&idx);
     gCpjCfgInfo[idx].cpjTransId = rrcMsg->u.cpjInfo.transId;
     gCpjCfgInfo[idx].ueId = rrcMsg->u.cpjInfo.ueInfo.ueId;
     gCpjCfgInfo[idx].cellId = rrcMsg->u.cpjInfo.ueInfo.cellId;
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* End of nhAcHdlCpjReEstReq */

/*
   *
   *       Fun:   nhAcHdlCpjReEstCfm
   *
   *       Desc:  CPJ RRC Connection Reestablishment Configuration Confirm
   *
   *       Ret:   ROK
   *
   *       Notes: None
   *
   *       File:  nhac_cpjhdl.c
   *
   */

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjReEstCfm
(
 CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
 CmXtaSpCb    *spCb     /* spCb data structcre  */
 )
#else
PUBLIC S16 nhAcHdlCpjReEstCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   CpjReEstCfmInfo  *cfmInfo = NULLP;
   Pst               pst;
   U8                idx         = 0;
   SuId              suId        = 0;
   ProcId            srcProcId   = 0;
   ProcId            dstProcId   = 0;
   U8                use         = 0;
   U8                duplicate   = 0;
   Bool              matchProc   = FALSE;
   U16               ueId        = NHAC_INVALID_UEID;
   S16               cellId      = -1;
   S16               ret         = RFAILED;
   U8                cleanup     = TRUE;
   U8                status      = 1;
   U8                nullSdu = 0;


   TRC2(nhAcHdlCpjReEstCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjReEstCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjReEstCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status", &(status));
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "use",&use);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "duplicate",&duplicate);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "cleanup",&cleanup);

   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "cellId",  &(cellId));

   if (use)
   {

      if(ueId != NHAC_INVALID_UEID)
      {
         ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
         if(ret == RFAILED)
         {
            CMXTA_DBG_ERR((_cmxtap,"nhHdlCpjReEstCfm() Ue context not found\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      CMXTA_ALLOC(&cfmInfo, sizeof (CpjReEstCfmInfo));
      if (NULLP == cfmInfo)
      {
         CMXTA_DBG_FATAL((_cmxtap, "nhHdlCpjReEstCfm() Can't alocate memory\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      cfmInfo->transId = gCpjCfgInfo[idx].cpjTransId;
      cfmInfo->ueId    = gCpjCfgInfo[idx].ueId;
      cfmInfo->cellId  = gCpjCfgInfo[idx].cellId;

      if(status)
      {
         cfmInfo->status = CPJ_CFG_CFM_OK;
      }
      else
      {
         cfmInfo->status = CPJ_CFG_CFM_NOK;
      }
   }
   else if (duplicate)
   {
      if(ueId != NHAC_INVALID_UEID)
      {
        ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
       if(ret == RFAILED)
       {
          CMXTA_DBG_ERR((_cmxtap,"nhHdlCpjReEstCfm() Ue context not found\n"));
          RETVALUE(CMXTA_ERR_INT);
       }
      }
      CMXTA_ALLOC(&cfmInfo, sizeof (CpjReEstCfmInfo));
      if (NULLP == cfmInfo)
      {
         CMXTA_DBG_FATAL((_cmxtap, "nhHdlCpjReEstCfm() Can't alocate memory\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      cfmInfo->transId = gCpjCfgInfo[idx].cpjTransId;
      cfmInfo->ueId    = gCpjCfgInfo[idx].ueId;
      cfmInfo->cellId  = gCpjCfgInfo[idx].cellId;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "invalidTransId",
                          &cfmInfo->transId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidUeId",
                          &cfmInfo->ueId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidCellId", 
                             &cfmInfo->cellId);

      /* Fill Success by Default */
      cfmInfo->status = CPJ_CFG_CFM_OK;
   }
   else
   {
      cfmInfo->transId = NHAC_INVALID_TRANSID;
      cfmInfo->ueId = NHAC_INVALID_UEID;
      cfmInfo->cellId = NHAC_INVALID_CELLID;
      cfmInfo->status = CPJ_CFG_CFM_NOK;
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullSdu",  &(nullSdu));
   if (nullSdu)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(cfmInfo, sizeof(CpjReEstCfmInfo));
         cfmInfo = NULLP;
      }
      else
      {
         CMXTA_FREE(cfmInfo, sizeof(CpjReEstCfmInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   if (CMXTA_ERR_NONE != PjUiCpjReEstCfm (&pst, suId, cfmInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjReEstCfm() : returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* End of nhAcHdlCpjReEstCfm */

/*
   *
   *       Fun:   nhAcHdlCpjSecCfgReq
   *
   *       Desc:  CPJ Security Configuration Request
   *
   *       Ret:   ROK
   *
   *       Notes: None
   *
   *       File:  nhac_cpjhdl.c
   *
   */

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjSecCfgReq
(
 CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
 CmXtaSpCb    *spCb     /* spCb data structcre  */
 )
#else
PUBLIC S16 nhAcHdlCpjSecCfgReq(tcCb, spCb)
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
   Bool          matchProc = FALSE;
   SpId          spId = 0;
   U8            idx;

   TRC2(nhAcHdlCpjSecCfgReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjSecCfgReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjSecCfgReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjSecCfgReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif
      
   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCPJSECCFGREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCpjSecCfgReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.cpjInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.cpjInfo.cmInfo.spId), 2);

      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Valdiate the Cfg Request against paramters passed by RRC user
      (by using gCpjCfgStore) */
   if(nhAccCb.valChk)
   {
      ret = nhAcUtlCpjSecVal(tcCb, spCb, &(rrcMsg->u.cpjInfo.secCfgInfo));
      if (ret != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjSecCfgReq: Security Valdiation Failed\n"));
         cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

   }


   /* initialize before GetVal */
   use = 0;

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8,"use",&use);

   if (use)
   {
     nhAcCpjGetUnusedCfgIdx(&idx);
     gCpjCfgInfo[idx].cpjTransId = rrcMsg->u.cpjInfo.transId;
     gCpjCfgInfo[idx].ueId = rrcMsg->u.cpjInfo.secCfgInfo.ueId;
     gCpjCfgInfo[idx].cellId = rrcMsg->u.cpjInfo.secCfgInfo.cellId;
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* End of nhAcHdlCpjSecCfgReq */

/*
   *
   *       Fun:   nhAcHdlCpjSecCfgCfm
   *
   *       Desc:  CPJ Security Configuration Confirm
   *
   *       Ret:   ROK
   *
   *       Notes: None
   *
   *       File:  nhac_cpjhdl.c
   *
   */

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjSecCfgCfm
(
 CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
 CmXtaSpCb    *spCb     /* spCb data structcre  */
 )
#else
PUBLIC S16 nhAcHdlCpjSecCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   CpjSecCfgCfmInfo  *cfmInfo = NULLP;
   Pst               pst;
   U8                idx;
   SuId              suId        = 0;
   ProcId            srcProcId   = 0;
   ProcId            dstProcId   = 0;
   U8                use         = 0;
   U8                duplicate   = 0;
   Bool              matchProc   = FALSE;
   U16               ueId        = NHAC_INVALID_UEID;
   S16               cellId      = -1;
   S16               ret         = RFAILED;
   U8                cleanup     = TRUE;
   U8                secFail     = 0;
   U8                nullCfgCfm  = 0;


   TRC2(nhAcHdlCpjSecCfgCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjSecCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjSecCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "secFail", &(secFail));
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "use",&use);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "duplicate",&duplicate);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "cleanup",&cleanup);

   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "cellId",  &(cellId));

   if (use)
   {

      if(ueId != NHAC_INVALID_UEID)
      {
         ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
         if(ret == RFAILED)
         {
            CMXTA_DBG_ERR((_cmxtap,"nhHdlCpjSecCfgCfm() Ue context not found\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      CMXTA_ALLOC(&cfmInfo, sizeof (CpjSecCfgCfmInfo));
      if (NULLP == cfmInfo)
      {
         CMXTA_DBG_FATAL((_cmxtap, "nhHdlCpjSecCfgCfm() Can't alocate memory\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      cfmInfo->transId = gCpjCfgInfo[idx].cpjTransId;
      cfmInfo->ueId    = gCpjCfgInfo[idx].ueId;
      cfmInfo->cellId  = gCpjCfgInfo[idx].cellId;

      cfmInfo->status = CPJ_CFG_CFM_OK;

      if(secFail == 1)
      {
         cfmInfo->status = CPJ_CFG_CFM_NOK;
      }
   }
   else if (duplicate)
   {
      if(ueId != NHAC_INVALID_UEID)
      {
        ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
       if(ret == RFAILED)
       {
          CMXTA_DBG_ERR((_cmxtap,"nhHdlCpjSecCfgCfm() Ue context not found\n"));
          RETVALUE(CMXTA_ERR_INT);
       }
      }
      CMXTA_ALLOC(&cfmInfo, sizeof (CpjSecCfgCfmInfo));
      if (NULLP == cfmInfo)
      {
         CMXTA_DBG_FATAL((_cmxtap, "nhHdlCpjSecCfgCfm() Can't alocate memory\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      cfmInfo->transId = gCpjCfgInfo[idx].cpjTransId;
      cfmInfo->ueId    = gCpjCfgInfo[idx].ueId;
      cfmInfo->cellId  = gCpjCfgInfo[idx].cellId;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "invalidTransId",
                          &cfmInfo->transId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidUeId",
                          &cfmInfo->ueId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidCellId", 
                             &cfmInfo->cellId);

      /* Fill Success by Default */
      cfmInfo->status = CPJ_CFG_CFM_OK;
   }
   else
   {
      cfmInfo->transId = NHAC_INVALID_TRANSID;
      cfmInfo->ueId = NHAC_INVALID_UEID;
      cfmInfo->cellId = NHAC_INVALID_CELLID;
      cfmInfo->status = CPJ_CFG_CFM_NOK;
   }

   if(cleanup)
   {
      cmMemset((U8*)&gCpjCfgInfo[idx], 0, sizeof(NhAcCpjCfgInfo));
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullCfgCfm",  &(nullCfgCfm));
   if (nullCfgCfm)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(cfmInfo, sizeof (CpjSecCfgCfmInfo));
         cfmInfo = NULLP;
      }
      else
      {
         CMXTA_FREE(cfmInfo, sizeof (CpjSecCfgCfmInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   if (CMXTA_ERR_NONE != PjUiCpjSecCfgCfm (&pst, suId, cfmInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjSecCfgCfm() : returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* End of nhAcHdlCpjSecCfgCfm */

/*
   *
   *       Fun:   nhAcHdlCpjCountReq
   *
   *       Desc:  CPJ Count Request
   *
   *       Ret:   ROK
   *
   *       Notes: None
   *
   *       File:  nhac_cpjhdl.c
   *
   */

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjCountReq
(
 CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
 CmXtaSpCb    *spCb     /* spCb data structcre  */
 )
#else
PUBLIC S16 nhAcHdlCpjCountReq(tcCb, spCb)
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
   Bool          matchProc = FALSE;
   SpId          spId = 0;
   U8            idx;

   TRC2(nhAcHdlCpjCountReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjCountReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjCountReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjCountReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCPJCOUNTREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCpjCountReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.cpjInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.cpjInfo.cmInfo.spId), 2);

      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8,"use",&use);

   if (use)
   {
     nhAcCpjGetUnusedCfgIdx(&idx);
     gCpjCfgInfo[idx].cpjTransId = rrcMsg->u.cpjInfo.transId;
     gCpjCfgInfo[idx].ueId = rrcMsg->u.cpjInfo.ueInfo.ueId;
     gCpjCfgInfo[idx].cellId = rrcMsg->u.cpjInfo.ueInfo.cellId;
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* End of nhAcHdlCpjCountReq */

/*
   *
   *       Fun:   nhAcHdlCpjCountCfm
   *
   *       Desc:  CPJ Count Confirm
   *
   *       Ret:   ROK
   *
   *       Notes: None
   *
   *       File:  nhac_cpjhdl.c
   *
   */

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjCountCfm
(
 CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
 CmXtaSpCb    *spCb     /* spCb data structcre  */
 )
#else
PUBLIC S16 nhAcHdlCpjCountCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   CpjCountCfmInfo  *cfmInfo = NULLP;
   Pst               pst;
   U8                idx;
   SuId              suId        = 0;
   ProcId            srcProcId   = 0;
   ProcId            dstProcId   = 0;
   U8                use         = 0;
   U8                duplicate   = 0;
   Bool              matchProc   = FALSE;
   U16               ueId        = NHAC_INVALID_UEID;
   S16               cellId      = -1;
   S16               ret         = RFAILED;
   U8                cleanup     = TRUE;
   U8                status      = 1;
   U8                drbIds[CPJ_MAX_DRB];
   Txt               msgStr[100];
   Txt               frstWrd[3];
   U16               len;
   U8                numOfDrbs = 0;
   U8                cfmFail = 0;
   U8                nullCfgCfm = 0;


   TRC2(nhAcHdlCpjCountCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjCountCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjCountCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status", &(status));
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "use",&use);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "duplicate",&duplicate);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "cleanup",&cleanup);

   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "cellId",  &(cellId));

   /* Store the DRB Ids to be modified into addModDrb array */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "drbIdStr", &msgStr);
   len = 0;
   while(len <= strlen(msgStr))
   {
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      nhAcCpjUtlStrToken(&msgStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      drbIds[numOfDrbs] = atoi(frstWrd);
      numOfDrbs++;
   }

   if (numOfDrbs == 0)
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjCountCfm(): No drb IDs found\n"));
      RETVALUE(CMXTA_ERR_INT);
   }


   if (use)
   {

      if(ueId != NHAC_INVALID_UEID)
      {
         ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
         if(ret == RFAILED)
         {
            CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjCountCfm() Ue context not found\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      CMXTA_ALLOC(&cfmInfo, sizeof (CpjCountCfmInfo));
      if (NULLP == cfmInfo)
      {
         CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjCountCfm() Can't alocate memory\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      cfmInfo->transId = gCpjCfgInfo[idx].cpjTransId;
      cfmInfo->ueId    = gCpjCfgInfo[idx].ueId;
      cfmInfo->cellId  = gCpjCfgInfo[idx].cellId;

      if(status)
      {
         cfmInfo->numRb   = numOfDrbs;
         cfmInfo->status  = ROK;

         for (idx = 0; idx < numOfDrbs; idx++)
         {
            cfmInfo->countInfo[idx].rbId = drbIds[idx];
            cfmInfo->countInfo[idx].dir = NHU_DIR_UPLINK;
            cfmInfo->countInfo[idx].ulCount = 10 * idx;
            cfmInfo->countInfo[idx].dlCount = 20 * idx;
         }
      }
      else
      {
         cfmInfo->status = RFAILED;
      }
   }
   else if (duplicate)
   {
      if(ueId != NHAC_INVALID_UEID)
      {
        ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
       if(ret == RFAILED)
       {
          CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjCountCfm() Ue context not found\n"));
          RETVALUE(CMXTA_ERR_INT);
       }
      }
      CMXTA_ALLOC(&cfmInfo, sizeof (CpjCountCfmInfo));
      if (NULLP == cfmInfo)
      {
         CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjCountCfm() Can't alocate memory\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      cfmInfo->transId = gCpjCfgInfo[idx].cpjTransId;
      cfmInfo->ueId    = gCpjCfgInfo[idx].ueId;
      cfmInfo->cellId  = gCpjCfgInfo[idx].cellId;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "invalidTransId",
                          &cfmInfo->transId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidUeId",
                          &cfmInfo->ueId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidCellId", 
                             &cfmInfo->cellId);

      if(status)
      {
         cfmInfo->numRb   = numOfDrbs;
         cfmInfo->status  = CPJ_CFG_CFM_OK;

         for (idx = 0; idx < numOfDrbs; idx++)
         {
            cfmInfo->countInfo[idx].rbId = drbIds[idx];
            cfmInfo->countInfo[idx].dir = NHU_DIR_UPLINK;
            cfmInfo->countInfo[idx].ulCount = 10 * idx;
            cfmInfo->countInfo[idx].dlCount = 20 * idx;
         }
      }

      /* Fill Success by Default */
      cfmInfo->status = ROK;
   }
   else
   {
      cfmInfo->transId = NHAC_INVALID_TRANSID;
      cfmInfo->ueId = NHAC_INVALID_UEID;
      cfmInfo->cellId = NHAC_INVALID_CELLID;
      cfmInfo->status = ROK;
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cfmFail",
                                                            &cfmFail);

   if (cfmFail)
   {
      nhAccCb.makeCfmFail = TRUE;
   }
   else
   {
      nhAccCb.makeCfmFail = FALSE;
   }

   if(cleanup)
   {
      ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
      if (ret != RFAILED)
      {
         cmMemset((U8*)&gCpjCfgInfo[idx], 0, sizeof(NhAcCpjCfgInfo));
      }
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullCfgCfm",  &(nullCfgCfm));
   if (nullCfgCfm)
   {
      if (pst.selector == 1)
      {
         CMXTA_FREE(cfmInfo, sizeof(CpjCountCfmInfo));
         cfmInfo = NULLP;
      }
      else
      {
         CMXTA_FREE(cfmInfo, sizeof(CpjCountCfmInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   if (CMXTA_ERR_NONE != PjUiCpjCountCfm (&pst, suId, cfmInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjCountCfm() : returned RFAILED\n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* End of nhAcHdlCpjCountCfm */

/*
   *
   *       Fun:   nhAcHdlCpjSduStaReq
   *
   *       Desc:  CPJ SDU Status Request
   *
   *       Ret:   ROK
   *
   *       Notes: None
   *
   *       File:  nhac_cpjhdl.c
   *
   */

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjSduStaReq
(
 CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
 CmXtaSpCb    *spCb     /* spCb data structcre  */
 )
#else
PUBLIC S16 nhAcHdlCpjSduStaReq(tcCb, spCb)
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
   Bool          matchProc = FALSE;
   SpId          spId = 0;
   U8            idx;

   TRC2(nhAcHdlCpjSduStaReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjSduStaReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjSduStaReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjSduStaReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCPJSDUSTAREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCpjSduStaReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.cpjInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.cpjInfo.cmInfo.spId), 2);

      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8,"use",&use);

   if (use)
   {
     nhAcCpjGetUnusedCfgIdx(&idx);
     gCpjCfgInfo[idx].cpjTransId = rrcMsg->u.cpjInfo.transId;
     gCpjCfgInfo[idx].ueId = rrcMsg->u.cpjInfo.ueInfo.ueId;
     gCpjCfgInfo[idx].cellId = rrcMsg->u.cpjInfo.ueInfo.cellId;
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* End of nhAcHdlCpjSduStaReq */
/*ashenoy*/
/*
   *
   *       Fun:   nhAcHdlCpjDataFwdReq
   *
   *       Desc:  CPJ SDU Status Request
   *
   *       Ret:   ROK
   *
   *       Notes: None
   *
   *       File:  nhac_cpjhdl.c
   *
   */

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjDataFwdReq
(
 CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
 CmXtaSpCb    *spCb     /* spCb data structcre  */
 )
#else
PUBLIC S16 nhAcHdlCpjDataFwdReq(tcCb, spCb)
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
   Bool          matchProc = FALSE;
   SpId          spId = 0;
   U8            idx;

   TRC2(nhAcHdlCpjSduStaReq)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjSduStaReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjSduStaReq(), tcId (%d)\n", tcCb->tcId));
#endif

   if (ROK != cmXtaPeekMsg((CmXtaMsgQ*)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjSduStaReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;
   rrcMsg     =   (NhAccMsgQElm *)msg->data;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);
   pst.event = EVTCPJSTARTDATAFWDREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcHdlCpjSduStaReq() : pst mismatch\n"));
      cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);
      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ*)&(tcCb->msgQ), &msg);

   /*-- Set default value & validate for spid --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId", &(spId));
   if (spId != rrcMsg->u.cpjInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed:spId Mismatch: exp (%d) recvd (%d)\n",
                         spId, rrcMsg->u.cpjInfo.cmInfo.spId), 2);

      cmXtaFlushMsg((CmXtaMsgQ*)&(tcCb->msgQ), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8,"use",&use);

   if (use)
   {
     nhAcCpjGetUnusedCfgIdx(&idx);
     gCpjCfgInfo[idx].cpjTransId = rrcMsg->u.cpjInfo.transId;
     gCpjCfgInfo[idx].ueId = rrcMsg->u.cpjInfo.ueInfo.ueId;
     gCpjCfgInfo[idx].cellId = rrcMsg->u.cpjInfo.ueInfo.cellId;
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg ((CmXtaMsgQ*)&(tcCb->msgQ), msg);

   RETVALUE(CMXTA_ERR_NONE);
}/* End of nhAcHdlCpjSduStaReq */


/*
   *
   *       Fun:   nhAcHdlCpjSduStaCfm
   *
   *       Desc:  CPJ SDU Stratus Confirm
   *
   *       Ret:   ROK
   *
   *       Notes: None
   *
   *       File:  nhac_cpjhdl.c
   *
   */

#ifdef ANSI
PUBLIC S16 nhAcHdlCpjSduStaCfm
(
 CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
 CmXtaSpCb    *spCb     /* spCb data structcre  */
 )
#else
PUBLIC S16 nhAcHdlCpjSduStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structcre  */
CmXtaSpCb    *spCb;    /* spCb data structcre  */
#endif
{
   CpjSduStaCfmInfo  *cfmInfo = NULLP;
   Pst               pst;
   U8                idx;
   SuId              suId        = 0;
   ProcId            srcProcId   = 0;
   ProcId            dstProcId   = 0;
   U8                use         = 0;
   U8                duplicate   = 0;
   Bool              matchProc   = FALSE;
   U16               ueId        = NHAC_INVALID_UEID;
   S16               cellId      = -1;
   S16               ret         = RFAILED;
   U8                cleanup     = TRUE;
   U8                status      = 1;
   U8                drbIds[CPJ_MAX_DRB];
   Txt               msgStr[100];
   Txt               frstWrd[3];
   U16               len;
   U8                numOfDrbs = 0;
   U8                nullCfgCfm = 0;
   U8                zeroRBs = 0;


   TRC2(nhAcHdlCpjSduStaCfm)

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjSduStaCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcHdlCpjSduStaCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

#ifdef SS_MULTIPLE_PROCS
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U16,"procId",&srcProcId);
#endif

   /*-- Validate if this is the msg for this function --*/
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID,srcProcId,dstProcId,matchProc);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "status", &(status));
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "use",&use);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "duplicate",&duplicate);
   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U8, "cleanup",&cleanup);

   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(tcCb,spCb->childStep, CMXTA_ATTRIB_S16, "cellId",  &(cellId));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "zeroRBs", &zeroRBs);
   /* Store the DRB Ids to be modified into addModDrb array */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "drbIdStr", &msgStr);

   len = 0;
   while(len <= strlen(msgStr))
   {
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      nhAcCpjUtlStrToken(&msgStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      drbIds[numOfDrbs] = atoi(frstWrd);
      numOfDrbs++;
   }

   if (zeroRBs)
   {
      numOfDrbs=0;
   }

   if (use)
   {

      if(ueId != NHAC_INVALID_UEID)
      {
         ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
         if(ret == RFAILED)
         {
            CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjSduStaCfm() Ue context not found\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      CMXTA_ALLOC(&cfmInfo, sizeof (CpjSduStaCfmInfo));
      if (NULLP == cfmInfo)
      {
         CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjSduStaCfm() Can't alocate memory\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      cfmInfo->transId = gCpjCfgInfo[idx].cpjTransId;
      cfmInfo->ueId    = gCpjCfgInfo[idx].ueId;
      cfmInfo->cellId  = gCpjCfgInfo[idx].cellId;

      if(status)
      {
         cfmInfo->numRb   = numOfDrbs;
         cfmInfo->status  = ROK;

         for (idx = 0; idx < numOfDrbs; idx++)
         {
            cfmInfo->sduStaInfo[idx].rbId = drbIds[idx];
            cfmInfo->sduStaInfo[idx].dir = NHU_DIR_UPLINK;
            cfmInfo->sduStaInfo[idx].ulSduStaInfo.numBits = 9;
            cfmInfo->sduStaInfo[idx].ulSduStaInfo.count = 10 * idx;
            cfmInfo->sduStaInfo[idx].dlSduStaInfo.count = 20 * idx;
            CMXTA_ALLOC((&cfmInfo->sduStaInfo[idx].ulSduStaInfo.ulBitMap), sizeof (U8) * 2);
            if(cfmInfo->sduStaInfo[idx].ulSduStaInfo.ulBitMap == NULLP)
            {
               CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjSduStaCfm() Can't alocate memory\n"));
               RETVALUE(CMXTA_ERR_INT);
            }
            *cfmInfo->sduStaInfo[idx].ulSduStaInfo.ulBitMap = 0x55;
         }
      }
      else
      {
         cfmInfo->status = RFAILED;
         cfmInfo->reason = RFAILED;
      }
   }
   else if (duplicate)
   {
      if(ueId != NHAC_INVALID_UEID)
      {
        ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
       if(ret == RFAILED)
       {
          CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjSduStaCfm() Ue context not found\n"));
          RETVALUE(CMXTA_ERR_INT);
       }
      }
      CMXTA_ALLOC(&cfmInfo, sizeof (CpjSduStaCfmInfo));
      if (NULLP == cfmInfo)
      {
         CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjSduStaCfm() Can't alocate memory\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      cfmInfo->transId = gCpjCfgInfo[idx].cpjTransId;
      cfmInfo->ueId    = gCpjCfgInfo[idx].ueId;
      cfmInfo->cellId  = gCpjCfgInfo[idx].cellId;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "invalidTransId",
                          &cfmInfo->transId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidUeId",
                          &cfmInfo->ueId);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "invalidCellId", 
                             &cfmInfo->cellId);

      cfmInfo->numRb   = numOfDrbs;
      cfmInfo->status  = ROK;

      for (idx = 0; idx < numOfDrbs; idx++)
      {
         cfmInfo->sduStaInfo[idx].rbId = drbIds[idx];
         cfmInfo->sduStaInfo[idx].dir = NHU_DIR_UPLINK;
         cfmInfo->sduStaInfo[idx].ulSduStaInfo.numBits = 8;
         cfmInfo->sduStaInfo[idx].ulSduStaInfo.count = 10 * idx;
         cfmInfo->sduStaInfo[idx].dlSduStaInfo.count = 20 * idx;
         CMXTA_ALLOC((&cfmInfo->sduStaInfo[idx].ulSduStaInfo.ulBitMap), sizeof (U8));
         if(cfmInfo->sduStaInfo[idx].ulSduStaInfo.ulBitMap == NULLP)
         {
            CMXTA_DBG_FATAL((_cmxtap, "nhAcHdlCpjSduStaCfm() Can't alocate memory\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
         *cfmInfo->sduStaInfo[idx].ulSduStaInfo.ulBitMap = 0x55;
      }

      /* Fill Success by Default */
      cfmInfo->status = ROK;
   }
   else
   {
      cfmInfo->transId = NHAC_INVALID_TRANSID;
      cfmInfo->ueId = NHAC_INVALID_UEID;
      cfmInfo->cellId = NHAC_INVALID_CELLID;
      cfmInfo->status = ROK;
   }

   if(cleanup)
   {
      ret = nhAcCpjGetCfgIndx(ueId, cellId, &idx, 0);
      if (ret != RFAILED)
      {
         cmMemset((U8*)&gCpjCfgInfo[idx], 0, sizeof(NhAcCpjCfgInfo));
      }
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "nullCfgCfm",  &(nullCfgCfm));
   if (nullCfgCfm)
   {
      if (pst.selector == 1)
      {
         if (use)
         {
            for (idx = 0; idx < numOfDrbs; idx++)
            {
               CMXTA_FREE((cfmInfo->sduStaInfo[idx].ulSduStaInfo.ulBitMap), (2 * sizeof (U8)));
            }
         }
         else if(duplicate)
         {
            for (idx = 0; idx < numOfDrbs; idx++)
            {
               CMXTA_FREE((cfmInfo->sduStaInfo[idx].ulSduStaInfo.ulBitMap), (sizeof (U8)));
            }
         }

         CMXTA_FREE(cfmInfo, sizeof(CpjSduStaCfmInfo));
         cfmInfo = NULLP;
      }
      else
      {
         if (use)
         {
            for (idx = 0; idx < numOfDrbs; idx++)
            {
               CMXTA_FREE((cfmInfo->sduStaInfo[idx].ulSduStaInfo.ulBitMap), (2 * sizeof (U8)));
            }
         }
         else if(duplicate)
         {
            for (idx = 0; idx < numOfDrbs; idx++)
            {
               CMXTA_FREE((cfmInfo->sduStaInfo[idx].ulSduStaInfo.ulBitMap), (sizeof (U8)));
            }
         }

         CMXTA_FREE(cfmInfo, sizeof(CpjSduStaCfmInfo));
         RETVALUE(CMXTA_ERR_NONE);
      }
   }

   if (CMXTA_ERR_NONE != PjUiCpjSduStaCfm (&pst, suId, cfmInfo))
   {
      CMXTA_DBG_ERR((_cmxtap,"nhAcHdlCpjSduStaCfm() : returned RFAILED\n"));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* End of nhAcHdlCpjSduStaCfm */


/**********************************************************************
         End of file:     nhac_cpjhdl.c@@/main/3 - Fri Jul  1 01:12:57 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    dm               1. LTE RRC Initial Release.
/main/2      ---    ch               1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

