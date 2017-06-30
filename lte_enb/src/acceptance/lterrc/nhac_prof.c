/********************************************************************20**

     Name:    RRC

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_prof.c

     Sid:      nhac_prof.c@@/main/3 - Fri Jul  1 01:13:09 2011

     Prg:     rer

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "ctf.h"           /* PHY Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
/* external headers */


/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#include "nhac_asn.x"
using namespace NH_LTERRC_REL11;
#include "nhac_nhu.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "nh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"

PUBLIC CmXtaTopology cmXtaTop[] =
{
#ifdef CMXTA_MASTER
   /* Profile 0 for Master mode of execution */
   cmXtaTopStart(" MASTER ")
      /*-- Number of System Tasks --*/  
      cmXtaTopSTasks(1)

#ifndef SS_MULTIPLE_PROCS
      cmXtaTopProcStart(1)  
      CMXTA_PROCID_MASTER 
      cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
#endif  /* SS_MULTIPLE_PROCS */

       /*-- TAPA Entities to be registered on this instance --*/  
       /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
       cmXtaTopEntitiesStart
#ifdef SS_MULTIPLE_PROCS
#else  /* SS_MULTIPLE_PROCS */          
       cmXtaTopEntity(1, CMXTA_PROCID_SLAVE,  ENTNH,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhActvInit,     nhActvTsk)
       cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID,  TTNORM, PRIOR0, smActvInit,     smActvTsk)
       cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID,  TTNORM, PRIOR0, smActvInit,     cmXtaActvTsk)
       cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTRG,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcRgActvInit, nhAcRgActvTsk)  
       cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTKW,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcKwActvInit, nhAcKwActvTsk)  
       cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTNX,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcNxActvInit, nhAcNxActvTsk) 
       cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcPjActvInit, nhAcPjActvTsk) 
#ifdef RRC_PHY_CFG_SUPP
       cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTTF,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcTfActvInit, nhAcTfActvTsk) 
#endif /* RRC_PHY_CFG_SUPP */
#endif /* SS_MULTIPLE_PROCS */
       cmXtaTopEntitiesEnd

       /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
#else   
      cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID,  0, 0)
      cmXtaTopCoupling(CMXTA_PROCID_MASTER,ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID,  0, 0)
      cmXtaTopCoupling(CMXTA_PROCID_MASTER,ENTRG,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID,  0, 0)
      cmXtaTopCoupling(CMXTA_PROCID_MASTER,ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID,  0, 0)
      cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTKW, CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID, 0,0)
      cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTNX,  CMXTA_INST_ID, 0,0)
      cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTRG,  CMXTA_INST_ID, 0,0)
      cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTKW,  CMXTA_INST_ID, 0,0)
      cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID, 0,0)
#ifdef RRC_PHY_CFG_SUPP
      cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTTF,  CMXTA_INST_ID, 0,0)
#endif /* RRC_PHY_CFG_SUPP */

      cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, 0, 0)
      cmXtaTopCoupling(CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTRG,  CMXTA_INST_ID, 0, 0)
      cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, 0, 0)
      cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID, 0, 0)
      cmXtaTopCoupling(CMXTA_PROCID_SLAVE,  ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTNX,  CMXTA_INST_ID, 0, 0) 
#endif   /*  SS_MULTIPLE_PROCS  */

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile  0--*/

#endif /*-- CMXTA_MASTER --*/

   /* Profile 1 to run in SLAVE Mode */
   cmXtaTopStart("Slave")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

        /*   first one will be used, 0 is a reserved Proc Id --*/
      cmXtaTopProcStart(1)
         CMXTA_PROCID_SLAVE
      cmXtaTopProcEnd

      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID,   TTNORM, PRIOR0, nhActvInit, nhActvTsk)  
      cmXtaTopEntitiesEnd

      cmXtaTopCouplingStart
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTNH,  CMXTA_INST_ID, 0, 0)
      cmXtaTopCouplingEnd

   cmXtaTopEnd /*-- End Of Profile  1--*/

#ifdef CMXTA_MASTER
   /* Profile 2 to run in Loose Coupled Mode */
   cmXtaTopStart("LC (ALL)")

   /*-- Number of System Tasks --*/  
   cmXtaTopSTasks(1)

   /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the 
          first one wil be used, 0 is a reserved Proc Id --*/    
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       CMXTA_PROCID_MASTER
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
#endif  /* SS_MULTIPLE_PROCS */

 /*-- TAPA Entities to be registered on this instance --*/  
 /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/ 

  cmXtaTopEntitiesStart  
#ifdef SS_MULTIPLE_PROCS

#else  /* SS_MULTIPLE_PROCS   */
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,  TTNORM, PRIOR0, smActvInit,     cmXtaActvTsk)
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcRgActvInit, nhAcRgActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcKwActvInit, nhAcKwActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhActvInit,     nhActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcNxActvInit, nhAcNxActvTsk) 
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,  TTNORM,
PRIOR0, smNhActvInit, smNhActvTsk) 
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcPjActvInit, nhAcPjActvTsk) 
#ifdef RRC_PHY_CFG_SUPP
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcTfActvInit, nhAcTfActvTsk) 
#endif /* RRC_PHY_CFG_SUPP */
      
#endif  /* SS_MULTIPLE_PROCS   */
      cmXtaTopEntitiesEnd

       /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
#else   /* SS_MULTIPLE_PROCS   */
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, 0, 0)
#ifdef RRC_PHY_CFG_SUPP
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, 0, 0)
#endif /* RRC_PHY_CFG_SUPP */

#endif   /*  SS_MULTIPLE_PROCS  */
      cmXtaTopCouplingEnd
   
      cmXtaTopEnd  /*-- End Of Profile  2--*/

#ifdef DM
      /* Profile 3 to run in Tight Coupled Mode with Dmmy XTA layers */
      cmXtaTopStart("TC (ALL) with Dummy XTA Call back fuctions")

   /*-- Number of System Tasks --*/  
   cmXtaTopSTasks(1)

   /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the 
          first one wil be used, 0 is a reserved Proc Id --*/    
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       CMXTA_PROCID_SINGLE
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
#endif  /* SS_MULTIPLE_PROCS */

 /*-- TAPA Entities to be registered on this instance --*/  
 /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/ 

  cmXtaTopEntitiesStart  
#ifdef SS_MULTIPLE_PROCS

#else  /* SS_MULTIPLE_PROCS   */
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, TTNORM, PRIOR0, smActvInit,     cmXtaActvTsk)
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, TTNORM, PRIOR0, nhAcRgActvInit, nhAcRgActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, TTNORM, PRIOR0, nhAcKwActvInit, nhAcKwActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, TTNORM, PRIOR0, nhActvInit,     nhActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, TTNORM, PRIOR0, nhAcNxActvInit, nhAcNxActvTsk) 
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, TTNORM,
PRIOR0, smNhActvInit, smNhActvTsk) 
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, TTNORM, PRIOR0, nhAcPjActvInit, nhAcPjActvTsk)  
#ifdef RRC_PHY_CFG_SUPP
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, TTNORM, PRIOR0, nhAcTfActvInit, nhAcTfActvTsk)  
#endif /* RRC_PHY_CFG_SUPP */


#endif  /* SS_MULTIPLE_PROCS   */
      cmXtaTopEntitiesEnd

       /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS

#else   /* SS_MULTIPLE_PROCS   */
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 2, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, 1, 2)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 2, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, 1, 2)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 2, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, 1, 2)

         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 2, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, 1, 2)
#ifdef RRC_PHY_CFG_SUPP
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 2, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, 1, 2)
#endif /* RRC_PHY_CFG_SUPP */

#endif   /*  SS_MULTIPLE_PROCS  */
      cmXtaTopCouplingEnd
   
   cmXtaTopEnd /*-- End Of Profile  3--*/

#endif /* ifdef DM */

   /* Profile 4 to run in LWLC Mode */
   cmXtaTopStart("LWLC (ALL)")

   /*-- Number of System Tasks --*/  
   cmXtaTopSTasks(1)

   /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the 
          first one wil be used, 0 is a reserved Proc Id --*/    
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       CMXTA_PROCID_MASTER
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
#endif  /* SS_MULTIPLE_PROCS */

 /*-- TAPA Entities to be registered on this instance --*/  
 /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/ 

  cmXtaTopEntitiesStart  
#ifdef SS_MULTIPLE_PROCS

#else  /* SS_MULTIPLE_PROCS   */
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,  TTNORM, PRIOR0, smActvInit,     cmXtaActvTsk)
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcRgActvInit, nhAcRgActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcKwActvInit, nhAcKwActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhActvInit,     nhActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcNxActvInit, nhAcNxActvTsk) 
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,  TTNORM, PRIOR0, smNhActvInit, smNhActvTsk) 
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcPjActvInit, nhAcPjActvTsk) 
#ifdef RRC_PHY_CFG_SUPP
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID,  TTNORM, PRIOR0, nhAcTfActvInit, nhAcTfActvTsk) 
#endif /* RRC_PHY_CFG_SUPP */
      
#endif  /* SS_MULTIPLE_PROCS   */
      cmXtaTopEntitiesEnd

       /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS
#else   /* SS_MULTIPLE_PROCS   */
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, 2, 2)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 2, 2)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, 0, 0)
#ifdef RRC_PHY_CFG_SUPP
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, 0, 0)
#endif /* RRC_PHY_CFG_SUPP */

#endif   /*  SS_MULTIPLE_PROCS  */
      cmXtaTopCouplingEnd
   
      cmXtaTopEnd  /*-- End Of Profile  4--*/

   /* Profile 5 to run in Tight Coupled Mode */
      cmXtaTopStart("TC (ALL) with Actual Lower  Layers")

   /*-- Number of System Tasks --*/  
      cmXtaTopSTasks(1)

   /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the 
          first one wil be used, 0 is a reserved Proc Id --*/    
#ifndef SS_MULTIPLE_PROCS
   cmXtaTopProcStart(1)  
       CMXTA_PROCID_SINGLE
   cmXtaTopProcEnd
#else     /* SS_MULTIPLE_PROCS   */
#endif  /* SS_MULTIPLE_PROCS */

 /*-- TAPA Entities to be registered on this instance --*/  
 /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/ 

  cmXtaTopEntitiesStart  
#ifdef SS_MULTIPLE_PROCS

#else  /* SS_MULTIPLE_PROCS   */
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, TTNORM, PRIOR0, smActvInit,     cmXtaActvTsk)
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, TTNORM, PRIOR0, nhAcRgActvInit, nhAcRgActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, TTNORM, PRIOR0, nhAcKwActvInit, nhAcKwActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, TTNORM, PRIOR0, nhActvInit,     nhActvTsk)  
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, TTNORM, PRIOR0, nhAcNxActvInit, nhAcNxActvTsk) 
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, TTNORM,
PRIOR0, smNhActvInit, smNhActvTsk) 
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, TTNORM, PRIOR0, nhAcPjActvInit, nhAcPjActvTsk)  
#ifdef RRC_PHY_CFG_SUPP
      cmXtaTopEntity(1, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, TTNORM, PRIOR0, nhAcTfActvInit, nhAcTfActvTsk)  
#endif /* RRC_PHY_CFG_SUPP */


#endif  /* SS_MULTIPLE_PROCS   */
      cmXtaTopEntitiesEnd

       /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

#ifdef SS_MULTIPLE_PROCS

#else   /* SS_MULTIPLE_PROCS   */
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNX,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID, 1, 1)

         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, 1, 1)
#ifdef RRC_PHY_CFG_SUPP
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, 1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SINGLE, ENTTF,  CMXTA_INST_ID, 1, 1)
#endif /* RRC_PHY_CFG_SUPP */

#endif   /*  SS_MULTIPLE_PROCS  */
      cmXtaTopCouplingEnd
   
   cmXtaTopEnd /*-- End Of Profile  5--*/

#endif /*-- CMXTA_MASTER --*/

}; /* End of CmXtaTopology */



/**********************************************************************
         End of file:     nhac_prof.c@@/main/3 - Fri Jul  1 01:13:09 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    rer              1. LTE RRC Initial Release.
/main/2      ---    chebli           1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
