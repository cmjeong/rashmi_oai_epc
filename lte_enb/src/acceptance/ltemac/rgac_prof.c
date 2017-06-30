


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code with the profile information for LTE MAC testing.
  
     File:     rgac_prof.c 
  
     Sid:      rgac_prof.c@@/main/3 - Sat Jul 30 02:20:59 2011
  
     Prg:     sm 
  
**********************************************************************/

/** @file rgac_prof.c.
@brief It has contains the Profile information for LTE MAC testing. The 
information include the entities executing in the test environment and also
the coupling amongst them.
*/

#include "rg_env.h"
#include "rg_sch_inf.h"
#include "rg.h"
#include "envdep.h"
#include "rg_sch.h"

#include "rgac_acc.x"
#include "rg_sch_inf.x"
#include "rg_prg.x"
#include "rg_sch.x"
#include "rg.x"

PUBLIC CmXtaTopology cmXtaTop[] = 
{
#ifdef CMXTA_MASTER
   cmXtaTopStart("TC (All)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)
      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
      cmXtaTopProcStart(1)
         CMXTA_PROCID_SINGLE
      cmXtaTopProcEnd

      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  (CMXTA_INST_ID + 1), TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  (CMXTA_INST_ID + 2), TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  (CMXTA_INST_ID + 3), TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  (CMXTA_INST_ID + 4), TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  RGSCH_INST_START, TTNORM, PRIOR0, schActvInit,   schActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcTfActvInit,   rgAcTfActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcNhActvInit,   rgAcNhActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcNxActvInit,   rgAcNxActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcKwActvInit,   rgAcKwActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcRmActvInit,   rgAcRmActvTsk      )
      cmXtaTopEntitiesEnd
      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 1,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 2,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 3,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 4,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  RGSCH_INST_START,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  RGSCH_INST_START,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 1,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 2,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 3,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 4,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  RGSCH_INST_START,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 1,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 2,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 3,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID + 4,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  RGSCH_INST_START,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  RGSCH_INST_START ,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  RGSCH_INST_START,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTF, CMXTA_INST_ID,     1, 1)
      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   cmXtaTopStart("TC (All)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)
      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
      cmXtaTopProcStart(1)
         CMXTA_PROCID_SINGLE
      cmXtaTopProcEnd

      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID  + 1,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID  + 2,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID  + 3,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID  + 4,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  (CMXTA_INST_ID + 5), TTNORM, PRIOR0, schActvInit,   schActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcTfActvInit,   rgAcTfActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcNhActvInit,   rgAcNhActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcRmActvInit,   rgAcRmActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcNxActvInit,   rgAcNxActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcKwActvInit,   rgAcKwActvTsk      )
      cmXtaTopEntitiesEnd
      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+ 5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     0, 0)
      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   /* For scheduler as separate System Task */
   /* Follwing code shoukld be enabled only when we intend to run Scheduler and
    * MAC on deifferent threads XXX: Remeber to enable LCRG and LCSCH ,acros in
    * rg.mak */
   
   cmXtaTopStart("TC (All)")
      cmXtaTopSTasks(1)
      cmXtaTopProcStart(1)
         CMXTA_PROCID_SINGLE
      cmXtaTopProcEnd

      cmXtaTopEntitiesStart
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID  + 1,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID  + 2,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID  + 3,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID  + 4,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  (CMXTA_INST_ID + 5), TTNORM, PRIOR0, schActvInit,   schActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcTfActvInit,   rgAcTfActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcNhActvInit,   rgAcNhActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcRmActvInit,   rgAcRmActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcNxActvInit,   rgAcNxActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcKwActvInit,   rgAcKwActvTsk      )
      cmXtaTopEntitiesEnd
      cmXtaTopCouplingStart
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+ 5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     0, 0)
      cmXtaTopCouplingEnd
   cmXtaTopEnd 
  
   cmXtaTopStart("Master")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)
      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
      cmXtaTopProcStart(1)
         CMXTA_PROCID_MASTER
      cmXtaTopProcEnd

      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart
            cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTTF,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcTfActvInit,   rgAcTfActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcNhActvInit,   rgAcNhActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTRM,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcRmActvInit,   rgAcRmActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTNX,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcNxActvInit,   rgAcNxActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTKW,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgAcKwActvInit,   rgAcKwActvTsk      )
      cmXtaTopEntitiesEnd
      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+1,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+2,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+3,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+4,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTRG,  CMXTA_INST_ID+5,     0, 0)
            cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID,     0, 0)
      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/
#endif /*-- CMXTA_MASTER --*/

   cmXtaTopStart("Slave")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)
      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
      cmXtaTopProcStart(1)
         CMXTA_PROCID_SLAVE
      cmXtaTopProcEnd

      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart
            cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTRG, CMXTA_INST_ID,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTRG, CMXTA_INST_ID+1,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTRG, CMXTA_INST_ID+2,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTRG, CMXTA_INST_ID+3,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTRG, CMXTA_INST_ID+4,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
            cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  (CMXTA_INST_ID + 5), TTNORM, PRIOR0, schActvInit,   schActvTsk      )
      cmXtaTopEntitiesEnd
      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
   cmXtaTopEnd /*-- End Of Profile --*/
};


/**********************************************************************
 
         End of file:     rgac_prof.c@@/main/3 - Sat Jul 30 02:20:59 2011
 
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
/main/1      ---     sm   1. Initial Release.
*********************************************************************91*/



/**********************************************************************
 
         End of file:     rgac_prof.c@@/main/3 - Sat Jul 30 02:20:59 2011
 
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
/main/1      ---     sm   1. Initial Release.
/main/2      ---     sm   1. LTE MAC 2.1 release
/main/3      ---     dvasisht          1. Updated for LTE MAC Release 3.1          
$SID$        ---     rt   1. LTE MAC 4.1 release
*********************************************************************91*/
