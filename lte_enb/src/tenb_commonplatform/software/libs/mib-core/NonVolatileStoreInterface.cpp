///////////////////////////////////////////////////////////////////////////////
//
// NonVolatileStoreInterface.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NonVolatileStoreInterface.h"

///////////////////////////////////////////////////////////////////////////////
// Functions
//
// Note: These are *not* members of NonVolatileStoreInterface, they are
// global scope functions that allow the use of << operator.  Hence we are
// not adding functionality to the NonVolatileStoreInterface *interface*
// class.
///////////////////////////////////////////////////////////////////////////////

std::ostream & operator<< (std::ostream & os, NvContainerDescriptor nvContainerDescriptor)
{
    ENTER();

    os << '[' << nvContainerDescriptor.m_nvContainerName << '/' << nvContainerDescriptor.m_nvContainerInstance << ']';

    RETURN(os);
}

std::ostream & operator<<(std::ostream & os, NvAttributeDescriptor nvAttributeDescriptor)
{
    ENTER();

    os << nvAttributeDescriptor.m_nvAttributeName << '/' << nvAttributeDescriptor.m_nvAttributeInstance;

    RETURN(os);
}

std::ostream & operator<<(std::ostream & os, NvAttribute nvAttribute)
{
    ENTER();

    os << nvAttribute.m_nvAttributeDescriptor << " = " << nvAttribute.m_nvAttributeValue.GetAsString();

    RETURN(os);
}
