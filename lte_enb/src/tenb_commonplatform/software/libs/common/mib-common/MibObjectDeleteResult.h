///////////////////////////////////////////////////////////////////////////////
//
// MibObjectDeleteResult.h
//
// Result code for an Object deletion request
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#if (!defined(__MibObjectDeleteResult_h_) || defined(ENUM_GENERATE_STRINGS) || defined(ENUM_GENERATE_TABLE))

#if (!defined(ENUM_GENERATE_STRINGS) && !defined(ENUM_GENERATE_TABLE))
    #define __MibObjectDeleteResult_h_
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/EnumToString.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

ENUM_START(MibObjectDeleteResult)
{
    ENUM_ELEMENT_VALUE_STRING(MIB_OBJ_DEL_SUCCESS,             0, "MibObject deletion OK")
    ENUM_ELEMENT_VALUE_STRING(MIB_OBJ_DEL_OBJECT_NOT_FOUND,    1, "MibObject deletion unnecessary: Object not found")
    ENUM_ELEMENT_VALUE_STRING(MIB_OBJ_DEL_OBJECT_HAS_CHILDREN, 2, "MibObject deletion not possible: Object has child objects")

    ENUM_ELEMENT(MIB_OBJ_DEL_INVALID)

}
ENUM_END(MibObjectDeleteResult)

#endif
