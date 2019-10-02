#include "DGKInput.h"


int dbKeyState(int iScanCode)
{
	int pressed = 0;

	// db scancode to raylib mapping
	int _scancode = 0;

	if (IsKeyPressed(_scancode))
	{
		pressed = 1;
	}

	return pressed;
}