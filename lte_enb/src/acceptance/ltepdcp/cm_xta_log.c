
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_log.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:21 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta.h"
/* cm_xta_log_c_001.main_2 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"

/* cm_xta_log_c_001.main_2 Removed cm_xta_app.x for Psf-Diameter 1.1 */
/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaLogXml
(
CmXtaTCCb      *tcCb,
U8 logType
)
#else
PUBLIC S16 cmXtaLogXml(tcCb, logType)
CmXtaTCCb      *tcCb;
U8 logType;
#endif
{
   U32  memAvail;
   SsMemDbgInfo memInfo;

   PRIVATE Txt infoStr [][50] =
   {
      "",
      "",
      "Info      : Pre TA Init memory usage\n",
      "Info      : Post TA DeInit memory usage\n",
      "Info      : Pre TC Init memory usage\n",
      "Info      : Post TC DeInit memory usage\n",
      "Info      : Pre TC Run memory usage\n",
      "Info      : Post TC Clean memory usage\n",
   };

   TRC2(cmXtaLogXml)

   /*-- Check we have to show the SSI memory usage here --*/
   /*-- Check if XML Output --*/
   if (cmXtaCb.directives.memCalculate == TRUE)
   {
      switch (logType)
      {
         case CMXTA_MEM_TC_INIT :

            cmXtaRegInfoShow(tcCb, logType, &tcCb->memPreCfg);

            break;

         case CMXTA_MEM_TC_DEINIT :
            cmXtaRegInfoShow(tcCb, logType, &tcCb->memPostShutdown);

            break;

         case CMXTA_MEM_TC_RUN :

            cmXtaRegInfoShow(tcCb, logType, &tcCb->memPreTest);

            break;

         case CMXTA_MEM_TC_CLEAN :

            cmXtaRegInfoShow(tcCb, logType, &tcCb->memPostClean);

            break;

         default :
            break;
      }
   }

   if ((cmXtaCb.directives.xmlOutput == TRUE) && (cmXtaCb.directives.memFlag == TRUE))
   {
      switch (logType)
      {
         case CMXTA_MEM_LOG_INIT :

            CMXTA_DBG_RES((_cmxtap, "<tapa.log>\n"));
            /*-- Increment XML Indent count --*/
            cmXtaCb.xmlIndent++;
            break;

         case CMXTA_MEM_LOG_DEINIT :
            /*-- Decrement XML Indent count --*/
            cmXtaCb.xmlIndent--;

            CMXTA_DBG_RES((_cmxtap, "</tapa.log>\n"));
            break;

         case CMXTA_MEM_TA_INIT :

            CMXTA_DBG_RESIND((_cmxtap, "<tapa.ta>\n"), cmXtaCb.xmlIndent);

            /*-- Increment XML Indent count --*/
            cmXtaCb.xmlIndent++;

            cmXtaRegInfoShow(tcCb, logType, &memInfo);

            break;

         case CMXTA_MEM_TA_DEINIT :
            cmXtaRegInfoShow(tcCb, logType, &memInfo);

            /*-- Decrement XML Indent count --*/
            cmXtaCb.xmlIndent--;

            CMXTA_DBG_RESIND((_cmxtap, "</tapa.ta>\n"), cmXtaCb.xmlIndent);

            break;

         case CMXTA_MEM_TC_INIT :

            CMXTA_DBG_RESIND((_cmxtap, "<tapa.testcase id=\"%s\">\n", tcCb->xmlCb->cmd), cmXtaCb.xmlIndent);

            /*-- Increment XML Indent count --*/
            cmXtaCb.xmlIndent++;

            cmXtaRegInfoShow(tcCb, logType, &tcCb->memPreCfg);

            /*-- Decrement XML Indent count --*/
            cmXtaCb.xmlIndent--;

            break;

         case CMXTA_MEM_TC_DEINIT :
            /*-- Increment XML Indent count --*/
            cmXtaCb.xmlIndent++;

            cmXtaRegInfoShow(tcCb, logType, &tcCb->memPostShutdown);

            /*-- Decrement XML Indent count --*/
            cmXtaCb.xmlIndent--;

            CMXTA_DBG_RESIND((_cmxtap, "</tapa.testcase>\n"), cmXtaCb.xmlIndent);

            break;

         case CMXTA_MEM_TC_RUN :

            /*-- Increment XML Indent count --*/
            cmXtaCb.xmlIndent++;

            cmXtaRegInfoShow(tcCb, logType, &tcCb->memPreTest);

            /*-- Decrement XML Indent count --*/
            cmXtaCb.xmlIndent--;

            break;

         case CMXTA_MEM_TC_CLEAN :
            /*-- Increment XML Indent count --*/
            cmXtaCb.xmlIndent++;

            cmXtaRegInfoShow(tcCb, logType, &tcCb->memPostClean);

            /*-- Decrement XML Indent count --*/
            cmXtaCb.xmlIndent--;

            break;

         default :
            break;
      }
   }
   else if (cmXtaCb.directives.memFlag == TRUE)
   {
      CMXTA_DBG_RES((_cmxtap, infoStr[logType]));
      SRegInfoShow(cmXtaCb.init.region, &memAvail);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaLogXml */


/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaRegInfoShow
(
CmXtaTCCb      *tcCb,
U8 logType,
SsMemDbgInfo *memInfo
)
#else
PUBLIC S16 cmXtaRegInfoShow( tcCb,logType,memInfo)
CmXtaTCCb      *tcCb;
U8 logType;
SsMemDbgInfo *memInfo;
#endif
{
   S16  ret;
   U16   idx;
   QLen  qLen;

   PRIVATE Txt xmlInfoStr [][50] =
   {
      "",
      "",
      "tainit",
      "tadeinit",
      "tcinit",
      "tcdeinit",
      "tcrun",
      "tcclean",
   };

   TRC2(cmXtaRegInfoShow)

   /*-- Lock System Task Table so that no System tasks are added or removed. This
        is required because we have to sample the demand queues for all the system tasks
        and without this lock, tasks may be added or removed from the system --*/
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   /*-- Acquire the region semaphore, so that the no memory can be freed or allocated
        beyond this --*/
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   /*-- I guess the system is crippled by this time, lets take a snapshot --*/

   /*-- Check memory in buckets --*/
   SGetRegInfo(cmXtaCb.init.region, memInfo);

   /*-- Check pending messages in SSI queues --*/
   cmXtaFndLenDmndQ(&qLen);

   /*-- Release the system slowly --*/

   /*-- Release the region semaphore --*/
   if (SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
      RETVALUE(RFAILED);
   }

   /*-- Unlock System Task Table --*/
   ret = SUnlock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   /*-- This calculation is an approximation at the best. This method can't find the memory which is
        neither in buckets nor in SSI queues and will raise false positives for all such scenarios

        To alleviate that, we tolerate atleast a difference of one bucket for every system task --*/

   /* cm_xta_log_c_001.main_1: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "cmXtaRegInfoShow(): bucket 0 (number:%u, size:%u, allocated:%u, queue:%u)\n",
                memInfo->bktDbgTbl[0].numBlks, memInfo->bktDbgTbl[0].size,
                memInfo->bktDbgTbl[0].numAlloc, qLen));
#else
   CMXTA_DBG_INFO((_cmxtap, "cmXtaRegInfoShow(): bucket 0 (number:%lu, size:%lu, allocated:%lu, queue:%lu)\n",
                memInfo->bktDbgTbl[0].numBlks, memInfo->bktDbgTbl[0].size,
                memInfo->bktDbgTbl[0].numAlloc, qLen));
#endif /* ALIGN_64BIT */

   if (memInfo->numBkts > 0)
      memInfo->bktDbgTbl[0].numAlloc -= qLen;

   if ((cmXtaCb.directives.xmlOutput == TRUE) && (cmXtaCb.directives.memFlag == TRUE))
   {
      CMXTA_DBG_RESIND((_cmxtap, "<tapa.memory type=\"%s\">\n", xmlInfoStr[logType]), cmXtaCb.xmlIndent);

      for (idx = 0; idx < memInfo->numBkts; idx++)
      {
         /* cm_xta_log_c_001.main_1: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
         CMXTA_DBG_RESIND((_cmxtap, "<tapa.mem bucket=\"%d\" number=\"%u\" size=\"%u\" allocated=\"%u\"/>\n",
                  idx,
                  memInfo->bktDbgTbl[idx].numBlks,
                  memInfo->bktDbgTbl[idx].size,
                  memInfo->bktDbgTbl[idx].numAlloc), cmXtaCb.xmlIndent+1);
#else
         CMXTA_DBG_RESIND((_cmxtap, "<tapa.mem bucket=\"%d\" number=\"%lu\" size=\"%lu\" allocated=\"%lu\"/>\n",
                  idx,
                  memInfo->bktDbgTbl[idx].numBlks,
                  memInfo->bktDbgTbl[idx].size,
                  memInfo->bktDbgTbl[idx].numAlloc), cmXtaCb.xmlIndent+1);
#endif /* ALIGN_64BIT */
      }

      /* cm_xta_log_c_001.main_1: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
      CMXTA_DBG_RESIND((_cmxtap, "<tapa.heap size=\"%u\" allocated=\"%u\"",
               memInfo->heapSize, memInfo->heapAlloc), cmXtaCb.xmlIndent+1);
#else
      CMXTA_DBG_RESIND((_cmxtap, "<tapa.heap size=\"%lu\" allocated=\"%lu\"",
               memInfo->heapSize, memInfo->heapAlloc), cmXtaCb.xmlIndent+1);
#endif /* ALIGN_64BIT */

#if (ERRCLASS & ERRCLS_DEBUG)
      CMXTA_DBG_RES((_cmxtap, " segmented=\"%d\"", memInfo->numFragBlk));
#endif

      CMXTA_DBG_RES((_cmxtap, "/>\n"));

      CMXTA_DBG_RESIND((_cmxtap, "</tapa.memory>\n"), cmXtaCb.xmlIndent);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaRegInfoShow */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaFndLenDmndQ
(
QLen  *qLen
)
#else
PUBLIC S16 cmXtaFndLenDmndQ(qLen)
QLen  *qLen;
#endif
{
   U16   n;
   QLen  tmpQLen;

   TRC1(cmXtaFndLenDmndQ);

   *qLen   = 0;
   tmpQLen = 0;

   /*-- This is a temporary fix to find the number of message in SSI 
        demand queue. It is a hack code since we are not checking for
        the number of dBuf associated for the messages. The assumption
        is that the size is taken from the first block of 128 bytes --*/ 
   for (n = 0;  n < SS_MAX_STSKS;  n++)
   {
      if (osCp.sTskTbl[n].used)
      {
         ssFndLenDmndQ(&osCp.sTskTbl[n].dQ, PRIORNC, &tmpQLen);
         *qLen += tmpQLen;
      }

   }


   RETVALUE(ROK);
} 

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaCheckMemory
(
CmXtaTCCb      *tcCb
)
#else
PUBLIC S16 cmXtaCheckMemory(tcCb)
CmXtaTCCb      *tcCb;
#endif
{
   CmXtaTstGrp *tstGrp;
   U16   idx;
   U16   cnt;
   U16   n;
   U8  localRes;

   U32 memCount1;
   U32 memCount2;
   U32 diffAllowed;

   SsMemDbgInfo *memInfoList[4];
   SsMemDbgInfo *memInfo1;
   SsMemDbgInfo *memInfo2;

   TRC2(cmXtaCheckMemory)

   /*-- Allow one message per system task, right now it is done without Lock --*/
   diffAllowed = 0;
   for (n = 0;  n < SS_MAX_STSKS;  n++)
   {
      if (osCp.sTskTbl[n].used)
      {
         diffAllowed++;
      }
   }

   tstGrp = &cmXtaCb.tstGrp[cmXtaCb.curTstGroup];

   /*-- This calculation is an approximation at the best. This method can't find the memory which is
        neither in buckets nor in SSI queues and will raise false positives for all such scenarios

        To alleviate that, we tolerate atleast a difference of one bucket for every system task --*/

   /*-- Check for memory usage difference between cfg and shutdown and run
        and clean steps --*/

   memInfoList[0]= &tcCb->memPreCfg;
   memInfoList[1]= &tcCb->memPostShutdown;

   memInfoList[2]= &tcCb->memPreTest;
   memInfoList[3]= &tcCb->memPostClean;

   for (cnt = 0; cnt < 2; cnt++)
   {
      memInfo1 = memInfoList[cnt * 2];
      memInfo2 = memInfoList[cnt * 2 + 1];

      localRes = CMXTA_TEST_LEAK_CFG;
      if (cnt == 1)
         localRes = CMXTA_TEST_LEAK_RUN;

      /*-- We are taking the assumption that memory bucket configuration 
           has not changed in the middle and so we may use any other bucket
           info for the loop. 

           We will only check for the difference in the allocated numbers
           to check for the leak. No validationi is done for the same bucket
           id etc --*/

      if (memInfo1->numBkts != memInfo2->numBkts)
      {
         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): invalid bucket sizes %d %d\n",
                      memInfo1->numBkts, memInfo2->numBkts));
      }

      memCount1 = 0;
      memCount2 = 0;

      /*-- We return for first memory leak --*/
      for (idx = 0; idx < memInfo1->numBkts; idx++)
      {
         if ((memInfo1->bktDbgTbl[idx].numBlks != memInfo1->bktDbgTbl[idx].numBlks)  ||
             (memInfo1->bktDbgTbl[idx].size    != memInfo1->bktDbgTbl[idx].size   ))
         {
            CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): bucket info mimatch, memory sample missed in some scenario\n"));

         }

         /* cm_xta_log_c_001.main_1: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): comparing bucket %d (number:%u, size:%u, allocated:%u)\n", 
                      cnt * 2,
                      memInfo1->bktDbgTbl[idx].numBlks,
                      memInfo1->bktDbgTbl[idx].size,
                      memInfo1->bktDbgTbl[idx].numAlloc));

         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): comparing bucket %d (number:%u, size:%u, allocated:%u)\n", 
                      cnt * 2 + 1,
                      memInfo2->bktDbgTbl[idx].numBlks,
                      memInfo2->bktDbgTbl[idx].size,
                      memInfo2->bktDbgTbl[idx].numAlloc));
#else
         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): comparing bucket %d (number:%lu, size:%lu, allocated:%lu)\n", 
                      cnt * 2,
                      memInfo1->bktDbgTbl[idx].numBlks,
                      memInfo1->bktDbgTbl[idx].size,
                      memInfo1->bktDbgTbl[idx].numAlloc));

         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): comparing bucket %d (number:%lu, size:%lu, allocated:%lu)\n", 
                      cnt * 2 + 1,
                      memInfo2->bktDbgTbl[idx].numBlks,
                      memInfo2->bktDbgTbl[idx].size,
                      memInfo2->bktDbgTbl[idx].numAlloc));
#endif /* ALIGN_64BIT */
         memCount1 +=memInfo1->bktDbgTbl[idx].numAlloc;
         memCount2 +=memInfo2->bktDbgTbl[idx].numAlloc;
      }

      /*-- Check bucket usage --*/
      if (memCount1 == memCount2) 
      {
         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): Perfect match, no leak from buckets\n"));
      }
      else if (((memCount1 < memCount2) && ((memCount1 + diffAllowed) >= memCount2)) ||
               ((memCount1 > memCount2) && ((memCount2 + diffAllowed) >= memCount1)))
      {
         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): Leak within permissible limits, maybe some transient messages\n"));
         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): Use memory tool to validate the results\n"));
      }
      else
      {

         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): Memory leak: bucket usage mismatch\n"));

         tstGrp->tstList[tstGrp->curTest].memResult |= localRes;
         tstGrp->memResult |= localRes;

         /*-- Update result field only for ignored and successful scenarios --*/
         if (tstGrp->result != CMXTA_TEST_FAILED)
         {
            tstGrp->tstList[tstGrp->curTest].result = CMXTA_TEST_LEAK;
            tstGrp->result = CMXTA_TEST_LEAK;
         }
      }

      /*-- Check heap usage --*/
      if (memInfo1->heapAlloc < memInfo2->heapAlloc)
      {
         /* cm_xta_log_c_001.main_1: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): Memory leak: heap mismatch (%u) vs (%u)\n",
                      memInfo1->heapAlloc, memInfo2->heapAlloc));
#else
         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): Memory leak: heap mismatch (%lu) vs (%lu)\n",
                      memInfo1->heapAlloc, memInfo2->heapAlloc));
#endif /* ALIGN_64BIT */

         tstGrp->tstList[tstGrp->curTest].memResult |= localRes;
         tstGrp->memResult |= localRes;

         /*-- Update result field only for ignored and successful scenarios --*/
         if (tstGrp->result != CMXTA_TEST_FAILED)
         {
            tstGrp->tstList[tstGrp->curTest].result = CMXTA_TEST_LEAK;
            tstGrp->result = CMXTA_TEST_LEAK;
         }
      }
      else
      {
         CMXTA_DBG_INFO((_cmxtap, "cmXtaCheckMemory(): Perfect match, no leak from heap\n"));
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaCheckMemory */

/********************************************************************30**

         End of file:     cm_xta_log.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:21 2015

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
/main/1      ----     up  1. Main release
/main/2      ---      cm_xta_log_c_001.main_1  pkaX  1. Fix for 64bit compilation warnings
/main/3      ----      cm_xta_log_c_001.main_2 nh    1. Updated for Psf-Diameter 1.1
                             release Removed cm_xta_app.[hx]
*********************************************************************91*/
