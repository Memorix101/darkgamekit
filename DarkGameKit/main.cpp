
#include "DarkGameKit.h"
#include <iostream>
#include <string>
#include "DGKText.h"

class Game1 : public DarkGameKit {

	DGKCore Core;
	DGKText Text;

	int t = NULL;
	char* c = NULL;

	int abc = 0;
	int def = 0;

	void DarkGDK() override
	{
		std::cout << Core.dbTAN(45) << "\n";
		for (int i = 0; i < 10; i++)
			std::cout << Core.dbRND(5) << "\n";

		/*
		Text.dbSetTextFont("tahoma.ttf");
		Text.dbSetTextSize(50);		
		
		Text.dbCenterText(0, 0, "center");			

		Text.dbSetTextSize(24);
		Text.dbText(100, 100, "Hi");		
		*/

		/*
		Core.dbSetCursor(50, 100);
		Core.dbPrint("I like trains!");
		Core.dbPrint("" + std::to_string(Core.dbTAN(45)));

		for (int a = 0; a < 5; a++)
		{
			Core.dbPrint("DFG");
		}

		for (int a = 0; a < 5; a++)
		{
			Core.dbPrint("ABC");
		}
		*/
		
	}

	void LoopGDK() override
	{
		/*
		Core.dbPrint("Kong Strong");
		Core.dbPrint("" + std::to_string(Core.dbTAN(45)));
		*/

		/*
		abc++;
		def++;

		Text.dbText(200, 200, "abc");
		Core.dbSetCursor(10, 50);
		if (abc < 5)
			Core.dbPrint("Meeeeooooow");	

		Core.dbWait(250);
		*/

		Core.dbSetCursor(Core.dbRND(640), Core.dbRND(800));
		Core.dbPrint("*");
	}
};

int main(int argc, char* argv[])
{
	DarkGameKit* game1 = new Game1;
	game1->Init();
	game1->Run();

	return 0;
}

