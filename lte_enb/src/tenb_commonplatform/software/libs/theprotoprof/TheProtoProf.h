///////////////////////////////////////////////////////////////////////////////
//
// TheProtoProf - The Protocol Professor
//
// Processes a stream of text to extract lines representing messaging and
// present them as a message sequence chart.
//
// PP|<timestamp>|<srcLayer>|<dstLayer>|<protocol>|<message>|<procedureId>|<transactionId1>|<transactionId2>|<additionalInfo>
//    e.g.
//    PP|12345|UeL3|NetL3|SM|ActPDPContReq|Activation|00123456789|75|blah blah
//    PP|12347|UeL3|NetL3|SM|ActPDPContReq|Activation|00444444444|82|yatta yatta
//    PP|12350|NetL3|UeL3|SM|ActPDPContAcc|Activation|00123456789|75|guff guff
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TheProtoProf_h_
#define __TheProtoProf_h_

#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "TextColour.h"

namespace threeway
{

	class ColourControl
    {
    public:
        ColourControl (TextAttr ta, TextColour fc, TextColour bc)
            { textAttribute = ta; foregroundColour = fc; backgroundColour = bc; }

        TextAttr textAttribute;
        TextColour foregroundColour;
        TextColour backgroundColour;
    };

    typedef std::map <std::string, ColourControl *> ProtocolColours;

    class TheProtoProf
    {
    
    public:
    
        // IDs for each of the trace line tokens.  Used when setting filters.
        typedef enum
        {
            // Mandatory tokens.
            TOKEN_PREFIX = 0,
            TOKEN_TIMESTAMP,
            TOKEN_SRC_LAYER,
            TOKEN_DST_LAYER,
            TOKEN_PROTOCOL,
            TOKEN_MESSAGE,
            
            // Optional tokens.
            TOKEN_PROCEDURE_ID,
            TOKEN_TRANSACTION_ID_1,
            TOKEN_TRANSACTION_ID_2,
            TOKEN_ADDITIONAL_INFO,
            
            TOKEN_NUM_TOKENS
        } Tokens;

        // Filter modes - for when there are multiple filters.        
        typedef enum
        {
            FILTER_MODE_OR = 0,
            FILTER_MODE_AND
        } FilterMode;
            
        
        static const char * GetExampleFormat() { return "PP|<timestamp>|<srcLayer>|<dstLayer>|<protocol>|<message>|<procedureId>|<transactionId1>|<transactionId2>|<additionalInfo>"; }
        
        /**
         * Construction / destruction.
         */
        TheProtoProf(std::istream& sourceTrace, std::ostream& generatedSequenceChart);
        virtual ~TheProtoProf();
        
        /**
         * Reads everything from sourceTrace and as far as possible, generates the
         * message sequence and outputs to generatedSequenceChart.
         * 
         * Trace is delimited by CR, LF or CR/LF.
         * 
         * Silently discards all lines of trace that do not conform to the
         * Protocol Professor trace format. 
         */
        void ProcessStream();
        
        /**
         * Various configuration options.
         */
        void SetProtocols(const std::string& protocols); // Comma separated list
        void SetIncludeOriginalTrace(bool includeOriginalTrace);
        void SetColumnWidth(unsigned int columnWidth);
        void SetColumnOrder(const std::string& columns); // Comma separated list
        void SetTimestampWidth(unsigned int timestampWidth);
        void SetProtocolWidth(unsigned int protocolWidth);
        void SetMsgsBetweenHeaders(unsigned int msgsBetweenHeaders);
        void SetShowProcedures(bool showProcedures);
        void SetDelimiter(char delimiter);
        void SetColourise(bool colourise);
        void SetListProtocolsOnly(bool listProtocolsOnly);

        /**
         * Set a filter for the specified part of the message.
         * E.g. If token = transactionId1 and tokenFilter = "AB123" then only
         * messages where transactionId1 is AB123 will be shown.  If multiple filters
         * are specified the SetFilterMode function sets whether they are
         * AND'd or OR'd together.
         */
        void SetFilter(unsigned int tokenNum, std::string& filter);
        void SetFilterMode(FilterMode filterMode);

        /**
         * Generate suitable trace strings.
         */
        //static std::string BuildTrace();
        //static std::string BuildTrace(... marqy to define ...);
    
    private:
        
        // Private types.
         
        typedef struct UniqueStringInfoTag
        {
            unsigned int count; // How many times have we seen this string.
            unsigned int userVar; // Use for whatever you like (e.g. level of indentation).
        } UniqueStringInfo;
        
        typedef std::map<std::string,UniqueStringInfo> UniqueStrings;

        // Private functions.

        /**
         * Parse a single line of trace and determine if anything should
         * be output to the generated sequence chart.
         * 
         * \param traceLine The line of trace to parse.
         * \return String to send to generated output.  May be empty to indicate nothing new to output.
         */ 
        void ParseLine(std::string& traceLine);

        /**
         * Check format of a line of trace is OK i.e. that it conforms
         * to the Protocol Professor standard(s). 
         * 
         * \param traceLine The line of trace to check.
         * \return true if format is OK.
         */
        bool IsFormatOK(const std::string& traceLine) const;
        
        /**
         * General string tokeniser.
         * 
         * \param str The string to tokenise.
         * \param delim Characters to delimit by.
         * \param tokens The returned tokens (vector is append to).
         * \return Number of tokens (including any that were in there already).
         */
        unsigned int Tokenise(const std::string & str, const std::string & delim, std::vector<std::string>& tokens);

        /**
         * Work out if the trace line should be included or not.
         * 
         * \param tokens The tokens from the current trace line.
         * \return true if the trace line should be kept.
         */
        bool CheckFilter(const std::vector<std::string>& tokens) const;
        
        /**
         * Check if protocol is to be output based on list of allowed protocols.
         *
         * \param protocol Protocol to check e.g. "RRC"
         * \return true if should be in output stream, false otherwise
         */
        bool ProtocolAllowed(const std::string& protocol);

        /**
         * Look up the layer token in our list of layers that have been used
         * previously.  If not found, add it to the list.
         * 
         * \param layerName Name of the layer as extracted from the trace stream.
         * \return The found or newly created information about the layer.
         */
        UniqueStringInfo& FindLayer(std::string& layerName);

        void ColourOn (const std::string &tokenName) const;
        void ColourOff () const;

        // The input and output streams we are dealing with.
        std::istream&           m_sourceTrace;
        std::ostream&           m_generatedSequenceChart;
        std::istream::pos_type  m_readPos;
        
        // Colourise certain protocols in the output?
        bool m_colourise;

        // State data relating to the message sequences.
        UniqueStrings   m_layers;
        unsigned int    m_layerIndex;
        
        std::map<unsigned int, std::string> m_layerHeaders; // Maintain separate list of layer names.  Index is same as userVar in above container.
        
        // Layout information.
        std::set<std::string> m_protocols;
        bool            m_includeOriginalTrace;
        unsigned int    m_columnWidth;
        unsigned int    m_timestampWidth;
        unsigned int    m_protocolWidth;
        unsigned int    m_procedureWidth;
        unsigned int    m_msgsBetweenHeaders;
        bool            m_showProcedures;
        char            m_delimiter;
        bool            m_listProtocolsOnly;
        
        // Filter information.
        std::string     m_tokenFilters[TOKEN_NUM_TOKENS];
        FilterMode      m_filterMode;

        // Protocols discovered in the trace file.
        std::set<std::string> m_foundProtocols;

		// Protolcol layer colouring information.
	    ProtocolColours m_protocolColours;
    };

}

#endif
