/** \file filesys.c
 * Header file containing filesystem function implementations.
 */
#include "filesys.h"

// To-Do - Make these functions safe - check for up to n before stopping.
// Same with strlen.

unsigned int font_to_char( FONTCHARACTER *fonts, char *chars )
{
	unsigned int i = 0;

	while( fonts[i] != '\0' ) {
		chars[i] = fonts[i];
		i++;
	}

	chars[i] = '\0';

	return i;
}

unsigned int char_to_font( char *chars, FONTCHARACTER *fonts )
{
	unsigned int i = 0;

	while( chars[i] != '\0' ) {
		fonts[i] = chars[i];
		i++;
	}

	fonts[i] = '\0';

	return i;
}

unsigned int fntlen( FONTCHARACTER *fonts )
{
	unsigned int i = 0;

	while( fonts[i] != '\0' ) {
		i++;
	}

	return (i - 1);
}

int construct_path( FONTCHARACTER **path, enum DEVICE_TYPE device, char *directory, char *file )
{
	size_t path_length = 0;

	// Choose length of output depending on device chosen and fields populated.
	switch( device )
	{
		case DEVICE_MAIN_MEMORY:
			path_length = AL_MAX_FILENAME_MAIN;
		break;

		case DEVICE_STORAGE:
		case DEVICE_SD_CARD:
			if( NULL == file && NULL == directory)
			{
				path_length = AL_MAX_PATH_DEV;
			} else if( NULL == file && NULL != directory)
			{
				path_length = AL_MAX_PATH_DIR;
			} else if( NULL != file && NULL == directory)
			{
				path_length = AL_MAX_PATH_FILE;
			} else if( NULL != file && NULL != directory)
			{
				path_length = AL_MAX_PATH;
			}
		break;

		default:
			return 0;
	}

	*path = ( FONTCHARACTER * )malloc( path_length * sizeof( FONTCHARACTER ) );

	if( NULL == *path )
	{
		// Memory allocation failure.
		return -1;
	}

	switch( device )
	{
		// Main memory only requires filename, no folders or device name.
		case DEVICE_MAIN_MEMORY:
			if( strlen( file ) < AL_MAX_FILENAME_MAIN )
			{
				char_to_font( file, *path );
			} else {
				// Filename too long for main.
				return 0;
			}

			return path_length;
		break;

		// Format: \\fls0
		case DEVICE_STORAGE:
			char_to_font( "\\\\", *path );
			char_to_font( AL_MEM_STORAGE, &((( FONTCHARACTER * )*path)[2]) );
		break;

		// Format: \\crd0
		case DEVICE_SD_CARD:
			char_to_font( "\\\\", *path );
			char_to_font( AL_MEM_SDCARD, &((( FONTCHARACTER * )*path)[2]) );
		break;
	}

	// Format: \\fls0\dirname
	if( NULL != directory )
	{
		unsigned int pos = fntlen( *path );
		// Check length first.
		if( strlen( directory ) < AL_MAX_DIR )
		{
			char_to_font( "\\", &((( FONTCHARACTER * )*path)[pos + 1]) );
			char_to_font( directory, &((( FONTCHARACTER * )*path)[pos + 2]) );
		} else {
			// Too long!
			return 0;
		}
	}

	// Format: \\fls0\dirname\filename or just \\fls0\filename
	if( NULL != file )
	{
		unsigned int pos = fntlen( *path );
		// Check length first.
		if( strlen( file ) < AL_MAX_FILENAME )
		{
			char_to_font( "\\", &((( FONTCHARACTER * )*path)[pos + 1]) );
			char_to_font( file, &((( FONTCHARACTER * )*path)[pos + 2]) );
		} else {
			// Too long!
			return 0;
		}
	}

	// Shrink path? Realloc if larger than needed?

	return path_length;
}

void free_nodes( fs_node **nodes_list, unsigned int num_nodes )
{
	unsigned int i;

	// Free memory allocated for names.
	for( i = 0; i < num_nodes; i++ )
	{
		free( ((( fs_node * )*nodes_list)[i]).name );
	}

	// Free the node list itself.
	free( *nodes_list );
}

int read_dir( fs_node **nodes_list, enum DEVICE_TYPE device, char *directory, char *wildcard )
{
	FONTCHARACTER *path = NULL;
	FONTCHARACTER found_file[AL_MAX_FILENAME];

	FILE_INFO file_info;
	int find_handle = 0;

	unsigned int num_nodes = 0;

	// Can only read directory contents in storage memory and SD card.
	if( DEVICE_STORAGE != device && DEVICE_SD_CARD != device )
	{
		return -1;
	}

	// TO-DO: check return value of construct_path and handle.
	if( construct_path( &path, device, directory, wildcard ) > 0 )
	{
		if( Bfile_FindFirst( path, &find_handle, found_file, &file_info ) == IML_FILEERR_NOERROR )
		{
			do {
				// Enlarge our list and populate it with type, size and name.
				*nodes_list = realloc( *nodes_list, ++num_nodes * sizeof( fs_node ) );

				((( fs_node * )*nodes_list)[num_nodes - 1]).type = file_info.type;
				((( fs_node * )*nodes_list)[num_nodes - 1]).size = file_info.dsize;
				((( fs_node * )*nodes_list)[num_nodes - 1]).name = malloc( AL_MAX_FILENAME * sizeof( char ) );

				if( NULL != ((( fs_node * )*nodes_list)[num_nodes - 1]).name )
				{
					font_to_char( found_file, ((( fs_node * )*nodes_list)[num_nodes - 1]).name );
				} else {
					// Memalloc error
					return -2;
				}
			} while( Bfile_FindNext( find_handle, found_file, &file_info ) == IML_FILEERR_NOERROR );

			Bfile_FindClose( find_handle );
		}
	}

	if( NULL != path )
	{
		free( path );
	}

	return num_nodes;
}
