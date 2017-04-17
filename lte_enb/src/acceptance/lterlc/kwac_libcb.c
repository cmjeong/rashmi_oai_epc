

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_libcb.c

     Sid:      kwac_libcb.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:28 2014

     Prg:     cp
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
#include "pju.h"           /* PJU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw_err.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_lib.h"      /* LIB Acceptance defines */
#include "kwac_acc.h"      /* Acceptance defines */

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
#include "pju.x"           /* PJU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"
/*#include "kw_pj_lib.x"      LIB */

#include "cm_xta.x"
#include "kwac_lib.x"      /* LIB Acceptance defines */
#include "kwac_acc.x"      /* Acceptance defines */

#ifdef KW_PDCP
/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to configure ROHC 
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to configure ROHC 
 *        per RB per UE.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdCmpInitReq 
(
Pst      *pst,                    /* post structure */
PjCmpCxt cmpCxt,                  /* Context for ROHC */
PjRohc   rohc,                    /* ROHC Config Info */
PTR      *cmpCxtId                /* FD pointer */
)
#else
PUBLIC S16 kwAcLibObdCmpInitReq(pst, cmpCxt, rohc, cmpCxtId)
Pst      *pst;                    /* post structure */
PjCmpCxt cmpCxt;                  /* Context for ROHC */
PjRohc   rohc;                    /* ROHC Config Info */
PTR      *cmpCxtId;               /* FD pointer */
#endif
{
   Bool  cmpInitFail = FALSE;

   TRC3(kwAcLibObdCmpInitReq);

   cmpInitFail =  kwAcCb.directive.cmpInitFail;
   kwAcCb.directive.cmpInitFail  =  FALSE;
#ifdef PJ_CMP_ASYNC
   CMXTA_ZERO(pst, sizeof(Pst));

   cmXtaGetPst(pst, ENTOC, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   cmPkLibObdCmpInitCfm(pst, cmpCxt, 0);
#else
   (*cmpCxtId) =  0;
#endif /* PJ_CMP_ASYNC */

   RETVALUE(ROK);
} /* end of kwAcLibObdCmpInitReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to configure Integration unit.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to configure
 *        Integrity protection / verification with the Integrity algo and key
 *        for SRBs of an UE.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdIntInitReq 
(
Pst      *pst,                    /* post structure */
PjSecCxt secCxt,                  /* Context for Intg protection/verification */
PjIntInfo intInfo,                /* Integrity Cfg Info */
PTR      *cxtId                   /* FD pointer */
)
#else
PUBLIC S16 kwAcLibObdIntInitReq(pst, secCxt, intInfo, cxtId)
Pst      *pst;                    /* post structure */
PjSecCxt secCxt;                  /* Context for Intg protection/verificatino */
PjIntInfo intInfo;                /* Integrity Cfg Info */
PTR      *cxtId;                  /* FD pointer */
#endif
{
   KwAcLibSecEnt   *intEnt;
   Bool  intInitFail = FALSE;

   TRC3(kwAcLibObdIntInitReq);

   intInitFail =  kwAcCb.directive.intInitFail;
   kwAcCb.directive.intInitFail  =  FALSE;

   PJ_ALLOC(intEnt, sizeof(KwAcLibSecEnt));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (intEnt == NULLP)
   {
      PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
            "kwAcLibObdIntInitReq: intEnt allocation Failed.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   intEnt->fd  = libCb.intCb.fdCounter ++; 
   intEnt->algoType  =  intInfo.algoType;
   cmMemcpy((U8 *)intEnt->key, (U8 *)intInfo.intKey, 16);
   intEnt->listEnt.node   = (PTR) intEnt;
   cmLListAdd2Tail(&libCb.intCb.intList, &intEnt->listEnt);

#ifdef PJ_SEC_ASYNC
   CMXTA_ZERO(pst, sizeof(Pst));

   cmXtaGetPst(pst, ENTOS, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   if (kwAcCb.nhCpjCb.intInitFail == FALSE)
   {
      cmPkLibObdIntInitCfm(pst, secCxt, intEnt->fd);
   }
#else
   (*cxtId) =  intEnt->fd;
#endif /* PJ_SEC_ASYNC */

   /* If intInitFail is TRUE then return RFAILED */
   if (kwAcCb.nhCpjCb.intInitFail)
   {
      kwAcCb.nhCpjCb.intInitFail = FALSE;
      RETVALUE(RFAILED);
   }
   else
   {
      RETVALUE(ROK);
   }

} /* end of kwAcLibObdIntInitReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to configure ciphering unit.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to configure
 *        ciphering / deciphering with the ciphering algo and key
 *        for SRBs of an UE.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdCpInitReq
(
Pst      *pst,                    /* post structure */
PjSecCxt secCxt,                  /* Context for Intg protection/verificatino */
U8       algoType,                /* Type of the algorithm */
U8       *cpKey,                   /* Control plane ciphering key */
PTR      *cxtId                   /* FD pointer */
)
#else
PUBLIC S16 kwAcLibObdCpInitReq(pst, secCxt, algoType, cpKey, cxtId)
Pst      *pst;                    /* post structure */
PjSecCxt secCxt;                  /* Context for Intg protection/verificatino */
U8       algoType;                /* Type of the algorithm */
U8       *cpKey;                   /* Control plane ciphering key */
PTR      *cxtId;                  /* FD pointer */
#endif
{
   KwAcLibSecEnt   *cipEnt;

   TRC3(kwAcLibObdCpInitReq)


   PJ_ALLOC(cipEnt, sizeof(KwAcLibSecEnt));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (cipEnt == NULLP)
   {
      PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
            "kwAcLibObdCpInitReq: cipEnt allocation Failed.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
   cipEnt->fd  = libCb.cipCb.fdCounter ++; 
   cmMemcpy((U8 *)cipEnt->key, (U8 *)cpKey, sizeof(16));
   cipEnt->algoType   =  algoType;
   cipEnt->listEnt.node   =  (PTR)cipEnt;
   cmLListAdd2Tail(&libCb.cipCb.cipList, &cipEnt->listEnt);

#ifdef PJ_SEC_ASYNC
   CMXTA_ZERO(pst, sizeof(Pst));
   
   cmXtaGetPst(pst, ENTOS, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   /* If cipInitFail is TRUE then return RFAILED */
   if (kwAcCb.nhCpjCb.cipInitFail)
   {
      kwAcCb.nhCpjCb.cipInitFail = FALSE;
      /* Do not return any cmPkLibObdCpInitCfm.
       * In this case obd_wait_tmr will expire and takes negative security
       * confirm to RRC.
       */
   }
   else
      cmPkLibObdCpInitCfm(pst, secCxt, cipEnt->fd);
#else
   (*cxtId) =  cipEnt->fd;
#endif /* PJ_SEC_ASYNC */

   RETVALUE(ROK);
} /* end of kwAcLibObdCpInitReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to configure ciphering unit.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to configure
 *        ciphering / deciphering with the ciphering algo and key
 *        for DRBs of an UE.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdUpInitReq
(
Pst      *pst,                    /* post structure */
PjSecCxt secCxt,                  /* Context for Intg protection/verificatino */
U8       algoType,                /* Type of the algorithm */
U8       *upKey,                   /* User plane ciphering key */
PTR      *cxtId                   /* FD pointer */
)
#else
PUBLIC S16 kwAcLibObdUpInitReq(pst,secCxt, algoType, upKey, cxtId)
Pst      *pst;                    /* post structure */
PjSecCxt secCxt;                  /* Context for Intg protection/verificatino */
U8       algoType;                /* Type of the algorithm */
U8       *upKey;                   /* User plane ciphering key */
PTR      *cxtId;                  /* FD pointer */
#endif
{
   KwAcLibSecEnt   *cipEnt;

   TRC3(kwAcLibObdUpInitReq)


   PJ_ALLOC(cipEnt, sizeof(KwAcLibSecEnt));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (cipEnt == NULLP)
   {
      PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
            "kwAcLibObdUpInitReq: cipEnt allocation Failed.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   cipEnt->fd  = libCb.cipCb.fdCounter ++; 
   cmMemcpy((U8 *)cipEnt->key, (U8 *)upKey, sizeof(16));
   cipEnt->listEnt.node   =  (PTR)cipEnt;
   cipEnt->algoType   =  algoType;
   cmLListAdd2Tail(&libCb.cipCb.cipList, &cipEnt->listEnt);

#ifdef PJ_SEC_ASYNC
   CMXTA_ZERO(pst, sizeof(Pst));
   
   cmXtaGetPst(pst, ENTOS, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
   cmPkLibObdUpInitCfm(pst, secCxt, cipEnt->fd);
#else
   (*cxtId) =  cipEnt->fd;
#endif /* PJ_SEC_ASYNC */

   /* If cipInitFail is TRUE then return RFAILED */
   if (kwAcCb.nhCpjCb.cipInitFail)
   {
      kwAcCb.nhCpjCb.cipInitFail = FALSE;
      RETVALUE(RFAILED);
   }
   else
   {
      RETVALUE(ROK);
   }

} /* end of kwAcLibObdUpInitReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to compress SDU.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to compress 
 *        SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdCmpReq 
(
Pst      *pst,                    /* post structure */
PTR      cmpCxtId,                /* Context Id for compression */
PjLibTrans *libTrans,             /* Transaction Id */
Buffer   *mBuf,                   /* SDU to be compressed */
Buffer   **opSdu                  /* Compressed SDU */
)
#else
PUBLIC S16 kwAcLibObdCmpReq(pst, cmpCxtId, libTrans, mBuf, opSdu)
Pst      *pst;                    /* post structure */
PTR      cmpCxtId;                /* Context Id for compression */
PjLibTrans *libTrans;             /* Transaction Id */
Buffer   *mBuf;                   /* SDU to be compressed */
Buffer   **opSdu;                 /* Compressed SDU */
#endif
{
   Buffer *outSdu;
   Bool  cmpFail = FALSE;

   TRC3(kwAcLibObdCmpReq)

   cmpFail =  kwAcCb.directive.cmpFail;
   kwAcCb.directive.cmpFail   =  FALSE;

   if ( cmpFail == FALSE )
   {
   SCpyMsgMsg(mBuf, kwCb.init.region, kwCb.init.pool, &outSdu);

   /* After copying to outSdu add COMP_BYTE and
    * delete mBuf only in case of PJ_CMP_ASYNC flag */
   SAddPreMsg(PJ_ACC_COMP_BYTE, outSdu);
   }
   else
      outSdu = NULLP;

#ifdef PJ_CMP_ASYNC
   {
      U32   id;
      Bool saveMsg;
      KwAcLibOutEnt *ent;

      id =  kwAcCb.directive.id;
      saveMsg =  kwAcCb.directive.saveCmpMsg;
      kwAcCb.directive.saveCmpMsg   =  FALSE;


      CMXTA_ZERO(pst, sizeof(Pst));

      cmXtaGetPst(pst, ENTOC, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
      if(saveMsg)
      {
         PJ_ALLOC(ent, sizeof(KwAcLibOutEnt));
#if (ERRCLASS & ERRCLS_ADD_RES)
         if (ent == NULLP)
         {
            PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
                  "kwAcLibObdCmpReq: ent allocation Failed.");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

         ent->fd  =  cmpCxtId;
         ent->id  =  id;
         cmMemcpy((U8 *)&ent->pst,(U8 *)pst,sizeof(Pst));
         cmMemcpy((U8 *)&ent->libTrans,(U8 *)libTrans,sizeof(PjLibTrans));
         ent->mBuf   =  (outSdu);
         kwAcLibUtlInsOutEnt(&libCb.compCb.compOutList, ent);
      }
      else
      {
         cmPkLibObdCmpCfm(pst, cmpCxtId, *libTrans, outSdu);
         SPutMsg(outSdu);
      }

      /* Delete mBuf only in case of PJ_CMP_ASYNC */
      PJ_FREE_BUF(mBuf);
   }
#else
   *opSdu   =  outSdu;
#endif /* PJ_CMP_ASYNC */

   RETVALUE(ROK);

} /* end of kwAcLibObdCmpReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to request for integrity
 *        protection
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to compress 
 *        SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdIntProtReq 
(
Pst        *pst,                    /* post structure */
PTR        cxtId,                   /* Context Id for compression */
PjSecInp   secInp,                 /* Input for Integrity protection */                  
PjLibTrans *libTrans,               /* Transaction Id */
Buffer     *mBuf,                   /* SDU to be compressed */
U32        *macI                    /* Message authentication code for the SDU */
)
#else
PUBLIC S16 kwAcLibObdIntProtReq(pst, cxtId, secInp, libTrans, mBuf, macI)
Pst        *pst;                    /* post structure */
PTR        cxtId;                   /* Context Id for compression */
PjSecInp   secInp;                 /* Input for Integrity protection */
PjLibTrans *libTrans;               /* Transaction Id */
Buffer     *mBuf;                   /* SDU to be compressed */
U32        *macI;                   /* Message authentication code for the SDU */
#endif
{
   U8 *data;
   MsgLen   len;
   U32      libLen = 0;
   MsgLen   cCnt;
   U32      *outMacI = NULLP;
   KwAcLibSecEnt   *intEnt;
   Bool  intProtFail = FALSE;

#ifndef KWAC_LIB_SUPPORT 
   U32 tmpMacI =  0;
#endif /* KWAC_LIB_SUPPORT */

   TRC3(kwAcLibObdIntProtReq);

   intProtFail =  kwAcCb.directive.intProtFail;
   kwAcCb.directive.intProtFail  =  FALSE;

   SFndLenMsg(mBuf, &len);
   libLen = len +  ((len % 4)?(4- (len % 4)):0);

   PJ_ALLOC(data, libLen);
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (data == NULLP)
   {
      PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
            "kwAcLibObdIntProtReq: data allocation Failed.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
   for(cCnt = 0; cCnt < len; cCnt ++)
      SExamMsg(&data[cCnt], mBuf, cCnt);

   kwAcLibUtlGetEnt(&libCb.intCb.intList, cxtId, &intEnt);
   if(intEnt == NULLP)
   {
      RETVALUE(RFAILED);
   }

#ifdef KWAC_LIB_SUPPORT 
   if(intEnt->algoType ==  CPJ_SEC_ALG_NULL)
   {
      outMacI  =  0;
      /* outMacI = (U32 *)kwAcKasF9((U8 *)&intEnt->key, secInp.count, secInp.rbId, PJ_SEC_DIR_UL, data,(PTR) len); */
   }
   else if(intEnt->algoType ==  CPJ_SEC_ALG_SNOW3G)
   {
      outMacI = (U32 *)kwAcSnowF9((U8 *)&intEnt->key, secInp.count, secInp.rbId,
            PJ_SEC_DIR_UL, data,(U32) len * 8);

   }
   else
   {
      RETVALUE(RFAILED);
   }
#else
   {
      outMacI  =  &tmpMacI;
   }
#endif /* KWAC_LIB_SUPPORT */

   PJ_FREE(data, libLen);
   if (outMacI == NULLP)
   {
      RETVALUE(RFAILED);
   }

#ifdef PJ_SEC_ASYNC
   {
      U32   id;
      Bool  saveMsg;
      KwAcLibOutEnt *ent;

      id =  kwAcCb.directive.id;
      saveMsg =  kwAcCb.directive.saveIntMsg;
      kwAcCb.directive.saveIntMsg   =  FALSE;

      CMXTA_ZERO(pst, sizeof(Pst));

      cmXtaGetPst(pst, ENTOS, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);

      if(saveMsg)
      {
         PJ_ALLOC(ent, sizeof(KwAcLibOutEnt));
#if (ERRCLASS & ERRCLS_ADD_RES)
         if (ent == NULLP)
         {
            PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
                  "kwAcLibObdIntProtReq: ent allocation Failed.");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

         ent->fd  =  cxtId;
         ent->id  =  id;
         cmMemcpy((U8 *)&ent->pst,(U8 *)pst,sizeof(Pst));
         cmMemcpy((U8 *)&ent->libTrans,(U8 *)libTrans,sizeof(PjLibTrans));
         ent->macIStatus   =  (*outMacI);
         kwAcLibUtlInsOutEnt(&libCb.intCb.intOutList, ent);
      }
      else
      {
         cmPkLibObdIntProtCfm(pst, cxtId, *libTrans, (*outMacI));
      }

      SPutMsg(mBuf);
   }
#else
   *macI  =  *outMacI;
#endif /* PJ_SEC_ASYNC */

   RETVALUE(ROK);
} /* end of kwAcLibObdIntProtReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to cipher SDU.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to cipher 
 *        SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdCipherReq 
(
Pst      *pst,                    /* post structure */
PTR         secCxtId,           /* Context Id for compression */
PjLibTrans  *libTrans,           /* Transaction Id */
PjSecInp    secInp,             /* Input for Ciphering */                  
Buffer      *mBuf,              /* SDU to be ciphered */
Buffer      **opSdu             /* ciphered SDU */
)
#else
PUBLIC S16 kwAcLibObdCipherReq(pst, secCxtId, libTrans, secInp, mBuf, opSdu)
Pst      *pst;                    /* post structure */
PTR         secCxtId;           /* Context Id for ciphering */
PjLibTrans  *libTrans;           /* Transaction Id */
PjSecInp    secInp;             /* Input for ciphering */                  
Buffer      *mBuf;              /* SDU to be ciphering */
Buffer      **opSdu;            /* Ciphering SDU */
#endif
{
   U8 *data;
   MsgLen   len;
   MsgLen libLen = 0;
   MsgLen   cCnt;
   Buffer *outSdu;
   KwAcLibSecEnt   *cipEnt;
   Bool  cipFail = FALSE;

   TRC3(kwAcLibObdCipherReq);

   cipFail =  kwAcCb.directive.cipFail;
   kwAcCb.directive.cipFail   =  FALSE;

   SFndLenMsg(mBuf, &len);
   libLen = len +  ((len % 4)?(4- (len % 4)):0);
   if ( cipFail == FALSE )
   {
      PJ_ALLOC(data, libLen);
#if (ERRCLASS & ERRCLS_ADD_RES)
      if (data == NULLP)
      {
         PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
               "kwAcLibObdCipherReq: ent allocation Failed.");
         RETVALUE(RFAILED);
      }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
      for(cCnt = 0; cCnt < len; cCnt ++)
         SExamMsg(&data[cCnt], mBuf, cCnt);

      kwAcLibUtlGetEnt(&libCb.cipCb.cipList, secCxtId, &cipEnt);

#ifdef KWAC_LIB_SUPPORT 

      if(cipEnt->algoType ==  CPJ_SEC_ALG_NULL)
      {
         /* kwAcKasF8(cipEnt->key, secInp.count, secInp.rbId, PJ_SEC_DIR_UL, data,(PTR) len); */
      }
      else if(cipEnt->algoType ==  CPJ_SEC_ALG_SNOW3G)
      {
         kwAcSnowF8(cipEnt->key, secInp.count, secInp.rbId, PJ_SEC_DIR_UL, \
               data,(U32) len * 8);
      }
      else if(cipEnt->algoType ==  CPJ_SEC_ALG_AES)
      {
         kwAcAesEncrypt(data, (U32)len, cipEnt->key);
      }
      else
      {
         RETVALUE(RFAILED);
      }
#endif /* KWAC_LIB_SUPPORT */

      SGetMsg(0,0,&outSdu);

      for(cCnt = 0; cCnt < len; cCnt ++)
         SAddPstMsg(data[cCnt], (outSdu));

      PJ_FREE(data, libLen);
   }
   else
   {
      outSdu = NULLP;
   }
#ifdef PJ_SEC_ASYNC
   {
      U32   id;
      Bool  saveMsg;
      KwAcLibOutEnt *ent;

      id =  kwAcCb.directive.id;
      saveMsg =  kwAcCb.directive.saveCpMsg;
      kwAcCb.directive.saveCpMsg =  FALSE;

      CMXTA_ZERO(pst, sizeof(Pst));

      cmXtaGetPst(pst, ENTOS, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);

      if(saveMsg)
      {
         PJ_ALLOC(ent, sizeof(KwAcLibOutEnt));
#if (ERRCLASS & ERRCLS_ADD_RES)
         if (ent == NULLP)
         {
            PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
                  "kwAcLibObdCipherReq: ent allocation Failed.");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

         ent->fd  =  secCxtId;
         ent->id  =  id;
         cmMemcpy((U8 *)&ent->pst,(U8 *)pst,sizeof(Pst));
         cmMemcpy((U8 *)&ent->libTrans,(U8 *)libTrans,sizeof(PjLibTrans));
         ent->mBuf   =  outSdu;
         kwAcLibUtlInsOutEnt(&libCb.cipCb.cipOutList, ent);
      }
      else
      {
         cmPkLibObdCipherCfm(pst, secCxtId, *libTrans, outSdu);
         SPutMsg(outSdu);
      }
      SPutMsg(mBuf);
   }
#else
   (*opSdu) =  outSdu;
#endif /* PJ_SEC_ASYNC */
   RETVALUE(ROK);

} /* end of kwAcLibObdCipherReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to decompress the SDU.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to decompress 
 *        the SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdDecmpReq 
(
Pst      *pst,                    /* post structure */
PTR      cmpCxtId,                /* Context Id for compression */
PjLibTrans *libTrans,              /* Transaction Id */
Buffer   *mBuf,                   /* SDU to be decompressed */
Buffer   **opSdu,                 /* Decompressed SDU */
Buffer   **feedback               /* ROHC feedback buffer */
)
#else
PUBLIC S16 kwAcLibObdDecmpReq(pst, cmpCxtId, libTrans, mBuf, opSdu, feedback)
Pst      *pst;                    /* post structure */
PTR      cmpCxtId;                /* Context Id for compression */
PjLibTrans *libTrans;              /* Transaction Id */
Buffer   *mBuf;                   /* SDU to be decompressed */
Buffer   **opSdu;                 /* Decompressed SDU */
Buffer   **feedback;              /* ROHC feedback buffer */
#endif
{
   Data data       = 0;
   Buffer *outSdu  = NULLP;
   Buffer *fBuf    = NULLP;
   Bool  decmpFail = FALSE;
   Bool  fBack     = FALSE;

   TRC3(kwAcLibObdDecmpReq)

   decmpFail =  kwAcCb.directive.decmpFail;
   fBack =  kwAcCb.directive.feedback;
   kwAcCb.directive.decmpFail =  FALSE;
   kwAcCb.directive.feedback  =  FALSE;

   if(decmpFail != TRUE)
   {
      SCpyMsgMsg(mBuf, kwCb.init.region, kwCb.init.pool, &outSdu);

      /* Do not alter mBuf, Modify only opSdu */
      SRemPreMsg(&data, outSdu);
   }
   else
   {
      /* send a negative feedback */
      fBack =  TRUE;
   }

   if(fBack)
   {
      SGetMsg(0, 0, &fBuf);
      SAddPreMsg(data, fBuf);
   }

#ifdef PJ_CMP_ASYNC
   {
      U32   id;
      Bool  saveMsg;
      KwAcLibOutEnt *ent;

      id =  kwAcCb.directive.id;

      saveMsg =  kwAcCb.directive.saveDecmpMsg;
      kwAcCb.directive.saveDecmpMsg =  FALSE;

      CMXTA_ZERO(pst, sizeof(Pst));
      cmXtaGetPst(pst, ENTOC, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
      if(saveMsg)
      {
         PJ_ALLOC(ent, sizeof(KwAcLibOutEnt));
#if (ERRCLASS & ERRCLS_ADD_RES)
         if (ent == NULLP)
         {
            PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
                  "kwAcLibObdDecmpReq: ent allocation Failed.");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

         ent->fd  =  cmpCxtId;
         ent->id  =  id;
         cmMemcpy((U8 *)&ent->pst,(U8 *)pst,sizeof(Pst));
         cmMemcpy((U8 *)&ent->libTrans,(U8 *)libTrans,sizeof(PjLibTrans));
         ent->mBuf   =  (outSdu);
         kwAcLibUtlInsOutEnt(&libCb.compCb.compOutList, ent);
      }
      else
      {
         cmPkLibObdDecmpCfm(pst, cmpCxtId, *libTrans, (outSdu), (fBuf));
         PJ_FREE_BUF(outSdu);
         PJ_FREE_BUF(fBuf);

      }

      /* Delete mBuf only in case of PJ_CMP_ASYNC */
      PJ_FREE_BUF(mBuf);
   }
#else
   *opSdu   =  outSdu;
   *feedback   =  fBuf;
#endif /* PJ_CMP_ASYNC */

   RETVALUE(ROK);

} /* end of kwAcLibObdDecmpReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to request for integrity
 *        verification
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to verify integrity 
 *        SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdIntVerReq 
(
Pst         *pst,                   /* post structure */
PTR        intCxtId,                /* Context Id for compression */
PjSecInp   secInp,                  /* Input for Integrity protection */                  
PjLibTrans *libTrans,                /* Transaction Id */
Buffer     *mBuf,                   /* SDU to be compressed */
U32        macI,                   /* Message authentication code for the SDU */
Status     *status                  /* Status of the Integrity verification */
)
#else
PUBLIC S16 kwAcLibObdIntVerReq(pst, intCxtId, secInp, libTrans, mBuf, macI, status)
Pst      *pst;                    /* post structure */
PTR        intCxtId;                /* Context Id for compression */
PjSecInp   secInp;                  /* Input for Integrity protection */
PjLibTrans *libTrans;                 /* Transaction Id */
Buffer     *mBuf;                   /* SDU to be compressed */
U32        macI;                   /* Message authentication code for the SDU */
Status     *status;                 /* Status of the Integrity verification */
#endif
{

   U8            *data;
   MsgLen         len;
   MsgLen         cCnt;
   U32      libLen = 0;
   U32           *outMacI = NULLP;
   KwAcLibSecEnt *intEnt;
   Bool  intVerFail = FALSE;
   Status   outStatus;

#ifndef KWAC_LIB_SUPPORT 
   U32 tmpMacI =  0;
#endif /* KWAC_LIB_SUPPORT */

   TRC3(kwAcLibObdIntVerReq);

   intVerFail =  kwAcCb.directive.intVerFail;
   kwAcCb.directive.intVerFail   =  FALSE;

   if(intVerFail == FALSE)
   {
      SFndLenMsg(mBuf, &len);
      libLen = len +  ((len % 4)?(4- (len % 4)):0);
      PJ_ALLOC(data, libLen);
#if (ERRCLASS & ERRCLS_ADD_RES)
      if (data == NULLP)
      {
         PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
               "kwAcLibObdIntVerReq: data allocation Failed.");
         RETVALUE(RFAILED);
      }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
      for(cCnt = 0; cCnt < len; cCnt ++)
         SExamMsg(&data[cCnt], mBuf, cCnt);

      /* TODO: - what is fresh  sendinf rbID for fresh */
      kwAcLibUtlGetEnt(&libCb.intCb.intList, intCxtId, &intEnt);
      if(intEnt == NULLP)
      {
         RETVALUE(RFAILED);
      }

#ifdef KWAC_LIB_SUPPORT 

      if(intEnt->algoType ==  CPJ_SEC_ALG_KASUMI)
      {
         /* outMacI = (U32 *)kwAcKasF9(intEnt->key, secInp.count, secInp.rbId, PJ_SEC_DIR_UL, data,(PTR) len); */
      }
      else if(intEnt->algoType ==  CPJ_SEC_ALG_SNOW3G)
      {

         outMacI = (U32 *)kwAcSnowF9(intEnt->key, secInp.count, secInp.rbId,\
               PJ_SEC_DIR_UL, data,(U32) len * 8);
      }
      else
      {
         RETVALUE(RFAILED);
      }
#else
   {
      outMacI  =  &tmpMacI;
   }
#endif /* KWAC_LIB_SUPPORT */

      PJ_FREE(data, libLen);
      if (outMacI == NULLP)
      {
         RETVALUE(RFAILED);
      }

      (outStatus)   =  ((macI) == (*outMacI))? LCM_PRIM_OK: LCM_PRIM_NOK;
   }
   else
   {
      (outStatus)   =   LCM_PRIM_NOK;
   }

#ifdef PJ_SEC_ASYNC
   {
      U32   id;
      Bool  saveMsg;
      KwAcLibOutEnt *ent;

      saveMsg =  kwAcCb.directive.saveIntVerMsg;
      kwAcCb.directive.saveIntVerMsg   =  FALSE;
      id =  kwAcCb.directive.id;

      CMXTA_ZERO(pst, sizeof(Pst));

      cmXtaGetPst(pst, ENTOS, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   
      if(saveMsg)
      {
         PJ_ALLOC(ent, sizeof(KwAcLibOutEnt));
#if (ERRCLASS & ERRCLS_ADD_RES)
         if (ent == NULLP)
         {
            PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
                  "kwAcLibObdIntVerReq: ent allocation Failed.");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

         ent->fd  =  intCxtId;
         ent->id  =  id;
         cmMemcpy((U8 *)&ent->pst,(U8 *)pst,sizeof(Pst));
         cmMemcpy((U8 *)&ent->libTrans,(U8 *)libTrans,sizeof(PjLibTrans));
         ent->macIStatus   =  (outStatus);
         kwAcLibUtlInsOutEnt(&libCb.intCb.intOutList, ent );
      }
      else
      {
         cmPkLibObdIntVerCfm(pst, intCxtId, *libTrans, outStatus);
      }

      SPutMsg(mBuf);

   }
#else
   (*status)  =  outStatus;
#endif /* PJ_SEC_ASYNC */

   RETVALUE(ROK);

} /* end of kwAcLibObdIntVerReq */

/**
 *
 * @brief 
 *
 *        Portable function for synchronous hook to decipher SDU.
 *
 * @b Description:
 *
 *        This is a portable function for synchronous hook to decipher 
 *        SDU 
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdDecipherReq 
(
Pst      *pst,                    /* post structure */
PTR         cxtId,           /* Context Id for compression */
PjLibTrans  *libTrans,           /* Transaction Id */
PjSecInp    secInp,             /* Input for Deciphering */                  
Buffer      *mBuf,              /* SDU to be deciphered */
Buffer      **opSdu             /* deciphered SDU */
)
#else
PUBLIC S16 kwAcLibObdDecipherReq(pst, cxtId, libTrans, secInp, mBuf, opSdu)
Pst      *pst;                    /* post structure */
PTR         cxtId;           /* Context Id for Deciphering */
PjLibTrans  *libTrans;           /* Transaction Id */
PjSecInp    secInp;             /* Input for Deciphering */                  
Buffer      *mBuf;              /* SDU to be Deciphering */
Buffer      **opSdu;            /* Deciphering SDU */
#endif
{
   U8 *data;
   MsgLen   len;
   MsgLen   libLen = 0;
   MsgLen   cCnt;
   Buffer   *outSdu;
   KwAcLibSecEnt   *cipEnt = NULLP;
   Bool  decipFail = FALSE;

   TRC3(kwAcLibObdDecipherReq);

   decipFail =  kwAcCb.directive.decipFail;
   kwAcCb.directive.decipFail =  FALSE;

   if ( decipFail == FALSE)
   {
      SFndLenMsg(mBuf, &len);
      libLen = len +  ((len % 4)?(4- (len % 4)):0);
      PJ_ALLOC(data, libLen);
#if (ERRCLASS & ERRCLS_ADD_RES)
      if (data == NULLP)
      {
         PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
               "kwAcLibObdDecipherReq: data allocation Failed.");
         RETVALUE(RFAILED);
      }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

      for(cCnt = 0; cCnt < len; cCnt ++)
         SExamMsg(&data[cCnt], mBuf, cCnt);

      kwAcLibUtlGetEnt(&libCb.cipCb.cipList, cxtId, &cipEnt);
      if(cipEnt == NULLP)
      {
         RETVALUE(RFAILED);
      }

#ifdef KWAC_LIB_SUPPORT
      if(cipEnt->algoType ==  CPJ_SEC_ALG_KASUMI)
      {
         kwAcKasF8(cipEnt->key, secInp.count, secInp.rbId, PJ_SEC_DIR_UL, \
               data,(PTR) len * 8);
      }
      else if(cipEnt->algoType ==  CPJ_SEC_ALG_SNOW3G)
      {
         kwAcSnowF8(cipEnt->key, secInp.count, secInp.rbId, PJ_SEC_DIR_UL,\
               data,(U32) len * 8);
      }
      else if(cipEnt->algoType ==  CPJ_SEC_ALG_AES)
      {
         kwAcAesDecrypt(data, (U32)len, cipEnt->key);
      }
      else
      {
         RETVALUE(RFAILED);
      }
#endif /* KWAC_LIB_SUPPORT */

      SGetMsg(0,0,&outSdu);
      for(cCnt = 0; cCnt < len; cCnt ++)
         SAddPstMsg(data[cCnt], outSdu);

      PJ_FREE(data, libLen);
   }
   else
   {
      outSdu = NULLP;
   }

#ifdef PJ_SEC_ASYNC
   {
      PRIVATE U32   id;
      Bool  saveMsg;
      KwAcLibOutEnt *ent;

      saveMsg =  kwAcCb.directive.saveDecpMsg;

      if(kwAcCb.directive.seqStart == TRUE)
      {
         id =  0;
         kwAcCb.directive.seqStart = FALSE;
      }

      if(kwAcCb.directive.seqOn == TRUE)
      {
         id++;
      }
      else
      {
         id = kwAcCb.directive.id; 
         kwAcCb.directive.saveDecpMsg  =  FALSE;
      }

      CMXTA_ZERO(pst, sizeof(Pst));

      cmXtaGetPst(pst, ENTOS, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);

      if(saveMsg)
      {
         PJ_ALLOC(ent, sizeof(KwAcLibOutEnt));
#if (ERRCLASS & ERRCLS_ADD_RES)
         if (ent == NULLP)
         {
            PJLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
                  "kwAcLibObdDecipherReq: ent allocation Failed.");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

         ent->fd  =  cxtId;
         ent->id  =  id;
         cmMemcpy((U8 *)&ent->pst,(U8 *)pst,sizeof(Pst));
         cmMemcpy((U8 *)&ent->libTrans,(U8 *)libTrans,sizeof(PjLibTrans));
         ent->mBuf   =  outSdu;
         kwAcLibUtlInsOutEnt(&libCb.cipCb.cipOutList, ent);
      }
      else
      {
         cmPkLibObdDecipherCfm(pst, cxtId, *libTrans, outSdu);
         if ( outSdu != NULLP )
         {
            SPutMsg(outSdu);
         }
      }

      SPutMsg(mBuf);

   }
#else
   (*opSdu) = outSdu;
#endif /* PJ_SEC_ASYNC */
   RETVALUE(ROK);


} /* end of kwAcLibObdDecipherReq */

/**
 *
 * @brief 
 *
 *        Handler for resetting the context with the compression unit (either 
 *        synchronous or asynchronous) for RB within an UE.
 *
 * @b Description:
 *
 *        This function resets an existing context with the compression unit per RB per
 *        UE, either using synchronous / asynchronous function calls with relevant input parameters.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdCmpResetReq
(
Pst      *pst,                    /* post structure */
PTR      cmpCxtId                 /* ROHC Context to be closed */
)
#else
PUBLIC S16 kwAcLibObdCmpResetReq(pst, cmpCxtId)
Pst      *pst;                    /* post structure */
PTR      cmpCxtId;                /* ROHC Context to be closed */
#endif
{
   TRC3(kwAcLibObdCmpResetReq)

   RETVALUE(ROK);

} /* end of kwAcLibObdCmpResetReq */

/**
 *
 * @brief 
 *
 *        Handler to send the feedback to the compression unit (either 
 *        synchronous or asynchronous) for RB within an UE.
 *
 * @b Description:
 *
 *        This function to send the feedback to the compression unit per RB per
 *        UE, either using synchronous / asynchronous function calls with relevant input parameters.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdCmpFbReq
(
Pst      *pst,                    /* post structure */
PTR      cmpCxtId,                /* ROHC Context to be closed */
PjLibTrans *libTrans,             /* Library Transaction */
Buffer   *feedback                /* Feedback */
)
#else
PUBLIC S16 kwAcLibObdCmpFbReq(pst, cmpCxtId, libTrans, feedback)
Pst      *pst;                    /* post structure */
PTR      cmpCxtId;                /* ROHC Context to be closed */
PjLibTrans *libTrans;             /* Library Transaction */
Buffer   *feedback;               /* Feedback */
#endif
{
   TRC3(kwAcLibObdCmpFbReq)

   PJ_FREE_BUF(feedback);
   RETVALUE(ROK);

} /* end of kwAcLibObdCmpFbReq */

/**
 *
 * @brief 
 *
 *        Handler for closing the context with the compression unit (either 
 *        synchronous or asynchronous) for RB within an UE.
 *
 * @b Description:
 *
 *        This function closes an existing context with the compression unit per RB per
 *        UE, either using synchronous / asynchronous function calls with relevant input parameters.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdCmpCloseReq
(
Pst      *pst,                    /* post structure */
PTR      cmpCxtId                 /* ROHC Context to be closed */
)
#else
PUBLIC S16 kwAcLibObdCmpCloseReq(pst, cmpCxtId)
Pst      *pst;                    /* post structure */
PTR      cmpCxtId;                /* ROHC Context to be closed */
#endif
{
   TRC3(kwAcLibObdCmpCloseReq)

   RETVALUE(ROK);

} /* end of kwAcLibObdCmpCloseReq */

/**
 *
 * @brief 
 *
 *        Handler for closing the context with the Integration unit (either 
 *        synchronous or asynchronous) for all RBs of an UE.
 *
 * @b Description:
 *
 *        This function closes an existing context with the security algo unit per UE
 *        for Integration protection/verification using synchronous / asynchronous function 
 *        calls with relevant input parameters.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdIntCloseReq
(
Pst      *pst,                    /* post structure */
PTR      intCxtId                 /* Integration CxtId to be closed */
)
#else
PUBLIC S16 kwAcLibObdIntCloseReq(pst, intCxtId)
Pst      *pst;                    /* post structure */
PTR      intCxtId;                /* Integration CxtId to be closed */
#endif
{
   TRC3(kwAcLibObdIntCloseReq)

   kwAcLibUtlDelEnt(&libCb.intCb.intList, intCxtId);

   RETVALUE(ROK);

} /* end of kwAcLibObdIntCloseReq */

/**
 *
 * @brief 
 *
 *        Handler for closing the context with the Ciphering unit (either 
 *        synchronous or asynchronous) for SRBs of an UE.
 *
 * @b Description:
 *
 *        This function closes an existing context with the security algo unit per UE
 *        for ciphering / deciphering with control plane key using synchronous / asynchronous 
 *        function calls with relevant input parameters.
 *
 *
 *  @param[in] pst     Post structure  
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAcLibObdCipherCloseReq
(
Pst      *pst,                    /* post structure */
PTR      cpCxtId                  /* Context Id for SRBs to be closed */
)
#else
PUBLIC S16 kwAcLibObdCipherCloseReq(pst, cpCxtId)
Pst      *pst;                    /* post structure */
PTR      cpCxtId;                 /* Context Id for SRBs to be closed */
#endif
{
   TRC3(kwAcLibObdCipherCloseReq)

   kwAcLibUtlDelEnt(&libCb.cipCb.cipList, cpCxtId);

   RETVALUE(ROK);

} /* end of kwAcLibObdCipherCloseReq */

#endif /* KW_PDCP */

/********************************************************************30**

         End of file:     kwac_libcb.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:28 2014

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
/main/1      ---   gk         1. Initial Release.
*********************************************************************91*/


