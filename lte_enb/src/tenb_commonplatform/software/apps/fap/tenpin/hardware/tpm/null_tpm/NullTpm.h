///////////////////////////////////////////////////////////////////////////////
//
// TenpinTpm.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NullTpm_h_
#define __NullTpm_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinHardwareInterfaces.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class NullTpm : public threeway::ITenpinTpm
{
public:
    // Singleton
    virtual ~NullTpm() {};
    static shared_ptr<NullTpm> GetInstance(void);

    // Implement ITenpinTpm
    bool ExtractFapId(std::string& fapId);
    bool ExtractCertificateToFile(TpmCert certId, const char * filename);
    bool RsaSign(TpmSecEnv env, TpmPrivKey keyId, const std::string& data, std::string& signature);

    void RegisterCli(shared_ptr<CliHandler> handler);

private:
    // Singleton
    NullTpm() {};
    static shared_ptr<NullTpm> s_instance;
};

} // namespace threeway

#endif
