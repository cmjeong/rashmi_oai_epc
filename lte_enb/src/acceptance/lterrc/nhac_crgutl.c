/********************************************************************20**

     Name:    RRC - acc test file

     Type:    C file

     Desc:    Utility funtions required by CRG XTA 

     File:    nhac_crgutl.c 

     Sid:      nhac_crgutl.c@@/main/3 - Fri Jul  1 01:12:59 2011

     Prg:    chebli 

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

#include "crg.h"
#include "nhac_acc.x"

EXTERN NhAccCb nhAccCb;
PUBLIC NhAccCrgVal gCrgValStore[25];


#ifdef ANSI
PUBLIC S16 nhAcUtlCrgGetValIdxCrnti
(
U8 *idx,
U16 id
)
#else
PUBLIC S16 nhAcUtlCrgGetValIdxCrnti(idx,id)
U8 *idx;
U16 id;
#endif
{
  U8 i=0;
  TRC2(nhAcUtlCpjGetValIdxCrnti);

  for(i=0;i<25;i++)
  {
    if(gCrgValStore[i].used ==TRUE && gCrgValStore[i].tCrnti == id)
    {
       *idx = i;
       RETVALUE(ROK);
    }
  }
  RETVALUE(RFAILED);
}

#ifdef ANSI
PUBLIC S16 nhAcUtlCrgGetValIdxUe
(
U8 *idx,
U16 id
)
#else
PUBLIC S16 nhAcUtlCrgGetValIdxUe(idx,id)
U8 *idx;
U16 id;
#endif
{
  U8 i=0;
  TRC2(nhAcUtlCrgGetValIdxUe);

  for(i=0;i<25;i++)
  {
    if(gCrgValStore[i].used ==TRUE && gCrgValStore[i].ueId == id)
    {
       *idx = i;
       RETVALUE(ROK);
    }
  }
  RETVALUE(RFAILED);
}
/*
*
*       Fun:   nhAcCrgValidate
*
*       Desc:  This function is used to validate cfg params
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_crgutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcCrgValidate
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */
CrgCfgReqInfo *cfg
)
#else
PUBLIC S16 nhAcCrgValidate(tcCb, spCb, cfg)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CrgCfgReqInfo *cfg;
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
   TRC2(nhAcCrgValidate);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "tCrntiPres", &(tCrntiPres));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ueIdPres", &(ueIdPres));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "cleanup", &(cleanup));

   if(tCrntiPres)
   {
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "valTCrnti", &(tCrnti));
     nhAcUtlCrgGetValIdxCrnti(&idx, tCrnti);
   }
   else if(ueIdPres)
   {
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "valUeId", &(ueId));
     nhAcUtlCrgGetValIdxUe(&idx,ueId);
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "rbIdx", &(rbIdx));

   if(cfg->action == CRG_CONFIG)
   {
       if(cfg->u.cfgInfo.cfgType == CRG_UE_CFG)
       {
         NHAC_CHK(cfg->u.cfgInfo.u.ueCfg.cellId, gCrgValStore[idx].cellId)
         NHAC_CHK(cfg->u.cfgInfo.u.ueCfg.crnti, gCrgValStore[idx].tCrnti)
       }
      if(cfg->u.cfgInfo.cfgType == CRG_LCH_CFG) 
       {
          NHAC_CHK(cfg->u.cfgInfo.u.lchCfg.cellId, gCrgValStore[idx].cellId)
          NHAC_CHK(cfg->u.cfgInfo.u.lchCfg.crnti, gCrgValStore[idx].tCrnti)
          NHAC_CHK(cfg->u.cfgInfo.u.lchCfg.lcId, gCrgValStore[idx].u.crgCfg.lchCfg[rbIdx].lcId)
          NHAC_CHK(cfg->u.cfgInfo.u.lchCfg.dlInfo.dlTrchType,gCrgValStore[idx].u.crgCfg.lchCfg[rbIdx].dlTrchType)
          NHAC_CHK(cfg->u.cfgInfo.u.lchCfg.ulInfo.ulTrchType,gCrgValStore[idx].u.crgCfg.lchCfg[rbIdx].ulTrchType)
       }
   }
   else if(cfg->action == CRG_RECONFIG)
   {
        if(cfg->u.cfgInfo.cfgType == CRG_UE_CFG)
       {
         NHAC_CHK(cfg->u.recfgInfo.u.ueRecfg.cellId,gCrgValStore[idx].cellId)
         /*cfg->cfgInfo.ueRecfg.oldCrnti*/
         NHAC_CHK(cfg->u.recfgInfo.u.ueRecfg.newCrnti, gCrgValStore[idx].tCrnti)
       }
       if(cfg->u.cfgInfo.cfgType == CRG_LCH_CFG) 
       {
          NHAC_CHK(cfg->u.recfgInfo.u.lchRecfg.cellId, gCrgValStore[idx].cellId)
          NHAC_CHK(cfg->u.recfgInfo.u.lchRecfg.crnti, gCrgValStore[idx].tCrnti)
          NHAC_CHK(cfg->u.recfgInfo.u.lchRecfg.lcId, gCrgValStore[idx].u.crgReCfg.lchCfg[rbIdx].lcId) 
       }

   }
   else
   {
       if(cfg->u.delInfo.delType == CRG_UE_CFG)
       {
          NHAC_CHK(cfg->u.delInfo.u.ueDel.cellId,gCrgValStore[idx].cellId)
          NHAC_CHK(cfg->u.delInfo.u.ueDel.crnti,gCrgValStore[idx].tCrnti)
       }
       if(cfg->u.delInfo.delType == CRG_LCH_CFG) 
       {
          NHAC_CHK(cfg->u.delInfo.u.lchDel.cellId, gCrgValStore[idx].cellId)
          NHAC_CHK(cfg->u.delInfo.u.lchDel.crnti, gCrgValStore[idx].tCrnti)
          /*cfg->u.delInfo.u.lchDel.lcId
          cfg->u.delInfo.u.lchDel.dir*/
       }
   }

   if(cleanup)
   {
      cmMemset((U8*)&gCrgValStore[idx], 0 , sizeof(NhAccCrgVal));
      gCrgValStore[idx].used = FALSE;
   }
   
   RETVALUE(ROK);

} /* End of nhAcCrgValidate() */



/*
 *
 *       Fun:    nhAcCrgTstCbFind -
 *
 *       Desc:   Find the test Case Control Block 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   nhac_crgutl.c
 *
 */

#ifdef ANSI
PUBLIC CmXtaTCCb*  nhAcCrgTstCbFind
(
)
#else
PUBLIC CmXtaTCCb*  nhAcCrgTstCbFind ()
#endif
{
   TRC2(nhAcCrgTstCbFind)

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
*       Fun:   nhAcUtlCrgCb
*
*       Desc:  This function is used to free the Queue Element
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_crgutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlCrgCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 nhAcUtlCrgCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   NhAccMsgQElm  *rrcMsg = NULLP;

   TRC2(nhAcUtlCrgCb)

   CMXTA_DBG_PARAM((_cmxtap, "nhAcUtlCrgCb(): \n"));

   rrcMsg = (NhAccMsgQElm *)qElm->data;
   /* Free mem allocated in XTA cb functions */
   CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlCrgCb() */




/**********************************************************************
         End of file:     nhac_crgutl.c@@/main/3 - Fri Jul  1 01:12:59 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    chebli           1. LTE RRC Initial Release.
/main/2      ---    chebli           1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
