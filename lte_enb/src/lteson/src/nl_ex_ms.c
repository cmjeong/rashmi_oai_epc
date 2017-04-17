/********************************************************************20**

     Name:     SON Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     nl_ex_ms.c

     Sid:      bk_ex_ms.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 17:51:11 2014

     Prg:      subhamay 

*********************************************************************21*/
static const char* RLOG_MODULE_NAME="SON";
static int RLOG_FILE_ID=248;
static int RLOG_MODULE_ID=256;

/* Header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"
#include "rl_common.h"     /* RLOG defines */
#include "rl_interface.h"
#include "cm_tkns.h"       /* Common Token defines */
#include "cm_mblk.h"       /* Common Mem Allocation defines */
#include "cm_llist.h"      /* Common Link List defines */
#include "cm_hash.h"       /* Common Hashlist defines */
#include "cm_pasn.h"       /* Common Pasn defines */
#include "cm_lte.h"        /* Common Pasn defines */

#include "lnl.h"           /* NL Interface defines */
#include "nlu.h"
#include "nl.h"            /* SON defines */

/* Header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "cm5.x"
#include "cm_tkns.x"       /* Common Token definitions */
#include "cm_mblk.x"       /* Common Memory Allocation */
#include "cm_llist.x"      /* Common Link List definitions */
#include "cm_hash.x"       /* Common Hashlist definitions */
#include "cm_lib.x"        /* Common Library definitions */
#include "cm_pasn.x"       /* Common Hashlist definitions */
#include "cm_lte.x"       /* Common Pasn defines */

#include "lnl.x"           /* NL Interface includes */
#include "nlu.x"
#include "nl.x"            /* SON includes */

/* local defines */
PUBLIC NlCb nlCb;
/* local typedefs */
 
/* local externs */

/* forward references */

/************************************************************************
 *
 *      Fun:   nlActvTsk
 *
 *      Desc:  This is the entry point for all loosely coupled messages
 *             that have the SON as the destination. This includes layer
 *             manager messages, eNodeB application messages.
 *
 *      Ret:   ROK - ok
 *
 *      Notes: None
 *
 *      File:  nl_ex_ms.c
 *
 ************************************************************************/
#ifdef ANSI
PUBLIC S16 nlActvTsk
(
Pst     *pst,                        /* Post structure */
Buffer  *mBuf                        /* message buffer */
)
#else /* ANSI */
PUBLIC S16 nlActvTsk(pst, mBuf)
Pst     *pst;                        /* Post structure */
Buffer  *mBuf;                       /* message buffer */
#endif /* ANSI */
{

   TRC3(nlActvTsk);
   
   switch(pst->srcEnt)
   {
      
      case ENTSM: /* Layer Manager events */
      {
         switch(pst->event)
         {
            case EVTLNLCFGREQ:
               cmUnpkLnlCfgReq(NlMiLnlCfgReq, pst, mBuf);
               break;
            case EVTLNLCNTRLREQ:
               cmUnpkLnlCntrlReq(NlMiLnlCntrlReq, pst, mBuf);
               break;
            case EVTLNLSTAIND:
               cmUnpkLnlStatInd(NlMiLnlStatInd, pst, mBuf);
               break;
            default:
               RLOG0(L_ERROR, "SON received Invalid Event received from SM \n");
               NL_FREE_MBUF(mBuf);
               break;
         } 
         break;
      }
      case ENTWR : /* eNB Application events */
      {
         switch(pst->event)  
         {
            case EVTNLUBNDREQ:
               cmUnpkNluBndReq(NlUiNluBndReq, pst, mBuf);
               break;
            case EVTNLUNHBRREQ:
               cmUnpkNluNeighborReq(NlUiNluNeighborReq, pst, mBuf);
               break;
            case EVTNLUPCIMODINDCFM:
               cmUnpkNluPciModIndCfm(NlUiNluPciModIndCfm, pst, mBuf);
               break;
            case EVTNLUUEMEASRPTIND :
               cmUnpkNluUeMeasReportInd(NlUiNluUeMeasReportInd, pst, mBuf);
               break;
#ifdef RGR_CQI_REPT
            case EVTNLUUECQIRPTIND :
               cmUnpkNluUeCqiReportInd(NlUiNluUeCqiReportInd, pst, mBuf);
               break;
#endif
            case EVTNLUUEIND :
               cmUnpkNluUeInd(NlUiNluUeInd, pst, mBuf);
               break;
            /* Periodic REM for TPM */
            case EVTNLUPERCELLSRCHRSP:
               cmUnpkNluPerCellSrchRsp(NlUiNluPerdCellSrchRsp, pst, mBuf);
               break;
            /* Periodic REM for TPM End */
            default :
               RLOG0(L_ERROR, "SON received Invalid Event received from eNB-APP  \n");
               NL_FREE_MBUF(mBuf);
               break;
         }
         break;
      }
      case ENTYS :
      {
         switch(pst->event)
         {
            case EVTNLVENDORDSONDATIND :
               nlUnpkVendorDSonDatInd(NlVendorDSonDatInd, pst, mBuf);
               break;
            default :
               RLOG0(L_ERROR, "SON received Invalid Event received from DSON  \n");
               NL_FREE_MBUF(mBuf);
               break;
         }
         break;
      }
      default:
      {
         RLOG0(L_ERROR, " SON received invalid event from unexpected source entity \n");
         NL_FREE_MBUF(mBuf);
         break;
      }
   }
   SExitTsk();
   RETVALUE(ROK);
} /* end of nlActvTsk */

/********************************************************************30**

           End of file:     bk_ex_ms.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 17:51:11 2014

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
*********************************************************************91*/

