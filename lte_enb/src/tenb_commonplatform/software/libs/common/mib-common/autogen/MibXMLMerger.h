///////////////////////////////////////////////////////////////////////////////
//
// MibXMLMerger.h
//
// TODO: Describe purpose and usage of class(es).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibXMLMerger_h_
#define __MibXMLMerger_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibXMLMerger
{
public:
    /**
     * Default constructor.
     */
    MibXMLMerger(const std::string &outputFile);

    /**
     * Destructor.
     */
    ~MibXMLMerger();

    /***
     * Merge mib xml file into current file.
     */
    void Merge(const std::string & inputFile);

    /***
     * Merge the attributeDef elements under the pointer into the current document
     * @param inputAttributeDefs
     */
    void MergeAttributeDefs(const xmlNodePtr inputAttributeDefs);

    /***
     * Merge the managedOjbect elements under the pointer into the current document
     * @param inputManagedObjects
     */
    void MergeManagedObjects(const xmlNodePtr inputManagedObjects);

protected:

private:
    std::string m_outputFile; // file to save merged data into

/*
    static const xmlChar * name;

    static const xmlChar * nsUri;
    static const xmlChar * nsPrefix;

    // input match strings
    static const xmlChar * mib;
    static const xmlChar * attributeDefs;
    static const xmlChar * attributeDef;
    static const xmlChar * attributeEnumDef;
    static const xmlChar * managedObjects;
    static const xmlChar * managedObject;

    // output match strings
    static const xmlChar * mibOutput;
*/
    xmlDocPtr m_doc;       /* document pointer */
    xmlNodePtr m_root_node;/* node pointers...i.e. mib node*/
    xmlNodePtr m_attributeDefs_node; /* attributeDefs node */
    xmlNodePtr m_managedObjects_node; /* managedObjects node */

};

#endif
