
// Dark GDK - The Game Creators - www.thegamecreators.com

// include the Dark GDK header
#include "DarkGDK.h"

void DarkGDK ( void )
{
	// entry point for the application

	// switch on sync rate and set to a maximum of 60 fps
	dbSyncOn ( );
	dbSyncRate ( 60 );

	// we are going to use a skybox in this demo and it will
	// be scaled up to quite a large size, this will initially
	// result in it being outside of the cameras default range
	// therefore it will not be drawn, to adjust this we simply
	// increase the cameras range
	dbSetCameraRange ( 1.0f, 30000.0f );

	// two textures are going to be used for the terrain, the first
	// will be the diffuse part and the second will be used to
	// create extra detail on the terrain
	dbLoadImage ( "texture.jpg", 1 );
	dbLoadImage ( "detail.jpg",  2 );
	
	// the first step in creating a terrain is to call the
	// function dbSetupTerrain, this will perform some internal
	// work that allows us to get started
	dbSetupTerrain ( );

	// now we can get started on making the terrain object
	dbMakeObjectTerrain ( 1 );

	// here we pass in a heightmap that will be used to create the terrain
	dbSetTerrainHeightMap ( 1, "map.bmp" );

	// now we set the scale, this will have the effect of making
	// the terrain large on the X and Z axis but quite small on the Y
	dbSetTerrainScale ( 1, 3.0f, 0.6f, 3.0f );

	// adjust the lighting for the terrain, this function takes the ID
	// number, then a direction for the light, then 3 colours for the light
	// and finally the scale, by using this function we can adjust the
	// overall colour of the terrain
	dbSetTerrainLight ( 1, 1.0f, -0.25f, 0.0f, 1.0f, 1.0f, 0.78f, 0.5f );

	// in this call we're telling the terrain that its diffuse texture
	// will come from image 1 and its detail texture will come from
	// image 2
	dbSetTerrainTexture ( 1, 1, 2 );

	// once we have set all properties of the terrain we can build it,
	// at this point it gets created and added into your world
	dbBuildTerrain ( 1 );

	// with the terrain in place we can now load a skybox
	dbLoadObject ( "skybox2.x", 2 );

	// we dont need it to respond to light so switch light off
	dbSetObjectLight ( 2, 0 );

	// make the skybox much larger
	dbScaleObject ( 2, 30000, 30000, 30000 );
	
	// position the camera
	dbPositionCamera ( 385, 23, 100 );

	// adjust texture properties of sky box
	dbSetObjectTexture ( 2, 3, 1 );

	// now onto our main loop
	while ( LoopGDK ( ) )
	{
		// let the user move the camera around with the arrow keys
		dbControlCameraUsingArrowKeys ( 0, 2.0f, 2.0f );

		// find the ground height of the terrain
		float fHeight = dbGetTerrainGroundHeight ( 1, dbCameraPositionX ( ), dbCameraPositionZ ( ) );

		// reposition the camera so it is directly above the ground
		dbPositionCamera ( dbCameraPositionX ( ), fHeight + 10.0f, dbCameraPositionZ ( ) );

		// update the terrain
		dbUpdateTerrain ( );

		// update the screen
		dbSync ( );
	}
}