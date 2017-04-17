


/**********************************************************************
 
    Name:  
 
    Type:   C include file
 
    Desc:   
 
    File:  wr_tenb_stats.c
 
    Sid:      wr_tenb_stats.c@@/main/tenb_5.0_RIB/3 - Tue Oct 27 14:21:17 2015
 
    Prg:   sm
 
**********************************************************************/
 
/** @file wr_tenb_stats.c
@brief This file contains 
*/

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*
*/

/* header include files (.h) */
  
#include "envopt.h"             /* Environment options */  
#include "envdep.h"             /* Environment dependent */
#include "envind.h"             /* Environment independent */
#include "gen.h"                /* General */
#include "ssi.h"                /* System services interface */
#include "cm_llist.h"           /* Linked list header file */
#include "cm_tkns.h"            /* Common tokens header file */


/* header/extern include files (.x) */

#include "gen.x"                /* General */
#include "ssi.x"                /* System services interface */
#include "cm_lib.x"             /* Common lib header file */
#include "cm_llist.x"           /* Linked list header file */
#include "cm_tkns.x"            /* Common tokens header file */
#include "ss_queue.h"
#include "ss_queue.x"
#include "ss_task.x"
#include "ss_msg.x"
#include "cm_tenb_stats.x"    /* Total EnodeB Stats declarations */

#include <unistd.h>
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/socket.h>
#include <string.h>  
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>

#ifdef TENB_STATS
#include "wr_cmn.h"

EXTERN U32   wrSmDfltNumCells; /**/
/* Statistics Logs are maintained in files separate from LOG files.
 * Schema of Stats <UE1_STATS>....<UEn_STATS><CELL_STATS><n>.
 * File Naming convention TeNB_Stats_<TIME_STAMP>.
 * A file is closed and sent to dest, once it has 2000 Records. */

pthread_t sockThrdId;
struct sockaddr_in addrOthr;  
socklen_t addrOthrLen;
int sockFd;

U32 sockStatsBuf[2500] = {0};
U32 bufWritIdx = 0;


U32 cellStatsCount = 0;
U32 ueStatsCount = 0;
TSInfStatsCb tsCb={0};
#define TS_INVALID_VALUE      0xff
#define TS_FILE_STATS_START   1
#define TS_FILE_STATS_STOP    2
#define TS_MAX_FILE_RECORDS   400
#define TS_MAX_UE_HDR         1000
#define TS_MAX_CELL_HDR       500 
#define TS_OAM_STATS_PER_MULT 100

S8 ueStatsHdr[TS_MAX_UE_HDR];
S8 cellStatsHdr[TS_MAX_CELL_HDR];
PRIVATE Void TSInfGenUeStatsHdr ARGS((Void));
PRIVATE Void TSInfGenCellStatsHdr ARGS((Void));
PRIVATE Void TSInfStatsFileInit ARGS ((FILE   **fp));
PRIVATE Void TSInfSockBasedStatsInit ARGS((Void));
PRIVATE Void TSInfSockBasedStatsDeInit ARGS((Void));
EXTERN Void TSInfCfgCL ARGS((Void));

#ifdef ANSI
PUBLIC Void TSInfCfgCL
(
)
#else
PUBLIC Void TSInfCfgCL()
#endif
{
   TRC2(TSInfCfgCL)

   smBuildYsTenbStatsCntrl(tsCb.statsPer);

   RETVOID;
}

#ifdef ANSI
PUBLIC Void TSInfSetEnbIp
(
 U32 enbIpAddr
)
#else
PUBLIC Void TSInfSetEnbIp(U32 enbIpAddr)
 U32 enbIpAddr;
#endif
{
   TRC2(TSInfSetEnbIp)

   if (tsCb.enbIp == 0)
   {
      /* Initial Configuration */
      tsCb.enbIp = htonl(enbIpAddr);
   }
   else if (tsCb.enbIp != enbIpAddr)
   {
      /* EnbIP changed, Reopen Socket */
      TSInfSockBasedStatsDeInit();
      tsCb.enbIp = htonl(enbIpAddr);
      TSInfSockBasedStatsInit();
   }
   RETVOID;
}

#ifdef ANSI
PUBLIC S16 TSInfInitStatsFrmWork
(
 Bool   tenbSocketStats,
 Bool   tenbFileStats,
 Bool   tenbConsoleStats,
 U32    tenbStatsPeriodicity,
 U32    tendStatsSocketPort
)
#else
PUBLIC S16 TSInfInitStatsFrmWork( tenbSocketStats, tenbFileStats,\
      tenbConsoleStats, tenbStatsPeriodicity, tendStatsSocketPort)
 Bool   tenbSocketStats;
 Bool   tenbFileStats;
 Bool   tenbConsoleStats;
 U32    tenbStatsPeriodicity;
 U32    tendStatsSocketPort;
#endif
{
   TRC2(TSInfInitStatsFrmWork)

   if (((tenbSocketStats == TRUE) ||
        (tenbFileStats == TRUE) ||
        (tenbConsoleStats == TRUE)) &&
       (tenbStatsPeriodicity == 0))
   {
      RETVALUE(RFAILED);
   }
   if (tsCb.initDone == FALSE)
   {
      printf("TENB CFG UPDATE [%d:%d:%d:%d:%d]\n", (int)tenbSocketStats, (int)tenbFileStats,
      (int)tenbConsoleStats, (int)tenbStatsPeriodicity, (int)tendStatsSocketPort);
      tsCb.sockSend = tenbSocketStats;
      tsCb.fileSend = tenbFileStats;
      tsCb.consPrint = tenbConsoleStats;
      tsCb.statsPer = tenbStatsPeriodicity * TS_OAM_STATS_PER_MULT;
      tsCb.sockPort = tendStatsSocketPort;
      tsCb.initDone = TRUE;
      if (tsCb.sockSend)
      {
         TSInfSockBasedStatsInit();
      }
      if (tsCb.fileSend)
      {
         tsCb.cmdForFileStats = TS_FILE_STATS_START;
      }
      if (tsCb.consPrint)
      {
         TSInfGenCellStatsHdr();
         TSInfGenUeStatsHdr();
      }
      //CL Would be configured post CL SM configuration
      //smBuildYsTenbStatsCntrl(tsCb.statsPer);
   }
   else
   {
      Bool sockSendPrev = tsCb.sockSend;
      Bool fileSendPrev = tsCb.fileSend;
      Bool consPrintPrev = tsCb.consPrint;
      U32  statsPerPrev = tsCb.statsPer;

      printf("TENB RECFG UPDATE [%d:%d:%d:%d:%d]\n", (int)tenbSocketStats, (int)tenbFileStats,
      (int)tenbConsoleStats, (int)tenbStatsPeriodicity, (int)tendStatsSocketPort);
      tsCb.sockSend = tenbSocketStats;
      tsCb.fileSend = tenbFileStats;
      tsCb.consPrint = tenbConsoleStats;
      tsCb.statsPer = tenbStatsPeriodicity * TS_OAM_STATS_PER_MULT;
      tsCb.sockPort = tendStatsSocketPort;

      if (statsPerPrev != tsCb.statsPer)
      {
         TSInfCfgCL();
      }
      if ((consPrintPrev == FALSE) && (tsCb.consPrint == TRUE))
      {
         TSInfGenCellStatsHdr();
         TSInfGenUeStatsHdr();
      }
      if ((fileSendPrev == TRUE) && (tsCb.fileSend == FALSE))
      {
         tsCb.cmdForFileStats = TS_FILE_STATS_STOP;
      }
      if ((fileSendPrev == FALSE) && (tsCb.fileSend == TRUE))
      {
         tsCb.cmdForFileStats = TS_FILE_STATS_START;
      }
      if ((sockSendPrev == TRUE) && (tsCb.sockSend == FALSE))
      {
         TSInfSockBasedStatsDeInit();
      }
      if ((sockSendPrev == FALSE) && (tsCb.sockSend == TRUE))
      {
         TSInfSockBasedStatsInit();
      }
   }
   RETVALUE(ROK);
}

#ifdef ANSI
PRIVATE Void TSInfStatsFileInit
(
 FILE    **fp
)
#else
PRIVATE Void TSInfStatsFileInit(fp)
 FILE    **fp;
#endif
{
   S8 timeStamp[75];

   TRC2(TSInfStatsFileInit)

   strcpy(tsCb.fileName, "TeNB_Stats_");;
   SGetTimeStamp(timeStamp);
   strcat(tsCb.fileName, timeStamp);
   strcat(tsCb.fileName, ".csv");
   *fp= fopen(tsCb.fileName, "w+");
   setvbuf(*fp, NULLP, _IOFBF, 4000);

   RETVOID;
}

#if 1
unsigned int totalDlTpt = 0;
unsigned int totalUlTpt = 0;
unsigned int  gEgtpUlPktDropCount = 0;
#endif

#ifdef ANSI
PRIVATE Void TSInfPrintUeStats
(
 TSInfL2UeStats    *s
)
#else
PRIVATE Void TSInfPrintUeStats(s)
 TSInfL2UeStats    *s;
#endif
{
   S8 pBuf[1000];
   U32 k = 0;
   U32 dlBler, avgCw0Cqi, avgCw1Cqi, avgCw0iTbs, avgCw1iTbs;
   U32 ulBler, ulAvgCqi, ulAvgiTbs; 

   TRC2(TSInfPrintUeStats)

   for (k = 0; k < L2_STATS_MAX_CELLS; k++)
   {
      if ((s->nonPersistent.sch[k].dlAckNackCnt[0] + s->nonPersistent.sch[k].dlAckNackCnt[1]) == 0) s->nonPersistent.sch[k].dlAckNackCnt[0] = 1;
      dlBler = ((s->nonPersistent.sch[k].dlNackCnt[0] + s->nonPersistent.sch[k].dlNackCnt[1]) * 100)/
         (s->nonPersistent.sch[k].dlAckNackCnt[0] + s->nonPersistent.sch[k].dlAckNackCnt[1]); 

      if (s->nonPersistent.sch[k].dlNumCw0Cqi == 0) s->nonPersistent.sch[k].dlNumCw0Cqi = 1;
      avgCw0Cqi = s->nonPersistent.sch[k].dlSumCw0Cqi/s->nonPersistent.sch[k].dlNumCw0Cqi;
      if (s->nonPersistent.sch[k].dlNumCw1Cqi == 0) s->nonPersistent.sch[k].dlNumCw1Cqi = 1;
      avgCw1Cqi = s->nonPersistent.sch[k].dlSumCw1Cqi/s->nonPersistent.sch[k].dlNumCw1Cqi;
      if (s->nonPersistent.sch[k].dlNumCw0iTbs == 0) s->nonPersistent.sch[k].dlNumCw0iTbs = 1;
      avgCw0iTbs = s->nonPersistent.sch[k].dlSumCw0iTbs/s->nonPersistent.sch[k].dlNumCw0iTbs;
      if (s->nonPersistent.sch[k].dlNumCw1iTbs == 0) s->nonPersistent.sch[k].dlNumCw1iTbs = 1;
      avgCw1iTbs = s->nonPersistent.sch[k].dlSumCw1iTbs/s->nonPersistent.sch[k].dlNumCw1iTbs;
      if (s->nonPersistent.sch[k].ulAckNackCnt == 0) s->nonPersistent.sch[k].ulAckNackCnt = 1;
      ulBler = (s->nonPersistent.sch[k].ulNackCnt*100)/s->nonPersistent.sch[k].ulAckNackCnt;
      if (s->nonPersistent.sch[k].ulNumCqi == 0) s->nonPersistent.sch[k].ulNumCqi = 1;
      ulAvgCqi = s->nonPersistent.sch[k].ulSumCqi/s->nonPersistent.sch[k].ulNumCqi;
      if (s->nonPersistent.sch[k].ulNumiTbs == 0) s->nonPersistent.sch[k].ulNumiTbs = 1;
      ulAvgiTbs = s->nonPersistent.sch[k].ulSumiTbs/s->nonPersistent.sch[k].ulNumiTbs;
      /* TODO move out Other than nonPersistent.sch[] variables */

      sprintf(pBuf, "%-5u %-6u %-7u%-5u%-7u%-6u%-6u%-8u%-7u%-7u%-9u%-9u%-9u%-8u%-6u%-6u%-6u%-6u%-4u  |  %-8u%-5u%-7u%-6u%-5u%-6u",
            (unsigned int)s->rnti, (unsigned int)s->nonPersistent.sch[k].dlBo/(unsigned int)tsCb.statsPer, \
            (unsigned int)s->nonPersistent.sch[k].dlTpt/(unsigned int)tsCb.statsPer, \
            (unsigned int)s->nonPersistent.sch[k].dlTxOccns, (unsigned int)s->nonPersistent.sch[k].dlRetxOccns, \
            (unsigned int)dlBler, (unsigned int)s->nonPersistent.sch[k].dlDtxCnt[0], \
            (unsigned int)s->nonPersistent.sch[k].dlPrbUsg, (unsigned int)s->nonPersistent.sch[k].riCnt[0], \
            (unsigned int)s->nonPersistent.sch[k].riCnt[1], (unsigned int)avgCw0Cqi, (unsigned int)avgCw1Cqi, \
            (unsigned int)avgCw0iTbs, (unsigned int)avgCw1iTbs, (unsigned int)s->nonPersistent.sch[k].dlPdbLvl[0], \
            (unsigned int)s->nonPersistent.sch[k].dlPdbLvl[1],(unsigned int)s->nonPersistent.sch[k].dlPdbLvl[2], \
            (unsigned int)s->nonPersistent.sch[k].dlPdbLvl[3],(unsigned int)s->nonPersistent.sch[k].dlPdbLvl[4],
            (unsigned int)s->nonPersistent.sch[k].ulTpt/(unsigned int)tsCb.statsPer, \
            (unsigned int)s->nonPersistent.sch[k].ulTxOccns, (unsigned int)s->nonPersistent.sch[k].ulRetxOccns, \
            (unsigned int)ulBler, (unsigned int)ulAvgCqi, (unsigned int)ulAvgiTbs); 
#if 1
      {
          totalDlTpt += (unsigned int)s->nonPersistent.sch[k].dlTpt;
          totalUlTpt += (unsigned int)s->nonPersistent.sch[k].ulTpt;
      }
#endif

      puts(pBuf);
   }
   RETVOID;
}

#ifdef ANSI
PRIVATE Void TSInfGenUeStatsHdr
(
)
#else
PRIVATE Void TSInfGenUeStatsHdr()
#endif
{
   U32 widx=0;

   TRC2(TSInfGenUeStatsHdr)

   widx += snprintf(ueStatsHdr+widx, TS_MAX_UE_HDR-widx, "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   widx += snprintf(ueStatsHdr+widx, TS_MAX_UE_HDR-widx, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   widx += snprintf(ueStatsHdr+widx, TS_MAX_UE_HDR-widx, "%-5s %-6s%-7s%-5s%-7s%-6s%-6s%-8s%-7s%-7s%-9s%-9s%-9s%-8s%-6s%-6s%-6s%-6s%-2s  |  %-8s%-5s%-7s%-6s%-5s%-6s\n",
   "UEID", "BO", "TPT", "#TX", "#RETX", 
   "BLER", "#DTX", "PRB", "#RI_1", "#RI_2",
   "CW0_CQI", "CW1_CQI", "CW0_IT", "CW1_IT", "PDBL1", "PDBL2", "PDBL3", "PDBL4", "PDBLB",
   "UL_TPT", "#TX", "#RETX", "BLER", "CQI", "ITBS"); 
   widx += snprintf(ueStatsHdr+widx, TS_MAX_UE_HDR-widx, "%-5s %-6s%-7s%-5s%-7s%-6s%-6s%-8s%-7s%-7s%-9s%-9s%-9s%-8s%-6s%-6s%-6s%-6s%-2s  |  %-8s%-5s%-7s%-6s%-5s%-6s",
   "====", "--", "---", "---", "-----", 
   "----", "----", "---", "-----", "-----", 
   "-------", "-------", "------", "------","-----","-----","-----","-----","-----",
   "==----", "---", "-----", "----", "---", "----"); 
   /* Note: 583 Chars are written in ueStatsHdr so far. 
    * Update this numer of HDR is changed. */
   RETVOID;
}

#ifdef ANSI
PRIVATE Void TSInfPrintCellStats
(
 TSInfL2CellStats    *s
)
#else
PRIVATE Void TSInfPrintCellStats(s)
 TSInfL2CellStats    *s;
#endif
{
   S8 pBuf[1000];
   U32 dlBler, dlDtxCnt=0, avgCw0Cqi, avgCw1Cqi, avgCw0iTbs, avgCw1iTbs;
   U32 ulBler, ulAvgCqi, ulAvgiTbs; 
   U32 i, j, totNack=0, totAckNack=0;

   TRC2(TSInfPrintCellStats)

   for (j=0; j<4; j++)
   {
      dlDtxCnt += s->sch.dlDtx[0][j];
   }

   for (i=0; i<2; i++)
      for (j=0; j<4; j++)
	 {
            totNack += s->sch.dlNack[i][j];
	 }
   for (i=0; i<2; i++)
      for (j=0; j<4; j++)
	 {
            totAckNack += s->sch.dlAckNack[i][j];
	 }
   if (totAckNack == 0) 
   {
      totAckNack = 1;
   }
   dlBler = (totNack*100)/totAckNack;

   totNack=0;
   totAckNack=0;
   for (j=0; j<4; j++)
   {
      totNack += s->sch.ulNack[j];
   }
   for (j=0; j<4; j++)
   {
      totAckNack += s->sch.ulAckNack[j];
   }
   if (totAckNack == 0) 
   {
      totAckNack = 1;
   }
   ulBler = (totNack*100)/totAckNack;

   if (s->sch.dlNumCw0Cqi == 0) s->sch.dlNumCw0Cqi = 1;
   avgCw0Cqi = s->sch.dlSumCw0Cqi/s->sch.dlNumCw0Cqi;
   if (s->sch.dlNumCw1Cqi == 0) s->sch.dlNumCw1Cqi = 1;
   avgCw1Cqi = s->sch.dlSumCw1Cqi/s->sch.dlNumCw1Cqi;
   if (s->sch.dlNumCw0iTbs == 0) s->sch.dlNumCw0iTbs = 1;
   avgCw0iTbs = s->sch.dlSumCw0iTbs/s->sch.dlNumCw0iTbs;
   if (s->sch.dlNumCw1iTbs == 0) s->sch.dlNumCw1iTbs = 1;
   avgCw1iTbs = s->sch.dlSumCw1iTbs/s->sch.dlNumCw1iTbs;
   if (s->sch.ulNumCqi == 0) s->sch.ulNumCqi = 1;
   ulAvgCqi = s->sch.ulSumCqi/s->sch.ulNumCqi;
   if (s->sch.ulNumiTbs == 0) s->sch.ulNumiTbs = 1;
   ulAvgiTbs = s->sch.ulSumiTbs/s->sch.ulNumiTbs;

   sprintf(pBuf, "%-10u %-6u%-6u%-8u%-7u%-6u%-9u%-9u%-10u%-10u%-10u%-8u%-5u%-6u",
   (unsigned int)1, (unsigned int)dlBler, (unsigned int)dlDtxCnt, (unsigned int)s->sch.dlPrbUsage[0], (unsigned int)s->sch.riCnt[0], (unsigned int)s->sch.riCnt[1], 
   (unsigned int)avgCw0Cqi, (unsigned int)avgCw1Cqi, (unsigned int)avgCw0iTbs, (unsigned int)avgCw1iTbs,
   (unsigned int)ulBler, (unsigned int)s->sch.ulPrbUsage[0], (unsigned int)ulAvgCqi, (unsigned int)ulAvgiTbs); 
   puts(pBuf);
   sprintf(pBuf, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
   puts(pBuf);
   sprintf(pBuf, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
   puts(pBuf);

   RETVOID;
}

#ifdef ANSI
PRIVATE Void TSInfGenCellStatsHdr
(
)
#else
PRIVATE Void TSInfGenCellStatsHdr()
#endif
{
   U32 widx=0;

   TRC2(TSInfGenCellStatsHdr)

   widx += snprintf(cellStatsHdr+widx, TS_MAX_CELL_HDR-widx, "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   widx += snprintf(cellStatsHdr+widx, TS_MAX_CELL_HDR-widx, "%-10s %-6s%-6s%-8s%-7s%-6s%-9s%-9s%-10s%-10s%-10s%-8s%-5s%-6s\n",
   "CELLID", "BLER", "#DTX", "PRB", "#RI_1", "#RI_2", 
   "CW0_CQI", "CW1_CQI", "CW0_ITBS", "CW1_ITBS",
   "ULBLER", "PRB", "CQI", "ITBS"); 
   widx += snprintf(cellStatsHdr+widx, TS_MAX_CELL_HDR-widx, "%-10s %-6s%-6s%-8s%-7s%-6s%-9s%-9s%-10s%-10s%-10s%-8s%-5s%-6s",
   "======", "----", "----", "---", "-----", "-----", 
   "-------", "-------", "--------", "--------",
   "==----", "---", "---", "----"); 
   /* Note: 335 Chars are written in cellStatsHdr so far. 
    * Update this numer of HDR is changed. */
   RETVOID;
}

#ifdef ANSI
PUBLIC Void TSInfHdlL2UeStatsInd
(
 Pst               *pst,
 SuId              suId,
 TSInfL2UeStats    *stats
)
#else
PUBLIC Void TSInfHdlL2UeStatsInd(pst, suId, stats)
 Pst               *pst;
 SuId              suId;
 TSInfL2UeStats    *stats;
#endif
{
   U32 k = 0;
   
   TRC2(TSInfHdlL2UeStatsInd)

   if (tsCb.consPrint)
   {
      if (ueStatsCount == 0)
      {
         puts(ueStatsHdr);
      }
      TSInfPrintUeStats(stats);
#if 0
      printf("\n#####################################\n");
      printf("Rishi: Persistent %u,%u,%u,",
            (unsigned int)stats->persistent.numActivation,
            (unsigned int)stats->persistent.numDeactivation,
            (unsigned int)stats->persistent.activatedSCells);
      printf("\n#####################################\n");
#endif
   }

   if (tsCb.fptr)
   {

      fprintf(tsCb.fptr, "%u,",
               (unsigned int)stats->rnti);
      for (k = 0; k < L2_STATS_MAX_CELLS; k++)
      {
         fprintf(tsCb.fptr, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,",
               (unsigned int)stats->nonPersistent.sch[k].dlTxOccns,
               (unsigned int)stats->nonPersistent.sch[k].dlRetxOccns,
               (unsigned int)stats->nonPersistent.sch[k].dlPrbUsg,
               (unsigned int)stats->nonPersistent.sch[k].dlAckNackCnt[0],
               (unsigned int)stats->nonPersistent.sch[k].dlAckNackCnt[1], 
               (unsigned int)stats->nonPersistent.sch[k].dlNackCnt[0],
               (unsigned int)stats->nonPersistent.sch[k].dlNackCnt[1],
               (unsigned int)stats->nonPersistent.sch[k].dlDtxCnt[0],
               (unsigned int)stats->nonPersistent.sch[k].dlDtxCnt[1],
               (unsigned int)stats->nonPersistent.sch[k].dlSumCw0Cqi,
               (unsigned int)stats->nonPersistent.sch[k].dlNumCw0Cqi,
               (unsigned int)stats->nonPersistent.sch[k].dlSumCw1Cqi,
               (unsigned int)stats->nonPersistent.sch[k].dlNumCw1Cqi,
               (unsigned int)stats->nonPersistent.sch[k].dlSumCw0iTbs,
               (unsigned int)stats->nonPersistent.sch[k].dlNumCw0iTbs,
               (unsigned int)stats->nonPersistent.sch[k].dlSumCw1iTbs,
               (unsigned int)stats->nonPersistent.sch[k].dlNumCw1iTbs,
               (unsigned int)stats->nonPersistent.sch[k].cqiDropCnt,
               (unsigned int)stats->nonPersistent.sch[k].dlPdbLvl[0],
               (unsigned int)stats->nonPersistent.sch[k].dlPdbLvl[1], 
               (unsigned int)stats->nonPersistent.sch[k].dlPdbLvl[2],
               (unsigned int)stats->nonPersistent.sch[k].dlPdbLvl[3],
               (unsigned int)stats->nonPersistent.sch[k].dlPdbLvl[4],
               (unsigned int)stats->nonPersistent.sch[k].riCnt[0],
               (unsigned int)stats->nonPersistent.sch[k].riCnt[1],
               (unsigned int)stats->nonPersistent.sch[k].riCnt[2],
               (unsigned int)stats->nonPersistent.sch[k].riCnt[3],
               (unsigned int)stats->nonPersistent.sch[k].dlBo,
               (unsigned int)stats->nonPersistent.sch[k].dlTpt,
               (unsigned int)stats->nonPersistent.sch[k].ulTxOccns,
               (unsigned int)stats->nonPersistent.sch[k].ulRetxOccns,
               (unsigned int)stats->nonPersistent.sch[k].ulPrbUsg,
               (unsigned int)stats->nonPersistent.sch[k].ulAckNackCnt,
               (unsigned int)stats->nonPersistent.sch[k].ulNackCnt,
               (unsigned int)stats->nonPersistent.sch[k].ulDtxCnt,
               (unsigned int)stats->nonPersistent.sch[k].ulSumCqi,
               (unsigned int)stats->nonPersistent.sch[k].ulNumCqi,
               (unsigned int)stats->nonPersistent.sch[k].ulSumiTbs,
               (unsigned int)stats->nonPersistent.sch[k].ulNumiTbs,
               (unsigned int)stats->nonPersistent.sch[k].ulTpt);
      }
      fprintf(tsCb.fptr, "%u,%u,%u,",
            (unsigned int)stats->nonPersistent.pdcp.dlPdcpDropCnt,
            (unsigned int)stats->nonPersistent.pdcp.dlFlowCtrlDropCnt,
            (unsigned int)stats->nonPersistent.rlc.ulReOdrTmrExpCnt);
      fprintf(tsCb.fptr, "%u,%u,%u,",
            (unsigned int)stats->persistent.numActivation,
            (unsigned int)stats->persistent.numDeactivation,
            (unsigned int)stats->persistent.activatedSCells);
   }
   if (tsCb.startSockSend)
   {
      sockStatsBuf[bufWritIdx] = stats->rnti;
      bufWritIdx++;
      cmMemcpy((U8*)(sockStatsBuf+bufWritIdx), (U8*)(&stats->nonPersistent), sizeof(stats->nonPersistent));
      bufWritIdx += (sizeof(stats->nonPersistent)/sizeof(U32));
      cmMemcpy((U8*)(sockStatsBuf+bufWritIdx), (U8*)(&stats->persistent), sizeof(stats->persistent));
      bufWritIdx += (sizeof(stats->persistent)/sizeof(U32));
   }

   ueStatsCount++;

   RETVOID;
}

#ifdef ANSI
PUBLIC Void TSInfHdlL2CellStatsInd
(
 Pst                 *pst,
 SuId                suId,
 TSInfL2CellStats    *stats
)
#else
PUBLIC Void TSInfHdlL2CellStatsInd(pst, suId, stats)
 Pst                 *pst;
 SuId                suId;
 TSInfL2CellStats    *stats;
#endif
{
   U32 i, j;
   static U32 cellsCount = 0;

   TRC2(TSInfHdlL2CellStatsInd)

   if (tsCb.consPrint)
   {
      puts(cellStatsHdr);
      TSInfPrintCellStats(stats);
   }
#if 1
   {
      printf("\n Total DL TPT::%u UL TPT::%u \n",
            totalDlTpt/(unsigned int)tsCb.statsPer,
            totalUlTpt/(unsigned int)tsCb.statsPer);

      printf("Egtp Ul DropCount %u\n",
            gEgtpUlPktDropCount);
      totalDlTpt = 0;
      totalUlTpt = 0;
      gEgtpUlPktDropCount = 0;
   }
   
   cellsCount++;

#endif   
   cellsCount++;

   if (tsCb.fptr)
   {
      fprintf(tsCb.fptr, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,", 
      (unsigned int)stats->sch.msg4Fail,
      (unsigned int)stats->sch.msg3Fail,
      (unsigned int)stats->sch.dlSumCw0Cqi,
      (unsigned int)stats->sch.dlNumCw0Cqi,
      (unsigned int)stats->sch.dlSumCw1Cqi,
      (unsigned int)stats->sch.dlNumCw1Cqi,
      (unsigned int)stats->sch.dlSumCw0iTbs,
      (unsigned int)stats->sch.dlNumCw0iTbs,
      (unsigned int)stats->sch.dlSumCw1iTbs,
      (unsigned int)stats->sch.dlNumCw1iTbs,
      (unsigned int)stats->sch.riCnt[0], (unsigned int)stats->sch.riCnt[1], (unsigned int)stats->sch.riCnt[2], (unsigned int)stats->sch.riCnt[3]);

      for (i=0; i<2; i++)
         for (j=0; j<4; j++)
       {
               fprintf(tsCb.fptr, "%u,", (unsigned int)stats->sch.dlAckNack[i][j]);
       }
      for (i=0; i<2; i++)
         for (j=0; j<4; j++)
       {
               fprintf(tsCb.fptr, "%u,", (unsigned int)stats->sch.dlNack[i][j]);
       }
      for (i=0; i<2; i++)
         for (j=0; j<4; j++)
       {
               fprintf(tsCb.fptr, "%u,", (unsigned int)stats->sch.dlDtx[i][j]);
       }
      for (i=0; i<4; i++)
       {
               fprintf(tsCb.fptr, "%u,", (unsigned int)stats->sch.ulAckNack[i]);
       }
      for (i=0; i<4; i++)
       {
               fprintf(tsCb.fptr, "%u,", (unsigned int)stats->sch.ulNack[i]);
       }
      for (i=0; i<4; i++)
       {
               fprintf(tsCb.fptr, "%u,", (unsigned int)stats->sch.ulDtx[i]);
       }
      for (i=0; i<10; i++)
       {
               fprintf(tsCb.fptr, "%u,", (unsigned int)stats->sch.dlPrbUsage[i]);
       }
      for (i=0; i<10; i++)
       {
               fprintf(tsCb.fptr, "%u,", (unsigned int)stats->sch.ulPrbUsage[i]);
       }
      for (i=0; i<10; i++)
       {
               fprintf(tsCb.fptr, "%u,", (unsigned int)stats->sch.dlPdbRatio[i]);
       }
      fprintf(tsCb.fptr, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,", 
      (unsigned int)stats->sch.avgTtiProcTime,
      (unsigned int)stats->sch.cntTtiProcTime1000,
      (unsigned int)stats->sch.cntTtiProcTime900,
      (unsigned int)stats->sch.cntTtiProcTime800,
      (unsigned int)stats->sch.cntTtiProcTime700,
      (unsigned int)stats->sch.cntTtiProcTime600,
      (unsigned int)stats->sch.cntTtiProcTime500,
      (unsigned int)stats->sch.ulSumCqi,
      (unsigned int)stats->sch.ulNumCqi,
      (unsigned int)stats->sch.ulSumiTbs,
      (unsigned int)stats->sch.ulNumiTbs,
      (unsigned int)stats->rlc.maxRlcSrbRetxFail,
      (unsigned int)stats->rlc.maxRlcDrbRetxFail,
      (unsigned int)stats->rlc.reOdrTmrExp);

      if(cellsCount == wrSmDfltNumCells)
      {
         fprintf(tsCb.fptr, "%u,%u \n",(unsigned int)ueStatsCount,
               (unsigned int)cellsCount);
         fflush(tsCb.fptr);
      }
   }

   if (tsCb.startSockSend)
   {
      int ret;

      sockStatsBuf[bufWritIdx] = stats->cellId;
      bufWritIdx++;
      cmMemcpy((U8*)(sockStatsBuf+bufWritIdx), (U8*)(&stats->sch), sizeof(stats->sch));
      bufWritIdx += (sizeof(stats->sch)/sizeof(U32));
      cmMemcpy((U8*)(sockStatsBuf+bufWritIdx), (U8*)(&stats->rlc), sizeof(stats->rlc));
      bufWritIdx += (sizeof(stats->rlc)/sizeof(U32));
      
      if(cellsCount == wrSmDfltNumCells)
      {
         sockStatsBuf[bufWritIdx] = ueStatsCount;
         bufWritIdx++;
         sockStatsBuf[bufWritIdx] = cellsCount;
         bufWritIdx++;
         ret = sendto(sockFd, (char *)sockStatsBuf, (bufWritIdx*sizeof(U32)), 0, (struct sockaddr *)&addrOthr, addrOthrLen);    
         if (ret < 0)
         {
            printf("Error sending data on SOCKET!\n");    
         }

      }
   }

  if(cellsCount == wrSmDfltNumCells)
  {
     if (tsCb.fptr)
     {
        cellStatsCount++;
        if (cellStatsCount % TS_MAX_FILE_RECORDS == 0)
        {
           /* After storing TS_MAX_FILE_RECORDS records of <UE1_STATS>....<UEn_STATS><CELL_STATS><n>
            * Close and send this file and create a new file */
           fclose(tsCb.fptr);
           //TODO TSInfStatsFileSend();
           TSInfStatsFileInit(&tsCb.fptr);
        }
     }
  }

   if (tsCb.cmdForFileStats == TS_FILE_STATS_START)
   {
      cellStatsCount = 0;
      TSInfStatsFileInit(&tsCb.fptr);
      tsCb.cmdForFileStats = TS_INVALID_VALUE;
   }
   else if (tsCb.cmdForFileStats == TS_FILE_STATS_STOP)
   {
      fclose(tsCb.fptr);
      //TODO TSInfStatsFileSend();
      tsCb.fptr = NULLP;
      tsCb.cmdForFileStats = TS_INVALID_VALUE;
   }

   if(cellsCount == wrSmDfltNumCells)
   {/* Reset the variables */
      bufWritIdx = 0;
      ueStatsCount = 0;
      cellsCount = 0; 
   }

   RETVOID;
}

#ifdef ANSI
PRIVATE Void *TSInfSockThrdCalBkFunc
(
Void *arg
)
#else
PRIVATE Void *TSInfSockThrdCalBkFunc()
Void *arg;
#endif
{
   struct sockaddr_in addr_me;  
   int addrLen;  

   TRC2(TSInfSockThrdCalBkFunc)

   pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

   sockFd = socket(AF_INET, SOCK_DGRAM, 0);  
   if (sockFd < 0) 
   {  
     printf("Error creating socket!\n");  
     exit(1);  
   }  

   memset(&addr_me, 0, sizeof(addr_me));  
   addr_me.sin_family = AF_INET;  
   addr_me.sin_addr.s_addr = tsCb.enbIp; /*inet_addr("10.188.6.38");*/ 
   addr_me.sin_port = htons(tsCb.sockPort);  
   addrLen = sizeof(addr_me);  

   if (bind(sockFd, &addr_me, addrLen) == -1)
   {
      printf("Error binding!\n");  
      exit(1);
   }
#if 0
   {
      struct in_addr ipAddr;
      ipAddr.s_addr = tsCb.enbIp;
      printf("!!!!!!Enodeb IP address is %s\n", inet_ntoa(ipAddr));
   }

#endif

   while(1)
   {
      char cmd[10];
      int cmdLen;
      struct sockaddr_in tempAddrOthr;  
      socklen_t tempAddrOthrLen = sizeof(tempAddrOthr);

      cmdLen = recvfrom(sockFd, cmd, 10, 0, (struct sockaddr*)&tempAddrOthr, &tempAddrOthrLen);
      cmd[cmdLen] = 0;
      addrOthr = tempAddrOthr;
      addrOthrLen = tempAddrOthrLen;
      printf("RCVD CMD [%s] from IP[%s] Port[%d]\n", cmd, inet_ntoa(addrOthr.sin_addr), ntohs(addrOthr.sin_port));
      if (strcmp(cmd, "START") == 0)
      {
         tsCb.startSockSend = TRUE;
      }
      else if (strcmp(cmd, "STOP") == 0)
      {
         tsCb.startSockSend = FALSE;
      }
      else
      {
         printf("INVALID COMMAND<%s> FROM TOOL\n", cmd); 
      }
   }
}

#ifdef ANSI
PRIVATE Void TSInfSockBasedStatsDeInit
(
)
#else
PRIVATE Void TSInfSockBasedStatsDeInit()
#endif
{
   TRC2(TSInfSockBasedStatsDeInit)

   pthread_cancel(sockThrdId);
   close(sockFd);
   tsCb.startSockSend = FALSE;

   RETVOID;
}

#ifdef ANSI
PRIVATE Void TSInfSockBasedStatsInit
(
)
#else
PRIVATE Void TSInfSockBasedStatsInit()
#endif
{
   pthread_attr_t attr;
   struct sched_param tskIdRsysHwparam;
   
   TRC2(TSInfSockBasedStatsInit)

   tskIdRsysHwparam.sched_priority = sched_get_priority_min(SCHED_RR);
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

   tskIdRsysHwparam.sched_priority = sched_get_priority_min(SCHED_RR);
   
   if ((pthread_create(&sockThrdId, &attr, TSInfSockThrdCalBkFunc, NULLP)) != 0)
   {
      pthread_attr_destroy(&attr);
      RETVOID;
   }
   pthread_setschedparam(sockThrdId, SCHED_RR, &tskIdRsysHwparam);

   RETVOID;
}
#endif /* TENB_STATS */
/**********************************************************************
         End of file:     wr_tenb_stats.c@@/main/tenb_5.0_RIB/3 - Tue Oct 27 14:21:17 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------

*********************************************************************91*/
