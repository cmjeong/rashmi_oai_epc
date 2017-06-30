///////////////////////////////////////////////////////////////////////////////
//
// StlToString.h
//
// Helper functions for converting STL containers to strings and streams.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __StlToString_h_
#define __StlToString_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <3waytypes.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes / Functions
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

class StlToString
{
public:
    /**
     * Overloaded functions for converting an STL vector to
     * a stream.  Although many are the same implementation it's
     * not done as a template so that we can provide specialist
     * output if required.
     */
    static void VectorToStream(const vector<u32>& vector, ostream& stream);
    static void VectorToStream(const vector<u16>& vector, ostream& stream);
    static void VectorToStream(const vector<u8>& vector, ostream& stream);
    static void VectorToStream(const vector<s32>& vector, ostream& stream);
    static void VectorToStream(const vector<s16>& vector, ostream& stream);
    static void VectorToStream(const vector<s8>& vector, ostream& stream);
    static void VectorToStream(const vector<string>& vector, ostream& stream);

    /**
     * Converting to a string is done as a template as it simply
     * calls the appropriate VectorToStream() function.
     */
    template <class T>
    static string VectorToString(const vector<T>& vector);

};

}

#endif
