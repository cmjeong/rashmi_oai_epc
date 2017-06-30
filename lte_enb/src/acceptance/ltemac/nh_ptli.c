

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      nh_ptli.c@@/main/2 - Sat Jul 30 02:22:22 2011
  
     Prg:      ps
  
**********************************************************************/

/** @file rg_dhm.c
@brief APIs related to Downlink HARQ.
*/

#include "rgac_acc.x"

/* Solaris g++ compilation */
/* added the  ifdef __cplusplus to solve the anachronism */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if !(defined(LCNHLICRG)  && defined(RG) && defined(LWLCNHLICRG))
#define PTNHLICRG
#endif


/* MAX Number of Service Providers of NH */
#define NH_MAX_CRG_PROV   3

#ifdef PTNHLICRG
/** @brief Request from RRC to MAC to bind the interface saps */
EXTERN S16 PtLiCrgBndReq ARGS((Pst* pst, SuId suId, SpId spId));
/** @brief Request from RRC to MAC to Unbind the interface saps */
EXTERN S16 PtLiCrgUbndReq ARGS((Pst* pst, SpId spId, Reason reason));
/** @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lc */
EXTERN S16 PtLiCrgCfgReq ARGS((Pst* pst, SpId spId, CrgCfgTransId transId, CrgCfgReqInfo  * cfgReqInfo));
#endif /*--#ifdef PTNHLICRG--*/

/** @brief Request from RRC to MAC to bind the interface saps */
PRIVATE CONSTANT CrgBndReq NhLiCrgBndReqMt[NH_MAX_CRG_PROV] =
{
#ifdef LCNHLICRG
   cmPkCrgBndReq,
#else
   PtLiCrgBndReq,
#endif
#ifdef RG
   RgUiCrgBndReq,
#else
   PtLiCrgBndReq,
#endif
#ifdef LWLCNHLICRG
   cmPkCrgBndReq
#else
   PtLiCrgBndReq
#endif
};

/** @brief Request from RRC to MAC to Unbind the interface saps */
PRIVATE CONSTANT CrgUbndReq NhLiCrgUbndReqMt[NH_MAX_CRG_PROV] =
{
#ifdef LCNHLICRG
   cmPkCrgUbndReq,
#else
   PtLiCrgUbndReq,
#endif
#ifdef RG
   RgUiCrgUbndReq,
#else
   PtLiCrgUbndReq,
#endif
#ifdef LWLCNHLICRG
   cmPkCrgUbndReq
#else
   PtLiCrgUbndReq
#endif
};

/** @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lc */
PRIVATE CONSTANT CrgCfgReq NhLiCrgCfgReqMt[NH_MAX_CRG_PROV] =
{
#ifdef LCNHLICRG
   cmPkCrgCfgReq,
#else
   PtLiCrgCfgReq,
#endif
#ifdef RG
   RgUiCrgCfgReq,
#else
   PtLiCrgCfgReq,
#endif
#ifdef LWLCNHLICRG
   cmPkCrgCfgReq
#else
   PtLiCrgCfgReq
#endif
};

#ifdef __cplusplus
}
#endif /* __cplusplus */
#ifdef NH



/**
* @brief Request from RRC to MAC to bind the interface saps
*
* @details
*
*     Function : NhLiCrgBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 NhLiCrgBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 NhLiCrgBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(NhLiCrgBndReq);

   (*NhLiCrgBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);

}



/**
* @brief Request from RRC to MAC to Unbind the interface saps
*
* @details
*
*     Function : NhLiCrgUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 NhLiCrgUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 NhLiCrgUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(NhLiCrgUbndReq);

   (*NhLiCrgUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);

}



/**
* @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lc
*
* @details
*
*     Function : NhLiCrgCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CrgCfgTransId  transId
*  @param[in]   CrgCfgReqInfo  *  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 NhLiCrgCfgReq
(
Pst* pst,
SpId spId,
CrgCfgTransId transId,
CrgCfgReqInfo  * cfgReqInfo
)
#else
PUBLIC S16 NhLiCrgCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
CrgCfgTransId transId;
CrgCfgReqInfo  * cfgReqInfo;
#endif
{

   TRC3(NhLiCrgCfgReq);

   (*NhLiCrgCfgReqMt[pst->selector])(pst, spId, transId, cfgReqInfo);

   RETVALUE(ROK);

}

#endif /*--ifdef NH--*/

#ifdef PTNHLICRG



/**
* @brief Request from RRC to MAC to bind the interface saps
*
* @details
*
*     Function : PtLiCrgBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiCrgBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 PtLiCrgBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(PtLiCrgBndReq);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(ROK);

}



/**
* @brief Request from RRC to MAC to Unbind the interface saps
*
* @details
*
*     Function : PtLiCrgUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiCrgUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 PtLiCrgUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(PtLiCrgUbndReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(reason);

   RETVALUE(ROK);

}



/**
* @brief Configuration Request from RRC to MAC for 
 * configuring Cell/Ue/Lc
*
* @details
*
*     Function : PtLiCrgCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   CrgCfgTransId  transId
*  @param[in]   CrgCfgReqInfo  *  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiCrgCfgReq
(
Pst* pst,
SpId spId,
CrgCfgTransId transId,
CrgCfgReqInfo  * cfgReqInfo
)
#else
PUBLIC S16 PtLiCrgCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
CrgCfgTransId transId;
CrgCfgReqInfo  * cfgReqInfo;
#endif
{

   TRC3(PtLiCrgCfgReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(transId);
   UNUSED(cfgReqInfo);

   RETVALUE(ROK);

}


#endif /*--ifdef PTNHLICRG--*/



/**********************************************************************
 
         End of file:     nh_ptli.c@@/main/2 - Sat Jul 30 02:22:22 2011
 
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
/main/2      ---     gj              1. LTE MAC 3.1 Release.
*********************************************************************91*/
