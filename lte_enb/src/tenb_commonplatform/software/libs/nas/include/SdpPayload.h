

#ifndef __SdpPayload_h_
#define __SdpPayload_h_

#include <stlMap.h>
#include <stlString.h>
#include <NumberList.h>

#define MEDIA_FORMATS_LIMIT		16

// Note we use char() and not NASString as the implementation code
// will memset() this structure when (re)initialising.

typedef struct structSdpMedia
{
	std::string mediaDescription;

	NumberList mediaAttributes;

}SdpMedia;

typedef std::map < std::string, SdpMedia * > SdpPayloadTypes;

#endif


