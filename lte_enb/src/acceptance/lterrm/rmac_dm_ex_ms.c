/********************************************************************20**

     Name:    eNodeB Application - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    wrac_dm_ex_ms.c

     Sid:      rmac_dm_ex_ms.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:25 2013

     Prg:     pakumar
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */
#include "cm_xta.h" 
#include "cm_pasn.h"
#include "rm.h"
#include "lrm.h"
#include "rmu.h"
#include "rmac_acc.h"        /* defines for RM acceptance tests */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */
#include "cm_pasn.x"
#include "cm_xta.x" 
#include "lrm.x"
#include "rmu.x"
#include "rmac_acc.x"        /* defines for RM acceptance tests */


/*
*
*       Fun:   rmDmActvTsk
*
*       Desc:  Dummy Active task function for the loosely coupled
*              interface from application lower layer
*              This is a single function which will be used for all
*              the interfaces which are present at lower interface.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rmac_dm_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 rmDmActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else /* ANSI */
PUBLIC S16 rmDmActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
   Mem sMem; 
   S16 ret; 
 
   TRC2(rmDmActvTsk);
 
   sMem.region = DFLT_REGION;
   sMem.pool = DFLT_POOL;

   switch(pst->dstEnt)
   {
      /* Messages sent to SM layer */
      case ENTSM:
      {
         switch (pst->event)
         {
            case EVTLRMCFGCFM:
               cmUnpkLwLcLrmCfgCfm(SmMiLrmCfgCfm, pst, mBuf);
               break;
            case EVTLRMCNTRLCFM:           /* Control confirm */
               ret = cmUnpkLwLcLrmCntrlCfm(SmMiLrmCntrlCfm, pst, mBuf);
               break;
            default:
               printf("\n In %s %d ********* Unhadled event for entity (%d) event (%d) ********\n",__FILE__, __LINE__, pst->dstEnt, pst->event);
               break;
         } /* end of switch pst->event */
         break;
      } /* end of case ENTSM */

      /* Messages sent to FSM layer */
      case ENTWR:
      {
         switch(pst->event) /* FSM User events */ 
         {
            case EVTRMUCELLRECFGIND:
               cmUnpkLwLcRmuCellReCfgInd(WrLiRmuCellRecfgInd, pst, mBuf);
               break;
            case EVTRMUUEADMITRSP: 
               cmUnpkLwLcRmuUeAdmitRsp(WrLiRmuUeAdmitRsp, pst, mBuf);
               break;
            case EVTRMUUERELRSP:
               cmUnpkLwLcRmuUeRelRsp(WrLiRmuUeRelRsp, pst, mBuf );
               break;
            case  EVTRMUUERECFGRSP:
               cmUnpkLwLcRmuUeRecfgRsp(WrLiRmuUeRecfgRsp, pst, mBuf);
               break;
            case  EVTRMUUEHORSP:
               cmUnpkLwLcRmuUeHoRsp(WrLiRmuUeHoRsp, pst, mBuf);
               break;
            case EVTRMUUERELIND:
               cmUnpkLwLcRmuUeRelInd(WrLiRmuUeRelInd, pst, mBuf);
               break;
            case EVTRMUBNDCFM:
               cmUnpkLwLcRmuBndCfm(WrLiRmuBndCfm, pst, mBuf);
               break;
            default:
               printf("\n In %s %d ********* Unhadled event for entity (%d) event (%d) ********\n",__FILE__, __LINE__, pst->dstEnt, pst->event);
               break;
         }
         break;
      } /* end of case ENTWR */

      case ENTRG:
      {
      } /* end of case ENTRG */

    }	
   RETVALUE(ROK);
}/* rmDmActvTsk */

/*
*
*       Fun:   wrDmActvInit
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wrac_dm_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 rmDmActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 rmDmActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
{

  /* DUMMY FUNCTION: */
  RETVALUE(ROK);
}

/*
*
*       Fun:   smRgActvInit
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wrac_dm_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 smRgActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 smRgActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
{
  /* DUMMY FUNCTION: */
  RETVALUE(ROK);
}

/*
*
*       Fun:   smRgActvTsk
*
*       Desc:  Dummy Active task function for the loosely coupled
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  wrac_dm_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 smRgActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else /* ANSI */
PUBLIC S16 smRgActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
	RETVALUE(ROK);

}




