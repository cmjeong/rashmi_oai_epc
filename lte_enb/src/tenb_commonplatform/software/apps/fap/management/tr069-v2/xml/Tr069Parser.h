///////////////////////////////////////////////////////////////////////////////
//
// Tr069Parser
//
// Parses the TR069 XML to extract  contents
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069Parser_h_
#define __Tr069Parser_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <libxml/parser.h>

#include "xml/Tr069AddObject.h"
#include "xml/Tr069DeleteObject.h"
#include "xml/Tr069ParameterList.h"
#include "xml/Tr069AttributeList.h"
#include "xml/Tr069ParameterValueStruct.h"
#include "xml/Tr069SetParameterValues.h"

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class Tr069ParseParameterAttributeStruct
{
public:
    Tr069ParseParameterAttributeStruct(xmlNodePtr cur);
    ~Tr069ParseParameterAttributeStruct() {};

    std::string name;
    std::string notificationChange;
    std::string notification;
    std::string accessListChange;
    std::string accessList;
};

class Tr069ParseParameterAttributeList
{
public:
    Tr069ParseParameterAttributeList(xmlNodePtr cur);
    ~Tr069ParseParameterAttributeList() {
        parameterAttributeStruct.clear();
    }

    std::vector< boost::shared_ptr<Tr069ParseParameterAttributeStruct> > parameterAttributeStruct;
};

class Tr069ParseParameterNames
{
public:
	Tr069ParseParameterNames(xmlNodePtr cur);
	~Tr069ParseParameterNames() {
		aString.clear();
	}

	std::vector< std::string > aString;
};

class Tr069ParseSetParameterAttributes
{
public:
    Tr069ParseSetParameterAttributes(xmlNodePtr cur);

    boost::shared_ptr<Tr069ParseParameterAttributeList> parameterList;

};


class Tr069ParseInformResponse
{
public:
	Tr069ParseInformResponse(xmlNodePtr cur);

	std::string maxEnvelopes;

};

class Tr069ParseGetParameterValues
{
public:
	Tr069ParseGetParameterValues(xmlNodePtr cur);

	boost::shared_ptr<Tr069ParseParameterNames> parameterNames;

};

class Tr069ParseGetParameterNames
{
public:
	Tr069ParseGetParameterNames(xmlNodePtr cur);

	string parameterPath;
	string nextLevel;
};

class Tr069ParseGetParameterAttributes
{
public:
	Tr069ParseGetParameterAttributes(xmlNodePtr cur);

	boost::shared_ptr<Tr069ParseParameterNames> parameterNames;
};

class Tr069ParseGetRpcMethods
{
public:
	Tr069ParseGetRpcMethods(xmlNodePtr cur);
};

class Tr069ParseDownload
{
public:
    Tr069ParseDownload(xmlNodePtr cur);

    std::string commandKey;
    std::string fileType;
    std::string url;
    std::string username;
    std::string password;
    std::string fileSize;
    std::string targetFileName;
    std::string delaySeconds;
    std::string successUrl;
    std::string failureUrl;
};

class Tr069ParseTransferCompleteResponse
{
public:
    Tr069ParseTransferCompleteResponse(xmlNodePtr cur);

    std::string dummy;

};

class Tr069ParseFaultDetail
{
public:

    typedef enum FaultCode_tag
    {
        // Class: FGW
        MethodNotSupported_Server = 8000,
        RequestDenied_NoReasonSpecified_Server = 8001,
        InternalError_Server = 8002,
        InvalidArguments_Server = 8003,
        ResourceExceeded_Server = 8004,
        RetryRequest = 8005,

        UnauthorisedFap = 8800,
        UnexpectedEvent = 8801,
        FapAtUnauthorisedLocation = 8802,

        // Class: FAP
        NoFault = 0,
        MethodNotSupported = 9000,
        RequestDenied_NoReasonSpecified = 9001,
        InternalError = 9002,
        InvalidArguments = 9003,
        ResourceExceeded = 9004,
        InvalidParameterName = 9005,
        InvalidParameterType = 9006,
        InvalidParameterValue = 9007,
        AttemptToSetNonwritableParameter = 9008,
        NotificationRequestRejected = 9009,
        DownloadFailure = 9010,
        UploadFailure = 9011,
        FileTransferServerAuthenticationFailure = 9012,
        UnsupportedProtocolForFileTransfer = 9013
    } FaultCode;

    Tr069ParseFaultDetail(xmlNodePtr cur);

    std::string faultcode;
    std::string faultstring;
};

class Tr069ParseDetail
{
public:
    Tr069ParseDetail(xmlNodePtr cur);

    boost::shared_ptr<Tr069ParseFaultDetail> faultDetail;
};

class Tr069ParseFactoryReset
{
public:
    Tr069ParseFactoryReset(xmlNodePtr cur);

};

class Tr069ParseFault
{
public:
    Tr069ParseFault(xmlNodePtr cur);

    std::string faultcode;
    std::string faultstring;
    std::string faultactor;
    boost::shared_ptr<Tr069ParseDetail> detail;
};

class Tr069ParseReboot
{
public:
    Tr069ParseReboot(xmlNodePtr cur);

    std::string commandKey;
};

class Tr069ParseUpload
{
public:
    Tr069ParseUpload(xmlNodePtr cur);

    std::string commandKey;
    std::string fileType;
    std::string url;
    std::string username;
    std::string password;
    std::string delaySeconds;
};


class Tr069ParseBody
{
public:
	Tr069ParseBody(xmlNodePtr cur);

    boost::shared_ptr<AddObject> addObject;
    boost::shared_ptr<DeleteObject> deleteObject;
    boost::shared_ptr<Tr069ParseDownload> download;
    boost::shared_ptr<Tr069ParseFactoryReset> factoryReset;
    boost::shared_ptr<Tr069ParseFault> fault;
    boost::shared_ptr<Tr069ParseGetParameterValues> getParameterValues;
    boost::shared_ptr<Tr069ParseInformResponse> informResponse;
    boost::shared_ptr<SetParameterValues> setParameterValues;
    boost::shared_ptr<Tr069ParseSetParameterAttributes> setParameterAttributes;
    boost::shared_ptr<Tr069ParseReboot> reboot;
    boost::shared_ptr<Tr069ParseTransferCompleteResponse> transferCompleteResponse;
    boost::shared_ptr<Tr069ParseUpload> upload;
    boost::shared_ptr<Tr069ParseGetParameterNames> getParameterNames;
    boost::shared_ptr<Tr069ParseGetRpcMethods> getRpcMethods;
    boost::shared_ptr<Tr069ParseGetParameterAttributes> getParameterAttributes;
};

class Tr069ParseHeader
{
public:
	Tr069ParseHeader(xmlNodePtr cur);

	std::string holdRequests;
	std::string cwmp_Id;

};

class Tr069Parse
{
public:
    Tr069Parse(xmlNodePtr cur);

    boost::shared_ptr<Tr069ParseBody> body;
    boost::shared_ptr<Tr069ParseHeader> header;
};

}

#endif
