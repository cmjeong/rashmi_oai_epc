
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_queue.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:26 2015

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
/* cm_xta_queue_c_001.main_2 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"

/* cm_xta_queue_c_001.main_2 Removed cm_xta_app.x for Psf-Diameter 1.1 */
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
PUBLIC S16 cmXtaInitQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC S16 cmXtaInitQ(msgQ)
CmXtaMsgQ   *msgQ;
#endif
{
   S16 ret;

   TRC2(cmXtaInitQ)

   /* Init message queue lock */
   SInitLock(&msgQ->qLock, SS_LOCK_MUTEX);

   /* zero the memory */
   CMXTA_ZERO(&msgQ->qElm, sizeof(CmXtaMsgQElm) * CMXTA_MSGQ_SIZE);

   msgQ->rdPtr = 0;
   msgQ->wrPtr = 0;

   if ((ret = cmXtaAppInitQ(msgQ)) != CMXTA_ERR_NONE)
      RETVALUE(ret);

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaInitQ */

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
PUBLIC Void cmXtaFlushQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC Void cmXtaFlushQ(msgQ)
CmXtaMsgQ *msgQ;
#endif
{
   /* local variables */
   CmXtaMsgQElm   *msg;          /* local QElm pointer      */

   TRC2(cmXtaFlushQ)

   /* Release any memory associated with the messages */
   while (cmXtaPopMsg(msgQ, &msg) == ROK)
      cmXtaFlushMsg(msgQ, msg);

   /* lock the message queue */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaFlushQ(): SLock()\n"));
   (Void) SLock(&msgQ->qLock);

   cmXtaAppFlushQ(msgQ);

   /* zero the memory */
   CMXTA_ZERO(&msgQ->qElm, sizeof(CmXtaMsgQElm) * CMXTA_MSGQ_SIZE);
   msgQ->rdPtr = 0;
   msgQ->wrPtr = 0;

   /* release the message queue lock */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaFlushQ(): SUnlock()\n"));
   (Void) SUnlock(&msgQ->qLock);

   RETVOID;
} /* cmXtaFlushQ */

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
PUBLIC S16 cmXtaPushMsg
(
CmXtaMsgQ *msgQ,
CmXtaMsgQElm  *msg            /* Message to be inserted in the queue */
)
#else
PUBLIC S16 cmXtaPushMsg(msgQ, msg)
CmXtaMsgQ *msgQ;
CmXtaMsgQElm  *msg;           /* Message to be inserted in the queue */
#endif
{
   U16   oldPtr;          /* saved pointer value */

   TRC2(cmXtaPushMsg)

   /* lock the message queue */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaPushMsg(): SLock()\n"));
   (Void) SLock(&msgQ->qLock);

   /* save the old pointer */
   oldPtr = msgQ->wrPtr;

   /* increment the write pointer */
   msgQ->wrPtr++;

   /* if write-ptr has reached end of the queue, roll it to the
    * head of the queue */
   if (msgQ->wrPtr == (U16) CMXTA_MSGQ_SIZE)
   {
      msgQ->wrPtr = 0;
   }

   /* Check if the queue is FULL */
   if (msgQ->wrPtr == msgQ->rdPtr)
   {
      /* We're losing primitives - we must prevent memory leaks */
      cmXtaFlushMsg(msgQ, msg);

      /* restore old write pointer */
      msgQ->wrPtr = oldPtr;

      CMXTA_DBG_FATAL((_cmxtap, "cmXtaPushMsg(): queue full: cannot queue primitive\n"));

      /* release message queue lock */
      CMXTA_DBG_INFO((_cmxtap, "cmXtaPushMsg(): SUnlock()\n"));
      (Void) SUnlock(&msgQ->qLock);

      RETVALUE(RFAILED);
   }

   /* queue the passed element */
   (Void) cmMemcpy((U8 *) &msgQ->qElm[oldPtr],
                   (U8 *) msg,
                   (PTR) sizeof(CmXtaMsgQElm));

   /* release message queue lock */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaPushMsg(): SUnlock()\n"));
   (Void) SUnlock(&msgQ->qLock);

   RETVALUE(ROK);
} /* cmXtaPushMsg */

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
PUBLIC  S16 cmXtaPopMsg
(
CmXtaMsgQ *msgQ,
CmXtaMsgQElm  **msg           /* queue message to be returned */
)
#else
PUBLIC  S16 cmXtaPopMsg(msgQ, msg)
CmXtaMsgQ *msgQ;
CmXtaMsgQElm  **msg;          /* queue message to be returned */
#endif
{
   TRC2(cmXtaPopMsg)

   /* lock the message queue */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaPopMsg(): SLock()\n"));
   (Void) SLock(&msgQ->qLock);

   /* Check if queue is EMPTY */
   if (msgQ->rdPtr == msgQ->wrPtr)
   {
      /* no element to return */
      *msg = (CmXtaMsgQElm *)NULLP;

      /* release the message queue lock */
      CMXTA_DBG_INFO((_cmxtap, "cmXtaPopMsg(): SUnlock()\n"));
      (Void) SUnlock(&msgQ->qLock);

      RETVALUE(RFAILED);
   }

   /* point to the correct queued element */
   *msg = &msgQ->qElm[msgQ->rdPtr];

   /* Increment the read pointer to the next location */
   msgQ->rdPtr++;

   /* if read-ptr has reached end of the queue,
      roll it to the head of the queue */
   if (msgQ->rdPtr == (U16) CMXTA_MSGQ_SIZE)
   {
      msgQ->rdPtr = 0;
   }

   /* release the message queue lock */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaPopMsg(): SUnlock()\n"));
   (Void) SUnlock(&msgQ->qLock);

   RETVALUE(ROK);

} /* cmXtaPopMsg */

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
PUBLIC  S16 cmXtaPeekMsg
(
CmXtaMsgQ *msgQ,
CmXtaMsgQElm  **msg              /* message queue element */
)
#else
PUBLIC  S16 cmXtaPeekMsg(msgQ, msg)
CmXtaMsgQ *msgQ;
CmXtaMsgQElm  **msg;             /* message queue element */
#endif
{
   TRC2(cmXtaPeekMsg)

   /* lock the message queue */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaPeekMsg(): SLock()\n"));
   (Void) SLock(&msgQ->qLock);

   /* Check If queue is empty */
   if (msgQ->rdPtr == msgQ->wrPtr)
   {
      /* no element to return */
      *msg = (CmXtaMsgQElm *)NULLP;

      /* release the message queue lock */
      CMXTA_DBG_INFO((_cmxtap, "cmXtaPeekMsg(): SUnlock()\n"));
      (Void) SUnlock(&msgQ->qLock);

      RETVALUE(RFAILED);
   }

   /* point to correct queue element */
   *msg = &msgQ->qElm[msgQ->rdPtr];

   /* release the message queue lock */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaPeekMsg(): SUnlock()\n"));
   (Void) SUnlock(&msgQ->qLock);

   RETVALUE(ROK);
} /* cmXtaPeekMsg */

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
PUBLIC S16 cmXtaFlushMsg
(
CmXtaMsgQ *msgQ,
CmXtaMsgQElm *msg                /* message queue element */
)
#else
PUBLIC S16 cmXtaFlushMsg(msgQ, msg)
CmXtaMsgQ *msgQ;
CmXtaMsgQElm *msg;               /* message queue element */
#endif
{
   TRC2(cmXtaFlushMsg)

   /* lock the message queue */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaFlushMsg(): release message\n"));

   if (msg->msgFreeFun != NULLP)
      (*msg->msgFreeFun)(msg);

   RETVALUE(ROK);
} /* cmXtaFlushMsg */

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
PUBLIC S16 cmXtaLenMsgQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC S16 cmXtaLenMsgQ(msgQ)
CmXtaMsgQ *msgQ;           /* Message to be inserted in the queue */
#endif
{
   S16   len;

   TRC2(cmXtaLenMsgQ)

   /* lock the message queue */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaLenMsgQ(): SLock()\n"));
   (Void) SLock(&msgQ->qLock);

   /* if write-ptr has reached end of the queue, roll it to the
    * head of the queue */
   if (msgQ->wrPtr >= msgQ->rdPtr)
      len = msgQ->wrPtr - msgQ->rdPtr;
   else
      len = CMXTA_MSGQ_SIZE + msgQ->wrPtr - msgQ->rdPtr;

   CMXTA_DBG_INFO((_cmxtap, "cmXtaLenMsgQ(): SUnlock()\n"));
   (Void) SUnlock(&msgQ->qLock);
   RETVALUE(len);
} /* cmXtaLenMsgQ */

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
PUBLIC Void cmXtaDispNFlushQ
(
CmXtaMsgQ *msgQ
)
#else
PUBLIC Void cmXtaDispNFlushQ(msgQ)
CmXtaMsgQ  *msgQ;           /* Message to be inserted in the queue */
#endif
{
   /* local variables */
   Pst            *pst;
   CmXtaMsgQElm   *msg;          /* local QElm pointer      */

   TRC2(cmXtaDispNFlushQ)

   /* Release any memory associated with the messages */
   while (cmXtaPopMsg(msgQ, &msg) == ROK)
   {
      pst = &msg->pst;

      CMXTA_DBG_CALLIND((_cmxtap, "Received: [src:%hd.%hd dst:%hd.%hd evt:%hd]\n",
         pst->srcEnt, pst->srcInst, pst->dstEnt, pst->dstInst, pst->event), 2);

      cmXtaFlushMsg(msgQ, msg);
   }

   /* lock the message queue */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaDispNFlushQ(): SLock()\n"));
   (Void) SLock(&msgQ->qLock);

   msg = &msgQ->qElm[0];

   CMXTA_FREE(msg, sizeof(CmXtaMsgQElm) * CMXTA_MSGQ_SIZE);

   /* zero the memory */
   CMXTA_ZERO(&msgQ->qElm, sizeof(CmXtaMsgQElm) * CMXTA_MSGQ_SIZE);
   msgQ->rdPtr = 0;
   msgQ->wrPtr = 0;

   /* release the message queue lock */
   CMXTA_DBG_INFO((_cmxtap, "cmXtaDispNFlushQ(): SUnlock()\n"));
   (Void) SUnlock(&msgQ->qLock);

   RETVOID;
} /* cmXtaDispNFlushQ */

/********************************************************************30**

         End of file:     cm_xta_queue.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:26 2015

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
/main/2      ----     up  1. Main release
/main/3      ---- cm_xta_queue_c_001.main_2 nh 1. Updated for Psf-Diameter 1.1
                             release Removed cm_xta_app.[hx]
*********************************************************************91*/
