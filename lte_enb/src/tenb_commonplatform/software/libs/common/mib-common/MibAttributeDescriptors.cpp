///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeDescriptors.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <map>
#include <cstring> // strcmp
#include <algorithm>

#include <system/Trace.h>
#include <MibAttributes.h>
#include <MibManagedObjects.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributeDescriptors.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

const char * getMibAttributeTypeName(MibAttributeType type)
{
    ENTER();

    switch(type)
    {
    case MIB_ATTRIBUTE_TYPE_U32: RETURN("u32"); break;
    case MIB_ATTRIBUTE_TYPE_U32ARRAY: RETURN("u32[]"); break;
    case MIB_ATTRIBUTE_TYPE_S32: RETURN("s32"); break;
    case MIB_ATTRIBUTE_TYPE_S32ARRAY: RETURN("s32[]"); break;
    case MIB_ATTRIBUTE_TYPE_STRING: RETURN("string"); break;
    case MIB_ATTRIBUTE_TYPE_STRINGARRAY: RETURN("string[]"); break;
    case MIB_ATTRIBUTE_TYPE_ENUM: RETURN("enum"); break;
    case MIB_ATTRIBUTE_TYPE_ENUMARRAY: RETURN("enum[]"); break;
    }

    RSYS_ASSERT(false);

    RETURN(NULL);
}

const char * getMibAttributeAccessClassName(MibAttributeAccessClass accessClass)
{
    ENTER();

    switch(accessClass)
    {
    case MIB_ACCESS_READ_WRITE: RETURN("R/W"); break;
    case MIB_ACCESS_READ_ONLY: RETURN("R/O"); break;
    case MIB_ACCESS_WRITE_ONCE: RETURN("W/O"); break;
    }

    RSYS_ASSERT(false);

    RETURN(NULL);
}

const char * getMibAttributeStorageClassName(MibAttributeStorageClass storageClass)
{
    ENTER();

    switch(storageClass)
    {
    case MIB_STORAGE_VOLATILE: RETURN("Volatile"); break;
    case MIB_STORAGE_NON_VOLATILE: RETURN("NonVolatile"); break;
    }

    RSYS_ASSERT(false);

    RETURN(NULL);
}


template <class T>
bool MibAttributeDescriptorComp(const T & lhs,
                                const T & rhs)
{
    return(lhs.mibAttributeId < rhs.mibAttributeId);
}

const MibAttributeU32Descriptor* getMibAttributeU32Descriptor(MibAttributeId id)
{
    ENTER();

    RSYS_ASSERT_PRINTF(id < NUM_MIB_ATTR_IDS, "id=%"PRIu32" (0x%08X)", (u32)id, (u32)id);

    // Check that this attributeID is of the correct type
    RSYS_ASSERT_PRINTF((mibAttributeCommonDescriptors[id].mibAttributeType == MIB_ATTRIBUTE_TYPE_U32)
                        || (mibAttributeCommonDescriptors[id].mibAttributeType == MIB_ATTRIBUTE_TYPE_ENUM),
                       "Expected U32 or ENUM but %s is of type %"PRIu32,
                       getMibAttributeName(id), (u32)(mibAttributeCommonDescriptors[id].mibAttributeType));

    MibAttributeU32Descriptor searchKey;
    searchKey.mibAttributeId = id;
    const MibAttributeU32Descriptor* foundKey =
        std::lower_bound(mibAttributesU32Descriptors,
                         mibAttributesU32Descriptors + mibAttributesU32DescriptorsNum,
                         searchKey,
                         MibAttributeDescriptorComp<MibAttributeU32Descriptor>);
    RSYS_ASSERT_PRINTF(foundKey != NULL, "No id found");
    RSYS_ASSERT_PRINTF(id == foundKey->mibAttributeId, "No id found");

    RETURN(foundKey);
}

const MibAttributeU32ArrayDescriptor* getMibAttributeU32ArrayDescriptor(MibAttributeId id)
{
    ENTER();

    RSYS_ASSERT_PRINTF(id < NUM_MIB_ATTR_IDS, "id=%"PRIu32" (0x%08X)", (u32)id, (u32)id);

    // Check that this attributeID is of the correct type
    RSYS_ASSERT_PRINTF(mibAttributeCommonDescriptors[id].mibAttributeType == MIB_ATTRIBUTE_TYPE_U32ARRAY,
                       "Expected U32ARRAY but %s is of type %"PRIu32,
                       getMibAttributeName(id), (u32)(mibAttributeCommonDescriptors[id].mibAttributeType));

    MibAttributeU32ArrayDescriptor searchKey;
    searchKey.mibAttributeId = id;
    const MibAttributeU32ArrayDescriptor* foundKey =
        std::lower_bound(mibAttributesU32ArrayDescriptors,
                         mibAttributesU32ArrayDescriptors + mibAttributesU32ArrayDescriptorsNum,
                         searchKey,
                         MibAttributeDescriptorComp<MibAttributeU32ArrayDescriptor>);
    RSYS_ASSERT_PRINTF(foundKey != NULL, "No id found");
    RSYS_ASSERT_PRINTF(id == foundKey->mibAttributeId, "No id found");

    RETURN(foundKey);
}

const MibAttributeS32Descriptor* getMibAttributeS32Descriptor(MibAttributeId id)
{
    ENTER();

    RSYS_ASSERT_PRINTF(id < NUM_MIB_ATTR_IDS, "id=%"PRIu32" (0x%08X)", (u32)id, (u32)id);

    // Check that this attributeID is of the correct type
    RSYS_ASSERT_PRINTF(mibAttributeCommonDescriptors[id].mibAttributeType == MIB_ATTRIBUTE_TYPE_S32,
                       "Expected S32 but %s is of type %"PRIu32,
                       getMibAttributeName(id), (u32)(mibAttributeCommonDescriptors[id].mibAttributeType));

    MibAttributeS32Descriptor searchKey;
    searchKey.mibAttributeId = id;
    const MibAttributeS32Descriptor* foundKey =
        std::lower_bound(mibAttributesS32Descriptors,
                         mibAttributesS32Descriptors + mibAttributesS32DescriptorsNum,
                         searchKey,
                         MibAttributeDescriptorComp<MibAttributeS32Descriptor>);
    RSYS_ASSERT_PRINTF(foundKey != NULL, "No id found");
    RSYS_ASSERT_PRINTF(id == foundKey->mibAttributeId, "No id found");

    RETURN(foundKey);
}

const MibAttributeS32ArrayDescriptor* getMibAttributeS32ArrayDescriptor(MibAttributeId id)
{
    ENTER();

    RSYS_ASSERT_PRINTF(id < NUM_MIB_ATTR_IDS, "id=%"PRIu32" (0x%08X)", (u32)id, (u32)id);

    // Check that this attributeID is of the correct type
    RSYS_ASSERT_PRINTF(mibAttributeCommonDescriptors[id].mibAttributeType == MIB_ATTRIBUTE_TYPE_S32ARRAY,
                       "Expected S32ARRAY but %s is of type %"PRIu32,
                       getMibAttributeName(id), (u32)(mibAttributeCommonDescriptors[id].mibAttributeType));

    MibAttributeS32ArrayDescriptor searchKey;
    searchKey.mibAttributeId = id;
    const MibAttributeS32ArrayDescriptor* foundKey =
        std::lower_bound(mibAttributesS32ArrayDescriptors,
                         mibAttributesS32ArrayDescriptors + mibAttributesS32ArrayDescriptorsNum,
                         searchKey,
                         MibAttributeDescriptorComp<MibAttributeS32ArrayDescriptor>);
    RSYS_ASSERT_PRINTF(foundKey != NULL, "No id found");
    RSYS_ASSERT_PRINTF(id == foundKey->mibAttributeId, "No id found");

    RETURN(foundKey);
}

const MibAttributeStringDescriptor* getMibAttributeStringDescriptor(MibAttributeId id)
{
    ENTER();

    RSYS_ASSERT_PRINTF(id < NUM_MIB_ATTR_IDS, "id=%"PRIu32" (0x%08X)", (u32)id, (u32)id);

    // Check that this attributeID is of the correct type
    RSYS_ASSERT_PRINTF(mibAttributeCommonDescriptors[id].mibAttributeType == MIB_ATTRIBUTE_TYPE_STRING,
                       "Expected STRING but %s is of type %"PRIu32,
                       getMibAttributeName(id), (u32)(mibAttributeCommonDescriptors[id].mibAttributeType));

    MibAttributeStringDescriptor searchKey;
    searchKey.mibAttributeId = id;
    const MibAttributeStringDescriptor* foundKey =
        std::lower_bound(mibAttributesStringDescriptors,
                         mibAttributesStringDescriptors + mibAttributesStringDescriptorsNum,
                         searchKey,
                         MibAttributeDescriptorComp<MibAttributeStringDescriptor>);
    RSYS_ASSERT_PRINTF(foundKey != NULL, "No id found");
    RSYS_ASSERT_PRINTF(id == foundKey->mibAttributeId, "No id found");

    RETURN(foundKey);
}

const MibAttributeStringArrayDescriptor* getMibAttributeStringArrayDescriptor(MibAttributeId id)
{
    ENTER();

    RSYS_ASSERT_PRINTF(id < NUM_MIB_ATTR_IDS, "id=%"PRIu32" (0x%08X)", (u32)id, (u32)id);

    // Check that this attributeID is of the correct type
    RSYS_ASSERT_PRINTF(mibAttributeCommonDescriptors[id].mibAttributeType == MIB_ATTRIBUTE_TYPE_STRINGARRAY,
                       "Expected STRINGARRAY but %s is of type %"PRIu32,
                       getMibAttributeName(id), (u32)(mibAttributeCommonDescriptors[id].mibAttributeType));

    MibAttributeStringArrayDescriptor searchKey;
    searchKey.mibAttributeId = id;
    const MibAttributeStringArrayDescriptor* foundKey =
        std::lower_bound(mibAttributesStringArrayDescriptors,
                         mibAttributesStringArrayDescriptors + mibAttributesStringArrayDescriptorsNum,
                         searchKey,
                         MibAttributeDescriptorComp<MibAttributeStringArrayDescriptor>);
    RSYS_ASSERT_PRINTF(foundKey != NULL, "No id found");
    RSYS_ASSERT_PRINTF(id == foundKey->mibAttributeId, "No id found");

    RETURN(foundKey);
}

const MibAttributeCommonDescriptor* getMibAttributeCommonDesc(MibAttributeId id)
{
    ENTER();

    RSYS_ASSERT_PRINTF(id < NUM_MIB_ATTR_IDS, "id=%"PRIu32" (0x%08X)", (u32)id, (u32)id);

    RETURN(&mibAttributeCommonDescriptors[id]);
}

const char * getMibAttributeName(MibAttributeId id)
{
    ENTER();

    RSYS_ASSERT_PRINTF(id < NUM_MIB_ATTR_IDS, "id=%"PRIu32" (0x%08X)", (u32)id, (u32)id);

    RETURN(mibAttributeCommonDescriptors[id].mibAttributeName);
}

MibAttributeType getMibAttributeType(MibAttributeId id)
{
    ENTER();

    RSYS_ASSERT_PRINTF(id < NUM_MIB_ATTR_IDS, "id=%"PRIu32" (0x%08X)", (u32)id, (u32)id);

    RETURN(mibAttributeCommonDescriptors[id].mibAttributeType);
}

const MibManagedObjectDescriptor* getManagedObjectDescriptor(MibObjectClass mibObjectClass)
{
    const MibManagedObjectDescriptor* moDescriptor = 0; // 0 means "unfound"
    for (int i = 0; i < mibManagedObjectDescriptorsNum; ++i)
    {
        if (mibManagedObjectDescriptors[i].mibObjectClass == mibObjectClass)
        {
            moDescriptor = mibManagedObjectDescriptors+i;
            break;
        }
    }

     return moDescriptor;
}
