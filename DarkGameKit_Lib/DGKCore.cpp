#include "DGKCore.h"


//std::vector<std::function<void()>> q;

DGKCore::DGKCore()
{
	print_cursor.x = 0;
	print_cursor.y = 0;
	print_cursor.width = 0;
	print_cursor.height = 0;

	last_printPos.x = 0;
	last_printPos.y = 0;
	last_printPos.width = 0;
	last_printPos.height = 0;

	printObjCount = 0;
}

void DGKCore::dbSyncOn()
{
	sync_i = 1;
}

void DGKCore::dbSyncOff()
{
	sync_i = 0;
}

void DGKCore::dbSync()
{

}

void DGKCore::dbSyncRate(int rate)
{
	SetTargetFPS(rate); // Set our game to run at 60 frames-per-second
}

void DGKCore::dbFastsync(void)
{

}

void DGKCore::dbCLS(void)
{

}

void DGKCore::dbSetCursor(int x, int y)
{
	print_cursor.x = x;
	print_cursor.y = y;
}

void DGKCore::dbPrint(std::string text)
{
	printObj a;
	a.text = text;

	if (print_cursor.y != last_print_cursor.y)// && last_printPos.y == ((printFontHeight)* printObjCount))
	{
		printObjCount = 0;
	}

	if (!printRef.empty()) {
		if (!fontScrolling) {
			a.pos.x = print_cursor.x;;
			if (print_cursor.y == 0) {
				a.pos.y = 0 + ((printFontHeight)*printObjCount);// +(last_printPos.y));// * printRef.size()); 
				// 0 + 15 defaultFontHeight * printRef.size() = 0 ...
			}
			else
			{
				a.pos.y = print_cursor.y + ((printFontHeight) * (printObjCount));
			}
		}
		else
		{
			a.pos.x = print_cursor.x;
			if (print_cursor.y == 0) {
				a.pos.y = print_cursor.y + (printRef[printRef.size() - 1].pos.y) + (printFontHeight);
				// 0 + 15 defaultFontHeight * printRef.size() = 0 ...
			}
			else
			{
				a.pos.y = print_cursor.y + ((printFontHeight) * (printObjCount));
			}
		}
	}
	else if (print_cursor.x != 0 || print_cursor.y != 0)
	{
		a.pos.x = print_cursor.x;
		a.pos.y = print_cursor.y;
	}
	else
	{
		a.pos.x = 0;
		a.pos.y = 0;
	}

	printRef.push_back(a);

	printObjCount++;

	last_printPos.x = a.pos.x;
	last_printPos.y = a.pos.y;
	last_print_cursor.x = print_cursor.x;
	last_print_cursor.y = print_cursor.y;

	//print_cursor.x = 0;
	//print_cursor.y = 0;

	//Rectangle pos;
	//pos.x = 0;
	//pos.y = 0;

	//DrawPrint(pos, text);

	//char* t = text;
	//q.push_back(std::bind(drawfont, pos, t)); //https://stackoverflow.com/questions/10565019/c-stdvector-of-stdfunction-with-arbitrary-signatures
}

void DGKCore::dbInput(std::string text, int variable)
{

}

void DGKCore::dbWait(int ms)
{
	//SDL_Delay(ms);
}

void DGKCore::dbSleep(int ms)
{
	//SDL_Delay(ms);
}

void DGKCore::dbWaitKey(void)
{

}

void DGKCore::dbWaitMouse(void)
{

}

void DGKCore::dbSuspendForKey(void)
{

}

void DGKCore::dbSuspendForMouse(void)
{

}

void DGKCore::dbDrawToBack(void)
{

}

void DGKCore::dbDrawToFront(void)
{

}

void DGKCore::dbDrawSpritesFirst(void)
{

}

void DGKCore::dbDrawSpritesLast(void)
{

}

void DGKCore::dbRandomize(int seed)
{

}

int DGKCore::dbRND(int range)
{
	return rand() % (range + 1);
}

float DGKCore::dbCOS(float value)
{
	return cos(value);
}

float DGKCore::dbSIN(float value)
{
	return sin(value);
}

float DGKCore::dbTAN(float value)
{
	return tan(value);
}

float DGKCore::dbACOS(float value)
{
	return acos(value);
}

float DGKCore::dbASIN(float value)
{
	return asin(value);
}

float DGKCore::dbATANFULL(float x, float y)
{
	return atan2(x, y);
}

float DGKCore::dbHCOS(float value)
{
	return cosh(value);
}

float DGKCore::dbHSIN(float value)
{
	return sinh(value);
}

float DGKCore::dbHTAN(float value)
{
	return tanh(value);
}

float DGKCore::dbSQRT(float value)
{
	return sqrt(value);
}

float DGKCore::dbABS(float value)
{
	return abs(value);
}

int DGKCore::dbINT(float value)
{
	return (int)value;
}

float DGKCore::dbEXP(float value)
{
	return NULL;
}

int DGKCore::dbTimer(void)
{
	return NULL;
}

char* DGKCore::dbInKey$(void)
{
	return NULL;
}

char* DGKCore::dbCL$(void)
{
	return NULL;
}

char* DGKCore::dbGetDate$(void)
{
	return NULL;
}

char* DGKCore::dbGetTime$(void)
{
	return NULL;
}

float DGKCore::dbCurveValue(float destination, float curve, float speed)
{
	return NULL;
}

float DGKCore::dbWrapValue(float angle)
{
	return NULL;
}

float DGKCore::dbNewXValue(float x, float angle, float step)
{
	return NULL;
}

float DGKCore::dbNewYValue(float x, float angle, float step)
{
	return NULL;
}

float DGKCore::dbNewZValue(float x, float angle, float step)
{
	return NULL;
}

float DGKCore::dvCurveValue(float fDestination, float fCurve, float fSpeed)
{
	return NULL;
}