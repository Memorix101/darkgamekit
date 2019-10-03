#include "DGKInput.h"

bool dbKeyState(int iScanCode)
{
	bool pressed = false;

	// db scancode to raylib mapping
	int _scancode = 0;

	// Keyboard keys
	switch (iScanCode)
	{
	case 57:
		_scancode = KEY_SPACE;
		break;
	case 29:
		_scancode = KEY_RIGHT_CONTROL;
		break;
	case 156:
		_scancode = KEY_LEFT_CONTROL;
		break;
	case 203:
		_scancode = KEY_LEFT;
		break;
	case 30:
		_scancode = KEY_A;
		break;
	case 205:
		_scancode = KEY_RIGHT;
		break;
	case 32:
		_scancode = KEY_S;
		break;
	}

	if (IsKeyPressed(_scancode))
	{
		std::cout << "dbKeyState " << iScanCode << std::endl;
		pressed = true;
	}

	return pressed;
}