
/********************************************************************20**

     Name:     SCTP Dummy Layer

     Type:     C source file

     Desc:     C source code for Dummy portable Upper Interface

     File:     szac_sctptui.c

     Sid:      szac_sctptui.c@@/main/2 - Mon Jan 10 22:15:58 2011

     Prg:      

*********************************************************************21*/


/* header include files (.h) */

/* header/extern include files (.x) */



/*

The following functions are provided in this file:


It should be noted that not all of these functions may be required
by a particular network layer service user.


*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm_err.h"        /* common error */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common transport defines */
#include "sct.h"           /* sct interface */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* common transport defines */
#include "cm5.x"           /* common timer */
#include "sct.x"           /* sct interface */



#define MAXDMUI 2          /* max SB Layer upper users */

#if ( (!defined(LCDMUISCT)) || (!defined(SZ)))
#define PTDMUISCT
#endif

/* local typedefs */

/* local externs */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef PTDMUISCT

/* declaration of portable functions */
PRIVATE S16 PtUiSctBndCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          SctResult      result));

PRIVATE S16 PtUiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

PRIVATE S16 PtUiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));


PRIVATE S16 PtUiSctAssocInd          ARGS((Pst               *pst,
                                           SuId               suId,
                                           UConnId            suEndpId,
                                           SctAssocIndParams *assocParams,
                                           Buffer            *vsInfo));

/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2
PRIVATE S16 PtUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo ));
#else /* SCT2 */
PRIVATE S16 PtUiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo ));
#endif /* SCT2 */

PRIVATE S16 PtUiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

PRIVATE S16 PtUiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

PRIVATE S16 PtUiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

PRIVATE S16 PtUiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

PRIVATE S16 PtUiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

#endif
PRIVATE S16 PtUiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));

#ifdef PTDMUISCT
PRIVATE S16 PtUiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));

PRIVATE S16 PtUiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));


#endif /* PTDMUISCT */

#ifdef __cplusplus
}
#endif /* __cplusplus */



/*
  The following matrices define the mapping between the primitives
  called by the upper interface of SCTP Layer
  and the corresponding primitives of the SCTP Layer
  service user(s).

  The dispatching is performed by the configurable variable: selector.
  The selector is configured on a per SAP basis.

  The selectors are:

  0 - loosely coupled (#define LCDMUISCT)
  2 - S1AP           (#define SZ)

*/



PRIVATE SctBndCfm DmUiSctBndCfmMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctBndCfm,         /* 0 - loosely coupled */
#else
   PtUiSctBndCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ
   SzLiSctBndCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctBndCfm,         /* 12 - tightly coupled, portable */
#endif
};


PRIVATE SctEndpOpenCfm DmUiSctEndpOpenCfmMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctEndpOpenCfm,         /* 0 - loosely coupled */
#else
   PtUiSctEndpOpenCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ
   SzLiSctEndpOpenCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctEndpOpenCfm,         /* 12 - tightly coupled, portable */
#endif
};

PRIVATE SctEndpCloseCfm DmUiSctEndpCloseCfmMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctEndpCloseCfm,         /* 0 - loosely coupled */
#else
   PtUiSctEndpCloseCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ
   SzLiSctEndpCloseCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctEndpCloseCfm,         /* 12 - tightly coupled, portable */
#endif
};

PRIVATE SctAssocInd DmUiSctAssocIndMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctAssocInd,         /* 0 - loosely coupled */
#else
   PtUiSctAssocInd,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ
   SzLiSctAssocInd,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctAssocInd,         /* 12 - tightly coupled, portable */
#endif
};

PRIVATE SctAssocCfm DmUiSctAssocCfmMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctAssocCfm,         /* 0 - loosely coupled */
#else
   PtUiSctAssocCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ
   SzLiSctAssocCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctAssocCfm,         /* 12 - tightly coupled, portable */
#endif
};

PRIVATE SctTermInd DmUiSctTermIndMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctTermInd,         /* 0 - loosely coupled */
#else
   PtUiSctTermInd,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ
   SzLiSctTermInd,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctTermInd,         /* 12 - tightly coupled, portable */
#endif
};

PRIVATE SctTermCfm DmUiSctTermCfmMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctTermCfm,         /* 0 - loosely coupled */
#else
   PtUiSctTermCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ
   SzLiSctTermCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctTermCfm,         /* 12 - tightly coupled, portable */
#endif
};

PRIVATE SctSetPriCfm DmUiSctSetPriCfmMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctSetPriCfm,         /* 0 - loosely coupled */
#else
   PtUiSctSetPriCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ_PHASE2
#ifdef SZ
   SzLiSctSetPriCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctSetPriCfm,         /* 12 - tightly coupled, portable */
#endif /* SZ */
#endif /* SZ_PHASE2 */
};

PRIVATE SctHBeatCfm DmUiSctHBeatCfmMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctHBeatCfm,         /* 0 - loosely coupled */
#else
   PtUiSctHBeatCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ_PHASE2
#ifdef SZ
   SzLiSctHBeatCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctHBeatCfm,         /* 12 - tightly coupled, portable */
#endif /* SZ */
#endif /* SZ_PHASE2 */
};

PRIVATE SctDatInd DmUiSctDatIndMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctDatInd,         /* 0 - loosely coupled */
#else
   PtUiSctDatInd,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ
   SzLiSctDatInd,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctDatInd,         /* 12 - tightly coupled, portable */
#endif
};

PRIVATE SctStaCfm DmUiSctStaCfmMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctStaCfm,         /* 0 - loosely coupled */
#else
   PtUiSctStaCfm,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ_PHASE2
#ifdef SZ
   SzLiSctStaCfm,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctStaCfm,         /* 12 - tightly coupled, portable */
#endif
#else
   PtUiSctStaCfm,         /* 12 - tightly coupled, portable */
#endif
};

PRIVATE SctStaInd DmUiSctStaIndMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctStaInd,         /* 0 - loosely coupled */
#else
   PtUiSctStaInd,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ
   SzLiSctStaInd,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctStaInd,         /* 12 - tightly coupled, portable */
#endif
};

PRIVATE SctFlcInd DmUiSctFlcIndMt[MAXDMUI] =
{
#ifdef LCDMUISCT
   cmPkSctFlcInd,         /* 0 - loosely coupled */
#else
   PtUiSctFlcInd,         /* 0 - tightly coupled, portable */
#endif
#ifdef SZ
   SzLiSctFlcInd,         /* 12 - tightly coupled, S1AP */
#else
   PtUiSctFlcInd,         /* 12 - tightly coupled, portable */
#endif /* SZ */
};

/*
 *  upper interface functions
 */




#ifdef ANSI
PUBLIC S16 DmUiSctBndCfm
(
Pst           *pst,
SuId           suId,
SctResult      result
)
#else
PUBLIC S16 DmUiSctBndCfm(pst, suId, result)
Pst           *pst;
SuId           suId;
SctResult      result;
#endif
{
   TRC3(DmUiSctBndCfm)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctBndCfmMt[pst->selector])(pst, suId, result);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 DmUiSctEndpOpenCfm
(
Pst           *pst,
SuId           suId,
UConnId        suEndpId,
UConnId        spEndpId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 DmUiSctEndpOpenCfm(pst, suId, suEndpId, spEndpId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suEndpId;
UConnId        spEndpId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(DmUiSctEndpOpenCfm)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctEndpOpenCfmMt[pst->selector])(pst, suId, suEndpId, spEndpId, 
             result, cause);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 DmUiSctEndpCloseCfm
(
Pst           *pst,
SuId           suId,
UConnId        suEndpId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 DmUiSctEndpCloseCfm(pst, suId, suEndpId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suEndpId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(DmUiSctEndpCloseCfm)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctEndpCloseCfmMt[pst->selector])(pst, suId, suEndpId, result, 
              cause);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 DmUiSctAssocInd
(
Pst               *pst,
SuId               suId,
UConnId            suEndpId,
SctAssocIndParams *assocParams,
Buffer            *vsInfo
)
#else
PUBLIC S16 DmUiSctAssocInd(pst, suId, suEndpId, assocParams, vsInfo)
Pst               *pst;
SuId               suId;
UConnId            suEndpId;
SctAssocIndParams *assocParams;
Buffer            *vsInfo;
#endif
{
   TRC3(DmUiSctAssocInd)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctAssocIndMt[pst->selector])(pst, suId, suEndpId, assocParams, 
             vsInfo);
         break;
   }

   RETVALUE(ROK);
}



/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2
#ifdef ANSI
PUBLIC S16 DmUiSctAssocCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
UConnId        spAssocId,
SctNetAddrLst *dstNAddrLst,
SctPort        dstPort,
SctStrmId      inStrms,
SctStrmId      outStrms,
Buffer        *vsInfo
)
#else
PUBLIC S16 DmUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, dstPort, inStrms, outStrms, vsInfo )
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
SctNetAddrLst *dstNAddrLst;
SctPort        dstPort;
SctStrmId      inStrms;
SctStrmId      outStrms;
Buffer        *vsInfo;
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 DmUiSctAssocCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
UConnId        spAssocId,
SctNetAddrLst *dstNAddrLst,
SctPort        dstPort,
SctStrmId      outStrms,
Buffer        *vsInfo
)
#else
PUBLIC S16 DmUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, dstPort, outStrms, vsInfo )
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
SctNetAddrLst *dstNAddrLst;
SctPort        dstPort;
SctStrmId      outStrms;
Buffer        *vsInfo;
#endif /* ANSI */
#endif /* SCT2  */
{
   TRC3(DmUiSctAssocCfm)

/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, inStrms, outStrms, vsInfo);
         break;
   }

#else /* SCT2 */

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctAssocCfmMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
              dstNAddrLst, dstPort, outStrms, vsInfo);
         break;
   }

#endif /* SCT2 */

   RETVALUE(ROK);
}




#ifdef ANSI
PUBLIC S16 DmUiSctTermInd
(
Pst           *pst,
SuId           suId,
UConnId        assocId,
U8             assocIdType,
SctStatus      status,
SctCause       cause,
SctRtrvInfo   *rtrvInfo
)
#else
PUBLIC S16 DmUiSctTermInd(pst, suId, assocId, assocIdType, status, cause, rtrvInfo)
Pst           *pst;
SuId           suId;
UConnId        assocId;
U8             assocIdType;
SctStatus      status;
SctCause       cause;
SctRtrvInfo   *rtrvInfo;
#endif
{
   TRC3(DmUiSctTermInd)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctTermIndMt[pst->selector])(pst, suId, assocId, assocIdType, 
             status, cause, rtrvInfo);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 DmUiSctTermCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 DmUiSctTermCfm(pst, suId, suAssocId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(DmUiSctTermCfm)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctTermCfmMt[pst->selector])(pst, suId, suAssocId, result, cause);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 DmUiSctSetPriCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 DmUiSctSetPriCfm(pst, suId, suAssocId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(DmUiSctSetPriCfm)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctSetPriCfmMt[pst->selector])(pst, suId, suAssocId, result,
             cause);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 DmUiSctHBeatCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
CmNetAddr     *dstNAddr,
SctStatus      status,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 DmUiSctHBeatCfm(pst, suId, suAssocId, dstNAddr, status, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
CmNetAddr     *dstNAddr;
SctStatus      status;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(DmUiSctHBeatCfm)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctHBeatCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr,
              status, result, cause);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 DmUiSctDatInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctStrmId      strmId,
SctDatIndType *indType,
U32            protId,
Buffer        *mBuf
)
#else
PUBLIC S16 DmUiSctDatInd(pst, suId, suAssocId, strmId, indType, protId, mBuf)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctStrmId      strmId;
SctDatIndType *indType;
U32            protId;
Buffer        *mBuf;
#endif
{
   TRC3(DmUiSctDatInd)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctDatIndMt[pst->selector])(pst, suId, suAssocId, strmId, 
             indType, protId, mBuf);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 DmUiSctStaCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
CmNetAddr     *dstNAddr,
SctResult      result,
SctCause       cause,
SctStaInfo    *staInfo
)
#else
PUBLIC S16 DmUiSctStaCfm(pst, suId, suAssocId, dstNAddr, result, cause, staInfo)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
CmNetAddr     *dstNAddr;
SctResult      result;
SctCause       cause;
SctStaInfo    *staInfo;
#endif
{
   TRC3(DmUiSctStaCfm)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctStaCfmMt[pst->selector])(pst, suId, suAssocId, dstNAddr, 
             result, cause, staInfo);
         break;
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 DmUiSctStaInd
(
 Pst           *pst,       /* post structure */
 SuId          suId,       /* service user SAP identifier */
 UConnId       suAssocId,  /* service user assoc identifier */
 UConnId       spAssocId,  /* service provider assoc identifier */
 CmNetAddr     *dstNAddr,  /* destination network address */
 SctStatus     status,
 SctCause      cause,
 Buffer        *mBuf       /* message buffer */
)
#else
PUBLIC S16 DmUiSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr,
                           status, cause, mBuf)
Pst            *pst;       /* post structure */
SuId           suId;       /* service user SAP identifier */
UConnId        suAssocId;  /* service user assoc identifier */
UConnId        spAssocId;  /* service provider assoc identifier */
CmNetAddr      *dstNAddr;  /* destination network address */
SctStatus      status;
SctCause       cause;
Buffer         *mBuf;       /* message buffer */
#endif
{
   TRC3(DmUiSctStaInd)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctStaIndMt[pst->selector])(pst, suId, suAssocId, spAssocId, 
             dstNAddr, status, cause, mBuf);
         break;
   }

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 DmUiSctFlcInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
Reason         reason
)
#else
PUBLIC S16 DmUiSctFlcInd(pst, suId, suAssocId, reason)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
Reason         reason;
#endif
{
   TRC3(DmUiSctFlcInd)

   switch (pst->dstEnt)
   {
      default:
         (*DmUiSctFlcIndMt[pst->selector])(pst, suId, suAssocId, reason);
         break;
   }

   RETVALUE(ROK);
}


/*
*     upper interface portable functions
*/

#ifdef PTDMUISCT


#ifdef ANSI
PUBLIC S16 PtUiSctBndCfm
(
Pst           *pst,
SuId           suId,
SctResult      result
)
#else
PUBLIC S16 PtUiSctBndCfm(pst, suId, result)
Pst           *pst;
SuId           suId;
SctResult      result;
#endif
{
   TRC3(PtUiSctBndCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(result);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 PtUiSctEndpOpenCfm
(
Pst           *pst,
SuId           suId,
UConnId        suEndpId,
UConnId        spEndpId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 PtUiSctEndpOpenCfm(pst, suId, suEndpId, spEndpId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suEndpId;
UConnId        spEndpId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(PtUiSctEndpOpenCfm)


   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suEndpId);
   UNUSED(spEndpId);
   UNUSED(result);
   UNUSED(cause);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 PtUiSctEndpCloseCfm
(
Pst           *pst,
SuId           suId,
UConnId        suEndpId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 PtUiSctEndpCloseCfm(pst, suId, suEndpId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suEndpId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(PtUiSctEndpCloseCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suEndpId);
   UNUSED(result);
   UNUSED(cause);

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 PtUiSctAssocInd
(
Pst               *pst,
SuId               suId,
UConnId            suEndpId,
SctAssocIndParams *assocParams,
Buffer            *vsInfo
)
#else
PUBLIC S16 PtUiSctAssocInd(pst, suId, suEndpId, assocParams, vsInfo)
Pst               *pst;
SuId               suId;
UConnId            suEndpId;
SctAssocIndParams *assocParams;
Buffer            *vsInfo;
#endif
{
   TRC3(PtUiSctAssocInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suEndpId);
   UNUSED(assocParams);
   UNUSED(vsInfo);

   RETVALUE(ROK);
}



/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2
#ifdef ANSI
PUBLIC S16 PtUiSctAssocCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
UConnId        spAssocId,
SctNetAddrLst *dstNAddrLst,
SctPort        dstPort,
SctStrmId      inStrms,
SctStrmId      outStrms,
Buffer        *vsInfo
)
#else
PUBLIC S16 PtUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst, 
                           dstPort, inStrms, outStrms, vsInfo)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
SctNetAddrLst *dstNAddrLst;
SctPort        dstPort;
SctStrmId      inStrms;
SctStrmId      outStrms;
Buffer        *vsInfo;
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 PtUiSctAssocCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
UConnId        spAssocId,
SctNetAddrLst *dstNAddrLst,
SctPort        dstPort,
SctStrmId      outStrms,
Buffer        *vsInfo
)
#else
PUBLIC S16 PtUiSctAssocCfm(pst, suId, suAssocId, spAssocId, dstNAddrLst,
                           dstPort, outStrms, vsInfo)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
SctNetAddrLst *dstNAddrLst;
SctPort        dstPort;
SctStrmId      outStrms;
Buffer        *vsInfo;
#endif /* ANSI */
#endif /* SCT2 */
{
   TRC3(PtUiSctAssocCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(spAssocId);
   UNUSED(dstNAddrLst);
   UNUSED(dstPort);
/* sb016.102 - Include in-stream parameter here */
#ifdef SCT2
   UNUSED(inStrms);
#endif /* SCT2 */
   UNUSED(outStrms);
   UNUSED(vsInfo);

   RETVALUE(ROK);
}




#ifdef ANSI
PUBLIC S16 PtUiSctTermInd
(
Pst           *pst,
SuId           suId,
UConnId        assocId,
U8             assocIdType,
SctStatus      status,
SctCause       cause,
SctRtrvInfo   *rtrvInfo
)
#else
PUBLIC S16 PtUiSctTermInd(pst, suId, assocId, assocIdType, status, cause,
                          rtrvInfo)
Pst           *pst;
SuId           suId;
UConnId        assocId;
U8             assocIdType;
SctStatus      status;
SctCause       cause;
SctRtrvInfo   *rtrvInfo;
#endif
{
   TRC3(PtUiSctTermInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(assocId);
   UNUSED(assocIdType);
   UNUSED(status);
   UNUSED(cause);
   UNUSED(rtrvInfo);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 PtUiSctTermCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 PtUiSctTermCfm(pst, suId, suAssocId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(PtUiSctTermCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(result);
   UNUSED(cause);

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 PtUiSctSetPriCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 PtUiSctSetPriCfm(pst, suId, suAssocId, result, cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(PtUiSctSetPriCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(result);
   UNUSED(cause);

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 PtUiSctHBeatCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
CmNetAddr     *dstNAddr,
SctStatus      status,
SctResult      result,
SctCause       cause
)
#else
PUBLIC S16 PtUiSctHBeatCfm(pst, suId, suAssocId, dstNAddr, status, result,
                           cause)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
CmNetAddr     *dstNAddr;
SctStatus      status;
SctResult      result;
SctCause       cause;
#endif
{
   TRC3(PtUiSctHBeatCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(dstNAddr);
   UNUSED(status);
   UNUSED(result);
   UNUSED(cause);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 PtUiSctDatInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
SctStrmId      strmId,
SctDatIndType *indType,
U32            protId,
Buffer        *mBuf
)
#else
PUBLIC S16 PtUiSctDatInd(pst, suId, suAssocId, strmId, indType, protId, mBuf)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
SctStrmId      strmId;
SctDatIndType *indType;
U32            protId;
Buffer        *mBuf;
#endif
{
   TRC3(PtUiSctDatInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(strmId);
   UNUSED(indType);
   UNUSED(protId);
   UNUSED(mBuf);

   RETVALUE(ROK);
}


#endif

#ifdef ANSI
PUBLIC S16 PtUiSctStaCfm
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
CmNetAddr     *dstNAddr,
SctResult      result,
SctCause       cause,
SctStaInfo    *staInfo
)
#else
PUBLIC S16 PtUiSctStaCfm(pst, suId, suAssocId, dstNAddr, result,
                         cause, staInfo)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
CmNetAddr     *dstNAddr;
SctResult      result;
SctCause       cause;
SctStaInfo    *staInfo;
#endif
{
   TRC3(PtUiSctStaCfm)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(dstNAddr);
   UNUSED(result);
   UNUSED(cause);
   UNUSED(staInfo);

   RETVALUE(ROK);
}


#ifdef PTDMUISCT

#ifdef ANSI
PUBLIC S16 PtUiSctStaInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
UConnId        spAssocId,
CmNetAddr     *dstNAddr,
SctStatus      status,
SctCause       cause,
Buffer        *mBuf
)
#else
PUBLIC S16 PtUiSctStaInd(pst, suId, suAssocId, spAssocId, dstNAddr, status,
                         cause, mBuf)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
UConnId        spAssocId;
CmNetAddr     *dstNAddr;
SctStatus      status;
SctCause       cause;
Buffer        *mBuf;
#endif
{
   TRC3(PtUiSctStaInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(spAssocId);
   UNUSED(dstNAddr);
   UNUSED(status);
   UNUSED(cause);
   UNUSED(mBuf);

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 PtUiSctFlcInd
(
Pst           *pst,
SuId           suId,
UConnId        suAssocId,
Reason         reason
)
#else
PUBLIC S16 PtUiSctFlcInd(pst, suId, suAssocId, reason)
Pst           *pst;
SuId           suId;
UConnId        suAssocId;
Reason         reason;
#endif
{
   TRC3(PtUiSctFlcInd)

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(suAssocId);
   UNUSED(reason);

   RETVALUE(ROK);
}

#endif /* PTDMUISCT */


/********************************************************************30**

         End of file:     szac_sctptui.c@@/main/2 - Mon Jan 10 22:15:58 2011

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************70**

  version    initials                   description
-----------  ---------  ------------------------------------------------

*********************************************************************71*/

/********************************************************************80**

*********************************************************************81*/
/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/2      ---      vvashishth  1. Updated for S1AP release 3.1
*********************************************************************91*/
