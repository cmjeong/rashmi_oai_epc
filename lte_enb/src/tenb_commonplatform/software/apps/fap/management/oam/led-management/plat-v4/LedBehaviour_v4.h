///////////////////////////////////////////////////////////////////////////////
//
// LedBehaviour_v4.h
//
// Implementation of LedBehaviourInterface for 4.0 HW
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LedBehaviour_v4_h_
#define __LedBehaviour_v4_h_

#include "LedBehaviourInterface.h"
#include "LedTypes_v4.h"


class LedBehaviour_v4 : public LedBehaviourInterface
{
public:

    LedBehaviour_v4() {};

    ~LedBehaviour_v4() {};

    void LoadDefaultMap(map<LedEvent, LedMap> &);
};

#endif
