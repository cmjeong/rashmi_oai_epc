///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeS32.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <cassert>
#include <ostream>
#include <sstream>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibXMLParser.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

const xmlChar * MibXMLParser::name = (const xmlChar*) "name";
const xmlChar * MibXMLParser::type = (const xmlChar*) "type";

const xmlChar * MibXMLParser::twoDimensionArray = (const xmlChar*) "twoDimensionArray";
const xmlChar * MibXMLParser::array = (const xmlChar*) "array";
const xmlChar * MibXMLParser::entity = (const xmlChar*) "entity";
const xmlChar * MibXMLParser::enumeration = (const xmlChar*) "enumeration";
const xmlChar * MibXMLParser::enumValue = (const xmlChar*) "enumValue";
const xmlChar * MibXMLParser::scalar = (const xmlChar*) "scalar";
const xmlChar * MibXMLParser::noprocess = (const xmlChar*) "noprocess";


///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibXMLParser::MibXMLParser(const std::string &file)
{
    m_doc = xmlParseFile(file.c_str());

    assert(not(m_doc == NULL ));

    m_cur = xmlDocGetRootElement(m_doc);

    assert (m_cur != NULL);
    // All the files must have the MIB root element
    assert(not(xmlStrcmp(m_cur->name, (const xmlChar *) "mib")));

    return;
}

MibXMLParser::~MibXMLParser()
{
    xmlFreeDoc(m_doc);
    return;
}

void MibXMLParser::CreateDoc(std::ostream &os)
{
    xmlNodePtr cur = m_cur->xmlChildrenNode;
    while (cur != NULL)
    {
        if (!xmlStrcmp(cur->name, twoDimensionArray))
        {
            CreateTwoDimensionalArray(os, cur);
        }
        else if (!xmlStrcmp(cur->name, enumeration))
        {
            CreateEnumeration(os, cur);
        }
        else if (!xmlStrcmp(cur->name, scalar))
        {
            CreateScalar(os, cur);
        }
        else if (!xmlStrcmp(cur->name, noprocess))
        {
            GetCData(os, cur); // This allows non-dynamic data to decorate the output file
        }
        else
        {
            // ignore unrecognised nodes - don't issue warnings about them
        }

        os << std::endl;
        cur = cur->next;
    }

    return;
}

void MibXMLParser::CreateEnumeration(std::ostream &os, xmlNodePtr cur)
{
    bool firstElement = true;

    assert(cur != NULL);
    assert(!xmlStrcmp(cur->name, enumeration));
    xmlChar * xmlPropVal = xmlGetProp( cur, name );

    cur = cur->xmlChildrenNode;


    os << "ENUM_START(" << xmlPropVal << ')' << std::endl
              << '{' << std::endl;
    while (cur != NULL)
    {
        if ((!xmlStrcmp(cur->name, enumValue))) {
            xmlChar* key = xmlNodeListGetString(m_doc, cur->xmlChildrenNode, 1);
            if (firstElement)
            {
                os << "    ENUM_ELEMENT_VAL(" << key << ",0)" << std::endl;
                firstElement = false;
            }
            else
            {
                os << "    ENUM_ELEMENT(" << key << ')' << std::endl;
            }
            xmlFree(key);
        }

        cur = cur->next;
    }
    os << '}' << std::endl
              << "ENUM_END(" << xmlPropVal << ')' << std::endl;

    xmlFree(xmlPropVal);

}

void MibXMLParser::CreateTwoDimensionalArray(std::ostream &os, xmlNodePtr cur)
{
    assert(cur != NULL);
    assert(!xmlStrcmp(cur->name, twoDimensionArray));

    xmlChar * xmlPropName = xmlGetProp( cur, name );
    xmlChar * xmlPropType = xmlGetProp( cur, type );

    os << "static const " << xmlPropType << ' ' << xmlPropName << "[] =" << std::endl
       << '{';

    cur = cur->xmlChildrenNode;

    while (cur != NULL)
    {
        xmlNodePtr innerCur = cur->xmlChildrenNode;

        assert(!xmlStrcmp(cur->name, array));

        if (not(cur->parent->children == cur)) // not first child
        {
            os << ", ";
        }

        os  << std::endl << "    ";
        // Only use curly braces if there's more than 1 child
        if (innerCur->next != NULL)
        {
            os << '{';
        }

        while (innerCur != NULL)
        {
            assert (!xmlStrcmp(innerCur->name, entity));

            xmlChar* key = xmlNodeListGetString(m_doc, innerCur->xmlChildrenNode, 1);
            if (not(innerCur->parent->children == innerCur)) // not first inner child
            {
                os << ", ";
            }
            os << key;

            xmlFree(key);


            innerCur = innerCur->next;
        } // end inner loop
        // Only use curly braces if there's more than 1 child
        if (cur->children->next != NULL)
        {
            os << '}';
        }


        cur = cur->next;
    } // end outer loop
    os << std::endl << "};" << std::endl;


    xmlFree(xmlPropName);
    xmlFree(xmlPropType);

    return;
}

void MibXMLParser::CreateScalar(std::ostream &os, xmlNodePtr cur)
{
    assert(cur != NULL);
    assert(!xmlStrcmp(cur->name, scalar));
    xmlChar * xmlPropName = xmlGetProp( cur, name );
    xmlChar * xmlPropType = xmlGetProp( cur, type );
    xmlChar* key = xmlNodeListGetString(m_doc, cur->xmlChildrenNode, 1);

    os << "static const " << xmlPropType << ' ' << xmlPropName
        << " = " << key << ';' << std::endl;

    /// Free the data structures
    xmlFree(xmlPropName);
    xmlFree(xmlPropType);
    xmlFree(key);

    return;
}

void MibXMLParser::GetCData(std::ostream &os, xmlNodePtr cur)
{
    assert(cur != NULL);
    assert(!xmlStrcmp(cur->name, noprocess));

    xmlChar* key = xmlNodeListGetString(m_doc, cur->xmlChildrenNode, 1);

    os << key;

    xmlFree(key);

    return;
}

void MibXMLParser::parseRecursive (xmlNodePtr cur, int indent)
{
    indent+=2;
    cur = cur->xmlChildrenNode;
    while (cur != NULL)
    {
        if (xmlStrcmp(cur->name, (const xmlChar *)"text"))
        {
//            printf("%*s", indent,"");
//            printf("%s\n", (const char*)cur->name);
        }
        parseRecursive(cur, indent);

        cur = cur->next;
    }

    return;
}
