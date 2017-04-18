

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      nx_ptli.c@@/main/2 - Sat Jul 30 02:22:23 2011
  
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



#if !(defined(LCNXLIRGR)  && defined(RG) && defined(LWLCNXLIRGR))
#define PTNXLIRGR
#endif


/* MAX Number of Service Providers of NX */
#define NX_MAX_RGR_PROV   3

#ifdef PTNXLIRGR
/** @brief Request from RRM to MAC to bind the interface saps */
EXTERN S16 PtLiRgrBndReq ARGS((Pst* pst, SuId suId, SpId spId));
/** @brief Request from RRM to MAC to Unbind the interface saps */
EXTERN S16 PtLiRgrUbndReq ARGS((Pst* pst, SpId spId, Reason reason));
/** @brief Configuration Request from RRM to MAC for 
 * configuring Cell/Ue/Lc */
EXTERN S16 PtLiRgrCfgReq ARGS((Pst* pst, SpId spId, RgrCfgTransId transId, RgrCfgReqInfo * cfgReqInfo));
/* rg004.201-ADD-Added for SI Enhancement*/
/** @brief SI Configuration Request from RRM to MAC */
#ifdef RGR_SI_SCH
EXTERN S16 PtLiRgrSiCfgReq ARGS((Pst* pst, SpId spId, RgrCfgTransId transId, RgrSiCfgReqInfo* cfgReqInfo));

EXTERN S16 PtLiRgrWarningSiCfgReq ARGS((Pst* pst, SpId spId, 
                                        RgrCfgTransId transId,          
                                        RgrWarningSiCfgReqInfo* cfgReqInfo));
EXTERN S16 PtLiRgrWarningSiStopReq ARGS((Pst* pst, SpId spId, 
                                        RgrCfgTransId transId, U8 siId));
#endif
/* LTE_ADV_FLAG_REMOVED_START */
EXTERN S16 PtLiRgrLoadInfReq ARGS((Pst* pst, SpId spId, RgrCfgTransId transId, RgrLoadInfReqInfo* loadInfReqInfo));
/* LTE_ADV_FLAG_REMOVED_END */
#endif /*--#ifdef PTNXLIRGR--*/

/** @brief Request from RRM to MAC to bind the interface saps */
PRIVATE CONSTANT RgrBndReq NxLiRgrBndReqMt[NX_MAX_RGR_PROV] =
{
#ifdef LCNXLIRGR
   cmPkRgrBndReq,
#else
   PtLiRgrBndReq,
#endif
#ifdef RG
   RgUiRgrBndReq,
#else
   PtLiRgrBndReq,
#endif
#ifdef LWLCNXLIRGR
   cmPkRgrBndReq
#else
   PtLiRgrBndReq
#endif
};

/** @brief Request from RRM to MAC to Unbind the interface saps */
PRIVATE CONSTANT RgrUbndReq NxLiRgrUbndReqMt[NX_MAX_RGR_PROV] =
{
#ifdef LCNXLIRGR
   cmPkRgrUbndReq,
#else
   PtLiRgrUbndReq,
#endif
#ifdef RG
   RgUiRgrUbndReq,
#else
   PtLiRgrUbndReq,
#endif
#ifdef LWLCNXLIRGR
   cmPkRgrUbndReq
#else
   PtLiRgrUbndReq
#endif
};

/** @brief Configuration Request from RRM to MAC for 
 * configuring Cell/Ue/Lc */
PRIVATE CONSTANT RgrCfgReq NxLiRgrCfgReqMt[NX_MAX_RGR_PROV] =
{
#ifdef LCNXLIRGR
   cmPkRgrCfgReq,
#else
   PtLiRgrCfgReq,
#endif
#ifdef RG
   RgUiRgrCfgReq,
#else
   PtLiRgrCfgReq,
#endif
#ifdef LWLCNXLIRGR
   cmPkRgrCfgReq
#else
   PtLiRgrCfgReq
#endif
};

/* rg004.201-ADD-Added for SI Enhancement*/
#ifdef RGR_SI_SCH
/** @brief SI Configuration Request from RRM to MAC for 
 * configuring SI */
PRIVATE CONSTANT RgrSiCfgReq NxLiRgrSiCfgReqMt[NX_MAX_RGR_PROV] =
{
#ifdef LCNXLIRGR
   cmPkRgrSiCfgReq,
#else
   PtLiRgrSiCfgReq,
#endif
#ifdef RG
   RgUiRgrSiCfgReq,
#else
   PtLiRgrSiCfgReq,
#endif
#ifdef LWLCNXLIRGR
   cmPkRgrSiCfgReq
#else
   PtLiRgrSiCfgReq
#endif
};


PRIVATE CONSTANT RgrWarningSiCfgReq NxLiRgrWarningSiCfgReqMt[NX_MAX_RGR_PROV] =
{
#ifdef LCNXLIRGR
   cmPkRgrWarningSiCfgReq,
#else
   PtLiRgrWarningSiCfgReq,
#endif
#ifdef RG
   RgUiRgrWarningSiCfgReq,
#else
   PtLiRgrWarningSiCfgReq,
#endif
#ifdef LWLCNXLIRGR
   cmPkRgrWarningSiCfgReq
#else
   PtLiRgrWarningSiCfgReq
#endif
};

 
PRIVATE CONSTANT RgrWarningSiStopReq NxLiRgrWarningSiStopReqMt[NX_MAX_RGR_PROV] =
{
#ifdef LCNXLIRGR
   cmPkRgrWarningSiStopReq,
#else
   PtLiRgrWarningSiStopReq,
#endif
#ifdef RG
   RgUiRgrWarningSiStopReq,
#else
   PtLiRgrWarningSiStopReq,
#endif
#ifdef LWLCNXLIRGR
   cmPkRgrWarningSiStopReq
#else
   PtLiRgrWarningSiStopReq
#endif
};
#endif
/* LTE_ADV_FLAG_REMOVED_START */
/** @brief Load Info Request from RRM to MAC  */
PRIVATE CONSTANT RgrLoadInfReq NxLiRgrLoadInfReqMt[NX_MAX_RGR_PROV] =
{
#ifdef LCNXLIRGR
   cmPkRgrLoadInfReq,
#else
   PtLiRgrLoadInfReq,
#endif
#ifdef RG
   RgUiRgrLoadInfReq,
#else
   PtLiRgrLoadInfReq,
#endif
#ifdef LWLCNXLIRGR
   cmPkRgrLoadInfReq
#else
   PtLiRgrLoadInfReq
#endif
};
/* LTE_ADV_FLAG_REMOVED_END */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef NX



/**
* @brief Request from RRM to MAC to bind the interface saps
*
* @details
*
*     Function : NxLiRgrBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 NxLiRgrBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 NxLiRgrBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(NxLiRgrBndReq);

   (*NxLiRgrBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);

}



/**
* @brief Request from RRM to MAC to Unbind the interface saps
*
* @details
*
*     Function : NxLiRgrUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 NxLiRgrUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 NxLiRgrUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(NxLiRgrUbndReq);

   (*NxLiRgrUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);

}



/**
* @brief Configuration Request from RRM to MAC for 
 * configuring Cell/Ue/Lc
*
* @details
*
*     Function : NxLiRgrCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RgrCfgTransId  transId
*  @param[in]   RgrCfgReqInfo *  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 NxLiRgrCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrCfgReqInfo * cfgReqInfo
)
#else
PUBLIC S16 NxLiRgrCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrCfgReqInfo * cfgReqInfo;
#endif
{

   TRC3(NxLiRgrCfgReq);

   (*NxLiRgrCfgReqMt[pst->selector])(pst, spId, transId, cfgReqInfo);

   RETVALUE(ROK);

}

/* rg004.201-ADD-Added for SI Enhancement*/
#ifdef RGR_SI_SCH
/**
* @brief SI Configuration Request from RRM to MAC for 
 * configuring SI
*
* @details
*
*     Function : NxLiRgrSiCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RgrCfgTransId  transId
*  @param[in]   RgrSiCfgReqInfo *  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 NxLiRgrSiCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrSiCfgReqInfo * cfgReqInfo
)
#else
PUBLIC S16 NxLiRgrSiCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrSiCfgReqInfo * cfgReqInfo;
#endif
{

   TRC3(NxLiRgrSiCfgReq);

   (*NxLiRgrSiCfgReqMt[pst->selector])(pst, spId, transId, cfgReqInfo);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NxLiRgrWarningSiCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrWarningSiCfgReqInfo * cfgReqInfo
)
#else
PUBLIC S16 NxLiRgrWarningSiCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrWarningSiCfgReqInfo * cfgReqInfo;
#endif
{

   TRC3(NxLiRgrWarningSiCfgReq);

   (*NxLiRgrWarningSiCfgReqMt[pst->selector])(pst, spId, transId, cfgReqInfo);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 NxLiRgrWarningSiStopReq
(
Pst* pst,
SpId spId,
RgrCfgTransId     transId,
U8   siId
)
#else
PUBLIC S16 NxLiRgrWarningSiStopReq(pst, spId, transId, siId)
Pst* pst;
SpId spId;
RgrCfgTransId     transId;
U8   siId;
#endif
{

   TRC3(NxLiRgrWarningSiStopReq);

   (*NxLiRgrWarningSiStopReqMt[pst->selector])(pst, spId, transId, siId);

   RETVALUE(ROK);

}
 
#endif /*RGR_SI_SCH*/

/* LTE_ADV_FLAG_REMOVED_START */
/**
* @brief LoadInfo Request from RRM to MAC 
* 
*
* @details
*
*     Function : NxLiRgrLoadInfReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RgrCfgTransId  transId
*  @param[in]   RgrLoadInfReqInfo *  loadInfReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 NxLiRgrLoadInfReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrLoadInfReqInfo *  loadInfReqInfo
)
#else
PUBLIC S16 NxLiRgrLoadInfReq(pst, spId, transId, loadInfReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrLoadInfReqInfo *  loadInfReqInfo;
#endif
{

   TRC3(NxLiRgrLoadInfReq);

   (*NxLiRgrLoadInfReqMt[pst->selector])(pst, spId, transId, loadInfReqInfo);

   RETVALUE(ROK);

}
/* LTE_ADV_FLAG_REMOVED_END */
#endif /*--ifdef NX--*/

#ifdef PTNXLIRGR



/**
* @brief Request from RRM to MAC to bind the interface saps
*
* @details
*
*     Function : PtLiRgrBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRgrBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 PtLiRgrBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(PtLiRgrBndReq);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(ROK);

}



/**
* @brief Request from RRM to MAC to Unbind the interface saps
*
* @details
*
*     Function : PtLiRgrUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRgrUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 PtLiRgrUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(PtLiRgrUbndReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(reason);

   RETVALUE(ROK);

}



/**
* @brief Configuration Request from RRM to MAC for 
 * configuring Cell/Ue/Lc
*
* @details
*
*     Function : PtLiRgrCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RgrCfgTransId  transId
*  @param[in]   RgrCfgReqInfo *  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRgrCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrCfgReqInfo * cfgReqInfo
)
#else
PUBLIC S16 PtLiRgrCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrCfgReqInfo * cfgReqInfo;
#endif
{

   TRC3(PtLiRgrCfgReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(transId);
   UNUSED(cfgReqInfo);

   RETVALUE(ROK);

}

/* rg004.201-ADD-Added for SI Enhancement*/
#ifdef RGR_SI_SCH
/**
* @brief SI Configuration Request from RRM to MAC for 
 * configuring SI
*
* @details
*
*     Function : PtLiRgrSiCfgReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RgrCfgTransId  transId
*  @param[in]   RgrSiCfgReqInfo *  cfgReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRgrSiCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrSiCfgReqInfo * cfgReqInfo
)
#else
PUBLIC S16 PtLiRgrSiCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrSiCfgReqInfo * cfgReqInfo;
#endif
{

   TRC3(PtLiRgrSiCfgReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(transId);
   UNUSED(cfgReqInfo);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiRgrWarningSiCfgReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrWarningSiCfgReqInfo * cfgReqInfo
)
#else
PUBLIC S16 PtLiRgrWarningSiCfgReq(pst, spId, transId, cfgReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrWarningSiCfgReqInfo * cfgReqInfo;
#endif
{

   TRC3(PtLiRgrWarningSiCfgReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(transId);
   UNUSED(cfgReqInfo);

   RETVALUE(ROK);

}
 
#ifdef ANSI
PUBLIC S16 PtLiRgrWarningSiStopReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
U8   siId
)
#else
PUBLIC S16 PtLiRgrWarningSiStopReq(pst, spId, transId,siId)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
U8   siId;
#endif
{

   TRC3(PtLiRgrWarningSiStopReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(siId);

   RETVALUE(ROK);

}
#endif /*RGR_SI_SCH*/
/* LTE_ADV_FLAG_REMOVED_START */
/**
* @brief Load Info Request from RRM to MAC for 
 * configuring RNTP
*
* @details
*
*     Function : PtLiRgrLoadInfReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RgrCfgTransId  transId
*  @param[in]   RgrLoadInfReqInfo *  loadInfReqInfo
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 PtLiRgrLoadInfReq
(
Pst* pst,
SpId spId,
RgrCfgTransId transId,
RgrLoadInfReqInfo *loadInfReqInfo
)
#else
PUBLIC S16 PtLiRgrLoadInfReq(pst, spId, transId, loadInfReqInfo)
Pst* pst;
SpId spId;
RgrCfgTransId transId;
RgrLoadInfReqInfo *loadInfReqInfo;
#endif
{

   TRC3(PtLiRgrLoadInfReq);

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(transId);
   UNUSED(loadInfReqInfo);

   RETVALUE(ROK);

}
/* LTE_ADV_FLAG_REMOVED_END */
#endif /*--ifdef PTNXLIRGR--*/



/**********************************************************************
 
         End of file:     nx_ptli.c@@/main/2 - Sat Jul 30 02:22:23 2011
 
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
