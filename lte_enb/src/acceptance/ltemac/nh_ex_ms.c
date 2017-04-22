
/********************************************************************20**

     Name:    LTE MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source.

     File:    rgac_nh_ex_ms.c

     Sid:      nh_ex_ms.c@@/main/2 - Sat Jul 30 02:22:21 2011

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
#include "rgac_crg.h"
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
#include "rgac_crg.x"        /* MAC error defines */


/** @brief This is the activation task of the dummy RRC layer. 
 * @param pst pointer to the Pst structure
 * @param mBuf pointer to the Buffer. 
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 rgAcNhActvTsk
(
 Pst     *pst,
 Buffer  *mBuf
 )
#else
PUBLIC S16 rgAcNhActvTsk (pst, mBuf)
 Pst     *pst;
 Buffer  *mBuf;
#endif
{
   S16 ret=ROK;

   TRC3(rgAcNhActvTsk);
   switch(pst->srcEnt)
   {
      case ENTRG:
         {
            switch (pst->event)
            {
#ifdef LCCRG
               case EVTCRGBNDCFM:
                  ret = cmUnpkCrgBndCfm (NhLiCrgBndCfm, pst, mBuf);
                  break;
               case EVTCRGCFGCFM:
                  ret = cmUnpkCrgCfgCfm (NhLiCrgCfgCfm, pst, mBuf);
                  break;
#endif
               default:
                  break;
            } /* end of switch (evnt) */
         }
         break;
      default:
         CMXTA_DBG_ERR((_cmxtap, "rgAcNhActvTsk():Message from an invalid entity! \n"));
         ret = RFAILED;

   } /* end of switch */

   SExitTsk();
   RETVALUE (ret);
} /* end of rgAcNhActvTsk */

/** @brief This is the activation task of Dummy RRC layer, its called by
 * SSI to initialize the layer. 
 * @param ent
 * @param inst
 * @param region
 * @reason reason
 */
#ifdef ANSI
PUBLIC S16 rgAcNhActvInit
(
 Ent     ent,
 Inst    inst,
 Region  region,
 Reason  reason
 )
#else
PUBLIC S16 rgAcNhActvInit (ent, inst, region, reason)
 Ent     ent;
 Inst    inst;
 Region  region;
 Reason  reason;
#endif
{
   TRC2(rgAcNhActvInit)
   UNUSED(ent);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);
      /* need to do nothing here, all intialization shall happen once an XML
       * command is issued from the test case.
       */
   RETVALUE(ROK);
} /* rgAcNhActvInit */
/********************************************************************30**

         End of file:     nh_ex_ms.c@@/main/2 - Sat Jul 30 02:22:21 2011

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
/main/2      ---     gj                1. LTE MAC 3.1 Release.
*********************************************************************91*/
