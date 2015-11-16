/** \file filesys.h
 * Header file containing filesystem function prototypes.
 */
#ifndef __FILESYS_H__
#define __FILESYS_H__

#include "fxlib.h"
#include "stdlib.h"

// All lengths include null terminator.

/** Max length of a directory name in the storage memory/SD card. */
#define AL_MAX_DIR 9

/** Max length of a filename in the storage memory/SD card. */
#define AL_MAX_FILENAME 13
/** Max length of a filename in the main memory. */
#define AL_MAX_FILENAME_MAIN 9

/** Max length of a path consisting only of the device name. */
#define AL_MAX_PATH_DEV 7
/** Max length of a path consisting only of the device name and a directory. */
#define AL_MAX_PATH_DIR 16
/** Max length of a path consisting only of the device name and a file. */
#define AL_MAX_PATH_FILE 20
/** Max length of a path consisting of a device, directory and file. */
#define AL_MAX_PATH 29

/** String representation of storage memory. */
#define AL_MEM_STORAGE "fls0"
/** String representation of the SD card. */
#define AL_MEM_SDCARD  "crd0"

/*
#define AL_ERR_FILE_NAME_TOO_LONG
#define AL_ERR_DIR_NAME_TOO_LONG
*/

/**
 * Structure for a filesystem member.
 */
typedef struct _fs_node {
	unsigned short type; /**< Type of node: file/directory. */
	char *name;          /**< Name on the filesystem. */
	int size;            /**< Size of the node (excluding header). */
} fs_node;

/**
 * A function to convert a string of characters from the FONTCHARACTER format
 * to char.
 *
 * \param[in]  fonts Pointer to array of FONTCHARACTER.
 * \param[out] chars Pointer to array of char.
 *
 * \return The length of the converted string.
 */
unsigned int font_to_char( FONTCHARACTER *fonts, char *chars );

/**
 * A function to convert a string of characters from the char format to
 * FONTCHARACTER.
 *
 * \param[in]  chars Pointer to array of char.
 * \param[out] fonts Pointer to array of FONTCHARACTER.
 *
 * \return The length of the converted string.
 */
unsigned int char_to_font( char *chars, FONTCHARACTER *fonts );

/**
 * A function to find the length of a FONTCHARACTER type string.
 *
 * \param[in] fonts Pointer to array of FONTCHARACTER.
 *
 * \return The length of the string.
 */
unsigned int fntlen( FONTCHARACTER *fonts );

/**
 * A function that generates a string of type FONTCHARACTER representing the
 * path located at \\{device}\{directory}\{file}.
 *
 * \param[out] path      Pointer to a FONTCHARACTER array to store the path in.
 * \param[in]  device    ID of device being accessed (defined in filebios.h).
 * \param[in]  directory Directory in path. NULL if unused.
 * \param[in]  file      File in path. NULL if unused.
 *
 * \return Length of FONTCHARACTER string on success, 0 if the length of file
 * or directory exceed limits, -1 if there was an error allocating memory.
 */
int construct_path( FONTCHARACTER **path, enum DEVICE_TYPE device, char *directory, char *file );

/**
 * A function that frees all the memory allocated to a list of nodes.
 *
 * \param[out] nodes_list Pointer to a list of nodes to be freed.
 * \param[in]  num_nodes  Number of nodes in the list.
 */
void free_nodes( fs_node **nodes_list, unsigned int num_nodes );

/**
 * A function that lists the contents of a directory on either the storage
 * memory or SD card. Doubles as a search function if wildcard is specified.
 *
 * \param[out] nodes_list Pointer to a fs_node array to store the contents.
 * \param[in]  device     ID of device being accessed (defined in filebios.h).
 * \param[in]  directory  Directory in path. NULL if unused.
 * \param[in]  wildcard   Wildcard string to only list files/directories
 * that match it. "*" if unused.
 *
 * \return Number of files/directories found on success, -1 if invalid device
 * specified (cannot search in the main memory).
 */
int read_dir( fs_node **nodes_list, enum DEVICE_TYPE device, char *directory, char *wildcard );

#endif
