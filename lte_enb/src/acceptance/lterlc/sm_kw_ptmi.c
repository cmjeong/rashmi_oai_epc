

/********************************************************************20**
  
        Name:     Sample Layer Manager
    
        Type:     C source file
  
        Desc:     Sample Layer Manager for RLC Layer
 
        File:     sm_kw_ptmi.c

        Sid:      sm_kw_ptmi.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:09:03 2014
  
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
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "pju.h"           /* PJU defines */
#include "lpj.h"           /* LPJ defines */
#endif

#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

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
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "pju.x"           /* PJU */
#include "lpj.x"           /* LPJ */
#endif

#include "kw.x"

  
/* local defines */
#ifndef LCKWMILKW
#define PTSMLKW
#endif

#ifndef SM 
#define PTSMLKW
#endif

#ifdef KW_PDCP
#ifndef LCPJMILPJ
#define PTSMLPJ
#endif

#ifndef SM 
#define PTSMLPJ
#endif
#endif /* KW_PDCP */

   
/*****************************************************************************
 *                         RLC LM PTMI
 ****************************************************************************/
#ifdef PTSMLKW
/* forward references */
PRIVATE S16 PtMiLkwCfgReq   ARGS((Pst *pst, KwMngmt *cfg ));
PRIVATE S16 PtMiLkwCntrlReq   ARGS((Pst *pst, KwMngmt *cfg ));
PRIVATE S16 PtMiLkwStaReq   ARGS((Pst *pst, KwMngmt *sta ));
PRIVATE S16 PtMiLkwStsReq   ARGS((Pst *pst, Action action, KwMngmt *sts ));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
PRIVATE S16 PtMiLkwL2MeasReq ARGS((Pst *pst,  KwL2MeasReqEvt *measReqEvt));
#endif
#endif

/* public variable declarations */

/* private variable declarations */

/* config request primitive */

PRIVATE LkwCfgReq smMiLkwCfgReqMt[] =
{
#ifdef LCKWMILKW
   cmPkLkwCfgReq,          /* 0 - loosely coupled - fc */
#else
   PtMiLkwCfgReq,          /* 0 - loosely coupled portable */
#endif /* LCKWMILKW */
#ifdef KW
   KwMiLkwCfgReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLkwCfgReq,          /* 1 - tightly coupled portable */
#endif /* RL */
};

/* control request primitive */
PRIVATE LkwCntrlReq smMiLkwCntrlReqMt[] =
{
#ifdef LCKWMILKW 
   cmPkLkwCntrlReq,          /* 0 - loosely coupled - fc */
#else
   PtMiLkwCntrlReq,          /* 0 - tightly coupled, portable */
#endif /* LCKWMILKW */
#ifdef KW 
   KwMiLkwCntrlReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLkwCntrlReq,          /* 1 - tightly coupled, portable */
#endif /* RL */
};

/* solicited status request primitive */
PRIVATE LkwStaReq smMiLkwStaReqMt[] =
{
#ifdef LCKWMILKW
   cmPkLkwStaReq,          /* 0 - loosely coupled - fc */
#else
   PtMiLkwStaReq,          /* 0 - tightly coupled, portable */
#endif /* LCKWMILKW */
#ifdef KW
   KwMiLkwStaReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLkwStaReq,          /* 1 - tightly coupled, portable */
#endif /* RL */
};

/* statistics request primitive */
PRIVATE LkwStsReq smMiLkwStsReqMt[] =
{
#ifdef LCKWMILKW
   cmPkLkwStsReq,          /* 0 - loosely coupled - fc */
#else
   PtMiLkwStsReq,          /* 0 - tightly coupled, portable */
#endif /* LCKWMILKW */
#ifdef KW
   KwMiLkwStsReq,          /* 1 - tightly coupled, layer management */
#else
   PtMiLkwStsReq,          /* 1 - tightly coupled, portable */
#endif /* RL */
};


/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
PRIVATE CONSTANT LkwL2MeasReq SmMiLkwL2MeasReqMt[] =
{
#ifdef LCKWMILKW
   cmPkLkwL2MeasReq,
#else
   PtMiLkwL2MeasReq,
#endif
#ifdef PJ
   KwMiLkwL2MeasReq,
#else
   PtMiLkwL2MeasReq,
#endif
};
#endif
/*
*     layer management interface functions
*/

/*
*
*       Fun:   Configuration request
*
*       Desc:  This function is used to configure
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sm_kw_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLkwCfgReq
(
Pst *pst,                 /* post structure */
KwMngmt *cfg              /* configure */
)
#else
PUBLIC S16 SmMiLkwCfgReq(pst, cfg)
Pst *pst;                 /* post structure */
KwMngmt *cfg;             /* configure */
#endif
{
   TRC3(SmMiLkwCfgReq)
   /* jump to specific primitive depending on configured selector */
   (*smMiLkwCfgReqMt[pst->selector])(pst, cfg);
   RETVALUE(ROK);

} /* end SmMiLkwCfgReq */


/*
*
*       Fun:   Control request
*
*       Desc:  This function is used to control 
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sm_kw_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLkwCntrlReq
(
Pst *pst,                 /* post structure */
KwMngmt *cntrl            /* control */
)
#else
PUBLIC S16 SmMiLkwCntrlReq(pst, cntrl)
Pst *pst;                 /* post structure */
KwMngmt *cntrl;           /* control */
#endif
{
   TRC3(SmMiLkwCntrlReq)
   /* jump to specific primitive depending on configured selector */
   (*smMiLkwCntrlReqMt[pst->selector])(pst, cntrl);
   RETVALUE(ROK);
} /* end of SmMiLkwCntrlReq */


/*
*
*       Fun:   Status request 
*
*       Desc:  This function is used to request status from RLC
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sm_kw_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLkwStaReq
(
Pst *pst,                 /* post structure */
KwMngmt *sta              /* status */
)
#else
PUBLIC S16 SmMiLkwStaReq(pst, sta)
Pst *pst;                 /* post structure */
KwMngmt *sta;             /* status */
#endif
{
   TRC3(SmMiLkwStaReq)
   /* jump to specific primitive depending on configured selector */
   (*smMiLkwStaReqMt[pst->selector])(pst, sta);
   RETVALUE(ROK);

} /* end SmMiLkwStaReq */


/*
*
*       Fun:   Statistics request
*
*       Desc:  This function is used to request statistics  
*              from RLC
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sm_kw_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 SmMiLkwStsReq
(
Pst *pst,                 /* post structure */
Action action,            /* action */
KwMngmt *sts              /* statistics */
)
#else
PUBLIC S16 SmMiLkwStsReq(pst, action, sts)
Pst *pst;                 /* post structure */
Action action;            /* action */
KwMngmt *sts;             /* statistics */
#endif
{
   TRC3(SmMiLkwStsReq)
   /* jump to specific primitive depending on configured selector */
   (*smMiLkwStsReqMt[pst->selector])(pst, action, sts);
   RETVALUE(ROK);

} /* end SmMiLkwStsReq */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef ANSI
PUBLIC S16 SmMiLkwL2MeasReq 
(
Pst            *pst, 
KwL2MeasReqEvt *measReqEvt 
)
#else
PUBLIC S16 SmMiLkwL2MeasReq (pst, measReqEvt)
Pst            *pst; 
KwL2MeasReqEvt *measReqEvt;
#endif
{
   TRC3(SmMiLkwL2MeasReq )

   (*SmMiLkwL2MeasReqMt[pst->selector])(pst,measReqEvt);

   RETVALUE(ROK);
}
#endif
#ifdef PTSMLKW
/*
*
*       Fun:   Portable configure Request RLC
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sm_kw_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLkwCfgReq
(
Pst *pst,                   /* post structure */
KwMngmt *cfg                /* configure */
)
#else
PRIVATE S16 PtMiLkwCfgReq(pst, cfg)
Pst *pst;                   /* post structure */
KwMngmt *cfg;               /* configure */
#endif
{
  TRC3(PtMiLkwCfgReq);
  UNUSED(cfg);
  UNUSED(pst);
  TRC2(this function is not implemented)
  RETVALUE(ROK);
} /* end of PtMiLkwCfgReq */


/*
*
*       Fun:   Portable control Request RLC 
*
*       Desc: 
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sm_kw_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLkwCntrlReq
(
Pst *pst,                   /* post structure */
KwMngmt *cntrl              /* control */
)
#else
PRIVATE S16 PtMiLkwCntrlReq(pst, cntrl)
Pst *pst;                   /* post structure */
KwMngmt *cntrl;             /* control */
#endif
{
  TRC3(PtMiLkwCntrlReq);

  UNUSED(cntrl);
  UNUSED(pst);
  TRC2(this function is not implemented)
  RETVALUE(ROK);
} /* end of PtMiLkwCntrlReq */


/*
*
*       Fun:   Portable status request function
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sm_kw_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLkwStaReq
(
Pst *pst,                   /* post structure */
KwMngmt *sta                /* status */
)
#else
PRIVATE S16 PtMiLkwStaReq(pst, sta)
Pst *pst;                   /* post structure */
KwMngmt *sta;               /* status */
#endif
{
  TRC3(PtMiLkwStaReq);

  UNUSED(sta);
  UNUSED(pst);

  RETVALUE(ROK);
} /* end of PtMiLkwStaReq */


/*
*
*       Fun:   Portable statistics  request function
*
*       Desc:
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  sm_kw_ptmi.c
*
*/

#ifdef ANSI
PRIVATE S16 PtMiLkwStsReq
(
Pst *pst,                   /* post structure */
Action action,              /* action */
KwMngmt *sts                /* statistics */
)
#else
PRIVATE S16 PtMiLkwStsReq(pst, action, sts)
Pst *pst;                   /* post structure */
Action action;              /* action */
KwMngmt *sts;               /* statistics */
#endif
{
  TRC3(PtMiLkwStaReq);

  UNUSED(sts);
  UNUSED(action);
  UNUSED(pst);

   KWDBGP((KW_DBGMASK_INF | KW_DBGMASK_DETAIL),
       (_kwPBuf, "PtMiLkwStsReq\n"));
  RETVALUE(ROK);
} /* end of PtMiLkwStsReq */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef ANSI
PRIVTAE S16 PtMiLkwL2MeasReq 
(
Pst            *pst, 
KwL2MeasReqEvt *measReqEvt 
)
#else
PRIVATE S16 PtMiLkwL2MeasReq (pst, measReqEvt)
Pst            *pst; 
KwL2MeasReqEvt *measReqEvt;
#endif
{
   TRC3(PtMiLkwL2MeasReq)

   UNUSED(pst);
   UNUSED(measReqEvt);
}
#endif/* LTE_L2_MEAS */
#endif /* PTSMLKW */

   
/*****************************************************************************
 *                         PDCP LM PTMI
 ****************************************************************************/
#ifdef KW_PDCP
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
#endif /* KW_PDCP */

  
/********************************************************************30**
  
         End of file:     sm_kw_ptmi.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:09:03 2014
  
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

