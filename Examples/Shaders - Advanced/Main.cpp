
// Dark GDK - The Game Creators - www.thegamecreators.com

// include DarkGDK header file and because we're using
// files from Dark Shader include the Dark Shader header
#include "DarkGDK.h"
#include "ShaderData.h"


void DarkGDK ( void )
{
	// this is the entry point for the program

	// switch on sync rate and set the maximum
	// refresh rate to 60 frames per second
	dbSyncOn   ( );
	dbSyncRate ( 60 );

	// prepare the shader functions
	dbShaderDataStart ( );

	// make a sphere,  load an image and texture it
	dbMakeObjectSphere ( 1, 10 );
	dbLoadImage        ( "detail.jpg", 1 );
	dbTextureObject    ( 1, 1 );

	// switch autocam off
	dbAutoCamOff ( );

	// make a camera and color the backdrop to 0
	dbMakeCamera    ( 1 );
	dbColorBackdrop ( 1, 0 );

	// load an effect for the camera
	dbLoadCameraEffect ( "Bloom.dbs", 1, 0 );
	dbSetCameraEffect  ( 1, 1, 1 );

	// make a plane and set the quad effect for it
	dbMakeObjectPlane ( 2, 2, 2 );
	dbLoadEffect      ( "quad.fx", 2, 0 );
	dbSetObjectEffect ( 2, 2 );

	// set up properties for our quad effect
	dbMakeVector4             ( 1 );
	dbSetVector4              ( 1, dbScreenWidth ( ), dbScreenHeight ( ), 0, 0 );
	dbSetEffectConstantVector ( 2, "ViewSize", 1 );
	dbDeleteVector4           ( 1 );
	dbTextureObject           ( 2, 0, 1 );
	
	// ensure camera 1 is set to same position and rotation as camera 0
	dbPositionCamera ( 1, dbCameraPositionX ( 0 ), dbCameraPositionY ( 0 ), dbCameraPositionZ ( 0 ) );
	dbRotateCamera   ( 1, dbCameraAngleX    ( 0 ), dbCameraAngleY    ( 0 ), dbCameraAngleZ    ( 0 ) );

	// main program loop
	while ( LoopGDK ( ) )
	{
		// rotate the sphere
		dbTurnObjectLeft ( 1, 0.1 );

		// hide the quad, show the sphere and draw
		// this camera effect to our quad
		dbHideObject ( 2 );
		dbShowObject ( 1 );
		dbSyncCamera ( 1 );

		// hide the sphere, show the quad
		dbHideObject ( 1 );
		dbShowObject ( 2 );

		/// update the screen, camera 1 is shown
		dbSync ( );
	}
}
