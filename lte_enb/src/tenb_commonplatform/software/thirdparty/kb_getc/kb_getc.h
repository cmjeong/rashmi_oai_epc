/* ***************************************************************************
 *
 *          Copyright 1992-2005 by Pete Wilson All Rights Reserved
 *           50 Staples Street : Lowell Massachusetts 01851 : USA
 *        http://www.pwilson.net/   pete@pwilson.net   +1 978-454-4547
 *
 * This item is free software: you can redistribute it and/or modify it as 
 * long as you preserve this copyright notice. Pete Wilson prepared this item 
 * hoping it might be useful, but it has NO WARRANTY WHATEVER, not even any 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *
 *************************************************************************** */

/* ***************************************************************************
 *
 *                          KBHIT.H
 *
 * Based on the work of W. Richard Stevens in "Advanced Programming in
 *   the Unix Environment," Addison-Wesley; and of Floyd Davidson. 
 *
 * Contains these functions:
 *
 *  To set the TTY mode:
 *     tty_set_raw() Unix setup to read a character at a time.
 *     tty_set_cooked() Unix setup to reverse tty_set_raw()
 *
 *  To read keyboard input:
 *     kb_getc()      keyboard get character, NON-BLOCKING. If a char
 *                      has been typed, return it. Else return 0.
 *     kb_getc_w()    kb get char with wait: BLOCKING. Wait for a char
 *                      to be typed and return it.
 *
 *  How to use:
 *     tty_set_raw()  set the TTY mode to read one char at a time.
 *     kb_getc()      read chars one by one.
 *     tty_set_cooked() VERY IMPORTANT: restore cooked mode when done.
 *
 * Revision History:
 *
 *     DATE                  DESCRIPTION
 * -----------    --------------------------------------------
 * 12-jan-2002     new
 * 20-aug-2002     cleanup
 *
 * Notes:
 * -----------    --------------------------------------------
 * 25-nov-2003     notate anomoly in some Unices: termattr.c_cc[VMIN] = 0;
 *************************************************************************** */

#ifdef __cplusplus
  extern "C" {
#endif

/* ***************************************************************************
 *
 * set_tty_raw(), put the user's TTY in one-character-at-a-time mode.
 * returns 0 on success, -1 on failure.
 *
 *************************************************************************** */
extern int set_tty_raw(void);

/* ***************************************************************************
 *
 * set_tty_cbreak(), put the user's TTY in cbreak mode.
 * returns 0 on success, -1 on failure.
 *
 *************************************************************************** */
extern int set_tty_cbreak();

/* ***************************************************************************
 *
 * set_tty_cooked(), restore normal TTY mode. Very important to call
 *   the function before exiting else the TTY won't be too usable.
 * returns 0 on success, -1 on failure.
 *
 *************************************************************************** */
extern int set_tty_cooked();

/* ***************************************************************************
 *
 * kb_getc(), if there's a typed character waiting to be read,
 *   return it; else return 0.
 *
 *************************************************************************** */
extern unsigned char kb_getc(void);

/* ***************************************************************************
 *
 * kb_getc_w(), wait for a character to be typed and return it.
 *
 *************************************************************************** */
extern unsigned char kb_getc_w(void);


#ifdef __cplusplus
}
#endif


