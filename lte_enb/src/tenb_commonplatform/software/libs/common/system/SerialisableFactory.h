///////////////////////////////////////////////////////////////////////////////
//
// SerialisableFactory.h
//
// Interface for declaring that a class that can take serialised data and
// create the correct Serialisable object from it.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SerialisableFactory_h_
#define __SerialisableFactory_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Serialisable.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class SerialisableFactory
{
public:
    /**
     * Deserialise data and create object to pass back to user via
     * a shared pointer.
     *
     * \param serialisationId    Unique ID that let's us create the correct
     *                           type of object.
     * \param serialisedData     Data to deserialise.
     * \param serialisedDataLen  Length of data to deserialise in bytes.
     * \return                   Shared ptr to created object or NULL if failed.
     */
    virtual boost::shared_ptr<Serialisable> GetSerialisable(
                                                u32 serialisationId,
                                                const u8* serialisedData,
                                                u32 serialisedDataLen
                                                           ) = 0;

    /**
     * Make destructor virtual to remove compiler warnings.
     */
    virtual ~SerialisableFactory () {};
};

}

#endif
