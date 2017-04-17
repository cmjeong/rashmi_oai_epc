///////////////////////////////////////////////////////////////////////////////
//
// SmGgsnInterface.h
//
// Interface definitions for function call based communications between
// SM layer and GGSN.  Note, these functions could implement messaging
// so that each layer can run in a different thread/app.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SmGgsnInterface_h_
#define __SmGgsnInterface_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <comms/IPv4Address.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

enum GgsnPsBearerType
{
    GGSN_PS_BEARER_CHANNEL_1 = 0,
};

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

//
// Downlink GGSN->SM
//
class GgsnToSmInterface
{
public:
    // TODO - no acknowledgements required at the moment.  SM to GGSN messages are fire and forget.
    //virtual void GgsnToSmCreatePDPContextRsp() = 0;
};


//
// Uplink SM->GGSN
//
class SmToGgsnInterface
{
public:
    virtual void SmToGgsnCreatePDPContextInd(const threeway::IPv4Address &ueIpAddress, GgsnPsBearerType bearerType, u32 psDataStreamId) = 0;
    virtual void SmToGgsnDeletePDPContextInd(const threeway::IPv4Address &ueIpAddress) = 0;

    /**
     * Make destructor virtual to remove compiler warnings.
     */
    virtual ~SmToGgsnInterface () {}
};

#endif
