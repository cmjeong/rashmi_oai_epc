

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     rgac_lm_ex_ms.c 
  
     Sid:      lm_ex_ms.c@@/main/3 - Sat Jul 30 02:22:20 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_lm_ex_ms.c
@brief This file contains the SSI register functions of dummy LM.
*/

/* header include files -- defines (.h) */
#include "rgac_acc.x"
#include "rgac_acc.h"         /* defines for MAC acceptance tests */
#include "rgac_lrg.h"      /* XTA_ACC definitions specific for RGU */
#include "rgac_acc.x"         /* typedefs for MAC acceptance tests */
#include "rgac_lrg.x"      /* XTA_ACC definitions specific for RGU */



/** @brief This is the activation task of the dummy layer manager. 
 * @param pst pointer to the Pst structure
 * @param mBuf pointer to the Buffer. 
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 smRgActvTsk
(
 Pst     *pst,
 Buffer  *mBuf
 )
#else
PUBLIC S16 smRgActvTsk (pst, mBuf)
 Pst     *pst;
 Buffer  *mBuf;
#endif
{
   S16 ret;

   TRC3(smRgActvTsk)

   ret = ROK;
   switch(pst->srcEnt)
   {
      case ENTRG:
         {
            switch (pst->event)
            {
#ifdef LCLRG
               case RGAC_LRG_EVTCFGCFM:
                  ret = cmUnpkLrgCfgCfm (SmMiLrgCfgCfm, pst, mBuf);
                  break;
               case RGAC_LRG_EVTSCHCFGCFM:
                  ret = cmUnpkLrgSchCfgCfm(SmMiLrgSchCfgCfm, pst, mBuf);
                  break;
               case RGAC_LRG_EVTCNTRLCFM:
                  ret = cmUnpkLrgCntrlCfm (SmMiLrgCntrlCfm, pst, mBuf);
                  break;
               case RGAC_LRG_EVTSCHCNTRLCFM:
                  ret = cmUnpkLrgSchCntrlCfm(SmMiLrgSchCntrlCfm, pst, mBuf);
                  break;
               case RGAC_LRG_EVTSTSCFM:
                  ret = cmUnpkLrgStsCfm (SmMiLrgStsCfm, pst, mBuf);
                  break;
               case RGAC_LRG_EVTSTACFM:
                  ret = cmUnpkLrgStaCfm (SmMiLrgStaCfm, pst, mBuf);
                  break;
               case RGAC_LRG_EVTSTAIND:
                  ret = cmUnpkLrgStaInd (SmMiLrgStaInd, pst, mBuf);
                  break;
               case RGAC_LRG_EVTSCHSTAIND:
                  ret = cmUnpkLrgSchStaInd (SmMiLrgSchStaInd, pst, mBuf);
                  break;
               case RGAC_LRG_EVTTRCIND:
                  ret = cmUnpkLrgTrcInd (SmMiLrgTrcInd, pst, mBuf);
                  break;
#ifdef LTE_L2_MEAS
               case RGAC_LRG_EVTL2MEASCFM:
                  ret = cmUnpkLrgSchL2MeasCfm(SmMiLrgSchL2MeasCfm, pst, mBuf);
                  break;
#endif
#endif
               default:
                  CMXTA_DBG_ERR((_cmxtap, "smRgActvTsk(): Message from an invalid entity! \n"));
                  ret = RFAILED;
                  break;

            } /* end of switch (evnt) */
         }
         break;
      default:
         CMXTA_DBG_ERR((_cmxtap, "smRgActvTsk(): Message from an invalid entity! \n"));
         ret = RFAILED;

   } /* end of switch */

   SExitTsk();
   RETVALUE (ret);
} /* end of smRgActvTsk */

/** @brief This is the activation task of Dummy layer manager, its called by
 * SSI to initialize the layer. 
 * @param ent
 * @param inst
 * @param region
 * @reason reason
 */
#ifdef ANSI
PUBLIC S16 smRgActvInit
(
 Ent     ent,
 Inst    inst,
 Region  region,
 Reason  reason
 )
#else
PUBLIC S16 smRgActvInit (ent, inst, region, reason)
 Ent     ent;
 Inst    inst;
 Region  region;
 Reason  reason;
#endif
{
   TRC2(smRgActvInit)
   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
}


/**********************************************************************
 
         End of file:     lm_ex_ms.c@@/main/3 - Sat Jul 30 02:22:20 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm                1. Initial Release.
/main/2      ---     sm                1. LTE MAC 2.1 release
/main/3      ---     gj                1. LTE MAC 3.1 Release.
*********************************************************************91*/
