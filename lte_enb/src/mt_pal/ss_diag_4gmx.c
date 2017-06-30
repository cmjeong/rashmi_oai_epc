

/********************************************************************20**
 
     Name:     System Services -- Logging functions
 
     Type:     C source file
 
     Desc:     Source code for System Services Logging.
 
     File:     
 
     Sid:      
 
     Prg:      pakumar
  
*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "rb_ss.h"

/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "cm_lib.x"
#include "ss_diag.h"        /* Common log file */ 

/*Globale variables*/
PRIVATE U8 ssDiagBufEntMap[SS_MAX_ENT][SS_MAX_INST];
PUBLIC    SsDiagCirBuf ssDiagCirBuf[SS_DIAG_MAX_CIRC_BUF];
PUBLIC U32 numTti = 0;
/**
 *  @brief  This function initializes the log buffer with respect to
 *  entity and instance. 
 *
 *  @details  This function initializes the log buffer with respect to
 *  entity and instance. 
 *  Function:ssDiagInitBuf
 *
 *  @param[in]  Void      
 *
 *  @return Void          
 */
#ifdef ANSI
PUBLIC S16 ssDiagInitBuf
(
 void
)
#else
PUBLIC S16 ssDiagInitBuf(Void)
#endif 
{
   S16 ret = ROK;

   ret = ssDiagInitCircBuf(&(ssDiagCirBuf[SS_DIAG_BUF1]), SS_DIAG_BUF1_LEN);
   ret = ssDiagInitCircBuf(&(ssDiagCirBuf[SS_DIAG_BUF2]), SS_DIAG_BUF2_LEN);

   RETVALUE(ret);
}

/**
 *  @brief  This function initializes the log buffer with respect to
 *  entity and instance. 
 * 
 *  @details  This function initializes the log buffer with respect to
 *  entity and instance. 
 *  Function:ssDiagInitBufEntMap
 *
 *  @param[in]  Void      
 *
 *  @return S16          
 *        -# ROK     - successful.
 *        -# RFAILED - failure.
 */
#ifdef ANSI
PRIVATE Void ssDiagInitBufEntMap
(
 void
)
#else
PRIVATE Void ssDiagInitBufEntMap(Void)
#endif
{
   ssDiagBufEntMap[ENTSZ][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTSB][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTNH][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTSM][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTCZ][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTHI][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTEG][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTWR][SS_DIAG_INST0] = 0;

#ifdef MSPD
   ssDiagBufEntMap[ENTYS][SS_DIAG_INST0] = 1;
   ssDiagBufEntMap[ENTTF][SS_DIAG_INST0] = 1;
   ssDiagBufEntMap[ENTRG][SS_DIAG_INST1] = 1;
   ssDiagBufEntMap[ENTRG][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTKW][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTPJ][SS_DIAG_INST0] = 0;
#else
   ssDiagBufEntMap[ENTYS][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTTF][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTRG][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTRG][SS_DIAG_INST1] = 0;
   ssDiagBufEntMap[ENTKW][SS_DIAG_INST0] = 0;
   ssDiagBufEntMap[ENTPJ][SS_DIAG_INST0] = 0;
#endif

   RETVOID;
}/* end of ssDiagInitBufEntMap */
 
/**
 *    @brief  This function initializes SSI logging circular buffers.
 *    @details  This function initializes SSI logging circular buffers.
 *    Function:ssDiagInitCircBuf
 *
 *    @param[in]  bufPtr
 *    @param[in]  maxBufLen
 *
 *    @return S16
 *         -# ROK     - successful.
 *         -# RFAILED - failure.
 */
#ifdef ANSI
PUBLIC S16 ssDiagInitCircBuf
(
SsDiagCirBuf *bufPtr,
U16          maxBufLen
)
#else
PUBLIC S16 ssDiagInitCircBuf(bufPtr, maxBufLen)
SsDiagCirBuf *bufPtr;
U16          maxBufLen;
#endif
{
   /* Initialize the entity buffer ID mapping  */
   ssDiagInitBufEntMap();

   bufPtr->rear = 0;
   bufPtr->front = 0;
   bufPtr->logBuf = NULLP;
   bufPtr->nLen = maxBufLen;
   bufPtr->noLogLost = 0;
   bufPtr->nLen = maxBufLen;

   /* allocate Buffer for storing logging information */
   SGetSBuf(DFLT_REGION, DFLT_POOL, (Data **)&(bufPtr->logBuf),
         (sizeof(SsDiagBuf) * maxBufLen));
   if(bufPtr->logBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }
   cmMemset((U8*)( bufPtr->logBuf), 0, (sizeof(SsDiagBuf) * maxBufLen));

   RETVALUE(ROK);
} /* end of ssDiagInitCircBuf */
 
/**
 *   @brief  This function provides the index to place the log in the circular
 *           buffer.
 *   @details  This function provides the index to place the log in the circular
 *           buffer.
 *           Function: ssDiagGetBufIdx
 *
 *   @param[in]  bufPtr
 *   @param[in]  trgBufPtr
 *
 *   @return S16
 *        -# ROK     - successful.
 *        -# RFAILED - failure.
 */
#ifdef ANSI
PRIVATE S16 ssDiagGetBufIdx
(
 SsDiagCirBuf *bufPtr,
 SsDiagBuf    **trgBufPtr
)
#else
PRIVATE S16 ssDiagGetBufIdx (bufPtr, trgBufPtr)
SsDiagCirBuf *bufPtr;
SsDiagBuf    **trgBufPtr;
#endif
{
   U32 tmp;

   /* Check for space in Circular Buffer */
   if(bufPtr->front == ((bufPtr->rear + SS_DIAG_MIN_BUF_DIFF) % bufPtr->nLen))
   {
      bufPtr->logLostState = SS_DIAG_RPT_PEND;
      bufPtr->noLogLost++;
      RETVALUE(RFAILED);
   }

   /* Check and report if any logs lost */
   if(bufPtr->noLogLost > 0)
   { 
      ++bufPtr->rear;
      tmp = bufPtr->rear % bufPtr->nLen;
      bufPtr->rear = tmp;
      bufPtr->logBuf[bufPtr->rear].type = SS_DIAG_MSG_TYPE_NOLOGLOST;
      bufPtr->logBuf[bufPtr->rear].arg1 = bufPtr->noLogLost;
      SS_DIAG_GET_TIME_STAMP( bufPtr->logBuf[bufPtr->rear].timRef);
      bufPtr->noLogLost = 0; 
      bufPtr->logLostState = SS_DIAG_REPORTED;
      if(bufPtr->front == (bufPtr->rear + SS_DIAG_MIN_BUF_DIFF))
      {
         bufPtr->noLogLost++;
         RETVALUE(RFAILED);
      }
   }

   /* Get the log record for pointed by the rear pointer */
   *trgBufPtr = &(bufPtr->logBuf[bufPtr->rear]);
   bufPtr->rear = ((++bufPtr->rear) % bufPtr->nLen);

   if(bufPtr->logLostState == SS_DIAG_REPORTED)
   {
      bufPtr->logLostState = SS_DIAG_NORMAL;
   }

   RETVALUE(ROK);
} /* end of ssDiagGetBufIdx */
 
/**
 *    @brief  This function stores log information in the index pointed by the rear
 *            pointer in Circular Buffer.
 *    @details  This function stores log information in the index pointed by the rear
 *            pointer in Circular Buffer.
 *    Function:ssDiagFix 
 *    @param[in]  entId
 *    @param[in]  logLvl
 *    @param[in]  tknId
 *    @param[in]  splArg
 *    @param[in]  arg1
 *    @param[in]  arg2
 *    @param[in]  arg3
 *    @param[in]  arg4
 *
 *    @return Void
 */
#ifdef ANSI
PUBLIC Void ssDiagFix 
(
U32   tknId,
U32   splArgEnum,
U32   entId,
U32   instId,
U32   logLvl,
U32   logType,
U32   splArg,
U32   arg1,
U32   arg2,
U32   arg3,
U32   arg4,
S8    *string
)
#else
PUBLIC Void ssDiagFix(tknId, splArgEnum, entId, instId, logLvl, logType, splArg, arg1, arg2, arg3, arg4, *string)
U32   tknId;
U32   splArgEnum,
U32   entId;
U32   instId;
U32   logLvl;
U32   logType;
U32   splArg;
U32   arg1;
U32   arg2;
U32   arg3;
U32   arg4;
S8    *string;
#endif
{
   SsDiagBuf    *tmpRecBuf = NULLP; 
   SsDiagCirBuf *bufPtr = NULLP;
   S16         ret = RFAILED;

   bufPtr = &ssDiagCirBuf[ssDiagBufEntMap[entId][instId]];
   /* Get the index for the log placing in the circular Q */
   ret = ssDiagGetBufIdx(bufPtr, &tmpRecBuf);
   if((ret != ROK) || (tmpRecBuf == NULLP))
   {
      /* Return by dropping the log if we don't have any place to hold log */
      MSPD_DBG(" ssDiagGetBufIdx failed logs are droped\n");  
      RETVOID;
   }

   /* Get the time stamp or time reference */
   SS_DIAG_GET_TIME_STAMP(tmpRecBuf->timRef); 

   /* Store the logs in the index pointed by the rear pointer */
   tmpRecBuf->tknId   = tknId;
   tmpRecBuf->entInstId   = entId;
   tmpRecBuf->entInstId <<= 16;
   tmpRecBuf->entInstId  = (tmpRecBuf->entInstId | instId);
   tmpRecBuf->level   = logLvl;
   tmpRecBuf->type    = logType;
   tmpRecBuf->splArg  = splArg;
   tmpRecBuf->arg1    = arg1;
   tmpRecBuf->arg2    = arg2;
   tmpRecBuf->arg3    = arg3;
   tmpRecBuf->arg4    = arg4;
   RETVOID;
} /* end of ssDiagFix */
 
/**
 *    @brief  This function will call packing function.
 *
 *    @detail This function will be called from convergence layer.
 *
 *    @param[in]  pst 
 *
 *    @return S16
 *         -# ROK     - successful.
 *         -# RFAILED - failure.
 */
 
#ifdef ANSI
PUBLIC S16 ssDiagSndToPack
(
Pst *pst
)
#else
PUBLIC S16 ssDiagSndToPack (pst)
Pst *pst;
#endif
{
   S16 ret = ROK;
 
   if(numTti % 10 == 0)
   {
      /* Packing logs into buffer to post it to upper layer */
      ret = ssPackLogs(pst);
   } 

   RETVALUE(ret);
} /* end of ssDiagSndToPack */ 


/**
 *    @brief  This function will pack the buffer in the post structure and post
 *            it to the layer manager.
 *
 *    @detail This function will be called after every 10 TTI's.
 *
 *    @param  pst 
 *
 *    @return S16
 *         -# ROK     - successful.
 *         -# RFAILED - failure.
 */
 
#ifdef ANSI
PUBLIC S16 ssPackLogs
(
Pst *pst
)
#else
PUBLIC S16 ssPackLogs (Pst *pst)
Pst *pst;
#endif
{
   U16         cnt;
   U16         bufType = 0;
   Buffer      *mBuf = NULLP;
   SsDiagCirBuf *tmpBuf = NULLP;
   U32         tmp = 0;

   /* Check for any new buffers in the circular buffer */
   if(ssDiagCirBuf[SS_DIAG_BUF1].rear != ssDiagCirBuf[SS_DIAG_BUF1].front)
   {
      /* Allocate the buffer for packing the log buffer */
      SGetMsg(DFLT_REGION, DFLT_POOL, &mBuf);

      if(mBuf == NULLP)
      {
         MSPD_DBG("Mbuf is null ssPackLogs \n");  
         RETVALUE(RFAILED);
      }

      /* Initialize the count variable and buffer type. Also, get the 
       * circular buffer */
      cnt = 0;
      bufType = SS_DIAG_BUF1;
      tmpBuf = &ssDiagCirBuf[SS_DIAG_BUF1];

      /* Pack the log information one by one into mbuf */
      while((tmpBuf->rear != tmpBuf->front) && (cnt < SS_DIAG_MAX_LOG_POST))
      {
         SAddPreMsgMult((U8*)&(tmpBuf->logBuf[tmpBuf->front]), sizeof(SsDiagBuf), mBuf); 
         /* packing two buffers in one mBuf to post to uarm */
         cnt++;
         ++tmpBuf->front;
         tmp = tmpBuf->front % tmpBuf->nLen;
         tmpBuf->front = tmp;
      }

      /* Pack the number of log information packed and buffer type into mBuf */
      SAddPreMsgMult((U8*)&cnt, sizeof(U16), mBuf);
      SAddPreMsgMult((U8*)&bufType, sizeof(U16), mBuf);

      /* Assign the respective post event type and post the buffer to UARM */
      pst->event = EVTLYSRSYSLOG;
      SPstTsk(pst, mBuf);
   }

   /* Check for any new buffers in the circular buffer */
   if(ssDiagCirBuf[SS_DIAG_BUF2].rear != ssDiagCirBuf[SS_DIAG_BUF2].front)
   {
      /* Allocate the buffer for packing the log buffer */
      SGetMsg(DFLT_REGION, DFLT_POOL, &mBuf);
      if(mBuf == NULLP)
      {
         MSPD_DBG("Mbuf is null to ssPackLogs\n");  
         RETVALUE(RFAILED);
      }

      /* Initialize the count variable and buffer type. Also, get the 
       * circular buffer */
      cnt = 0;
      bufType = SS_DIAG_BUF2;
      tmpBuf = &ssDiagCirBuf[SS_DIAG_BUF2];

      /* Pack the log information one by one into mbuf */
      while((tmpBuf->rear != tmpBuf->front) && (cnt < SS_DIAG_MAX_LOG_POST))
      {
         SAddPreMsgMult((U8*)&(tmpBuf->logBuf[tmpBuf->front]), sizeof(SsDiagBuf), mBuf);
         /* packing two buffers in one mBuf to post to uarm */
         cnt++;
         ++tmpBuf->front;
         tmp = tmpBuf->front % tmpBuf->nLen;
         tmpBuf->front = tmp;
      }

      /* Pack the number of log information packed and buffer type into mBuf */
      SAddPreMsgMult((U8*)&cnt, sizeof(U16), mBuf);
      SAddPreMsgMult((U8*)&bufType, sizeof(U16), mBuf);

      /* Assign the respective post event type and post the buffer to UARM */
      pst->event = EVTLYSRSYSLOG;
      SPstTsk(pst, mBuf);
   }
   RETVALUE(ROK);
} /* end of ssPackLogs */
