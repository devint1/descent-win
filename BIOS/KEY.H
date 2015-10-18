/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/
/*
* $Source: f:/miner/source/bios/rcs/key.h $
* $Revision: 1.19 $
* $Author: john $
* $Date: 1994/10/24 13:58:12 $
*
* Header for keyboard functions
*
* $Log: key.h $
* Revision 1.19  1994/10/24  13:58:12  john
* Hacked in support for pause key onto code 0x61.
*
* Revision 1.18  1994/10/21  15:17:10  john
* Added KEY_PRINT_SCREEN
*
* Revision 1.17  1994/08/31  12:22:13  john
* Added KEY_DEBUGGED
*
* Revision 1.16  1994/08/24  18:53:50  john
* Made Cyberman read like normal mouse; added dpmi module; moved
* mouse from assembly to c. Made mouse buttons return time_down.
*
* Revision 1.15  1994/08/18  14:56:16  john
* *** empty log message ***
*
* Revision 1.14  1994/08/08  10:43:24  john
* Recorded when a key was pressed for key_inkey_time.
*
* Revision 1.13  1994/06/17  17:17:28  john
* Added keyd_time_last_key_was_pressed or something like that.
*
* Revision 1.12  1994/04/29  12:14:19  john
* Locked all memory used during interrupts so that program
* won't hang when using virtual memory.
*
* Revision 1.11  1994/02/17  15:57:14  john
* Changed key libary to C.
*
* Revision 1.10  1994/01/31  08:34:09  john
* Fixed reversed lshift/rshift keys.
*
* Revision 1.9  1994/01/18  10:58:17  john
* *** empty log message ***
*
* Revision 1.8  1993/10/16  19:24:43  matt
* Added new function key_clear_times() & key_clear_counts()
*
* Revision 1.7  1993/10/15  10:17:09  john
* added keyd_last_key_pressed and released for use with recorder.
*
* Revision 1.6  1993/10/06  16:20:37  john
* fixed down arrow bug
*
* Revision 1.5  1993/10/04  13:26:42  john
* changed the #defines for scan codes.
*
* Revision 1.4  1993/09/28  11:35:20  john
* added key_peekkey
*
* Revision 1.3  1993/09/20  18:36:43  john
* *** empty log message ***
*
* Revision 1.1  1993/07/10  13:10:39  matt
* Initial revision
*
*
*/

#ifndef _KEY_H
#define _KEY_H 

#include "fix.h"
#include "types.h"
#include <Windows.h>

//==========================================================================
// This installs the int9 vector and initializes the keyboard in buffered
// ASCII mode. key_close simply undoes that.
extern void key_init();
extern void key_close();

//==========================================================================
// These are configuration parameters to setup how the buffer works.
// set keyd_buffer_type to 0 for no key buffering.
// set it to 1 and it will buffer scancodes.
extern char keyd_buffer_type;
extern char keyd_repeat;        // 1=allow repeating, 0=dont allow repeat

								// keyd_editor_mode... 0=game mode, 1=editor mode.
								// Editor mode makes key_down_time always return 0 if modifiers are down.
extern char keyd_editor_mode;

// Time in seconds when last key was pressed...
extern volatile int keyd_time_when_last_pressed;

//==========================================================================
// These are the "buffered" keypress routines.  Use them by setting the
// "keyd_buffer_type" variable.

extern void key_flush();    // Clears the 256 char buffer
extern int key_checkch();   // Returns 1 if a char is waiting
extern int key_getch();     // Gets key if one waiting other waits for one.
extern int key_inkey();     // Gets key if one, other returns 0.
extern int key_inkey_time(fix *time);     // Same as inkey, but returns the time the key was pressed down.
extern int key_peekkey();   // Same as inkey, but doesn't remove key from buffer.

extern char key_to_ascii(int keycode);

extern void key_debug();    // Does an INT3

							//==========================================================================
							// These are the unbuffered routines. Index by the keyboard scancode.

							// Set to 1 if the key is currently down, else 0
extern volatile unsigned char keyd_pressed[];
extern volatile unsigned char keyd_last_pressed;
extern volatile unsigned char keyd_last_released;

// Returns the seconds this key has been down since last call.
extern fix key_down_time(int scancode);

// Returns number of times key has went from up to down since last call.
extern unsigned int key_down_count(int scancode);

// Returns number of times key has went from down to up since last call.
extern unsigned int key_up_count(int scancode);

// Clears the times & counts used by the above functions
// Took out... use key_flush();
//void key_clear_times();
//void key_clear_counts();


#define KEY_SHIFTED     0x100
#define KEY_ALTED       0x200
#define KEY_CTRLED      0x400
#define KEY_DEBUGGED		0x800

#define KEY_0           0x30
#define KEY_1           0x31
#define KEY_2           0x32
#define KEY_3           0x33
#define KEY_4           0x34
#define KEY_5           0x35
#define KEY_6           0x36
#define KEY_7           0x37
#define KEY_8           0x38
#define KEY_9           0x39

#define KEY_A           0x41
#define KEY_B           0x42
#define KEY_C           0x43
#define KEY_D           0x44
#define KEY_E           0x45
#define KEY_F           0x46
#define KEY_G           0x47
#define KEY_H           0x48
#define KEY_I           0x49
#define KEY_J           0x4a
#define KEY_K           0x4b
#define KEY_L           0x4c
#define KEY_M           0x4d
#define KEY_N           0x4e
#define KEY_O           0x4f
#define KEY_P           0x50
#define KEY_Q           0x51
#define KEY_R           0x52
#define KEY_S           0x53
#define KEY_T           0x54
#define KEY_U           0x55
#define KEY_V           0x56
#define KEY_W           0x57
#define KEY_X           0x58
#define KEY_Y           0x59
#define KEY_Z           0x5a

#define KEY_MINUS       VK_OEM_MINUS
#define KEY_EQUAL       VK_OEM_PLUS
#define KEY_DIVIDE      VK_OEM_2
#define KEY_SLASH       VK_OEM_5
#define KEY_COMMA       VK_OEM_COMMA
#define KEY_PERIOD      VK_OEM_PERIOD
#define KEY_SEMICOL     VK_OEM_1

#define KEY_LBRACKET    VK_OEM_4
#define KEY_RBRACKET    VK_OEM_6

#define KEY_RAPOSTRO    0x28
#define KEY_LAPOSTRO    0x29

#define KEY_ESC         VK_ESCAPE
#define KEY_ENTER       VK_RETURN
#define KEY_BACKSP      VK_BACK
#define KEY_TAB         VK_TAB
#define KEY_SPACEBAR    VK_SPACE

#define KEY_NUMLOCK     VK_NUMLOCK
#define KEY_SCROLLOCK   VK_SCROLL
#define KEY_CAPSLOCK    VK_CAPITAL

#define KEY_LSHIFT      VK_LSHIFT
#define KEY_RSHIFT      VK_RSHIFT

#define KEY_LALT        VK_LMENU
#define KEY_RALT        VK_RMENU

#define KEY_LCTRL       VK_LCONTROL
#define KEY_RCTRL       VK_RCONTROL

#define KEY_F1          VK_F1
#define KEY_F2          VK_F2
#define KEY_F3          VK_F3
#define KEY_F4          VK_F4
#define KEY_F5          VK_F5
#define KEY_F6          VK_F6
#define KEY_F7          VK_F7
#define KEY_F8          VK_F8
#define KEY_F9          VK_F9
#define KEY_F10         VK_F10
#define KEY_F11         VK_F11
#define KEY_F12         VK_F12

#define KEY_PAD0        VK_NUMPAD0
#define KEY_PAD1        VK_NUMPAD1
#define KEY_PAD2        VK_NUMPAD2
#define KEY_PAD3        VK_NUMPAD3
#define KEY_PAD4        VK_NUMPAD4
#define KEY_PAD5        VK_NUMPAD5
#define KEY_PAD6        VK_NUMPAD6
#define KEY_PAD7        VK_NUMPAD7
#define KEY_PAD8        VK_NUMPAD8
#define KEY_PAD9        VK_NUMPAD9
#define KEY_PADMINUS    VK_SUBTRACT
#define KEY_PADPLUS     VK_ADD
#define KEY_PADPERIOD   VK_DECIMAL
#define KEY_PADDIVIDE   VK_DIVIDE
#define KEY_PADMULTIPLY VK_MULTIPLY
#define KEY_PADENTER    VK_RETURN

#define KEY_INSERT      VK_INSERT
#define KEY_HOME        VK_HOME
#define KEY_PAGEUP      VK_PRIOR
#define KEY_DELETE      VK_DELETE
#define KEY_END         VK_END
#define KEY_PAGEDOWN    VK_NEXT
#define KEY_UP          VK_UP
#define KEY_DOWN        VK_DOWN
#define KEY_LEFT        VK_LEFT
#define KEY_RIGHT       VK_RIGHT

#define KEY_PRINT_SCREEN	VK_SNAPSHOT
#define KEY_PAUSE			VK_PAUSE

#endif

