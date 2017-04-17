
/********************************************************************20**

     Name:     RRM Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     rm_ptli.c

     Sid:      qf_ptli.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 18:22:35 2013

     Prg:     jbm 

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="RRM";
static int RLOG_FILE_ID=293;
static int RLOG_MODULE_ID=128;
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"
#include "cm_lte.h"        /* Common LTE Defines */
#include "rgm.h"           /* RGU Interface defines */
#include "rm_cmn.h"           /* RGU Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"
#include "cm_lte.x"        /* Common LTE Defines */
#include "rgm.x"           /* RGU Interface includes */

#include "rm_application.h"

#if !(defined(RGM_TC) && defined(RGM_INTF))
#define PTRMLIRGM
#endif


/* MAX Number of Service Providers of RM */
#define RM_MAX_RGM_PROV   3

#ifdef PTRMLIRGM
#if 1
/** @brief This API is used to send a Bind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
 */
EXTERN S16 PtLiRgmBndReq ARGS((Pst * pst, SuId suId, SpId spId));
/** @brief This API is used to send an Unbind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service provider.
 * @param reason Reason for Unbind request.
 * @return ROK/RFAILED
 */
EXTERN S16 PtLiRgmUbndReq ARGS((Pst * pst, SpId spId, Reason reason));

/** @brief This Primitive carries the Data PDUs from MAC to PHY for
  * transmission. 
  * @details The data being sent in this primitive is meant to be transmitted on
  * the downlink channel PDSCH and PBCH (if present). To facilitate physical
  * layer processing, requisite control information is also sent along with the
  * data. 
  * @sa TfUiRgmCntrlReq
  * @param pst 
  * @param spId
  * @param rgmDatReq pointer to RgmDatReqInfo
  * @return 
  */
EXTERN S16 PtLiRgmCfgPrbRprt ARGS((Pst * pst, SpId spId, RgmPrbRprtCfg *prbRprtCfg));
#endif /* #if 0 */
#endif /*--#ifdef PTRMLIRGM--*/

/** @brief This API is used to send a Bind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT RgmBndReq RmLiRgmBndReqMt[RM_MAX_RGM_PROV] =
{
#ifdef RGM_LC
   cmPkRgmBndReq,
#else
   PtLiRgmBndReq,
#endif
#ifdef RGM_LWLC
   cmPkLwLcRgmBndReq,
#else
   PtLiRgmBndReq,
#endif
#ifdef RGM_TC
   RgUiRgmBndReq
#else
   PtLiRgmBndReq
#endif
};
#if 1
/** @brief This API is used to send an Unbind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service provider.
 * @param reason Reason for Unbind request.
 * @return ROK/RFAILED
 */
PRIVATE CONSTANT RgmUbndReq RmLiRgmUbndReqMt[RM_MAX_RGM_PROV] =
{
#ifdef RGM_LC
   cmPkRgmUbndReq,
#else
   PtLiRgmUbndReq,
#endif
#ifdef RGM_LWLC 
   cmPkLwLcRgmUbndReq,
#else
   PtLiRgmUbndReq,
#endif
#ifdef RGM_TC
   RgUiRgmUbndReq
#else
   PtLiRgmUbndReq
#endif
};
#endif

/** @brief This Primitive carries the Data PDUs from MAC to PHY for
  * transmission. 
  * @details The data being sent in this primitive is to configure the 
  * the downlink channel PDSCH and PBCH (if present). To facilitate physical
  * layer processing, requisite control information is also sent along with the
  * data. 
  * @sa RgUiRgmCfgPrbRprt
  * @param pst 
  * @param spId
  * @param rgmDatReq pointer to RgmDatReqInfo
  * @return 
  */
PRIVATE CONSTANT RgmCfgPrbRprtFptr RmLiRgmCfgPrbRprtMt[RM_MAX_RGM_PROV] =
{
#ifdef RGM_LC
   cmPkRgmCfgPrbRprt,
#else
   PtLiRgmCfgPrbRprt,
#endif
#ifdef RGM_LWLC
   cmPkLwLcRgmCfgPrbRprt,
#else
   PtLiRgmCfgPrbRprt,
#endif
#ifdef RGM_TC
   RgUiRgmCfgPrbRprt
#else
   PtLiRgmCfgPrbRprt
#endif
};


#ifdef RM_INTF

EXTERN PUBLIC S16 tipLiRgmBndReq(Pst *pst, SuId   suId,   SpId   spId);


/***********************************************************
*
*     Func : RmLiRgmBndReq
*
*
*     Desc : This API is used to send a Bind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
PUBLIC S16 RmLiRgmBndReq
(
Pst * pst,
SuId suId,
SpId spId
)
{

   TRC3(RmLiRgmBndReq)
#ifdef TIP_L3_UL2_LL2_SPLIT
//   tipLiRgmBndReq(pst, suId, spId);
RmLiRgmBndCfm(pst, suId, CM_BND_OK);

#else
   RETVALUE((*RmLiRgmBndReqMt[pst->selector])(pst, suId, spId));
#endif

}

#if 1
/***********************************************************
*
*     Func : RmLiRgmUbndReq
*
*
*     Desc : This API is used to send an Unbind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service provider.
 * @param reason Reason for Unbind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
PUBLIC S16 RmLiRgmUbndReq
(
Pst * pst,
SpId spId,
Reason reason
)
{

   TRC3(RmLiRgmUbndReq)

   RETVALUE((*RmLiRgmUbndReqMt[pst->selector])(pst, spId, reason));

}

#endif



/***********************************************************
*
*     Func : RmLiRgmCfgPrbRprt
*
*
* Desc : This Primitive carries the PRB Report Configuration from RRM to MAC 
* @details: The data being sent in this primitive is meant to configure the 
*           MAC to start/stop the PRB usage Indications sent to RRM. 
* @sa RgUiRgmCfgPrbRprt
* @param pst 
* @param spId
* @param prbRprtCfg pointer to RgmPrbRprtCfg
* @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
PUBLIC S16 RmLiRgmCfgPrbRprt
(
Pst            *pst,
SuId           suId,
RgmPrbRprtCfg  *prbRprtCfg
)
{
   TRC3(RmLiRgmDatReq)

   RETVALUE((*RmLiRgmCfgPrbRprtMt[pst->selector])(pst, suId, prbRprtCfg));
}


PUBLIC S16 RmLiRgmPrbRprtInd
(
Pst                  *pst,
SpId                 spId,
RgmPrbRprtInd        *prbRprtInd
)
{
	g_rObjRRMApp.processMacMsg(pst->event, (U8*)prbRprtInd);

	RETVALUE(ROK);
}

PUBLIC S16 RmLiRgmBndCfm
(
   Pst*                 pst,
   SuId                 suId,
   U8                   status
)
{
   TRC3(RgLiRgmBndCfm);

   RETVALUE(rmLrmBndCfm (suId, status));
}

#endif /*--ifdef RM--*/


#ifdef PTRMLIRGM



/***********************************************************
*
*     Func : PtLiRgmBndReq
*
*
*     Desc : This API is used to send a Bind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
PUBLIC S16 PtLiRgmBndReq
(
Pst * pst,
SuId suId,
SpId spId
)
{

   TRC3(PtLiRgmBndReq)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(ROK);

}

/***********************************************************
*
*     Func : PtLiRgmUbndReq
*
*
*     Desc : This API is used to send an Unbind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service provider.
 * @param reason Reason for Unbind request.
 * @return ROK/RFAILED
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
PUBLIC S16 PtLiRgmUbndReq
(
Pst * pst,
SpId spId,
Reason reason
)
{

   TRC3(PtLiRgmUbndReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(reason);

   RETVALUE(ROK);

}

/***********************************************************
*
*     Func : PtLiRgmCfgPrbRprt
*
* Desc : This Primitive carries the PRB Report Configuration from RRM to MAC 
* @details: The data being sent in this primitive is meant to configure the 
*           MAC to start/stop the PRB usage Indications sent to RRM. 
* @sa RgUiRgmCfgPrbRprt
* @param pst 
* @param spId
* @param prbRprtCfg pointer to RgmPrbRprtCfg
* @return
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
PUBLIC S16 PtLiRgmCfgPrbRprt
(
Pst                  *pst,
SpId                 spId,
RgmPrbRprtCfg        *prbRprtCfg
)
{

   TRC3(PtLiRgmDatReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(prbRprtCfg);

   RETVALUE(ROK);

}
#endif /*--ifdef PTRMLIRGM--*/



/**
 * @brief This API is invoked to send RRM SAP bind request to PHY.
 *
 * @details
 *
 *     Function : rmLIMRgmBndReq
 *      
 *      This API is invoked to send RGM SAP bind request to PHY. It fills in 
 *      the Pst structure, spId and suId values and invokes bind request
 *      primitive at RGM.
 *           
 *  @param[in]  SuId            suId 
 *  @param[in]  SpId            spId
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
PUBLIC S16 rmLIMRgmBndReq
(
SuId    suId, 
SpId    spId
)
{
   S16         ret;
   RmLiSapCb   *rgmSap;

   TRC2(rmLIMRgmBndReq);

   /* Get the lower SAP control block from the layer control block. */
   rgmSap = &(g_stRmCb.rgmSap);

//   (Void)cmMemcpy ((U8*)&pst, (U8*)&(rgmSap->pst), sizeof(Pst));

   if((ret = RmLiRgmBndReq (&g_stRmCb.rgmSap.pst, suId, spId)) != ROK)
   {
      RLOG0(L_ERROR,"Sending RGM Bind Req Failed");
      /*
      RMDBGERR((rmPBuf,"rmLIMRgmBndReq() Call to RmLiRgmBndReq() failed\n"));
      MSPD_ERR("rmLIMRgmBndReq() Call to RmLiRgmBndReq() failed\n");
      */
   }
   RETVALUE(ret);
}  /* rmLIMRgmBndReq */


/**
 * @brief This API is invoked to send RGM SAP unbind request to PHY.
 *
 * @details
 *
 *     Function : rmLIMRgmBndReq
 *      
 *      This API is invoked to send RGM SAP unbind request to PHY. It fills in 
 *      the Pst structure and spId value and invokes unbind request
 *      primitive at RGM.
 *           
 *  @param[in]  SpId            spId
 *  @param[in]  Reason          reason 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
PUBLIC S16 rmLIMRgmUbndReq
(
SpId    spId, 
Reason  reason
)
{
   S16         ret;
   RmLiSapCb  *rgmSap;
   Pst         pst;

   TRC2(rmLIMRgmUbndReq);

   /* Get the lower SAP control block from the layer control block. */
   rgmSap = &(g_stRmCb.rgmSap);
   cmMemcpy ((U8*)&pst, (U8*)&(rgmSap->pst), sizeof(Pst));

   if((ret = RmLiRgmUbndReq (&pst, rgmSap->spId, reason)) != ROK)
   {
      /*
      RMDBGERR((rmPBuf,"rmLIMRgmUbndReq() Call to RmLiRgmUbndReq() failed\n"));
      MSPD_ERR("rmLIMRgmUbndReq() Call to RmLiRgmUbndReq() failed\n");
      */
   }
   RETVALUE(ret);

}  /* rmLIMRgmUbndReq */
PUBLIC S16 RmLiRgmTransModeInd 
(
Pst                  *pst,
SpId                 spId,
RgmTransModeInd      *transModeInd
)
{
	g_rObjRRMApp.processMacMsg(pst->event, (U8*)transModeInd);

	RETVALUE(ROK);
}

/********************************************************************30**

           End of file:     qf_ptli.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 18:22:35 2013

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
*********************************************************************91*/
