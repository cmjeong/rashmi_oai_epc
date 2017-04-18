///////////////////////////////////////////////////////////////////////////////
//
// Serialisable.h
//
// Interface for declaring that a class can be serialised/deserialised for
// transferring/storing as a byte array.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Serialisable_h_
#define __Serialisable_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <3waytypes.h>
#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SerialisedData.h"

using namespace boost;

#ifdef __cplusplus

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class Serialisable
{
public:
    /**
     * Destructor must be virtual or you'll get memory leaks
     */
    virtual ~Serialisable () {}

    /**
     * Get a unique serialisation ID for the class being serialised.
     * This can be transmitted/stored along with the serialisation data if to
     * resolve what the data is a serialisation of.
     *
     * In your Serialisable class you must return a UNIQUE u32 when compared
     * to the SerialisationId's of other classes including classes in the same
     * inheritance hierarchy.  Yes, this isn't straightforward to manage but
     * you could do it by having a global enum/consts or by just being careful.
     */
    virtual u32 GetSerialisationId() const = 0;

    /**
     * Serialise the object.
     *
     * This should write to 'data' and return the number of bytes written.
     * The data should include everything required to reconstruct the object
     * using the DeSerialise method.
     *
     * \param data The location to write the serialised data into.
     * \param dataMaxBytes The available space at 'data'.
     * \return Number of bytes written to 'data' or -1 if couldn't serialise
     *         e.g. because there wasn't enough space at 'data'.
     */
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const = 0;

    /**
     * Deserialise the object.
     *
     * This should put the object into the state expressed by the serialised
     * data.  Don't call this directly, use the template method below.
     *
     * \param data The location to read the serialised data from.
     * \param dataLen Length of 'data'.
     */
    virtual bool DeSerialise(const u8* data, u32 dataLen) = 0;

    /**
     * Deserialise the object.
     *
     * This is done as a templated function so any derived type can be
     * deserialised safely.  Will return NULL if the data fails validation.
     */
    template<class T> static boost::shared_ptr<T> DeSerialise(const u8* data, u32 dataLen)
    {
        boost::shared_ptr<T> deserialisedObject(new T());
        if (!deserialisedObject->DeSerialise(data, dataLen))
        {
            // discard the object as invalid
            deserialisedObject.reset();
        }
        return deserialisedObject;
    }

    template<class T> static boost::shared_ptr<T> DeSerialise(boost::shared_ptr<SerialisedData> serialisedData)
    {
        boost::shared_ptr<T> deserialisedObject(new T());
        if (!deserialisedObject->DeSerialise(serialisedData->GetSerialData(), serialisedData->GetSerialDataLength()))
        {
            // discard the object as invalid
            deserialisedObject.reset();
        }
        return deserialisedObject;
    }

    /**
     * Get detailed information about the message as a string for debug/presentation.
     */
    virtual std::string ToString() const = 0;

    /**
     * Get one line of information summarising the message as a string.
     * This short form of message information is used for tracing and may omit
     * the full details of the message to give just the key content.
     */
    virtual std::string ToBriefString() const { return std::string(); };

    /**
     * Print verbose information describing the message as a string.
     * This gives a super-set of information to that normally returned by
     * ToBriefString() or ToString(), and writes output directly to the passed
     * file.  The function returns true if anything was printed, false otherwise.
     * This function is most suited to decoding binary payloads such as NAS
     * messages.
     */
    virtual bool        PrintDetailsToFile(FILE *f) const { return false; };

protected:

};

} // namespace threeway

#endif // __cplusplus


#endif
