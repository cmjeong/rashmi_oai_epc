

/********************************************************************20**
  
        Name:    PDCP service user (RLC) lower interface
    
        Type:    C file
  
        Desc:    This file Contains the PDCP service user lower interface
                  primitive implementation
 
        File:    pjac_lib_ptli.c

        Sid:      pjac_lib_ptli.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:55 2015
  
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
#include "kwu.h"           /* KWU defines */
#include "pju.h"           /* PJU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_lib.h"      /* Acceptance defines */
#include "pjac_acc.h"      /* Acceptance defines */

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
#include "kwu.x"           /* KWU */
#include "pju.x"           /* PJU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"
#include "pj_lib.x"     /* LIB */

#include "cm_xta.x"
#include "pjac_lib.x"      /* Acceptance defines */
#include "pjac_acc.x"      /* Acceptance defines */

#ifdef PJ_CMP_ASYNC
/************************************************************************
                             PJU Interface Matrices
************************************************************************/

/****************************************************************************
 *                         PJU Interface Mt functions
 ***************************************************************************/

#ifdef ANSI
PUBLIC S16 PjLibObdCmpInitReq
(
Pst * pst,
PjCmpCxt cmpCxt,
PjRohc rohc
)
#else
PUBLIC S16 PjLibObdCmpInitReq(pst, cmpCxt, rohc)
Pst * pst;
PjCmpCxt cmpCxt;
PjRohc rohc;
#endif
{

   TRC3(PjLibObdCmpInitReq)

   cmPkLibObdCmpInitReq(pst, cmpCxt, rohc);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdCmpReq
(
Pst * pst,
PTR cmpCxtId,
PjLibTrans libTrans,
Buffer * mBuf
)
#else
PUBLIC S16 PjLibObdCmpReq(pst, cmpCxtId, libTrans, mBuf)
Pst * pst;
PTR cmpCxtId;
PjLibTrans libTrans;
Buffer * mBuf;
#endif
{

   TRC3(PjLibObdCmpReq)

   cmPkLibObdCmpReq(pst, cmpCxtId, libTrans, mBuf);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdDecmpReq
(
Pst * pst,
PTR cmpCxtId,
PjLibTrans libTrans,
Buffer * mBuf
)
#else
PUBLIC S16 PjLibObdDecmpReq(pst, cmpCxtId, libTrans, mBuf)
Pst * pst;
PTR cmpCxtId;
PjLibTrans libTrans;
Buffer * mBuf;
#endif
{

   TRC3(PjLibObdDecmpReq)

   cmPkLibObdDecmpReq(pst, cmpCxtId, libTrans, mBuf);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdCmpCloseReq
(
Pst * pst,
PTR cmpCxtId
)
#else
PUBLIC S16 PjLibObdCmpCloseReq(pst, cmpCxtId)
Pst * pst;
PTR cmpCxtId;
#endif
{

   TRC3(PjLibObdCmpCloseReq)

   cmPkLibObdCmpCloseReq(pst, cmpCxtId);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdCmpResetReq
(
Pst * pst,
PTR cmpCxtId
)
#else
PUBLIC S16 PjLibObdCmpResetReq(pst, cmpCxtId)
Pst * pst;
PTR cmpCxtId;
#endif
{

   TRC3(PjLibObdCmpResetReq)

   cmPkLibObdCmpResetReq(pst, cmpCxtId);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdCmpFbReq
(
Pst * pst,
PTR cmpCxtId,
PjLibTrans libTrans,
Buffer *feedback
)
#else
PUBLIC S16 PjLibObdCmpFbReq(pst, cmpCxtId, libTrans, feedback)
Pst * pst;
PTR cmpCxtId;
PjLibTrans libTrans;
Buffer *feedback;
#endif
{

   TRC3(PjLibObdCmpFbReq)

   cmPkLibObdCmpFbReq(pst, cmpCxtId, libTrans, feedback);

   RETVALUE(ROK);

}
#endif /* PJ_CMP_ASYNC */

#ifdef PJ_SEC_ASYNC

#ifdef ANSI
PUBLIC S16 PjLibObdIntInitReq
(
Pst * pst,
PjSecCxt secCtx,
PjIntInfo intInfo
)
#else
PUBLIC S16 PjLibObdIntInitReq(pst, secCtx, intInfo)
Pst * pst;
PjSecCxt secCtx;
PjIntInfo intInfo;
#endif
{

   TRC3(PjLibObdIntInitReq)

   cmPkLibObdIntInitReq(pst, secCtx, intInfo);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdIntProtReq
(
Pst * pst,
PTR intCxtId,
PjSecInp secInp,
PjLibTrans libTrans,
Buffer **mBuf
)
#else
PUBLIC S16 PjLibObdIntProtReq(pst, intCxtId, secInp, libTrans, mBuf)
Pst * pst;
PTR intCxtId;
PjSecInp secInp;
PjLibTrans libTrans;
Buffer ** mBuf;
#endif
{

   TRC3(PjLibObdIntProtReq)

   cmPkLibObdIntProtReq(pst, intCxtId, secInp, libTrans, *mBuf);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdIntVerReq
(
Pst * pst,
PTR intCxtId,
PjSecInp secInp,
PjLibTrans libTrans,
Buffer * mBuf,
U32   macI
)
#else
PUBLIC S16 PjLibObdIntVerReq(pst, intCxtId, secInp, libTrans, mBuf, macI)
Pst * pst;
PTR intCxtId;
PjSecInp secInp;
PjLibTrans libTrans;
Buffer * mBuf;
U32   macI;
#endif
{

   TRC3(PjLibObdIntVerReq)

   cmPkLibObdIntVerReq(pst, intCxtId, secInp, libTrans, mBuf, macI);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdIntCloseReq
(
Pst * pst,
PTR intCxtId
)
#else
PUBLIC S16 PjLibObdIntCloseReq(pst, intCxtId)
Pst * pst;
PTR intCxtId;
#endif
{

   TRC3(PjLibObdIntCloseReq)

   cmPkLibObdIntCloseReq(pst, intCxtId);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdCpInitReq
(
Pst * pst,
PjSecCxt secCxt,
U8 algoType,
U8 *cpKey
)
#else
PUBLIC S16 PjLibObdCpInitReq(pst, secCxt, algoType, cpKey)
Pst * pst;
PjSecCxt secCxt;
U8 algoType;
U8 *cpKey;
#endif
{

   TRC3(PjLibObdCpInitReq)

   cmPkLibObdCpInitReq(pst, secCxt, algoType, cpKey);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PjLibObdUpInitReq
(
Pst * pst,
PjSecCxt secCxt,
U8 algoType,
U8 *upKey
)
#else
PUBLIC S16 PjLibObdUpInitReq(pst, secCxt, algoType, upKey)
Pst * pst;
PjSecCxt secCxt;
U8 algoType;
U8 *upKey;
#endif
{

   TRC3(PjLibObdUpInitReq)

   cmPkLibObdUpInitReq(pst, secCxt, algoType, upKey);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdCipherReq
(
Pst * pst,
PTR cxtId,
PjSecInp secInp,
PjLibTrans libTrans,
Buffer * mBuf
)
#else
PUBLIC S16 PjLibObdCipherReq(pst, cxtId, secInp, libTrans, mBuf)
Pst * pst;
PTR cxtId;
PjSecInp secInp;
PjLibTrans libTrans;
Buffer * mBuf;
#endif
{

   TRC3(PjLibObdCipherReq)

   cmPkLibObdCipherReq(pst, cxtId, secInp, libTrans, mBuf);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PjLibObdDecipherReq
(
Pst * pst,
PTR cxtId,
PjSecInp secInp,
PjLibTrans libTrans,
Buffer * mBuf
)
#else
PUBLIC S16 PjLibObdDecipherReq(pst, cxtId, secInp, libTrans, mBuf)
Pst * pst;
PTR cxtId;
PjSecInp secInp;
PjLibTrans libTrans;
Buffer * mBuf;
#endif
{

   TRC3(PjLibObdDecipherReq)

   cmPkLibObdDecipherReq(pst, cxtId, secInp, libTrans, mBuf);

   RETVALUE(ROK);

}

#ifdef ANSI
PUBLIC S16 PjLibObdCipherCloseReq
(
Pst * pst,
PTR cpCxtId
)
#else
PUBLIC S16 PjLibObdCipherCloseReq(pst, cpCxtId)
Pst * pst;
PTR cpCxtId;
#endif
{

   TRC3(PjLibObdCipherCloseReq)

   cmPkLibObdCipherCloseReq(pst, cpCxtId);

   RETVALUE(ROK);

}

#endif /*--ifdef PJ_SEC_ASYNC--*/
/********************************************************************30**
         End of file:     pjac_lib_ptli.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:55 2015
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
/main/1      ---      av        1. LTE PDCP Initial Release 2.1
*********************************************************************91*/

