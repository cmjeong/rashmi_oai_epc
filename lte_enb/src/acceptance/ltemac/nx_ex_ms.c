
/********************************************************************20**

     Name:    LTE MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source.

     File:    rgac_nx_ex_ms.c

     Sid:      nx_ex_ms.c@@/main/2 - Sat Jul 30 02:22:22 2011

     Prg:     nsadar 
*********************************************************************21*/
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
#include "rgac_rgr.h"
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
#include "rgac_rgr.x"        /* MAC error defines */

/** @brief This is the activation task of the RRM layer. 
 * @param pst pointer to the Pst structure
 * @param mBuf pointer to the Buffer. 
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcNxActvTsk
(
 Pst     *pst,
 Buffer  *mBuf
 )
#else
PUBLIC S16 rgAcNxActvTsk (pst, mBuf)
 Pst     *pst;
 Buffer  *mBuf;
#endif
{
   S16 ret=ROK;

   TRC3(rgAcNxActvTsk);
   switch(pst->srcEnt)
   {
      case ENTRG:
         {
            switch (pst->event)
            {
#ifdef LCRGR
               case EVTRGRBNDCFM:
                  ret = cmUnpkRgrBndCfm (NxLiRgrBndCfm, pst, mBuf);
                  break;
               case EVTRGRCFGCFM:
                  ret = cmUnpkRgrCfgCfm (NxLiRgrCfgCfm, pst, mBuf);
                  break;
                  /* rg001.201: Added for sending TTI tick to RRM */
#ifdef RGR_RRM_TICK
               case EVTRGRTTIIND:
                  ret = cmUnpkRgrTtiInd (NxLiRgrTtiInd, pst, mBuf);
                  break;
#endif
               /* rg004.201-ADD-Added for SI Enhancement. */
#ifdef RGR_SI_SCH
               case EVTRGRSICFGCFM:
                  ret = cmUnpkRgrSiCfgCfm (NxLiRgrSiCfgCfm, pst, mBuf);
                  break;
               case EVTRGRWARNINGSICFGCFM:
                  ret = cmUnpkRgrWarningSiCfgCfm (NxLiRgrWarningSiCfgCfm, pst, mBuf);
                  break;
#endif/*RGR_SI_SCH*/

/* ccpu00117452 - MOD - Changed macro name from
   RGR_RRM_DLPWR_CNTRL to RGR_CQI_REPT */
#ifdef RGR_CQI_REPT
               case EVTRGRSTAIND:
                  ret = cmUnpkRgrStaInd (NxLiRgrStaInd, pst, mBuf);
                  break;
#endif
#endif
               case EVTRGRUESTAIND:
                  ret = cmUnpkRgrUeStaInd (NxLiRgrUeStaInd, pst, mBuf);
                  break;
               default:
                  break;
            } /* end of switch (evnt) */
         }
         break;
      default:
         CMXTA_DBG_ERR((_cmxtap, "rgAcNxActvTsk(): Message from an invalid entity! \n"));
         ret = RFAILED;

   } /* end of switch */

   SExitTsk();
   RETVALUE (ret);
} /* end of rgAcNxActvTsk */

/** @brief This is the activation task of RRM layer, its called by
 * SSI to initialize the layer. 
 * @param ent
 * @param inst
 * @param region
 * @reason reason
 */
#ifdef ANSI
PUBLIC S16 rgAcNxActvInit
(
 Ent     ent,
 Inst    inst,
 Region  region,
 Reason  reason
 )
#else
PUBLIC S16 rgAcNxActvInit (ent, inst, region, reason)
 Ent     ent;
 Inst    inst;
 Region  region;
 Reason  reason;
#endif
{
   TRC2(rgAcNxActvInit)
   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
      /* need to do nothing here, all intialization shall happen once an XML
       * command is issued from the test case.
       */
   RETVALUE(ROK);
} /* rgAcNxActvInit */
/********************************************************************30**

         End of file:     nx_ex_ms.c@@/main/2 - Sat Jul 30 02:22:22 2011

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
/main/1      ---     ns  1. Initial Release.
            rg001.201 sm 1. Removed extra comments.
            rg004.201 rnt 1. Modified for SI Enhancement
/main/2      ---     gj                1. LTE MAC 3.1 Release.            
*********************************************************************91*/
