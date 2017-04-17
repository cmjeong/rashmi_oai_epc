
/********************************************************************20**

     Name:     LTE UE Simulator

     Type:     C source file

     Desc:     This file contains call back functions for PJU
               interface.

     File:     ue_data_app.c

     Sid:      ue_data_app_cav.c@@/main/1 - Sun Mar 28 22:59:22 2010

     Prg:      vp

*********************************************************************21*/

#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "cvmx.h"
#include "cvmx-config.h"
#include "cvmx-fpa.h"
#include "cvmx-wqe.h"
#include "cvmx-pko.h"
#include "cvmx-helper.h"
#include "cvmx-pip.h"
#include "cvmx-packet.h"

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer defines */
#include "cm_tkns.h"       /* Common tokens defines */
#include "cm_mblk.h"       /* Common memory allocation library defines */
#include "cm_llist.h"      /* Common link list  defines  */
#include "cm_hash.h"       /* Common hashlist  defines */
#include "cm_lte.h"        /* Common LTE defines */
#include "cm_pasn.h"       /* Common Pasn includes */
#include <unistd.h>
#include "nhu_asn.h"
#include "nhu.h"

#include "ue_nhu_app.h"    /* UE App Interface with RRC */
#include "ue.h"            /* UE Includes */
#include "cm_emm_esm.h"    /* EMM-ESM Defines */
#include "cm_emm.h"        /* EMM Defines */
#include "cm_esm.h"        /* ESM Defines */
#include "ue_app.h"        /* UE application includes */
#include "ue_err.h"



/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */

#include "cm5.x"           /* Common timer library */
#include "cm_tkns.x"       /* Common tokens */
#include "cm_llist.x"      /* Common link list */
#include "cm_mblk.x"       /* Common memory allocation */
#include "cm_hash.x"       /* Common hashlist */
#include "cm_lib.x"
#include "cm_lte.x"       /*  Common UMTS includes */
#include "cm_pasn.x"       /* Common Pasn includes */

#include "nhu_asn.x"
#include "ue_nhu_app.x"    /* UE App Interface with RRC */
#include "ue_pju_app.x"    /* UE App Interface with RRC */
#include "cm_emm.x"        /* EMM Includes */
#include "cm_esm.x"        /* ESM Includes */
#include "cm_emm_esm.x"    /* EMM-ESM Includes */
#include "ue_app.x"        /* UE App Includes */

#define PIP_IP_OFFSET 4
#define UE_ARP_REQ    0x0001
#define UE_ARP_RSP    0x0002
#define UE_ETH_TYPE_ARP  0x0806
#define UE_ETH_TYPE_IP   0x0800


PRIVATE S16 ueAppInitEthPkt ARGS((Void));
PRIVATE Void ueAppSendEthPkt ARGS((U8  *ethPkt,
                                   U32 len));

PRIVATE S16 ueAppSendArpReqPkt ARGS(( U8  *ipAddr));


PRIVATE cvmx_buf_ptr_t UeGetBufPtr ARGS((const cvmx_wqe_t *work));

/* ue006.101: Removed function prototype */

PRIVATE S16 ueAppGetNwParam ARGS((U32 selfIp));

PRIVATE S16 ueAppInitAdaptor ARGS((Void));

/* ue002.101: Multi ue support changes */
PRIVATE U8 * ueAppFindMACAddress ARGS((U32 ipAddr, U16 ueIdx));

PRIVATE S16 ueAppBuildEthPkt ARGS(( Buffer *mBuf, U16 ueIdx));

PUBLIC Void ueAppPktReceiver ARGS((Void *arg));

PRIVATE S16 ueAppRcvdPktHndlr ARGS(( cvmx_wqe_t  *work));
PRIVATE S16 ueAppHndlArpPkt ARGS(( cvmx_wqe_t  *work));

/* ue006.101: Added function prototype */
EXTERN PUBLIC S16 ueAppHndlIPPkt ARGS((cvmx_wqe_t *work));
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
U16 ueIdx
)
#else
PUBLIC S16 ueAppCfgrPdnAssignedAddr (pdnAsgndAddr, ueIdx)
U32 pdnAsgndAddr;
U16 ueIdx;
#endif
{
   S16 ret;
   U8 ipAddr[UE_APP_MAX_IP_ADDR_LEN];
  /* ue002.101: Multi ue support changes */
   UeAppDataCb *dataCb = NULLP;
   U8 idx;

   TRC2(ueAppCfgrPdnAssignedAddr);
   /* ue002.101: Multi ue support changes */ 
   /* Before sending the ARP request , update the ip2mac table for this UE */
   dataCb = &ueAppCellCb.dataCb;
   cmMemset((U8 *)&dataCb->ip2Mac, 0,
                  sizeof(UeAppDataRouteCb) * (UE_APP_MAX_CONNS));
   dataCb->ip2Mac[ueIdx].ipAddr =
             ueAppCellCb.ueAppCbLst[ueIdx].ueCtxt.selfAddr.u.ipv4NetAddr;
   for (idx = 0; idx < UE_APP_MAX_IP_ADDR_LEN; idx++)
   {
      dataCb->ip2Mac[ueIdx].ipAddrStr[idx] =
      ueAppCellCb.ueAppCbLst[ueIdx].ueCtxt.selfAddr.u.ipv4NetAddr >> (8 * (3 - idx));
   }

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppCfgrPdnAssignedAddr:Configuring the PDN assigned IP Address "));

   ipAddr[0] = (U8)((pdnAsgndAddr >> 24) & 0xff);
   ipAddr[1] = (U8)((pdnAsgndAddr >> 16) & 0xff);
   ipAddr[2] = (U8)((pdnAsgndAddr >> 8) & 0xff);
   ipAddr[3] = (U8)((pdnAsgndAddr & 0xff));

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
   U16 ethType = UE_ETH_TYPE_IP;
  /* ue002.101: Multi ue support changes */
   UeAppDataCb *dataCb = &ueAppCellCb.dataCb;

   TRC2(ueAppInitEthPkt)
   dataCb->ethPkt = (U8 *) cvmx_fpa_alloc(CVMX_FPA_PACKET_POOL);

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
   U16 ethType = UE_ETH_TYPE_ARP;
   U16 ethProtocolType = UE_ETH_TYPE_IP;
   U16 arpType = UE_ARP_REQ;
   U16 arp_hardware_type_ethernet = 0x0001;
   U8  arp_hardware_size = 0x06;
   U8  arp_protocol_size = 0x04;
   UeArpPkt  *arpPkt;
   UeAppDataCb *ueAppDataCb;
   U8 idx;

   TRC2(ueAppInitArpPkt)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppInitArpPkt:Initializing the ARP Packet"));

/* ue002.101: Multi ue support changes */
   ueAppDataCb = &(ueAppCellCb.dataCb);
   ueAppDataCb->arpPkt = (U8 *) cvmx_fpa_alloc(CVMX_FPA_PACKET_POOL);

   /* First Fill Ethenet Header */
   /* Set the destination MAC address to broadcast address and 
      set the source MAC address to local MAC address */
   cmMemcpy(ueAppDataCb->arpPkt, ueAppDataCb->ethPkt, UE_APP_MAC_ADDR_LEN * 2);
   idx = UE_APP_MAC_ADDR_LEN * 2;

   /* Set the type of Ethernet packet to ARP (0x0806) */
   cmMemcpy(ueAppDataCb->arpPkt + idx, (U8 *)&ethType, 2);

   /* Fill ARP packet (Ethernet payload) */
   idx += 2;

   arpPkt = (UeArpPkt *) (ueAppDataCb->arpPkt + idx); 
   /* Set the hardware type to Ethernet (0x0001) */
   arpPkt->hw_type = arp_hardware_type_ethernet;
   arpPkt->proto = ethProtocolType;
   arpPkt->hw_addr_len = arp_hardware_size;
   arpPkt->proto_addr_len = arp_protocol_size;

   arpPkt->opcode = arpType;

   /* Set the Sender Hardware Address to local MAC address */
   cmMemcpy(arpPkt->src_mac, ueAppDataCb->lclMACAddr,
            UE_APP_MAC_ADDR_LEN);

   /* Set the Sender Protocol Address to local IP address */
   cmMemcpy(arpPkt->src_ip, ueAppDataCb->ueAppIpAddrStr,
            UE_APP_MAX_IP_ADDR_LEN);

   /* Initialise the Target Hardware Address and 
      Target Protocol Adress to 0xff */
   cmMemset(arpPkt->dest_mac, 0xff, UE_APP_MAC_ADDR_LEN);
   cmMemset(arpPkt->dest_ip, 0xff, UE_APP_MAX_IP_ADDR_LEN);

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
   UeArpPkt  *arpPkt;
   TRC2(ueAppSendArpReqPkt)
/* ue002.101: Multi ue support changes */
   arpPkt = (UeArpPkt *) (ueAppCellCb.dataCb.arpPkt + UE_APP_L2_HEADER_SIZE);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppSendArpReqPkt:Sending the ARP Request Packet for %d:%d:%d:%d",
       ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]));
   /* Take the default ARP packet and add the destination IP address */
   cmMemcpy(arpPkt->dest_ip, ipAddr, UE_APP_MAX_IP_ADDR_LEN);


   /* Send out ARP request packet */
   /* ue002.101: Multi ue support changes */
   ueAppSendEthPkt(ueAppCellCb.dataCb.arpPkt, UE_APP_ARP_PKT_SIZE);

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
cvmx_wqe_t *work
)
#else
PRIVATE Void ueAppSendArpRspPkt (work)
cvmx_wqe_t *work;
#endif
{
   UeArpPkt  *arpPkt;
   U8 *pkt;
   U32 dstIpAddr;
   cvmx_buf_ptr_t ueBufPtr;


   TRC2(ueAppSendArpRspPkt)

   ueBufPtr = UeGetBufPtr(work);
   pkt = (U8 *)cvmx_phys_to_ptr(ueBufPtr.s.addr);
   arpPkt = (UeArpPkt *)(pkt + UE_APP_L2_HEADER_SIZE);

/* ue002.101: Multi ue support changes */
   cmMemcpy(pkt, pkt+UE_APP_MAC_ADDR_LEN, UE_APP_MAC_ADDR_LEN); 
   cmMemcpy((pkt+UE_APP_MAC_ADDR_LEN),ueAppCellCb.dataCb.lclMACAddr,
                                    UE_APP_MAC_ADDR_LEN); 
   arpPkt->opcode = UE_ARP_RSP;
   cmMemcpy((U8 *)&dstIpAddr,(U8 *)arpPkt->dest_ip,UE_APP_MAX_IP_ADDR_LEN);
   cmMemcpy(arpPkt->dest_ip, arpPkt->src_ip, UE_APP_MAX_IP_ADDR_LEN);
   cmMemcpy(arpPkt->dest_mac, arpPkt->src_mac, UE_APP_MAC_ADDR_LEN);
   /* Add local MAC address as source MAC address */
   cmMemcpy(arpPkt->src_mac, ueAppCellCb.dataCb.lclMACAddr,UE_APP_MAC_ADDR_LEN);

   cmMemcpy(arpPkt->src_ip,(U8 *) &dstIpAddr, UE_APP_MAX_IP_ADDR_LEN);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppSendArpRspPkt:Sending the ARP Response to %d:%d:%d:%d",
      arpPkt->dest_ip[0], arpPkt->dest_ip[1], arpPkt->dest_ip[2], 
      arpPkt->dest_ip[3]));

   /* Send out ARP response packet */
   ueAppSendEthPkt(pkt,UE_APP_ARP_PKT_SIZE);

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
   U64 queue;
   U16 port = UE_APP_BASE_PORT + UE_APP_MAC_PORT_ID;
   cvmx_pko_command_word0_t pkoCmd;
   cvmx_pko_status_t status;
   cvmx_buf_ptr_t bufPtr;

   TRC2(ueAppSendEthPkt);
 
   queue = cvmx_pko_get_base_queue(port);


   cvmx_pko_send_packet_prepare(port, queue, CVMX_PKO_LOCK_CMD_QUEUE);
/*
   cvmx_pko_send_packet_prepare(port, queue, CVMX_PKO_LOCK_NONE);
*/

   bufPtr.u64  = 0;
   bufPtr.s.addr = cvmx_ptr_to_phys(ethPkt);
   bufPtr.s.pool = CVMX_FPA_PACKET_POOL;
   bufPtr.s.i    = 0;
   bufPtr.s.size = len;

   /* Build a PKO pointer to this packet */
   pkoCmd.u64 = 0;
   pkoCmd.s.dontfree = 1;
   pkoCmd.s.segs = 1;
   pkoCmd.s.total_bytes = len;
   

   status = cvmx_pko_send_packet_finish(port, queue, pkoCmd,bufPtr, CVMX_PKO_LOCK_CMD_QUEUE);
/*
   status = cvmx_pko_send_packet_finish(port, queue, pkoCmd,bufPtr, CVMX_PKO_LOCK_NONE);
*/
   if (status != CVMX_PKO_SUCCESS)
   {
      UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppSendEthPkt: Failed to send packet using cvmx_pko_send_packet2"));
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
PUBLIC Void ueAppPktReceiver
(
Void *arg
)
#else
PUBLIC Void ueAppPktReceiver (arg)
Void *arg;
#endif
{
#ifndef SS_CAVIUM
   /* Read packets from Ethernet interface and invoke ueAppRcvdPktHndlr
      callback function for every packet read */
   /* ue002.101: Multi ue support changes */
   pcap_loop(ueAppCellCb.dataCb.dataHdlr, -1, ueAppRcvdPktHndlr, NULLP);
#else
   cvmx_wqe_t *work;
   S16 ret;

   TRC2(ueAppPktReceiver)
   work = (cvmx_wqe_t *) arg; 


   ret = ueAppRcvdPktHndlr(work);
   if (ret == UE_APP_FREE_PKT)
   {
      cvmx_helper_free_packet_data(work);
   }
   if (ret != UE_APP_DONT_FREE_WQE)
   {
      cvmx_fpa_free(work, CVMX_FPA_WQE_POOL, 0);
   }
#endif

   return;
}/* End of ueAppPktReceiver */

#ifdef ANSI
PRIVATE S16 ueAppRcvdPktHndlr
(
cvmx_wqe_t  *work
)
#else
PRIVATE S16 ueAppRcvdPktHndlr (work)
cvmx_wqe_t  *work;
#endif
{

   S16 ret;
   TRC2(ueAppRcvdPktHndlr)

   if (cvmx_unlikely(work->word2.s.rcv_error))
   {
       ret = UE_APP_FREE_PKT;
   }
   else if (cvmx_likely (!work->word2.s.not_IP))
   {
      ret = ueAppHndlIPPkt(work);
   }
   else if (cvmx_unlikely (work->word2.s.not_IP))
   {
      if (cvmx_likely(work->word2.snoip.is_arp))
      {
         ret =  ueAppHndlArpPkt(work);
      }
      else
      {
         ret = UE_APP_FREE_PKT;
      }
   }

   RETVALUE(ret);
}/* End of ueAppRcvdPktHndlr */

#ifdef SS_CAVIUM
cvmx_buf_ptr_t UeGetBufPtr(const cvmx_wqe_t *work)
{
    cvmx_buf_ptr_t uePtr;
    if (cvmx_likely(work->word2.s.bufs == 0))
    {
        uePtr.u64 = 0;
        uePtr.s.pool = CVMX_FPA_WQE_POOL;
        uePtr.s.size = CVMX_FPA_WQE_POOL_SIZE;
        uePtr.s.addr = cvmx_ptr_to_phys((void*)work->packet_data);
        /* WARNING: This code assume that PIP_GBL_CFG[RAW_SHF]=0 and
            PIP_GBL_CFG[NIP_SHF]=0. If this was not the case we'd
            need to add these offsets depending on if the packet was
            in RAW mode or not.
            addr += PIP_GBL_CFG[RAW_SHF] for the RAW case.
            addr += PIP_GBL_CFG[NIP_SHF]; for the non-IP case */
        if (cvmx_likely(!work->word2.s.not_IP))
        {
            uePtr.s.addr += PIP_IP_OFFSET*8 - work->word2.s.ip_offset;
            uePtr.s.addr += (work->word2.s.is_v6^1)*4;
        }
    }
    else
        uePtr = work->packet_ptr;
    return uePtr;
}


/*
 *
 *       Fun:   ueAppHndlArpPkt
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
PRIVATE S16 ueAppHndlArpPkt
(
cvmx_wqe_t  *work
)
#else
PRIVATE S16 ueAppHndlArpPkt (work)
cvmx_wqe_t  *work;
#endif
{
   UeAppDataCb *dataCb = NULLP;
   UeArpPkt *arpPkt;
   UeAppCb *ueAppCb;
   cvmx_buf_ptr_t ueBufPtr;
   S16 ret;
   U16 idx;
   U8 *buf;

   TRC2(ueAppHndlArpPkt)

   ueBufPtr = UeGetBufPtr(work);
   buf = (U8 *)cvmx_phys_to_ptr(ueBufPtr.s.addr);
   

   arpPkt = (UeArpPkt *)(buf + UE_APP_L2_HEADER_SIZE);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppHndlArpPkt :destination IP %x", *(U32 *)arpPkt->dest_ip));
   /* Drop invalid ARP entries without processing */
   if ((arpPkt->hw_addr_len != UE_APP_MAC_ADDR_LEN) || 
       (arpPkt->proto_addr_len != UE_APP_MAX_IP_ADDR_LEN))
   {
        RETVALUE (UE_APP_FREE_PKT);
   }

   if (arpPkt->opcode ==  UE_ARP_REQ)
   {
      /* ue002.101: Multi ue support changes */
      if ((*(U32 *)(arpPkt->dest_ip)) == ueAppCellCb.dataCb.ueAppDstAddr)
      {
         UE_DBGP_INFO((UE_PRNTBUF,
          "ueAppHndlArpPkt :Sending ARP Response Packet"));
         ueAppSendArpRspPkt(work);
         RETVALUE(UE_APP_FREE_PKT);
      }
   }
   else
   {
      dataCb = &ueAppCellCb.dataCb;
      if (dataCb->mapCnt >= UE_APP_MAX_CONNS)
      {
         ret = UE_APP_FREE_PKT;
      }
     
      while (idx < dataCb->mapCnt)
      {
         if (*(U32 *)arpPkt->src_ip == dataCb->ip2Mac[idx].ipAddr)
         {
            cmMemcpy((U8 *) &(dataCb->ip2Mac[idx].macAddr),
                   arpPkt->src_mac, UE_APP_MAC_ADDR_LEN);
            ueAppCb = &ueAppCellCb.ueAppCbLst[idx];
        
            if (ueAppCb != NULLP)
            {
               ueAppSndArpCompInd(ueAppCb);
            }

            RETVALUE(UE_APP_FREE_PKT);
         }
         idx++;
      }
      dataCb->mapCnt += 1;
   }

   RETVALUE(ret);
}/* End of ueAppHndlArpPkt */

/* ue006.101: Modified function type to PUBLICe */
/*
 *
 *       Fun:   ueAppHndlIPPkt
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
PUBLIC S16 ueAppHndlIPPkt
(
cvmx_wqe_t  *work
)
#else
PUBLIC S16 ueAppHndlIPPkt (work)
cvmx_wqe_t  *work;
#endif
{

   U32 srcIpAddr;
   U32 dstIpAddr;
   cvmx_buf_ptr_t ueBufPtr;
   U8   *ipPkt;
   S16 ret;
   U16 ueIdx;
   UeAppCb *ueAppCb

   TRC2(ueAppHndlIPPkt)

   ueBufPtr = UeGetBufPtr(work);

   ipPkt = (U8 *) cvmx_phys_to_ptr(ueBufPtr.s.addr + UE_APP_L2_HEADER_SIZE);


   srcIpAddr = *(U32 *) (ipPkt + UE_APP_SRC_IP_ADDR_IDX);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppHndlIPPkt: Handling IP packet with SRC addr %x",srcIpAddr));

   /* ue002.101: Multi ue support changes */
   /* Find the correct UE from the ueAppCellCb and get the ueIdx */
   for(ueIdx=0; ueIdx < UE_NUM_PER_CELL;ueIdx++)
   {
     if (srcIpAddr == ueAppCellCb.ueAppCbLst[ueIdx].ueCtxt.selfAddr.u.ipv4NetAddr)
     {
       ueAppCb = &ueAppCellCb.ueAppCbLst[ueIdx]; 
     }
   }
   if(ueAppCb == NULLP)
   {     
     RETVALUE(UE_APP_FREE_PKT);
   }

   dstIpAddr = *(U32 *) (ipPkt + UE_APP_DST_IP_ADDR_IDX);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppHndlIPPkt: Handling IP packet with Dst addr %x",dstIpAddr));

   /* ue002.101: Multi ue support changes */
   if (dstIpAddr != ueAppCellCb.dataCb.ueAppDstAddr)
   {
      UE_DBGP_INFO((UE_PRNTBUF,
         "ueAppHndlIPPkt: IP packet not for us but for %x",dstIpAddr));

       RETVALUE(UE_APP_FREE_PKT);
   }
   
   /* Send the IP packet to eNodeB, exclude Ethernet header 
      portion of first 14 bytes */
   /* ue002.101: Multi ue support changes */
   ueAppLimSndPdcpMsg(work,ueAppCb);

   RETVALUE(ret);
}/* End of ueAppHndlIPPkt */
#endif

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
   cvmx_sysinfo_t *cvmSysInfo;

   TRC2(ueAppGetNwParam)

   cvmSysInfo = cvmx_sysinfo_get();

   /* ue002.101: Multi ue support changes */
   cmMemcpy(ueAppCellCb.dataCb.lclMACAddr, (U8 *)cvmSysInfo->mac_addr_base, 
                  UE_APP_MAC_ADDR_LEN);
   ueAppCellCb.dataCb.lclMACAddr[5] += UE_APP_MAC_PORT_ID;

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

   TRC2(ueAppInitAdaptor)

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
   /* ue002.101: Removed unnecessary code */
   U8   idx;
   U8  *addr;
   S16  ret;

   TRC2(ueAppRouteInit)

   /* This function is invoked by the UE sender task as Receive
   task would have been just created */


      /* ue008.101: Fixed compilation error */
      UE_DBGP_INFO((UE_PRNTBUF,
               "ueAppRouteInit: Initialising UE Routing Parameters"));

   /* ue002.101: Multi ue support changes */
   dataCb = &ueAppCellCb.dataCb;


   /* Store the UE App IP Address, this is the one used in Proxy setting */
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

   /* The no. of UE app clients, currently 1 */
   /* ue002.101: Multi ue support changes */
   dataCb->mapCnt = UE_NUM_PER_CELL;

  /* IP address for UE client gets updated once received with
    attach accept from CN */

   /* Get Network Parameters using self assigned IP Address */
   ret = ueAppGetNwParam(dataCb->ueAppIpAddr);
   if (ROK != ret)
   {
      /* ue007.101: Compilation error fix in cavium */
      UELOGERROR(ERRCLS_ADD_RES, EUE054, (ErrVal)0,
         "ueAppRouteInit: Failed to get UE network parameters\n");
      RETVALUE(RFAILED);
   }


   addr = dataCb->lclMACAddr;

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppRouteInit: Ethernet address :  %x:%x:%x:%x:%x:%x", addr[0],
      addr[1], addr[2], addr[3], addr[4], addr[5]));

   addr = dataCb->ueIpAddrStr;

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppRouteInit: UE  IP address : %d.%d.%d.%d", addr[0],
      addr[1], addr[2], addr[3]));


   addr = dataCb->ueAppIpAddrStr;

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppRouteInit: UE  App (Proxy) IP address : %d.%d.%d.%d", addr[0],
      addr[1], addr[2], addr[3]));

   /* Initialize Ethernet packet */
   ret = ueAppInitEthPkt();
   if (ret != ROK)
   {
      /* ue007.101: Compilation error fix in cavium */
      UELOGERROR(ERRCLS_ADD_RES, EUE055, (ErrVal)0,
         "ueAppRouteInit: Failed to initialize Ethernet Packet\n");
      RETVALUE(RFAILED);
   }

   /* Initialize ARP packet */
   ret = ueAppInitArpPkt();
   if (ret != ROK)
   {
      /* ue007.101: Compilation error fix in cavium */
      UELOGERROR(ERRCLS_ADD_RES, EUE056, (ErrVal)0,
         "ueAppRouteInit: Failed to initialize ARP Packet\n");
      RETVALUE(RFAILED);
   }

   /* Open the adaptor for capturing packets - LibPcap */
   ret = ueAppInitAdaptor();
   if (ret != ROK)
   {
      /* ue007.101: Compilation error fix in cavium */
      UELOGERROR(ERRCLS_ADD_RES, EUE057, (ErrVal)0,
         "ueAppRouteInit: ueAppInitAdaptor failed\n");
      RETVALUE(RFAILED);
   }

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
U16 ueIdx
)
#else
PRIVATE U8 * ueAppFindMACAddress (ipAddr,ueIdx)
U32 ipAddr;
U16 ueIdx;
#endif
{
   TRC2(ueAppFindMACAddress)

   /* search for MAC address mapped to the ipAddr */
   /* ue002.101: Multi ue support changes */
   if (ipAddr == ueAppCellCb.dataCb.ip2Mac[ueIdx].ipAddr)
   {
       RETVALUE(ueAppCellCb.dataCb.ip2Mac[ueIdx].macAddr);
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
PRIVATE S16 ueAppBuildEthPkt
(
Buffer *mBuf,
U16     ueIdx
)
#else
PRIVATE S16 ueAppBuildEthPkt (mBuf, ueIdx)
Buffer *mBuf;
U16     ueIdx;
#endif
{
   MsgLen msgLen;
   MsgLen mBufLen;
   U32  dstIPAddr;
   U8  *dstMACAddr;
   UeAppDataCb *dataCb = &ueAppCellCb.dataCb;
   S16 ret;

   TRC2(ueAppBuildEthPkt)
   
   SFndLenMsg(mBuf, &mBufLen);
   
   if ((mBufLen + UE_APP_L2_HEADER_SIZE) < CVMX_FPA_PACKET_POOL_SIZE)  
   {
      /* Copy IP packet into Ethernet payload */
      ret = SCpyMsgFix(mBuf, 0, mBufLen, 
                (dataCb->ethPkt + UE_APP_L2_HEADER_SIZE), &msgLen);
      if ((ret != ROK) || (msgLen != mBufLen))                                                                             
      {
         RETVALUE(RFAILED);
      }

      /* Find out the destination MAC address using destination IP address */
      dstIPAddr = *(U32 *)(dataCb->ethPkt + 
                    UE_APP_L2_HEADER_SIZE + UE_APP_DST_IP_ADDR_IDX);

      /* Search the MAC map for destination MAC address */
      /* ue002.101: Multi ue support changes */
      dstMACAddr = ueAppFindMACAddress(dstIPAddr, ueIdx);
      if(dstMACAddr == NULLP)
      {
        printf("Could not find MAC address\n");
        RETVALUE(RFAILED);
      }  

      /* Copy the destination MAC address */
      cmMemcpy(dataCb->ethPkt, dstMACAddr, UE_APP_MAC_ADDR_LEN);

   }
   else
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE058, (ErrVal)msgLen,
         "ueAppBuildEthPkt: Invalid Size and should not happen\n");
   }
   RETVALUE(ROK);
}/* End of ueAppBuildEthPkt */

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
Buffer *mBuf,
U16     ueIdx
)
#else
PUBLIC S16 ueAppFrwdIpPkt (mBuf,ueIdx)
Buffer *mBuf;
U16     ueIdx;
#endif
{

   MsgLen  msgLen;

   TRC2(ueAppFrwdIpPkt)
   
   SFndLenMsg(mBuf, &msgLen);

   if(msgLen > UE_APP_MAX_ETH_PKT_LEN)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE059, (ErrVal)msgLen,
         "ueAppFrwdIpPkt: Failed to send the Packet as it  exceeds Max\
          Ethernet Packet Size Size of Packet\n"); 
      RETVALUE(RFAILED);
   }

   /* ue002.101: Multi ue support changes */
   /* Encapsulate the IP packet in an Ethernet packet */
   ueAppBuildEthPkt(mBuf,ueIdx);
   /* Send out Ethernet packet */
   ueAppSendEthPkt(ueAppCellCb.dataCb.ethPkt, msgLen + 14);

   RETVALUE(ROK);
}



/**********************************************************************
 
         End of file:     ue_data_app_cav.c@@/main/1 - Sun Mar 28 22:59:22 2010
 
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
/main/1      ---      vp                    1. Initial Release.
/main/1+   ue002.101  sv                    1. Multi ue support changes.
/main/1+   ue006.101  sriky                 1. Performance tuning.
/main/1+   ue007.101  rk                    1. Cavium compilation error fix
/main/1+   ue008.101  ragrawal              1. Cavium compilation error fix
*********************************************************************91*/

