
// Dark GDK - The Game Creators - www.thegamecreators.com

// include Dark GDK header file
#include <DarkGameKit.h>
#include <stdio.h>

// main entry point for program
void DarkGDK ( void )
{
	// set up variables
	int		t		    = 0;
	const char*	desc	    = "Fast Image Pasting ( 1000 per cycle )";
	char	fps [ 256 ] = "";

	// switch to media directory
	//dbSetDir ( "media\\" );

	// set sync rate
	dbSyncOn ( );
	dbSyncRate ( 0 );

	// set text properties
/*	dbSetTextFont ( "arial" );
	dbSetTextSize ( 16 );
	dbSetTextToBold ( );
	dbSetTextTransparent ( );*/

	// load an image
	dbLoadImage ( "image.bmp" , 1 );

	// main loop
	while ( LoopGDK ( ) )
	{
		// quit on escape key
	//	if ( dbEscapeKey ( ) )
	//		return;

		// paste images at random locations
	for ( t = 1 ; t < 1001; t++ )
			dbPasteImage ( 1, dbRND ( 680 ) - 16, dbRND ( 520 ) - 32);

		// display frame rate
	//	dbText ( 20, dbScreenHeight ( ) - 40, desc );
	//	sprintf_s ( fps, "FPS: %d" , dbScreenFPS ( ) );
	//	dbText ( dbScreenWidth ( ) - 20 - dbTextWidth ( fps ) , dbScreenHeight ( ) - 40 , fps );

		// update screen
		dbSync ( );
	}
}

int main(void)
{
	StartGDK();
	DarkGDK();
	return 0;
}