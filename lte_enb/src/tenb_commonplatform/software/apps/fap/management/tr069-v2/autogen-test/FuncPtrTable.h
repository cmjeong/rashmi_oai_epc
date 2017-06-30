/*
 * AUTOMATICALLY GENERATED CODE:
 * DO NOT EDIT !
 */


#ifndef __fap_management_tr069_autogen-test_FuncPtrTableh__
#define __fap_management_tr069_autogen-test_FuncPtrTableh__



#include "MibGroupEnum.h"
#include "MibGroup.h"

namespace tr069
{


typedef ValidationFailureDescriptor (*FuncPtr) (const Tr069AttributeValues&, MibAttributeValues&);

typedef struct
{
   ExtDataModelAttrGroupId   group;
   FuncPtr                   function;
} FuncPtrPair;


static const FuncPtrPair FuncTable[] =
{
   {ScramblingCodeGroup,	ProcessScramblingcodegroup },
   {DCAC_BEARER_TYPE_GRP,	ProcessDcacBearerTypeGrp },
};

}

#endif

