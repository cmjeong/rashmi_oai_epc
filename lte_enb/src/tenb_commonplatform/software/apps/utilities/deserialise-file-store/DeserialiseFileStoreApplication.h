///////////////////////////////////////////////////////////////////////////////
//
// DeserialiseFileStoreApplication.h
//
// Decode (deserialise and display) the contents of a SerialisableFileStore
// binary file.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __DeserialiseFileStoreApplication_h_
#define __DeserialiseFileStoreApplication_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Application.h>
#include <system/SerialisableFactory.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class DeserialiseFileStoreApplication : public threeway::Application, public threeway::SerialisableFactory
{
private:
    // Is singleton so private constructor.
    DeserialiseFileStoreApplication();

public:
    ~DeserialiseFileStoreApplication();
    static DeserialiseFileStoreApplication& GetInstance();

    virtual boost::shared_ptr<threeway::Serialisable> GetSerialisable(
                                                u32 serialisationId,
                                                const u8* serialisedData,
                                                u32 serialisedDataLen
                                                           );

private:
    static DeserialiseFileStoreApplication* s_instance;

    int Main(int argc, char * argv[]);

};

#endif
