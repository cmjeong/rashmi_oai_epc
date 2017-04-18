///////////////////////////////////////////////////////////////////////////////
//
// Tr069ActiveAlarmEventListRadisysXmlGenerator.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069ActiveAlarmEventListRadisysXmlGenerator_h_
#define __Tr069ActiveAlarmEventListRadisysXmlGenerator_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/AlarmEventLog.h>
#include <system/ActiveAlarms.h>
#include <messaging/transport/ApplicationWithMessaging.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr196Alarm.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////



class Tr069AlarmEventListRadisysXMLGenerator : public AlarmEventListVisitor
{
public:
    typedef enum AlarmFileType_tag
    {
        SITUATION,
        LOG,
    } AlarmFileType;

    Tr069AlarmEventListRadisysXMLGenerator( AlarmFileType type, const char * filename ) :
        m_file(NULL)
    {
        m_file = fopen(filename, "w" );

        switch(type)
        {
            case SITUATION:
                TRACE_PRINTF("Alarm Situation File %s", filename);
                m_fieldText = "FapAlarmSituation";
                break;

            case LOG:
                TRACE_PRINTF("Alarm Log File %s", filename);
                m_fieldText = "FapAlarmLog";
                break;
        }

    }

    ~Tr069AlarmEventListRadisysXMLGenerator()
    {
        if(m_file)
        {
            fclose(m_file);
            m_file = NULL;
        }
    }

    void WriteFileHeader(void)
    {
        RSYS_ASSERT(m_file);

        TRACE_PRINTF("<file>");

        fprintf(m_file,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
        fprintf(m_file,"<%s xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"FapAlarmsDefinition.xsd\">", m_fieldText.c_str() );
    }

    void WriteFileFooter(void)
    {
        RSYS_ASSERT(m_file);

        TRACE_PRINTF("</file>");

        fprintf(m_file,"</%s>", m_fieldText.c_str());
        fflush(m_file);
    }

    void VisitAlarmEvent(const AlarmEvent& alarmEvent)
    {
        shared_ptr<Tr196RadisysAlarm> tr196Alarm( new Tr196RadisysAlarm(alarmEvent) );

        TRACE_PRINTF("%s (%s) %s: %s",
                tr196Alarm->GetAlarmIdentifier().c_str(),
                tr196Alarm->GetEventType().c_str(),
                tr196Alarm->GetProbableCause().c_str(),
                tr196Alarm->GetSpecificProblem().c_str()
                );

        fprintf( m_file,
                 "<AlarmData AlarmNumber=\"%s\" AlarmActivity=\"%s\" ObservationTime=\"%s\" Severity=\"%s\" AlarmText=\"%s\" AlarmAdditionalInfo=\"%s\" EventType=\"%s\" SequenceNumber=\"%s\"/>",
                 tr196Alarm->GetAlarmIdentifier().c_str(),
                 "tr196Alarm->GetAlarmActivity()",
                 tr196Alarm->GetEventTime().c_str(),
                 tr196Alarm->GetPercievedSeverity().c_str(),
                 XmlSafeString(tr196Alarm->GetProbableCause()).c_str(),
                 XmlSafeString(tr196Alarm->GetSpecificProblem()).c_str(),
                 tr196Alarm->GetEventType().c_str(),
                 "tr196Alarm->GetAlarmSequenceNumber()"
                 );
    }


private:
    FILE * m_file;
    string m_fieldText;
};


#endif
