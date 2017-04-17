#ifndef _OamAction_h_
#define _OamAction_h_

typedef enum OamActionTag
{
    OAM_ACTION_NOACTION = 0,

    OAM_ACTION_REBOOT,
    OAM_ACTION_FACTORY_RESET,
    OAM_ACTION_START_PERIODIC_REM_TIMER,
    OAM_ACTION_REM_SCAN,

    // Following used from SNMP only
    OAM_ACTION_GET_RSSI,
    OAM_ACTION_START_FRAME_AND_ERROR_COUNT,
    OAM_ACTION_STOP_FRAME_AND_ERROR_COUNT,

    OAM_ACTION_UNDEFINED
} OamAction;

#endif /*_OamAction_h_*/
