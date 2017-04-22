///////////////////////////////////////////////////////////////////////////////
//
// MibAutoGen.cpp
//
// This is the main file for the MIB C++ header file autogeneration tool.
// The tool accepts an input of the mib.xml file for the relevant
// platform and outputs the corresponding header files for each XML stylesheet
// that is passed. And so...
// It relies on the program 'xsltproc' to perform the XML transforms.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>
#include <iterator>
#include <iostream> // cout
#include <fstream>
#include <sstream>

#include <cassert> // assert macro
#include <cstdlib> // system

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibXMLMerger.h"
#include "MibXMLParser.h"
#include "MibXMLValidate.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

const std::string mergeCmdString = "--merge";
const std::string validateCmdString = "--validate";
const std::string generateCmdString = "--generate";
const std::string xslSuffix = ".xsl";
const std::string xmlSuffix = ".xml";
const std::string cppHeaderSuffix = ".h";
const std::string xsltProg = "xsltproc --output ";


const int params_pos_command = 1;
// --merge file positions
const int params_pos_outputfile = 2;
const int params_pos_firstsnippetfile = 3;

// --generate file positions
const int params_pos_mibxml = 2;
const int params_pos_mibxsd = 3;
const int params_pos_stylesheets = 4; // index of first stylesheet ... everything after must be a stylesheet
const int params_num =  5; // only 1 (5-4) stylesheet may be passed through

///////////////////////////////////////////////////////////////////////////////
// Functions - main!
///////////////////////////////////////////////////////////////////////////////

void printHelp(const std::string &command)
{
    std::cout << "Usage: " << command << ' ' << mergeCmdString << '|' << generateCmdString << std::endl
    << mergeCmdString << " <output merged file name> <mib xml file snippets>*"
    << "       Merge all the mib xml files into one. They should individually validate against mib-simple.xsd" << std::endl
    << validateCmdString << " <mib xml file>  <mib xsd file>"
    << "       Validate xml file against xsd file" << std::endl
    << generateCmdString << " <mib xml file>  <mib xsd file> <mib xsl file>"
    << "       A header file with the same name as the stylesheet will be output for the style sheet" << std::endl;

    return;
}


int main(int argc, char **argv) {
	int result = 0;

    // TODO: Currently we don't check the XML schema here although it is a required parameter. This may change in the future.
    if (argc < params_pos_firstsnippetfile) // because --merge is the shortest command
    {
        printHelp(argv[0]);
        return(1);
    }

    if (mergeCmdString.compare(argv[params_pos_command]) == 0)
    {
        // No need to check for minimum command line arguments, already dealt with.

        MibXMLMerger mibXMLMerger(argv[params_pos_outputfile]);

        for (int index = params_pos_firstsnippetfile; index < argc; ++index)
        {
            mibXMLMerger.Merge(argv[index]);
        }
    }
    else if (validateCmdString.compare(argv[params_pos_command]) == 0)
    {
        // No need to check for minimum command line arguments, already dealt with.

        MibXMLValidate mibXMLValidate(argv[3]);

        result = (mibXMLValidate.IsValid(argv[2]))?0:1;
    }
    else if (generateCmdString.compare(argv[params_pos_command]) == 0)
    {
        // TODO: Check that the passed stylesheets are all unique. This is fixed in the makefile but we should probably check it.
        if (argc < params_num)
        {
            printHelp(argv[0]);
            return(1);
        }
        std::vector<std::string> MibFiles;
        // Check the list of files passed in
        for (int index = params_pos_stylesheets; index < params_num; ++index) {
            // check that file exists
            std::ifstream testFile(argv[index]);
            if (not(testFile.good())) return(1);

            // insert into list
            MibFiles.push_back(argv[index]);
        }

        int result = 0;
        for (std::vector<std::string>::iterator iter = MibFiles.begin(); iter != MibFiles.end(); ++iter)
        {
            // MIB XML file to intermediate XML file with C++ like structure
            std::string xmlFileStr(*iter);
            xmlFileStr = xmlFileStr.replace(xmlFileStr.find(xslSuffix), xmlFileStr.length(),xmlSuffix);
            std::stringstream commandStream;
            commandStream << xsltProg << xmlFileStr
                          << ' ' << *iter
                          << ' ' << argv[params_pos_mibxml];
            // example: xsltproc --output output.xml transform.xsl input.xml
            result = std::system(commandStream.str().c_str());
            assert(result == 0);

            // Perform final stage XML to C++ header file transformation
            std::string headerFileStr(*iter);
            headerFileStr = headerFileStr.replace(headerFileStr.find(xslSuffix), headerFileStr.length(), cppHeaderSuffix);

            std::ofstream headerFile(headerFileStr.c_str());
            MibXMLParser mibXMLParser(xmlFileStr);
            mibXMLParser.CreateDoc(headerFile);
        }
    }
    else
    {
        printHelp(argv[0]);
        return(1);
    }


    return (result);
}



