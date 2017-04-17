/********************************************************************20**

     Name:    
             

     Type:    C source file

     Desc:    Functions required for scheduling and initialization.


     File:    nhac_pj_ex_ms.c

     Sid:      nhac_pj_ex_ms.c@@/main/3 - Fri Jul  1 01:13:07 2011

     Prg:     dm

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

#include "cpj.h"
#include "cpj.x"
#include "pju.h"
#include "pju.x"
#include "nhac_acc.x"

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
*       File:   nhac_pj_ex_ms.c.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcPjActvTsk
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 nhAcPjActvTsk(pst, mBuf)
Pst    *pst;                /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret = ROK;
#ifdef LCPJU
   TRC3(nhAcPjActvTsk)

   switch(pst->srcEnt)
   {
      case ENTNH:
      {
         switch(pst->event)
         {
#ifdef LCNHLIPJU
            case  EVTPJUBNDREQ:
            {
               ret = cmUnpkPjuBndReq(DmUiPjuBndReq, pst, mBuf);
               break;
            }
            case  EVTPJUUBNDREQ:
            {
               ret = cmUnpkPjuUbndReq(DmUiPjuUbndReq, pst, mBuf);
               break;
            }
            case  EVTPJUDATREQ:
            {
               ret = cmUnpkPjuDatReq(DmUiPjuDatReq, pst, mBuf);
               break;
            }
#endif /* LCNHLIPJU */
#ifdef LCNHLICPJ
            case EVTCPJBNDREQ:
            {
               ret = cmUnpkCpjBndReq(DmUiCpjBndReq, pst, mBuf);
               break;
            }
            case EVTCPJCFGREQ:
            {
               ret = cmUnpkCpjCfgReq(DmUiCpjCfgReq, pst, mBuf);
               break;
            } 
            case EVTCPJUBNDREQ:
            {
               ret = cmUnpkCpjUbndReq(DmUiCpjUbndReq, pst, mBuf);
               break;
            }
            case EVTCPJUEIDCHGREQ:
            {
               ret = cmUnpkCpjUeIdChgReq(DmUiCpjUeIdChgReq, pst, mBuf);
               break;
            }
            case EVTCPJSECCFGREQ:
            {
               ret = cmUnpkCpjSecCfgReq(DmUiCpjSecCfgReq ,pst, mBuf);
               break;
            }
            case EVTCPJSDUSTAREQ:
            {
               ret = cmUnpkCpjSduStaReq(DmUiCpjSduStaReq ,pst, mBuf);
               break;
            }
            case EVTCPJCOUNTREQ:
            {
               ret = cmUnpkCpjCountReq(DmUiCpjCountReq ,pst, mBuf);
               break;
            }
            case EVTCPJREESTREQ:
            {
               ret = cmUnpkCpjReEstReq(DmUiCpjReEstReq ,pst, mBuf);
               break;
            }
            case EVTCPJSTARTDATAFWDREQ:
	    {
 		ret = cmUnpkCpjStartDataFwdReq(DmUiCpjDatForwardReq, pst, mBuf);
		break;
	    }
#endif /* LCNHLICPJ */
            default:
            {
               CMXTA_DBG_ERR((_cmxtap, "nhAcPjActvTsk(): Invalid Event(%d) from service user", pst->event));
               (Void)SPutMsg(mBuf);
               ret = RFAILED;
               break;
            }
         }/* end switch */
         break;
      }

      default:
      {
         CMXTA_DBG_ERR((_cmxtap, "nhAcPjActvTsk(): Invalid source entity (%d)", pst->srcEnt));
         (Void)SPutMsg(mBuf);
         ret = RFAILED;
         break;
      } /* end of default  */
   }/* end of switch */

   SExitTsk();
#endif
   RETVALUE(ret);
}/* end of nhAcPjActvTsk */


/*
*
*      Fun:   Activate Task - initialize
* 
*      Desc:  Invoked by system services to initialize Dummy MAC Task.
* 
*      Ret:   ROK
* 
*      Notes: None
* 
*      File:  nhac_pj_ex_ms.c.c
* 
*/

#ifndef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 nhAcPjActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 nhAcPjActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
#else
#ifdef ANSI
PUBLIC S16 nhAcPjActvInit
(
ProcId proc,           /* procId */
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason,         /* reason */
Void **xxCb            /* Layer Cb */
)
#else
PUBLIC S16 nhAcPjActvInit( proc, entity, inst, region, reason, xxCb)
ProcId proc;           /* procId */
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
Void **xxCb;           /* Layer Cb */
#endif
#endif /* SS_MULTIPLE_PROCS */
{

   TRC2(nhAcPjActvInit)

   UNUSED(entity);
   UNUSED(inst);
   UNUSED(region);
   UNUSED(reason);

   RETVALUE(ROK);
}/* end of nhAcPjActvInit */



/* ------------------------------------------------------------ */



/********************************************************************30**

*********************************************************************31*/
/**********************************************************************
         End of file:     nhac_pj_ex_ms.c@@/main/3 - Fri Jul  1 01:13:07 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    dm               1. LTE RRC Initial Release.
/main/2      ---    chebli           1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

