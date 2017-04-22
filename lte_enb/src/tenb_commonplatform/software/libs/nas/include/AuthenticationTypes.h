///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// AuthenticationTypes.h
//
// Wrapper structures shared between the HLR + CORE primarily: used when
// generating authentication + cyphering information during moble registration.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AuthenticationTypes_h_
#define __AuthenticationTypes_h_

///////////////////////////////////////////////////////////////////////////////
// Global System Includes
///////////////////////////////////////////////////////////////////////////////
//CODE_CLEANUP
#if 0 
#include <ed_c.h>

///////////////////////////////////////////////////////////////////////////////
// NAS Application Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Application Working Directory
//
// For Now!  Obviously, we will move this into a configuration file later.
///////////////////////////////////////////////////////////////////////////////

typedef struct structAuthVectors
{
	// The AUTN below consists of (SQN XOR AK) & AMF & MAC (Where & indicates
	// concatentation).
	u8 AUTN[16];

	// A random 128 bit quantity, used to obtain uniqueness in the generated
	// values below.
	u8 RAND[16];

	// Cypher Key K, as obtained from the HLR.  Unique for every UE.
	u8 K[16];

	// Only requirement on the SEQuence Number is that it is unique on every
	// authentication attempt, and that it does not cycle too frequently to
	// cause the UE to reject us for unsuitable re-use of key numbers.
	u8 SQN[6];

	// Authentication Management Field, generated internally within the 
	// Authentication Centre.  Still looking for the generation mechanism
	// for this.
	u8 AMF[2];

	// MAC_A is obtained by running authentication function f1.  This is done
	// when obtaining a new set of authentication keys.
	u8 MAC_A[8];

	// MAC_S is obtained by running authentication function f1*.  This is done
	// when obtaining a new set of authentication keys due to synchronisation errors.
	u8 MAC_S[8];

	// RES is obtained by running authentication function f2.  The length of this
	// parameter is variable (4 - 16 Octets), hence the size parameter.
	u8 RES[16];

	// Number of Octets present in the RES buffer.
	u8 RES_Size;

	// CK is obtained by running authentication function f3.
	u8 CK[16];

	// IK is obtained by running authentication function f4.
	u8 IK[16];

	// AK is obtained by running authentication function f5.
	// Note this is NOT currently in use: AK will be 0x0000...
	u8 AK[6];

	// In the Authentication Failure case, where the cause is SYNCHRONISATION_FAILURE, this
	// will hold the concealed value of SQN[ms] held in the UE.
	u8 AUTS[14];

}AuthVectors;

// Structure used for CS Authentication and Cyphering.
typedef struct tagAUTNKeys
{
	// Note that the IMSI + TMSI need to be _checked_ for validity, as they may
	// or may not be populated depending on which operation is taking place
	// within the 3G network.

	// The IMSI of the subscriber for which this key information is relevant.
	c_MobileId ueImsi;

	// The TMSI of the subscriber for which this key information is relevant.
	c_MobileId ueTmsi;

	// The first stage of the authentication procedure is to obtain Authentication
	// vectors from the Authentication Centre, either running locally or within
	// the macro network switch.  Second stage is to transport the RES parameter
	// for checking against the network generated value.
	AuthVectors authVectors;

	// We have to know if the reason for the authentication vector request is a
	// location update procedure.  In that case, we have to contact the macro network
	// for new authentication keys.  In all other cases, we should be able to use
	// the existing vectors.
	bool userIsLocationUpdating;

}AUTNKeys;

// Structure used for PS Authentication and Cyphering.
typedef struct structAUTNKeysPS
{
	// In most cases, this will contain the PTMSI of the subscriber.  When it's the first
	// time we have seen a subscriber, it will be the IMSI.
	c_MobileId subscriberIdentity;

	// The associated PTMSI signature.  Will be set to 0 if not present.
	u32 ptmsiSignature;

	// Specifically, the IMSI of the subscriber, which is always returned for internal use.
	c_MobileId subscriberImsi;

	// The RAI applied to a Routing Area Update accept, if present.
	c_RoutingAreaIdenti routingArea;

	// And the authentication vectors provided from the Authentication Centre.  We are relying
	// on the Location Area Update [CS] procedure to generate these keys initially, and to
	// freshen them.
	AuthVectors authVectors;

	// If this is a new Routing Area Update, we will need to generate a new PTMSI and
	// associated PTMSI Signature.
	bool isRoutingAreaUpdate;

}AUTNKeysPS;

#define IDENTITY_PRESENT(x) x.IdentityDigit.items > 0
#endif /*0*/
#endif

