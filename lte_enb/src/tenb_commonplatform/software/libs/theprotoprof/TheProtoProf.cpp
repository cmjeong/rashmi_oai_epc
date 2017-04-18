///////////////////////////////////////////////////////////////////////////////
//
// TheProtoProf.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "TheProtoProf.h"
#include "TextColour.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const char VALID_LINE_PREFIX[] = "PP|";
static const unsigned int VALID_LINE_MIN_TOKENS = 6;
static const unsigned int LAYOUT_COLUMN_WIDTH_DEFAULT = 25;
static const unsigned int LAYOUT_COLUMN_WIDTH_MIN = 5;
static const unsigned int LAYOUT_TIMESTAMP_WIDTH_DEFAULT = 13;
static const unsigned int LAYOUT_PROTOCOL_WIDTH_DEFAULT = 8;
static const unsigned int LAYOUT_PROCEDURE_WIDTH_DEFAULT = 15;
static const unsigned int LAYOUT_MAX_LINES_BETWEEN_HEADERS = 20;


///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

TheProtoProf::TheProtoProf(istream& sourceTrace, ostream& generatedSequenceChart) :
    m_sourceTrace(sourceTrace),
    m_generatedSequenceChart(generatedSequenceChart),
    m_colourise(false),
    m_readPos(EOF),
    m_layerIndex(0),
    m_includeOriginalTrace(false),
    m_columnWidth(LAYOUT_COLUMN_WIDTH_DEFAULT),
    m_timestampWidth(LAYOUT_TIMESTAMP_WIDTH_DEFAULT),
    m_protocolWidth(LAYOUT_PROTOCOL_WIDTH_DEFAULT),
    m_procedureWidth(LAYOUT_PROCEDURE_WIDTH_DEFAULT),
    m_msgsBetweenHeaders(LAYOUT_MAX_LINES_BETWEEN_HEADERS),
    m_showProcedures(false),
    m_delimiter('|'),
    m_listProtocolsOnly(false),
    m_filterMode(FILTER_MODE_OR)
{
    // Put these onto command line or into config file?
    m_protocolColours.insert (std::make_pair ("RRC", new ColourControl (TA_BRIGHT, TC_RED, TC_BLACK)));
    m_protocolColours.insert (std::make_pair ("MM", new ColourControl (TA_BRIGHT, TC_GREEN, TC_BLACK)));
    m_protocolColours.insert (std::make_pair ("CC", new ColourControl (TA_BRIGHT, TC_BLUE, TC_BLACK)));
    m_protocolColours.insert (std::make_pair ("GMM", new ColourControl (TA_BRIGHT, TC_YELLOW, TC_BLACK)));
    m_protocolColours.insert (std::make_pair ("SM", new ColourControl (TA_BRIGHT, TC_MAGENTA, TC_BLACK)));
    m_protocolColours.insert (std::make_pair ("SMS", new ColourControl (TA_BRIGHT, TC_CYAN, TC_BLACK)));
    m_protocolColours.insert (std::make_pair ("MAP", new ColourControl (TA_BRIGHT, TC_RED, TC_BLACK)));
    m_protocolColours.insert (std::make_pair ("RabmSm", new ColourControl (TA_BRIGHT, TC_MAGENTA, TC_BLACK)));
    m_protocolColours.insert (std::make_pair ("GgsnSm", new ColourControl (TA_BRIGHT, TC_MAGENTA, TC_BLACK)));
    m_protocolColours.insert (std::make_pair ("GmmSm", new ColourControl (TA_BRIGHT, TC_MAGENTA, TC_BLACK)));
}

TheProtoProf::~TheProtoProf()
{
}

void TheProtoProf::ProcessStream()
{
    string traceLine;

//    if(m_readPos != EOF)
//    {
//        m_sourceTrace.seekg(m_readPos, ios::beg);
//    }

    while(!m_sourceTrace.eof())
    {
        getline (m_sourceTrace, traceLine);

        ParseLine(traceLine);
    }

    if(m_listProtocolsOnly)
    {
        for(set<string>::const_iterator iter = m_foundProtocols.begin(); iter != m_foundProtocols.end(); ++iter)
        {
            TRACE_PRINTF("%s\n",(*iter).c_str());
        }
    }

//    m_readPos = m_sourceTrace.tellg();

}

void TheProtoProf::SetProtocols(const std::string& protocols)
{
    vector<string> protocolVector;
    Tokenise(protocols, ",", protocolVector);

    for(unsigned int i = 0; i < protocolVector.size(); i++)
    {
        m_protocols.insert(protocolVector.at(i));
    }
}

void TheProtoProf::SetIncludeOriginalTrace(bool includeOriginalTrace)
{
    m_includeOriginalTrace = includeOriginalTrace;
}

void TheProtoProf::SetColumnWidth(unsigned int columnWidth)
{
    if(columnWidth >= LAYOUT_COLUMN_WIDTH_MIN)
    {
        m_columnWidth = columnWidth;
    }
}

void TheProtoProf::SetColumnOrder(const std::string& columns)
{
    vector<string> columnsVector;
    Tokenise(columns, ",", columnsVector);

    for(unsigned int i = 0; i < columnsVector.size(); i++)
    {
        FindLayer(columnsVector.at(i));
    }
}

void TheProtoProf::SetTimestampWidth(unsigned int timestampWidth)
{
    m_timestampWidth = timestampWidth;
}

void TheProtoProf::SetProtocolWidth(unsigned int protocolWidth)
{
    m_protocolWidth = protocolWidth;
}

void TheProtoProf::SetMsgsBetweenHeaders(unsigned int msgsBetweenHeaders)
{
    m_msgsBetweenHeaders = msgsBetweenHeaders;
}

void TheProtoProf::SetShowProcedures(bool showProcedures)
{
    m_showProcedures = showProcedures;
}

void TheProtoProf::SetDelimiter(char delimiter)
{
    m_delimiter = delimiter;
}

void TheProtoProf::SetColourise(bool colourise)
{
    m_colourise = colourise;
}

void TheProtoProf::SetListProtocolsOnly(bool listProtocolsOnly)
{
    m_listProtocolsOnly = listProtocolsOnly;
}

void TheProtoProf::SetFilter(unsigned int tokenNum, std::string& filter)
{
    if(tokenNum < TOKEN_NUM_TOKENS)
    {
        m_tokenFilters[tokenNum] = filter;
    }
}

void TheProtoProf::SetFilterMode(FilterMode filterMode)
{
    m_filterMode = filterMode;
}

void TheProtoProf::ParseLine(string& traceLine)
{
    bool newLayer = false;
    static unsigned int outputLinesSinceHdrs = 0;
    ostringstream mscLine;

    traceLine = traceLine.substr(0, traceLine.find_first_of("\n\r")); // Strip any trailing \n \r

    if(!IsFormatOK(traceLine))
    {
        if(!m_listProtocolsOnly && (m_includeOriginalTrace || (traceLine.find("TRACE FILE ROTATED") != string::npos)))
        {
            m_generatedSequenceChart << traceLine << endl;
        }

        return;
    }

    vector<string> tokens;
    unsigned int numTokens = Tokenise(traceLine, string() + m_delimiter, tokens);

    if(numTokens < VALID_LINE_MIN_TOKENS)
    {
        // There aren't enough tokens on the line.
        m_generatedSequenceChart << "Invalid PP trace statement - insufficient tokens" << endl;
        return;
    }

    if(m_listProtocolsOnly)
    {
        m_foundProtocols.insert(tokens[TOKEN_PROTOCOL]);
        return;
    }

    if(!CheckFilter(tokens))
    {
        // Silently return.
        return;
    }

    if(!ProtocolAllowed(tokens[TOKEN_PROTOCOL]))
    {
        // Silently return.
        return;
    }

    // If the message starts with SERIALISATION_ID_ then remove it.
    if(tokens[TOKEN_MESSAGE].compare(0, 17, "SERIALISATION_ID_") == 0)
    {
        tokens[TOKEN_MESSAGE] = tokens[TOKEN_MESSAGE].substr(17);
    }

    // Look for optional tokens.
    string transactionId1;
    string transactionId2;
    if(numTokens > TOKEN_TRANSACTION_ID_1)
    {
        transactionId1 = tokens[TOKEN_TRANSACTION_ID_1];
    }

    if(numTokens > TOKEN_TRANSACTION_ID_2)
    {
        transactionId2 = tokens[TOKEN_TRANSACTION_ID_2];
    }

    // Look for existing src and dst layers and use same indentation.
    UniqueStringInfo& srcLayerInfo = FindLayer(tokens[TOKEN_SRC_LAYER]);
    UniqueStringInfo& dstLayerInfo = FindLayer(tokens[TOKEN_DST_LAYER]);

    if(srcLayerInfo.count == 0 || dstLayerInfo.count == 0)
    {
        // Haven't seen at least one of these layers before so tag as new layer
        // so we output new headers below.
        newLayer = true;
    }

    // Work out some sizes and lengths for the message layout.
    unsigned int columnDiff = m_columnWidth * (unsigned int)abs((int)srcLayerInfo.userVar - (int)dstLayerInfo.userVar);
    unsigned int messageLen = tokens[TOKEN_MESSAGE].length();
    unsigned int paddingReqd = messageLen < columnDiff - 3 ?
                                    columnDiff - 3 - messageLen :
                                    0;

    // Output the timestamp and protocol at the start of the line.
    mscLine.width(m_timestampWidth);
    mscLine << left << tokens[TOKEN_TIMESTAMP].substr(0, m_timestampWidth-1);
    mscLine.width(m_protocolWidth);
    mscLine << left << tokens[TOKEN_PROTOCOL].substr(0, m_protocolWidth-1);

    if(m_showProcedures)
    {
        if(numTokens > TOKEN_PROCEDURE_ID)
        {
            mscLine.width(m_procedureWidth);
            mscLine << left << tokens[TOKEN_PROCEDURE_ID].substr(0, m_procedureWidth-1);
        }
        else
        {
            mscLine << string(m_procedureWidth, ' ');
        }
    }

    // Calculate the indent based on the layer.
    unsigned int indent = dstLayerInfo.userVar * m_columnWidth;
    if(srcLayerInfo.userVar < dstLayerInfo.userVar)
    {
        indent = srcLayerInfo.userVar * m_columnWidth;
    }

    mscLine << " " << string(indent, ' '); // Pads to start of correct column.

    // Display the message with arrows.
    if(srcLayerInfo.userVar < dstLayerInfo.userVar)
    {
        // We have a message that will look like:
        //        NetL3                  UeL3
        //         ------The Message----->
        mscLine << string(1 + (paddingReqd-paddingReqd/2), '-');
        mscLine << tokens[TOKEN_MESSAGE].substr(0, columnDiff - 3);
        mscLine << string(1 + paddingReqd/2, '-');
        mscLine << ">";
    }
    else if(dstLayerInfo.userVar < srcLayerInfo.userVar)
    {
        // We have a message that will look like:
        //        NetL3                  UeL3
        //         <-----The Message------
        mscLine << "<";
        mscLine << string(1 + paddingReqd/2, '-');
        mscLine << tokens[TOKEN_MESSAGE].substr(0, columnDiff - 3);
        mscLine << string(1 + (paddingReqd-paddingReqd/2), '-');
    }
    else
    {
        // Same layer.  We have a message that will look like:
        //        NetL3                  UeL3
        //   < The Message >
        mscLine << "< " << tokens[TOKEN_MESSAGE].substr(0, columnDiff - 4);
        mscLine << " >";
    }

    //m_generatedSequenceChart << "SrcLayerIndex=" << srcLayerInfo.userVar << ", DstLayerIndex=" << dstLayerInfo.userVar << ", Timestamp=" << tokens[TOKEN_TIMESTAMP] << ", SrcLayer=" << tokens[TOKEN_SRC_LAYER] << ", DstLayer=" << tokens[TOKEN_DST_LAYER] << ", Protocol=" << tokens[TOKEN_PROTOCOL] << ", Message=" << tokens[TOKEN_MESSAGE] << ", TransactionId=" << transactionId1;

    // Add on any additional trace.
    if(numTokens > TOKEN_ADDITIONAL_INFO)
    {
        string additionalInfo;
        for(unsigned int i = TOKEN_ADDITIONAL_INFO; i < numTokens; i++)
        {
            if(!tokens[i].empty())
            {
                additionalInfo += tokens[i] + " ";
            }
        }
        if(!additionalInfo.empty())
        {
            mscLine << " : " << additionalInfo;
        }
    }

    // Work out if we need to output new column (layer) headers.
    if(newLayer || (outputLinesSinceHdrs == 0))
    {
        // Found a new layer so print headers before the MSC line.
        m_generatedSequenceChart << string(m_timestampWidth + m_protocolWidth, ' ');
        if(m_showProcedures)
        {
            m_generatedSequenceChart << string(m_procedureWidth, ' '); // Skip procedure columns.
        }

        string truncatedLayerName;
        for(unsigned int layerIndex = 0; layerIndex < m_layerIndex; layerIndex++)
        {
            truncatedLayerName = m_layerHeaders[layerIndex].substr(0, m_columnWidth - 1);

            m_generatedSequenceChart << truncatedLayerName;

            // Add some space after if not last column.
            if(layerIndex != m_layerIndex - 1)
                m_generatedSequenceChart << std::string(m_columnWidth - truncatedLayerName.length(), ' ');
        }
        m_generatedSequenceChart << endl;
    }

    outputLinesSinceHdrs++;
    if(m_msgsBetweenHeaders == outputLinesSinceHdrs)
    {
        outputLinesSinceHdrs = 0;
    }


    if(m_colourise)
    {
        ColourOn (tokens[TOKEN_PROTOCOL]);
    }

    m_generatedSequenceChart << mscLine.str() << endl;

    if(m_colourise)
    {
        ColourOff ();
    }

    // If there is a transactionId1 then output it on next line.
    if(!transactionId1.empty() || !transactionId2.empty())
    {
        ostringstream transactionIdLine;
        transactionIdLine << string(m_timestampWidth + m_protocolWidth, ' '); // Skip timestamp and protocol columns.
        if(m_showProcedures)
        {
            transactionIdLine << string(m_procedureWidth, ' '); // Skip procedure columns.
        }
        transactionIdLine << " " << string(indent, ' '); // Pads to start of correct column.
        transactionIdLine << " (";
        if(transactionId1.empty())
        {
            transactionIdLine << "[empty]";
        }
        else
        {
            transactionIdLine << transactionId1;
        }
        if(transactionId2.empty())
        {
            transactionIdLine << ", [empty])";
        }
        else
        {
            transactionIdLine << ", " << transactionId2 << ")";
        }
        m_generatedSequenceChart << transactionIdLine.str() << endl;
    }
}

bool TheProtoProf::IsFormatOK(const string& traceLine) const
{
    if(traceLine.find(VALID_LINE_PREFIX) == 0)
    {
        return true;
    }

    return false;
}

unsigned int TheProtoProf::Tokenise(const string & str, const string & delim, vector<string>& tokens)
{
    if(str.length() == 0)
    {
        return 0;
    }

    size_t p0 = 0;
    size_t p1 = 0;
    while(p1 != string::npos)
    {
        p1 = str.find_first_of(delim, p0); // Returns npos if not found.
        string token = str.substr(p0, (p1 == string::npos) ? string::npos : (p1 - p0)); // For the last token, p1 will be npos.
        tokens.push_back(token);
        p0 = p1 + 1;
    }

    return tokens.size();
}

bool TheProtoProf::CheckFilter(const vector<string>& tokens) const
{
    bool atLeastOneDidntMatch = false;
    bool atLeastOneMatched = false;

    unsigned int numTokens = tokens.size();

    // Get the minimum of the number of tokens provided and the maximum number that are relevant.
    numTokens = numTokens > TOKEN_NUM_TOKENS ? TOKEN_NUM_TOKENS : numTokens;

    for(unsigned int token = TOKEN_PREFIX; token < numTokens; token++)
    {
        if(!m_tokenFilters[token].empty())
        {
            // There is a filter for this token.  See if it matches the token provided.
            if(tokens[token] == m_tokenFilters[token])
            {
                atLeastOneMatched = true;
            }
            else
            {
                atLeastOneDidntMatch = true;
            }
        }
    }

    bool noFilters = (atLeastOneDidntMatch == false) && (atLeastOneMatched == false);

    if(noFilters)
    {
        // Don't filter it out if there weren't any filters!
        return true;
    }

    if(m_filterMode == FILTER_MODE_OR)
    {
        // OR mode so as long as one matched, keep it.
        return atLeastOneMatched;
    }

    // Must be AND mode.  So check that all filters matched.
    return atLeastOneMatched && !atLeastOneDidntMatch;
}

bool TheProtoProf::ProtocolAllowed(const string& protocol)
{
    if(m_protocols.empty())
    {
        // If none specified, allow all.
        return true;
    }

    if(m_protocols.find(protocol) != m_protocols.end())
    {
        // Only allow if in list.
        return true;
    }

    return false;
}

TheProtoProf::UniqueStringInfo& TheProtoProf::FindLayer(string& layerName)
{
    UniqueStrings::iterator it = m_layers.find(layerName);
    if(it == m_layers.end())
    {
        UniqueStringInfo layerInfo;
        layerInfo.count = 0;
        layerInfo.userVar = m_layerIndex++;
        // Not found so add it.
        m_layers[layerName] = layerInfo;
        m_layerHeaders[layerInfo.userVar] = layerName;

        return m_layers[layerName];
    }

    // Found it, return ref.
    it->second.count++;
    return it->second;
}

void TheProtoProf::ColourOn (const string &tokenName) const
{
    ProtocolColours::const_iterator foundToken = m_protocolColours.find (tokenName);
    if (foundToken != m_protocolColours.end ())
    {
        const ColourControl &cc = *(foundToken->second);
        textColour (
            cc.textAttribute,
            cc.foregroundColour,
            cc.backgroundColour);
    }//end if
}

void TheProtoProf::ColourOff () const
{
    textColour (TA_RESET, TC_WHITE, TC_BLACK);
}

} // namespace
