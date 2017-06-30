

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     rgac_kw_ex_ms.c 
  
     Sid:      kw_ex_ms.c@@/main/3 - Sat Jul 30 02:22:19 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_kw_ex_ms.c
@brief This file contains the SSI register functions of dummy RLC.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_lte.h"        /* Common LTE Defines */
#include "cm_xta.h"        /* Common LTE Defines */
#include "rg_env.h"        /* MAC Environment Defines */
#include "crg.h"           /* CRG Interface defines */
#include "rgr.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_rgu.h"
#include "rgac_acc.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_xta.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */
#include "rgr.x"           /* RGR Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"
#include "rgac_rgu.x"        /* MAC error defines */


/** @brief This is the activation task of the dummy RLC layer. 
 * @param pst pointer to the Pst structure
 * @param mBuf pointer to the Buffer. 
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcKwActvTsk
(
 Pst     *pst,
 Buffer  *mBuf
 )
#else
PUBLIC S16 rgAcKwActvTsk (pst, mBuf)
 Pst     *pst;
 Buffer  *mBuf;
#endif
{
   S16 ret;

   TRC3(rgAcKwActvTsk)

   ret = ROK;
   switch(pst->srcEnt)
   {
      case ENTRG:
         {
            switch (pst->event)
            {
#ifdef LCRGU
               case RGAC_RGU_EVTCSTAIND:
                  ret = cmUnpkRguCStaInd (KwLiRguCStaInd, pst, mBuf);
                  break;
               case RGAC_RGU_EVTDSTAIND:
                  ret = cmUnpkRguDStaInd (KwLiRguDStaInd, pst, mBuf);
                  break;
               case RGAC_RGU_EVTCDATIND:
                  ret = cmUnpkRguCDatInd (KwLiRguCDatInd, pst, mBuf);
                  break;
               case RGAC_RGU_EVTDDATIND:
                  ret = cmUnpkRguDDatInd (KwLiRguDDatInd, pst, mBuf);
                  break;
               case RGAC_RGU_EVTBNDCFM:
                  ret = cmUnpkRguBndCfm (KwLiRguBndCfm, pst, mBuf);
                  break;
#ifdef LTE_L2_MEAS
               case RGAC_RGU_EVTHQSTAIND:
                  ret = cmUnpkRguHqStaInd(KwLiRguHqStaInd, pst, mBuf);
                  break;
#endif
#endif
               default:
                  CMXTA_DBG_ERR((_cmxtap, "rgAcKwActvTsk(): Message from an invalid entity! \n"));
                  ret = RFAILED;
                  break;

            } /* end of switch (evnt) */
         }
         break;
      default:
         CMXTA_DBG_ERR((_cmxtap, "rgAcKwActvTsk(): Message from an invalid entity! \n"));
         ret = RFAILED;

   } /* end of switch */

   SExitTsk();
   RETVALUE (ret);
} /* end of rgAcKwActvTsk */

/** @brief This is the activation task of Dummy RLC layer, its called by
 * SSI to initialize the layer. 
 * @param ent
 * @param inst
 * @param region
 * @reason reason
 */
#ifdef ANSI
PUBLIC S16 rgAcKwActvInit
(
 Ent     ent,
 Inst    inst,
 Region  region,
 Reason  reason
 )
#else
PUBLIC S16 rgAcKwActvInit (ent, inst, region, reason)
 Ent     ent;
 Inst    inst;
 Region  region;
 Reason  reason;
#endif
{
   TRC2(rgAcKwActvInit)
   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
   cmMemset((U8 *)&rgAccCb.rgAcRguCb, 0, sizeof(RgAcRguCb));
   RETVALUE(ROK);
}


/**********************************************************************
 
         End of file:     kw_ex_ms.c@@/main/3 - Sat Jul 30 02:22:19 2011
 
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
/main/2      ---     sm                1. LTE MAC 2.1 Release
/main/3      ---     gj                1. LTE MAC 3.1 Release.
*********************************************************************91*/
