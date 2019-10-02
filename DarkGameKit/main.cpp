
#include "DarkGameKit.h"
#include <iostream>
#include <raylib.h>
#include <string>

#pragma comment(lib, "DarkGameKit.lib")

int main(void) //int argc, char* argv[]
{
	StartGDK();

	dbSyncRate(60);

	dbLoadImage("nalacat.jpg", 10);
	dbLoadSound("saucer.wav", 4);
	//dbPlaySound(4);
	//dbSetSoundSpeed(4, 2000);
	//dbLoopSound(4);

	while (LoopGDK())
	{
		//dbLoopSound(4);
		dbSetCursor(dbRND(640), dbRND(800));
		dbSprite(25, 10, 10, 10);
		dbPrint("*");
	}

	/*dbSyncOn();
	//dbSetDisplayMode(1024, 768, 32);
	dbSyncRate(60);
	dbCreateAnimatedSprite(1, "animatedsprite.png", 4, 4, 1);

	while (LoopGDK())
	{
		dbPasteSprite(1, 0, 0);
		dbPlaySprite(1, 1, 16, 1);
		dbSync();
	}*/

	return 0;
}