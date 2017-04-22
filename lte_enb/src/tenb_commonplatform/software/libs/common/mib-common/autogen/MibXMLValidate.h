///////////////////////////////////////////////////////////////////////////////
//
// MibXMLValidate.h
//
// This is a class wrapper for libxml2's schemaValidateDoc function
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibXMLValidate_h_
#define __MibXMLValidate_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>

#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibXMLValidate
{
public:
    /**
     * Default constructor.
     */
    MibXMLValidate(const std::string & schemaFile);

    /**
     * Destructor.
     */
    ~MibXMLValidate();

    /**
     * Validate the passed xmlFile against the schema passed in the constructor
     * @param xmlFile XML file to validate
     * @return True if XML file validates against the schema
     */
    bool IsValid(const std::string & xmlFile);

protected:

private:
    /***
     * XML Schema document pointer
     * ***/
    xmlDocPtr m_schemaDoc;

    /***
     * XML Schema Parser Context Pointer
     */
    xmlSchemaParserCtxtPtr m_schemaCtxt;

    /***
     * XML Schema pointer
     */
    xmlSchemaPtr m_wxschemas;

    /***
     * XML Schema Validate Context Pointer
     */
    xmlSchemaValidCtxtPtr m_schemaValidCtxt;
};

#endif
