/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */
#include "lry.h"

#include "cm_xta.h"
#include "cm_xta_app.h"
#include "cm_ftha.h"

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */
#include "lry.x"

#include "cm_xta_app.x"
#include "cm_ftha.x"
#include "cm_xta.x"

/********************************************************************20**

     Name:    Common 

     Type:    C source file

     Desc:    C code for dummy handling 

     File:    cm_xta_dsm_ex_ms.c

     Sid:      cm_xta_dsm_ex_ms.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:13 2015

     Prg:     up 

*********************************************************************21*/

/* header include files (.h) */


/*
*
*       Fun: cmXtaDsmActvTsk 
*
*       Desc: This is the active task for the dummy Stack manager
*              that will run on the slaves. This is needed to capture
*              the config confirms from relay. 
*              
*              
*       Ret:  ROK/RFAILED 
*              
*       Notes: 
*
*       File: cm_xta_dsm_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaDsmActvTsk
(
Pst            *pst,           /* pst structure */
Buffer         *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmXtaDsmActvTsk (pst, mBuf)
Pst            *pst;           /* pst structure */
Buffer         *mBuf;           /* message buffer */
#endif
{
   S16      ret;

   ret = ROK;
   TRC2(cmXtaDsmActvTsk)

      /* cm_xta_dsm_ex_ms_c_001.main_1: In case of new relay, the confirmation
       * is sent by the child thread */
#ifndef OLD_RY
      switch (pst->event)
      {
         case EVTLRYCFGCFM:
            CMXTA_DBG_INFO((_cmxtap, "Received Config confirm from Relay !\n"));
            /* cm_xta_dsm_ex_ms_c_001.main_1: It is required to unpack and send 
             * confirmation to XTA test engine so that the further configuration
             * takes place */
#ifdef CMXTA_FTHA_INTEGRATED
             ret = cmUnpkMiLryCfgCfm(rycmXtaGenCfgCfm, pst, mBuf);
#endif
            break;

         default:
            /*-- shouldn't get here --*/
            CMXTA_DBG_ERR((_cmxtap, "cmXtaDsmActvTsk() : Invalid event \n"));
            break;

      } /*-- End of switch --*/
#endif
} /*-- cmXtaDsmActvTsk --*/
 

/*****************************************************************************
*
*     Fun:   cmXtaDsmActvInit
*
*     Desc:  Invoked by system services to initialize the FM Layer
*            protocol layer.
*
*     Ret:   ROK   - ok
*
*     Notes: None
*
*     File:  cm_xta_dsm_ex_ms.c
*
*****************************************************************************/
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 cmXtaDsmActvInit
(
ProcId proc,                /* proc id */
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason,              /* reason */
void   **xxCb
)
#else
PUBLIC S16 cmXtaDsmActvInit(proc, ent, inst, region, reason, xxCb)
ProcId    proc;                 /* proc id */
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
void   **xxCb;
#endif
#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 cmXtaDsmActvInit
(
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 cmXtaDsmActvInit(ent, inst, region, reason)
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
#endif
#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(cmXtaDsmActvInit);

#ifdef SS_MULTIPLE_PROCS
   *xxCb = NULLP;
#endif
   RETVALUE(ROK);
} /* cmXtaDsmActvInit */


/********************************************************************30**

         end of file:     cm_xta_dsm_ex_ms.c@@/main/1 - wed jun 27 16:21:27 2007

*********************************************************************31*/


/********************************************************************40**

        notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ----     aj  1. main release
/main/2      ---      cm_xta_dsm_ex_ms_c_001.main_1  pka    1. Changes done for integration
                                                testing.
*********************************************************************91*/

