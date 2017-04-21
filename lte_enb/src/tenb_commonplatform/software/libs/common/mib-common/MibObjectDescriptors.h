///////////////////////////////////////////////////////////////////////////////
//
// MibObjectDescriptors.h
//
// Structures used in autogenerated MIB code.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibObjectDescriptors_h_
#define __MibObjectDescriptors_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <MibObjectClass.h>
#include <mib-common/MibAttributeDescriptors.h>


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef struct MibChildObjectDescriptorTag
{
    const MibObjectClass validChildClass;
    const u32 minInstances;
    const u32 maxInstances;
}MibChildObjectDescriptor;

typedef struct MibManagedObjectDescriptorTag
{
    const char * mibObjectName;
    const MibObjectClass mibObjectClass;
    const MibObjectClass validParentClass;
    const MibChildObjectDescriptor * const validChildClasses;
    const u32 validChildClassesNum;
    const MibObjectAttributeDescriptor * const validAttributeIds;
    const u32 validAttributeIdsNum;
} MibManagedObjectDescriptor;


///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

const MibManagedObjectDescriptor* getManagedObjectDescriptor(MibObjectClass mibObjectClass);

#endif