
#include "DarkGameKit.h"
#include <iostream>
#include <string>

#pragma comment(lib, "DarkGameKit.lib")

int main(void) //int argc, char* argv[]
{
	StartGDK();

	/*dbSyncRate(60);

	while ( LoopGDK ( ) )
	{
		dbSetCursor(dbRND(640), dbRND(800));
		dbPrint("*");
	}*/

	dbSyncOn();
	dbSyncRate(60);
	dbCreateAnimatedSprite(1, "animatedsprite.png", 4, 4, 1);

	while (LoopGDK())
	{
		dbPasteSprite(1, 0, 0);
		dbPlaySprite(1, 1, 16, 1);
		dbSync();
	}

	return 0;
}