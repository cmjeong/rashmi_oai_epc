


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      rgac_edutl.c@@/main/3 - Sat Jul 30 02:20:54 2011
  
     Prg:      ps
  
**********************************************************************/

/** @file rg_dhm.c
@brief APIs related to Downlink HARQ.
*/

/* This file shall contain the encoding decoding functions for MAC PDUs. */

#include "rg.h"
#include "rgac_acc.x"

PRIVATE S16 rgAcRaAddHeader ARGS((
         RgAcRarPdu    *datPdu,
         CmMemListCp   *memCp));

PRIVATE S16 rgAcAddHeader ARGS((
         RgAcDatPdu    *datPdu,
         CmMemListCp   *memCp));

PRIVATE S16 rgAcAddCE ARGS((
         RgAcDatPdu    *datPdu,
         CmMemListCp   *memCp));

PRIVATE S16 rgAcAddRarPdu ARGS((
         RgAcRarPdu    *rarPdu,
         CmMemListCp   *memCp));

PRIVATE S16 rgAcUtlEncodeCe ARGS((
         U8            lcId,
         RgAcCEorSDU   *ce,
         Buffer        *ceBuf,
         Buffer        *hdrBuf,
         Bool          isLast,
         Bool          invEBit));

/** @brief This function is used to decode a buffer coming from MAC into and
 * encoding/decoding structure RgAcEdEvent. This function first decodes all the subHeaders, till the last one is
 * found. Having found the last subheaders, it looks for any Control elements
 * following the headers. Once all the CEs have been decoded, it looks for any
 * PDUs following it. 
 * @param [in] inBuf This is the incoming buffer that needs decoding. 
 * @param [out] outEvnt This is the structure that the buffer is decoded into, this is allocated by this function but needs to be freed by the user. 
 * @return ROK/RFAILED.
 */
#ifdef ANSI
PUBLIC S16 rgAcUtlDecodeDataPdu 
(
 Buffer        *inBuf,
 RgAcEdEvent   **outEvnt,
 U16           *padBytes
 )
#else
PUBLIC S16 rgAcUtlDecodeDataPdu (inBuf, outEvnt, padBytes)
 Buffer        *inBuf;
 RgAcEdEvent   **outEvnt;
 U16           *padBytes;
#endif
{
   S16            ret;
   Mem            evntMem;
   RgAcDatPdu     *datPdu;
   Data           byte;
   U8             lcId;
   U8             mask;
   Bool           isLastHdr;
   RgAcSubHeader  *subHdr;
   U8             shortLength;
   U16            longLength;
   U16            secondByte;
   U8             i;
   CmLList        *subHdrNode;

   TRC2(rgAcUtlDecodeDataPdu);

   isLastHdr   = FALSE;

   /* Here is a brief idea of we shall be doing in the following section of the
    * code.
    * 1. Run through buffer looking for subHeaders, till we get to the end of
    * the headers. Also populating the event structure as we go along. 
    * 2. Run through the remaining buffer, first looking for Control elements
    * and populating the event structure, and then the PDUs.
    */

   /* Lets allocate the outEvnt structure here */
   evntMem.region = cmXtaCb.init.region;
   evntMem.pool   = cmXtaCb.init.pool;
   if (cmAllocEvnt (sizeof (RgAcEdEvent), RG_BLKSZ, &evntMem, (Ptr*)outEvnt) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcUtlDecodeDataPdu(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   (*outEvnt)->type = RG_ACC_DAT_PDU;
   datPdu = &(((*outEvnt)->u.datPdu));
   cmLListInit (&(datPdu->subHdrs));
   cmLListInit (&(datPdu->ceOrSdus));


   /* Start going through the sub headers one by one till we encounter E=1*/
   for (i = 0; i < RG_ACC_TFU_MAX_SUBHDRS; i++)
   {

      /* Lets examine the first one byte of the header */
      ret = SRemPreMsg(&byte, inBuf);
      if (ret != ROK)
         goto errorHandle;
      mask = 32;  /* setting the 6th bit to 1 to see if extension bit is set
                     or not. */
      if (!(mask & byte))
         isLastHdr = TRUE;

      if (rgAcAddHeader (datPdu, &((*outEvnt)->memCp)) != ROK)
         goto errorHandle;

      subHdrNode = datPdu->subHdrs.last;
      subHdr = (RgAcSubHeader*)subHdrNode->node;

      mask = 31; /* Zero out the first 3 bits */
      lcId = (byte & mask);

      /* If last header then there is no second byte to consider */
      if (isLastHdr == TRUE)
      {
         subHdr->type                  = RG_ACC_LAST_SUBHDR;
         subHdr->lcId                  = lcId;
         subHdr->u.lastSubHdr.isLast   = TRUE;
         break;
      }

      /* It could be that this header corresponds to a Control element, the
       * following check if for that purpose
       */
#ifndef LTE_ADV
      if ((lcId == RG_ACC_PADDING_CE) ||
            (lcId == RG_ACC_DRX_CMD_CE) ||
            (lcId == RG_ACC_TIMING_ADV_CE) ||
            (lcId == RG_ACC_CONT_RES_CE))
#else
      if ((lcId == RG_ACC_PADDING_CE) ||
            (lcId == RG_ACC_DRX_CMD_CE) ||
            (lcId == RG_ACC_TIMING_ADV_CE) ||
            (lcId == RG_ACC_CONT_RES_CE) ||
            (lcId == RG_ACC_SCELL_ACT_CE))

#endif
      {
         subHdr->type                = RG_ACC_LAST_SUBHDR;
         subHdr->lcId                = lcId;
         continue;
      }

      /* now we need to figure out the type of this sub header */
      /* Lets examine the second byte of the header */
      ret = SRemPreMsg(&byte, inBuf);
      if (ret != ROK)
         goto errorHandle;

      mask = 128; /* need to check the "F" bit */
      if (mask & byte)
      {
         subHdr->type               = RG_ACC_LONG_SUBHDR;
         subHdr->lcId               = lcId;
         mask                       = 127;
         longLength                 = mask & byte;
         longLength                 = longLength << 8;
         /* Lets examine the third byte of the header */
         ret = SRemPreMsg(&byte, inBuf);
         if (ret != ROK)
            RETVALUE(ret);
         secondByte = byte;
         longLength = longLength | secondByte;
         /* Fill in the header structure */
         subHdr->u.longSubHdr.length  = longLength;
      } /* End of isLong */
      else
      {
         subHdr->type                  = RG_ACC_SHORT_SUBHDR;
         subHdr->lcId                  = lcId;
         mask                          = 127;
         shortLength                   = mask & byte;
         /* Fill in the header structure */
         subHdr->u.shortSubHdr.length  = shortLength;
      } /* End of !isLong */

   } /* end of for */

   /* Now we have all the subheaders in place, next step is to look for any
    * control elements 
    */
   if (rgAcUtlDecodeCEorPDU (&((*outEvnt)->memCp), datPdu, inBuf, padBytes) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcUtlDecodeDataPdu(): Unable to decode control elements\n"));
      goto errorHandle;
   }
   (Void)SPutMsg (inBuf);
   RETVALUE(ROK);
errorHandle:
   if (datPdu)
      cmFreeMem((Ptr)datPdu);
   RETVALUE(ret);
} /* end of rgAcUtlDecodeDataPdu */

 /** @brief This function decodes the buffer, into MAC control elements or MAC
  * PDUs.
  * @param  memCp a pointer to the CmMemListCp
  * @param  datPdu a pointer to the RgAcDatPdu, containing the decoded
  * information.
  * @param  inBuf the buffer to be decoded. 
  * @return ROK/RFAILED
  */
#ifdef ANSI
PUBLIC S16 rgAcUtlDecodeCEorPDU
(
 CmMemListCp      *memCp,
 RgAcDatPdu       *datPdu,
 Buffer           *inBuf,
 U16              *padBytes
)
#else
PUBLIC S16 rgAcUtlDecodeCEorPDU (memCp, datPdu, inBuf, padBytes)
 CmMemListCp      *memCp;
 RgAcDatPdu       *datPdu;
 Buffer           *inBuf;
 U16              *padBytes;
#endif
{
   S16 ret;
   RgAcSubHeader  *subHdr;
   RgAcCE         *rgCE;
   RgAcCEorSDU    *ce;
   CmLList        *node;
   CmLList        *ceNode;
   MsgLen      length;

   TRC2(rgAcUtlDecodeCEorPDU);

   /* Lets run through all the headers looking for specific LCID, if it does
    * match, we shall pick up the following PDU from the buffer and move on. 
    */
   node = datPdu->subHdrs.first;
   while (node)
   {
      subHdr = (RgAcSubHeader*)node->node;
      switch (subHdr->lcId)
      {
         case RG_ACC_CONT_RES_CE:
            /* Its a contention resolution CE we need the next 6 bytes of
             * data.
             */
            if (rgAcAddCE (datPdu, memCp) != ROK)
               RETVALUE(CMXTA_ERR_RSRC);
            ceNode = datPdu->ceOrSdus.last;
            ce = (RgAcCEorSDU*)ceNode->node;
            ce->isCE = TRUE;
            rgCE = &(ce->u.rgAcCE);
            rgCE->type  = RG_ACC_CONT_RES_CE;   /* LCID shall double up as type also */

            /* Remove the 6 bytes from the buffer onto the CE */
            ret = SRemPreMsgMult (rgCE->u.rgAcContRes.contRes, 
                  (MsgLen)6, inBuf);

                  break;
         case RG_ACC_TIMING_ADV_CE:
            if (rgAcAddCE (datPdu, memCp) != ROK)
               RETVALUE(CMXTA_ERR_RSRC);
            ceNode = datPdu->ceOrSdus.last;
            ce = (RgAcCEorSDU*)ceNode->node;
            ce->isCE = TRUE;
            rgCE = &(ce->u.rgAcCE);
            rgCE->type  = RG_ACC_TIMING_ADV_CE;   /* LCID shall double up as type also */
            /* Remove the 1 byte from the buffer onto the CE */
            ret = SRemPreMsgMult (&(rgCE->u.rgAcTimingAdv.timingAdv), 
                  (MsgLen)1, inBuf);
            break;
#ifdef LTE_ADV
         case RG_ACC_SCELL_ACT_CE:
            if (rgAcAddCE (datPdu, memCp) != ROK)
               RETVALUE(CMXTA_ERR_RSRC);
            ceNode = datPdu->ceOrSdus.last;
            ce = (RgAcCEorSDU*)ceNode->node;
            ce->isCE = TRUE;
            rgCE = &(ce->u.rgAcCE);
            rgCE->type  = RG_ACC_SCELL_ACT_CE;   /* LCID shall double up as type also */
            /* Remove the 1 byte from the buffer onto the CE */
            ret = SRemPreMsgMult (&(rgCE->u.rgSCellAct.sCellAct), 
                  (MsgLen)1, inBuf);
            break;
#endif
         case RG_ACC_DRX_CMD_CE:
            if (rgAcAddCE (datPdu, memCp) != ROK)
               RETVALUE(CMXTA_ERR_RSRC);
            ceNode = datPdu->ceOrSdus.last;
            ce = (RgAcCEorSDU*)ceNode->node;
            ce->isCE = TRUE;
            rgCE = &(ce->u.rgAcCE);
            rgCE->type  = RG_ACC_DRX_CMD_CE;   /* LCID shall double up as type also */
            break;
         case RG_ACC_PADDING_CE:
            /* If this is the last sub header then the remaining bytes are all
             * padding bytes. */
            if ((subHdr->type == RG_ACC_LAST_SUBHDR) &&
                  (subHdr->u.lastSubHdr.isLast))
            {
               length = 0;
               SFndLenMsg(inBuf, &length);
               if (length)
               {
                  ret = SRemPreMsgMult (NULLP, (MsgLen)length, inBuf);
               }
               *padBytes = length;
            }
            break;
         default:
            /* This implies its a PDU that we would just add to the buffer */
            if (rgAcAddCE (datPdu, memCp) != ROK)
               RETVALUE(CMXTA_ERR_RSRC);
            ceNode = datPdu->ceOrSdus.last;
            ce = (RgAcCEorSDU*)ceNode->node;
            ce->isCE = FALSE;
            /* Remove the 6 bytes from the buffer onto the CE */
            length = 0;
            switch (subHdr->type)
            {
               case RG_ACC_LAST_SUBHDR:
                  /* Length is what ever is left */
                  SFndLenMsg(inBuf, &length);
                  break;
               case RG_ACC_SHORT_SUBHDR:
                  length = subHdr->u.shortSubHdr.length;
                  break;
               case RG_ACC_LONG_SUBHDR:
                  length = subHdr->u.longSubHdr.length;
                  break;
            }
            /* Currently we just plan to rip off the message of the specified
             * length
             */
            ret = SRemPreMsgMult (NULLP, (MsgLen)length, inBuf);
            break;
      }
      node = node->next;
   } /* end of while */

   RETVALUE(ROK);
} /* end of rgAcUtlDecodeCEorPDU */

 /** @brief This function Adds a new subheader to the list of sub headers in the
  * dat PDU.
  * @param  datPdu The PDU to which we need to addition. 
  * @param  memCp A pointer to the CmMemListCp
  * @return ROK/RFAILED
  */
#ifdef ANSI
PRIVATE S16 rgAcRaAddHeader 
(
 RgAcRarPdu    *rarPdu,
 CmMemListCp   *memCp
 )
#else
PRIVATE S16 rgAcRaAddHeader (rarPdu, memCp)
 RgAcRarPdu    *rarPdu;
 CmMemListCp   *memCp;
#endif
{
   S16            ret;
   RgAcRaSubHdr   *newRaHdr;

   TRC2(rgAcAddHeader)

   /* Now we can allocate the specific header */
   if ((ret = cmGetMem (memCp, sizeof(RgAcRaSubHdr), 
            (Ptr *)&(newRaHdr))) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcAddHeader(): resource error\n"));
      RETVALUE(ret);
   }
   newRaHdr->lnk.node = (PTR)newRaHdr;
   cmLListAdd2Tail (&(rarPdu->raSubHdrs), &(newRaHdr->lnk));
   RETVALUE(ret);
} /* end of rgAcAddHeader */


 /** @brief This function Adds a new subheader to the list of sub headers in the
  * dat PDU.
  * @param  datPdu The PDU to which we need to addition. 
  * @param  memCp A pointer to the CmMemListCp
  * @return ROK/RFAILED
  */
#ifdef ANSI
PRIVATE S16 rgAcAddHeader 
(
 RgAcDatPdu    *datPdu,
 CmMemListCp   *memCp
 )
#else
PRIVATE S16 rgAcAddHeader (datPdu, memCp)
 RgAcDatPdu    *datPdu;
 CmMemListCp   *memCp;
#endif
{
   S16            ret;
   RgAcSubHeader  *newHdr;

   TRC2(rgAcAddHeader)

   if ((ret = cmGetMem (memCp, sizeof(RgAcSubHeader), 
            (Ptr *)&(newHdr))) != ROK) 
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcAddHeader(): resource error\n"));
      RETVALUE(ret);
   }
   newHdr->lnk.node = (PTR)newHdr;
   cmLListAdd2Tail (&(datPdu->subHdrs), &(newHdr->lnk));
   RETVALUE(ret);
} /* end of rgAcAddHeader */



 /** @brief This function Adds another Control element to the list of control
  * elements, present in the Data PDU. 
  * @param  datPdu the PDU to which the CE is to be added. 
  * @param  memCp a pointer to the CmMemListCp
  * @return ROK/RFAILED
  */
#ifdef ANSI
PRIVATE S16 rgAcAddCE 
(
 RgAcDatPdu    *datPdu,
 CmMemListCp   *memCp
 )
#else
PRIVATE S16 rgAcAddCE (datPdu, memCp)
 RgAcDatPdu    *datPdu;
 CmMemListCp   *memCp;
#endif
{
   S16            ret;
   RgAcCEorSDU    *ce;

   TRC2(rgAcAddHeader)

   
   if ((ret = cmGetMem (memCp, sizeof(RgAcCEorSDU), 
            (Ptr *)&(ce))) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcAddCE(): resource error\n"));
      RETVALUE(ret);
   }
   ce->lnk.node = (PTR)ce;
   cmLListAdd2Tail (&(datPdu->ceOrSdus), &(ce->lnk));
   RETVALUE(ret);
} /* end of rgAcAddCE */


 /** @brief This function Decodes the Random Access Response PDU into the event
  * structure. 
  * @param  inBuf This is the buffer that has to be decoded.
  * @param  outEvnt This is the event structure that the buffer is decoded into
  * @return ROK/RFAILED
  */
#ifdef ANSI
PUBLIC S16 rgAcUtlDecodeRarPdu 
(
 Buffer        *inBuf,
 RgAcEdEvent   **outEvnt,
 Bool          *biPres
 )
#else
PUBLIC S16 rgAcUtlDecodeRarPdu (inBuf, outEvnt, biPres)
 Buffer        *inBuf;
 RgAcEdEvent   **outEvnt;
 Bool          *biPres;
#endif
{
   S16            ret;
   Mem            evntMem;
   RgAcRarPdu     *rarPdu;
   U8             i;
   Data           byte;
   U8             mask;
   Bool           isLastHdr;
   RgAcRaSubHdr    *subHdr;
   CmLList        *raSubHdrNode;

   TRC2(rgAcUtlDecodeRarPdu)

   isLastHdr   = FALSE;

   /* Here is a brief idea of we shall be doing in the following section of the
    * code.
    * 1. We shall go through all the sub headers and store them in the event.
    * 2. We shall go through the RAR PDUs and store them in the structure. 
    */

   /* Lets allocate the outEvnt structure here */
   evntMem.region = cmXtaCb.init.region;
   evntMem.pool   = cmXtaCb.init.pool;
   if (cmAllocEvnt (sizeof (RgAcEdEvent), 2000, &evntMem, (Ptr*)outEvnt) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcUtlDecodeRarPdu(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   (*outEvnt)->type = RG_ACC_RAR_PDU;
   rarPdu = &(((*outEvnt)->u.rarPdu));
   cmLListInit (&(rarPdu->raSubHdrs));
   cmLListInit (&(rarPdu->rarPdus));

   /* Start going through the sub headers one by one till we encounter E=1*/
   for (i = 0; ((i < RG_ACC_TFU_MAX_SUBHDRS) && (isLastHdr == FALSE)); i++)
   {

      /* Lets examine the first one byte of the header */
      ret = SRemPreMsg(&byte, inBuf);
      if (ret != ROK)
         RETVALUE(ret);
      mask = 128;  /* setting the 7 bit to 1 to see if extension bit is set
                     or not. */
      if (!(mask & byte))
         isLastHdr = TRUE;

      if (rgAcRaAddHeader (rarPdu, &((*outEvnt)->memCp)) != ROK)
         RETVALUE(CMXTA_ERR_RSRC);

      raSubHdrNode = rarPdu->raSubHdrs.last;
      subHdr = (RgAcRaSubHdr*)raSubHdrNode->node;

      mask = 64; /* set the 6th bit to 1 */
      if (byte & mask)
      {
         /* This one contains a RAPID */
         subHdr->isBi = FALSE;
         mask = 63;
         subHdr->u.rapId = (byte & mask);
      }
      else
      {
         /* This is the one that contains the BI and possibly the last one */
         *biPres = TRUE;
         subHdr->isBi = TRUE;
         mask = 15;
         subHdr->u.bi = (byte & mask);
      }
      if (isLastHdr)
         break;
   } /* end of for */

   /* Now we have all the subheaders in place, next step is to look for any
    * control elements 
    */
   if ((ret = rgAcUtlDecodeRarHdrs (&((*outEvnt)->memCp), rarPdu, inBuf)) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcUtlDecodeRarPdu(): Unable to decode RAR PDUs\n"));
      RETVALUE(ret);
   }

   (Void)SPutMsg (inBuf);

   RETVALUE(ROK);
} /* end of rgAcUtlDecodeRarPdu */

 /** @brief This function Decodes the RAR PDU
  * @param  memCp A pointer to the CmMemListCp
  * @param  rarPdu The RAR PDU that is decoded from the buffer.
  * @param  inBuf The buffer to be decoded.
  * @return ROK/RFAILED
  */
#ifdef ANSI
PUBLIC S16 rgAcUtlDecodeRarHdrs
(
 CmMemListCp      *memCp,
 RgAcRarPdu       *rarPdu,
 Buffer           *inBuf
)
#else
PUBLIC S16 rgAcUtlDecodeRarHdrs (memCp, rarPdu, inBuf)
 CmMemListCp      *memCp;
 RgAcRarPdu       *rarPdu;
 Buffer           *inBuf;
#endif
{
   S16            ret;
   U8             mask;
   U8             firstByte;
   U8             secondByte;
   U8             thirdByte;
   U8             fourthByte;
   U8             temp;
   U8             timingAdv;
   U32            ulGrant;
   U16            scndTmp;
   U16            tempCrnti;
   RgAcRarHdrs    *pdu;
   RgAcRaSubHdr   *raSubHdr;   /*!< A Dynamic list of RA sub headers */
   CmLList        *node;
   CmLList        *pduNode;

   TRC2(rgAcUtlDecodeRarHdrs)

   ret         = ROK;

   /* There are no CEs, we only have fixed length RAR PDUs.
    */
   node = rarPdu->raSubHdrs.first;
   while (node)
   {
      raSubHdr    = (RgAcRaSubHdr *)node->node;
      /* First check is if it is a BI or not, if it is then we quitely exit as
       * this has to be the last.
       */
      if (raSubHdr->isBi == TRUE)
      {
         node = node->next;
         continue;
      }

      /* First we need to extract TA command - this is of 11 bits it seems. */
      ret = SRemPreMsg (&firstByte, inBuf);
      if (ret != ROK)
         RETVALUE(ret);
      ret = SRemPreMsg (&secondByte, inBuf);
      if (ret != ROK)
         RETVALUE(ret);
      /* We have two bytes we need to add to for the Timing advance */
      if (rgAcAddRarPdu (rarPdu, memCp) != ROK)
         RETVALUE(CMXTA_ERR_RSRC);
      /* Zero out the first "R" Bit */
      mask = 127;
      firstByte = firstByte & mask;
      /* Zero out the last 4 bits */
      mask = 240;
      temp = secondByte & mask;
      temp = temp >> 4;
      timingAdv = firstByte;
      timingAdv = timingAdv << 4;
      timingAdv = timingAdv | temp;

      /* now we need the UL Grant part of it */
      ret = SRemPreMsg (&thirdByte, inBuf);
      if (ret != ROK)
         RETVALUE(ret);

      ret = SRemPreMsg (&fourthByte, inBuf);
      if (ret != ROK)
         RETVALUE(ret);
      /* Zero out the 4 MSBs */
      mask = 15; 
      temp = secondByte & mask;
      ulGrant = 0;
      ulGrant = temp;
      ulGrant = ulGrant << 16;

      scndTmp = thirdByte;
      scndTmp = scndTmp << 8;
      ulGrant = ulGrant | scndTmp;
      ulGrant = ulGrant | fourthByte;

      /* Now we need to temp crnti from the last two bytes */
      ret = SRemPreMsg (&firstByte, inBuf);
      if (ret != ROK)
         RETVALUE(ret);

      ret = SRemPreMsg (&secondByte, inBuf);
      if (ret != ROK)
         RETVALUE(ret);

      scndTmp = firstByte;
      scndTmp = scndTmp << 8;
      tempCrnti = scndTmp;
      tempCrnti = tempCrnti | secondByte;

      pduNode = rarPdu->rarPdus.last;
      pdu = (RgAcRarHdrs *)pduNode->node;
      pdu->timingAdv = timingAdv;
      pdu->ulGrant   = ulGrant;
      pdu->tempCrnti = tempCrnti;
      node = node->next;
   } /* end of while */

   RETVALUE(ROK);
} /* end of rgAcUtlDecodeRarHdrs */


 /** @brief This function Adds a new RAR PDU to the existing list of RAR PDUs.
  * @param  rarPdu The PDU to which a new PDU is to be added.
  * @param  memCp A pointer to the CmMemListCp
  * @return ROK/RFAILED
  */
#ifdef ANSI
PRIVATE S16 rgAcAddRarPdu 
(
 RgAcRarPdu    *rarPdu,
 CmMemListCp   *memCp
 )
#else
PRIVATE S16 rgAcAddRarPdu (rarPdu, memCp)
 RgAcRarPdu    *rarPdu;
 CmMemListCp   *memCp;
#endif
{
   S16            ret;
   RgAcRarHdrs    *newPdu;

   TRC2(rgAcAddRarPdu)

   /* Now we can allocate the specific header */
   if ((ret = cmGetMem (memCp, sizeof(RgAcRarHdrs), 
            (Ptr *)&(newPdu))) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcAddRarPdu(): resource error\n"));
      RETVALUE(ret);
   }
   newPdu->lnk.node = (PTR)newPdu;
   cmLListAdd2Tail (&(rarPdu->rarPdus), &(newPdu->lnk));
   RETVALUE(ret);
} /* end of rgAcAddRarPdu */


 /** @brief This function Encodes a DATA PDU from an event structure into a
  * buffer. 
  * @param  inEvnt The input event that is to be encoded.
  * @param  outBuf The buffer that contains the encoded message.
  * @return ROK/RFAILED
  */
#ifdef ANSI
PUBLIC S16 rgAcUtlEncodeDatPdu 
(
 RgAcEdEvent   *inEvnt,
 Buffer        **outBuf,
 Bool          swpCESDU,
 Bool          invEBit,
 Bool          invLen,
 S16           dedBufIdx
 )
#else
PUBLIC S16 rgAcUtlEncodeDatPdu (inEvnt, outBuf,  swpCESDU, invEBit, invLen, dedBufIdx)
 RgAcEdEvent   *inEvnt;
 Buffer        **outBuf;
 Bool          swpCESDU;
 Bool          invEBit;
 Bool          invLen;
 S16           dedBufIdx;
#endif
{
   S16            ret;
   RgAcDatPdu     *datPdu;
   RgAcSubHeader  *subHdr;
   RgAcCEorSDU    *ce;
   Buffer         *hdrBuf = NULLP;
   Buffer         *ceBuf = NULLP;
   CmLList        *subHdrNode = NULLP;
   CmLList        *ceNode = NULLP;
   Bool           isLast;
   MsgLen            len;
   U8             shortHdr[2];
   U8             longHdr[3];
   U8             oneByte;

   TRC2(rgAcUtlEncodeDatPdu)
   datPdu = &(inEvnt->u.datPdu);
   isLast = FALSE;

   /* Lets see how can we encode the event into a buffer. The plan should be
    * fairly simple - we can just keep on adding stuff i.e. the subheaders first
    * then the control elements in the order they come.
    */

   if (SGetMsg (cmXtaCb.init.region, cmXtaCb.init.pool, &hdrBuf) != ROK)
   {
      CMXTA_DBG_FATAL((_cmxtap, "rgAcUtlEncodeDatPdu(): resource error\n"));
      RETVALUE (CMXTA_ERR_RSRC);
   }

   if (SGetMsg (cmXtaCb.init.region, cmXtaCb.init.pool, &ceBuf) != ROK)
   {
      (Void)SPutMsg(hdrBuf);
      CMXTA_DBG_FATAL((_cmxtap, "rgAcUtlEncodeDatPdu(): resource error\n"));
      RETVALUE (CMXTA_ERR_RSRC);
   }
   if (swpCESDU)
   {
      subHdrNode = datPdu->subHdrs.last;
      ceNode     = datPdu->ceOrSdus.last;
   }
   else
   {
      subHdrNode = datPdu->subHdrs.first;
      ceNode     = datPdu->ceOrSdus.first;
   }
   while ((subHdrNode != NULLP) && (ceNode != NULLP))
   {
      subHdr = (RgAcSubHeader *)subHdrNode->node;
      ce = (RgAcCEorSDU *)ceNode->node;

      if (swpCESDU)
      {
         if (subHdrNode == datPdu->subHdrs.first)
         {
            subHdr->type = RG_ACC_LAST_SUBHDR;
            subHdr->u.lastSubHdr.isLast = TRUE;
         }
      }
      else
      {
         if (subHdrNode == datPdu->subHdrs.last)
         {
            subHdr->type = RG_ACC_LAST_SUBHDR;
            subHdr->u.lastSubHdr.isLast = TRUE;
         }
      }
      switch (subHdr->type)
      {
         case RG_ACC_LAST_SUBHDR:
            /* This happens to be the last header, i.e we need to wrap it up
             * after this point. 
             */
            if (subHdr->u.lastSubHdr.isLast == TRUE)
               isLast = TRUE;
            /* If its not the last subheader it must correspond to a Control
             * element.
             */
            if (swpCESDU)
               ret = rgAcUtlEncodeCe (subHdr->lcId, ce, ceBuf, hdrBuf, isLast, invEBit);
            else
               ret = rgAcUtlEncodeCe (subHdr->lcId, ce, ceBuf, hdrBuf, isLast, invEBit);
            if (ret != ROK)
            {
               (Void)SPutMsg(hdrBuf);
               (Void)SPutMsg(ceBuf);
               RETVALUE(ret);
            }
            break;
         case RG_ACC_SHORT_SUBHDR:
            len = subHdr->u.shortSubHdr.length;
            if (invLen == TRUE)
            {
            }
            else
            {
               if((ret = SAddPstMsgMult ((Data *)&junkData, len, ceBuf)) != ROK)
               {
                  (Void)SPutMsg(hdrBuf);
                  (Void)SPutMsg(ceBuf);
                  RETVALUE(ret);
               }
            }
            shortHdr[0] = subHdr->lcId | 32;
            shortHdr[1] = 0;
            shortHdr[1] = (U8)len;
            ret = SAddPstMsgMult ((Data*)shortHdr, (MsgLen) 2, hdrBuf);
            break;
         case RG_ACC_LONG_SUBHDR:
            len = subHdr->u.longSubHdr.length;
            if((ret = SAddPstMsgMult ((Data *)&junkData, (MsgLen)len, ceBuf)) != ROK)
            {
               (Void)SPutMsg(hdrBuf);
               (Void)SPutMsg(ceBuf);
               RETVALUE(ret);
            }
            longHdr[0] = 0;
            longHdr[0] = subHdr->lcId | 32;
            longHdr[1] = 128;
            /* also set the "F" bit to 1 */
            /* Added the variable oneByte. Insure will shut up as we
             * now shift oneByte instead shifting complete len of 16 bits */ 
            oneByte = len >> 8; 
            longHdr[1] = longHdr[1] | oneByte;
            longHdr[2] = 0;
            longHdr[2] = longHdr[2] |  (U8)((len >> 8) & 0xff);
            ret = SAddPstMsgMult ((Data*)longHdr, (MsgLen)3, hdrBuf);
            break;
         default:
            ret = RFAILED;
            break;
      } /* end of switch */
      if (dedBufIdx != -1)
      {
         if (rgAccCb.dedBuf[dedBufIdx] != NULLP)
         {
            SPutMsg(rgAccCb.dedBuf[dedBufIdx]);
            rgAccCb.dedBuf[dedBufIdx] = NULLP;
         }
         if ((SCpyMsgMsg (ceBuf, CMXTA_TSTREG, 
                     CMXTA_TSTPOOL, &(rgAccCb.dedBuf[dedBufIdx]))) != ROK)
         {
            CMXTA_DBG_ERR((_cmxtap, "resource error\n"));
            RETVALUE(RFAILED);
         }
      }
      /* If swapped we need to travese backwards */
      if (swpCESDU)
      {
         subHdrNode = subHdrNode->prev;
         ceNode = ceNode->prev;
      }
      else
      {
         subHdrNode = subHdrNode->next;
         ceNode = ceNode->next;
      }
   } /* end of while */

   /* So at this point point we have pretty much encoded the headers and the
    * CE/PDUs separately, lets just add them together and get the final thingy. 
    */
   ret = SCatMsg (hdrBuf, ceBuf, M1M2);
   (Void)SPutMsg(ceBuf);
   if (ret != ROK)
   {
      (Void)SPutMsg(hdrBuf);
      RETVALUE(RFAILED);
   }
   /* Assign the new buffer to the output */
   *outBuf = hdrBuf;
   RETVALUE(ROK);

} /* end of rgAcUtlEncodeDatPdu */
 
 /** @brief This function Encodes a MAC control element into a buffer.
  * @param  lcId the logical channel id used to identify the CE.
  * @param  ce the control element to be encoded.
  * @param  ceBuf The buffer to be used to encode the CE.
  * @return ROK/RFAILED
  */
#ifdef ANSI
PRIVATE S16 rgAcUtlEncodeCe 
(
 U8            lcId,
 RgAcCEorSDU   *ce,
 Buffer        *ceBuf,
 Buffer        *hdrBuf,
 Bool          isLast,
 Bool          invEBit
 )
#else
PRIVATE S16 rgAcUtlEncodeCe (lcId, ce, ceBuf, hdrBuf, isLast, invEBit)
 U8            lcId;
 RgAcCEorSDU   *ce;
 Buffer        *ceBuf;
 Buffer        *hdrBuf;
 Bool          isLast;
 Bool          invEBit;
#endif
{
   S16    ret;
   U8     data;
   U8     mask;
   U8     crnti[2];
   U8     bufferSize;
   U8     bufSize1;
   U8     bufSize2;
   U8     bufSize3;
   U8     bufSize4;
   U8     bo[3];
   U8     tmp;
   U8     hdr;
   U8     extPhrBuff[13]; /* 1 byte for CI, 2 Bytes for Type 2, 5 * 2 for Type 1 for all serving cells = 13 */
   RgAcExtPhr * rgAcExtPhr;
   U8     Ci = 0;
   U8     idx;
   U8     extPhrByteCnt;

   TRC2(rgAcUtlEncodeCe)
   ret         = ROK;

   switch (lcId)
   {
      case RG_ACC_EXT_PWR_HDR_CE:
         rgAcExtPhr = &(ce->u.rgAcCE.u.rgAcExtPhr);

         if (rgAcExtPhr->phrInfo[1].phr != 0xFF)
         {
            /* Both PCELL and SCELL Idx 1 phr present */
            /* SCELL idx 0 is reserved and should be set to 0 */
            Ci = 0x2;
         }
         else
         {
            /* Only PCELL phr present */
            /* SCELL idx 0 is reserved and should be set to 0 */
            Ci = 0x0;
         }
         ret = SAddPstMsg (Ci, ceBuf);

         /* Ext PHR for PCELL */
         extPhrBuff[0] = (rgAcExtPhr->phrInfo[0].phr & 0x3F);
         extPhrByteCnt = 1;
         if (rgAcExtPhr->phrInfo[0].pCMax != 0xFF)
         {
            /* REF PCMAX */
            extPhrBuff[1] = (rgAcExtPhr->phrInfo[0].pCMax & 0x3F);
            extPhrByteCnt++;
         }
         else
         {
            extPhrBuff[0] |= (1<<6); /* setting V to 1 */
         }

         /* Ext PHR for SCELL */
         extPhrBuff[2] = (rgAcExtPhr->phrInfo[1].phr & 0x3F);
         extPhrByteCnt++;

         if (rgAcExtPhr->phrInfo[1].pCMax != 0xFF)
         {
            /* REF PCMAX */
            extPhrBuff[3] = (rgAcExtPhr->phrInfo[1].pCMax & 0x3F);
            extPhrByteCnt++;
         }
         else
         {
            extPhrBuff[2] |= (1<<6); /* setting V to 1 */
         }


         ret = SAddPstMsgMult ((Data*)extPhrBuff, (MsgLen)extPhrByteCnt,  ceBuf);

         if (isLast == TRUE)
            hdr = lcId;
         else
            hdr = lcId | 32;
         ret = SAddPstMsg (hdr, hdrBuf);
         break;

      case RG_ACC_PWR_HDR_CE:
         data = ce->u.rgAcCE.u.rgAcPwrHdr.pwrHdr;
         ret = SAddPstMsg (data, ceBuf);
         if (isLast == TRUE)
            hdr = lcId;
         else
            hdr = lcId | 32;
         ret = SAddPstMsg (hdr, hdrBuf);
         break;
      case RG_ACC_CRNTI_CE:
         crnti[0] = (U8)(ce->u.rgAcCE.u.rgAcCrnti.crnti >> 8);
         crnti[1] = (U8)ce->u.rgAcCE.u.rgAcCrnti.crnti;
         ret = SAddPstMsgMult ((Data*)crnti, (MsgLen)2,  ceBuf);
         if (isLast == TRUE)
            hdr = lcId;
         else
            hdr = lcId | 32;
         ret = SAddPstMsg (hdr, hdrBuf);
         break;
      case RG_ACC_SBSR_CE:
      case RG_ACC_TBSR_CE:
         /* same for Short and truncated BSR */
         data = ce->u.rgAcCE.u.rgAcShortBSR.lcgId;
         data = data << 6;
         bufferSize = ce->u.rgAcCE.u.rgAcShortBSR.bufferSize;
         data = data | bufferSize;
         ret = SAddPstMsg (data, ceBuf);
         if (isLast == TRUE)
            hdr = lcId;
         else
            hdr = lcId | 32;
         ret = SAddPstMsg (hdr, hdrBuf);
         break;
      case RG_ACC_LBSR_CE:
         bufSize1 = ce->u.rgAcCE.u.rgAcLongBSR.bufferSize1;
         bufSize2 = ce->u.rgAcCE.u.rgAcLongBSR.bufferSize2;
         bufSize3 = ce->u.rgAcCE.u.rgAcLongBSR.bufferSize3;
         bufSize4 = ce->u.rgAcCE.u.rgAcLongBSR.bufferSize4;
         /* interested in 6 bits of bufSize1 */
         bo[0] = bufSize1 << 2;
         /* interested in first 2 bits of bufSize2 */
         tmp = bufSize2 >> 4;
         bo[0] = bo[0] | tmp;
         /* interested in last 4 bits of bufSize2 */
         mask = 240;
         bo[1] = ((bufSize2 << 4) & mask);
         /* interested in first 4 bits of bufSize3 */
         bo[1] = bo[1] | (bufSize3 >> 2);
         /* interested in last 2 bits of bufSize3 and all of bufSize4 */
         mask = 63;
         bo[2] = (bufSize3 << 6) | (bufSize4 & mask);
         /* Append to the last of the buffer */
         ret = SAddPstMsgMult ((Data*)bo, (MsgLen)3,  ceBuf);
         if (isLast == TRUE)
            hdr = lcId;
         else
            hdr = lcId | 32;
         ret = SAddPstMsg (hdr, hdrBuf);
         break;
      case RG_ACC_PADDING_CE:
         if (isLast == TRUE)
            hdr = lcId;
         else
            hdr = lcId | 32;
         ret = SAddPstMsg (hdr, hdrBuf);
         if (isLast == TRUE)
         {
            ret = SAddPstMsgMult ((Data*)&junkData, (MsgLen)ce->u.pduSize,  ceBuf);
         }
         break;
      default:
         if (isLast == TRUE)
         {
            if (invEBit == TRUE)
               hdr = lcId | 32;
            else
               hdr = lcId;
         }
         else
            hdr = lcId | 32;
         ret = SAddPstMsg (hdr, hdrBuf);
         if (ce->isCE != FALSE)
         {
            CMXTA_DBG_FATAL((_cmxtap, "rgAcUtlEncodeCe(): Invalid lcId \n"));
            RETVALUE(CMXTA_ERR_INT);
         }
         ret = SAddPstMsgMult ((Data*)&junkData, (MsgLen)ce->u.pduSize,  ceBuf);
         break;
   } /* end of switch */
   RETVALUE(ret);
} /* end of rgAcUtlEncodeCe */



/**********************************************************************
 
         End of file:     rgac_edutl.c@@/main/3 - Sat Jul 30 02:20:54 2011
 
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
/main/1      ---     ps              1. Initial Release.
/main/2      ---     ps              1. LTE MAC 2.1 release
          rg003.201  ns              1. Compilation fixed when TRACE enabled.
          rg009.201  nudupi          1. Insure fixes during SPS
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
$SID$        ---     rt              1. LTE MAC 4.1 release
*********************************************************************91*/
