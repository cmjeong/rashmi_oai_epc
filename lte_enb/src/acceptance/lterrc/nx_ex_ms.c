/**********************************************************************
 
     Name:     RRC User

     Type:     C source file

     Desc:     C source code for upper layer(RX) across NHU interface

     File:     nx_ex_ms.c

     Sid:      nx_ex_ms.c@@/main/tenb_main_ccb/1 - Wed Jul 22 20:19:26 2015

     Prg:      rer 
  
**********************************************************************/
/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000369     LTE-RRC
*
*/

 
/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
 
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */

#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_mblk.h"       /* Common Mem Allocation Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_lte.h"       /* Common LTE Defines */
#include "cm_pasn.h"       /* Common Pasn Defines */

#include "nhu_asn.h"       /* NHU interface ASN defines */
#include "nhu.h"           /* NHU Interface defines */
#include "lnh.h"           /* LRR Interface defines */

#include "nh.h"            /* RRC defines */


/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_lib.x"        /* Common library Definitions */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_mblk.x"       /* Common Mem Allocation */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"       /* Common LTE Defines */
#include "cm_pasn.x"       /* Common Pasn Definitions */

#include "nhu.x"           /* NHU Interface includes */
#include "lnh.x"           /* LRR Interface includes */

#include "nh.x"            /* RRC includes */
/* forward references */

#ifdef __cplusplus
extern "C" {
#endif
/* Function Prototype Declarations */
PUBLIC S16 nxActvTsk ARGS((Pst *pst, Buffer *mBuf));
PUBLIC S16 nxActvInit ARGS((Ent entity, Inst inst, Region region,
                            Reason reason));


/************************************************************************
 *
 *      Fun:   nxActvTsk
 *
 *      Desc:  This is the entry point for all Loosely coupled messages
 *             that have the LTE-RRC as the destination. This includes Layer
 *             manager messages, Upper and Lower layer(s) messages.
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nx_ex_ms.c
 *
 ************************************************************************/


#ifdef ANSI
PUBLIC S16 nxActvTsk
(
Pst     *pst,                       /* post structure */
Buffer  *mBuf                       /* message buffer */
)
#else
PUBLIC S16 nxActvTsk(pst, mBuf)
Pst     *pst;                       /* post structure */
Buffer  *mBuf;                      /* message buffer */
#endif
{

    Mem sMem;
    Size maxBlkSize;
    
    maxBlkSize = NH_MEM_PDU_SIZE;
 
    sMem.region = 0;
    sMem.pool = 0;
 
    TRC3(nxActvTsk);
   
    switch(pst->srcEnt)
    { 
#ifdef LCNXLINHU
     case ENTNH : 
        switch ( pst->event )
         {
            case EVTNHUDATIND : 
               cmUnpkNhuDatInd(NxLiNhuDatInd, pst, mBuf, &sMem, NH_MEM_PDU_SIZE);
               break;
            case EVTNHUBNDCFM :
               cmUnpkNhuBndCfm(NxLiNhuBndCfm, pst, mBuf);
               break;
            case  EVTNHUERRIND:
               cmUnpkNhuErrInd(NxLiNhuErrInd, pst, mBuf,&sMem, NH_MEM_PDU_SIZE);
               break;
            case EVTNHUCFGCFM  :
               cmUnpkNhuCfgCfm(NxLiNhuCfgCfm, pst, mBuf,&sMem, NH_MEM_PDU_SIZE);
               break;
            case  EVTNHUCELLCFGCFM :
               cmUnpkNhuCellCfgCfm(NxLiNhuCellCfgCfm, pst, mBuf,&sMem, NH_MEM_PDU_SIZE);
               break;
 
            default :
               break;
         }
        break;
#endif /* LCNXLINHU */        
     default:
        SPutMsg(mBuf);
        break;
        
    } /* pst->srcEnt */     

    RETVALUE(ROK);
}


/**************************************************************************
 *
 *      Fun:   nxActvInit 
 *
 *      Desc:  Invoked by system services to initialize upper layer
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
 *      File:  nx_ex_ms.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 nxActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 nxActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
{

   TRC2(nxActvInit);
   UNUSED(inst);
   UNUSED(entity);
   UNUSED(region);
   UNUSED(reason);
   RETVALUE(ROK);
} /* end of funcion nxActvInit */
#ifdef __cplusplus
}
#endif

/**********************************************************************
 
         End of file:     nx_ex_ms.c@@/main/tenb_main_ccb/1 - Wed Jul 22 20:19:26 2015
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
   ver       pat     init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     rer             1. LTE RRC Initial Release.
/main/2      ---     chebli          1. LTE RRC release 2.1.
/main/3      ---     sbalakrishna    1. Updated for Release of 3.1.
*********************************************************************91*/
