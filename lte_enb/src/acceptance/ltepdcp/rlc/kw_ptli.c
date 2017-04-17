

/********************************************************************20**
  
        Name:    LTE-RLC Layer - Upper Interface
    
        Type:    C file
  
        Desc:    C source code for the upper interface of LTE-RLC
 
        File:    kw_ptui.c

        Sid:      kw_ptli.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:48 2014
  
        Prg:     gk
  
*********************************************************************21*/

/** @file gp_ptui.c
@brief RLC Upper Interface
*/

/*
 *      This software may be combined with the following TRILLIUM
 *      software:
 *
 *      part no.                      description
 *      --------    ----------------------------------------------
 *      1000371     LTE-RLC
 */


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
#include "pju.h"           /* PJU defines */
#include "lpj.h"           /* LPJ defines */
#endif
#include "kw_err.h"
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

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
#include "cpj.x"           /* CPJ defines */
#include "pju.x"           /* PJU defines */
#include "lpj.x"           /* LPJ defines */
#endif
#include "kw.x"

#ifndef LCKWLIRGU
#define PTKWRGU
#endif

#ifndef RG
#define PTKWRGU
#endif

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */


/*********************************************************************
 *             Forward Declaration of RGU Porting Functions
 ********************************************************************/
EXTERN S16 PtLiRguBndReq ARGS((
Pst         *post,
SuId        suId,
SpId        spId
));

EXTERN S16 PtLiRguUbndReq ARGS ((
Pst         *post,
SpId        spId,
Reason      reason
));

EXTERN S16 PtLiRguCDatReq ARGS ((
Pst               *post,
SpId              spId,
RguCDatReqInfo    *datReq
));

EXTERN S16 PtLiRguDDatReq ARGS ((
Pst               *post,
SpId              spId,
RguDDatReqInfo    *datReq
));

EXTERN S16 PtLiRguCStaRsp ARGS ((
Pst               *post,
SpId              spId,
RguCStaRspInfo    *staRsp
));

EXTERN S16 PtLiRguDStaRsp ARGS ((
Pst               *post,
SpId              spId,
RguDStaRspInfo    *staRsp
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
EXTERN S16 PtLiRguL2mUlThrpMeasReq ARGS ((
Pst                      *post,
SpId                     spId,
RguL2MUlThrpMeasReqInfo  *l2mUlThrpMeasReq
));
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS  */


/*********************************************************************
 *             Primitives for RGU interface 
 ********************************************************************/

/* RGU Bind Request primitive */

PUBLIC RguBndReq kwLiRguBndReqMt[] =
{
#ifdef LCKWLIRGU
   cmPkRguBndReq,            /* 0 - loosely coupled */
#else
   PtLiRguBndReq,            /* 0 - loosely coupled, portable  */
#endif /* LCRGUIRGU */
#ifdef RG 
   RgUiRguBndReq,            /* 1 - tightly coupled, MAC  */
#else
   PtLiRguBndReq,            /* 1 - tightly coupled, portable */
#endif /* RG */
};

/* RGU Unbind Request primitive */

PUBLIC RguBndReq kwLiRguUbndReqMt[] =
{
#ifdef LCKWLIRGU
   cmPkRguUbndReq,            /* 0 - loosely coupled */
#else
   PtLiRguUbndReq,            /* 0 - loosely coupled, portable  */
#endif /* LCRGUIRGU */
#ifdef RG 
   RgUiRguUbndReq,            /* 1 - tightly coupled, MAC  */
#else
   PtLiRguUbndReq,            /* 1 - tightly coupled, portable */ /* RG */
#endif /* RG */
};

/* RGU Common Channel Data Request primitive */

PUBLIC RguCDatReq kwLiRguCDatReqMt[] =
{
#ifdef LCKWLIRGU
   cmPkRguCDatReq,            /* 0 - loosely coupled */
#else
   PtLiRguCDatReq,            /* 0 - loosely coupled, portable  */
#endif /* LCRGUIRGU */
#ifdef RG 
   RgUiRguCDatReq,            /* 1 - tightly coupled, MAC  */
#else
   PtLiRguCDatReq,            /* 1 - tightly coupled, portable */
#endif /* RG */
};

/* RGU Dedicated Channel Data Request primitive */

PUBLIC RguDDatReq kwLiRguDDatReqMt[] =
{
#ifdef LCKWLIRGU
   cmPkRguDDatReq,            /* 0 - loosely coupled */
#else
   PtLiRguDDatReq,            /* 0 - loosely coupled, portable  */
#endif /* LCRGUIRGU */
#ifdef RG 
   RgUiRguDDatReq,            /* 1 - tightly coupled, MAC  */
#else
   PtLiRguDDatReq,            /* 1 - tightly coupled, portable */
#endif /* RG */
};

/* RGU Common Channel Status Response primitive */

PUBLIC RguCStaRsp kwLiRguCStaRspMt[] =
{
#ifdef LCKWLIRGU
   cmPkRguCStaRsp,            /* 0 - loosely coupled */
#else
   PtLiRguCStaRsp,            /* 0 - loosely coupled, portable  */
#endif /* LCRGUIRGU */
#ifdef RG 
   RgUiRguCStaRsp,            /* 1 - tightly coupled, MAC  */
#else
   PtLiRguCStaRsp,            /* 1 - tightly coupled, portable */
#endif /* RG */
};

/* RGU Dedicated Channel Status Response primitive */

PUBLIC RguDStaRsp kwLiRguDStaRspMt[] =
{
#ifdef LCKWLIRGU
   cmPkRguDStaRsp,            /* 0 - loosely coupled */
#else
   PtLiRguDStaRsp,            /* 0 - loosely coupled, portable  */
#endif /* LCRGUIRGU */
#ifdef RG 
   RgUiRguDStaRsp,            /* 1 - tightly coupled, MAC  */
#else
   PtLiRguDStaRsp,            /* 1 - tightly coupled, portable */
#endif /* RG */
};

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
/* RGU L2 Measurement Ul Ip Throughput Measurement Request primitive */

PUBLIC RguL2MUlThrpMeasReq kwLiRguL2MUlThrpMeasReqMt[] =
{
#ifdef LCKWLIRGU
   cmPkRguL2MUlThrpMeasReq,            /* 0 - loosely coupled */
#else
   PtLiRguL2mUlThrpMeasReq,            /* 0 - loosely coupled, portable  */
#endif /* LCRGUIRGU */
#ifdef RG 
   RgUiRguL2MUlThrpMeasReq,            /* 1 - tightly coupled, MAC  */
#else
   PtLiRguL2mUlThrpMeasReq,            /* 1 - tightly coupled, portable */
#endif /* RG */
};
#endif /* LTE_RLC_R9 */
#endif /*  LTE_L2_MEAS */

/****************************************************************************
 *                         RGU Interface Mt functions
 ***************************************************************************/
/**
 *
 * @brief 
 *
 *        Handler for RGU SAP bind Request.
 *
 * @b Description:
 *
 *        This function is used by RLC to request for binding to 
 *        MAC for accessing MAC services.This function binds MAC's 
 *        SAP (identified by spId) with the service user's SAP 
 *        (identified by suId).
 *
 *  @param[in] pst   Post structure  
 *  @param[in] suId  Service user SAP ID 
 *  @param[in] spId  Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 KwLiRguBndReq
(
Pst  *post,                       /* post structure */
SuId suId,                      /* Service User Id */
SpId spId                       /* Service Provider Id */
)
#else
PUBLIC S16 KwLiRguBndReq(post, suId, spId)
Pst  *post;                       /* post structure */
SuId suId;                      /* Service User Id */
SpId spId;                      /* Service Provider Id */
#endif
{
   TRC3(KwLiRguBndReq)

   /* jump to specific primitive depending on configured selector */
   (*kwLiRguBndReqMt[post->selector])(post, suId, spId);

   RETVALUE(ROK);

} /* end of KwLiRguBndReq */


/**
 *
 * @brief 
 *
 *        Handler for bind confirmation from MAC.
 *
 * @b Description:
 *
 *        This function handles the bind confirmation received
 *        from MAC. 
 *
 *  @param[in] post     - Post structure  
 *  @param[in] suId    - Service provider SAP ID 
 *  @param[in] reason  - Reason of confirmation
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 KwLiRguUbndReq
(
Pst         *post,
SpId        spId,
Reason      reason
)
#else
PUBLIC S16 KwLiRguUbndReq(post, spId, reason)
Pst         *post;
SpId        spId;
Reason      reason;
#endif
{
   TRC3(KwLiRguUbndReq)

   /* jump to specific primitive depending on configured selector */
   (*kwLiRguUbndReqMt[post->selector])(post, spId, reason);

   RETVALUE(ROK);

} /* end of KwLiRguUbndReq */

  
/**
 *
 * @brief 
 *
 *        Handler for sending the PDU from RLC to MAC for common logical channels. 
 *
 * @b Description:
 *
 *        This function sends a PDU of a common logical channel to MAC
 *        along with timing info for BCCH and PCCH and RNTI for CCCH. 
 *
 *  @param[in] post         Post structure  
 *  @param[in] spId        Service Provider ID
 *  @param[in] datIndInfo  Data Request Information 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 KwLiRguCDatReq
(
Pst               *post,
SpId              spId,
RguCDatReqInfo    *datReq
)
#else
PUBLIC S16 KwLiRguCDatReq(post, spId, datReq)
Pst               *post;
SpId              spId;
RguCDatReqInfo    *datReq;
#endif
{
   TRC3(KwLiRguCDatReq)

   /* jump to specific primitive depending on configured selector */
   (*kwLiRguCDatReqMt[post->selector])(post, spId, datReq);

   RETVALUE(ROK);

} /* end of KwLiRguCDatReq */

  
/**
 *
 * @brief 
 *
 *        Handler for sending PDU(s) from RLC to MAC for dedicated logical channels. 
 *
 * @b Description:
 *
 *        This function sends PDU(s) to MAC via one or more dedicated 
 *        logical channels along with the Buffer Occupancy of these
 *        channels.
 *
 *  @param[in] post         Post structure  
 *  @param[in] spId        Service Provider ID
 *  @param[in] datIndInfo  Data Request Information 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 KwLiRguDDatReq
(
Pst               *post,
SpId              spId,
RguDDatReqInfo    *datReq
)
#else
PUBLIC S16 KwLiRguDDatReq(post, spId, datReq)
Pst               *post;
SpId              spId;
RguDDatReqInfo    *datReq;
#endif
{
   TRC3(KwLiRguDDatReq)

   /* jump to specific primitive depending on configured selector */
   (*kwLiRguDDatReqMt[post->selector])(post, spId, datReq);

   RETVALUE(ROK);

} /* end of KwLiRguDDatReq */

  
/**
 *
 * @brief  
 *
 *        Handler for reporting the Buffer Occupancy to MAC 
 *     for common logical channels.
 *
 * @b Description:
 *
 *        This function reports the Buffer Occupancy of a common logical
 *        channel to MAC along with timing information for BCCH and PCCH
 *        and RNTI for CCCH. 
 *
 *  @param[in] post         Post structure  
 *  @param[in] spId        Service Provider ID
 *  @param[in] staRspInfo  Status Response Information 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 KwLiRguCStaRsp
(
Pst               *post,
SpId              spId,
RguCStaRspInfo    *staRsp
)
#else
PUBLIC S16 KwLiRguCStaRsp(post, spId, staRsp)
Pst               *post;
SpId              spId;
RguCStaRspInfo    *staRsp;
#endif
{
   TRC3(KwLiRguCStaRsp)

   /* jump to specific primitive depending on configured selector */
   (*kwLiRguCStaRspMt[post->selector])(post, spId, staRsp);

   RETVALUE(ROK);

} /* end of KwLiRguCStaRsp */

  
/**
 *
 * @brief  
 *
 *        Handler for reporting the Buffer Occupancy to MAC 
 *        for dedicated logical channels.
 *
 * @b Description:
 *
 *        This function reports the Buffer Occupancy of one or more
 *        dedicated logical channels to MAC. 
 *
 *  @param[in] post         Post structure  
 *  @param[in] spId        Service Provider ID
 *  @param[in] staRspInfo  Status Response Information 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 KwLiRguDStaRsp
(
Pst               *post,
SpId              spId,
RguDStaRspInfo    *staRsp
)
#else
PUBLIC S16 KwLiRguDStaRsp(post, spId, staRsp)
Pst               *post;
SpId              spId;
RguDStaRspInfo    *staRsp;
#endif
{
   TRC3(KwLiRguDStaRsp)

   /* jump to specific primitive depending on configured selector */
   (*kwLiRguDStaRspMt[post->selector])(post, spId, staRsp);

   RETVALUE(ROK);

} /* end of KwLiRguDStaRsp */


/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
  
/**
 *
 * @brief 
 *
 *        Handler for sending ulThrpMeasReqInfo from RLC to MAC for UL ip throughput measurement. 
 *
 * @b Description:
 *
 *        This function sends ulThrpMeasReqInfo from RLC to MAC whenver UL ip throughput
 * measurement is ON for a single or multiple qci in a UE. This is an indication for MAC
 * to start the T2/T1 time stamps for the coresponding LCHs in the UE.
 *
 *  @param[in] post                    Post structure  
 *  @param[in] spId                   Service Provider ID
 *  @param[in] ulThrpMeasReqInfo      Ul ip measurement request info
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 KwLiRguL2MUlThrpMeasReq
(
Pst                     *post,
SpId                    spId,
RguL2MUlThrpMeasReqInfo *l2mUlThrpMeasReq
)
#else
PUBLIC S16 KwLiRguL2MUlThrpMeasReq(post, spId, l2mUlThrpMeasReq)
Pst                     *post;
SpId                    spId;
RguL2MUlThrpMeasReqInfo *l2mUlThrpMeasReq;
#endif
{
   TRC3(KwLiRguL2MUlThrpMeasReq)

   /* jump to specific primitive depending on configured selector */
   (*kwLiRguL2MUlThrpMeasReqMt[post->selector])(post, spId, l2mUlThrpMeasReq);

   RETVALUE(ROK);

} /* end of KwLiRguL2MUlThrpMeasReq */

#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS */



/****************************************************************************
 *                         Porting Functions
 ***************************************************************************/

/**
 *
 * @brief 
 *
 *        PtLiRguBndReq - portable bind request
 *
 *  @param[in] post   - Post structure  
 *  @param[in] suId  - Service user SAP ID 
 *  @param[in] spId  - Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiRguBndReq
(
Pst         *post,
SuId        suId,
SpId        spId
)
#else
PUBLIC S16 PtLiRguBndReq(post, suId, spId)
Pst         *post;
SuId        suId;
SpId        spId;
#endif /* ANSI */
{
#if (ERRCLASS & ERRCLS_DEBUG)
   KwCb   *tKwCb;
#endif

   TRC3(PtLiRguBndReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   tKwCb = KW_GET_KWCB(post->srcInst);
   KWLOGERROR(tKwCb, ERRCLS_DEBUG, EKW034, ERRZERO, 
      "Improper selector for RgUiRguBndReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(suId);
   UNUSED(spId);

   RETVALUE(ROK);
} /* end of PtLiRguBndReq() */

  
/**
 *
 * @brief 
 *
 *        PtLiRguUbndReq - portable bind request
 *
 *  @param[in] post    -  Post structure  
 *  @param[in] spId   -  Service user SAP ID 
 *  @param[in] reason -  Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiRguUbndReq
(
Pst         *post,
SpId        spId,
Reason      reason
)
#else
PUBLIC S16 PtLiRguUbndReq(post, spId, reason)
Pst         *post;
SpId        spId;
Reason      reason;
#endif /* ANSI */
{
#if (ERRCLASS & ERRCLS_DEBUG)
   KwCb   *tKwCb;
#endif

   TRC3(PtLiRguUbndReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   tKwCb = KW_GET_KWCB(post->srcInst);
   KWLOGERROR(tKwCb, ERRCLS_DEBUG, EKW035, ERRZERO, 
      "Improper selector for RgUiRguUbndReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(spId);
   UNUSED(reason);

   RETVALUE(ROK);
} /* end of PtLiRguUbndReq() */

  
/**
 *
 * @brief 
 *
 *        PtLiRguCDatReq - portable common channel data request
 *
 *  @param[in] post    -  Post structure  
 *  @param[in] spId   -  Service user SAP ID 
 *  @param[in] datReq -  Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiRguCDatReq
(
Pst               *post,
SpId              spId,
RguCDatReqInfo    *datReq
)
#else
PUBLIC S16 PtLiRguCDatReq(post, spId, datReq)
Pst               *post;
SpId              spId;
RguCDatReqInfo    *datReq;
#endif /* ANSI */
{
#if (ERRCLASS & ERRCLS_DEBUG)
   KwCb   *tKwCb;
#endif

   TRC3(PtLiRguCDatReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   tKwCb = KW_GET_KWCB(post->srcInst);
   KWLOGERROR(tKwCb, ERRCLS_DEBUG, EKW036, ERRZERO, 
      "Improper selector for RgUiRguCDatReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(spId);
   UNUSED(datReq);

   RETVALUE(ROK);
} /* end of PtLiRguCDatReq() */

  
/**
 *
 * @brief 
 *
 *        PtLiRguDDatReq - portable dedicated channel data request
 *
 *  @param[in] post    -  Post structure  
 *  @param[in] spId   -  Service user SAP ID 
 *  @param[in] datReq -  Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiRguDDatReq
(
Pst               *post,
SpId              spId,
RguDDatReqInfo    *datReq
)
#else
PUBLIC S16 PtLiRguDDatReq( post, spId, datReq)
Pst               *post;
SpId              spId;
RguDDatReqInfo    *datReq;
#endif /* ANSI */
{
#if (ERRCLASS & ERRCLS_DEBUG)
   KwCb   *tKwCb;
#endif

   TRC3(PtLiRguDDatReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   tKwCb = KW_GET_KWCB(post->srcInst);
   KWLOGERROR(tKwCb, ERRCLS_DEBUG, EKW037, ERRZERO, 
      "Improper selector for RgUiRguDDatReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(spId);
   UNUSED(datReq);

   RETVALUE(ROK);
} /* end of PtLiRguDDatReq() */

  
/**
 *
 * @brief 
 *
 *        PtLiRguCStaRsp - portable common channel Status Response
 *
 *  @param[in] post    -  Post structure  
 *  @param[in] spId   -  Service user SAP ID 
 *  @param[in] staRsp -  Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiRguCStaRsp
(
Pst               *post,
SpId              spId,
RguCStaRspInfo    *staRsp
)
#else
PUBLIC S16 PtLiRguCStaRsp(post, spId, staRsp)
Pst               *post;
SpId              spId;
RguCStaRspInfo    *staRsp;
#endif /* ANSI */
{
#if (ERRCLASS & ERRCLS_DEBUG)
   KwCb   *tKwCb;
#endif

   TRC3(PtLiRguCStaRsp)
#if (ERRCLASS & ERRCLS_DEBUG)
   tKwCb = KW_GET_KWCB(post->srcInst);
   KWLOGERROR(tKwCb, ERRCLS_DEBUG, EKW038, ERRZERO, 
      "Improper selector for RgUiRguCStaRsp\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(spId);
   UNUSED(staRsp);

   RETVALUE(ROK);
} /* end of PtLiRguCStaRsp() */

  
/**
 *
 * @brief 
 *
 *        PtLiRguDStaRsp - portable dedicated channel Status Response
 *
 *  @param[in] post    -  Post structure  
 *  @param[in] spId   -  Service user SAP ID 
 *  @param[in] staRsp -  Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiRguDStaRsp
(
Pst               *post,
SpId              spId,
RguDStaRspInfo    *staRsp
)
#else
PUBLIC S16 PtLiRguDStaRsp(post, spId, staRsp)
Pst               *post;
SpId              spId;
RguDStaRspInfo    *staRsp;
#endif /* ANSI */
{
#if (ERRCLASS & ERRCLS_DEBUG)
   KwCb   *tKwCb;
#endif

   TRC3(PtLiRguDStaRsp)
#if (ERRCLASS & ERRCLS_DEBUG)
   tKwCb = KW_GET_KWCB(post->srcInst);
   KWLOGERROR(tKwCb, ERRCLS_DEBUG, EKW039, ERRZERO, 
      "Improper selector for RgUiRguDStaRsp\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(spId);
   UNUSED(staRsp);

   RETVALUE(ROK);
} /* end of PtLiRguDStaRsp() */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
  
/**
 *
 * @brief 
 *
 *      PtLiRguL2mUlThrpMeasReq - portable L2 Measurement Ul Thoughput Measurement Request
 *
 *  @param[in] post    -  Post structure  
 *  @param[in] spId   -  Service user SAP ID 
 *  @param[in] l2mUlThrpMeasReq -  Ul Throughput Measurement Request
 *
 *  @return  S16
 *      -# ROK 
 */

#ifdef ANSI
PUBLIC S16 PtLiRguL2mUlThrpMeasReq
(
Pst                     *post,
SpId                    spId,
RguL2MUlThrpMeasReqInfo *l2mUlThrpMeasReq
)
#else
PUBLIC S16 PtLiRguL2mUlThrpMeasReq(post, spId, l2mUlThrpMeasReq)
Pst                     *post,
Pst                      *post;
SpId                     spId;
RguL2MUlThrpMeasReqInfo  *l2mUlThrpMeasReq;
#endif /* ANSI */
{
#if (ERRCLASS & ERRCLS_DEBUG)
   KwCb   *tKwCb;
#endif

   TRC3(PtLiRguL2mUlThrpMeasReq)
#if (ERRCLASS & ERRCLS_DEBUG)
   tKwCb = KW_GET_KWCB(post->srcInst);
   KWLOGERROR(tKwCb, ERRCLS_DEBUG, EKWXXX, ERRZERO, 
      "Improper selector for RgUiRguL2MUlThrpMeasReq\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   UNUSED(post);
   UNUSED(spId);
   UNUSED(l2mUlThrpMeasReq);

   RETVALUE(ROK);
} /* end of PtLiRguL2mUlThrpMeasReq() */

#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS */


#ifdef __cplusplus
}
#endif /* __cplusplus */
  
/********************************************************************30**
         End of file:     kw_ptli.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:48 2014
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
/main/1      ---      gk   1. initial release.
/main/2      ---      gk   1. LTERLC Release 2.1
/main/3   kw005.201   rd   1. Added the interface fn KwLiRguL2MUlThrpMeasReq
                           2. Added the pt function PtLiRguL2mUlThrpMeasReq.
*********************************************************************91*/

