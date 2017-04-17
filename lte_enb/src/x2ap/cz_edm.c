


/**********************************************************************

     Name:     LTE-X2AP Layer 
  
     Type:     C Source file
  
     Desc:     This file handles the encoding/decoding of the X2AP messages.

     File:     cz_edm.c

     Sid:      tr_edm.c@@/main/2 - Tue Aug 30 18:36:10 2011

     Prg:       

**********************************************************************/
/* Header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_pasn.h"       /* common per asn.1                */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "sct.h"           /* SCT interface defines           */
#include "czt.h"           /* CZT interface defines           */
#include "lcz.h"           /* X2AP Layer management           */
#include "cz.h"            /* X2AP layer defines              */
#include "cz_err.h"        /* X2AP - error */

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_inet.x"       /* Common socket library           */
#include "cm_pasn.x"       /* common per asn.1                */
#include "sct.x"           /* SCT interface defines           */
#include "czt.x"           /* CZT interface structures        */
#include "lcz.x"           /* X2AP Layer management           */
#include "cz.x"            /* X2AP layer structures           */

/* local defines */

/* local typedefs */
   EXTERN CmPAsnElmDef *czMsgDb[];
/* local externs */
 
/* forward references */

/** @defgroup edmmodule X2AP Encoder/Decoder Module
 *  @{
 */
/**********************************************************************/
/* Public Function Definitions */
/**********************************************************************/

/**
 * @brief Encodes the X2AP message in ASN.1 format.
 * 
 * @details This function encodes the X2AP message into the buffer 
 * to be sent to the peer. Uses CM_PASN library for encoding.
 *
 * @param[in]  mem          Memory Region and pool info
 * @param[in]  x2apPdu      PDU to be encoded
 * @param[out] mBuf         Encoded buffer
 *
 * @return 
 *  - ROK        - If the message is successfully encoded.
 *  - RFAILED    - If the encoding is unsuccessful due to any failure.
*/

#ifdef ANSI
PUBLIC S16 czEdmEncode
(
Mem          *mem,
CztX2AP_PDU  *x2apPdu,
Buffer       **mBuf
)
#else
PUBLIC S16 czEdmEncode (mem, x2apPdu, mBuf)
Mem          *mem;
CztX2AP_PDU  *x2apPdu;
Buffer       **mBuf;
#endif
{
   U8        dbgFlag;
   CmPAsnErr asnErr;
   S16       ret;
   U32       len=0;
   
   CZ_TRC2(czEdmEncode)

   dbgFlag = TRUE;

   
   CZ_ALLOCMBUF(mBuf);
   if (NULLP == mBuf)
   {
      CZ_DBG_ERROR((CZ_PRNT_BUF, "Message Buffer Not allocated \n"));

      CZ_RETVALUE(RFAILED);
   }

   /* Initialize the PASN Error code */ 
   asnErr.errCode = 0;
  
   ret = cmPAsnEncMsg((TknU8 *)x2apPdu, CM_PASN_USE_MBUF, 
                      (Void *)(*mBuf), CZ_PASN_VER_ZERO, 
                      (CmPAsnElmDef **)czMsgDb, &asnErr, 
                      &len, dbgFlag, FALSE );
  
   if (ret == RFAILED)
   {
      /* It's an ASN.1 Error */
      CZ_DBG_ERROR((CZ_PRNT_BUF,
        "Transfer Syntax Error:Encoding failed, Reason %d\n",asnErr.errCode)); 
      
      CZ_FREEMBUF(*mBuf);
      CZ_RETVALUE(RFAILED);
  }

   CZ_RETVALUE(ROK);
} /* end of czEncode */

/* cz001.101 : CR fixes */

/**
 * @brief Decodes the X2AP message using the cm_pasn library.
 * 
 * @details  This function decodes the buffer received from the lower layer
 * into X2AP event to be sent the X2AP user. 
 
 * @param[in] uiEvnt Decoded X2AP PDU
 * @param[in] sMem   Memory control pointer
 * @param[in] mBuf   Buffer to be decoded
 * @param[out] err   ASN error if decoding fails 
 *
 * @return 
 *  - ROK        - If the message is successfully decoded.
 *  - RFAILED    - If the decoding is unsuccessful due to any failure.
*/
#ifdef ANSI
PUBLIC S16 czEdmDecode
(
CztEvnt   **uiEvnt,
Mem       *sMem, 
Buffer    *mBuf,
CmPAsnErr *err
)
#else
PUBLIC S16 czEdmDecode (uiEvnt, sMem, mBuf, err)
CztEvnt   **uiEvnt;
Mem       *sMem; 
Buffer    *mBuf;
CmPAsnErr *err;       
#endif
{
   U32          numDecOct; /* number of octets decoded */
   S16          ret;       /* return value from different procedures */
   U8           dbgFlag;
   U32          msgLen;
   CztEvnt      *event = NULLP;
      

   CZ_TRC2(czEdmDecode)
                   
   dbgFlag = FALSE;

      
   /* Initialize the PASN Error code */ 
   CZ_ALLOCEVNT((Ptr *)&event, sizeof(CztEvnt), sMem);
   if(NULLP == event)
   {
      CZ_DBG_FATAL((CZ_PRNT_BUF,"Allocation of CzEvnt Failed \n"));
      CZ_FREEMBUF(mBuf);
      CZ_RETVALUE(RFAILED);
   }
      
   err->errCode = 0;
   msgLen = 0;
  
   ret = (cmPAsnDecMsg((Void *)&(event->pdu), CM_PASN_USE_MBUF, 
                  (Void **)&mBuf, &numDecOct, CZ_PASN_VER_ZERO, 
                  (CmPAsnElmDef **)czMsgDb, CM_PASN_GEN_ERR, err, 
                  msgLen, (CmMemListCp *)event, dbgFlag));
  
   if (ret == RFAILED)
   {
      /* It's an ASN.1 Error */
      CZ_DBG_INFO((CZ_PRNT_BUF,
            " Syntax Error : Decoding failed, Reason %d\n", 
                               err->errCode)); 
      /* CZ_FREEEVNT(event);    */
      /* CZ_RETVALUE(RFAILED); */
   }

   CZ_FREEMBUF(mBuf);
   *uiEvnt = event;
   
   CZ_RETVALUE(ret);
} /* end of czEdmDecode */


/** @} */

/**********************************************************************
  
         End of file:     tr_edm.c@@/main/2 - Tue Aug 30 18:36:10 2011
   
**********************************************************************/
 
/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---        ds              1. LTE-X2AP Initial Release.
            cz001.101   mm              1. CR Fixes, Memory Leak fixes.
/main/2      ---        pt              1. LTE-X2AP 3.1 release.
*********************************************************************91*/
