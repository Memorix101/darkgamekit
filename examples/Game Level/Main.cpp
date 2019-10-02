
// Dark GDK - The Game Creators - www.thegamecreators.com

// whenever using Dark GDK you must ensure you include the header file
#include "DarkGDK.h"

// the main entry point for the application is this function
void DarkGDK ( void )
{
	// turn on sync rate and set maximum rate to 60 fps
	dbSyncOn   ( );
	dbSyncRate ( 60 );

	// switch to the media directory, load our world
	// and turn lighting off
	SetCurrentDirectory ( "media" );
	dbLoadObject		( "universe.dbo", 1 );
	dbSetObjectLight	( 1, 0 );

	// load a model for our sky
	dbLoadObject		( "skybox2.x", 2 );
	dbSetObjectLight	( 2, 0 );
	dbSetObjectTexture	( 2, 3, 2 );
	dbScaleObject		( 2, 5000, 5000, 5000 );

	// position the camera
	dbPositionCamera	( 434, 42, -517 );

	// camera variables
	float fCameraAngleX = 0.0f;
	float fCameraAngleY = 0.0f;

	// our main loop
	while ( LoopGDK ( ) )
	{
		// move the camera using the arrow keys
		dbControlCameraUsingArrowKeys ( 0, 5.0f, 0.3f );

		// create a rotation axis based on mouse movement
		fCameraAngleX = dbWrapValue ( fCameraAngleX + dbMouseMoveY ( ) * 0.4f );
		fCameraAngleY = dbWrapValue ( fCameraAngleY + dbMouseMoveX ( ) * 0.4f );

		// rotate camera
		dbXRotateCamera ( fCameraAngleX );
		dbYRotateCamera ( fCameraAngleY );
		
		// update the screen
		dbSync ( );
	}

	// return back to windows
	return;
}
