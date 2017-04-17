///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// iu_user_plane.h
//
// Shared messaging between the cs-user-plane application, controlling audio
// send + receive between layer 1 FIFO's and some remote gateway.
//
// Copyright ? 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __iu_user_plane_h_
#define __iu_user_plane_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

// From 25.413, R99 9.2.1.3 RAB Parameter constants...
#define MAX_RAB_SUBFLOW_COMBINATIONS	64
#define MAX_RAB_SUBFLOWS				7

typedef enum enumIuUpMode
{
	IU_UP_TRANSPARENT_MODE,
	IU_UP_SUPPORT_MODE
}IuUpMode;

typedef enum enumIuUpDataPduType
{
    IU_UP_DATA_PDU_TYPE_0,
    IU_UP_DATA_PDU_TYPE_1
}IuUpDataPduType;

typedef struct structSDUParameters
{
	// List of acceptable SDU sizes, and the number of sub flows.
	u8 numberOfSduSubFlows;
	u16 sduSubFlowSizes [MAX_RAB_SUBFLOW_COMBINATIONS];
}SDUParameters;

typedef struct structIuUserPlane
{
	// Logical and physical RAB subflow descriptions, and the number of sub flows.
	u8 sduParameterCount;
	SDUParameters sduParameters [MAX_RAB_SUBFLOWS];

	// The size of the Sdu gives us whether the Cs call is Video (640)
	// or Amr Speech (any other value, 244 = 12.2k Amr).
	u16 maxSduSize;

	// Bitmap where each bit is 'on' to indicate mode supported,
	// and 'off' to indicate not supported.  Received from the CN
	// indicating supported modes at the switch.  Current modes are;
	// Transparent Mode - Mode 1
	// Support Mode - Mode 1, Mode 2
	u16 iuModeVersionBitmap;

	// Data Pdu type to use.  0 if we are not error checking (there
	// is no payload Crc in Type 0), 1 if we are checking.
	IuUpDataPduType iuDataPduType;
	
	// What's the Radio Bearer Identity associated with this media stream?
	u8 radioBearerIdentity;

	// In TRANSPARENT mode, there is no INITIALISATION message and no Iu UP header
	// information in the data packets.  In SUPPORT mode, the opposite is true...
	IuUpMode iuUpMode;

}IuUserPlane;


#endif
