
/********************************************************************20**

     Name:     RRM Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     rm_ptmi.c

     Sid:      qf_ptmi.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:34 2013

     Prg:     jbm 

*********************************************************************21*/

/* header include files */

#include "rm.h"
#include "rm_cmn.h"

#if (!defined(LCSMRMMILRM) || !defined(TCSMRMMILRM) || !defined(LWLCSMRMMILRM))
#define PTWRMILWR
#endif

#define RM_MAX_SEL       3      /* maximum number of selectors */

/* forward references */
#ifdef PTWRMILWR
PUBLIC S16 PtMiLrmCfgCfm    (Pst *pst, RmMngmt *cfg);
PUBLIC S16 PtMiLrmCntrlCfm   (Pst *pst, RmMngmt *cfm );
#endif

/* private variable definitions */
PRIVATE LrmCfgCfm rmMiLrmCfgCfmMt[RM_MAX_SEL] =
{
#ifdef LCSMRMMILRM
   cmPkLrmCfgCfm,
#else
   PtMiLrmCfgCfm,
#endif

#ifdef TCSMRMMILRM 
#ifdef RMU_DM
   DmMiLrmCfgCfm,
#else
   SmMiLrmCfgCfm,
#endif /*RMU_DM*/
#else
   PtMiLrmCfgCfm,
#endif 

#ifdef LWLCSMRMMILRM
   cmPkLwLcLrmCfgCfm,
#else
   PtMiLrmCfgCfm,
#endif
};


/** @brief Control Confirm primitive Matrix */
PRIVATE CONSTANT LrmCntrlCfm RmMiLrmCntrlCfmMt[RM_MAX_SEL] =
{
#ifdef LCSMRMMILRM
   cmPkLrmCntrlCfm,
#else
   PtMiLrmCntrlCfm,
#endif

#ifdef TCSMRMMILRM 
#ifdef RMU_DM
   DmMiLrmCfgCfm,
#else
   SmMiLrmCntrlCfm,
#endif /*RMU_DM*/
#else
   PtMiLrmCntrlCfm,
#endif 

#ifdef LWLCSMRMMILRM
   cmPkLwLcLrmCntrlCfm
#else
   PtMiLrmCntrlCfm
#endif

};




/*
*     layer management interface functions
*/
/*
*
*       Fun:    RmMiLrmCfgCfm
*
*       Desc:   configuration confirm
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   rm_ptmi.c
*
*/

PUBLIC S16 RmMiLrmCfgCfm
(
Pst         *pst,
RmMngmt    *cfg
)
{
   S16 ret = ROK;

   TRC3(RmMiLrmCfgCfm)
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst == (Pst *)NULLP || pst->selector >= RM_MAX_SEL)
   {
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   ret = (*rmMiLrmCfgCfmMt[pst->selector])(pst, cfg);

   RETVALUE(ret);
}

/**
 * @brief Layer Manager Control confirm handler. 
 *
 * @details
 *
 *     Function : RmMiLrmCntrlCfm
 *     
 *     This function handles the control
 *     confirm invoked by RRM to Layer Manager.
 *     -# Based on the pst->selector value it invokes one of the
 *        functions cmPkLrmCntrlCfm() or SmMiLrmCntrlCfm().
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  RmMngmt *cfm, the control confirm structure
 *  @return  S16
 *      -# ROK
 **/
PUBLIC S16 RmMiLrmCntrlCfm
(
Pst      *pst,    /* post structure  */
RmMngmt  *cfm     /* control confirm structure  */
)
{
   
   TRC3(RmMiLrmCntrlCfm);

   (*RmMiLrmCntrlCfmMt[pst->selector])(pst,cfm);

   RETVALUE(ROK);
   
}/*-- RmMiLrmCntrlCfm --*/





/* Portable functions */
#ifdef PTWRMILWR
/*
*
*       Fun:    PtMiLrmCfgCfm
*
*       Desc:   Dummy configuration confirm, customize if necessary
*
*       Ret:    ROK     - succeeded
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   rm_ptmi.c
*
*/

PUBLIC S16 PtMiLrmCfgCfm
(
Pst                     *pst,
RmMngmt                 *cfm
)
{
   TRC3(PtMiLrmCfgCfm)
   UNUSED(pst);
   SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(RmMngmt));
   RETVALUE(RFAILED);
}

/**
 * @brief Portable Function definition for Layer Manager Control 
 *         confirm handler. 
 *
 * @details
 *
 *     Function : PtMiLrmCntrlCfm 
 *     
 *     This function handles the control 
 *     confirm invoked by RRM to Layer Manager.
 *     Users of RRM who intend to provide a glue logic 
 *     for portability of control Confirm are expected 
 *     to fill in the code in this function definition.
 *     
 *  @param[in]  Pst *pst, the post structure     
 *  @param[in]  RmMngmt *cfm, the control confirm structure
 *  @return  S16
 *      -# ROK
 **/
PUBLIC S16 PtMiLrmCntrlCfm
(
Pst *pst,               /* post structure */
RmMngmt *cfm            /* Control Confirm */
)
{
   TRC3(PtMiLrmCntrlCfm)
   SPutSBuf(pst->region, pst->pool, (Data *)cfm, sizeof(RmMngmt));
   RETVALUE(ROK);
}/* end of PtMiLrmCntrlCfm */


#endif

/********************************************************************30**

           End of file:     qf_ptmi.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:34 2013

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
*********************************************************************91*/
