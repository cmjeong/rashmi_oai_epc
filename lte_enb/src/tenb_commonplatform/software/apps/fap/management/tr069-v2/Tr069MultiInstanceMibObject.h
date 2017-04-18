///////////////////////////////////////////////////////////////////////////////
//
// Tr069MultiInstanceObject.h
//
// TR069 Add/Delete Object classes
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069MultiInstanceObject_h_
#define __Tr069MultiInstanceObject_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <messaging/transport/MibAccessInterface.h>
#include <messaging/transport/Messenger.h>
#include <mib-common/messages/MibCreateObjectReq.h>
#include <mib-common/messages/MibDeleteObjectReq.h>
#include <mib-common/MibDN.h>
#include <MibObjectClass.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "Tr069MioMibInterface.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
#define MAX_HISTORY_ALARMS 150
#define MAX_EXPEDITED_ALARMS 50
#define MAX_QUEUED_ALARMS 50
namespace tr069
{

typedef struct MultiInstanceObjectDefintionTag
{
    struct
    {
        const char * path;
        const char * maxEntriesParameter;
        const char * currentEntriesParameter;
    } DataModel;
    struct
    {
        const char * parentDn;
        MibObjectClass childClass;
    } Mib;
} MultiInstanceObjectDefintion;

typedef map< string /* pathname */, class Tr069MultiInstanceObject & > Tr069MultiInstanceObjectsByPathname;
typedef map<string,struct CellInfo *> FreqCellMap;
struct CellInfo
{
   MibAttributeId freqname;
   MibObjectClass cellObjectClass;
   MibAttributeId cellfreq;
};
typedef struct 
{
   string freq;
   struct CellInfo cellinfo;
}FreqCellInfo;


class Tr069MultiInstanceObject
{
public:
    /**
     * Construction / destruction.
     */
    Tr069MultiInstanceObject(
            SendMessageInterface & messenger,
            MibAccessInterface& mib,
            const MultiInstanceObjectDefintion mioDef);
    ~Tr069MultiInstanceObject();

    shared_ptr<MibCreateObjectReq> New( MibAttributeValues & attr );
    bool check_if_instance_exist(u32 instance);  
    bool Delete( u32 instance );
    bool ValidateFreqCell(MibDN dn);


    u32 GetNumberOfEntries();
    u32 GetMaxEntries();

    void SubscribeToMib( u32 subId );
    void MibUpdated();
MibObjectClass GetChildClass();
private:
    bool m_rolling;
    SendMessageInterface & m_messenger;
    MibAccessInterface& m_mib;
    MultiInstanceObjectDefintion  m_mioDef;
    mutable MibDN m_parentDn;

    s32    m_previousMibInstance;
    u32    m_currentEntries;
    u32    m_maxEntries;
	u32    m_numObj;
	enum {
		added=0,
		modified,
		deleted
		} ObjStatus;

};



}
#endif
