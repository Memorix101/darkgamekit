#pragma once
#include "DGKBase.h"

void dbPerformCheckListForGraphicsCards ( void );
void dbPerformCheckListForDisplayModes ( void );
void dbSetDisplayMode ( int iWidth, int iHeight, int iDepth );
void dbSetGraphicsCard ( char* szName );
void dbSetGamma ( int iRed, int iGreen, int iBlue );

void dbShowWindow ( void );
void dbHideWindow ( void );
void dbMaximizeWindow  ( void );
void dbMinimizeWindow ( void );
void dbRestoreWindow ( void );
void dbSetWindowOn ( void );
void dbSetWindowOff ( void );
void dbSetWindowSize ( int iWidth, int iHeight );
void dbSetWindowTitle ( char* szString );
void dbSetWindowLayout ( int iStyle, char* szCaption, int iIcon );
void dbSetWindowPosition ( int iX, int iY );

void dbLockBackBuffer ( void );
void dbUnlockBackBuffer ( void );

int dbScreenType ( void );
int dbScreenWidth ( void );
int dbScreenHeight ( void );
int dbScreenDepth ( void );
int dbScreenInvalid ( void );
int dbScreenFPS ( void );

char* dbCurrentGraphicsCard$ ( void );
int dbCheckDisplayMode ( int iWidth, int iHeight, int iDepth );

int dbGetBackBufferPtr ( void );
int dbGetBackBufferWidth ( void );
int dbGetBackBufferHeight ( void );
int dbGetBackBufferDepth ( void );
int dbGetBackBufferPitch ( void );