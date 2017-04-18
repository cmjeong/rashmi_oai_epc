
/**********************************************************************

     Name:     LTE-RRC Layer 
  
     Type:     C Source file
  
     Desc:     RRC Layer Manager Interface

     File:     smnhptmi.c

     Sid:      smnhptmi.c@@/main/2 - Fri Dec 11 18:48:08 2009

     Prg:      rcs

**********************************************************************/
/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000369     LTE-RRC
*
*/

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
#include "cm_pasn.h"       /* common Pasn defines */

#include "nhu.h"           /* NHU Interface defines */
#include "lnh.h"           /* LNH Interface defines */
#include "kwu.h"           /* KWU Interface defines */
#include "ckw.h"           /* CKW Interface defines */
#include "crg.h"           /* CRG Interface defines */
#include "pju.h"           /* PJU Interface defines */
#include "cpj.h"           /* CPJ Interface defines */

#include "nh.h"            /* RRC defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_pasn.x"       /* common Pasn includes */
#include "cm_lib.x"        /* common memory allocation library */

#include "kwu.x"           /* KWU Interface includes */
#include "ckw.x"           /* CKW Interface includes */
#include "nhu.x"           /* NHU Interface includes */
#include "lnh.x"           /* LNH Interface includes */
#include "crg.x"           /* CRG Interface includes */
#include "cpj.x"           /* CPJ Interface includes */
#include "pju.x"           /* PJU Interface includes */
#include "nh.x"            /* RRC includes */

/* Layer management provides the necessary functions to control and
monitor the condition of each protocol layer.

The following functions are provided in this file:

     SmMiLnhCfgReq      Configuration Request
     SmMiLnhStaReq      Status Request
     SmMiLnhStsReq      Statistics Request
     SmMiLnhCntrlReq    Control Request

It is assumed that the following functions are provided in the
layer managment service provider file:

     SmMiLnhCfgCfm      Configuration Confirm
     SmMiLnhStaCfm      Status Confirm
     SmMiLnhStsCfm      Statistics Confirm
     SmMiLnhCntrlCfm    Control Confirm

*/


/* local defines */
#define MAXNHMI  2         /* The size of the LC/TC matrix */

#ifndef LCSMNHMILNH
#define PTSMMILNH   1      /* Portable LNH Interface */
#else
#ifndef SM
#define PTSMMILNH   1      /* Portable LNH Interface */
#endif /* SM */
#endif /* LCSMNHMILNH */

#ifdef __cplusplus
extern "C" {
#endif /* cplusplus */
 
/*
  
   The following matrices define the mapping between the primitives called by 
   the Layer Manager of RRC and the corresponding primitives of RRC layer.

   The dispatching is performed by the configurable variable: selector.  The 
   selector is configured on a per SAP basis.

   The selectors are:

   NH_SEL_LC - loosely coupled
   NH_SEL_TC - tightly coupled Lower layer 

*/

/* local externs */
#ifdef PTSMMILNH
/* forward references */
PRIVATE S16 PtMiLnhCfgReq   ARGS((Pst *pst, NhMngmt *cfg ));
PRIVATE S16 PtMiLnhStaReq   ARGS((Pst *pst, NhMngmt *sta ));
PRIVATE S16 PtMiLnhStsReq   ARGS((Pst *pst, Action action, NhMngmt *sts ));
PRIVATE S16 PtMiLnhCntrlReq ARGS((Pst *pst, NhMngmt *cntrl ));
#endif /* PTSMMILNH */

PRIVATE LnhCfgReq SmMiLnhCfgReqMt[MAXNHMI] =
{
#ifdef LCSMNHMILNH
   cmPkLnhCfgReq,          /* 0 - loosely coupled */
#else
   PtMiLnhCfgReq,          /* 0 - tightly coupled, portable */
#endif /* LCSMNHMILNH */
#ifdef NH
   NhMiLnhCfgReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLnhCfgReq,          /* 1 - tightly coupled, portable */
#endif /* NH */
};

/* Statistics request primitive */
 
PRIVATE LnhStsReq SmMiLnhStsReqMt[MAXNHMI] =
{
#ifdef LCSMNHMILNH
   cmPkLnhStsReq,          /* 0 - loosely coupled */
#else
   PtMiLnhStsReq,          /* 0 - tightly coupled, portable */
#endif /* LCSMNHMILNH */
#ifdef NH
   NhMiLnhStsReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLnhStsReq,          /* 1 - tightly coupled, portable */
#endif /* NH */
};

/* Status request primitive */
 
PRIVATE LnhStaReq SmMiLnhStaReqMt[MAXNHMI] =
{
#ifdef LCSMNHMILNH
   cmPkLnhStaReq,        /* 0 - loosely coupled */
#else
   PtMiLnhStaReq,          /* 0 - tightly coupled, portable */
#endif /* LCSMNHMILNH */
#ifdef NH
   NhMiLnhStaReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLnhStaReq,          /* 1 - tightly coupled, portable */
#endif /* NH */
};

/* Control request primitive */
 
PRIVATE LnhCntrlReq SmMiLnhCntrlReqMt[MAXNHMI] =
{
#ifdef LCSMNHMILNH
   cmPkLnhCntrlReq,          /* 0 - loosely coupled */
#else
   PtMiLnhCntrlReq,          /* 0 - tightly coupled, portable */
#endif /* LCSMNHMILNH */
#ifdef NH
   NhMiLnhCntrlReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLnhCntrlReq,          /* 1 - tightly coupled, portable */
#endif /* NH */
};

/**************************************************************************
 *
 *      Fun:   Configuration request
 *
 *      Desc:  This function is used to configure RRC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  smnhptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 SmMiLnhCfgReq
(
Pst *pst,                 /* post structure */
NhMngmt *cfg              /* configure */
)
#else
PUBLIC S16 SmMiLnhCfgReq(pst, cfg)
Pst *pst;                 /* post structure */   
NhMngmt *cfg;             /* configure */
#endif
{
   TRC3(SmMiLnhCfgReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLnhCfgReqMt[pst->selector])(pst, cfg); 
   RETVALUE(ROK);
} /* end of SmMiLnhCfgReq */

/**************************************************************************
 *
 *      Fun:   Status request
 *
 *      Desc:  This function is used to send the status request RRC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  smnhptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 SmMiLnhStaReq
(
Pst *pst,                 /* post structure */
NhMngmt *sta              /* status */
)
#else
PUBLIC S16 SmMiLnhStaReq(pst, sta)
Pst *pst;                 /* post structure */   
NhMngmt *sta;             /* status */
#endif
{
   TRC3(SmMiLnhStaReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLnhStaReqMt[pst->selector])(pst, sta); 
   RETVALUE(ROK);
} /* end of SmMiLnhStaReq */


/**************************************************************************
 *
 *      Fun:   Statistics request
 *
 *      Desc:  This function is used to send the statistics request RRC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  smnhptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 SmMiLnhStsReq
(
Pst *pst,                 /* post structure */
Action action,            /* Action */
NhMngmt *sts              /* statistics */
)
#else
PUBLIC S16 SmMiLnhStsReq(pst, action, sts)
Pst *pst;                 /* post structure */   
Action action;            /* Action */
NhMngmt *sts;             /* statistics */
#endif
{
   TRC3(SmMiLnhStsReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLnhStsReqMt[pst->selector])(pst, action, sts); 
   RETVALUE(ROK);
} /* end of SmMiLnhStsReq */

/**************************************************************************
 *
 *      Fun:   Control request
 *
 *      Desc:  This function is used to send the control request RRC
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  smnhptmi.c
 *
 *************************************************************************/
 
 #ifdef ANSI
PUBLIC S16 SmMiLnhCntrlReq
(
Pst *pst,                 /* post structure */
NhMngmt *cntrl            /* control */
)
#else
PUBLIC S16 SmMiLnhCntrlReq(pst, cntrl)
Pst *pst;                 /* post structure */   
NhMngmt *cntrl;           /* control */
#endif
{
   TRC3(SmMiLnhCntrlReq)
   /* jump to specific primitive depending on configured selector */
   (*SmMiLnhCntrlReqMt[pst->selector])(pst, cntrl); 
   RETVALUE(ROK);
} /* end of SmMiLnhCntrlReq */




#ifdef PTSMMILNH
/**************************************************************************
 *
 *      Fun:   Portable Configuration request
 *
 *      Desc:  This function is used to send the configuration request RRC
 *             (Portable)
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  smnhptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PRIVATE S16 PtMiLnhCfgReq
(
Pst *pst,                   /* post structure */
NhMngmt *cfg                /* configure */
)
#else
PRIVATE S16 PtMiLnhCfgReq(pst, cfg)
Pst *pst;                   /* post structure */
NhMngmt *cfg;               /* configure */
#endif
{
  TRC3(PtMiLnhCfgReq);

  UNUSED(cfg);
  UNUSED(pst);
  RETVALUE(ROK);
} /* end of PtMiLnhCfgReq */


/**************************************************************************
 *
 *      Fun:   Portable Status request
 *
 *      Desc:  This function is used to send the status request RRC
 *             (Portable)
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  smnhptmi.c
 *
 *************************************************************************/


#ifdef ANSI
PRIVATE S16 PtMiLnhStaReq
(
Pst *pst,                   /* post structure */
NhMngmt *sta                /* status */
)
#else
PRIVATE S16 PtMiLnhStaReq(pst, sta)
Pst *pst;                   /* post structure */
NhMngmt *sta;               /* status */
#endif
{
  TRC3(PtMiLnhStaReq);

  UNUSED(sta);
  UNUSED(pst);
  RETVALUE(ROK);
} /* end of PtMiLnhStaReq */


/**************************************************************************
 *
 *      Fun:   Portable Statistics request
 *
 *      Desc:  This function is used to send the statistics request RRC
 *             (Portable)
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  smnhptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PRIVATE S16 PtMiLnhStsReq
(
Pst *pst,                   /* post structure */
Action action,              /* Action */
NhMngmt *sts                /* statistics */
)
#else
PRIVATE S16 PtMiLnhStsReq(pst, action, sts)
Pst *pst;                   /* post structure */
Action action;              /* Action */
NhMngmt *sts;               /* statistics */
#endif
{
  TRC3(PtMiLnhStsReq);

  UNUSED(action);
  UNUSED(sts);
  UNUSED(pst);

  RETVALUE(ROK);
} /* end of PtMiLnhStsReq */



/**************************************************************************
 *
 *      Fun:   Portable Control request
 *
 *      Desc:  This function is used to send the control request RRC
 *             (Portable)
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  smnhptmi.c
 *
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 PtMiLnhCntrlReq
(
Pst *pst,                   /* post structure */
NhMngmt *cntrl              /* control */
)
#else
PRIVATE S16 PtMiLnhCntrlReq(pst, cntrl)
Pst *pst;                   /* post structure */
NhMngmt *cntrl;             /* control */
#endif
{
  TRC3(PtMiLnhCntrlReq);

  UNUSED(cntrl);
  UNUSED(pst);

  RETVALUE(ROK);
} /* end of PtMiLnhCntrlReq */

#endif /* PTSMMILNH */

#ifdef __cplusplus
}
#endif /* cplusplus */


/**********************************************************************
  
         End of file:     smnhptmi.c@@/main/2 - Fri Dec 11 18:48:08 2009
   
**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rcs   1. LTE RRC Initial Release.
/main/2      ----     chebli  1. LTE RRC release 2.1.
*********************************************************************91*/
