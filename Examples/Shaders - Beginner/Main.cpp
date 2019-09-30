
// Dark GDK - The Game Creators - www.thegamecreators.com

// include DarkGDK header file
#include "DarkGDK.h"

void DarkGDK ( void )
{
	// this is the entry point for the program

	// switch on sync rate and set the maximum
	// refresh rate to 60 frames per second
	dbSyncOn   ( );
	dbSyncRate ( 60 );

	// make our cube, load the effect and apply
	// it to our object
	dbMakeObjectCube ( 1, 1 );
	dbLoadEffect ( "DetailMapping.dbs", 1, 1 );
	dbSetObjectEffect ( 1, 1 );

	dbSetEffectConstantFloat ( 1, "detailScale", 1 );

	// main program loop
	while ( LoopGDK ( ) )
	{
		// rotate the object
		dbTurnObjectLeft ( 1, 0.5 );

		// update the screen
		dbSync ( );
	}
}
