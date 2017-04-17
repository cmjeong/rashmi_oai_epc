///////////////////////////////////////////////////////////////////////////////
//
// NASTrace.cpp
//
// Debug tracing functionality available in the system.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include <system/TimeWrap.h>
#include <system/StringUtils.h>

#include <NASTrace.h>
#include <Layer3Constants.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SystemConfiguration.h"
#include "lib-system/NASTrace.h"
#include "lib-system/NASString.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

NASTrace& NASTrace::GetInstance()
{
    if (s_instance == NULL)
    {
        s_instance.reset(new NASTrace());
    }

    return *(boost::dynamic_pointer_cast<NASTrace>(s_instance));
}

NASTrace::NASTrace() :
    Trace()
{
}

NASTrace::~NASTrace()
{
}

/*void NASTrace::TraceFunc (u32 category, u32 level, const char *varName, const c_MobileId &subscriberIdentity)
{
    char timeStr[20];
    char traceMsg[2048];
    std::string identityType, identityStr;

    GetTimeStr(timeStr, sizeof(timeStr));

	switch (subscriberIdentity.IdentityType)
	{
	case MI_IMSI:
		{
			identityType = "IMSI";

			char tempStr[4];
			for (s32 i=0;i<subscriberIdentity.IdentityDigit.items;i++)
			{
				snprintf (tempStr, sizeof(tempStr) - 1, "%lX", subscriberIdentity.IdentityDigit.data[i]);
				tempStr[sizeof(tempStr) - 1] = '\0';
				identityStr.append(tempStr);
			}//end for
		}
		break;

	case MI_IMEI:
		{
			identityType = "IMEI";

			char tempStr[4];
			for (s32 i=0;i<subscriberIdentity.IdentityDigit.items;i++)
			{
				snprintf (tempStr, sizeof(tempStr) - 1, "%lX", subscriberIdentity.IdentityDigit.data[i]);
				tempStr[sizeof(tempStr) - 1] = '\0';
                identityStr.append(tempStr);
			}//end for
		}
		break;

	case MI_TMSI_P_TMSI:
		{
			identityType = "TMSI";

            for (int i = 0; i < subscriberIdentity.IdentityDigit.items; i++)
			{
				u8 nextDigit = (u8) ((subscriberIdentity.IdentityDigit.data[i] & 0xf0) >> 4);
				identityStr.append(1, (char)(nextDigit <= 9 ? nextDigit + 48 : nextDigit + 55));
				nextDigit = (u8) (subscriberIdentity.IdentityDigit.data[i] & 0x0f);
				identityStr.append(1, (char)(nextDigit <= 9 ? nextDigit + 48 : nextDigit + 55));
			}//end for
		}
		break;

	default:
		{
	         char tempStr[16];
             snprintf(tempStr, sizeof(tempStr) - 1, "?%lu", subscriberIdentity.IdentityType);
             tempStr[sizeof(tempStr) - 1] = '\0';
             identityType = tempStr;
		}
	}//end switch

	snprintf (traceMsg, sizeof(traceMsg), "%s%*c%s: %s:%s\n", timeStr, GetCallStackIndent(), ' ', varName, identityType.c_str(), identityStr.c_str());
	traceMsg[sizeof(traceMsg) - 1] = '\0';

    LogToFile(traceMsg);
    LogToUdp(traceMsg);
}

void NASTrace::TraceFunc (u32 category, u32 level, const char *varName, const c_LocationAreaId &locationArea)
{
    char timeStr[20];
    char traceMsg[2048];

    GetTimeStr(timeStr, sizeof(timeStr));

	NASString locArea;
	if (locationArea.MNC3 != 0x0f)
	{
		snprintf ((char *) locArea, locArea.GetSize(), "MCC %u%u%u MNC %u%u%u LAC 0x%04X",
			locationArea.MCC1, locationArea.MCC2, locationArea.MCC3,
			locationArea.MNC1, locationArea.MNC2, locationArea.MNC3,
			locationArea.LAC);
	}
	else
	{
		snprintf ((char *) locArea, locArea.GetSize(), "MCC %u%u%u MNC %u%u LAC 0x%04X",
			locationArea.MCC1, locationArea.MCC2, locationArea.MCC3,
			locationArea.MNC1, locationArea.MNC2,
			locationArea.LAC);
	}//end if

	snprintf (traceMsg, sizeof(traceMsg), "%s%*c%s: %s\n", timeStr, GetCallStackIndent(), ' ', varName, (const char *) locArea);

    LogToFile(traceMsg);
    LogToUdp(traceMsg);
}

void NASTrace::TraceFunc (u32 category, u32 level, const char *varName, const c_RoutingAreaIdenti &routingArea)
{
    char timeStr[20];
    char traceMsg[2048];

    GetTimeStr(timeStr, sizeof(timeStr));

    NASString locArea;
	if (routingArea.MNC3 != 0x0f)
	{
		snprintf ((char *) locArea, locArea.GetSize(), "MCC %u%u%u MNC %u%u%u LAC 0x%04X RAC %u",
			routingArea.MCC1, routingArea.MCC2, routingArea.MCC3,
			routingArea.MNC1, routingArea.MNC2, routingArea.MNC3,
			routingArea.LAC, routingArea.RAC);
	}
	else
	{
		snprintf ((char *) locArea, locArea.GetSize(), "MCC %u%u%u MNC %u%u LAC 0x%04X RAC %u",
			routingArea.MCC1, routingArea.MCC2, routingArea.MCC3,
			routingArea.MNC1, routingArea.MNC2,
			routingArea.LAC, routingArea.RAC);
	}//end if

	snprintf (traceMsg, sizeof(traceMsg), "%s%*c%s: %s\n", timeStr, GetCallStackIndent(), ' ', varName, (const char *) locArea);

    LogToFile(traceMsg);
    LogToUdp(traceMsg);
}

void NASTrace::TraceFunc (u32 category, u32 level, const char *varName, const c_TBCDArray &numberDigits)
{
    char timeStr[20];
    char traceMsg[2048];

    GetTimeStr(timeStr, sizeof(timeStr));

	if (numberDigits.items > 0)
	{
		char numberBuff[32];
		memset (numberBuff, '\0', sizeof (numberBuff));

		for (int i=0;i<numberDigits.items;i++)
			numberBuff[i] = (char) (numberDigits.data[i] + 48);

		snprintf (traceMsg, sizeof(traceMsg), "%s%*c%s: %s\n", timeStr, GetCallStackIndent(), ' ', varName, numberBuff);
	}
	else
	{
		snprintf (traceMsg, sizeof(traceMsg), "%s%*c%s: Number Is EMPTY\n", timeStr, GetCallStackIndent(), ' ', varName);
	}//end if

    LogToFile(traceMsg);
    LogToUdp(traceMsg);
}*/

void NASTrace::TraceFunc (u32 category, u32 level, const char *varName, const BCDAddress &bcdAddress)
{
    char timeStr[20];
    char traceMsg[2048];

    // Preconditions.
    RSYS_ASSERT(bcdAddress.addressLength <= sizeof(bcdAddress.bcdDigit));

    GetTimeStr(timeStr, sizeof(timeStr));

	if (bcdAddress.addressLength > 0)
	{
		NASString numberBuff;

		u8 digitCount = 0, nextDigit = 0;
		for (u8 i=0;i<bcdAddress.addressLength;i++)
		{
			nextDigit = bcdAddress.bcdDigit[i] & 0x0f;
			numberBuff[digitCount++] = (char) (nextDigit + 48);

			nextDigit = ((bcdAddress.bcdDigit[i] & 0xf0) >> 4);
			if (nextDigit != 0x0f)
				numberBuff[digitCount++] = (char) (nextDigit + 48);
		}//end for

		snprintf (traceMsg, sizeof(traceMsg), "%s%*c%s: BCD [%s]\n",
            timeStr, GetCallStackIndent(), ' ', varName, (const char *) numberBuff);
	}
	else
	{
		snprintf (traceMsg, sizeof(traceMsg), "%s%*c%s: Number Is EMPTY\n",
            timeStr, GetCallStackIndent(), ' ', varName);
	}//end if

    LogToFile(traceMsg);
    LogToUdp(traceMsg);
}

void NASTrace::TraceFunc (u32 category, u32 level, const char *varName, const struct sockaddr sockAddress)
{
    struct sockaddr_in fC;
    char timeStr[20];
    char traceMsg[2048];

    // Copy to avoid aliasing warning
    memcpy(&fC, &sockAddress, sizeof(struct sockaddr_in));

    GetTimeStr(timeStr, sizeof(timeStr));
    snprintf(traceMsg, sizeof (traceMsg), "%s%*c%s: %s\n",
             timeStr, GetCallStackIndent(), ' ', varName, inet_ntoa(fC.sin_addr));

    LogToFile(traceMsg);
    LogToUdp(traceMsg);
}

void NASTrace::FormatString (char *stringBuffer, u32 numericValue, u16 lengthOfString)
{
	char scratchPad[64];
	bzero (scratchPad, 64);

	// Everywhere, in all ways, -1 means undefined (in our system).  Display
	// formatted text instead of UINT_MAX...
	if (numericValue == (u32) -1)
	{
		strncpysafe (scratchPad, "UNDEFINED", sizeof(scratchPad));
	}
	else
	{
		snprintf (scratchPad, sizeof(scratchPad), "%" PRIu32, numericValue);
	}//end if

	u16 startingLength = (u16) strlen (scratchPad);

	if (lengthOfString > startingLength)
		for (u16 i=0;i<lengthOfString - startingLength;i++)
			strncat (scratchPad, " ", sizeof(scratchPad) - strlen(scratchPad));

	strcpy (stringBuffer, scratchPad);
}

void NASTrace::FormatString (char *stringBuffer, const char *stringValue, u16 lengthOfString)
{
	char scratchPad[64];
	bzero (scratchPad, 64);

	strncpysafe (scratchPad, stringValue, sizeof(scratchPad));

	u16 startingLength = (u16) strlen (scratchPad);

	if (lengthOfString > startingLength)
		for (u16 i=0;i<lengthOfString - startingLength;i++)
			strncat (scratchPad, " ", sizeof(scratchPad) - strlen(scratchPad));

	strcpy (stringBuffer, scratchPad);
}

