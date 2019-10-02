
// Dark GDK - The Game Creators - www.thegamecreators.com

// whenever using Dark GDK you must ensure you include the header file
#include "DarkGDK.h"

// the main entry point for the application is this function
void DarkGDK ( void )
{
	// turn on sync rate and set maximum rate to 60 fps
	dbSyncOn   ( );
	dbSyncRate ( 60 );

	dbPrint ( "Please wait loading model..." );
	dbSync ( );
	dbSync ( );
	
	dbLoadObject ( "Colonel-X.X", 1 );
	
	dbPositionCamera ( 0, 50, -80 );

	dbLoopObject ( 1 );
	dbSetObjectSpeed ( 1, 40 );
	
	// our main loop
	while ( LoopGDK ( ) )
	{
		// update the screen
		dbSync ( );
	}

	// return back to windows
	return;
}

