/** \file menu.c
 * Source file containing menu function implementations.
 */
#include "menu.h"

/**
 * A function to draw the graphic for a child menu entry to the screen.
 *
 * \param[in] position Position (0-5) of the menu item to draw.
 */
void draw_child( unsigned int position )
{
	unsigned int x_base = ( position * 21 ) + 2;
	unsigned int x_end  = ( ( position + 1 ) * 21 ) - 1;

	Bdisp_DrawLineVRAM( x_base, 56, x_end , 56);
	Bdisp_DrawLineVRAM( x_base, 56, x_base, 63);
}

/**
 * A function to draw the graphic for a filled child menu entry to the screen.
 *
 * \param[in] position Position (0-5) of the menu item to draw.
 */
void draw_child_filled( unsigned int position )
{
	unsigned int x_base = ( position * 21 ) + 2;
	unsigned int x_end  = ( ( position + 1 ) * 21 ) - 1;
	unsigned int i;

	for( i = 56; i < 64; i++ )
	{
		Bdisp_DrawLineVRAM( x_base, i, x_end, i );
	}
}

/**
 * A function to draw the graphic for a parent menu entry to the screen.
 *
 * \param[in] position Position (0-5) of the menu item to draw.
 */
void draw_parent( unsigned int position )
{
	unsigned int x_base = ( position * 21 ) + 2;
	unsigned int x_end  = ( ( position + 1 ) * 21 ) - 1;

	Bdisp_DrawLineVRAM( x_base, 56, x_end    , 56 );
	Bdisp_DrawLineVRAM( x_base, 57, x_end    , 57 );
	Bdisp_DrawLineVRAM( x_base, 58, x_end    , 58 );
	Bdisp_DrawLineVRAM( x_base, 59, x_end    , 59 );
	Bdisp_DrawLineVRAM( x_base, 60, x_end    , 60 );
	Bdisp_DrawLineVRAM( x_base, 61, x_end - 1, 61 );
	Bdisp_DrawLineVRAM( x_base, 62, x_end - 2, 62 );
	Bdisp_DrawLineVRAM( x_base, 63, x_end - 3, 63 );
}

void clear_menu_position( unsigned int position )
{
	unsigned int x_base = ( position * 21 ) + 2;
	unsigned int x_end  = ( ( position + 1 ) * 21 ) - 1;
	unsigned int i;

	for( i = 56; i < 64; i++ )
	{
		Bdisp_ClearLineVRAM( x_base, i, x_end, i );
	}
}

void clear_menu()
{
	unsigned int i;

	for( i = 56; i <= 63; i++ )
	{
		Bdisp_ClearLineVRAM( 0, i, 127, i );
	}
}

void display_menu( menu_entry menu_entries[][AL_ENTRIES_PER_MENU], unsigned int menu_id )
{
	unsigned int i = 0;

	clear_menu();

	for( i = 0; i < AL_ENTRIES_PER_MENU; i++ )
	{
		switch( menu_entries[menu_id][i].type )
		{
			case AL_MENU_TYPE_PARENT:
				draw_parent( i );
				PrintMini( ( i * 21 ) + 4, 58, ( const unsigned char * )menu_entries[menu_id][i].name, MINI_REV );
			break;

			case AL_MENU_TYPE_CHILD:
				draw_child( i );
				PrintMini( ( i * 21 ) + 4, 58, ( const unsigned char * )menu_entries[menu_id][i].name, 0 );
			break;

			case AL_MENU_TYPE_UP:
				draw_child( i );
				PrintMini( ( i * 21 ) + 10, 58, ( const unsigned char * )AL_MENU_UP, 0 );
			break;

			case AL_MENU_TYPE_PAGE_PREV:
				draw_child( i );
				PrintMini( ( i * 21 ) + 10, 58, ( const unsigned char * )AL_MENU_PREV, 0 );
			break;

			case AL_MENU_TYPE_PAGE_NEXT:
				draw_child( i );
				PrintMini( ( i * 21 ) + 10, 58, ( const unsigned char * )AL_MENU_NEXT, 0 );
			break;

			case AL_MENU_TYPE_EMPTY:
			default:
			break;
		}
	}
}
