#include "DGKCore.h"

Rectangle print_cursor;
Rectangle last_print_cursor;
Rectangle last_printPos;
int DGKPrintCount;

//std::vector<std::function<void()>> q;

/*DGKCore()
{
	print_cursor.x = 0;
	print_cursor.y = 0;
	print_cursor.width = 0;
	print_cursor.height = 0;

	last_printPos.x = 0;
	last_printPos.y = 0;
	last_printPos.width = 0;
	last_printPos.height = 0;

	DGKPrintCount = 0;
}*/

void dbSyncOn()
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSyncOff()
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSync()
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSyncRate(int rate)
{
	SetTargetFPS(rate); // Set our game to run at 60 frames-per-second
}

void dbFastsync(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbCLS(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetCursor(int x, int y)
{
	print_cursor.x = x;
	print_cursor.y = y;
}

void dbPrint(std::string text)
{
	DGKPrint a;
	a.text = text;

	if (print_cursor.y != last_print_cursor.y)// && last_printPos.y == ((printFontHeight)* DGKPrintCount))
	{
		DGKPrintCount = 0;
	}

	if (!printRef.empty()) {
		if (!fontScrolling) {
			a.pos.x = print_cursor.x;;
			if (print_cursor.y == 0) {
				a.pos.y = 0 + ((printFontHeight)*DGKPrintCount);// +(last_printPos.y));// * printRef.size()); 
				// 0 + 15 defaultFontHeight * printRef.size() = 0 ...
			}
			else
			{
				a.pos.y = print_cursor.y + ((printFontHeight) * (DGKPrintCount));
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
				a.pos.y = print_cursor.y + ((printFontHeight) * (DGKPrintCount));
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

	//std::cout << " printRef.size() " << printRef.size() << std::endl;
	printRef.push_back(a);

	DGKPrintCount++;

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

void dbInput(std::string text, int variable)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbWait(int ms)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSleep(int ms)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbWaitKey(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbWaitMouse(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSuspendForKey(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSuspendForMouse(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbDrawToBack(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbDrawToFront(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbDrawSpritesFirst(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbDrawSpritesLast(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbRandomize(int seed)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

int dbRND(int range)
{
	return rand() % (range + 1);
}

float dbCOS(float value)
{
	return cos(value);
}

float dbSIN(float value)
{
	return sin(value);
}

float dbTAN(float value)
{
	return tan(value);
}

float dbACOS(float value)
{
	return acos(value);
}

float dbASIN(float value)
{
	return asin(value);
}

float dbATANFULL(float x, float y)
{
	return atan2(x, y);
}

float dbHCOS(float value)
{
	return cosh(value);
}

float dbHSIN(float value)
{
	return sinh(value);
}

float dbHTAN(float value)
{
	return tanh(value);
}

float dbSQRT(float value)
{
	return sqrt(value);
}

float dbABS(float value)
{
	return abs(value);
}

int dbINT(float value)
{
	return (int)value;
}

float dbEXP(float value)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbTimer(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

char* dbInKey$(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

char* dbCL$(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

char* dbGetDate$(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

char* dbGetTime$(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbCurveValue(float destination, float curve, float speed)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbWrapValue(float angle)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbNewXValue(float x, float angle, float step)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbNewYValue(float x, float angle, float step)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbNewZValue(float x, float angle, float step)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dvCurveValue(float fDestination, float fCurve, float fSpeed)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}