
#include "DarkGameKit.h"
#include <iostream>
#include <string>
#include "DGKText.h"

#pragma comment(lib, "DarkGameKit.lib")

int main(void) //int argc, char* argv[]
{
	StartGDK();
	
	while ( LoopGDK ( ) )
	{
		dbSetCursor(dbRND(640), dbRND(800));
		dbPrint("*");
	}

	return 0;
}