#pragma once

void enemiesSetup ( void );
void enemiesUpdate ( void );
void enemiesSpawn ( void );
void enemiesAnimate ( void );
void enemiesMove ( void );
void enemiesMoveRight ( void );
void enemiesMoveDown ( void );
void enemiesMoveLeft ( void );
void enemiesFire ( void );
void enemyAddBullet ( int iSprite );
void enemyCheckBullets ( void );
int enemiesGetLeftOffset ( void );
int enemiesGetRightOffset ( void );
void enemiesSaucer ( void );
void enemiesTimeCheck ( void );

extern bool g_bEnemiesSpawned;
extern int g_iEnemySpeedX;
extern int g_iEnemySpeedY;
extern int g_iEnemyOldY;
extern bool g_bEnemiesAlive[5][5];
extern int g_EnemiesDeadCount;