///////////////////////////////////////////////////////////////////////////////
//
// TenpinHardwareInterfaces.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinHardwareInterfaces_h_
#define __TenpinHardwareInterfaces_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <messaging/transport/CliHandler.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef enum TpmGroupEnum
{
	TPM_GROUP_VERSION,
	TPM_GROUP_ID,
	TPM_GROUP_CERT,
	TPM_GROUP_SEC_ENV,
	TPM_GROUP_PUB_KEY,
	TPM_GROUP_PRIV_KEY,
	TPM_GROUP_3DES,
	TPM_GROUP_DUMMY,
} TpmGroup;

// Indexes; must match record id in the TPM file system
typedef enum TpmVersionEnum
{
	TPM_VERSION_TPM_FS = 1
} TpmVersion;

typedef enum TpmIdEnum
{
	TPM_ID_FAP   = 1,
	TPM_ID_BATCH = 2
} TpmId;

typedef enum TpmCertEnum
{
    TPM_CERT_FAP           = 1,  // FAP certificate w/ 2048-bit key
    TPM_CERT_RADISYS_BATCH = 2,  // Radisys Intermediate Batch certificate
    TPM_CERT_RADISYS_ROOT1 = 3,  // Radisys root ca 1 certificate
    TPM_CERT_RADISYS_ROOT2 = 4,  // Radisys root ca 2 certificate
    TPM_CERT_RADISYS_SPARE = 5   // Radisys spare certificate
} TpmCert;

typedef enum TpmSecEnvEnum
{
    TPM_SEC_ENV_RSA_ENCDEC       = 1,
    TPM_SEC_ENV_RSA_SIGN         = 3,
    TPM_SEC_ENV_RSA_SIGN_SHA1    = 4,
    TPM_SEC_ENV_RSA_SIGN_SHA256  = 5,
    TPM_SEC_ENV_3DES_ENCDEC_KEY1 = 6,
    TPM_SEC_ENV_3DES_ENCDEC_KEY2 = 7,
    TPM_SEC_ENV_3DES_SIGN_KEY1   = 8,
    TPM_SEC_ENV_3DES_SIGN_KEY2   = 9
} TpmSecEnv;

typedef enum TpmPubKeyEnum
{
    TPM_PUB_KEY_FAP           = 1,
    TPM_PUB_KEY_RADISYS_ROOT1 = 2,
    TPM_PUB_KEY_RADISYS_ROOT2 = 3,
    TPM_PUB_KEY_RADISYS_SPARE = 4
} TpmPubKey;

typedef enum TpmPrivKeyEnum
{
    TPM_PRIV_KEY_FAP = 1     // rsa private keys
} TpmPrivKey;

typedef enum TpmDesKeyEnum
{
    TPM_3DES_KEY1 = 1,    // global secret 3des key 1
    TPM_3DES_KEY2 = 2     // global secret 3des key 2
} TpmDesKey;

typedef enum TpmDummyEnum
{
    TPM_DUMMY1 = 1,
    TPM_DUMMY2 = 2
} TpmDummy;

typedef struct TpmRecordStruct
{
    const u8     groupIndex;
    const u8     recordIndex;
    const char * name;
} TpmRecord;

typedef struct TpmFSGroupInfo
{
	const u8     groupIndex;
    const char * path;
    const char * format;
    const char * name;
} TpmGroupInfo;

typedef struct TpmStateStruct
{
    u8           value;
    const char * name;
} TpmState;


///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

class ITenpinTpm
{
public:
    virtual ~ITenpinTpm() {}

    virtual bool ExtractFapId(std::string& fapId) = 0;

    virtual bool ExtractCertificateToFile(
        TpmCert      certId,
        const char * filename
    ) = 0;

    virtual bool RsaSign(
        TpmSecEnv          secenvId,
        TpmPrivKey         keyId,
        const std::string& data,
        std::string&       signature
    ) = 0;

    virtual void RegisterCli(shared_ptr<threeway::CliHandler> handler) = 0;

};

class ITenpinHardware
{
public:
    virtual ~ITenpinHardware() {}

    virtual shared_ptr<ITenpinTpm> GetTpm() = 0;
};

} // namespace threeway

#endif
