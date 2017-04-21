
/********************************************************************20**

     Name:     LTE CNE Layer

     Type:     C source file

     Desc:     

     File:     smvbexms.c

     Sid:      smvbexms.c@@/main/1 - Mon Jun 28 19:35:33 2010

     Prg:      ap 

*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_dns.h"        /* Common DNS library              */
#include "cm_inet.h"       /* Common socket library           */
#include "lvb.h"           /* LTE CNE Layer management           */


/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_dns.x"        /* Common DNS library              */
#include "cm_inet.x"       /* Common socket library           */
#include "lvb.x"           /* LTE CNE Layer management            */

/* public routines */

/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from LTE CNE layer
*
*       Ret:    ROK  - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   smvbexms.c
*
*/


#ifdef ANSI
PUBLIC S16 smVbActvTsk
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 smVbActvTsk(pst, mBuf)
Pst    *pst;                /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16         ret;           /* return code */

   TRC3(smVbActvTsk)

   ret = ROK;

   switch(pst->event)
   {
#ifdef LCSMVBMILVB
                   
      case EVTLVBCFGCFM:             /* Config confirm */
         ret = cmUnpkLvbCfgCfm(SmMiLvbCfgCfm, pst, mBuf);
         break;

      case EVTLVBCNTRLCFM:           /* Control confirm */
         ret = cmUnpkLvbCntrlCfm(SmMiLvbCntrlCfm, pst, mBuf);
         break;

      case EVTLVBSTACFM:             /* Status Confirm */
         ret = cmUnpkLvbStaCfm(SmMiLvbStaCfm, pst, mBuf);
         break;

      case EVTLVBSTSCFM:             /* Statistics Confirm */
         ret = cmUnpkLvbStsCfm(SmMiLvbStsCfm, pst, mBuf);
         break;

      case EVTLVBSTAIND:             /* Status Indication */
         ret = cmUnpkLvbStaInd(SmMiLvbStaInd, pst, mBuf);
         break;

      case EVTLVBTRCIND:             /* Trace Indication */
         ret = cmUnpkLvbTrcInd(SmMiLvbTrcInd, pst, mBuf);
         break;

#endif /* LCSMVBMILVB */

      default:
         /* we should never get here, especially if tightly coupled */
         SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
        SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId, __FILE__, \
                   __LINE__, (ErrCls) ERRCLS_DEBUG, (ErrVal)0, 
                   (ErrVal)pst->event, "smVbActvTsk () Failed"); 
#endif
         ret = RFAILED;
         break;
   }
   
   SExitTsk();

   RETVALUE(ret);
} /* smVbActvTsk */


/********************************************************************30**

         End of file:     smvbexms.c@@/main/1 - Mon Jun 28 19:35:33 2010

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      -       sp                 1.LTE-MME:Initial Release
*********************************************************************91*/