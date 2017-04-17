

/**********************************************************************
 
    Name:   UE Application interface with NHU[RRC]
 
    Type:   C include file
 
    Desc:   Defines required by UE Application interface with RRC
 
    File:   ue_nhu_app.x 
 
    Sid:      ue_nhu_app.x@@/main/1 - Sun Mar 28 22:59:25 2010
 
    Prg:    vp
 
**********************************************************************/
 
 
#ifndef __UE_NHU_APPX__
#define __UE_NHU_APPX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*    Crnti. Required to create a UE context. */
typedef U16 NhuCrnti;      

/*CellId. Required to create the Cell Cb. RRC user has to map the actual 
  CellId (bit string of size 28) into the U16.*/
typedef U16 NhuCellId;     

/*   This structure contains the CellId, UeId, RbId, and PdcpId. All the NHU
interface primitives carry this information. 
*/
typedef struct nhuHdr
{
   NhuCellId      cellId;   /* Cell ID */
   NhuCrnti       ueId;     /* Ue ID */
   U32            transId;  /* Transaction identifier for simultaneous 
                               procedures */
} NhuHdr;

typedef struct nhuUlCcchMsg
{
   NhuUL_CCCH_Msg     ccchMsg;
}NhuUlCcchMsg;

typedef struct nhuDlCcchMsg
{
   NhuDL_CCCH_Msg     ccchMsg;
}NhuDlCcchMsg;

typedef struct nhuUlDcchMsg
{
   NhuUL_DCCH_Msg     dcchMsg;
}NhuUlDcchMsg;

typedef struct nhuDlDcchMsg
{
   NhuDL_DCCH_Msg     dcchMsg;
}NhuDlDcchMsg;

/* Data Request SDUs containing UL-CCCH and UL-DCCH messages from 
   UE to eNodeB */
typedef struct nhuDatReqSdus     
{
   CmMemListCp          memCp;
   NhuHdr               hdr;   

   struct  
   {
      U8              msgCategory;
      union
      {
/* ue003.101: Paging and Broadcast changes */
         NhuPCCH_Msg      pcchMsg;       /*!< DL-PCCH-PCH SDU */
         NhuBCCH_DL_SCH_Msg bcchDlSchMsg;  /*!< DL-BCCH-DLSCH SDU */
         NhuUlCcchMsg       ulCcchMsg;
         NhuUlDcchMsg       ulDcchMsg;
      } m;    
   }sdu;   
} NhuDatReqSdus;

/* Data Request SDUs containing DL-CCCH and DL-DCCH messages from 
   eNodeB to UE */

typedef struct nhuDatIndSdus     
{
   CmMemListCp          memCp;
   NhuHdr               hdr;   
   struct  
   {
      U8              msgCategory;
      union   
      {
         NhuDlCcchMsg     dlCcchMsg;
         NhuDlDcchMsg     dlDcchMsg;
      } m;    
   }sdu;   
} NhuDatIndSdus;


/*
This structure contains the status information for DL DCCH RRC messages. The
status is indicated to the RRC user in NhUiNhuDatCfm.
This is used by RRC to indicate to the RRC user of any errors occurred during
PDCP or RLC transmission of the DL DCCH RRC message. The error causes are:
RLC maximum transmissions reached, but the message is not sent to UE.
PDCP SDU discard timer expired before sending the message to UE.
Based on the information present in this SDU, the RRC user might choose to take
different actions.*/
typedef struct nhuDatCfmSdus          
{
   NhuHdr           hdr;              /* SDU Header */
   U8               pdcpId;           /* PDCP ID */
   U8               datCfmStatus;     /* Data Confirm Status */
} NhuDatCfmSdus;

/* Application Lower Interface with dummy RRC */
EXTERN S16 UeAppLiNhuBndCfm ARGS((Pst     *pst,
                                  SuId    suId,
                                  U8      status));

EXTERN S16 UeAppLiNhuDatInd ARGS((Pst           *pst,          
                                  SuId           suId,
                                  NhuDatIndSdus *datIndSdus)); 


EXTERN S16 UeAppNhUiNhuDatReq ARGS((Pst         *pst,          
                                  SpId           spId,
                                  NhuDatReqSdus *datReqSdus)); 

EXTERN S16 UeAppLiNhuDatCfm ARGS((Pst *pst, 
                                  SuId suId, 
                                  NhuDatCfmSdus *datCfmSdus ));

/* Dummy RRC's upper interface with UE Application */
/* ue002.101: Multi ue support changes */
EXTERN S16 UeUiNhuDatReq ARGS((Pst           *pst,          
                               SpId           spId,
                               NhuDatReqSdus *datReqSdus,
                               U16            cellId,
                               U16            ueId)); 


EXTERN S16 ueAppActvInit ARGS((Ent    entity,       
                               Inst   inst,        
                               Region region,     
                               Reason reason));

EXTERN S16 ueAppActvTsk ARGS((Pst           *pst,
                              Buffer        *mBuf));

EXTERN S16 ueAppTmrInit ARGS((Void));
EXTERN S16 ueRrcEncRRCMsg
ARGS ((U8 msgCategory,NhuDatReqSdus *datReqSdu,Buffer **mBuf));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __UE_NHU_APPX__*/



/**********************************************************************
         End of file:     ue_nhu_app.x@@/main/1 - Sun Mar 28 22:59:25 2010
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       vp           1. Initial Release.
/main/1+    ue002.101  sv           1. Multi ue support changes.
/main/1+    ue003.101  rp           1. Paging and Broadcast support changes.
*********************************************************************91*/



