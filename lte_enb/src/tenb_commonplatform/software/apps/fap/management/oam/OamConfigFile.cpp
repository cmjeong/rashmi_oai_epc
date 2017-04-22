///////////////////////////////////////////////////////////////////////////////
//
// OamConfigFile.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////
#if 0
#ifdef PRODUCT_hbs2_iu

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#include <system/Trace.h>
#include <system/Url.h>

#include <messaging/messages/common/OamActionReq.h>
#include <messaging/messages/common/OamActionCnf.h>
#include <messaging/messages/common/ApplyUpdateReq.h>
#include <messaging/messages/common/ApplyUpdateCnf.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "OamUserApplication.h"
#include "OamConfigFile.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Local Macros
///////////////////////////////////////////////////////////////////////////////

#define Log(...) \
    TRACE_PRINTF("ConfigFile: " __VA_ARGS__)

#define ARRAY_LENGTH(arr) \
    (sizeof(arr) / sizeof((arr)[0]))

///////////////////////////////////////////////////////////////////////////////
// Local Types
///////////////////////////////////////////////////////////////////////////////

typedef struct ProcedureFileTag {

    const char * const  filename;
    const char * const  mode;
    FILE *              file;

} ProcedureFile_t;

typedef struct KeyValueTag {

    ProcedureFile_t *   from;
    const char * const  key;
    char                value[512];

} KeyValue_t;

typedef struct TftpTag {

    const char *    server;
    const char *    remoteFilename;
    const char *    localFilename;

} Tftp_t;

typedef struct UnpackTag {

    char    tarFilename[512];

} Unpack_t;

typedef bool (*ElementFunction)(
    struct ProcedureTag *   procedure,
    void *                  arg
);

typedef struct ProcedureElementTag {

    const char * const  name;
    ElementFunction     func;
    void *              arg;

} ProcedureElement_t;

typedef struct ProcedureStepTag {

    const char * const  name;
    ProcedureElement_t  elements[8];

} ProcedureStep_t;

typedef struct ProcedureTag {

    bool            configSigningEnable;
    ProcedureFile_t input;
    KeyValue_t      parsedServer;
    KeyValue_t      parsedFilename;
    KeyValue_t      parsedDnsServer1;
    KeyValue_t      parsedDnsServer2;

    ProcedureFile_t vendorConfig;
    KeyValue_t      gatewayVendor;

    ProcedureFile_t secGwConfig;
    KeyValue_t      secGwUrl1;
    KeyValue_t      secGwUrl2;
    KeyValue_t      secGwUrl3;

    ProcedureFile_t fsapiConfig;
    KeyValue_t      fsapiServerPort;
    KeyValue_t      fsapiClientAddress;
    KeyValue_t      fsapiClientPort;

    ProcedureFile_t eth0Config;
    KeyValue_t      eth0MTU;
    KeyValue_t      eth0DHCP;
    KeyValue_t      eth0StaticIpAddress;
    KeyValue_t      eth0StaticNetmask;
    KeyValue_t      eth0StaticGateway;

    ProcedureFile_t ipsecConfig;
    KeyValue_t      ikeSendIntermediateCerts;
    KeyValue_t      ipsecNatTPort;

    ProcedureFile_t dnsConfig;
    KeyValue_t      dnsIpAddress1;
    KeyValue_t      dnsIpAddress2;
    KeyValue_t      dnsIpAddress3;

    ProcedureStep_t stepParseInput;
    ProcedureStep_t stepDns;
    ProcedureStep_t stepTftp;
    ProcedureStep_t stepUnpack;
    ProcedureStep_t stepConfigureVendor;
    ProcedureStep_t stepConfigureSecGw;
    ProcedureStep_t stepConfigureFsapi;
    ProcedureStep_t stepConfigureEth0;
    ProcedureStep_t stepConfigureIPsec;
    ProcedureStep_t stepConfigureDNS;
    ProcedureStep_t stepCopyCertificates;

    Tftp_t      tftp;
    Unpack_t    unpack;
    char        command[512];
    bool        configured;

} Procedure_t;

///////////////////////////////////////////////////////////////////////////////
// Local Variables
///////////////////////////////////////////////////////////////////////////////

static bool FileOpen(Procedure_t * procedure, void * arg);
static bool FileClose(Procedure_t * procedure, void * arg);
static bool ParseKeyValue(Procedure_t * procedure, void * arg);
static bool DnsConfigure(Procedure_t * procedure, void * arg);
static bool TftpConfigure(Procedure_t * procedure, void * arg);
static bool TftpOpenPinhole(Procedure_t * procedure, void * arg);
static bool TftpDownload(Procedure_t * procedure, void * arg);
static bool TftpClosePinhole(Procedure_t * procedure, void * arg);
static bool UnpackConfigure(Procedure_t * procedure, void * arg);
static bool UnpackVerify(Procedure_t * procedure, void * arg);
static bool UnpackUntar(Procedure_t * procedure, void * arg);
static bool ApplyVendorConfig(Procedure_t * procedure, void * arg);
static bool ApplySecGwConfig(Procedure_t * procedure, void * arg);
static bool ApplyFsapiConfig(Procedure_t * procedure, void * arg);
static bool ApplyEth0Config(Procedure_t * procedure, void * arg);
static bool ApplyIPsecConfig(Procedure_t * procedure, void * arg);
static bool ApplyDNSConfig(Procedure_t * procedure, void * arg);
static bool ApplyCertificates(Procedure_t * procedure, void * arg);

static const char * const pathTmp = "/tmp/ConfigFile";

static Procedure_t procedure = {
    /* configSigningEnable */
    true,

    /* input */
    { "/etc/bootp.inf", "rb", },
    /* parsedServer */
    { &procedure.input, "TFTP_SERVER = ", },
    /* parsedFilename */
    { &procedure.input, "FILE_NAME = ", },
    /* parsedDnsServer1 */
    { &procedure.input, "DNS_SERVER = ", },
    /* parsedDnsServer2 */
    { &procedure.input, "DNS_SERVER = ", },

    /* vendorConfig */
    { "/tmp/ConfigFile/VENDOR_config.txt", "rb", },
    /* gatewayVendor */
    { &procedure.vendorConfig, "GATEWAY_VENDOR = ", },

    /* secGwConfig */
    { "/tmp/ConfigFile/CS_config.txt", "rb", },
    /* secGwUrl1 */
    { &procedure.secGwConfig, "", },
    /* secGwUrl2 */
    { &procedure.secGwConfig, "", },
    /* secGwUrl3 */
    { &procedure.secGwConfig, "", },

    /* fsapiConfig */
    { "/tmp/ConfigFile/FSAPI_config.txt", "rb", },
    /* fsapiServerPort */
    { &procedure.fsapiConfig, "SERVER_PORT = ", },
    /* fsapiClientAddress */
    { &procedure.fsapiConfig, "CLIENT_ADDRESS = ", },
    /* fsapiClientPort */
    { &procedure.fsapiConfig, "CLIENT_PORT = ", },

    /* eth0Config */
    { "/tmp/ConfigFile/ETH0_config.txt", "rb", },
    /* eth0MTU */
    { &procedure.eth0Config, "MTU = ", },
    /* eth0DHCP */
    { &procedure.eth0Config, "DHCP = ", },
    /* eth0StaticIpAddress */
    { &procedure.eth0Config, "IP_ADDRESS = ", },
    /* eth0StaticNetmask */
    { &procedure.eth0Config, "NETMASK = ", },
    /* eth0StaticGateway */
    { &procedure.eth0Config, "GATEWAY = ", },

    /* ipsecConfig */
    { "/tmp/ConfigFile/IPSEC_config.txt", "rb", },
    /* ikeSendIntermediateCerts */
    { &procedure.ipsecConfig, "SEND_INTERMEDIATE_CERTS = ", },
    /* ipsecNatTPort */
    { &procedure.ipsecConfig, "NAT-T_PORT = ", },

    /* dnsConfig */
    { "/tmp/ConfigFile/DNS_config.txt", "rb", },
    /* dnsIpAddress1 */
    { &procedure.dnsConfig, "", },
    /* dnsIpAddress2 */
    { &procedure.dnsConfig, "", },
    /* dnsIpAddress3 */
    { &procedure.dnsConfig, "", },

    /* stepParseInput */
    { "parse input",
      {
        { "open file",          FileOpen,       &procedure.input },
        { "parse server",       ParseKeyValue,  &procedure.parsedServer },
        { "parse filename",     ParseKeyValue,  &procedure.parsedFilename },
        { "parse dns server 1", ParseKeyValue,  &procedure.parsedDnsServer1 },
        { "parse dns server 2", ParseKeyValue,  &procedure.parsedDnsServer2 },
        { "close file",         FileClose,      &procedure.input },
      }
    },

    /* stepDns */
    { "dns",
      {
        { "configure",  DnsConfigure,   NULL },
      },
    },

    /* stepTftp */
    { "tftp",
      {
        { "configure",      TftpConfigure,      NULL },
        { "open pinhole",   TftpOpenPinhole,    NULL },
        { "download",       TftpDownload,       NULL },
        { "close pinhole",  TftpClosePinhole,   NULL },
      },
    },

    /* stepUnpack */
    { "unpack",
      {
        { "configure",  UnpackConfigure,    NULL },
        { "verify",     UnpackVerify,       NULL },
        { "untar",      UnpackUntar,        NULL },
      },
    },

    /* stepConfigureVendor */
    { "configure vendor",
      {
        { "open file",              FileOpen,           &procedure.vendorConfig },
        { "parse gateway vendor",   ParseKeyValue,      &procedure.gatewayVendor },
        { "apply",                  ApplyVendorConfig,  NULL },
        { "close file",             FileClose,          &procedure.vendorConfig },
      },
    },

    /* stepConfigureSecGw */
    { "configure SecGw",
      {
        { "open file",          FileOpen,           &procedure.secGwConfig },
        { "parse address 1",    ParseKeyValue,      &procedure.secGwUrl1 },
        { "parse address 2",    ParseKeyValue,      &procedure.secGwUrl2 },
        { "parse address 3",    ParseKeyValue,      &procedure.secGwUrl3 },
        { "apply",              ApplySecGwConfig,   NULL },
        { "close file",         FileClose,          &procedure.secGwConfig },
      },
    },

    /* stepConfigureFsapi */
    { "configure FSAPI",
      {
        { "open file",              FileOpen,           &procedure.fsapiConfig },
        { "parse server port",      ParseKeyValue,      &procedure.fsapiServerPort },
        { "parse client address",   ParseKeyValue,      &procedure.fsapiClientAddress },
        { "parse client port",      ParseKeyValue,      &procedure.fsapiClientPort },
        { "apply",                  ApplyFsapiConfig,   NULL },
        { "close file",             FileClose,          &procedure.fsapiConfig },
      },
    },

    /* stepConfigureEth0 */
    { "configure eth0",
      {
        { "open file",          FileOpen,           &procedure.eth0Config },
        { "parse MTU",          ParseKeyValue,      &procedure.eth0MTU },
        { "parse DHCP",         ParseKeyValue,      &procedure.eth0DHCP },
        { "parse IP address",   ParseKeyValue,      &procedure.eth0StaticIpAddress },
        { "parse netmask",      ParseKeyValue,      &procedure.eth0StaticNetmask },
        { "parse gateway",      ParseKeyValue,      &procedure.eth0StaticGateway },
        { "apply",              ApplyEth0Config,    NULL },
        { "close file",         FileClose,          &procedure.eth0Config },
      },
    },

    /* stepConfigureIPsec */
    { "configure IPsec",
      {
        { "open file",                          FileOpen,           &procedure.ipsecConfig },
        { "parse IKE send intermediate certs",  ParseKeyValue,      &procedure.ikeSendIntermediateCerts },
        { "parse NAT-T port",                   ParseKeyValue,      &procedure.ipsecNatTPort },
        { "apply",                              ApplyIPsecConfig,   NULL },
        { "close file",                         FileClose,          &procedure.ipsecConfig },
      },
    },

    /* stepConfigureDNS */
    { "configure DNS",
      {
        { "open file",          FileOpen,       &procedure.dnsConfig },
        { "parse address 1",    ParseKeyValue,  &procedure.dnsIpAddress1 },
        { "parse address 2",    ParseKeyValue,  &procedure.dnsIpAddress2 },
        { "parse address 3",    ParseKeyValue,  &procedure.dnsIpAddress3 },
        { "apply",              ApplyDNSConfig, NULL },
        { "close file",         FileClose,      &procedure.dnsConfig },
      },
    },

    /* stepCopyCertificates */
    { "copy certificates",
      {
        { "apply",  ApplyCertificates,  NULL },
      },
    },
};

///////////////////////////////////////////////////////////////////////////////
// Local Functions
///////////////////////////////////////////////////////////////////////////////

static bool IsIPv4Address(
    const char *    value
)
{
    struct sockaddr_in sa;

    if (    (value)
         && (1 == inet_pton(AF_INET, value, &sa.sin_addr))
       )
    {
        return true;
    }

    return false;
}

static bool ProcedureConfigure(
    Procedure_t *   p,
    bool            configSigningEnable
)
{
    if (!p || p->configured)
    {
        Log("failed to configure");
        return false;
    }

    p->configSigningEnable  = configSigningEnable;
    p->configured           = true;

    return true;
}

static bool ProcedureDoCommand(
    Procedure_t *   procedure,
    const char *    fmt,
    ...
)
{
    if (procedure && fmt)
    {
        int     n;
        va_list ap;

        va_start(ap, fmt);
        n = vsnprintf(procedure->command, sizeof(procedure->command), fmt, ap);
        va_end(ap);

        if (    (-1 < n)
             && (n < (int)sizeof(procedure->command))
           )
        {
            Log("executing command '%s'", procedure->command);

            if (0 == system(procedure->command))
            {
                return true;
            }
        }
    }

    return false;
}

/* Element Functions */

static bool FileOpen(
    Procedure_t *   procedure,
    void *          arg
)
{
    ProcedureFile_t *   pf = (ProcedureFile_t *)arg;

    if (pf && pf->filename && pf->mode && !pf->file)
    {
        pf->file = fopen(pf->filename, pf->mode);

        if (pf->file)
        {
            return true;
        }

        Log("failed to open file %s with mode %s", pf->filename, pf->mode);
    }

    return false;
}

static bool FileClose(
    Procedure_t *   procedure,
    void *          arg
)
{
    ProcedureFile_t *   pf = (ProcedureFile_t *)arg;

    if (pf && pf->file)
    {
        fclose(pf->file);
        pf->file = NULL;

        return true;
    }

    return false;
}

static bool ParseKeyValue(
    Procedure_t *   procedure,
    void *          arg
)
{
    KeyValue_t *    kv = (KeyValue_t *)arg;

    if (kv && kv->from && kv->from->file && kv->key)
    {
        static char buffer[512];

        size_t  keyLen   = strlen(kv->key);
        size_t  valueLen = sizeof(kv->value);
        char *  line     = fgets(buffer, sizeof(buffer), kv->from->file);

        if (line != buffer)
        {
            Log("failed to read line from %s", kv->from->filename);
        }
        else if (0 != strncmp(line, kv->key, keyLen))
        {
            Log("failed to read key '%s' from %s", kv->key, kv->from->filename);
        }
        else if (valueLen < (strlen(line) + 1 - keyLen))
        {
            Log("failed to copy value for key '%s' from %s", kv->key, kv->from->filename);
        }
        else
        {
            size_t copyLen = strlen(line) + 1 - keyLen; /* +1 for terminator */
            memcpy(kv->value, line + keyLen, copyLen);

            /* smash out any newline chars delivered by fgets() */
            for (size_t i = 0; i < copyLen; i++)
            {
                if (    ('\r' == kv->value[i])
                     || ('\n' == kv->value[i])
                   )
                {
                    kv->value[i] = '\0';
                    break;
                }
            }

            Log("parsed value '%s' for key '%s' from %s", kv->value, kv->key, kv->from->filename);
        }
    }

    /* returning true allows other steps to run */
    /* output value is indicator of success/failure */

    return true;
}

static bool DnsConfigure(
    Procedure_t *   procedure,
    void *          arg
)
{
    const char * const parsedDnsServer1 = procedure->parsedDnsServer1.value;
    const char * const parsedDnsServer2 = procedure->parsedDnsServer2.value;

    /* apply in reverse order, entries are added to the head of the list */

    if (IsIPv4Address(parsedDnsServer2))
    {
        IPv4Address addr(parsedDnsServer2);

        OamUserApplication::GetInstance().DnsServerAdd(0, addr);
    }

    if (IsIPv4Address(parsedDnsServer1))
    {
        IPv4Address addr(parsedDnsServer1);

        OamUserApplication::GetInstance().DnsServerAdd(0, addr);
    }

    return true;
}

static bool TftpConfigure(
    Procedure_t *   procedure,
    void *          arg
)
{
    const char * const parsedServer   = procedure->parsedServer.value;
    const char * const parsedFilename = procedure->parsedFilename.value;

    if (IsIPv4Address(parsedServer))
    {
        procedure->tftp.server = parsedServer;

        Log("configured server address %s", procedure->tftp.server);
    }

    if (strlen(parsedFilename))
    {
        procedure->tftp.remoteFilename = parsedFilename;

        Log("configured remote filename '%s'", procedure->tftp.remoteFilename);
    }

    if (procedure->tftp.remoteFilename)
    {
        const char * localFilename = strrchr(procedure->tftp.remoteFilename, '/');

        if (localFilename)
        {
            localFilename += 1;
        }
        else
        {
            localFilename = procedure->tftp.remoteFilename;
        }

        if (strlen(localFilename))
        {
            procedure->tftp.localFilename = localFilename;

            Log("configured local filename '%s'", procedure->tftp.localFilename);
        }

    }

    if (    procedure->tftp.server
         && procedure->tftp.remoteFilename
         && procedure->tftp.localFilename
       )
    {
        return true;
    }

    return false;
}

static bool TftpOpenPinhole(
    Procedure_t *   procedure,
    void *          arg
)
{
    IPAddress tftpServer(procedure->tftp.server);

    OamUserApplication::GetInstance().TftpOpenPinhole(tftpServer);

    return true;
}

static bool TftpDownload(
    Procedure_t *   procedure,
    void *          arg
)
{
    ProcedureDoCommand(
        procedure,
        "mkdir -p %s && cd %s && tftp -g -r '%s' -l '%s' %s 1>tftp.out 2>tftp.err",
        pathTmp,
        pathTmp,
        procedure->tftp.remoteFilename,
        procedure->tftp.localFilename,
        procedure->tftp.server
    );

    return true;
}

static bool TftpClosePinhole(
    Procedure_t *   procedure,
    void *          arg
)
{
    OamUserApplication::GetInstance().TftpClosePinhole();

    return true;
}

static bool UnpackConfigure(
    Procedure_t *   procedure,
    void *          arg
)
{
    if (procedure->tftp.localFilename)
    {
        int tarLen = sizeof(procedure->unpack.tarFilename);

        const char * extension = "";

        int localLen = strlen(procedure->tftp.localFilename);

        if (    (localLen < 4)
             || (0 != strcmp(".tar", procedure->tftp.localFilename + localLen - 4))
           )
        {
            extension = ".tar";
        }

        int s = snprintf(procedure->unpack.tarFilename, tarLen, "%s%s", procedure->tftp.localFilename, extension);

        if ((0 < s) && (s < tarLen))
        {
            Log("configured tar filename '%s'", procedure->unpack.tarFilename);

            return true;
        }
    }

    return false;
}

static bool UnpackVerify(
    Procedure_t *   procedure,
    void *          arg
)
{
    if (0 != strcmp(procedure->tftp.localFilename, procedure->unpack.tarFilename))
    {
        return ProcedureDoCommand(
            procedure,
            "mkdir -p %s && cd %s && /mnt/dbx/sigverify config '%s/%s' '%s/%s' 1>verify.out 2>verify.err",
            pathTmp,
            pathTmp,
            pathTmp,
            procedure->tftp.localFilename,
            pathTmp,
            procedure->unpack.tarFilename
        );
    }
    else if (!procedure->configSigningEnable)
    {
        return true;
    }

    return false;
}

static bool UnpackUntar(
    Procedure_t *   procedure,
    void *          arg
)
{
    return ProcedureDoCommand(
        procedure,
        "mkdir -p %s && cd %s && tar -xvf '%s' 1>untar.out 2>untar.err",
        pathTmp,
        pathTmp,
        procedure->unpack.tarFilename
    );
}

typedef ParamId (*NextParamId_fp)(ParamId id);

static ParamId ApplyIpAddress(
    ParamId         id,
    const char *    value,
    NextParamId_fp  nextParamId
)
{
    if (    (PARAM_ID_INVALID != id)
         && (IsIPv4Address(value))
       )
    {
        Log("applying IP Address %s", value);

        MibAttributeValues values;
        values.AddAttribute(id, value);
        OamUserApplication::GetInstance().GetMibCache().SetMibAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), values, ENTITY_OAM);

        return nextParamId(id);
    }

    return id;
}

static ParamId ApplyUrl(
    ParamId         id,
    const char *    value,
    NextParamId_fp  nextParamId
)
{
    if (    (PARAM_ID_INVALID != id)
         && (Url::FromString(string(value)))
       )
    {
        Log("applying Url %s", value);

        MibAttributeValues values;
        values.AddAttribute(id, value);
        OamUserApplication::GetInstance().GetMibCache().SetMibAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), values, ENTITY_OAM);

        return nextParamId(id);
    }

    return id;
}

static bool ApplyVendorConfig(
    Procedure_t *   procedure,
    void *          arg
)
{
    const char * value = procedure->gatewayVendor.value;

    Log("applying Gateway Vendor %s", value);

    MibAttributeValues values;
    values.AddAttribute( PARAM_ID_GATEWAY_VENDOR, value);
    OamUserApplication::GetInstance().GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), values, ENTITY_OAM);

    return true;
}

static ParamId NextSecGwServerParamId(
    ParamId id
)
{
    switch (id)
    {
    case PARAM_ID_LTE_SEC_GW_SERVER_1: return PARAM_ID_LTE_SEC_GW_SERVER_2;   break;
    case PARAM_ID_LTE_SEC_GW_SERVER_2: return PARAM_ID_LTE_SEC_GW_SERVER_3;   break;
    default:                          return PARAM_ID_INVALID;              break;
    }
}

static bool ApplySecGwConfig(
    Procedure_t *   procedure,
    void *          arg
)
{
    ParamId id = PARAM_ID_LTE_SEC_GW_SERVER_1;

    id = ApplyUrl(id, procedure->secGwUrl1.value, NextSecGwServerParamId);
    id = ApplyUrl(id, procedure->secGwUrl2.value, NextSecGwServerParamId);
    id = ApplyUrl(id, procedure->secGwUrl3.value, NextSecGwServerParamId);

    return true;
}

static bool ApplyFsapiConfig(
    Procedure_t *   procedure,
    void *          arg
)
{
    if (strlen(procedure->fsapiServerPort.value))
    {
        int serverPort = atoi(procedure->fsapiServerPort.value);

        if (0 <= serverPort)
        {
            Log("applying FSAPI server port %d", serverPort);
        }
    }

    if (strlen(procedure->fsapiClientAddress.value))
    {
        int clientPort = 0;

        if (strlen(procedure->fsapiClientPort.value))
        {
            clientPort = atoi(procedure->fsapiClientPort.value);

            if (clientPort < 0)
            {
                clientPort = 0;
            }
        }

        Log("applying FSAPI client address %s", procedure->fsapiClientAddress.value);
        Log("applying FSAPI client port %d", clientPort);
    }

    return true;
}

static void ApplyEth0MTU(
    char *  value
)
{
    if (strlen(value))
    {
        const int min = 576;
        const int max = 1500;

        int  mtu    = atoi(value);
        bool apply  = ((min <= mtu) && (mtu <= max));

        Log("%s eth0 MTU %s", (apply ? "applying" : "discarding"), value);

        if (apply)
        {
            MibAttributeValues values;
            values.AddAttribute(PARAM_ID_MTU, (u32)mtu);
            OamUserApplication::GetInstance().GetMibCache().SetMibAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), values, ENTITY_OAM);
        }
    }
}

static void ApplyEth0DHCP(
    char *  value
)
{
    if (strlen(value))
    {
        u32 dhcp = ((0 == atoi(value)) ? 0 : 1);

        Log("applying eth0 DHCP %d", dhcp);

        MibAttributeValues values;
        values.AddAttribute(PARAM_ID_DHCP, dhcp);
        OamUserApplication::GetInstance().GetMibCache().SetMibAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), values, ENTITY_OAM);
    }
}

static void ApplyEth0IPv4AddressParam(
    ParamId id,
    const char *  name,
    char *  value
)
{
    if (    (PARAM_ID_INVALID != id)
         && (name)
         && (strlen(value))
       )
    {
        bool apply = IsIPv4Address(value);

        Log("%s eth0 %s %s", (apply ? "applying" : "discarding"), name, value);

        if (apply)
        {
            MibAttributeValues values;
            values.AddAttribute(id, value);
            OamUserApplication::GetInstance().GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), values, ENTITY_OAM);
        }
    }
}

static bool ApplyEth0Config(
    Procedure_t *   procedure,
    void *          arg
)
{
    ApplyEth0MTU(procedure->eth0MTU.value);
    ApplyEth0DHCP(procedure->eth0DHCP.value);
    ApplyEth0IPv4AddressParam(PARAM_ID_STATIC_IP_CONFIG_IP_ADDRESS, "static IP address", procedure->eth0StaticIpAddress.value);
    ApplyEth0IPv4AddressParam(PARAM_ID_STATIC_IP_CONFIG_NET_MASK, "static netmask", procedure->eth0StaticNetmask.value);
    ApplyEth0IPv4AddressParam(PARAM_ID_STATIC_IP_CONFIG_GATEWAY, "static gateway", procedure->eth0StaticGateway.value);

    return true;
}

static void ApplyIkeSendIntermediateCerts(
    char *  value
)
{
    if (strlen(value))
    {
        u32 certs = ((0 == atoi(value)) ? 0 : 1);

        Log("applying IKE send intermediate certs %d", certs);

        MibAttributeValues values;
        values.AddAttribute(PARAM_ID_IKE_SEND_INTERMEDIATE_CERTS, certs);
        OamUserApplication::GetInstance().GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), values, ENTITY_OAM);
    }
}

static void ApplyIPsecNatTPort(
    char *  value
)
{
    if (strlen(value))
    {
        int port = atoi(value);

        if (    (port < 0)
             || (65535 < port)
           )
        {
            port = 0;
        }

        Log("applying IPsec NAT-T port %d", port);

        MibAttributeValues values;
        values.AddAttribute(PARAM_ID_IPSEC_NAT_T_PORT, (u32)port);
        OamUserApplication::GetInstance().GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), values, ENTITY_OAM);
    }
}

static bool ApplyIPsecConfig(
    Procedure_t *   procedure,
    void *          arg
)
{
    ApplyIkeSendIntermediateCerts(procedure->ikeSendIntermediateCerts.value);
    ApplyIPsecNatTPort(procedure->ipsecNatTPort.value);

    return true;
}

static ParamId NextDNSServerParamId(
    ParamId id
)
{
    switch (id)
    {
    case PARAM_ID_DNS_SERVER_ADDRESS_1: return PARAM_ID_DNS_SERVER_ADDRESS_2; break;
    case PARAM_ID_DNS_SERVER_ADDRESS_2: return PARAM_ID_DNS_SERVER_ADDRESS_3; break;
    default:                            return PARAM_ID_INVALID;              break;
    }
    return PARAM_ID_INVALID;
}

static bool ApplyDNSConfig(
    Procedure_t *   procedure,
    void *          arg
)
{
    ParamId id = PARAM_ID_DNS_SERVER_ADDRESS_1;

    id = ApplyIpAddress(id, procedure->dnsIpAddress1.value, NextDNSServerParamId);
    id = ApplyIpAddress(id, procedure->dnsIpAddress2.value, NextDNSServerParamId);
    id = ApplyIpAddress(id, procedure->dnsIpAddress3.value, NextDNSServerParamId);
    return true;
}

static bool ApplyCertificates(
    Procedure_t *   procedure,
    void *          arg
)
{
    return ProcedureDoCommand(
        procedure,
        "mkdir -p %s && cd %s && chmod 644 *.pem 1>certificates.out 2>certificates.err && cp *.pem /mnt/certificates/trusted/ 1>>certificates.out 2>>certificates.err",
        pathTmp,
        pathTmp
    );
}

/* procedure steps */

static void ProcedureStep(
    Procedure_t *       procedure,
    ProcedureStep_t *   step
)
{
    bool success = true;

    for (size_t i = 0; success && (i < ARRAY_LENGTH(step->elements)); i++)
    {
        ProcedureElement_t * element = &step->elements[i];

        if (element->func)
        {
            Log("doing %s for step %s...", element->name, step->name);

            success = element->func(procedure, element->arg);

            if (!success)
            {
                Log("...failed to %s", element->name);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Global Functions
///////////////////////////////////////////////////////////////////////////////

void OamConfigFileProcedure(
    bool    configSigningEnable
)
{
    if (ProcedureConfigure(&procedure, configSigningEnable))
    {
        ProcedureStep(&procedure, &procedure.stepParseInput);
        ProcedureStep(&procedure, &procedure.stepDns);
        ProcedureStep(&procedure, &procedure.stepTftp);
        ProcedureStep(&procedure, &procedure.stepUnpack);
        ProcedureStep(&procedure, &procedure.stepConfigureVendor);
        ProcedureStep(&procedure, &procedure.stepConfigureSecGw);
        ProcedureStep(&procedure, &procedure.stepConfigureFsapi);
        ProcedureStep(&procedure, &procedure.stepConfigureEth0);
        ProcedureStep(&procedure, &procedure.stepConfigureIPsec);
        ProcedureStep(&procedure, &procedure.stepConfigureDNS);
        ProcedureStep(&procedure, &procedure.stepCopyCertificates);
    }
}

#endif /* PRODUCT_hbs2_iu */
#endif
