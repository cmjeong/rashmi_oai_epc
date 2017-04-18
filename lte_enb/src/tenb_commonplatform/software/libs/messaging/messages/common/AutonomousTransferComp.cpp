#include <sstream>
#include <system/Trace.h>
#include <system/SerialisationUtils.h>
#include "AutonomousTransferComp.h"

using namespace std;
using namespace threeway;

/////////////////////////////////////////////////////////////////////////////
// Class Functions
/////////////////////////////////////////////////////////////////////////////

s32 AutonomousTransferComp::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();
    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(fileToUpload, serialisedData);
    SerialiseIt(fileUploadStartTime, serialisedData);
    SerialiseIt(fileUploadCompleteTime, serialisedData);
    SerialiseIt(isFileUploadSuccess, serialisedData);
    
    RETURN(serialisedData - data);
}

bool AutonomousTransferComp::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    DeSerialiseIt(fileToUpload, data,80);
    DeSerialiseIt(fileUploadStartTime, data,80);
    DeSerialiseIt(fileUploadCompleteTime, data,80);
    DeSerialiseIt(isFileUploadSuccess, data);

    RETURN(true);
}

std::string AutonomousTransferComp::ToString() const
{
     ENTER();

     ostringstream stream;
     stream << "File Requested To Upload: " <<fileToUpload ;

     RETURN(stream.str());
}

