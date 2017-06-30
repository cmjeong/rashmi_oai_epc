

/********************************************************************20**
  
        Name:    PDCP service user lower interface
    
        Type:    C file
  
        Desc:    TKWs file Contains the RLC service user lower interface
                  primitive implementain
 
        File:    pjac_nh_ptli.c

        Sid:      pjac_nh_ptli.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:04 2015
  
        Prg:     Adarsh
  
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
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */
#include "pj_err.h"        /* Error defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_kwu.h"      /* CKW Acceptance defines */
#include "pjac_pju.h"      /* CKW Acceptance defines */

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
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_kwu.x"      /* CKW Acceptance defines */

#include "pjac_pju.x"      /* CKW Acceptance defines */


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

EXTERN S16 PtLiCpjDatResumeReq ARGS((Pst * pst, SpId spId, CpjDatResumeReqInfo * datResumeReq));

EXTERN S16 PtLiCpjDatForwardReq ARGS((Pst * pst, SpId spId, CpjDataFwdReqInfo * datForwardReq));
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


PRIVATE CONSTANT CpjDatResumeReq NhLiCpjDatResumeReqMt[] =
{
#ifdef LCPJUICPJ
   cmPkCpjDatResumeReq,
#else
   PtLiCpjDatResumeReq,
#endif
#ifdef PJ
   PjUiCpjDatResumeReq,
#else
   PtLiCpjDatResumeReq,
#endif
};

PRIVATE CONSTANT CpjDataFwdReq NhLiCpjDatForwardReqMt[] =
{
#ifdef LCPJUICPJ
   cmPkCpjStartDataFwdReq, 
#else
   PtLiCpjDatForwardReq,
#endif
#ifdef PJ
   PjUiCpjDatForwardReq,
#else
   PtLiCpjDatForwardReq,
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


#ifdef ANSI
PUBLIC S16 NhLiCpjDatResumeReq
(
Pst * pst,
SpId spId,
CpjDatResumeReqInfo * datResumeReq
)
#else
PUBLIC S16 NhLiCpjDatResumeReq(pst, spId, datResumeReq)
Pst * pst;
SpId spId;
CpjDatResumeReqInfo * datResumeReq;
#endif
{

   TRC3(NhLiCpjDatResumeReq)

   (*NhLiCpjDatResumeReqMt[pst->selector])(pst, spId, datResumeReq);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 NhLiCpjDatForwardReq
(
Pst * pst,
SpId spId,
CpjDataFwdReqInfo * datForwardReq
)
#else
PUBLIC S16 NhLiCpjDatForwardReq(pst, spId, datForwardReq)
Pst * pst;
SpId spId;
CpjDataFwdReqInfo * datForwardReq;
#endif
{

   TRC3(NhLiCpjDatForwardReq)

   (*NhLiCpjDatForwardReqMt[pst->selector])(pst, spId, datForwardReq);

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


#ifdef ANSI
PUBLIC S16 PtLiCpjDatResumeReq
(
Pst * pst,
SpId spId,
CpjDatResumeInfo * datResumeReq
)
#else
PUBLIC S16 PtLiCpjDatResumeReq(pst, spId, datResumeReq)
Pst * pst;
SpId spId;
CpjDatResumeInfo * datResumeReq;
#endif
{

   TRC3(PtLiCpjDatResumeReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(datResumeReq);

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 PtLiCpjDatForwardReq
(
Pst * pst,
SpId spId,
CpjDataFwdReqInfo *datForwardReq
)
#else
PUBLIC S16 PtLiCpjDatForwardReq(pst, spId, datForwardReq)
Pst * pst;
SpId spId;
CpjDataFwdReqInfo * datForwardReq;
#endif
{

   TRC3(PtLiCpjDatForwardReq)

   UNUSED(pst);
   UNUSED(spId);
   UNUSED(datForwardReq);

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
/* kw006.201 ccpu00120534, fixed the problem of passing suId and spId as argument */
#ifdef ANSI
PUBLIC S16 NhLiPjuBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 NhLiPjuBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{

   TRC3(NhLiPjuBndReq)

   (*NhLiPjuBndReqMt[pst->selector])(pst, suId, spId);

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


/********************************************************************30**
         End of file:     pjac_nh_ptli.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:04 2015
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
/main/1      ---       vb        1. LTE PDCP Initial release 2.1
*********************************************************************91*/
