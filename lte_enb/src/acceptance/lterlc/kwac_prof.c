

/********************************************************************20**

     Name:    RLC - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    kwac_prof.c

     Sid:      kwac_prof.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:39 2014

     Prg:     cp 
*********************************************************************21*/


/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */
#include "kw_udx.h"

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#include "kw.x"
/*Pradeep - added kw_dl.x*/
#include "kw_udx.x"
#include "kw_dl.x"
#include "kw_ul.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */

PUBLIC CmXtaTopology cmXtaTop[] =
{
#ifdef CMXTA_MASTER
   cmXtaTopStart("TC (All)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1) /*Pradeep - TODO do we need to create two system tasks (for RLC-UL & RLC-DL)*/

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
   cmXtaTopProcStart(1)  
       KWAC_PROCID_SINGLE /*Pradeep - TODO do we need two procIds (for RLC-UL & RLC-DL)*/ 
   cmXtaTopProcEnd
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
/*Pradeep - added kwUlActvTsk & kwDlActvTsk*/
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     TTNORM, PRIOR0, kwDlActvInit,   kwDlActvTsk      )
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     TTNORM, PRIOR0, kwUlActvInit,   kwUlActvTsk      )
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     TTNORM, PRIOR0, pjActvInit,   pjActvTsk      )
/*Pradeep - added another instance for PDCP with instanceId - 1*/
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     TTNORM, PRIOR0, pjActvInit,   pjActvTsk      )
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID,     TTNORM, PRIOR0, nhActvInit,   nhActvTsk      )

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     1, 1)
/*Pradeep - added ENTKW instanceId - 1*/
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     1, 1)
/*Pradeep - added coupling b/w RLC-UL and RLC-DL*/
/*Pradeep - TODO what type of coupling need to use here*/
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     2, 2)

         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     2, 1)
/*Pradeep - added another instance for PDCP with instanceId - 1*/
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     2, 1)

         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     1, 1)
/*Pradeep - added ENTKW instanceId - 1*/
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     1, 1)
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
/*Pradeep - added ENTKW instanceId - 1*/
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1, KWAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   /*cmXtaTopStart("LC (LKW, CKW, KWU, RGU)")*/
   cmXtaTopStart("LC (LKW, CKW, KWU, RGU, UDX)") /*Pradeep - added UDX interface*/
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1) /*Pradeep - TODO do we need to create two system tasks (for RLC-UL & RLC-DL)*/

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
   cmXtaTopProcStart(1)  
       KWAC_PROCID_SINGLE /*Pradeep - TODO do we need two procIds (for RLC-UL & RLC-DL)*/ 
   cmXtaTopProcEnd
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
/*Pradeep - added kwUlActvTsk & kwDlActvTsk*/
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     TTNORM, PRIOR0, kwDlActvInit,   kwDlActvTsk      )
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     TTNORM, PRIOR0, kwUlActvInit,   kwUlActvTsk      )
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     TTNORM, PRIOR0, pjActvInit,   pjActvTsk      )
/*Pradeep - added another instance for PDCP with instanceId - 1*/
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     TTNORM, PRIOR0, pjActvInit,   pjActvTsk      )
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID,     TTNORM, PRIOR0, nhActvInit,   nhActvTsk      )
         cmXtaTopEntity(1, KWAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     0, 0)
/*Pradeep - added another instance for RLC with instanceId - 1*/
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     0, 0)
/*Pradeep - added coupling b/w RLC-UL and RLC-DL*/
/*Pradeep - TODO what type of coupling need to use here*/
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     2, 2)

         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     0, 0)
/*Pradeep - added another instance for PDCP with instanceId - 1*/
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     0, 0)
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     1, 1)
/*Pradeep - added ENTKW instanceId - 1*/
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     1, 1)
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
/*Pradeep - added ENTKW instanceId - 1*/
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1, KWAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(KWAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, KWAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)

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
/*Pradeep - added kwUlActvTsk & kwDlActvTsk*/
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTKW,  CMXTA_INST_ID, TTNORM, PRIOR0, kwDlActvInit,   kwDlActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTKW,  CMXTA_INST_ID+1, TTNORM, PRIOR0, kwUlActvInit,   kwUlActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTPJ,  CMXTA_INST_ID, TTNORM, PRIOR0, pjActvInit,   pjActvTsk      )
/*Pradeep - added another instance for PDCP with instanceId - 1*/
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTPJ,  CMXTA_INST_ID+1, TTNORM, PRIOR0, pjActvInit,   pjActvTsk      )

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
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID,     TTNORM, PRIOR0, pjActvInit,   pjActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTRG,  CMXTA_INST_ID,     TTNORM, PRIOR0, rgActvInit,   rgActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID,     TTNORM, PRIOR0, nhActvInit,   nhActvTsk      )

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID,     0, 0)
/*Pradeep - added another instance for RLC with instanceId - 1*/
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1,     0, 0)
/*Pradeep - added coupling b/w RLC-UL and RLC-DL*/
/*Pradeep - TODO what type of coupling need to use here*/
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1,     2, 2)

         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTRG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID,     0, 0)
/*Pradeep - added another instance for RLC & PDCP with instanceId - 1*/
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID+1, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID,     0, 0)
/*Pradeep - added ENTKW instanceId - 1*/
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTRG,  CMXTA_INST_ID,     0, 0)
/*Pradeep - added ENTKW instanceId - 1*/
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1, CMXTA_PROCID_MASTER, ENTRG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID,     1, 1)

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/
#endif /*-- CMXTA_MASTER --*/

};

/********************************************************************30**

         End of file:     kwac_prof.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:39 2014

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
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
*********************************************************************91*/

