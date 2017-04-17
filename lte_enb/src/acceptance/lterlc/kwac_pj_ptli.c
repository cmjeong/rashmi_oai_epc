

/********************************************************************20**
  
        Name:    RLC service user (PDCP) lower interface
    
        Type:    C file
  
        Desc:    This file Contains the RLC service user lower interface
                  primitive implementain
 
        File:    kwac_pj_ptli.c

        Sid:      kwac_pj_ptli.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:37 2014
  
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

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_ckw.h"      /* CKW Acceptance defines */
#include "kwac_kwu.h"      /* CKW Acceptance defines */

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

#ifndef KW_PDCP

/************************************************************************
                             KWU Interface Matrices
************************************************************************/

PUBLIC KwuBndReq pjLiKwuBndReqMt [] =
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

PUBLIC KwuUbndReq pjLiKwuUbndReqMt [] =
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

PUBLIC KwuDatReq pjLiKwuDatReqMt [] =
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

PUBLIC KwuDiscSduReq pjLiKwuDiscSduReqMt [] =
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


/****************************************************************************
 *                         KWU Interface Mt functions
 ***************************************************************************/
/**
 *
 * @brief 
 *
 *        PjLiKwuBndReq - KWU SAP bind Request
 *
 *  @param[in] pst   - Post structure  
 *  @param[in] suId  - Service user SAP ID 
 *  @param[in] spId  - Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 PjLiKwuBndReq
(
Pst *pst,                       /* post structure */
SuId suId,                      /* Service User Id */
SpId spId                       /* Service Provider Id */
)
#else
PUBLIC S16 PjLiKwuBndReq(pst, suId, spId)
Pst *pst;                       /* post structure */
SuId suId;                      /* Service User Id */
SpId spId;                      /* Service Provider Id */
#endif
{
   TRC3(PjLiKwuBndReq)

   /* jump to specific primitive depending on configured selector */
   (*pjLiKwuBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);

} /* end of PjLiKwuBndReq */


/**
 *
 * @brief 
 *
 *        PjLiKwuUbndReq - KWU SAP unbind Request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] spId    - Service provider SAP ID 
 *  @param[in] reason  - Reason
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 PjLiKwuUbndReq
(
Pst         *pst,
SpId        spId,
Reason      reason
)
#else
PUBLIC S16 PjLiKwuUbndReq(pst, spId, reason)
Pst         *pst;
SpId        spId;
Reason      reason;
#endif
{
   TRC3(PjLiKwuUbndReq)

   /* jump to specific primitive depending on configured selector */
   (*pjLiKwuUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);

} /* end of PjLiKwuUbndReq */


/**
 *
 * @brief 
 *
 *        PjLiKwuDatReq - KWU Data Request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] spId    - Service provider SAP ID 
 *  @param[in] datReq  - Data Request
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 PjLiKwuDatReq
(
Pst            *pst,
SpId           spId,
KwuDatReqInfo  *datReq,
Buffer         *mBuf
)
#else
PUBLIC S16 PjLiKwuDatReq(pst, spId, datReq, mBuf)
Pst            *pst;
SpId           spId;
KwuDatReqInfo  *datReq;
Buffer         *mBuf;
#endif
{
   TRC3(PjLiKwuDatReq)

   /* jump to specific primitive depending on configured selector */
   (*pjLiKwuDatReqMt[pst->selector])(pst, spId, datReq, mBuf);

   RETVALUE(ROK);

} /* end of PjLiKwuDatReq */


/**
 *
 * @brief 
 *
 *        PjLiKwuDiscSduReq - KWU Discard SDU Request
 *
 *  @param[in] pst     - Post structure  
 *  @param[in] spId    - Service provider SAP ID 
 *  @param[in] datReq  - Data Request
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 PjLiKwuDiscSduReq
(
Pst               *pst,
SpId              spId,
KwuDiscSduInfo    *discSdu
)
#else
PUBLIC S16 PjLiKwuDiscSduReq(pst, spId, discSdu)
Pst               *pst;
SpId              spId;
KwuDiscSduInfo    *discSdu;
#endif
{
   TRC3(PjLiKwuDiscSduReq)

   /* jump to specific primitive depending on configured selector */
   (*pjLiKwuDiscSduReqMt[pst->selector])(pst, spId, discSdu);

   RETVALUE(ROK);

} /* end of PjLiKwuDiscSduReq */
#endif /* KW_PDCP */

/****************************************************************************
 *                         Porting Functions
 ***************************************************************************/
/* Porting functions are defined in kwac_pj_ptli.c */
  
/********************************************************************30**
         End of file:     kwac_pj_ptli.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:37 2014
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
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
*********************************************************************91*/

