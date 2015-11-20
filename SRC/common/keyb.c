/** \file keyb.h
 * Source file containing keyboard function implementations.
 */

#include "keyb.h"
#include "syscalls.h"

int cursor_x = 0;
int cursor_y = 0;

void cursor_on()
{
	// Start timer.
	SetTimer( ID_USER_TIMER1, 500, &cursor_handler );
}

void cursor_off()
{
	KillTimer( ID_USER_TIMER1 );
	Bdisp_ClearLineVRAM( cursor_x, cursor_y, cursor_x, cursor_y + 6 );
}

void cursor_handler()
{
	Bdisp_AreaReverseVRAM( cursor_x, cursor_y, cursor_x, cursor_y + 6 );
	Bdisp_PutDisp_DD();
}

void move_cursor( int x, int y )
{
	// Backup previous cursor location.
	int tmp_x = cursor_x, tmp_y = cursor_y;

	// Move cursor.
	cursor_x = x;
	cursor_y = y;

	// Clear previous position of cursor.
	Bdisp_ClearLineVRAM( tmp_x, tmp_y, tmp_x, tmp_y + 6 );
}

void move_cursor_cr( int column, int row )
{
	move_cursor( ( column - 1 ) * 6, ( row - 1 ) * 8 );
}

// Add parameter to choose what type of characters
int read_string( char **result, int max_length, int x_start, int y_start )
{
	unsigned int key = 0;
	int length = 0;
	int position = 0;
	int i;

	*result = ( char * )malloc( ( max_length + 1 ) * sizeof( char ) );

	memset( *result, ' ', max_length ); // Fill the string with spaces

	((( char * )*result)[max_length]) = '\0';

	locate( x_start, y_start );
	move_cursor_cr( x_start, y_start );

	//Cursor_SetFlashOn( 0 );
	cursor_on();

	do {
		GetKey( &key );

		if( ( ( key >= KEY_CHAR_A ) && ( key <= KEY_CHAR_Z ) ) || ( ( key >= KEY_CHAR_0 ) && ( key <= KEY_CHAR_9 ) ) || ( key == KEY_CHAR_DP ) )
		{
			// Check if the buffer is full
			if( length < max_length )
			{
				// If there are no characters ahead of us
				if( position >= length )
				{
					// Write the character as normal
					((( char * )*result)[position++]) = ( char )key;
					++length;
				} else {
					// There are characters ahead of where we are typing, shift right one
					memcpy( &((( char * )*result)[position + 1]), &((( char * )*result)[position]), max_length - position - 1 );
					((( char * )*result)[position++]) = ( char )key;
					++length;
				}
			}
		}

		if( key == KEY_CTRL_DEL )
		{
			if( position > 0 )
			{
				if( position >= length ) // Delete if we are at the end
				{
					((( char * )*result)[--position]) = ' ';
					--length;
				} else {
					// Shift left one then delete
					memcpy( &((( char * )*result)[position-1]), &((( char * )*result)[position]), max_length - position - 1 );
					for( i = length - 1; i <= max_length - 1; i++ )
					{
						((( char * )*result)[i]) = ' ';
					}
					((( char * )*result)[max_length]) = '\0';
					--position; // Move cursor left.
					--length; // Decrease size of string by 1.
				}
			}
		}

		if( key == KEY_CTRL_LEFT )
		{
			if( position > 0)
			{
				position--;
			}
		}

		if( key == KEY_CTRL_RIGHT )
		{
			// If we are not at the max length of the string and there are characters in front to move cursor to
			if( position < max_length && position < length )
			{
				position++;
			}
		}

		// Update display
		locate( x_start, y_start );
		move_cursor_cr( x_start, y_start );
		Print( ( unsigned char * )*result );
		locate( x_start + position, y_start );
		move_cursor_cr( x_start + position, y_start );
	} while( key != KEY_CTRL_EXE );

	//Cursor_SetFlashOff();
	cursor_off();

	// Remove trailing spaces & shrink?
	((( char * )*result)[length]) = '\0';
	*result = ( char * )realloc( *result, length + 1 );

	return length;
}
