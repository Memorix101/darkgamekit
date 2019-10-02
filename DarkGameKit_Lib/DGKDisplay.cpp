#include "DGKDisplay.h"
#include <cstddef>

void dbPerformCheckListForGraphicsCards ( void ){ }
void dbPerformCheckListForDisplayModes ( void ){ }
void dbSetDisplayMode ( int iWidth, int iHeight, int iDepth )
{
	window_width = iWidth;
	window_height = iHeight;
	SetWindowSize(window_width, window_height);
	SetWindowPosition(GetMonitorWidth(0)/2 - window_width/2, GetMonitorHeight(0)/2 - window_height/2);
}

void dbSetGraphicsCard ( char* szName ){ }
void dbSetGamma ( int iRed, int iGreen, int iBlue ){ }

void dbShowWindow ( void ){ }
void dbHideWindow ( void ){ }

void dbMaximizeWindow ( void )
{
	ToggleFullscreen();
}

void dbMinimizeWindow ( void ){ }
void dbRestoreWindow ( void ){ }
void dbSetWindowOn ( void ){ }
void dbSetWindowOff ( void ){ }
void dbSetWindowSize ( int iWidth, int iHeight ){ }
void dbSetWindowTitle ( char* szString ){ }
void dbSetWindowLayout ( int iStyle, char* szCaption, int iIcon ){ }
void dbSetWindowPosition ( int iX, int iY ){ }

void dbLockBackBuffer ( void ){ }
void dbUnlockBackBuffer ( void ){ }

int dbScreenType ( void )
{
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
	return NULL;
}

int dbScreenInvalid ( void )
{
	return NULL;
}

int dbScreenFPS ( void )
{
	return NULL;
}

char* dbCurrentGraphicsCard$ ( void )
{
	return NULL;
}

int dbCheckDisplayMode ( int iWidth, int iHeight, int iDepth )
{
	return NULL;
}

int dbGetBackBufferPtr ( void )
{
	return NULL;
}
int dbGetBackBufferWidth ( void )
{
	return NULL;
}

int dbGetBackBufferHeight ( void )
{
	return NULL;
}

int dbGetBackBufferDepth ( void )
{
	return NULL;
}

int dbGetBackBufferPitch ( void )
{
	return NULL;
}