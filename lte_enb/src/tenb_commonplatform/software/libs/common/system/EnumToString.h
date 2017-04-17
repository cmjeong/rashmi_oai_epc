///////////////////////////////////////////////////////////////////////////////
//
// EnumToString.h
//
// Macros to allow easy generation of stringified enums.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#undef ENUM_START
#undef ENUM_END
#undef ENUM_ELEMENT
#undef ENUM_ELEMENT_VAL
#undef ENUM_ELEMENT_DUPLICATE
#undef ENUM_ELEMENT_VALUE_STRING

/*
 * If C++ then we need some stream and string stuff for the ...ToStringTable() function.
 */
#ifdef __cplusplus
#include <sstream>
#include <string>
#endif

#ifdef ENUM_GENERATE_STRINGS

    // This bit generates the code to go in the .c/.cpp that corresponds to your
    // enum header file.  It generates the function <EnumName>ToString() that
    // takes an enum value and returns the stringified version of it.

    #define ENUM_START( eNUMnAME ) \
      const char * eNUMnAME##ToString(enum eNUMnAME##Tag someEnum) \
        { \
            switch(someEnum)


    #define ENUM_END( eNUMnAME ) \
            return #eNUMnAME; \
        }

    #define ENUM_ELEMENT( eLEMENT ) \
                case eLEMENT: return #eLEMENT; break;

    #define ENUM_ELEMENT_VAL( eLEMENT, vALUE ) \
                case eLEMENT: return #eLEMENT; break;

    #define ENUM_ELEMENT_DUPLICATE( eLEMENT, vALUE )

    #define ENUM_ELEMENT_VALUE_STRING( eLEMENT, vALUE, sTRING ) \
                case eLEMENT: return sTRING; break;

#elif defined ENUM_GENERATE_THE_FROM_STRING_FUNCTION

    // This bit generates the code to go in the .cpp that corresponds to your
    // enum header file.  It generates the function <EnumName>FromString() that
    // takes a string, and finds the matching enum value and returns a bool
    // indicating success status.
    // Only works from C++ source file.

    #define ENUM_START( eNUMnAME ) \
        bool eNUMnAME##FromString(const std::string & enumString, enum eNUMnAME##Tag & enumVal) \
        { \
             bool matched = false; \
             do

    #define ENUM_END( eNUMnAME ) \
             while(false);\
             return matched; \
        }

    #define ENUM_ELEMENT( eLEMENT ) \
             if((matched = (enumString == #eLEMENT))) {enumVal = eLEMENT; break;}

    #define ENUM_ELEMENT_VAL( eLEMENT, vALUE ) \
             if((matched = (enumString == #eLEMENT))) {enumVal = eLEMENT; break;}

    #define ENUM_ELEMENT_DUPLICATE( eLEMENT, vALUE )

    #define ENUM_ELEMENT_VALUE_STRING( eLEMENT, vALUE, sTRING ) \
             if((matched = (enumString == sTRING))) {enumVal = eLEMENT; break;}


#elif defined ENUM_GENERATE_THE_FROM_C_STRING_FUNCTION

    // This bit generates the code to go in the .c that corresponds to your
    // enum header file.  It generates the function <EnumName>FromString() that
    // takes a char *, and finds the matching enum value and returns a bool
    // indicating success status.

    #define ENUM_START( eNUMnAME ) \
        bool eNUMnAME##FromString(const char *enumString, enum eNUMnAME##Tag *enumVal) \
        { \

    #define ENUM_END( eNUMnAME ) \
             return false; \
        }

    #define ENUM_ELEMENT( eLEMENT ) \
             if(strcmp(enumString, #eLEMENT) == 0) {*enumVal = eLEMENT; return true;}

    #define ENUM_ELEMENT_VAL( eLEMENT, vALUE ) \
             ENUM_ELEMENT( eLEMENT)

    #define ENUM_ELEMENT_DUPLICATE( eLEMENT, vALUE )

    #define ENUM_ELEMENT_VALUE_STRING( eLEMENT, vALUE, sTRING ) \
             if(strcmp(enumString, sTRING) == 0) {*enumVal = eLEMENT; return true;}

#elif defined ENUM_GENERATE_TABLE

    // This bit generates a function that will return a string that contains
    // enum string/value pairs for debug purposes e.g. for when looking in a trace
    // file or wireshark log and you want to know what a particular value is.
    // Only works from C++ source file.

    #define ENUM_START( eNUMnAME ) \
        std::string eNUMnAME##ToStringTable() \
        { \
            std::ostringstream table;

    #define ENUM_END( eNUMnAME ) \
            return table.str(); \
        }

    #define ENUM_ELEMENT( eLEMENT ) \
            table << (unsigned int)eLEMENT << " (0x" << std::hex << (unsigned int)eLEMENT << std::dec << ") = " << #eLEMENT << std::endl;

    #define ENUM_ELEMENT_VAL( eLEMENT, vALUE ) \
            table << (unsigned int)eLEMENT << " (0x" << std::hex << (unsigned int)eLEMENT << std::dec << ") = " << #eLEMENT << std::endl;

    #define ENUM_ELEMENT_DUPLICATE( eLEMENT, vALUE )

    #define ENUM_ELEMENT_VALUE_STRING( eLEMENT, vALUE, sTRING ) \
            table << (unsigned int)eLEMENT << " (0x" << std::hex << (unsigned int)eLEMENT << std::dec << ") = " << sTRING << std::endl;

#else

    // This bit generates the normal enum header file containing an
    // enum typedef and all the elements.

    #define ENUM_START( eNUMnAME ) \
        typedef enum eNUMnAME##Tag

    #ifdef __cplusplus
        #define ENUM_END( eNUMnAME ) \
            eNUMnAME; \
            extern "C" { \
                const char * eNUMnAME##ToString(enum eNUMnAME##Tag someEnum); \
            } \
            bool eNUMnAME##FromString(const std::string & enumString, enum eNUMnAME##Tag & enumVal); \
            std::string eNUMnAME##ToStringTable();
    #else
        #define ENUM_END( eNUMnAME ) \
            eNUMnAME; \
            const char * eNUMnAME##ToString(enum eNUMnAME##Tag someEnum);
    #endif

    #define ENUM_ELEMENT( eLEMENT ) \
        eLEMENT,

    #define ENUM_ELEMENT_VAL( eLEMENT, vALUE ) \
        eLEMENT = vALUE,

    #define ENUM_ELEMENT_DUPLICATE( eLEMENT, vALUE ) \
        eLEMENT = vALUE,

    #define ENUM_ELEMENT_VALUE_STRING( eLEMENT, vALUE, sTRING ) \
        eLEMENT = vALUE,

#endif
