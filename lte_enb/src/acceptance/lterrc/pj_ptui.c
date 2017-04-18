
/**********************************************************************

     Name:     LTE-RRC Layer 
  
     Type:     C Source file
  
     Desc:     Code for LTE PDCP Upper interface outgoing 
               primitives towards LTE RRC(NH)

     File:     pj_ptui.c

     Sid:      pj_ptui.c@@/main/2 - Fri Dec 11 18:48:07 2009

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
#include "pju.h"           /* PJU Interface defines */
#include "cpj.h"           /* CPJ Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_lib.x"        /* Common library definitions */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE includes */
#include "lnh.x"           /* LNH Interface includes */
#include "pju.x"           /* PJU Interface includes */
#include "cpj.x"           /* CPJ Interface includes */

/* local defines */
#define MAXPJUI   3        /* size of Matrix used for LC/TC */

/* local typedefs */

/* local externs */

/* forward references */

#if (!(defined(LCPJUIPJU) ))
#define PTPJUIPJU    1        /* Portable PJU Interface */
#else
#ifndef NH                    /* NH - RRC */
#define PTPJUIPJU    1        /* Portable PJU Interface */
#endif /* NH */
#endif /*(!(defined(LCPJUIPJU) )) */

#if (!(defined(LCPJUICPJ) ))
#define PTPJUICPJ    1        /* Portable CPJ Interface */
#else
#ifndef NH                    /* NH - RRC */
#define PTPJUICPJ    1        /* Portable CPJ Interface */
#endif /* NH */
#endif /*(!(defined(LCPJUICPJ) )) */

/* Prototypes of Portable Functions */
#ifdef PTPJUIPJU
PRIVATE S16 PtUiPjuBndCfm ARGS((Pst *pst, SuId suId, U8 status));
PRIVATE S16 PtUiPjuDatCfm ARGS((Pst *pst, SuId suId, CmLtePdcpId *pdcpId, 
                                PjuDatCfmInfo *datCfm));
PRIVATE S16 PtUiPjuDatInd ARGS((Pst *pst, SuId suId, CmLtePdcpId *pdcpId, 
                                Buffer *buf));
PRIVATE S16 PtUiPjuStaInd ARGS((Pst *pst, SuId suId, CmLtePdcpId *pdcpId,
                                PjuStaIndInfo *staInd, Buffer *buf));
#endif /* PTPJUIPJU */

#ifdef PTPJUICPJ
PRIVATE S16 PtUiCpjBndCfm ARGS((Pst *pst, SuId suId, U8 status));
PRIVATE S16 PtUiCpjCfgCfm ARGS((Pst *pst, SuId suId, CpjCfgCfmInfo *cfgCfm));
PRIVATE S16 PtUiCpjUeIdChgCfm ARGS((Pst *pst, SuId suId, U32 transId, CpjUeInfo
         *ueInfo, CmStatus status));
PRIVATE S16 PtUiCpjSduStaCfm ARGS(( Pst *pst, SuId suId, CpjSduStaCfmInfo *cfgCfm));
PRIVATE S16 PtUiCpjSecCfgCfm ARGS(( Pst *pst, SuId suId, CpjSecCfgCfmInfo *cfgCfm));
PRIVATE S16 PtUiCpjCountCfm ARGS(( Pst *pst, SuId suId, CpjCountCfmInfo *cfgCfm));
PRIVATE S16 PtUiCpjReEstCfm ARGS(( Pst *pst, SuId suId, CpjReEstCfmInfo *cfgCfm));
#endif /* PTPJUICPJ */

/* PJU Primitives */

/* Bind Confirm Primitive */
PRIVATE CONSTANT PjuBndCfm PjUiPjuBndCfmMt [MAXPJUI] =
{
#ifdef LCPJUIPJU
   cmPkPjuBndCfm,       /* 0 - loosely coupled */
#else
   PtUiPjuBndCfm,       /* 0 - loosely coupled, portable */
#endif /* LCPJUIPJU */
#ifdef NH
   NhLiPjuBndCfm,       /* 1 - tight coupled, NH */
#else
   PtUiPjuBndCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/* Data Indication Primitive */
PRIVATE CONSTANT PjuDatInd PjUiPjuDatIndMt [MAXPJUI] =
{
#ifdef LCPJUIPJU
   cmPkPjuDatInd,       /* 0 - loosely coupled */
#else
   PtUiPjuDatInd,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiPjuDatInd,       /* 1 - tight coupled, NH */
#else
   PtUiPjuDatInd,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/* Data Confirm Primitive */
PRIVATE CONSTANT PjuDatCfm PjUiPjuDatCfmMt [MAXPJUI] =
{
#ifdef LCPJUIPJU
   cmPkPjuDatCfm,       /* 0 - loosely coupled */
#else
   PtUiPjuDatCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiPjuDatCfm,       /* 1 - tight coupled, NH */
#else
   PtUiPjuDatCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};
/* Status Indication Primitive */
PRIVATE CONSTANT PjuStaInd PjUiPjuStaIndMt [MAXPJUI] =
{
#ifdef LCPJUIPJU
   cmPkPjuStaInd,       /* 0 - loosely coupled */
#else
   PtUiPjuStaInd,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiPjuStaInd,       /* 1 - tight coupled, NH */
#else
   PtUiPjuStaInd,       /* 1 - tight coupled, portable */
#endif /* NH */
};
/* CPJ Primitives */

/* Cell Configuration Primitive */
PRIVATE CONSTANT CpjCfgCfm PjUiCpjCfgCfmMt [MAXPJUI] =
{
#ifdef LCPJUICPJ
   cmPkCpjCfgCfm,       /* 0 - loosely coupled */
#else
   PtUiCpjCfgCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCpjCfgCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCpjCfgCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/* Cell Configuration Primitive */
PRIVATE CONSTANT CpjSecCfgCfm PjUiCpjSecCfgCfmMt [MAXPJUI] =
{
#ifdef LCPJUICPJ
   cmPkCpjSecCfgCfm,       /* 0 - loosely coupled */
#else
   PtUiCpjSecCfgCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCpjSecCfgCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCpjSecCfgCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

PRIVATE CONSTANT CpjCountCfm PjUiCpjCountCfmMt [MAXPJUI] =
{
#ifdef LCPJUICPJ
   cmPkCpjCountCfm,       /* 0 - loosely coupled */
#else
   PtUiCpjCountCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCpjCountCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCpjCountCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

PRIVATE CONSTANT CpjSduStaCfm PjUiCpjSduStaCfmMt [MAXPJUI] =
{
#ifdef LCPJUICPJ
   cmPkCpjSduStaCfm,       /* 0 - loosely coupled */
#else
   PtUiCpjSduStaCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCpjSduStaCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCpjSduStaCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

PRIVATE CONSTANT CpjReEstCfm PjUiCpjReEstCfmMt [MAXPJUI] =
{
#ifdef LCPJUICPJ
   cmPkCpjReEstCfm,       /* 0 - loosely coupled */
#else
   PtUiCpjReEstCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCpjReEstCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCpjReEstCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/* Cell Configuration Primitive */
PRIVATE CONSTANT CpjUeIdChgCfm PjUiCpjUeIdChgCfmMt [MAXPJUI] =
{
#ifdef LCPJUICPJ
   cmPkCpjUeIdChgCfm,       /* 0 - loosely coupled */
#else
   PtUiCpjUeIdChgCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCpjUeIdChgCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCpjUeIdChgCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};
/* Bind Confirm Primitive */
PRIVATE CONSTANT CpjBndCfm PjUiCpjBndCfmMt [MAXPJUI] =
{
#ifdef LCPJUICPJ
   cmPkCpjBndCfm,       /* 0 - loosely coupled */
#else
   PtUiCpjBndCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCpjBndCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCpjBndCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/**************************************************************************
 * LTE PDCP Upper interface primitives
 *************************************************************************/
/**************************************************************************
 *
 *      Fun:   PjUiPjuBndCfm
 *
 *      Desc:  PDCP Bind Confirm to RRC for PDCP Data Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiPjuBndCfm
(
Pst *pst,               /* post structure */
SuId suId,              /* service user identifier */
U8 status               /* status */
)
#else
PUBLIC S16 PjUiPjuBndCfm (pst, suId, status)
Pst *pst;               /* post structure */
SuId suId;              /* service user identifier */
U8 status;              /* status */
#endif
{
   TRC3(PjUiPjuBndCfm);

   RETVALUE((*PjUiPjuBndCfmMt[pst->selector])(pst, suId, status));
} /* end of PjUiPjuBndCfm */

/**************************************************************************
 *
 *      Fun:   PjUiPjuDatInd
 *
 *      Desc:  Data Indication to RRC 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiPjuDatInd
(
Pst *pst, 
SuId suId,
CmLtePdcpId *pdcpId,
Buffer *buf
)
#else
PUBLIC S16 PjUiPjuDatInd (pst, suId, pdcpId, buf)
Pst *pst;
SuId suId;
CmLtePdcpId *pdcpId;
Buffer *buf;
#endif
{
   TRC3(PjUiPjuDatInd);

   RETVALUE((*PjUiPjuDatIndMt[pst->selector])(pst, suId, pdcpId, buf));
} /* end of PjUiPjuDatInd */

/**************************************************************************
 *
 *      Fun:   PjUiPjuDatCfm
 *
 *      Desc:  Data Confirmation to RRC 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiPjuDatCfm
(
Pst *pst, 
SuId suId,
CmLtePdcpId *pdcpId,
PjuDatCfmInfo *datCfm
)
#else
PUBLIC S16 PjUiPjuDatCfm (pst, suId, pdcpId, datCfm)
Pst *pst;
SuId suId;
CmLtePdcpId *pdcpId;
PjuDatCfmInfo *datCfm;
#endif
{
   TRC3(PjUiPjuDatCfm);

   RETVALUE((*PjUiPjuDatCfmMt[pst->selector])(pst, suId, pdcpId, datCfm));
} /* end of PjUiPjuDatCfm */

/**************************************************************************
 *
 *      Fun:   PjUiPjuStaInd
 *
 *      Desc:  Status Indication to RRC 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiPjuStaInd
(
Pst *pst, 
SuId suId,
CmLtePdcpId *pdcpId,
PjuStaIndInfo *staInd, 
Buffer *buf
)
#else
PUBLIC S16 PjUiPjuStaInd (pst, suId, pdcpId, staInd, buf)
Pst *pst;
SuId suId;
CmLtePdcpId *pdcpId;
PjuStaIndInfo *staInd;
Buffer *buf;
#endif
{
   TRC3(PjUiPjuStaInd);

   RETVALUE((*PjUiPjuStaIndMt[pst->selector])(pst, suId, pdcpId, staInd, buf));
} /* end of PjUiPjuStaInd */
/**************************************************************************
 *
 *      Fun:   PjUiCpjBndCfm
 *
 *      Desc:  PDCP Bind Confirm to RRC for PDCP Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiCpjBndCfm
(
Pst *pst,               /* post structure */
SuId suId,              /* service user identifier */
U8 status               /* status */
)
#else
PUBLIC S16 PjUiCpjBndCfm (pst, suId, status)
Pst *pst;               /* post structure */
SuId suId;              /* service user identifier */
U8 status;              /* status */
#endif
{
   TRC3(PjUiCpjBndCfm);

   RETVALUE((*PjUiCpjBndCfmMt[pst->selector])(pst, suId, status));
} /* end of PjUiCpjBndCfm */

/**************************************************************************
 *
 *      Fun:   PjUiCpjCfgCfm
 *
 *      Desc:  PDCP Configuration Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiCpjCfgCfm
(
Pst *pst,
SuId suId,
CpjCfgCfmInfo *cfgCfm               
)
#else
PUBLIC S16 PjUiCpjCfgCfm (pst, suId, cfgCfm)
Pst *pst;          
SuId suId;        
CpjCfgCfmInfo *cfgCfm;
#endif
{
   TRC3(PjUiCpjCfgCfm);

   RETVALUE((*PjUiCpjCfgCfmMt[pst->selector])(pst, suId, cfgCfm));
} /* end of PjUiCpjCfgCfm */

/**************************************************************************
 *
 *      Fun:   PjUiCpjUeIdChgCfm
 *
 *      Desc:  PDCP Configuration Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiCpjUeIdChgCfm
(
Pst *pst,
SuId suId,
U32  transId,
CpjUeInfo *ueInfo,
CmStatus   status             
)
#else
PUBLIC S16 PjUiCpjUeIdChgCfm (pst, suId, transId, ueInfo, status)
Pst *pst;          
SuId suId;        
U32  transId;
CpjUeInfo *ueInfo;
CmStatus   status;             
#endif
{
   TRC3(PjUiCpjUeIdChgCfm);

   RETVALUE((*PjUiCpjUeIdChgCfmMt[pst->selector])(pst, suId, transId, ueInfo,
                                                                      status));
} /* end of PjUiCpjCfgCfm */

/**************************************************************************
 *
 *      Fun:   PjUiCpjSecCfgCfm
 *
 *      Desc:  PDCP Configuration Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiCpjSecCfgCfm
(
Pst *pst,
SuId suId,
CpjSecCfgCfmInfo *cfgCfm               
)
#else
PUBLIC S16 PjUiCpjSecCfgCfm (pst, suId, cfgCfm)
Pst *pst;          
SuId suId;        
CpjSecCfgCfmInfo *cfgCfm;
#endif
{
   TRC3(PjUiCpjSecCfgCfm);

   RETVALUE((*PjUiCpjSecCfgCfmMt[pst->selector])(pst, suId, cfgCfm));
} /* end of PjUiCpjSecCfgCfm */

/**************************************************************************
 *
 *      Fun:   PjUiCpjCountCfm
 *
 *      Desc:  PDCP Configuration Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiCpjCountCfm
(
Pst *pst,
SuId suId,
CpjCountCfmInfo *cfgCfm               
)
#else
PUBLIC S16 PjUiCpjCountCfm (pst, suId, cfgCfm)
Pst *pst;          
SuId suId;        
CpjCountCfmInfo *cfgCfm;
#endif
{
   TRC3(PjUiCpjCountCfm);

   RETVALUE((*PjUiCpjCountCfmMt[pst->selector])(pst, suId, cfgCfm));
} /* end of PjUiCpjCountCfm */

/**************************************************************************
 *
 *      Fun:   PjUiCpjReEstCfm
 *
 *      Desc:  PDCP Configuration Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiCpjReEstCfm
(
Pst *pst,
SuId suId,
CpjReEstCfmInfo *cfgCfm               
)
#else
PUBLIC S16 PjUiCpjReEstCfm (pst, suId, cfgCfm)
Pst *pst;          
SuId suId;        
CpjReEstCfmInfo *cfgCfm;
#endif
{
   TRC3(PjUiCpjReEstCfm);

   RETVALUE((*PjUiCpjReEstCfmMt[pst->selector])(pst, suId, cfgCfm));
} /* end of PjUiCpjReEstCfm */

/**************************************************************************
 *
 *      Fun:   PjUiCpjSduStaCfm
 *
 *      Desc:  PDCP Configuration Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PjUiCpjSduStaCfm
(
Pst *pst,
SuId suId,
CpjSduStaCfmInfo *cfgCfm               
)
#else
PUBLIC S16 PjUiCpjSduStaCfm (pst, suId, cfgCfm)
Pst *pst;          
SuId suId;        
CpjSduStaCfmInfo *cfgCfm;
#endif
{
   TRC3(PjUiCpjSduStaCfm);

   RETVALUE((*PjUiCpjSduStaCfmMt[pst->selector])(pst, suId, cfgCfm));
} /* end of PjUiCpjSduStaCfm */
#ifdef PTPJUIPJU
/*
 *
 *       Fun:   portable - Bind confirmation for PDCP Data Interface
 *
 *       Desc:  None
 *
 *
 *       Ret:   ROK   - ok
 *
 *       Notes: None
 *
 *       File:  pj_ptui.c
 *
 */
#ifdef ANSI
PRIVATE S16 PtUiPjuBndCfm
(
Pst *pst,               /* post structure */
SuId suId,              /* service user identifier */
U8 status               /* status */
)
#else
PRIVATE S16 PtUiPjuBndCfm (pst, suId, status)
Pst *pst;               /* post structure */
SuId suId;              /* service user identifier */
U8 status;              /* status */
#endif
{
   TRC3(PtUiPjuBndCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiPjuBndCfm */

/**************************************************************************
 *
 *      Fun:   PtUiPjuDatInd
 *
 *      Desc:  Portable -Data Indication 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 PtUiPjuDatInd
(
Pst *pst, 
SuId suId,
CmLtePdcpId *pdcpId,
Buffer *buf
)
#else
PRIVATE S16 PtUiPjuDatInd (pst, suId, pdcpId, buf)
Pst *pst;
SuId suId;
CmLtePdcpId *pdcpId;
Buffer *buf;
#endif
{
   TRC3(PtUiPjuDatInd);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(pdcpId);
   UNUSED(buf);

   RETVALUE(ROK);
} /* end of PtUiPjuDatInd */

/**************************************************************************
 *
 *      Fun:   PtUiPjuDatCfm
 *
 *      Desc:  Portable - Data Confirmation 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 PtUiPjuDatCfm
(
Pst *pst, 
SuId suId,
CmLtePdcpId *pdcpId,
PjuDatCfmInfo *datCfm
)
#else
PRIVATE S16 PtUiPjuDatCfm (pst, suId, pdcpId, datCfm)
Pst *pst;
SuId suId;
CmLtePdcpId *pdcpId;
PjuDatCfmInfo *datCfm;
#endif
{
   TRC3(PtUiPjuDatCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(pdcpId);
   UNUSED(datCfm);

   RETVALUE(ROK);
} /* end of PtUiPjuDatCfm */

/**************************************************************************
 *
 *      Fun:   PtUiPjuStaInd
 *
 *      Desc:  Portable - Status Indication 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 PtUiPjuStaInd
(
Pst *pst, 
SuId suId,
CmLtePdcpId *pdcpId,
PjuStaIndInfo *staInd,
Buffer *buf
)
#else
PRIVATE S16 PtUiPjuStaInd (pst, suId, pdcpId, staInd, buf)
Pst *pst;
SuId suId;
CmLtePdcpId *pdcpId;
PjuStaIndInfo *staInd;
Buffer *buf;
#endif
{
   TRC3(PtUiPjuStaInd);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(pdcpId);
   UNUSED(staInd);

   RETVALUE(ROK);
} /* end of PtUiPjuStaInd */

#endif

#ifdef PTPJUICPJ
/**************************************************************************
 *
 *      Fun:   PtUiCpjBndCfm
 *
 *      Desc:  Portable - PDCP Bind Confirm for PDCP Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCpjBndCfm
(
Pst *pst,               /* post structure */
SuId suId,              /* service user identifier */
U8 status               /* status */
)
#else
PUBLIC S16 PtUiCpjBndCfm (pst, suId, status)
Pst *pst;               /* post structure */
SuId suId;              /* service user identifier */
U8 status;              /* status */
#endif
{
   TRC3(PtUiCpjBndCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiCpjBndCfm */

/**************************************************************************
 *
 *      Fun:   PtUiCpjCfgCfm
 *
 *      Desc:  Portable - PDCP Configuration Confirm 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCpjCfgCfm
(
Pst *pst,
SuId suId,
CpjCfgCfmInfo *cfgCfm               
)
#else
PUBLIC S16 PtUiCpjCfgCfm (pst, suId, cfgCfm)
Pst *pst;          
SuId suId;        
CpjCfgCfmInfo *cfgCfm;
#endif
{
   TRC3(PtUiCpjCfgCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(cfgCfm);

   RETVALUE(ROK);
} /* end of PtUiCpjCfgCfm */

/**************************************************************************
 *
 *      Fun:   PtUiCpjSecCfgCfm
 *
 *      Desc:  Portable - PDCP Bind Confirm for PDCP Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCpjSecCfgCfm
(
Pst *pst,
SuId suId,
CpjSecCfgCfmInfo *cfgCfm
)
#else
PUBLIC S16 PtUiCpjSecCfgCfm (pst, suId, cfgCfm)
Pst *pst;
SuId suId;
CpjSecCfgCfmInfo *cfgCfm;
#endif
{
   TRC3(PtUiCpjSecCfgCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(cfgCfm);

   RETVALUE(ROK);
}
/**************************************************************************
 *
 *      Fun:   PtUiCpjCountCfm
 *
 *      Desc:  Portable - PDCP Bind Confirm for PDCP Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCpjCountCfm
(
Pst *pst,
SuId suId,
CpjCountCfmInfo *cfgCfm
)
#else
PUBLIC S16 PtUiCpjCountCfm (pst, suId, cfgCfm)
Pst *pst;
SuId suId;
CpjCountCfmInfo *cfgCfm;
#endif
{
   TRC3(PtUiCpjCountCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(cfgCfm);

   RETVALUE(ROK);
}
/**************************************************************************
 *
 *      Fun:   PtUiCpjSduStaCfm
 *
 *      Desc:  Portable - PDCP Bind Confirm for PDCP Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCpjSduStaCfm
(
Pst *pst,
SuId suId,
CpjSduStaCfmInfo *cfgCfm
)
#else
PUBLIC S16 PtUiCpjSduStaCfm (pst, suId, cfgCfm)
Pst *pst;
SuId suId;
CpjSduStaCfmInfo *cfgCfm;
#endif
{
   TRC3(PtUiCpjSduStaCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(cfgCfm);

   RETVALUE(ROK);
}
/**************************************************************************
 *
 *      Fun:   PtUiCpjReEstCfm
 *
 *      Desc:  Portable - PDCP Bind Confirm for PDCP Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCpjReEstCfm
(
Pst *pst,
SuId suId,
CpjReEstCfmInfo *cfgCfm
)
#else
PUBLIC S16 PtUiCpjReEstCfm (pst, suId, cfgCfm)
Pst *pst;
SuId suId;
CpjReEstCfmInfo *cfgCfm;
#endif
{
   TRC3(PtUiCpjReEstCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(cfgCfm);

   RETVALUE(ROK);
}

/**************************************************************************
 *
 *      Fun:   PtUiCpjUeIdChgCfm
 *
 *      Desc:  Portable - PDCP Configuration Confirm 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  pj_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCpjUeIdChgCfm
(
Pst *pst,
SuId suId,
U32  transId,
CpjUeInfo *ueInfo,
CmStatus   status
)
#else
PUBLIC S16 PtUiCpjUeIdChgCfm (pst, suId, transId, ueInfo, status)
Pst *pst;          
SuId suId;        
U32  transId;
CpjUeInfo *ueInfo;
CmStatus   status;
#endif
{
   TRC3(PtUiCpjUeIdChgCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(transId);
   UNUSED(ueInfo);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiCpjUeIdChgCfm */
#endif
/**********************************************************************
  
         End of file:     pj_ptui.c@@/main/2 - Fri Dec 11 18:48:07 2009
   
**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ----      rer     1. LTE RRC Initial Release.
/main/2      ----     chebli  1. LTE RRC release 2.1.
*********************************************************************91*/
