#include "DarkSDK.h"

// load all our sounds in
void soundSetup ( void )
{
	dbLoadSound ( "Assets\\space.wav" , 1 );
	dbLoadSound ( "Assets\\shoot.wav" , 2 );
	dbLoadSound ( "Assets\\explode.wav" , 3 );
	dbLoadSound ( "Assets\\saucer.wav" , 4 );
	dbLoadSound ( "Assets\\atmos.wav" , 5 );
}