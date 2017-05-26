
/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_ui.c
  
     Sid:      yw_ui.c@@/main/2 - Thu Dec  2 02:27:27 2010
  
     Prg:      pk
  
**********************************************************************/

/** @file ys_ui.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management defines for LTE-CL */
#include "tfu.h"
#include "ys_pal.h"            /* defines and macros for CL */
#include <sys/time.h>
#include "ys_pal_err.h"        /* YS error defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"
#include "ys_pal.x"            /* typedefs for CL */
#include "ss_diag.h"        /* Common log file */
PRIVATE S16 ysCtfDelCellCfg ARGS((
CtfCellReleaseInfo *cellRel
));

PRIVATE S16 ysUiChkAndGetTfuSap ARGS((
SpId       spId,
YsTfuSapType type,
YsTfuSapCb **tfuSapCb
));
/* CL Control Block Structure */
PUBLIC YsCb ysCb;

/**
 * @brief Handler for Bind request from RRC towards CL.
 *
 * @details
 *
 *     Function : YsUiCtfBndReq
 *     
 *     This function handles the bind request from RRC.
 *     
 *           
 *  @param[in]  Pst  *pst
 *  @param[in]  SuId suId
 *  @param[in]  SpId spId
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 YsUiCtfBndReq
(
Pst  *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 YsUiCtfBndReq(pst, suId, spId)
Pst  *pst;
SuId suId;
SpId spId;
#endif
{
   Pst       retPst;
   S16       ret;

   TRC2(YsUiCtfBndReq)

   YS_DBG_INFO((_ysp, "YsUiCtfBndReq(): suId = %d; spId = %d;\n", suId, spId));
   ret = ROK;

   cmMemcpy((U8 *)&retPst, (U8 *)pst, sizeof(Pst));
   retPst.dstProcId = pst->srcProcId;
   retPst.dstEnt    = pst->srcEnt;
   retPst.dstInst   = pst->srcInst;
   retPst.srcProcId = pst->dstProcId;
   retPst.srcEnt    = pst->dstEnt;
   retPst.srcInst   = pst->dstInst;

   if(spId == ysCb.ctfSap.spId)
   {
      /* Check the state of the SAP */
      switch (ysCb.ctfSap.sapState)
      {
         case LYS_NOT_CFG: /* SAP Not configured */
            YS_DBG_INFO((_ysp, "SAP Not Configured\n"));
            ret = YsUiCtfBndCfm(&retPst, suId, CM_BND_NOK);
            break;
         
         case LYS_UNBND: /* SAP is not bound */
            YS_DBG_INFO((_ysp, "SAP Not yet bound\n"));
            ysCb.ctfSap.sapState = LYS_BND;
            ysCb.ctfSap.suId = suId;
            ysCb.ctfSap.sapPst.dstProcId = pst->srcProcId;
            ysCb.ctfSap.sapPst.dstEnt    = pst->srcEnt;
            ysCb.ctfSap.sapPst.dstInst   = pst->srcInst;
            /* Send Bind Confirm with status as SUCCESS */
            ret = YsUiCtfBndCfm(&ysCb.ctfSap.sapPst, suId, CM_BND_OK);
            break;
            
         case LYS_BND: /* SAP is already bound*/
            YS_DBG_INFO((_ysp, "SAP already bound\n"));
            ret = YsUiCtfBndCfm(&ysCb.ctfSap.sapPst, suId, CM_BND_OK);
            break;
         default: /* Should Never Enter here */
#if (ERRCLASS & ERRCLS_INT_PAR)      
            YS_LOGERR_INTPAR(EYST001, (ErrVal)ysCb.ctfSap.sapState,
                  "Invalid SAP State:YsUiCtfBndReq failed\n");
#endif
            ret = YsUiCtfBndCfm(&retPst, suId, CM_BND_NOK);
            break;
      }
   }
   else
   {
#if (ERRCLASS & ERRCLS_INT_PAR)      
      YS_LOGERR_INTPAR(EYST002, (ErrVal)ysCb.ctfSap.spId,
            "Invalid SAP Id:YsUiCtfBndReq failed\n");
#endif
      ret = YsUiCtfBndCfm(&retPst, suId, CM_BND_NOK);
   }
   RETVALUE(ret);
}  /* YsUiCtfBndReq */

/**
 * @brief API for unbind request from RRC towards CL. 
 *
 * @details
 *
 *     Function: YsUiCtfUbndReq
 *     
 *     This API is invoked by RRC towards CL to unbind CTF SAP. 
 *     These API validates the Pst, spId, suId and transfers the unbind request
 *     specific information to corresponding ownership module (GOM) API.
 *
 *           
 *  @param[in]  Pst    *pst
 *  @param[in]  SuId   suId
 *  @param[in]  Reason reason
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 YsUiCtfUbndReq
(
Pst    *pst,
SpId   spId,
Reason reason
)
#else
PUBLIC S16 YsUiCtfUbndReq(pst, spId, reason)
Pst    *pst; 
SpId   spId;
Reason reason;
#endif
{
   TRC2(YsUiCtfUbndReq)
   
   YS_DBG_INFO((_ysp, "YsUiCtfUbndReq: spId = %d; reason = %d \n", spId, reason));

   /* SAP Id validation */
   if(spId == ysCb.ctfSap.spId)
   {
      switch (ysCb.ctfSap.sapState)
      {
         case LYS_BND: /* SAP is already bound*/
            /* setting SAP state to UN BOUND */
            YS_DBG_INFO((_ysp, "SAP Is Bound\n"));
            ysCb.ctfSap.sapState = LYS_UNBND;
            break;
         default:
#if (ERRCLASS & ERRCLS_INT_PAR)      
            YS_LOGERR_INTPAR(EYST003, (ErrVal)ysCb.ctfSap.sapState,
                  "Invalid SAP State: YsUiCtfUbndReq failed\n");
#endif
            RETVALUE(RFAILED);
      }
   }
   else
   {
#if (ERRCLASS & ERRCLS_INT_PAR)      
      YS_LOGERR_INTPAR(EYST004, (ErrVal)ysCb.ctfSap.spId,
            "Invalid SAP Id:YsUiCtfUbndReq failed\n");
#endif
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}  /* YsUiCtfUbndReq */

/* ys005.102: Modified YsUiCtfCfgReq() CTF related changes  */
/** 
 * @brief Configuration Request from RRC.
 *
 *     Function: YsUiCtfCfgReq
 *
 * @details This primitive is used by RRC for the following at PHY:
 *          - Configure Cell related parameters.
 *          - Reconfigure cell related parameters.
 *          - Release a cell context.
 *          - Configure UE specific information.
 *          - Reconfigure UE specific information.
 *          - Release UE specific configuration.
 * The cell specific configuration is identified using a cell identifier.
 * The UE specific configuration is identified using a cell identifier and 
 * UE identifier.
 * The configuration request primitive is assocated with a transaction 
 * identifier to correlate the configuration confirm returned by PHY.
 *
 * @param[in] pst Pointer to the service user task configuration structure.
 * @param[in] spId The service provider SAP ID.
 * @param[in] transId The transaction identifier.
 * @param[in] cfgReqInfo Pointer to the PHY(Cell/UE) configuration information.
 *
 * @return S16
 *  -# ROK
 *  -# RFAILED
 *
*/
#ifdef ANSI
PUBLIC S16 YsUiCtfCfgReq
(
Pst*                 pst,
SpId                 spId,
CtfCfgTransId        transId,
CtfCfgReqInfo*       cfgReqInfo
)
#else
PUBLIC S16 YsUiCtfCfgReq(pst, spId, transId, cfgReqInfo) 
Pst*                 pst;
SpId                 spId;
CtfCfgTransId        transId;
CtfCfgReqInfo*       cfgReqInfo;
#endif
{
   S16       ret;
   YsCtfSapCb  *ctfSapCb;
   YsCellCb  *cellCb;

   TRC2(YsUiCtfCfgReq)
   
   YS_DBG_INFO((_ysp, "YsUiCtfCfgReq(): spId = %d; transId = %s;\n", 
                     spId, transId.trans));

   
   ret = ROK;

   if(ysUiChkAndGetCtfSap(spId, &ctfSapCb) != ROK) 
   {
      YsUiCtfCfgCfm(&ysCb.ctfSap.sapPst, ysCb.ctfSap.suId,
                     transId, CTF_CFG_CFM_NOK);
#ifdef CTF_VER3
      if( cfgReqInfo->vendorParams.paramBuffer != NULLP )
      {
         SPutSBuf (pst->region, pst->pool, (Data *)&cfgReqInfo->vendorParams.paramBuffer,
               cfgReqInfo->vendorParams.buffLen) ;
      }
#endif

      SPutSBuf (pst->region, pst->pool, (Data *)cfgReqInfo,
         sizeof(CtfCfgReqInfo));
      RETVALUE(RFAILED);
   }

#ifdef YS_PICO
#else /* YS_PICO */
   switch(cfgReqInfo->cfgType)
   {
      case CTF_DELETE:
         {
            switch(cfgReqInfo->u.release.cfgElem)
            {
               case CTF_CELL_CFG:
                  ret = ysCtfDelCellCfg(&cfgReqInfo->u.release.u.cellRel);
                  break;
               case CTF_UE_CFG:
                  break;
               default :
                  /* Do nothing */
                  break;
            }
            break;
         }
      case CTF_CONFIG:
         {
            /*ys004.102:Cell Delete Fix CRID:ccpu00117556*/
            cellCb = &ysCb.cellCb;
#ifdef TIP_LOWER_L2
            cmMemcpy((U8*)&cellCb->cellCfg, (U8*)&cfgReqInfo->u.cfg.u.cellCfg, sizeof(CtfCellCfgInfo));
#else
	    main7(&cfgReqInfo->u.cfg.u.cellCfg);
            cellCb->phyState = LYS_PHY_STATE_RUN;
            ysCb.ttiReady = TRUE;
#endif
            break;       
         }  
      case CTF_RECONFIG:
            switch(cfgReqInfo->u.reCfg.cfgElem)
            {
               /* Starts - Fix for CR ccpu00123185 */
               case CTF_TX_PWR_CFG:
                  /* Code to be added as part of MSPD 1.8 integration */
                  printf("\n Received CTF_TX_PWR_CFG for RefSigPwr=%d\n\n", cfgReqInfo->u.reCfg.u.cellRecfg.pdschCfg.refSigPwr);
                  break;
               /* Ends - Fix for CR ccpu00123185 */
            }
      default:
         /* Do nothing */
         break;
   }



   YsUiCtfCfgCfm(&ysCb.ctfSap.sapPst, ysCb.ctfSap.suId,
                 transId, CTF_CFG_CFM_OK);


#endif /* YS_PICO */

#ifdef CTF_VER3
      if( cfgReqInfo->vendorParams.paramBuffer != NULLP )
      {
         SPutSBuf (pst->region, pst->pool, (Data *)cfgReqInfo->vendorParams.paramBuffer,
               cfgReqInfo->vendorParams.buffLen) ;
      }
#endif
   SPutSBuf (pst->region, pst->pool, (Data *)cfgReqInfo,
         sizeof(CtfCfgReqInfo));

   RETVALUE(ret);
}  /* YsUiCtfCfgReq */

/* ys005.102: Modified ysCtfAddCellCfg() CTF related changes */

/**
 * @brief API for handle delete cell configuration request from RRM
 *
 * @details
 *
 *     Function: ysCtfDelCellCfg
 *     
 *     This API for handle delete cell configuration request from RRM
 *           
 *  @param[in]
 *  @param[in]
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 ysCtfDelCellCfg
(
CtfCellReleaseInfo  *cellRel
)
#else
PRIVATE S16 ysCtfDelCellCfg(cellRel)
   CtfCellReleaseInfo  *cellRel;
#endif
{
/*ys004.102:Cell Delete Fix CRID:ccpu00117556*/   
#ifdef YS_LTE_PAL
   YsCellCb  *cellCb;
#endif


   TRC2(ysCtfDelCellCfg)

      YS_DBG_PARAM((_ysp, "ysCtfDelCellCfg(): cellId = %d \n", cellRel->cellId));

#if (ERRCLASS & ERRCLS_INT_PAR)      
   if(cellRel->cellId >= YS_NUM_LOG_CELLS)
   {
      YS_LOGERR_INTPAR(EYST014, (ErrVal)cellRel->cellId,
            "Invalid cellId: ysCtfDelCellCfg failed\n");
      RETVALUE(RFAILED);
   }
#endif
   /*ys004.102:Cell Delete Fix CRID:ccpu00117556*/
#ifdef YS_LTE_PAL
   /*TTI ready flag is disabled*/
   ysCb.ttiReady = FALSE;
   /*Updating the PHY State to Idle*/
   cellCb = &ysCb.cellCb;
   cellCb->phyState = LYS_PHY_STATE_IDLE;
#endif

      RETVALUE(ROK);
}  /* ysCtfDelCellCfg*/

/*
 *
 *       Fun:   ysUiChkAndGetCtfSap
 *
 *       Desc:  This function checks SAP state and returns 
 *              sapCb if present
 *
 *       Ret:   ROK     - success
 *              RFAILED - failure
 *
 *       Notes: None 
 *
 *       File:  ys_uim.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 ysUiChkAndGetCtfSap 
(
SpId       spId,
YsCtfSapCb **ctfSapCb
)
#else
PUBLIC S16 ysUiChkAndGetCtfSap(spId, ctfSapCb)
SpId       spId;
YsCtfSapCb **ctfSapCb;
#endif
{
#if (ERRCLASS & ERRCLS_INT_PAR)
#endif

   TRC3(ysUiChkAndGetCtfSap);

   *ctfSapCb = NULLP;

#if (ERRCLASS & ERRCLS_INT_PAR)
   if(spId == ysCb.ctfSap.spId)
   {
      switch(ysCb.ctfSap.sapState)
      {
         case LYS_BND: /* SAP is already bound */
            YS_DBG_INFO((_ysp, "SAP Is already Bound\n"));
            break;
         default: /* Should never reach here */
            YS_LOGERR_INTPAR(EYST034, (ErrVal)ysCb.ctfSap.sapState,
                  "Invalid SAP State: ysUiChkAndGetCtfSap failed\n");
            RETVALUE(RFAILED);
      }
      
      *ctfSapCb = &ysCb.ctfSap;
   }
   else
   {
      YS_LOGERR_INTPAR(EYST035, (ErrVal)spId,
            "Invalid SAP Id:ysUiChkAndGetCtfSap failed\n");
      RETVALUE(RFAILED);
   }
#else
   *ctfSapCb = &ysCb.ctfSap;
#endif
   RETVALUE(ROK);
} /* ysUiChkAndGetCtfSap */

/**
 * @brief Handler for Bind request.
 *
 * @details
 *
 *     Function : YsUiTfuBndReq
 *     
 *     This function handles the bind request from MAC Service User.
 *     
 *           
 *  @param[in]  Pst  *pst
 *  @param[in]  SuId suId
 *  @param[in]  SpId spId
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 YsUiTfuBndReq
(
Pst  *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 YsUiTfuBndReq(pst, suId, spId)
Pst  *pst;
SuId suId;
SpId spId;
#endif
{
   S16         ret;
   YsTfuSapCb  *tfuSap;
   Pst         retPst;

   TRC2(YsUiTfuBndReq)
   
   ret = ROK;

   YS_DBG_INFO((_ysp, "YsUiTfuBndReq(): suId = %d; spId = %d;\n", suId, spId));

   cmMemcpy((U8 *)&retPst, (U8 *)pst, sizeof(Pst));
   retPst.dstProcId = pst->srcProcId;
   retPst.dstEnt    = pst->srcEnt;
   retPst.dstInst   = pst->srcInst;
   retPst.srcProcId = pst->dstProcId;
   retPst.srcEnt    = pst->dstEnt;
   retPst.srcInst   = pst->dstInst;




#ifdef YS_LTE_PAL
   tfuSap = &(ysCb.tfuSap);

   if (spId != tfuSap->spId)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)      
      YS_LOGERR_INTPAR(EYST039, (ErrVal)spId,
            "Invalid SAP Id:YsUiTfuBndReq failed\n");
#endif
      YsUiTfuBndCfm(&retPst, suId, CM_BND_NOK);
      RETVALUE(RFAILED);
   }
#endif /* YS_LTE_PAL */
   /* Check the state of the SAP */
   switch (tfuSap->sapState)
   {
      case LYS_NOT_CFG: /* SAP Not configured */
         YS_DBG_INFO((_ysp, "SAP Not Configured\n"));
         ret = YsUiTfuBndCfm(&retPst, suId, CM_BND_NOK);
         break;

      case LYS_UNBND: /* SAP is not bound */
         YS_DBG_INFO((_ysp, "SAP Not yet bound\n"));
         tfuSap->suId          = suId;
         tfuSap->sapPst.dstProcId = pst->srcProcId;
         tfuSap->sapPst.dstEnt    = pst->srcEnt;
         tfuSap->sapPst.dstInst   = pst->srcInst;


         tfuSap->sapState = LYS_BND;
         /* Send Bind Confirm with status as SUCCESS */
         ret = YsUiTfuBndCfm(&tfuSap->sapPst, suId, CM_BND_OK);
         break;

      case LYS_BND: /* SAP is already bound*/
         YS_DBG_INFO((_ysp, "SAP already bound\n"));
         ret = YsUiTfuBndCfm(&tfuSap->sapPst, suId, CM_BND_OK);
         break;

      default: /* Should Never Enter here */
#if (ERRCLASS & ERRCLS_INT_PAR)      
         YS_LOGERR_INTPAR(EYST040, (ErrVal)tfuSap->sapState,
               "Invalid SAP State:YsUiTfuBndReq failed\n");
#endif
         ret = YsUiTfuBndCfm(&retPst, suId, CM_BND_NOK);
         break;
   }
   
   RETVALUE(ret);
}  /* YsUiTfuBndReq */

/**
 * @brief API for unbind request from MAC towards CL. 
 *
 * @details
 *
 *     Function: YsUiTfuUbndReq
 *     
 *     This API is invoked by MAC towards CL to unbind TFU SAP. 
 *     These API validates the Pst, spId, suId and transfers the unbind request
 *     specific information to corresponding ownership module (GOM) API.
 *
 *           
 *  @param[in]  Pst    *pst
 *  @param[in]  SuId   suId
 *  @param[in]  Reason reason
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 YsUiTfuUbndReq
(
Pst    *pst,
SpId   spId,
Reason reason
)
#else
PUBLIC S16 YsUiTfuUbndReq(pst, spId, reason)
Pst    *pst; 
SpId   spId;
Reason reason;
#endif
{
   YsTfuSapCb  *tfuSapCb;

   TRC2(YsUiTfuUbndReq)
   
   YS_DBG_INFO((_ysp, "YsUiTfuUbndReq: spId = %d; reason = %d \n", spId, reason));

   if(ysUiChkAndGetTfuSap(spId, LYS_TFU_USR_SAP, &tfuSapCb) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   tfuSapCb->sapState = LYS_UNBND;

   RETVALUE(ROK);
}  /* YsUiTfuUbndReq */

/**
 * @brief Handler for TFU sap Bind request.
 *
 * @details
 *
 *     Function : YsUiTfuSchBndReq
 *     
 *     This function handles the bind request from Scheduler. 
 *     
 *           
 *  @param[in]  Pst  *pst
 *  @param[in]  SuId suId
 *  @param[in]  SpId spId
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 YsUiTfuSchBndReq
(
Pst  *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 YsUiTfuSchBndReq(pst, suId, spId)
Pst  *pst;
SuId suId;
SpId spId;
#endif
{
   S16         ret;
   YsTfuSapCb  *schTfuSap;
   Pst         retPst;

   TRC2(YsUiTfuSchBndReq)
   
   ret = ROK;

   YS_DBG_INFO((_ysp, "YsUiTfuSchBndReq(): suId = %d; spId = %d;\n", suId, spId));

   cmMemcpy((U8 *)&retPst, (U8 *)pst, sizeof(Pst));
   retPst.dstProcId = pst->srcProcId;
   retPst.dstEnt    = pst->srcEnt;
   retPst.dstInst   = pst->srcInst;
   retPst.srcProcId = pst->dstProcId;
   retPst.srcEnt    = pst->dstEnt;
   retPst.srcInst   = pst->dstInst;



#ifdef YS_LTE_PAL
   schTfuSap = &(ysCb.schTfuSap);

   if (spId != schTfuSap->spId)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)      
      YS_LOGERR_INTPAR(EYST044, (ErrVal)spId,
            "Invalid SAP Id:YsUiTfuSchBndReq failed\n");
#endif
      YsUiTfuSchBndCfm(&retPst, suId, CM_BND_NOK);
      RETVALUE(RFAILED);
   }
#endif /* YS_LTE_PAL */

   /* Check the state of the SAP */
   switch (schTfuSap->sapState)
   {
      case LYS_NOT_CFG: /* SAP Not configured */
         YS_DBG_INFO((_ysp, "SAP Not Configured\n"));
         ret = YsUiTfuSchBndCfm(&retPst, suId, CM_BND_NOK);
         break;

      case LYS_UNBND: /* SAP is not bound */
         YS_DBG_INFO((_ysp, "SAP Not yet bound\n"));
         schTfuSap->suId             = suId;
         schTfuSap->sapPst.dstProcId = pst->srcProcId;
         schTfuSap->sapPst.dstEnt    = pst->srcEnt;
         schTfuSap->sapPst.dstInst   = pst->srcInst;

         schTfuSap->sapState = LYS_BND;
         /* Send Bind Confirm with status as SUCCESS */
         ret = YsUiTfuSchBndCfm(&schTfuSap->sapPst, suId, CM_BND_OK);
         break;

      case LYS_BND: /* SAP is already bound*/
         YS_DBG_INFO((_ysp, "SAP already bound\n"));
         ret = YsUiTfuSchBndCfm(&schTfuSap->sapPst, suId, CM_BND_OK);
         break;

      default: /* Should Never Enter here */
#if (ERRCLASS & ERRCLS_INT_PAR)      
         YS_LOGERR_INTPAR(EYST045, (ErrVal)schTfuSap->sapState,
               "Invalid SAP State:YsUiTfuSchBndReq failed\n");
#endif
         ret = YsUiTfuSchBndCfm(&retPst, suId, CM_BND_NOK);
         break;
   }
   
   RETVALUE(ret);
}  /* YsUiTfuSchBndReq */

/**
 * @brief API for unbind request from MAC towards CL. 
 *
 * @details
 *
 *     Function: YsUiTfuSchUbndReq
 *     
 *     This API is invoked by MAC towards CL to unbind TFU SAP. 
 *     These API validates the Pst, spId, suId and transfers the unbind request
 *     specific information to corresponding ownership module (GOM) API.
 *
 *           
 *  @param[in]  Pst    *pst
 *  @param[in]  SuId   suId
 *  @param[in]  Reason reason
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 YsUiTfuSchUbndReq
(
Pst    *pst,
SpId   spId,
Reason reason
)
#else
PUBLIC S16 YsUiTfuSchUbndReq(pst, spId, reason)
Pst    *pst; 
SpId   spId;
Reason reason;
#endif
{
   YsTfuSapCb  *tfuSapCb;

   TRC2(YsUiTfuSchUbndReq)
   
   YS_DBG_INFO((_ysp, "YsUiTfuSchUbndReq: spId = %d; reason = %d \n", spId, reason));

   if(ysUiChkAndGetTfuSap(spId, LYS_TFU_SCH_SAP, &tfuSapCb) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   tfuSapCb->sapState = LYS_UNBND;

   RETVALUE(ROK);
}  /* YsUiTfuSchUbndReq */

/**
 * @brief API for sending control information MAC to PHY
 *
 * @details
 *
 *     Function: YsUiTfuCntrlReq
 *     
 *     This API is invoked to send control information from MAC to RLC.
 *     It provides PHY with all the control information
 *       - PDCCH
 *       - PHICH
 *       - PCFICH
 *           
 *  @param[in]  pst
 *  @param[in]  spId
 *  @param[in]  cntrlReq pointer to TfuCntrlReqInfo
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 YsUiTfuCntrlReq
(
Pst             *pst,
SpId            spId,
TfuCntrlReqInfo *cntrlReq
)
#else
PUBLIC S16 YsUiTfuCntrlReq(pst, spId, cntrlReq)
Pst             *pst;
SpId            spId;
TfuCntrlReqInfo *cntrlReq;
#endif
{
   S16             ret;
   YsCellCb        *cellCb;

#ifndef NO_ERRCLS
   YsTfuSapCb      *tfuSapCb; 
#endif
   
   TRC2(YsUiTfuCntrlReq)
   
   
   YS_DBG_PARAM((_ysp, "YsUiTfuCntrlReq(): spId = %d;\n", spId));

   /* Removing sap and cell condition for data performance path */
#ifndef NO_ERRCLS 
   ret = ROK;
   if(ysUiChkAndGetTfuSap(spId, LYS_TFU_SCH_SAP, &tfuSapCb) != ROK) 
   {
      YS_FREE_SDU(cntrlReq);
      RETVALUE(RFAILED);
   }
#endif

   if((cellCb = ysUtlGetCellCfg(cntrlReq->cellId)) == NULLP) 
   {
      YS_DBG_ERR((_ysp, "ysUtlGetCellCfg Failed \n"));
      YS_FREE_SDU(cntrlReq);
      RETVALUE(RFAILED);
   }

   /* Removing sap and cell condition for data performance path */
#ifndef NO_ERRCLS
   if(cellCb->phyState != LYS_PHY_STATE_RUN)
   {
      YS_DBG_ERR((_ysp, "PHY is not in running state \n"));
      YS_FREE_SDU(cntrlReq);
      RETVALUE(RFAILED);
   }
   tfuSapCb->tfuSts.numCntrlReqRcvd++;
#endif


#ifdef YS_LTE_PAL   
   ret = ysPalPrcCntrlReq(cellCb, cntrlReq);  
#endif /* YS_LTE_PAL */


   if(ret != ROK)
   {
      YS_DBG_ERR((_ysp, "CntrlReq processing Failed \n"));
      YS_FREE_SDU(cntrlReq);
      RETVALUE(RFAILED);
   }

   RETVALUE(ret);
}  /* YsUiTfuCntrlReq*/

/**
 * @brief This Primitive carries the Data PDUs from MAC to PHY for transmission
 *
 * @details
 *
 *     Function: YsUiTfuDatReq
 *     
 * @details The data being sent in this primitive is meant to be transmitted on
 * the downlink channel PDSCH and PBCH (if present). To facilitate physical
 * layer processing, requisite control information is also sent along with the
 * data. 
 *           
 *  @param[in]  pst
 *  @param[in]  spId
 *  @param[in]  tfuDatReq pointer to TfuDatReqInfo
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 YsUiTfuDatReq
(
Pst             *pst,
SpId            spId,
TfuDatReqInfo   *datReq
)
#else
PUBLIC S16 YsUiTfuDatReq(pst, spId, datReq)
Pst             *pst;
SpId            spId;
TfuDatReqInfo   *datReq;
#endif
{
   S16  ret;
   YsCellCb *cellCb;
   YsTfuSapCb *tfuSapCb;
   
   TRC2(YsUiTfuDatReq)
   
   ret = ROK;



   if(ysUiChkAndGetTfuSap(spId, LYS_TFU_USR_SAP, &tfuSapCb) != ROK) 
   {
      ysUtlFreeDatReq(datReq);
      RETVALUE(RFAILED);
   }

   if((cellCb = ysUtlGetCellCfg(datReq->cellId)) == NULLP) 
   {
      YS_DBG_ERR((_ysp, "ysUtlGetCellCfg Failed \n"));
      ysUtlFreeDatReq(datReq);
      RETVALUE(RFAILED);
   }

   if(cellCb->phyState != LYS_PHY_STATE_RUN)
   {
      YS_DBG_ERR((_ysp, "PHY is not in running state \n"));
      ysUtlFreeDatReq(datReq);
      RETVALUE(RFAILED);
   }

   tfuSapCb->tfuSts.numDatReqRcvd++;


/* ys005.102 : wireshark changes */
#ifdef YS_WIRESHARK_LOG
    U8 cnt = 0;
    TfuDatReqPduInfo *temp = NULLP;
    if (datReq->pdus.count > 0)
    {
       temp = (TfuDatReqPduInfo *)datReq->pdus.first->node;
       if ((temp->rnti != 0xFFFE) && (temp->rnti != 0xFFFF))
       {
          for(cnt = 0; cnt < temp->nmbOfTBs; cnt++)
          {
             if (NULLP != temp->mBuf[cnt])
            {
                U32 duplexMode = cellCb->cellCfg.txCfg.duplexMode;
                
                if(temp->rnti >= 1 && temp->rnti <= 60)
                {

                   ysTrillWiresharkMsg(temp->mBuf[cnt], duplexMode, DIRECTION_DOWNLINK, RA_RNTI,
                      temp->rnti, 0, datReq->timingInfo.subframe, 0, 0, 1); 
                }
                else
                { 
                   ysTrillWiresharkMsg(temp->mBuf[cnt], duplexMode, DIRECTION_DOWNLINK, C_RNTI,
                      temp->rnti, 0, datReq->timingInfo.subframe, 0, 0, 1); 
                }
             }
          }
       }
    }
#endif



#ifdef YS_LTE_PAL   
   ret = ysPalPrcDatReq(cellCb, datReq);  
#endif /* YS_LTE_PAL */


   if(ret != ROK)
   {
      YS_DBG_ERR((_ysp, "Failed to process Data Request\n"));
      ysUtlFreeDatReq(datReq);
      RETVALUE(RFAILED);
   }

   RETVALUE(ret);
}  /* YsUiTfuDatReq*/

/**
 * @brief brief This primitive is sent from Scheduler to PHY.
 *
 * @details
 *
 *     Function: YsUiTfuRecpReq
 *     
 * @details This primitive provides PHY with all the information required by 
 * PHY to decode transmissions from the UE on either PUCCH or PUSCH.
 * -# On PUCCH UE can transmit the following
 *    -# SR
 *    -# HARQ feedback
 *    -# CQI report
 *    -# HARQ + CQI
 *    -# HARQ + SR
 * -# On PUSCH UE can transmit the following
 *    -# Data
 *    -# Data + CQI
 *    -# Data + HARQ Feedback
 * This primitive carries all the information for the expected subframe for all
 * the UEs that have been scheduled to transmit.
 *           
 *  @param[in]  pst
 *  @param[in]  spId
 *  @param[in]  recpReq Pointer to the TfuRecpReqInfo structure.
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 YsUiTfuRecpReq
(
Pst             *pst,
SpId            spId,
TfuRecpReqInfo  *recpReq
)
#else
PUBLIC S16 YsUiTfuRecpReq(pst, spId, recpReq)
Pst             *pst;
SpId            spId;
TfuRecpReqInfo  *recpReq;
#endif
{
   S16  ret;
   YsCellCb *cellCb;
   YsTfuSapCb *tfuSapCb;
   
   TRC2(YsUiTfuRecpReq)
   
   ret = ROK;
   
   YS_DBG_PARAM((_ysp, "YsUiTfuRecpReq(): spId = %d;\n", spId));

   if(ysUiChkAndGetTfuSap(spId, LYS_TFU_SCH_SAP, &tfuSapCb) != ROK) 
   {
      YS_FREE_SDU(recpReq);
      RETVALUE(RFAILED);
   }

   if((cellCb = ysUtlGetCellCfg(recpReq->cellId)) == NULLP) 
   {
      YS_DBG_ERR((_ysp, "ysUtlGetCellCfg Failed \n"));
      YS_FREE_SDU(recpReq);
      RETVALUE(RFAILED);
   }

   if(cellCb->phyState != LYS_PHY_STATE_RUN)
   {
      YS_DBG_ERR((_ysp, "PHY is not in running state \n"));
      YS_FREE_SDU(recpReq);
      RETVALUE(RFAILED);
   }

   tfuSapCb->tfuSts.numRecpReqRcvd++;

#ifdef YS_LTE_PAL   
   ret = ysPalPrcRecpReq(cellCb, recpReq);  
#endif /* YS_LTE_PAL */


   if(ret != ROK)
   {
      YS_DBG_ERR((_ysp, "Failed to process Reception Request\n"));
      YS_FREE_SDU(recpReq);
      RETVALUE(RFAILED);
   }

   RETVALUE(ret);
}  /* YsUiTfuRecpReq*/

/*
 *
 *       Fun:   ysUiChkAndGetTfuSap
 *
 *       Desc:  This function checks SAP state and returns 
 *              sapCb if present
 *
 *       Ret:   ROK     - success
 *              RFAILED - failure
 *
 *       Notes: None 
 *
 *       File:  ys_uim.c
 *
 */
#ifdef YS_PICO
#else /* YS_PICO */

#ifdef ANSI
PRIVATE S16 ysUiChkAndGetTfuSap 
(
SpId       spId,
YsTfuSapType type,
YsTfuSapCb **tfuSapCb
)
#else
PRIVATE S16 ysUiChkAndGetTfuSap(spId, type, tfuSapCb)
SpId       spId;
YsTfuSapType type;
YsTfuSapCb **tfuSapCb;
#endif
{
   YsTfuSapCb  *sap = NULLP;

   TRC3(ysUiChkAndGetTfuSap);


   if (type == LYS_TFU_USR_SAP)
   {
      sap = &(ysCb.tfuSap);
   }
   else if (type == LYS_TFU_SCH_SAP)
   {
      sap = &(ysCb.schTfuSap);
   }

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (spId != sap->spId)
   {
      YS_LOGERR_INTPAR(EYST050, (ErrVal)spId,
            "Invalid SAP Id:ysUiChkAndGetTfuSap failed\n");
      RETVALUE(RFAILED);
   }

   switch (sap->sapState)
   {
      case LYS_BND: /* SAP is already bound */
         break;

      default: /* Should never reach here */
         YS_LOGERR_INTPAR(EYST051, (ErrVal)sap->sapState,
               "Invalid SAP State: YsUiTfuUbndReq failed\n");
         RETVALUE(RFAILED);
   }
#endif

   *tfuSapCb = sap;

   RETVALUE(ROK);
} /* ysUiChkAndGetTfuSap */
#endif /* YS_PICO */

#ifdef TIP_LOWER_L2
S16 tipStartCell(U16 cellId)
{
   printf("\n Cell Start\n");
   YsCellCb  *cellCb;
   cellCb = ysUtlGetCellCfg(cellId);
   if(NULLP == cellCb)
   {
      RETVALUE(RFAILED);
   }
   main7(&cellCb->cellCfg);
   cellCb->phyState = LYS_PHY_STATE_RUN;
   ysCb.ttiReady = TRUE;
   RETVALUE(ROK);
}
#endif
/********************************************************************30**
  
         End of file:     yw_ui.c@@/main/2 - Thu Dec  2 02:27:27 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm    1. eNodeB 1.2 release
/main/2    ys003.102 sgm    1. Fix for CID:1622-02-01 DefectId:ccpu00115333
/main/2              pkd    1. Fix for  DefectId:ccpu00117677
                                adding Cell delete feature for PAL.
/main/2    ys005.102 pbyadgi 1. Cell Delete Fix CRID:ccpu00117556
                             2. CellModification Change ccpu00118674
                             3. ccpu00117376: added support for CTF cell reconfiguration        
                             4. wireshark changes
                             5. CTF related changes.
*********************************************************************91*/
