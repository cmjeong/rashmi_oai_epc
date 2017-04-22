

/********************************************************************20**
  
        Name:     <name for the file for readability>
    
        Type:     <File type - C include file, C source file, make file>
  
        Desc:     <description of file contents>
 
        File:     sm_kw_ex_ms.c

        Sid:      sm_pj_ex_ms.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:19 2014
  
        Prg:      nm 
  
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
#include "cpj.h"           /* CPJ defines */
#include "pju.h"           /* PJU defines */
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
#include "cpj.x"           /* CPJ */
#include "pju.x"           /* PJU */
#include "lpj.x"           /* LPJ */


  
/* local defines */

/* local typedefs */

/* local externs */
  
/* forward references */

/* public variable declarations */

/* private variable declarations */

/*
 *   support functions
 */

/*
*
*       Fun:    smPjActvTsk
*
*       Desc:   Activation function for Layer Manager 
*
*       Ret:    ROK  - ok
*
*       Notes:  new version.
*
*       File:   sm_kw_ex_ms.c
*
*/


#ifdef ANSI
PUBLIC S16 smPjActvTsk
(
Pst     *pst,                                   /* post structure       */
Buffer  *mBuf                                   /* message buffer       */
)
#else
PUBLIC S16 smPjActvTsk(pst, mBuf)
Pst     *pst;                                   /* post structure       */
Buffer  *mBuf;                                  /* message buffer       */
#endif
{
   TRC2(smPjActvTsk)

   switch (pst->srcEnt)
   {
       case ENTPJ: /* message originates from stack manager */
       {
           switch (pst->event)
           {
#ifdef LCPJMILPJ
            case LPJ_EVT_CFG_CFM:
               cmUnpkLpjCfgCfm(SmMiLpjCfgCfm, pst, mBuf);
               break;
            case LPJ_EVT_CNTRL_CFM:
               cmUnpkLpjCntrlCfm(SmMiLpjCntrlCfm, pst, mBuf);
               break;
            case LPJ_EVT_STA_IND:
               cmUnpkLpjStaInd(SmMiLpjStaInd, pst, mBuf);
               break;
            case LPJ_EVT_STA_CFM:
               cmUnpkLpjStaCfm(SmMiLpjStaCfm, pst, mBuf);
               break;
            case LPJ_EVT_STS_CFM:
               cmUnpkLpjStsCfm(SmMiLpjStsCfm, pst, mBuf);
               break;
            case LPJ_EVT_TRC_IND:
               cmUnpkLpjTrcInd(SmMiLpjTrcInd, pst, mBuf);
               break;
/*kw005.201 added support for L2 Measurement */                   
#ifdef LTE_L2_MEAS
            case LPJ_EVT_L2MEAS_CFM:
               cmUnpkLpjL2MeasCfm(SmMiLpjL2MeasCfm, pst, mBuf);
               break;
#endif
#endif /* LCPJMILPJ */
               default:
               /* An invalid Event*/
                   SPutMsg(mBuf);
                   break;
           }
           break;

        default:
        /* Invalid Entity */
            SPutMsg(mBuf);
            break;
       }
    }
    SExitTsk();
    RETVALUE(ROK);
} /* End of smPjActvTsk */

/*
 *
 *     Fun  : smPjActvInit
 *
 *     Desc : Invoked by system services to initialize a task. Initilization
 *            parameters are copied into the gnInit structure for later
 *            use.
 *
 *     Ret  : ROK   - ok
 *
 *     Notes: None
 *
 *     File : smrlbdy1.c
 *
 */
#ifdef ANSI
PUBLIC S16 smPjActvInit
(
Ent             entity,                 /* entity id passed from SS     */
Inst            inst,                   /* instance id passed from SS   */
Region          region,                 /* region id passed from SS     */
Reason          reason                  /* reason for this (re)start-up */
)
#else
PUBLIC S16 smPjActvInit(entity, inst, region, reason)
Ent             entity;                 /* entity id passed from SS     */
Inst            inst;                   /* instance id passed from SS   */
Region          region;                 /* region id passed from SS     */
Reason          reason;                 /* reason for this (re)start-up */
#endif
{
   TRC2(smPjActvInit)
   UNUSED(entity);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);

   /* Initialisation Code to be added */

   RETVALUE(ROK);
} /* end of smPjActvInit */


  
/********************************************************************30**
  
         End of file:     sm_pj_ex_ms.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:19 2014
  
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
/main/2      ---  nm 1. Created for Release of LTE RLC 2.1.
/main/3      kw005.201 ap 1. Added support for L2 Measurement.
*********************************************************************91*/

