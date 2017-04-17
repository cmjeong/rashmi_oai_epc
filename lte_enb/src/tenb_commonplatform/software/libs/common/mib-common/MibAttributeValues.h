///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeValues.h
//
// Typedefs/classes for MIB attribute ID / value pairs.  This is used by
// MIB CREATE-MO, SET ATTRIBUTES APIs.  We don't need/want to transfer entire
// attribute descriptions in these messages.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibAttributeValues_h_
#define __MibAttributeValues_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <set>
#include <sstream> // ostringstream used in ToString()
#include <string>

#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/SerialisationUtils.h>
#include <MibAttributeId.h>

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributeDescriptors.h"
#include "MibDN.h"
#include "MibAttributeIds.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

// TODO: This limit seems a bit arbitrary... need to think about this a bit more.
static const u32 MIB_MAX_STRING_LENGTH = 1024;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Base class for representing a value of an attribute in the MIB.
 */
class MibAttributeValue : public threeway::Serialisable
{
public:

    /**
     * Factory for MibAttributeValues.  Create object given type and string representation.
     */
    static boost::shared_ptr<MibAttributeValue> Create(MibAttributeType type, const std::string& valueAsString);

    /**
     * Constructor/destructor.
     */
    MibAttributeValue(MibAttributeType type) : m_type(type) {};
    MibAttributeValue() { m_type = MIB_ATTRIBUTE_TYPE_U32; }; // Not to be used directly; only for Serialisable::DeSerialise()
    virtual ~MibAttributeValue() {};

    /**
     * Accessors.
     */
    MibAttributeType GetType() const { return m_type; };

    virtual u32 GetValueU32() const { RSYS_ASSERT_PRINTF(false, "Not u32 value! %s", ToString().c_str()); return 0; };
    virtual std::vector<u32> GetValueU32Array() const { RSYS_ASSERT_PRINTF(false, "Not u32Array value! %s", ToString().c_str()); return std::vector<u32>(); };
    virtual s32 GetValueS32() const { RSYS_ASSERT_PRINTF(false, "Not s32 value! %s", ToString().c_str()); return 0; };
    virtual std::vector<s32> GetValueS32Array() const { RSYS_ASSERT_PRINTF(false, "Not s32Array value! %s", ToString().c_str()); return std::vector<s32>(); };
    virtual std::string GetValueString() const { RSYS_ASSERT_PRINTF(false, "Not string value! %s", ToString().c_str()); return "";};
    virtual std::vector<std::string> GetValueStringArray() const { RSYS_ASSERT_PRINTF(false, "Not string array value! %s", ToString().c_str()); return std::vector<std::string>();};

    virtual std::string GetValueAsString(bool longFormat = false) const = 0;
    virtual bool IsValueEqual(const MibAttributeValue& rhs) const = 0;

    /**
     * Implement Serialisable virtuals.
     */
    virtual std::string ToString() const { std::ostringstream stream; stream << getMibAttributeTypeName(m_type); return stream.str(); };

protected:
    MibAttributeType m_type;
};

/**
 * Concrete class for representing a U32 value in the MIB.
 */
class MibAttributeValueU32 : public MibAttributeValue
{
public:
    MibAttributeValueU32(u32 value) : MibAttributeValue(MIB_ATTRIBUTE_TYPE_U32), m_value(value) {};
    MibAttributeValueU32() { m_value = 0; };  // Not to be used directly; only for Serialisable::DeSerialise()
    virtual ~MibAttributeValueU32() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_ATTRIBUTE_VALUE_U32; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const { RSYS_ASSERT(dataMaxBytes >= 4); SerialiseIt(m_value, data); return 4; };
    virtual bool DeSerialise(const u8* data, u32 dataLen) { RSYS_ASSERT(dataLen == 4); DeSerialiseIt(m_value, data); return true; };
    virtual std::string ToString() const { std::ostringstream stream; stream << m_value; return stream.str(); };

    virtual u32 GetValueU32() const { return m_value; };

    virtual std::string GetValueAsString(bool longFormat) const;
    virtual bool IsValueEqual(const MibAttributeValue& rhs) const { return m_value == rhs.GetValueU32(); };

private:
    u32 m_value;
};

/**
 * Concrete class for representing a S32 value in the MIB.
 */
class MibAttributeValueS32 : public MibAttributeValue
{
public:
    MibAttributeValueS32(s32 value) : MibAttributeValue(MIB_ATTRIBUTE_TYPE_S32), m_value(value) {};
    MibAttributeValueS32() { m_value = 0; }; // Not to be used directly; only for Serialisable::DeSerialise()
    virtual ~MibAttributeValueS32() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_ATTRIBUTE_VALUE_S32; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const { RSYS_ASSERT(dataMaxBytes >= 4); SerialiseIt(m_value, data); return 4; };
    virtual bool DeSerialise(const u8* data, u32 dataLen) { RSYS_ASSERT(dataLen == 4); DeSerialiseIt(m_value, data); return true; };
    virtual std::string ToString() const { std::ostringstream stream; stream << m_value; return stream.str(); };

    virtual s32 GetValueS32() const { return m_value; };

    virtual std::string GetValueAsString(bool longFormat) const;
    virtual bool IsValueEqual(const MibAttributeValue& rhs) const { return m_value == rhs.GetValueS32(); };

private:
    s32 m_value;
};

/**
 * Concrete class for representing a string value in the MIB.
 */
class MibAttributeValueString : public MibAttributeValue
{
public:
    MibAttributeValueString(const std::string& value) : MibAttributeValue(MIB_ATTRIBUTE_TYPE_STRING), m_value(value) {};
    MibAttributeValueString(const char * value) : MibAttributeValue(MIB_ATTRIBUTE_TYPE_STRING), m_value(value) {};
    MibAttributeValueString() {};
    virtual ~MibAttributeValueString() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_ATTRIBUTE_VALUE_STRING; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const { RSYS_ASSERT(dataMaxBytes > 2 + m_value.size()); u8* dataStart = data; SerialiseIt(m_value, data); return data - dataStart; };
    virtual bool DeSerialise(const u8* data, u32 dataLen) { DeSerialiseIt(m_value, data, MIB_MAX_STRING_LENGTH); return true; };
    virtual std::string ToString() const { std::ostringstream stream; stream << "\"" << m_value << "\""; return stream.str(); };

    virtual std::string GetValueString() const { return m_value; };

    virtual std::string GetValueAsString(bool longFormat) const { return m_value; };
    virtual bool IsValueEqual(const MibAttributeValue& rhs) const { return m_value == rhs.GetValueString(); };

private:
    std::string m_value;
};

/**
 * Concrete class for representing string array values in the MIB.
 */
class MibAttributeValueStringArray : public MibAttributeValue
{
public:
    MibAttributeValueStringArray(const std::vector<std::string> & value) : MibAttributeValue(MIB_ATTRIBUTE_TYPE_STRINGARRAY), m_value(value) {};
    MibAttributeValueStringArray(const char * value) : MibAttributeValue(MIB_ATTRIBUTE_TYPE_STRINGARRAY)
    {
       m_value.push_back(value);
    };
    MibAttributeValueStringArray() {};
    virtual ~MibAttributeValueStringArray() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_ATTRIBUTE_VALUE_STRINGARRAY; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const { RSYS_ASSERT(dataMaxBytes > 2 + m_value.capacity()); u8* dataStart = data; SerialiseIt(m_value, data); return data - dataStart; }
    virtual bool DeSerialise(const u8* data, u32 dataLen) { DeSerialiseIt(m_value, data, MIB_MAX_STRING_LENGTH); return true; }
    virtual std::string ToString() const { return(GetValueAsString(false)); }

    virtual std::vector<std::string> GetValueStringArray() const { return m_value; }

    virtual std::string GetValueAsString(bool longFormat) const;
    virtual bool IsValueEqual(const MibAttributeValue& rhs) const;

private:
    std::vector<std::string> m_value;
};

/**
 * Concrete class for representing u32 array values in the MIB.
 */
class MibAttributeValueU32Array : public MibAttributeValue
{
public:
    MibAttributeValueU32Array(const std::vector<u32> & value) : MibAttributeValue(MIB_ATTRIBUTE_TYPE_U32ARRAY), m_value(value) {};
    MibAttributeValueU32Array(u32 value) : MibAttributeValue(MIB_ATTRIBUTE_TYPE_U32ARRAY)
    {
       m_value.push_back(value);
    };
    MibAttributeValueU32Array() {};
    virtual ~MibAttributeValueU32Array() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_ATTRIBUTE_VALUE_U32ARRAY; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const { u8* dataStart = data; SerialiseIt(m_value, data); return data - dataStart; }
    virtual bool DeSerialise(const u8* data, u32 dataLen) { DeSerialiseIt(m_value, data); return true; }
    virtual std::string ToString() const { return(GetValueAsString(false)); }

    virtual std::vector<u32> GetValueU32Array() const { return m_value; }

    virtual std::string GetValueAsString(bool longFormat) const;
    virtual bool IsValueEqual(const MibAttributeValue& rhs) const;

private:
    std::vector<u32> m_value;
};

/**
 * Concrete class for representing s32 array values in the MIB.
 */
class MibAttributeValueS32Array : public MibAttributeValue
{
public:
    MibAttributeValueS32Array(const std::vector<s32> & value) : MibAttributeValue(MIB_ATTRIBUTE_TYPE_S32ARRAY), m_value(value) {};
    MibAttributeValueS32Array(s32 value) : MibAttributeValue(MIB_ATTRIBUTE_TYPE_S32ARRAY)
    {
       m_value.push_back(value);
    }
    MibAttributeValueS32Array() {};
    virtual ~MibAttributeValueS32Array() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_ATTRIBUTE_VALUE_S32ARRAY; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const { u8* dataStart = data; SerialiseIt(m_value, data); return data - dataStart; }
    virtual bool DeSerialise(const u8* data, u32 dataLen) { DeSerialiseIt(m_value, data); return true; }
    virtual std::string ToString() const { return(GetValueAsString(false)); }

    virtual std::vector<s32> GetValueS32Array() const { return m_value; }

    virtual std::string GetValueAsString(bool longFormat) const;
    virtual bool IsValueEqual(const MibAttributeValue& rhs) const;

private:
    std::vector<s32> m_value;
};

/**
 * Interface for visiting all the values of a MibAttributeValues object.
 */
class MibAttributeValuesVisitor
{
public:
    virtual ~MibAttributeValuesVisitor() {};

    virtual void VisitMibAttributeValue(MibAttributeId id, const MibAttributeValue& mibAttributeValue) = 0;
};

/**
 * Class for aggregating and serialising a set of MIB attributes.
 */
class MibAttributeValues : public threeway::Serialisable
{
public:
    typedef std::map<MibAttributeId, boost::shared_ptr<MibAttributeValue> > MibAttributeValuesById;

    /**
     * Default constructor.
     */
    MibAttributeValues();

    /**
     * Destructor.
     */
    ~MibAttributeValues();

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_ATTRIBUTE_VALUES; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Add or overwrite an attribute value.
     *
     * \id      MIB attribute ID.
     * \value   Attribute value (contains type+value).
     */
    void AddAttribute(MibAttributeId id, boost::shared_ptr<MibAttributeValue> value);

    /**
     * Add or overwrite a U32 attribute value.
     *
     * \id      MIB attribute ID.
     * \value   Attribute value.
     */
    void AddAttribute(MibAttributeId id, u32 value);

    /**
     * Add or overwrite a U32ARRAY attribute value.
     *
     * \id      MIB attribute ID.
     * \value   Attribute value.
     */
    void AddAttribute(MibAttributeId id, vector<u32> value);

    /**
     * Add or overwrite a S32 attribute value.
     *
     * \id      MIB attribute ID.
     * \value   Attribute value.
     */
    void AddAttribute(MibAttributeId id, s32 value);

    /**
     * Add or overwrite a S32ARRAY attribute value.
     *
     * \id      MIB attribute ID.
     * \value   Attribute value.
     */
    void AddAttribute(MibAttributeId id, vector<s32> value);

    /**
     * Add or overwrite a string attribute value.
     *
     * \id      MIB attribute ID.
     * \value   Attribute value.
     */
    void AddAttribute(MibAttributeId id, const std::string& value);

    /**
     * Add or overwrite a string array attribute value.
     *
     * \id      MIB attribute ID.
     * \value   Attribute value.
     */
    void AddAttribute(MibAttributeId id, const std::vector<std::string>& value);

    /**
     * Add or overwrite a string attribute value.
     *
     * \id      MIB attribute ID.
     * \value   Attribute value.
     */
    void AddAttribute(MibAttributeId id, const char * value);

    /**
     * Add or overwrite a boolean attribute value.
     *
     * \id      MIB attribute ID.
     * \value   Attribute value.
     */
    void AddAttribute(MibAttributeId id, bool value);

    /**
     * Add or overwrite a set of attribute values, and creates lists of any changed values in
     * the process (to be used by MibAttributesUpdated method).
     *
     * \mibAttributeValues Attribute values to add/overwrite.
     * \oldValues          Subset of mibAttributeValues - Lists only the attributes that have changed, together with the pre-change values.
     * \newValues          Subset of mibAttributeValues - Lists only the attributes that have either been added or changed, together with the updated values.
     */
    void AddAttributes(const MibAttributeValues& mibAttributeValues, MibAttributeValues &oldValues, MibAttributeValues &newValues);

    /**
     * Remove an attribute from the list (if present).
     */
    void RemoveAttribute(MibAttributeId id);

    /**
     * "Visit" the attribute values.
     */
    void AcceptVisitor(MibAttributeValuesVisitor& visitor) const;

    /**
     * Get a const ref to the attribute values.  Bit mucky but visitor can
     * get clunky when we need to visit for different purposes from same class.
     */
    const MibAttributeValuesById& GetAttributeValues() const { return m_attributes; };

    /**
     * Get a specific value by ID.
     */
    boost::shared_ptr<MibAttributeValue> GetAttributeValue(MibAttributeId id) const;

    /**
     * Get attribute value.  Will assert if not present or wrong type.
     */
    void GetAttributeValue(MibAttributeId id, bool& value) const;
    void GetAttributeValue(MibAttributeId id, u32& value) const;
    void GetAttributeValue(MibAttributeId id, vector<u32>& value) const;
    void GetAttributeValue(MibAttributeId id, u16& value) const;
    void GetAttributeValue(MibAttributeId id, u8& value) const;
    void GetAttributeValue(MibAttributeId id, s32& value) const;
    void GetAttributeValue(MibAttributeId id, vector<s32>& value) const;
    void GetAttributeValue(MibAttributeId id, s16& value) const;
    void GetAttributeValue(MibAttributeId id, std::string& value) const;
    void GetAttributeValue(MibAttributeId id, std::vector<std::string>& value) const;

    /**
     * Get just the attribute IDs.
     */
    MibAttributeIds GetAttributeIds() const;

    /**
     * Find out how many attributes are present.
     */
    u32 GetAttributeCount() const { return m_attributes.size(); };

    /**
     * Check if attribute is present.
     */
    bool IsAttributePresent(MibAttributeId id) const;

    /**
     * Find out how many attributes are in the list
     */
    int GetAttributeCount() { return m_attributes.size(); }

private:
    /**
     * Map of attributes by ID.
     */
    MibAttributeValuesById m_attributes;

};

#endif
