
#include "DarkGameKit.h"
#include <iostream>

int main(void) //int argc, char* argv[]
{
	StartGDK();

	/*dbSyncRate(60);
	dbLoadImage("test.jpg", 10);
	dbLoadSound("saucer.wav", 4);
	//dbPlaySound(4);
	//dbSetSoundSpeed(4, 2000);
	//dbLoopSound(4);
	//dbDeleteImage(10);
	dbSprite(25, 100, 100, 10);
	dbSprite(30, 50, 50, 10);
	//dbSprite(31, 200, 200, 10);
	//dbSetSpritePriority(25, 2);
	//dbSetSpritePriority(31, 1);
	//dbCloneSprite(25, 30);
	//dbSizeSprite(25, 300, 300);
	dbPasteSprite(30, 10, 10);
	dbSetSpriteTextureCoord(30, 0, 1, 1); // manipulated
	dbSetSpriteTextureCoord(25, 0, 0, 0); // normal

	int A = 10;

	while (LoopGDK())
	{
		if(dbKeyState(57))
		{
			std::cout << "MOO!" << std::endl;
		}

		if(dbKeyState(16))
		{
			std::cout << "WOO!" << std::endl;
		}

		//dbLoopSound(4);
		dbSetCursor(dbRND(640), dbRND(800));
		//dbMoveSprite(25, 8);
		//A++;
		//dbSprite(25, A, 10, 10);
		//std::cout << dbSpriteImage(25) << std::endl;
		//std::cout << dbSpriteImage(30) << std::endl;
		//std::cout << dbSpriteFrame(25) << std::endl;
		dbPrint("*");
	}*/

	dbSyncOn ( );
	dbSyncRate ( 60 );

	// load an image
	dbLoadImage("test.jpg", 1);
	
	// main loop
	while ( LoopGDK ( ) )
	{
		// quit on escape key
	//	if ( dbEscapeKey ( ) )
	//		return;

		// paste images at random locations
	/*	for ( t = 1 ; t < 1001; t++ )
			dbPasteImage ( 1, dbRND ( 680 ) - 16, dbRND ( 520 ) - 32);*/

		dbPasteImage ( 1, 10, 10);

		// display frame rate
	//	dbText ( 20, dbScreenHeight ( ) - 40, desc );
	//	sprintf_s ( fps, "FPS: %d" , dbScreenFPS ( ) );
	//	dbText ( dbScreenWidth ( ) - 20 - dbTextWidth ( fps ) , dbScreenHeight ( ) - 40 , fps );

		// update screen
		dbSync ( );
	}
	

	/*//dbSetDisplayMode(1024, 768, 32);
	dbSyncRate(60);
	dbCreateAnimatedSprite(1, "animatedsprite.png", 4, 4, 1);
	//dbCreateAnimatedSprite(2, "alien_anim.png", 3, 3, 10);
	//dbSprite(2, 300, 300, 10);
	//dbHideSprite(2);
	//dbSetSpriteFrame(2, 7);

	while (LoopGDK())
	{
		dbPasteSprite(1, 100, 0);
		//dbPasteSprite(2, 100, 0);
		dbPlaySprite(1, 1, 16, 200);
		//dbPlaySprite(2, 5, 8, 200);
		//dbSetSpriteTextureCoord(1, 0, 0.5f, 1.0f);
		//std::cout << dbSpriteFrame(1) << std::endl;
		//
		if (dbKeyState(57))
		{
			dbShowSprite(2);
		}

		dbSync();
	}*/

	return 0;
}