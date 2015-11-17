/** \file menu.c
 * Header file containing menu function implementations.
 */
#include "menu.h"
#include "syscalls.h"

void draw_child( unsigned int position )
{
	unsigned int x_base = ( position * 21 ) + 2;
	unsigned int x_end  = ( ( position + 1 ) * 21 ) - 1;

	Bdisp_DrawLineVRAM( x_base, 56, x_end , 56);
	Bdisp_DrawLineVRAM( x_base, 56, x_base, 63);
}

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

void clear_menu()
{
	unsigned int i;

	for( i = 56; i <= 63; i++ )
	{
		Bdisp_ClearLineVRAM( 0, i, 127, i );
	}
}

void print_menu( unsigned int menu_id )
{
	unsigned int i = 0;

	clear_menu();

	for( i = 0; i < AL_ENTRIES_PER_MENU; i++ )
	{
		switch( menu_entries[menu_id][i].type )
		{
			case AL_MENU_TYPE_PARENT:
				draw_parent( i );
			break;

			case AL_MENU_TYPE_CHILD:
				draw_child( i );
			break;

			case AL_MENU_TYPE_EMPTY:
			default:
			break;
		}
		//PrintMini( ( i * 21 ) + 3, 58, menu_entries[menu_id][i].name, 0 );
	}
}
