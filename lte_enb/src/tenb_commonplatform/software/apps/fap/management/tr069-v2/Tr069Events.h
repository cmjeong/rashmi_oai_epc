///////////////////////////////////////////////////////////////////////////////
//
// Tr069Events.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069Events_h_
#define __Tr069Events_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <queue>
#include <libcsoap/soap-client.h>
#include <system/TimerInterface.h>


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


#include "Tr069EventActivateSoftware.h"
#include "Tr069Event0Bootstrap.h"
#include "Tr069ConnectionRequest.h"
#include "Tr069DataModelVerifyCnf.h"
#include "Tr069DownloadRequest.h"
#include "Tr069DownloadResponse.h"
#include "Tr069FactoryResetCommand.h"
#include "Tr069FtpSessionCommand.h"
#include "Tr069FgwQuery.h"
#include "Tr069HmsModifyReq.h"
#include "Tr069HttpPostRequest.h"
#include "Tr069HttpPostResponse.h"
#include "Tr069RpcSetParameterValue.h"
#include "Tr069SecGwModifyReq.h"
#include "Tr069ServerDeselect.h"
#include "Tr069StartTransactionSession.h"
#include "Tr069TcpConnectionFailureInd.h"
#include "Tr069TcpConnectCnf.h"
#include "Tr069TcpConnectInd.h"
#include "Tr069TcpConnectReq.h"
#include "Tr069TcpConnectRej.h"
#include "Tr069TcpDisconnectCnf.h"
#include "Tr069TcpDisconnectReq.h"
#include "Tr069TimerExpiryEvent.h"
#include "Tr069TransactionSessionCommand.h"
#include "Tr069TransactionSessionComplete.h"
#include "Tr069UploadRequest.h"
#include "Tr069UploadResponse.h"
#include "Tr069ValueChange.h"
#include "Tr069Periodic.h"
#include "Tr069PeriodicInformUpdate.h"

#include "Tr069SocketsInterface.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////


#endif
