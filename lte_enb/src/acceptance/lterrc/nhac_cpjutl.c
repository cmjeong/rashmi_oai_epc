/********************************************************************20**

     Name:    RRC - acc test file

     Type:    C file

     Desc:    

     File:    nhac_cpjutl.c

     Sid:      nhac_cpjutl.c@@/main/3 - Fri Jul  1 01:12:58 2011

     Prg:     dm

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="RRC";
static int RLOG_MODULE_ID=65;
static int RLOG_FILE_ID=91;

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
using namespace NH_LTERRC_REL11;
#include "nhac_nhu.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "nh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"
#include "nhac_acc_cpj.x"

/*global array holding PDPC config structure for a given UE*/
PUBLIC NhAccCpjVal gCpjCfgStore[25];

#ifdef ANSI
PUBLIC S16 nhAcUtlCpjGetValIdxUe
(
U8 *idx, 
U16 id
)
#else
PUBLIC S16 nhAcUtlCpjGetValIdxUe(idx,id)
U8 *idx;
U16 id;
#endif
{
  U8 i=0;
  TRC2(nhAcUtlCpjGetValIdxUe);

  for(i=0;i<25;i++)
  {
    if(gCpjCfgStore[i].used ==TRUE && gCpjCfgStore[i].ueId == id)
    {
       *idx = i;
       RETVALUE(ROK);
    } 
  }
  RETVALUE(RFAILED);
}

#ifdef ANSI
PUBLIC S16 nhAcUtlCpjGetValIdxCrnti
(
U8 *idx, 
U16 id
)
#else
PUBLIC S16 nhAcUtlCpjGetValIdxCrnti(idx,id)
U8 *idx;
U16 id;
#endif
{
  U8 i=0;
  TRC2(nhAcUtlCpjGetValIdxUe);

  for(i=0;i<25;i++)
  {
    if(gCpjCfgStore[i].used ==TRUE && gCpjCfgStore[i].tCrnti == id)
    {
       *idx = i;
       RETVALUE(ROK);
    } 
  }
  RETVALUE(RFAILED);
}

/*
*
*       Fun:   nhAcUtlCpjVal
*
*       Desc:  This function is used to free the Queue Element
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_cpjutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlCpjVal 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */
CpjCfgReqInfo *req
)
#else
PUBLIC S16 nhAcUtlCpjVal(tcCb, spCb, req)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;     /* spCb data structure  */
CpjCfgReqInfo *req;
#endif /* ANSI */
{

   U8 i=0;
   U16 ueId=0;
   U8 idx=0;
   U16 tCrnti;
   U8 tCrntiPres=0;
   U8 ueIdPres=0;
   U8 cleanup=0;

   TRC2(nhAcUtlCpjVal);


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "tCrntiPres", &(tCrntiPres)); 
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ueIdPres", &(ueIdPres)); 
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "cleanup", &(cleanup));

   if(tCrntiPres) 
   {
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "valTCrnti", &(tCrnti)); 
     nhAcUtlCpjGetValIdxCrnti(&idx, tCrnti);
   }
   else if(ueIdPres)
   {
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "valUeId", &(ueId)); 
     nhAcUtlCpjGetValIdxUe(&idx,ueId);
   }
    
   NHAC_CHK(req->transId,gCpjCfgStore[idx].transId);
   NHAC_CHK(req->cellId,gCpjCfgStore[idx].cellId);

   for( i=0; i<req->numEnt; i++)
   {
      if(req->cfgEnt[i].cfgType == CPJ_CFG_ADD)
      {
         if(req->cfgEnt[i].m.addCfg.hdrCompCfg.hdrCompUsed == NH_USED)
         {
            NHAC_CHK(req->cfgEnt[i].m.addCfg.hdrCompCfg.rohcInfo.maxCid,
                     gCpjCfgStore[idx].entity[i].hdrComCfg.rohcInfo.maxCid);
            NHAC_CHK(req->cfgEnt[i].m.addCfg.hdrCompCfg.rohcInfo.profLst,
                     gCpjCfgStore[idx].entity[i].hdrComCfg.rohcInfo.profLst);
         }
      }
      if(req->cfgEnt[i].cfgType == CPJ_CFG_MODIFY)
      {
         if(req->cfgEnt[i].m.modCfg.hdrCompCfg.hdrCompUsed == NH_USED)
         {
            NHAC_CHK(req->cfgEnt[i].m.modCfg.hdrCompCfg.rohcInfo.maxCid,
                     gCpjCfgStore[idx].entity[i].hdrComCfg.rohcInfo.maxCid);
            NHAC_CHK(req->cfgEnt[i].m.modCfg.hdrCompCfg.rohcInfo.profLst,
                     gCpjCfgStore[idx].entity[i].hdrComCfg.rohcInfo.profLst);
         }
      }

   }

   if(cleanup)
   {
      cmMemset((U8*)&gCpjCfgStore[idx], 0 , sizeof(NhAccCpjVal));
      gCpjCfgStore[idx].used = FALSE;
   }

   
   RETVALUE(ROK);
}

/*
 *
 *       Fun:    nhAcCpjTstCbFind -
 *
 *       Desc:   Find the test Case Control Block 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:  nhac_cpjutl.c 
 *
 */
#ifdef ANSI
PUBLIC CmXtaTCCb*  nhAcCpjTstCbFind
(
Void 
)
#else
PUBLIC CmXtaTCCb*  nhAcCpjTstCbFind ()
#endif
{
   TRC2(nhAcCpjTstCbFind)

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
*       Fun:   nhAcUtlCpjCb
*
*       Desc:  This function is used to free the Queue Element
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_cpjutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlCpjCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 nhAcUtlCpjCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   NhAccMsgQElm  *rrcMsg = NULLP;

   TRC2(nhAcUtlCpjCb)

   CMXTA_DBG_PARAM((_cmxtap, "nhAcUtlCpjCb(): \n"));

   rrcMsg = (NhAccMsgQElm *)qElm->data;
   
   if (rrcMsg != NULLP)
   {
      CMXTA_FREE(rrcMsg, sizeof (NhAccMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlCpjCb() */

/*
*
*       Fun:   nhAcUtlCpjSecVal
*
*       Desc:  This function valiadtes the Security request sent to CPJ
*              against actual values request from RRC user
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_cpjutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlCpjSecVal 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */
CpjSecCfgReqInfo *req
)
#else
PUBLIC S16 nhAcUtlCpjSecVal(tcCb, spCb, req)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;     /* spCb data structure  */
CpjSecCfgReqInfo *req;
#endif /* ANSI */
{

   U16 ueId=0;
   U8 idx=0;
   U16 tCrnti;
   U8 tCrntiPres=0;
   U8 ueIdPres=0;
   U8 cleanup=0;
   U8 keyIndex;

   TRC2(nhAcUtlCpjVal);


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "tCrntiPres", &(tCrntiPres)); 
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ueIdPres", &(ueIdPres)); 
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "cleanup", &(cleanup));

   if(tCrntiPres) 
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "valTCrnti", &(tCrnti)); 
      if(nhAcUtlCpjGetValIdxCrnti(&idx, tCrnti) == RFAILED)
      {
         CMXTA_DBG_ERR((_cmxtap,"nhAcUtlCpjSecVal() Ue context not found\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else if(ueIdPres)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "valUeId", &(ueId)); 
      if(nhAcUtlCpjGetValIdxCrnti(&idx, ueId) == RFAILED)
      {
         CMXTA_DBG_ERR((_cmxtap,"nhAcUtlCpjSecVal() Ue context not found\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   NHAC_CHK(req->transId, gCpjCfgStore[idx].transId);
   NHAC_CHK(req->cellId, gCpjCfgStore[idx].cellId);

   /* TODO Check is selSecMod proper */
   if(gCpjCfgStore[idx].secInfo.conReCfgCause & NHU_CONN_RECFG_AT_HNDOVR)
   {
      NHAC_CHK(req->secCfg.selSecAct, FALSE);
   }

   /* TODO Check are Integrity Alog info is proper is It is present */
   if(gCpjCfgStore[idx].secInfo.secCfgBitMsk & CPJ_SEC_INTG_INFO)
   {

      switch(gCpjCfgStore[idx].secInfo.intgCfgInfo.intgAlgo)
      {
#ifdef LTE_RRC
         case NHU_INTG_ALGO_EIA0: /*R9 upgrade: Added to support NULL IP*/
            NHAC_CHK(req->secCfg.integInfo.algoType, CPJ_SEC_ALG_NULL);
            break;
#endif/*LTE_RRC*/
         case NHU_INTG_ALGO_EIA1:
            NHAC_CHK(req->secCfg.integInfo.algoType, CPJ_SEC_ALG_SNOW3G);
            break;
         case NHU_INTG_ALGO_EIA2:
            NHAC_CHK(req->secCfg.integInfo.algoType, CPJ_SEC_ALG_AES);
            break;
         default:
            RLOG0(L_ERROR, " Validation failed: Invalid intg Algo ");
            RETVALUE(RFAILED);
            break;
      }
      for(keyIndex = 0; keyIndex < CPJ_INTG_KEY_LEN; keyIndex++)
         NHAC_CHK(req->secCfg.integInfo.intKey[keyIndex],
            gCpjCfgStore[idx].secInfo.intgCfgInfo.intgKey[keyIndex]);
   }

   /* TODO Check are Ciphering Alog info is proper is It is present */
   if(gCpjCfgStore[idx].secInfo.secCfgBitMsk & CPJ_SEC_CIPHER_INFO)
   {
      switch(gCpjCfgStore[idx].secInfo.cipCfgInfo.ciphAlgo)
      {
         case NHU_CIPHER_ALGO_EEA0:
            NHAC_CHK(req->secCfg.cipherInfo.algoType, CPJ_SEC_ALG_NULL);
            break;
         case NHU_CIPHER_ALGO_EEA1:
            NHAC_CHK(req->secCfg.cipherInfo.algoType,  CPJ_SEC_ALG_SNOW3G);
            break;
         case NHU_CIPHER_ALGO_EEA2:
            NHAC_CHK(req->secCfg.cipherInfo.algoType, CPJ_SEC_ALG_AES);
            break;
         default:
            RLOG0(L_ERROR, " Validation failed: Invalid ciph Algo ");
            RETVALUE(RFAILED);
            break;
      }

      for(keyIndex=0; keyIndex<CPJ_CIPHER_KEY_LEN; keyIndex++)
         NHAC_CHK(req->secCfg.cipherInfo.ctrlplnKey[keyIndex],
               gCpjCfgStore[idx].secInfo.cipCfgInfo.cipherCpKey[keyIndex]);

      for(keyIndex=0; keyIndex<CPJ_CIPHER_KEY_LEN; keyIndex++)
         NHAC_CHK(req->secCfg.cipherInfo.usrplnKey[keyIndex],
            gCpjCfgStore[idx].secInfo.cipCfgInfo.cipherUpKey[keyIndex]);
   }

   if(cleanup)
   {
      cmMemset((U8*)&gCpjCfgStore[idx], 0 , sizeof(NhAccCpjVal));
      gCpjCfgStore[idx].used = FALSE;
   }

   
   RETVALUE(ROK);
}

/*
*
*       Fun:   nhAcCpjUtlStrToken
*
*       Desc:  This function extracts the string till delimiter
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_cpjutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcCpjUtlStrToken
(
Txt      *line,                  /* text buffer */
Txt      *frstWord,              /* target for first word after : */
Txt      delimiter
)
#else
PUBLIC S16 nhAcCpjUtlStrToken(line, frstWord,  delimiter)
Txt      *line;                  /* text buffer */
Txt      *frstWord;
Txt      delimiter;
#endif
{
   /* local variable */

   U16         i;
   U16         j;

   TRC2(nhAcUtlStrToken)

   /* extract the first word */
   i = 0;
   j = 0;
   while (line[i] != delimiter)
   {
      /* have we reached the end of the line */
      if ((line[i] == '\0') || (line[i] == '\n'))
      {
         /* NULL terminate it */
         frstWord[j] = '\0';
         /* no ":" found so far so there is an error */
         RETVALUE(CMXTA_ERR_INT);
      }

      frstWord[j++] = line[i];
      i++;
   }

   /* NULL terminate it */
   frstWord[j] = '\0';

   RETVALUE(CMXTA_ERR_NONE);
}

/**********************************************************************
         End of file:     nhac_cpjutl.c@@/main/3 - Fri Jul  1 01:12:58 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat     init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     dm               1. LTE RRC Initial Release.
/main/2      ---     ch               1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
