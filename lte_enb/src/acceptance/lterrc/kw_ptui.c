

/**********************************************************************

     Name:     LTE-RRC Layer 
  
     Type:     C Source file
  
     Desc:     Code for LTE RLC Upper interface outgoing 
               primitives towards LTE RRC(NH)

     File:     kw_ptui.c

     Sid:      kw_ptui.c@@/main/2 - Fri Dec 11 18:48:05 2009

     Prg:      rcs 

**********************************************************************/

/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_lte.h"        /* Common LTE Defines */
#include "lnh.h"           /* LNH Interface defines */
#include "kwu.h"           /* KWU Interface defines */
#include "ckw.h"           /* CKW Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_lib.x"        /* Common library definitions */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE includes */
#include "lnh.x"           /* LNH Interface includes */
#include "kwu.x"           /* KWU Interface includes */
#include "ckw.x"           /* CKW Interface includes */

/* local defines */
#define MAXKWUI   3        /* size of Matrix used for LC/TC */

/* local typedefs */

/* local externs */

/* forward references */

#if (!(defined(LCKWUIKWU)))
#define PTKWUIKWU    1        /* Portable KWU Interface */
#else
#ifndef NH                    /* NH - RRC */
#define PTKWUIKWU    1        /* Portable KWU Interface */
#endif /* NH */
#endif /*(!(defined(LCKWUIKWU) )) */

#if (!(defined(LCKWUICKW)))
#define PTKWUICKW    1        /* Portable CKW Interface */
#else
#ifndef NH                    /* NH - RRC */
#define PTKWUICKW    1        /* Portable CKW Interface */
#endif /* NH */
#endif /*(!(defined(LCKWUICKW) )) */

/* Prototypes of Portable Functions */
#ifdef PTKWUIKWU
PRIVATE S16 PtUiKwuBndCfm ARGS((Pst *pst, SuId suId, U8 status));
PRIVATE S16 PtUiKwuDatInd ARGS((Pst *pst, SuId suId, KwuDatIndInfo *datInd,
                                Buffer *buf));
#endif /* PTKWUIKWU */

#ifdef PTKWUICKW
PRIVATE S16 PtUiCkwBndCfm ARGS((Pst *pst, SuId suId, U8 status));
PRIVATE S16 PtUiCkwCfgCfm ARGS((Pst *pst, SuId suId, CkwCfgCfmInfo *cfgCfm));
PRIVATE S16 PtUiCkwUeIdChgCfm ARGS((Pst *pst, SuId suId, U32 transId, CkwUeInfo
         *ueInfo, CmStatus status));
#endif /* PTKWUICKW */

/* KWU Primitives */

/* Bind Confirm Primitive */
PRIVATE CONSTANT KwuBndCfm KwUiKwuBndCfmMt [MAXKWUI] =
{
#ifdef LCKWUIKWU
   cmPkKwuBndCfm,       /* 0 - loosely coupled */
#else
   PtUiKwuBndCfm,       /* 0 - loosely coupled, portable */
#endif /* LCKWUIKWU */
#ifdef NH
   NhLiKwuBndCfm,       /* 1 - tight coupled, NH */
#else
   PtUiKwuBndCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/* Data Indication Primitive */
PRIVATE CONSTANT KwuDatInd KwUiKwuDatIndMt [MAXKWUI] =
{
#ifdef LCKWUIKWU
   cmPkKwuDatInd,       /* 0 - loosely coupled */
#else
   PtUiKwuDatInd,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiKwuDatInd,       /* 1 - tight coupled, NH */
#else
   PtUiKwuDatInd,       /* 1 - tight coupled, portable */
#endif /* NH */
};


/* CKW Primitives */

/* Cell Configuration Primitive */
PRIVATE CONSTANT CkwCfgCfm KwUiCkwCfgCfmMt [MAXKWUI] =
{
#ifdef LCKWUICKW
   cmPkCkwCfgCfm,       /* 0 - loosely coupled */
#else
   PtUiCkwCfgCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCkwCfgCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCkwCfgCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/* Cell Configuration Primitive */
PRIVATE CONSTANT CkwUeIdChgCfm KwUiCkwUeIdChgCfmMt [MAXKWUI] =
{
#ifdef LCKWUICKW
   cmPkCkwUeIdChgCfm,       /* 0 - loosely coupled */
#else
   PtUiCkwUeIdChgCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCkwUeIdChgCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCkwUeIdChgCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};
/* Bind Confirm Primitive */
PRIVATE CONSTANT CkwBndCfm KwUiCkwBndCfmMt [MAXKWUI] =
{
#ifdef LCKWUICKW
   cmPkCkwBndCfm,       /* 0 - loosely coupled */
#else
   PtUiCkwBndCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCkwBndCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCkwBndCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/**************************************************************************
 * LTE RLC Upper interface primitives
 *************************************************************************/
/**************************************************************************
 *
 *      Fun:   KwUiKwuBndCfm
 *
 *      Desc:  RLC Bind Confirm to RRC for RLC Data Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  kw_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 KwUiKwuBndCfm
(
Pst *pst,               /* post structure */
SuId suId,              /* service user identifier */
U8 status               /* status */
)
#else
PUBLIC S16 KwUiKwuBndCfm (pst, suId, status)
Pst *pst;               /* post structure */
SuId suId;              /* service user identifier */
U8 status;              /* status */
#endif
{
   TRC3(KwUiKwuBndCfm);

   RETVALUE((*KwUiKwuBndCfmMt[pst->selector])(pst, suId, status));
} /* end of KwUiKwuBndCfm */

/**************************************************************************
 *
 *      Fun:   KwUiKwuDatInd
 *
 *      Desc:  Data Indication to RRC 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  kw_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 KwUiKwuDatInd
(
Pst *pst, 
SuId suId,
KwuDatIndInfo *datInd,
Buffer *buf
)
#else
PUBLIC S16 KwUiKwuDatInd (pst, suId, datInd, buf)
Pst *pst;
SuId suId;
KwuDatIndInfo *datInd;
Buffer *buf;
#endif
{
   TRC3(KwUiKwuDatInd);

   RETVALUE((*KwUiKwuDatIndMt[pst->selector])(pst, suId, datInd, buf));
} /* end of KwUiKwuDatInd */

/**************************************************************************
 *
 *      Fun:   KwUiCkwBndCfm
 *
 *      Desc:  RLC Bind Confirm to RRC for RLC Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  kw_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 KwUiCkwBndCfm
(
Pst *pst,               /* post structure */
SuId suId,              /* service user identifier */
U8 status               /* status */
)
#else
PUBLIC S16 KwUiCkwBndCfm (pst, suId, status)
Pst *pst;               /* post structure */
SuId suId;              /* service user identifier */
U8 status;              /* status */
#endif
{
   TRC3(KwUiCkwBndCfm);

   RETVALUE((*KwUiCkwBndCfmMt[pst->selector])(pst, suId, status));
} /* end of KwUiCkwBndCfm */

/**************************************************************************
 *
 *      Fun:   KwUiCkwCfgCfm
 *
 *      Desc:  RLC Configuration Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  kw_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 KwUiCkwCfgCfm
(
Pst *pst,
SuId suId,
CkwCfgCfmInfo *cfgCfm               
)
#else
PUBLIC S16 KwUiCkwCfgCfm (pst, suId, cfgCfm)
Pst *pst;          
SuId suId;        
CkwCfgCfmInfo *cfgCfm;
#endif
{
   TRC3(KwUiCkwCfgCfm);

   RETVALUE((*KwUiCkwCfgCfmMt[pst->selector])(pst, suId, cfgCfm));
} /* end of KwUiCkwCfgCfm */

/**************************************************************************
 *
 *      Fun:   KwUiCkwUeIdChgCfm
 *
 *      Desc:  RLC Configuration Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  kw_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 KwUiCkwUeIdChgCfm
(
Pst           *pst,
SuId           suId,
U32            transId,
CkwUeInfo      *ueInfo,
CmStatus        status
)
#else
PUBLIC S16 KwUiCkwUeIdChgCfm (pst, suId, transId, ueInfo, status)
Pst           *pst;          
SuId           suId;        
U32            transId;
CkwUeInfo     *ueInfo;
CmStatus       status;
#endif
{
   TRC3(KwUiCkwUeIdChgCfm);

   RETVALUE((*KwUiCkwUeIdChgCfmMt[pst->selector])(pst, suId, transId, ueInfo,
                                                                      status));
} /* end of KwUiCkwCfgCfm */
#ifdef PTKWUIKWU
/*
 *
 *       Fun:   portable - Bind confirmation for RLC Data Interface
 *
 *       Desc:  None
 *
 *
 *       Ret:   ROK   - ok
 *
 *       Notes: None
 *
 *       File:  kw_ptui.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtUiKwuBndCfm
(
Pst *pst,               /* post structure */
SuId suId,              /* service user identifier */
U8 status               /* status */
)
#else
PRIVATE S16 PtUiKwuBndCfm (pst, suId, status)
Pst *pst;               /* post structure */
SuId suId;              /* service user identifier */
U8 status;              /* status */
#endif
{
   TRC3(PtUiKwuBndCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiKwuBndCfm */

/**************************************************************************
 *
 *      Fun:   PtUiKwuDatInd
 *
 *      Desc:  Portable -Data Indication 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  kw_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 PtUiKwuDatInd
(
Pst *pst, 
SuId suId,
KwuDatIndInfo *datInd,
Buffer *buf
)
#else
PRIVATE S16 PtUiKwuDatInd (pst, suId, datInd, buf)
Pst *pst;
SuId suId;
KwuDatIndInfo *datInd;
Buffer *buf;
#endif
{
   TRC3(PtUiKwuDatInd);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(datInd);
   UNUSED(buf);

   RETVALUE(ROK);
} /* end of PtUiKwuDatInd */


#endif

#ifdef PTKWUICKW
/**************************************************************************
 *
 *      Fun:   PtUiCkwBndCfm
 *
 *      Desc:  Portable - RLC Bind Confirm for RLC Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  kw_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 PtUiCkwBndCfm
(
Pst *pst,               /* post structure */
SuId suId,              /* service user identifier */
U8 status               /* status */
)
#else
PRIVATE S16 PtUiCkwBndCfm (pst, suId, status)
Pst *pst;               /* post structure */
SuId suId;              /* service user identifier */
U8 status;              /* status */
#endif
{
   TRC3(PtUiCkwBndCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiCkwBndCfm */

/**************************************************************************
 *
 *      Fun:   PtUiCkwCfgCfm
 *
 *      Desc:  Portable - RLC Configuration Confirm 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  kw_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 PtUiCkwCfgCfm
(
Pst *pst,
SuId suId,
CkwCfgCfmInfo *cfgCfm               
)
#else
PRIVATE S16 PtUiCkwCfgCfm (pst, suId, cfgCfm)
Pst *pst;          
SuId suId;        
CkwCfgCfmInfo *cfgCfm;
#endif
{
   TRC3(PtUiCkwCfgCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(cfgCfm);

   RETVALUE(ROK);
} /* end of PtUiCkwCfgCfm */
/**************************************************************************
 *
 *      Fun:   PtUiCkwUeIdChgCfm
 *
 *      Desc:  Portable - RLC Configuration Confirm 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  kw_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 PtUiCkwUeIdChgCfm
(
Pst *pst,
SuId suId,
U32 transId,
CkwUeInfo *ueInfo,
CmStatus   status
)
#else
PRIVATE S16 PtUiCkwUeIdChgCfm (pst, suId, transId, ueInfo, status)
Pst *pst;          
SuId suId;        
U32  transId;
CkwUeInfo *ueInfo;
CmStatus   status;
#endif
{
   TRC3(PtUiCkwUeIdChgCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(transId);
   UNUSED(ueInfo);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiCkwCfgCfm */
#endif
/**********************************************************************
  
         End of file:     kw_ptui.c@@/main/2 - Fri Dec 11 18:48:05 2009
   
**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ----     rcs     1. LTE RRC Initial release.
/main/2      ----     chebli  1. LTE RRC release 2.1.
*********************************************************************91*/
