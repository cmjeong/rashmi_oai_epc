///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeId.h
//
// This is a tool that parses the XML files that were generated from applying the 4 XML
// stylesheets to mib.xml. It then writes the structure - in C++ syntax (with some
// Radisys macros) - to the output. This class encapsulates the tools core functions.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////
#ifndef __MIBXMLPARSER_H__
#define __MIBXMLPARSER_H__

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iosfwd>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibXMLParser
{
public:
    /***
     * Constructor
     * @param file This is the XML file from which the data structures are extracted.
     * The root node in the XML must be MIB and not empty. Otherwise it'll assert.
     * @return
     */
    MibXMLParser(const std::string &file);
    /***
     * Destructor
     * @return
     */
    ~MibXMLParser();

    /***
    * Create the C++ structures for the given the tree pointer.
    * @param os This is the output stream
    * @param cur This is the point in the tree where the enumeration is defined
    * @return Nothing
    */
    void CreateDoc(std::ostream &os);

    /***
    * This function writes output an enumeration from this point in...
    *  the tree to the given output stream.
    * @param os This is the output stream
    * @param cur This is the point in the tree where the enumeration is defined
    * @return Nothing
    */
    void CreateEnumeration(std::ostream &os, xmlNodePtr cur);

    /***
     * This function creates a 2d array C++ array from the tree.
     * @param os Output stream.
     * @param cur Pointer to definition in the tree.
     * @return Nothing
     */
    void CreateTwoDimensionalArray(std::ostream &os, xmlNodePtr cur);

    /***
     * This creates a C++ scalar from the tree and writes it to the stream.
     * @param os Output stream
     * @param cur Pointer to definition in the tree.
     */
    void CreateScalar(std::ostream &os, xmlNodePtr cur);

    /***
     * This gets the data "as is" from the XSL file and inserts it into the C++ file.
     * @param os Output stream
     * @param cur Pointer to definition in the tree.
     */
    void GetCData(std::ostream &os, xmlNodePtr cur);

    /***
     * A debugging function.
     */
    void parseRecursive (xmlNodePtr cur, int indent);
private:
    xmlDocPtr m_doc; // This the document pointer
    xmlNodePtr m_cur; // This always points to the top of the tree
    static const xmlChar * name;
    static const xmlChar * type;
    static const xmlChar * twoDimensionArray;
    static const xmlChar * array;
    static const xmlChar * entity;
    static const xmlChar * enumeration;
    static const xmlChar * enumValue;
    static const xmlChar * scalar;
    static const xmlChar * noprocess;

};


#endif //  __MIBXMLPARSER_H__
