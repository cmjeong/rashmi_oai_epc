#include <sstream>
#include <system/Trace.h>
#include <system/SerialisationUtils.h>
#include "UploadLogReq.h"

using namespace std;
using namespace threeway;

/////////////////////////////////////////////////////////////////////////////
// Class Functions
/////////////////////////////////////////////////////////////////////////////

s32 UploadLogReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();
    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(fileToUpload, serialisedData);
    SerialiseIt(isUploadFileToDel,serialisedData);    
    RETURN(serialisedData - data);
}

bool UploadLogReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    DeSerialiseIt(fileToUpload, data,80);
    DeSerialiseIt(isUploadFileToDel,data);
     /* fairly arbitrary limit check - enum has gaps so can't easily do t    his programmatically */
    RETURN(true);
}

std::string UploadLogReq::ToString() const
{
     ENTER();

     ostringstream stream;
     stream << "File Requested To Upload: " <<fileToUpload ;

     RETURN(stream.str());
}

