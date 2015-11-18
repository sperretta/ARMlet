/** \file menu.h
 * Header file containing menu function prototypes.
 */
#ifndef __MENU_H__
#define __MENU_H__

#include "fxlib.h"

/** Max length of a menu entry name. */
#define AL_MENU_MAX_NAME 5
/** Number of entries per menu (some can be blank). */
#define AL_ENTRIES_PER_MENU 6


#define AL_MENU_PREV "\xE6\x9A" /**< Multibyte character for left arrow. */
#define AL_MENU_NEXT "\xE6\x9B" /**< Multibyte character for right arrow. */
#define AL_MENU_UP   "\xE6\x9C" /**< Multibyte character for up arrow. */

/**
 * Enumerated list of menu entry types.
 */
typedef enum menu_type {
	AL_MENU_TYPE_PARENT,    /**< Parent entry. Filled box with a corner. */
	AL_MENU_TYPE_UP,        /**< Up a menu - child with an up arrow. */
	AL_MENU_TYPE_PAGE_NEXT, /**< Next page - child with a right arrow. */
	AL_MENU_TYPE_PAGE_PREV, /**< Previous page - child with a left arrow. */
	AL_MENU_TYPE_CHILD,     /**< Child entry - draws an outline box. */
	AL_MENU_TYPE_EMPTY      /**< Empty menu entry. Draws nothing. */
};

/**
 * Structure for a menu entry.
 */
typedef struct _menu_entry {
	char name[AL_MENU_MAX_NAME]; /**< 4 character menu name. */
	unsigned char position;      /**< 0-5 representing keys F1-F6. */
	unsigned char type;          /**< See menu_type enum. */
	unsigned char child;         /**< 0-255 for address of child. */
} menu_entry;

/**
 * The menu structure of the explorer dialog.
 * TO-DO: Move to explorer header.
 */
static const menu_entry explorer_entries[][AL_ENTRIES_PER_MENU] = {
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

/**
 * A function that draws the given menu to the screen.
 *
 * \param[in] menu_entries List of menu entries.
 * \param[in] menu_id      ID of menu to display.
 */
void display_menu( menu_entry menu_entries[][AL_ENTRIES_PER_MENU], unsigned int menu_id );

/**
 * A function that clears the region of the screen where menus are displayed.
 */
void clear_menu();

/**
 * A function that clears a stated menu item from the screen.
 *
 * \param[in] position Position (0-5) of the menu item to clear.
 */
void clear_menu_position( unsigned int position );

#endif
