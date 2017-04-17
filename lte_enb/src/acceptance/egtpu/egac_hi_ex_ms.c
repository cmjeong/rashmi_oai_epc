
/********************************************************************20**

     Name:    TCP UDP Convergence Layer - external - mos
              (TUCL)

     Type:    C source file

     Desc:    Functions required for scheduling and initialization.


     File:    egac_hi_ex_ms.c

     Sid:      egac_hi_ex_ms.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:31 2015

     Prg:     an

*********************************************************************21*/

/* header include files (.h) */
#include "egac_acc.x"
#include "hit.h"
#include "hit.x"
#include "egac_hit.x"


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
*       File:   egac_hi_ex_ms.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcHiActvTsk
(
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 egAcHiActvTsk(pst, mBuf)
Pst    *pst;                /* post */
Buffer *mBuf;               /* message buffer */
#endif
{

   S16 ret = ROK;
#ifdef IPV6_OPTS_SUPPORTED
   Mem memInfo;             /* mem info passed when calling cmUnpkHitUDatReq */
#endif

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHiActvTsk)

   switch(pst->srcEnt)
   {
#ifdef LCHIUIHIT
#ifndef REVIEW
      case ENTEG:
      {
         switch(pst->event)
         {

            case  EVTHITBNDREQ:
               ret = cmUnpkHitBndReq(DHiLiHitBndReq, pst, mBuf);
               break;

            case  EVTHITUBNDREQ:
               ret = cmUnpkHitUbndReq(DHiLiHitUbndReq, pst, mBuf);
               break;

            case  EVTHITSRVOPENREQ:
               ret = cmUnpkHitServOpenReq(DHiLiHitServOpenReq, pst, mBuf);
               break;

            case  EVTHITCONREQ:

               ret = cmUnpkHitConReq(DHiLiHitConReq, pst, mBuf);
               break;

            case  EVTHITCONRSP:
               ret = cmUnpkHitConRsp(DHiLiHitConRsp, pst, mBuf);
               break;

            case  EVTHITDATREQ:

               ret = cmUnpkHitDatReq(DHiLiHitDatReq, pst, mBuf);
               break;
            case  EVTHITUDATREQ:

#ifdef IPV6_OPTS_SUPPORTED
               memInfo.region = hiCb.hiInit.region;
               memInfo.pool = hiCb.hiInit.pool;
               ret = cmUnpkHitUDatReq(DHiLiHitUDatReq, pst, mBuf, &memInfo);
#else
               ret = cmUnpkHitUDatReq(DHiLiHitUDatReq, pst, mBuf);
#endif /* IPV6_OPTS_SUPPORTED */
               break;

            case  EVTHITDISCREQ:
               ret = cmUnpkHitDiscReq(DHiLiHitDiscReq, pst, mBuf);
               break;
            default:
               CMXTA_DBG_ERR((_cmxtap, "egAcHiActvTsk(): Invalid Event(%d) from service user", pst->event));
               (Void)SPutMsg(mBuf);
               ret = RFAILED;
               break;
         }/* end switch */
         break;
      }
#endif /*review */      
#endif /* LCHIUIHIT */

      default:
         CMXTA_DBG_ERR((_cmxtap, "egAcHiActvTsk(): Invalid source entity (%d)", pst->srcEnt));
         (Void)SPutMsg(mBuf);
         ret = RFAILED;
         break;
   }/* end of switch */

   SExitTsk();

   RETVALUE(ret);
}/* end of egAcHiActvTsk */

/*
*
*      Fun:   Activate Task - initialize
* 
*      Desc:  Invoked by system services to initialize a task.
* 
*      Ret:   ROK
* 
*      Notes: None
* 
*      File:  egac_hi_ex_ms.c
* 
*/
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 egAcHiActvInit
(
ProcId procId,         /* procId */
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason,         /* reason */
Void **xxCb           /* Protocol Control Block */
)
#else
PUBLIC S16 egAcHiActvInit(procId,entity, inst, region, reason, xxCb)
ProcId procId;         /* procId */
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
Void **xxCb;           /* Protocol Control Block */
#endif
#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 egAcHiActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 egAcHiActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
#endif /*-- SS_MULTIPLE_PROCS --*/
{

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcHiActvInit)

   RETVALUE(ROK);
}/* end of egAcHiActvInit */

/********************************************************************30**

         End of file:     egac_hi_ex_ms.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:31 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rss         1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3     eg003.201 psingh      1. Merged code from eg006.102 to Fix TRACE5 
                                     macro related issue 
*********************************************************************91*/
