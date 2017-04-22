

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     wrac_rmucb.c 

     Sid:      rmac_rmucb.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:29 2013

     Prg:      sck

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
#include "cm_xta.h"
//#include "wrac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
#include "rm.h"
#include "rmu.h"
#include "lrm.h"
//#include "wrac_acc.h"
//#include "wrac_rmu.h"
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
#include "nhu.x"           /* RRC Upper Interface */
#include "nhu_asn.x"
#include "lnh.x"
#include "cm_pasn.x"
#include "nh.x"
#include "lrm.x"
#include "rmu.x"
#include "rmu.h"
#include "rmac_acc.x"
#include "rmac_rmu.x"

/* Following functions are implemented

DmRmuUeAdmitRsp
DmRmuUeHoRsp
DmRmuUeRelRsp
DmRmuUeRecfgRsp

*/

#define WR_MAX_UIRMU_SEL   5

/************************************************************************
                              Prototypes
************************************************************************/

PUBLIC RmuFsmStatusIndFPtr wrLiRmuFsmStatusIndMt[WR_MAX_UIRMU_SEL] =
{
   cmPkRmuFsmStatusInd,      /* 0 - loosely coupled */
#ifdef RMU_LWLC
   cmPkLwLcRmuFsmStatusInd,  /* 1 - LWLC */
#endif /*RMU_LWLC*/
#ifdef RMU_NPLC
   cmNoPkRmuFsmStatusInd,    /* 2 - No packing loosely coupled*/
#endif /*RMU_NPLC*/
#ifdef RM_INTF
#ifdef RMU_ACC
   DmUiRmuFsmStatusInd,      /* 3 - For ACC Test*/
#else 
#ifdef RMU_TC
   RmUiRmuFsmStatusInd       /* 3 - tightly coupled */
#endif
#endif      
#endif /*RMU_INTF */
};

PUBLIC RmuMmeOvldStartIndFPtr wrLiRmuMmeOverloadStartIndMt[WR_MAX_UIRMU_SEL] =
{
   cmPkRmuMmeOverloadStartInd,      /* 0 - loosely coupled */
#ifdef RMU_LWLC
   cmPkLwLcRmuMmeOverloadStartInd,  /* 1 - LWLC */
#endif /*RMU_LWLC*/
#ifdef RMU_NPLC
   cmNoPkRmuMmeOverloadStartInd,    /* 2 - No packing loosely coupled*/
#endif /*RMU_NPLC*/
#ifdef RM_INTF
#ifdef RMU_ACC
   DmUiRmuMmeOverloadStartInd,      /* 3 - For ACC Test*/
#else 
#ifdef RMU_TC
   RmUiRmuMmeOverloadStartInd       /* 3 - tightly coupled */
#endif
#endif      
#endif /*RMU_INTF */
};


PUBLIC RmuMmeOvldStopIndFPtr wrLiRmuMmeOverloadStopIndMt[WR_MAX_UIRMU_SEL] =
{
   cmPkRmuMmeOverloadStopInd,      /* 0 - loosely coupled */
#ifdef RMU_LWLC             
   cmPkLwLcRmuMmeOverloadStopInd,  /* 1 - LWLC */
#endif /*RMU_LWLC*/
#ifdef RMU_NPLC
   cmNoPkRmuMmeOverloadStopInd,    /* 2 - No packing loosely coupled (NPLC)*/
#endif /*RMU_NPLC*/
#ifdef RM_INTF
#ifdef RMU_ACC
   DmUiRmuMmeOverloadStopInd,     /* 3 - For ACC Test*/
#else
#ifdef RMU_TC
   RmUiRmuMmeOverloadStopInd       /*3 - tightly coupled */
#endif      
#endif      
#endif /*RMU_INTF */
};


PUBLIC RmuUeAdmitReqFPtr wrLiRmuUeAdmitReqMt[WR_MAX_UIRMU_SEL] =
{
   cmPkRmuUeAdmitReq,        /* 0 - loosely coupled */
#ifdef RMU_LWLC
   cmPkLwLcRmuUeAdmitReq,    /* 1 - LWLC */
#endif /*RMU_LWLC*/
#ifdef RMU_NPLC
   cmNoPkRmuUeAdmitReq,      /* 2 - NPLC */
#endif /*RMU_NPLC*/
#ifdef RM_INTF
#ifdef RMU_ACC
   DmUiRmuUeAdmitReq,       /* 3 - For ACC Test*/
#else
#ifdef RMU_TC
   RmUiRmuUeAdmitReq         /* 3 - tightly coupled */
#endif      
#endif      
#endif /*RMU_INTF */
};


PUBLIC RmuUeHoReqFPtr wrLiRmuUeHoReqMt[WR_MAX_UIRMU_SEL] =
{
   cmPkRmuUeHoReq,           /* 0 - loosely coupled */
#ifdef RMU_LWLC
   cmPkLwLcRmuUeHoReq,       /* 1 - LWLC */
#endif /*RMU_LWLC*/
#ifdef RMU_NPLC
   cmNoPkRmuUeHoReq,         /* 2 - NPLC */
#endif /*RMU_NPLC*/
#ifdef RM_INTF
#ifdef RMU_ACC
   DmUiRmuUeHoReq,           /* 3 - For ACC Test*/
#else
#ifdef RMU_TC
   RmUiRmuUeHoReq            /* 3 - tightly coupled */
#endif      
#endif      
#endif /*RMU_INTF */
};


PUBLIC RmuUeRelReqFPtr wrLiRmuUeRelReqMt[WR_MAX_UIRMU_SEL] =
{
   cmPkRmuUeRelReq,          /* 0 - loosely coupled */
#ifdef RMU_LWLC
   cmPkLwLcRmuUeRelReq,      /* 1 - LWLC */
#endif /*RMU_LWLC*/
#ifdef RMU_NPLC
   cmNoPkRmuUeRelReq,        /* 2 - NPLC */
#endif /*RMU_NPLC*/
#ifdef RM_INTF
#ifdef RMU_ACC
   DmUiRmuUeRelReq,          /* 3 - For ACC Test*/
#else
#ifdef RMU_TC
   RmUiRmuUeRelReq           /* 3 - tightly coupled */
#endif      
#endif      
#endif /*RMU_INTF */
};


PUBLIC RmuUeRecfgReqFPtr wrLiRmuUeRecfgReqMt[WR_MAX_UIRMU_SEL] =
{
   cmPkRmuUeRecfgReq,        /* 0 - loosely coupled */
#ifdef RMU_LWLC
   cmPkLwLcRmuUeRecfgReq,    /* 1 - LWLC */
#endif /*RMU_LWLC*/
#ifdef RMU_NPLC
   cmNoPkRmuUeRecfgReq,      /* 2 - NPLC */
#endif /*RMU_NPLC*/
#ifdef RM_INTF
#ifdef RMU_ACC
   DmUiRmuUeRecfgReq,        /* 3 - For ACC Test*/
#else
#ifdef RMU_TC
   RmUiRmuUeRecfgReq         /* 3 - tightly coupled */
#endif      
#endif      
#endif /*RMU_INTF */
};

/* SPS changes starts */
PUBLIC RmuUeSpsDisIndFPtr wrLiRmuUeSpsDisIndMt[WR_MAX_UIRMU_SEL] =
{
   cmPkRmuUeSpsDisInd,        /* 0 - loosely coupled */
#ifdef RMU_LWLC
   cmPkLwLcRmuUeSpsDisInd,    /* 1 - LWLC */
#endif /*RMU_LWLC*/
#ifdef RMU_NPLC
   cmNoPkRmuUeSpsDisInd,      /* 2 - NPLC */
#endif /*RMU_NPLC*/
#ifdef RM_INTF
#ifdef RMU_ACC
   DmUiRmuUeSpsDisInd,        /* 3 - For ACC Test*/
#else
#ifdef RMU_TC
   RmUiRmuUeSpsDisInd         /* 3 - tightly coupled */
#endif      
#endif      
#endif /*RMU_INTF */
};
/* SPS changes ends */

PUBLIC RmuBndReqFPtr wrLiRmuBndReqMt[WR_MAX_UIRMU_SEL] =
{
   cmPkRmuBndReq,        /* 0 - loosely coupled */
#ifdef RMU_LWLC
   cmPkLwLcRmuBndReq,    /* 1 - LWLC */
#endif /*RMU_LWLC*/
#ifdef RMU_NPLC
   cmNoPkRmuBndReq,      /* 2 - NPLC */
#endif /*RMU_NPLC*/
#ifdef RM_INTF
#ifdef RMU_ACC
   DmUiRmuBndReq,        /* 3 - For ACC Test*/
#else
#ifdef RMU_TC
   RmUiRmuBndReq         /* 3 - tightly coupled */
#endif      
#endif      
#endif /*RMU_INTF */
};



/************************************************************************
                       Upper Interface Functions
************************************************************************/

/*
 *
 *       Fun:   WrLiWrtFsmStatusInd
 *
 *       Desc:  This function resolves the WR_RM _MME_OVERLOAD_START_IND  primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  wr_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 WrLiRmuFsmStatusInd
(
Pst *pst,
SuId suId,
RmuFsmStatusInd *statusInd
)
#else
PUBLIC S16 WrLiRmuFsmStatusInd (pst, suId, statusInd)
Pst *pst;
SuId suId;
RmuFsmStatusInd *statusInd;
#endif
{
   TRC3(WrLiRmuFsmStatusInd)

   (*wrLiRmuFsmStatusIndMt[pst->selector])
      (pst, suId, statusInd);

   RETVALUE(ROK);
} /* WrLiRmuFsmStatusInd */


/*
 *
 *       Fun:   WrLiWrtMmeOverloadStartInd
 *
 *       Desc:  This function resolves the WR_RM _MME_OVERLOAD_START_IND  primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  wr_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 WrLiRmuMmeOvldStartInd
(
Pst *pst,
SuId suId,
RmuMmeOvldStartInd *startInfo
)
#else
PUBLIC S16 WrLiRmuMmeOvldStartInd (pst, suId, startInfo)
Pst *pst;
SuId suId;
RmuMmeOvldStartInd *startInfo;
#endif
{
   TRC3(WrLiRmuMmeOvldStartInd)

   (*wrLiRmuMmeOverloadStartIndMt[pst->selector])
      (pst, suId, startInfo);

   RETVALUE(ROK);
} /* WrLiRmuMmeOverloadStartInd */


/*
 *
 *       Fun:   WrLiWrtMmeOverloadStopInd
 *
 *       Desc:  This function resolves the WR_RM_MME_OVERLOAD_STOP_IND primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  wr_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 WrLiRmuMmeOvldStopInd
(
Pst *pst,
SuId suId,
RmuMmeOvldStopInd *stopinfo
)
#else
PUBLIC S16 WrLiRmuMmeOvldStopInd (pst, suId, stopinfo)
Pst *pst;
SuId suId;
RmuMmeOvldStopInd *stopinfo;
#endif
{
   TRC3(WrLiRmuMmeOverloadStopInd)

   (*wrLiRmuMmeOverloadStopIndMt[pst->selector])
      (pst, suId, stopinfo);

   RETVALUE(ROK);
} /* WrLiRmuMmeOverloadStopInd */

/*
 *
 *       Fun:   WrLiRmuUeAdmitReq
 *
 *       Desc:  This function resolves the WR_RM_UE_ADMIT_REQ primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  wr_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 WrLiRmuUeAdmitReq
(
Pst *pst,
SuId suId,
RmuUeAdmitReq *admitinfo
)
#else
PUBLIC S16 WrLiRmuUeAdmitReq (pst, suId, admitinfo)
Pst *pst;
SuId suId;
RmuUeAdmitReq *admitinfo;
#endif
{
   TRC3(WrLiRmuUeAdmitReq)

   (*wrLiRmuUeAdmitReqMt[pst->selector])
      (pst, suId, admitinfo);

   RETVALUE(ROK);
} /* WrLiRmuUeAdmitReq */

/*
 *
 *       Fun:   WrLiRmuUeHoReq
 *
 *       Desc:  This function resolves the WR_RM_UE_HO_REQ  primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  wr_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 WrLiRmuUeHoReq
(
Pst *pst,
SuId suId,
RmuUeHoReq *hoinfo
)
#else
PUBLIC S16 WrLiRmuUeHoReq (pst, suId, hoinfo)
Pst *pst;
SuId suId;
RmuUeHoReq *hoinfo;
#endif
{
   TRC3(WrLiRmuUeHoReq)

   (*wrLiRmuUeHoReqMt[pst->selector])
      (pst, suId, hoinfo);

   RETVALUE(ROK);
} /* WrLiRmuUeHoReq */

/*
 *
 *       Fun:   WrLiRmuUeRelReq
 *
 *       Desc:  This function resolves the WR_RM_UE_REL_REQ primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  wr_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 WrLiRmuUeRelReq
(
Pst *pst,
SuId suId,
RmuUeRelReq *relinfo
)
#else
PUBLIC S16 WrLiRmuUeRelReq (pst, suId, relinfo)
Pst *pst;
SuId suId;
RmuUeRelReq *relinfo;
#endif
{
   TRC3(WrLiRmuUeRelReq)

   (*wrLiRmuUeRelReqMt[pst->selector])
      (pst, suId, relinfo);

   RETVALUE(ROK);
} /* WrLiWrtUeRelReq */

/*
 *
 *       Fun:   WrLiRmuUeRecfgReq
 *
 *       Desc:  This function resolves the WR_RM_UE_RECONFIG_REQ primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  wr_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 WrLiRmuUeRecfgReq
(
Pst *pst,
SuId suId,
RmuUeRecfgReq *reconfiginfo
)
#else
PUBLIC S16 WrLiRmuUeRecfgReq (pst, suId, reconfiginfo)
Pst *pst;
SuId suId;
RmuUeRecfgReq *reconfiginfo;
#endif
{
   TRC3(WrLiRmuUeRecfgReq)

   (*wrLiRmuUeRecfgReqMt[pst->selector])
      (pst, suId, reconfiginfo);

   RETVALUE(ROK);
} /* WrLiRmuUeRecfgReq */

/* SPS changes starts */
/*
 *
 *       Fun:   WrLiRmuUeSpsDisInd
 *
 *       Desc:  This function resolves the WR_RM_UE_SPS_DISABLE_IND primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  wr_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 WrLiRmuUeSpsDisInd
(
Pst *pst,
SuId suId,
RmuUeSpsDisInd *ueSpsDisInd
)
#else
PUBLIC S16 WrLiRmuUeSpsDisInd (pst, suId, reconfiginfo)
Pst *pst;
SuId suId;
RmuUeSpsDisInd *ueSpsDisInd;
#endif
{
   TRC3(WrLiRmuUeSpsDisInd)

   (*wrLiRmuUeSpsDisIndMt[pst->selector])
      (pst, suId, ueSpsDisInd);

   RETVALUE(ROK);
} /* WrLiRmuUeSpsDisInd */
/* SPS changes ends */
/*
 *
 *       Fun:   WrLiRmuBndReq
 *
 *       Desc:  This function resolves the BNDREQ primitive
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  wr_ptui.c
 *
 */
#ifdef ANSI
PUBLIC S16 WrLiRmuBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 WrLiRmuBndReq (pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
   TRC3(WrLiRmuBndReq)

   (*wrLiRmuBndReqMt[pst->selector])
      (pst, suId, spId);

   RETVALUE(ROK);
} /* WrLiRmuUeRecfgReq */




/*
*
*       Fun:   rmAcRmuTstCbFind
*
*       Desc:  Call handler for finding the Test Case Control Block
*
*       Ret:   Test Case Control Block
*
*       Notes: None
*              
*       File:  rmac_rmucb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  rmAcRmuTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  rmAcRmuTstCbFind ()
#endif
{
   TRC2(rmAcRmuTstCbFind);

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
} /* rmAcRmuTstCbFind */



/*
*
*       Fun:   rmAcRmuSaveMsg
*
*       Desc:  Function to push the message on queue 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  rmac_rmucb.c
*
*/

#ifdef ANSI
PRIVATE S16 rmAcRmuSaveMsg
(
Pst  *pst,
SuId suId,
SpId spId,
void *rmuInfo
)
#else
PRIVATE S16 rmAcRmuSaveMsg(pst, spId, rmuInfo)
Pst  *pst;
SuId suId;
SpId spId;
void *rmuInfo;
#endif 
{
   CmXtaTCCb    *tcCb = NULLP;
   RmAccMsgQElm *rmuMsg = NULLP; 
   CmXtaMsgQElm   qElm;
   S16            ret;
   Mem            mem;

   TRC3(rmAcRmuSaveMsg);

   cmMemset( (U8* )&qElm, 0, sizeof(CmXtaMsgQElm));

   CMXTA_DBG_PARAM((_cmxtap, "rmAcRmuSaveMsg(): suId (%d))", suId));

   /*-- Allocate memory data --*/
   CMXTA_ALLOC(&rmuMsg, sizeof (RmAccMsgQElm));
   if (rmuMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rmAcRmuSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rmuMsg->u.rmuInfo.suId = suId;
   rmuMsg->u.rmuInfo.data = rmuInfo;

   switch (pst->event)
   {
      case EVTRMUUEADMITRSP:
			rmuMsg->u.rmuInfo.len = sizeof(RmuUeAdmitRsp);
         break;

      case EVTRMUUEHORSP:
			rmuMsg->u.rmuInfo.len = sizeof(RmuUeHoRsp);
         break;

      case EVTRMUUERELRSP:
			rmuMsg->u.rmuInfo.len = sizeof(RmuUeRelRsp);
         break;

      case EVTRMUUERECFGRSP:
			rmuMsg->u.rmuInfo.len = sizeof(RmuUeRecfgRsp);
         break;
      
      case EVTRMUCELLRECFGIND:
         rmuMsg->u.rmuInfo.len = sizeof(RmuCellRecfgInd);
         break;

      case EVTRMUUERELIND:
         rmuMsg->u.rmuInfo.len = sizeof(RmuUeRelInd);
         break;
      case EVTRMUBNDCFM:
         rmuMsg->u.rmuInfo.data = NULLP;
         rmuMsg->u.rmuInfo.status = *(U8*)rmuInfo;
         rmuMsg->u.rmuInfo.len = 0;
         break;


	  default:
         CMXTA_DBG_INFO((_cmxtap, "rmAcRmuSaveMsg(): Unhandled event\n"));
         RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Usual mode --*/
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Fill the message in the queue structure --*/
   CMXTA_CPY((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   if ((tcCb = (CmXtaTCCb*)rmAcRmuTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "rmAcRmuSaveMsg(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   qElm.data = (Void *)rmuMsg;
   qElm.msgFreeFun = rmAcUtlRmuFreeCb;
   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ,(CmXtaMsgQElm *) &qElm);

   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of rmAcRmuSaveMsg() */


/*
*
*       Fun:   WrLiRmuUeRelInd - RMU Cell Reconfig Ind
*
*       Desc:  This function is used to present RMU cell Reconfig Ind.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_rmucb.c
*
*/

#ifdef ANSI
PUBLIC S16 WrLiRmuUeRelInd
(
Pst             *pst,          
SuId			    suId,
RmuUeRelInd     *ueRelinfo
)
#else
PUBLIC S16 WrLiRmuUeRelInd(pst,suId,ueRelinfo)
Pst              *pst;          /* post structure */
SuId			 suId;
RmuUeRelInd     *ueRelinfo;
#endif
{
   TRC2(WrLiRmuUeRelInd);

   CMXTA_DBG_PARAM((_cmxtap, "WrLiRmuUeRelInd():\n"));

   /*-- Update Event --*/
   pst->event = EVTRMUUERELIND;

   rmAcRmuSaveMsg(pst, suId, 0, (Void*)ueRelinfo);

   /* MEM LEAK FIX */
   if(pst->selector == RMU_SEL_LWLC)
	{
		//free the memory of response
		SPutSBuf(pst->region, pst->pool, (Data *)ueRelinfo, sizeof(RmuUeRelInd));
	}

   RETVALUE(ROK);

}

PUBLIC S16 WrLiRmuUeERabRelInd 
(
Pst *pst,
SuId suId,
RmuUeERabRelInd *relIndinfo
)
{
   S16 ret = RFAILED;

   TRC3(WrLiRmuUeERabRelInd);
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(relIndinfo);


   RETVALUE(ret);
   
}/* WrLiRmuUeERabRelInd*/

/*
*
*       Fun:   DmUiRmuUeAdmitRsp - RMU Cell Reconfig Ind
*
*       Desc:  This function is used to present RMU cell Reconfig Ind.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_rmucb.c
*
*/

#ifdef ANSI
PUBLIC S16 WrLiRmuCellRecfgInd
(
Pst             *pst,          
SuId			    suId,
RmuCellRecfgInd *cellRcfginfo
)
#else
PUBLIC S16 WrLiRmuCellRecfgInd(pst,suId,cellRcfginfo)
Pst              *pst;          /* post structure */
SuId			 suId;
RmuCellRecfgInd *cellRcfginfo;
#endif
{
   TRC2(WrLiRmuCellRecfgInd);

   CMXTA_DBG_PARAM((_cmxtap, "WrLiRmuCellRecfgInd():\n"));

   /*-- Update Event --*/
   pst->event = EVTRMUCELLRECFGIND;

   rmAcRmuSaveMsg(pst, suId, 0, (Void*)cellRcfginfo);
   RETVALUE(ROK);

}


/*
*
*       Fun:   DmUiRmuUeAdmitRsp - RMU Ue Admit rsp 
*
*       Desc:  This function is used to present RMU Ue Admit rsp.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_rmucb.c
*
*/

#ifdef ANSI
PUBLIC S16 WrLiRmuUeAdmitRsp
(
Pst             *pst,          
SuId			suId,
RmuUeAdmitRsp *admitRspinfo
)
#else
PUBLIC S16 WrLiRmuUeAdmitRsp(pst,suId,admitRspinfo)
Pst              *pst;          /* post structure */
SuId			 suId;
RmuUeAdmitRsp    *admitRspinfo;
#endif
{
   TRC2(WrLiRmuUeAdmitRsp);

   CMXTA_DBG_PARAM((_cmxtap, "WrLiRmuUeAdmitRsp():\n"));

   /*-- Update Event --*/
   pst->event = EVTRMUUEADMITRSP;

   rmAcRmuSaveMsg(pst, suId, 0, (Void*)admitRspinfo);
   RETVALUE(ROK);

}

/*
*
*       Fun:   DmRmuUeRelRsp - RMU Ue Release rsp 
*
*       Desc:  This function is used to present RMU Ue Release rsp.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_rmucb.c
*
*/

#ifdef ANSI
PUBLIC S16 WrLiRmuUeRelRsp
(
Pst             *pst,          
SuId			suId,
RmuUeRelRsp		*relrspinfo
)
#else
PUBLIC S16 WrLiRmuUeRelRsp(pst,suId,relrspinfo)
Pst              *pst;          /* post structure */
SuId			 suId;
RmuUeRelRsp		 *relrspinfo;
#endif
{
   TRC2(WrLiRmuUeRelRsp);

   CMXTA_DBG_PARAM((_cmxtap, "WrLiRmuUeRelRsp():\n"));

   /*-- Update Event --*/
   pst->event = EVTRMUUERELRSP;

   rmAcRmuSaveMsg(pst, suId, 0, (Void*)relrspinfo);
   RETVALUE(ROK);
}

/*
*
*       Fun:   DmRmuUeRecfgRsp - RMU Ue Recfg rsp 
*
*       Desc:  This function is used to present RMU Ue Recfg rsp.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_rmucb.c
*
*/

#ifdef ANSI
PUBLIC S16 WrLiRmuUeRecfgRsp
(
Pst             *pst,          
SuId			suId,
RmuUeRecfgRsp   *recfgRspinfo
)
#else
PUBLIC S16 WrLiRmuUeRecfgRsp(pst,suId,recfgRspinfo)
Pst              *pst;          /* post structure */
SuId			 suId;
RmuUeRecfgRsp    *recfgRspinfo;
#endif
{
   TRC2(WrLiRmuUeRecfgRsp);

   CMXTA_DBG_PARAM((_cmxtap, "WrLiRmuUeRecfgRsp():\n"));

   /*-- Update Event --*/
   pst->event = EVTRMUUERECFGRSP;

   rmAcRmuSaveMsg(pst, suId, 0, (Void*)recfgRspinfo);
   RETVALUE(ROK);
}

/*
*
*       Fun:   DmRmuUeHoRsp - RMU Ue HO rsp 
*
*       Desc:  This function is used to present RMU Ue HO rsp.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  rmac_rmucb.c
*
*/

#ifdef ANSI
PUBLIC S16 WrLiRmuUeHoRsp
(
Pst             *pst,          
SuId			suId,
RmuUeHoRsp		*hoRspinfo
)
#else
PUBLIC S16 WrLiRmuUeHoRsp(pst,suId,hoRspinfo)
Pst             *pst;          /* post structure */
SuId			suId;
RmuUeHoRsp		*hoRspinfo;
#endif
{
   TRC2(WrLiRmuUeHoRsp);

   CMXTA_DBG_PARAM((_cmxtap, "WrLiRmuUeHoRsp():\n"));

   /*-- Update Event --*/
   pst->event = EVTRMUUEHORSP;

   rmAcRmuSaveMsg(pst, suId, 0, (Void*)hoRspinfo);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 WrLiRmuBndCfm
(
Pst             *pst,
SuId            suId,
U8              status
)
#else
PUBLIC S16 WrLiRmuBndCfm(pst,suId,status)
Pst             *pst;          /* post structure */
SuId            suId;
U8              status;
#endif
{
   TRC2(WrLiRmuBndCfm);

   CMXTA_DBG_PARAM((_cmxtap, "WrLiRmuBndCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTRMUBNDCFM;

   rmAcRmuSaveMsg(pst, suId, 0, (Void*)&status);
   RETVALUE(ROK);
}


PUBLIC S16 WrLiRmuUeRecfgInd
(
Pst *pst,
SuId suId,
RmuUeRecfgInd         *rrmWrUeRecfgInd
)
{
   S16 ret = RFAILED;

   TRC3 (WrLiRmuUeRecfgInd);

//   ret = wrUmmProcRmUeRecfgInd (rrmWrUeRecfgInd);


   RETVALUE(ret);
} /* WrLiRmuUeReCfgInd */
