///////////////////////////////////////////////////////////////////////////////
//
// CliUserInput.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include "fstream"

#include <system/Trace.h>
#include <system/SerialisationIds.h>
#include <system/TimerEngine.h>
#include <system/ThreadWithQueue.h>
#include <messaging/messages/common/RegisterEntityCnf.h>
#include <messaging/messages/cli/CliExecuteCmdReq.h>
#include <messaging/messages/cli/CliExecuteCmdCnf.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliApplication.h"
#include "CliTypes.h"
#include "CliEvents.h"
#include "CliUserInput.h"
#include "CliCmdFileMgr.h"


using namespace std;
using namespace boost;
using namespace threeway;



int UserInput::FindMatchingCommands(const string & currentCommandLine, set<string> &matches)
{
    ENTER();

    RSYS_ASSERT(matches.empty());

    set<string> availableCommands;

    CliCmdFileMgr::GetInstance().ListAllMatchingCommands( availableCommands, currentCommandLine);

    set<string>::iterator i;

    for (i = availableCommands.begin(); i != availableCommands.end(); i++)
    {
        if (i->compare(0, currentCommandLine.size(), currentCommandLine) == 0)
        {
            bool matchNamespace = (string::npos == currentCommandLine.find_first_of('.'));

            string stringToAddToMatches;

            if(matchNamespace)
            {
                size_t posOfNextDot = i->find_first_of('.', currentCommandLine.size() + 1);

                stringToAddToMatches = i->substr(0, posOfNextDot + 1);
            }
            else
            {
                stringToAddToMatches = *i;
            }

            TRACE_PRINTF("Added %s to full matching commands set.", stringToAddToMatches.c_str() );

            matches.insert( stringToAddToMatches );
        }
    }

    RETURN (matches.size());
}

UserInput::UserInput( ) :
    m_state(GETTING_CHARS),
    m_historyPos(0),
    m_cursorPos(0),
    m_newCursorPos(0),
    m_currentLineLength(0),
    m_lastLineLength(0)
{
    ENTER();

    EXIT();
}

UserInput::~UserInput()
{
    ENTER();
    EXIT();
}


bool UserInput::GetUserInputLine( u8 c, string &commandLine, const string & prompt )
{
    ENTER();

    bool done = false;
    static int tabCount = 0;

    if ((c != TAB) && (tabCount > 0))
    {
        tabCount = 0;
        TRACE_PRINTF_LEV(TRACE_VERBOSE, "Reset Tab Count");
    }

    int keyType = DecodeKey(c);
    m_currentLineLength = m_inputLine.length();
    m_newCursorPos = m_cursorPos;

    switch (keyType)
    {
        case NORMAL_KEY:
            switch ((u32) c)
            {
                case CARRIAGE_RETURN:
                case LINE_FEED:
                    done = true;
                    break;

                case BS:
                case BS2:
                    if (m_cursorPos)
                    {
                        m_newCursorPos--;
                        m_inputLine = m_inputLine.erase(m_newCursorPos, 1);
                    }
                    break;

                case TAB:
                    HandleTab (++tabCount, prompt);
                    break;

                default:
                    if (m_cursorPos < m_currentLineLength)
                    {
                        m_inputLine.insert(m_newCursorPos++, 1, (char) c);
                    }
                    else
                    {
                        m_newCursorPos++;
                        m_inputLine.push_back(c);
                    }
                    break;
            }
            break;

        case CURSOR_UP:
        case CURSOR_DOWN:
        case CURSOR_LEFT:
        case CURSOR_RIGHT:
            HandleCursor(keyType) ;
            break;

        case HOME:
            m_newCursorPos = 0;
            break;

        case END:
            m_newCursorPos = m_currentLineLength;
            break;

        case DELETE:
            if (m_currentLineLength && (m_cursorPos < m_currentLineLength))
            {
                m_inputLine = m_inputLine.erase(m_newCursorPos, 1);
            }
            break;

        default:
            break;
    }

    if (done)
    {
    	if (m_inputLine.size())
    	{
    		m_userInputHistory.push_front(m_inputLine);
    	    if (m_userInputHistory.size() > COMMAND_LINE_HISTORY_SIZE)
    	    {
    	        m_userInputHistory.pop_back();
    	    }
    	}
    	m_historyPos = -1 ;
        tabCount = 0;
        m_cursorPos = 0;
        m_newCursorPos = 0;
        commandLine = m_inputLine;
        m_inputLine.clear();
    }
    else
    {
   	   UpdateUserInputLine(m_inputLine, m_cursorPos, m_newCursorPos, m_currentLineLength);
   	   m_cursorPos = m_newCursorPos ;
    }

    RETURN(done);
}


KeyEventType UserInput::DecodeKey(u8 c)
{
    ENTER();

    KeyEventType keyEvent = NO_KEY;

    switch (m_state)
    {
        case GETTING_EDIT_KEY:
            switch ((u32) c)
            {
                case CURSOR_UP_KEY:
                    keyEvent = CURSOR_UP ;
                    m_state = GETTING_CHARS ;
                    break;

                case CURSOR_DOWN_KEY:
                    keyEvent = CURSOR_DOWN ;
                    m_state = GETTING_CHARS;
                    break;

                case CURSOR_LEFT_KEY:
                    keyEvent = CURSOR_LEFT ;
                    m_state = GETTING_CHARS;
                    break;

                case CURSOR_RIGHT_KEY:
                    keyEvent = CURSOR_RIGHT ;
                    m_state = GETTING_CHARS;
                    break;

                case INSERT_KEY:
                    keyEvent = INSERT;
                    m_state = COMPLETING_ESC_SEQUENCE ; // 4 Byte sequence
                    break ;

                case DELETE_KEY:
                    keyEvent = DELETE;
                    m_state = COMPLETING_ESC_SEQUENCE ; // 4 Byte sequence
                    break ;

                case HOME_KEY:
                    keyEvent = HOME;
                    m_state = GETTING_CHARS ;
                    break ;

                case END_KEY:
                    keyEvent = END;
                    m_state = GETTING_CHARS ;
                    break ;

                default:
                    keyEvent = NO_KEY ;
                    m_state = GETTING_CHARS;
            }
            break;

        case GETTING_ESC_SEQUENCE:
            switch ((u32) c)
            {
                case EDIT_KEY:
                case OTHER_EDIT_KEY:
                    keyEvent = NO_KEY ;
                    m_state = GETTING_EDIT_KEY;
                    break;

                default:
                    keyEvent = NO_KEY ;
                    m_state = GETTING_CHARS;
            }
            break;

        case GETTING_CHARS:
            if ((u32)c == ESC)
            {
                m_state = GETTING_ESC_SEQUENCE;
                keyEvent = NO_KEY ;
            }
            else
            {
                keyEvent = NORMAL_KEY ;
            }
            break ;

        case COMPLETING_ESC_SEQUENCE:
            m_state = GETTING_CHARS ;
            keyEvent = NO_KEY ;
            break ;
    }

    RETURN(keyEvent) ;
}

void UserInput::Prompt( const string & prompt)
{
    ENTER();

    TRACE_PRINTF_CONSOLE("%s",prompt.c_str());

    if (!m_inputLine.empty())
    {
        // Previous value for current position is invalidated because we've moved to the
        // beginning of a new line! The following shenanigans will rewrite the current
        // user input then reset the current cursor position.
        m_newCursorPos = m_cursorPos ;
        m_cursorPos = 0 ;
        UpdateUserInputLine(m_inputLine, m_cursorPos, m_newCursorPos, m_currentLineLength) ;
        m_cursorPos = m_newCursorPos ;
    }
    cout.flush();

    EXIT();
}



void UserInput::UpdateUserInputLine(const string &inputLine, u32 cursorPos,
                                    u32 newCursorPos, u32 currentLineLength)
{
    ENTER() ;

    ostringstream outputString;
    string cliStr;
    u32 newLineLength = inputLine.length();
    u32 firstChangedChar = 0;

    TRACE_PRINTF_LEV(TRACE_VERBOSE, "inputLine=%s, displayLine = %s, cursorPos=%"PRIu32", newCursorPos=%"PRIu32", currentLineLength=%"PRIu32", newLineLength %"PRIu32"",
                                    inputLine.c_str(), m_displayLine.c_str(), cursorPos, newCursorPos, currentLineLength, newLineLength);

    // Find first character of new line which differs from previous
    u32 charsToCompare = min (currentLineLength, newLineLength) ;
    TRACE_PRINTF_LEV(TRACE_VERBOSE, "charsToCompare %"PRIu32"", charsToCompare);
    for (u32 index = 0; index < charsToCompare; index++)
    {
    	firstChangedChar = index ;
    	if (inputLine[index] != m_displayLine[index])
    	{
    		break ;
    	}
    	else
    	{
    		firstChangedChar++;
    	}
    }
    TRACE_PRINTF_LEV(TRACE_VERBOSE, "FirstChangedChar = %"PRId32, firstChangedChar);

   	// Move cursor to first differing character in line.
   	u32 movement = abs ((int)cursorPos - (int)firstChangedChar);
   	string movementString = CURSOR_LEFT_STRING ;
   	if (firstChangedChar > cursorPos)
   	{
   		movementString = CURSOR_RIGHT_STRING ;
   		TRACE_PRINTF_LEV(TRACE_VERBOSE, "Move %"PRIu32" characters right", movement);
   	}
   	else
   	{
   	    TRACE_PRINTF_LEV(TRACE_VERBOSE, "Move %"PRIu32" characters left", movement);
   	}

   	for (u32 count = 0; count < movement; count++)
   	{
   		outputString << movementString ;
   	}


   	// If line we're displaying is shorter than what was there before we
   	// need to blank the old text
   	if (newLineLength < currentLineLength)
   	{
   		u32 charsToBlank = currentLineLength - firstChangedChar ;
   		for (u32 count = 0; count < charsToBlank; count++)
   		{
   			outputString << " " ;
   		}

   		for (u32 count = 0; count < charsToBlank; count++)
   		{
   			outputString << CURSOR_LEFT_STRING ;
   		}
   	}

    // Append the new display text
    outputString << inputLine.substr(firstChangedChar) ;

    // And finally position the cursor.
    for (u32 count = 0; count < newLineLength - newCursorPos; count++)
    {
        outputString << CURSOR_LEFT_STRING ;
    }

    cliStr = outputString.str();
    TRACE_PRINTF_CONSOLE_WITHOUT_NEWLINE("%s",cliStr.c_str());
    cout.flush();
    TRACE_PRINTF_LEV(TRACE_VERBOSE, "Characters in update string = %zu", outputString.str().size());
    m_displayLine = inputLine ;
    EXIT();
}

void UserInput::HandleTab(int tabCount, const string & prompt )
{
    ENTER();

    set<string> matches;

    string partialCommandUptoCursor = m_inputLine.substr(0, m_newCursorPos);

    TRACE_PRINTF("Tab match for input line '%s'", m_inputLine.c_str());

    FindMatchingCommands( partialCommandUptoCursor, matches);

    if( !matches.empty() )
    {
        TRACE_PRINTF("Matches found = % zi, tab count = %d", matches.size(), tabCount);

        for (set<string>::iterator i = matches.begin(); i != matches.end(); i++)
        {
            TRACE_PRINTF("%s", i->c_str());
        }

        if(matches.size() > 1)
        {
            // Can we go further with the matches found?
            size_t shortestMatchedLength = matches.begin()->size();

            set<string>::iterator i = matches.begin();

            while( i != matches.end() )
            {
                string s1 = *i;

                i++;

                if(i != matches.end())
                {
                    string s2 = *i;

                    TRACE_PRINTF("Compare %s vs %s, (matched length was %zu)", s1.c_str(), s2.c_str(), shortestMatchedLength );

                    size_t matchedLength = min( s1.size(), s2.size() );

                    matchedLength = min( matchedLength, shortestMatchedLength);

                    while( 0 != s1.compare( 0, matchedLength, s2, 0, matchedLength ) && matchedLength > 0)
                    {
                        TRACE_PRINTF("Comparison %s; %s; %s. MatchedLength=%zu", partialCommandUptoCursor.c_str(), s1.c_str(), s2.c_str(), matchedLength );
                        RSYS_ASSERT_PRINTF(matchedLength >= partialCommandUptoCursor.size(), "Comparison error! %s; %s; %s. MatchedLength=%zu", partialCommandUptoCursor.c_str(), s1.c_str(), s2.c_str(), matchedLength );
                        matchedLength--;
                    }

                    shortestMatchedLength = min(shortestMatchedLength, matchedLength);
                }
            }

            if(shortestMatchedLength > partialCommandUptoCursor.size())
            {
                TRACE_PRINTF("Replaced %s with %s", partialCommandUptoCursor.c_str(), matches.begin()->substr(0, shortestMatchedLength).c_str());

                m_inputLine.replace (0, partialCommandUptoCursor.size(), matches.begin()->substr(0, shortestMatchedLength));
                m_newCursorPos = m_inputLine.length();
            }
            else if (tabCount > 1)
            {
                for (set<string>::iterator i = matches.begin(); i != matches.end(); i++)
                {
                    TRACE_PRINTF_CONSOLE_WITHOUT_NEWLINE("\n\t%s",(*i).c_str());
                }

                // Hack to force entire input line to be redisplayed as we've
                // moved to a new line and can't rely on what's already on the
                // screen!
                m_displayLine.clear();
                Prompt( prompt ) ;
            }
        }
        else if (matches.size() == 1)
        {
            string match = *matches.begin();

            bool matchedCompleteCommand = match.size() == partialCommandUptoCursor.size();

            if( matchedCompleteCommand )
            {
                CliCmdFile cliCmdFile(match.c_str() );

                if( !cliCmdFile.GetShortDescription().empty() )
                {
                    TRACE_PRINTF_CONSOLE("\n\tUsage: %s",cliCmdFile.GetShortDescription().c_str());

                    m_inputLine.insert ( partialCommandUptoCursor.size(), " ");
                    m_cursorPos = m_newCursorPos = m_inputLine.length();

                    TRACE_PRINTF("Input ine=\"%s\", cursor position = %"PRIu32"",m_inputLine.c_str(), m_newCursorPos );
                    m_displayLine.clear();
                    Prompt( prompt ) ;
                }
            }
            else
            {
                m_inputLine.replace (0, partialCommandUptoCursor.size(), match);
                m_newCursorPos = m_inputLine.length();
            }
        }
    }

    EXIT();
}

void UserInput::HandleCursor(int keyEvent)
{
    ENTER();
    int historyBufferSize = m_userInputHistory.size() ;

    if ((keyEvent == CURSOR_LEFT) && (m_cursorPos > 0))
    {
        m_newCursorPos--;
    }
    else if ((keyEvent == CURSOR_RIGHT) && (m_cursorPos < m_currentLineLength))
    {
        m_newCursorPos++;
    }
    else if (((keyEvent == CURSOR_UP) || (keyEvent == CURSOR_DOWN)) && historyBufferSize)
    {
        if (keyEvent == CURSOR_UP && m_historyPos < (historyBufferSize-1))
        {
            m_historyPos++;
        }
        else if ( (keyEvent == CURSOR_DOWN) && (m_historyPos >= 0))
        {
            m_historyPos--;
        }

        TRACE_PRINTF("%d Commands in command history buffer, index = %d", historyBufferSize, m_historyPos);
        for (u32 cmdCount = 0; cmdCount < (u32)historyBufferSize; cmdCount++)
        {
            TRACE_PRINTF("Command History entry %" PRIu32 " = %s", cmdCount, m_userInputHistory[cmdCount].c_str());
        }

        if (m_historyPos >= 0)
        {
        	m_inputLine = m_userInputHistory[m_historyPos];
        }
        else
        {
        	m_inputLine.clear();
        }
        m_newCursorPos = m_inputLine.length();
    }

    EXIT();
}

int TokeniseString(string inputString, StringVector& tokens, bool ignoreDot)
{
    ENTER();

    TRACE_PRINTF("Tokenising string %s", inputString.c_str());
    if (inputString.size() > 0)
    {
        string::size_type delimPos = string::npos;
        string::size_type spaceDelimPos = string::npos;
        string::size_type dotDelimPos = string::npos;
        bool gotDot = false ;

        do
        {
            TRACE_PRINTF("Processing string %s", inputString.c_str());
            spaceDelimPos = inputString.find(" ");
            if ((!gotDot) && (!ignoreDot))
            {
                dotDelimPos = inputString.find(".");
            }
            else
            {
                dotDelimPos = string::npos ;
            }

            TRACE_PRINTF("spaceDelimPos = %" PRIu32 ", dotDelimPos = %" PRIu32, (u32)spaceDelimPos, (u32)dotDelimPos);

            if (spaceDelimPos == string::npos)
            {
                delimPos = dotDelimPos ;
                TRACE_PRINTF("No space found, delimPos = %" PRIu32, (u32)delimPos);
            }
            else if (dotDelimPos == string::npos)
            {
                delimPos = spaceDelimPos ;
                TRACE_PRINTF("No dot found, delimPos = %" PRIu32, (u32)delimPos);
            }
            else
            {
                delimPos = min (spaceDelimPos, dotDelimPos);
                TRACE_PRINTF("Space & dot found, delimPos = %" PRIu32, (u32)delimPos);
            }

            if (delimPos == dotDelimPos)
            {
                gotDot = true ;
            }

            if (delimPos == 0)
            {
                // Leading space (or possibly dot)!
                TRACE_PRINTF ("Leading Space found");
                inputString = inputString.substr(delimPos + 1);
            }
            else
            {
                TRACE_PRINTF("Adding %s to token vector", inputString.substr(0, delimPos).c_str());
                tokens.push_back(inputString.substr(0, delimPos)) ;
                inputString = inputString.substr(delimPos + 1);
            }
        } while (delimPos != string::npos) ;

        TRACE_PRINTF("Found %" PRIu32 " tokens", (u32)tokens.size());
        for (u32 count = 0; count < tokens.size(); count++)
        {
            TRACE_PRINTF("%s", tokens[count].c_str());
        }
    }

    RETURN (tokens.size()) ;
}
