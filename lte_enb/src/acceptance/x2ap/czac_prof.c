
/********************************************************************20**

     Name:    X2AP acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    czac_prof.c

     Sid:      czac_prof.c@@/main/2 - Tue Aug 30 18:35:52 2011

     Prg:     sy
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
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "sct.h"           /* SB (SCTP) layer */
#include "czt.h"           /* czt defines */
#include "lcz.h"           /* layer management defines for CZT */

#ifdef HI
#include "lhi.h"
#endif

#ifdef    SB
#include "lsb.h"
#endif    /* SB */

#include "cm_xta.h" 

#include "cz.h"            /* defines and macros for X2AP */
#include "cz_err.h"        /* X2AP error defines */
#include "czac_acc.h"        /* defines for X2AP acceptance tests */

/* header/extern include files (.x) */

#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "cm_lib.x"        /* Common library definitions */
#include "cm_tkns.x"       /* Common Token definitions */
#include "cm_llist.x"      /* Common Link List definitions */
#include "cm_hash.x"       /* Common Hashlist definitions */
#include "cm_mblk.x"       /* common memory */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "cm_pasn.x"       /* Common ASn.1 Library           */
#include "sct.x"           /* SCTP Layer */
#include "cm5.x"           /* Common timer definitions */
#include "sct.x"           /* SCTP Layer */
#include "lcz.x"           /* LCZ Interface includes */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* CZT Interface includes */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "sct.x"           /* SCTP Interface Structures */
#include "czac_czt_inf.x"           /* czt types */
#include "lcz.x"           /* layer management typedefs for X2AP */

#ifdef HI
#include "lhi.x"
#endif

#ifdef    SB
#include "lsb.x"
#endif    /* SB */

#include "cm_xta.x" 
#include "cz.x"            /* typedefs for X2AP */
#include "rs.x"            /* typedefs for X2AP */
#include "czac_acc.x"        /* typedefs for X2AP acceptance tests */

#ifdef DM
#include "czac_sct.x"
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
       CZAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       CZAC_PROCID_ZERO,
       CZAC_PROCID_ONE,
       CZAC_PROCID_TWO,
       CZAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID,     TTNORM, PRIOR0, rsActvInit,   rsActvTsk      )

         cmXtaTopEntity(1, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, czAcSbActvInit, czAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTPERM, PRIOR0, NULLP, hiScanPermTsk         )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )

#endif /* HI */
#else   /*SS_MULTIPLE_PROCS*/

         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   rsActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, czAcSbActvInit, czAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )

#endif /* HI */
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)

#ifdef SB
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,    13, 1)
         cmXtaTopCoupling(CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,    13, 1)
         cmXtaTopCoupling(CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,    13, 1)
         cmXtaTopCoupling(CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,    13, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */         

#ifdef DM
         cmXtaTopCoupling(CZAC_PROCID_ZERO,  ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_ONE,   ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_TWO,   ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_THREE, ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
#endif /*DM*/

         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
#else  /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)

#ifdef SB
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,    13, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */

#ifdef DM
         cmXtaTopCoupling(CZAC_PROCID_ZERO, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
#endif /*DM*/
 
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   
   cmXtaTopStart("LC ALL(LCZ, CZT, SCT, HIT)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       CZAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       CZAC_PROCID_ZERO,
       CZAC_PROCID_ONE,
       CZAC_PROCID_TWO,
       CZAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk    )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   rsActvTsk    )
         cmXtaTopEntity(1, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk    )
         cmXtaTopEntity(1, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk    )
         cmXtaTopEntity(1, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk    )
         cmXtaTopEntity(1, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk    )
#ifdef SB
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk    )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, czAcSbActvInit, czAcSbActvTsk   )
#endif /*DM*/
#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk       )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk    )

#endif /* HI */
#else

         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk    )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   rsActvTsk    )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk    )
#ifdef SB
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk    )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, czAcSbActvInit, czAcSbActvTsk   )
#endif /*DM*/
#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk    )
#endif /* HI */
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#ifdef SB
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */         
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID,     0, 0)

#ifdef DM
         cmXtaTopCoupling(CZAC_PROCID_ZERO,  ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_ONE,   ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_TWO,   ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_THREE, ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
#endif /*DM*/

         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     0, 0)
#else /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
#ifdef SB
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */         

#ifdef DM
         cmXtaTopCoupling(CZAC_PROCID_ZERO, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
#endif /*DM*/
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   cmXtaTopStart("LC ALL with LCLW for CZT ")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       CZAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       CZAC_PROCID_ZERO,
       CZAC_PROCID_ONE,
       CZAC_PROCID_TWO,
       CZAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   rsActvTsk      )

         cmXtaTopEntity(1, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, czAcSbActvInit, czAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTPERM, PRIOR0, NULLP, hiScanPermTsk         )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )

#endif /* HI */

#else   /*SS_MULTIPLE_PROCS*/

         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   rsActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, czAcSbActvInit, czAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* HI */
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)

#ifdef SB
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */         

#ifdef DM
         cmXtaTopCoupling(CZAC_PROCID_ZERO,  ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_ONE,   ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_TWO,   ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_THREE, ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
#endif /*DM*/
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
#else  /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)

#ifdef SB
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */

#ifdef DM
         cmXtaTopCoupling(CZAC_PROCID_ZERO, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_SINGLE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
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
       CZAC_PROCID_SINGLE 
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
   cmXtaTopProcStart(4)            
       CZAC_PROCID_ZERO,
       CZAC_PROCID_ONE,
       CZAC_PROCID_TWO,
       CZAC_PROCID_THREE,
   cmXtaTopProcEnd  
#endif  /* SS_MULTIPLE_PROCS   */
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

#ifdef SS_MULTIPLE_PROCS

         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTRS,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   rsActvTsk      )

         cmXtaTopEntity(1, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, czAcSbActvInit, czAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID+4,   TTPERM, PRIOR0, NULLP, hiScanPermTsk         )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* HI */

#else   /*SS_MULTIPLE_PROCS*/

         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTRS,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   rsActvTsk      )
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
#ifdef SB
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif /* SB */
#ifdef DM
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, czAcSbActvInit, czAcSbActvTsk   )
#endif /*DM*/

#ifdef HI
#ifndef HI_MULTI_THREADED 
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID+4,   TTNORM, PRIOR0, NULLP, hiScanPermTsk  )
#endif   /* HI_MULTI_THREADED  */
         cmXtaTopEntity(1, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* HI */
#endif /* SS_MULTIPLE_PROCS */

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ONE,    ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)

#ifdef SB
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_ZERO,   ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,    13, 1)
         cmXtaTopCoupling(CZAC_PROCID_ONE,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,    13, 1)
         cmXtaTopCoupling(CZAC_PROCID_TWO,    ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,    13, 1)
         cmXtaTopCoupling(CZAC_PROCID_THREE,  ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,    13, 1)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */         

#ifdef DM
         cmXtaTopCoupling(CZAC_PROCID_ZERO,  ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_ONE,   ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_TWO,   ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CZAC_PROCID_THREE, ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
#endif /*DM*/

         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID, CZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     1, 1)
#else  /* SS_MULTIPLE_PROCS */
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTCZ,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTRS,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTCZ,  CMXTA_INST_ID,     2, 2)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID, CZAC_PROCID_ONE, ENTTST, CMXTA_INST_ID,     1, 1)

#ifdef SB
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSM,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID,    13, 1)
         cmXtaTopCoupling(CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* SB */

#ifdef DM
         cmXtaTopCoupling(CZAC_PROCID_ZERO, ENTCZ,  CMXTA_INST_ID, CZAC_PROCID_ONE, ENTSB,  CMXTA_INST_ID + 5, 1, 3)  /*-- DUMMY SCTP --*/
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

         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE1, ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )

         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE2, ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )

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

         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )

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
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTRS,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   rsActvTsk      )
#ifdef DM
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, czAcSbActvInit, czAcSbActvTsk   )
#endif /*DM*/
      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTRS,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE1,  ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE2,  ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
#ifdef SB
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,  ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE1,  ENTSB,  CMXTA_INST_ID,     13, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE2,  ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID,     13, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
#endif 
#ifdef DM
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE1, ENTCZ,  CMXTA_INST_ID,  CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 0, 0)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE2, ENTCZ,  CMXTA_INST_ID,  CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 0, 0)  /*-- DUMMY SCTP --*/
#endif /*DM*/
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRS,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE1,  ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRS,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE2,  ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRS,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,  ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE1, ENTHI,  CMXTA_INST_ID,     12, 2)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE2,  ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTHI,  CMXTA_INST_ID,     12, 2)
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
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTRS,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   rsActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTCZ,  CMXTA_INST_ID,     TTNORM, PRIOR0, czActvInit,   czActvTsk      )
#ifdef HI
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID,     TTNORM, PRIOR0, hiActvInit,   hiActvTsk      )
#endif /* HI */
#ifdef SB               
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID,     TTNORM, PRIOR0, sbActvInit,   sbActvTsk      )
#endif
#ifdef DM
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID+5,   TTNORM, PRIOR0, czAcSbActvInit, czAcSbActvTsk   )
#endif /*DM*/
      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTRS,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTCZ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE , ENTCZ,  CMXTA_INST_ID,     0, 0)
#ifdef HI
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /*HI*/
#ifdef SB
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID,     0, 0)
#endif  /* SB */

#ifdef SB
         cmXtaTopCoupling(CMXTA_PROCID_MASTER,  ENTCZ, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE ,  ENTCZ, CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTSB,  CMXTA_INST_ID,     0, 0)
#ifdef HI
         cmXtaTopCoupling(CMXTA_PROCID_MASTER,  ENTSB, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,   ENTSB, CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* HI */
#endif /* SB */
#ifdef HI
         cmXtaTopCoupling(CMXTA_PROCID_MASTER,  ENTCZ, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTHI,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,   ENTCZ, CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTHI,  CMXTA_INST_ID,     0, 0)
#endif /* HI */
#ifdef DM
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 0, 0)  /*-- DUMMY SCTP --*/
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE , ENTCZ,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSB,  CMXTA_INST_ID + 5, 0, 0)  /*-- DUMMY SCTP --*/
#endif /*DM*/
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRS,  CMXTA_INST_ID, CMXTA_PROCID_MASTER,  ENTCZ, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTRS,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE ,  ENTCZ, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID,     1, 1)

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/
#endif /*-- CMXTA_MASTER --*/

};

/********************************************************************30**

         End of file:     czac_prof.c@@/main/2 - Tue Aug 30 18:35:52 2011

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
/main/1      ---       sy       1. LTE-X2AP Initial Release.
/main/2      ---       pt       1. LTE-X2AP 3.1 release.
*********************************************************************91*/
