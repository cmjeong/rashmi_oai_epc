///////////////////////////////////////////////////////////////////////////////
//
// NullX509.cpp
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinX509.h"
#include "NullX509.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

shared_ptr<NullX509> NullX509::s_instance;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

shared_ptr<NullX509> NullX509::GetInstance()
{
    if (NULL == s_instance)
    {
        s_instance.reset(new NullX509());
    }

    return s_instance;
}

bool NullX509::SignatureVerify(
    const char * rootCertificate,
    const char * inputFilename,
    const char * outputFilename
)
{
    /* failed to verify */
    return false;
}

bool NullX509::IKEv2CA(
    const char *    certificate,
    unsigned char * ca,
    unsigned int *  caLen
)
{
    /* failed to generate CA value */
    return false;
}

bool NullX509::ReportDates(
    const char * certificate,
    std::string& notBef,
    std::string& notAft
)
{
    return false;
}

bool NullX509::ReportSubject(
    const char * certificate,
    std::string& subj
)
{
	return false;
}

bool NullX509::VerifySHA1Signature(
    const char * signature,
    const char * data,
    const char * fapCertificate
)
{
	/* failed to verify signature */
	return false;
}

bool NullX509::VerifySignedCert(
    const char * uppercert,
    const char * lowercert
)
{
	/* failed to verify signed certificate */
	return false;
}

void NullX509::RegisterCli(
    shared_ptr<CliHandler>  handler
)
{
	/* failed to register CLI */
	return;
}
