

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_prof.c

     Sid:      rmac_prof.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:26 2013

     Prg:      vprabhu

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
#include "cm_dns.h"        /* common DNS libraru defines */
#include "cm_xta.h" 
#include "cm_pasn.h"
#include "rm.h"
//#include "wr_cmn.h"
//#include "wr_smm_init.h"
#include "rmac_acc.h"
#include "rmu.h"
#include "lrm.h"


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
#include "cm_xta.x" 
#include "cm_pasn.x"
#include "rmu.x"
#include "lrm.x"
#include "rmac_acc.x"

PUBLIC CmXtaTopology cmXtaTop[] =
{
   cmXtaTopStart("TC (All)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
      cmXtaTopProcStart(1)
         CMXTA_PROCID_ONE
      cmXtaTopProcEnd

      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart
        cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmActvInit,   rmActvTsk)

         cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   rmDmActvTsk)
         cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   cmXtaActvTsk      )

/* Venu */
	cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTWR,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   rmDmActvTsk)
	cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTRG,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   rmDmActvTsk      )
/* Venu */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         /* Venu */
	cmXtaTopCoupling(CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     2, 2)
	cmXtaTopCoupling(CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_ONE, ENTWR,  CMXTA_INST_ID,     1, 1)

	cmXtaTopCoupling(CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_ONE, ENTRG,  CMXTA_INST_ID,     1, 1)
//	cmXtaTopCoupling(CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     1, 1)
//	cmXtaTopCoupling(CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     1, 1)
         /* Venu */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/


   cmXtaTopStart("LC (All)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
      cmXtaTopProcStart(1)
         CMXTA_PROCID_ONE
      cmXtaTopProcEnd

      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

       cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmActvInit,   rmActvTsk)
         cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   rmDmActvTsk)
         cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   cmXtaActvTsk      )
/* Venu */
        cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTWR,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   rmDmActvTsk)
	     cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTRG,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   rmDmActvTsk)
/* Venu */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         /* Venu */
         /* Venu */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/


   cmXtaTopStart("LWLC/LC (All)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
      cmXtaTopProcStart(1)
         CMXTA_PROCID_ONE
      cmXtaTopProcEnd

      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

        cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmActvInit,   rmActvTsk)
         cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   rmDmActvTsk)
         cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   cmXtaActvTsk      )
/* Venu */
        cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTWR,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   rmDmActvTsk)
        cmXtaTopEntity(1, CMXTA_PROCID_ONE, ENTRG,  CMXTA_INST_ID,     TTNORM, PRIOR0, rmDmActvInit,   rmDmActvTsk      )
/* Venu */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         /* Venu */
        cmXtaTopCoupling(CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     2, 2)
        cmXtaTopCoupling(CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_ONE, ENTWR,  CMXTA_INST_ID,     1, 1)

        cmXtaTopCoupling(CMXTA_PROCID_ONE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_ONE, ENTRG,  CMXTA_INST_ID,     1, 1)
         /* Venu */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

};


