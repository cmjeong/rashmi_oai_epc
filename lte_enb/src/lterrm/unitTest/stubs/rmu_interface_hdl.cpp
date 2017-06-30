

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     rmu_interface_hdl.cpp 


     Prg:      

*********************************************************************21*/

/* header include files (.h) */


/************************************************************************
                       Upper Interface Functions
************************************************************************/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_lte.h"        /* common LTE structures */
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "lnh.h"
#include "cm_pasn.h"
#include "rm.h"
#include "rmu.h"
#include "lrm.h"
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
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#include "nhu.x"           /* RRC Upper Interface */
#include "nhu_asn.x"
#include "lnh.x"
#include "cm_pasn.x"
#include "lrm.x"
#include "rmu.x"
#include "rmu.h"
#include "rgm.x"

#include "gtest/gtest.h"
#include "test_rm.h"

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
PUBLIC S16 WrLiRmuUeRecfgInd
(
Pst *pst,
SuId suId,
RmuUeRecfgInd         *rrmWrUeRecfgInd
)
#else
PUBLIC S16 WrLiRmuUeRelInd(pst,suId,rrmWrUeRecfgInd)
Pst *pst;
SuId suId;
RmuUeRecfgInd         *rrmWrUeRecfgInd;
#endif
{
   UNUSED(pst);
   UNUSED(suId);

   SPutSBuf(0, 0, (Data*)rrmWrUeRecfgInd, sizeof(RmuUeRecfgInd));

   RETVALUE(ROK);

}


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
   UNUSED(pst);
   UNUSED(suId);

   SPutSBuf(0, 0, (Data*)ueRelinfo, sizeof(RmuUeRelInd));

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

   isUeErabRelIndRcvd = TRUE;

   EXPECT_EQ(isUeErabRelIndRcvd, isUeErabRelIndExpected);

   SPutSBuf(0, 0, (Data*)relIndinfo, sizeof(RmuUeERabRelInd));

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
   UNUSED(pst);
   UNUSED(suId);

   // first check if cell reconfiguration is received when expected
   EXPECT_EQ(true, isCellRecfgIndExpected);
   if(isCellRecfgIndExpected)
   {
      if(cellRcfginfo->enCellRecfgType == RMU_CELL_RECFG_ACB_IND)
      {
         RmuAcbParamInd *acbParams = &cellRcfginfo->stAcbParamInd;
         EXPECT_EQ(acbParams->stAcbInfo.bAcBarringEmergency, 
               cellRecfgIndExp.u.acbExpInfo.emergency);

         EXPECT_EQ(acbParams->stAcbInfo.bIsacBarringMoSig, 
               cellRecfgIndExp.u.acbExpInfo.moSig.isEnable);
         if(acbParams->stAcbInfo.bIsacBarringMoSig)
         {
            CmRrmAcb *moSigInfo = &acbParams->stAcbInfo.stAcBarringMoSig;
            AcbInfo *moSigExpInfo = &cellRecfgIndExp.u.acbExpInfo.moSig;
            EXPECT_EQ(moSigInfo->enAcbFactor, moSigExpInfo->factor);
            EXPECT_EQ(moSigInfo->enAcbTime, moSigExpInfo->time);
            EXPECT_EQ(moSigInfo->bAcbForSpac, moSigExpInfo->spAc);
         }

         EXPECT_EQ(acbParams->stAcbInfo.bIsacBarringMoData, 
               cellRecfgIndExp.u.acbExpInfo.moData.isEnable);
         if(acbParams->stAcbInfo.bIsacBarringMoData)
         {
            CmRrmAcb *moDataInfo = &acbParams->stAcbInfo.stAcBarringMoData;
            AcbInfo *moDataExpInfo = &cellRecfgIndExp.u.acbExpInfo.moData;
            EXPECT_EQ(moDataInfo->enAcbFactor, moDataExpInfo->factor);
            EXPECT_EQ(moDataInfo->enAcbTime, moDataExpInfo->time);
            EXPECT_EQ(moDataInfo->bAcbForSpac, moDataExpInfo->spAc);
         }
      }
   }

   SPutSBuf(0, 0, (Data*)cellRcfginfo, sizeof(RmuCellRecfgInd));
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
   UNUSED(pst);
   UNUSED(suId);

   if(isUeAdmitRspExpInfoSet)
   {
      EXPECT_EQ(admitRspinfo->stStatusInfo.enStatus,
            ueAdmitRspExp.stStatusInfo.enStatus);
   }

   SPutSBuf(0, 0, (Data*)admitRspinfo, sizeof(RmuUeAdmitRsp));

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
   UNUSED(pst);
   UNUSED(suId);

   SPutSBuf(0, 0, (Data*)relrspinfo, sizeof(RmuUeRelRsp));

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
SuId			     suId;
RmuUeRecfgRsp    *recfgRspinfo;
#endif
{
   TRC2(WrLiRmuUeRecfgRsp);
   UNUSED(pst);
   UNUSED(suId);

   if(isUeRecfgExpInfoSet)
   {
      EXPECT_EQ(recfgRspinfo->stStatusInfo.enStatus,
            ueRecfgExp.stStatusInfo.enStatus);
      EXPECT_EQ(recfgRspinfo->usCrnti, ueRecfgExp.usCrnti);
      EXPECT_EQ(recfgRspinfo->bRecfgBitMap, ueRecfgExp.bRecfgBitMap);
      EXPECT_EQ(recfgRspinfo->bNoErabsAccepted, ueRecfgExp.bNoErabsAccepted);
      EXPECT_EQ(recfgRspinfo->bNoErabsRejected, ueRecfgExp.bNoErabsRejected);
      EXPECT_EQ(isUeErabRelIndRcvd, isUeErabRelIndExpected);
   }

   SPutSBuf(0, 0, (Data*)recfgRspinfo, sizeof(RmuUeRecfgRsp));

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
   UNUSED(pst);
   UNUSED(suId);

   if(isUeRecfgExpInfoSet)
   {
      EXPECT_EQ(hoRspinfo->stStatusInfo.enStatus,
            ueHoAdmitRspExp.stStatusInfo.enStatus);
      EXPECT_EQ(hoRspinfo->usCrnti, ueHoAdmitRspExp.usCrnti);
      EXPECT_EQ(hoRspinfo->bNoErabsAdmitted, ueHoAdmitRspExp.bNoErabsAdmitted);
      EXPECT_EQ(isUeErabRelIndRcvd, isUeErabRelIndExpected);
   }

   SPutSBuf(0, 0, (Data*)hoRspinfo, sizeof(RmuUeHoRsp));

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
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(status);

   RETVALUE(ROK);
}

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 rdConQ
(
Data data
)
#else
PUBLIC S16 rdConQ(data)
Data data;
#endif
{
   TRC2(rdConQ)
   UNUSED(data);

   RETVALUE(RFAILED);
}/* rdConQ */


/*********************** RGM Interface Functions  *****************************/
#ifdef ANSI
PUBLIC S16 RgUiRgmBndReq
(
Pst   *pst, 
SuId  suId,
SpId  spId
)
#else
PUBLIC S16 RgUiRgmBndReq(pst, suId, spId)
Pst   *pst; 
SuId  suId;
SpId  spId;
#endif
{
   TRC3(RgUiRgmBndReq)
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(spId);
   
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 RgUiRgmUbndReq
(
Pst    *pst,
SpId   spId,
Reason reason
)
#else
PUBLIC S16 RgUiRgmUbndReq(pst, spId, reason)
Pst    *pst; 
SpId   spId;
Reason reason;
#endif
{
   TRC3(RgUiRgmUbndReq);
   UNUSED(pst);
   UNUSED(spId);
   UNUSED(reason);

   RETVALUE(ROK);
}  /* RgUiRgmUbndReq */

#ifdef ANSI
PUBLIC S16 RgUiRgmCfgPrbRprt
(
Pst   *pst, 
SpId  spId,
RgmPrbRprtCfg   *prbRprtCfg
)
#else
PUBLIC S16 RgUiRgmCfgPrbRprt(pst, spId, prbRprtCfg)
Pst   *pst; 
SpId  spId;
RgmPrbRprtCfg   *prbRprtCfg;
#endif
{
   TRC2(RgUiRgmCfgPrbRprt);
   UNUSED(pst);
   UNUSED(spId);

   if(isStartPrbReportCfg)
   {
      EXPECT_EQ(prbRprtCfg->bConfigType, RGM_PRB_REPORT_START);
   }
   else if(isStopPrbReportCfg)
   {
      EXPECT_EQ(prbRprtCfg->bConfigType, RGM_PRB_REPORT_STOP);
   }
   else
   {
      EXPECT_EQ(prbRprtCfg->bConfigType, 2); // expected PRB report type not set
   }

   SPutSBuf(0, 0, (Data*)prbRprtCfg, sizeof(RgmPrbRprtCfg));

   RETVALUE(ROK);
}


