
/********************************************************************20**
 
     Name:     CTF Interface
 
     Type:     C file
 
     Desc:     This file contains the packing/unpacking functions
               for control plane primitives on CTF interface.

     File:     ctf.c

     Sid:      ctf.c@@/main/5 - Thu Feb 16 20:18:30 2012
 
     Prg:      vkulkarni
     
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_lte.h"        /* Common LTE Defines              */
#include "ctf.h"           /* CTF interface defines           */

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_lte.x"        /* Common LTE library              */
#include "ctf.x"          


#if (defined(LCCTF) || defined(LWLCCTF))


/**
* @brief Request from RRC to PHY to bind the CTF interface SAP.
*
* @details
*
*     Function: cmPkCtfBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCtfBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkCtfBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCtfBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF001, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF002, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF003, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCTFBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Request from RRC to PHY to bind the CTF interface SAP.
*
* @details
*
*     Function: cmUnpkCtfBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfBndReq
(
CtfBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfBndReq(func, pst, mBuf)
CtfBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId = 0;
   SpId spId = 0;
   
   TRC3(cmUnpkCtfBndReq)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF004, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF005, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, spId));
}


/**
* @brief Confirmation from PHY to RRC for the bind 
 * request for the CTF interface SAP.
*
* @details
*
*     Function: cmPkCtfBndCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCtfBndCfm
(
Pst* pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkCtfBndCfm(pst, suId, status)
Pst* pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCtfBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF006, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF007, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF008, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCTFBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Confirmation from PHY to RRC for the bind 
 * request for the CTF interface SAP.
*
* @details
*
*     Function: cmUnpkCtfBndCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfBndCfm
(
CtfBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfBndCfm(func, pst, mBuf)
CtfBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId = 0;
   U8 status;
   
   TRC3(cmUnpkCtfBndCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF009, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF010, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, status));
}


/**
* @brief Request from RRC to PHY to Unbind the CTF interface SAP.
*
* @details
*
*     Function: cmPkCtfUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCtfUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkCtfUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCtfUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF011, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF012, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF013, (ErrVal)0,(Txt*)&"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCTFUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Request from RRC to PHY to Unbind the CTF interface SAP.
*
* @details
*
*     Function: cmUnpkCtfUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfUbndReq
(
CtfUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfUbndReq(func, pst, mBuf)
CtfUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId = 0;
   Reason reason = 0;
   
   TRC3(cmUnpkCtfUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF014, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF015, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}


/* ctf_c_001.main_4 : Added new function cmRelCtfCfgReq() */
/***********************************************************
*
*     Func: cmRelCtfCfgReq
*
*
*     Desc:  This fucntion will release the memory used for ctf cfg req
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PRIVATE S16 cmRelCtfCfgReq
(
Pst  *pst,
CtfCfgReqInfo *cfgReqInfo
)
#else
PRIVATE S16 cmRelCtfCfgReq(pst,cfgReqInfo)
Pst  *pst;
CtfCfgReqInfo *param;
#endif
{
   /* ctf_c_001.main_4: Added support for vendor specific parameters */
#ifdef CTF_VER3
   if(cfgReqInfo->vendorParams.paramBuffer != NULLP) {
      SPutSBuf(pst->region, pst->pool, 
                   (Data *)cfgReqInfo->vendorParams.paramBuffer,
                   cfgReqInfo->vendorParams.buffLen);
   }
#endif
   SPutSBuf(pst->region, pst->pool, (Data *)cfgReqInfo, sizeof(CtfCfgReqInfo)); 
   RETVALUE(ROK);
}

/* ctf_c_001.main_4: Modified cmPkCtfCfgReq() to support vendor specific
 * parameter */
/**
* @brief Configuration Request from RRC to PHY for 
 * cell or dedicated configuration.
*
* @details
*
*     Function: cmPkCtfCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CtfCfgTransId  transId
*  @param[in]   CtfCfgReqInfo*  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCtfCfgReq
(
Pst* pst,
SpId spId,
CtfCfgTransId transId,
CtfCfgReqInfo* cfgReqInfo
)
#else
PUBLIC S16 cmPkCtfCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
CtfCfgTransId transId;
CtfCfgReqInfo* cfgReqInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCtfCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF016, (ErrVal)0, "Packing failed");
#endif
      cmRelCtfCfgReq(pst, cfgReqInfo);     
      RETVALUE(RFAILED);
   }

   if (pst->selector == CTF_SEL_LC) {
      if (cmPkCtfCfgReqInfo(cfgReqInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF017, (ErrVal)0, "Packing failed");
#endif
         cmRelCtfCfgReq(pst, cfgReqInfo);     
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CTF_SEL_LWLC) {
      if (cmPkPtr((PTR)cfgReqInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF018, (ErrVal)0, "Packing failed");
#endif
         cmRelCtfCfgReq(pst, cfgReqInfo);     
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (cmPkCtfCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF019, (ErrVal)0, "Packing failed");
#endif
      cmRelCtfCfgReq(pst, cfgReqInfo);     
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF020, (ErrVal)0, "Packing failed");
#endif
      cmRelCtfCfgReq(pst, cfgReqInfo);     
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CTF_SEL_LWLC) {
         cmRelCtfCfgReq(pst, cfgReqInfo); 
   }
   pst->event = (Event) EVTCTFCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Configuration Request from RRC to PHY for 
 * cell or dedicated configuration.
*
* @details
*
*     Function: cmUnpkCtfCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CtfCfgTransId  transId
*  @param[in]   CtfCfgReqInfo*  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfCfgReq
(
CtfCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfCfgReq(func, pst, mBuf)
CtfCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId = 0;
   CtfCfgTransId transId;
   CtfCfgReqInfo *cfgReqInfo = NULLP;
   
   TRC3(cmUnpkCtfCfgReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF022, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkCtfCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF023, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CTF_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfgReqInfo, sizeof(CtfCfgReqInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF024, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CTF_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&cfgReqInfo, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   /* ctf_c_001.main_4: Added support for vendor specific parameter */
   else if (pst->selector == CTF_SEL_LC) {
      if (cmUnpkCtfCfgReqInfo(pst,cfgReqInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
        __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
        (ErrVal)ECTF025, (ErrVal)0, "Packing failed");
#endif
        cmRelCtfCfgReq(pst, cfgReqInfo);     
        SPutMsg(mBuf);
        RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, transId, cfgReqInfo));
}


/**
* @brief Configuration Confirm from PHY to RRC.
*
* @details
*
*     Function: cmPkCtfCfgCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   CtfCfgTransId  transId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCtfCfgCfm
(
Pst* pst,
SuId suId,
CtfCfgTransId transId,
U8 status
)
#else
PUBLIC S16 cmPkCtfCfgCfm(pst, suId, transId, status)
Pst* pst;
SuId suId;
CtfCfgTransId transId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCtfCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF026, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SPkU8(status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF027, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmPkCtfCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF028, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF029, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTCTFCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Configuration Confirm from PHY to RRC.
*
* @details
*
*     Function: cmUnpkCtfCfgCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   CtfCfgTransId  transId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfCfgCfm
(
CtfCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfCfgCfm(func, pst, mBuf)
CtfCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId = 0;
   CtfCfgTransId transId;
   U8 status;
   
   TRC3(cmUnpkCtfCfgCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF030, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkCtfCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF031, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (SUnpkU8(&status, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF032, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId, status));
}


/**
* @brief UE ID Change Request from RRC to PHY.
*
* @details
*
*     Function: cmPkCtfUeIdChgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CtfCfgTransId  transId
*  @param[in]   CtfUeInfo *  ueInfo
*  @param[in]   CtfUeInfo *  newUeInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCtfUeIdChgReq
(
Pst* pst,
SpId spId,
CtfCfgTransId transId,
CtfUeInfo * ueInfo,
CtfUeInfo * newUeInfo
)
#else
PUBLIC S16 cmPkCtfUeIdChgReq(pst, spId, transId, ueInfo, newUeInfo)
Pst* pst;
SpId spId;
CtfCfgTransId transId;
CtfUeInfo * ueInfo;
CtfUeInfo * newUeInfo;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCtfUeIdChgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF033, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CtfUeInfo));
      RETVALUE(RFAILED);
   }
   if (pst->selector == CTF_SEL_LC) {
      if (cmPkCtfUeInfo(newUeInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF034, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
         SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CtfUeInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CTF_SEL_LWLC) {
      if (cmPkPtr((PTR)newUeInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF035, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
         SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CtfUeInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CTF_SEL_LC) {
      if (cmPkCtfUeInfo(ueInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF036, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
         SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CtfUeInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CTF_SEL_LWLC) {
      if (cmPkPtr((PTR)ueInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF037, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
         SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CtfUeInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (cmPkCtfCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF038, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CtfUeInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF039, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CtfUeInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CTF_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF040, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      if (SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CtfUeInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF041, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTCTFUEIDCHGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief UE ID Change Request from RRC to PHY.
*
* @details
*
*     Function: cmUnpkCtfUeIdChgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CtfCfgTransId  transId
*  @param[in]   CtfUeInfo *  ueInfo
*  @param[in]   CtfUeInfo *  newUeInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfUeIdChgReq
(
CtfUeIdChgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfUeIdChgReq(func, pst, mBuf)
CtfUeIdChgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId = 0;
   CtfCfgTransId transId;
   CtfUeInfo *ueInfo = NULLP;
   CtfUeInfo *newUeInfo = NULLP;
   
   TRC3(cmUnpkCtfUeIdChgReq)

   if (SUnpkS16(&spId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
        (Txt*)& __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF042, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkCtfCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF043, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CTF_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&ueInfo, sizeof(CtfUeInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF044, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CTF_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&ueInfo, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CTF_SEL_LC) 
      if (cmUnpkCtfUeInfo(ueInfo, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF045, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CTF_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&newUeInfo, sizeof(CtfUeInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF046, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CTF_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&newUeInfo, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CTF_SEL_LC) 
      if (cmUnpkCtfUeInfo(newUeInfo, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo, sizeof(CtfUeInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF047, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, transId, ueInfo, newUeInfo));
}


/**
* @brief UE ID Change Confirm from PHY to RRC.
*
* @details
*
*     Function: cmPkCtfUeIdChgCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   CtfCfgTransId  transId
*  @param[in]   CtfUeInfo *  ueInfo
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCtfUeIdChgCfm
(
Pst* pst,
SuId suId,
CtfCfgTransId transId,
CtfUeInfo * ueInfo,
CmStatus status
)
#else
PUBLIC S16 cmPkCtfUeIdChgCfm(pst, suId, transId, ueInfo, status)
Pst* pst;
SuId suId;
CtfCfgTransId transId;
CtfUeInfo * ueInfo;
CmStatus status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkCtfUeIdChgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF048, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      RETVALUE(RFAILED);
   }
   if (cmPkCmStatus(&status, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF049, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector == CTF_SEL_LC) {
      if (cmPkCtfUeInfo(ueInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF050, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CTF_SEL_LWLC) {
      if (cmPkPtr((PTR)ueInfo, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF051, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (cmPkCtfCfgTransId(&transId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF052, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(suId, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF053, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (pst->selector != CTF_SEL_LWLC) {
      if (SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF054, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTCTFUEIDCHGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief UE ID Change Confirm from PHY to RRC.
*
* @details
*
*     Function: cmUnpkCtfUeIdChgCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   CtfCfgTransId  transId
*  @param[in]   CtfUeInfo *  ueInfo
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfUeIdChgCfm
(
CtfUeIdChgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfUeIdChgCfm(func, pst, mBuf)
CtfUeIdChgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId = 0;
   CtfCfgTransId transId;
   CtfUeInfo *ueInfo = NULLP;
   CmStatus status;
   
   TRC3(cmUnpkCtfUeIdChgCfm)

   if (SUnpkS16(&suId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF055, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkCtfCfgTransId(&transId, mBuf) != ROK) {
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF056, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (pst->selector != CTF_SEL_LWLC) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&ueInfo, sizeof(CtfUeInfo))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ECTF057, (ErrVal)0, (Txt*)&"Packing failed");
#endif
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   if (pst->selector == CTF_SEL_LWLC) {
      if (cmUnpkPtr((PTR *)&ueInfo, mBuf) != ROK) {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else if (pst->selector == CTF_SEL_LC) 
      if (cmUnpkCtfUeInfo(ueInfo, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF058, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   if (cmUnpkCmStatus(&status, mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)ueInfo, sizeof(CtfUeInfo));
      SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
      /* ctf_c_001.main_3 Compilation warning fix with g++ */
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
         (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
         (ErrVal)ECTF059, (ErrVal)0, (Txt*)&"Packing failed");
#endif
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, transId, ueInfo, status));
}


/***********************************************************
*
*     Func: cmPkCtfCfgTransId
*
*
*     Desc: Transaction ID between CTF and RRC.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfCfgTransId
(
CtfCfgTransId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfCfgTransId(param, mBuf)
CtfCfgTransId *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmPkCtfCfgTransId)

   for (i=CTF_CFG_TRANSID_SIZE-1; i >= 0; i--) {
      CMCHKPK(SPkU8, param->trans[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfCfgTransId
*
*
*     Desc: Transaction ID between CTF and RRC.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfCfgTransId
(
CtfCfgTransId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfCfgTransId(param, mBuf)
CtfCfgTransId *param;
Buffer *mBuf;
#endif
{

   S32 i;
   TRC3(cmUnpkCtfCfgTransId)

   for (i=0; i<CTF_CFG_TRANSID_SIZE; i++) {
      CMCHKUNPK(SUnpkU8, &param->trans[i], mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfUeInfo
*
*
*     Desc: *  UE ID information
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfUeInfo
(
CtfUeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfUeInfo(param, mBuf)
CtfUeInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfUeInfo)

   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfUeInfo
*
*
*     Desc: *  UE ID information
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfUeInfo
(
CtfUeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfUeInfo(param, mBuf)
CtfUeInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfUeInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfBwCfgInfo
*
*
*     Desc:   Bandwidth Configuration
 * @details This structure contains the uplink and downlink bandwidth 
 *          information for configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfBwCfgInfo
(
CtfBwCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfBwCfgInfo(param, mBuf)
CtfBwCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfBwCfgInfo)

   CMCHKPK(SPkU8, param->eUtraBand, mBuf);
   CMCHKPK(SPkU32, param->ulBw, mBuf);
   CMCHKPK(SPkU32, param->dlBw, mBuf);
   /* ctf_c_001.main_4: Removed packing of param->pres */
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfBwCfgInfo
*
*
*     Desc:   Bandwidth Configuration
 * @details This structure contains the uplink and downlink bandwidth 
 *          information for configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfBwCfgInfo
(
CtfBwCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfBwCfgInfo(param, mBuf)
CtfBwCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfBwCfgInfo)

   /* ctf_c_001.main_4: Removed UnPacking of param->pres */
   CMCHKUNPK(SUnpkU32, (U32 *)&param->dlBw, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->ulBw, mBuf);
   CMCHKUNPK(SUnpkU8, &param->eUtraBand, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfTxSchemeCfg
*
*
*     Desc:   Transmission Scheme Configuration
 * @details This structure contains the transmission scheme related information.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfTxSchemeCfg
(
CtfTxSchemeCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfTxSchemeCfg(param, mBuf)
CtfTxSchemeCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfTxSchemeCfg)

   CMCHKPK(SPkU32, param->cycPfx, mBuf);
   CMCHKPK(SPkU32, param->scSpacing, mBuf);
   CMCHKPK(SPkU32, param->duplexMode, mBuf);
   /* ctf_c_001.main_4: Removed packing of param->pres */
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfTxSchemeCfg
*
*
*     Desc:   Transmission Scheme Configuration
 * @details This structure contains the transmission scheme related information.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfTxSchemeCfg
(
CtfTxSchemeCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfTxSchemeCfg(param, mBuf)
CtfTxSchemeCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfTxSchemeCfg)

   /* ctf_c_001.main_4: Removed UnPacking of param->pres */
   CMCHKUNPK(SUnpkU32, (U32 *)&param->duplexMode, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->scSpacing, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->cycPfx, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfAntennaCfgInfo
*
*
*     Desc:   Antenna Ports configuration
 * @details This structure contains the antenna configuration information for 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfAntennaCfgInfo
(
CtfAntennaCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfAntennaCfgInfo(param, mBuf)
CtfAntennaCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfAntennaCfgInfo)

   CMCHKPK(SPkU32, param->antPortsCnt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfAntennaCfgInfo
*
*
*     Desc:   Antenna Ports configuration
 * @details This structure contains the antenna configuration information for 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfAntennaCfgInfo
(
CtfAntennaCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfAntennaCfgInfo(param, mBuf)
CtfAntennaCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfAntennaCfgInfo)

   CMCHKUNPK(SUnpkU32, (U32 *)&param->antPortsCnt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfPrachCfgInfo
*
*
*     Desc:   PRACH configuration
 * @details This structure contains the configuration information for PRACH at PHY.
 *          -# PRACH preamble sequences are generated by PHY using Zadoff-Chu 
 *             sequences.[Ref: 36.211, 5.7.2]
 *          -# PRACH preamble format is derived from PRACH Configuration Index.
 *             [Ref: 36.211, Table 5.7.1-2]
 *          -# PrachFreqOffset is the first physical resource block allocated to 
 *             the PRACH opportunity considered for preamble format 0, 1, 2, and 3.
 *             [Ref: 36.211, 5.7.1]
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfPrachCfgInfo
(
CtfPrachCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfPrachCfgInfo(param, mBuf)
CtfPrachCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfPrachCfgInfo)

   /*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU8, param->prachFreqOffset, mBuf);
      CMCHKPK(SPkU8, param->highSpeedFlag, mBuf);
      CMCHKPK(SPkU8, param->zeroCorrelationZoneCfg, mBuf);
      CMCHKPK(SPkU8, param->prachCfgIndex, mBuf);
      CMCHKPK(SPkU16, param->rootSequenceIndex, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfPrachCfgInfo
*
*
*     Desc:   PRACH configuration
 * @details This structure contains the configuration information for PRACH at PHY.
 *          -# PRACH preamble sequences are generated by PHY using Zadoff-Chu 
 *             sequences.[Ref: 36.211, 5.7.2]
 *          -# PRACH preamble format is derived from PRACH Configuration Index.
 *             [Ref: 36.211, Table 5.7.1-2]
 *          -# PrachFreqOffset is the first physical resource block allocated to 
 *             the PRACH opportunity considered for preamble format 0, 1, 2, and 3.
 *             [Ref: 36.211, 5.7.1]
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfPrachCfgInfo
(
CtfPrachCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfPrachCfgInfo(param, mBuf)
CtfPrachCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfPrachCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKUNPK(SUnpkU16, &param->rootSequenceIndex, mBuf);
      CMCHKUNPK(SUnpkU8, &param->prachCfgIndex, mBuf);
      CMCHKUNPK(SUnpkU8, &param->zeroCorrelationZoneCfg, mBuf);
      CMCHKUNPK(SUnpkU8, &param->highSpeedFlag, mBuf);
      CMCHKUNPK(SUnpkU8, &param->prachFreqOffset, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfPdschCfgInfo
*
*
*     Desc:   PDSCH configuration
 * @details This structure contains the PDSCH configuration information for 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfPdschCfgInfo
(
CtfPdschCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfPdschCfgInfo(param, mBuf)
CtfPdschCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfPdschCfgInfo)
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU8, param->p_b, mBuf);
      CMCHKPK(SPkS8, param->refSigPwr, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfPdschCfgInfo
*
*
*     Desc:   PDSCH configuration
 * @details This structure contains the PDSCH configuration information for 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfPdschCfgInfo
(
CtfPdschCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfPdschCfgInfo(param, mBuf)
CtfPdschCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfPdschCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
     CMCHKUNPK(SUnpkS8, &param->refSigPwr, mBuf);
     CMCHKUNPK(SUnpkU8, &param->p_b, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfPuschCfgBasic
*
*
*     Desc:   Basic PUSCH configuration
 * @details This structure contains the basic PUSCH configuration information for 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfPuschCfgBasic
(
CtfPuschCfgBasic *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfPuschCfgBasic(param, mBuf)
CtfPuschCfgBasic *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfPuschCfgBasic)

   CMCHKPK(SPkU8, param->enable64QAM, mBuf);
   CMCHKPK(SPkU8, param->hoppingOffset, mBuf);
   CMCHKPK(SPkU32, param->hoppingMode, mBuf);
   CMCHKPK(SPkU8, param->noOfsubBands, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfPuschCfgBasic
*
*
*     Desc:   Basic PUSCH configuration
 * @details This structure contains the basic PUSCH configuration information for 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfPuschCfgBasic
(
CtfPuschCfgBasic *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfPuschCfgBasic(param, mBuf)
CtfPuschCfgBasic *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfPuschCfgBasic)

   CMCHKUNPK(SUnpkU8, &param->noOfsubBands, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->hoppingMode, mBuf);
   CMCHKUNPK(SUnpkU8, &param->hoppingOffset, mBuf);
   CMCHKUNPK(SUnpkU8, &param->enable64QAM, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfPuschUlRS
*
*
*     Desc:   PUSCH Uplink Reference Signals configuration
 * @details This structure contains the PUSCH configuration information for 
 *          uplink reference signals configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfPuschUlRS
(
CtfPuschUlRS *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfPuschUlRS(param, mBuf)
CtfPuschUlRS *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfPuschUlRS)

   CMCHKPK(SPkU8, param->cycShift, mBuf);
   CMCHKPK(SPkU8, param->grpNum, mBuf);
   CMCHKPK(SPkU8, param->seqHopEnabled, mBuf);
   CMCHKPK(SPkU8, param->grpHopEnabled, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfPuschUlRS
*
*
*     Desc:   PUSCH Uplink Reference Signals configuration
 * @details This structure contains the PUSCH configuration information for 
 *          uplink reference signals configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfPuschUlRS
(
CtfPuschUlRS *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfPuschUlRS(param, mBuf)
CtfPuschUlRS *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfPuschUlRS)

   CMCHKUNPK(SUnpkU8, &param->grpHopEnabled, mBuf);
   CMCHKUNPK(SUnpkU8, &param->seqHopEnabled, mBuf);
   CMCHKUNPK(SUnpkU8, &param->grpNum, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cycShift, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfPuschCfgInfo
*
*
*     Desc:   PUSCH configuration
 * @details This structure contains the information for PUSCH 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfPuschCfgInfo
(
CtfPuschCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfPuschCfgInfo(param, mBuf)
CtfPuschCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfPuschCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
     CMCHKPK(cmPkCtfPuschUlRS, &param->puschUlRS, mBuf);
     CMCHKPK(cmPkCtfPuschCfgBasic, &param->puschBasicCfg, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfPuschCfgInfo
*
*
*     Desc:   PUSCH configuration
 * @details This structure contains the information for PUSCH 
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfPuschCfgInfo
(
CtfPuschCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfPuschCfgInfo(param, mBuf)
CtfPuschCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfPuschCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
     CMCHKUNPK(cmUnpkCtfPuschCfgBasic, &param->puschBasicCfg, mBuf);
     CMCHKUNPK(cmUnpkCtfPuschUlRS, &param->puschUlRS, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfPhichCfgInfo
*
*
*     Desc:   PHICH configuration
 * @details This structure contains the duration and resource information for
 *          PHICH configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfPhichCfgInfo
(
CtfPhichCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfPhichCfgInfo(param, mBuf)
CtfPhichCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfPhichCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU32, param->resource, mBuf);
      CMCHKPK(SPkU32, param->duration, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfPhichCfgInfo
*
*
*     Desc:   PHICH configuration
 * @details This structure contains the duration and resource information for
 *          PHICH configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfPhichCfgInfo
(
CtfPhichCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfPhichCfgInfo(param, mBuf)
CtfPhichCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfPhichCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
     CMCHKUNPK(SUnpkU32, (U32 *)&param->duration, mBuf);
     CMCHKUNPK(SUnpkU32, (U32 *)&param->resource, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfPucchCfgInfo
*
*
*     Desc:   PUCCH configuration
 * @details This structure contains the information for PUCCH
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfPucchCfgInfo
(
CtfPucchCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfPucchCfgInfo(param, mBuf)
CtfPucchCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfPucchCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU32, param->deltaShift, mBuf);
      CMCHKPK(SPkU16, param->n1PUCCH, mBuf);
      CMCHKPK(SPkU8, param->nCS, mBuf);
      CMCHKPK(SPkU8, param->nRB, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfPucchCfgInfo
*
*
*     Desc:   PUCCH configuration
 * @details This structure contains the information for PUCCH
 *          configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfPucchCfgInfo
(
CtfPucchCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfPucchCfgInfo(param, mBuf)
CtfPucchCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfPucchCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKUNPK(SUnpkU8, &param->nRB, mBuf);
      CMCHKUNPK(SUnpkU8, &param->nCS, mBuf);
      CMCHKUNPK(SUnpkU16, &param->n1PUCCH, mBuf);
      CMCHKUNPK(SUnpkU32, (U32 *)&param->deltaShift, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfSrsUlCfgInfo
*
*
*     Desc:   SRS uplink configuration
 * @details This structure contains the information for setting-up/release
 *          of uplink SRS configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfSrsUlCfgInfo
(
CtfSrsUlCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfSrsUlCfgInfo(param, mBuf)
CtfSrsUlCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfSrsUlCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU8, param->srsSetup.srsMaxUpPts, mBuf);
      CMCHKPK(SPkU8, param->srsSetup.srsANSimultTx, mBuf);
      CMCHKPK(SPkU8, param->srsSetup.sfCfg, mBuf);
      CMCHKPK(SPkU8, param->srsSetup.srsBw, mBuf);
      CMCHKPK(SPkU8, param->srsCfgType, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfSrsUlCfgInfo
*
*
*     Desc:   SRS uplink configuration
 * @details This structure contains the information for setting-up/release
 *          of uplink SRS configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfSrsUlCfgInfo
(
CtfSrsUlCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfSrsUlCfgInfo(param, mBuf)
CtfSrsUlCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfSrsUlCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKUNPK(SUnpkU8, &param->srsCfgType, mBuf);
      CMCHKUNPK(SUnpkU8, &param->srsSetup.srsBw, mBuf);
      CMCHKUNPK(SUnpkU8, &param->srsSetup.sfCfg, mBuf);
      CMCHKUNPK(SUnpkU8, &param->srsSetup.srsANSimultTx, mBuf);
      CMCHKUNPK(SUnpkU8, &param->srsSetup.srsMaxUpPts, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfTddSfCfgInfo
*
*
*     Desc:   Subframe Configuration for TDD mode.
 * @details This structure contains the information for setting-up
 *          the subframe for TDD mode at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfTddSfCfgInfo
(
CtfTddSfCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfTddSfCfgInfo(param, mBuf)
CtfTddSfCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfTddSfCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU8, param->spclSfPatterns, mBuf);
      CMCHKPK(SPkU8, param->sfAssignment, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}


/* ctf_c_001.main_4: Added support for vendor specific parameters */
#ifdef CTF_VER3
/***********************************************************
*
*     Func: cmPkCtfVendorSpecParams
*
*
*     Desc: Vendor Specific Parameter configuration 
*   @details This structure contains the Parameters which is spaciftc to
*            Vendor.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfVendorSpecParams
(
CtfVendorSpecific *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfVendorSpecParams(param, mBuf)
CtfVendorSpecific *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfVendorSpecParams)
   if( param->buffLen != 0) {
     SAddPreMsgMultInOrder(param->paramBuffer,param->buffLen,mBuf);   
   }
   CMCHKPK(SPkU16,param->buffLen,mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func: cmUnpkCtfVendorSpecParams
*
*
*     Desc: Vendor Specific Parameter configuration  
* @details  This structure contains the Parameters which is spaciftc to
*           Vendor.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfVendorSpecParams
(
Pst *pst,
CtfVendorSpecific *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfVendorSpecParams(pst, param, mBuf)
Pst *pst;
CtfVendorSpecific *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfVendorSpecParams)

   CMCHKUNPK(SUnpkU16, &param->buffLen, mBuf);

   if(param->buffLen != 0) {
      if ((SGetSBuf(pst->region, pst->pool, (Data **)&param->paramBuffer, param->buffLen)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECTF060, (ErrVal)0, (Txt*)&"Unpacking failed");
#endif
         RETVALUE(RFAILED) ;
      }
      SRemPreMsgMult(param->paramBuffer, param->buffLen,mBuf) ;   
   }
   else {
      param->paramBuffer = NULLP ;
   }

   RETVALUE(ROK);
}
#endif

/***********************************************************
*
*     Func: cmUnpkCtfTddSfCfgInfo
*
*
*     Desc:   Subframe Configuration for TDD mode.
 * @details This structure contains the information for setting-up
 *          the subframe for TDD mode at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfTddSfCfgInfo
(
CtfTddSfCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfTddSfCfgInfo(param, mBuf)
CtfTddSfCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfTddSfCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKUNPK(SUnpkU8, &param->sfAssignment, mBuf);
      CMCHKUNPK(SUnpkU8, &param->spclSfPatterns, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfCellCfgInfo
*
*
*     Desc:   Cell Configuration Information
 * @details This structure contains the information for setting-up
 *          of a cell and its associated resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfCellCfgInfo
(
CtfCellCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfCellCfgInfo(param, mBuf)
CtfCellCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfCellCfgInfo)
   CMCHKPK(cmPkCtfTddSfCfgInfo, &param->tddSfCfg, mBuf);
   CMCHKPK(cmPkCtfSrsUlCfgInfo, &param->srsUlCfg, mBuf);
   CMCHKPK(cmPkCtfPucchCfgInfo, &param->pucchCfg, mBuf);
   CMCHKPK(cmPkCtfPhichCfgInfo, &param->phichCfg, mBuf);
   CMCHKPK(cmPkCtfPuschCfgInfo, &param->puschCfg, mBuf);
   CMCHKPK(cmPkCtfPdschCfgInfo, &param->pdschCfg, mBuf);
   CMCHKPK(cmPkCtfPrachCfgInfo, &param->prachCfg, mBuf);
   CMCHKPK(cmPkCtfAntennaCfgInfo, &param->antennaCfg, mBuf);
   CMCHKPK(cmPkCtfTxSchemeCfg, &param->txCfg, mBuf);
   CMCHKPK(cmPkCtfBwCfgInfo, &param->bwCfg, mBuf);
   CMCHKPK(SPkU8, param->physCellId, mBuf);
   CMCHKPK(SPkU8, param->cellIdGrpId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfCellCfgInfo
*
*
*     Desc:   Cell Configuration Information
 * @details This structure contains the information for setting-up
 *          of a cell and its associated resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfCellCfgInfo
(
CtfCellCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfCellCfgInfo(param, mBuf)
CtfCellCfgInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkCtfCellCfgInfo)

   /* ctf_c_001.main_3: Added the unpack for newly added fileds inside the CFG structure*/
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cellIdGrpId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->physCellId, mBuf);
   CMCHKUNPK(cmUnpkCtfBwCfgInfo, &param->bwCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfTxSchemeCfg, &param->txCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfAntennaCfgInfo, &param->antennaCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfPrachCfgInfo, &param->prachCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfPdschCfgInfo, &param->pdschCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfPuschCfgInfo, &param->puschCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfPhichCfgInfo, &param->phichCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfPucchCfgInfo, &param->pucchCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfSrsUlCfgInfo, &param->srsUlCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfTddSfCfgInfo, &param->tddSfCfg, mBuf);

   RETVALUE(ROK);
}



/* ctf_c_001.main_4: Modified cmPkCtfCellRecfgInfo() to Add support for
 * vendor specific parameters */
/***********************************************************
*
*     Func: cmPkCtfCellRecfgInfo
*
*
*     Desc:   Cell Re-configuration Information
 * @details This structure contains the information for reconfiguration
 *          of a cell and its associated resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfCellRecfgInfo
(
CtfCellRecfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfCellRecfgInfo(param, mBuf)
CtfCellRecfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfCellRecfgInfo)
   CMCHKPK(cmPkCtfTddSfCfgInfo, &param->tddSfCfg, mBuf);
   CMCHKPK(cmPkCtfSrsUlCfgInfo, &param->srsUlCfg, mBuf);
   CMCHKPK(cmPkCtfPucchCfgInfo, &param->pucchCfg, mBuf);
   CMCHKPK(cmPkCtfPhichCfgInfo, &param->phichCfg, mBuf);
   CMCHKPK(cmPkCtfPuschCfgInfo, &param->puschCfg, mBuf);
   CMCHKPK(cmPkCtfPdschCfgInfo, &param->pdschCfg, mBuf);
   CMCHKPK(cmPkCtfPrachCfgInfo, &param->prachCfg, mBuf);
   CMCHKPK(cmPkLteTimingInfo, &param->actvnTime, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/* ctf_c_001.main_4: Modified cmUnpkCtfCellRecfgInfo() to Add support for
 * vendor specific parameters */
/***********************************************************
*
*     Func: cmUnpkCtfCellRecfgInfo
*
*
*     Desc:   Cell Re-configuration Information
 * @details This structure contains the information for reconfiguration
 *          of a cell and its associated resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfCellRecfgInfo
(
CtfCellRecfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfCellRecfgInfo(param, mBuf)
CtfCellRecfgInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkCtfCellRecfgInfo)
   
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteTimingInfo, &param->actvnTime, mBuf);
   CMCHKUNPK(cmUnpkCtfPrachCfgInfo, &param->prachCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfPdschCfgInfo, &param->pdschCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfPuschCfgInfo, &param->puschCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfPhichCfgInfo, &param->phichCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfPucchCfgInfo, &param->pucchCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfSrsUlCfgInfo, &param->srsUlCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfTddSfCfgInfo, &param->tddSfCfg, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfDedPdschCfgInfo
*
*
*     Desc:   Dedicated PDSCH Configuration
 * @details This structure contains the information for PDSCH configuration
 *          specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfDedPdschCfgInfo
(
CtfDedPdschCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfDedPdschCfgInfo(param, mBuf)
CtfDedPdschCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfDedPdschCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
      CMCHKPK(SPkU32, param->pA, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfDedPdschCfgInfo
*
*
*     Desc:   Dedicated PDSCH Configuration
 * @details This structure contains the information for PDSCH configuration
 *          specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfDedPdschCfgInfo
(
CtfDedPdschCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfDedPdschCfgInfo(param, mBuf)
CtfDedPdschCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfDedPdschCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
      CMCHKUNPK(SUnpkU32, (U32 *)&param->pA, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfDedPucchCfgInfo
*
*
*     Desc:   Dedicated PUCCH Configuration
 * @details This structure contains the information for setting-up/release 
 *          PUCCH configuration specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfDedPucchCfgInfo
(
CtfDedPucchCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfDedPucchCfgInfo(param, mBuf)
CtfDedPucchCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfDedPucchCfgInfo)

/*ctf_c_001.main_1*/
  if(param->pres != FALSE)
  {
#ifdef CTF_VER3
     /*ctf_c_001.main_4:115549: packing tddAckNackFBMode and tddAckNackCfgPres */
       if (param->tddAckNackCfgPres != FALSE)
       {
          CMCHKPK(SPkU32, param->tddAckNackFBMode, mBuf);
       }
 
       CMCHKPK(SPkU8, param->tddAckNackCfgPres, mBuf);
#endif /* CTF_VER3 */
      CMCHKPK(SPkU16, param->pucchSetup.n1PUCCHRep, mBuf);
#ifdef CTF_VER3
      /*ctf_c_001.main_4:115549: packing pucchSetup.repFactPres */
       if (param->pucchSetup.repFactPres)
       {
          CMCHKPK(SPkU32, param->pucchSetup.repFact, mBuf);
       }
 
       CMCHKPK(SPkU8, param->pucchSetup.repFactPres, mBuf);
#else
        CMCHKPK(SPkU32, param->pucchSetup.repFact, mBuf);
#endif /* CTF_VER3 */
      CMCHKPK(SPkU8, param->dedPucchCfgType, mBuf);
  }
  CMCHKPK(SPkU8, param->pres, mBuf);
  RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfDedPucchCfgInfo
*
*
*     Desc:   Dedicated PUCCH Configuration
 * @details This structure contains the information for setting-up/release 
 *          PUCCH configuration specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfDedPucchCfgInfo
(
CtfDedPucchCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfDedPucchCfgInfo(param, mBuf)
CtfDedPucchCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfDedPucchCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKUNPK(SUnpkU8, &param->dedPucchCfgType, mBuf);
#ifdef CTF_VER3
      /* ctf_c_001.main_4:115549: unpacking pucchSetup.repFactPres */
       CMCHKUNPK(SUnpkU8, &param->pucchSetup.repFactPres, mBuf);
 
       if (param->pucchSetup.repFactPres)
       {
          CMCHKUNPK(SUnpkU32, (U32 *)&param->pucchSetup.repFact, mBuf);
       }
#else
        CMCHKUNPK(SUnpkU32, (U32 *)&param->pucchSetup.repFact, mBuf);
#endif /*CTF_VER3 */
      CMCHKUNPK(SUnpkU16, &param->pucchSetup.n1PUCCHRep, mBuf);
#ifdef CTF_VER3
      /*ctf_c_001.main_4:115549: unpacking tddAckNackCfgPres and tddAckNackFBMode */
      CMCHKUNPK(SUnpkU8, &param->tddAckNackCfgPres, mBuf);

      if (param->tddAckNackCfgPres != FALSE)
      {
         CMCHKUNPK(SUnpkU32, (U32 *)&param->tddAckNackFBMode, mBuf);
      }
#endif /* CTF_VER3 */
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfDedPuschCfgInfo
*
*
*     Desc:   Dedicated PUSCH Configuration
 * @details This structure contains the information for PUCCH 
 *          configuration specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfDedPuschCfgInfo
(
CtfDedPuschCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfDedPuschCfgInfo(param, mBuf)
CtfDedPuschCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfDedPuschCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU8, param->betaOffsetCqiIdx, mBuf);
      CMCHKPK(SPkU8, param->betaOffsetRiIdx, mBuf);
      CMCHKPK(SPkU8, param->betaOffsetAckIdx, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfDedPuschCfgInfo
*
*
*     Desc:   Dedicated PUSCH Configuration
 * @details This structure contains the information for PUCCH 
 *          configuration specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfDedPuschCfgInfo
(
CtfDedPuschCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfDedPuschCfgInfo(param, mBuf)
CtfDedPuschCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfDedPuschCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKUNPK(SUnpkU8, &param->betaOffsetAckIdx, mBuf);
      CMCHKUNPK(SUnpkU8, &param->betaOffsetRiIdx, mBuf);
      CMCHKUNPK(SUnpkU8, &param->betaOffsetCqiIdx, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfCqiRptModePeriodic
*
*
*     Desc:   Periodic CQI Report Configuration
 * @details This structure contains the information for periodic CQI report
 *          related configuration specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfCqiRptModePeriodic
(
CtfCqiRptModePeriodic *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfCqiRptModePeriodic(param, mBuf)
CtfCqiRptModePeriodic *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfCqiRptModePeriodic)
/* ctf_c_001.main_2: added packning for cqiMask*/
#ifdef CTF_VER1
      CMCHKPK(SPkU32, (U32 )param->cqiSetup.cqiMask.cqiMaskSetup, mBuf);
      CMCHKPK(SPkU8, param->cqiSetup.cqiMask.pres, mBuf);
#endif /* CTF_VER1 */
      CMCHKPK(SPkU8, param->cqiSetup.simultaneousAckNack, mBuf);
      CMCHKPK(SPkU16, param->cqiSetup.riCfgIndx, mBuf);
      CMCHKPK(SPkU8, param->cqiSetup.riCfgPres, mBuf);
      CMCHKPK(SPkU8, param->cqiSetup.subbandCqi.k, mBuf);
      CMCHKPK(SPkU8, param->cqiSetup.formatIndicator, mBuf);
      CMCHKPK(SPkU16, param->cqiSetup.cqiPmiCfgIndx, mBuf);
      CMCHKPK(SPkU16, param->cqiSetup.cqiPUCCHRsrcIndx, mBuf);
   CMCHKPK(SPkU8, param->cqiPeriodicCfgType, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfCqiRptModePeriodic
*
*
*     Desc:   Periodic CQI Report Configuration
 * @details This structure contains the information for periodic CQI report
 *          related configuration specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfCqiRptModePeriodic
(
CtfCqiRptModePeriodic *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfCqiRptModePeriodic(param, mBuf)
CtfCqiRptModePeriodic *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfCqiRptModePeriodic)

   CMCHKUNPK(SUnpkU8, &param->cqiPeriodicCfgType, mBuf);
      CMCHKUNPK(SUnpkU16, &param->cqiSetup.cqiPUCCHRsrcIndx, mBuf);
      CMCHKUNPK(SUnpkU16, &param->cqiSetup.cqiPmiCfgIndx, mBuf);
      CMCHKUNPK(SUnpkU8, &param->cqiSetup.formatIndicator, mBuf);
         CMCHKUNPK(SUnpkU8, &param->cqiSetup.subbandCqi.k, mBuf);
      CMCHKUNPK(SUnpkU8, &param->cqiSetup.riCfgPres, mBuf);
      CMCHKUNPK(SUnpkU16, &param->cqiSetup.riCfgIndx, mBuf);
      CMCHKUNPK(SUnpkU8, &param->cqiSetup.simultaneousAckNack, mBuf);
/* ctf_c_001.main_2: added Unpackning for cqiMask*/
#ifdef CTF_VER1
      CMCHKUNPK(SUnpkU8, &param->cqiSetup.cqiMask.pres, mBuf);
      CMCHKUNPK(SUnpkU32, (U32 *)&param->cqiSetup.cqiMask.cqiMaskSetup, mBuf);
#endif /* CTF_VER1 */
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfCqiReportCfgInfo
*
*
*     Desc:   CQI Report Configuration
 * @details This structure contains the information for CQI report
 *          related configuration specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfCqiReportCfgInfo
(
CtfCqiReportCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfCqiReportCfgInfo(param, mBuf)
CtfCqiReportCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfCqiReportCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
#ifdef CTF_VER2
      /* 
       * ctf_c_001.main_2: Added provision to send Periodic and aPeriodic CQI
       *report configuration in the same message
       */
       if(param->reportMode.aPeriodicRpt.pres != FALSE)
       {
           CMCHKPK(SPkU32, param->reportMode.aPeriodicRpt.aPeriodicRptMode, mBuf);
       }
       CMCHKPK(SPkU8, param->reportMode.aPeriodicRpt.pres, mBuf);

       if(param->reportMode.periodicRpt.pres != FALSE)
       {
           CMCHKPK(cmPkCtfCqiRptModePeriodic, &param->reportMode.periodicRpt, mBuf);
       }
       CMCHKPK(SPkU8, param->reportMode.periodicRpt.pres, mBuf);

#else /* CTF_VER2 */

      switch(param->reportingMode) {
         case CTF_CQI_RPTMODE_PRDIOC:
            CMCHKPK(cmPkCtfCqiRptModePeriodic, &param->reportMode.periodicRpt, mBuf);
            break;
         case CTF_CQI_RPTMODE_APRDIOC:
            CMCHKPK(SPkU32, param->reportMode.aPeriodicRpt, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
      CMCHKPK(SPkU8, param->reportingMode, mBuf);
#endif /* CTF_VER2 */

/* ctf_c_001.main_2: added packning for pmiRiRpt*/
#ifdef CTF_VER1
       CMCHKPK(SPkU32, param->pmiRiRpt.pmiRiRptSetup, mBuf);
       CMCHKPK(SPkU8, param->pmiRiRpt.pres, mBuf);
#endif /* CTF_VER1 */
   }

   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfCqiReportCfgInfo
*
*
*     Desc:   CQI Report Configuration
 * @details This structure contains the information for CQI report
 *          related configuration specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfCqiReportCfgInfo
(
CtfCqiReportCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfCqiReportCfgInfo(param, mBuf)
CtfCqiReportCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfCqiReportCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
/* ctf_c_001.main_2: added Unpackning for cqiMask*/
#ifdef CTF_VER1
      CMCHKUNPK(SUnpkU8, &param->pmiRiRpt.pres, mBuf);
      CMCHKUNPK(SUnpkU32, (U32 *)&param->pmiRiRpt.pmiRiRptSetup, mBuf);
#endif /* CTF_VER1 */

#ifdef CTF_VER2
      /* 
       *ctf_c_001.main_2: Added provision to send Periodic and aPeriodic CQI
       *report configuration in the same message
       */
      CMCHKUNPK(SUnpkU8, &param->reportMode.periodicRpt.pres, mBuf)
      if(param->reportMode.periodicRpt.pres != FALSE)
      {
         CMCHKUNPK(cmUnpkCtfCqiRptModePeriodic, &param->reportMode.periodicRpt, mBuf);
      }
       
      CMCHKUNPK(SUnpkU8, &param->reportMode.aPeriodicRpt.pres, mBuf)
      if(param->reportMode.aPeriodicRpt.pres != FALSE)
      {
         CMCHKUNPK(SUnpkU32, (U32 *)&param->reportMode.aPeriodicRpt.\
               aPeriodicRptMode, mBuf);
      }

#else /* CTF_VER2 */

      CMCHKUNPK(SUnpkU8, &param->reportingMode, mBuf);
      switch(param->reportingMode) {
         case CTF_CQI_RPTMODE_APRDIOC:
            CMCHKUNPK(SUnpkU32, (U32 *)&param->reportMode.aPeriodicRpt, mBuf);
            break;
         case CTF_CQI_RPTMODE_PRDIOC:
            CMCHKUNPK(cmUnpkCtfCqiRptModePeriodic, &param->reportMode.periodicRpt, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
#endif /* CTF_VER2 */
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfDedSrsUlCfgInfo
*
*
*     Desc:   Dedicated Uplink SRS Configuration
 * @details This structure contains the information for setting-up/release
 *          UL SRS configuration specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfDedSrsUlCfgInfo
(
CtfDedSrsUlCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfDedSrsUlCfgInfo(param, mBuf)
CtfDedSrsUlCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfDedSrsUlCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU8, param->dedSrsSetup.cyclicShift, mBuf);
      CMCHKPK(SPkU8, param->dedSrsSetup.txComb, mBuf);
      CMCHKPK(SPkU16, param->dedSrsSetup.srsCfgIdx, mBuf);
      CMCHKPK(SPkU8, param->dedSrsSetup.duration, mBuf);
      CMCHKPK(SPkU8, param->dedSrsSetup.freqDmnPos, mBuf);
      CMCHKPK(SPkU8, param->dedSrsSetup.srsHopngBw, mBuf);
      CMCHKPK(SPkU8, param->dedSrsSetup.srsBw, mBuf);
      CMCHKPK(SPkU8, param->dedSrsUlCfgType, mBuf);
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfDedSrsUlCfgInfo
*
*
*     Desc:   Dedicated Uplink SRS Configuration
 * @details This structure contains the information for setting-up/release
 *          UL SRS configuration specific to an UE.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfDedSrsUlCfgInfo
(
CtfDedSrsUlCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfDedSrsUlCfgInfo(param, mBuf)
CtfDedSrsUlCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfDedSrsUlCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKUNPK(SUnpkU8, &param->dedSrsUlCfgType, mBuf);
      CMCHKUNPK(SUnpkU8, &param->dedSrsSetup.srsBw, mBuf);
      CMCHKUNPK(SUnpkU8, &param->dedSrsSetup.srsHopngBw, mBuf);
      CMCHKUNPK(SUnpkU8, &param->dedSrsSetup.freqDmnPos, mBuf);
      CMCHKUNPK(SUnpkU8, &param->dedSrsSetup.duration, mBuf);
      CMCHKUNPK(SUnpkU16, &param->dedSrsSetup.srsCfgIdx, mBuf);
      CMCHKUNPK(SUnpkU8, &param->dedSrsSetup.txComb, mBuf);
      CMCHKUNPK(SUnpkU8, &param->dedSrsSetup.cyclicShift, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfDedSRCfgInfo
*
*
*     Desc:   Dedicated SR Configuration
 * @details This structure contains the information for setting-up/release
 *          SR configuration specific to an UE at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfDedSRCfgInfo
(
CtfDedSRCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfDedSRCfgInfo(param, mBuf)
CtfDedSRCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfDedSRCfgInfo)

/*ctf_c_001.main_1*/
  if(param->pres != FALSE)
  {
     CMCHKPK(SPkU8, param->dedSrSetup.srCfgIdx, mBuf);
     CMCHKPK(SPkU16, param->dedSrSetup.srPUCCHRi, mBuf);
     CMCHKPK(SPkU8, param->dedSRCfgType, mBuf);
  }
  CMCHKPK(SPkU8, param->pres, mBuf);
  RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfDedSRCfgInfo
*
*
*     Desc:   Dedicated SR Configuration
 * @details This structure contains the information for setting-up/release
 *          SR configuration specific to an UE at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfDedSRCfgInfo
(
CtfDedSRCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfDedSRCfgInfo(param, mBuf)
CtfDedSRCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfDedSRCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKUNPK(SUnpkU8, &param->dedSRCfgType, mBuf);
      CMCHKUNPK(SUnpkU16, &param->dedSrSetup.srPUCCHRi, mBuf);
      CMCHKUNPK(SUnpkU8, &param->dedSrSetup.srCfgIdx, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfDedAntCfgInfo
*
*
*     Desc:   Dedicated Antenna Configuration
 * @details This structure contains the information for antenna related
 *          configuration specific to an UE at PHY.
*
*
*     Ret : S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfDedAntCfgInfo
(
CtfDedAntCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfDedAntCfgInfo(param, mBuf)
CtfDedAntCfgInfo *param;
Buffer *mBuf;
#endif
{
   
#ifdef CTF_VER2
   U8  idx;
#endif  /* CTF_VER2 */

   TRC3(cmPkCtfDedAntCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
      CMCHKPK(SPkU32, param->ueTxAntSelection.txAntSelect, mBuf);
      CMCHKPK(SPkU8, param->ueTxAntSelection.cfgType, mBuf);
     /* ctf_c_001.main_3 txMode is of type enum and is 32bit length */
      CMCHKPK(SPkU32, (U32)param->txMode, mBuf);
#ifdef CTF_VER2
      /* 
       *ctf_c_001.main_2: Added Packing of CodeBookSubsetRestriction parameter
       */
      switch(param->codeBookSubsetRes.ctfCdBkRestType)
      {
          case N2TX_ANT_TM3:
              CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.
			     n2TxAntTm3, mBuf);
	      break;

          case N4TX_ANT_TM3:
              CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.
			     n4TxAntTm3, mBuf);
	      break;

          case N2TX_ANT_TM4:
              CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.
			     n2TxAntTm4, mBuf);
	      break;

          case N4TX_ANT_TM4:
              for(idx = 0; idx < 8; idx++)
                  CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.
				 n4TxAntTm4[idx], mBuf);
	      break;

          case N2TX_ANT_TM5:
              CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.
			     n2TxAntTm5, mBuf);
	      break;

          case N4TX_ANT_TM5:
              CMCHKPK(SPkU16, param->codeBookSubsetRes.codeBookSubsetRestn.
			      n4TxAntTm5, mBuf);
	      break;

          case N2TX_ANT_TM6:
              CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.
			     n2TxAntTm6, mBuf);
	      break;

          case N4TX_ANT_TM6:
              CMCHKPK(SPkU16, param->codeBookSubsetRes.codeBookSubsetRestn.
			      n4TxAntTm6, mBuf);
	      break;
	  default :
              break;

      }
      CMCHKPK(SPkU32, param->codeBookSubsetRes.ctfCdBkRestType, mBuf);
#endif /* CTF_VER2 */
   }
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfDedAntCfgInfo
*
*
*     Desc:   Dedicated Antenna Configuration
 * @details This structure contains the information for antenna related
 *          configuration specific to an UE at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfDedAntCfgInfo
(
CtfDedAntCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfDedAntCfgInfo(param, mBuf)
CtfDedAntCfgInfo *param;
Buffer *mBuf;
#endif
{
#ifdef CTF_VER2
   S16  idx;
#endif /* CTF_VER2 */

   TRC3(cmUnpkCtfDedAntCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
   {
#ifdef CTF_VER2
      /* 
       * Added Unpacking for CodeBookSubsetRestriction parameter
       */
      CMCHKUNPK(SUnpkU32, (U32 *)&param->codeBookSubsetRes.ctfCdBkRestType, mBuf);
      switch(param->codeBookSubsetRes.ctfCdBkRestType)
      {
          case N2TX_ANT_TM3:
              CMCHKUNPK(SUnpkU8, &param->codeBookSubsetRes.codeBookSubsetRestn.
			     n2TxAntTm3, mBuf);
	      break;

          case N4TX_ANT_TM3:
              CMCHKUNPK(SUnpkU8, &param->codeBookSubsetRes.codeBookSubsetRestn.
			     n4TxAntTm3, mBuf);
	      break;

          case N2TX_ANT_TM4:
              CMCHKUNPK(SUnpkU8, &param->codeBookSubsetRes.codeBookSubsetRestn.
			     n2TxAntTm4, mBuf);
	      break;

          case N4TX_ANT_TM4:
              for(idx = 7; idx >= 0; idx--)
              {
                 CMCHKUNPK(SUnpkU8, &(param->codeBookSubsetRes.codeBookSubsetRestn.
                       n4TxAntTm4[idx]), mBuf);
              }
	      break;

          case N2TX_ANT_TM5:
              CMCHKUNPK(SUnpkU8, &param->codeBookSubsetRes.codeBookSubsetRestn.
			     n2TxAntTm5, mBuf);
	      break;

          case N4TX_ANT_TM5:
              CMCHKUNPK(SUnpkU16, &param->codeBookSubsetRes.codeBookSubsetRestn.
			      n4TxAntTm5, mBuf);
	      break;

          case N2TX_ANT_TM6:
              CMCHKUNPK(SUnpkU8, &param->codeBookSubsetRes.codeBookSubsetRestn.
			     n2TxAntTm6, mBuf);
	      break;

          case N4TX_ANT_TM6:
              CMCHKUNPK(SUnpkU16, &param->codeBookSubsetRes.codeBookSubsetRestn.
			      n4TxAntTm6, mBuf);
	      break;
	  default :
              break;
      }
#endif /* CTF_VER2 */
      /* ctf_c_001.main_3 Enum is 32bit length */
      CMCHKUNPK(SUnpkU32, (U32 *)&param->txMode, mBuf);
      CMCHKUNPK(SUnpkU8, &param->ueTxAntSelection.cfgType, mBuf);
      CMCHKUNPK(SUnpkU32, (U32 *)&param->ueTxAntSelection.txAntSelect, mBuf);
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfUeCatCfgInfo
*
*
*     Desc:   UE Category Configuration
 * @details This structure contains the information for configuring
 *          the UE category at PHY.
*
*
*     Ret : S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfUeCatCfgInfo
(
CtfUeCatCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfUeCatCfgInfo(param, mBuf)
CtfUeCatCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfUeCatCfgInfo)

/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
      CMCHKPK(SPkU32, param->ueCategory, mBuf);
   CMCHKPK(SPkU8, param->pres, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfUeCatCfgInfo
*
*
*     Desc:   UE Category Configuration
 * @details This structure contains the information for configuring
 *          the UE category at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfUeCatCfgInfo
(
CtfUeCatCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfUeCatCfgInfo(param, mBuf)
CtfUeCatCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfUeCatCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->pres, mBuf);
/*ctf_c_001.main_1*/
   if(param->pres != FALSE)
      CMCHKUNPK(SUnpkU32, (U32 *)&param->ueCategory, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfDedCfgInfo
*
*
*     Desc:   Dedicated Configuration Information
 * @details This structure contains the information for configuration 
 *          of UE-specific physical channel resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfDedCfgInfo
(
CtfDedCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfDedCfgInfo(param, mBuf)
CtfDedCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfDedCfgInfo)

   CMCHKPK(cmPkCtfDedAntCfgInfo, &param->antInfo, mBuf);
   CMCHKPK(cmPkCtfDedSRCfgInfo, &param->dedSRCfg, mBuf);
   CMCHKPK(cmPkCtfDedSrsUlCfgInfo, &param->srsUlCfg, mBuf);
   CMCHKPK(cmPkCtfCqiReportCfgInfo, &param->cqiRptCfg, mBuf);
   CMCHKPK(cmPkCtfDedPuschCfgInfo, &param->puschCfg, mBuf);
   CMCHKPK(cmPkCtfDedPucchCfgInfo, &param->pucchCfg, mBuf);
   CMCHKPK(cmPkCtfDedPdschCfgInfo, &param->pdschCfg, mBuf);
   CMCHKPK(cmPkCtfUeCatCfgInfo, &param->ueCatCfg, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfDedCfgInfo
*
*
*     Desc:   Dedicated Configuration Information
 * @details This structure contains the information for configuration 
 *          of UE-specific physical channel resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfDedCfgInfo
(
CtfDedCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfDedCfgInfo(param, mBuf)
CtfDedCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfDedCfgInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   CMCHKUNPK(cmUnpkCtfUeCatCfgInfo, &param->ueCatCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedPdschCfgInfo, &param->pdschCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedPucchCfgInfo, &param->pucchCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedPuschCfgInfo, &param->puschCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfCqiReportCfgInfo, &param->cqiRptCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedSrsUlCfgInfo, &param->srsUlCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedSRCfgInfo, &param->dedSRCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedAntCfgInfo, &param->antInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfDedRecfgInfo
*
*
*     Desc:   Dedicated Re-configuration Information
 * @details This structure contains the information for re-configuration 
 *          of UE-specific physical channel resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfDedRecfgInfo
(
CtfDedRecfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfDedRecfgInfo(param, mBuf)
CtfDedRecfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfDedRecfgInfo)

   /*ctf_c_001.main_1*/
   CMCHKPK(cmPkCtfDedAntCfgInfo, &param->antInfo, mBuf);
   CMCHKPK(cmPkCtfCqiReportCfgInfo, &param->cqiRptCfg, mBuf);
   CMCHKPK(cmPkCtfDedSRCfgInfo, &param->dedSRCfg, mBuf);
   CMCHKPK(cmPkCtfDedSrsUlCfgInfo, &param->srsUlCfg, mBuf);
   CMCHKPK(cmPkCtfDedPuschCfgInfo, &param->puschCfg, mBuf);
   CMCHKPK(cmPkCtfDedPucchCfgInfo, &param->pucchCfg, mBuf);
   CMCHKPK(cmPkCtfDedPdschCfgInfo, &param->pdschCfg, mBuf);
   CMCHKPK(cmPkCtfUeCatCfgInfo, &param->ueCatCfg, mBuf);
   /* ctf_c_001.main_4: ReEst Fix */
#ifdef CTF_VER3
   CMCHKPK(cmPkLteRnti, param->newUeId, mBuf);
#endif
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfDedRecfgInfo
*
*
*     Desc:   Dedicated Re-configuration Information
 * @details This structure contains the information for re-configuration 
 *          of UE-specific physical channel resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfDedRecfgInfo
(
CtfDedRecfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfDedRecfgInfo(param, mBuf)
CtfDedRecfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfDedRecfgInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   /* ctf_c_001.main_4: ReEst Fix */
#ifdef CTF_VER3
   CMCHKUNPK(cmUnpkLteRnti, &param->newUeId, mBuf);
#endif
   CMCHKUNPK(cmUnpkCtfUeCatCfgInfo, &param->ueCatCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedPdschCfgInfo, &param->pdschCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedPucchCfgInfo, &param->pucchCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedPuschCfgInfo, &param->puschCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedSrsUlCfgInfo, &param->srsUlCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedSRCfgInfo, &param->dedSRCfg, mBuf);
   /*ctf_c_001.main_1*/
   CMCHKUNPK(cmUnpkCtfCqiReportCfgInfo, &param->cqiRptCfg, mBuf);
   CMCHKUNPK(cmUnpkCtfDedAntCfgInfo, &param->antInfo, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfCellReleaseInfo
*
*
*     Desc:   Cell Release Information
 * @details This structure contains the information for release/removal 
 *          of a cell and its assocated resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfCellReleaseInfo
(
CtfCellReleaseInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfCellReleaseInfo(param, mBuf)
CtfCellReleaseInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfCellReleaseInfo)

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfCellReleaseInfo
*
*
*     Desc:   Cell Release Information
 * @details This structure contains the information for release/removal 
 *          of a cell and its assocated resources at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfCellReleaseInfo
(
CtfCellReleaseInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfCellReleaseInfo(param, mBuf)
CtfCellReleaseInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfCellReleaseInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfDedReleaseInfo
*
*
*     Desc:   Dedicated Release Information
 * @details This structure contains the information for release/removal 
 *          of dedicated/UE-specific configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfDedReleaseInfo
(
CtfDedReleaseInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfDedReleaseInfo(param, mBuf)
CtfDedReleaseInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfDedReleaseInfo)

   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfDedReleaseInfo
*
*
*     Desc:   Dedicated Release Information
 * @details This structure contains the information for release/removal 
 *          of dedicated/UE-specific configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfDedReleaseInfo
(
CtfDedReleaseInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfDedReleaseInfo(param, mBuf)
CtfDedReleaseInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfDedReleaseInfo)

   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   CMCHKUNPK(cmUnpkLteRnti, &param->ueId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfCfgInfo
*
*
*     Desc:   Configuration Information
 * @details This structure contains the information for setting-up 
 *          cell or UE-specific configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfCfgInfo
(
CtfCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfCfgInfo(param, mBuf)
CtfCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfCfgInfo)

      switch(param->cfgElem) {
         case CTF_UE_CFG:
            CMCHKPK(cmPkCtfDedCfgInfo, &param->u.dedCfg, mBuf);
            break;
         case CTF_CELL_CFG:
            CMCHKPK(cmPkCtfCellCfgInfo, &param->u.cellCfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->cfgElem, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfCfgInfo
*
*
*     Desc:   Configuration Information
 * @details This structure contains the information for setting-up 
 *          cell or UE-specific configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfCfgInfo
(
CtfCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfCfgInfo(param, mBuf)
CtfCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->cfgElem, mBuf);
      switch(param->cfgElem) {
         case CTF_CELL_CFG:
            CMCHKUNPK(cmUnpkCtfCellCfgInfo, &param->u.cellCfg, mBuf);
            break;
         case CTF_UE_CFG:
            CMCHKUNPK(cmUnpkCtfDedCfgInfo, &param->u.dedCfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }      
   
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfReCfgInfo
*
*
*     Desc:   Re-configuration Information
 * @details This structure contains the information for re-configuring 
 *          cell or UE-specific configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfReCfgInfo
(
CtfReCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfReCfgInfo(param, mBuf)
CtfReCfgInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfReCfgInfo)

      switch(param->cfgElem) {
         case CTF_UE_CFG:
            CMCHKPK(cmPkCtfDedRecfgInfo, &param->u.dedRecfg, mBuf);
            break;
         case CTF_CELL_CFG:
            CMCHKPK(cmPkCtfCellRecfgInfo, &param->u.cellRecfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->cfgElem, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfReCfgInfo
*
*
*     Desc:   Re-configuration Information
 * @details This structure contains the information for re-configuring 
 *          cell or UE-specific configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfReCfgInfo
(
CtfReCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfReCfgInfo(param, mBuf)
CtfReCfgInfo *param;
Buffer *mBuf;
#endif
{
   
   TRC3(cmUnpkCtfReCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->cfgElem, mBuf);
      switch(param->cfgElem) {
         case CTF_CELL_CFG:
            CMCHKUNPK(cmUnpkCtfCellRecfgInfo, &param->u.cellRecfg, mBuf);
            break;
         case CTF_UE_CFG:
            CMCHKUNPK(cmUnpkCtfDedRecfgInfo, &param->u.dedRecfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfReleaseInfo
*
*
*     Desc:   Release configuration Information
 * @details This structure contains the information for releasing 
 *          cell or UE-specific configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfReleaseInfo
(
CtfReleaseInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfReleaseInfo(param, mBuf)
CtfReleaseInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfReleaseInfo)

      switch(param->cfgElem) {
         case CTF_UE_CFG:
            CMCHKPK(cmPkCtfDedReleaseInfo, &param->u.dedRel, mBuf);
            break;
         case CTF_CELL_CFG:
            CMCHKPK(cmPkCtfCellReleaseInfo, &param->u.cellRel, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->cfgElem, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmUnpkCtfReleaseInfo
*
*
*     Desc:   Release configuration Information
 * @details This structure contains the information for releasing 
 *          cell or UE-specific configuration at PHY.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfReleaseInfo
(
CtfReleaseInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfReleaseInfo(param, mBuf)
CtfReleaseInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkCtfReleaseInfo)

   CMCHKUNPK(SUnpkU8, &param->cfgElem, mBuf);
      switch(param->cfgElem) {
         case CTF_CELL_CFG:
            CMCHKUNPK(cmUnpkCtfCellReleaseInfo, &param->u.cellRel, mBuf);
            break;
         case CTF_UE_CFG:
            CMCHKUNPK(cmUnpkCtfDedReleaseInfo, &param->u.dedRel, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func: cmPkCtfCfgReqInfo
*
*
*     Desc:   Configuration Request information
 * @details This is the main structure in the Configuration request primitive.
 *    -# This structure contains the configuration information as given by 
 *       the RRC to configure PHY layer for common/dedicated resources.
 *    -# It can contain Config/Reconfig/Release.
 *    -# The result of configuration is indicated in TfUiCtfCfgCfm.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkCtfCfgReqInfo
(
CtfCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCtfCfgReqInfo(param, mBuf)
CtfCfgReqInfo *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkCtfCfgReqInfo)

   /* ctf_c_001.main_4: Added support for vendor specific parameters */
#ifdef CTF_VER3
   CMCHKPK(cmPkCtfVendorSpecParams, &param->vendorParams, mBuf);
#endif    
      switch(param->cfgType) {
         case CTF_DELETE:
            CMCHKPK(cmPkCtfReleaseInfo, &param->u.release, mBuf);
            break;
         case CTF_RECONFIG:
            CMCHKPK(cmPkCtfReCfgInfo, &param->u.reCfg, mBuf);
            break;
         case CTF_CONFIG:
            CMCHKPK(cmPkCtfCfgInfo, &param->u.cfg, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }
   CMCHKPK(SPkU8, param->cfgType, mBuf);
   RETVALUE(ROK);
}



   /* ctf_c_001.main_4: Modified cmUnpkCtfCfgReqInfo() to add support
    * for vendor specific parameters */
/***********************************************************
*
*     Func: cmUnpkCtfCfgReqInfo
*
*
*     Desc:   Configuration Request information
 * @details This is the main structure in the Configuration request primitive.
 *    -# This structure contains the configuration information as given by 
 *       the RRC to configure PHY layer for common/dedicated resources.
 *    -# It can contain Config/Reconfig/Release.
 *    -# The result of configuration is indicated in TfUiCtfCfgCfm.
*
*
*     Ret: S16
*
*     Notes:
*
*     File: 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkCtfCfgReqInfo
(
Pst  *pst,
CtfCfgReqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkCtfCfgReqInfo(param, mBuf)
Pst  *pst;
CtfCfgReqInfo *param;
Buffer *mBuf;
#endif
{

#ifdef CTF_VER3
   S16 retVal;
#endif

   TRC3(cmUnpkCtfCfgReqInfo)
   CMCHKUNPK(SUnpkU8, &param->cfgType, mBuf);
      switch(param->cfgType) {
         case CTF_CONFIG:
            CMCHKUNPK(cmUnpkCtfCfgInfo, &param->u.cfg, mBuf);
            break;
         case CTF_RECONFIG:
            CMCHKUNPK(cmUnpkCtfReCfgInfo, &param->u.reCfg, mBuf);
            break;
         case CTF_DELETE:
            CMCHKUNPK(cmUnpkCtfReleaseInfo, &param->u.release, mBuf);
            break;
         default :
            RETVALUE(RFAILED);
      }  
#ifdef CTF_VER3
    if((retVal = cmUnpkCtfVendorSpecParams(pst, &param->vendorParams, mBuf)) != ROK)
        RETVALUE(retVal);
#endif
   RETVALUE(ROK);
}
#endif


/********************************************************************30**

         End of file:     ctf.c@@/main/5 - Thu Feb 16 20:18:30 2012

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vkulkarni       1. Initial Release.
/main/2      ---      chebli          1. (ctf_c_001.main_1) Added pack/unpack support
                                         for newly added members in CtfDedRecfgInfo.
                                      2. Added presence check while packing/unpacking. 
/main/3      ---      ctf_c_001.main_2 mpatel   1. Updated for Release of 3.1. added packing and
                                         unpacking for cqiMask, PmiRiRpt      
/main/4      ---      ctf_c_001.main_3 pmacharla     1. CtfUeTxAntMode is 32bit
                                           quantity, un/pack corrected to 32bit
                          ms            2. Compilation warning fix with g++
                          mnawas        3. Added pack/unpack for newly added variables
                                           in Cfg and ReCfg structures
/main/5      ---      ctf_c_001.main_4 ragrawal 1. Added pack/unpack for new fields introduced
                                                   in CtfDedPucchCfgInfo structure  
                                                2. Added support for vendor specific parameters.
                                                3. ReEst Fix.
*********************************************************************91*/
