
/* CNM API messages */

#ifndef __WR_CNM_H__
#define __WR_CNM_H__

/* Macros for ICTA Msg Id's */
#define WR_CNM_ICTA_START_REQ   90
#define WR_CNM_ICTA_START_RESP  91
#define WR_CNM_ICTA_STOP_REQ    92
#define WR_CNM_ICTA_STOP_RESP   93
#define WR_CNM_ICTA_SYNC_IND    96
#define WR_CNM_ICTA_FOE_REQ     98
#define WR_CNM_ICTA_FOE_RESP    99

#define WR_CNM_MAX_VENDOR_LIST  6 /* same MAX_VENDOR_LIST listed in interface API header file */
#define WR_CNM_MAX_EARFCN_TABLE_SIZE 8 /* from freq band 33 to 40
                                        * For FDD, this needs to be modified
                                        * */
#define WR_CNM_RADIO_ELMNT_SIZE 20 /* From the CNM API doc */

typedef struct wrCnmIctaStartVendorSpcfc
{
   U8 ictaRadioAddElement[WR_CNM_RADIO_ELMNT_SIZE];
   U8 enbRadioAddElement[WR_CNM_RADIO_ELMNT_SIZE];
}__attribute__((__packed__))WrCnmIctaStartVendorSpcfc;

typedef struct wrCnmIctaStartMsg
{
    U16 msgLen;
    U8  msgType;
    U8  phyEntityId;
    U16 nghEarfcn; 
    U16 servEarfcn; 
    S16 nghPci;
    S16 nghCellCp;
    S16 nghSpecSfCfg;
    S16 nghTxAntCount;
    S16 nghTrackNRb;
    S16 trackPeriod;
    U8  vendorSpcfcLstCount;
    U8  radioChipType;
    WrCnmIctaStartVendorSpcfc vendorSpcfcLst;
} __attribute__ ((__packed__))WrCnmIctaStartMsg;


typedef struct wrCnmIctaStopMsg
{
    U16 msgLen;
    U8  msgType;
    U8  phyEntityId;
    U8  vendorSpcfcLstCount;
    U16 vendorSpcfcLst[WR_CNM_MAX_VENDOR_LIST];
} __attribute__ ((__packed__))WrCnmIctaStopMsg;

typedef struct wrCnmIctaFoeReqMsg
{
    U16 msgLen;
    U8  msgType;
    U8  phyEntityId;
    U8  vendorSpcfcLstCount;
    U16 vendorSpcfcLst[WR_CNM_MAX_VENDOR_LIST];
} __attribute__ ((__packed__))WrCnmIctaFoeReqMsg;


typedef struct wrCnmEarfcnTable
{
  U16   fDlLow;
  U16   nOffsetDl;
  U16   earfcnStart;
  U16   earfcnEnd;
  U8    freqBand;
}WrCnmEarfcnTable;
EXTERN S16 wrCnmTrigIctaFoeReq ARGS((Void));
EXTERN S16 wrCnmTrigIctaStartReq ARGS((Void));
#endif
