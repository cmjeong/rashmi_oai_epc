

/************************************************************************
 
     Name:     LTE-CL layer
  
     Type:     C source file
  
     Desc:     C source code for pack/unpack of LYS interface primitives. 
  
     File:     lys.c 
  
     Sid:      lys.c@@/main/3 - Tue Aug 30 18:10:39 2011
  
     Prg:      pk
  
**********************************************************************/

/** @file lys.c
@brief This file contains the packing/unpacking code for the LYS interface 
       primitives.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_lte.h"        /* Common LTE Defines */
#include "lys.h"           /* LRG Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE Defines */
#include "lys.x"           /* LRG Interface includes */


#ifdef LCLYS

/**
* @brief This API is used to send a 
Config Request from LM to CL.
*
* @details
*
*     Function : cmPkLysCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysCfgReq
(
Pst * pst,
YsMngmt * cfg
)
#else
PUBLIC S16 cmPkLysCfgReq(pst, cfg)
Pst * pst;
YsMngmt * cfg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cfg, EVTLYSCFGREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Config Request from LM to CL.
*
* @details
*
*     Function : cmUnpkLysCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysCfgReq
(
LysCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysCfgReq(func, pst, mBuf)
LysCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cfg;
   
   TRC3(cmUnpkLysCfgReq)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfg, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, cfg, EVTLYSCFGREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfg, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfg));
}


/**
* @brief This API is used to send a 
Config Cfm from CL to LM.
*
* @details
*
*     Function : cmPkLysCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysCfgCfm
(
Pst * pst,
YsMngmt * cfm
)
#else
PUBLIC S16 cmPkLysCfgCfm(pst, cfm)
Pst * pst;
YsMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cfm, EVTLYSCFGCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Config Cfm from CL to LM.
*
* @details
*
*     Function : cmUnpkLysCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysCfgCfm
(
LysCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysCfgCfm(func, pst, mBuf)
LysCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cfm;
   
   TRC3(cmUnpkLysCfgCfm)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfm, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, cfm, EVTLYSCFGCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/**
* @brief This API is used to send a 
Statistics Request from LM to CL.
*
* @details
*
*     Function : cmPkLysStsReq
*
*  @param[in]   Pst *  pst
*  @param[in]   Action  action
*  @param[in]   YsMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysStsReq
(
Pst * pst,
YsMngmt * sts
)
#else
PUBLIC S16 cmPkLysStsReq(pst, sts)
Pst * pst;
YsMngmt * sts;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysStsReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, sts, EVTLYSSTSREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSSTSREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Statistics Request from LM to CL.
*
* @details
*
*     Function : cmUnpkLysStsReq
*
*  @param[in]   Pst *  pst
*  @param[in]   Action  action
*  @param[in]   YsMngmt *  sts
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysStsReq
(
LysStsReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysStsReq(func, pst, mBuf)
LysStsReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *sts;
   
   TRC3(cmUnpkLysStsReq)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&sts, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, sts, EVTLYSSTSREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)sts, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, sts));
}


/**
* @brief This API is used to send a 
statistics Confirm from CL to LM.
*
* @details
*
*     Function : cmPkLysStsCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysStsCfm
(
Pst * pst,
YsMngmt * cfm
)
#else
PUBLIC S16 cmPkLysStsCfm(pst, cfm)
Pst * pst;
YsMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysStsCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cfm, EVTLYSSTSCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSSTSCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
statistics Confirm from CL to LM.
*
* @details
*
*     Function : cmUnpkLysStsCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysStsCfm
(
LysStsCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysStsCfm(func, pst, mBuf)
LysStsCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cfm;
   
   TRC3(cmUnpkLysStsCfm)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfm, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, cfm, EVTLYSSTSCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/**
* @brief This API is used to send a 
Status Request from LM to CL.
*
* @details
*
*     Function : cmPkLysStaReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysStaReq
(
Pst * pst,
YsMngmt * sta
)
#else
PUBLIC S16 cmPkLysStaReq(pst, sta)
Pst * pst;
YsMngmt * sta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysStaReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, sta, EVTLYSSSTAREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSSSTAREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Status Request from LM to CL.
*
* @details
*
*     Function : cmUnpkLysStaReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  sta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysStaReq
(
LysStaReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysStaReq(func, pst, mBuf)
LysStaReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *sta;
   
   TRC3(cmUnpkLysStaReq)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&sta, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)sta, 0, sizeof(YsMngmt));
   if (cmUnpkYsMngmt(pst, sta, EVTLYSSSTAREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)sta, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, sta));
}


/**
* @brief This API is used to send a 
status Confirm from CL to LM.
*
* @details
*
*     Function : cmPkLysStaCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysStaCfm
(
Pst * pst,
YsMngmt * cfm
)
#else
PUBLIC S16 cmPkLysStaCfm(pst, cfm)
Pst * pst;
YsMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysStaCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cfm, EVTLYSSSTACFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSSSTACFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
status Confirm from CL to LM.
*
* @details
*
*     Function : cmUnpkLysStaCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysStaCfm
(
LysStaCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysStaCfm(func, pst, mBuf)
LysStaCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cfm;
   
   TRC3(cmUnpkLysStaCfm)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfm, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   cmMemset((U8 *)cfm, 0, sizeof(YsMngmt));
   if (cmUnpkYsMngmt(pst, cfm, EVTLYSSSTACFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/**
* @brief This API is used to send a 
status Indication from CL to LM.
*
* @details
*
*     Function : cmPkLysStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysStaInd
(
Pst * pst,
YsMngmt * usta
)
#else
PUBLIC S16 cmPkLysStaInd(pst, usta)
Pst * pst;
YsMngmt * usta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, usta, EVTLYSUSTAIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSUSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
status Indication from CL to LM.
*
* @details
*
*     Function : cmUnpkLysStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysStaInd
(
LysStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysStaInd(func, pst, mBuf)
LysStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *usta;
   
   TRC3(cmUnpkLysStaInd)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&usta, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, usta, EVTLYSUSTAIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)usta, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, usta));
}


/**
* @brief This API is used to send a 
Control Request from LM to CL.
*
* @details
*
*     Function : cmPkLysCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysCntrlReq
(
Pst * pst,
YsMngmt * cntrl
)
#else
PUBLIC S16 cmPkLysCntrlReq(pst, cntrl)
Pst * pst;
YsMngmt * cntrl;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cntrl, EVTLYSCNTRLREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSCNTRLREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Control Request from LM to CL.
*
* @details
*
*     Function : cmUnpkLysCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cntrl
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysCntrlReq
(
LysCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysCntrlReq(func, pst, mBuf)
LysCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cntrl;
   
   TRC3(cmUnpkLysCntrlReq)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cntrl, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, cntrl, EVTLYSCNTRLREQ, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cntrl, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cntrl));
}


/**
* @brief This API is used to send a 
control Confirm from CL to LM.
*
* @details
*
*     Function : cmPkLysCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysCntrlCfm
(
Pst * pst,
YsMngmt * cfm
)
#else
PUBLIC S16 cmPkLysCntrlCfm(pst, cfm)
Pst * pst;
YsMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLysCntrlCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (cmPkYsMngmt(pst, cfm, EVTLYSCNTRLCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSCNTRLCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
control Confirm from CL to LM.
*
* @details
*
*     Function : cmUnpkLysCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysCntrlCfm
(
LysCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysCntrlCfm(func, pst, mBuf)
LysCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *cfm;
   
   TRC3(cmUnpkLysCntrlCfm)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&cfm, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, cfm, EVTLYSCNTRLCFM, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, cfm));
}


/**
* @brief This API is used to send a 
trace Indication from CL to LM.
*
* @details
*
*     Function : cmPkLysTrcInd
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  trc
*  @param[in]   Buffer *  trcBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLysTrcInd
(
Pst * pst,
YsMngmt * trc,
Buffer * trcBuf
)
#else
PUBLIC S16 cmPkLysTrcInd(pst, trc, trcBuf)
Pst * pst;
YsMngmt * trc;
Buffer * trcBuf;
#endif
{
   Buffer *mBuf = NULLP;
   S16 msgLen;
   TRC3(cmPkLysTrcInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   if (SFndLenMsg(trcBuf, &msgLen) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      RETVALUE(RFAILED);
   }
   if (SCatMsg(mBuf, trcBuf, M1M2) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      RETVALUE(RFAILED);
   }
   SPutMsg(trcBuf);
   CMCHKPK(SPkS16, msgLen, mBuf);

   if (cmPkYsMngmt(pst, trc, EVTLYSTRCIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(YsMngmt));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(YsMngmt)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"Packing failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event) EVTLYSTRCIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
trace Indication from CL to LM.
*
* @details
*
*     Function : cmUnpkLysTrcInd
*
*  @param[in]   Pst *  pst
*  @param[in]   YsMngmt *  trc
*  @param[in]   Buffer *  trcBuf
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLysTrcInd
(
LysTrcInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLysTrcInd(func, pst, mBuf)
LysTrcInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   YsMngmt *trc;
   Buffer *trcBuf;
   S16 msgLen, totalMsgLen;
   
   TRC3(cmUnpkLysTrcInd)

   if ((SGetSBuf(pst->region, pst->pool, (Data **)&trc, sizeof(YsMngmt))) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (cmUnpkYsMngmt(pst, trc, EVTLYSTRCIND, mBuf) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)trc, sizeof(YsMngmt));
      RETVALUE(RFAILED);
   }
   CMCHKUNPK(SUnpkS16, &msgLen, mBuf);
   if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      RETVALUE(RFAILED);
   }
   if (SSegMsg(mBuf, totalMsgLen-msgLen, &trcBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)      
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
          (Txt*)&__FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
          (ErrVal)ELYSXXX, (ErrVal)0,(Txt*)&"UnPacking failed");
#endif      
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, trc, trcBuf));
}


/***********************************************************
*
*     Func : cmPkYsGenCfg
*
*
*     Desc : ysGenCfg
   Structure holding configuration parameters for CL General Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsGenCfg
(
YsGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsGenCfg(param, mBuf)
YsGenCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsGenCfg);

   CMCHKPK(SPkU16, param->nmbUe, mBuf);
   CMCHKPK(SPkU16, param->maxTfuSaps, mBuf);
   CMCHKPK(cmPkPst, &param->lmPst, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsGenCfg
*
*
*     Desc : ysGenCfg
   Structure holding configuration parameters for CL General Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsGenCfg
(
YsGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsGenCfg(param, mBuf)
YsGenCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsGenCfg);

   CMCHKUNPK(cmUnpkPst, &param->lmPst, mBuf);
   CMCHKUNPK(SUnpkU16, &param->maxTfuSaps, mBuf);
   CMCHKUNPK(SUnpkU16, &param->nmbUe, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsTfuSapCfg
*
*
*     Desc : ysTfuSapCfg
   Structure holding configuration parameters for CL Upper SAP Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsTfuSapCfg
(
YsTfuSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsTfuSapCfg(param, mBuf)
YsTfuSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsTfuSapCfg);

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(SPkU32, param->type, mBuf);
   CMCHKPK(SPkS16, param->suId, mBuf);
   CMCHKPK(SPkS16, param->spId, mBuf);
   CMCHKPK(SPkU8, param->route, mBuf);
   CMCHKPK(SPkU8, param->inst, mBuf);
   CMCHKPK(SPkU8, param->ent, mBuf);
   CMCHKPK(SPkU16, param->procId, mBuf);
   CMCHKPK(SPkU8, param->prior, mBuf);
   CMCHKPK(cmPkMemoryId, &param->mem, mBuf);
   CMCHKPK(SPkU8, param->selector, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsTfuSapCfg
*
*
*     Desc : ysTfuSapCfg
   Structure holding configuration parameters for CL Upper SAP Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsTfuSapCfg
(
YsTfuSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsTfuSapCfg(param, mBuf)
YsTfuSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsTfuSapCfg);

   CMCHKUNPK(SUnpkU8, &param->selector, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &param->mem, mBuf);
   CMCHKUNPK(SUnpkU8, &param->prior, mBuf);
   CMCHKUNPK(SUnpkU16, &param->procId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ent, mBuf);
   CMCHKUNPK(SUnpkU8, &param->inst, mBuf);
   CMCHKUNPK(SUnpkU8, &param->route, mBuf);
   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->suId, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->type, mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &param->cellId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsCtfSapCfg
*
*
*     Desc : ysCtfSapCfg
   Structure holding configuration parameters for CL Upper SAP Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsCtfSapCfg
(
YsCtfSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsCtfSapCfg(param, mBuf)
YsCtfSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsCtfSapCfg);

   CMCHKPK(SPkS16, param->suId, mBuf);
   CMCHKPK(SPkS16, param->spId, mBuf);
   CMCHKPK(SPkU8, param->route, mBuf);
   CMCHKPK(SPkU8, param->inst, mBuf);
   CMCHKPK(SPkU8, param->ent, mBuf);
   CMCHKPK(SPkU16, param->procId, mBuf);
   CMCHKPK(SPkU8, param->prior, mBuf);
   CMCHKPK(cmPkMemoryId, &param->mem, mBuf);
   CMCHKPK(SPkU8, param->selector, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsCtfSapCfg
*
*
*     Desc : ysCtfSapCfg
   Structure holding configuration parameters for CL Upper SAP Configuration
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsCtfSapCfg
(
YsCtfSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsCtfSapCfg(param, mBuf)
YsCtfSapCfg *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsCtfSapCfg);

   CMCHKUNPK(SUnpkU8, &param->selector, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &param->mem, mBuf);
   CMCHKUNPK(SUnpkU8, &param->prior, mBuf);
   CMCHKUNPK(SUnpkU16, &param->procId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->ent, mBuf);
   CMCHKUNPK(SUnpkU8, &param->inst, mBuf);
   CMCHKUNPK(SUnpkU8, &param->route, mBuf);
   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->suId, mBuf);

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsCtfSapSts
*
*
*     Desc : ysCtfSapSts
   Structure holding CTF SAP statistical information of CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsCtfSapSts
(
YsCtfSapSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsCtfSapSts(param, mBuf)
YsCtfSapSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsCtfSapSts);

   CMCHKPK(SPkU16, param->numCellCfg, mBuf);
   CMCHKPK(SPkU32, param->numUeCfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsCtfSapSts
*
*
*     Desc : ysGenSts
   Structure holding General statistical information of CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsCtfSapSts
(
YsCtfSapSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsCtfSapSts(param, mBuf)
YsCtfSapSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsCtfSapSts);

   CMCHKUNPK(SUnpkU32, &param->numUeCfg, mBuf);
   CMCHKUNPK(SUnpkU16, &param->numCellCfg, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsTfuSapSts
*
*
*     Desc : ysTfuSapSts
   Structure holding statistical information of a SAP in CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsTfuSapSts
(
YsTfuSapSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsTfuSapSts(param, mBuf)
YsTfuSapSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsTfuSapSts);

   CMCHKPK(SPkU32, param->numRecpReqRcvd, mBuf);
   CMCHKPK(SPkU32, param->numDatReqRcvd, mBuf);
   CMCHKPK(SPkU32, param->numCntrlReqRcvd, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsTfuSapSts
*
*
*     Desc : ysTfuSapSts
   Structure holding statistical information of a SAP in CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsTfuSapSts
(
YsTfuSapSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsTfuSapSts(param, mBuf)
YsTfuSapSts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsTfuSapSts);

   CMCHKUNPK(SUnpkU32, &param->numCntrlReqRcvd, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numDatReqRcvd, mBuf);
   CMCHKUNPK(SUnpkU32, &param->numRecpReqRcvd, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsPhySts
*
*
*     Desc : ysPhySts
   Structure holding statistical information of a SAP in CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsPhySts
(
YsL1PhySts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsPhySts(param, mBuf)
YsL1PhySts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsPhySts);

   /* lys_c_001.main_1 */
#ifdef YS_MSPD
   CMCHKPK(cmPkStsCntr, param->numRxStatusInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxEndInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxSduInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxStartInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxStartCfm, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxStartReq, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxEndInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxSduCfm, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxSduReq, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxStartInd, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxStartCfm, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxStartReq, mBuf);
#else
   CMCHKPK(cmPkStsCntr, param->numSrsIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRachIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numRxIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numCrcIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numHarqIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numTxReqTx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numHiDciReqTx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numSfIndRx, mBuf);
   CMCHKPK(cmPkStsCntr, param->numSfReqTx, mBuf);
#endif   

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsPhySts
*
*
*     Desc : ysPhySts
   Structure holding statistical information of a SAP in CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsPhySts
(
YsL1PhySts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsPhySts(param, mBuf)
YsL1PhySts *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsPhySts);

   /* lys_c_001.main_1 */
#ifdef YS_MSPD
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxStartReq, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxStartCfm, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxStartInd, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxSduReq, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxSduCfm, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxEndInd, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxStartReq, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxStartCfm, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxStartInd, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxSduInd, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxEndInd, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxStatusInd, mBuf);
#else
   CMCHKUNPK(cmUnpkStsCntr, &param->numSfReqTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numSfIndRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numHiDciReqTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numTxReqTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numHarqIndRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numCrcIndRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRxIndRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numRachIndRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &param->numSrsIndRx, mBuf);
#endif

   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsCfg
*
*
*     Desc : ysCfg
   Structure holding configuration parameters for CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsCfg
(
YsCfg *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsCfg(param, elmnt, mBuf)
YsCfg *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsCfg);

   switch(elmnt) {
      case STCTFSAP:
         CMCHKPK(cmPkYsCtfSapCfg, &param->s.ctfSap, mBuf);
         break;
      case STTFUSAP:
         CMCHKPK(cmPkYsTfuSapCfg, &param->s.tfuSap, mBuf);
         break;
      case STGEN:
         CMCHKPK(cmPkYsGenCfg, &param->s.genCfg, mBuf);
         break;
      default :
         break;
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsCfg
*
*
*     Desc : ysCfg
   Structure holding configuration parameters for CL
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsCfg
(
YsCfg *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsCfg(param, elmnt, mBuf)
YsCfg *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsCfg);

   switch(elmnt) {
      case STGEN:
         CMCHKUNPK(cmUnpkYsGenCfg, &param->s.genCfg, mBuf);
         break;
      case STTFUSAP:
         CMCHKUNPK(cmUnpkYsTfuSapCfg, &param->s.tfuSap, mBuf);
         break;
      case STCTFSAP:
         CMCHKUNPK(cmUnpkYsCtfSapCfg, &param->s.ctfSap, mBuf);
         break;
      default :
         break;
   }
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsSapSta
*
*
*     Desc : ysSapSta
   Structure holding a SAP's status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsSapSta
(
YsSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsSapSta(param, mBuf)
YsSapSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsSapSta);

   CMCHKPK(SPkU8, param->sapState, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsSapSta
*
*
*     Desc : ysSapSta
   Structure holding a SAP's status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsSapSta
(
YsSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsSapSta(param, mBuf)
YsSapSta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsSapSta);

   CMCHKUNPK(SUnpkU8, &param->sapState, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsSts
*
*
*     Desc : ysSts
   Structure holding CL's statistical Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsSts
(
YsSts *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsSts(param, elmnt, mBuf)
YsSts *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsSts);

   switch(elmnt) {
      case STL1PHY:
         CMCHKPK(cmPkYsPhySts, &param->s.phySts, mBuf);
         break;
      case STTFUSAP:
         CMCHKPK(cmPkYsTfuSapSts, &param->s.tfuSts, mBuf);
         break;
      case STCTFSAP:
         CMCHKPK(cmPkYsCtfSapSts, &param->s.ctfSts, mBuf);
         break;
      default :
         break;
   }
   CMCHKPK(SPkS16, param->action, mBuf);
   CMCHKPK(SPkU8, param->sapInst, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsSts
*
*
*     Desc : ysSts
   Structure holding CL's statistical Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsSts
(
YsSts *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsSts(param, elmnt, mBuf)
YsSts *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsSts);

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->sapInst, mBuf);
   CMCHKUNPK(SUnpkS16, &param->action, mBuf);
   switch(elmnt) {
      case STCTFSAP:
         CMCHKUNPK(cmUnpkYsCtfSapSts, &param->s.ctfSts, mBuf);
         break;
      case STTFUSAP:
         CMCHKUNPK(cmUnpkYsTfuSapSts, &param->s.tfuSts, mBuf);
         break;
      case STL1PHY:
         CMCHKPK(cmUnpkYsPhySts, &param->s.phySts, mBuf);
         break;
      default :
         break;
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsSsta
*
*
*     Desc : ysSsta
   Structure holding CL's solicited status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsSsta
(
Pst *pst,
YsSsta *param,
S16 elmnt,
U8 eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsSsta(pst, param, elmnt,eventType, mBuf)
Pst *pst;
YsSsta *param;
S16 elmnt;
U8 eventType;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsSsta);

   switch(elmnt) {
      case STL1PHY:
         CMCHKPK(SPkU8, param->s.phyState,mBuf);
         break;
      case STCTFSAP:
         CMCHKPK(cmPkYsSapSta, &param->s.ctfSapSta, mBuf);
         break;
      case STTFUSAP:
         CMCHKPK(cmPkYsSapSta, &param->s.tfuSapSta, mBuf);
         break;
      case STGEN:
         /*lys_c_001.main_2 : ccpu00118324 system id packing/unpacking done on confirm event */
         if( eventType == EVTLYSSSTACFM)
         {
            CMCHKPK(cmPkSystemId, &param->s.sysId, mBuf);
            if (param->s.sysId.ptNmb != NULLP)
            {
               SPutSBuf(pst->region, pst->pool, (Data *)param->s.sysId.ptNmb, LYS_PT_NUM_SIZE);
            }
         }
         break;
      default :
         break;
   }
   CMCHKPK(SPkU8, param->sapInst, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsSsta
*
*
*     Desc : ysSsta
   Structure holding CL's solicited status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsSsta
(
Pst *pst,
YsSsta *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsSsta(pst, param, elmnt, mBuf)
Pst *pst;
YsSsta *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsSsta);

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->sapInst, mBuf);
   switch(elmnt) {
      case STGEN:
         /*lys_c_001.main_2 : ccpu00118324 system id packing/unpacking done on confirm event */
         if(pst->event == EVTLYSSSTACFM)
         {
            SGetSBuf(pst->region, pst->pool, (Data **)&param->s.sysId.ptNmb, LYS_PT_NUM_SIZE);
            cmMemset((U8 *)param->s.sysId.ptNmb, 0, LYS_PT_NUM_SIZE);
            /* lys_c_001.main_1 */
            CMCHKUNPK(cmUnpkSystemId, &param->s.sysId, mBuf);
         }
         break;
      case STTFUSAP:
         CMCHKUNPK(cmUnpkYsSapSta, &param->s.tfuSapSta, mBuf);
         break;
      case STCTFSAP:
         CMCHKUNPK(cmUnpkYsSapSta, &param->s.ctfSapSta, mBuf);
         break;
      case STL1PHY:
         CMCHKUNPK(SUnpkU8, &param->s.phyState, mBuf);
         break;
      default :
         break;
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsUstaDgn
*
*
*     Desc : ysUstaDgn 
   Alarm diagnostics structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsUstaDgn
(
YsUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsUstaDgn(param, mBuf)
YsUstaDgn *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsUstaDgn);

   switch(param->type) {
      case LYS_USTA_DGNVAL_SFN_SF:
         CMCHKPK(cmPkLteTimingInfo, &param->u.timingInfo, mBuf);
         break;
      case LYS_USTA_DGNVAL_SAP:
         CMCHKPK(SPkS16, param->u.sapId,mBuf);
         break;
      case LYS_USTA_DGNVAL_MEM:
         CMCHKPK(cmPkMemoryId, &param->u.mem, mBuf);
         break;
      default :
         break;
   }
   CMCHKPK(SPkU8, param->type, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsUstaDgn
*
*
*     Desc : ysUstaDgn 
   Alarm diagnostics structure
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsUstaDgn
(
YsUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsUstaDgn(param, mBuf)
YsUstaDgn *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsUstaDgn);

   CMCHKUNPK(SUnpkU8, &param->type, mBuf);
   switch(param->type) {
      case LYS_USTA_DGNVAL_MEM:
         CMCHKUNPK(cmUnpkMemoryId, &param->u.mem, mBuf);
         break;
      case LYS_USTA_DGNVAL_SAP:
         CMCHKUNPK(SUnpkS16, &param->u.sapId,mBuf);
         break;
      case LYS_USTA_DGNVAL_SFN_SF:
         CMCHKUNPK(cmUnpkLteTimingInfo, &param->u.timingInfo,mBuf);
         break;
      default :
         break;
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsUsta
*
*
*     Desc : ysUsta
   Structure holding CL's Unsolicited status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsUsta
(
YsUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsUsta(param, mBuf)
YsUsta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsUsta);

   CMCHKPK(cmPkYsUstaDgn, &param->dgn, mBuf);
   CMCHKPK(cmPkCmAlarm, &param->cmAlarm, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsUsta
*
*
*     Desc : ysUsta
   Structure holding CL's Unsolicited status information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsUsta
(
YsUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsUsta(param, mBuf)
YsUsta *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsUsta);

   CMCHKUNPK(cmUnpkCmAlarm, &param->cmAlarm, mBuf);
   CMCHKUNPK(cmUnpkYsUstaDgn, &param->dgn, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsTrc
*
*
*     Desc : ysTrc
   Structure holding CL's Trace Indication information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsTrc
(
YsTrc *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsTrc(param, mBuf)
YsTrc *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsTrc);

   CMCHKPK(SPkU8, param->evnt, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsTrc
*
*
*     Desc : ysTrc
   Structure holding CL's Trace Indication information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsTrc
(
YsTrc *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsTrc(param, mBuf)
YsTrc *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsTrc);

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->evnt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsDbgCntrl
*
*
*     Desc : ysDbgCntrl
   Structure holding CL's Debug Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsDbgCntrl
(
YsDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsDbgCntrl(param, mBuf)
YsDbgCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsDbgCntrl);

   CMCHKPK(SPkU32, param->dbgMask, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsDbgCntrl
*
*
*     Desc : ysDbgCntrl
   Structure holding CL's Debug Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsDbgCntrl
(
YsDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsDbgCntrl(param, mBuf)
YsDbgCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsDbgCntrl);

   CMCHKUNPK(SUnpkU32, &param->dbgMask, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmPkYsSapCntrl
*
*
*     Desc : ysSapCntrl
   Structure holding CL's SAP Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsSapCntrl
(
YsSapCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsSapCntrl(param, mBuf)
YsSapCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsSapCntrl);

   CMCHKPK(SPkS16, param->spId, mBuf);
   CMCHKPK(SPkS16, param->suId, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsSapCntrl
*
*
*     Desc : ysSapCntrl
   Structure holding CL's SAP Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsSapCntrl
(
YsSapCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsSapCntrl(param, mBuf)
YsSapCntrl *param;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsSapCntrl);

   CMCHKUNPK(SUnpkS16, &param->suId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->spId, mBuf);
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsCntrl
*
*
*     Desc : ysCntrl
   Structure holding CL's Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsCntrl
(
YsCntrl *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsCntrl(param, elmnt, mBuf)
YsCntrl *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsCntrl);

   switch(elmnt) {
      case STGEN:
         switch( param->subAction )
         {
            case SADBG :
               CMCHKPK(cmPkYsDbgCntrl, &param->s.ysDbgCntrl, mBuf);
               break;
            case SATRC:
               CMCHKPK(SPkS16, param->s.trcLen, mBuf);
               break;
            case SASTOPL1:
               CMCHKPK(cmPkLteCellId, param->s.cellId, mBuf);
               break;
            default:
               break;
         }
         break;
      case STTFUSAP:
      case STCTFSAP:
         switch(param->subAction)
         {
            default:
               CMCHKPK(cmPkYsSapCntrl, &param->s.ysSapCntrl, mBuf);
               break;
         }
      break;
      default :
         break;
   }
   CMCHKPK(SPkU8, param->subAction, mBuf);
   CMCHKPK(SPkU8, param->action, mBuf);
   CMCHKPK(cmPkDateTime, &param->dt, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsCntrl
*
*
*     Desc : ysCntrl
   Structure holding CL's Control information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsCntrl
(
YsCntrl *param,
S16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsCntrl(param, elmnt, mBuf)
YsCntrl *param;
S16 elmnt;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsCntrl);

   CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
   CMCHKUNPK(SUnpkU8, &param->action, mBuf);
   CMCHKUNPK(SUnpkU8, &param->subAction, mBuf);
   switch(elmnt)
   {
      case STGEN :
         switch( param->subAction )
         {
            case SADBG:
               CMCHKUNPK(cmUnpkYsDbgCntrl, &param->s.ysDbgCntrl,mBuf);
               break;
            case SATRC:
               CMCHKUNPK(SUnpkS16, &param->s.trcLen,mBuf);
               break;
            case SASTOPL1:
               CMCHKUNPK(cmUnpkLteCellId, &param->s.cellId, mBuf);
               break;
            default:
               break;
         }
         break;
      case STTFUSAP:
      case STCTFSAP:
         switch( param->subAction )
         {
            default:
               CMCHKUNPK(cmUnpkYsSapCntrl, &param->s.ysSapCntrl,mBuf);
               break;
         }
         break;
      default:
         break;
   }
   RETVALUE(ROK);
}


/***********************************************************
*
*     Func : cmPkYsMngmt
*
*
*     Desc : ysMngmt
   Structure holding CL's Configuration and Control Management Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkYsMngmt
(
Pst *pst,
YsMngmt *param,
U8 eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkYsMngmt(pst, param, eventType, mBuf)
Pst *pst;
YsMngmt *param;
U8 eventType;
Buffer *mBuf;
#endif
{

   TRC3(cmPkYsMngmt);

   switch(eventType) {
      case EVTLYSCNTRLREQ:
      case EVTLYSCNTRLCFM:
         if (cmPkYsCntrl(&param->t.cntrl, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSTRCIND:
         CMCHKPK(cmPkYsTrc, &param->t.trc, mBuf);
         break;
      case EVTLYSUSTAIND:
         CMCHKPK(cmPkYsUsta, &param->t.usta, mBuf);
         break;
      case EVTLYSSSTACFM:
      case EVTLYSSSTAREQ:
         /*lys_c_001.main_2 : ccpu00118324 system id packing/unpacking done on confirm event */
         if (cmPkYsSsta(pst, &param->t.ssta, param->hdr.elmId.elmnt,eventType, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSSTSCFM:
      case EVTLYSSTSREQ:
         if (cmPkYsSts(&param->t.sts, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSCFGREQ:
      case EVTLYSCFGCFM:
         if (cmPkYsCfg(&param->t.cfg, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      default :
         RETVALUE(RFAILED);
   }
   CMCHKPK(cmPkCmStatus, &param->cfm, mBuf);
   CMCHKPK(cmPkHeader, &param->hdr, mBuf);
   RETVALUE(ROK);
}



/***********************************************************
*
*     Func : cmUnpkYsMngmt
*
*
*     Desc : ysMngmt
   Structure holding CL's Configuration and Control Management Information
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkYsMngmt
(
Pst *pst,
YsMngmt *param,
U8 eventType,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkYsMngmt(pst, param, eventType, mBuf)
Pst *pst;
YsMngmt *param;
U8 eventType;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkYsMngmt);

   CMCHKUNPK(cmUnpkHeader, &param->hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &param->cfm, mBuf);
   switch(eventType) {
      case EVTLYSCFGREQ:
      case EVTLYSCFGCFM:
         if (cmUnpkYsCfg(&param->t.cfg, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSSTSCFM:
      case EVTLYSSTSREQ:
         if (cmUnpkYsSts(&param->t.sts, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSSSTACFM:
      case EVTLYSSSTAREQ:
         if (cmUnpkYsSsta(pst, &param->t.ssta, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      case EVTLYSUSTAIND:
         CMCHKUNPK(cmUnpkYsUsta, &param->t.usta, mBuf);
         break;
      case EVTLYSTRCIND:
         CMCHKUNPK(cmUnpkYsTrc, &param->t.trc, mBuf);
         break;
      case EVTLYSCNTRLREQ:
      case EVTLYSCNTRLCFM:
         if (cmUnpkYsCntrl(&param->t.cntrl, param->hdr.elmId.elmnt, mBuf) != ROK)
            RETVALUE(RFAILED);
         break;
      default :
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}
#endif

/**********************************************************************
 
         End of file:     lys.c@@/main/3 - Tue Aug 30 18:10:39 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     pk                1. Initial Release.
/main/2      ---      lys_c_001.main_1 apany      1. Minor fixes and additional PHY info
/main/3      ---      lys_c_001.main_2 ms           1. system id packing/unpacking done on confirm event.
*********************************************************************91*/
