/********************************************************************20**

     Name:    eNodeB Application - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    nlac_dm_ex_ms.c

     Sid:      nlac_dm_ex_ms.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:02:48 2014

     Prg:     subhamay 
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
#include "nl.h"
#include "lnl.h"
#include "nlu.h"
#include "nlac_acc.h"        /* defines for NL acceptance tests */

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
#include "lnl.x"
#include "nlu.x"
#include "nlac_acc.x"        /* defines for NL acceptance tests */


/*
*
*       Fun:   smNlActvTsk
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
*       File:  nlac_dm_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 smNlActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else /* ANSI */
PUBLIC S16 smNlActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
   Mem sMem; 
   S16 ret; 
 
   TRC2(smNlActvTsk);
 
   sMem.region = DFLT_REGION;
   sMem.pool = DFLT_POOL;

   switch(pst->dstEnt)
   {
      /* Messages sent to SM layer */
      case ENTSM:
      {
         switch (pst->event)
         {
            case EVTLNLCFGCFM:
               cmUnpkLnlCfgCfm(SmMiLnlCfgCfm, pst, mBuf);
               break;
            case EVTLNLCNTRLCFM:
               cmUnpkLnlCntrlCfm(SmMiLnlCntrlCfm, pst, mBuf);
               break;
            case EVTLNLCFGUPDATEIND :
               ret = cmUnpkLnlCfgUpdateInd (SmMiLnlCfgUpdateInd, pst, mBuf);
               break;
            case EVTLNLSTAIND :
               ret = cmUnpkLnlStatInd(SmMiLnlStatInd, pst, mBuf);
               break;
            case EVTLNLSONCFGIND :
               ret = cmUnpkLnlSonCfgInd(SmMiLnlSonCfgInd, pst, mBuf);
               break;
            default:
               printf("\n In %s %d ********* Unhadled event for entity (%d) event (%d) ********\n",__FILE__, __LINE__, pst->dstEnt, pst->event);
               break;
         } /* end of switch pst->event */
         break;
      } 

      /* Messages sent to FSM layer */
      case ENTWR:
      {
         switch(pst->event) /* FSM User events */ 
         {
            case EVTNLUBNDCFM :
               cmUnpkNluBndCfm(WrLiNluBndCfm, pst, mBuf);
               break;
         }
         break;
      }
      default:
      {
         break;
      }    
   }
   SExitTsk();	
   RETVALUE(ROK);
}/* smNlActvTsk */

/*
*
*       Fun:   smNlActvInit
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nlac_dm_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 smNlActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 smNlActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
{

  /* DUMMY FUNCTION: */
  RETVALUE(ROK);
}





