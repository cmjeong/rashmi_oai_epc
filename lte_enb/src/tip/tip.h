/**********************************************************************

  Name:     tip.h 
  
  Type:     C Include File 
  
  Desc:     Structures, variables, and typedefs commonly required by the 
            L3, Lower-L2 and Upper-L2 interface.

  File:     tip.h

  Prg:      Radisys 

**********************************************************************/

#ifndef __TIP_H__
#define __TIP_H__

/* Module Identities */
#define RRC_MOD_ID           100
#define PDCP_MOD_ID          200
#define DATARELAY_MOD_ID     210
#define RLC_MOD_ID           300
#define MAC_MOD_ID           310
#define PHY_MOD_ID           320

/* VM Synchronization message identifiers */
#define MAC_INIT_IND   100
#define MAC_INIT_REQ   101
#define MAC_INIT_RSP   102
#define RLC_INIT_IND   103
#define RLC_INIT_REQ   104
#define RLC_INIT_RSP   105
#define PDCP_INIT_IND  106
#define PDCP_INIT_REQ  107
#define PDCP_INIT_RSP  108
#define HEARTBEAT_REQ  109
#define HEARTBEAT_RSP  110

/**
 * @brief Packet format sent on the interface
 */
typedef struct tipPacket
{
   uint16_t        srcModId;    /*!< Sender module identity */
   uint16_t        dstModId;    /*!< Receiver module identity */
   uint16_t        cellId;      /*!< Cell identity */
   uint16_t        msgId;       /*!< Message/API identity */
   uint32_t        transId;     /*!< Transaction identity */
   uint16_t        pktLen;      /*!< Packet length (includes header length) */
   uint8_t         spare[2];       /*!< Spare */
   uint8_t         message[1];  /*!< Message/API content */
} TipPacket;

/**
 * @brief Init Indication message from L2U and L2L toward L3
 */
typedef struct initInd
{
   int8_t       l2IpAddr[16]; /*!< IPv4 address in string format */
} InitInd; 

/**
 * @brief Init Request message from L3 to L2U and L2L 
 */
typedef struct initReq
{
   int8_t       l2uIpAddr[16]; /*!< IPv4 address in string format */
   int8_t       l2lIpAddr[16]; /*!< IPv4 address in string format */
} InitReq;

/**
 * @brief Init Response message from L2U and L2L to L3
   Unused and Reserved
 */
typedef struct initRsp
{
   uint8_t         spare[4];       /*!< Spare */
} InitRsp;  
#endif
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
     1.1              radisys  1. Spare bit adjustment
     1.2              radisys  1. Spare bit adjustment
     1.3              radisys  1. INIT* messages for Multi-Cell
     1.4              radisys  1. Removal of spare
**********************************************************************/

