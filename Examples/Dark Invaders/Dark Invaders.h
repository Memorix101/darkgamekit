#pragma once

void game ( void );
void gameSetup ( void );
void gameReset ( void );
void gameTitle( void );
void gameWaitForFire ( void );
void gameLevel ( void );
void gameLevelWait ( void );
void gameLevelWait2 ( void );
void gamePlay ( void );
void gameWin( void );
void gameDie ( void );
void gameOver ( void );

extern int g_iLevel;
extern int g_iLevelStartTime;