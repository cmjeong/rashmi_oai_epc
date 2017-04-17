

/********************************************************************20**
  
        Name:    CKW user interface
    
        Type:    C file
  
        Desc:    This file Contains the Acceptance Register code
                  for CKW Interface
 
        File:    kwac_ckwreg.c

        Sid:      kwac_ckwreg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:23 2014
  
        Prg:     chakrapani
  
*********************************************************************21*/


/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_ckw.h"      /* CKW Acceptance defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_ckw.x"      /* CKW Acceptance defines */


PRIVATE CmXtaCmd kwAcCkwSimpleCmd[] =
{
   {"tapa.ckw.bndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCkwBndReq, NULLP,
      "CKW Bind Request"
   },
 
   {"tapa.ckw.bndcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCkwBndCfm, NULLP,
      "CKW Bind Confirm"
   },
 
   {"tapa.ckw.ubndreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCkwUbndReq, NULLP,
      "CKW Unbind Request"
   },
 
   {"tapa.ckw.cfgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCkwCfgReq, NULLP,
      "CKW Configuration Request"
   },
 
   {"tapa.ckw.cfgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCkwCfgCfm, NULLP,
      "CKW Configuration Confirm"
   },
 
   {"tapa.ckw.ueidchgreq", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCkwUeIdChgReq, NULLP,
      "CKW Configuration Request"
   },
 
   {"tapa.ckw.ueidchgcfm", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCkwUeIdChgCfm, NULLP,
      "CKW Configuration Confirm"
   },
 
   {"tapa.ckw.mapdlul", CMXTA_TYPE_LEAF, CMXTA_SUBTYPE_OTHER, kwAcHdlCkwMapDlUl, NULLP,
      "CKW KwAcCb Mapping between Down link an uplink to loopback the PDUs"
   },

};
 
/*
*
*       Fun:   kwAcCkwInit
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  kwac_ckwreg.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcCkwInit
(
Void
)
#else
PUBLIC S16 kwAcCkwInit()
#endif
{
   U16   cnt;
   S16   ret;
 
   TRC2(kwAcCkwInit);
 
   cnt = sizeof(kwAcCkwSimpleCmd)/sizeof(kwAcCkwSimpleCmd[0]);
 
   if ((ret = cmXtaXmlLoadSimpleCmd(cnt, kwAcCkwSimpleCmd)) != ROK)
      RETVALUE(ret);
 
   RETVALUE(ROK);
}/* kwAcCkwInit */
 
/*
*
*       Fun:   kwAcCkwDeInit
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  kwac_ckwreg.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcCkwDeInit
(
Void
)
#else
PUBLIC S16 kwAcCkwDeInit()
#endif
{
   TRC2(kwAcCkwDeInit);
 
   kwAcUtlCkwCQMakeNull(&(kwAcCb.ckwCb.cfgReq));

   RETVALUE(ROK);
}/* kwAcCkwDeInit --*/

/* Temporarily keeping this code to run the acceptance  
 * Start here*/

/*
*
*       Fun:   SPkF32
*
*       Desc:  This function packs an 32 bit ieee-754 format float value into a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SPkF32
(
F32 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkF32(val, mBuf)
F32 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16  ret;                /* return code */
   S8   tmpArray[15];       /* temporary array */
#ifdef FCSPKINT             /* backward compatibility, packing order */
   S32  tIdx = 14;          /* counters */
   S32  kIdx = 0;           /* counters */
   S8   pkArray[15];        /* packing array */
#endif /*FCSPKINT*/
  
   TRC1(SPkF32)

   sprintf(tmpArray, "%.7e", val);

#ifndef FCSPKINT            /* backward compatibility, packing order */
   ret = SAddPreMsgMult((Data*)tmpArray, (MsgLen) 15, mBuf);
#else
   while(tIdx >= 0)
   {
      pkArray[kIdx] = tmpArray[tIdx];
      tIdx--; kIdx++;
   }
   ret = SAddPreMsgMult((Data*)pkArray, (MsgLen) 15, mBuf);
#endif


#if (ERRCLASS & ERRCLS_ADD_RES)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_ADD_RES, ESS248, (ErrVal)ret, "SAddPreMsgMult() failed");
#endif
   RETVALUE(ret);
} /* end of SPkF32 */

/*
*
*       Fun:   SPkF64
*
*       Desc:  This function packs an 64 bit ieee-754 format float value into a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPkF64
(
F64 val,                    /* value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPkF64(val, mBuf)
F64 val;                    /* value */
Buffer *mBuf;               /* message buffer */
#endif
{

   S16  ret;                /* return code */
   S8   tmpArray[25];       /* temporary array */
#ifdef FCSPKINT             /* backward compatibility, packing order */
   S32  tIdx = 24;          /* counters */
   S32  kIdx = 0;           /* counters */
   S8   pkArray[25];        /* packing array */
#endif /*FCSPKINT*/
  
   TRC1(SPkF64)

   sprintf(tmpArray, "%.16le", val);

#ifndef FCSPKINT            /* backward compatibility, packing order */
   ret = SAddPreMsgMult((Data*)tmpArray, (MsgLen) 25, mBuf);
#else
   while(tIdx >= 0)
   {
      pkArray[kIdx] = tmpArray[tIdx];
      tIdx--; kIdx++;
   }
   ret = SAddPreMsgMult((Data*)pkArray, (MsgLen) 25, mBuf);
#endif


#if (ERRCLASS & ERRCLS_ADD_RES)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_ADD_RES, ESS249, (ErrVal)ret, "SAddPreMsgMult() failed");
#endif
   RETVALUE(ret);

} /* end of SPkF64 */

/*
*
*       Fun:   SUnpkF32
*
*       Desc:  This function unpacks an 32 bit ieee-754 format float value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SUnpkF32
(
F32 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkF32(val, mBuf)
F32 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{
   S16 ret;                 /* return code */
   S8 tmpArray[15];         /* temporary array */
#ifndef FCSPKINT            /* backward compatibility, packing order */
   S32 tIdx = 14;           /* temparory array index */
   S32 kIdx = 0;            /* unpacking array index */
   S8 unpkArray[15];        /* unpacking array */
#endif /* FCSPKINT */

   TRC1(SUnpkF32)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!val)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS262, ERRZERO, "SUnpkF32 : Null value");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ret = SRemPreMsgMult((Data*)tmpArray, (MsgLen) 15, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_DEBUG, ESS263, (ErrVal)ret, "SRemPreMsgMult() failed");
#endif

#ifndef FCSPKINT            /* backward compatibility, packing order */
   while(tIdx >= 0)
   {
      unpkArray[kIdx] = tmpArray[tIdx];
      tIdx--; kIdx++;
   }
   sscanf(unpkArray, "%f", val);
#else
   sscanf(tmpArray, "%f", val);
#endif

   RETVALUE(ret);

} /* end of SUnpkF32 */

/*
*
*       Fun:   SUnpkF64
*
*       Desc:  This function unpacks an 64 bit ieee-754 format float value from a message.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_pack.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SUnpkF64
(
F64 *val,                   /* pointer to value */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SUnpkF64(val, mBuf)
F64 *val;                   /* pointer to value */
Buffer *mBuf;               /* message buffer */
#endif
{

   S16 ret;                 /* return code */
   S8 tmpArray[25];         /* temporary array */
#ifndef FCSPKINT            /* backward compatibility, packing order */
   S32 tIdx = 24;           /* temparory array index */
   S32 kIdx = 0;            /* unpacking array index */
   S8 unpkArray[25];        /* unpacking array */
#endif /* FCSPKINT */

   TRC1(SUnpkF64)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!val)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS264, ERRZERO, "SUnpkF64 : Null value");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ret = SRemPreMsgMult((Data*)tmpArray, (MsgLen) 25, mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      SSLOGERROR(ERRCLS_DEBUG, ESS265, (ErrVal)ret, "SRemPreMsgMult() failed");
#endif

#ifndef FCSPKINT            /* backward compatibility, packing order */
   while(tIdx >= 0)
   {
      unpkArray[kIdx] = tmpArray[tIdx];
      tIdx--; kIdx++;
   }
   sscanf(unpkArray, "%lf", val);
#else
   sscanf(tmpArray, "%lf", val);
#endif

   RETVALUE(ret);

} /* end of SUnpkF64 */
/* Temporarily keeping this code to run the acceptance  
 * End here*/

  
/********************************************************************30**
         End of file:     kwac_ckwreg.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:23 2014
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
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
*********************************************************************91*/

