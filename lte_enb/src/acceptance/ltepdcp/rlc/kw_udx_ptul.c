

/************************************************************************
 
     Name:     LTE-RLC ULDL Interface
  
     Type:     C source file
  
     Desc:     C source code for INF Interface Module 
  
     File:     kw_udx_pt.c
  
     Sid:      kw_udx_ptul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:51 2014
  
     Prg:      mraj
  
**********************************************************************/

/** @file kw_udx_pt.c
*/

/* header include files (.h) */
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
#include "kw_err.h"        /* Err defines */
#include "kw_env.h"        /* RLC environment options */

#include "kw.h"            /* RLC defines */
#include "kw_dl.h"
#include "kw_udx.h"

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

#include "kw.x"
#include "kw_dl.x"
#include "kw_udx.x"

PRIVATE S16 PtUlUdxBndReq ARGS((Pst* pst, SuId suId,SpId  spId ));
PRIVATE S16 PtUlUdxUbndReq ARGS((Pst* pst, SuId suId,Reason reason));
PRIVATE S16 PtUlUdxCfgReq ARGS((Pst *pst, SpId spId, UdxCfgInfo *cfgInfo));
PRIVATE S16 PtUlUdxStaUpdReq ARGS((Pst* pst,SpId spId,CmLteRlcId *rlcId,
                                KwUdxStaPdu         *pStaPdu ));
PRIVATE S16 PtUlUdxUeIdChgReq ARGS((Pst *pst, SpId spId, U32 transId, 
                                   UdxUeInfo *ueInfo, UdxUeInfo *newUeInfo));
PRIVATE S16 PtUlUdxStaPduReq ARGS(( Pst* pst,SpId  spId, CmLteRlcId *rlcId,
                             KwUdxDlStaPdu  *pStaPdu ));
#ifdef ANSI
PRIVATE S16 PtUlUdxBndReq
(
Pst *pst,                       /* post structure */
SuId suId,                      /* Service User Id */
SpId spId                    /* Status */
)
#else
PRIVATE S16 PtUlUdxBndReq(pst, suId,spId)
Pst *pst;                       /* post structure */
SuId suId;                      /* Service User Id */
SpId spId;                    /* Status */
#endif
{
   TRC3(PtUlUdxBndReq)

   RETVALUE(ROK);

} /* end of KwDlUdxBndReq */

/**
 *
 * @brief 
 *
 *        Handler for confirming  the bind request received from KWU
 *        interface.
 *
 * @b Description:
 *
 *        This function send the bind confirm primitive to the RLC user,
 *        when it receives a bind request from its service user.
 *
 *  @param[in] pst     Post structure  
 *  @param[in] suId    Service user SAP ID 
 *  @param[in] status  Status of Confirmation 
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PRIVATE S16 PtUlUdxUbndReq
(
Pst *pst,                       /* post structure */
SpId spId,                      /* Service User Id */
Reason   reason                     /* Status */
)
#else
PRIVATE S16 PtUlUdxUbndReq(pst, suId, status)
Pst *pst;                       /* post structure */
SpId spId;                      /* Service User Id */
Reason Reason;                    /* Status */
#endif
{
   TRC3(PtUlUdxUbndReq)

   RETVALUE(ROK);

} /* end of PtDlUdxBndReq */

#ifdef ANSI
PRIVATE S16 PtUlUdxCfgReq
(
Pst *pst,                       /* post structure */
SpId spId,                      /* Service User Id */
UdxCfgInfo *cfmInfo             /* Config Info */
)
#else
PRIVATE S16 PtUlUdxCfgReq(pst, spId, status)
Pst *pst;                       /* post structure */
SpId spId;                      /* Service User Id */
UdxCfgInfo *cfmInfo;              /* Config Info */
#endif
{
   TRC3(PtUlUdxCfgReq)

   RETVALUE(ROK);

} /* end of KwDlUdxCfgReq */

#ifdef ANSI
PRIVATE S16 PtUlUdxUeIdChgReq
(
Pst *pst,                      /* post structure */
SpId spId,                     /* Service User Id */
U32      transId,              /* transaction Id */
UdxUeInfo *ueInfo,             /* Config Info */
UdxUeInfo *newUeInfo           /* Config Info */
)
#else
PRIVATE S16 PtUlUdxUeIdChgReq(pst, spId,transId, ueInfo, newUeInfo)
Pst *pst;                      /* post structure */
SpId spId;                     /* Service User Id */
U32      transId;              /* transaction Id */
UdxUeInfo *ueInfo;             /* Config Info */
UdxUeInfo *newUeInfo;          /* Config Info */
#endif
{
   TRC3(PtUlUdxUeIdChgReq)


   RETVALUE(ROK);

} /* end of KwDlUdxCfgReq */


PRIVATE S16  PtUlUdxStaPduReq
(
Pst*                pst,
SpId                spId,
CmLteRlcId          *rlcId,
KwUdxDlStaPdu       *pStaPdu
)
{
   TRC3(PtUlUdxStaPduReq);

   RETVALUE(ROK);
}

/**
* @brief Request from ULM to DLM for UE Status
*
* @details
*
*     Function : KwUdxUdxStatUpd
*
*  @param[in]   Pst*           pst

*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PRIVATE S16  PtUlUdxStaUpdReq
(
Pst*                pst,
SpId                spId,
CmLteRlcId          *rlcId,
KwUdxStaPdu       *pStaPdu
)
#else
PRIVATE S16 PtUlUdxStaUpdReq(pst, rlcId, pStaPdu)
Pst*                pst;
SpId                spId;
CmLteRlcId          *rlcId;
KwUdxDlStaPdu       *pStaPdu;
#endif
{

   TRC3(PtUlUdxStaUpdReq);

   RETVALUE(ROK);
} /* end of KwUlmDlmStaUpd*/


PRIVATE UdxBndReq kwUlUdxBndReqMt[] =
{
#ifdef LCKWULUDX
   cmPkUdxBndReq,            /* 0 - loosely coupled */
#else
   PtUlUdxBndReq,            /* 0 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef LWLCKWULUDX
   cmPkUdxBndReq,            /* 1 - loosely coupled */
#else
   PtUlUdxBndReq,            /* 1 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef KW
   KwDlUdxBndReq,            /* 2 - tightly coupled, RRC  */
#else
   PtUlUdxBndReq,            /* 2 - tightly coupled, portable */
#endif /* KW */
};

PRIVATE UdxUbndReq kwUlUdxUbndReqMt[] =
{
#ifdef LCKWULUDX
   cmPkUdxUbndReq,            /* 0 - loosely coupled */
#else
   PtUlUdxUbndReq,            /* 0 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef LWLCKWULUDX
   cmPkUdxUbndReq,            /* 1 - loosely coupled */
#else
   PtUlUdxUbndReq,            /* 1 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef KW
   KwDlUdxUbndReq,            /* 2 - tightly coupled, RRC  */
#else
   PtUlUdxUbndReq,            /* 2 - tightly coupled, portable */
#endif /* KW */
};


PRIVATE UdxCfgReq kwUlUdxCfgReqMt[] =
{
#ifdef LCKWULUDX
   cmPkUdxCfgReq,            /* 0 - loosely coupled */
#else
   PtUlUdxCfgReq,            /* 0 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef LWLCKWULUDX
   cmPkUdxCfgReq,            /* 1 - loosely coupled */
#else
   PtUlUdxCfgReq,            /* 1 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef KW
   KwDlUdxCfgReq,            /* 2 - tightly coupled, RRC  */
#else
   PtUlUdxCfgReq,            /* 2 - tightly coupled, portable */
#endif /* KW */
};

PRIVATE UdxUeIdChgReq kwUlUdxUeIdChgReqMt[] =
{
#ifdef LCKWULUDX
   cmPkUdxUeIdChgReq,            /* 0 - loosely coupled */
#else
   PtUlUdxUeIdChgReq,            /* 0 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef LWLCKWULUDX
   cmPkUdxUeIdChgReq,            /* 1 - loosely coupled */
#else
   PtUlUdxUeIdChgReq,            /* 1 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef KW
   KwDlUdxUeIdChgReq,            /* 2 - tightly coupled, RRC  */
#else
   PtUlUdxUeIdChgReq,            /* 2 - tightly coupled, portable */
#endif /* KW */
};


PRIVATE CONSTANT UdxStaUpdReq kwUlUdxStaUpdReqMt[KW_MAX_UDX] =
{
#ifdef LCKWULUDX
   cmPkUdxStaUpdReq,            /* 0 - loosely coupled */
#else
   PtUlUdxStaUpdReq,            /* 0 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef LWLCKWULUDX
   cmPkUdxStaUpdReq,            /* 1 - loosely coupled */
#else
   PtUlUdxStaUpdReq,            /* 1 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef KW
   KwDlUdxStaUpdReq,            /* 2 - tightly coupled, RRC  */
#else
   PtUlUdxStaUpdReq,            /* 2 - tightly coupled, portable */
#endif /* KW */
};

PRIVATE CONSTANT UdxStaPduReq kwUlUdxStaPduReqMt[KW_MAX_UDX] =
{
#ifdef LCKWULUDX
   cmPkUdxStaPduReq,            /* 0 - loosely coupled */
#else
   PtUlUdxStaPduReq,            /* 0 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef LWLCKWULUDX
   cmPkUdxStaPduReq,            /* 1 - loosely coupled */
#else
   PtUlUdxStaPduReq,            /* 1 - loosely coupled, portable  */
#endif /* LCKWUIKWU */
#ifdef KW
   KwDlUdxStaPduReq,            /* 2 - tightly coupled, RRC  */
#else
   PtUlUdxStaPduReq,            /* 2 - tightly coupled, portable */
#endif /* KW */
};

/**
 *
 * @brief 
 *
 *        Handler for confirming  the bind request received from KWU
 *        interface.
 *
 * @b Description:
 *
 *        This function send the bind confirm primitive to the RLC user,
 *        when it receives a bind request from its service user.
 *
 *  @param[in] pst     Post structure  
 *  @param[in] suId    Service user SAP ID 
 *  @param[in] status  Status of Confirmation 
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 KwUlUdxBndReq
(
Pst *pst,                       /* post structure */
SuId suId,                      /* Service User Id */
SpId spId                     /* Status */
)
#else
PUBLIC S16 KwUlUdxBndReq(pst, suId, status)
Pst *pst;                       /* post structure */
SuId suId;                      /* Service User Id */
SpId spId;                    /* Status */
#endif
{
   TRC3(KwUlUdxBndReq)

   /* jump to specific primitive depending on configured selector */
   (*kwUlUdxBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);

} /* end of KwDlUdxBndReq */

/**
 *
 * @brief 
 *
 *        Handler for confirming  the bind request received from KWU
 *        interface.
 *
 * @b Description:
 *
 *        This function send the bind confirm primitive to the RLC user,
 *        when it receives a bind request from its service user.
 *
 *  @param[in] pst     Post structure  
 *  @param[in] suId    Service user SAP ID 
 *  @param[in] status  Status of Confirmation 
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 KwUlUdxUbndReq
(
Pst *pst,                       /* post structure */
SpId spId,                      /* Service User Id */
Reason   reason                     /* Status */
)
#else
PUBLIC S16 KwUlUdxUbndReq(pst, suId, status)
Pst *pst;                       /* post structure */
SpId spId;                      /* Service User Id */
Reason Reason;                    /* Status */
#endif
{
   TRC3(KwUlUdxUbndReq)

   /* jump to specific primitive depending on configured selector */
   (*kwUlUdxUbndReqMt[pst->selector])(pst, spId,reason );

   RETVALUE(ROK);

} /* end of KwDlUdxBndReq */

#ifdef ANSI
PUBLIC S16 KwUlUdxCfgReq
(
Pst *pst,                       /* post structure */
SpId spId,                      /* Service User Id */
UdxCfgInfo *cfmInfo             /* Config Info */
)
#else
PUBLIC S16 KwUlUdxCfgReq(pst, suId, status)
Pst *pst;                       /* post structure */
SuId spId;                      /* Service User Id */
UdxCfgInfo *cfmInfo;              /* Config Info */
#endif
{
   TRC3(KwUlUdxCfgReq)

   /* jump to specific primitive depending on configured selector */
   (*kwUlUdxCfgReqMt[pst->selector])(pst, spId, cfmInfo);

   RETVALUE(ROK);

} /* end of KwDlUdxCfgReq */

#ifdef ANSI
PUBLIC S16 KwUlUdxUeIdChgReq
(
Pst *pst,                      /* post structure */
SpId spId,                     /* Service User Id */
U32      transId,              /* transaction Id */
UdxUeInfo *ueInfo,             /* Config Info */
UdxUeInfo *newUeInfo           /* Config Info */
)
#else
PUBLIC S16 KwUlUdxUeIdChgReq(pst, spId,transId, ueInfo, newUeInfo)
Pst *pst;                      /* post structure */
SpId spId;                     /* Service User Id */
U32      transId;              /* transaction Id */
UdxUeInfo *ueInfo;             /* Config Info */
UdxUeInfo *newUeInfo;          /* Config Info */
#endif
{
   TRC3(KwUlUdxUeIdChgReq)

   /* jump to specific primitive depending on configured selector */
   (*kwUlUdxUeIdChgReqMt[pst->selector])(pst, spId,transId,ueInfo,newUeInfo);

   RETVALUE(ROK);

} /* end of KwDlUdxCfgReq */



PUBLIC S16  KwUlUdxStaPduReq
(
Pst*                pst,
SpId                spId,
CmLteRlcId          *rlcId,
KwUdxDlStaPdu       *pStaPdu
)
{
   TRC3(KwUlUdxStaPduReq);

   RETVALUE((*kwUlUdxStaPduReqMt[pst->selector])(pst,spId, rlcId, pStaPdu));
}

/**
* @brief Request from ULM to DLM for UE Status
*
* @details
*
*     Function : KwUdxUdxStatUpd
*
*  @param[in]   Pst*           pst

*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16  KwUlUdxStaUpdReq
(
Pst*                pst,
SpId                spId,
CmLteRlcId          *rlcId,
KwUdxStaPdu         *pStaPdu
)
#else
PUBLIC S16 KwUlUdxStaUpdReq(pst, rlcId, pStaPdu)
Pst*                pst;
SpId                spId;
CmLteRlcId          *rlcId;
KwUdxStaPdu         *pStaPdu;
#endif
{

   TRC3(KwUlUdxStaUpdReq);

   RETVALUE((*kwUlUdxStaUpdReqMt[pst->selector])(pst,spId, rlcId, pStaPdu));
} /* end of KwUlmDlmStaUpd*/

/**********************************************************************
 
         End of file:     kw_udx_ptul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:51 2014
 
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
/main/1      ---       mraj                1. LTE RLC Initial Release
*********************************************************************91*/

