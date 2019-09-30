#include "DarkSDK.h"
#include "Input.h"

// check the keys we have assigned to be the fire key
bool checkFire ( void )
{

	if ( dbKeyState ( 57 ) || dbKeyState ( 29 ) || dbKeyState ( 157 ) ) 
		return true;

	return false;
}

// check the keys we have assigned to be the left key
bool checkLeft ( void )
{

	if ( dbKeyState ( 203 ) || dbKeyState ( 30 ) ) 
		return true;

	return false;
}

// check the keys we have assigned to be the right key
bool checkRight ( void )
{

	if ( dbKeyState ( 205 ) || dbKeyState ( 32 )  ) 
		return true;

	return false;
}