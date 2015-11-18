/** \file ARMlet.c
 * Source file containing the program entrypoint, initialisation and quit
 * handler.
 */

#include "fxlib.h"
#include "common/filesys.h"
#include "common/menu.h"

/**
 * Program entrypoint.
 *
 * \param[in] isAppli   1 if launched from the menu, 0 by an eACT application.
 * \param[in] OptionNum Strip number (0-3). Only used if isAppli == 0.
 *
 * \return 0 if there has been an error, otherwise 1.
 */
int AddIn_main(int isAppli, unsigned short OptionNum)
{
	unsigned int key;

	Bdisp_AllClr_DDVRAM();

	GetKey( &key );
	display_menu( explorer_entries, 0 );
	GetKey( &key );
	display_menu( explorer_entries, 1 );
	GetKey( &key );
	display_menu( explorer_entries, 2 );

	while( 1 )
	{
		GetKey( &key );
	}

	return 1;
}

#pragma section _BR_Size
unsigned long BR_Size; /**< Global variable BR_Size. */
#pragma section

#pragma section _TOP
/**
 * Initialise system.
 *
 * \param[in] isAppli   1 for an application, 0 for an eActivity.
 * \param[in] OptionNum Strip number (0-3). Only used for eActivities.
 *
 * \return 0 if there has been an error, otherwise 1.
 */
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
	return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}
#pragma section
