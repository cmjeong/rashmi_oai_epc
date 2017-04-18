

/********************************************************************20**
  
        Name:     Sample Layer Manager
    
        Type:     C source file
  
        Desc:     Sample Layer Manager for RLC Layer
 
        File:     sm_kw_ptmi.c

        Sid:      sm_pk_ptmi.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:20 2014
  
        Prg:      slv
  
*********************************************************************21*/
 

/*
 *      This software may be combined with the following TRILLIUM
 *      software:
 *
 *      part no.                      description
 *      --------    ----------------------------------------------
 *    
 */


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
#include "lpj.h"           /* LPK defines */
#include "lpk.h"           /* LPK defines */

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
#include "lpj.x"           /* LPK */
#include "lpk.x"           /* LPK */

  
/* local defines */
#ifndef LCPKMILPK
#define PTSMLPK
#endif

#ifndef SM 
#define PTSMLPK
#endif


   
/*****************************************************************************
 *                         PDCP LM PTMI
 ****************************************************************************/
#ifdef PTSMLPK

EXTERN S16 PtMiLpkCfgReq ARGS((Pst * pst, PkMngmt * cfg));

EXTERN S16 PtMiLpkCntrlReq ARGS((Pst * pst, PkMngmt * cntl));

EXTERN S16 PtMiLpkStaReq ARGS((Pst * pst, PkMngmt * staReq));

EXTERN S16 PtMiLpkStsReq ARGS((Pst * pst, Action actn, PkMngmt * sts));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
PRIVATE S16 PtMiLpkL2MeasReq ARGS((Pst *pst,  PkL2MeasReqEvt *measReqEvt));
#endif
#endif /*--#ifdef PTSMLPK--*/

#ifndef LCPKMILPK
#define PTPKMILPK
#endif
PRIVATE CONSTANT LpkCfgReq SmMiLpkCfgReqMt[] =
{
#ifdef LCPKMILPK
   cmPkLpkCfgReq,
#else
   PtMiLpkCfgReq,
#endif
#ifdef PK
   PkMiLpkCfgReq,
#else
   PtMiLpkCfgReq,
#endif
};


PRIVATE CONSTANT LpkCntrlReq SmMiLpkCntrlReqMt[] =
{
#ifdef LCPKMILPK
   cmPkLpkCntrlReq,
#else
   PtMiLpkCntrlReq,
#endif
#ifdef PK
   PkMiLpkCntrlReq,
#else
   PtMiLpkCntrlReq,
#endif
};


PRIVATE CONSTANT LpkStaReq SmMiLpkStaReqMt[] =
{
#ifdef LCPKMILPK
   cmPkLpkStaReq,
#else
   PtMiLpkStaReq,
#endif
#ifdef PK
   PkMiLpkStaReq,
#else
   PtMiLpkStaReq,
#endif
};


PRIVATE CONSTANT LpkStsReq SmMiLpkStsReqMt[] =
{
#ifdef LCPKMILPK
   cmPkLpkStsReq,
#else
   PtMiLpkStsReq,
#endif
#ifdef PK
   PkMiLpkStsReq,
#else
   PtMiLpkStsReq,
#endif
};

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
PRIVATE CONSTANT LpkL2MeasReq SmMiLpkL2MeasReqMt[] =
{
#ifdef LCPKMILPK
   cmPkLpkL2MeasReq,
#else
   PtMiLpkL2MeasReq,
#endif
#ifdef PK
   PkMiLpkL2MeasReq,
#else
   PtMiLpkL2MeasReq,
#endif
};
#endif

#ifdef SM
#ifdef ANSI
PUBLIC S16 SmMiLpkCfgReq
(
Pst * pst,
PkMngmt * cfg
)
#else
PUBLIC S16 SmMiLpkCfgReq(pst, cfg)
Pst * pst;
PkMngmt * cfg;
#endif
{

   TRC3(SmMiLpkCfgReq)

   (*SmMiLpkCfgReqMt[pst->selector])(pst, cfg);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 SmMiLpkCntrlReq
(
Pst * pst,
PkMngmt * cntl
)
#else
PUBLIC S16 SmMiLpkCntrlReq(pst, cntl)
Pst * pst;
PkMngmt * cntl;
#endif
{

   TRC3(SmMiLpkCntrlReq)

   (*SmMiLpkCntrlReqMt[pst->selector])(pst, cntl);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 SmMiLpkStaReq
(
Pst * pst,
PkMngmt * staReq
)
#else
PUBLIC S16 SmMiLpkStaReq(pst, staReq)
Pst * pst;
PkMngmt * staReq;
#endif
{

   TRC3(SmMiLpkStaReq)

   (*SmMiLpkStaReqMt[pst->selector])(pst, staReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 SmMiLpkStsReq
(
Pst * pst,
Action actn,
PkMngmt * sts
)
#else
PUBLIC S16 SmMiLpkStsReq(pst, actn, sts)
Pst * pst;
Action actn;
PkMngmt * sts;
#endif
{

   TRC3(SmMiLpkStsReq)

   (*SmMiLpkStsReqMt[pst->selector])(pst, actn, sts);

   RETVALUE(ROK);

}
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef ANSI
PUBLIC S16 SmMiLpkL2MeasReq 
(
Pst            *pst, 
PkL2MeasReqEvt *measReqEvt 
)
#else
PUBLIC S16 SmMiLpkL2MeasReq (pst, measReqEvt)
Pst            *pst; 
PkL2MeasReqEvt *measReqEvt;
#endif
{
   TRC3(SmMiLpkL2MeasReq )

   (*SmMiLpkL2MeasReqMt[pst->selector])(pst,measReqEvt);

   RETVALUE(ROK);
}
#endif
#endif /*--ifdef SM--*/

#ifdef PTPKMILPK
#ifdef ANSI
PUBLIC S16 PtMiLpkCfgReq
(
Pst * pst,
PkMngmt * cfg
)
#else
PUBLIC S16 PtMiLpkCfgReq(pst, cfg)
Pst * pst;
PkMngmt * cfg;
#endif
{

   TRC3(PtMiLpkCfgReq)

   UNUSED(pst);
   UNUSED(cfg);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtMiLpkCntrlReq
(
Pst * pst,
PkMngmt * cntl
)
#else
PUBLIC S16 PtMiLpkCntrlReq(pst, cntl)
Pst * pst;
PkMngmt * cntl;
#endif
{

   TRC3(PtMiLpkCntrlReq)

   UNUSED(pst);
   UNUSED(cntl);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtMiLpkStaReq
(
Pst * pst,
PkMngmt * staReq
)
#else
PUBLIC S16 PtMiLpkStaReq(pst, staReq)
Pst * pst;
PkMngmt * staReq;
#endif
{

   TRC3(PtMiLpkStaReq)

   UNUSED(pst);
   UNUSED(staReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtMiLpkStsReq
(
Pst * pst,
Action actn,
PkMngmt * sts
)
#else
PUBLIC S16 PtMiLpkStsReq(pst, actn, sts)
Pst * pst;
Action actn;
PkMngmt * sts;
#endif
{

   TRC3(PtMiLpkStsReq)

   UNUSED(pst);
   UNUSED(actn);
   UNUSED(sts);

   RETVALUE(ROK);

}
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef ANSI
PRIVTAE S16 PtMiLpkL2MeasReq 
(
Pst            *pst, 
PkL2MeasReqEvt *measReqEvt 
)
#else
PRIVATE S16 PtMiLpkL2MeasReq (pst, measReqEvt)
Pst            *pst; 
PkL2MeasReqEvt *measReqEvt;
#endif
{
   TRC3(PtMiLpkL2MeasReq)

   UNUSED(pst);
   UNUSED(measReqEvt);
}
#endif/* LTE_L2_MEAS */
#endif /*--ifdef PTSMLPK--*/

  
/********************************************************************30**
  
         End of file:     sm_pk_ptmi.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:20 2014
  
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
----------- -------- ---- -----------------------------------------------
/main/1      ---  gk   1. initial release LTE RLC
/main/2      ---  gk   1. LTE RLC release 2.1
/main/3      kw005.201 ap 1. Added support for L2 Measurement.
*********************************************************************91*/

