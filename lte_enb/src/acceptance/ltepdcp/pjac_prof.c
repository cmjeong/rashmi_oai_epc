

/********************************************************************20**

     Name:    PDCP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source

     File:    pjac_prof.c

     Sid:      pjac_prof.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:07 2015

     Prg:     Adarsh 
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

#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */


#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */

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
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */

#include "pj.x"
#include "pj.h"
#include "pj.x"
#include "pj_udx.h"
#include "pj_udx.x"
#include "pj_dl.x"
#include "pj_ul.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */

PUBLIC CmXtaTopology cmXtaTop[] =
{
#ifdef CMXTA_MASTER
   cmXtaTopStart("TC (All)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
   cmXtaTopProcStart(1)  
       PJAC_PROCID_SINGLE 
   cmXtaTopProcEnd
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
 
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     TTNORM, PRIOR0, pjDlActvInit,   pjDlActvTsk      )
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,    TTNORM, PRIOR0, pjUlActvInit,   pjUlActvTsk      )

#ifdef KW_PDCP
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID,     TTNORM, PRIOR0, pxActvInit,   pxActvTsk      )
#ifdef PJ_SEC_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOS, CMXTA_INST_ID,     TTNORM, PRIOR0, osActvInit,  osActvTsk     )
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOC, CMXTA_INST_ID,     TTNORM, PRIOR0, ocActvInit,  ocActvTsk     )
#endif /* PJ_CMP_ASYNC */

#else  /* #ifndef KW_PDCP */       
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID,     TTNORM, PRIOR0, pxActvInit,   pxActvTsk      )
#ifdef PJ_SEC_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOS, CMXTA_INST_ID,     TTNORM, PRIOR0, osActvInit,  osActvTsk     )
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOC, CMXTA_INST_ID,     TTNORM, PRIOR0, ocActvInit,  ocActvTsk     )
#endif /* PJ_CMP_ASYNC */
#endif /* KW_PDCP */


      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     1, 1)

/*Pradeep - added coupling b/w RLC-UL and RLC-DL*/
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     2, 2)
         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
#ifdef KW_PDCP
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     1, 1)
 
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     1, 1)

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     1, 1)
         /* Venki */
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     1, 1)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     2, 1)
         /* Venki */
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     2, 1)
#ifdef PJ_SEC_ASYNC
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTOS,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         /* Venki */
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTOS,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTOC,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         /* Venki */
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTOC,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)
#endif /* PJ_CMP_ASYNC */
        
         /* Venki - adding on May29 */
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,    1, 1)

#else
         /* ############################ ifndef KW_PDCP ################################################## */
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     1, 1)
         /* Venki */
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     1, 1)

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     1, 1)

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     1, 1)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     2, 1)

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     2, 1)
#ifdef PJ_SEC_ASYNC
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTOS,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         /* Venki */
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTOS,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTOC,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         /* Venki */
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTOC,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)
#endif /* PJ_CMP_ASYNC */

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     2, 1)
        /* Venki */
         /*Pradeep - KW-UL to PJ-UL and PJ-DL to KW-DL*/
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,    2, 1)
#endif /* KW_PDCP */
         /* ############################################################################################### */

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID,  PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     1, 1)
         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1, PJAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     1, 1)
         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     2, 2)

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/

   cmXtaTopStart("LC (LKW, CKW, KWU, RGU)")
      /*-- Number of System Tasks --*/
      cmXtaTopSTasks(1)

      /*-- Number of Tapa Processors, in absence of SS_MULTIPLE_PROCS, only the
           first one will be used, 0 is a reserved Proc Id --*/
   cmXtaTopProcStart(1)  
       PJAC_PROCID_SINGLE 
   cmXtaTopProcEnd
           
      /*-- TAPA Entities to be registered on this instance --*/
      /*-- sTsk, proc, ent, inst, type, prior, initTsk, actvTsk --*/
      cmXtaTopEntitiesStart

         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   smActvTsk      )
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     TTNORM, PRIOR0, smActvInit,   cmXtaActvTsk   )
#ifdef KW         
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,        TTNORM, PRIOR0, kwDlActvInit,   kwDlActvTsk      )
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,         TTNORM, PRIOR0, kwUlActvInit,   kwUlActvTsk      )
#endif
#ifdef PJ         
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,        TTNORM, PRIOR0, pjDlActvInit,   pjDlActvTsk      )
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,       TTNORM, PRIOR0, pjUlActvInit,   pjUlActvTsk      )
#endif
#ifdef KW_PDCP
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID,     TTNORM, PRIOR0, pxActvInit,   pxActvTsk      )
#ifdef PJ_SEC_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOS, CMXTA_INST_ID,     TTNORM, PRIOR0, osActvInit,  osActvTsk     )
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOC, CMXTA_INST_ID,     TTNORM, PRIOR0, ocActvInit,  ocActvTsk     )
#endif /* PJ_CMP_ASYNC */
#endif /* KW_PDCP */
       
       /* #######################################ifndef KW_PDCP ############################################### */
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID,     TTNORM, PRIOR0, pxActvInit,   pxActvTsk      )
#ifdef PJ_SEC_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOS, CMXTA_INST_ID,     TTNORM, PRIOR0, osActvInit,  osActvTsk     )
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOC, CMXTA_INST_ID,     TTNORM, PRIOR0, ocActvInit,  ocActvTsk     )
#endif /* PJ_CMP_ASYNC */

        /* ##################################################################################################### */


         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID,     TTNORM, PRIOR0, nhActvInit,   nhActvTsk      )

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     0, 0)
         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
#ifdef KW_PDCP
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)
         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)
         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)
#ifdef PJ_SEC_ASYNC
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTOS, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1, PJAC_PROCID_SINGLE, ENTOS, CMXTA_INST_ID,     0, 0)
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTOC, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1, PJAC_PROCID_SINGLE, ENTOC, CMXTA_INST_ID,     0, 0)
#endif /* PJ_CMP_ASYNC */

#else
         /* #########################################ifndef KW_PDCP ############################################ */
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTSM,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)
#ifdef PJ_SEC_ASYNC
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTOS, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1, PJAC_PROCID_SINGLE, ENTOS, CMXTA_INST_ID,     0, 0)
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTOC, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1, PJAC_PROCID_SINGLE, ENTOC, CMXTA_INST_ID,     0, 0)
#endif /* PJ_CMP_ASYNC */
        /* ####################################################################################################### */

         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     0, 0)
#endif /* KW_PDCP */

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTNH,  CMXTA_INST_ID,         PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1,     0, 0)
         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTKW,  CMXTA_INST_ID+1, PJAC_PROCID_SINGLE, ENTRG,  CMXTA_INST_ID,     0, 0)

         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID, PJAC_PROCID_SINGLE, ENTTST, CMXTA_INST_ID,     1, 1)
         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     2, 2)

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
#ifdef KW
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTKW,  CMXTA_INST_ID, TTNORM,         PRIOR0, kwDlActvInit,   kwDlActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTKW,  CMXTA_INST_ID+1, TTNORM,         PRIOR0, kwUlActvInit,   kwUlActvTsk      )
#endif
#ifdef PJ         
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTPJ,  CMXTA_INST_ID, TTNORM,         PRIOR0, pjDlActvInit,   pjDlActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_SLAVE, ENTPJ,  CMXTA_INST_ID+1, TTNORM,         PRIOR0, pjUlActvInit,   pjUlActvTsk      )
#endif
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
#ifdef KW_PDCP
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID,     TTNORM, PRIOR0, pxActvInit,   pxActvTsk      )
#ifdef PJ_SEC_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOS, CMXTA_INST_ID,     TTNORM, PRIOR0, osActvInit,  osActvTsk     )
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOC, CMXTA_INST_ID,     TTNORM, PRIOR0, ocActvInit,  ocActvTsk     )
#endif /* PJ_CMP_ASYNC */
#else
       /* ################################## ifndef KW_PDCP ################################################## */

         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTPX,  CMXTA_INST_ID,     TTNORM, PRIOR0, pxActvInit,   pxActvTsk      )
#ifdef PJ_SEC_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOS, CMXTA_INST_ID,     TTNORM, PRIOR0, osActvInit,  osActvTsk     )
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopEntity(1, PJAC_PROCID_SINGLE, ENTOC, CMXTA_INST_ID,     TTNORM, PRIOR0, ocActvInit,  ocActvTsk     )
#endif /* PJ_CMP_ASYNC */
        /* #################################################################################################### */

         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID,         TTNORM, PRIOR0, pjDlActvInit,   pjDlActvTsk      )
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID+1,         TTNORM, PRIOR0, pjUlActvInit,   pjUlActvTsk      )
#endif /* KW_PDCP */
         cmXtaTopEntity(1, CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID,     TTNORM, PRIOR0, nhActvInit,   nhActvTsk      )

      cmXtaTopEntitiesEnd

      /*-- Selector Coupling between user and provider entities --*/
      /*-- dstProc, dstEnt, dstInst, srcProc, srcEnt, srcInst, toSel, fromSel --*/
      cmXtaTopCouplingStart

         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID,         CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1,     0, 0)
         
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTRG,  CMXTA_INST_ID,     0, 0)
#ifdef KW_PDCP
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID,         CMXTA_PROCID_SLAVE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)
         
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,   CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,   CMXTA_INST_ID,         CMXTA_PROCID_SLAVE,  ENTPJ,  CMXTA_INST_ID+1,     0, 0)
         
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPX,   CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPX,   CMXTA_INST_ID,         CMXTA_PROCID_SLAVE,  ENTPJ,  CMXTA_INST_ID+1,     0, 0)
#ifdef PJ_SEC_ASYNC
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTPJ,   CMXTA_INST_ID, CMXTA_PROCID_MASTER,  ENTOS, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTPJ,   CMXTA_INST_ID+1, CMXTA_PROCID_MASTER,  ENTOS, CMXTA_INST_ID,     0, 0)
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTPJ,   CMXTA_INST_ID, CMXTA_PROCID_MASTER,  ENTOC, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTPJ,   CMXTA_INST_ID+1, CMXTA_PROCID_MASTER,  ENTOC, CMXTA_INST_ID,     0, 0)
#endif /* PJ_CMP_ASYNC */
         /* Venki - adding coupling b/w PDCP DL- RLC DL and RLC-DL and RLC-UL */
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID+1,  CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1,     1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID,     1, 1)
#else

         /* ##################################### ifndef KW_PDCP ################################################## */
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE, ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTSM,  CMXTA_INST_ID,         CMXTA_PROCID_SLAVE, ENTPJ,  CMXTA_INST_ID+1,     0, 0)

         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,   CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,   CMXTA_INST_ID,         CMXTA_PROCID_SLAVE,  ENTPJ,  CMXTA_INST_ID+1,     0, 0)

         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPX,   CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTPJ,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPX,   CMXTA_INST_ID,         CMXTA_PROCID_SLAVE,  ENTPJ,  CMXTA_INST_ID+1,     0, 0)
#ifdef PJ_SEC_ASYNC
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTPJ,   CMXTA_INST_ID, CMXTA_PROCID_MASTER,  ENTOS, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTPJ,   CMXTA_INST_ID+1, CMXTA_PROCID_MASTER,  ENTOS, CMXTA_INST_ID,     0, 0)
#endif /* PJ_SEC_ASYNC */
#ifdef PJ_CMP_ASYNC
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTPJ,   CMXTA_INST_ID, CMXTA_PROCID_MASTER,  ENTOC, CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE, ENTPJ,   CMXTA_INST_ID+1, CMXTA_PROCID_MASTER,  ENTOC, CMXTA_INST_ID,     0, 0)
#endif /* PJ_CMP_ASYNC */
         /* Venki - adding coupling b/w PDCP DL- RLC DL and RLC-DL and RLC-UL */
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID+1,  CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1,     1, 1)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID,     1, 1)
         /* ######################################################################################################### */

         /*cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID,     CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1,     0, 0)
         
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID+1, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTPJ,  CMXTA_INST_ID+1,         CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1,     0, 0)*/
#endif /* KW_PDCP */
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID, CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTNH,  CMXTA_INST_ID,         CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1,     0, 0)
         
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTRG,  CMXTA_INST_ID,     0, 0)
         cmXtaTopCoupling(CMXTA_PROCID_SLAVE,  ENTKW,  CMXTA_INST_ID+1, CMXTA_PROCID_MASTER, ENTRG,  CMXTA_INST_ID,     0, 0)
         
         cmXtaTopCoupling(CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID, CMXTA_PROCID_MASTER, ENTTST, CMXTA_INST_ID,     1, 1)
         
         cmXtaTopCoupling(PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID,     PJAC_PROCID_SINGLE, ENTPJ,  CMXTA_INST_ID+1,     2, 2)

      cmXtaTopCouplingEnd
   cmXtaTopEnd /*-- End Of Profile --*/
#endif /*-- CMXTA_MASTER --*/

};

/********************************************************************30**

         End of file:     pjac_prof.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:07 2015

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
/main/1      ---       vb         1. LTE PDCP Initial release 2.1
*********************************************************************91*/
