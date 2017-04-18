
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_diag.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="EMM";
static int RLOG_MODULE_ID=1;
static int RLOG_FILE_ID=45;
#include "wr.h"
#include "wr_umm.h"
#include "unistd.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/* @brief Public function forward declaration */
PUBLIC S16  wrDiagCreatSock(U8 *ipaddr, U32 port);
PUBLIC S16  wrDiagPrntPlmnId(WrPlmnId *plmnId, U8 diagLvl);

/* @brief Public declaration */
PUBLIC WrSockAddr wrDiagDstAddr;
PUBLIC U32 wrDiagSockFd; 
/**
 *  @brief This is an utility function to print PlmnId from the message
 *  @details
 *  This is an utility function to print PlmnId from the message
 *  
 *       Function: wrDiagPrntPlmnId
 *  
 *           Processing steps:
 *           -  decode the PLMN from the message
 *           - provide fixed log
 *  
 *   @param[in]  plmnId : pointer to PLMN 
 *   @param[in]  diagLvl: Diagnostic level
 *   @return S16
 *            -# Success : ROK
 *            -# Failure : RFAILED
 */
PUBLIC S16 wrDiagPrntPlmnId(WrPlmnId *plmnId, U8 diagLvl)
{
   U32 mcc = 0;
   U32 mnc = 0;
   if(NULLP == plmnId)
   {
      RETVALUE(RFAILED);
   }
   if(plmnId->numMncDigits == 2)
   {
      mcc = (plmnId->mcc[2] | (plmnId->mcc[1] <<4) | (plmnId->mcc[0] <<8));
      mnc = (plmnId->mnc[1] | (plmnId->mnc[0] <<4));
   }
   else
   {
      mcc = (plmnId->mcc[2] | (plmnId->mcc[1] <<4) | (plmnId->mcc[0] <<8));
      mnc = (plmnId->mnc[2] | (plmnId->mnc[1] <<4) | (plmnId->mnc[0] <<8));
   }
   switch(diagLvl)
   {
      case 0:
         RLOG2(L_DEBUG, "PLMN ID: MCC [%03x] MNC [%02x]", mcc, mnc);
         break;
      case 1:
         RLOG2(L_DEBUG, "PLMN ID: MCC [%03x] MNC [%02x]", mcc, mnc);
         break;
      case 2:
         RLOG2(L_DEBUG, "PLMN ID: MCC [%03x] MNC [%02x]", mcc, mnc);
         break;
      case 3:
         RLOG2(L_DEBUG, "PLMN ID: MCC [%03x] MNC [%02x]", mcc, mnc);
         break;
      case 4:
         RLOG2(L_DEBUG, "PLMN ID: MCC [%03x] MNC [%02x]", mcc, mnc);
         break;
      default:
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} /* end of wrDiagPrntPlmnId */


/** 
 * @brief This function is used to create a socket is used to send logs
 *  
 * @details
 * This function is used to create a socket is used to send logs
 *
 *     Function:wrDiagCreatSock 
 *
 *         Processing steps:
 *           - create socket for sending logs
 *           
 * @param[in] ipaddr : Local IP address
 * @param[in] port   : Local Port
 * @return S16
 */   
PUBLIC S16 wrDiagCreatSock(U8 *ipaddr, U32 port)
{
   S32 ret;
   CmInetAddrInfo addrInfo;
   CmInetAddrInfo *res;
   CmInetAddrInfo *tmp;
   ret = ROK;
   U16 domain = 0;

   cmMemset((U8*)&addrInfo, 0, sizeof(CmInetAddrInfo));
   memset((char *) &wrDiagDstAddr, 0, sizeof(wrDiagDstAddr));

   /* set the caller to accept any address family */
   addrInfo.ai_family = PF_UNSPEC;
   /* set the socket type */
   /* We are setting to connection oriented socket type for 
    * retrieving the IP address type 
    */
   addrInfo.ai_socktype = SOCK_STREAM;
   /* Fill the hosts canonical(real) name in the result */
   addrInfo.ai_flags |= AI_CANONNAME;
   ret = cmInetGetAddrInfo((S8 *)ipaddr, NULLP,&addrInfo,&res);
   if(ret != ROK)
   {
      RLOG_STR(L_ERROR, "wrDiagCreatSock: IP addr validation failed:[%s]", (S8*)ipaddr);
      RETVALUE(ret);
   }
   tmp = res;
   if (res)
   {
      switch (res->ai_family)
      {
        case AF_INET:
          domain = AF_INET;
          wrDiagDstAddr.len = sizeof(struct sockaddr_in);
          wrDiagDstAddr.type = CM_IPV4ADDR_TYPE;
          /* Set address family of IPV4 */
          wrDiagDstAddr.u.addr.sin_family = AF_INET;
          wrDiagDstAddr.u.addr.sin_port = htons(port);
          /* Copy IPv4 address(4bytes) into the destination */ 
          cmMemcpy((U8 *)&(wrDiagDstAddr.u.addr.sin_addr), 
             (U8 *) &((struct sockaddr_in *) res->ai_addr)->sin_addr, 4);
          break;
        case AF_INET6:
          domain = AF_INET6;
          wrDiagDstAddr.len = sizeof(struct sockaddr_in6);
          /* Set address family of IPV6 */
          wrDiagDstAddr.u.addr6.sin6_family = AF_INET6;
          wrDiagDstAddr.u.addr6.sin6_port = htons(port);
          /* Copy IPv6 address(16bytes) into the destination */ 
          cmMemcpy((U8 *)(&wrDiagDstAddr.u.addr6.sin6_addr.s6_addr), 
            (U8 *) &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr, 16);
          break;
      }
      res = res->ai_next;
   }

   cmInetFreeAddrInfo(tmp);

   if (( wrDiagSockFd = socket(domain, SOCK_DGRAM, 0))==-1)
   {
      ALARM("failed to open socketfd\n");
      RETVALUE(RFAILED);
   }

   ALARM("Sending logs to ipaddr = %s port %lu\n",ipaddr, port);
   RETVALUE(ROK);
} /* end of wrDiagCreatSock */


/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
