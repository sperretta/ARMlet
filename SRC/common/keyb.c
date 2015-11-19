/** \file keyb.h
 * Source file containing keyboard function implementations.
 */

#include "keyb.h"
#include "syscalls.h"

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

	Cursor_SetFlashOn( 0 );

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
		Print( ( unsigned char * )*result );
		locate( x_start + position, y_start );
	} while( key != KEY_CTRL_EXE );

	Cursor_SetFlashOff();

	// Remove trailing spaces & shrink?
	((( char * )*result)[length]) = '\0';
	*result = ( char * )realloc( *result, length + 1 );

	return length;
}
