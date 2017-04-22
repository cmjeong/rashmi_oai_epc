
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     C code for the APIs implemented by the layer manager, viz.
               LWR confirms and indications

     File:     wr_ptmi.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#include "wr.h" 
#include "wr_lwr.h"

#if (!defined(LCWRMILWR) || !defined(SM) || !defined(LWLCWRMILWR))
#define PTWRMILWR
#endif

#define WR_LWR_MAX_SEL       3      /* maximum number of selectors */

/* forward references */
#ifdef PTWRMILWR
PRIVATE S16 PtMiLwrCfgCfm    (Pst *pst, LwrMngmt *cfg);
PRIVATE S16 PtMiLwrCntrlCfm  (Pst *pst, LwrMngmt *cntrl);
PRIVATE S16 PtMiLwrStaInd  (Pst *pst, LwrMngmt *usta);
PUBLIC S16 PtMiLwrAddNeighCfgReq(Pst *pst,LwrMngmt *cntrl);
PUBLIC S16 PtMiLwrDynCfgCfm(Pst *pst,LwrDynMngmt *cfgCfm);
PUBLIC S16 PtMiLwrAddNeighCfgReq(Pst  *pst,LwrMngmt   *cntrl);
PUBLIC S16 PtMiLwrUpDateNhgCellCfgReq(Pst *pst,LwrMngmt *cntrl);
#endif
PUBLIC S16 WrMiLwrDynCfgCfm(Pst *pst,LwrDynMngmt *dynCfm);
PUBLIC S16 WrMiLwrAddNeighCfgReq(Pst  *pst,LwrMngmt   *cfgReq );

EXTERN S16 SmMiLwrUpDateNhgCellCfgReq(Pst *pst,LwrMngmt *nghCellCfgReq);
EXTERN S16 cmPkLwrUpDateNhgCellCfgReq (Pst *pst,LwrMngmt *cfg);

/* Status Indication primitive */
PRIVATE LwrStaInd WrMiLwrStaIndMt[WR_LWR_MAX_SEL] =
{
#ifdef LCWRMILWR
   cmPkLwrStaInd,          /* 0 - loosely coupled  */
#else
   PtMiLwrStaInd,          /* 0 - loosely coupled, portable */
#endif /* LCWRMILWR */
#ifdef SM
   SmMiLwrStaInd,          /* 1 - tightly coupled, layer management */
#else
   PtMiLwrStaInd,          /* 1 - tightly coupled, portable */
#endif /* SM */
#ifdef LWLCWRMILWR
   cmPkLwrStaInd,          /* 2 - Light weight loosely coupled  */
#else
   PtMiLwrStaInd,          /* 2 - Light weight loosely, portable */
#endif /* LCWRMILWR */
};

/* private variable definitions */
PRIVATE LwrCfgCfm wrMiLwrCellCfgCfmMt[WR_LWR_MAX_SEL] =
{
#ifdef LCWRMILWR
   cmPkLwrCellCfgCfm,            /* 0 - loosely coupled  */
#else
   PtMiLwrCfgCfm,            /* 0 - loosely coupled, portable */
#endif 
#ifdef SM                                                                
   SmMiCellLwrCfgCfm,        /* 1 - tightly coupled, layer management */
#else                                                                    
   PtMiLwrCfgCfm,            /* 1 - tightly coupled, portable */
#endif /* SM */                                                          
#ifdef LWLCWRMILWR
   cmPkLwrCellCfgCfm,            /* 2 - Light weight loosely coupled  */
#else
   PtMiLwrCfgCfm,            /* 2 - Light weight loosely, portable */
#endif  
};
/* private variable definitions */
PRIVATE LwrCfgCfm wrMiLwrCfgCfmMt[WR_LWR_MAX_SEL] =
{
#ifdef LCWRMILWR
   cmPkLwrCfgCfm,            /* 0 - loosely coupled  */
#else
   PtMiLwrCfgCfm,            /* 0 - loosely coupled, portable */
#endif 
#ifdef SM                                                                
   SmMiLwrCfgCfm,            /* 1 - tightly coupled, layer management */
#else                                                                    
   PtMiLwrCfgCfm,            /* 1 - tightly coupled, portable */
#endif /* SM */                                                          
#ifdef LWLCWRMILWR
   cmPkLwrCfgCfm,            /* 2 - Light weight loosely coupled  */
#else
   PtMiLwrCfgCfm,            /* 2 - Light weight loosely, portable */
#endif  
};
PRIVATE LwrCfgCfm wrMiDamLwrCfgCfmMt[WR_LWR_MAX_SEL] =
{
#ifdef LCWRMILWR
   cmPkLwrCfgCfm,            /* 0 - loosely coupled  */
#else
   PtMiLwrCfgCfm,            /* 0 - loosely coupled, portable */
#endif 
#ifdef SM                                                                
   SmMiDamLwrCfgCfm,            /* 1 - tightly coupled, layer management */
#else                                                                    
   PtMiLwrCfgCfm,            /* 1 - tightly coupled, portable */
#endif /* SM */                                                          
#ifdef LWLCWRMILWR
   cmPkLwrCfgCfm,            /* 2 - Light weight loosely coupled  */
#else
   PtMiLwrCfgCfm,            /* 2 - Light weight loosely, portable */
#endif  
};
PRIVATE LwrCntrlCfm wrMiLwrCellCntrlCfmMt[WR_LWR_MAX_SEL] =
{
#ifdef LCWRMILWR
   cmPkLwrCellCntrlCfm,       /* 0 - loosely coupled  */
#else
   PtMiLwrCntrlCfm,       /* 0 - loosely coupled, portable */
#endif
#ifdef SM                                                             
   SmMiLwrCellCntrlCfm,       /* 1 - tightly coupled, layer management */
#else
   PtMiLwrCntrlCfm,       /* 1 - tightly coupled, portable */
#endif 
#ifdef LWLCWRMILWR                                                    
   cmPkLwrCellCntrlCfm,       /* 2 - Light weight loosely coupled  */
#else
   PtMiLwrCntrlCfm,       /* 2 - Light weight loosely, portable */
#endif
};
PRIVATE LwrCntrlCfm wrMiLwrCntrlCfmMt[WR_LWR_MAX_SEL] =
{
#ifdef LCWRMILWR
   cmPkLwrCntrlCfm,       /* 0 - loosely coupled  */
#else
   PtMiLwrCntrlCfm,       /* 0 - loosely coupled, portable */
#endif
#ifdef SM                                                             
   SmMiLwrCntrlCfm,       /* 1 - tightly coupled, layer management */
#else
   PtMiLwrCntrlCfm,       /* 1 - tightly coupled, portable */
#endif 
#ifdef LWLCWRMILWR                                                    
   cmPkLwrCntrlCfm,       /* 2 - Light weight loosely coupled  */
#else
   PtMiLwrCntrlCfm,       /* 2 - Light weight loosely, portable */
#endif
};
PRIVATE LwrUpDateNhgCellCfg wrMiLwrUpDateNhgCellCfgMt[WR_LWR_MAX_SEL] =
{
#ifdef LCWRMILWR
   cmPkLwrUpDateNhgCellCfgReq,    /* 0 - loosely coupled  */
#else
   PtMiLwrUpDateNhgCellCfgReq,    /* 0 - loosely coupled, portable */
#endif
#ifdef SM                                                           
   SmMiLwrUpDateNhgCellCfgReq,    /* 1 - tightly coupled, layer management */
#else
   PtMiLwrUpDateNhgCellCfgReq,    /* 1 - tightly coupled, portable */
#endif 
#ifdef LWLCWRMILWR                                                  
   cmPkLwrUpDateNhgCellCfgReq,    /* 2 - Light weight loosely coupled  */
#else
   PtMiLwrUpDateNhgCellCfgReq,    /* 2 - Light weight loosely, portable */
#endif
}; 

PRIVATE LwrDynCfgCfm wrMiLwrDynCfgCfmMt[WR_LWR_MAX_SEL] =
{
#ifdef LCWRMILWR
   cmPkLwrDynCfgCfm,    /* 0 - loosely coupled  */
#else
   PtMiLwrDynCfgCfm,    /* 0 - loosely coupled, portable */
#endif
#ifdef SM                                                           
   SmMiLwrDynCfgCfm,    /* 1 - tightly coupled, layer management */
#else
   PtMiLwrDynCfgCfm,    /* 1 - tightly coupled, portable */
#endif 
#ifdef LWLCWRMILWR                                                  
   cmPkLwrDynCfgCfm,    /* 2 - Light weight loosely coupled  */
#else
   PtMiLwrDynCfgCfm,    /* 2 - Light weight loosely, portable */
#endif
}; 

PRIVATE LwrCntrlReq wrMiLwrAddNeighCfgReqMt[WR_LWR_MAX_SEL] =
{
#ifdef LCWRMILWR
   cmPkLwrAddNeighCfgReq,    /* 0 - loosely coupled  */
#else
   PtMiLwrAddNeighCfgReq,    /* 0 - loosely coupled, portable */
#endif
#ifdef SM                                                                
   SmMiLwrAddNeighCfgReq,    /* 1 - tightly coupled, layer management */
#else
   PtMiLwrAddNeighCfgReq,    /* 1 - tightly coupled, portable */
#endif 
#ifdef LWLCWRMILWR                                                       
   cmPkLwrAddNeighCfgReq,    /* 2 - Light weight loosely coupled  */
#else
   PtMiLwrAddNeighCfgReq,    /* 2 - Light weight loosely, portable */
#endif
}; 
/*
*     layer management interface functions
*/
/*
*
*       Fun:    WrMiLwrCfgCfm
*
*       Desc:   configuration confirm
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   wr_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 WrMiLwrCfgCfm
(
Pst         *pst,
LwrMngmt    *cfg
)
#else
PUBLIC S16 WrMiLwrCfgCfm(pst, cfg)
Pst         *pst;
LwrMngmt    *cfg;
#endif /* ANSI */
{
   TRC3(WrMiLwrCfgCfm)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= WR_LWR_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   RETVALUE((*wrMiLwrCfgCfmMt[pst->selector])(pst, cfg));
}
/*
*     layer management interface functions
*/
/*
*
*       Fun:    WrMiLwrCellCfgCfm
*
*       Desc:   configuration confirm
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   wr_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 WrMiLwrCellCfgCfm
(
Pst         *pst,
LwrMngmt    *cfg
)
#else
PUBLIC S16 WrMiLwrCellCfgCfm(pst, cfg)
Pst         *pst;
LwrMngmt    *cfg;
#endif /* ANSI */
{
   TRC3(WrMiLwrCellCfgCfm)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= WR_LWR_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   RETVALUE((*wrMiLwrCellCfgCfmMt[pst->selector])(pst, cfg));
}
/*
*
*       Fun:    WrMiDamLwrCfgCfm
*
*       Desc:   configuration confirm
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   wr_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 WrMiDamLwrCfgCfm
(
Pst         *pst,
LwrMngmt    *cfg
)
#else
PUBLIC S16 WrMiDamLwrCfgCfm(pst, cfg)
Pst         *pst;
LwrMngmt    *cfg;
#endif /* ANSI */
{
   TRC3(WrMiDamLwrCfgCfm)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= WR_LWR_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   RETVALUE((*wrMiDamLwrCfgCfmMt[pst->selector])(pst, cfg));
}
/*
*
*       Fun:    WrMiLwrCntrlCfm
*
*       Desc:   control confirm
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   rr_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 WrMiLwrCntrlCfm
(
Pst         *pst,             /* post structure */         
LwrMngmt      *cntrl            /* management structure */   
)
#else
PUBLIC S16 WrMiLwrCntrlCfm(pst, cntrl)
Pst         *pst;             /* post structure */         
LwrMngmt     *cntrl;           /* management structure */   
#endif
{
   TRC3(WrMiLwrCntrlCfm)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= WR_LWR_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   RETVALUE((*wrMiLwrCntrlCfmMt[pst->selector])(pst, cntrl));
}
/*
*
*       Fun:    WrMiLwrCellCntrlCfm
*
*       Desc:   control confirm
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   rr_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 WrMiLwrCellCntrlCfm
(
Pst         *pst,             /* post structure */         
LwrMngmt      *cntrl            /* management structure */   
)
#else
PUBLIC S16 WrMiLwrCellCntrlCfm(pst, cntrl)
Pst         *pst;             /* post structure */         
LwrMngmt     *cntrl;           /* management structure */   
#endif
{
   TRC3(WrMiLwrCellCntrlCfm)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= WR_LWR_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   RETVALUE((*wrMiLwrCellCntrlCfmMt[pst->selector])(pst, cntrl));
}
/**
*
*       Fun:   WrMiLwrUpDateNhgCellCfg 
*
*       Desc:  send neighbor cell info to sm 
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   fc_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 WrMiLwrUpDateNhgCellCfg 
(
Pst         *pst,             /* post structure */         
LwrMngmt    *nghCellCfg
)
#else
PUBLIC S16 WrMiLwrUpDateNhgCellCfg(pst, nghCellCfg)
Pst         *pst;             /* post structure */         
LwrMngmt    *nghCellCfg;
#endif
{
   TRC3(WrMiLwrUpDateNhgCellCfg)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= WR_LWR_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   RETVALUE((*wrMiLwrUpDateNhgCellCfgMt[pst->selector])(pst, nghCellCfg));
}


/**
*
*       Fun:    WrMiLwrDynCfgCfm
*
*       Desc:   control confirm
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   rr_ptmi.c
*
*/
#ifdef ANSI
PUBLIC S16 WrMiLwrDynCfgCfm
(
Pst         *pst,             /* post structure */         
LwrDynMngmt *dynCfm
)
#else
PUBLIC S16 WrMiLwrDynCfgCfm(pst, cntrl)
Pst         *pst;             /* post structure */         
LwrDynMngmt *dynCfm;
#endif
{
   TRC3(WrMiLwrDynCfgCfm)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= WR_LWR_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   RETVALUE((*wrMiLwrDynCfgCfmMt[pst->selector])(pst, dynCfm));
}

/**************************************************************************
 *
 *      Fun:  WrMiLwrStaInd  
 *
 *      Desc: Used to indicate the status of the RRC layer to the layer manager. 
 *
 *      Ret:  ROK - OK 
 *
 *      Notes:None 
 *
 *      File:  wr_ptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 WrMiLwrStaInd
(
Pst *pst,                 /* Post structure */
LwrMngmt *usta             /* Unsolicited status */
)
#else
PUBLIC S16 WrMiLwrStaInd(pst, usta)
Pst *pst;                 /* Post structure */   
LwrMngmt *usta;            /* Unsolicited status */
#endif
{
   TRC3(WrMiLwrStaInd);

   /* jump to specific primitive depending on configured selector */
   (*WrMiLwrStaIndMt[pst->selector])(pst, usta); 

   RETVALUE(ROK);
} /* end of function WrMiLwrStaInd */


/* Portable functions */
#ifdef PTWRMILWR
/*
*
*       Fun:    PtMiLwrCfgCfm
*
*       Desc:   Dummy configuration confirm, customize if necessary
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   wr_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 PtMiLwrCfgCfm
(
Pst                     *pst,
LwrMngmt                *cfg
)
#else
PUBLIC S16 PtMiLwrCfgCfm(pst, cfg)
Pst                     *pst;
LwrMngmt                *cfg;
#endif
{
   TRC3(PtMiLwrCfgCfm)
   UNUSED(pst);
   UNUSED(cfg);
   RETVALUE(RFAILED);
}

/*
*
*       Fun:    PtMiLwrCntrlCfm
*
*       Desc:   Dummy control confirm, customize if necessary
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   wr_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 PtMiLwrCntrlCfm
(
Pst                     *pst,
LwrMngmt                *cntrl
)
#else
PUBLIC S16 PtMiLwrCntrlCfm(pst, cntrl)
Pst                     *pst;
LwrMngmt                *cntrl;
#endif
{
   TRC3(PtMiLwrCntrlCfm)
   UNUSED(pst);
   UNUSED(cntrl);
   RETVALUE(RFAILED);
}
/*
*
*       Fun:   PtMiLwrUpDateNhgCellCfgReq 
*
*       Desc:   Dummy control confirm, customize if necessary
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   wr_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 PtMiLwrUpDateNhgCellCfgReq 
(
Pst                     *pst,
LwrMngmt                *cntrl
)
#else
PUBLIC S16 PtMiLwrUpDateNhgCellCfgReq(pst, cntrl)
Pst                     *pst;
LwrMngmt                *cntrl;
#endif
{
   TRC3(PtMiLwrCntrlCfm)
   UNUSED(pst);
   UNUSED(cntrl);
   RETVALUE(RFAILED);
}/*end of PtMiLwrUpDateNhgCellCfgReq*/




/**
*
*       Fun:    
*
*       Desc:   Dummy Dynnamic confirm, customize if necessary
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   wr_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 PtMiLwrDynCfgCfm
(
Pst         *pst,
LwrDynMngmt *cfgCfm

)
#else
PUBLIC S16 PtMiLwrDynCfgCfm(pst, cfgCfm)
Pst         *pst,
LwrDynMngmt *cfgCfm
#endif
{
   TRC3(PtMiLwrCntrlCfm)
   UNUSED(pst);
   UNUSED(cfgCfm);
   RETVALUE(RFAILED);
}


/**************************************************************************
 *
 *      Fun:  PtMiLwrStaInd (Portable) 
 *
 *      Desc: Used to indicate the status of the RRC layer to the layer manager. 
 *
 *      Ret:  ROK - OK 
 *
 *      Notes:None 
 *
 *      File:  wr_ptmi.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 PtMiLwrStaInd
(
Pst *pst,                 /* Post structure */
LwrMngmt *usta             /* Unsolicited status */
)
#else
PUBLIC S16 PtMiLwrStaInd(pst, usta)
Pst *pst;                 /* Post structure */   
LwrMngmt *usta;            /* Unsolicited status */
#endif
{
   TRC3(PtMiLwrStaInd);

   UNUSED(pst);
   UNUSED(usta);


   RETVALUE(ROK);
} /* end of PtMiLwrStaInd */

/*
*
*       Fun:    PtMiLwrCntrlCfm
*
*       Desc:   Dummy control confirm, customize if necessary
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   wr_ptmi.c
*
*/

#ifdef ANSI
PUBLIC S16 PtMiLwrAddNeighCfgReq
(
Pst                     *pst,
LwrMngmt                *cntrl
)
#else
PUBLIC S16 PtMiLwrAddNeighCfgReq(pst, cntrl)
Pst                     *pst;
LwrMngmt                *cntrl;
#endif
{
   TRC3(PtMiLwrAddNeighCfgReq)
   UNUSED(pst);
   UNUSED(cntrl);
   RETVALUE(RFAILED);
}

#endif

/*
 * *
 * *       Fun:    WrMiLwrAddNeighCfgReq
 * *
 * *       Desc:   control confirm
 * *
 * *       Ret:    ROK     - succeeded
 * *               RFAILED - failed
 * *
 * *       Notes:  None
 * *
 * *       File:   wr_ptmi.c
 * *
 * */

#ifdef ANSI
PUBLIC S16 WrMiLwrAddNeighCfgReq
(
Pst         *pst,             /* post structure */
LwrMngmt    *cfgReq            /* management structure */
)
#else
PUBLIC S16 WrMiLwrAddNeighCfgReq(pst, cfgReq)
Pst         *pst;             /* post structure */
LwrMngmt    *cfgReq;           /* management structure */
#endif
{
   TRC3(WrMiLwrAddNeighCfgReq)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= WR_LWR_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   RETVALUE((*wrMiLwrAddNeighCfgReqMt[pst->selector])(pst, cfgReq));
}
 



/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
