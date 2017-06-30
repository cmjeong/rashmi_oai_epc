
/********************************************************************20**

     Name:     LTE RRC

     Type:     C source file

     Desc:     This file contains call back functions for NHU
               interface.

     File:     nhac_nhucb.c

     Sid:      nhac_nhucb.c@@/main/3 - Fri Jul  1 01:13:05 2011

     Prg:      Reena

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
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_acc_nhu.x"
#include "nh.x"

/* Following functions are implemented

NxLiNhuBndCfm
NxLiNhuDatInd
NxLiNhuDatCfm
NxLiNhuErrInd
NxLiNhuCfgCfm
NxLiNhuCellCfgCfm
NxLiNhuDecodeCfm
NxLiNhuCountCfm
NxLiNhuEncodeCfm

*/
/*
*
*       Fun:   NxLiNhuBndCfm - NHU Bind Cfm
*
*       Desc:  This function is used by to present Bind Cfm to NHU.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuBndCfm
(
Pst     *pst,
SuId    suId,
U8      status
)
#else
PUBLIC S16 NxLiNhuBndCfm(pst,suId,status)
Pst     *pst;  
SuId    suId;
U8      status;
#endif
{

   TRC2(NxLiNhuBndCfm)

   CMXTA_DBG_PARAM((_cmxtap, "NhLiNhuBndCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUBNDCFM;

   sprintf(pbuf,"\t XTA NHU : Bind Confirm Message Received\n ");
   SPrint(  pbuf  );

   if (nhAccCb.makeCfmFail)
   {
      nhAccCb.makeCfmFail = FALSE;
      RETVALUE(RFAILED);
   }
   else
   {
      nhAcNhuSaveMsg(pst, suId, status, NULLP);
      RETVALUE(ROK);
   }
} /* end of NxLiNhuBndCfm */

/*
*
*       Fun:   NxLiNhuDatInd - NHU Data Indication
*
*       Desc:  This function is used by to present Data Indication to NHU.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuDatInd
(
Pst     *pst,          
SuId     suId,
NhuDatIndSdus *nhuDatIndSdus           
)
#else
PUBLIC S16 NxLiNhuDatInd (pst,suId,nhuDatIndSdus)
Pst     *pst;          /* post structure */
SuId     suId;
NhuDatIndSdus *nhuDatIndSdus;          /* configuration */
#endif
{
   TRC2(NxLiNhuDatInd)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuDatInd():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUDATIND;

   if (nhAccCb.makeCfmFail)
   {
      nhAccCb.makeCfmFail = FALSE;
      CMXTA_FREEEVNT(nhuDatIndSdus)
      RETVALUE(RFAILED);
   }
   else
   {
      nhAcNhuSaveMsg(pst, suId, 0, nhuDatIndSdus);
      RETVALUE(ROK);
   }

} /* end of NxLiNhuDatInd */

/*
*
*       Fun:   NxLiNhuDatCfm - NHU Data Confirm
*
*       Desc:  This function is used by to present Data Confirmation to NHU.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuDatCfm
(
Pst     *pst,          
SuId    suId,
NhuDatCfmSdus *nhDatCfmSdus           
)
#else
PUBLIC S16 NxLiNhuDatCfm (pst,suId,nhDatCfmSdus)
Pst     *pst;          
SuId     suId;
NhuDatCfmSdus *nhDatCfmSdus;
#endif
{
   TRC2(NxLiNhuDatCfm)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuDatCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUDATCFM;

   nhAcNhuSaveMsg(pst, suId, 0, nhDatCfmSdus);

   RETVALUE(ROK);
} /* end of NxLiNhuDatCfm */

/*
*
*       Fun:   NxLiNhuStaInd - NHU status Indication
*
*       Desc:  This function is used by to present status indication to NHU.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuStaInd
(
Pst     *pst,          
SuId    suId,
NhuStaIndSdus *nhStaIndSdus           
)
#else
PUBLIC S16 NxLiNhuStaInd (pst,suId, nhStaIndSdus)
Pst     *pst;          
SuId     suId;
NhuStaIndSdus *nhStaIndSdus;
#endif
{
   TRC2(NxLiNhuStaInd)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuStaInd():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUSTAIND;

   nhAcNhuSaveMsg(pst, suId, 0, nhStaIndSdus);

   RETVALUE(ROK);
} /* end of NxLiNhuStaInd */
/*
*
*       Fun:   NxLiNhuErrInd - Error Indication
*
*       Desc:  This function is used by to present configuration 
*              confirm information to NHU.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuErrInd
(
Pst     *pst,          
SuId     suId,
NhuErrIndSdus *nhErrIndSdus           
)
#else
PUBLIC S16 NxLiNhuErrInd(pst,suId,nhErrIndSdus)
Pst     *pst;          
SuId     suId;
NhuErrIndSdus *nhErrIndSdus;          
#endif
{
   TRC2(NxLiNhuErrInd)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuErrInd():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUERRIND;

   nhAcNhuSaveMsg(pst, suId, 0, nhErrIndSdus);

   RETVALUE(ROK);
} /* end of NxLiNhuErrInd */


#ifdef ANSI
PUBLIC S16 NxLiNhuPdcpDatResumeCfm
(
Pst     *pst,          
SuId     suId,
NhuPdcpDatResumeCfm *nhDataResumeCfm
)
#else
PUBLIC S16 NxLiNhuPdcpDatResumeCfm(pst,suId,nhErrIndSdus)
Pst     *pst;          
SuId     suId;
NhuPdcpDatResumeCfm *nhDataResumeCfm;          
#endif
{
   TRC2(NxLiNhuPdcpDatResumeCfm)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuErrInd():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUPDCPDATRESUMECFM;

   nhAcNhuSaveMsg(pst, suId, 0, nhDataResumeCfm);

   RETVALUE(ROK);
} /* end of NxLiNhuErrInd */



/*
*
*       Fun:   NxLiNhuCfgCfm - Lower layer config confirm
*
*       Desc:  This function is used by to present configuration confirm
*              to NHU.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuCfgCfm
(
Pst     *pst,
SuId     suId,
NhuCfgCfmSdus *nhuCfgCfmSdus
)
#else
PUBLIC S16 NxLiNhuCfgCfm(pst,suId,nhuCfgCfmSdus)
Pst     *pst;
SuId     suId;
NhuCfgCfmSdus *nhuCfgCfmSdus;
#endif
{
   TRC2(NxLiNhuCfgCfm)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuCfgCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUCFGCFM;

   if (nhAccCb.makeCfmFail)
   {
      nhAccCb.makeCfmFail = FALSE;
      CMXTA_FREE(nhuCfgCfmSdus, sizeof(NhuCfgCfmSdus))
      RETVALUE(RFAILED);
   }
   else
   {
      nhAcNhuSaveMsg(pst, suId, 0, nhuCfgCfmSdus);
      RETVALUE(ROK);
   }
} /* end of NxLiNhuCfgCfm */

/*
*
*       Fun:   NxLiNhuCellCfgCfm - Cell Configuration Confirm
*
*       Desc:  This function is used by to present Cell Config Status Confirm
*              information to NHU.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuCellCfgCfm
(
Pst     *pst,          
SuId     suId,
NhuCellCfgCfmSdus *nhuCellCfgCfmSdus           
)
#else
PUBLIC S16 NxLiNhuCellCfgCfm(pst,suId,nhuCellCfgCfmSdus)
Pst     *pst;         
SuId     suId;
NhuCellCfgCfmSdus *nhuCellCfgCfmSdus;          
#endif
{
   TRC2(NxLiNhuCellCfgCfm)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuCellCfgCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUCELLCFGCFM;

   if (nhAccCb.makeCfmFail)
   {
      nhAccCb.makeCfmFail = FALSE;
      CMXTA_FREE(nhuCellCfgCfmSdus, sizeof(NhuCellCfgCfmSdus))
      RETVALUE(RFAILED);
   }

   nhAcNhuSaveMsg(pst, suId, 0, nhuCellCfgCfmSdus);
   RETVALUE(ROK);
} /* end of NxLiNhuCellCfgCfm */

/*
*
*       Fun:   NxLiNhuDecodeCfm - Decode Confirm
*
*       Desc:  This function is used to inform decode confirmation to RRC user.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuDecodeCfm
(
Pst     *pst,
SuId     suId,
NhuDecodeSduCfm *nhuDecodeSduCfm
)
#else
PUBLIC S16 NxLiNhuDecodeCfm(pst,suId,nhuDecodeSduCfm)
Pst     *pst;
SuId     suId;
NhuDecodeSduCfm *nhuDecodeSduCfm;
#endif
{
   TRC2(NxLiNhuDecodeCfm)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuDecodeCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUDCODECFM;

   if (nhAccCb.makeCfmFail)
   {
      nhAccCb.makeCfmFail = FALSE;
      CMXTA_FREEEVNT(nhuDecodeSduCfm);
      RETVALUE(RFAILED);
   }
   else
   {
      nhAcNhuSaveMsg(pst, suId, 0, nhuDecodeSduCfm);
      RETVALUE(ROK);
   }

} /* end of NxLiNhuDecodeCfm */

/*
*
*       Fun:   NxLiNhuCountCfm - Count Confirm
*
*       Desc:  This function is used to inform COUNT values of DRBs to RRC user.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuCountCfm
(
Pst     *pst,
SuId     suId,
NhuDRBCountInfoLst *nhuDRBCountInfoLst
)
#else
PUBLIC S16 NxLiNhuCountCfm(pst,suId,nhuDRBCountInfoLst)
Pst     *pst;
SuId     suId;
NhuDRBCountInfoLst *nhuDRBCountInfoLst;
#endif
{
   TRC2(NxLiNhuCountCfm)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuCountCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUCOUNTCFM;

   if (nhAccCb.makeCfmFail)
   {
      nhAccCb.makeCfmFail = FALSE;
      CMXTA_FREEEVNT(nhuDRBCountInfoLst);
      RETVALUE(RFAILED);
   }
   else
   {
      nhAcNhuSaveMsg(pst, suId, 0, nhuDRBCountInfoLst);
      RETVALUE(ROK);
   }
} /* end of NxLiNhuCountCfm */

/*
*
*       Fun:   NxLiNhuEncodeCfm - Encode Confirm
*
*       Desc:  This function is used to inform Encode confirmation to RRC user.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuEncodeCfm
(
Pst     *pst,
SuId     suId,
NhuEncCfmSdus *nhuEncCfmSdus
)
#else
PUBLIC S16 NxLiNhuEncodeCfm(pst,suId,nhuEncCfmSdus)
Pst     *pst;
SuId     suId;
NhuEncCfmSdus *nhuEncCfmSdus;
#endif
{
   TRC2(NxLiNhuEncodeCfm)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuEncodeCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUENCODECFM;

   nhAcNhuSaveMsg(pst, suId, 0, nhuEncCfmSdus);

   RETVALUE(ROK);
} /* end of NxLiNhuEncodeCfm */

/*
*
*       Fun:   NxLiNhuPdcpSduStaCfm - PDCP SDU Status Confirm
*
*       Desc:  This function is used to inform PDCP SDU Status confirmation to 
*              RRC user.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 NxLiNhuPdcpSduStaCfm
(
Pst     *pst,
SuId     suId,
NhuPdcpSduStaCfm *nhuPdcpSduStaCfm
)
#else
PUBLIC S16 NxLiNhuPdcpSduStaCfm(pst,suId,nhuPdcpSduStaCfm)
Pst     *pst;
SuId     suId;
NhuPdcpSduStaCfm *nhuPdcpSduStaCfm;
#endif
{
   TRC2(NxLiNhuPdcpSduStaCfm)

   CMXTA_DBG_PARAM((_cmxtap, "NxLiNhuPdcpSduStaCfm():\n"));

   /*-- Update Event --*/
   pst->event = EVTNHUPDCPSDUSTACFM;

   nhAcNhuSaveMsg(pst, suId, 0, nhuPdcpSduStaCfm);

   RETVALUE(ROK);
} /* end of NxLiNhuPdcpSduStaCfm */

/*
*
*       Fun:   NxLiNhuPdcpDatResumeCfm - PDCP Data Resume Confirm
*
*       Desc:  This function is used for handling PDCP Data Resume Confirm 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhucb.c
*
*/
#if 0
#ifdef ANSI
PUBLIC S16 NxLiNhuPdcpDatResumeCfm 
(
Pst     *pst,
SuId     suId,
NhuPdcpDatResumeCfm *nhuPdcpDatResumeCfm
)
#else
PUBLIC S16 NxLiNhuPdcpDatResumeCfm(pst,suId,nhuPdcpDatResumeCfm)
Pst     *pst;
SuId     suId;
NhuPdcpDatResumeCfm *nhuPdcpDatResumeCfm;
#endif
{
   TRC2(NxLiNhuPdcpDatResumeCfm)

   /* To be done */
   CMXTA_DBG_ERR((_cmxtap, "NxLiNhuPdcpDatResumeCfm() : To be done \n"));

   RETVALUE(ROK);
} /* end of NxLiNhuPdcpDatResumeCfm */
#endif
/*
*
*       Fun:   nhAcNhuSaveMsg
*
*       Desc:  Function to push the message on queue 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_nhucb.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcNhuSaveMsg
(
Pst  *pst,
SuId suId,
U8   status,
void *nhuInfo
)
#else
PUBLIC S16 nhAcNhuSaveMsg(pst, suId, status, nhuInfo)
Pst  *pst;
SuId suId;
U8   status;
void *nhuInfo;
#endif 
{
   CmXtaTCCb    *tcCb = NULLP;
   NhAccMsgQElm *rrcMsg = NULLP; 
   CmXtaMsgQElm qElm;
   U8           msgLen;

   TRC3(nhAcNhuSaveMsg);

   cmMemset( (U8* )&qElm, 0, sizeof(CmXtaMsgQElm));

   CMXTA_DBG_PARAM((_cmxtap, "nhAcNhuSaveMsg(): suId (%d))", suId));

   /*-- Allocate RRC memory data --*/
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcNhuSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.nhuInfo.suId = suId;

   switch (pst->event)
   {
      case EVTNHUBNDCFM:
         rrcMsg->u.nhuInfo.status = status;
         break;

      case EVTNHUDATIND:
         if (NULLP != nhuInfo)
         {
             CMXTA_ALLOC(&rrcMsg->mBuf, sizeof(NhuDatIndSdus));
             cmMemcpy((U8*)rrcMsg->mBuf, 
                      (CONSTANT U8*)((NhuDatIndSdus*)nhuInfo), 
                      sizeof(NhuDatIndSdus));
            CMXTA_FREEEVNT(nhuInfo);
         }
         break;

      case EVTNHUCFGCFM:
         if (NULLP != nhuInfo)
         {
            CMXTA_ALLOC(&rrcMsg->mBuf, sizeof (NhuCfgCfmSdus));
            cmMemcpy((U8*)rrcMsg->mBuf, 
                     (CONSTANT U8*)((NhuCfgCfmSdus*)nhuInfo), 
                      sizeof(NhuCfgCfmSdus));
            CMXTA_FREE(nhuInfo, sizeof(NhuCfgCfmSdus));
         }
         break;

      case EVTNHUCELLCFGCFM:
         if (NULLP != nhuInfo)
         {
            CMXTA_ALLOC(&rrcMsg->mBuf, sizeof (NhuCellCfgCfmSdus));
            cmMemcpy((U8*)rrcMsg->mBuf, 
                     (CONSTANT U8*)((NhuCellCfgCfmSdus*)nhuInfo), 
                     sizeof(NhuCellCfgCfmSdus));
            CMXTA_FREE(nhuInfo, sizeof(NhuCellCfgCfmSdus));
         }
         break;

      case EVTNHUDATCFM:
         if (NULLP != nhuInfo)
         {
            CMXTA_ALLOC(&rrcMsg->mBuf, sizeof(NhuDatCfmSdus));
            cmMemcpy((U8*)rrcMsg->mBuf,
                     (CONSTANT U8*)((NhuDatCfmSdus *)nhuInfo), 
                     sizeof(NhuDatCfmSdus));
            CMXTA_FREE(nhuInfo, sizeof(NhuDatCfmSdus));
         }
         break;

      case EVTNHUSTAIND:
         if (NULLP != nhuInfo)
         {
            CMXTA_ALLOC(&rrcMsg->mBuf, sizeof(NhuStaIndSdus));
            cmMemcpy((U8*)rrcMsg->mBuf,
                     (CONSTANT U8*)((NhuStaIndSdus *)nhuInfo), 
                     sizeof(NhuStaIndSdus));
            CMXTA_FREE(nhuInfo, sizeof(NhuStaIndSdus));
         }
         break;

      case EVTNHUERRIND:
         if (NULLP != nhuInfo)
         {
            CMXTA_ALLOC(&rrcMsg->mBuf, sizeof(NhuErrIndSdus));
            cmMemcpy((U8*)rrcMsg->mBuf,
                     (CONSTANT U8*)((NhuErrIndSdus *)nhuInfo), 
                     sizeof(NhuErrIndSdus));
            CMXTA_FREE(nhuInfo, sizeof(NhuErrIndSdus));
         }
         break;

      case EVTNHUENCODECFM:
         if (NULLP != nhuInfo)
         {
            msgLen = ((NhuEncCfmSdus*)nhuInfo)->sdu.msgLen/8;
            if(((NhuEncCfmSdus*)nhuInfo)->sdu.msgLen % 8)
               msgLen++;
            /* Store the encoded buffer. This is required in case of HO */
            if( (((NhuEncCfmSdus*)nhuInfo)->sdu.status == NHU_ENCODE_SUCCESS) && 
                (msgLen) )
            {
               SCpyMsgMsg(((NhuEncCfmSdus*)nhuInfo)->sdu.mBuf, 
                          0, 0, &rrcMsg->u.nhuInfo.encBufInfo.encBuf);

               rrcMsg->u.nhuInfo.encBufInfo.msgLen = msgLen;
               rrcMsg->u.nhuInfo.encBufInfo.encBufPres = TRUE;
            }
            CMXTA_ALLOC(&rrcMsg->mBuf, sizeof(NhuEncCfmSdus));
            cmMemcpy((U8*)rrcMsg->mBuf,
                     (CONSTANT U8*)((NhuEncCfmSdus *)nhuInfo), 
                     sizeof(NhuEncCfmSdus));
            CMXTA_FREEMBUF(((NhuEncCfmSdus*)nhuInfo)->sdu.mBuf);
            CMXTA_FREE(nhuInfo, sizeof(NhuEncCfmSdus));
         }
         break;

      case EVTNHUDCODECFM:
         if (NULLP != nhuInfo)
         {
            rrcMsg->u.nhuInfo.decMsgType = 
                       ((NhuDecodeSduCfm*)nhuInfo)->sduType;
            CMXTA_FREEEVNT(nhuInfo);
         }
         break;

      case EVTNHUCOUNTCFM:
         if (NULLP != nhuInfo)
         {
            NhuDrbCountInfo *nhuDrbCountInfo = NULLP;
            CMXTA_ALLOC(&rrcMsg->mBuf, sizeof(NhuDRBCountInfoLst));
            cmMemcpy((U8*)rrcMsg->mBuf,
                     (CONSTANT U8*)((NhuDRBCountInfoLst *)nhuInfo),
                     sizeof(NhuDRBCountInfoLst));

            CMXTA_ALLOC(&nhuDrbCountInfo, ((NhuDRBCountInfoLst *)nhuInfo)->numDrbs *
                     sizeof(NhuDrbCountInfo));
            cmMemcpy((U8*)nhuDrbCountInfo,
                     (CONSTANT U8*) (((NhuDRBCountInfoLst *)nhuInfo)->member),
                     ((NhuDRBCountInfoLst *)nhuInfo)->numDrbs * sizeof(NhuDrbCountInfo));

           ((NhuDRBCountInfoLst *)(rrcMsg->mBuf))->member = nhuDrbCountInfo;

            CMXTA_FREEEVNT(nhuInfo);
         }
         break;

      case EVTNHUPDCPSDUSTACFM:
         if (NULLP != nhuInfo)
         {
            CMXTA_ALLOC(&rrcMsg->mBuf, sizeof(NhuPdcpSduStaCfm));
            cmMemcpy((U8*)rrcMsg->mBuf,
                     (CONSTANT U8*)((NhuPdcpSduStaCfm *)nhuInfo),
                     sizeof(NhuPdcpSduStaCfm));
            CMXTA_FREEEVNT(nhuInfo);
         }
         break;
      case EVTNHUSTARTPDCPDATAFWDREQ:
         break;   
      case EVTNHUPDCPDATRESUMECFM:
         /* TODO */
         /* Handler for resume confirmation */
         break;

      default:
         CMXTA_DBG_INFO((_cmxtap, "nhAcNhuSaveMsg(): Unhandled event\n"));
         RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Usual mode --*/
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Fill the message in the queue structure --*/
   CMXTA_CPY((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   if ((tcCb = (CmXtaTCCb*)nhAcNhuTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "nhAcNhuSaveMsg(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlNhuCb;
   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ,(CmXtaMsgQElm *) &qElm);

   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcNhuSaveMsg() */

/*
*
*       Fun:   nhAcNhuTstCbFind
*
*       Desc:  Call handler for finding the Test Case Control Block
*
*       Ret:   Test Case Control Block
*
*       Notes: None
*              
*       File:  nhac_nhucb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  nhAcNhuTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  nhAcNhuTstCbFind ()
#endif
{
   TRC2(nhAcNhuTstCbFind)

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
} /* nhAcNhuTstCbFind */

/********************************************************************30**

         End of file:     nhac_nhucb.c@@/main/3 - Fri Jul  1 01:13:05 2011

*********************************************************************31*/
/********************************************************************40**

        Notes:

*********************************************************************41*/
/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      Reena            1. LTE RRC Initial Release.
/main/2      ---      chebli           1. RRC Release 2.1.
/main/3      ---      sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
