/** \file menu.h
 * Header file containing menu function prototypes.
 */
 #ifndef __MENU_H__
 #define __MENU_H__

#include "fxlib.h"

/*
Menu CHILD as char name[4], position (0-5), type (PARENT/menu), function pointer to call
*/

#define AL_MENU_MAX_NAME 5
#define AL_ENTRIES_PER_MENU 6

#define AL_MENU_PREV      "\xE6\x9A"
#define AL_MENU_TYPE_NEXT "\xE6\x9B"
#define AL_MENU_UP        "\xE6\x9C"

typedef enum menu_type {
	AL_MENU_TYPE_PARENT,
	AL_MENU_TYPE_UP,
	AL_MENU_TYPE_PAGE_NEXT,
	AL_MENU_TYPE_PAGE_PREV,
	AL_MENU_TYPE_CHILD,
	AL_MENU_TYPE_EMPTY
};

typedef struct _menu_CHILD {
	char name[AL_MENU_MAX_NAME]; /**< 4 character menu name. */
	unsigned char position;      /**< 0-5 representing keys F1-F6. */
	unsigned char type;          /**<  */
	unsigned char child;         /**< 0-255 for address of child. */
} menu_CHILD;

const menu_CHILD menu_entries[][AL_ENTRIES_PER_MENU] = {
	{ // 0
		{ "Open", 0, AL_MENU_TYPE_CHILD,     -1 },
		{ "New",  1, AL_MENU_TYPE_CHILD,     -1 },
		{ "Edit", 2, AL_MENU_TYPE_CHILD,     -1 },
		{ "Ren",  3, AL_MENU_TYPE_CHILD,     -1 },
		{ "Move", 4, AL_MENU_TYPE_CHILD,     -1 },
		{ "",     5, AL_MENU_TYPE_PAGE_NEXT,  1 }
	},
	{ // 1
		{ "Sel",  0, AL_MENU_TYPE_PARENT,     2 },
		{ "AddD", 1, AL_MENU_TYPE_CHILD,     -1 },
		{ "Srch", 2, AL_MENU_TYPE_CHILD,     -1 },
		{ "Info", 3, AL_MENU_TYPE_CHILD,     -1 },
		{ "Sett", 4, AL_MENU_TYPE_CHILD,     -1 },
		{ "",     5, AL_MENU_TYPE_PAGE_PREV, -1 }
	},
	{ // 2
		{ "Sel",  0, AL_MENU_TYPE_CHILD,     -1 },
		{ "Del",  1, AL_MENU_TYPE_CHILD,     -1 },
		{ "Move", 2, AL_MENU_TYPE_CHILD,     -1 },
		{ "",     3, AL_MENU_TYPE_EMPTY,     -1 },
		{ "",     4, AL_MENU_TYPE_EMPTY,     -1 },
		{ "",     5, AL_MENU_TYPE_UP,         1 }
	}
};

void display_menu( unsigned int menu_id );

void clear_menu();

#endif
