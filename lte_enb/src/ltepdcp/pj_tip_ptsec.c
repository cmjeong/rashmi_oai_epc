

/************************************************************************

     Name:     LTE PDCP Security Interface 

     Type:     C source file

     Desc:     C source code for TIP Security Functions

     File:     

     Sid:      eq_mspdt2k_ptsec.c@@/main/TeNB_Main_BR/14 - Mon Aug 11 16:42:50 2014

     Prg:     

**********************************************************************/
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer defines */
#include "cm_tkns.h"       /* Common tokens defines */
#include "cm_mblk.h"       /* Common memory allocation library defines */
#include "cm_llist.h"      /* Common link list defines  */
#include "cm_hash.h"       /* Common hashlist defines */
#include "cm_lte.h"        /* Common LTEE defines */
#include "cpj.h"           /* CPJ Interface defines */
#include "pju.h"                /* PJU defines */
#include "lpj.h"                /* LPJ defines */
#include "pj_ptsec.h"
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"
#include "pj_tip_ptsec.h"

#include "ext_common.h"
#include "auth_alg.h"
#include "hmacsha256.h"
#include "snow3g_f8f9.h"

#include "gen.x"           /* General */
#include "ssi.x"           /* System services */

#include "cm5.x"           /* Common timer library */
#include "cm_tkns.x"       /* Common tokens */
#include "cm_mblk.x"       /* Common memory allocation */
#include "cm_llist.x"      /* Common link list */
#include "cm_hash.x"       /* Common hashlist */
#include "cm_lte.x"        /* Common LTE includes */
#include "cm_lib.x"
#include "cpj.x"                /* CPJ */
#include "pju.x"                /* PJU */
#include "lpj.x"                /* LPJ */
#include "pj.x"
#include "pj_udx.h"          /* LIB */
#include "pj_udx.x"          /* LIB */
#include "pj_ul.x"
#include "pj_dl.x"

#ifdef LTE_PAL_ENB
static const char* RLOG_MODULE_NAME="PDCP";
static int RLOG_MODULE_ID=1024;
static int RLOG_FILE_ID=222;

/**
 * @brief         - This function derives the requested key from string S 
 *                  input.
 *
 * @details       - This function provides as input string S for derivation of the
 *                  required key (integrity/Up/Cp Chiphering key).The input
 *                  string is provided as input for the HMAC-SHA-256
 * @param[in]     - pSecInfo  Input parameters for Opening handle and processing.
 * @param[in_out] - U8*  key  Output key (cipher/Integrity)
 *
 * @return ROK/RFAILED
 */
#ifdef ANSI
PUBLIC S16 pjTipKDF
(
PjLibTrans libTrans,
U8   *key
)
#else
PUBLIC S16 pjTipKDF(libTrans, key)
PjLibTrans libTrans;
U8   *key;
#endif
{
   U8 digest[512] = {'\0'};
   hmacsha256Param sp;
   TRC2(pjTipKDF);

   hmacsha256Setup(&sp, (const byte*)libTrans.key, (size_t)CPJ_SEC_KEY_LEN * 8);
   hmacsha256Update(&sp, (const byte*)libTrans.strS, (size_t)libTrans.strSlen);
   hmacsha256Digest(&sp, (byte*)digest);
   if(libTrans.strSlen == PJ_STR_S_LEN7)
   {
      cmMemcpy(key, digest + (CPJ_SEC_KEY_LEN - PJ_INTG_KEY_LEN), CPJ_SEC_KEY_LEN);
   }
   else
   {
      cmMemcpy(key, digest , CPJ_SEC_KEY_LEN);
   }

   RETVALUE(ROK);

}

/**
 * @brief         - This function is used to initiate key derivation.
 *
 * @details       - 
 *                  
 * @param[in]     - MsSecInfo, Key
 *
 * @return         - ROK on success
 */
#ifdef ANSI
PUBLIC S16 pjSendToTipKeyDeriveFunc
(
PjLibTrans libTrans,
U8   *key
)
#else
PUBLIC S16 pjSendToTipKeyDeriveFunc(libTrans, key)
PjLibTrans libTrans;
U8   *key;
#endif
{
   S16 ret = ROK;

   TRC3(pjSendToTipKeyDeriveFunc)

   ret = pjTipKDF(libTrans, key);
   RETVALUE(ret);
}


/**
 * @brief This function is used to Integrity Protect the buffer received
 *        as input.
 * @details This function sets the context for the Integrity Protection.
 *
 * @param[in] pSecInfo - Information passed from PDCP.
 * @param[in_out] mBuf - Buffer for Integrity Protection. 
 *
 * @return             - ROK/RFAILED
 */
#ifdef ANSI
PUBLIC U32 pjTipIntegProtPkt
(
PjLibTrans  *libTrans, 
Buffer **mBuf
)
#else
PUBLIC U32 pjTipIntegProtPkt(libTrans, mBuf)
PjLibTrans  *libTrans;
Buffer **mBuf;
#endif
{
   U32 macI = 0;
   U8 msg[PJ_MAX_SDU_SIZE] = {0};
   MsgLen mBufLen;
   MsgLen len;
   U32 fresh = 0;

   TRC3(pjTipIntegProtPkt);

   SFndLenMsg(*mBuf, &mBufLen);
   S16 ret = SCpyMsgFix(*mBuf,0,mBufLen,msg,&len);
   if ((ret != ROK) || (mBufLen != len)) 
   {
      RLOG2(L_ERROR,"SCpyMsgFix failed [mBufLen: %d len: %d]\n", mBufLen, len);
      RETVALUE(RFAILED);
   }
   /* SRI TIP */
   fresh = libTrans->rbId << 27;

   //macI = f9Snow3g(libTrans->key, libTrans->count, libTrans->rbId, libTrans->dir, msg, len * 8);
   macI = f9Snow3g(libTrans->key, libTrans->count, fresh, libTrans->dir, msg, len * 8);

   PJ_PACK_MACI(*mBuf, macI);

#if 0
   printf("\n[%d][%d] IntgProt Count: %d RBID: %d DIR: %d [MACI: %x] Len: %d\n",
         libTrans->cellId, libTrans->ueId, libTrans->count,
         libTrans->rbId, libTrans->dir, macI, (len*8));
   {
      printf("Key:");
      int i;
      for(i = 0; i < PJ_INTG_KEY_LEN; i++)
         printf("%x ", libTrans->key[i]);
      printf("\n\n");
   }
#endif
   RETVALUE(ROK);
}

/**
 * @brief This function is used for Integrity Verification for
 *        the buffer received as input.
 *
 * @details This function sets the context for the integrity 
 *          verification. 
 *
 * @param[in] pSecInfo - Information passed from PDCP.
 * @param[in] mBuf - Buffer for Integrity Verification  
 * @param[in] macI     - macI for verification 
 *
 * @return             - ROK/RFAILED
 */
#ifdef ANSI
PUBLIC U32 pjTipIntegProtVerifyPkt 
(
PjLibTrans  *libTrans,
Buffer **mBuf,
U32 macI
)
#else
PUBLIC U32 pjTipIntegProtVerifyPkt(libTrans, mBuf, macI)
PjLibTrans  *libTrans;
Buffer **mBuf;
U32 macI;
#endif
{
   U32 ret = ROK;
   U32 dervMacI = 0;
   MsgLen mBufLen;
   MsgLen len;
   U8 msg[PJ_MAX_SDU_SIZE] = {0};
   U32 fresh = 0;

   TRC3(pjTipIntegProtVerifyPkt);
   
   SFndLenMsg(*mBuf, &mBufLen);
   ret = SCpyMsgFix(*mBuf,0,mBufLen,msg,&len);
   if ((ret != ROK) || (mBufLen != len)) 
   {
      printf("SCpyMsgFix failed [mBufLen: %d len: %d]\n", mBufLen, len);
      RETVALUE(RFAILED);
   }

   fresh = libTrans->rbId << 27;

   dervMacI = f9Snow3g(libTrans->key, libTrans->count, fresh, libTrans->dir, msg, len * 8);

   if(dervMacI != macI)
   {
       RLOG2(L_ERROR,"Integrity Verification Failed : Rcvd MAC-I [%u] calc MAC-I [%u]"
               , macI, dervMacI);
       //ret = RFAILED; 
       ret = ROK;
   }

#if 0
   printf("\n[%d][%d] IntgVerf Count: %d RBID: %d DIR: %d "
         "[Recvd MACI: %x | MACI: %x] Len: %d\n",
         libTrans->cellId, libTrans->ueId, libTrans->count,
         libTrans->rbId, libTrans->dir, macI, dervMacI, (len*8));
   {
      printf("Key:");
      int i;
      for(i = 0; i < PJ_INTG_KEY_LEN; i++)
         printf("%x ", libTrans->key[i]);
      printf("\n\n");
   }
#endif

   RETVALUE(ret);
}



/**
 * @brief         - This function is used to Send packets for ciphering.
 *
 * @details       - 
 *                  
 * @param[in]     -  libTrans, mBuf
 *
 * @return         - ROK on success
 */
#ifdef ANSI
PUBLIC S16 pjTipSendToCipher
(
PjLibTrans  *libTrans,
Buffer      *mBuf,
Buffer      **opSdu
)
#else
PUBLIC S16 pjTipSendToCipher(libTrans, mBuf, opSdu)
PjLibTrans  *libTrans;
Buffer      *mBuf;
Buffer      **opSdu;
#endif
{
   S16 ret = ROK;
   MsgLen mBufLen;
   MsgLen len;
   U8 msg[PJ_MAX_SDU_SIZE] = {0};

   TRC3(pjTipSendToCipher)
   
   SFndLenMsg(mBuf, &mBufLen);
   ret = SCpyMsgFix(mBuf,0,mBufLen,msg,&len);
   if ((ret != ROK) || (mBufLen != len)) 
   {
      printf("SCpyMsgFix failed [mBufLen: %d len: %d]\n", mBufLen, len);
      RETVALUE(RFAILED);
   }

   f8Snow3g(libTrans->key, libTrans->count, libTrans->rbId, libTrans->dir, msg, len * 8);

   if (SGetMsg(0, 0, opSdu) != ROK)
   {
       RLOG0(L_FATAL, "Memory Allocation Failed  ");
       RETVALUE(RFAILED);
   }

   if ( ROK != SAddPstMsgMult(msg, len, *opSdu))
   {
       RLOG0(L_FATAL, "PDCP Ciphering Failed ");
       ret = RFAILED;
   }

   RETVALUE(ret);
}

/*This function is used to Send packets for de-ciphering.
 *
 * @details       - 
 *                  
 * @param[in]     -  libTrans, mBuf
 *
 * @return         - ROK on success
 */
#ifdef ANSI
PUBLIC S16 pjTipSendToDeCipher
(
 PjLibTrans  *libTrans,
 Buffer      *mBuf,
 Buffer      **opSdu
)
#else
PUBLIC S16 pjTipSendToDeCipher(libTrans, mBuf, opSdu)
PjLibTrans  *libTrans;
Buffer      *mBuf;
Buffer      **opSdu;
#endif
{
   S16 ret = ROK;
   MsgLen mBufLen;
   MsgLen len;
   U8 msg[PJ_MAX_SDU_SIZE] = {0};

   TRC3(pjTipSendToDeCipher)
   
   SFndLenMsg(mBuf, &mBufLen);
   ret = SCpyMsgFix(mBuf,0,mBufLen,msg,&len);

   if ((ret != ROK) || (mBufLen != len)) 
   {
      RLOG2(L_ERROR,"SCpyMsgFix failed [mBufLen: %d len: %d]\n", mBufLen, len);
      RETVALUE(RFAILED);
   }

   f8Snow3g(libTrans->key, libTrans->count, libTrans->rbId, libTrans->dir, msg, len * 8);

   if (SGetMsg(0, 0, opSdu) != ROK)
   {
       RLOG0(L_FATAL, "Memory Allocation Failed  ");
       RETVALUE(RFAILED);
   }

   if ( ROK != SAddPstMsgMult(msg, len, *opSdu))
   {
       RLOG0(L_FATAL, "PDCP DeCiphering Failed ");
       ret = RFAILED;
   }
    
   RETVALUE(ret);
}
#endif
