///////////////////////////////////////////////////////////////////////////////
//
// Tr069AutoTransferCompResponse.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069AutoTransferCompResponse_h_
#define __Tr069AutoTransferCompResponse_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "Tr069Application.h"
#include "Tr069XmlStringUtils.h"

using namespace std;
using namespace boost;
using namespace tr069;

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

class AutoTransferCompResponse : public Xmlable
{
public:
    AutoTransferCompResponse( string fileName, string sTime, string cTime, bool status) 
    {
       uploadFileName = fileName;
       startTime = sTime;
       completeTime = cTime;
       isUploadSuccess = status;
       TRACE_PRINTF("AutoTransferCompResponse():filename=%s ,startTime=%s",fileName.c_str(),sTime.c_str());
    }

    virtual ~AutoTransferCompResponse()
    {}

    bool QueryValid() const
    {
        return true;
    }

    string Xmlise() const
    {
        std::ostringstream txAutonomousTransferCompReq;
        string xmlString;
        if(QueryValid())
        {
            std::ostringstream ss;
            ss<<random();
            string cwmp_id = ss.str();
           
       //     txAutonomousTransferCompReq << "<soap-env:Envelope" << tr069::tr069XmlNsHeaderPreamble << ">"
       //     "<soap-env:Header>"
       //     "<cwmp:ID soap-env:mustUnderstand=\"1\">"<<cwmp_id<<"</cwmp:ID>";
       //       txAutonomousTransferCompReq  <<
       //     "</soap-env:Header>"
            txAutonomousTransferCompReq<<
            "<soap-env:Body>"
            "<cwmp:AutonomousTransferComplete>"
            "<AnnounceURL></AnnounceURL>"
            "<TransferURL></TransferURL>"
            "<IsDownload>false</IsDownload>"
            "<FileType>"<<"4 Vendor Log File"<<"</FileType>"
            "<FileSize>0</FileSize>"
            "<TargetFileName>"<<uploadFileName<<"</TargetFileName>"
            "<FaultStruct>";
             if(isUploadSuccess != true)
             {
                 txAutonomousTransferCompReq  <<
                     "<FaultCode>9011</FaultCode>"
                     "<FaultString>Upload Failure</FaultString>";
             }
             else
             {
                 txAutonomousTransferCompReq  <<
                   "<FaultCode>0</FaultCode>"
                   "<FaultString></FaultString>";
              }
              txAutonomousTransferCompReq  <<
              "</FaultStruct>"
              "<StartTime>"<<startTime<<"</StartTime>"
              "<CompleteTime>"<<completeTime<<"</CompleteTime>"
              "</cwmp:AutonomousTransferComplete>"
              "</soap-env:Body>";
           //   "</soap-env:Envelope>";
        }
        else
        {
            TRACE_PRINTF("AutoTransferCompResponse::Xmlise(invalid)")
        }

        xmlString = XmlStringUtils::ToElementString("cwmp:AutoTransferCompResponse", txAutonomousTransferCompReq.str());
        return xmlString;
    }

private:
    string uploadFileName,startTime,completeTime;
     bool isUploadSuccess;

};

}

#endif
