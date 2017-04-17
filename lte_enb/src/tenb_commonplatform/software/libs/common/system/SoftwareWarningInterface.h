///////////////////////////////////////////////////////////////////////////////
//
// SoftwareWarningInterface.h
//
// Interface to log a Software Warning Alarm.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SoftwareWarningInterface_h_
#define __SoftwareWarningInterface_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class SoftwareWarningInterface
{
public:
    SoftwareWarningInterface(){};
    virtual ~SoftwareWarningInterface(){};

    virtual void SoftwareWarning( const char * warning ) const = 0;
};


}

#endif

#endif
