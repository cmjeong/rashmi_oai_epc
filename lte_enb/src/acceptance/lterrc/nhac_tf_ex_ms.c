/********************************************************************20**

     Name:    
             

     Type:    C source file

     Desc:    Functions required for scheduling and initialization.


     File:    nhac_tf_ex_ms.c

     Sid:      nhac_tf_ex_ms.c@@/main/2 - Fri Jul  1 01:13:09 2011

     Prg:     yk 

*********************************************************************21*/
/* header include files (.h) */
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
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"

/* local defines */

/* local typedefs */

/* local externs */

/* functions in other modules */

/* public variable declarations */

/* private variable declarations */

/*
*     support functions
*/

/* ------------------------------------------------------------ */

/*
*
*       Fun:    activation task
*
*       Desc:   Processes received event from Upper/Lower Layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   nhac_tf_ex_ms.c.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcTfActvTsk
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 nhAcTfActvTsk(pst, mBuf)
Pst    *pst;                /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret = ROK;

   TRC3(nhAcTfActvTsk)

   switch(pst->srcEnt)
   {
      case ENTNH:
      {
#if (defined(RRC_PHY_CFG_SUPP) && defined(LCNHLICTF))
         switch(pst->event)
         {
#ifdef LCCTF            
            case  EVTCTFBNDREQ:
            {
               ret = cmUnpkCtfBndReq(DmUiCtfBndReq, pst, mBuf);
               break;
            }
            case  EVTCTFUBNDREQ:
            {
               ret = cmUnpkCtfUbndReq(DmUiCtfUbndReq, pst, mBuf);
               break;
            }
            case  EVTCTFCFGREQ:
            {
               ret = cmUnpkCtfCfgReq(DmUiCtfCfgReq, pst, mBuf);
               break;
            }
            case  EVTCTFUEIDCHGREQ:
            {
               ret = cmUnpkCtfUeIdChgReq(DmUiCtfUeIdChgReq, pst, mBuf);
               break;
            }
            default:
            {
               CMXTA_DBG_ERR((_cmxtap, "nhAcTfActvTsk(): Invalid Event(%d) from service user", pst->event));
               (Void)SPutMsg(mBuf);
               ret = RFAILED;
               break;
            }
#endif /* LCCTF */            
         }/* end switch */
#endif
         break;
      }

      default:
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcTfActvTsk(): Invalid source entity (%d)", pst->srcEnt));
         (Void)SPutMsg(mBuf);
         ret = RFAILED;
         break;
      } /* end of default  */
   }/* end of switch */

   SExitTsk();

   RETVALUE(ret);
}/* end of nhAcTfActvTsk */

/*
*
*      Fun:   Activate Task - initialize
* 
*      Desc:  Invoked by system services to initialize Dummy PHY Task.
* 
*      Ret:   ROK
* 
*      Notes: None
* 
*      File:  nhac_tf_ex_ms.c.c
* 
*/

#ifndef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 nhAcTfActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 nhAcTfActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
#else
#ifdef ANSI
PUBLIC S16 nhAcTfActvInit
(
ProcId proc,           /* procId */
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason,         /* reason */
Void **xxCb            /* Layer Cb */
)
#else
PUBLIC S16 nhAcTfActvInit( proc, entity, inst, region, reason, xxCb)
ProcId proc;           /* procId */
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
Void **xxCb;           /* Layer Cb */
#endif
#endif /* SS_MULTIPLE_PROCS */
{

   TRC2(nhAcTfActvInit)

   UNUSED(entity);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);

   RETVALUE(ROK);
}/* end of nhAcTfActvInit */

/********************************************************************30**

*********************************************************************31*/
/**********************************************************************
         End of file:     nhac_tf_ex_ms.c@@/main/2 - Fri Jul  1 01:13:09 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat     init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     yk               1. RRC LTE Initial Release.
/main/2      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
