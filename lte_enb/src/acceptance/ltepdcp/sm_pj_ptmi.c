

/********************************************************************20**
  
        Name:     Sample Layer Manager
    
        Type:     C source file
  
        Desc:     Sample Layer Manager for RLC Layer
 
        File:     sm_kw_ptmi.c

        Sid:      sm_pj_ptmi.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:19 2014
  
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
#include "lpj.h"           /* LPJ defines */

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
#include "lpj.x"           /* LPJ */

  
/* local defines */
#ifndef LCPJMILPJ
#define PTSMLPJ
#endif

#ifndef SM 
#define PTSMLPJ
#endif


   
/*****************************************************************************
 *                         PDCP LM PTMI
 ****************************************************************************/
#ifdef PTSMLPJ

EXTERN S16 PtMiLpjCfgReq ARGS((Pst * pst, PjMngmt * cfg));

EXTERN S16 PtMiLpjCntrlReq ARGS((Pst * pst, PjMngmt * cntl));

EXTERN S16 PtMiLpjStaReq ARGS((Pst * pst, PjMngmt * staReq));

EXTERN S16 PtMiLpjStsReq ARGS((Pst * pst, Action actn, PjMngmt * sts));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
PRIVATE S16 PtMiLpjL2MeasReq ARGS((Pst *pst,  PjL2MeasReqEvt *measReqEvt));
#endif
#endif /*--#ifdef PTSMLPJ--*/

#ifndef LCPJMILPJ
#define PTKWMILPJ
#endif
PRIVATE CONSTANT LpjCfgReq SmMiLpjCfgReqMt[] =
{
#ifdef LCPJMILPJ
   cmPkLpjCfgReq,
#else
   PtMiLpjCfgReq,
#endif
#ifdef PJ
   PjMiLpjCfgReq,
#else
   PtMiLpjCfgReq,
#endif
};


PRIVATE CONSTANT LpjCntrlReq SmMiLpjCntrlReqMt[] =
{
#ifdef LCPJMILPJ
   cmPkLpjCntrlReq,
#else
   PtMiLpjCntrlReq,
#endif
#ifdef PJ
   PjMiLpjCntrlReq,
#else
   PtMiLpjCntrlReq,
#endif
};


PRIVATE CONSTANT LpjStaReq SmMiLpjStaReqMt[] =
{
#ifdef LCPJMILPJ
   cmPkLpjStaReq,
#else
   PtMiLpjStaReq,
#endif
#ifdef PJ
   PjMiLpjStaReq,
#else
   PtMiLpjStaReq,
#endif
};


PRIVATE CONSTANT LpjStsReq SmMiLpjStsReqMt[] =
{
#ifdef LCPJMILPJ
   cmPkLpjStsReq,
#else
   PtMiLpjStsReq,
#endif
#ifdef PJ
   PjMiLpjStsReq,
#else
   PtMiLpjStsReq,
#endif
};

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
PRIVATE CONSTANT LpjL2MeasReq SmMiLpjL2MeasReqMt[] =
{
#ifdef LCPJMILPJ
   cmPkLpjL2MeasReq,
#else
   PtMiLpjL2MeasReq,
#endif
#ifdef PJ
   PjMiLpjL2MeasReq,
#else
   PtMiLpjL2MeasReq,
#endif
};
#endif

#ifdef SM
#ifdef ANSI
PUBLIC S16 SmMiLpjCfgReq
(
Pst * pst,
PjMngmt * cfg
)
#else
PUBLIC S16 SmMiLpjCfgReq(pst, cfg)
Pst * pst;
PjMngmt * cfg;
#endif
{

   TRC3(SmMiLpjCfgReq)

   (*SmMiLpjCfgReqMt[pst->selector])(pst, cfg);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 SmMiLpjCntrlReq
(
Pst * pst,
PjMngmt * cntl
)
#else
PUBLIC S16 SmMiLpjCntrlReq(pst, cntl)
Pst * pst;
PjMngmt * cntl;
#endif
{

   TRC3(SmMiLpjCntrlReq)

   (*SmMiLpjCntrlReqMt[pst->selector])(pst, cntl);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 SmMiLpjStaReq
(
Pst * pst,
PjMngmt * staReq
)
#else
PUBLIC S16 SmMiLpjStaReq(pst, staReq)
Pst * pst;
PjMngmt * staReq;
#endif
{

   TRC3(SmMiLpjStaReq)

   (*SmMiLpjStaReqMt[pst->selector])(pst, staReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 SmMiLpjStsReq
(
Pst * pst,
Action actn,
PjMngmt * sts
)
#else
PUBLIC S16 SmMiLpjStsReq(pst, actn, sts)
Pst * pst;
Action actn;
PjMngmt * sts;
#endif
{

   TRC3(SmMiLpjStsReq)

   (*SmMiLpjStsReqMt[pst->selector])(pst, actn, sts);

   RETVALUE(ROK);

}
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef ANSI
PUBLIC S16 SmMiLpjL2MeasReq 
(
Pst            *pst, 
PjL2MeasReqEvt *measReqEvt 
)
#else
PUBLIC S16 SmMiLpjL2MeasReq (pst, measReqEvt)
Pst            *pst; 
PjL2MeasReqEvt *measReqEvt;
#endif
{
   TRC3(SmMiLpjL2MeasReq )

   (*SmMiLpjL2MeasReqMt[pst->selector])(pst,measReqEvt);

   RETVALUE(ROK);
}
#endif
#endif /*--ifdef SM--*/

#ifdef PTKWMILPJ
#ifdef ANSI
PUBLIC S16 PtMiLpjCfgReq
(
Pst * pst,
PjMngmt * cfg
)
#else
PUBLIC S16 PtMiLpjCfgReq(pst, cfg)
Pst * pst;
PjMngmt * cfg;
#endif
{

   TRC3(PtMiLpjCfgReq)

   UNUSED(pst);
   UNUSED(cfg);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtMiLpjCntrlReq
(
Pst * pst,
PjMngmt * cntl
)
#else
PUBLIC S16 PtMiLpjCntrlReq(pst, cntl)
Pst * pst;
PjMngmt * cntl;
#endif
{

   TRC3(PtMiLpjCntrlReq)

   UNUSED(pst);
   UNUSED(cntl);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtMiLpjStaReq
(
Pst * pst,
PjMngmt * staReq
)
#else
PUBLIC S16 PtMiLpjStaReq(pst, staReq)
Pst * pst;
PjMngmt * staReq;
#endif
{

   TRC3(PtMiLpjStaReq)

   UNUSED(pst);
   UNUSED(staReq);

   RETVALUE(ROK);

}


#ifdef ANSI
PUBLIC S16 PtMiLpjStsReq
(
Pst * pst,
Action actn,
PjMngmt * sts
)
#else
PUBLIC S16 PtMiLpjStsReq(pst, actn, sts)
Pst * pst;
Action actn;
PjMngmt * sts;
#endif
{

   TRC3(PtMiLpjStsReq)

   UNUSED(pst);
   UNUSED(actn);
   UNUSED(sts);

   RETVALUE(ROK);

}
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef ANSI
PRIVTAE S16 PtMiLpjL2MeasReq 
(
Pst            *pst, 
PjL2MeasReqEvt *measReqEvt 
)
#else
PRIVATE S16 PtMiLpjL2MeasReq (pst, measReqEvt)
Pst            *pst; 
PjL2MeasReqEvt *measReqEvt;
#endif
{
   TRC3(PtMiLpjL2MeasReq)

   UNUSED(pst);
   UNUSED(measReqEvt);
}
#endif/* LTE_L2_MEAS */
#endif /*--ifdef PTSMLPJ--*/

  
/********************************************************************30**
  
         End of file:     sm_pj_ptmi.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:19 2014
  
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

