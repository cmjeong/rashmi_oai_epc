///////////////////////////////////////////////////////////////////////////////
//
// LedBehaviour_v3_5.h
//
// Implementation of LedBehaviourInterface for 3.5 HW
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LedBehaviour_v3_5_h_
#define __LedBehaviour_v3_5_h_

#include "LedBehaviourInterface.h"
#include "LedTypes_v3_5.h"

class LedBehaviour_v3_5 : public LedBehaviourInterface
{
public:

    LedBehaviour_v3_5() {};

    ~LedBehaviour_v3_5() {};

    void LoadDefaultMap(map<LedEvent, LedMap> &);

};

#endif
