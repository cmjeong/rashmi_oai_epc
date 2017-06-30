///////////////////////////////////////////////////////////////////////////////
//
// NASTrace.h
//
// Debug tracing functionality available in the system.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASTrace_h_
#define __NASTrace_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <system/Trace.h>
#include <system/TimeWrap.h>

//#include "ed_c.h"
#include "BCDAddress.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const u32 TRACE_RANAP_PDU = 0x00001000; // Put this well above the values in Trace.h

static const char UE_L3_TAG []  = "UeL3";
static const char NET_L3_TAG [] = "NetL3";

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

//class NASException;

///////////////////////////////////////////////////////////////////////////////
// Class: NASTrace
// Desc : Manage packing user data into a simple structure and sending it
//        to the specified application.
///////////////////////////////////////////////////////////////////////////////
class NASTrace : public threeway::Trace
{
private:
    // Singleton
    NASTrace();

public:
    // Singleton
    virtual ~NASTrace();
    static NASTrace& GetInstance();

	// Base class methods.
    void TraceFunc (u32 category, u32 level, const char *varName, u32 numberValue) { threeway::Trace::TraceFunc(category, level, varName, numberValue); };
    void TraceFunc (u32 category, u32 level, const char *varName, s32 numberValue) { threeway::Trace::TraceFunc(category, level, varName, numberValue); };
    void TraceFunc (u32 category, u32 level, const char *varName, unsigned long numberValue) { threeway::Trace::TraceFunc(category, level, varName, (u32)numberValue); };
    void TraceFunc (u32 category, u32 level, const char *varName, const char *strValue) { threeway::Trace::TraceFunc(category, level, varName, strValue); };
    void TraceFunc (u32 category, u32 level, const threeway::Exception &e) { threeway::Trace::TraceFunc(category, level, e); };
    void TraceFunc (u32 category, u32 level, const char *varName, const u8 digitArray [], u16 digitCount) { threeway::Trace::TraceFunc(category, level, varName, digitArray, digitCount); };
    void TraceFunc (u32 category, u32 level, const char *varName, const threeway::TimeWrap &timeValue) { threeway::Trace::TraceFunc(category, level, varName, timeValue); };
    // Additional NASTrace methods.
    /*void TraceFunc (u32 category, u32 level, const char *varName, const c_MobileId &subscriberIdentity);
    void TraceFunc (u32 category, u32 level, const char *varName, const c_LocationAreaId &locationArea);
    void TraceFunc (u32 category, u32 level, const char *varName, const c_RoutingAreaIdenti &routingArea);
    void TraceFunc (u32 category, u32 level, const char *varName, const c_TBCDArray &numberDigits);*/
    void TraceFunc (u32 category, u32 level, const char *varName, const BCDAddress &bcdAddress);
    void TraceFunc (u32 category, u32 level, const char *varName, const struct sockaddr sockAddress);

	// Static helper functions for string manipulation.
	static void FormatString (char *stringBuffer, u32 numericValue, u16 lengthOfString);
	static void FormatString (char *stringBuffer, const char *stringValue, u16 lengthOfString);

};

// These macros provided so we don't have to go through all the NAS code and
// change the macro calls.

#define NAS_ENTER ENTER

#define NAS_EXIT EXIT

#define NAS_RETURN(x) RETURN(x)

#define NAS_RETURN_VOID RETURN_VOID

#define NAS_TRACE(x,y) \
    NASTrace::GetInstance().TraceFunc (0, TRACE_INFO, x,y);

#define NAS_TRACE_X(x,y,z) TRACE_X(x,y,z)

#define NAS_TRACE_HEX(x,y) TRACE_HEX(x,y)

#define NAS_MSG(x) TRACE_MSG(x)

#define NAS_EXCEPTION(x) \
    if (g_Trace_enabledLevels & TRACE_EXCEPTIONS) \
        NASTrace::GetInstance().TraceFunc (0, TRACE_EXCEPTIONS, x);

// New macros for NASTrace

#define NAS_APP_FROM_PORT(x) \
    NASTrace::GetNASTrace().GetAppNameFromPort(x);

#define NAS_TRACE_RANAP() \
    (g_Trace_enabledLevels & TRACE_RANAP_PDU)

#endif


