///////////////////////////////////////////////////////////////////////////////
//
// NullX509.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NullX509_h_
#define __NullX509_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinX509Interfaces.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

class NullX509 : public ITenpinX509
{
public:
    // Singleton
    virtual ~NullX509() {}
    static shared_ptr<NullX509> GetInstance();

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

    virtual void RegisterCli(shared_ptr<CliHandler> handler);

private:
    // Singleton
    NullX509() {}
    static shared_ptr<NullX509> s_instance;
};

} // namespace threeway

#endif
