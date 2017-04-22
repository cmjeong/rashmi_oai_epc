

/********************************************************************20**
  
        Name:    RLC service provider (MAC) upper interface
    
        Type:    C file
  
        Desc:    This file Contains the RLC service provider upper interface
                  primitive implementain
 
        File:    kwac_dm_ptui.c

        Sid:      kwac_rg_ptui.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:41 2014
  
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
#include "kwac_rgu.h"      /* CKW Acceptance defines */

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
#include "kwac_rgu.x"      /* CKW Acceptance defines */

  
/************************************************************************
                             RGU Interface Matrices
************************************************************************/

/* RGU Bind Confirm primitive */

PUBLIC RguBndCfm rgUiRguBndCfmMt [] =
{
#ifdef LCKWLIRGU
   cmPkRguBndCfm,        /* 0 - loosely coupled */
#else
   PtUiRguBndCfm,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwLiRguBndCfm,        /* 1 - tightly coupled, stub layer */
#else
   PtUiRguBndCfm,        /* 1 - tightly coupled, portable */
#endif
};

/* RGU Common Channel Data Indication primitive */

PUBLIC RguCDatInd rgUiRguCDatIndMt [] =
{
#ifdef LCKWLIRGU
   cmPkRguCDatInd,        /* 0 - loosely coupled */
#else
   PtUiRguCDatInd,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwLiRguCDatInd,        /* 1 - tightly coupled, stub layer */
#else
   PtUiRguCDatInd,        /* 1 - tightly coupled, portable */
#endif
};

/* RGU Dedicated Channel Data Indication primitive */

PUBLIC RguDDatInd rgUiRguDDatIndMt [] =
{
#ifdef LCKWLIRGU
   cmPkRguDDatInd,        /* 0 - loosely coupled */
#else
   PtUiRguDDatInd,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwLiRguDDatInd,        /* 1 - tightly coupled, stub layer */
#else
   PtUiRguDDatInd,        /* 1 - tightly coupled, portable */
#endif
};

/* RGU Common Channel Status Indication primitive */

PUBLIC RguCStaInd rgUiRguCStaIndMt [] =
{
#ifdef LCKWLIRGU
   cmPkRguCStaInd,        /* 0 - loosely coupled */
#else
   PtUiRguCStaInd,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwLiRguCStaInd,        /* 1 - tightly coupled, stub layer */
#else
   PtUiRguCStaInd,        /* 1 - tightly coupled, portable */
#endif
};

/* RGU Dedicated Channel Status Indication primitive */

PUBLIC RguDStaInd rgUiRguDStaIndMt [] =
{
#ifdef LCKWLIRGU
   cmPkRguDStaInd,        /* 0 - loosely coupled */
#else
   PtUiRguDStaInd,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwLiRguDStaInd,        /* 1 - tightly coupled, stub layer */
#else
   PtUiRguDStaInd,        /* 1 - tightly coupled, portable */
#endif
};

PRIVATE RguFlowCntrlIndInfo RgUiRguFlowCntrlIndMt[] =
{
  cmPkRguFlowCntrlInd,
  KwLiRguFlowCntrlInd
};
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/* RGU Dedicated Channel Status Indication primitive */

PUBLIC RguHqStaInd rgUiRguHqStaIndMt [] =
{
#ifdef LCKWLIRGU
   cmPkRguHqStaInd,        /* 0 - loosely coupled */
#else
   PtUiRguHqStaInd,        /* 0 - loosely coupled, portable */
#endif
#ifdef KW
   KwLiRguHqStaInd,        /* 1 - tightly coupled, stub layer */
#else
   PtUiRguHqStaInd,        /* 1 - tightly coupled, portable */
#endif
};
#endif
  
/************************************************************************
                             RGU Interface Primitives
************************************************************************/
/**
 *
 * @brief 
 *
 *        RgUiRguBndCfm - RGU SAP bind Confirm
 *
 *  @param[in] pst   - Post structure  
 *  @param[in] suId    Service user SAP ID 
 *  @param[in] status  Status of Confirmation 
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 RgUiRguBndCfm
(
Pst      *pst,                      /* post structure */
SuId     suId,                      /* Service User Id */
U8       status                     /* Status */
)
#else
PUBLIC S16 RgUiRguBndCfm(pst, suId, status)
Pst      *pst;                      /* post structure */
SuId     suId;                      /* Service User Id */
U8       status;                    /* Status */
#endif
{
   TRC3(RgUiRguBndCfm)

   /* jump to specific primitive depending on configured selector */
   (*rgUiRguBndCfmMt[pst->selector])(pst, suId, status);

   RETVALUE(ROK);

} /* end of RgUiRguBndCfm */


/**
 *
 * @brief 
 *
 *        RgUiRguCDatInd - RGU SAP Common Channel Data Indication
 *
 *  @param[in] pst       - Post structure  
 *  @param[in] suId      - Service provider SAP ID 
 *  @param[in] cDatInd   - Common Channel Data Indication
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 RgUiRguCDatInd
(
Pst               *pst,
SuId              suId,
RguCDatIndInfo    *cDatInd
)
#else
PUBLIC S16 RgUiRguCDatInd(pst, suId, cDatInd)
Pst               *pst;
SuId              suId;
RguCDatIndInfo    *cDatInd;
#endif
{
   TRC3(RgUiRguCDatInd)

   /* jump to specific primitive depending on configured selector */
   (*rgUiRguCDatIndMt[pst->selector])(pst, suId, cDatInd);

   RETVALUE(ROK);

} /* end of RgUiRguCDatInd */


/**
 *
 * @brief 
 *
 *        RgUiRguDDatInd - RGU SAP Dedicated Channel Data Indication
 *
 *  @param[in] pst       - Post structure  
 *  @param[in] suId      - Service provider SAP ID 
 *  @param[in] dDatInd   - Dedicated Channel Data Indication
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 RgUiRguDDatInd
(
Pst               *pst,
SuId              suId,
RguDDatIndInfo    *dDatInd
)
#else
PUBLIC S16 RgUiRguDDatInd(pst, suId, dDatInd)
Pst               *pst;
SuId              suId;
RguDDatIndInfo    *dDatInd;
#endif
{
   TRC3(RgUiRguDDatInd)

   /* jump to specific primitive depending on configured selector */
   (*rgUiRguDDatIndMt[pst->selector])(pst, suId, dDatInd);

   RETVALUE(ROK);

} /* end of RgUiRguDDatInd */


/**
 *
 * @brief 
 *
 *        RgUiRguCStaInd - RGU SAP Common Channel Status Indication
 *
 *  @param[in] pst       - Post structure  
 *  @param[in] suId      - Service provider SAP ID 
 *  @param[in] cStaInd   - Common Channel Status Indication
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 RgUiRguCStaInd
(
Pst               *pst,
SuId              suId,
RguCStaIndInfo    *cStaInd
)
#else
PUBLIC S16 RgUiRguCStaInd(pst, suId, cStaInd)
Pst               *pst;
SuId              suId;
RguCStaIndInfo    *cStaInd;
#endif
{
   TRC3(RgUiRguCStaInd)

   /* jump to specific primitive depending on configured selector */
   (*rgUiRguCStaIndMt[pst->selector])(pst, suId, cStaInd);

   RETVALUE(ROK);

} /* end of RgUiRguCStaInd */


/**
 *
 * @brief 
 *
 *        RgUiRguDStaInd - RGU SAP Dedicated Channel Status Indication
 *
 *  @param[in] pst       - Post structure  
 *  @param[in] suId      - Service provider SAP ID 
 *  @param[in] dStaInd   - Dedicated Channel Status Indication
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 RgUiRguDStaInd
(
Pst               *pst,
SuId              suId,
RguDStaIndInfo    *dStaInd
)
#else
PUBLIC S16 RgUiRguDStaInd(pst, suId, dStaInd)
Pst               *pst;
SuId              suId;
RguDStaIndInfo    *dStaInd;
#endif
{
   TRC3(RgUiRguDStaInd)

   /* jump to specific primitive depending on configured selector */
   (*rgUiRguDStaIndMt[pst->selector])(pst, suId, dStaInd);

   RETVALUE(ROK);

} /* end of RgUiRguDStaInd */

#ifdef ANSI
PUBLIC S16 RgUiRguFlowCntrlInd
(
Pst* pst,
SuId suId,
RguFlowCntrlInd *flowCntrlInd
)
#else
PUBLIC S16 RgUiRguFlowCntrlInd(pst, suId, harqStatusInd)
Pst* pst;
SuId suId;
RguFlowCntrlInd *flowCntrlInd;
#endif
{
  RETVALUE((*RgUiRguFlowCntrlIndMt[pst->selector])(pst, suId, flowCntrlInd));
}
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS

/**
 *
 * @brief 
 *
 *        - RGU SAP Harq Status Indication
 *
 *  @param[in] pst       - Post structure  
 *  @param[in] suId      - Service provider SAP ID 
 *  @param[in] harqStatusInd- Harq Status Indication
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 RgUiRguHqStaInd 
(
Pst               *pst,
SuId              suId,
RguHarqStatusInd *harqStatusInd
)
#else
PUBLIC S16 RgUiRguHqStaInd (pst, suId, harqStatusInd)
Pst               *pst;
SuId              suId;
RguHarqStatusInd *harqStatusInd;
#endif
{
   TRC3(RgUiRguHqStaInd )

   /* jump to specific primitive depending on configured selector */
   (*rgUiRguHqStaIndMt[pst->selector])(pst, suId, harqStatusInd);
   RETVALUE(ROK);

} /* end of RgUiRguHqStaInd */
#endif
  
/************************************************************************
                             RGU Interface Porting Functions
************************************************************************/
/*
 *
 *       Fun:    PtUiRguBndCfm - portable bind confirm
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   kwac_rg_ptui.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtUiRguBndCfm
(
Pst      *pst,                      /* post structure */
SuId     suId,                      /* Service User Id */
U8       status                     /* Status */
)
#else
PUBLIC S16 PtUiRguBndCfm(pst, suId, status)
Pst      *pst;                      /* post structure */
SuId     suId;                      /* Service User Id */
U8       status;                    /* Status */
#endif /* ANSI */
{
   TRC3(PtUiRguBndCfm)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for RgUiRguBndCfm\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);
   RETVALUE(RFAILED);
} /* end of PtUiRguBndCfm() */

  
/*
 *
 *       Fun:    PtUiRguCDatInd - portable data indication
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   kwac_rg_ptui.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtUiRguCDatInd
(
Pst               *pst,
SuId              suId,
RguCDatIndInfo    *cDatInd
)
#else
PUBLIC S16 PtUiRguCDatInd(pst, suId, cDatInd)
Pst               *pst;
SuId              suId;
RguCDatIndInfo    *cDatInd;
#endif /* ANSI */
{
   TRC3(PtUiRguCDatInd)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for RgUiRguCDatInd\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(cDatInd);
   RETVALUE(RFAILED);
} /* end of PtUiRguCDatInd() */

  
/*
 *
 *       Fun:    PtUiRguDDatInd - portable data indication
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   kwac_rg_ptui.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtUiRguDDatInd
(
Pst               *pst,
SuId              suId,
RguDDatIndInfo    *dDatInd
)
#else
PUBLIC S16 PtUiRguDDatInd(pst, suId, dDatInd)
Pst               *pst;
SuId              suId;
RguDDatIndInfo    *dDatInd;
#endif /* ANSI */
{
   TRC3(PtUiRguDDatInd)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for RgUiRguDDatInd\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(dDatInd);
   RETVALUE(RFAILED);
} /* end of PtUiRguDDatInd() */

  
/*
 *
 *       Fun:    PtUiRguCStaInd - portable data indication
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   kwac_rg_ptui.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtUiRguCStaInd
(
Pst               *pst,
SuId              suId,
RguCStaIndInfo    *cStaInd
)
#else
PUBLIC S16 PtUiRguCStaInd(pst, suId, cStaInd)
Pst               *pst;
SuId              suId;
RguCStaIndInfo    *cStaInd;
#endif /* ANSI */
{
   TRC3(PtUiRguCStaInd)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for RgUiRguCStaInd\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(cStaInd);
   RETVALUE(RFAILED);
} /* end of PtUiRguCStaInd() */

  
/*
 *
 *       Fun:    PtUiRguDStaInd - portable data indication
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   kwac_rg_ptui.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtUiRguDStaInd
(
Pst               *pst,
SuId              suId,
RguDStaIndInfo    *dStaInd
)
#else
PUBLIC S16 PtUiRguDStaInd(pst, suId, dStaInd)
Pst               *pst;
SuId              suId;
RguDStaIndInfo    *dStaInd;
#endif /* ANSI */
{
   TRC3(PtUiRguDStaInd)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for RgUiRguDStaInd\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(dStaInd);
   RETVALUE(RFAILED);
} /* end of PtUiRguDStaInd() */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
  
/*
 *
 *       Fun:    PtUiRguHqStaInd - portable harq status indication
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
         File:   kwac_rg_ptui.c
 *
 */

#ifdef ANSI
PUBLIC S16 PtUiRguHqStaInd
(
Pst               *pst,
SuId              suId,
RguHarqStatusInd *harqStatusInd
)
#else
PUBLIC S16 PtUiRguHqStaInd(pst, suId, harqStatusInd)
Pst               *pst;
SuId              suId;
RguHarqStatusInd *harqStatusInd;
#endif /* ANSI */
{
   TRC3(PtUiRguHqStaInd)
#if (ERRCLASS & ERRCLS_DEBUG)
   KWLOGERROR_ACC(ERRCLS_DEBUG, EKWxxx, ERRZERO, 
      "Improper selector for PtUiRguHqStaInd\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(harqStatusInd);
   RETVALUE(ROK);
} /* end of PtUiRguHqStaInd() */
#endif

/********************************************************************30**
         End of file:     kwac_rg_ptui.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:41 2014
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
/main/1      ---      cp      1. Initial release.
/main/2      ---      gk      1. LTE RLC Release 2.1.
/main/3    kw005.201  ap      1. Added support for L2 Measurement.
*********************************************************************91*/

