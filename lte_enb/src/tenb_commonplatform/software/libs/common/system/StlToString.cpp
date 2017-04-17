///////////////////////////////////////////////////////////////////////////////
//
// StlToString.cpp
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
#include <vector>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "StlToString.h"

using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

typedef vector<u32> U32Vector;
typedef vector<u16> U16Vector;
typedef vector<u8> U8Vector;
typedef vector<s32> S32Vector;
typedef vector<s16> S16Vector;
typedef vector<s8> S8Vector;
typedef vector<string> StringVector;

void StlToString::VectorToStream(const vector<u32>& vector, ostream& stream)
{
    ENTER();
    
    U32Vector::const_iterator iter;
    iter = vector.begin();
    stream << "[u32: ";
    while(iter != vector.end())
    {
        stream << *iter;
        ++iter;
        if(iter != vector.end())
        {
            stream << " ";
        }
    }
    stream << "]";
    
    EXIT();
}

void StlToString::VectorToStream(const vector<u16>& vector, ostream& stream)
{
    ENTER();
    
    U16Vector::const_iterator iter = vector.begin();
    stream << "[u16: ";
    while(iter != vector.end())
    {
        stream << (u32)(*iter);
        ++iter;
        if(iter != vector.end())
        {
            stream << " ";
        }
    }
    stream << "]";
    
    EXIT();
}

void StlToString::VectorToStream(const vector<u8>& vector, ostream& stream)
{
    ENTER();
    
    U8Vector::const_iterator iter = vector.begin();
    stream << "[u8: ";
    while(iter != vector.end())
    {
        stream << (u32)(*iter);
        ++iter;
        if(iter != vector.end())
        {
            stream << " ";
        }
    }
    stream << "]";
    
    EXIT();
}

void StlToString::VectorToStream(const vector<s32>& vector, ostream& stream)
{
    ENTER();
    
    S32Vector::const_iterator iter = vector.begin();
    stream << "[s32: ";
    while(iter != vector.end())
    {
        stream << *iter;
        ++iter;
        if(iter != vector.end())
        {
            stream << " ";
        }
    }
    stream << "]";
    
    EXIT();
}

void StlToString::VectorToStream(const vector<s16>& vector, ostream& stream)
{
    ENTER();
    
    S16Vector::const_iterator iter = vector.begin();
    stream << "[s16: ";
    while(iter != vector.end())
    {
        stream << (s32)(*iter);
        ++iter;
        if(iter != vector.end())
        {
            stream << " ";
        }
    }
    stream << "]";
    
    EXIT();
}

void StlToString::VectorToStream(const vector<s8>& vector, ostream& stream)
{
    ENTER();
    
    // Iterate through once to get numbers.
    S8Vector::const_iterator iter = vector.begin();
    stream << "[s8: ";
    while(iter != vector.end())
    {
        stream << (s32)(*iter);
        ++iter;
        if(iter != vector.end())
        {
            stream << " ";
        }
    }
    
    // Do it again to get ascii string.
    stream << " \"";
    iter = vector.begin();
    while(iter != vector.end())
    {
        if(isprint(*iter))
        {
            stream << (char)(*iter);
        }
        else
        {
            stream << ".";
        }
        ++iter;
    }
    stream << "\"]";
    
    EXIT();
}

void StlToString::VectorToStream(const vector<string>& vector, ostream& stream)
{
    ENTER();
    
    StringVector::const_iterator iter = vector.begin();
    stream << "[string: ";
    while(iter != vector.end())
    {
        stream << *iter;
        ++iter;
        if(iter != vector.end())
        {
            stream << " ";
        }
    }
    stream << "]";
    
    EXIT();
}

template <class T>
string StlToString::VectorToString(const vector<T>& vector)
{
    ENTER();
    
    ostringstream stream;
    
    VectorToStream(vector, stream);
    
    RETURN(stream.str());
}

}
