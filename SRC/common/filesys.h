#ifndef __FILESYS_H__
#define __FILESYS_H__

#include "fxlib.h"
#include "stdlib.h"

/*
Types of memory device:
Main Memory
Storage Memory
SD Memory

Main Memory Limitations:
Max directory length: No directories in main memory.
Max filename length: 8
Can't search.

Storage/SD Memory Limitations:
Max directory length: 8
Max filename length: 12

Max filepath is therefore 28
Max folderpath is 15

Path structure: \\mem_type\\dir_name\\file_name
E.g. \\fls0\\dir\file.abc
*/

// Defined as n(characters) + 1 for null terminator.
#define AL_MAX_DIR 9

#define AL_MAX_FILENAME 13
#define AL_MAX_FILENAME_MAIN 9

#define AL_MAX_PATH_DEV 7
#define AL_MAX_PATH_DIR 16
#define AL_MAX_PATH_FILE 20
#define AL_MAX_PATH 29

#define AL_MEM_STORAGE "fls0"
#define AL_MEM_SDCARD  "crd0"

#define AL_ERR_FILE_NAME_TOO_LONG
#define AL_ERR_DIR_NAME_TOO_LONG

typedef struct _fs_node {
	unsigned short type;
	char *name;
} fs_node;

unsigned int font_to_char( FONTCHARACTER *fonts, char *chars );
unsigned int char_to_font( char *chars, FONTCHARACTER *fonts );

int construct_path( FONTCHARACTER **path, enum DEVICE_TYPE device, char *directory, char *file );

int read_dir( fs_node **nodes_list, enum DEVICE_TYPE device, char *directory, char *wildcard );

#endif
