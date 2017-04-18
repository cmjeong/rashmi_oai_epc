
 
 #include "prc_types.h"
/* lenghth of the pointer variable */
#define BC_ICPU_MSG_LEN  sizeof(BcIcpuMsg)
#define BC_LOCAL_REG     0
#define BC_SHARED_REG    1
#define BC_ICPU_MSG_NOR  0
#define BC_ICPU_MSG_FREE 1

#define BC_MAX_PDU_CIPHER_REQ 1
#define BC_MAX_PDU_INTPROT_REQ 1
#define BC_MAX_CPU 2


#define PJ_SEC_ALLOC(_cb, _buf, _size)                         \
{                                                          \
 if (SGetSBuf(1,0, (Data **)&_buf,\
                (Size) _size) == ROK)                      \
   {                                                       \
      cmMemset((U8 *)(_buf), 0, _size);                    \
   }                                                       \
   else                                                    \
   {                                                       \
      (_buf) = NULLP;                                      \
   }                                                       \
}
typedef struct intProtCallBkParams
{
   PRC_SNOW_INTEGRITY_PARAMS *intgrtyParams;
   U32                       numPdu;
   PRC_SNOW_INTEGRITY_DATA   *pdu_list;
   PjLibTrans                libTrans; 
   Pst                    *pst;
   Buffer                 *pduInfoBuffer;
   Buffer                 *pduListBuffer;
}IntProtCallBkParams;
typedef struct intVerCallBkParams
{
   PRC_SNOW_INTEGRITY_PARAMS *intgrtyParams;
   U32                       numPdu;
   PRC_SNOW_INTEGRITY_DATA   *pdu_list;
   PjLibTrans                libTrans; 
   Pst                    *pst;
   Buffer                 *pduInfoBuffer;
   Buffer                 *pduListBuffer;
   U32                    recvMacI;
}IntVerCallBkParams;

#ifdef CIPH_BATCH_PROC
typedef struct pjTxEntDtl {
  void   *txEnt;
  void  *rbCb;
}PjTxEntDtl;

typedef struct pjRxEntDtl {
  void   *rxEnt;
  void  *rbCb;
}PjRxEntDtl;
#endif
typedef struct cipherCallBkParams
{
#ifdef CIPH_BATCH_PROC
   Data                  *cipheredBuf[32];
   PjTxEnt                *txEntLst[32];      
   PjRxEnt                *rxEntLst[32];      
   PRC_SNOW_CIPHER_DATA *pduList;
#else
   PRC_SNOW_CIPHER_DATA   *pdu_list;
   PjLibTrans             libTrans; 
   Buffer                 *mBuf[10];
   Buffer                 *pduInfoBuffer;
   Buffer                 *pduListBuffer;
   Pst                    *pst;
#endif
   U32                    numTxPdu;
   U32                    numRxPdu;
   PRC_SNOW_CIPHER_PARAMS *cipherParams;
}CipherCallBkParams;

/* ZUC_ALGO start */
typedef struct zucIntProtCallBkParams
{
   PRC_ZUC_INTEGRITY_PARAMS *intgrtyParams;
   U32                       numPdu;
   PRC_ZUC_INTEGRITY_DATA   *pdu_list;
   PjLibTrans                libTrans; 
   Pst                    *pst;
   Buffer                 *pduInfoBuffer;
   Buffer                 *pduListBuffer;
}ZucIntProtCallBkParams;

typedef struct zucIntVerCallBkParams
{
   PRC_ZUC_INTEGRITY_PARAMS *intgrtyParams;
   U32                       numPdu;
   PRC_ZUC_INTEGRITY_DATA   *pdu_list;
   PjLibTrans                libTrans; 
   Pst                    *pst;
   Buffer                 *pduInfoBuffer;
   Buffer                 *pduListBuffer;
   U32                    recvMacI;
}ZucIntVerCallBkParams;

typedef struct zucEncryptCallBkParams
{
#ifdef CIPH_BATCH_PROC
   Data                  *encryptBuf[32];
   PjTxEnt                *txEntLst[32];      
   PjRxEnt                *rxEntLst[32];
   PRC_ZUC_ENCRYPTION_DATA  *pduList;      
#else
   PRC_ZUC_ENCRYPTION_DATA   *pdu_list;
   PjLibTrans             libTrans; 
   Buffer                 *mBuf[10];
   Buffer                 *pduInfoBuffer;
   Buffer                 *pduListBuffer;
   Pst                    *pst;
#endif
   U32                    numTxPdu;
   U32                    numRxPdu;
   PRC_ZUC_ENCRYPTION_PARAMS *encryptParams;
}ZucEncryptCallBkParams;
/* ZUC_ALGO - end */

#ifdef AES
typedef struct aesIntProtCallBkParams
{
   PRC_AES_INTEGRITY_PARAMS *intgrtyParams;
   U32                       numPdu;
   PRC_AES_INTEGRITY_DATA   *pdu_list;
   PjLibTrans                libTrans; 
   Pst                    *pst;
   Buffer                 *pduInfoBuffer;
   Buffer                 *pduListBuffer;
}AesIntProtCallBkParams;

typedef struct aesIntVerCallBkParams
{
   PRC_AES_INTEGRITY_PARAMS *intgrtyParams;
   U32                       numPdu;
   PRC_AES_INTEGRITY_DATA   *pdu_list;
   PjLibTrans                libTrans; 
   Pst                    *pst;
   Buffer                 *pduInfoBuffer;
   Buffer                 *pduListBuffer;
   U32                    recvMacI;
}AesIntVerCallBkParams;

typedef struct aesEncryptCallBkParams
{
#ifdef CIPH_BATCH_PROC
   Data                  *encryptBuf[32];
   PjTxEnt                *txEntLst[32];      
   PjRxEnt                *rxEntLst[32];
   PRC_AES_ENCRYPTION_DATA  *pduList;      
#else
   PRC_AES_ENCRYPTION_DATA   *pdu_list;
   PjLibTrans             libTrans; 
   Buffer                 *mBuf[10];
   Buffer                 *pduInfoBuffer;
   Buffer                 *pduListBuffer;
   Pst                    *pst;
#endif
   U32                    numTxPdu;
   U32                    numRxPdu;
   PRC_AES_ENCRYPTION_PARAMS *encryptParams;
}AesEncryptCallBkParams;
#endif /* AES */

#ifdef CIPH_BATCH_PROC
typedef struct deCipherCallBkParams
{
   U32                    numPdu;
   PjRxEnt                *rxEntLst[32];      
   //Buffer                 *deCipheredBuf[16];
   PRC_SNOW_CIPHER_DATA *pduList;
   PRC_SNOW_CIPHER_PARAMS *deCipherParams;
}DecipherCallBkParams;

typedef struct decryptCallBkParams
{
   U32                    numPdu;
   PjRxEnt                *rxEntLst[32];      
   //Buffer                 *deCipheredBuf[16];
   PRC_ZUC_ENCRYPTION_DATA *pduList;
   PRC_ZUC_ENCRYPTION_PARAMS *decryptParams;
}DecryptCallBkParams;

#ifdef AES
typedef struct decryptAesCallBkParams
{
   U32                    numPdu;
   PjRxEnt                *rxEntLst[32];      
   //Buffer                 *deCipheredBuf[16];
   PRC_AES_ENCRYPTION_DATA *pduList;
   PRC_AES_ENCRYPTION_PARAMS *decryptParams;
}DecryptAesCallBkParams;
#endif
#endif

#if 0
extern UINT16 prc_snow_ciphering(int mode,
            int number_of_pdu, 
         PRC_SNOW_CIPHER_DATA *pdu_list,
            int wait_mode, 
         PRC_CALLBACK_FUNC callback_func,
            void *callback_params);

extern UINT16 prc_snow_integrity(int number_of_pdu, 
         PRC_SNOW_INTEGRITY_DATA *pdu_list,
         int wait_mode, 
         PRC_CALLBACK_FUNC callback_func,
         void *callback_params);
#endif

#ifdef PJ_INT_ASYNC
extern  S16 pjUtlIntProtCallBk ARGS((
U32 rc, 
Void* callback_params
));
extern  S16 pjUtlIntVerCallBk ARGS((
U32 rc, 
Void* callback_params
));


extern S16 bcIntProtReq ARGS((
Pst       *pst,
PjSecInp   secInp,                  /* Input for Integrity protection */
PjLibTrans libTrans,
Buffer     *mBuf                  /* SDU to be compressed */
));
#else
extern S16 bcIntProtReq ARGS((
PjSecInp   secInp,                  /* Input for Integrity protection */
PjDlUeCb *ueCb,
Buffer     *mBuf,                  /* SDU to be compressed */
U32        *macI                   /* Message authentication code for the SDU */
));
#endif

extern S16 pjUtlCipherCallBk ARGS((U32 rc, Void* callback_params));
#ifdef CIPH_BATCH_PROC
extern S16 pjUtlBatchCipherCallBk ARGS((U32 rc, Void* callback_params));
#endif

#if 0
EXTERN U16 prc_snow_ciphering(int mode, int number_of_pdu, 
       PRC_SNOW_CIPHER_DATA *pdu_list,int wait_mode, 
       PRC_CALLBACK_FUNC callback_func,
            void *callback_params);

EXTERN U16 prc_snow_integrity(int number_of_pdu, 
         PRC_SNOW_INTEGRITY_DATA *pdu_list,
         int wait_mode, 
         PRC_CALLBACK_FUNC callback_func,
         void *callback_params);
#endif


