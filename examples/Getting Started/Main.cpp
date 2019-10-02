
// Dark GDK - The Game Creators - www.thegamecreators.com

// in this program we're going to take an image and animate
// it on screen by using a sprite

// whenever using Dark GDK you must include the header file
#include <DarkGameKit.h>

// the main entry point for the application is this function
void DarkGDK ( void )
{
	// at the start of the program we will switch the sync rate on
	// by using the function dbSyncOn, this means that we control
	// when the screen is updated
	dbSyncOn ( );

	// now we're going to set the maximum amount of times per second
	// that the program can update the screen, we set this to a
	// value of 60 meaning this program will run at a potential 
	// frame rate of 60 frames per second
	dbSyncRate ( 60 );

	// now comes the part where we take our image and create a sprite
	// for it, we achieve this by using the function dbCreateAnimatedSprite,
	// this function takes 5 parameters, the first parameter is an ID number
	// for the sprite, we can use any number from 1 upwards, this number is
	// then used whenever we want to control the sprite in any way, the 
	// second parameter is the filename of the image to load, the third
	// parameter is used to define how many frames of animation the image
	// contains horizontally, in this case it is 4 frames, the fourth
	// parameter defines how many vertical frames of animation are contained
	// in the image, and finally the last parameter controls the ID number
	// for the image we are loading, after calling this function we will
	// have a sprite in memory that can be displayed and animated on screen
	dbCreateAnimatedSprite ( 1, "animatedsprite.png", 4, 4, 1 );
	
	// this is our main loop, it is a simple while loop that will call
	// a GDK function named LoopGDK, this function will perform some internal
	// routines, it is recommended to always base your main loop on this
	// function call
	while ( LoopGDK ( ) )
	{
		// inside our main loop we can control the logic of the program,
		// we want to take our animated sprite and display it on screen,
		// this can be achieved by calling the function dbPasteSprite, this
		// function takes 3 parameters, the first parameter is an ID number
		// of the sprite, earlier on when we created the sprite we used an
		// ID number of 1, so when we call dbPasteSprite we pass in an ID of
		// 1 to indicate the sprite we created, the next two parameters are
		// X and Y coordinates, these are used to position the sprite at a
		// specific location on screen, in our case we will position the
		// sprite at 0, 0 which is the top left of the screen
		dbPasteSprite ( 1, 0, 0 );

		// our sprite is using an image that has multiple frames on, by default
		// it will display frame 1, we want to cycle through all the images to
		// show our animation, we can do this by calling dbPlaySprite, this
		// function takes 4 parameters, the first is an ID number, we use ID number
		// 1, the second parameter controls the start frame, we start from the
		// beginning so use a value of 1, the third parameter defines the end
		// frame, we have 16 frames of animation so pass in a value of 16, the
		/// final parameter controls the delay between switching frames, we pass
		// in a value of 200, lower values will make the frames change quickly
		// while higher values will make the frames change slowly
		dbPlaySprite ( 1, 1, 16, 200 );

		// the final call in our main loop is to dbSync, this function will
		// update the screen and draw any graphics
		dbSync ( );
	}

	// return back to windows
	return;
}

int main(void) //int argc, char* argv[]
{
	StartGDK();
	DarkGDK();
	return 0;
}