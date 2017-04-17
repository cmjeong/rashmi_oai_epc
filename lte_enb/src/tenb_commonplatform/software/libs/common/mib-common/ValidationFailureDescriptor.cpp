///////////////////////////////////////////////////////////////////////////////
//
// ValidationFailureDescriptor.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidationFailureDescriptor.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

ValidationFailureDescriptor::ValidationFailureDescriptor() :
    m_failureDescription(""),
    m_failureCause(CAUSE_NOT_SPECIFIED)
{
    ENTER();
    EXIT();
}

void ValidationFailureDescriptor::Set(ValidationFailureCause cause, const std::string& description)
{
    ENTER();

    m_failureDescription = description;
    m_failureCause = cause;

    EXIT();
}

void ValidationFailureDescriptor::Set(ValidationFailureCause cause)
{
    ENTER();

    m_failureCause = cause;

    EXIT();
}

string ValidationFailureDescriptor::ToString() const
{
    ENTER();

    ostringstream stream;

    switch(m_failureCause)
    {
    case CAUSE_NOT_SPECIFIED:           stream << "NotSpecified";       break;
    case CAUSE_OBJECT_DOES_NOT_EXIST:   stream << "ObjectDoesNotExist"; break;
    case CAUSE_NOT_ALLOWED_ON_OBJECT:   stream << "NotAllowedOnObject"; break;
    case CAUSE_ATTRIBUTE_ID_NOT_FOUND:  stream << "AttributeIdNotFound";break;
    case CAUSE_BELOW_MINIMUM:           stream << "BelowMinimum";       break;
    case CAUSE_ABOVE_MAXIMUM:           stream << "AboveMaximum";       break;
    case CAUSE_NOT_VALID_VALUE:         stream << "NotValidValue";      break;
    case CAUSE_TOO_SHORT:               stream << "TooShort";           break;
    case CAUSE_TOO_LONG:                stream << "TooLong";            break;
    case CAUSE_TOO_MANY:                stream << "TooManyInstances";   break;
    case CAUSE_READ_ONLY:               stream << "ReadOnly";           break;
    case CAUSE_INVALID:                 stream << "Invalid";            break;
    case CAUSE_OTHER:                   stream << "Other";              break;
    }

    if(m_failureDescription.length() > 0)
    {
        stream << ": " << m_failureDescription;
    }

    RETURN(stream.str());
}
