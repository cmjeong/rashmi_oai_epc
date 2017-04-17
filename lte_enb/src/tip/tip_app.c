
/********************************************************************20**
 
     Name:     TIP PHY Interface
 
     Type:     C file
 
     Desc:     This file contains the packing/unpacking functions
               for control plane primitives on TIP PHY Open Interface.

     File:     tip_ctf.c

     Sid:      tip_ctf.c@@

     Prg:      Radisys
     
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm_lte.h"        /* Common LTE Defines              */
#include "lpj.h"        /* Common LTE Defines              */
#include "kwu.h"        /* Common LTE Defines              */
#include "crg.h"        /* Common LTE Defines              */
#include "rgm.h"        /* Common LTE Defines              */
#include "pju.h"        /* Common LTE Defines              */
#include "ctf.h"        /* Common LTE Defines              */
#include "ckw.h"        /* Common LTE Defines              */
//#include "wr_smm_init.h"        /* Common LTE Defines              */

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm_lib.x"        /* Common LTE library              */
#include "cm_lte.x"        /* Common LTE library              */
#include "lpj.x"        /* Common LTE library              */
#include "kwu.x"
#include "crg.x"
#include "ctf.x"
#include "pju.x"
#include "rgm.x"
#include "ckw.x"

#include "tip_cmn.h"

#include "tip.h"

#ifndef LTE_ENB_PAL
EXTERN S16 YsUiCtfBndReq ARGS(( Pst *pst, SuId suId, SpId spId));
#endif

/**
* @brief Configuration Request from RRC to PHY for 
 * cell or dedicated configuration.
*
* @details
*
*     Function: tipLL2MiLpjCntrlReq
*
*  @param[in]   Pst*  pst
*  @param[in]   cntrl PjMngmt
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipLL2MiLpjCntrlReq
(
Pst *ppst, 
PjMngmt *cntrl
)
#else
PUBLIC S16 tipLL2MiLpjCntrlReq(ppst, cntrl)
Pst *ppst;
PjMngmt *cntrl;
#endif
{
   SuId                      suId;
   SpId                      spId;
   Pst                       pst; 

   TRC3(tipLL2MiLpjCntrlReq);
#if 0
   pst->selector = SM_SELECTOR_LC;
   pst->dstProcId = SM_KW_UL_PROC;
   pst->dstEnt = ENTKW;
   pst->dstInst = WR_SM_KWUL_INST;
   pst->srcProcId = SM_PJ_PROC;
   pst->srcEnt = ENTPJ;
   pst->srcInst = WR_SM_PJUL_INST;
   pst->event = EVTNONE;

   suId = SM_ZERO_VAL;
   spId = 1;
   KwUiKwuBndReq(pst, suId, spId);

   pst->selector = SM_SELECTOR_LC;
   pst->dstProcId = SM_KW_PROC;
   pst->dstEnt = ENTKW;
   pst->dstInst = WR_SM_KWDL_INST;
   pst->srcProcId = SM_PJ_PROC;
   pst->srcEnt = ENTPJ;
   pst->srcInst = WR_SM_PJDL_INST;
   pst->event = EVTNONE;

   suId = SM_ZERO_VAL;
   spId = 1;
   KwUiKwuBndReq(pst, suId, spId);
#endif
   pst.intfVer = 0;
   pst.pool = 0;
   pst.prior = 0;
   pst.region = 0;
   pst.route = 0;

   pst.selector = 0;
   pst.dstProcId = 30;
   pst.dstEnt = ENTKW;
   pst.dstInst = 0;
   pst.srcProcId = 20;
   pst.srcEnt = ENTPJ;
   pst.srcInst = 0;
   pst.event = EVTNONE;

   suId = 0;
   spId = 1;
   KwUiKwuBndReq(&pst, suId, spId);

   pst.selector = 0;
   pst.dstProcId = 30;
   pst.dstEnt = ENTKW;
   pst.dstInst = 1;
   pst.srcProcId = 20;
   pst.srcEnt = ENTPJ;
   pst.srcInst = 1;
   pst.event = EVTNONE;

   suId = 0;
   spId = 1;
   KwUiKwuBndReq(&pst, suId, spId);

   pst.selector = 0;
   pst.dstProcId = 30;
   pst.dstEnt = ENTKW;
   pst.dstInst = 0;
   pst.srcProcId = 10;
   pst.srcEnt = ENTNH;
   pst.srcInst = 0;
   pst.event = EVTNONE;

   suId = 0;
   spId = 0;
 
   KwUiCkwBndReq (&pst, suId, spId);

   pst.selector = 0;
   pst.dstProcId = 30;
   pst.dstEnt = ENTRG;
   pst.dstInst = 0;
   pst.srcProcId = 10;
   pst.srcEnt = ENTNH;
   pst.srcInst = 0;
   pst.event = EVTNONE;

   suId = 0;
   spId = 0;
   
   RgUiCrgBndReq(&pst, suId, spId);
 
   pst.selector = 0;
   pst.dstProcId = 30;
   pst.dstEnt = ENTKW;
   pst.dstInst = 0;
   pst.srcProcId = 10;
   pst.srcEnt = ENTNH;
   pst.srcInst = 0;
   pst.event = EVTNONE;

   suId = 1;
   spId = 0;
   KwUiKwuBndReq(&pst, suId, spId);

   pst.selector = 0;
   pst.dstProcId = 30;
   pst.dstEnt = ENTKW;
   pst.dstInst = 1;
   pst.srcProcId = 10;
   pst.srcEnt = ENTNH;
   pst.srcInst = 1;
   pst.event = EVTNONE;

   suId = 0;
   spId = 0;
   KwUiKwuBndReq(&pst, suId, spId);

   pst.selector = 0;
   pst.dstProcId = 30;
   pst.dstEnt = ENTTF;
   pst.dstInst = 0;
   pst.srcProcId = 10;
   pst.srcEnt = ENTWR;
   pst.srcInst = 0;
   pst.event = EVTNONE;

   suId = 0;
   spId = 0;

#ifdef LTE_ENB_PAL
   TfUiCtfBndReq(&pst, suId, spId);
#else
   YsUiCtfBndReq(&pst, suId, spId);
#endif

   pst.selector = 0;
   pst.dstProcId = 30;
   pst.dstEnt = ENTRG;
   pst.dstInst = 2;
   pst.srcProcId = 10;
   pst.srcEnt = ENTWR;
   pst.srcInst = 0;
   pst.event = EVTNONE;

   suId = 0;
   spId = 0;
   RgUiRgrBndReq(&pst, suId, spId);
#ifdef TIP_LOWER_L2
   {
      tipBldSendInitInd(MAC_MOD_ID, MAC_INIT_IND); 
      tipBldSendInitInd(RLC_MOD_ID, RLC_INIT_IND); 
   }
#endif

   RETVALUE(ROK);
}


/**
* @brief Configuration Request from RRC to PHY for 
 * cell or dedicated configuration.
*
* @details
*
*     Function: tipUL2LiKwuBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   cntrl PjMngmt
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipUL2LiKwuBndReq  
(
Pst *ppst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 tipUL2LiKwuBndReq(ppst, suId, spId)
Pst *ppst;
SuId suId;
SpId spId
#endif
{
   Pst pst; 

   TRC3(tipUL2LiKwuBndReq);
#if 0
   pst->selector = SM_SELECTOR_LC;
   pst->dstProcId = SM_KW_UL_PROC;
   pst->dstEnt = ENTKW;
   pst->dstInst = WR_SM_KWUL_INST;
   pst->srcProcId = SM_PJ_PROC;
   pst->srcEnt = ENTPJ;
   pst->srcInst = WR_SM_PJUL_INST;
   pst->event = EVTNONE;

   suId = SM_ZERO_VAL;
   spId = 1;
   KwUiKwuBndReq(pst, suId, spId);

   pst->selector = SM_SELECTOR_LC;
   pst->dstProcId = SM_KW_PROC;
   pst->dstEnt = ENTKW;
   pst->dstInst = WR_SM_KWDL_INST;
   pst->srcProcId = SM_PJ_PROC;
   pst->srcEnt = ENTPJ;
   pst->srcInst = WR_SM_PJDL_INST;
   pst->event = EVTNONE;

   suId = SM_ZERO_VAL;
   spId = 1;
   KwUiKwuBndReq(pst, suId, spId);
#endif
   pst.selector = 0;
   pst.dstProcId = 20;
   pst.dstEnt = ENTPJ;
   pst.dstInst = 0;
   pst.srcProcId = 30;
   pst.srcEnt = ENTKW;
   pst.srcInst = 0;
   pst.event = EVTNONE;

   suId = 0;
   PjLiKwuBndCfm(&pst, suId, CM_BND_OK);

   pst.selector = 0;
   pst.dstProcId = 20;
   pst.dstEnt = ENTPJ;
   pst.dstInst = 1;
   pst.srcProcId = 30;
   pst.srcEnt = ENTKW;
   pst.srcInst = 1;
   pst.event = EVTNONE;

   suId = 0;
   PjLiKwuBndCfm(&pst, suId, CM_BND_OK);

   pst.selector = 0;
   pst.dstProcId = 20;
   pst.dstEnt = ENTPJ;
   pst.dstInst = 0;
   pst.srcProcId = 10;
   pst.srcEnt = ENTNH;
   pst.srcInst = 0;
   pst.event = EVTNONE;

   spId = 0;
   suId = 0;
   PjUiCpjBndReq (&pst, suId, spId);
   RETVALUE(ROK);
}
/**
* @brief Configuration Request from RRC to PHY for 
 * cell or dedicated configuration.
*
* @details
*
*     Function: tipUL2MiLnhCntrlReq
*
*  @param[in]   Pst*  pst
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipUL2MiLnhCntrlReq
(
Pst *ppst
)
#else
PUBLIC S16 tipUL2MiLnhCntrlReq(ppst)
Pst *ppst;
#endif
{
   SuId                      suId;
   SpId                      spId;
   Pst                       pst; 

   TRC3(tipUL2MiLnhCntrlReq);
#if 0
   pst->selector = SM_SELECTOR_LC;
   pst->dstProcId = SM_KW_UL_PROC;
   pst->dstEnt = ENTKW;
   pst->dstInst = WR_SM_KWUL_INST;
   pst->srcProcId = SM_PJ_PROC;
   pst->srcEnt = ENTPJ;
   pst->srcInst = WR_SM_PJUL_INST;
   pst->event = EVTNONE;

   suId = SM_ZERO_VAL;
   spId = 1;
   KwUiKwuBndReq(pst, suId, spId);

   pst->selector = SM_SELECTOR_LC;
   pst->dstProcId = SM_KW_PROC;
   pst->dstEnt = ENTKW;
   pst->dstInst = WR_SM_KWDL_INST;
   pst->srcProcId = SM_PJ_PROC;
   pst->srcEnt = ENTPJ;
   pst->srcInst = WR_SM_PJDL_INST;
   pst->event = EVTNONE;

   suId = SM_ZERO_VAL;
   spId = 1;
   KwUiKwuBndReq(pst, suId, spId);
   pst->selector = 0;
   pst->dstProcId = 20;
   pst->dstEnt = ENTKW;
   pst->dstInst = 0;
   pst->srcProcId = 10;
   pst->srcEnt = ENTNH;
   pst->srcInst = 0;
   pst->event = EVTNONE;

   suId = 0;
   spId = 0;
   KwUiCkwBndReq(pst, suId, spId);

#endif
   pst.selector = 0;
   pst.dstProcId = 20;
   pst.dstEnt = ENTPJ;
   pst.dstInst = 0;
   pst.srcProcId = 10;
   pst.srcEnt = ENTNH;
   pst.srcInst = 0;
   pst.event = EVTNONE;

   suId = 1;
   spId = 0;
   PjUiPjuBndReq(&pst,suId, spId);

   pst.selector = 0;
   pst.dstProcId = 20;
   pst.dstEnt = ENTPJ;
   pst.dstInst = 1;
   pst.srcProcId = 10;
   pst.srcEnt = ENTNH;
   pst.srcInst = 0;
   pst.event = EVTNONE;

   suId = 0;
   spId = 0;
   PjUiPjuBndReq(&pst,suId, spId);

   RETVALUE(ROK);
}
/**
* @brief Configuration Request from RRC to PHY for 
 * cell or dedicated configuration.
*
* @details
*
*     Function: tipLiRgmBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   cntrl PjMngmt
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 tipLiRgmBndReq
(
   Pst                       *pst, 
   SuId                      suId,
   SpId                      spId
)
#else
PUBLIC S16 tipLiRgmBndReq(pst, suId,spId)
   Pst                       *pst;
   SuId                      suId;
   SpId                      spId;
#endif
{

   TRC3(tipLiRgmBndReq);
   RmLiRgmBndCfm(pst, suId, CM_BND_OK);
#if 0
   pst->selector = SM_SELECTOR_LC;
   pst->dstProcId = SM_KW_UL_PROC;
   pst->dstEnt = ENTKW;
   pst->dstInst = WR_SM_KWUL_INST;
   pst->srcProcId = SM_PJ_PROC;
   pst->srcEnt = ENTPJ;
   pst->srcInst = WR_SM_PJUL_INST;
   pst->event = EVTNONE;

   suId = SM_ZERO_VAL;
   spId = 1;
   KwUiKwuBndReq(pst, suId, spId);

   pst->selector = SM_SELECTOR_LC;
   pst->dstProcId = SM_KW_PROC;
   pst->dstEnt = ENTKW;
   pst->dstInst = WR_SM_KWDL_INST;
   pst->srcProcId = SM_PJ_PROC;
   pst->srcEnt = ENTPJ;
   pst->srcInst = WR_SM_PJDL_INST;
   pst->event = EVTNONE;

   suId = SM_ZERO_VAL;
   spId = 1;
   KwUiKwuBndReq(pst, suId, spId);
   pst->selector = 0;
   pst->dstProcId = 20;
   pst->dstEnt = ENTKW;
   pst->dstInst = 0;
   pst->srcProcId = 10;
   pst->srcEnt = ENTNH;
   pst->srcInst = 0;
   pst->event = EVTNONE;

   suId = 0;
   spId = 0;
   KwUiCkwBndReq(pst, suId, spId);

#endif
   RETVALUE(ROK);
}


#if 0
/**
* @brief Configuration Request from RRC to MAC for 
 * cell or dedicated configuration.
*
* @details
*
*     Function: tipSendCrgCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   cntrl rgMngmt
*  @return   S16
*      -# ROK
**/
PUBLIC S16 tipSendCrgCfgReq
(
Pst *post,                       /* Post structure */
SpId spId,                      /* Service provider ID */
CrgCfgTransId transId,          /* cfg trans ID */
CrgCfgReqInfo *cmacCfg              /* MAC Configuration information */
)
{
}/*endif of tipSendCrgCfgReq*/

/**
* @brief Configuration Request from RRC to RLC for 
 * cell or dedicated configuration.
*
* @details
*
*     Function: tipSendCkwCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   cntrl rgMngmt
*  @return   S16
*      -# ROK
**/
PUBLIC S16 tipSendCkwCfgReq
(
Pst *post,                /* Post structure */
SpId spId,               /* Service provider */
CkwCfgInfo *cfgInfo
)
{
}/*endif of tipSendCkwCfgReq*/
#endif
