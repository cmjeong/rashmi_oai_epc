////////////////////////////////////////////////////////////////////////////////
//
// CliUserInput.h
//
// Character by character user input, editing, and history fo CLI app
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef CLIUSERINPUT_H_
#define CLIUSERINPUT_H_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <string.h>
#include <iostream>
#include <sstream>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliTypes.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * User Input class
 */
class UserInput
{
public:
    UserInput();
    virtual ~UserInput();

    /**
     * Get a line of user input using unbuffered input.
     * /param &commandLine  Completed line of user input gets put in here.
     */
    bool GetUserInputLine( u8 c,
                          string &commandLine,
                          const string & prompt );

private:

    typedef enum UserInputStateTag
    {
        GETTING_CHARS,
        GETTING_ESC_SEQUENCE,
        GETTING_EDIT_KEY,
        COMPLETING_ESC_SEQUENCE
    } UserInputState;

    UserInputState m_state;

    // Command History
    static const u32 COMMAND_LINE_HISTORY_SIZE = 10;
    deque<string> m_userInputHistory;
    int m_historyPos;

    /**
     * User input built up and edited in this string.
     */
    string m_inputLine;

    /*
     * Stuff used to display user input line when characters inserted/deleted,
     * cursor moved, etc, etc, etc.
     */
    string m_displayLine;
    u32 m_cursorPos;
    u32 m_newCursorPos;
    u32 m_currentLineLength;
    u32 m_lastLineLength;

    // Redisplay the users input string after an edit or cursor move.
    void UpdateUserInputLine(const string &inputLine, u32 cursorPos,
                             u32 newCursorPos, u32 currentLineLength);

    // Decode character input to actual keystroke (handle escape sequences).
    KeyEventType DecodeKey(u8 c);

    /**
     * Tab completion/listing stuff
     */
    int FindMatchingNamespaces(
            const string & currentCommandLine,
            set<string> &matches);

    int FindMatchingCommands(
            const string & currentCommandLine,
            set<string> &matchedNamespaceTags);

    /*
     * "Special" key handlers.
     */
    void HandleTab(int tabCount, const string & prompt );
    void HandleCursor(int key);

    void Prompt( const string & prompt);


    // Constants for interpreting Key input strings
    static const u32 BS = 127; // Telnet gives this for backspace.
    static const u32 BS2 = 8; // Serial port gives this for backspace.
    static const u32 TAB = 9;
    static const u32 LINE_FEED = 10;
    static const u32 CARRIAGE_RETURN = 13;

    static const u32 ESC = 27;

    static const u32 EDIT_KEY = 91; // Second byte of cursor key or INS/DEL ESC sequence
    static const u32 OTHER_EDIT_KEY = 79; // Second Byte of HOME/END sequence

    static const u32 CURSOR_UP_KEY = 65;
    static const u32 CURSOR_DOWN_KEY = 66;
    static const u32 CURSOR_LEFT_KEY = 68;
    static const u32 CURSOR_RIGHT_KEY = 67;

    static const u32 INSERT_KEY = 50;
    static const u32 DELETE_KEY = 51;

    static const u32 HOME_KEY = 72;
    static const u32 END_KEY = 70;
};


//
// Handy utility functions
//
int TokeniseString(string inputString, vector<string>& tokens, bool ignoreDot = false);



// Constants for manipulating cursor
// const string CURSOR_LEFT_AND_BLANK_STRING = "\033\133\104 \033\133\104";
const string CURSOR_LEFT_STRING           = "\033\133\104" ;
const string CURSOR_RIGHT_STRING          = "\033\133\103" ;


#endif /* CLIUSERINPUT_H_ */
