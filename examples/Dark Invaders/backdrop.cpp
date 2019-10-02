#include <DarkGameKit.h>
#include "backdrop.h"

// variables to store how much the backdrops have scrolled
float fBackDropBottomScrollY = 0;
float fBackDropMiddleScrollY = 0;
float fBackDropTopScrollY = 0;
// we can change this global in the main part of our program to alter the overall speed of all 3 layers
float g_fBackdropSpeed = 1.0f;

// Load in all the images we need for the backdrops - we are going to create a parallax scrolling effect with 3 seperate images laid on top of each other moving at different speeds
// to give a nice effect of depth
void backdropSetup( void )
{
	// bottom layer
	dbLoadImage ( "Assets\\backbottom.png" , 50 );
	// middle layer
	dbLoadImage ( "Assets\\backmiddle.png" , 52 );
	// top layer
	dbLoadImage ( "Assets\\backtop.png" , 54 );
}

// keep our backdrops scrolling
void backdropUpdate( void )
{
	// first the bottom one - we draw it first so it appears underneath the others
	// first lets increase the scroll value
	fBackDropBottomScrollY += 0.25f*g_fBackdropSpeed;

	// if we have reached the bottom of the screen, reset it to the top
	if ( fBackDropBottomScrollY >= 768.0f )
		fBackDropBottomScrollY = 0.0f;

	// the main sprite
	dbSprite ( 50 , 0 , (int)fBackDropBottomScrollY , 50 );
	// second sprite is draw above the first, so when the sprite scrolls down we still see the backdrop following on
	dbSprite ( 51 , 0 , (int)fBackDropBottomScrollY-768 , 50 );

	// now the middle layer
	// first lets increase the scroll value
	fBackDropMiddleScrollY += 1.0f*g_fBackdropSpeed;

	// if we have reached the bottom of the screen, reset it to the top
	if ( fBackDropMiddleScrollY >= 768.0f )
		fBackDropMiddleScrollY = 0.0f;
	
	// the main sprite
	dbSprite ( 52 , 0 , (int)fBackDropMiddleScrollY , 52 );
	// second sprite is draw above the first, so when the sprite scrolls down we still see the backdrop following on
	dbSprite ( 53 , 0 , (int)fBackDropMiddleScrollY-768 , 52 );

	// now the top layer
	// first lets increase the scroll value
	fBackDropTopScrollY += 2.0f*g_fBackdropSpeed;

	// if we have reached the bottom of the screen, reset it to the top
	if ( fBackDropTopScrollY >= 768.0f )
		fBackDropTopScrollY = 0.0f;

	// the main sprite
	dbSprite ( 54 , 0 , (int)fBackDropTopScrollY , 54 );
	// second sprite is draw above the first, so when the sprite scrolls down we still see the backdrop following on
	dbSprite ( 55 , 0 , (int)fBackDropTopScrollY-768 , 54 );
}
