

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      rm_ptli.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 13:47:58 2013
  
     Prg:      ps
  
**********************************************************************/

/** @file rg_dhm.c
@brief APIs related to Downlink HARQ.
*/

#include "rgac_acc.x"
#include "rgm.x"
#include "rgm.h"


/* Solaris g++ compilation */
/* added the  ifdef __cplusplus to solve the anachronism */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#define RM_MAX_RGM_PROV   3



/** @brief Request from RRM to MAC to bind the interface saps */
EXTERN S16 PtLiRgmBndReq ARGS((Pst* pst, SuId suId, SpId spId));
/** @brief Request from RRM to MAC to Unbind the interface saps */
EXTERN S16 PtLiRgmUbndReq ARGS((Pst* pst, SpId spId, Reason reason));
EXTERN S16 PtLiRgmCfgPrbRprt ARGS((Pst* pst, SpId spId, RgmPrbRprtCfg   *prbRprtCfg));
/* rg004.201-ADD-Added for SI Enhancement*/
/** @brief SI Configuration Request from RRM to MAC */

/** @brief Request from RRM to MAC to bind the interface saps */
PRIVATE CONSTANT RgmBndReq RmLiRgmBndReqMt[RM_MAX_RGM_PROV] =
{
#ifdef RGM_LC
   cmPkRgmBndReq,
#else
   PtLiRgmBndReq,
#endif
#ifdef RG
   RgUiRgmBndReq,
#else
   PtLiRgmBndReq,
#endif
};

/** @brief Request from RRM to MAC to bind the interface saps */
PRIVATE CONSTANT RgmCfgPrbRprtFptr RmLiRgmCfgPrdReprtMt[RM_MAX_RGM_PROV] =
{
#ifdef RGM_LC
   cmPkRgmCfgPrbRprt,
#else
   PtLiRgmCfgPrbRprt,
#endif
#ifdef RG
   RgUiRgmCfgPrbRprt,
#else
   PtLiRgmCfgPrbRprt,
#endif
};


/** @brief Request from RRM to MAC to Unbind the interface saps */
PRIVATE CONSTANT RgmUbndReq RmLiRgmUbndReqMt[RM_MAX_RGM_PROV] =
{
#ifdef LCNXLIRGM
   cmPkRgmUbndReq,
#else
   PtLiRgmUbndReq,
#endif
#ifdef RG
   RgUiRgmUbndReq,
#else
   PtLiRgmUbndReq,
#endif
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef RM



/**
* @brief Request from RRM to MAC to bind the interface saps
*
* @details
*
*     Function : RmLiRgmBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 RmLiRgmBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 RmLiRgmBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(RmLiRgmBndReq);

   (*RmLiRgmBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);

}
/**
* @brief Request from RRM to MAC to bind the interface saps
*
* @details
*
*     Function : RmLiRgmCfgPrbRprt
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 RmLiRgmCfgPrbRprt
(
Pst* pst,
SpId spId,
RgmPrbRprtCfg   *prbRprtCfg
)
#else
PUBLIC S16 RmLiRgmCfgPrbRprt(pst, spId, prbRprtCfg)
Pst* pst;
SpId spId;
RgmPrbRprtCfg   *prbRprtCfg;
#endif
{

   TRC3(RmLiRgmCfgPrbRprt);

   (*RmLiRgmCfgPrdReprtMt[pst->selector])(pst, spId, prbRprtCfg);

   RETVALUE(ROK);

}



/**
* @brief Request from RRM to MAC to Unbind the interface saps
*
* @details
*
*     Function : RmLiRgmUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 RmLiRgmUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 RmLiRgmUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(RmLiRgmUbndReq);

   (*RmLiRgmUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);

}

#endif /*--ifdef NX--*/




/**
* @brief Request from RRM to MAC to bind the interface saps
*
* @details
*
*     Function : PtLiRgmBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRgmBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 PtLiRgmBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(PtLiRgmBndReq);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(ROK);

}
/**
* @brief Request from RRM to MAC to send the PRB reprot config
*
* @details
*
*     Function : PtLiRgmCfgPrbRprt
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRgmCfgPrbRprt
(
Pst* pst,
SpId spId,
RgmPrbRprtCfg   *prbRprtCfg
)
#else
PUBLIC S16 PtLiRgmCfgPrbRprt(pst, spId, prbRprtCfg)
Pst* pst;
SpId spId;
RgmPrbRprtCfg   *prbRprtCfg;
#endif
{

   TRC3(PtLiRgmBndReq);

   UNUSED(pst);
   UNUSED(prbRprtCfg);
   UNUSED(spId);

   RETVALUE(ROK);

}




/**
* @brief Request from RRM to MAC to Unbind the interface saps
*
* @details
*
*     Function : PtLiRgmUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRgmUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 PtLiRgmUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(PtLiRgmUbndReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(reason);

   RETVALUE(ROK);

}

/* rg004.201-ADD-Added for SI Enhancement*/




/**********************************************************************
 
         End of file:     rm_ptli.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 13:47:58 2013
 
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
/main/1      ---     sm              1. Initial Release.
             rg004.201  rnt          1. Modified for SI Enhancement
/main/2      ---     gj              1. LTE MAC 3.1 Release.
*********************************************************************91*/
