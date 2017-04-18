///////////////////////////////////////////////////////////////////////////////
//
// ValidationFailureDescriptor.h
//
// Provides detailed information on the reason for a validation failure.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidationFailureDescriptor_h_
#define __ValidationFailureDescriptor_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidationFailureDescriptor
{
public:

    enum ValidationFailureCause
    {
        CAUSE_NOT_SPECIFIED = 0,
        CAUSE_OBJECT_DOES_NOT_EXIST,
        CAUSE_NOT_ALLOWED_ON_OBJECT,
        CAUSE_ATTRIBUTE_ID_NOT_FOUND,
        CAUSE_BELOW_MINIMUM,
        CAUSE_ABOVE_MAXIMUM,
	CAUSE_NOT_VALID_VALUE,
        CAUSE_TOO_SHORT,
        CAUSE_TOO_LONG,
        CAUSE_TOO_MANY,
        CAUSE_READ_ONLY,
        CAUSE_INVALID,
        CAUSE_OTHER
    };

    /**
     * Default constructor.
     */
    ValidationFailureDescriptor();

    /**
     * Destructor.
     */
    virtual ~ValidationFailureDescriptor() {};

    /**
     * Set the reason for validation failure.
     * Not done at construction so we can efficiently call validators with the same instance
     * of one of these classes as normally validation won't fail.  Don't want to be constructing
     * one to pass back every time from the validate function for no reason.
     */
    void Set(ValidationFailureCause cause, const std::string& description);
    void Set(ValidationFailureCause cause);

    /**
     * Get info about the failure.
     */
    std::string GetDescription() const { return m_failureDescription; };
    ValidationFailureCause GetCause() const { return m_failureCause; };

    /**
     * Get as string.  Combines the description and a textual representation of the cause.
     */
    virtual std::string ToString() const;

protected:

private:
    std::string m_failureDescription;
    ValidationFailureCause m_failureCause;

};

#endif
