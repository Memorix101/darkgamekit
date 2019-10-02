#include "DGKInput.h"

bool dbKeyState(int iScanCode)
{
	bool pressed = false;

	// db scancode to raylib mapping
	int _scancode = 0;

	if (IsKeyPressed(KEY_SPACE))
	{
		std::cout << "dbKeyState " << iScanCode << std::endl;
		pressed = true;
	}

	return pressed;
}