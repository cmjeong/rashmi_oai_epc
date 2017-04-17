

/********************************************************************20**
  
        Name:    RLC service user (PDCP) lower interface
    
        Type:    C file
  
        Desc:    This file Contains the RLC service user lower interface
                  primitive implementain
 
        File:    kwac_pj_ptli.c

        Sid:      kwac_px_ptli.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:40 2014
  
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
#include "pju.h"           /* PJU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_ckw.h"      /* CKW Acceptance defines */
#include "kwac_kwu.h"      /* CKW Acceptance defines */
#include "kwac_pju.h"      /* CKW Acceptance defines */

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
#include "pju.x"           /* PJU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_ckw.x"      /* CKW Acceptance defines */
#include "kwac_kwu.x"      /* CKW Acceptance defines */
#include "kwac_pju.x"      /* CKW Acceptance defines */


#ifdef KW_PDCP

EXTERN S16 PtLiPjuBndReq ARGS ((
Pst* pst,
SpId spId,
SuId suId
));

EXTERN S16 PtLiPjuUbndReq ARGS ((
Pst* pst,
SpId spId,
Reason reason
));

EXTERN S16 PtLiPjuDatReq ARGS ((
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuSduId sduId,
Buffer * mBuf
));

EXTERN S16 PtLiPjuDatFwdReq ARGS ((
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuDatFwdReqInfo * datFwdReq
));


/************************************************************************
                             PJU Interface Matrices
************************************************************************/
PRIVATE CONSTANT PjuBndReq PxLiPjuBndReqMt[] =
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


PRIVATE CONSTANT PjuUbndReq PxLiPjuUbndReqMt[] =
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


PRIVATE CONSTANT PjuDatReq PxLiPjuDatReqMt[] =
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


PRIVATE CONSTANT PjuDatFwdReq PxLiPjuDatFwdReqMt[] =
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
#ifdef PX
#ifdef ANSI
PUBLIC S16 PxLiPjuBndReq
(
Pst* pst,
SpId spId,
SuId suId
)
#else
PUBLIC S16 PxLiPjuBndReq(pst, spId, suId)
Pst* pst;
SpId spId;
SuId suId;
#endif
{

   TRC3(PxLiPjuBndReq)

   (*PxLiPjuBndReqMt[pst->selector])(pst, spId, suId);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PxLiPjuUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 PxLiPjuUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(PxLiPjuUbndReq)

   (*PxLiPjuUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PxLiPjuDatReq
(
Pst* pst,
SpId spId,
CmLtePdcpId *pdcpId,
PjuSduId sduId,
Buffer *mBuf
)
#else
PUBLIC S16 PxLiPjuDatReq(pst, spId, pdcpId, sduId, mBuf)
Pst* pst;
SpId spId;
CmLtePdcpId *pdcpId;
PjuSduId sduId;
Buffer *mBuf;
#endif
{

   TRC3(PxLiPjuDatReq)

   (*PxLiPjuDatReqMt[pst->selector])(pst, spId, pdcpId, sduId, mBuf);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PxLiPjuDatFwdReq
(
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuDatFwdReqInfo * datFwdReq
)
#else
PUBLIC S16 PxLiPjuDatFwdReq(pst, spId, pdcpId, datFwdReq)
Pst* pst;
SpId spId;
CmLtePdcpId * pdcpId;
PjuDatFwdReqInfo * datFwdReq;
#endif
{

   TRC3(PxLiPjuDatFwdReq)

   (*PxLiPjuDatFwdReqMt[pst->selector])(pst, spId, pdcpId, datFwdReq);

   RETVALUE(ROK);

}
#endif /*--ifdef PX--*/

  
/****************************************************************************
 *                         Porting Functions
 ***************************************************************************/
#ifdef ANSI
PUBLIC S16 PtLiPjuBndReq
(
Pst* pst,
SpId spId,
SuId suId
)
#else
PUBLIC S16 PtLiPjuBndReq(pst, spId, suId)
Pst* pst;
SpId spId;
SuId suId;
#endif
{

   TRC3(PtLiPjuBndReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(suId);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiPjuUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 PtLiPjuUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{

   TRC3(PtLiPjuUbndReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(reason);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiPjuDatReq
(
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuSduId sduId,
Buffer * mBuf
)
#else
PUBLIC S16 PtLiPjuDatReq(pst, spId, pdcpId, sduId, mBuf)
Pst* pst;
SpId spId;
CmLtePdcpId * pdcpId;
PjuSduId sduId;
Buffer * mBuf;
#endif
{

   TRC3(PtLiPjuDatReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(pdcpId);
   UNUSED(sduId);
   UNUSED(mBuf);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtLiPjuDatFwdReq
(
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuDatFwdReqInfo * datFwdReq
)
#else
PUBLIC S16 PtLiPjuDatFwdReq(pst, spId, pdcpId, datFwdReq)
Pst* pst;
SpId spId;
CmLtePdcpId * pdcpId;
PjuDatFwdReqInfo * datFwdReq;
#endif
{

   TRC3(PtLiPjuDatFwdReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(pdcpId);
   UNUSED(datFwdReq);

   RETVALUE(ROK);

}

#endif /* KW_PDCP */
  
/********************************************************************30**
         End of file:     kwac_px_ptli.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:40 2014
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
/main/1      ---   gk         1. Initial Release.
*********************************************************************91*/

