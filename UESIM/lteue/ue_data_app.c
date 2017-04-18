
/********************************************************************20**

     Name:     LTE UE Simulator

     Type:     C source file

     Desc:     This file contains call back functions for PJU
               interface.

     File:     ue_data_app.c

     Sid:      ue_data_app.c@@/main/1 - Sun Mar 28 22:59:22 2010

     Prg:      vp

*********************************************************************21*/

#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer defines */
#include "cm_tkns.h"       /* Common tokens defines */
#include "cm_mblk.h"       /* Common memory allocation library defines */
#include "cm_llist.h"      /* Common link list  defines  */
#include "cm_hash.h"       /* Common hashlist  defines */
#include "cm_inet.h"       /* common tokens */
#include "cm_lte.h"        /* Common LTE defines */
#include "cm_pasn.h"       /* Common Pasn includes */
#include <unistd.h>

#include "ue.h"            /* UE Includes */
#include "nhu_asn.h"
#include "nhu.h"
#include "ue_nhu_app.h"    /* UE App Interface with RRC */
#include "cm_emm_esm.h"    /* EMM-ESM Defines */
#include "cm_emm.h"        /* EMM Defines */
#include "cm_esm.h"        /* ESM Defines */
#include "ue_app.h"        /* UE application includes */
#include "ue_err.h"

/* ue002.101: Changes for supporting MSPD CL */
#ifdef YS_MSPD
#include "LtePhyL2Api.h" /* Phy api file */
#endif


/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */

#include "cm5.x"           /* Common timer library */
#include "cm_tkns.x"       /* Common tokens */
#include "cm_mblk.x"       /* Common memory allocation */
#include "cm_llist.x"      /* Common link list */
#include "cm_hash.x"       /* Common hashlist */
#include "cm_lib.x"
#include "cm_inet.x"       /* common tokens */
#include "cm_lte.x"       /*  Common UMTS includes */
#include "cm_pasn.x"       /* Common Pasn includes */
#include "nhu_asn.x"
#include "ue_nhu_app.x"    /* UE App Interface with RRC */
#include "ue_pju_app.x"    /* UE App Interface with RRC */
#include "cm_emm.x"        /* EMM Includes */
#include "cm_esm.x"        /* ESM Includes */
#include "cm_emm_esm.x"    /* EMM-ESM Includes */
#include "ue_app.x"        /* UE App Includes */
#include "ue_pju_app.x"        /* UE App Includes */


/* Following functions are implemented
*/

PRIVATE S16 ueAppInitEthPkt ARGS((Void));
PRIVATE Void ueAppSendEthPkt ARGS((U8  *ethPkt,
                                   U32 len));

PRIVATE S16 ueAppSendArpReqPkt ARGS(( U8  *ipAddr));

PRIVATE Void ueAppSendArpRspPkt ARGS(( CONSTANT U8  *arpReq, U32 length));

PRIVATE Void ueAppRcvdPktHndlr ARGS((u_char                   *args,
                                     const struct pcap_pkthdr *hdr,
                                     const u_char             *pktData));

/*ue008.101 : ADD: Fixed error for g++ compilation on Linux */
#ifdef __cplusplus   
EXTERN "C" {
#endif

/* ue006.101: Changes for end to end performance support */
EXTERN Void ueAppHndlIPPkt ARGS((CONSTANT U8  *ipPkt,
                                  U32          bytesRcvd));

#ifdef __cplusplus   
}
#endif
PRIVATE Void ueAppHndlARPResponse ARGS((CONSTANT U8  *arpPkt,
                                  U32          bytesRcvd));

PRIVATE Void ueAppHndlARPRequest ARGS((CONSTANT U8  *arpPkt,
                                  U32          bytesRcvd));

PRIVATE S16 ueAppGetNwParam ARGS((U32 selfIp));

PRIVATE S16 ueAppInitAdaptor ARGS((Void));

/* ue002.101: Multi ue support changes */
PRIVATE U8 * ueAppFindMACAddress ARGS((U32 ipAddr,U16 cellIdx,U16 ueIdx));

PRIVATE Void ueAppBuildEthPkt ARGS((U8   *ipPkt, 
                                    U32   len,
                                    U16   cellIdx,
                                    U16 ueIdx));



PRIVATE Void ueAppFragmentIPPkt ARGS((U8  *ipPkt, 
                                      U32  len,
                                      U16 cellIdx,
                                      U16 ueIdx));

PRIVATE Void* ueAppPktReceiver ARGS((Void *arg));

/*ue008.101 : Fixed error for g++ compilation on Linux */
#ifdef __cplusplus
EXTERN "C" {
#endif

/* Declaration of pcap_sendpacket() which is not present in pcap.h */
EXTERN int pcap_sendpacket(pcap_t *hdl, CONSTANT U8* buf, int len);

#ifdef __cplusplus   
}
#endif

/* ue006.101: Changes for end to end performance support */
PUBLIC U16 noAppSdus = 0;
/* ue002.101: Removed unnecessary code */

/*
 *
 *       Fun:   ueAppCfgrPdnAssignedAddr
 *
 *       Desc:  This function configures the IP address
 *              given by PDN gateway
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueAppCfgrPdnAssignedAddr
(
U32 pdnAsgndAddr,
U16 cellIdx,
U16 ueIdx
)
#else
PUBLIC S16 ueAppCfgrPdnAssignedAddr (pdnAsgndAddr,ueIdx)
U32 pdnAsgndAddr;
U16 cellIdx;
U16 ueIdx;
#endif
{
   S16 ret;
   U8 ipAddr[UE_APP_MAX_IP_ADDR_LEN];
   /* ue002.101: Multi ue support changes */
   UeAppDataCb *dataCb = NULLP;
   U8 idx;
   

   TRC2(ueAppCfgrPdnAssignedAddr);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppCfgrPdnAssignedAddr:Configuring the PDN assigned IP Address "));

   ipAddr[0] = (U8)((pdnAsgndAddr >> 24) & 0xff);
   ipAddr[1] = (U8)((pdnAsgndAddr >> 16) & 0xff);
   ipAddr[2] = (U8)((pdnAsgndAddr >> 8) & 0xff);
   ipAddr[3] = (U8)((pdnAsgndAddr & 0xff));
   
   /* ue002.101: Removed unnecessary code; Multi ue changes */
   printf("ueAppCfgrPdnAssignedAddr:Sending the ARP Request Packet for %d:%d:%d:%d\n",
       ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);

   /* Before sending the ARP request , update the ip2mac table for this UE */
   dataCb = &ueSimAppCb.dataCb;
   /* ue007.101: Changes */
   /* 
    * we should not reset entire table, just reset for this UE only 
    */
   cmMemset((U8 *)&dataCb->ip2Mac[cellIdx][ueIdx], 0, sizeof(UeAppDataRouteCb));
   dataCb->ip2Mac[cellIdx][ueIdx].ipAddr = pdnAsgndAddr; 

   for (idx = 0; idx < UE_APP_MAX_IP_ADDR_LEN; idx++)
   {
      dataCb->ip2Mac[cellIdx][ueIdx].ipAddrStr[idx] = (pdnAsgndAddr >> (8 * (3 - idx)));
   
   }
   /* Send the ARP request */
   ret = ueAppSendArpReqPkt(ipAddr);

   RETVALUE(ret);
}

/*
 *
 *       Fun:   ueAppInitEthPkt
 *
 *       Desc:  This function initializes the Ethernet Packet
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppInitEthPkt
(
Void
)
#else
PRIVATE S16 ueAppInitEthPkt (Void)
#endif
{
   U16 ethType = UE_APP_ETH_TYPE_IP;

/* ue002.101: Multi ue support changes */
   UeAppDataCb *dataCb = &ueSimAppCb.dataCb;

   TRC2(ueAppInitEthPkt)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppInitEthPkt:Initializing the Ethernet Packet"));

   /* Set the destination MAC address to broadcast address (all 0xff) */
   cmMemset(dataCb->ethPkt, 0xff, UE_APP_MAC_ADDR_LEN);

   /* Set the source MAC address to local MAC address */
   cmMemcpy(dataCb->ethPkt + UE_APP_MAC_ADDR_LEN, 
            dataCb->lclMACAddr, UE_APP_MAC_ADDR_LEN);

   /* Set the type of Ethernet packet to IP packet (0x0800) */
   cmMemcpy(dataCb->ethPkt + (UE_APP_MAC_ADDR_LEN * 2), 
            (U8 *)&ethType, 2);

   RETVALUE(ROK);

}/* End of ueAppInitEthPkt */

/*
 *
 *       Fun:   ueAppInitArpPkt
 *
 *       Desc:  This function initializes the ARP Packet
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppInitArpPkt
(
Void
)
#else
PRIVATE S16 ueAppInitArpPkt (Void)
#endif
{
   U16 ethType = UE_APP_ETH_TYPE_ARP;
   U16 ethProtocolType = UE_APP_ETH_TYPE_IP;
   U16 arpType = UE_APP_ARP_REQ;
   U16 arp_hardware_type_ethernet = 0x0100;
   U8  arp_hardware_size = 0x06;
   U8  arp_protocol_size = 0x04;
   UeAppDataCb *ueAppDataCb;
   U8 idx;

   TRC2(ueAppInitArpPkt)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppInitArpPkt:Initializing the ARP Packet"));

/* ue002.101: Multi ue support changes */
   ueAppDataCb = &(ueSimAppCb.dataCb);

   /* First Fill Ethenet Header */
   /* Set the destination MAC address to broadcast address and 
      set the source MAC address to local MAC address */
   cmMemcpy(ueAppDataCb->arpPkt, ueAppDataCb->ethPkt, UE_APP_MAC_ADDR_LEN * 2);
   idx = UE_APP_MAC_ADDR_LEN * 2;

   /* Set the type of Ethernet packet to ARP (0x0806) */
   cmMemcpy(ueAppDataCb->arpPkt + idx, (U8 *)&ethType, 2);

   /* Fill ARP packet (Ethernet payload) */
   idx += 2;
   /* Set the hardware type to Ethernet (0x0001) */
   cmMemcpy(ueAppDataCb->arpPkt + idx, (U8 *)&arp_hardware_type_ethernet, 2);
   idx += 2;

   /* Set the ethernet protocol type to IP (0x0800) */
   cmMemcpy(ueAppDataCb->arpPkt + idx, (U8 *)&ethProtocolType, 2);
   idx += 2;

   /* Set hardware size to 6 for Ethernet */
   cmMemcpy(ueAppDataCb->arpPkt + idx, &arp_hardware_size, 1);
   idx += 1;

   /* Set protocol size to 4 for IP */
   cmMemcpy(ueAppDataCb->arpPkt + idx, &arp_protocol_size, 1);
   idx += 1;

   /* Set operation to ARP request (0x0001) */
   cmMemcpy(ueAppDataCb->arpPkt + idx, (U8 *)&arpType, 2);
   idx += 2;

   /* Set the Sender Hardware Address to local MAC address */
   cmMemcpy(ueAppDataCb->arpPkt + idx, ueAppDataCb->lclMACAddr,
            UE_APP_MAC_ADDR_LEN);

   idx += UE_APP_MAC_ADDR_LEN;

   /* Set the Sender Protocol Address to local IP address */
   cmMemcpy(ueAppDataCb->arpPkt + idx, ueAppDataCb->ueAppIpAddrStr,
            UE_APP_MAX_IP_ADDR_LEN);

   idx += UE_APP_MAX_IP_ADDR_LEN;

   /* Initialise the Target Hardware Address and 
      Target Protocol Adress to 0xff */
   cmMemset(ueAppDataCb->arpPkt + idx, 0xff,
            UE_APP_MAC_ADDR_LEN + UE_APP_MAX_IP_ADDR_LEN);

   RETVALUE(ROK);

}/* End of ueAppInitArpPkt */


/*
 *
 *       Fun:   ueAppSendArpReqPkt
 *
 *       Desc:  This function sends the ARP request packet
 *
 *       Ret:   None
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppSendArpReqPkt
(
U8  *ipAddr
)
#else
PRIVATE S16 ueAppSendArpReqPkt (ipAddr)
U8  *ipAddr;
#endif
{
   U16 idx = 38; /* Index of ARP packet at which destination IP address
                    has to be added */

   TRC2(ueAppSendArpReqPkt)
   printf("ueAppSendArpReqPkt:Sending the ARP Request Packet\n");

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppSendArpReqPkt:Sending the ARP Request Packet for %d:%d:%d:%d",
       ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]));

   /* ue002.101: Multi ue support changes */
   /* Take the default ARP packet and add the destination IP address */
   cmMemcpy(ueSimAppCb.dataCb.arpPkt + 38, ipAddr, UE_APP_MAX_IP_ADDR_LEN);
   /* Send out ARP request packet */
   ueAppSendEthPkt(ueSimAppCb.dataCb.arpPkt, idx + 4);

   RETVALUE(ROK);

}/* End of ueAppSendArpReqPkt */


/*
 *
 *       Fun:   ueAppSendArpRspPkt
 *
 *       Desc:  This function sends the ARP response packet
 *
 *       Ret:   None
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE Void ueAppSendArpRspPkt
(
CONSTANT U8  *arpReqPkt,
U32          len
)
#else
PRIVATE Void ueAppSendArpRspPkt (arpReqPkt, len)
CONSTANT U8  *arpReqPkt;
U32          len;
#endif
{
   U8 arpRspPkt[UE_APP_MAX_ETH_PKT_LEN]; /* ARP Response packet */

   U16 ethType = UE_APP_ETH_TYPE_ARP;
   U16 arpType = UE_APP_ARP_RSP;

   U8 idx = 0;

   TRC2(ueAppSendArpRspPkt)

   /* Fill Ethernet header */
   /* Collect sender MAC address from ARP request packet and 
      add it as destination MAC address in the Ethernet header */
   cmMemcpy(arpRspPkt, arpReqPkt + 8, UE_APP_MAC_ADDR_LEN);
   idx += UE_APP_MAC_ADDR_LEN;

   /* Add local MAC address as source MAC address */
   /* ue002.101: Multi ue support changes */
   cmMemcpy(arpRspPkt + idx, ueSimAppCb.dataCb.lclMACAddr,
            UE_APP_MAC_ADDR_LEN);

   idx += UE_APP_MAC_ADDR_LEN;

   /* Set type of Ethernet packet to ARP packet (0x0806) */
   cmMemcpy(arpRspPkt + idx, (U8 *)&ethType, 2);
   idx += 2;

   /* Construct ARP response packet (Ethernet payload) */
   /* First 6 bytes are same for ARP request and response, hence
      copy from ARP request packet */
   cmMemcpy(arpRspPkt + idx, arpReqPkt, 6);
   idx += 6;

   /* Fill the ARP response code */
   cmMemcpy(arpRspPkt + idx, (U8 *)&arpType, 2);
   idx += 2;

   /* Fill local MAC address as the sender MAC address */
   /* ue002.101: Multi ue support changes */
   cmMemcpy(arpRspPkt + idx, ueSimAppCb.dataCb.lclMACAddr,
            UE_APP_MAC_ADDR_LEN);

   idx += UE_APP_MAC_ADDR_LEN;

   /* Collect target IP address from ARP request packet and 
      add it as sender IP address */
   /* NOTE: We should not add local IP address as sender IP address because
      we are only responding to an ARP request directed at an IP address
      allocated to the UE */
   cmMemcpy(arpRspPkt + idx, arpReqPkt + 24, UE_APP_MAX_IP_ADDR_LEN);
   idx += UE_APP_MAX_IP_ADDR_LEN;

   /* Collect sender IP address and MAC address from ARP request packet 
      and add them as target IP and MAC addresses */
   cmMemcpy(arpRspPkt + idx, arpReqPkt + 8, 10);
   idx += 10;


   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppSendArpRspPkt:Sending the ARP Response Packet to %d.%d.%d.%d",
      arpRspPkt[38], arpRspPkt[39], arpRspPkt[40], arpRspPkt[41]));
   /* Send out ARP response packet */

   ueAppSendEthPkt(arpRspPkt, idx);

   RETVOID;

}/* End of ueAppSendArpRspPkt */


/*
 *
 *       Fun:   ueAppSendEthPkt
 *
 *       Desc:  This function sends out Ethernet packet
 *
 *       Ret:   None
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE Void ueAppSendEthPkt
(
U8    *ethPkt,
U32    len
)
#else
PRIVATE Void ueAppSendEthPkt (ethPkt, len)
U8    *ethPkt;
U32    len;
#endif
{
   S16 ret;

   TRC2(ueAppSendEthPkt)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppSendEth:Sending the Ethernet Packet"));
   /* Send out Ethernet packet using PCAP library function */
   /* ue002.101: Multi ue support changes */
   ret = pcap_sendpacket(ueSimAppCb.dataCb.dataHdlr, ethPkt, (S32)len);
   if (0 != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE037, (ErrVal)0,
         " ueAppSendEth:Failed to send Ethernet packet through interface\n"); 
   }

   RETVOID;
}/* End of ueAppSendEthPkt */


/*
 *
 *       Fun:   ueAppPktReceiver
 *
 *       Desc:  This function receives packets from network interface
 *
 *       Ret:   NULLP
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PUBLIC Void *ueAppPktReceiver
(
Void *arg
)
#else
PUBLIC Void *ueAppPktReceiver (arg)
Void *arg;
#endif
{
   /* Read packets from Ethernet interface and invoke ueAppRcvdPktHndlr
      callback function for every packet read */
   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppPktReceiver:Processing the received  Ethernet Packet"));
   /* ue002.101: Multi ue support changes */
   pcap_loop(ueSimAppCb.dataCb.dataHdlr, -1, ueAppRcvdPktHndlr, NULLP);

   RETVALUE(NULLP);
}/* End of ueAppPktReceiver */
/* ue006.101: Changes for end to end performance */
/*
 *       Fun:  ueAppDlvrIpPkt 
 *
 *       Desc:  This function posts packets to itself from network interface
 *
 *       Ret:   void 
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE Void ueAppDlvrIpPkt
(
const u_char   *pktData,
U32           bytesRcvd
)
#else
PRIVATE Void ueAppDlvrIpPkt(pktData,bytesRcvd)
const u_char *pktData;
U32   bytesRcvd;
#endif
{
   Buffer                *mBuf;
   Pst                   pst;

   TRC2(ueAppDlvrIpPkt)

   UE_ALLOC_BUF(mBuf);
   if (mBuf == NULLP)
   {
      RETVOID;
   }
   if (SAddPstMsgMult((Data *)pktData, bytesRcvd, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVOID;
   }
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
   pst.dstEnt = UE_ENT_APP;
   pst.srcEnt = UE_ENT_APP;
   pst.srcInst = 0;
   pst.dstInst = 0;
   pst.route = RTESPEC;
   pst.prior = PRIOR0;
   pst.region = UE_REGION;
   pst.pool = UE_POOL;
   
   SPstTsk(&pst, mBuf);

   RETVOID;
}
/*
 *
 *       Fun:   ueAppRcvdPktHndlr
 *
 *       Desc:  This is the callback function of pcap_loop
 *
 *       Ret:   None
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE Void ueAppRcvdPktHndlr
(
u_char                   *args,
const struct pcap_pkthdr *hdr,
const u_char             *pktData
)
#else
PRIVATE Void ueAppRcvdPktHndlr (args, hdr, pktData)
u_char                   *args;
const struct pcap_pkthdr *hdr;
const u_char             *pktData;
#endif
{
   U16 pktType;
   U32 bytesRcvd;

   TRC2(ueAppRcvdPktHndlr)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppRcvdPktHndlr:Processing the received  Ethernet Packet"));

   bytesRcvd = hdr->caplen;

   /* Find out the type of Ethernet packet (bytes 12-13 in Ethernet header),
      handle IP and ARP packets */
   pktType = (pktData[13] << 8) + pktData[12];
   if (pktType == UE_APP_ETH_TYPE_IP)
   {
      /* Handle the IP packet */
      /* ue006.101: Changes for end to end performance */
      /* Deliver the packet to APP task which should be same one as RLC */
         noAppSdus++;
         ueAppDlvrIpPkt(pktData, bytesRcvd);

   }
   else if (pktType == UE_APP_ETH_TYPE_ARP)
   {
      if (((U16)pktData[21] << 8 | pktData[20]) == UE_APP_ARP_RSP)
      {
         ueAppHndlARPResponse(pktData + 14, bytesRcvd);
      }
      else
      {
         ueAppHndlARPRequest(pktData + 14, bytesRcvd);
      }
   }
   else
   {
#if 0
      printf("\n *****************%d *************\n", pktType);
      UELOGERROR(ERRCLS_ADD_RES, EUE038, (ErrVal)pktType,
         " ueAppRcvdPktHndlr:Unknown packet type received\n"); 
#endif
   }

   RETVOID;
}/* End of ueAppRcvdPktHndlr */


/*
 *
 *       Fun:   ueAppHndlARPRequest
 *
 *       Desc:  This function handles the ARP request packet from client
 *
 *       Ret:   None
 *
 *       Notes: IP address conflict is not handled in this release
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE Void ueAppHndlARPRequest
(
CONSTANT U8  *arpPkt,
U32          bytesRcvd
)
#else
PRIVATE Void ueAppHndlARPRequest (arpPkt, bytesRcvd)
CONSTANT U8  *arpPkt;
U32          bytesRcvd;
#endif
{
   /* ue008.101 : TIC_ID : ccpu00117550 DEL: Deleted unused variable for warning removal on CentOS*/

   TRC2(ueAppHndlARPRequest)

   /* ue007.101: changes */
   /* irrespective of the destination address,
    * ue simulator should pass the arp request to the PDN 
    * */
   ueAppSendArpRspPkt(arpPkt, bytesRcvd);

   RETVOID;
}/* End of ueAppHndlARPRequest */

/*
 *
 *       Fun:   ueAppHndlARPResponse
 *
 *       Desc:  This function handles the ARP response packet
 *
 *       Ret:   None
 *
 *       Notes: IP address conflict is not handled in this release
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE Void ueAppHndlARPResponse
(
CONSTANT U8  *arpPkt,
U32          bytesRcvd
)
#else
PRIVATE Void ueAppHndlARPResponse (arpPkt, bytesRcvd)
CONSTANT U8  *arpPkt;
U32          bytesRcvd;
#endif
{
   /* ue002.101: Multi ue support changes */
   UeAppDataCb *dataCb = &ueSimAppCb.dataCb;
   UeAppCb *ueAppCb;
   U8  idx;
   U8  cIdx;
   U32 dstIPAddr;

   TRC2(ueAppHndlARPResponse)

   printf("ueAppHndlARPResponse:Received ARP Response\n");
   if (dataCb->mapCnt >= UE_APP_MAX_CONNS)
   {
      RETVOID;
   }

   dstIPAddr = (arpPkt[14] << 24) + (arpPkt[15] << 16) + 
               (arpPkt[16] << 8) + arpPkt[17];
   for (idx = 0; idx < dataCb->mapCnt; idx++)
   {
      /* Add the received sender MAC address and IP address to IP->MAC map. If
      this is the MAC address of gateway then store it in routeCb */
      cIdx = (dataCb->mapCnt % UE_NUM_PER_CELL);

      if (dstIPAddr == dataCb->ip2Mac[cIdx][idx].ipAddr)
      {
         UE_DBGP_INFO((UE_PRNTBUF,
             "ueAppHndlARPResponse:Received ARP Response for %d.%d.%d.%d",
             arpPkt[14],arpPkt[15], arpPkt[16], arpPkt[17]));
         cmMemcpy((U8 *)&(dataCb->ip2Mac[cIdx][idx].macAddr),
         arpPkt + 8, UE_APP_MAC_ADDR_LEN);

         /* ue002.101: Multi ue support changes */
         ueAppCb = &ueSimAppCb.cellCb[cIdx].ueAppCbLst[idx];
         if(ueAppCb != NULLP)
         {
#ifndef ENB_PERF_MEAS
            ueAppSndArpCompInd(ueAppCb);
#else
/* ue003.101: TransactionId is added as a parameter */ 
            ueAppLimHdlRRCConReCfg(ueAppCb, 0);
#endif /* ENB_PERF_MEAS */
         }
         else
         {
            /* ue007.101: Fix to ccpu00117388 */
            /* Compilation error ERRCLS defined in make file */
            UELOGERROR(ERRCLS_ADD_RES, EUE016, (ErrVal)idx,
            "ueAppHndlARPResponse : NULL ueAppCb \n");
         }
         RETVOID;
      }
   }
   /* This MAC Map list is mainted to save time in ARP request/responses. 
      Wrap around, if the list is overflowing */
/* No need to increment the count */
   /*
   dataCb->mapCnt =
               (dataCb->mapCnt + 1) % UE_APP_MAX_CONNS;
               */
   RETVOID;
}/* End of ueAppHndlARPResponse */

/*
 *
 *       Fun:   ueAppHndlIPPkt
 *
 *       Desc:  This function handles the received IP packet
 *
 *       Ret:   None
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PUBLIC Void ueAppHndlIPPkt
(
CONSTANT U8  *pkt,
U32           bytesRcvd
)
#else
PUBLIC Void ueAppHndlIPPkt (pkt, bytesRcvd)
CONSTANT U8  *pkt;
U32           bytesRcvd;
#endif
{
   U32  srcIPAddr;
   /* ue008.101 : TIC_ID : ccpu00117550 DEL: Deleted unused variable for warning removal on CentOS*/
   CONSTANT U8 *ipPkt = pkt + 14;
  /* ue002.101: Multi ue support changes */
   U16  cellIdx;
   UeAppCellCb *cell;
   U16  ueIdx;
   UeAppCb *ueAppCb = NULLP;

   TRC2(ueAppHndlIPPkt)

   /* Check the source IP address. If it is one of our IP addresses,
      process the packet. Otherwise ignore the packet. */
   /* NOTE: Here, our IP addresses refer to the IP addresses allocated by
      UESIM to UE SIM Client through PDP context activation accept */
   srcIPAddr = (ipPkt[12] << 24) + (ipPkt[13] << 16) +
               (ipPkt[14] << 8 ) + ipPkt[15];
   if( ipPkt[20] != 0x8 )
   {
       printf("\n PING RESPONSE PACKET IS RECEIVED WITH PACKET TYPE [%d]\n", ipPkt[20] );  
   }
   for (cellIdx=0; cellIdx < UE_NUM_CELL; cellIdx++)
   {
      cell = &ueSimAppCb.cellCb[cellIdx];
      /* ue002.101: Multi ue support changes */
      for(ueIdx=0;ueIdx < UE_NUM_PER_CELL;ueIdx++)
      {
        if(srcIPAddr == cell->ueAppCbLst[ueIdx].ueCtxt.selfAddr.u.ipv4NetAddr)
        {
           /* This is the IP address assigned to UE for PDN Connection */
           ueAppCb = &cell->ueAppCbLst[ueIdx];
           break;
        }
      }
      if (ueAppCb != NULLP)
      {
         break;
      }
   }
   if(ueAppCb == NULLP)
   {
      /* If ue not found just return */
      RETVOID;
   }
   /*ue008.101 Triggering Service Request procedure*/
   if(ueAppCb->ecmCb.state ==  UE_ECM_IDLE)
   {
      ueAppSndServiceReqMsg(ueAppCb);
      RETVOID;
   }/* end of if statement */

   /* ue007.101: ccpu00116719 changes */
   /* we want to access any IP which is reachable through the extenal GW
    * we are no more restricted to a particular data server
    */

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppHndlIPPkt:Sending the packet to PDCP "));
   /* Send the IP packet to eNodeB, exclude Ethernet header 
      portion of first 14 bytes */

   /* ue002.101: Multi ue support changes */
   ueAppLimSndPdcpMsg(ipPkt, bytesRcvd - 14,ueAppCb);

   RETVOID;
}/* End of ueAppHndlIPPkt */




/*
 *
 *       Fun:   ueAppGetNwParam
 *
 *       Desc:  This function gets the Network paramters Ethernet Interface,
 *              MAC address and gateway IP address
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppGetNwParam
(
U32 selfIp
)
#else
PRIVATE S16 ueAppGetNwParam (selfIp)
U32 selfIp;
#endif
{
   struct ifreq       *ifr;
   struct ifconf      ifc;
   struct in_addr     *addr;
   struct sockaddr_in sa;
   S32                sockfd;
   S32                ifclen;
   U8                 found = FALSE;

   TRC2(ueAppGetNwParam)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppGetNwParam:getting the network parameters"));

   /* Open a socket for ioctl */
   if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE040, (ErrVal)0,
         "ueAppGetNwParam:Failed to open a socket\n"); 
      perror("socket");
      close(sockfd);
      RETVALUE(RFAILED);
   }

   /* Get the length of configuration info of all interfaces */
   cmMemset((U8 *)&ifc, 0, sizeof(struct ifconf));
   if (ioctl(sockfd, SIOCGIFCONF, &ifc))
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE041, (ErrVal)0,
        "ueAppGetNwParam:Failed to get length of config info of interfaces\n"); 
      perror("ioctl SIOCGIFCONF");
      close(sockfd);
      RETVALUE(RFAILED);
   }
   ifclen = ifc.ifc_len;

   /* Get the configuration info of all interfaces */
   cmMemset((U8 *)&ifc, 0, sizeof(struct ifconf));

   UEAPP_ALLOC((&ifc.ifc_req), ifclen);

   if (NULLP == ifc.ifc_req)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE042, (ErrVal)ifclen,
         "ueAppGetNwParam: Failed to alloc memory for ifc.ifc_req\n"); 
      /* ue002.101: kworks_fix */
      close(sockfd);
      RETVALUE(RFAILED);
   }

   ifc.ifc_len = ifclen;
   if (ioctl(sockfd, SIOCGIFCONF, &ifc))
   {

      UELOGERROR(ERRCLS_ADD_RES, EUE043, (ErrVal)0,
         "ueAppGetNwParam: Failed to get config info of all interfaces\n"); 

      perror("ioctl SIOCGIFCONF");
      UEAPP_FREE(ifc.ifc_req, ifclen);

      close(sockfd);
      RETVALUE(RFAILED);
   }

   /* Get the ethernet interface name and address matching the selfIp from
      all configured interfaces */
   for (ifr = ifc.ifc_req; 
        (ifr && ((char *)ifr < (char *) ifc.ifc_req + ifc.ifc_len)); ++ifr)
   {
      addr = ((struct in_addr *) &ifr->ifr_addr.sa_data[sizeof(sa.sin_port)]);

      if (htonl(addr->s_addr) == selfIp)
      {
         /* Found the interface matching selfIp, get other details */
         strcpy(ueSimAppCb.dataCb.ethInf, ifr->ifr_name);

         /* Get Ethernet (Hardware) Address */
         if (ioctl(sockfd, SIOCGIFHWADDR, ifr))
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE044, (ErrVal)0,
               "ueAppGetNwParam: Failed to get Ethernet address\n"); 
            perror("ioctl SIOCGIFHWADDR");

            UEAPP_FREE(ifc.ifc_req, ifclen);
            close(sockfd);
            RETVALUE(RFAILED);
         }
         cmMemcpy(ueSimAppCb.dataCb.lclMACAddr, (U8 *)ifr->ifr_addr.sa_data, 
                  UE_APP_MAC_ADDR_LEN);
         found = TRUE;
         break;
      }
   }

   UEAPP_FREE(ifc.ifc_req, ifclen);
   close(sockfd);

   if (FALSE == found)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE045, (ErrVal)0,
         "ueAppGetNwParam: Failed to get network parameters\n"); 
      RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);
}/* End of ueAppGetNwParam */


/*
 *
 *       Fun:   ueAppInitAdaptor
 *
 *       Desc:  This function opens Ethernet adaptor for capturing packets
 *              and creates a thread for capturing packets
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppInitAdaptor
(
Void
)
#else
PRIVATE S16 ueAppInitAdaptor (Void)
#endif
{
   S8             errBuf[PCAP_ERRBUF_SIZE];

   TRC2(ueAppInitAdaptor)

   /* Open the Ethernet Adaptor with LibPCAP  */
   /* ue002.101: Multi ue support changes */
   ueSimAppCb.dataCb.dataHdlr = pcap_open_live(ueSimAppCb.dataCb.ethInf, 
                                        UE_APP_PCAP_BUF_SIZE,
                                        TRUE, UE_APP_PCAP_TIMEOUT, errBuf);
   if (NULLP == ueSimAppCb.dataCb.dataHdlr)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE046, (ErrVal)0,
         "ueAppInitAdaptor: Error opening network adaptor\n"); 
      RETVALUE(RFAILED);
   }
   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppInitAdaptor:Initialized the Eth interface for capturing packets"));

   RETVALUE(ROK);
}/* End of ueAppInitAdaptor */



/*
 *
 *       Fun:   ueAppRouteInit
 *
 *       Desc:  This function initializes the routing related params
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueAppRouteInit
(
)
#else
PUBLIC S16 ueAppRouteInit ()
#endif
{
   UeAppDataCb *dataCb = NULLP;
   pthread_t pcapTid;
  /* ue002.101: Removed unnecessary code */
   U8   idx;
   U8  *addr;
   S16  ret;

   TRC2(ueAppRouteInit)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppRouteInit:Initializing the Route Parameters"));
   /* This function is invoked by the UE sender task as Receive
   task would have been just created */

   /* ue002.101: Multi ue support changes */
   dataCb = &ueSimAppCb.dataCb;


   /* Store the UE IP Address */
   /* ue002.101: Multi ue support changes:
     ueIpAddr is no longer needed since we have
     the srcIpAddr in ueAppCb */

   /* Store the UE App IP Address */
   dataCb->ueAppIpAddr = UE_APP_SELF_ETH_INF_ADDR;

   /* Save the U32 local s IP address in byte array form
      to save time in future */
   for (idx = 0; idx < UE_APP_MAX_IP_ADDR_LEN; idx++)
   {
      dataCb->ueAppIpAddrStr[idx] = dataCb->ueAppIpAddr >> (8 * (3 - idx));
   }

   /* Store the Data server IP Address and port */
   dataCb->ueAppDstAddr = UE_APP_DATA_SRVR_ADDR;
   dataCb->ueAppDstPort = UE_APP_DATA_SRVR_PORT;

   /* Save the U32 local s IP address in byte array form
      to save time in future */
   for (idx = 0; idx < UE_APP_MAX_IP_ADDR_LEN; idx++)
   {
      dataCb->ueAppDstAddrStr[idx] = dataCb->ueAppDstAddr >> (8 * (3 - idx));
   }

   /* The proxy server port */
   dataCb->proxyPort = UE_APP_PROXY_PORT;

   /* The no of UE app clients, currently is UE_NUM_PER_CELL */
   dataCb->mapCnt = UE_NUM_PER_CELL * UE_NUM_CELL;

   /* Initialize IP to MAC Mapping Table */
   cmMemset((U8 *)&dataCb->ip2Mac, 0,
                  sizeof(UeAppDataRouteCb) * (UE_NUM_CELL * UE_NUM_PER_CELL));

   /* ue002.101: Multi ue support changes.
     UE client address gets updated when Attach accept comes from CN */

   /* Get Network Parameters using self assigned IP Address */
   ret = ueAppGetNwParam(dataCb->ueAppIpAddr);
   if (ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE047, (ErrVal)0,
         "ueAppRouteInit: Failed to get UE network parameters\n"); 
      RETVALUE(RFAILED);
   }

   addr = dataCb->lclMACAddr;

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppRouteInit: Ethernet address :  %x:%x:%x:%x:%x:%x", addr[0],
      addr[1], addr[2], addr[3], addr[4], addr[5]));

   addr = dataCb->ueAppIpAddrStr;

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppRouteInit: UE  App (Proxy) IP address : %d.%d.%d.%d", addr[0],
      addr[1], addr[2], addr[3]));

   /* Initialize Ethernet packet */
   ret = ueAppInitEthPkt();
   if (ret != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE048, (ErrVal)0,
         "ueAppRouteInit: Failed to initialise Ethernet Packet\n"); 
      RETVALUE(RFAILED);
   }

   /* Initialize ARP packet */
   ret = ueAppInitArpPkt();
   if (ret != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE049, (ErrVal)0,
         "ueAppRouteInit: Failed to initialise ARP Packet\n"); 
      RETVALUE(RFAILED);
   }

   /* Open the adaptor for capturing packets - LibPcap */
   ret = ueAppInitAdaptor();
   if (ret != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE050, (ErrVal)0,
         "ueAppRouteInit: Failed to initialise UE Adaptor\n"); 
      RETVALUE(RFAILED);
   }

   /* Create the thread for capturing the packets */
   if (pthread_create(&pcapTid, NULLP, ueAppPktReceiver, NULLP))
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE051, (ErrVal)0,
         "ueAppRouteInit: ueAppPktReceiver thread creation failed\n"); 
      RETVALUE(RFAILED);
   }

   /* ue002.101: Removed unnecessary code */
   /* Send Gratuitous ARP Request to inform all the clients
      on this ethernet interface for Destination Server */
/*   ueAppSendGratArpReqPkt(dataCb->ueAppDstAddrStr);*/

   RETVALUE(ROK);
}/* End of ueAppRouteInit */

/*
 *
 *       Fun:   ueAppFindMACAddress
 *
 *       Desc:  This function finds the MAC address corresponding to an
 *              IP address from the IP->MAC map
 *
 *       Ret:   Pointer to a MAC address (U8 *)
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE U8 * ueAppFindMACAddress
(
U32 ipAddr,
U16 cellIdx,
U16 ueIdx
)
#else
PRIVATE U8 * ueAppFindMACAddress (ipAddr, ueIdx)
U32 ipAddr;
U16 cellIdx;
U16 ueIdx;
#endif
{
   TRC2(ueAppFindMACAddress)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppFindMACAddress:Finding the MAC address"));

   /* search for MAC address mapped to the ipAddr */
   /* ue002.101: Multi ue support changes */
   if (ipAddr == ueSimAppCb.dataCb.ip2Mac[cellIdx][ueIdx].ipAddr)
   {
      RETVALUE(ueSimAppCb.dataCb.ip2Mac[cellIdx][ueIdx].macAddr);
   }

   /* Retrun UE Client MAC address if no MAC address is found in the map */
   RETVALUE(NULLP);

}/* End of ueAppFindMACAddress */

/*
 *
 *       Fun:   ueAppBuildEthPkt
 *
 *       Desc:  This function encapsulate IP packet in to Ethernet packet
 *
 *       Ret:   None
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE Void ueAppBuildEthPkt
(
U8   *ipPkt, 
U32   len,
U16   cellIdx,
U16   ueIdx
)
#else
PRIVATE Void ueAppBuildEthPkt (ipPkt, len, ueIdx)
U8   *ipPkt; 
U32   len;
U16   cellIdx;
U16   ueIdx;
#endif
{
   U32  dstIPAddr;
   U8  *dstMACAddr;
  /* ue002.101: Multi ue support changes */
   UeAppDataCb *dataCb = &ueSimAppCb.dataCb;

   TRC2(ueAppBuildEthPkt)
   
   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppBuildEthPkt:Encapsulating IP packet in a Eth packet"));
   /* Copy IP packet into Ethernet payload */
   cmMemcpy(dataCb->ethPkt + 14, ipPkt, len);

   /* Find out the destination MAC address using destination IP address */
   dstIPAddr = (dataCb->ethPkt[30] << 24) + (dataCb->ethPkt[31] << 16) +
               (dataCb->ethPkt[32] << 8) + dataCb->ethPkt[33];

   /* Search the MAC map for destination MAC address */
   /* ue002.101: Multi ue support changes */
   dstMACAddr = ueAppFindMACAddress(dstIPAddr, cellIdx,ueIdx);
   if(dstMACAddr == NULLP)
   {
      printf("could not find MAC address\n");
      RETVOID;
   }

   /* Copy the destination MAC address */
   cmMemcpy(dataCb->ethPkt, dstMACAddr, UE_APP_MAC_ADDR_LEN);

   RETVOID;
}/* End of ueAppBuildEthPkt */

/*
 *
 *       Fun:   ueAppCalcIPChecksum
 *
 *       Desc:  This function calculates the 16 bit IP header checksum
 *
 *       Ret:   U16, checksum
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PUBLIC U16 ueAppCalcIPChecksum
(
U8   *ipPkt, 
U32   ipHdrLen
)
#else
PUBLIC U16 ueAppCalcIPChecksum (ipPkt, ipHdrLen)
U8   *ipPkt; 
U32   ipHdrLen;
#endif
{
   U16 word;
   U16 idx;
   U32 chksum = 0;

   TRC2(ueAppCalcIPChecksum)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppCalcIPChecksum:Calculating IP check sum"));
   /* Make 16 bit words out of every two adjacent 8 bit octets in
      the packet and add them up */
   for (idx = 0; idx < ipHdrLen; idx += 2)
   {
      word = (((U16)ipPkt[idx] << 8) & 0xFF00) + (ipPkt[idx + 1] & 0xFF);
      chksum += (U32)word;
   }

   /* Take only 16 bits out of the 32 bit checksum */
   while (chksum >> 16)
   {
      chksum = (chksum & 0xFFFF) + (chksum >> 16);
   }

   /* One's complement the result */
   chksum = ~chksum;

   /* Return the 16 bit checksum */
   RETVALUE((U16)chksum);
}/* End of ueAppCalcIPChecksum */

/*
 *
 *       Fun:   ueAppFragmentIPPkt
 *
 *       Desc:  This function fragments the IP packet
 *
 *       Ret:   None
 *
 *       Notes: none
 *
 *       File:  ue_data_app.c
 *
 */
#ifdef ANSI
PRIVATE Void ueAppFragmentIPPkt
(
U8  *ipPkt, 
U32  len,
U16 cellIdx,
U16 ueIdx
)
#else
PRIVATE Void ueAppFragmentIPPkt (ipPkt, len, ueIdx)
U8  *ipPkt; 
U32  len;
U16 cellIdx;
U16 ueIdx;
#endif
{
   U8  *ipHdr;
   U32 ipHdrLen;
   U32 bytesSent;
   U8  ipPacket[UE_APP_MAX_IP_PKT];
   U32 bytesRemaining;
   U32 maxIPDatSize;
   U32 fragOffset;
   U32 totLen;
   U32 dataSent;
   U16 ipChksum;

   TRC2(ueAppFragmentIPPkt)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppFragmentIPPkt:Fragmenting IP packet of len %ld",len));

   /* Initialise variables */
   ipHdr = ipPkt; /* Copy IP header pointer */
   ipHdrLen = (ipPkt[0] & 0xF) * 4;
   bytesSent = ipHdrLen;
   bytesRemaining = len - bytesSent;
   maxIPDatSize = UE_APP_MAX_IP_PKT - ipHdrLen;
   fragOffset = 0;

   /* Loop for fragmenting the IP packets */
   while (bytesRemaining > 0)
   {
      /* Copy the original IP header to IP fragment and modify 
         the header to reflect fragmentation */
      cmMemcpy(ipPacket, ipHdr, ipHdrLen); 

      /* Set more flag in the IP header if this is not the last IP fragment */
      if (bytesRemaining > maxIPDatSize)
      {
         ipPacket[6] |= (0x1 << 5);
      }
      
      /* Set fragment offset */
      ipPacket[6] |= (U8)((fragOffset >> 8) & 0x1F);
      ipPacket[7] = (U8)(fragOffset & 0xFF);

      if (bytesRemaining > maxIPDatSize)
      {
         totLen = UE_APP_MAX_IP_PKT;
      }
      else
      {
         totLen = bytesRemaining + ipHdrLen;
      }

      dataSent = totLen - ipHdrLen;
      if (bytesRemaining > maxIPDatSize)
      {
         U32 bytesToSend;

         /* If there are more fragments, send multiple of 8 octets as data */
         bytesToSend = dataSent % 8;
         dataSent -= bytesToSend;
         totLen -= bytesToSend;
      }

      /* Change total length */
      ipPacket[2] = (U8)((totLen >> 8) & 0xFF);
      ipPacket[3] = (U8)(totLen & 0xFF);

      /* Calculate the IP header checksum */
      ipChksum = ueAppCalcIPChecksum(ipPacket, ipHdrLen);

      /* Copy new IP header checksum */
      ipPacket[10] = (ipChksum >> 8) & 0xFF;
      ipPacket[11] = ipChksum & 0xFF;

      /* Copy the data to IP packet */
      cmMemcpy(ipPacket + ipHdrLen, ipHdr + bytesSent, dataSent);

      /* Encapsulate IP packet in an Ethernet packet */
      /* ue002.101: Multi ue support changes */ 
      ueAppBuildEthPkt(ipPacket, totLen,cellIdx, ueIdx);

      UE_DBGP_INFO((UE_PRNTBUF,
          "ueAppFragmentIPPkt:Sending IP fragment from %d.%d.%d.%d to %d.%d.%d.%d",
             ipPkt[12], ipPkt[13], ipPkt[14], ipPkt[15],
             ipPkt[16], ipPkt[17], ipPkt[18], ipPkt[19]));

      printf(
          "ueAppFragmentIPPkt:Sending IP fragment from %d.%d.%d.%d to %d.%d.%d.%d",
             ipPkt[12], ipPkt[13], ipPkt[14], ipPkt[15],
             ipPkt[16], ipPkt[17], ipPkt[18], ipPkt[19]);

      /* Send out Ethernet packet */
      /* ue002.101: Multi ue support changes */
      ueAppSendEthPkt(ueSimAppCb.dataCb.ethPkt, (totLen + 14));
      
      /* Update variables */
      bytesSent += dataSent;
      bytesRemaining -= dataSent;
      fragOffset += ((dataSent + 7) / 8);
   }

   RETVOID;
}/* End of ueAppFragmentIPPkt */


/*
*
*       Fun:   ueAppFrwdIpPkt - Function to forward the IP packet to the client
*
*       Desc:  This function is used to present Data to video client.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ue_data_app.c
*
*/

#ifdef ANSI
PUBLIC S16 ueAppFrwdIpPkt
(
U8 *ipPkt,
U32 len,
U16 cellIdx,
U16 ueIdx
)
#else
PUBLIC S16 ueAppFrwdIpPkt (ipPkt, len, ueIdx)
U8 *ipPkt;
U32 len;
U16 cellIdx;
U16 ueIdx;
#endif
{
#ifdef CNE_UESIM_DEBUG
   U16 indx;
#endif

   TRC2(ueAppFrwdIpPkt)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppFrwdIpPkt: Forwarding the IP packet to client"));

   if(len > UE_APP_MAX_ETH_PKT_LEN)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE052, (ErrVal)len,
         "ueAppFrwdIpPkt: Failed to send the Packet as it  exceeds Max\
          Ethernet Packet Size Size of Packet\n"); 
      RETVALUE(RFAILED);
   }

   /* Check if this port falls in the range of the ports which was initially
       assigned as part of packet filter cb. */
   /* If within range just send the packet to external network, else
      update our packet filter control block */

   /* Fragment the IP packet if its length is greater than the 
      Maximum data size */
   if (len < UE_APP_MAX_IP_PKT)
   {
      /* ue002.101: Removed unnecessary code */
      /* Encapsulate the IP packet in an Ethernet packet */
      ueAppBuildEthPkt(ipPkt,len,cellIdx,ueIdx);

      UE_DBGP_INFO((UE_PRNTBUF,
          "ueAppFrwdIpPkt: Received IP packet from eNodeB: SRC from \
           %d.%d.%d.%d to %d.%d.%d.%d", ipPkt[12], ipPkt[13], ipPkt[14],
           ipPkt[15],ipPkt[16], ipPkt[17], ipPkt[18], ipPkt[19]));

#ifdef CNE_UESIM_DEBUG
      for(indx = 0; indx< (len); indx++)
      {
         printf("%02x ", ipPkt[indx]);
      }
#endif
      /* Send out Ethernet packet */
      ueAppSendEthPkt(ueSimAppCb.dataCb.ethPkt, len + 14);
   }
   else
   {
      /* Fragment IP packet */
      /* ue002.101: Multi ue support changes */
      ueAppFragmentIPPkt(ipPkt, len,cellIdx,ueIdx);
   }

   RETVALUE(ROK);
}


/**********************************************************************
 
         End of file:     ue_data_app.c@@/main/1 - Sun Mar 28 22:59:22 2010
 
**********************************************************************/

/**********************************************************************
 
        Notes:
 
**********************************************************************/

/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vp                  1. Initial Release.
/main/1+   ue002.101  sv                  1. Multi ue support changes.
/main/1+   ue003.101  rp                  1. Dedic bearer changes.
/main/1+   ue006.101  sriki               1. End to end performance support changes.
/main/1+   ue007.101  pmacharla           1. Web browsing feature added
                       rk                  1. Fix for DefectId: ccpu00117388
                                             Compilation error fix if ERRCLS defined.
                       ms                  1. Compilation error ERRCLS defined
                                             in make file.
/main/1+   ue008.101  ragrawal            1. TIC_ID:ccpu00117550 Fixed warning for gcc compilation on CentOS
                                          2. Fixed error for g++ compilation on Linux
                                          3. Service Request procedure added.
*********************************************************************91*/

