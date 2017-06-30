



/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:    rg_dux.c 
  
     Sid:      gk_dux.c@@/main/3 - Sat Jul 30 02:21:27 2011
  
     Prg:     sd 
  
**********************************************************************/

/** @file rg_dux.c
@brief This module handles de-multiplexing of the data recieved at MAC.
*/

static const char* RLOG_MODULE_NAME="MAC";
static int RLOG_FILE_ID=176;
static int RLOG_MODULE_ID=4096;
/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */

#include "cm_lte.h"        /* Common LTE */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* common memory link list library */

#include "rg_env.h"        /* MAC Environment Defines */
#include "tfu.h"           /* CRG Interface defines */
#include "crg.h"           /* CRG Interface defines */
#include "rg_sch_inf.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */

#include "rg.h"            /* MAC defines */
#include "rg_err.h"        /* MAC error defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* common timers */
#include "cm_lib.x"        /* common library */
#include "cm_lte.x"        /* Common LTE */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* common memory link list library */

#include "rgu.x"           /* RGU types */
#include "tfu.x"           /* CRG Interface includes */
#include "crg.x"           /* CRG Interface includes */
#include "rg_sch_inf.x"    /* SCH Interface includes */
#include "rg_prg.x"        /* PRG interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */

#include "rg.x"            /* MAC includes */

/* local defines */

/* local typedefs */
 
/* local externs */
 
/* forward references */

#define RG_DUX_ALLOC(_pdu, _size, _dataPtr, _ret) {\
   _ret = cmGetMem((Ptr)&_pdu->memCp, _size, (Ptr *)&_dataPtr); \
}

#define RG_INIT_CE_SUBHDR(_subHdr, _lcId) {\
   (_subHdr)->lcId = (_lcId); \
   (_subHdr)->subHdrLstEnt.next = NULLP; \
   (_subHdr)->subHdrLstEnt.prev = NULLP; \
   (_subHdr)->subHdrLstEnt.node = (PTR)(_subHdr); \
}

#define RG_INIT_SDU(_sdu, _lcId, _len) {\
   (_sdu)->lcId = (_lcId); \
   (_sdu)->len = (_len); \
   (_sdu)->mBuf = NULLP; \
   (_sdu)->sduLstEnt.next = NULLP; \
   (_sdu)->sduLstEnt.prev = NULLP; \
   (_sdu)->sduLstEnt.node = (PTR)(_sdu); \
}

#define RG_EXT_BS(_bsr, _bs1, _bs2, _bs3, _bs4)  {\
   _bs1 = _bsr[0] >> 2; \
   _bs2 = (((_bsr[0] & 0x3) << 4) | (_bsr[1] >> 4)); \
   _bs3 = (((_bsr[1] & 0x0F) << 2) | (_bsr[2] >> 6)); \
   _bs4 = _bsr[2] & 0x3F; \
}

#define RG_UNPACK_LONG_BSR(_bsr, _mBuf, _ret) {\
   _ret = SRemPreMsgMult((_bsr), 3, (_mBuf)); \
}

#define RG_UNPACK_SHORT_BSR(_bsr, _mBuf, _ret) {\
   _ret = SUnpkU8((_bsr), (_mBuf)); \
}

#define RG_UNPACK_TRUNC_BSR(_bsr, _mBuf, _ret) {\
   _ret = SUnpkU8((_bsr), (_mBuf)); \
}

#define RG_UNPACK_PHR(_phr, _mBuf, _ret) {\
   _ret = SUnpkU8((_phr), (_mBuf)); \
}

#define RG_UNPACK_CRNTI(_rnti, _mBuf, _ret) {\
   Data _unpkArray[2];\
   *_rnti = 0;\
   _ret = SRemPreMsgMult(_unpkArray, (MsgLen) 2, _mBuf);\
   if (_ret == ROK)\
   {\
      *_rnti = (U16) PutHiByte(*_rnti, (U8) _unpkArray[0]);\
      *_rnti = (U16) PutLoByte(*_rnti, (U8) _unpkArray[1]);\
   }\
}

/* For EXT PHR DEMUX */
#define RG_UNPACK_EXT_PHR_CI(_ci, _mBuf, _ret) {\
   _ret = SUnpkU8((_ci), (_mBuf)); \
}

#define RG_UNPACK_EXT_PHR(_extPhr, _mBuf, _ret) {\
   _ret = SUnpkU8((_extPhr), (_mBuf)); \
}




/**
 * @brief Handles the extraction of SDU length.
 *
 * @details
 *
 *     Function: rgDUXExtSduLen
 *     
 *     This API handles the extraction of SDU length.
 *     
 *     Processing Steps: 
 *      - Extract the length based on the format.
 *
 *  @param[in]  Inst        inst
 *  @param[in]  *mBuf
 *  @param[out] sduLen
 *  @param[out] *err
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgDUXExtSduLen
(
Inst        inst,
Buffer      *mBuf,
U16         *sduLen,
RgErrInfo   *err
)
#else
PUBLIC S16 rgDUXExtSduLen(inst,mBuf, sduLen, err)
Inst        inst;
Buffer      *mBuf;
U16         *sduLen;
RgErrInfo   *err;
#endif
{
   U8    byte;
   U8    fmt;

   TRC2(rgDUXExtSduLen)

   if(SUnpkU8(&byte, mBuf) != ROK)
   {
      RLOG0(L_ERROR, "SUnpkU8 failed");
      err->errCause = RGERR_DUX_UNPACK_FAILURE;
      RETVALUE(RFAILED);
   }
   fmt = byte & 0x80;
   *sduLen = byte & 0x7F;
   if(fmt)
   {
      if(SUnpkU8(&byte,mBuf) != ROK)
      {
         RLOG0(L_ERROR, "SUnpkU8 failed");
         err->errCause = RGERR_DUX_UNPACK_FAILURE;
         RETVALUE(RFAILED);
      }
      *sduLen = (*sduLen << 8) | byte;
   }
   RETVALUE(ROK);
}

/**
 * @brief Handles the insertion of SDU in to PDU.
 *
 * @details
 *
 *     Function: rgDUXInsSdu
 *     
 *     This API handles the insertion of SDU in to PDU.
 *     
 *     Processing Steps: 
 *      - Append the sdu to the sduLst of pdu.
 *
 *  @param[in]  Inst        inst
 *  @param[out] *pdu
 *  @param[in]  lcId
 *  @param[in]  sduLen
 *  @param[out] *err
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 rgDUXInsSdu
(
Inst        inst,
RgMacPdu    *pdu,
U8          lcId,
U16         sduLen,
RgErrInfo   *err
)
#else
PRIVATE S16 rgDUXInsSdu(inst,pdu, lcId, sduLen, err)
Inst        inst;
RgMacPdu    *pdu;
U8          lcId;
U16         sduLen;
RgErrInfo   *err;
#endif
{
   S16         ret;
   RgMacSdu    *sdu = NULLP;

   TRC2(rgDUXInsSdu)

   RG_DUX_ALLOC(pdu, sizeof(RgMacSdu), sdu, ret);
   if(ret != ROK)
   {
      RLOG1(L_ERROR, "Allocation of RgSubHdr failed for LCID:%d",lcId);
      err->errCause = RGERR_DUX_MEM_EXHAUST;
      RETVALUE(RFAILED);
   }
   RG_INIT_SDU(sdu, lcId, sduLen);
   cmLListAdd2Tail(&pdu->sduLst, &sdu->sduLstEnt);
   RETVALUE(ROK);
}

/**
 * @brief Handles extracting the CE sub headers from the MAC PDU.
 *
 * @details
 *
 *     Function: rgDUXExtPadSubHdrs
 *     
 *     This API handles extracting the CE sub headers from the MAC PDU.
 *     
 *     Processing Steps: 
 *      - Extract the each ce sub header.
 *      - Append the extracted sub header to the subHdrLst.
 *
 *  @param[in]  Inst        inst
 *  @param[out]  *pdu
 *  @param[in]  *mBuf
 *  @param[out] *numPadSubHdrs
 *  @param[out] *unPkByte
 *  @param[out] *extnBit
 *  @param[out] *subHdrChkCmp
 *  @param[out] *err
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 rgDUXExtPadSubHdrs
(
Inst        inst,
RgMacPdu    *pdu,
Buffer      *mBuf,
U8          *numPadSubHdrs,
U8          *unPkByte,
U8          *extnBit,
U8          *subHdrChkCmp,
RgErrInfo   *err
)
#else
PRIVATE S16 rgDUXExtPadSubHdrs(inst,pdu, mBuf, numPadSubHdrs,
unPkByte, extnBit, subHdrChkCmp, err)
Inst        inst;
RgMacPdu    *pdu;
Buffer      *mBuf;
U8          *numPadSubHdrs;
U8          *unPkByte;
U8          *extnBit;
U8          *subHdrChkCmp;
RgErrInfo   *err;
#endif
{
   U8             byte;
   U8             lcId;

   TRC2(rgDUXExtPadSubHdrs)
   
   *numPadSubHdrs = 0;
   *subHdrChkCmp = TRUE;
   do
   {
      if(SUnpkU8(&byte,mBuf) != ROK)
      {
         RLOG0(L_ERROR, "SUnpkU8 failed");
         err->errCause = RGERR_DUX_UNPACK_FAILURE;
         RETVALUE(RFAILED);
      }

      /* Extract the lcid */
      RG_EXT_LCID(lcId, byte);
      RG_EXT_EXTN_BIT(*extnBit, byte);

      if(lcId == RG_PAD_LCID)
      {
         if(*extnBit)
         {
            ++(*numPadSubHdrs);      
            if(*numPadSubHdrs > RG_MAX_EXTN_PAD_SUBHDRS)
            {
               RLOG1(L_ERROR, "padSubHdrs received more than 2 for LCID:%d",lcId);
               err->errCause = RGERR_DUX_INV_PDU_RX;
               RETVALUE(RFAILED);      
            }
            continue;
         }
         else
         {
            if(*numPadSubHdrs)
            {
               RLOG1(L_ERROR, "invalid padSubHdrs received for LCID:%d",lcId);
               err->errCause = RGERR_DUX_INV_PDU_RX;
               RETVALUE(RFAILED);
            }
            break;
         }
      }
      else
      { 
         *unPkByte = byte;
         *subHdrChkCmp = FALSE;
         break;
      }
   }
   while(*extnBit);
   RETVALUE(ROK);
} /* rgDUXExtPadSubHdrs */

/**
 * @brief Handles extracting the CE sub headers from the MAC PDU.
 *
 * @details
 *
 *     Function: rgDUXExtCeSubHdrs
 *     
 *     This API handles extracting the CE sub headers from the MAC PDU.
 *     
 *     Processing Steps: 
 *      - Extract the each ce sub header.
 *      - Append the extracted sub header to the subHdrLst.
 *
 *  @param[in]  Inst        inst
 *  @param[out]  *pdu
 *  @param[in]  *mBuf
 *  @param[out] *numPadSubHdrs
 *  @param[out] *unPkByte
 *  @param[out] *extnBit
 *  @param[out] *subHdrChkCmp
 *  @param[out] *err
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 rgDUXExtCeSubHdrs
(
Inst        inst,
RgMacPdu    *pdu,
Buffer      *mBuf,
U8          *numPadSubHdrs,
U8          *unPkByte,
U8          *extnBit,
U8          *subHdrChkCmp,
RgErrInfo   *err
)
#else
PRIVATE S16 rgDUXExtCeSubHdrs(inst,pdu, mBuf, numPadSubHdrs,
unPkByte, extnBit, subHdrChkCmp, err)
Inst        inst;
RgMacPdu    *pdu;
Buffer      *mBuf;
U8          *numPadSubHdrs;
U8          *unPkByte;
U8          *extnBit;
U8          *subHdrChkCmp;
RgErrInfo   *err;
#endif
{
   S16            ret;
   U8             byte;
   U8             lcId;
   RgMacCeSubHdr  *ceSubHdr = NULLP;

   TRC2(rgDUXExtCeSubHdrs)
   
   *subHdrChkCmp = TRUE;
  
   byte = *unPkByte; 
   do
   {
      /* Extract the lcid */
      RG_EXT_LCID(lcId, byte);
      RG_EXT_EXTN_BIT(*extnBit, byte);

      if(lcId == RG_PAD_LCID)
      {
         if(*extnBit)
         {
            RLOG1(L_ERROR, "invalid padSubHdrs received LCID:%d",lcId);
            err->errCause = RGERR_DUX_INV_PDU_RX;
            RETVALUE(RFAILED);      
         }
         else
         {
            if(*numPadSubHdrs)
            {
               RLOG1(L_ERROR, "invalid padSubHdrs received  LCID:%d",lcId);
               err->errCause = RGERR_DUX_INV_PDU_RX;
               RETVALUE(RFAILED);
            }
            break;
         }
      }
   
      if ((lcId >= RG_EXT_PHR_LCID) && (lcId <= RG_LONG_BSR_LCID))
      {
         RG_DUX_ALLOC(pdu, sizeof(RgMacCeSubHdr), ceSubHdr, ret);
         if(ret != ROK)
         {
            RLOG1(L_ERROR, "Allocation of RgMacCeSubHdr failed  LCID:%d",lcId);
            err->errCause = RGERR_DUX_MEM_EXHAUST;
            RETVALUE(RFAILED);
         }
         RG_INIT_CE_SUBHDR(ceSubHdr, lcId);
         cmLListAdd2Tail(&pdu->ceLst, &ceSubHdr->subHdrLstEnt);

         if(*extnBit)
         {
            if(SUnpkU8(&byte,mBuf) != ROK)
            {
               RLOG1(L_ERROR, "SUnpkU8 failed  LCID:%d",lcId);
               err->errCause = RGERR_DUX_UNPACK_FAILURE;
               RETVALUE(RFAILED);
            }
         }
      }
      else
      {
         *unPkByte = byte;
         *subHdrChkCmp = FALSE;
         break;
      }
   }
   while(*extnBit);
   RETVALUE(ROK);
} /* rgDUXExtCeSubHdrs */

/**
 * @brief Handles extracting the SDU sub headers from the MAC PDU.
 *
 * @details
 *
 *     Function: rgDUXExtSduSubHdrs
 *     
 *     This API handles extracting the SDU sub headers from the MAC PDU.
 *     
 *     Processing Steps: 
 *      - Extract the each sdu sub header.
 *      - Append the extracted sub header to the sduLst.
 *
 *  @param[in]  Inst        inst
 *  @param[out]  *pdu
 *  @param[in]  *mBuf
 *  @param[in]  numPadSubHdrs
 *  @param[in]  unPkByte
 *  @param[out] *err
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 rgDUXExtSduSubHdrs
(
Inst        inst,
RgMacPdu    *pdu,
RgInfCeInfo *ceInfo,
Buffer      *mBuf,
U8          numPadSubHdrs,
U8          unPkByte,
RgErrInfo   *err
)
#else
PRIVATE S16 rgDUXExtSduSubHdrs(inst,pdu, ceInfo, mBuf,
numPadSubHdrs, unPkByte, err)
Inst        inst;
RgMacPdu    *pdu;
RgInfCeInfo *ceInfo;
Buffer      *mBuf;
U8          numPadSubHdrs;
U8          unPkByte;
RgErrInfo   *err;
#endif
{
   U8       byte;
   U8       lcId;
   U16      sduLen;
   Bool     extnBit;
   /*U8       numSduSubHdrs = 0;*/

   TRC2(rgDUXExtSduSubHdrs)
   
   byte = unPkByte;
   do 
   {
      /* Extract the lcid */
      RG_EXT_LCID(lcId, byte);
      RG_EXT_EXTN_BIT(extnBit, byte);

      if(lcId == RG_PAD_LCID)
      {
         if(extnBit)
         {
            RLOG1(L_ERROR,"invalid padSubHdrs received LCID:%d",lcId);
            err->errCause = RGERR_DUX_INV_PDU_RX;
            RETVALUE(RFAILED);      
         }
         else
         {
            if(numPadSubHdrs)
            {
               RLOG1(L_ERROR,"invalid padSubHdrs received LCID:%d",lcId);
               err->errCause = RGERR_DUX_INV_PDU_RX;
               RETVALUE(RFAILED);
            }
            break;
         }
      }

      if(lcId <= RG_DEDLC_MAX_LCID)
      {
        /* ++numSduSubHdrs;*/
         if(lcId == RG_CCCH_LCID)
         {
            ceInfo->bitMask |= RG_CCCH_SDU_PRSNT;
         }

         if(extnBit)
         {
            if(rgDUXExtSduLen(inst,mBuf, &sduLen, err) != ROK)
            {
               RETVALUE(RFAILED);
            }
            
            if(rgDUXInsSdu(inst,pdu, lcId, sduLen, err) != ROK)
            {
               RETVALUE(RFAILED);
            }
            if(SUnpkU8(&byte,mBuf) != ROK)
            {
               RLOG1(L_ERROR,"SUnpkU8 failed LCID:%d",lcId);
               err->errCause = RGERR_DUX_UNPACK_FAILURE;
               RETVALUE(RFAILED);
            }
            continue;
         }
         else
         {
            sduLen = 0;
            if(rgDUXInsSdu(inst,pdu, lcId, sduLen, err) != ROK)
            {
               RETVALUE(RFAILED);
            }
            break;
         }
      }
      else
      {
         RLOG1(L_ERROR, "Invalid LCID:%u received" ,lcId); 
         err->errCause = RGERR_DUX_INV_LCID_RX;
         RETVALUE(RFAILED);
      }
   }
   while(extnBit);
   RETVALUE(ROK);
} /* rgDUXExtSduSubHdrs */

/**
 * @brief Handles extracting the CEs from the MAC PDU.
 *
 * @details
 *
 *     Function: rgDUXExtCes
 *     
 *     This API handles extracting the CEs from the MAC PDU.
 *     
 *     Processing Steps: 
 *      - Based on the ce sub header extract the ce.
 *
 *  @param[in]  Inst        inst
 *  @param[in,out]  *pdu
 *  @param[in]  *mBuf
 *  @param[out] *err
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 rgDUXExtCes
(
Inst        inst,
RgMacPdu    *pdu,
RgInfCeInfo  *ceInfo,
Buffer       *mBuf,
RgErrInfo    *err
)
#else
PRIVATE S16 rgDUXExtCes(inst,pdu, ceInfo, mBuf, err)
Inst        inst;
RgMacPdu    *pdu;
RgInfCeInfo  *ceInfo;
Buffer       *mBuf;
RgErrInfo    *err;
#endif
{
   S16            ret;
   CmLList        *tmpNode;
   RgMacCeSubHdr  *ceSubHdr;

   TRC2(rgDUXExtCes)

   CM_LLIST_FIRST_NODE(&pdu->ceLst,tmpNode);
   
   while(tmpNode)
   {
      ceSubHdr = (RgMacCeSubHdr *)(tmpNode->node);
      switch(ceSubHdr->lcId)
      {
         case RG_EXT_PHR_LCID:
               {
                  U8 Ci;
                  U8 sCellIdx;
                  U8 extPhrOctet;
                  U8 extPhrPCmax;
                  RgInfExtPhrCEInfo *extPhr;

                  RG_UNPACK_EXT_PHR_CI(&Ci,mBuf,ret);
                  if(ret != ROK)
                  {
                     RLOG1(L_ERROR,"Unpacking of EXT PHR failed LCID:%d",ceSubHdr->lcId);
                     err->errCause = RGERR_DUX_UNPACK_FAILURE;
                     RETVALUE(RFAILED);
                  }

                  /* Not handling Type 2 PHR report as simultaneous PUSCH/PUCCH
                     is not supported as of now */
                  extPhr = &ceInfo->ces.extPhr;
                  extPhr->numServCells = 0;

                  /* Setting first BIT as PCELL field even though reserved is always
                     reported by UE */
                  Ci |= 0x1;
                  for (sCellIdx = 0; (Ci && sCellIdx < CM_LTE_MAX_CELLS); sCellIdx++)
                  {
                     if (Ci & 0x1)
                     {
                        extPhr->servCellPhr[extPhr->numServCells].sCellIdx = sCellIdx;
                        RG_UNPACK_EXT_PHR(&extPhrOctet,mBuf,ret);
                        if(ret != ROK)
                        {
                           RLOG1(L_ERROR,"Unpacking of EXT PHR failed LCID:%d",ceSubHdr->lcId);
                           err->errCause = RGERR_DUX_UNPACK_FAILURE;
                           RETVALUE(RFAILED);
                        }

                        /* extPhrOctet: Bits : 7 6 5 4 3 2 1 0
                         *                     P V x x x x x x
                         *                         <6x Bit phr>
                         */
                        /* P : P Back off applied or not */
                        extPhr->servCellPhr[extPhr->numServCells].phr = (extPhrOctet & 0x3F);
                        extPhr->servCellPhr[extPhr->numServCells].pBackOff = 
                           ((extPhrOctet >> 7) & 0x01);

                        /* V: Virtual PCMAX or Real Tx PCMAX */
                        if (extPhrOctet & 0x40)
                        {
                           extPhr->servCellPhr[extPhr->numServCells].pCmax = RG_REF_PCMAX;
                        }
                        else
                        {
                           RG_UNPACK_EXT_PHR(&extPhrPCmax,mBuf,ret);
                           if(ret != ROK)
                           {
                              RLOG1(L_ERROR,"Unpacking of EXT PHR failed LCID:%d",ceSubHdr->lcId);
                              err->errCause = RGERR_DUX_UNPACK_FAILURE;
                              RETVALUE(RFAILED);
                           }
                           extPhr->servCellPhr[extPhr->numServCells].pCmax = (extPhrPCmax & 0x3F);
                        }
                        extPhr->numServCells++;
                     }
                     Ci >>= 1;
                  }

                  ceInfo->bitMask |= RG_EXT_PHR_CE_PRSNT;
               }
               break;

         case RG_PHR_LCID:
               {
                  RG_UNPACK_PHR(&ceInfo->ces.phr,mBuf,ret);
                  if(ret != ROK)
                  {
                     RLOG1(L_ERROR,"Unpacking of PHR failed LCID:%d",ceSubHdr->lcId);
                     err->errCause = RGERR_DUX_UNPACK_FAILURE;
                     RETVALUE(RFAILED);
                  }
                  ceInfo->bitMask |= RG_PHR_CE_PRSNT;
               }
               break;
         case RG_TRUNC_BSR_LCID:
               {
                  RG_UNPACK_TRUNC_BSR(&ceInfo->ces.bsr.truncBsr,mBuf,ret);
                  if(ret != ROK)
                  {
                     RLOG1(L_ERROR,"Unpacking of Trunc BSR failed LCID:%d",ceSubHdr->lcId);
                     err->errCause = RGERR_DUX_UNPACK_FAILURE;
                     RETVALUE(RFAILED);
                  }
                  ceInfo->bitMask |= RG_TRUNC_BSR_CE_PRSNT;
              }
               break;
         case RG_SHORT_BSR_LCID:
               {
                  RG_UNPACK_SHORT_BSR(&ceInfo->ces.bsr.shortBsr,mBuf,ret);
                  if(ret != ROK)
                  {
                     RLOG1(L_ERROR,"Unpacking of Short BSR failed LCID:%d",ceSubHdr->lcId);
                     err->errCause = RGERR_DUX_UNPACK_FAILURE;
                     RETVALUE(RFAILED);
                  }
                  ceInfo->bitMask |= RG_SHORT_BSR_CE_PRSNT;
               }
               break;
         case RG_LONG_BSR_LCID:
               {
                  U8 longBsr[3] = {0}; /* KW_FIXX */
                  RG_UNPACK_LONG_BSR(longBsr,mBuf,ret);
                  if(ret != ROK)
                  {
                     RLOG1(L_ERROR,"Unpacking of Long BSR failed LCID:%d",ceSubHdr->lcId);
                     err->errCause = RGERR_DUX_UNPACK_FAILURE;
                     RETVALUE(RFAILED);
                  }
                  RG_EXT_BS(longBsr, 
                     ceInfo->ces.bsr.longBsr.bs1, 
                     ceInfo->ces.bsr.longBsr.bs2, 
                     ceInfo->ces.bsr.longBsr.bs3, 
                     ceInfo->ces.bsr.longBsr.bs4);
                  ceInfo->bitMask |= RG_LONG_BSR_CE_PRSNT;
               }
               break;
         case RG_CRNTI_LCID:
               {
                  RG_UNPACK_CRNTI(&ceInfo->ces.cRnti,mBuf,ret);
                  if(ret != ROK)
                  {
                     RLOG1(L_ERROR,"Unpacking of C-RNTI failed LCID:%d",ceSubHdr->lcId);
                     err->errCause = RGERR_DUX_UNPACK_FAILURE;
                     RETVALUE(RFAILED);
                  }
                  ceInfo->bitMask |= RG_CRNTI_CE_PRSNT;
               }
               break;
         default:
            RLOG1(L_ERROR, "Invalid LCID:%u received",ceSubHdr->lcId); 
            err->errCause = RGERR_DUX_INV_LCID_RX;
            RETVALUE(RFAILED);
      }
      CM_LLIST_NEXT_NODE(&pdu->ceLst,tmpNode);
   }
   RETVALUE(ROK);
} /* rgDUXExtCes  */


/**
 * @brief Handles extracting the SDU from the MAC PDU.
 *
 * @details
 *
 *     Function: rgDUXExtSdus
 *     
 *     This API handles extracting the SDU corresponding to a logical channel.
 *     
 *     Processing Steps: 
 *      - Based on the length stored in the sub header extract the SDU.
 *
 *  @param[in]  Inst        inst
 *  @param[in,out]  *pdu
 *  @param[in]  *mBuf
 *  @param[out] *err
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE S16 rgDUXExtSdus
(
Inst        inst,
RgMacPdu    *pdu,
Buffer      *mBuf,
RgErrInfo   *err
)
#else
PRIVATE S16 rgDUXExtSdus(inst,pdu, mBuf, err)
Inst        inst;
RgMacPdu    *pdu;
Buffer      *mBuf;
RgErrInfo   *err;
#endif
{
   S16         ret;
   Buffer      *tmpBuf1;
   Buffer      *tmpBuf2 = NULLP;
   CmLList     *tmpNode;
   RgMacSdu    *sdu;

   TRC2(rgDUXExtSdus)

   tmpBuf1 = mBuf;
   CM_LLIST_FIRST_NODE(&pdu->sduLst,tmpNode);
   
   while(tmpNode)
   {
      sdu = (RgMacSdu *)(tmpNode->node);

      if(!sdu->len)
      {
         MsgLen len = 0;
         if(SFndLenMsg(tmpBuf1,&len) != ROK)
         {
            RG_FREE_MSG(tmpBuf1);
            RLOG0(L_ERROR,"mBuf length check failed");
            err->errCause = RGERR_DUX_UNPACK_FAILURE;
            RETVALUE(RFAILED);
         }
         sdu->len = len;
      }

      ret = SSegMsg(tmpBuf1,sdu->len,&tmpBuf2);

      if((ret != ROK) && (!((ret == ROKDNA) && (tmpNode->next == NULLP))))
      {
         RG_FREE_MSG(tmpBuf1);
         RLOG0(L_ERROR,"SSegMsg failed");
         err->errCause = RGERR_DUX_RLC_PDU_CREAT_FAIL;
         RETVALUE(RFAILED);
      }

      sdu->mBuf = tmpBuf1;
      tmpBuf1 = tmpBuf2;

      CM_LLIST_NEXT_NODE(&pdu->sduLst,tmpNode);
   }
   RG_FREE_MSG(tmpBuf1);
   RETVALUE(ROK);
}   /* rgDUXExtSdus */

/**
 * @brief Handles de-multiplexing of the data recieved at MAC.
 *
 * @details
 *
 *     Function: rgDUXDemuxData
 *     
 *     This API handles de-multiplexing of the data recieved at MAC.
 *     
 *     Invoked by: rgTOMTfuDatInd of TOM 
 *     
 *     Processing Steps: 
 *      - De-multiplex the mBuf
 *
 *  @param[in]  Inst        inst
 *  @param[in]  *pdu 
 *  @param[in]  *mBuf 
 *  @param[out] *err 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgDUXDemuxData
(
Inst          inst,
RgMacPdu      *pdu,
RgInfCeInfo   *ceInfo,
Buffer        **mBuf,
RgErrInfo     *err
)
#else
PUBLIC S16 rgDUXDemuxData(inst,pdu, ceInfo, mBuf, err)
Inst          inst;
RgMacPdu      *pdu;
RgInfCeInfo   *ceInfo;
Buffer        **mBuf;
RgErrInfo     *err;
#endif
{
   U8          numPadSubHdrs = 0;
   U8          unPkByte;
   U8          subHdrChkCmp = TRUE;
   U8          extnBit = TRUE;

   TRC2(rgDUXDemuxData)

   ceInfo->bitMask = 0x0000;

   /* Initialize the ce sub header list */
   cmLListInit(&pdu->ceLst);

   /* Initialize the sdu list */
   cmLListInit(&pdu->sduLst);

   /* Extract the pad sub headers */
   if(rgDUXExtPadSubHdrs(inst,pdu, *mBuf, &numPadSubHdrs, 
         &unPkByte, &extnBit, &subHdrChkCmp, err) != ROK)
   {
      RG_FREE_MSG(*mBuf);	      
      
      RLOG0(L_ERROR, "Failed to extract pad sub headers");
      RETVALUE(RFAILED);
   }

   if((!extnBit) && (subHdrChkCmp))
   {
      RG_FREE_MSG(*mBuf);	      
      RETVALUE(ROK);
   } 

   /* Extract the ce sub headers */
   if(rgDUXExtCeSubHdrs(inst,pdu, *mBuf,&numPadSubHdrs, 
         &unPkByte, &extnBit, &subHdrChkCmp, err) != ROK)
   {
      RG_FREE_MSG(*mBuf);	      
      
      RLOG0(L_ERROR, "failed to Extract the ce sub headers");
      RETVALUE(RFAILED);
   }

   if((!extnBit) && (subHdrChkCmp))
   {
      /* Extract the ces */
      if(rgDUXExtCes(inst,pdu, ceInfo, *mBuf, err) != ROK)
      {
         RG_FREE_MSG(*mBuf);	      
         
         RLOG0(L_ERROR, "failed to Extract the ces");
         RETVALUE(RFAILED);
      }
      RG_FREE_MSG(*mBuf);	      
      RETVALUE(ROK);
   }

   /* Extract the sdu sub headers */
   if(rgDUXExtSduSubHdrs(inst,pdu, ceInfo, *mBuf, 
         numPadSubHdrs, unPkByte, err) != ROK)
   {
      RG_FREE_MSG(*mBuf);	      
      
      RLOG0(L_ERROR, "failed to Extract the sdu sub headers");
      RETVALUE(RFAILED);
   }

   /* Extract the ces */
   if(rgDUXExtCes(inst,pdu, ceInfo, *mBuf, err) != ROK)
   {
      RG_FREE_MSG(*mBuf);	      
      
      RLOG0(L_ERROR, " failed to Extract the ces");
      RETVALUE(RFAILED);
   }

   /* Extract the sdus */
   if(rgDUXExtSdus(inst,pdu, *mBuf, err) != ROK)
   {
      /* Fix : syed rgDUXExtSdus would have segmented mBuf and hence
       * will be responsible for freeing mBuf */
      *mBuf = NULLP;
      RLOG0(L_ERROR, "failed to Extract the sdus");
      RETVALUE(RFAILED);
   }
   *mBuf = NULLP;
   RETVALUE(ROK);
}  /* rgDUXDemuxData */

/**********************************************************************
 
         End of file:     gk_dux.c@@/main/3 - Sat Jul 30 02:21:27 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sd   1. Initial Release.
/main/2      ---     sd   1. LTE MAC 2.1 release
/main/3      ---        gvj  1. Updated for LTE MAC Rel 3.1         
$SID$        ---     rt   1. LTE MAC 4.1 release
*********************************************************************91*/
