///////////////////////////////////////////////////////////////////////////////
//
// Tr069Parameters.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////


#ifndef __Tr069Parameters_h_
#define __Tr069Parameters_h_


///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <sstream>
#include <map>
#include <boost/shared_ptr.hpp>
#include <MibAttributeId.h>
#include <messaging/messages/common/OamActionReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


#include "Tr069Application.h"

using namespace std;

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////
typedef bool (*ParameterValidator)( const string & value );

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class NsnParameter
{
public:

    static const char * ActionReset;
    static const char * ActionRescan;

    typedef enum FactoryWidgets_tag
    {
        WidgetActionRescan,
        WidgetActionReset,

    } FactoryWidgets;

    typedef enum ParamFlags_tag
    {
        NULL_FLAG                   = 0x00000000,
        CS_READ                     = 0x00000001,
        CS_WRITE                    = 0x00000002,
        FGW_READ                    = 0x00000004,
        FGW_WRITE                   = 0x00000008,
        UPDATE_NV_ON_WRITE          = 0x00000010,
        ACTIVE_NOTIFICATIONS        = 0x00000020,

        // Useful compounds
        CS_RW                       = (CS_READ | CS_WRITE),
        FGW_RW                      = (FGW_READ | FGW_WRITE),
        READ                        = FGW_READ | CS_READ,
        WRITE                       = FGW_WRITE | CS_WRITE,
        RW                          = READ | WRITE,

    } ParamFlags;


    NsnParameter( const char * fullyQualifiedParameterName, MibObjectClass mibObjectClass, MibAttributeId mibAttributeId, ParameterValidator validator, u32 flags ) :
        m_fullyQualifiedName(fullyQualifiedParameterName),
        m_mibAttributeId(mibAttributeId),
        m_validator(validator),
        m_flags(flags)
    {
        // We use ROOT class to mean not-applicable so don't build DN if class is ROOT.
        if(mibObjectClass != MIB_OBJECT_CLASS_INVALID)
        {
            m_dn = MibDN::GenerateMibDN(mibObjectClass);
        }
    }

    virtual ~NsnParameter() {}

    virtual bool FullyQualifiedParameterNameMatch( const string & fullyQualifiedName)
    {
        return (fullyQualifiedName == m_fullyQualifiedName);
    }

    virtual bool PartiallyQualifiedPathNameMatch( const string & partiallyQualifiedName)
    {
        bool match = false;
        size_t strLength = partiallyQualifiedName.length();

        if(strLength > 0)
        {
            if('.' == partiallyQualifiedName.at(strLength-1))
            {
                match = (0 == partiallyQualifiedName.compare(0,strLength,m_fullyQualifiedName, 0, strLength));
            }
        }

        return match;
    }

    virtual void TriggerActiveNotification() { TRACE_PRINTF(("TriggerActiveNotification not implemented")); }

    virtual const string & FgwReadValue( ) = 0;
    virtual void FgwWriteValue( MibAttributeValues& mibAttrs, const string & value ) = 0;
    virtual void ChangeNotification( const string & value ) = 0;
    virtual void ChangeNotification( )
    {
        if( GetActiveNotification() )
        {
            TriggerActiveNotification();
        }
    }


    const string & GetFullyQualifiedParameterName() const {return m_fullyQualifiedName;}
    bool QueryParameterValid(const string & value) const { if(m_validator) return m_validator(value); else return true;}
    bool GetReadable() const {return (0 != (m_flags & (CS_READ | FGW_READ)));}
    bool GetWriteable() const {return (0 != (m_flags & (CS_WRITE | FGW_WRITE)));}
    bool GetUpdateNvOnWrite() const {return (0 != (m_flags & (UPDATE_NV_ON_WRITE)));}
    bool GetActiveNotification() const {return (0 != (m_flags & (ACTIVE_NOTIFICATIONS)));}
    void SetActiveNotification( bool activeNotification )
    {
        if(activeNotification)
        {
            m_flags &= ACTIVE_NOTIFICATIONS;
        }
        else
        {
            m_flags &= ~(u32)ACTIVE_NOTIFICATIONS;
        }
    }

    virtual const string & ToString() = 0;

    MibAttributeId GetMibAttributeId() const
    {
        RSYS_ASSERT(m_mibAttributeId != PARAM_ID_INVALID);
        return m_mibAttributeId;
    }

    typedef struct NsnParameterTypeDefinition_tag
    {
        FactoryWidgets      widget;
        const char *        fullyQualifiedName;
        MibObjectClass      mibObjectClass;
        MibAttributeId      mibAttributeId;
        ParameterValidator  validator;
        u32                 flags;

    } NsnParameterTypeDefinition;


    static const NsnParameterTypeDefinition nsnParameterDictionary[];
    static const size_t nsnParameterDictionaryLength;

protected:
    string m_toString;
    MibDN m_dn;
    MibAttributeId m_mibAttributeId;
    string m_fullyQualifiedName;
    ParameterValidator m_validator;
    u32 m_flags;
};


class NsnParameterString : public NsnParameter
{
public:
    NsnParameterString( const char * fullyQualifiedParameterName, MibObjectClass mibObjectClass, MibAttributeId mibAttributeId, ParameterValidator validator, u32 flags, const char * fgwInitialValue = ""  ) :
        NsnParameter(fullyQualifiedParameterName, mibObjectClass, mibAttributeId, validator, flags),
        m_valueOfParameterAsKnownByFgw(fgwInitialValue)
        {}
    virtual ~NsnParameterString() {}

    virtual const string & ToString()
    {
        m_toString = GetMibParam();

        return m_toString;
    }

    virtual void FgwWriteValue( MibAttributeValues& mibAttrs, const string & value )
    {
        RSYS_ASSERT(GetWriteable());

        m_valueOfParameterAsKnownByFgw = value;

        mibAttrs.AddAttribute(GetMibAttributeId(), m_valueOfParameterAsKnownByFgw);
    }

    virtual const string & FgwReadValue( )
    {
        RSYS_ASSERT(GetReadable());

        m_valueOfParameterAsKnownByFgw = GetMibParam();

        return ToString();
    }

    virtual void ChangeNotification( const string & value )
    {
        bool updateMibRequired = (GetMibParam() != value);

        if(updateMibRequired)
        {
            MibAttributeValues attrs;
            attrs.AddAttribute(GetMibAttributeId(), value);
            Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);
        }
    }

    virtual string GetMibParam() const
    {
        string value;

        if(Tr069Application::GetInstance().GetMibCache().IsMibAttributePresent(m_dn, GetMibAttributeId()))
        {
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute(m_dn, GetMibAttributeId(), value);
        }
        else
        {
            TRACE_PRINTF_LEV(TRACE_WARNING, "Trying to get MIB attribute %s but no value available", getMibAttributeName(GetMibAttributeId()));
        }

        return value;
    }

protected:
    string m_valueOfParameterAsKnownByFgw;
};


class NsnParameterActionReset : public NsnParameterString
{
public:
    NsnParameterActionReset( const char * fullyQualifiedParameterName, MibObjectClass mibObjectClass, MibAttributeId mibAttributeId, ParameterValidator validator, u32 flags, const char * fgwInitialValue = ""  ) :
        NsnParameterString(fullyQualifiedParameterName, mibObjectClass, mibAttributeId, validator, flags, fgwInitialValue)
        {}
    virtual ~NsnParameterActionReset() {}

    virtual void FgwWriteValue( MibAttributeValues& mibAttrs, const string & value );
};


class NsnParameterActionRescan : public NsnParameterString
{
public:
    NsnParameterActionRescan( const char * fullyQualifiedParameterName, MibObjectClass mibObjectClass, MibAttributeId mibAttributeId, ParameterValidator validator, u32 flags, const char * fgwInitialValue = ""  ) :
        NsnParameterString(fullyQualifiedParameterName, mibObjectClass, mibAttributeId, validator, flags, fgwInitialValue)
        {}
    virtual ~NsnParameterActionRescan() {}

    virtual void FgwWriteValue( MibAttributeValues& mibAttrs, const string & value );
};

class NsnParameterActionReconnect
{
public:
    static const u32 NormalReconnect = 0;
    static const u32 ReconnectToPrimaryFGW = 1;
    static const u32 ReconnectToOtherFGW = 2;

};


typedef map< string, shared_ptr< NsnParameter> > NsnParameterMap;
typedef map< MibAttributeId, shared_ptr< NsnParameter> > MibParamNsnParameterMap;


class NsnParameterManager
{
private:
    NsnParameterManager();

public:
    ~NsnParameterManager() {}
    static NsnParameterManager& GetInstance();

    const string & FgwReadValue( const string & parameterName );
    void FgwWriteValue( MibAttributeValues& mibAttrs, const char * parameterName, string & value );

    void ChangeNotification( const string& parameterName, string & value ); // for non MibParams

    void GetMibValue( const string& parameterName, u32 & value );
    void GetMibValue( const string& parameterName, string & value );

    bool SetParameterValueStruct( ParameterList_t  & paramValueStructs, std::ostringstream & osstreamFault );
    void SetParameter( const string& parameterName, const string & value );

private:

    bool QueryNameIsPartiallyQualifiedPath( const string & parameterName);

    static NsnParameterManager* s_instance;

    NsnParameterMap m_parameters;
    MibParamNsnParameterMap m_mibParamMap;
};





}


#endif


