#pragma once

void playerSetup ( void );
void playerUpdate ( void );
void playerAnimate ( void );
void playerReset ( void );
bool playerLevelStart ( void );
bool playerLevelStart2 ( void );
void playerUpdateFire ( void );
void playerCheckHitEnemies ( void );
bool playerDie ( void );
void playerShowLives ( void );
void playerUpdateScore ( void );

extern int iPlayerX;
extern int iPlayerY;
extern int iPlayerSpeed;
extern int iPlayerFrame;
extern int iFrameAnimateDelay;
extern bool bPlayerIsFiring;
extern int iPlayerBulletY;
extern bool g_bPlayerWin;
extern bool g_bPlayerHit;
extern int g_iPlayerDieFrame;
extern int g_iPlayerLives;
extern int g_iPlayerScore;