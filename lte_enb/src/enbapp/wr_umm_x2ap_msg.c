
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_umm_x2ap_msg.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="UMM";
static int RLOG_FILE_ID=78;


static int RLOG_MODULE_ID=32;

#include "wr.h"        
#include "wr_emm.h"        
#include "wr_umm.h"        
#include "czt_asn.x"
#include "wr_ifm_x2ap.h"
#include "wr_umm_x2ap_msg.h"

PUBLIC S16 wrX2apFillCause
(
CztCause                     *ie,
WrUmmMsgCause                *cause
)
{
   ie->choice.pres    = PRSNT_NODEF;
   ie->choice.val     = cause->causeTyp;
   switch(cause->causeTyp)
   {
      case WR_CAUSE_RADIONW:
         wrFillTknU32(&(ie->val.radioNw), cause->causeVal);
         break;
      case WR_CAUSE_TRANSPORT:
         wrFillTknU32(&(ie->val.transport), cause->causeVal);
         break;
      case WR_CAUSE_PROTOCOL:
         wrFillTknU32(&(ie->val.protocol), cause->causeVal);
         break;
      case WR_CAUSE_MISC:
         wrFillTknU32(&(ie->val.misc), cause->causeVal);
         break;
   }
   RETVALUE(ROK);
}

PUBLIC S16 wrX2apFillTnlAddr
(
CztEvnt                      *evnt,
CmTptAddr                    *lclAddr,
CztTportLyrAddr              *ie
)
{
   U16                       len = 0;
   U16                       cnt = 0;
  

   ie->pres = TRUE;
   if (CM_TPTADDR_IPV4 == lclAddr->type)
   {
      /* length in bits */
      len = WR_UMM_IPV4_LEN;
      WR_FILL_BIT_STR_VAL((*ie), len, lclAddr->u.ipv4TptAddr.address,
                   evnt);
   }
   else if(CM_TPTADDR_IPV6 == lclAddr->type)
   {
      /* length in bits */
      ie->len  = WR_UMM_IPV6_LEN;
      /* IPv6 length in bytes */
      len = WR_IPV6_ADDR_LEN;
      WR_GET_MEM((&evnt->memCp), len, (&ie->val));
      for (cnt = 0; cnt < len; cnt++)
      {
         ie->val[cnt] = (U8)(lclAddr->u.ipv6TptAddr.ipv6NetAddr[cnt]);
      }
   }
   else
   {
      RLOG1(L_ERROR, "Invalid Tunnel Address Type[%d]",lclAddr->type);
   }
   RETVALUE(ROK);
}

PUBLIC S16 wrX2apGetTnlAddr
(
CmTptAddr                    *addr,
CztTportLyrAddr              *ie
)
{
   U8                        shiftBits = 0;
   U16                       indx = 0;
   U32                       addrMask = 0;
   switch(ie->len)
   {
      case WR_UMM_IPV4_LEN:
      {
         addr->type = CM_TPTADDR_IPV4;
         addr->u.ipv4TptAddr.port = WR_DFLT_EGTP_PORT; 

         /* copy 4bytes into the U32 */
         shiftBits = ie->len / 8;
         addrMask = 0xFF000000;
         for(indx = 0; indx < 4; indx++)
         {
            shiftBits--;
            addr->u.ipv4TptAddr.address |=
               ((U32)(ie->val[indx] << (8 * shiftBits)) & addrMask);
            addrMask = addrMask >> 8;
         }
         break;
      }
      case WR_UMM_IPV6_LEN:
      {
         addr->type = CM_TPTADDR_IPV6;
         addr->u.ipv6TptAddr.port = WR_DFLT_EGTP_PORT;
         for (indx = 0; indx < 16; indx++)
         {
            addr->u.ipv6TptAddr.ipv6NetAddr[indx] = ie->val[indx];
         }
         break;
      }
   }
   RETVALUE(ROK);
}

PUBLIC S16 wrX2apGetTnlId
(
U32                       *tnlId,
CztGTP_TEI                *remTeIdStr
)
{
   U8                        shiftBits = 0;
   U16                       indx = 0;
   U32                       addrMask = 0;

   shiftBits = (remTeIdStr->len);
   addrMask = 0xFF000000;
   for(indx = 0;indx < remTeIdStr->len;indx++)
   {
      shiftBits--;
      (*tnlId) |= ((U32)(remTeIdStr->val[indx] << (8*shiftBits)) & addrMask);
      addrMask = addrMask>>8;
   }
   RETVALUE(RFAILED);
}

/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
