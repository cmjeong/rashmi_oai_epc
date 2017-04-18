//////////////////////////////////////////////////////////////////////////////
//
// TenpinX509Interfaces.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinX509Interfaces_h_
#define __TenpinX509Interfaces_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <messaging/transport/CliHandler.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

class ITenpinX509
{
public:
    virtual ~ITenpinX509() {}

    virtual bool SignatureVerify(
        const char * rootCertificate,
        const char * inputFilename,
        const char * outputFilename
    ) = 0;

    /* IKEv2 CA value for a certificate (RFC 4306 Section 3.7) */
    virtual bool IKEv2CA(
        const char *    certificate,
        unsigned char * ca,
        unsigned int *  caLen
    ) = 0;

    virtual bool ReportDates(
        const char * certificate,
        std::string& notBef,
        std::string& notAft
    ) = 0;

    virtual bool ReportSubject(
        const char * certificate,
        std::string& subj
    ) = 0;

    virtual bool VerifySHA1Signature(
        const char * signature,
        const char * data,
        const char * fapCertificate
    ) = 0;

    virtual bool VerifySignedCert(
        const char * uppercert,
        const char * lowercert
    ) = 0;

    virtual void RegisterCli(shared_ptr<CliHandler> handler) = 0;
};

} // namespace threeway

#endif
