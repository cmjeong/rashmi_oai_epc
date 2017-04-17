
/**********************************************************************

     Name:     LTE-RRC Layer 
  
     Type:     C Source file
  
     Desc:     Code for LTE MAC Upper interface outgoing 
               primitives towards LTE RRC(NH)

     File:     rg_ptui.c

     Sid:      rg_ptui.c@@/main/2 - Fri Dec 11 18:48:08 2009

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
#include "crg.h"           /* CRG Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_lib.x"        /* Common library definitions */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE includes */
#include "lnh.x"           /* LNH Interface includes */
#include "crg.x"           /* CRG Interface includes */

/* local defines */
#define MAXRGUI   3        /* size of Matrix used for LC/TC */

/* local typedefs */

/* local externs */

/* forward references */

#if (!(defined(LCRGUICRG) ))
#define PTRGUICRG    1        /* Portable CRG Interface */
#else
#ifndef NH                    /* NH - RRC */
#define PTRGUICRG    1        /* Portable CRG Interface */
#endif /* NH */
#endif /*(!(defined(LCRGUICRG) )) */

#ifdef PTRGUICRG
PRIVATE S16 PtUiCrgBndCfm ARGS((Pst *pst, SuId suId, U8 status));
PRIVATE S16 PtUiCrgCfgCfm ARGS((Pst *pst, SuId suId, CrgCfgTransId transId,
                                U8 status));
#endif /* PTRGUICRG */

/* CKW Primitives */

/* Configuration Primitive */
PRIVATE CONSTANT CrgCfgCfm RgUiCrgCfgCfmMt [MAXRGUI] =
{
#ifdef LCRGUICRG
   cmPkCrgCfgCfm,       /* 0 - loosely coupled */
#else
   PtUiCrgCfgCfm,       /* 0 - loosely coupled, portable */
#endif /* LCRGUICRG */
#ifdef NH
   NhLiCrgCfgCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCrgCfgCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/* Bind Confirm Primitive */
PRIVATE CONSTANT CrgBndCfm RgUiCrgBndCfmMt [MAXRGUI] =
{
#ifdef LCRGUICRG
   cmPkCrgBndCfm,       /* 0 - loosely coupled */
#else
   PtUiCrgBndCfm,       /* 0 - loosely coupled, portable */
#endif /* LCRGUICRG */
#ifdef NH
   NhLiCrgBndCfm,       /* 1 - tight coupled, NH */
#else
   PtUiCrgBndCfm,       /* 1 - tight coupled, portable */
#endif /* NH */
};

/**************************************************************************
 *
 *      Fun:   RgUiCrgBndCfm
 *
 *      Desc:  MAC Bind Confirm to RRC for MAC Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  rg_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 RgUiCrgBndCfm
(
Pst *pst,               /* post structure */
SuId suId,              /* service user identifier */
U8 status               /* status */
)
#else
PUBLIC S16 RgUiCrgBndCfm (pst, suId, status)
Pst *pst;               /* post structure */
SuId suId;              /* service user identifier */
U8 status;              /* status */
#endif
{
   TRC3(RgUiCrgBndCfm);

   RETVALUE((*RgUiCrgBndCfmMt[pst->selector])(pst, suId, status));
} /* end of RgUiCrgBndCfm */

/**************************************************************************
 *
 *      Fun:   RgUiCrgCfgCfm
 *
 *      Desc:  MAC Configuration Confirm to RRC
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  rg_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 RgUiCrgCfgCfm
(
Pst *pst,
SuId suId,
CrgCfgTransId transId,
U8 status
)
#else
PUBLIC S16 RgUiCrgCfgCfm (pst, suId, transId, status)
Pst *pst;          
SuId suId;        
CrgCfgTransId transId;
U8 status;
#endif
{
   TRC3(RgUiCrgCfgCfm);

   RETVALUE((*RgUiCrgCfgCfmMt[pst->selector])(pst, suId, transId, status));
} /* end of RgUiCrgCfgCfm */

#ifdef PTRGUICRG
/**************************************************************************
 *
 *      Fun:   PtUiCrgBndCfm
 *
 *      Desc:  Portable - MAC Bind Confirm for MAC Control Interface 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  rg_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCrgBndCfm
(
Pst *pst,               
SuId suId,             
U8 status             
)
#else
PUBLIC S16 PtUiCrgBndCfm (pst, suId, status)
Pst *pst;            
SuId suId;          
U8 status;         
#endif
{
   TRC3(PtUiCrgBndCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiCrgBndCfm */

/**************************************************************************
 *
 *      Fun:   PtUiCrgCfgCfm
 *
 *      Desc:  Portable - MAC Configuration Confirm 
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  rg_ptui.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 PtUiCrgCfgCfm
(
Pst *pst,
SuId suId,
CrgCfgTransId transId,
U8   status
)
#else
PUBLIC S16 PtUiCrgCfgCfm (pst, suId, transId, status)
Pst *pst;          
SuId suId;        
CrgCfgTransId transId;
U8   status;
#endif
{
   TRC3(PtUiCrgCfgCfm);

   UNUSED(pst);
   UNUSED(suId);
   UNUSED(transId);
   UNUSED(status);

   RETVALUE(ROK);
} /* end of PtUiCrgCfgCfm */
#endif
/**********************************************************************
  
         End of file:     rg_ptui.c@@/main/2 - Fri Dec 11 18:48:08 2009
   
**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     rer      1. LTE RRC Initial Release.
/main/2      ----     chebli  1. LTE RRC release 2.1.
*********************************************************************91*/
