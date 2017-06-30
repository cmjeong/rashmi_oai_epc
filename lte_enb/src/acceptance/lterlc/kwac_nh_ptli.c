

/********************************************************************20**
  
        Name:    RLC service user (RRC) lower interface
    
        Type:    C file
  
        Desc:    TKWs file Contains the RLC service user lower interface
                  primitive implementain
 
        File:    kwac_nh_ptli.c

        Sid:      kwac_nh_ptli.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:36 2014
  
        Prg:     chakrapani
  
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
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */
#include "kw_err.h"        /* Error defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_ckw.h"      /* CKW Acceptance defines */
#include "kwac_kwu.h"      /* CKW Acceptance defines */

#ifdef KW_PDCP
#include "kwac_pju.h"      /* CKW Acceptance defines */
#endif /* KW_PDCP */

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
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_ckw.x"      /* CKW Acceptance defines */
#include "kwac_kwu.x"      /* CKW Acceptance defines */

#ifdef KW_PDCP
#include "kwac_pju.x"      /* CKW Acceptance defines */
#endif /* KW_PDCP */


/************************************************************************
                             CKW Interface Matrices
************************************************************************/

PUBLIC CkwBndReq nhLiCkwBndReqMt [] =
{
#ifdef LCKWUICKW
   cmPkCkwBndReq,        /* 0 - loosely coupled */
#else
   PtLiCkwBndReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwUiCkwBndReq,        /* 1 - tightly coupled, stub layer */
#else
   PtLiCkwBndReq,        /* 1 - tightly coupled, portable */
#endif
};

PUBLIC CkwUbndReq nhLiCkwUbndReqMt [] =
{
#ifdef LCKWUICKW
   cmPkCkwUbndReq,        /* 0 - loosely coupled */
#else
   PtLiCkwUbndReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwUiCkwUbndReq,        /* 1 - tightly coupled, stub layer */
#else
   PtLiCkwUbndReq,        /* 1 - tightly coupled, portable */
#endif
};

PUBLIC CkwCfgReq nhLiCkwCfgReqMt [] =
{
#ifdef LCKWUICKW
   cmPkCkwCfgReq,        /* 0 - loosely coupled */
#else
   PtLiCkwCfgReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwUiCkwCfgReq,        /* 1 - tightly coupled, stub layer */
#else
   PtLiCkwCfgReq,        /* 1 - tightly coupled, portable */
#endif
};

PUBLIC CkwUeIdChgReq nhLiCkwUeIdChgReqMt [] =
{
#ifdef LCKWUICKW
   cmPkCkwUeIdChgReq,        /* 0 - loosely coupled */
#else
   PtLiCkwUeIdChgReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwUiCkwUeIdChgReq,        /* 1 - tightly coupled, stub layer */
#else
   PtLiCkwUeIdChgReq,        /* 1 - tightly coupled, portable */
#endif
};


/****************************************************************************
 *                         CKW Interface Mt functions
 ***************************************************************************/
/**
 *
 * @brief 
 *
 *        NhLiCkwBndReq - CKW SAP bind Request
 *
 *  @param[in] pst   - Post structure  
 *  @param[in] suId  - Service user SAP ID 
 *  @param[in] spId  - Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 NhLiCkwBndReq
(
Pst *pst,                       /* post structure */
SuId suId,                      /* Service User Id */
SpId spId                       /* Service Provider Id */
)
#else
PUBLIC S16 NhLiCkwBndReq(pst, suId, spId)
Pst *pst;                       /* post structure */
SuId suId;                      /* Service User Id */
SpId spId;                      /* Service Provider Id */
#endif
{
   TRC3(NhLiCkwBndReq)

   /* jump to specific primitive depending on configured selector */
   (*nhLiCkwBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);

} /* end of NhLiCkwBndReq */


/**
 *
 * @brief 
 *
 *        NhLiCkwUbndReq - CKW SAP unbind Request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] suId    - Service provider SAP ID 
 *  @param[in] reason  - Reason
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 NhLiCkwUbndReq
(
Pst         *pst,
SpId        spId,
Reason      reason
)
#else
PUBLIC S16 NhLiCkwUbndReq(pst, spId, reason)
Pst         *pst;
SpId        spId;
Reason      reason;
#endif
{
   TRC3(NhLiCkwUbndReq)

   /* jump to specific primitive depending on configured selector */
   (*nhLiCkwUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);

} /* end of NhLiCkwUbndReq */


/**
 *
 * @brief 
 *
 *        NhLiCkwCfgReq - CKW configuration Request
 *
 *  @param[in] pst      - Post structure  
 *  @param[in] spId     - Service provider SAP ID 
 *  @param[in] cfgInfo  - Configuration Request
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 NhLiCkwCfgReq
(
Pst         *pst,                      /* post structure */
SpId        spId,                      /* Service Provider Id */
CkwCfgInfo  *cfgInfo                   /* Configuration Request */
)
#else
PUBLIC S16 NhLiCkwCfgReq(pst, spId, cfgInfo)
Pst         *pst;                      /* post structure */
SpId        spId;                      /* Service Provider Id */
CkwCfgInfo  *cfgInfo;                  /* Configuration Request */
#endif
{
   TRC3(NhLiCkwCfgReq)

   /* jump to specific primitive depending on configured selector */
   (*nhLiCkwCfgReqMt[pst->selector])(pst, spId, cfgInfo);

   RETVALUE(ROK);

} /* end of NhLiCkwCfgReq */


/**
 *
 * @brief 
 *
 *        NhLiCkwUeIdChgReq - CKW Ue Id Change Request
 *
 *  @param[in] pst      - Post structure  
 *  @param[in] spId     - Service provider SAP ID 
 *  @param[in] cfgInfo  - Configuration Request
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 NhLiCkwUeIdChgReq
(
Pst         *pst,                      /* post structure */
SpId        spId,                      /* Service Provider Id */
U32         transId,                   /* Transaction Id */
CkwUeInfo   *ueInfo,                   /* UE Information */
CkwUeInfo   *newUeInfo                 /* New UE Information */
)
#else
PUBLIC S16 NhLiCkwUeIdChgReq(pst, spId, transId, ueInfo, newUeInfo)
Pst         *pst;                      /* post structure */
SpId        spId;                      /* Service Provider Id */
U32         transId;                   /* Transaction Id */
CkwUeInfo   *ueInfo;                   /* UE Information */
CkwUeInfo   *newUeInfo;                /* New UE Information */
#endif
{
   TRC3(NhLiCkwUeIdChgReq)

   /* jump to specific primitive depending on configured selector */
   (*nhLiCkwUeIdChgReqMt[pst->selector])(pst, spId, transId, ueInfo, newUeInfo);

   RETVALUE(ROK);

} /* end of NhLiCkwUeIdChgReq */

/****************************************************************************
 *                         Porting Functions
 ***************************************************************************/
/**
 *
 * @brief 
 *
 *        PtLiCkwBndReq - portable bind request
 *
 *  @param[in] pst      - Post structure  
 *  @param[in] suId  - Service user SAP ID 
 *  @param[in] spId  - Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 PtLiCkwBndReq
(
Pst         *post,
SuId        suId,
SpId        spId
)
#else
PUBLIC S16 PtLiCkwBndReq(post, suId, spId)
Pst         *post;
SuId        suId;
SpId        spId;
#endif /* ANSI */
{
   TRC3(PtLiCkwBndReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for NhLiCkwBndReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(suId);
   UNUSED(spId);
   RETVALUE(ROK);
} /* end of PtLiCkwBndReq() */

  
/**
 *
 * @brief 
 * 
 *       PtLiCkwUbndReq - portable unbind request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] suId    - Service provider SAP ID 
 *  @param[in] reason  - Reason
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiCkwUbndReq
(
Pst         *post,
SpId        spId,
Reason      reason
)
#else
PUBLIC S16 PtLiCkwUbndReq(post, spId, reason)
Pst         *post;
SpId        spId;
Reason      reason;
#endif /* ANSI */
{
   TRC3(PtLiCkwUbndReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for NhLiCkwUbndReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(spId);
   UNUSED(reason);
   RETVALUE(ROK);
} /* end of PtLiCkwUbndReq() */


/**
 *
 * @brief 
 *
 *        PtLiCkwCfgReq - portable config request
 *
 *  @param[in] pst      - Post structure  
 *  @param[in] spId     - Service provider SAP ID 
 *  @param[in] cfgInfo  - Configuration Request
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiCkwCfgReq
(
Pst         *pst,
SpId        spId,
CkwCfgInfo  *cfgInfo
)
#else
PUBLIC S16 PtLiCkwCfgReq(pst, spId, cfgInfo)
Pst         *pst;
SpId        spId;
CkwCfgInfo  *cfgInfo;
#endif /* ANSI */
{
   TRC3(PtLiCkwCfgReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for NhLiCkwCfgReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(cfgInfo);
   RETVALUE(ROK);
} /* end of PtLiCkwCfgReq() */


/**
 *
 * @brief 
 *
 *        PtLiCkwUeIdChgReq - portable config request
 *
 *  @param[in] pst      - Post structure  
 *  @param[in] spId     - Service provider SAP ID 
 *  @param[in] transId  - Transaction ID
 *  @param[in] ueInfo   - UE Information
 *  @param[in] newUeInfo   - New UE Information
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiCkwUeIdChgReq
(
Pst         *pst,
SpId        spId,
U32         transId,
CkwUeInfo   *ueInfo,
CkwUeInfo   *newUeInfo
)
#else
PUBLIC S16 PtLiCkwUeIdChgReq(pst, spId, transId, ueInfo, newUeInfo)
Pst         *pst;
SpId        spId;
U32         transId;
CkwUeInfo   *ueInfo;
CkwUeInfo   *newUeInfo;
#endif /* ANSI */
{
   TRC3(PtLiCkwUeIdChgReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for NhLiCkwUeIdChgReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(transId);
   UNUSED(ueInfo);
   UNUSED(newUeInfo);
   RETVALUE(ROK);
} /* end of PtLiCkwUeIdChgReq() */


/************************************************************************
 *                         KWU Interface Matrices
 ***********************************************************************/

PUBLIC KwuBndReq nhLiKwuBndReqMt [] =
{
#ifdef LCKWUIKWU
   cmPkKwuBndReq,        /* 0 - loosely coupled */
#else
   PtLiKwuBndReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwUiKwuBndReq,        /* 1 - tightly coupled, stub layer */
#else
   PtLiKwuBndReq,        /* 1 - tightly coupled, portable */
#endif
};

PUBLIC KwuUbndReq nhLiKwuUbndReqMt [] =
{
#ifdef LCKWUIKWU
   cmPkKwuUbndReq,        /* 0 - loosely coupled */
#else
   PtLiKwuUbndReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwUiKwuUbndReq,        /* 1 - tightly coupled, stub layer */
#else
   PtLiKwuUbndReq,        /* 1 - tightly coupled, portable */
#endif
};

PUBLIC KwuDatReq nhLiKwuDatReqMt [] =
{
#ifdef LCKWUIKWU
   cmPkKwuDatReq,        /* 0 - loosely coupled */
#else
   PtLiKwuDatReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwUiKwuDatReq,        /* 1 - tightly coupled, stub layer */
#else
   PtLiKwuDatReq,        /* 1 - tightly coupled, portable */
#endif
};

#ifndef KW_PDCP
PUBLIC KwuDiscSduReq nhLiKwuDiscSduReqMt [] =
{
#ifdef LCKWUIKWU
   cmPkKwuDiscSduReq,        /* 0 - loosely coupled */
#else
   PtLiKwuDiscSduReq,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwUiKwuDiscSduReq,        /* 1 - tightly coupled, stub layer */
#else
   PtLiKwuDiscSduReq,        /* 1 - tightly coupled, portable */
#endif
};
#endif /* KW_PDCP */


/****************************************************************************
 *                         KWU Interface Mt functions
 ***************************************************************************/
/**
 *
 * @brief 
 *
 *        NhLiKwuBndReq - KWU SAP bind Request
 *
 *  @param[in] pst   - Post structure  
 *  @param[in] suId  - Service user SAP ID 
 *  @param[in] spId  - Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 NhLiKwuBndReq
(
Pst *pst,                       /* post structure */
SuId suId,                      /* Service User Id */
SpId spId                       /* Service Provider Id */
)
#else
PUBLIC S16 NhLiKwuBndReq(pst, suId, spId)
Pst *pst;                       /* post structure */
SuId suId;                      /* Service User Id */
SpId spId;                      /* Service Provider Id */
#endif
{
   TRC3(NhLiKwuBndReq)

   /* jump to specific primitive depending on configured selector */
   (*nhLiKwuBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);

} /* end of NhLiKwuBndReq */


/**
 *
 * @brief 
 *
 *        NhLiKwuUbndReq - KWU SAP unbind Request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] spId    - Service provider SAP ID 
 *  @param[in] reason  - Reason
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 NhLiKwuUbndReq
(
Pst         *pst,
SpId        spId,
Reason      reason
)
#else
PUBLIC S16 NhLiKwuUbndReq(pst, spId, reason)
Pst         *pst;
SpId        spId;
Reason      reason;
#endif
{
   TRC3(NhLiKwuUbndReq)

   /* jump to specific primitive depending on configured selector */
   (*nhLiKwuUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);

} /* end of NhLiKwuUbndReq */


/**
 *
 * @brief 
 *
 *        NhLiKwuDatReq - KWU Data Request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] spId    - Service provider SAP ID 
 *  @param[in] datReq  - Data Request
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 NhLiKwuDatReq
(
Pst            *pst,
SpId           spId,
KwuDatReqInfo  *datReq,
Buffer         *mBuf
)
#else
PUBLIC S16 NhLiKwuDatReq(pst, spId, datReq, mBuf)
Pst            *pst;
SpId           spId;
KwuDatReqInfo  *datReq;
Buffer         *mBuf;
#endif
{
   TRC3(NhLiKwuDatReq)

   /* jump to specific primitive depending on configured selector */
   (*nhLiKwuDatReqMt[pst->selector])(pst, spId, datReq, mBuf);

   RETVALUE(ROK);

} /* end of NhLiKwuDatReq */


#ifndef KW_PDCP
/**
 *
 * @brief 
 *
 *        NhLiKwuDiscSduReq - KWU Discard SDU Request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] spId    - Service provider SAP ID 
 *  @param[in] datReq  - Data Request
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 NhLiKwuDiscSduReq
(
Pst               *pst,
SpId              spId,
KwuDiscSduInfo    *discSdu
)
#else
PUBLIC S16 NhLiKwuDiscSduReq(pst, spId, discSdu)
Pst               *pst;
SpId              spId;
KwuDiscSduInfo    *discSdu;
#endif
{
   TRC3(NhLiKwuDiscSduReq)

   /* jump to specific primitive depending on configured selector */
   (*nhLiKwuDiscSduReqMt[pst->selector])(pst, spId, discSdu);

   RETVALUE(ROK);

} /* end of NhLiKwuDiscSduReq */
#endif /* KW_PDCP */


/****************************************************************************
 *                         KWU Porting Functions
 ***************************************************************************/
/**
 *
 * @brief 
 *
 *        PtLiKwuBndReq - portable bind request
 *
 *  @param[in] pst   - Post structure  
 *  @param[in] suId  - Service user SAP ID 
 *  @param[in] spId  - Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiKwuBndReq
(
Pst         *post,
SuId        suId,
SpId        spId
)
#else
PUBLIC S16 PtLiKwuBndReq(post, suId, spId)
Pst         *post;
SuId        suId;
SpId        spId;
#endif /* ANSI */
{
   TRC3(PtLiKwuBndReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for NhLiKwuBndReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(ROK);
} /* end of PtLiKwuBndReq() */

  
/**
 *
 * @brief 
 *
 *        PtLiKwuUbndReq - portable unbind request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] suId    - Service provider SAP ID 
 *  @param[in] reason  - Reason
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 PtLiKwuUbndReq
(
Pst         *post,
SpId        spId,
Reason      reason
)
#else
PUBLIC S16 PtLiKwuUbndReq(post, spId, reason)
Pst         *post;
SpId        spId;
Reason      reason;
#endif /* ANSI */
{
   TRC3(PtLiKwuUbndReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for NhLiKwuUbndReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(spId);
   UNUSED(reason);
   
   RETVALUE(ROK);
} /* end of PtLiKwuUbndReq() */

  
/**
 *
 * @brief 
 *
 *        PtLiKwuDatReq - portable data request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] spId    - Service provider SAP ID 
 *  @param[in] datReq  - Data Request
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 PtLiKwuDatReq
(
Pst            *pst,
SpId           spId,
KwuDatReqInfo  *datReq,
Buffer         *mBuf
)
#else
PUBLIC S16 PtLiKwuDatReq(pst, spId, datReq, mBuf)
Pst            *pst;
SpId           spId;
KwuDatReqInfo  *datReq;
Buffer         *mBuf;
#endif /* ANSI */
{
   TRC3(PtLiKwuDatReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for NhLiKwuDatReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(datReq);
   UNUSED(mBuf);

   RETVALUE(ROK);
} /* end of PtLiKwuDatReq() */

  
#ifndef KW_PDCP
/**
 *
 * @brief 
 *
 *        PtLiKwuDiscSduReq - portable discard SDU request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] spId    - Service provider SAP ID 
 *  @param[in] datReq  - Data Request
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 PtLiKwuDiscSduReq
(
Pst               *post,
SpId              spId,
KwuDiscSduInfo    *discSdu
)
#else
PUBLIC S16 PtLiKwuDiscSduReq(post, spId, discSdu)
Pst               *post;
SpId              spId;
KwuDiscSduInfo    *discSdu;
#endif /* ANSI */
{
   TRC3(PtLiKwuDiscSduReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for NhLiKwuDiscSduReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(spId);
   UNUSED(discSdu);

   RETVALUE(ROK);
} /* end of PtLiKwuDiscSduReq() */
#endif /* KW_PDCP */


#ifdef KW_PDCP

/******************************************************************************
 *                      CPJ   Interface
 *****************************************************************************/
#ifndef LCPJUICPJ
#define PTNHLICPJ
#endif

#ifdef PTNHLICPJ

EXTERN S16 PtLiCpjBndReq ARGS((Pst * pst, SuId suId, SpId spId));

EXTERN S16 PtLiCpjUbndReq ARGS((Pst * pst, SpId spId, Reason reason));

EXTERN S16 PtLiCpjCfgReq ARGS((Pst * pst, SpId spId, CpjCfgReqInfo * cfgReq));

EXTERN S16 PtLiCpjReEstReq ARGS((Pst * pst, SpId spId, CpjReEstReqInfo * reEstReq));

EXTERN S16 PtLiCpjSecCfgReq ARGS((Pst * pst, SpId spId, CpjSecCfgReqInfo * secCfgReq));

EXTERN S16 PtLiCpjUeIdChgReq ARGS((Pst * pst, SpId spId, U32 transId, CpjUeInfo * oldUeInfo, CpjUeInfo * newUeInfo));

EXTERN S16 PtLiCpjCountReq ARGS((Pst * pst, SpId spId, CpjCountReqInfo * countReq));

EXTERN S16 PtLiCpjSduStaReq ARGS((Pst * pst, SpId spId, CpjSduStaReqInfo * staReq));
#endif /*--#ifdef PTNHLICPJ--*/


/************************************************************************
 *                         CPJ Interface Matrices
 ***********************************************************************/
PRIVATE CONSTANT CpjBndReq NhLiCpjBndReqMt[] =
{
#ifdef LCPJUICPJ
   cmPkCpjBndReq,
#else
   PtLiCpjBndReq,
#endif
#ifdef PJ
   PjUiCpjBndReq,
#else
   PtLiCpjBndReq,
#endif
};


PRIVATE CONSTANT CpjUbndReq NhLiCpjUbndReqMt[] =
{
#ifdef LCPJUICPJ
   cmPkCpjUbndReq,
#else
   PtLiCpjUbndReq,
#endif
#ifdef PJ
   PjUiCpjUbndReq,
#else
   PtLiCpjUbndReq,
#endif
};


PRIVATE CONSTANT CpjCfgReq NhLiCpjCfgReqMt[] =
{
#ifdef LCPJUICPJ
   cmPkCpjCfgReq,
#else
   PtLiCpjCfgReq,
#endif
#ifdef PJ
   PjUiCpjCfgReq,
#else
   PtLiCpjCfgReq,
#endif
};


PRIVATE CONSTANT CpjReEstReq nhLiCpjReEstReqMt[] =
{
#ifdef LCPJUICPJ
   cmPkCpjReEstReq,
#else
   PtLiCpjReEstReq,
#endif
#ifdef PJ
   PjUiCpjReEstReq,
#else
   PtLiCpjReEstReq,
#endif
};


PRIVATE CONSTANT CpjSecCfgReq NhLiCpjSecCfgReqMt[] =
{
#ifdef LCPJUICPJ
   cmPkCpjSecCfgReq,
#else
   PtLiCpjSecCfgReq,
#endif
#ifdef PJ
   PjUiCpjSecCfgReq,
#else
   PtLiCpjSecCfgReq,
#endif
};


PRIVATE CONSTANT CpjUeIdChgReq NhLiCpjUeIdChgReqMt[] =
{
#ifdef LCPJUICPJ
   cmPkCpjUeIdChgReq,
#else
   PtLiCpjUeIdChgReq,
#endif
#ifdef PJ
   PjUiCpjUeIdChgReq,
#else
   PtLiCpjUeIdChgReq,
#endif
};


PRIVATE CONSTANT CpjCountReq NhLiCpjCountReqMt[] =
{
#ifdef LCPJUICPJ
   cmPkCpjCountReq,
#else
   PtLiCpjCountReq,
#endif
#ifdef PJ
   PjUiCpjCountReq,
#else
   PtLiCpjCountReq,
#endif
};


PRIVATE CONSTANT CpjSduStaReq NhLiCpjSduStaReqMt[] =
{
#ifdef LCPJUICPJ
   cmPkCpjSduStaReq,
#else
   PtLiCpjSduStaReq,
#endif
#ifdef PJ
   PjUiCpjSduStaReq,
#else
   PtLiCpjSduStaReq,
#endif
};


/****************************************************************************
 *                         CPJ Interface Mt functions
 ***************************************************************************/
#ifdef NH
#ifdef ANSI
PUBLIC S16 NhLiCpjBndReq
(
Pst * pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 NhLiCpjBndReq(pst, suId, spId)
Pst * pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(NhLiCpjBndReq)

   (*NhLiCpjBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NhLiCpjUbndReq
(
Pst * pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 NhLiCpjUbndReq(pst, spId, reason)
Pst * pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(NhLiCpjUbndReq)

   (*NhLiCpjUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NhLiCpjCfgReq
(
Pst * pst,
SpId spId,
CpjCfgReqInfo * cfgReq
)
#else
PUBLIC S16 NhLiCpjCfgReq(pst, spId, cfgReq)
Pst * pst;
SpId spId;
CpjCfgReqInfo * cfgReq;
#endif
{

   TRC3(NhLiCpjCfgReq)

   (*NhLiCpjCfgReqMt[pst->selector])(pst, spId, cfgReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NhLiCpjReEstReq
(
Pst * pst,
SpId spId,
CpjReEstReqInfo * reEstReq
)
#else
PUBLIC S16 NhLiCpjReEstReq(pst, spId, reEstReq)
Pst * pst;
SpId spId;
CpjReEstReqInfo * reEstReq;
#endif
{

   TRC3(NhLiCpjReEstReq)

   (*nhLiCpjReEstReqMt[pst->selector])(pst, spId, reEstReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NhLiCpjSecCfgReq
(
Pst * pst,
SpId spId,
CpjSecCfgReqInfo * secCfgReq
)
#else
PUBLIC S16 NhLiCpjSecCfgReq(pst, spId, secCfgReq)
Pst * pst;
SpId spId;
CpjSecCfgReqInfo * secCfgReq;
#endif
{

   TRC3(NhLiCpjSecCfgReq)

   (*NhLiCpjSecCfgReqMt[pst->selector])(pst, spId, secCfgReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NhLiCpjUeIdChgReq
(
Pst * pst,
SpId spId,
U32 transId,
CpjUeInfo * oldUeInfo,
CpjUeInfo * newUeInfo
)
#else
PUBLIC S16 NhLiCpjUeIdChgReq(pst, spId, transId, oldUeInfo, newUeInfo)
Pst * pst;
SpId spId;
U32 transId;
CpjUeInfo * oldUeInfo;
CpjUeInfo * newUeInfo;
#endif
{

   TRC3(NhLiCpjUeIdChgReq)

   (*NhLiCpjUeIdChgReqMt[pst->selector])(pst, spId, transId, oldUeInfo, newUeInfo);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NhLiCpjCountReq
(
Pst * pst,
SpId spId,
CpjCountReqInfo * countReq
)
#else
PUBLIC S16 NhLiCpjCountReq(pst, spId, countReq)
Pst * pst;
SpId spId;
CpjCountReqInfo * countReq;
#endif
{

   TRC3(NhLiCpjCountReq)

   (*NhLiCpjCountReqMt[pst->selector])(pst, spId, countReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NhLiCpjSduStaReq
(
Pst * pst,
SpId spId,
CpjSduStaReqInfo * staReq
)
#else
PUBLIC S16 NhLiCpjSduStaReq(pst, spId, staReq)
Pst * pst;
SpId spId;
CpjSduStaReqInfo * staReq;
#endif
{

   TRC3(NhLiCpjSduStaReq)

   (*NhLiCpjSduStaReqMt[pst->selector])(pst, spId, staReq);

   RETVALUE(ROK);

}
#endif /*--ifdef NH--*/


/****************************************************************************
 *                         CPJ Porting Functions
 ***************************************************************************/
#ifdef PTNHLICPJ
#ifdef ANSI
PUBLIC S16 PtLiCpjBndReq
(
Pst * pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 PtLiCpjBndReq(pst, suId, spId)
Pst * pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(PtLiCpjBndReq)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiCpjUbndReq
(
Pst * pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 PtLiCpjUbndReq(pst, spId, reason)
Pst * pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(PtLiCpjUbndReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(reason);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiCpjCfgReq
(
Pst * pst,
SpId spId,
CpjCfgReqInfo * cfgReq
)
#else
PUBLIC S16 PtLiCpjCfgReq(pst, spId, cfgReq)
Pst * pst;
SpId spId;
CpjCfgReqInfo * cfgReq;
#endif
{

   TRC3(PtLiCpjCfgReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(cfgReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiCpjReEstReq
(
Pst * pst,
SpId spId,
CpjReEstReqInfo * reEstReq
)
#else
PUBLIC S16 PtLiCpjReEstReq(pst, spId, reEstReq)
Pst * pst;
SpId spId;
CpjReEstReqInfo * reEstReq;
#endif
{

   TRC3(PtLiCpjReEstReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(reEstReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiCpjSecCfgReq
(
Pst * pst,
SpId spId,
CpjSecCfgReqInfo * secCfgReq
)
#else
PUBLIC S16 PtLiCpjSecCfgReq(pst, spId, secCfgReq)
Pst * pst;
SpId spId;
CpjSecCfgReqInfo * secCfgReq;
#endif
{

   TRC3(PtLiCpjSecCfgReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(secCfgReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiCpjUeIdChgReq
(
Pst * pst,
SpId spId,
U32 transId,
CpjUeInfo * oldUeInfo,
CpjUeInfo * newUeInfo
)
#else
PUBLIC S16 PtLiCpjUeIdChgReq(pst, spId, transId, oldUeInfo, newUeInfo)
Pst * pst;
SpId spId;
U32 transId;
CpjUeInfo * oldUeInfo;
CpjUeInfo * newUeInfo;
#endif
{

   TRC3(PtLiCpjUeIdChgReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(transId);
   UNUSED(oldUeInfo);
   UNUSED(newUeInfo);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiCpjCountReq
(
Pst * pst,
SpId spId,
CpjCountReqInfo * countReq
)
#else
PUBLIC S16 PtLiCpjCountReq(pst, spId, countReq)
Pst * pst;
SpId spId;
CpjCountReqInfo * countReq;
#endif
{

   TRC3(PtLiCpjCountReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(countReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiCpjSduStaReq
(
Pst * pst,
SpId spId,
CpjSduStaReqInfo * staReq
)
#else
PUBLIC S16 PtLiCpjSduStaReq(pst, spId, staReq)
Pst * pst;
SpId spId;
CpjSduStaReqInfo * staReq;
#endif
{

   TRC3(PtLiCpjSduStaReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(staReq);

   RETVALUE(ROK);

}

#endif /*--ifdef PTNHLICPJ--*/


/************************************************************************
                             PJU Interface Matrices
************************************************************************/
PRIVATE CONSTANT PjuBndReq NhLiPjuBndReqMt[] =
{
#ifdef LCPJUIPJU
   cmPkPjuBndReq,
#else
   PtLiPjuBndReq,
#endif
#ifdef PJ
   PjUiPjuBndReq,
#else
   PtLiPjuBndReq,
#endif
};


PRIVATE CONSTANT PjuUbndReq NhLiPjuUbndReqMt[] =
{
#ifdef LCPJUIPJU
   cmPkPjuUbndReq,
#else
   PtLiPjuUbndReq,
#endif
#ifdef PJ
   PjUiPjuUbndReq,
#else
   PtLiPjuUbndReq,
#endif
};


PRIVATE CONSTANT PjuDatReq NhLiPjuDatReqMt[] =
{
#ifdef LCPJUIPJU
   cmPkPjuDatReq,
#else
   PtLiPjuDatReq,
#endif
#ifdef PJ
   PjUiPjuDatReq,
#else
   PtLiPjuDatReq,
#endif
};


PRIVATE CONSTANT PjuDatFwdReq NhLiPjuDatFwdReqMt[] =
{
#ifdef LCPJUIPJU
   cmPkPjuDatFwdReq,
#else
   PtLiPjuDatFwdReq,
#endif
#ifdef PJ
   PjUiPjuDatFwdReq,
#else
   PtLiPjuDatFwdReq,
#endif
};


/****************************************************************************
 *                         PJU Interface Mt functions
 ***************************************************************************/
#ifdef NH
#ifdef ANSI
PUBLIC S16 NhLiPjuBndReq
(
Pst* pst,
SpId spId,
SuId suId
)
#else
PUBLIC S16 NhLiPjuBndReq(pst, spId, suId)
Pst* pst;
SpId spId;
SuId suId;
#endif
{

   TRC3(NhLiPjuBndReq)

   (*NhLiPjuBndReqMt[pst->selector])(pst, spId, suId);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NhLiPjuUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 NhLiPjuUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(NhLiPjuUbndReq)

   (*NhLiPjuUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NhLiPjuDatReq
(
Pst* pst,
SpId spId,
CmLtePdcpId *pdcpId,
PjuSduId sduId,
Buffer *mBuf
)
#else
PUBLIC S16 NhLiPjuDatReq(pst, spId, pdcpId, sduId, mBuf)
Pst* pst;
SpId spId;
CmLtePdcpId *pdcpId;
PjuSduId sduId;
Buffer *mBuf;
#endif
{

   TRC3(NhLiPjuDatReq)

   (*NhLiPjuDatReqMt[pst->selector])(pst, spId, pdcpId, sduId, mBuf);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 NhLiPjuDatFwdReq
(
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuDatFwdReqInfo * datFwdReq
)
#else
PUBLIC S16 NhLiPjuDatFwdReq(pst, spId, pdcpId, datFwdReq)
Pst* pst;
SpId spId;
CmLtePdcpId * pdcpId;
PjuDatFwdReqInfo * datFwdReq;
#endif
{

   TRC3(NhLiPjuDatFwdReq)

   (*NhLiPjuDatFwdReqMt[pst->selector])(pst, spId, pdcpId, datFwdReq);

   RETVALUE(ROK);

}
#endif /*--ifdef NH--*/

#endif /* KW_PDCP */

  
/********************************************************************30**
         End of file:     kwac_nh_ptli.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:36 2014
*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision KWstory:
  
*********************************************************************61*/

/********************************************************************90**
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
*********************************************************************91*/

