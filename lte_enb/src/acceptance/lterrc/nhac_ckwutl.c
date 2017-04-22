/********************************************************************20**

     Name:    RRC - acc test file

     Type:    C file

     Desc:    

     File:     nhac_ckwutl.c

     Sid:      nhac_ckwutl.c@@/main/3 - Fri Jul  1 01:12:57 2011

     Prg:     rer

*********************************************************************21*/

/*
 *
 *       Fun:    nhAcCkwTstCbFind -
 *
 *       Desc:   Find the test Case Control Block 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   nhac_ckwutl.c
 *
 */
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

#include "ckw.h"
#include "nhac_acc.x"
EXTERN NhAccCb nhAccCb;

PUBLIC NhAccCkwVal gCkwValStore[25];

#ifdef ANSI
PUBLIC S16 nhAcUtlCkwGetValIdxUe
(
U8 *idx,
U16 id
)
#else
PUBLIC S16 nhAcUtlCkwGetValIdxUe(idx,id)
U8 *idx;
U16 id;
#endif
{
  U8 i=0;
  TRC2(nhAcUtlCkwGetValIdxUe);

  for(i=0;i<25;i++)
  {
    if(gCkwValStore[i].used ==TRUE && gCkwValStore[i].ueId == id)
    {
       *idx = i;
       RETVALUE(ROK);
    }
  }
  RETVALUE(RFAILED);
}

#ifdef ANSI
PUBLIC S16 nhAcUtlCkwGetValIdxCrnti
(
U8 *idx,
U16 id
)
#else
PUBLIC S16 nhAcUtlCkwGetValIdxCrnti(idx,id)
U8 *idx;
U16 id;
#endif
{
  U8 i=0;
  TRC2(nhAcUtlCkwGetValIdxUe);

  for(i=0;i<25;i++)
  {
    if(gCkwValStore[i].used ==TRUE && gCkwValStore[i].tCrnti == id)
    {
       *idx = i;
       RETVALUE(ROK);
    }
  }
  RETVALUE(RFAILED);
}


/*
*       Fun:   nhAcCkwValidate
*
*       Desc:  This function is used to validate cfg params
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_crlutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcCkwValidate
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */
CkwCfgInfo     *ckwCfgParam
)
#else
PUBLIC S16 nhAcCkwValidate(tcCb, spCb, ckwCfgParam)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;     /* spCb data structure  */
CkwCfgInfo     *ckwCfgParam;
#endif
{
   U16 ueId=0;
   U8 i=0;
   U8 idx=0;
   U8 tCrntiPres=0;
   U8 ueIdPres=0;
   U16  tCrnti;
   U8 cleanup=0;


   TRC2(nhAcCkwValidate);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "tCrntiPres", &(tCrntiPres));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ueIdPres", &(ueIdPres));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "cleanup", &(cleanup));

   if(tCrntiPres)
   {
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "valTCrnti", &(tCrnti));
     nhAcUtlCkwGetValIdxCrnti(&idx, tCrnti);
   }
   else if(ueIdPres)
   {
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "valUeId", &(ueId));
     nhAcUtlCkwGetValIdxUe(&idx,ueId);
   }

   NHAC_CHK(ckwCfgParam->transId,gCkwValStore[idx].transId);
   NHAC_CHK(ckwCfgParam->cellId,gCkwValStore[idx].cellId);

   for(i=0;i<ckwCfgParam->numEnt;i++)
   {
      /*NHAC_CHK(ckwCfgParam->entCfg[i].cfgType,gCkwValStore[idx].entity[i].cfgType)*/
      NHAC_CHK(ckwCfgParam->entCfg[i].rbId,gCkwValStore[idx].entity[i].rbId)
      if(ckwCfgParam->entCfg[i].dir == CKW_CFG_DIR_UL)
      {
      NHAC_CHK(ckwCfgParam->entCfg[i].entMode,gCkwValStore[idx].entity[i].entMode)
      }
      if(ckwCfgParam->entCfg[i].dir == CKW_CFG_DIR_DL)
      {
      NHAC_CHK(ckwCfgParam->entCfg[i].entMode,gCkwValStore[idx].entity[i].entMode)
      }
   }
   if(cleanup)
   {
      cmMemset((U8*)&gCkwValStore[idx], 0 , sizeof(NhAccCkwVal));
      gCkwValStore[idx].used = FALSE;
   }

   RETVALUE(ROK);
}
/*
*
*       Fun:   nhAcCkwTstCbFind
*
*       Desc:  This function is fins test Cb
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_ckwutl.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  nhAcCkwTstCbFind
(
)
#else
PUBLIC CmXtaTCCb*  nhAcCkwTstCbFind ()
#endif
{
   TRC2(nhAcCkwTstCbFind)

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
*       Fun:   nhAcUtlCkwCb
*
*       Desc:  This function is used to free the Queue Element
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_ckwutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlCkwCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 nhAcUtlCkwCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   NhAccMsgQElm  *rrcMsg = NULLP;

   TRC2(nhAcUtlCkwCb)

   CMXTA_DBG_PARAM((_cmxtap, "nhAcUtlCkwCb(): \n"));

   rrcMsg = (NhAccMsgQElm *)qElm->data;

   if (rrcMsg != NULLP)
   {
      CMXTA_FREE(rrcMsg, sizeof (NhAccMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlCkwCb() */


/**********************************************************************
         End of file:     nhac_ckwutl.c@@/main/3 - Fri Jul  1 01:12:57 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    rer              1. LTE RRC Initial Release.
/main/2      ---    ch               1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/


