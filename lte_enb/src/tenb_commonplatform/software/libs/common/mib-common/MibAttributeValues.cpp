///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeValues.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iterator>

#include <system/Trace.h>
#include <system/StringUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributeValues.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

shared_ptr<MibAttributeValue> MibAttributeValue::Create(MibAttributeType type, const string& valueAsString)
{
   shared_ptr<MibAttributeValue> value;

   switch (type)
   {
      case MIB_ATTRIBUTE_TYPE_U32:
      case MIB_ATTRIBUTE_TYPE_ENUM:
         {
            if(!valueAsString.empty() && valueAsString.at(0) != '-')
            {
               u32 valueU32 = 0;
               if( StringUtils::ConvertStringToInteger( valueAsString, valueU32 ) )
               {
                  value.reset(new MibAttributeValueU32(valueU32));
               }
            }
         }
         break;

      case MIB_ATTRIBUTE_TYPE_U32ARRAY:
      case MIB_ATTRIBUTE_TYPE_ENUMARRAY:
         {
            std::vector<u32> valueAsVector;
            if( StringUtils::ConvertStringToInteger( valueAsString, valueAsVector ) )
            {
               value.reset(new MibAttributeValueU32Array(valueAsVector));
            }
         }
         break;

      case MIB_ATTRIBUTE_TYPE_S32:
         {
            s32 valueS32 = 0;
            if( StringUtils::ConvertStringToInteger( valueAsString, valueS32 ) )
            {
               value.reset(new MibAttributeValueS32(valueS32));
            }
         }
         break;

      case MIB_ATTRIBUTE_TYPE_S32ARRAY:
         {
            std::vector<s32> valueAsVector;
            if( StringUtils::ConvertStringToInteger( valueAsString, valueAsVector ) )
            {
               value.reset(new MibAttributeValueS32Array(valueAsVector));
            }
         }
         break;

      case MIB_ATTRIBUTE_TYPE_STRING:
         value.reset(new MibAttributeValueString(valueAsString));
         break;

      case MIB_ATTRIBUTE_TYPE_STRINGARRAY:
         {
            // String arrays are escaped
            // e.g. "string,1", "string\"2", "string\\\\\"3", "atlast\nstring4"
            // TODO: Implement CSV unravelling here.
            std::vector<std::string> valueAsStringArray;
            stringstream conversionStream;
            std::string valueAsStringArrayItem;
            std::string previousValue;

            conversionStream << valueAsString;

            while (conversionStream.good())
            {
               // TODO: Verify this
               // identify word
               // unescape the word
               // add word to vector
               std::getline(conversionStream, valueAsStringArrayItem, ',');
               // Check that the last 2 characters are:-
               //       last == '"'
               //       penultimate != '\'
               std::string::size_type stringLength = valueAsStringArrayItem.size();
               if (stringLength >= 2)
               {
                  if ((valueAsStringArrayItem[stringLength - 1] == '"') && (valueAsStringArrayItem[stringLength -2] != '\\'))
                  {
                     valueAsStringArray.push_back(StringUtils::UnEscapeString(previousValue + valueAsStringArrayItem));
                     previousValue.clear();
                  }
                  else
                  {
                     previousValue.append(valueAsStringArrayItem);
                     previousValue.push_back(',');
                  }
               }
               else
               {
                  previousValue.append(valueAsStringArrayItem);
                  previousValue.push_back(',');
               }
            }
            value.reset(new MibAttributeValueStringArray(valueAsStringArray));
         }
         break;
   }
   RETURN(value);
}

string MibAttributeValueU32::GetValueAsString(bool longFormat) const
{
    ostringstream stream;
    if(longFormat)
    {
        stream << dec << m_value << " (0x" << hex << m_value << ")";
    }
    else
    {
        stream << dec << m_value;
    }

    return stream.str();
}

string MibAttributeValueS32::GetValueAsString(bool longFormat) const
{
    ostringstream stream;
    if(longFormat)
    {
        stream << dec << m_value << " (0x" << hex << m_value << ")";
    }
    else
    {
        stream << dec << m_value;
    }

    return stream.str();
}

std::string MibAttributeValueStringArray::GetValueAsString(bool longFormat) const
{
    std::ostringstream stream;

    //i.e. string"1 -> string\"1
    //     string\"2 -> string\\\"2
    //     string<newline> -> string\n
	if (not(m_value.empty()))
	{
	    for (std::vector<std::string>::const_iterator valueIter = m_value.begin();
	         not(valueIter == (m_value.begin() + (m_value.size() -1)));
	         ++valueIter)
	    {
	        stream << StringUtils::EscapeString(*valueIter) << ',';
	    }
	    stream << StringUtils::EscapeString(m_value.back());
	}

    return(stream.str());
}

std::string MibAttributeValueU32Array::GetValueAsString(bool longFormat) const
{
    std::ostringstream stream;

    // 1, 2, 3 etc...
    if (not(m_value.empty()))
    {
        for (std::vector<u32>::const_iterator valueIter = m_value.begin();
             valueIter != (m_value.begin() + (m_value.size() -1));
             ++valueIter)
        {
            stream << *valueIter << ',';
        }
        stream << m_value.back();
    }

    return(stream.str());
}

std::string MibAttributeValueS32Array::GetValueAsString(bool longFormat) const
{
    std::ostringstream stream;

    // 1, 2, 3 etc...
    if (not(m_value.empty()))
    {
        for (std::vector<s32>::const_iterator valueIter = m_value.begin();
             valueIter != (m_value.begin() + (m_value.size() -1));
             ++valueIter)
        {
            stream << *valueIter << ',';
        }
        stream << m_value.back();
    }

    return(stream.str());
}

bool MibAttributeValueStringArray::IsValueEqual(const MibAttributeValue& rhs) const
{
    ENTER();

    RSYS_ASSERT(rhs.GetType() == MIB_ATTRIBUTE_TYPE_STRINGARRAY);

    const MibAttributeValueStringArray& rhsStringArray = dynamic_cast<const MibAttributeValueStringArray&>(rhs);

    if(rhsStringArray.m_value.size() != m_value.size())
    {
        RETURN(false);
    }

    for (u32 i = 0; i < m_value.size(); i++)
    {
        if(m_value.at(i) != rhsStringArray.m_value.at(i))
        {
            RETURN(false);
        }
    }

    RETURN(true);
}

bool MibAttributeValueU32Array::IsValueEqual(const MibAttributeValue& rhs) const
{
    ENTER();

    RSYS_ASSERT(rhs.GetType() == MIB_ATTRIBUTE_TYPE_U32ARRAY);

    const MibAttributeValueU32Array& rhsU32Array = dynamic_cast<const MibAttributeValueU32Array&>(rhs);

    if(rhsU32Array.m_value.size() != m_value.size())
    {
        RETURN(false);
    }

    for (u32 i = 0; i < m_value.size(); i++)
    {
        if(m_value.at(i) != rhsU32Array.m_value.at(i))
        {
            RETURN(false);
        }
    }

    RETURN(true);
}

bool MibAttributeValueS32Array::IsValueEqual(const MibAttributeValue& rhs) const
{
    ENTER();

    RSYS_ASSERT(rhs.GetType() == MIB_ATTRIBUTE_TYPE_S32ARRAY);

    const MibAttributeValueS32Array& rhsS32Array = dynamic_cast<const MibAttributeValueS32Array&>(rhs);

    if(rhsS32Array.m_value.size() != m_value.size())
    {
        RETURN(false);
    }

    for (u32 i = 0; i < m_value.size(); i++)
    {
        if(m_value.at(i) != rhsS32Array.m_value.at(i))
        {
            RETURN(false);
        }
    }

    RETURN(true);
}

MibAttributeValues::MibAttributeValues()
{
    ENTER();

    EXIT();
}

MibAttributeValues::~MibAttributeValues()
{
    ENTER();

    EXIT();
}

s32 MibAttributeValues::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    u8* const dataStart = data;

    // Write out number of attributes.
    u32 numValues = m_attributes.size();
    SerialiseIt(numValues, data);

    // Write out attribute id/value pairs.
    for(MibAttributeValuesById::const_iterator iter = m_attributes.begin();
        iter != m_attributes.end();
        ++iter)
    {
        //TRACE_PRINTF("id=%"PRIu32", value=%s", static_cast<u32>(iter->first), iter->second->ToString().c_str());
        SerialiseIt(static_cast<u32>(iter->first), data);
        RSYS_ASSERT(iter->second != NULL);
        data += iter->second->Serialise(data, dataMaxBytes - (data - dataStart));
    }

    RETURN(data - dataStart);
}

bool MibAttributeValues::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    const u8* const dataStart = data;

    u32 numValues;
    DeSerialiseIt(numValues, data);

    for(u32 i = 0; i < numValues; i++)
    {
        u32 idAsU32;
        DeSerialiseIt(idAsU32, data);
        MibAttributeId id = static_cast<MibAttributeId>(idAsU32);

        // Get type from ID so we construct correct MibAttributeValue*
        shared_ptr<MibAttributeValue> mibAttributeValue;
        switch(getMibAttributeType(id))
        {
        case MIB_ATTRIBUTE_TYPE_U32:
        case MIB_ATTRIBUTE_TYPE_ENUM:
        {
            u32 valU32;
            DeSerialiseIt(valU32, data);
            mibAttributeValue.reset(new MibAttributeValueU32(valU32));
        }
        break;

        case MIB_ATTRIBUTE_TYPE_U32ARRAY:
        case MIB_ATTRIBUTE_TYPE_ENUMARRAY:
        {
            std::vector<u32> valU32Array;
            DeSerialiseIt(valU32Array, data );
            mibAttributeValue.reset(new MibAttributeValueU32Array(valU32Array));
        }
        break;

        case MIB_ATTRIBUTE_TYPE_S32ARRAY:
        {
            std::vector<s32> valS32Array;
            DeSerialiseIt(valS32Array, data );
            mibAttributeValue.reset(new MibAttributeValueS32Array(valS32Array));
        }
        break;

        case MIB_ATTRIBUTE_TYPE_S32:
        {
            s32 valS32;
            DeSerialiseIt(valS32, data);
            mibAttributeValue.reset(new MibAttributeValueS32(valS32));
        }
        break;

        case MIB_ATTRIBUTE_TYPE_STRING:
        {
            string valString;
            DeSerialiseIt(valString, data, dataLen - (data - dataStart));
            mibAttributeValue.reset(new MibAttributeValueString(valString));
        }
        break;

        case MIB_ATTRIBUTE_TYPE_STRINGARRAY:
        {
            std::vector<std::string> valStringArray;
            DeSerialiseIt(valStringArray, data, dataLen - (data - dataStart));
            mibAttributeValue.reset(new MibAttributeValueStringArray(valStringArray));
        }
        break;

        }

        m_attributes[id] = mibAttributeValue;
    }

    RETURN(true);
}

string MibAttributeValues::ToString() const
{
    ostringstream stream;

    MibAttributeValuesById::const_iterator iter = m_attributes.begin();
    while(iter != m_attributes.end())
    {
        // TODO change to use something with more concise output than getMibAttributeName().
        stream << getMibAttributeName(iter->first) << '=' << iter->second->ToString() << ' ';

        ++iter;
    }

    return stream.str();
}

void MibAttributeValues::AddAttribute(MibAttributeId id, shared_ptr<MibAttributeValue> value)
{
    ENTER();

    m_attributes[id] = value;

    EXIT();
}

void MibAttributeValues::AddAttribute(MibAttributeId id, u32 value)
{
    ENTER();

    shared_ptr<MibAttributeValue> mibAttributeValue(new MibAttributeValueU32(value));
    AddAttribute(id, mibAttributeValue);

    EXIT();
}

void MibAttributeValues::AddAttribute(MibAttributeId id, vector<u32> value)
{
    ENTER();

    shared_ptr<MibAttributeValue> mibAttributeValue(new MibAttributeValueU32Array(value));
    AddAttribute(id, mibAttributeValue);

    EXIT();
}

void MibAttributeValues::AddAttribute(MibAttributeId id, s32 value)
{
    ENTER();

    shared_ptr<MibAttributeValue> mibAttributeValue(new MibAttributeValueS32(value));
    AddAttribute(id, mibAttributeValue);

    EXIT();
}

void MibAttributeValues::AddAttribute(MibAttributeId id, vector<s32> value)
{
    ENTER();

    shared_ptr<MibAttributeValue> mibAttributeValue(new MibAttributeValueS32Array(value));
    AddAttribute(id, mibAttributeValue);

    EXIT();
}

void MibAttributeValues::AddAttribute(MibAttributeId id, const string& value)
{
    ENTER();

    shared_ptr<MibAttributeValue> mibAttributeValue(new MibAttributeValueString(value));
    AddAttribute(id, mibAttributeValue);

    EXIT();
}

void MibAttributeValues::AddAttribute(MibAttributeId id, const std::vector<std::string>& value)
{
    ENTER();

    shared_ptr<MibAttributeValue> mibAttributeValue(new MibAttributeValueStringArray(value));
    AddAttribute(id, mibAttributeValue);

    EXIT();
}

void MibAttributeValues::AddAttribute(MibAttributeId id, const char * value)
{
    ENTER();

    RSYS_ASSERT_PRINTF(value != NULL, "%s", getMibAttributeName(id));

    shared_ptr<MibAttributeValue> mibAttributeValue(new MibAttributeValueString(value));
    AddAttribute(id, mibAttributeValue);

    EXIT();
}

void MibAttributeValues::AddAttribute(MibAttributeId id, bool value)
{
    ENTER();

    shared_ptr<MibAttributeValue> mibAttributeValue(new MibAttributeValueU32(value ? 1 : 0));
    AddAttribute(id, mibAttributeValue);

    EXIT();
}

void MibAttributeValues::AddAttributes(const MibAttributeValues& mibAttributeValues, MibAttributeValues &oldValues, MibAttributeValues &newValues)
{
    ENTER();

    for(MibAttributeValuesById::const_iterator iter = mibAttributeValues.GetAttributeValues().begin();
        iter != mibAttributeValues.GetAttributeValues().end();
        ++iter)
    {
        RSYS_ASSERT(iter->second != NULL);
        shared_ptr<MibAttributeValue> updatedValue  = iter->second;

        if(IsAttributePresent(iter->first))
        {
            shared_ptr<MibAttributeValue> originalValue = GetAttributeValue(iter->first);

            if((originalValue != NULL) && (not(updatedValue->IsValueEqual(*originalValue))))
            {
                // Update the change table.
                oldValues.AddAttribute(iter->first, originalValue);
                newValues.AddAttribute(iter->first, updatedValue);
            }
        }
        else
        {
        	// Value is added so just update the new values table to show this.
            newValues.AddAttribute(iter->first, updatedValue);
        }
        m_attributes[iter->first] = updatedValue;
    }

    EXIT();
}

void MibAttributeValues::RemoveAttribute(MibAttributeId id)
{
    ENTER();

    // This is safe whether id already exists in the map or not.
    m_attributes.erase(id);

    EXIT();
}

void MibAttributeValues::AcceptVisitor(MibAttributeValuesVisitor& visitor) const
{
    ENTER();

    MibAttributeValuesById::const_iterator iter = m_attributes.begin();
    while(iter != m_attributes.end())
    {
        visitor.VisitMibAttributeValue(iter->first, *(iter->second));
        ++iter;
    }

    EXIT();
}

void MibAttributeValues::GetAttributeValue(MibAttributeId id, bool& value) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    value = m_attributes.at(id)->GetValueU32() == 0 ? false : true;

    EXIT();
}

void MibAttributeValues::GetAttributeValue(MibAttributeId id, u32& value) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    value = m_attributes.at(id)->GetValueU32();

    EXIT();
}

void MibAttributeValues::GetAttributeValue(MibAttributeId id, u16& value) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    value = static_cast<u16>(m_attributes.at(id)->GetValueU32());

    EXIT();
}

void MibAttributeValues::GetAttributeValue(MibAttributeId id, u8& value) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    value = static_cast<u8>(m_attributes.at(id)->GetValueU32());

    EXIT();
}

void MibAttributeValues::GetAttributeValue(MibAttributeId id, vector<u32>& value) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    value = m_attributes.at(id)->GetValueU32Array();

    EXIT();
}

void MibAttributeValues::GetAttributeValue(MibAttributeId id, s32& value) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    value = m_attributes.at(id)->GetValueS32();

    EXIT();
}

void MibAttributeValues::GetAttributeValue(MibAttributeId id, s16& value) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    value = static_cast<s16>(m_attributes.at(id)->GetValueS32());

    EXIT();
}

void MibAttributeValues::GetAttributeValue(MibAttributeId id, vector<s32>& value) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    value = m_attributes.at(id)->GetValueS32Array();

    EXIT();
}

void MibAttributeValues::GetAttributeValue(MibAttributeId id, string& value) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    value = m_attributes.at(id)->GetValueString();

    EXIT();
}

void MibAttributeValues::GetAttributeValue(MibAttributeId id, std::vector<std::string>& value) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    value = m_attributes.at(id)->GetValueStringArray();

    EXIT();
}

shared_ptr<MibAttributeValue> MibAttributeValues::GetAttributeValue(MibAttributeId id) const
{
    ENTER();

    RSYS_ASSERT_PRINTF(IsAttributePresent(id), "%s not present", getMibAttributeName(id));

    RETURN(m_attributes.at(id));
}

MibAttributeIds MibAttributeValues::GetAttributeIds() const
{
    ENTER();

    MibAttributeIds ids;
    for(MibAttributeValuesById::const_iterator iter = m_attributes.begin();
        iter != m_attributes.end();
        ++iter)
    {
        ids.insert(iter->first);
    }

    RETURN(ids);
}

bool MibAttributeValues::IsAttributePresent(MibAttributeId id) const
{
    ENTER();

    RETURN(m_attributes.find(id) != m_attributes.end());
}
