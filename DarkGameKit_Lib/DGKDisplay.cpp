#include "DGKDisplay.h"
#include <cstddef>

void dbPerformCheckListForGraphicsCards ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbPerformCheckListForDisplayModes ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetDisplayMode ( int iWidth, int iHeight, int iDepth )
{
	window_width = iWidth;
	window_height = iHeight;
	SetWindowSize(window_width, window_height);
	SetWindowPosition(GetMonitorWidth(0)/2 - window_width/2, GetMonitorHeight(0)/2 - window_height/2);
}

void dbSetGraphicsCard ( char* szName )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetGamma ( int iRed, int iGreen, int iBlue )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbShowWindow ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbHideWindow ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbMaximizeWindow ( void )
{
	ToggleFullscreen();
}

void dbMinimizeWindow ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbRestoreWindow ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetWindowOn ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetWindowOff ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetWindowSize ( int iWidth, int iHeight )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetWindowTitle ( char* szString )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetWindowLayout ( int iStyle, char* szCaption, int iIcon )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetWindowPosition ( int iX, int iY )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbLockBackBuffer ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbUnlockBackBuffer ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

int dbScreenType ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbScreenWidth ( void )
{
	return window_width;
}

int dbScreenHeight ( void )
{
	return window_height;
}

int dbScreenDepth ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbScreenInvalid ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbScreenFPS ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

char* dbCurrentGraphicsCard$ ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbCheckDisplayMode ( int iWidth, int iHeight, int iDepth )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbGetBackBufferPtr ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}
int dbGetBackBufferWidth ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbGetBackBufferHeight ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbGetBackBufferDepth ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbGetBackBufferPitch ( void )
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}