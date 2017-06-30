///////////////////////////////////////////////////////////////////////////////
//
// OpensslX509.cpp
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <openssl/bio.h>
#include <openssl/asn1.h>
#include <openssl/err.h>
#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/objects.h>
#include <openssl/pem.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinX509.h"
#include "OpensslX509.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

shared_ptr<OpensslX509> OpensslX509::s_instance;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

OpensslX509::OpensslX509()
{
    m_sha1 = EVP_sha1();
    ERR_load_crypto_strings();
    OpenSSL_add_all_digests();
}

shared_ptr<OpensslX509> OpensslX509::GetInstance()
{
    if (NULL == s_instance)
    {
        s_instance.reset(new OpensslX509());
    }

    return s_instance;
}

void OpensslX509::TraceErrors(
    void
)
{
    bool more;

    do
    {
        more = TraceNextError();
    }
    while (more);
}

bool OpensslX509::TraceNextError(
    void
)
{
    const char * errFile;
    int          errLine;
    const char * errData;
    int          errFlags;

    unsigned long errCode = ERR_get_error_line_data(&errFile, &errLine, &errData, &errFlags);

    if (errCode)
    {
        TRACE_PRINTF("openssl error: %lu at %s:%d", errCode, errFile, errLine);
        TRACE_PRINTF("... %s", ERR_error_string(errCode, NULL));

        if (errData && (errFlags & ERR_TXT_STRING))
        {
            TRACE_PRINTF("... %s", errData);
        }
    }

    return (errCode ? true : false);
}

X509 * OpensslX509::CertificateOpen(
    const char *    filename,
    BIO **          bp
)
{
    X509 * xp = NULL;

    if (    filename
         && (bp && (NULL == *bp))
       )
    {
        *bp = BIO_new_file(filename, "rb");

        if (*bp)
        {
            const size_t len = strlen(filename);

            if (    (4 < len)
                 && (0 == strncmp(filename + len - 4, ".cer", 4))
               )
            {
                /* assume DER format */
                xp = d2i_X509_bio(*bp, NULL);
            }
            else
            {
                /* assume PEM format */
                xp = PEM_read_bio_X509(*bp, NULL, NULL, NULL);
            }
        }
    }

    return xp;
}

void OpensslX509::CertificateClose(
    X509 ** xp,
    BIO **  bp
)
{
    if (xp && *xp) { X509_free(*xp); *xp = NULL; }
    if (bp && *bp) { BIO_free(*bp);  *bp = NULL; }
}

void OpensslX509::RegisterCli(
    shared_ptr<CliHandler>  handler
)
{
    CliCmdDescriptor x509Subject = { "subject", 1, 1, "ate", "subject <certificate> ", "Report certificate subject name" };
    handler->RegisterCliCmd(x509Subject, &OpensslX509::CliSubject);

    CliCmdDescriptor x509Dates = { "dates", 1, 1, "ate", "dates <certificate> ", "Report certificate validity dates" };
    handler->RegisterCliCmd(x509Dates, &OpensslX509::CliDates);

    CliCmdDescriptor x509Verify = { "verify", 3, 3, "ate", "verify <signature> <data> <certificate>", "Reports Verification: success or failure (assumes sha1 digest)" };
    handler->RegisterCliCmd(x509Verify, &OpensslX509::CliVerify);

    CliCmdDescriptor x509Chain = { "chain", 1, 4, "ate", "chain <self-signed> [root-signed [intermediate-signed...", "Reports certificate chain authentication: success or failure" };
    handler->RegisterCliCmd(x509Chain, &OpensslX509::CliChain);
}

shared_ptr<CliResponse> OpensslX509::CliSubject(
    const CliArguments& cliArgs
)
{
    shared_ptr<OpensslX509> x509 = OpensslX509::GetInstance();

    int    result  = CLI_ERROR_COMMAND_FAILED;
    string subject;

    if (x509->ReportSubject(cliArgs.at(0).c_str(), subject))
    {
        result = CLI_ERROR_NONE;
    }
    return shared_ptr<CliResponse>(new CliResponse(subject, result));
}

shared_ptr<CliResponse> OpensslX509::CliDates(
    const CliArguments& cliArgs
)
{
    shared_ptr<OpensslX509> x509 = OpensslX509::GetInstance();

    int    result  = CLI_ERROR_COMMAND_FAILED;
    string output, notBef, notAft;

    if (x509->ReportDates(cliArgs.at(0).c_str(), notBef, notAft))
    {
        output = notBef + "\n" + notAft;
        result = CLI_ERROR_NONE;
    }

    return shared_ptr<CliResponse>(new CliResponse(output, result));
}

shared_ptr<CliResponse>  OpensslX509::CliVerify(
    const CliArguments& cliArgs
)
{
    shared_ptr<OpensslX509> x509 = OpensslX509::GetInstance();
    string output = "failure";
    int    result  = CLI_ERROR_COMMAND_FAILED;

    if (x509->VerifySHA1Signature(cliArgs.at(0).c_str(), cliArgs.at(1).c_str(), cliArgs.at(2).c_str()))
    {
        output = "success";
        result  = CLI_ERROR_NONE;
    }
    return shared_ptr<CliResponse>(new CliResponse(output, result));
}

shared_ptr<CliResponse>  OpensslX509::CliChain(
    const CliArguments& cliArgs
)
{
    shared_ptr<OpensslX509> x509 = OpensslX509::GetInstance();
    int    result = CLI_ERROR_COMMAND_FAILED;
    size_t i = 0;
    string output;

    for (i = 0; i < cliArgs.size(); i++)
    {
        if (0 == i) // the first certificate is self-signed:
        {
            if (!x509->VerifySignedCert(cliArgs.at(i).c_str(), cliArgs.at(i).c_str())) { break; }
        }
        else
        {
            if (!x509->VerifySignedCert(cliArgs.at(i - 1).c_str(), cliArgs.at(i).c_str())) { break; }
        }
    }
    if (i == cliArgs.size())
    {
        output = "success";
        result = CLI_ERROR_NONE;
    }
    else
    {
        output = "failure\n" + cliArgs.at(i);
    }
    return shared_ptr<CliResponse>(new CliResponse(output, result));
}

bool OpensslX509::SignatureVerify(
    const char * rootCertificate,
    const char * inputFilename,
    const char * outputFilename
)
{
    bool verified = false;

    if (rootCertificate && inputFilename && outputFilename)
    {
        BIO * b_root   = BIO_new_file(rootCertificate, "rb");
        BIO * b_input  = BIO_new_file(inputFilename,   "rb");
        BIO * b_output = BIO_new_file(outputFilename,  "w");

        X509_STORE * x_store = X509_STORE_new();

        if (b_root && b_input && b_output && x_store)
        {
            X509 *  x_root = d2i_X509_bio(b_root, NULL);
            PKCS7 * p_data = d2i_PKCS7_bio(b_input, NULL);

            if (    (x_root && p_data)
                 && (0 < X509_STORE_add_cert(x_store, x_root))
                 && (1 == PKCS7_verify(p_data, NULL, x_store, NULL, b_output, 0))
               )
            {
                verified = true;
            }

            if (x_root) { X509_free(x_root); }
            if (p_data) { PKCS7_free(p_data); }
        }

        if (x_store)  { X509_STORE_free(x_store); }
        if (b_output) { BIO_free(b_output); }
        if (b_input)  { BIO_free(b_input); }
        if (b_root)   { BIO_free(b_root); }

        TraceErrors();
    }

    return verified;
}

bool OpensslX509::IKEv2CA(
    const char *    certificate,
    unsigned char * ca,
    unsigned int *  caLen
)
{
    bool result = false;

    if (certificate && ca && caLen && (EVP_MAX_MD_SIZE <= *caLen) && m_sha1)
    {
        BIO *  b_cert = NULL;
        X509 * x_cert = CertificateOpen(certificate, &b_cert);

        if (x_cert)
        {
            int publicKeyLen = i2d_X509_PUBKEY(X509_get_X509_PUBKEY(x_cert), NULL);

            if (0 < publicKeyLen)
            {
                unsigned char *  publicKey = (unsigned char *)malloc(publicKeyLen);
                unsigned char *  buffer    = publicKey;

                if (    (publicKey && buffer)
                     && (publicKeyLen == i2d_X509_PUBKEY(X509_get_X509_PUBKEY(x_cert), &buffer))
                   )
                {
                    EVP_MD_CTX ctx;
                    EVP_DigestInit(&ctx, m_sha1);
                    EVP_DigestUpdate(&ctx, publicKey, publicKeyLen);
                    EVP_DigestFinal(&ctx, ca, caLen);

                    free(publicKey);

                    result = true;
                }
            }
        }

        CertificateClose(&x_cert, &b_cert);
        TraceErrors();
    }

    return result;
}

bool OpensslX509::VerifySignedCert(
    const char * uppercert,
    const char * lowercert
)
{
    bool result = false;
    bool selfsigned = false;

    if (uppercert && lowercert)
    {
        if (0 == strcmp(uppercert, lowercert))
        {
            selfsigned = true;
        }

        BIO * b_upper = NULL;
        BIO * b_lower = NULL;

        X509 * x_upper = CertificateOpen(uppercert, &b_upper);
        X509 * x_lower = NULL;

        if (x_upper)
        {
            x_lower = (selfsigned) ? x_upper : CertificateOpen(lowercert,  &b_lower);

            if (x_lower)
            {
                int ans;
                if  (1 == (ans = X509_verify(x_lower, X509_PUBKEY_get(x_upper->cert_info->key))))
                {
                    result = true;
                }
                else
                {
                    TRACE_PRINTF("X509: Verify result failed, ans = %i", ans);
                }

            }

            if (selfsigned) { x_lower = NULL; }
        }

        CertificateClose(&x_lower, &b_lower);
        CertificateClose(&x_upper, &b_upper);

        TraceErrors();
    }

    return result;
}

bool OpensslX509::VerifySHA1Signature(
    const char * signature,
    const char * data,
    const char * fapCertificate
)
{
    bool verified = false;

    if (signature && data && fapCertificate && m_sha1)
    {
        BIO *  b_cert = NULL;
        X509 * x_cert = CertificateOpen(fapCertificate, &b_cert);

        if (x_cert)
        {
            FILE * f_sig = fopen(signature, "rb");

            if (f_sig)
            {
                struct stat st_sig;

                if (0 == stat(signature, &st_sig))
                {
                    const size_t    siglen       = st_sig.st_size;
                    unsigned char * signaturebuf = (unsigned char *)malloc(siglen);

                    if (signaturebuf)
                    {
                        EVP_MD_CTX ctx;

                        if (    (siglen == fread(signaturebuf, 1, siglen, f_sig))
                             && (1 == EVP_VerifyInit(&ctx, m_sha1))
                             && (1 == EVP_VerifyUpdate(&ctx, data, strlen(data)))
                             && (1 == EVP_VerifyFinal(&ctx, signaturebuf, siglen, X509_PUBKEY_get(x_cert->cert_info->key)))
                           )
                        {
                            verified = true;
                        }

                        free(signaturebuf);
                    }
                }

                fclose(f_sig);
            }
        }

        CertificateClose(&x_cert, &b_cert);
        TraceErrors();
    }

    return verified;
}

bool OpensslX509::ReportSubject(
    const char * certificate,
    string&      subj
)
{
    bool        result = false;
    BIO *       b_cert = NULL;
    X509 *      x_cert = CertificateOpen(certificate, &b_cert);

    if (x_cert)
    {
        BIO * out = BIO_new(BIO_s_mem());

        if (out)
        {
            int         NIDs[] = { NID_countryName, NID_localityName, NID_stateOrProvinceName, NID_organizationName, NID_organizationalUnitName, NID_commonName, 0 };
            const char * SNs[] = { SN_countryName,  SN_localityName,  SN_stateOrProvinceName,  SN_organizationName,  SN_organizationalUnitName,  SN_commonName,  NULL };
            X509_NAME_ENTRY * subjpart;
            BUF_MEM * bm;

            for (int attrIndex = 0; (0 != NIDs[attrIndex]); attrIndex++)
            {
                int index, nextIndex = -1;

                do
                {
                    index = nextIndex;
                    nextIndex = X509_NAME_get_index_by_NID(x_cert->cert_info->subject, NIDs[attrIndex], index);
                }
                while (0 <= nextIndex);

                if (    (0 <= index)
                     && (subjpart = X509_NAME_get_entry(x_cert->cert_info->subject, index))
                     && (0 < subjpart->value->length)
                   )
                {
                    BIO_printf(out, "/%s=", SNs[attrIndex]);
                    ASN1_STRING_print(out, subjpart->value);
                }
            }

            BIO_get_mem_ptr(out, &bm);

            if (0 < bm->length)
            {
                subj.assign(bm->data, bm->length);
                TRACE_PRINTF("X509: Subject name: %s", subj.c_str());
                result = true;
            }
            else
            {
                TRACE_PRINTF("X509: subject: nothing in BIO");
            }

            BIO_free(out);
        }
    }

    CertificateClose(&x_cert, &b_cert);
    TraceErrors();

    return result;
}

bool OpensslX509::ReportDates(
    const char * certificate,
    string&      notBef,
    string&      notAft
)
{
    bool   AftResult = false;
    bool   BefResult = false;

    BIO *  b_cert = NULL;
    X509 * x_cert = CertificateOpen(certificate, &b_cert);

    if (x_cert)
    {
        BIO * out = BIO_new(BIO_s_mem());

        if (out)
        {
            BUF_MEM *bm;
            if (0 < ASN1_TIME_print(out, x_cert->cert_info->validity->notAfter))
            {
                BIO_get_mem_ptr(out, &bm);

                if (0 < bm->length)
                {
                    notBef.assign(bm->data, bm->length);
                    TRACE_PRINTF("X509: Valid from:  %s", notBef.c_str());
                    BefResult = true;
                }
            }
            if (    (1 == BIO_reset(out))
                 && (0 < ASN1_TIME_print(out, x_cert->cert_info->validity->notBefore))
               )
            {
                BIO_get_mem_ptr(out, &bm);

                if (0 < bm->length)
                {
                    notAft.assign(bm->data, bm->length);
                    TRACE_PRINTF("X509: Valid until: %s", notAft.c_str());
                    AftResult = true;
                }
            }

            BIO_free(out);
        }
    }

    CertificateClose(&x_cert, &b_cert);
    TraceErrors();

    return (BefResult && AftResult);
}

