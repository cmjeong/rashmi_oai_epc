
/********************************************************************20**

     Name:    S1AP acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    szac_prof.c

     Sid:      szac_prof.c@@/main/3 - Mon Jan 10 22:15:55 2011

     Prg:     up 
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
/* sz006.301: Removed un-necessary include files  */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "szt.h"           /* szt defines */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* layer management defines for SZT */

#ifdef HI
#include "lhi.h"
#include "hi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h" 

#include "cm_pasn.h"
#include "sz.h"            /* defines and macros for S1AP */
#include "sz_err.h"        /* S1AP error defines */
#include "szac_acc.h"        /* defines for S1AP acceptance tests */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

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
#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */

#include "sct.x"           /* SCTP Interface Structures */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* szt types */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* layer management typedefs for S1AP */

#ifdef HI
#include "lhi.x"
#include "hi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_xta.x" 
#include "sz.x"            /* typedefs for S1AP */
#include "uz.x"            /* typedefs for S1AP */
#include "szac_acc.x"        /* typedefs for S1AP acceptance tests */

#ifdef DM
#include "szac_sct.x"
#endif /*DM*/



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
       SZAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       SZAC_PROCID_ZERO,
       SZAC_PROCID_ONE,
       SZAC_PROCID_TWO,
       SZAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, uzActvInit,   uzActvTsk      )

         cmXtaTopEntity(1, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, szAcSbActvInit, szAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTPERM, PRIOR0, NULLP, hiScanPermTsk         )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )

#endif /* HI */
#else   /*SS_MULTIPLE_PROCS*/

         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, uzActvInit,   uzActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, szAcSbActvInit, szAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )

#endif /* HI */
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)

#ifdef SB
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,    12, 1)
         cmXtaTopCoupling(SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,    12, 1)
         cmXtaTopCoupling(SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,    12, 1)
         cmXtaTopCoupling(SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,    12, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */         

#ifdef DM
         cmXtaTopCoupling(SZAC_PROCID_ZERO,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_ONE,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_TWO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_THREE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
#endif /*DM*/

         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
#else  /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)

#ifdef SB
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,    12, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */

#ifdef DM
         cmXtaTopCoupling(SZAC_PROCID_ZERO, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
#endif /*DM*/
 
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   
   cmXtaTopStart("LC ALL(LSZ, SZT, SCT, HIT)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       SZAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       SZAC_PROCID_ZERO,
       SZAC_PROCID_ONE,
       SZAC_PROCID_TWO,
       SZAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk    )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, uzActvInit,   uzActvTsk    )
         cmXtaTopEntity(1, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk    )
         cmXtaTopEntity(1, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk    )
         cmXtaTopEntity(1, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk    )
         cmXtaTopEntity(1, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk    )
#ifdef SB
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk    )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, szAcSbActvInit, szAcSbActvTsk   )
#endif /*DM*/
#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk       )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk    )

#endif /* HI */
#else

         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk    )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, uzActvInit,   uzActvTsk    )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk    )
#ifdef SB
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk    )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, szAcSbActvInit, szAcSbActvTsk   )
#endif /*DM*/
#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk    )
#endif /* HI */
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#ifdef SB
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */         
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID,     0, 0)

#ifdef DM
         cmXtaTopCoupling(SZAC_PROCID_ZERO,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5,  0, 0)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_ONE,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5,  0, 0)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_TWO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5,  0, 0)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_THREE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5,  0, 0)  /*-- DUMMY SCTP --*/
#endif /*DM*/

         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     0, 0)
#else /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
#ifdef SB
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */         

#ifdef DM
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5,  0, 0)  /*-- DUMMY SCTP --*/
#endif /*DM*/
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   cmXtaTopStart("LC ALL with LCLW for SZT ")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       SZAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       SZAC_PROCID_ZERO,
       SZAC_PROCID_ONE,
       SZAC_PROCID_TWO,
       SZAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, uzActvInit,   uzActvTsk      )

         cmXtaTopEntity(1, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, szAcSbActvInit, szAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTPERM, PRIOR0, NULLP, hiScanPermTsk         )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )

#endif /* HI */

#else   /*SS_MULTIPLE_PROCS*/

         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, uzActvInit,   uzActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, szAcSbActvInit, szAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* HI */
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)

#ifdef SB
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */         

#ifdef DM
         cmXtaTopCoupling(SZAC_PROCID_ZERO,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5,  0, 0)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_ONE,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5,  0, 0)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_TWO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5,  0, 0)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_THREE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5,  0, 0)  /*-- DUMMY SCTP --*/
#endif /*DM*/

         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
#else  /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)

#ifdef SB
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */

#ifdef DM
         cmXtaTopCoupling(SZAC_PROCID_ZERO, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5, 0, 0)  /*-- DUMMY SCTP --*/
#endif /*DM*/
 
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
       SZAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       SZAC_PROCID_ZERO,
       SZAC_PROCID_ONE,
       SZAC_PROCID_TWO,
       SZAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTUZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, uzActvInit,   uzActvTsk      )

         cmXtaTopEntity(1, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, szAcSbActvInit, szAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID+4,   TTPERM, PRIOR0, NULLP, hiScanPermTsk         )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* HI */

#else   /*SS_MULTIPLE_PROCS*/

         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTUZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, uzActvInit,   uzActvTsk      )
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, szAcSbActvInit, szAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* HI */
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ONE,    ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)

#ifdef SB
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_ZERO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,    12, 1)
         cmXtaTopCoupling(SZAC_PROCID_ONE,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,    12, 1)
         cmXtaTopCoupling(SZAC_PROCID_TWO,    ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,    12, 1)
         cmXtaTopCoupling(SZAC_PROCID_THREE,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,    12, 1)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */         

#ifdef DM
         cmXtaTopCoupling(SZAC_PROCID_ZERO,  ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_ONE,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_TWO,   ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(SZAC_PROCID_THREE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
#endif /*DM*/

         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID, SZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     1, 1)
#else  /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTUZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID, SZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     1, 1)

#ifdef SB
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,    12, 1)
         cmXtaTopCoupling(SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */

#ifdef DM
         cmXtaTopCoupling(SZAC_PROCID_ZERO, ENTSZ,  CMXTA_INST_ID, SZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
#endif /*DM*/
 
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   
#endif /*-- CMXTA_MASTER --*/

#ifdef SS_MULTIPLE_PROCS
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

         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE1, ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )

         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE2, ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )

#ifdef HI
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* HI */
#ifdef SB               
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
   cmXtaTopEnd /*-- End Of Profile --*/
#endif /* SS_MULTIPLE_PROCS */

   cmXtaTopStart("Slave for integrated setup")
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

         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )

#ifdef HI
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* HI */
#ifdef SB               
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif

      cmXtaTopEntitiesEnd

   cmXtaTopEnd /*-- End Of Profile --*/


#ifdef CMXTA_MASTER

#ifdef SS_MULTIPLE_PROCS
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
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTUZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, uzActvInit,   uzActvTsk      )
#ifdef DM
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, szAcSbActvInit, szAcSbActvTsk   )
#endif /*DM*/
      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTUZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE1,  ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE2,  ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
#ifdef SB
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID,     0, 0)
/*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE1,  ENTSZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE2,  ENTSZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
#endif 
#ifdef DM
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE1, ENTSZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 0, 0)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE2, ENTSZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 0, 0)  /*-- DUMMY SCTP --*/
#endif /*DM*/
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTUZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE1,  ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTUZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE2,  ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTUZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE1,  ENTSZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE2,  ENTSZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTHI,  CMXTA_INST_ID,     0, 0)
/*-- DUMMY TUCL --*/
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID,     1, 1)

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/
#endif /* SS_MULTIPLE_PROCS */


   cmXtaTopStart("Master for integrated setup")
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
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTUZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, uzActvInit,   uzActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTSZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, szActvInit,   szActvTsk      )
#ifdef HI
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* HI */
#ifdef SB               
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif
#ifdef DM
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, szAcSbActvInit, szAcSbActvTsk   )
#endif /*DM*/
      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTUZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE , ENTSZ,  CMXTA_INST_ID,     0, 0)
#ifdef HI
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /*HI*/
#ifdef SB
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID,     0, 0)
#endif  /* SB */

#ifdef SB
         cmXtaTopCoupling(CMXTA_PROCID_MASTER,  ENTSZ, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE ,  ENTSZ, CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID,     0, 0)
#ifdef HI
         cmXtaTopCoupling(CMXTA_PROCID_MASTER,  ENTSB, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,   ENTSB, CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* HI */
#endif /* SB */
#ifdef HI
         cmXtaTopCoupling(CMXTA_PROCID_MASTER,  ENTSZ, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,   ENTSZ, CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* HI */
#ifdef DM
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 0, 0)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE , ENTSZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 0, 0)  /*-- DUMMY SCTP --*/
#endif /*DM*/
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTUZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER,  ENTSZ, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTUZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE ,  ENTSZ, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID,     1, 1)

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/
#endif /*-- CMXTA_MASTER --*/

};

/********************************************************************30**

         End of file:     szac_prof.c@@/main/3 - Mon Jan 10 22:15:55 2011

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
/main/3      ---      pkaX  1. Updated for S1AP release 3.1
/main/3   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/3   sz006.301   ve    1. Removed un-necessary include files
/main/3   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
