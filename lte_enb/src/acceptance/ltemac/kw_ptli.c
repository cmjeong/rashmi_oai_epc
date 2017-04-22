

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      kw_ptli.c@@/main/2 - Sat Jul 30 02:22:20 2011
  
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



#if !(defined(LCKWLIRGU)  && defined(RG) && defined(LWLCKWLIRGU))
#define PTKWLIRGU
#endif


/* MAX Number of Service Providers of KW */
#define KW_MAX_RGU_PROV   3

#ifdef PTKWLIRGU
/** @brief Request from RLC to MAC to bind the interface saps */
EXTERN S16 PtLiRguBndReq ARGS((Pst* pst, SuId suId, SpId spId));
/** @brief Request from RLC to MAC to Unbind the interface saps */
EXTERN S16 PtLiRguUbndReq ARGS((Pst* pst, SpId spId, Reason reason));
/** @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
EXTERN S16 PtLiRguCDatReq ARGS((Pst* pst, SpId spId, RguCDatReqInfo  * datReq));
/** @brief Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission */
EXTERN S16 PtLiRguDDatReq ARGS((Pst* pst, SpId spId, RguDDatReqInfo  * datReq));
/** @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for common channels*/
EXTERN S16 PtLiRguCStaRsp ARGS((Pst* pst, SpId spId, RguCStaRspInfo  * staRsp));
/** @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for dedicated channels*/
EXTERN S16 PtLiRguDStaRsp ARGS((Pst* pst, SpId spId, RguDStaRspInfo  * staRsp));
#ifdef LTE_L2_MEAS
#ifdef LTEMAC_R9
/** @brief Primitive invoked from RLC to MAC to 
 *  * inform the On/Off Status of LC Id*/
EXTERN S16 PtLiRguL2MUlThrpMeasReq ARGS((Pst* pst, SpId spId, RguL2MUlThrpMeasReqInfo  *measReq));
#endif
#endif
#endif /*--#ifdef PTKWLIRGU--*/

/** @brief Request from RLC to MAC to bind the interface saps */
PRIVATE CONSTANT RguBndReq KwLiRguBndReqMt[KW_MAX_RGU_PROV] =
{
#ifdef LCKWLIRGU
   cmPkRguBndReq,
#else
   PtLiRguBndReq,
#endif
#ifdef RG
   RgUiRguBndReq,
#else
   PtLiRguBndReq,
#endif
#ifdef LWLCKWLIRGU
   cmPkRguBndReq
#else
   PtLiRguBndReq
#endif
};

/** @brief Request from RLC to MAC to Unbind the interface saps */
PRIVATE CONSTANT RguUbndReq KwLiRguUbndReqMt[KW_MAX_RGU_PROV] =
{
#ifdef LCKWLIRGU
   cmPkRguUbndReq,
#else
   PtLiRguUbndReq,
#endif
#ifdef RG
   RgUiRguUbndReq,
#else
   PtLiRguUbndReq,
#endif
#ifdef LWLCKWLIRGU
   cmPkRguUbndReq
#else
   PtLiRguUbndReq
#endif
};

/** @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
PRIVATE CONSTANT RguCDatReq KwLiRguCDatReqMt[KW_MAX_RGU_PROV] =
{
#ifdef LCKWLIRGU
   cmPkRguCDatReq,
#else
   PtLiRguCDatReq,
#endif
#ifdef RG
   RgUiRguCDatReq,
#else
   PtLiRguCDatReq,
#endif
#ifdef LWLCKWLIRGU
   cmPkRguCDatReq
#else
   PtLiRguCDatReq
#endif
};

/** @brief Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission */
PRIVATE CONSTANT RguDDatReq KwLiRguDDatReqMt[KW_MAX_RGU_PROV] =
{
#ifdef LCKWLIRGU
   cmPkRguDDatReq,
#else
   PtLiRguDDatReq,
#endif
#ifdef RG
   RgUiRguDDatReq,
#else
   PtLiRguDDatReq,
#endif
#ifdef LWLCKWLIRGU
   cmPkRguDDatReq
#else
   PtLiRguDDatReq
#endif
};

/** @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for common channels*/
PRIVATE CONSTANT RguCStaRsp KwLiRguCStaRspMt[KW_MAX_RGU_PROV] =
{
#ifdef LCKWLIRGU
   cmPkRguCStaRsp,
#else
   PtLiRguCStaRsp,
#endif
#ifdef RG
   RgUiRguCStaRsp,
#else
   PtLiRguCStaRsp,
#endif
#ifdef LWLCKWLIRGU
   cmPkRguCStaRsp
#else
   PtLiRguCStaRsp
#endif
};

/** @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for dedicated channels*/
PRIVATE CONSTANT RguDStaRsp KwLiRguDStaRspMt[KW_MAX_RGU_PROV] =
{
#ifdef LCKWLIRGU
   cmPkRguDStaRsp,
#else
   PtLiRguDStaRsp,
#endif
#ifdef RG
   RgUiRguDStaRsp,
#else
   PtLiRguDStaRsp,
#endif
#ifdef LWLCKWLIRGU
   cmPkRguDStaRsp
#else
   PtLiRguDStaRsp
#endif
};

#ifdef LTE_L2_MEAS
#ifdef LTEMAC_R9
/** @brief Primitive invoked from RLC to MAC to 
 *  * inform the On/Off Status of LC Id*/
PRIVATE CONSTANT RguL2MUlThrpMeasReq KwLiRguL2MUlThrpMeasReqMt[KW_MAX_RGU_PROV] =
{
#ifdef LCKWLIRGU
   cmPkRguL2MUlThrpMeasReq,
#else
   PtLiRguL2MUlThrpMeasReq,
#endif
#ifdef RG
   RgUiRguL2MUlThrpMeasReq,
#else
   PtLiRguL2MUlThrpMeasReq,
#endif
#ifdef LWLCKWLIRGU
   cmPkRguL2MUlThrpMeasReq,
#else
  PtLiRguL2MUlThrpMeasReq 
#endif
};
#endif
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef KW



/**
* @brief Request from RLC to MAC to bind the interface saps
*
* @details
*
*     Function : KwLiRguBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 KwLiRguBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 KwLiRguBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(KwLiRguBndReq);

   (*KwLiRguBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);

}



/**
* @brief Request from RLC to MAC to Unbind the interface saps
*
* @details
*
*     Function : KwLiRguUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 KwLiRguUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 KwLiRguUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(KwLiRguUbndReq);

   (*KwLiRguUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);

}



/**
* @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission
*
* @details
*
*     Function : KwLiRguCDatReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguCDatReqInfo  *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 KwLiRguCDatReq
(
Pst* pst,
SpId spId,
RguCDatReqInfo  * datReq
)
#else
PUBLIC S16 KwLiRguCDatReq(pst, spId, datReq)
Pst* pst;
SpId spId;
RguCDatReqInfo  * datReq;
#endif
{

   TRC3(KwLiRguCDatReq);

   (*KwLiRguCDatReqMt[pst->selector])(pst, spId, datReq);

   RETVALUE(ROK);

}



/**
* @brief Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission
*
* @details
*
*     Function : KwLiRguDDatReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguDDatReqInfo  *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 KwLiRguDDatReq
(
Pst* pst,
SpId spId,
RguDDatReqInfo  * datReq
)
#else
PUBLIC S16 KwLiRguDDatReq(pst, spId, datReq)
Pst* pst;
SpId spId;
RguDDatReqInfo  * datReq;
#endif
{

   TRC3(KwLiRguDDatReq);

   (*KwLiRguDDatReqMt[pst->selector])(pst, spId, datReq);

   RETVALUE(ROK);

}



/**
* @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for common channels
*
* @details
*
*     Function : KwLiRguCStaRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguCStaRspInfo  *  staRsp
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 KwLiRguCStaRsp
(
Pst* pst,
SpId spId,
RguCStaRspInfo  * staRsp
)
#else
PUBLIC S16 KwLiRguCStaRsp(pst, spId, staRsp)
Pst* pst;
SpId spId;
RguCStaRspInfo  * staRsp;
#endif
{

   TRC3(KwLiRguCStaRsp);

   (*KwLiRguCStaRspMt[pst->selector])(pst, spId, staRsp);

   RETVALUE(ROK);

}



/**
* @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for dedicated channels
*
* @details
*
*     Function : KwLiRguDStaRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguDStaRspInfo  *  staRsp
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 KwLiRguDStaRsp
(
Pst* pst,
SpId spId,
RguDStaRspInfo  * staRsp
)
#else
PUBLIC S16 KwLiRguDStaRsp(pst, spId, staRsp)
Pst* pst;
SpId spId;
RguDStaRspInfo  * staRsp;
#endif
{

   TRC3(KwLiRguDStaRsp);

   (*KwLiRguDStaRspMt[pst->selector])(pst, spId, staRsp);

   RETVALUE(ROK);

}

#ifdef LTE_L2_MEAS
#ifdef LTEMAC_R9
/**
* @brief Primitive invoked from RLC to MAC to 
* inform the On/Off Status of LC Id
*
* @details
*
*     Function :KwLiRguL2MUlThrpMeasReq 
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguL2MUlThrpMeasReqInfo  * measReq 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 KwLiRguL2MUlThrpMeasReq 
(
Pst* pst,
SpId spId,
RguL2MUlThrpMeasReqInfo* measReq 
)
#else
PUBLIC S16 KwLiRguL2MUlThrpMeasReq(pst, spId, measReq)
Pst* pst;
SpId spId;
RguL2MUlThrpMeasReqInfo* measReq;
#endif
{

   TRC3(KwLiRguL2MUlThrpMeasReq);

   (*KwLiRguL2MUlThrpMeasReqMt[pst->selector])(pst, spId, measReq);

   RETVALUE(ROK);

}
#endif
#endif


#endif /*--ifdef KW--*/

#ifdef PTKWLIRGU



/**
* @brief Request from RLC to MAC to bind the interface saps
*
* @details
*
*     Function : PtLiRguBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRguBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 PtLiRguBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(PtLiRguBndReq);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(ROK);

}



/**
* @brief Request from RLC to MAC to Unbind the interface saps
*
* @details
*
*     Function : PtLiRguUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRguUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 PtLiRguUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(PtLiRguUbndReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(reason);

   RETVALUE(ROK);

}



/**
* @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission
*
* @details
*
*     Function : PtLiRguCDatReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguCDatReqInfo  *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRguCDatReq
(
Pst* pst,
SpId spId,
RguCDatReqInfo  * datReq
)
#else
PUBLIC S16 PtLiRguCDatReq(pst, spId, datReq)
Pst* pst;
SpId spId;
RguCDatReqInfo  * datReq;
#endif
{

   TRC3(PtLiRguCDatReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(datReq);

   RETVALUE(ROK);

}



/**
* @brief Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission
*
* @details
*
*     Function : PtLiRguDDatReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguDDatReqInfo  *  datReq
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRguDDatReq
(
Pst* pst,
SpId spId,
RguDDatReqInfo  * datReq
)
#else
PUBLIC S16 PtLiRguDDatReq(pst, spId, datReq)
Pst* pst;
SpId spId;
RguDDatReqInfo  * datReq;
#endif
{

   TRC3(PtLiRguDDatReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(datReq);

   RETVALUE(ROK);

}



/**
* @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for common channels
*
* @details
*
*     Function : PtLiRguCStaRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguCStaRspInfo  *  staRsp
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRguCStaRsp
(
Pst* pst,
SpId spId,
RguCStaRspInfo  * staRsp
)
#else
PUBLIC S16 PtLiRguCStaRsp(pst, spId, staRsp)
Pst* pst;
SpId spId;
RguCStaRspInfo  * staRsp;
#endif
{

   TRC3(PtLiRguCStaRsp);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(staRsp);

   RETVALUE(ROK);

}



/**
* @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for dedicated channels
*
* @details
*
*     Function : PtLiRguDStaRsp
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguDStaRspInfo  *  staRsp
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRguDStaRsp
(
Pst* pst,
SpId spId,
RguDStaRspInfo  * staRsp
)
#else
PUBLIC S16 PtLiRguDStaRsp(pst, spId, staRsp)
Pst* pst;
SpId spId;
RguDStaRspInfo  * staRsp;
#endif
{

   TRC3(PtLiRguDStaRsp);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(staRsp);

   RETVALUE(ROK);

}

#ifdef LTE_L2_MEAS
#ifdef LTEMAC_R9
/**
* @brief Primitive invoked from RLC to MAC to 
*  * inform the On/Off Status of LC Id
*
* @details
*
*     Function :PtLiRguL2MUlThrpMeasReq 
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RguDStaRspInfo  *  staRsp
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRguL2MUlThrpMeasReq 
(
Pst* pst,
SpId spId,
RguL2MUlThrpMeasReqInfo* measReq
)
#else
PUBLIC S16 PtLiRguL2MUlThrpMeasReq(pst, spId, measReq)
Pst* pst;
SpId spId;
RguL2MUlThrpMeasReqInfo* measReq;
#endif
{

   TRC3(PtLiRguL2MUlThrpMeasReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(measReq);

   RETVALUE(ROK);

}
#endif
#endif

#endif /*--ifdef PTKWLIRGU--*/


/**********************************************************************
 
         End of file:     kw_ptli.c@@/main/2 - Sat Jul 30 02:22:20 2011
 
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
