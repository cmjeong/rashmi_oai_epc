
/********************************************************************20**

     Name:    eGTP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source. It defines the Toplogy.

     File:    egac_prof.c

     Sid:      egac_prof.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:39 2015

     Prg:     an
 
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
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS libraru defines */

#include "egt.h"           /* egt defines */
#include "leg.h"           /* layer management defines for EGT */

#ifdef HI
#include "lhi.h"           /* layer manager header of HI */
#include "hi.h"            /* macros of TUCL  */
#endif

#include "cm_xta.h" 

#include "eg_edm.h"        /* EDM Module structures            */
#include "eg.h"            /* defines and macros for eGTP */
#include "eg_err.h"        /* eGTP error defines */
#include "egac_acc.h"      /* defines for eGTP acceptance tests */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"        /* common DNS libraru defines */

#include "egt.x"           /* egt types */
#include "leg.x"           /* layer management typedefs for eGTP */

#ifdef HI
#include "lhi.x"           /* Structures of tucl layer manager */
#include "hi.x"            /* macro definitions of TUCL   */
#endif

#include "cm_xta.x" 
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* typedefs for eGTP */
#include "eu.x"            /* typedefs for eGTP */
#include "egac_acc.x"      /* typedefs for eGTP acceptance tests */


PUBLIC CmXtaTopology cmXtaTop[] =
{
#ifdef CMXTA_MASTER
   cmXtaTopStart("TC (All)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       EGAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       EGAC_PROCID_ZERO,
       EGAC_PROCID_ONE,
       EGAC_PROCID_TWO,
       EGAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID,     TTNORM, PRIOR0, euActvInit,   euActvTsk      )

         cmXtaTopEntity(1, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
#ifdef EG_ACC_INT
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTPERM, PRIOR0, NULLP, hiScanPermTsk         )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* EG_ACC_INT */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, egAcHiActvInit,   egAcHiActvTsk      )


#else   /*SS_MULTIPLE_PROCS*/

         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk)
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk)
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID,     TTNORM, PRIOR0, euActvInit,   euActvTsk)
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk)
#ifdef EG_ACC_INT
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTPERM , PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk)
#endif /* EG_ACC_INT */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, egAcHiActvInit,   egAcHiActvTsk)

#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd


      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#ifdef DHI
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5, 13, 2)
         cmXtaTopCoupling(EGAC_PROCID_ONE,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,  13, 2)
         cmXtaTopCoupling(EGAC_PROCID_TWO,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,  13, 2)
         cmXtaTopCoupling(EGAC_PROCID_THREE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,  13, 2)
#endif
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
#else  /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
#ifdef DHI
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5, 13, 2)
         cmXtaTopCoupling(EGAC_PROCID_ONE,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,  13, 2)
         cmXtaTopCoupling(EGAC_PROCID_TWO,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,  13, 2)
         cmXtaTopCoupling(EGAC_PROCID_THREE,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5, 13, 2)
#endif
 
#endif /* SS_MULTIPLE_PROCS */


      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   
   cmXtaTopStart("LC ALL(LEG, EGT, HIT)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       EGAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       EGAC_PROCID_ZERO,
       EGAC_PROCID_ONE,
       EGAC_PROCID_TWO,
       EGAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk    )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID,     TTNORM, PRIOR0, euActvInit,   euActvTsk    )
         cmXtaTopEntity(1, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk    )
         cmXtaTopEntity(1, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk    )
         cmXtaTopEntity(1, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk    )
         cmXtaTopEntity(1, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk    )
#ifdef EG_ACC_INT
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk       )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk    )
#endif /* EG_ACC_INT */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, egAcHiActvInit,   egAcHiActvTsk)

#else

         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk    )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID,     TTNORM, PRIOR0, euActvInit,   euActvTsk    )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk    )
#ifdef EG_ACC_INT
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk    )
#endif /* EG_ACC_INT */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, egAcHiActvInit,   egAcHiActvTsk)

#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     0, 0)
#ifdef DHI
         cmXtaTopCoupling(EGAC_PROCID_SINGLE,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,  0, 2)
         cmXtaTopCoupling(EGAC_PROCID_ONE,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,     0, 2)
         cmXtaTopCoupling(EGAC_PROCID_TWO,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,     0, 2)
         cmXtaTopCoupling(EGAC_PROCID_THREE,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,   0, 2)
#endif
#else /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
#ifdef DHI
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5, 0, 2)
         cmXtaTopCoupling(EGAC_PROCID_ONE,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,    0, 2)
         cmXtaTopCoupling(EGAC_PROCID_TWO,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,    0, 2)
         cmXtaTopCoupling(EGAC_PROCID_THREE,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,  0, 2)
#endif

#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   cmXtaTopStart("LC ALL with LCLW for EGT ")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       EGAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       EGAC_PROCID_ZERO,
       EGAC_PROCID_ONE,
       EGAC_PROCID_TWO,
       EGAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID,     TTNORM, PRIOR0, euActvInit,   euActvTsk      )

         cmXtaTopEntity(1, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
#ifdef EG_ACC_INT
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTPERM, PRIOR0, NULLP, hiScanPermTsk         )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* EG_ACC_INT */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, egAcHiActvInit,   egAcHiActvTsk)


#else   /*SS_MULTIPLE_PROCS*/

         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID,     TTNORM, PRIOR0, euActvInit,   euActvTsk      )
#ifdef EG_ACC_INT
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* EG_ACC_INT */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, egAcHiActvInit,   egAcHiActvTsk)

#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)

         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
#else  /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)


#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   cmXtaTopStart("TC (All) Enb (LC)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       EGAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       EGAC_PROCID_ZERO,
       EGAC_PROCID_ONE,
       EGAC_PROCID_TWO,
       EGAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTEU,  CMXTA_INST_ID,     TTNORM, PRIOR0, euActvInit,   euActvTsk      )

         cmXtaTopEntity(1, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
#ifdef EG_ACC_INT
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID+4,   TTPERM, PRIOR0, NULLP, hiScanPermTsk         )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* EG_ACC_INT */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, egAcHiActvInit,   egAcHiActvTsk)


#else   /*SS_MULTIPLE_PROCS*/

         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTEU,  CMXTA_INST_ID,     TTNORM, PRIOR0, euActvInit,   euActvTsk      )
         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
#ifdef EG_ACC_INT
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, EGAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* EG_ACC_INT */
         cmXtaTopEntity(1, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, egAcHiActvInit,   egAcHiActvTsk)

#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ONE,    ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(EGAC_PROCID_ZERO,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_ONE,    ENTEG,  CMXTA_INST_ID, EGAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_TWO,    ENTEG,  CMXTA_INST_ID, EGAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_THREE,  ENTEG,  CMXTA_INST_ID, EGAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)

         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTTST, CMXTA_INST_ID, EGAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     1, 1)
#ifdef DHI
         cmXtaTopCoupling(EGAC_PROCID_SINGLE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,   0, 2)
         cmXtaTopCoupling(EGAC_PROCID_ONE,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,    0, 2)
         cmXtaTopCoupling(EGAC_PROCID_TWO,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,    0, 2)
         cmXtaTopCoupling(EGAC_PROCID_THREE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,    0, 2)
#endif
#else  /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ONE, ENTEG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, EGAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTEU,  CMXTA_INST_ID, EGAC_PROCID_ONE, ENTEG,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(EGAC_PROCID_ONE, ENTTST, CMXTA_INST_ID, EGAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     1, 1)
#ifdef DHI
         cmXtaTopCoupling(EGAC_PROCID_SINGLE,ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,     0, 2)
         cmXtaTopCoupling(EGAC_PROCID_ONE,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,     0, 2)
         cmXtaTopCoupling(EGAC_PROCID_TWO,   ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,     0, 2)
         cmXtaTopCoupling(EGAC_PROCID_THREE, ENTEG,  CMXTA_INST_ID, EGAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID + 5,     0, 2)
#endif


#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   
#endif /*-- CMXTA_MASTER --*/

   cmXtaTopStart("Slave")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
      cmXtaTopProcStart(2)
         CMXTA_PROCID_SLAVE1,
         CMXTA_PROCID_SLAVE2
      cmXtaTopProcEnd

      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart


         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE2, ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE1, ENTEG,  CMXTA_INST_ID,     TTNORM, PRIOR0, egActvInit,   egActvTsk      )

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
   cmXtaTopEnd /*-- End Of Profile --*/


#ifdef CMXTA_MASTER

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

         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTEU,  CMXTA_INST_ID,     TTNORM, PRIOR0, euActvInit,   euActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, egAcHiActvInit,   egAcHiActvTsk)
      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTEU,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE1,  ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE2,  ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTEU,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE1,  ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTEU,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE2,  ENTEG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTEU,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE1,  ENTEG,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE2,  ENTEG,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTHI,  CMXTA_INST_ID,     0, 0)
/*-- DUMMY TUCL --*/
#ifdef DHI
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE1, ENTEG,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID + 5, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE2, ENTEG,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID + 5, 0, 0)
#endif
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID,     1, 1)

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/
#endif /*-- CMXTA_MASTER --*/

};

/********************************************************************30**

         End of file:     egac_prof.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:39 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
*********************************************************************91*/
