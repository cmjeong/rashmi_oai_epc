///////////////////////////////////////////////////////////////////////////////
//
// SetParameterAttribute.h
//
// Simple class to encapsulate an alarm event.  These can be raised by any
// entity/module and sent to OAM or other event handler.  Derived classes
// can add other information such as device or MO address.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SetParameterAttribute_h_
#define __SetParameterAttribute_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <time.h>
#include <string>

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/TimeWrap.h>
#include <system/AlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class SetParameterAttribute : public Serialisable
{
public:

    // Constants

    /**
     * Serialisation format version.
     * Allows us to serialise to file then check version on reading back.
     */
    static const u8 SERIALISATION_FORMAT = 0;

    /**
     * Maximum length of the additional info string.
     */
    static const u32 ATTRIBUTE_NAME_MAX_LENGTH = 512;

    // Typedefs

    /**
     * Attribute Notification.  Speaks for itself hopefully.
     */
    typedef enum
    {
        SET_PARAMETER_ATTRIBUTE_NOTIFICATION_BEGIN = 0,

        SET_PARAMETER_ATTRIBUTE_NOTIFICATION_OFF = 0,
        SET_PARAMETER_ATTRIBUTE_NOTIFICATION_PASSIVE = 1,
        SET_PARAMETER_ATTRIBUTE_NOTIFICATION_ACTIVE = 2,

        SET_PARAMETER_ATTRIBUTE_NOTIFICATION_END

    } SetParameterAttributeNotification;

    /**
     * Default constructor.  For messaging internal use only.
     */
    SetParameterAttribute();

    /**
     * Construct an alarm event.
     *
     * \param id             ID for the alarm.  Will be specific to a particular platform/product.
     * \param lifetime       Transient or non-transient?  Transient alarms don't have lifetimes.
     * \param severity       Level of severity, includes 'CLEARED' to clear an active non-transient alarm.
     * \param additionalInfo Any other info that may be useful in resolving the problem.
     * \param alarmType      Type/category of alarm.
     */
    SetParameterAttribute(
            std::string & name,
            SetParameterAttributeNotification notification );

    virtual ~SetParameterAttribute() {};


    /**
     * Getters.
     */
    std::string GetName() const { return m_name; };
    SetParameterAttributeNotification GetNotification() const { return m_notification; };

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_SET_PARAMETER_ATTRIBUTE; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

private:
    std::string m_name;
    SetParameterAttributeNotification  m_notification;
};

}

#endif
