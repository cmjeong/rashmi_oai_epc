/********************************************************************20**

     Name:    RRC - acc test file

     Type:    C file

     Desc:    Utility funtions required by CTF XTA 

     File:    nhac_ctfutl.c 

     Sid:      nhac_ctfutl.c@@/main/2 - Fri Jul  1 01:13:01 2011

     Prg:    yk 

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
using namespace NH_LTERRC_REL11;
#include "nhac_nhu.x"

#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"
#include "nhac_acc_ctf.x"

#include "ctf.h"

EXTERN NhAccCb nhAccCb;

#ifdef RRC_PHY_CFG_SUPP

PUBLIC NhAccCtfVal gCtfValStore[25];
EXTERN NhAcCtfCfgInfo gCtfCfgInfo[5];
EXTERN U8 gValIdx;


#ifdef ANSI
PUBLIC S16 nhAcUtlCtfGetValIdxCrnti
(
U8 *idx,
U16 id
)
#else
PUBLIC S16 nhAcUtlCtfGetValIdxCrnti(idx,id)
U8 *idx;
U16 id;
#endif
{
  U8 i=0;
  TRC2(nhAcUtlCtfGetValIdxCrnti);

  for(i=0;i<25;i++)
  {
    if(gCtfValStore[i].used ==TRUE && gCtfValStore[i].tCrnti == id)
    {
       *idx = i;
       RETVALUE(ROK);
    }
  }
  RETVALUE(RFAILED);
}

#ifdef ANSI
PUBLIC S16 nhAcUtlCtfGetValIdxUe
(
U8 *idx,
U16 id
)
#else
PUBLIC S16 nhAcUtlCtfGetValIdxUe(idx,id)
U8 *idx;
U16 id;
#endif
{
  U8 i=0;
  TRC2(nhAcUtlCtfGetValIdxUe);

  for(i=0;i<25;i++)
  {
    if(gCtfValStore[i].used ==TRUE && gCtfValStore[i].ueId == id)
    {
       *idx = i;
       RETVALUE(ROK);
    }
  }
  RETVALUE(RFAILED);
}
/*
*
*       Fun:   nhAcCtfUeValidate
*
*       Desc:  This function is used to validate Ue cfg params
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_ctfutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcCtfUeValidate
(
NhuPhyCfg *nhuCfg,
CtfDedCfgInfo *ctfCfg
)
#else
PUBLIC S16 nhAcCtfUeValidate(nhuCfg, ctfCfg)
NhuPhyCfg *nhuCfg;
CtfDedCfgInfo *ctfCfg;
#endif /* ANSI */
{
   TRC2(nhAcCtfUeValidate);

   if (nhuCfg->bitMask & NHU_DED_PHY_CFG_UE_CAT)
   {
      NHAC_CHK(nhuCfg->ueCategory, ctfCfg->ueCatCfg.ueCategory)
   }

   if (nhuCfg->bitMask & NHU_DED_PHY_CFG_PDSCH)
   {
      NHAC_CHK(nhuCfg->pdschCfg.pa, ctfCfg->pdschCfg.pA)
   }

   if (nhuCfg->bitMask & NHU_DED_PHY_CFG_PUCCH)
   {
      NHAC_CHK(nhuCfg->pucchCfg.cfgTyp, ctfCfg->pucchCfg.dedPucchCfgType)
      NHAC_CHK(nhuCfg->pucchCfg.setup.factor, ctfCfg->pucchCfg.pucchSetup.repFact)
      NHAC_CHK(nhuCfg->pucchCfg.setup.n1PUCCH_AN_Rep , ctfCfg->pucchCfg.pucchSetup.n1PUCCHRep)
   }

   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nhAcCtfUeModValidate
*
*       Desc:  This function is used to validate Ue ReCfg params
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_ctfutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcCtfUeModValidate
(
NhuPhyCfg *nhuCfg,
CtfDedRecfgInfo *ctfCfg
)
#else
PUBLIC S16 nhAcCtfUeModValidate(nhuCfg, ctfCfg)
NhuPhyCfg *nhuCfg;
CtfDedRecfgInfo *ctfCfg;
#endif /* ANSI */
{
   TRC2(nhAcCtfUeModValidate);


   RETVALUE(CMXTA_ERR_NONE);
}
#ifdef RRC_PHY_CFG_SUPP
/*
*
*       Fun:   nhAcCtfCmnValidate
*
*       Desc:  This function is used to validate Cmn cfg params
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_ctfutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcCtfCmnValidate
(
NhuCmnPhyCfg *nhuCfg,
CtfCellCfgInfo *ctfCfg
)
#else
PUBLIC S16 nhAcCtfCmnValidate(nhuCfg, ctfCfg)
NhuCmnPhyCfg *nhuCfg;
CtfCellCfgInfo *ctfCfg;
#endif /* ANSI */
{
   TRC2(nhAcCtfCmnValidate);

   if(ctfCfg->antennaCfg.antPortsCnt != 
              NH_GET_ANT_PORT_CNT(nhuCfg->numOfTxAnt))
   {
       CMXTA_DBG_ERR((_cmxtap, "nhAcCtfCmnValidate():\
                 Validation failed for Antenna Port Count\n"));
       RETVALUE(RFAILED);
   }

    if((ctfCfg->prachCfg.rootSequenceIndex != 
                                        nhuCfg->prachCfg.rootSequenceIndex) ||
       (ctfCfg->prachCfg.prachCfgIndex != nhuCfg->prachCfg.prachCfgIndex)   || 
       (ctfCfg->prachCfg.zeroCorrelationZoneCfg !=                          
                                 nhuCfg->prachCfg.zeroCorrelationZoneCfg)   || 
       (ctfCfg->prachCfg.highSpeedFlag != nhuCfg->prachCfg.highSpeedFlag)   || 
       (ctfCfg->prachCfg.prachFreqOffset != nhuCfg->prachCfg.prachFreqOffset))
    {
        CMXTA_DBG_ERR((_cmxtap, "nhAcCtfCmnValidate():\
                  Validation failed for PRACH Configuration\n"));
        RETVALUE(RFAILED);
    }

   RETVALUE(CMXTA_ERR_NONE);
}
#endif
/*
*
*       Fun:   nhAcCtfCmnModValidate
*
*       Desc:  This function is used to validate Cell Recfg params
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_ctfutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcCtfCmnModValidate
(
NhuCmnPhyRecfg *nhuCfg,
CtfCellRecfgInfo *ctfCfg
)
#else
PUBLIC S16 nhAcCtfCmnModValidate(nhuCfg, ctfCfg)
NhuCmnPhyRecfg *nhuCfg;
CtfCellRecfgInfo *ctfCfg;
#endif /* ANSI */
{
   TRC2(nhAcCtfCmnModValidate);


   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nhAcCtfValidate
*
*       Desc:  This function is used to validate cfg params
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_ctfutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcCtfValidate
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */
CtfCfgReqInfo *cfg
)
#else
PUBLIC S16 nhAcCtfValidate(tcCb, spCb, cfg)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CtfCfgReqInfo *cfg;
#endif /* ANSI */
{
   U16 ueId=0;
   U16 rbIdx=0;
   U8 idx=0;
   U8 tCrntiPres= 0;
   U8 ueIdPres= 0;
   U16 tCrnti;
   U8 cleanup=0;

   /*read ue id and rbid from XTA*/
   TRC2(nhAcCtfValidate);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "tCrntiPres", &(tCrntiPres));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ueIdPres", &(ueIdPres));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "cleanup", &(cleanup));

   if(tCrntiPres)
   {
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "valTCrnti", &(tCrnti));
     if (nhAcUtlCtfGetValIdxCrnti(&idx, tCrnti) == RFAILED)
     {
         CMXTA_DBG_ERR((_cmxtap,"nhAcUtlCtfValidate() tCrnti not found\n"));
         RETVALUE(CMXTA_ERR_INT);
     }
   }
   else if(ueIdPres)
   {
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "valUeId", &(ueId));
     if (nhAcUtlCtfGetValIdxUe(&idx,ueId) == RFAILED)
     {
         CMXTA_DBG_ERR((_cmxtap,"nhAcUtlCtfValidate() ue context not found\n"));
         RETVALUE(CMXTA_ERR_INT);
     }
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "rbIdx", &(rbIdx));

   if(cfg->cfgType == CTF_CONFIG)
   {
       if(cfg->u.cfg.cfgElem == CTF_UE_CFG)
       {
         NHAC_CHK(cfg->u.cfg.u.dedCfg.cellId, gCtfValStore[idx].cellId)
         NHAC_CHK(cfg->u.cfg.u.dedCfg.ueId, gCtfValStore[idx].ueId)

         if (nhAcCtfUeValidate(&(gCtfValStore[gValIdx].u.phyCfg),
                      &(cfg->u.cfg.u.dedCfg)) != 0)
         {
            CMXTA_DBG_ERR((_cmxtap,"nhAcUtlCtfValidate():Validation failed for PHY\n"));
            RETVALUE(RFAILED);
         }
       }
       if(cfg->u.cfg.cfgElem == CTF_CELL_CFG) 
       {
          NHAC_CHK(cfg->u.cfg.u.cellCfg.cellId, gCtfValStore[idx].cellId)

          if((cfg->u.cfg.u.cellCfg.bwCfg.dlBw != NH_GET_SYS_BW(NHU_SYS_BW_N50)) ||
                (cfg->u.cfg.u.cellCfg.bwCfg.ulBw != NH_GET_SYS_BW(NHU_SYS_BW_N75)) )
          {
             CMXTA_DBG_ERR((_cmxtap, "nhAcUtlCtfValidate():\
                      Validation failed for Bandwidth Configuration\n"));
             RETVALUE(RFAILED);
          }
          
#ifdef RRC_PHY_CFG_SUPP
          if (nhAcCtfCmnValidate(&(gCtfValStore[gValIdx].u.cellCfgInfo),
                 &(cfg->u.cfg.u.cellCfg)) != 0)
          {
            CMXTA_DBG_ERR((_cmxtap,"nhAcUtlCtfValidate():Validation failed for PHY\n"));
            RETVALUE(RFAILED);
          }
#endif
       }
   }
   else if(cfg->cfgType == CTF_RECONFIG)
   {
       if(cfg->u.reCfg.cfgElem == CTF_UE_CFG)
       {
         NHAC_CHK(cfg->u.reCfg.u.dedRecfg.cellId,gCtfValStore[idx].cellId)
         NHAC_CHK(cfg->u.reCfg.u.dedRecfg.ueId, gCtfValStore[idx].ueId)

         if (nhAcCtfUeModValidate(&(gCtfValStore[gValIdx].u.phyCfg),
                      &(cfg->u.reCfg.u.dedRecfg)) != 0)
         {
            CMXTA_DBG_ERR((_cmxtap,"nhAcUtlCtfValidate():Validation failed for PHY\n"));
            RETVALUE(RFAILED);
         }
       }
       if(cfg->u.reCfg.cfgElem == CTF_CELL_CFG) 
       {
          NHAC_CHK(cfg->u.reCfg.u.cellRecfg.cellId, gCtfValStore[idx].cellId)

          if (nhAcCtfCmnModValidate(&(gCtfValStore[gValIdx].u.cellRecfgInfo),
                 &(cfg->u.reCfg.u.cellRecfg)) != 0)
          {
            CMXTA_DBG_ERR((_cmxtap,"nhAcUtlCtfValidate():Validation failed for PHY\n"));
            RETVALUE(RFAILED);
          }
       }

   }
   else
   {
       if(cfg->u.release.cfgElem == CTF_UE_CFG)
       {
          NHAC_CHK(cfg->u.release.u.dedRel.cellId,gCtfValStore[idx].cellId)
          NHAC_CHK(cfg->u.release.u.dedRel.ueId,gCtfValStore[idx].ueId)
       }
       if(cfg->u.release.cfgElem == CTF_CELL_CFG) 
       {
          NHAC_CHK(cfg->u.release.u.cellRel.cellId, gCtfValStore[idx].cellId)
       }
   }

   if(cleanup)
   {
      cmMemset((U8*)&gCtfValStore[idx], 0 , sizeof(NhAccCtfVal));
      gCtfValStore[idx].used = FALSE;
   }
   
   RETVALUE(ROK);

} /* End of nhAcCtfValidate() */


/*
*
*       Fun:  nhAcCtfGetUnusedCfgIdx
*
*       Desc:  Returns the index of the first unused CfgInfo
*              structure from the array.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcCtfGetUnusedCfgIdx
(
U8 *idx
)
#else
PUBLIC S16 nhAcCtfGetUnusedCfgIdx(idx)
U8 *idx;
#endif
{
   U8 i;
   for(i=0; i<5; i++)
   {
      if(gCtfCfgInfo[i].used == FALSE)
      {
         *idx = i;
         gCtfCfgInfo[i].used = TRUE;
         RETVALUE(ROK);
      }
   }
   RETVALUE(RFAILED);
}


/*
*       Fun: nhAcCtfGetCfgIndx
*
*       Desc:  Returns the index of the first unused CfgInfo
*              structure from the array.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcCtfGetCfgIndx
(
S16 ueCellid,
U8 *idx,
Bool ueOrCell
)
#else
PUBLIC S16 nhAcCtfGetCfgIndx(ueCellid, idx, ueOrCell)
S16 ueCellid;
U8 *idx;
Bool ueOrCell;
#endif
{
   U8 i;
   Bool found = FALSE;

   if(ueOrCell == 0)
   {
      for(i=0;i<5;i++)
      {
         if(gCtfCfgInfo[i].ueId == ueCellid)
         {
            found = TRUE;
            *idx = i;
             RETVALUE(ROK);
         }
      }
   }
   else
   {
      for(i=0;i<5;i++)
      {
         if(gCtfCfgInfo[i].cellId == ueCellid)
         {
            found = TRUE;
            *idx = i;
             RETVALUE(ROK);
         }
      }
   }
   if(found == FALSE)
   {
     /*context for this does not exist create one*/
     if(nhAcCtfGetUnusedCfgIdx(idx) == ROK)
        RETVALUE(ROK);
     else
        RETVALUE(RFAILED);
   }
   RETVALUE(RFAILED);
}



/*
 *
 *       Fun:    nhAcCtfTstCbFind -
 *
 *       Desc:   Find the test Case Control Block 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   nhac_ctfutl.c
 *
 */

#ifdef ANSI
PUBLIC CmXtaTCCb*  nhAcCtfTstCbFind
(
)
#else
PUBLIC CmXtaTCCb*  nhAcCtfTstCbFind ()
#endif
{
   TRC2(nhAcCtfTstCbFind)

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
}

/*
*
*       Fun:   nhAcUtlCtfCb
*
*       Desc:  This function is used to free the Queue Element
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_ctfutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlCtfCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 nhAcUtlCtfCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   NhAccMsgQElm  *rrcMsg = NULLP;

   TRC2(nhAcUtlCtfCb)

   CMXTA_DBG_PARAM((_cmxtap, "nhAcUtlCtfCb(): \n"));

   rrcMsg = (NhAccMsgQElm *)qElm->data;
   /* Free mem allocated in XTA cb functions */
   CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlCtfCb() */

#endif /* RRC_PHY_CFG_SUPP */


/**********************************************************************
         End of file:     nhac_ctfutl.c@@/main/2 - Fri Jul  1 01:13:01 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     yk               1. LTE RRC Initial Release.
/main/2      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
