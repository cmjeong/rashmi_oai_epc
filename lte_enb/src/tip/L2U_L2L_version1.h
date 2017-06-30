/**********************************************************************

  Name:     L2U_L2L.h 
  
  Type:     C Include File 
  
  Desc:     Structures, variables, and typedefs required by the L2U<->L2L
             interface.

  File:     L2U_L2L.h

  Prg:      Radisys 

**********************************************************************/

#ifndef __L2U_L2L_H__
#define __L2U_L2L_H__

/* Message Identities */
#define RLC_SDU_STATUS_IND   701
#define PDCP_MSG_IND         702
#define RLC_DATAMSG_REQ      703
#define RLC_DATADISCARD_REQ  704

#define RLC_MAX_NUM_OF_SDU_ID 2048
#define RLC_MAX_DATA_BUFFER   1024
#define PDCP_MAX_DATA_BUFFER  1024

/**
  @brief Contains UE Index and CRNTI */
typedef struct ueIdentity
{
   uint16_t ueIndex;               /*!< UE Identity */
   uint16_t cRnti;                 /*!< C-RNTI */
}UeIdentity;

/**
  @brief Contains Radio Bearer and Logical Channel Identity */
typedef struct rbIdentity
{
   uint8_t rbId;                  /*!< Radio Bearer Identity */
   uint8_t lcId;                  /*!< Logical Channel Identity */
   uint8_t spare[2];              /*!< Added for 4byte alignment */
}RbIdentity;

typedef struct sduStatus
{
   uint32_t sduId;                  /*!< SDU Identity */
   Bool     status;                  /*!< Status- Success or Failure */
   uint8_t spare[3];              /*!< Added for 4byte alignment */
}SduStatus;


/**
  @brief RLC SDU STATUS IND */
typedef struct rlcSduStatusInd
{
    UeIdentity ueInfo;             /*!< Contains UE Identity */
    RbIdentity rbInfo;             /*!< Contains Radio bearer identity */
    uint32_t   numberOfSDU;        /*!< Number of SDUs for which
                                    * confirm is being sent */
    SduStatus  sduStatus[RLC_MAX_NUM_OF_SDU_ID]; /*!< SDU ID for AM */
}RlcSduStatusInd;

/**
  @brief PDCP MSG IND */
typedef struct pdcpMsgInd
{
    UeIdentity ueInfo;             /*!< Contains UE Identity */
    RbIdentity rbInfo;             /*!< Contains Radio bearer identity */
    uint32_t   datBufLen;         /*!< Data Buffer Length */
    uint8_t    reEstblishmentFlag; /*!< 0 (Normal packet), 
                                     1 (Packet received due 
                                       to RLC re-establishment) */
    uint8_t     spare[3];              /*!< Added for 4byte alignment */
    uint8_t    dataBuffer[1];     /*!< Data Buffer */
}PdcpMsgInd;


/**
  @brief RLC DataMsg Req */
typedef struct rlcDataMsgReq
{
    UeIdentity ueInfo;             /*!< Contains UE Identity */
    RbIdentity rbInfo;             /*!< Contains Radio bearer identity */
    uint32_t sduIdentity;          /*!< SDU ID value (same as TransID) */
    uint32_t dataBufLen;           /*!< SDU Data buffer Length */
    uint8_t  dataBuffer[1];        /*!< Data Buffer */
}RlcDataMsgReq; 

/**
  @brief RLC Data Discard Req */
typedef struct rlcDataDiscardReq
{
    UeIdentity ueInfo;                     /*!< Contains UE Identity */
    RbIdentity rbInfo;                     /*!< Contains Radio bearer 
                                            * identity */
    uint32_t numberOfSdu;                  /*!< Number of SDUs for which
                                            * discard is being sent */
    SduStatus  sduStatus[RLC_MAX_NUM_OF_SDU_ID]; /*!< SDU ID for AM */

}RlcDataDiscardReq;

#endif /* __L2U_L2L_H__ */

/**********************************************************************

         End of file:  
  
**********************************************************************/

/**********************************************************************
  
        Notes:
  
**********************************************************************/

/**********************************************************************
Put notes here
**********************************************************************/


/**********************************************************************
  
        Revision history:
  
**********************************************************************/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- -------  ----------------------------------------
     1.0        ---   radisys  1. initial release.
	 1.1        ---   radisys  1. UE and RB Identity 
	 1.2        ---   radisys  1. SDU Status
	 1.3        ---   radisys  1. Message Identities definition
	 1.4        ---   radisys  1. Removed spare from RlcDataMsgReq
    1.5        ---   radisys  1. Added spare bit in PdcpMsgInd
**********************************************************************/
