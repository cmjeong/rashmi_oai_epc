
/**********************************************************************

     Name:     LTE-RRC Layer 
  
     Type:     C Source file
  
     Desc:     Code for LTE PHY Upper interface outgoing 
               primitives towards LTE RRC(NH)

     File:     tf_ptui.c

     Sid:      tf_ptui.c@@/main/1 - Fri Dec 11 18:48:09 2009

     Prg:      yk 

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
#include "ctf.h"           /* CTF Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_lib.x"        /* Common library definitions */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE includes */
#include "lnh.x"           /* LNH Interface includes */
#include "ctf.x"           /* CTF Interface includes */

/* local defines */
#define MAXTFUI   3        /* size of Matrix used for LC/TC */

/* local typedefs */

/* local externs */

/* forward references */

#ifdef RRC_PHY_CFG_SUPP
#if (!(defined(LCTFUICTF) ))
#define PTTFUICTF    1        /* Portable CTF Interface */
#else
#ifndef NH                    /* NH - RRC */
#define PTTFUICTF    1        /* Portable CTF Interface */
#endif /* NH */
#endif /*(!(defined(LCTFUICTF) )) */

#ifdef PTTFUICTF
PRIVATE S16 PtUiCtfBndCfm ARGS((Pst *pst, SuId suId, U8 status));
PRIVATE S16 PtUiCtfCfgCfm ARGS((Pst *pst, SuId suId, CtfCfgTransId transId,
                                U8 status));
PRIVATE S16 PtUiCtfUeIdChgCfm ARGS((Pst *pst, SuId suId, CtfCfgTransId transId, 
         CtfUeInfo *ueInfo, CmStatus status));
#endif /* PTTFUICTF */

/* CKW Primitives */

/* Configuration Primitive */
PRIVATE CONSTANT CtfCfgCfm TfUiCtfCfgCfmMt [MAXTFUI] =
{
#ifdef LCTFUICTF
   cmPkCtfCfgCfm,       /* 0 - loosely coupled */
#else
   PtUiCtfCfgCfm,       /* 0 - loosely coupled, portable */
#endif /* LCTFUICTF */
#ifdef NH
   NhLiCtfCfgCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCtfCfgCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/* Bind Confirm Primitive */
PRIVATE CONSTANT CtfBndCfm TfUiCtfBndCfmMt [MAXTFUI] =
{
#ifdef LCTFUICTF
   cmPkCtfBndCfm,       /* 0 - loosely coupled */
#else
   PtUiCtfBndCfm,       /* 0 - loosely coupled, portable */
#endif /* LCTFUICTF */
#ifdef NH
   NhLiCtfBndCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCtfBndCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};


PRIVATE CONSTANT CtfUeIdChgCfm TfUiCtfUeIdChgCfmMt [MAXTFUI] =
{
#ifdef LCTFUICTF
   cmPkCtfUeIdChgCfm,       /* 0 - loosely coupled */
#else
   PtUiCtfUeIdChgCfm,       /* 0 - loosely coupled, portable */
#endif /* LCNHUINHU */
#ifdef NH
   NhLiCtfUeIdChgCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCtfUeIdChgCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/**************************************************************************
 *
 *      Fun:   TfUiCtfBndCfm
 *
 *      Desc:  PHY Bind Confirm to RRC for PHY Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  tf_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 TfUiCtfBndCfm
(
Pst *pst,               /* post structure */
SuId suId,              /* service user identifier */
U8 status               /* status */
)
#else
PUBLIC S16 TfUiCtfBndCfm (pst, suId, status)
Pst *pst;               /* post structure */
SuId suId;              /* service user identifier */
U8 status;              /* status */
#endif
{
   TRC3(TfUiCtfBndCfm);

   RETVALUE((*TfUiCtfBndCfmMt[pst->selector])(pst, suId, status));
} /* end of TfUiCtfBndCfm */

/**************************************************************************
 *
 *      Fun:   TfUiCtfCfgCfm
 *
 *      Desc:  PHY Configuration Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  tf_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 TfUiCtfCfgCfm
(
Pst *pst,
SuId suId,
CtfCfgTransId transId,
U8 status
)
#else
PUBLIC S16 TfUiCtfCfgCfm (pst, suId, transId, status)
Pst *pst;          
SuId suId;        
CtfCfgTransId transId;
U8 status;
#endif
{
   TRC3(TfUiCtfCfgCfm);

   RETVALUE((*TfUiCtfCfgCfmMt[pst->selector])(pst, suId, transId, status));
} /* end of TfUiCtfCfgCfm */

/**************************************************************************
 *
 *      Fun:   TfUiCtfUeIdChgCfm
 *
 *      Desc:  PHY Ue Id Chg Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  tf_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 TfUiCtfUeIdChgCfm
(
Pst *pst,
SuId suId,
CtfCfgTransId  transId,
CtfUeInfo *ueInfo,
CmStatus   status             
)
#else
PUBLIC S16 TfUiCtfUeIdChgCfm (pst, suId, transId, ueInfo, status)
Pst *pst;          
SuId suId;        
CtfCfgTransId  transId;
CtfUeInfo *ueInfo;
CmStatus   status;             
#endif
{
   TRC3(TfUiCtfUeIdChgCfm);

   RETVALUE((*TfUiCtfUeIdChgCfmMt[pst->selector])(pst, suId, transId, ueInfo,
                                                                      status));
} /* end of TfUiCtfUeIdChgCfm */

#ifdef PTTFUICTF
/**************************************************************************
 *
 *      Fun:   PtUiCtfBndCfm
 *
 *      Desc:  Portable - PHY Bind Confirm for PHY Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  tf_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCtfBndCfm
(
Pst *pst,               
SuId suId,             
U8 status             
)
#else
PUBLIC S16 PtUiCtfBndCfm (pst, suId, status)
Pst *pst;            
SuId suId;          
U8 status;         
#endif
{
   TRC3(PtUiCtfBndCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiCtfBndCfm */

/**************************************************************************
 *
 *      Fun:   PtUiCtfCfgCfm
 *
 *      Desc:  Portable - PHY Configuration Confirm 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  tf_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCtfCfgCfm
(
Pst *pst,
SuId suId,
CtfCfgTransId transId,
U8   status
)
#else
PUBLIC S16 PtUiCtfCfgCfm (pst, suId, transId, status)
Pst *pst;          
SuId suId;        
CtfCfgTransId transId;
U8   status;
#endif
{
   TRC3(PtUiCtfCfgCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(transId);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiCtfCfgCfm */
/**************************************************************************
 *
 *      Fun:   PtUiCtfUeIdChgCfm
 *
 *      Desc:  Portable - PHY Configuration Confirm 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  tf_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCtfUeIdChgCfm
(
Pst *pst,
SuId suId,
CtfCfgTransId  transId,
CtfUeInfo *ueInfo,
CmStatus   status
)
#else
PUBLIC S16 PtUiCtfUeIdChgCfm (pst, suId, transId, ueInfo, status)
Pst *pst;          
SuId suId;        
CtfCfgTransId  transId;
CtfUeInfo *ueInfo;
CmStatus   status;
#endif
{
   TRC3(PtUiCtfUeIdChgCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(transId);
   UNUSED(ueInfo);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiCtfUeIdChgCfm */
#endif
#endif /* RRC_PHY_CFG_SUPP */
/**********************************************************************
  
         End of file:     tf_ptui.c@@/main/1 - Fri Dec 11 18:48:09 2009
   
**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     yk      1. LTE RRC Initial Release.
*********************************************************************91*/
