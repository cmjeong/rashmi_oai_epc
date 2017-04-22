///////////////////////////////////////////////////////////////////////////////
//
// SetLed_v4.h
//
// Implementation of SetLedInterface for 4.0 HW
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SetLed_v4_h_
#define __SetLed_v4_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SetLedInterface.h"


class SetLed_v4 : public SetLedInterface
{
public:

    SetLed_v4() {};

    ~SetLed_v4() {};

    void SetLed(u32, LedColour, LedPattern);

private:

    /* This method ensures that the given led is completely switched off:
     * timers, pattern, colour
     * This allows transictions from a state to another to be clean */
    void ResetLed(string&);

    /* This function access directly the file in the system, rather
     * than using system() call */
    void WriteLed(const char *ledName,
                  const char *colour,
                  const char *file,
                  const char *value);

};

#endif
