

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_lib.c

     Sid:      kwac_lib.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:28 2014

     Prg:     cp
*********************************************************************21*/

/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_lib.h"      /* Acceptance defines */
#include "kwac_acc.h"      /* Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_lib.x"      /* Acceptance defines */
#include "kwac_acc.x"      /* Acceptance defines */
/*#include "kw_pj_lib.x"           LIB */


#ifdef KW_PDCP
/* Global Variables */
KwAcLibCb   libCb;

#ifdef PJ_CMP_ASYNC

#ifdef ANSI
PUBLIC S16 cmPkLibObdCmpInitReq
(
Pst * pst,
PjCmpCxt cmpCxt,
PjRohc rohc
)
#else
PUBLIC S16 cmPkLibObdCmpInitReq(pst, cmpCxt, rohc)
Pst * pst;
PjCmpCxt cmpCxt;
PjRohc rohc;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLibObdCmpInitReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD001, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmPkPjRohc(&rohc, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD002, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPjCmpCxt(&cmpCxt, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD003, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_CMP_INIT_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdCmpInitReq
(
LibObdCmpInitReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdCmpInitReq(func, pst, mBuf)
LibObdCmpInitReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjCmpCxt cmpCxt;
   PjRohc rohc;
   
   TRC3(cmUnpkLibObdCmpInitReq)

   if (cmUnpkPjCmpCxt(&cmpCxt, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD004, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjRohc(&rohc, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD005, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cmpCxt, rohc, NULLP));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdCmpReq
(
Pst * pst,
PTR cmpCxtId,
PjLibTrans libTrans,
Buffer * buff
)
#else
PUBLIC S16 cmPkLibObdCmpReq(pst, cmpCxtId, libTrans, buff)
Pst * pst;
PTR cmpCxtId;
PjLibTrans libTrans;
Buffer * buff;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkLibObdCmpReq)

   if (pst->selector == LIB_SEL_LC) {
      if (SFndLenMsg(buff, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD026, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
      if (SCpyMsgMsg(buff, pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD027, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else
   {
      if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EOBD025, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(buff);
         RETVALUE(RFAILED);
      }
   }

   CMCHKPK(cmPkMsgLen, msgLen, mBuf);

   if (cmPkPjLibTrans(&libTrans, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD029, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(cmpCxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD030, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_CMP_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdCmpReq
(
LibObdCmpReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdCmpReq(func, pst, mBuf)
LibObdCmpReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR cmpCxtId;
   PjLibTrans libTrans;
   Buffer *buff = NULLP;
   
   TRC3(cmUnpkLibObdCmpReq)

   if (cmUnpkPtr(&cmpCxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD031, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjLibTrans(&libTrans, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD032, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LIB_SEL_LC) {
      MsgLen msgLen = 0;
      MsgLen totalMsgLen = 0;

      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if (SSegMsg(mBuf, totalMsgLen-msgLen, &buff) != ROK)
         RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cmpCxtId, &libTrans, buff, NULLP));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdDecmpReq
(
Pst * pst,
PTR cmpCxtId,
PjLibTrans libTrans,
Buffer * buff
)
#else
PUBLIC S16 cmPkLibObdDecmpReq(pst, cmpCxtId, libTrans, buff)
Pst * pst;
PTR cmpCxtId;
PjLibTrans libTrans;
Buffer * buff;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkLibObdDecmpReq)

   if (pst->selector == LIB_SEL_LC) {
      if (SFndLenMsg(buff, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD054, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
      if (SCpyMsgMsg(buff, pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD055, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else
   {
      if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EOBD025, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(buff);
         RETVALUE(RFAILED);
      }
   }

   CMCHKPK(SPkS16, msgLen, mBuf);

   if (cmPkPjLibTrans(&libTrans, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD057, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(cmpCxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD058, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_DECMP_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdDecmpReq
(
LibObdDecmpReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdDecmpReq(func, pst, mBuf)
LibObdDecmpReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR cmpCxtId;
   PjLibTrans libTrans;
   Buffer *buff = NULLP;
   
   TRC3(cmUnpkLibObdDecmpReq)

   if (cmUnpkPtr(&cmpCxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD059, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjLibTrans(&libTrans, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD060, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LIB_SEL_LC) {
      MsgLen msgLen = 0;
      MsgLen totalMsgLen = 0;

      CMCHKUNPK(SUnpkS16, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if (SSegMsg(mBuf, totalMsgLen-msgLen, &buff) != ROK)
         RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cmpCxtId, &libTrans, buff, NULLP, NULLP));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdCmpCloseReq
(
Pst * pst,
PTR cmpCxtId
)
#else
PUBLIC S16 cmPkLibObdCmpCloseReq(pst, cmpCxtId)
Pst * pst;
PTR cmpCxtId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLibObdCmpCloseReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD081, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(cmpCxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD082, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_CMP_CLOSE_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdCmpCloseReq
(
LibObdCmpCloseReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdCmpCloseReq(func, pst, mBuf)
LibObdCmpCloseReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR cmpCxtId;
   
   TRC3(cmUnpkLibObdCmpCloseReq)

   if (cmUnpkPtr(&cmpCxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD083, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cmpCxtId));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdCmpResetReq
(
Pst * pst,
PTR cpCxtId
)
#else
PUBLIC S16 cmPkLibObdCmpResetReq(pst, cpCxtId)
Pst * pst;
PTR cpCxtId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLibObdCmpResetReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD090, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(cpCxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD091, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_CMP_RESET_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdCmpResetReq
(
LibObdCmpResetReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdCmpResetReq(func, pst, mBuf)
LibObdCmpResetReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR cpCxtId;
   
   TRC3(cmUnpkLibObdCmpResetReq)

   if (cmUnpkPtr(&cpCxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD092, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cpCxtId));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdCmpFbReq
(
Pst * pst,
PTR cmpCxtId,
PjLibTrans libTrans,
Buffer * feedback
)
#else
PUBLIC S16 cmPkLibObdCmpFbReq(pst, cmpCxtId, libTrans, feedback)
Pst * pst;
PTR cmpCxtId;
PjLibTrans libTrans;
Buffer * feedback;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkLibObdCmpFbReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD006, (ErrVal)0, "Packing failed");
#endif 
      RETVALUE(RFAILED);
   }     

   if (pst->selector == LIB_SEL_LC) {
      if (SFndLenMsg(feedback, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD026, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(feedback);
         RETVALUE(RFAILED);
      }
      if (SCatMsg(mBuf, feedback, M1M2) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD027, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(feedback);
         RETVALUE(RFAILED);
      }
      SPutMsg(feedback);
   }

   CMCHKPK(SPkS16, msgLen, mBuf);

   if (cmPkPjLibTrans(&libTrans, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD029, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(cmpCxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD030, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_CMP_FB_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdCmpFbReq
(
LibObdCmpFbReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdCmpFbReq(func, pst, mBuf)
LibObdCmpFbReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR cmpCxtId;
   PjLibTrans libTrans;
   Buffer *feedback = NULLP;
   
   TRC3(cmUnpkLibObdCmpReq)

   if (cmUnpkPtr(&cmpCxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD031, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjLibTrans(&libTrans, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD032, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LIB_SEL_LC) {
      MsgLen msgLen = 0;
      MsgLen totalMsgLen = 0;

      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if (SSegMsg(mBuf, totalMsgLen-msgLen, &feedback) != ROK)
         RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cmpCxtId, &libTrans, feedback));
}

#else

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to configure ROHC 
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to configure ROHC 
 *        per RB per UE.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibCmpInitReq 
(
PjCmpCxt cmpCxt,                  /* Context for ROHC */
PjRohc   rohc,                    /* ROHC Config Info */
PTR      *cmpCxtId                /* Compression Context ID */
)
#else
PUBLIC S16 pjLibCmpInitReq(cmpCxt, rohc, cmpCxtId)
PjCmpCxt cmpCxt;                  /* Context for ROHC */
PjRohc   rohc;                    /* ROHC Config Info */
PTR      *cmpCxtId;               /* Compression Context ID */
#endif
{
   TRC3(pjLibCmpInitReq)

   kwAcLibObdCmpInitReq(NULLP, cmpCxt, rohc, cmpCxtId);

   RETVALUE(ROK);

} /* end of pjLibCmpInitReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to compress SDU.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to compress 
 *        SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibCmpReq 
(
PTR      cmpCxtId,                /* Context Id for compression */
Buffer   *mBuf,                   /* SDU to be compressed */
Buffer   **opSdu                  /* Compressed SDU */
)
#else
PUBLIC S16 pjLibCmpReq(cmpCxtId, mBuf, opSdu)
PTR      cmpCxtId;                /* Context Id for compression */
Buffer   *mBuf;                   /* SDU to be compressed */
Buffer   **opSdu;                 /* Compressed SDU */
#endif
{
   TRC3(pjLibCmpReq)

   kwAcLibObdCmpReq(NULLP, cmpCxtId, NULLP, mBuf, opSdu);

   RETVALUE(ROK);

} /* end of pjLibCmpReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to decompress the SDU.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to decompress 
 *        the SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibDecmpReq 
(
PTR      cmpCxtId,                /* Context Id for compression */
Buffer   *mBuf,                   /* SDU to be decompressed */
Buffer   **feedback,                 /* Decompressed SDU */
Buffer   **opSdu               /* ROHC feedback buffer */
)
#else
PUBLIC S16 pjLibDecmpReq(cmpCxtId, mBuf, feedback, opSdu)
PTR      cmpCxtId;                /* Context Id for compression */
Buffer   *mBuf;                   /* SDU to be decompressed */
Buffer   **feedback;                 /* Decompressed SDU */
Buffer   **opSdu;              /* ROHC feedback buffer */
#endif
{
   TRC3(pjLibDecmpReq)

   kwAcLibObdDecmpReq(NULLP, cmpCxtId, NULLP, mBuf, opSdu, feedback);

   RETVALUE(ROK);

} /* end of pjLibDecmpReq */

/**
 *
 * @brief 
 *
 *        Handler for closing the context with the compression unit (either 
 *        synchronous or asynchronous) for RB within an UE.
 *
 * @b Description:
 *
 *        This function closes an existing context with the compression unit per RB per
 *        UE, either using synchronous / asynchronous function calls with relevant input parameters.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibCmpCloseReq
(
PTR      cmpCxtId                 /* ROHC Context to be closed */
)
#else
PUBLIC S16 pjLibCmpCloseReq(cmpCxtId)
PTR      cmpCxtId;                /* ROHC Context to be closed */
#endif
{
   TRC3(pjLibCmpCloseReq)

   kwAcLibObdCmpCloseReq(NULLP, cmpCxtId);

   RETVALUE(ROK);

} /* end of pjLibCmpCloseReq */


/**
 *
 * @brief 
 *
 *        Handler for reset the context with the compression unit (either 
 *        synchronous or asynchronous) for RB within an UE.
 *
 * @b Description:
 *
 *        This function reset an existing context with the compression unit per RB per
 *        UE, either using synchronous / asynchronous function calls with relevant input parameters.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibCmpResetReq
(
PTR      cmpCxtId                 /* ROHC Context to be closed */
)
#else
PUBLIC S16 pjLibCmpResetReq(cmpCxtId)
PTR      cmpCxtId;                /* ROHC Context to be closed */
#endif
{
   TRC3(pjLibCmpResetReq)

   kwAcLibObdCmpResetReq(NULLP, cmpCxtId);

   RETVALUE(ROK);

} /* end of pjLibCmpResetReq */

/**
 *
 * @brief 
 *
 *        Handler to send feedback packet to the compression unit (either 
 *        synchronous or asynchronous) for RB within an UE.
 *
 * @b Description:
 *
 *        This function sends feedback packet to the compression unit per RB per
 *        UE, either using synchronous / asynchronous function calls with relevant input parameters.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibCmpFbReq
(
PTR      cmpCxtId,                /* ROHC Context to be closed */
Buffer   *feedback                /* Feed back */
)
#else
PUBLIC S16 pjLibCmpFbReq(cmpCxtId, feedback)
PTR      cmpCxtId;                /* ROHC Context to be closed */
Buffer   *feedback;               /* Feed back */
#endif
{
   TRC3(pjLibCmpFbReq)

   kwAcLibObdCmpFbReq(NULLP, cmpCxtId, NULLP, feedback);

   RETVALUE(ROK);

} /* end of pjLibCmpFbReq */
#endif /* PJ_CM_ASYNC */

#ifdef PJ_SEC_ASYNC

#ifdef ANSI
PUBLIC S16 cmPkLibObdIntInitReq
(
Pst * pst,
PjSecCxt secCtx,
PjIntInfo intInfo
)
#else
PUBLIC S16 cmPkLibObdIntInitReq(pst, secCtx, intInfo)
Pst * pst;
PjSecCxt secCtx;
PjIntInfo intInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLibObdIntInitReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD006, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmPkPjIntInfo(&intInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD007, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPjSecCxt(&secCtx, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD008, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_INT_INIT_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdIntInitReq
(
LibObdIntInitReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdIntInitReq(func, pst, mBuf)
LibObdIntInitReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PjSecCxt secCtx;
   PjIntInfo intInfo;
   
   TRC3(cmUnpkLibObdIntInitReq)

   if (cmUnpkPjSecCxt(&secCtx, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD009, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjIntInfo(&intInfo, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD010, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, secCtx, intInfo, NULLP));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdCpInitReq
(
Pst * pst,
PjSecCxt secCxt,
U8 algoType,
U8 *cpKey
)
#else
PUBLIC S16 cmPkLibObdCpInitReq(pst, secCxt, algoType, cpKey)
Pst * pst;
PjSecCxt secCxt;
U8 algoType;
U8 *cpKey;
#endif
{
   S32 i;
   Buffer *mBuf = NULLP;
   TRC3(cmPkLibObdCpInitReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD011, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   for (i=PJ_CIPHER_KEY_LEN-1; i >= 0; i--) {
      CMCHKPK(SPkU8, cpKey[i], mBuf);
   }

   if (SPkU8(algoType, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD013, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPjSecCxt(&secCxt, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD014, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_CP_INIT_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdCpInitReq
(
LibObdCpInitReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdCpInitReq(func, pst, mBuf)
LibObdCpInitReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S32 i;
   PjSecCxt secCxt;
   U8 algoType;
   U8 cpKey[PJ_CIPHER_KEY_LEN];
   
   TRC3(cmUnpkLibObdCpInitReq)

   if (cmUnpkPjSecCxt(&secCxt, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD015, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&algoType, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD016, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   for (i=0; i < PJ_CIPHER_KEY_LEN; i++) {
      CMCHKUNPK(SUnpkU8, &cpKey[i], mBuf);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, secCxt, algoType, cpKey, NULLP));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdUpInitReq
(
Pst * pst,
PjSecCxt secCxt,
U8 algoType,
U8 *upKey
)
#else
PUBLIC S16 cmPkLibObdUpInitReq(pst, secCxt, algoType, upKey)
Pst * pst;
PjSecCxt secCxt;
U8 algoType;
U8 *upKey;
#endif
{
   S32 i;
   Buffer *mBuf = NULLP;
   TRC3(cmPkLibObdUpInitReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD018, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   for (i=PJ_INTG_KEY_LEN-1; i >= 0; i--) {
      CMCHKPK(SPkU8, upKey[i], mBuf);
   }

   if (SPkU8(algoType, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD020, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPjSecCxt(&secCxt, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD021, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_UP_INIT_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdUpInitReq
(
LibObdUpInitReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdUpInitReq(func, pst, mBuf)
LibObdUpInitReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S32 i;
   PjSecCxt secCxt;
   U8 algoType;
   U8 upKey[PJ_INTG_KEY_LEN];
   
   TRC3(cmUnpkLibObdUpInitReq)

   if (cmUnpkPjSecCxt(&secCxt, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD022, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&algoType, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD023, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   for (i=0; i < PJ_INTG_KEY_LEN; i++) {
      CMCHKUNPK(SUnpkU8, &upKey[i], mBuf);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, secCxt, algoType, upKey, NULLP));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdIntProtReq
(
Pst * pst,
PTR intCxtId,
PjSecInp secInp,
PjLibTrans libTrans,
Buffer * buff
)
#else
PUBLIC S16 cmPkLibObdIntProtReq(pst, intCxtId, secInp, libTrans, buff)
Pst * pst;
PTR intCxtId;
PjSecInp secInp;
PjLibTrans libTrans;
Buffer * buff;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkLibObdIntProtReq)

   if (pst->selector == LIB_SEL_LC) {
      if (SFndLenMsg(buff, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD034, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
      if (SCpyMsgMsg(buff, pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD035, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else
   {
      if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EOBD025, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(buff);
         RETVALUE(RFAILED);
      }
   }

   CMCHKPK(cmPkMsgLen, msgLen, mBuf);

   if (cmPkPjLibTrans(&libTrans, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD037, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPjSecInp(&secInp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD038, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(intCxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD039, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_INT_PROT_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdIntProtReq
(
LibObdIntProtReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdIntProtReq(func, pst, mBuf)
LibObdIntProtReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR intCxtId;
   PjSecInp secInp;
   PjLibTrans libTrans;
   Buffer *buff = NULLP;
   
   TRC3(cmUnpkLibObdIntProtReq)

   if (cmUnpkPtr(&intCxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD040, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjSecInp(&secInp, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD041, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjLibTrans(&libTrans, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD042, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LIB_SEL_LC) {
      MsgLen msgLen = 0;
      MsgLen totalMsgLen = 0;

      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if (SSegMsg(mBuf, totalMsgLen-msgLen, &buff) != ROK)
         RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, intCxtId, secInp, &libTrans, buff, NULLP));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdCipherReq
(
Pst * pst,
PTR cxtId,
PjSecInp secInp,
PjLibTrans libTrans,
Buffer * buff
)
#else
PUBLIC S16 cmPkLibObdCipherReq(pst, cxtId, secInp, libTrans, buff)
Pst * pst;
PTR cxtId;
PjSecInp secInp;
PjLibTrans libTrans;
Buffer * buff;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkLibObdCipherReq)

   if (pst->selector == LIB_SEL_LC) {
      if ( buff != NULLP )
      {
         if (SFndLenMsg(buff, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)EOBD044, (ErrVal)0, "Packing failed");
#endif
            RETVALUE(RFAILED);
         }
         if (SCpyMsgMsg(buff, pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)EOBD045, (ErrVal)0, "Packing failed");
#endif
            RETVALUE(RFAILED);
         }
      }
     else
     {
        msgLen = 0;
     }
   }
   else
   {
      if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EOBD025, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(buff);
         RETVALUE(RFAILED);
      }
   }

   CMCHKPK(cmPkMsgLen, msgLen, mBuf);

   if (cmPkPjLibTrans(&libTrans, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD047, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPjSecInp(&secInp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD048, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(cxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD049, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_CIPHER_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdCipherReq
(
LibObdCipherReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdCipherReq(func, pst, mBuf)
LibObdCipherReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR cxtId;
   PjSecInp secInp;
   PjLibTrans libTrans;
   Buffer *buff;
   
   TRC3(cmUnpkLibObdCipherReq)

   buff = NULLP;

   if (cmUnpkPtr(&cxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD050, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjSecInp(&secInp, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD051, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjLibTrans(&libTrans, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD052, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LIB_SEL_LC) {
      MsgLen msgLen = 0;
      MsgLen totalMsgLen = 0;

      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if ( msgLen != 0 )
      {
         if (SSegMsg(mBuf, totalMsgLen-msgLen, &buff) != ROK)
            RETVALUE(RFAILED);
      }
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cxtId, &libTrans, secInp, buff, NULLP));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdIntVerReq
(
Pst * pst,
PTR intCxtId,
PjSecInp secInp,
PjLibTrans libTrans,
Buffer * buff,
U32   macI
)
#else
PUBLIC S16 cmPkLibObdIntVerReq(pst, intCxtId, secInp, libTrans, buff, macI)
Pst * pst;
PTR intCxtId;
PjSecInp secInp;
PjLibTrans libTrans;
Buffer * buff;
U32   macI;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkLibObdIntVerReq)

   if (pst->selector == LIB_SEL_LC) {
      if (SFndLenMsg(buff, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD062, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
      if (SCpyMsgMsg(buff, pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD063, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else
   {
      if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EOBD025, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(buff);
         RETVALUE(RFAILED);
      }
   }

   CMCHKPK(cmPkMsgLen, msgLen, mBuf);

   CMCHKPK(SPkU32, macI, mBuf);

   if (cmPkPjLibTrans(&libTrans, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD065, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPjSecInp(&secInp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD066, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(intCxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD067, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_INT_VER_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdIntVerReq
(
LibObdIntVerReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdIntVerReq(func, pst, mBuf)
LibObdIntVerReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR intCxtId;
   PjSecInp secInp;
   PjLibTrans libTrans;
   Buffer *buff = NULLP;
   U32   macI;
   
   TRC3(cmUnpkLibObdIntVerReq)

   if (cmUnpkPtr(&intCxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD068, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjSecInp(&secInp, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD069, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjLibTrans(&libTrans, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD070, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   CMCHKUNPK(SUnpkU32, &macI, mBuf);

   if (pst->selector == LIB_SEL_LC) {
      MsgLen msgLen = 0;
      MsgLen totalMsgLen = 0;

      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if (SSegMsg(mBuf, totalMsgLen-msgLen, &buff) != ROK)
         RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, intCxtId, secInp, &libTrans, buff, macI, NULLP));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdDecipherReq
(
Pst * pst,
PTR cxtId,
PjSecInp secInp,
PjLibTrans libTrans,
Buffer * buff
)
#else
PUBLIC S16 cmPkLibObdDecipherReq(pst, cxtId, secInp, libTrans, buff)
Pst * pst;
PTR cxtId;
PjSecInp secInp;
PjLibTrans libTrans;
Buffer * buff;
#endif
{
   Buffer *mBuf = NULLP;
   MsgLen msgLen = 0;
   TRC3(cmPkLibObdDecipherReq)

   if (pst->selector == LIB_SEL_LC) {
      if (SFndLenMsg(buff, &msgLen) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD072, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
      if (SCpyMsgMsg(buff, pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)EOBD073, (ErrVal)0, "Packing failed");
#endif
         RETVALUE(RFAILED);
      }
   }
   else
   {
      if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)EOBD025, (ErrVal)0, "Packing failed");
#endif
         SPutMsg(buff);
         RETVALUE(RFAILED);
      }
   }

   CMCHKPK(cmPkMsgLen, msgLen, mBuf);

   if (cmPkPjLibTrans(&libTrans, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD075, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPjSecInp(&secInp, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD076, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(cxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD077, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_DECIPHER_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdDecipherReq
(
LibObdDecipherReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdDecipherReq(func, pst, mBuf)
LibObdDecipherReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR cxtId;
   PjSecInp secInp;
   PjLibTrans libTrans;
   Buffer *buff=NULLP;
   
   TRC3(cmUnpkLibObdDecipherReq)

   if (cmUnpkPtr(&cxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD078, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjSecInp(&secInp, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD079, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkPjLibTrans(&libTrans, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD080, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector == LIB_SEL_LC) {
      MsgLen msgLen = 0;
      MsgLen totalMsgLen = 0;

      CMCHKUNPK(cmUnpkMsgLen, &msgLen, mBuf);
      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if (SSegMsg(mBuf, totalMsgLen-msgLen, &buff) != ROK)
         RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cxtId, &libTrans, secInp, buff, NULLP));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdIntCloseReq
(
Pst * pst,
PTR intCxtId
)
#else
PUBLIC S16 cmPkLibObdIntCloseReq(pst, intCxtId)
Pst * pst;
PTR intCxtId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLibObdIntCloseReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD084, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(intCxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD085, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_INT_CLOSE_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdIntCloseReq
(
LibObdIntCloseReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdIntCloseReq(func, pst, mBuf)
LibObdIntCloseReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR intCxtId;
   
   TRC3(cmUnpkLibObdIntCloseReq)

   if (cmUnpkPtr(&intCxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD086, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, intCxtId));
}

#ifdef ANSI
PUBLIC S16 cmPkLibObdCipherCloseReq
(
Pst * pst,
PTR cpCxtId
)
#else
PUBLIC S16 cmPkLibObdCipherCloseReq(pst, cpCxtId)
Pst * pst;
PTR cpCxtId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLibObdCipherCloseReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD087, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmPkPtr(cpCxtId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD088, (ErrVal)0, "Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) OBD_EVT_CIPHER_CLOSE_REQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PUBLIC S16 cmUnpkLibObdCipherCloseReq
(
LibObdCipherCloseReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLibObdCipherCloseReq(func, pst, mBuf)
LibObdCipherCloseReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   PTR cpCxtId;
   
   TRC3(cmUnpkLibObdCipherCloseReq)

   if (cmUnpkPtr(&cpCxtId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)EOBD089, (ErrVal)0, "Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cpCxtId));
}

#else
/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to configure Integration unit.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to configure
 *        Integrity protection / verification with the Integrity algo and key
 *        for SRBs of an UE.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibIntInitReq 
(
PjSecCxt secCxt,                  /* Context for Intg protection/verification */
PjIntInfo intInfo,                /* Integrity Cfg Info */
PTR       *cxtId                  /* FD */
)
#else
PUBLIC S16 pjLibIntInitReq(secCxt, intInfo, cxtId)
PjSecCxt secCxt;                  /* Context for Intg protection/verificatino */
PjIntInfo intInfo;                /* Integrity Cfg Info */
PTR       *cxtId;                 /* FD */
#endif
{
   S16   ret = ROK;

   TRC3(pjLibIntInitReq)

   ret = kwAcLibObdIntInitReq(NULLP, secCxt, intInfo, cxtId);

   RETVALUE(ret);

} /* end of pjLibIntInitReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to configure ciphering unit.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to configure
 *        ciphering / deciphering with the ciphering algo and key
 *        for SRBs of an UE.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibCpInitReq
(
PjSecCxt secCxt,                  /* Context for Intg protection/verificatino */
U8       algoType,                /* Type of the algorithm */
U8       *cpKey,                  /* Control plane ciphering key */
PTR      *cxtId                   /* FD */
)
#else
PUBLIC S16 pjLibCpInitReq(secCxt, algoType, cpKey,cxtId)
PjSecCxt secCxt;                  /* Context for Intg protection/verificatino */
U8       algoType;                /* Type of the algorithm */
U8       *cpKey;                  /* Control plane ciphering key */
PTR      *cxtId;                  /* FD */
#endif
{
   S16   ret = ROK;

   TRC3(pjLibCpInitReq)

   ret = kwAcLibObdCpInitReq(NULLP, secCxt, algoType, cpKey, cxtId);

   RETVALUE(ret);

} /* end of pjLibCpInitReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to configure ciphering unit.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to configure
 *        ciphering / deciphering with the ciphering algo and key
 *        for DRBs of an UE.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibUpInitReq
(
PjSecCxt secCxt,                  /* Context for Intg protection/verificatino */
U8       algoType,                /* Type of the algorithm */
U8       *upKey,                  /* User plane ciphering key */
PTR      *cxtId                   /* FD */
)
#else
PUBLIC S16 pjLibUpInitReq(secCxt, algoType, upKey, cxtId)
PjSecCxt secCxt;                  /* Context for Intg protection/verificatino */
U8       algoType;                /* Type of the algorithm */
U8       *upKey;                  /* User plane ciphering key */
PTR      *cxtId;                  /* FD */
#endif
{
   TRC3(pjLibUpInitReq)

   kwAcLibObdUpInitReq(NULLP, secCxt, algoType, upKey, cxtId);

   RETVALUE(ROK);

} /* end of pjLibUpInitReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to request for integrity
 *        protection
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to compress 
 *        SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibIntProtReq 
(
PTR        intCxtId,                /* Context Id for compression */
PjSecInp   secInp,                  /* Input for Integrity protection */                  
Buffer     *mBuf,                   /* SDU to be compressed */
U32        *macI                    /* Message authentication code for the SDU */
)
#else
PUBLIC S16 pjLibIntProtReq(intCxtId, secInp, mBuf, macI)
PTR        intCxtId;                /* Context Id for compression */
PjSecInp   secInp;                  /* Input for Integrity protection */
Buffer     *mBuf;                   /* SDU to be compressed */
U32        *macI;                   /* Message authentication code for the SDU */
#endif
{
   TRC3(pjLibIntProtReq)

   kwAcLibObdIntProtReq(NULLP, intCxtId, secInp, NULLP, mBuf, macI);

   RETVALUE(ROK);

} /* end of pjLibIntProtReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to cipher SDU.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to cipher 
 *        SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibCipherReq 
(
PTR         secCxtId,           /* Context Id for compression */
PjSecInp    secInp,             /* Input for Ciphering */                  
Buffer      *mBuf,              /* SDU to be ciphered */
Buffer      **opSdu             /* ciphered SDU */
)
#else
PUBLIC S16 pjLibCipherReq(secCxtId, secInp, mBuf, opSdu)
PTR         secCxtId;           /* Context Id for ciphering */
PjSecInp    secInp;             /* Input for ciphering */                  
Buffer      *mBuf;              /* SDU to be ciphering */
Buffer      **opSdu;            /* Ciphering SDU */
#endif
{
   TRC3(pjLibCipherReq)

   kwAcLibObdCipherReq(NULLP, secCxtId, NULLP, secInp, mBuf, opSdu);

   RETVALUE(ROK);

} /* end of pjLibCmpReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to request for integrity
 *        verification
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to verify integrity 
 *        SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibIntVerReq 
(
PTR        intCxtId,                /* Context Id for compression */
PjSecInp   secInp,                  /* Input for Integrity protection */                  
Buffer     *mBuf,                   /* SDU to be compressed */
U32        macI,                    /* Message authentication code for the SDU */
Status     *status                  /* Status of the Integrity verification */
)
#else
PUBLIC S16 pjLibIntVerReq(intCxtId, secInp, mBuf, macI, status)
PTR        intCxtId;                /* Context Id for compression */
PjSecInp   secInp;                  /* Input for Integrity protection */
Buffer     *mBuf;                   /* SDU to be compressed */
U32        macI;                    /* Message authentication code for the SDU */
Status     *status;                 /* Status of the Integrity verification */
#endif
{
   TRC3(pjLibIntVerReq)

   kwAcLibObdIntVerReq(NULLP, intCxtId, secInp, NULLP, mBuf, macI, status);

   RETVALUE(ROK);

} /* end of pjLibIntVerReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to decipher SDU.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to decipher 
 *        SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibDecipherReq 
(
PTR         intCxtId,           /* Context Id for compression */
PjSecInp    secInp,             /* Input for Deciphering */                  
Buffer      *mBuf,              /* SDU to be deciphered */
Buffer      **opSdu             /* deciphered SDU */
)
#else
PUBLIC S16 pjLibDecipherReq(intCxtId, secInp, mBuf, opSdu)
PTR         intCxtId;           /* Context Id for Deciphering */
PjSecInp    secInp;             /* Input for Deciphering */                  
Buffer      *mBuf;              /* SDU to be Deciphering */
Buffer      **opSdu;            /* Deciphering SDU */
#endif
{
   TRC3(pjLibDecipherReq)

   kwAcLibObdDecipherReq(NULLP, intCxtId, NULLP, secInp, mBuf, opSdu);

   RETVALUE(ROK);

} /* end of pjLibDecipherReq */

/**
 *
 * @brief 
 *
 *        Handler for closing the context with the Integration unit (either 
 *        synchronous or asynchronous) for all RBs of an UE.
 *
 * @b Description:
 *
 *        This function closes an existing context with the security algo unit per UE
 *        for Integration protection/verification using synchronous / asynchronous function 
 *        calls with relevant input parameters.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibIntCloseReq
(
U32      intCxtId                 /* Integration CxtId to be closed */
)
#else
PUBLIC S16 pjLibIntCloseReq(intCxtId)
U32      intCxtId;                /* Integration CxtId to be closed */
#endif
{
   TRC3(pjLibIntCloseReq)

   kwAcLibObdIntCloseReq(NULLP, intCxtId);

   RETVALUE(ROK);

} /* end of pjLibIntCloseReq */

/**
 *
 * @brief 
 *
 *        Handler for closing the context with the Ciphering unit (either 
 *        synchronous or asynchronous) for SRBs of an UE.
 *
 * @b Description:
 *
 *        This function closes an existing context with the security algo unit per UE
 *        for ciphering / deciphering with control plane key using synchronous / asynchronous 
 *        function calls with relevant input parameters.
 *
 *
 *  @param[in] cxtId    Ciphering Context ID
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibCipherCloseReq
(
U32      cxtId                  /* Context Id for SRBs to be closed */
)
#else
PUBLIC S16 pjLibCipherCloseReq(cxtId)
U32      cxtId;                 /* Context Id for SRBs to be closed */
#endif
{
   TRC3(pjLibCipherCloseReq)

   kwAcLibObdCipherCloseReq(NULLP, cxtId);

   RETVALUE(ROK);

} /* end of pjLibCipherCloseReq */

/**
 *
 * @brief 
 *
 *        Handler for closing the context with the Ciphering unit (either 
 *        synchronous or asynchronous) for DRBs of an UE.
 *
 * @b Description:
 *
 *        This function closes an existing context with the security algo unit per UE
 *        for ciphering / deciphering with user plane key using synchronous / asynchronous 
 *        function calls with relevant input parameters.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 pjLibUpCloseReq
(
U32      upCxtId                  /* Context Id for DRBs to be closed */
)
#else
PUBLIC S16 pjLibUpCloseReq(upCxtId)
U32      upCxtId;                 /* Context Id for DRBs to be closed */
#endif
{
   TRC3(pjLibUpCloseReq)

   kwAcLibObdCipherCloseReq(NULLP, upCxtId);

   RETVALUE(ROK);

} /* end of pjLibUpCloseReq */

#endif /* PJ_SEC_ASYNC */

#endif /* KW_PDCP */

/********************************************************************30**

         End of file:     kwac_lib.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:28 2014

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
/main/1      ---   gk         1. Initial Release.
*********************************************************************91*/


