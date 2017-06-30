///////////////////////////////////////////////////////////////////////////////
//
// MibXMLMerger.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibXMLMerger.h"

using namespace std;

// TODO: Delete unused sections below.

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

const xmlChar * name = (const xmlChar*) "name";

const xmlChar * nsUri = (const xmlChar*) "http://www.Radisys.com/umts-fap/mib";
const xmlChar * nsPrefix = (const xmlChar*) "mib";
const xmlChar * mib = (const xmlChar*) "mib";
const xmlChar * mibOutput = (const xmlChar*) "mib:mib";
const xmlChar * attributeDefs = (const xmlChar*) "attributeDefs";
const xmlChar * attributeDef = (const xmlChar*) "attributeDef";
const xmlChar * attributeEnumDef = (const xmlChar*) "attributeEnumDef";
const xmlChar * managedObjects = (const xmlChar*) "managedObjects";
const xmlChar * managedObject = (const xmlChar*) "managedObject";

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibXMLMerger::MibXMLMerger(const std::string &outputFile)
{
    //ENTER();

    LIBXML_TEST_VERSION;


    // Save file
    m_outputFile = outputFile;
    /*
     * Creates a new document, a node and set it as a root node
     * This document is intended to be valid in the mib namespace so make it so
     */
    m_doc = xmlNewDoc(BAD_CAST "1.0");

    m_root_node = xmlNewNode(NULL, mibOutput);
    xmlDocSetRootElement(m_doc, m_root_node);

    /*
     * Add that namespace
     */
    xmlNewNs(m_root_node, nsUri ,nsPrefix);

    /*
     * xmlNewChild() creates a new node, which is "attached" as child node
     * of root_node node.
     */
    m_attributeDefs_node = xmlNewNode(NULL, attributeDefs);
    xmlAddChild(m_root_node, m_attributeDefs_node);

//    xmlNodePtr rar = xmlNewNode(NULL, (const xmlChar*) "rubbish");
//    xmlAddChild(m_attributeDefs_node, rar);

    m_managedObjects_node = xmlNewNode(NULL, managedObjects);
    xmlAddChild(m_root_node, m_managedObjects_node);

    //EXIT();
}

MibXMLMerger::~MibXMLMerger()
{
    //ENTER();
    /*
     * Dumping document to stdio or file
     */
    if (m_outputFile.empty())
    {
       xmlSaveFormatFileEnc("-", m_doc, "UTF-8", 1);
    }
    else
    {
        xmlSaveFormatFileEnc(m_outputFile.c_str(), m_doc, "UTF-8", 1);
    }

    /*free the document */
    xmlFreeDoc(m_doc);


    //EXIT();
}

void MibXMLMerger::Merge(const std::string & inputFile)
{
    //ENTER();

    xmlDocPtr inputDoc = NULL;       /* document pointer */
    xmlNodePtr intputRootNode = NULL;/* node pointers */

    inputDoc = xmlParseFile(inputFile.c_str());

    assert(not(inputDoc == NULL ));

    intputRootNode = xmlDocGetRootElement(inputDoc);

    assert(intputRootNode != NULL);
    // All the files must have the MIB root element
    assert(not(xmlStrcmp(intputRootNode->name, mib)));

    // Examine first child
    xmlNodePtr cur = intputRootNode->xmlChildrenNode;
    while (cur != NULL)
    {
        // Merge in attributeDefs element
        // ASSUMPTION The attributeDef elements are unique and not declared anywhere else
        if (xmlStrcmp(cur->name, attributeDefs) == 0)
        {
            MergeAttributeDefs(cur);
        }

        // Merge in managedObjects element
        // ASSUMPTION The managedObject elements are unique and not declared anywhere else
        if (xmlStrcmp(cur->name, managedObjects) == 0)
        {
            MergeManagedObjects(cur);
        }

        cur = cur->next;
    }

    xmlFreeDoc(inputDoc);

    //EXIT();
}


void MibXMLMerger::MergeAttributeDefs( const xmlNodePtr inputAttributeDefs)
{
    //ENTER();

    int extended = 1;

    if (inputAttributeDefs == NULL) return;

    xmlNodePtr cur = inputAttributeDefs->xmlChildrenNode;
    while (cur != NULL)
    {
        if ((xmlStrcmp(cur->name, attributeDef) == 0) || (xmlStrcmp(cur->name, attributeEnumDef) == 0))
        {
            xmlNodePtr toImport = xmlCopyNode(cur, extended);
            if (toImport == NULL) std::cerr << "ERROR: NULL returned from copy" << std::endl;
            xmlAddChild(m_attributeDefs_node, toImport);
        }

        cur = cur->next;
    }

    //EXIT();
}

void MibXMLMerger::MergeManagedObjects(const xmlNodePtr inputManagedObjects)
{
    //ENTER();

    int extended = 1;

    if (inputManagedObjects == NULL) return;
    xmlNodePtr cur = inputManagedObjects->xmlChildrenNode;
    while (cur != NULL)
    {
        if (xmlStrcmp(cur->name, managedObject) == 0)
        {
            xmlNodePtr toImport = xmlCopyNode(cur, extended);
            if (toImport == NULL) std::cerr << "ERROR: NULL returned from copy" << std::endl;
            xmlAddChild(m_managedObjects_node, toImport);
        }

        cur = cur->next;
    }

    //EXIT();
}
