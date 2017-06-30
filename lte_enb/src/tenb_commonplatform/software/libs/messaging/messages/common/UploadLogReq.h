 #include <system/Serialisable.h>
 #include <system/SerialisationIds.h>

#ifndef __UploadLogReq_h_
#define __UploadLogReq_h_

///////////////////////////////////////////////////////////////////////////////
//// Functions / Classes
/////////////////////////////////////////////////////////////////////////////////

namespace threeway
{ 
    class UploadLogReq : public threeway::Serialisable
    {
        public:
        /**
          * Default constructor.  For messaging internal use only.
         **/
         UploadLogReq()
         {
            isUploadFileToDel = true;
         };
         UploadLogReq(string fname)
         {
            fileToUpload = fname;
            isUploadFileToDel = true;
         };
         UploadLogReq(string fname, bool uploadFileToDel)
         {
            fileToUpload = fname;
            isUploadFileToDel = uploadFileToDel;
         }; 
       
        /**
        * Construct a Upload request message.
        *
        * 
        */
        virtual ~UploadLogReq() {};

        /**
         * Implement Serialisable pure virtuals.
         */
       virtual u32 GetSerialisationId() const { return SERIALISATION_ID_UPLOAD_LOG_REQ; };
       virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
       virtual bool DeSerialise(const u8* data, u32 dataLen);
       virtual std::string ToString() const;
       virtual std::string GetFileName()  { return fileToUpload; }
       virtual bool GetOpAfterFileUpload()  { return isUploadFileToDel; }

       private:
       string fileToUpload;
       bool isUploadFileToDel;
   };
}

#endif
