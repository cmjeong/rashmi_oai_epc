///////////////////////////////////////////////////////////////////////////////
//
// LedBehaviourInterface.h
//
// Interface for LedBehaviour
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LedBehaviourInterface_h_
#define __LedBehaviourInterface_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include <messaging/messages/oam/LedInfo.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
/* Following interface exists to future-proof customisation of LED patterns.
 * It allows decoupling from the MIB. */

//TODO: maybe this interface should be combined with SetLedInterface

class LedBehaviourInterface
{
public:
    virtual ~LedBehaviourInterface() {};

    /* This function loads a default Map of event - pattern
     * to be used to activate a specific LED behaviour in response of some event
     * (example: event: location acquired / pattern: location led turn to solid green.
     * Map contains enabled event types and corresponding patterns */
    virtual void LoadDefaultMap(map<LedEvent, LedMap> &) = 0;
};

#endif
