#include "fxlib.h"
#include "common/filesys.h"

int AddIn_main(int isAppli, unsigned short OptionNum)
{
	unsigned int key;
	fs_node *nodes_list = NULL;
	unsigned int num_nodes = 0, i;

	Bdisp_AllClr_DDVRAM();

	num_nodes = read_dir( &nodes_list, DEVICE_STORAGE, NULL, "*" );

	for( i = 0; i < num_nodes; i++ )
	{
		locate( 1, i + 1 );
		if( DT_DIRECTORY == nodes_list[i].type )
		{
			Print( ( const unsigned char * )"[" );
			Print( ( const unsigned char * )nodes_list[i].name );
			Print( ( const unsigned char * )"]" );
		} else {
			Print( ( const unsigned char * )nodes_list[i].name );
		}
		GetKey( &key );
	}

	free_nodes( &nodes_list, num_nodes );

	while( 1 )
	{
		GetKey( &key );
	}

	return 1;
}

#pragma section _BR_Size
unsigned long BR_Size;
#pragma section

#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
	return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}
#pragma section
