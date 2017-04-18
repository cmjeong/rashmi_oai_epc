 #include <system/Serialisable.h>
 #include <system/SerialisationIds.h>

#ifndef __AutonomousTransferComp_h_
#define __AutonomousTransferComp_h_

///////////////////////////////////////////////////////////////////////////////
//// Functions / Classes
/////////////////////////////////////////////////////////////////////////////////

namespace threeway
{ 
    class AutonomousTransferComp : public threeway::Serialisable
    {
        public:
        /**
          * Default constructor.  For messaging internal use only.
         **/
         AutonomousTransferComp() {};
         AutonomousTransferComp(string fname,string startTime,string completeTime, bool uploadSatus)
         {
            fileToUpload = fname;
            fileUploadStartTime = startTime;
            fileUploadCompleteTime = completeTime;
            isFileUploadSuccess = uploadSatus;
         }
       
        /**
        * Construct a Upload request message.
        *
        * 
        */
        virtual ~AutonomousTransferComp() {};

        /**
         * Implement Serialisable pure virtuals.
         */
       virtual u32 GetSerialisationId() const { return SERIALISATION_ID_AUTONOMOUS_TRANSFER_COMP; };
       virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
       virtual bool DeSerialise(const u8* data, u32 dataLen);
       virtual std::string ToString() const;
       virtual std::string GetFileName() const { return fileToUpload; };
       virtual std::string GetStartTime() const { return fileUploadStartTime; };
       virtual std::string GetCompleteTime() const { return fileUploadCompleteTime; };
       virtual bool GetUploadStatus() const { return isFileUploadSuccess; };

       private:
       string fileToUpload;
       string fileUploadStartTime;
       string fileUploadCompleteTime;
       bool isFileUploadSuccess;
   };
}

#endif
