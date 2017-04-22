
/********************************************************************20**

     Name:     cm_xta_lsgutl.c  
     Type:     C source file

     Desc:     File contains utility functions for LSG interface

     File:     cm_xta_lsgutl.c

     Sid:      cm_xta_lsgutl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:22 2015

     Prg:      sm

*********************************************************************21*/

/* header include files (.h) */


PUBLIC Txt *entityDef[41] =
#include "cm_xta.x"
{
"UA1",
"UA2",
"UA3",
"UA4",
"UA5",

"SLP1",
"SLP2",
"SLP3",
"SLP4",
"SLP5",

"CSP1",
"CSP2",
"CSP3",
"CSP4",
"CSP5",

"TSP1",
"TSP2",
"TSP3",
"TSP4",
"TSP5",

"PRX1",
"PRX2",
"PRX3",
"PRX4",
"PRX5",

"SFP1",
"SFP2",
"SFP3",
"SFP4",
"SFP5",

"DUA1",
"DUA2",
"DUA3",
"DUA4",
"DUA5",

"SPECTRA",
"SU1",
"SU2",
"SU3",
"SU4",
"SU5"
};


/*
 *
 *       Fun:    soAcDmSmGetSrvType - configuration confirm
 *
 *       Desc:   prints the config confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_dmsm.c
 *
 */

#ifdef ANSI
PUBLIC U8 soAcDmSmGetSrvType
(
U32            tptSrvId     /* transport server ID      */
)
#else
PUBLIC U8 soAcDmSmGetSrvType(tptSrvId)
U32            tptSrvId;     /* transport server ID      */
#endif /* ANSI */
{
   U8    servType;
   TRC3(soAcDmSmGetSrvType)

   CMXTA_DBG_PARAM((_cmxtap, "soAcDmSmGetSrvType(): tptSrvId(%ld)\n", tptSrvId));

   /*-- The magic figure of 200 is based on 5 UA, 5 CSP, 5 TSP & 5 SLP and
        10 tptSrvId per entity --*/

   servType = LSO_TPTPROT_UDP;
#define CMXTA_MAX_TPTSRVID 450

   if (tptSrvId < CMXTA_MAX_TPTSRVID)
   {
      switch (tptSrvId % 10)
      {
         case 0:
            /*-- DNS tptSrvId, use UDP --*/
            servType = LSO_TPTPROT_UDP;
            break;

         case 1:
         case 5:
            servType = LSO_TPTPROT_UDP;
            break;
         case 2:
         case 6:
            servType = LSO_TPTPROT_TCP;
            break;
         case 3:
         case 7:
            servType = LSO_TPTPROT_SCTP;
            break;
         case 4:
         case 8:
            servType = LSO_TPTPROT_TLS_TCP;
            break;
         default:
            servType = LSO_TPTPROT_NULL;
            break;
      }
   }
   else
   {
      /*-- Logic to handle any arbit tptsrvid number,
      find the mapping from the taCb --*/
   }

   RETVALUE(servType);
} /* end of soAcDmSmGetSrvType() */

/*
 *
 *       Fun:    soAcDmSmGetTptAddr - configuration confirm
 *
 *       Desc:   prints the config confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_dmsm.c
 *
 */

#ifdef ANSI
PUBLIC S16 soAcDmSmGetTptAddr
(
CmXtaTCCb *tcCb,
U32            tptSrvId,     /* transport server ID      */
CmTptAddr      *servAddr,
Txt            *addr
)
#else
PUBLIC S16 soAcDmSmGetTptAddr(tcCb, tptSrvId,servAddr, addr)
CmXtaTCCb *tcCb;
U32            tptSrvId;    /* transport server ID      */
CmTptAddr      *servAddr;
Txt            *addr;
#endif /* ANSI */
{
   U32 tmpU32;
   Bool samePort;
   Bool sameIp;
   U8      entId;
   U8      mod;
   Txt     tmpAddr[30];
   S8      *addrStr=NULLP;


   U16     basePort;
   U32     baseIp;
   U8 srvType;
   Txt      subDomain[100];
   Txt      secondDomain[100];
   Txt      topLevelDomain[100];
   Txt      tptProt[10];
   SoAcTCCb *soTcCb;

   TRC3(soAcDmSmGetTptAddr)

   CMXTA_DBG_PARAM((_cmxtap, "soAcDmSmGetTptAddr(): tptSrvId(%ld)\n", tptSrvId));

   soTcCb = (SoAcTCCb *)tcCb->tcCb;

   CMXTA_ZERO(servAddr, sizeof(CmTptAddr));

   /*-- Set address type --*/
   servAddr->type = CM_TPTADDR_IPV4;

   /*-- SOAC_ENHANCE:  Read base port from TA cmd Line --*/
   /* basePort = 5060; */
   basePort = soTcCb->directives.basePort;

   tmpU32 = soTcCb->directives.baseIp;

   /*-- Change it to host byte order --*/
   baseIp = CM_INET_NTOH_U32(tmpU32);


   /*-- SOAC_ENHANCE:  Should we listen at same IP for all entities, give an option from
       command line to either open on the same IP or use totally different IPs altogether --*/

   /*-- SOAC_ENHANCE:  Should we listen at same port and same IP for all tptSrvId in one entity, 
        give an option from command line to either open on the same port for all real ones or
       use totally different ports altogether --*/

   /*-- SOAC_ENHANCE:  get from TA --*/
   samePort = soTcCb->directives.samePort;
   sameIp = soTcCb->directives.sameIp;

   srvType = soAcDmSmGetSrvType(tptSrvId);

   /*-- Find associated entity --*/
   mod = tptSrvId % 10;

   entId = (tptSrvId - mod) / 10;

   /* if useDomainName is set to True then send the domain name in tptAddr */

   if ((entId < 35) || (entId >= 40))
   {
      /*-- Calculate port */
      if (samePort == FALSE)
      {
         /*-- Have one to one mapping to tptSrvId for port number --*/
         servAddr->u.ipv4TptAddr.port = basePort + tptSrvId - 1;
      }
      else
      {
         /*-- Same port for all services for a paritcular entity, 
           entity 1 SHALL have port 5060, entity 2 shall have
           5070 and so on ... exceptions taken care below --*/

         /*-- Check if the real tptSrvId or a dummy one --*/
         /*-- The first four tptSrvId are the real ones --*/
         if (mod < 5)
            servAddr->u.ipv4TptAddr.port = basePort + entId * 10;
         /*-- Set to a middle value for dummy ones --*/
         else
            servAddr->u.ipv4TptAddr.port = basePort + entId * 10 + 5;

         /*-- Remember TCP and TLS can not share the same port, so
           increment by one for TLS --*/
         if (srvType == LSO_TPTPROT_TLS_TCP)
            servAddr->u.ipv4TptAddr.port += 1;
      }

      /*-- Calculate IP */
      if (sameIp == FALSE)
      {
         /*-- SOAC_ENHANCE:  can we do arithmetic operation on 
           host byte order, i guess so --*/
         baseIp = baseIp + entId;

         /*-- Get back to network byte order --*/
         tmpU32 = CM_INET_HTON_U32(baseIp);

         /*-- Change it to ASCII string --*/
         cmInetNtoa(tmpU32, &addrStr);

         /*-- Have one to one mapping to entityId for IP --*/
         sprintf(tmpAddr, "%s", addrStr);
      }
      else
      {
         /*-- SOAC_ENHANCE:  can we do arithmetic operation on 
           host byte order, i guess so --*/
         /*-- Get back to network byte order --*/
         tmpU32 = CM_INET_HTON_U32(baseIp);

         /*-- Change it to ASCII string --*/
         cmInetNtoa(tmpU32, &addrStr);

         /*-- Have one to one mapping to entityId for IP --*/
         sprintf(tmpAddr, "%s", addrStr);
      }

      /*-- Find network byte order IP address for the string --*/
      servAddr->u.ipv4TptAddr.address =  baseIp;

      /*-- Populate the ASCII address with the port --*/
      sprintf(addr, "%s:%d", tmpAddr, servAddr->u.ipv4TptAddr.port);
   }
   else
   {

      /*-- temp fix for SPECTRA --*/
      tmpU32 = soTcCb->directives.spectraIp;

      /*-- Change it to host byte order --*/
      baseIp = CM_INET_NTOH_U32(tmpU32);

      /*-- Have one to one mapping to tptSrvId for port number --*/
      servAddr->u.ipv4TptAddr.port = soTcCb->directives.basePort + entId - 35;

      /*-- Get back to network byte order --*/
      tmpU32 = CM_INET_HTON_U32(baseIp);

      /*-- Change it to ASCII string --*/
      cmInetNtoa(tmpU32, &addrStr);

      /*-- Have one to one mapping to entityId for IP --*/
      sprintf(tmpAddr, "%s", addrStr);

      /*-- Have one to one mapping to entityId for IP --*/
      /*-- Find network byte order IP address for the string --*/
      servAddr->u.ipv4TptAddr.address = baseIp;

      /*-- Populate the ASCII address with the port --*/
      sprintf(addr, "%s:%d", tmpAddr, servAddr->u.ipv4TptAddr.port);
   }

   /* If we wish to use Tel URLs in place of SIP URLS */
   if (soTcCb->directives.useTel)
   {
      /* We need some sort of mapping between the entities and their corresponding 
         telephone numbers, we shall have a similar approach to the one used to 
         get the port numbers for different entities 
         Tel URL is 5555[entId][TptType]
         e.g. for UA1 and UDP it would be 
         +555501
      */
      
      sprintf(addr, "+5555%d%d", entId, soTcCb->directives.tptType);
   }

   if (soTcCb->directives.useDomainName)
   {
      /* If we get here, it implies that we need to fill in FQDNs in the message instead of 
         actual IP addresses. Based on the entId for which we are looking for we will 
         populate the string in the return value */
      /* Lets have a static array of entities's names corresponding to the entId as index. */
      /* We need to have separate domain names for separate transport - here get the tpt protcol*/

      switch(soTcCb->directives.tptType)
      {
         case LSO_TPTPROT_UDP:
            sprintf(tptProt, "%s", "udp");
            break;
         case LSO_TPTPROT_TCP:
            sprintf(tptProt, "%s", "tcp");
            break;
         case LSO_TPTPROT_SCTP:
            sprintf(tptProt, "%s", "sctp");
            break;
         case LSO_TPTPROT_TLS_TCP:
            sprintf(tptProt, "%s", "tls");
            break;
         default:
            sprintf(tptProt, "%s", "udp");
            break;
         
      }; /* End of switch */
      
      
      /* Get the name of the entity from the array */
      /* Is there a possibility that entId might be an incorrect value, i.e. do we need some 
         checking here or not? */
      if (mod >= 5)
      {
         /* This means we have a dummy entity in this case just add 25 to the tptSrvId */
         entId  = (tptSrvId - 5) / 10;
         entId += 30;
      }
      if ((entId > 40))
         sprintf(subDomain, "user");
      else
         sprintf(subDomain, "%s", entityDef[entId]);
      sprintf(secondDomain, "%s", "xxccin");
      sprintf(topLevelDomain, "%s", "com\0");
      if (soTcCb->directives.usePhone)
         sprintf(addr, "+5555%d%d@%s%s.%s.%s;user=phone", entId, soTcCb->directives.tptType, subDomain, tptProt, secondDomain, topLevelDomain);
      else
         sprintf(addr, "%s%s.%s.%s", subDomain, tptProt, secondDomain, topLevelDomain);

         CMXTA_DBG_PARAM((_cmxtap, "soAcDmSmGetTptAddr(): Addr (%s)\n", addr));
   } 
   RETVALUE(CMXTA_ERR_NONE);
} /* end of soAcDmSmGetTptAddr() */

/*
 *
 *       Fun:    soAcDmSmGetTSapIdFromProt - configuration confirm
 *
 *       Desc:   prints the config confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_dmsm.c
 *
 */

#ifdef ANSI
PUBLIC SpId soAcDmSmGetTSapIdFromProt
(
U8    protType
)
#else
PUBLIC SpId soAcDmSmGetTSapIdFromProt(protType)
U8    protType;
#endif /* ANSI */
{
   TRC3(soAcDmSmGetTSapIdFromProt)

   CMXTA_DBG_PARAM((_cmxtap, "soAcDmSmGetTSapIdFromProt(): \n"));

   /*-- Treat TUCL and D-TUCL as same, we come here only
        for dummy layers --*/
   if ((protType == LSO_TSAP_TYPE_TUCL)       ||
       (protType == LSO_TSAP_TYPE_DTUCL))
      RETVALUE(soAccCb.taCb.dtuclId);
   else if ((protType == LSO_TSAP_TYPE_SCTP)  ||
           (protType == LSO_TSAP_TYPE_DSCTP))
      RETVALUE(soAccCb.taCb.dsctpId);
      
   RETVALUE(0);
} /* end of TSapIdFromProt() */

/*
 *
 *       Fun:    soAcDmGetTptSrvId - configuration confirm
 *
 *       Desc:   prints the config confirm status
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_dmsm.c
 *
 */

#ifdef ANSI
PUBLIC S16 soAcDmGetTptSrvId
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
U8             entId,
U8             srvType
)
#else
PUBLIC S16 soAcDmGetTptSrvId(tcCb, entId, srvType)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
U8             entId;
U8             srvType;
#endif /* ANSI */
{
   U8    offSet;
   U8    dumOffSet;
   SoAcTCCb *soTcCb;

   TRC3(soAcDmGetTptSrvId)

   CMXTA_DBG_PARAM((_cmxtap, "soAcDmGetTptSrvId(): entId(%d) srvType(%d)\n",
                 entId, srvType));

   soTcCb = (SoAcTCCb *)tcCb->tcCb;
   dumOffSet = 0;
   if ((entId >= 30) && (entId < 35))
   {
      entId = soTcCb->dummyEntity;
      dumOffSet = 4;
   }
   
   switch (srvType)
   {
      case LSO_TPTPROT_UDP:
         offSet = dumOffSet + 1;
         break;

      case LSO_TPTPROT_TCP:
         offSet = dumOffSet + 2;
         break;

      case LSO_TPTPROT_SCTP:
         offSet = dumOffSet + 3;
         break;

      case LSO_TPTPROT_TLS_TCP:
         offSet = dumOffSet + 4;
         break;

      default:
         offSet = dumOffSet + 1;
         break;
   }

   RETVALUE(entId * 10 + offSet);
} /* end of soAcDmGetTptSrvId() */


/*
 *
 *       Fun:    soAcDmSmGetSsapId - Get the SSAP ID from tptSrvId 
 *
 *       Desc:   
 *
 *       Ret:    0 or +ive value     - succeeded
 *               -ive value - failed
 *
 *       Notes:  None
 *
 *       File:   xx_dmsm.c
 *
 */

#ifdef ANSI
PUBLIC SpId soAcDmSmGetSsapId
(
U32            tptSrvId     /* transport server ID      */
)
#else
PUBLIC SpId soAcDmSmGetSsapId(tptSrvId)
U32            tptSrvId;     /* transport server ID      */
#endif /* ANSI */
{
   SpId    ssapId;
   U8      entId;
   U8      mod;

   TRC3(soAcDmSmGetSsapId)

   /*-- Default value --*/
   ssapId = 0;

   CMXTA_DBG_PARAM((_cmxtap, "soAcDmSmGetSsapId(): tptSrvId(%ld)\n", tptSrvId));

   /*-- Find associated entity --*/
   mod = tptSrvId % 10;

   entId = (tptSrvId - mod) / 10;

   /*-- Check if the real tptSrvId or a dummy one --*/
   /*-- The first four tptSrvId are the real ones --*/
   if (mod < 5)
      ssapId = entId * 2;
   else
      ssapId = entId * 2 + 1;

   RETVALUE(ssapId);
} /* end of soAcDmSmGetSsapId() */

/*
 *
 *       Fun:    soAcDmSmGetTsapId - Get the TSAP ID from tptSrvId 
 *
 *       Desc:   
 *
 *       Ret:    0 or +ive value     - succeeded
 *               -ive value - failed
 *
 *       Notes:  None
 *
 *       File:   xx_dmsm.c
 *
 */

#ifdef ANSI
PUBLIC SuId soAcDmSmGetTsapId
(
U32            tptSrvId     /* transport server ID      */
)
#else
PUBLIC SuId soAcDmSmGetTsapId(tptSrvId)
U32            tptSrvId;     /* transport server ID      */
#endif /* ANSI */
{
   /*U8      entId;*/
   U8      srvType;

   SuId    tsapId;

   TRC3(soAcDmSmGetTsapId)

   /*-- Default value --*/
   tsapId = 0;

   CMXTA_DBG_PARAM((_cmxtap, "soAcDmSmGetTsapId(): tptSrvId(%ld)\n", tptSrvId));

   srvType = soAcDmSmGetSrvType(tptSrvId);

   RETVALUE(tsapId);
} /* end of soAcDmSmGetTsapId() */



/*
 *
 *       Fun:    soAcDmSmGetDomainName - Get the Domain Name from entityId 
 *
 *       Desc:   
 *
 *       Ret:    0 or +ive value     - succeeded
 *               -ive value - failed
 *
 *       Notes:  None
 *
 *       File:   soac_lsoutl.c
 *
 */
#ifdef ANSI
PUBLIC S16 soAcDmSmGetDomainName
(
CmXtaTCCb *tcCb,
U32       entId,     /* transport server ID      */
Txt       *domainName
)
#else
PUBLIC S16 soAcDmSmGetDomainName(tcCb, entId, domainName)
CmXtaTCCb *tcCb;
U32       entId;     /* transport server ID      */
Txt       *domainName;    /* Host Id                  */
#endif /* ANSI */
{
   Txt               subDomain[100];
   Txt               secondDomain[100];
   Txt               topLevelDomain[100];
   Txt               tptProt[10];
   SoAcTCCb *soTcCb;

   CMXTA_DBG_PARAM((_cmxtap, "soAcDmSmGetDomainName(): entId(%ld)\n", entId));

   soTcCb = (SoAcTCCb *)tcCb->tcCb;

   switch(soTcCb->directives.tptType)
   {
      case LSO_TPTPROT_UDP:
         sprintf(tptProt, "%s", "udp");
         break;
      case LSO_TPTPROT_TCP:
         sprintf(tptProt, "%s", "tcp");
         break;
      case LSO_TPTPROT_SCTP:
         sprintf(tptProt, "%s", "sctp");
         break;
      case LSO_TPTPROT_TLS_TCP:
         sprintf(tptProt, "%s", "sctp");
         break;
      default:
         sprintf(tptProt, "%s", "udp");
         break;
      
   }; /* End of switch */
   
   
   /* Get the name of the entity from the array */
   /* Is there a possibility that entId might be an incorrect value, i.e. do we need some 
      checking here or not? */
   if ((entId < 0) || (entId > 40))
      sprintf(subDomain, "user");
   else
      sprintf(subDomain, "%s", entityDef[entId]);
   sprintf(secondDomain, "%s", "xxccin");
   sprintf(topLevelDomain, "%s", "com\0");
   sprintf(domainName, "%s%s.%s.%s", subDomain, tptProt, secondDomain, topLevelDomain);
   RETVALUE(CMXTA_ERR_NONE);
} /* End of soAcDmSmGetDomainName */

/*
 *
 *       Fun:    soAcDmSmGetHostName - Get the Host Name from tptSrvId 
 *
 *       Desc:   
 *
 *       Ret:    0 or +ive value     - succeeded
 *               -ive value - failed
 *
 *       Notes:  None
 *
 *       File:   xx_dmsm.c
 *
 */

#ifdef ANSI
PUBLIC S16 soAcDmSmGetHostName
(
CmXtaTCCb *tcCb,
U32       tptSrvId,     /* transport server ID      */
Txt       *hostName
)
#else
PUBLIC S16 soAcDmSmGetHostName(tcCb, tptSrvId, hostName)
CmXtaTCCb *tcCb;
U32       tptSrvId;     /* transport server ID      */
Txt       *hostName;
#endif /* ANSI */
{
   U8               entId;
   U8               mod;

   TRC3(soAcDmSmGetHostName)

   /*SOAC_ENHANCE: Get this value thru logic*/
   cmMemcpy((U8 *) hostName,
            (CONSTANT U8 *) "host1.domain.com",
            (PTR) cmStrlen((CONSTANT U8 *) "host1.domain.com") + 1);

   /*-- Find associated entity --*/
   mod = tptSrvId % 10;
   entId = (tptSrvId - mod) / 10;

   soAcDmSmGetDomainName(tcCb, entId, hostName);

   CMXTA_DBG_PARAM((_cmxtap, "soAcDmSmGetHostName(): tptSrvId(%ld)\n", tptSrvId));
   RETVALUE(CMXTA_ERR_NONE);
} /* end of soAcDmSmGetHostName() */

#ifdef SO_SCTP
/*
 *
 *       Fun:    soAcDmSmGetEndpAddr - 
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_dmsm.c
 *
 */
#ifdef ANSI
PUBLIC S16 soAcDmSmGetEndpAddr
(
U32            endpId,     /* Endpoint ID      */
SctNetAddrLst  *srcAddrLst
)
#else
PUBLIC S16 soAcDmSmGetEndpAddr(endpId, srcAddrLst)
U32            endpId;     /* Endpoint ID      */
SctNetAddrLst  *srcAddrLst;
#endif /* ANSI */
{


   U32 tmpU32;
   Bool sameIp;
   U8      entId;
   U8      mod;
   U32     baseIp;

   TRC3(soAcDmSmGetEndpAddr)

   CMXTA_DBG_PARAM((_cmxtap, "soAcDmSmGetEndpAddr(): endpId(%ld)\n", endpId));

   CMXTA_ZERO(srcAddrLst, sizeof(SctNetAddrLst));

   cmInetAddr("127.0.0.1", &tmpU32);
   /*-- Change it to host byte order --*/
   baseIp = CM_INET_NTOH_U32(tmpU32);

   /*-- SOAC_ENHANCE:  Should we listen at same IP for all entities, give an option from
       command line to either open on the same IP or use totally different IPs altogether --*/

   sameIp = FALSE;

   /*-- Find associated entity --*/
   mod = endpId % 10;
   entId = (endpId - mod) / 10;

   /*-- Calculate IP */
   if (sameIp == FALSE)
   {
      /*-- SOAC_ENHANCE:  can we do arithmetic operation on 
      host byte order, i guess so --*/
      baseIp = baseIp + entId;

   }

   srcAddrLst->nmb = 1;
   srcAddrLst->nAddr[0].type = CM_TPTADDR_IPV4;

   srcAddrLst->nAddr[0].u.ipv4NetAddr = baseIp;

   RETVALUE(CMXTA_ERR_NONE);
} /* end of soAcDmSmGetEndpAddr() */
#endif /*SO_SCTP*/


/*
 *
 *       Fun:    soAcDmSmGetDnsAddr - Get the DNS Address stored in TA
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_dmsm.c
 *
 */

#ifdef ANSI
PUBLIC S16 soAcDmSmGetDnsAddr
(
CmTptAddr      *dnsTptAddr
)
#else
PUBLIC S16 soAcDmSmGetDnsAddr(dnsTptAddr)
CmTptAddr      *dnsTptAddr;
#endif /* ANSI */
{
   U32 tmpU32;

   TRC3(soAcDmSmGetDnsAddr)

   CMXTA_DBG_PARAM((_cmxtap, "soAcDmSmGetDnsAddr():\n"));

   dnsTptAddr->type = CM_TPTADDR_IPV4;  

   /*SOAC_ENHANCE: Get the proper Logic */
   cmInetAddr(soAccCb.taCb.dnsIpAddr, &tmpU32);

   dnsTptAddr->u.ipv4TptAddr.address = CM_INET_NTOH_U32(tmpU32);

   dnsTptAddr->u.ipv4TptAddr.port = soAccCb.taCb.dnsPort;

   RETVALUE(CMXTA_ERR_NONE);
} /* end of soAcDmSmGetDnsAddr() */


/*
*
*       Fun:   svStr2Port
*
*       Desc:  Converts a string into Port
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  xx_tcutl.c
*
*/
#ifdef ANSI
PUBLIC Void svStr2Port
(
Txt            *word,                     /* text buffer */
CmInetAddr     *address                   /* target address */
)
#else
PUBLIC Void svStr2Port(word, address)
Txt            *word;                     /* text buffer */
CmInetAddr     *address;                  /* target address */
#endif
{
   /* local variable */
   U16            i;
   U32            tmpU32;

   tmpU32 = 0;

   for (i = 0; (word[i] != '\n') && (word[i] != '\0'); i++)
   {
      tmpU32 += word[i] - '0';
      tmpU32 *= 10;
   }
   tmpU32 /= 10;

   address->port = (U16) tmpU32;

   RETVOID;
}/* svStr2Port */


/*
*
*       Fun:   svStr2IP
*
*       Desc:  Converts a string into an IP
*
*       Ret:   Void
*
*       Notes: The IP will be in Network Byte Order
*
*       File:  xx_tcutl.c
*
*/

#ifdef ANSI
PUBLIC Void svStr2IP
(
Txt            *word,                    /* text buffer */
CmInetAddr     *address                  /* target address */
)
#else
PUBLIC Void svStr2IP(word, address)
Txt            *word;                    /* text buffer */
CmInetAddr     *address;                 /* target address */
#endif
{
   /* local variable */
   U32            tmpU32;            /* temporary */

   /* start with the IP part contained in the first word */
   cmInetAddr(word, &(tmpU32));

   address->address = CM_INET_NTOH_U32(tmpU32);

   RETVOID;
}/* svStr2IP --*/


/********************************************************************30**

         End of file:     cm_xta_lsgutl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:22 2015

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ----      aj      1. main release
*********************************************************************91*/
