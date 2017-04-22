///////////////////////////////////////////////////////////////////////////////
//
// OpensslX509.h
//
// Implements ITenpinX509 using openssl.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OpensslX509_h_
#define __OpensslX509_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <openssl/engine.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinX509Interfaces.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

class OpensslX509 : public ITenpinX509
{
public:
    // Singleton
    virtual ~OpensslX509() {}
    static shared_ptr<OpensslX509> GetInstance();

    // Implement ITenpinX509
    virtual bool SignatureVerify(
        const char * rootCertificate,
        const char * inputFilename,
        const char * outputFilename
    );

    virtual bool IKEv2CA(
        const char *    certificate,
        unsigned char * ca,
        unsigned int *  caLen
    );

    virtual bool ReportDates(
        const char * certificate,
        std::string& notBef,
        std::string& notAft
    );

    virtual bool ReportSubject(
        const char * certificate,
        std::string& subj
    );

    virtual bool VerifySHA1Signature(
        const char * signature,
        const char * data,
        const char * fapCertificate
    );

    virtual bool VerifySignedCert(
        const char * uppercert,
        const char * lowercert
    );

    void RegisterCli(shared_ptr<CliHandler> handler);

private:
    // Singleton
    OpensslX509();
    static shared_ptr<OpensslX509> s_instance;

    // SHA-1 hashing
    const EVP_MD * m_sha1;

    static shared_ptr<CliResponse> CliSubject(const CliArguments& cliArgs);
    static shared_ptr<CliResponse> CliDates(const CliArguments& cliArgs);
    static shared_ptr<CliResponse> CliVerify(const CliArguments& cliArgs);
    static shared_ptr<CliResponse> CliChain(const CliArguments& cliArgs);

    X509 * CertificateOpen(const char * filename, BIO ** bp);
    void CertificateClose(X509 ** xp, BIO ** fp);

    void TraceErrors(void);
    bool TraceNextError(void);
};

} // namespace threeway

#endif
