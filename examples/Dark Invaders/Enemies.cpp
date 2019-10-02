#include <DarkGameKit.h>
#include "Enemies.h"
#include "Dark Invaders.h"
#include "Player.h"

// have the enemies been created
bool g_bEnemiesSpawned = false;
// speed of enemies on the x axis
int g_iEnemySpeedX = 1;
// speed of enemies of the y axis
int g_iEnemySpeedY = 1;
// place for us to store the old enemy Y so we know how far to move them down
int g_iEnemyOldY = 0;
// array to store the current state of each enemy (alive or dead)
bool g_bEnemiesAlive[5][5];
// quick way for us to tell if every enemy is dead
int g_EnemiesDeadCount = 0;
// used to slow down the animation for exploding an enemy
int g_iExplosionDelay = 0;
// speed of enemy bullets
int g_iEnemyBulletSpeed = 5;
// if the player takes too long completing a level we will add to this variable to speed things up
int g_iEnemySpeedBoost = 0;
// these variables will hold the top left and top right coordinates of the enemies as a group so we know where they are overall
int g_iEnemiesX = 0;
int g_iEnemiesY = 0;

// our different movement modes, right, down and left
enum eEnemiesMove { eEnemiesMoveRight , eEnemiesMoveDown, eEnemiesMoveLeft };

// variable to store which mode is current for our enemies
eEnemiesMove g_eEnemiesMoveMode = eEnemiesMoveRight;

// enemies setup
void enemiesSetup ( void )
{
	// load in an image and create an animated sprite from it
	dbCreateAnimatedSprite ( 10 , "Assets\\alien_anim.png" , 3 , 3 , 10 );
	// lets "clone" the animated sprite we created to make all the other enemies
	// we are going to have 5 rows of 5 enemies altogether
	for ( int i = 11 ; i < 35 ; i++ )
	{
		dbCloneSprite ( 10 , i );
	}
	// check if we have loaded this image already since this routine gets called whenever the game starts
	if ( dbImageExist ( 3 ) == 0 )
		// we havent loaded it already so lets load it
		dbLoadImage ( "Assets\\bolt2.png" , 3 );
	// check if we have created this sprite already
	if ( dbSpriteExist ( 60 ) == 0 )
	{
		// no so lets create and hide it until it is needed
		dbCreateAnimatedSprite ( 60 , "Assets\\saucer_anim.png" , 2 , 2 , 60 );
		dbHideSprite ( 60 );
	}
}

// update all enemies
void enemiesUpdate ( void )
{
	// check if we have created the enemies, if now lets create them
	if ( g_bEnemiesSpawned == false )
		enemiesSpawn();

	// see how much time has passed this level and speed up enemies if needs be
	enemiesTimeCheck();

	// animate enemies
	enemiesAnimate();
	// move enemies
	enemiesMove();
	// decide if the enemies should fire and update any bullets fired
	enemiesFire();
	// check if its time for the saucer / update the saucer
	enemiesSaucer();
}

// create the enemies and set up their initial positions and properties
void enemiesSpawn ( void )
{

	// reset variables
	g_iEnemyOldY = 0;
	g_EnemiesDeadCount = 0;
	g_iExplosionDelay = 0;

	// delete any sprites - "dead" enemies have been swapped to a different image and so loose their "animImage" capability, so we can delete and remake them to turn them back
	for ( int i = 9 ; i < 35 ; i++ )
	{
		if ( dbSpriteExist ( i ) )
			dbDeleteSprite ( i );
	}
	// Delete the image we loaded automatically with dbCreateAnimatedSprite, because we are going to make them again
	if ( dbImageExist ( 10 ) )
		dbDeleteImage ( 10 );
	
	// setup the enemies, load the images and sprites
	enemiesSetup();

	// delete the saucer's explosion sprite
	if ( dbSpriteExist ( 61 ) == 1 )
		dbDeleteSprite ( 61 );

	// set the initial position of all enemy sprites
	// loop through the 5 rows of enemies, 5 in each row
	int iSprite = 10;
	for ( int iY = 0 ; iY < 5 ; iY++ )
	{
		for ( int iX = 0; iX < 5 ; iX++ )
		{
			dbSetSpriteFrame ( iSprite , dbRND ( 7 ) + 1 );
			dbSprite ( iSprite , iX*130 , iY*66 , 10 );
			dbSetSpritePriority ( iSprite++ , 3 );
			// set each enemy to "alive"
			g_bEnemiesAlive[iX][iY] = true;
		}
	}

	// get our initial top left and top right positition of all the enemies as a group, we will from now on update these numbers ourselves
	g_iEnemiesX = dbSpriteX ( 10 );
	g_iEnemiesY = dbSpriteY ( 10 );

	g_bEnemiesSpawned = true;

	g_iEnemySpeedX = g_iLevel;
	// Lets cap the enemies speed at 10 so it doesnt get too mental
	if ( g_iEnemySpeedX > 10 )
		g_iEnemySpeedX = 10;
	// no speed boost yet
	g_iEnemySpeedBoost = 0;
}

// animate our enemies
void enemiesAnimate ( void )
{
	// 10 is the first sprite in our enemies list
	int iSprite = 10;
	// this will hold the enemies currently displayed frame number
	int iFrame;

	// increment the explosion delay, this allows us to slow down the explosion animation
	g_iExplosionDelay++;				

	// loop through the 5 rows of enemies, 5 in each row
	for ( int iY = 0 ; iY < 5 ; iY++ )
	{
		for ( int iX = 0; iX < 5 ; iX++ )
		{
			// if they are alive lets animate them using the animated image we loaded and appied to each one
			if ( g_bEnemiesAlive[iX][iY] )
			{
				iFrame = dbSpriteFrame ( iSprite );
				if ( iFrame < 8 )
					iFrame++;
				else
					iFrame = 1;
				dbSetSpriteFrame ( iSprite , iFrame );
			}
			else
			{
				// they are dead so we texture them with the next frame of the explosion animation which is seperate images
				if ( g_iExplosionDelay > 2 )
				{
					if ( dbSpriteImage ( iSprite ) < 23 )
					{
						dbSprite ( iSprite , dbSpriteX ( iSprite ) , dbSpriteY ( iSprite ) , dbSpriteImage ( iSprite )+1 );
					}
					else if ( dbSpriteVisible ( iSprite ) )
					{
						// once we finished the animation we can hide the departed alien
						dbHideSprite ( iSprite );
						g_EnemiesDeadCount++;
						// if 25 enemies (5 rows of 5) have all been killed, the level is completed
						if ( g_EnemiesDeadCount == 25 )
							g_bPlayerWin = true;
					}
				}
			}
			iSprite++;

		}
	}

	// check the explosion delay, if it is over 2 set it to zero to start the delay again
	if ( g_iExplosionDelay > 2 )
		g_iExplosionDelay = 0;

}

// all the moving of enemies is called from this routine
void enemiesMove ( void )
{
	// pick the direction and call the routine for it
	switch ( g_eEnemiesMoveMode )
	{
	case eEnemiesMoveRight:
		enemiesMoveRight(); break;
	case eEnemiesMoveDown:
		enemiesMoveDown(); break;
	case eEnemiesMoveLeft:
		enemiesMoveLeft(); break;
	}
}

void enemiesMoveRight ( void )
{
	// loop through the 5 rows of enemies, 5 in each row
	int iSprite = 10;
	for ( int iY = 0 ; iY < 5 ; iY++ )
	{
		for ( int iX = 0; iX < 5 ; iX++ )
		{
			// only move if the enemy is still alive
			if ( g_bEnemiesAlive[iX][iY] )
				dbSprite ( iSprite , dbSpriteX ( iSprite ) + (g_iEnemySpeedX + g_iEnemySpeedBoost) , dbSpriteY ( iSprite ) , dbSpriteImage ( iSprite ) );
			iSprite++;
		}
	}

	// update our stored position of the top left of the enemy group as a whole
	g_iEnemiesX += g_iEnemySpeedX + g_iEnemySpeedBoost;

	if ( g_iEnemiesX >= 1024-( 5*130 )-8 + enemiesGetRightOffset() )
	{
		g_iEnemyOldY = g_iEnemiesY;
		g_eEnemiesMoveMode = eEnemiesMoveDown;
	}
}

void enemiesMoveDown ( void )
{
	// loop through the 5 rows of enemies, 5 in each row
	int iSprite = 10;
	for ( int iY = 0 ; iY < 5 ; iY++ )
	{
		for ( int iX = 0; iX < 5 ; iX++ )
		{
			// only move if the enemy is still alive
			if ( g_bEnemiesAlive[iX][iY] )
				dbSprite ( iSprite , dbSpriteX ( iSprite ) , dbSpriteY ( iSprite ) + (g_iEnemySpeedY + g_iEnemySpeedBoost) , dbSpriteImage ( iSprite ) );
			// check if any have made it low enough to end the game
			if ( dbSpriteY ( iSprite ) > 650 - 64 )
			{
				// make sure they are alive first
				if ( g_bEnemiesAlive[iX][iY] == true )
				{
					g_iPlayerLives = 1;
					g_bPlayerHit = true;
				}
			}
			iSprite++;
		}
	}

	// update our stored position of the top left of the enemy group as a whole
	g_iEnemiesY += g_iEnemySpeedY + g_iEnemySpeedBoost;

	if ( g_iEnemiesY - g_iEnemyOldY >= 16 )
	{
		if ( g_iEnemiesX >= 1024-( 5*130 )-8 + enemiesGetRightOffset() )
			g_eEnemiesMoveMode = eEnemiesMoveLeft;
		else
			g_eEnemiesMoveMode = eEnemiesMoveRight;
	}
}

void enemiesMoveLeft ( void )
{
	// loop through the 5 rows of enemies, 5 in each row
	int iSprite = 10;
	for ( int iY = 0 ; iY < 5 ; iY++ )
	{
		for ( int iX = 0; iX < 5 ; iX++ )
		{
			// make sure they are alive first
			if ( g_bEnemiesAlive[iX][iY] )
				dbSprite ( iSprite , dbSpriteX ( iSprite ) - (g_iEnemySpeedX + g_iEnemySpeedBoost) , dbSpriteY ( iSprite ) , dbSpriteImage ( iSprite ) );
			iSprite++;
		}
	}

	// update our stored position of the top left of the enemy group as a whole
	g_iEnemiesX -= g_iEnemySpeedX + g_iEnemySpeedBoost;

	if ( g_iEnemiesX <= 8 - enemiesGetLeftOffset() )
	{
		g_iEnemyOldY = g_iEnemiesY;
		g_eEnemiesMoveMode = eEnemiesMoveDown;
	}
}

void enemiesFire ( void )
{
	// if the player is in the process of being blown up then we wont fire until the player returns to the game
	if ( g_bPlayerHit )
		return;
	// go through each enemy bullet - 3 to 5
	for ( int iBulletSprite = 3 ; iBulletSprite < 6 ; iBulletSprite++ )
	{
		// if the sprite exists then its in the game and needs to be updated
		if ( dbSpriteExist ( iBulletSprite ) )
		{
			dbSprite ( iBulletSprite , dbSpriteX ( iBulletSprite ) , dbSpriteY ( iBulletSprite ) + g_iEnemyBulletSpeed , 3 );
			if ( dbSpriteY ( iBulletSprite ) > 768-32 )
				dbDeleteSprite ( iBulletSprite );
		}
		else
		{
			// if the bullet sprite doesnt exist, lets pick a random number and see if its time to shoot it
			int iRnd = dbRND ( 60 );
			if ( iRnd == 0 )
				// lets add it
				enemyAddBullet( iBulletSprite );
		}
	}

	// check if any bullets have hit the player
	enemyCheckBullets();

}

// time to add an enemy bullet
void enemyAddBullet ( int iBulletSprite )
{
	// we need to pick a collumn
	int iX = dbRND ( 4 );
	
	// then work from the bottom up, the lowest enemy on that collum will be the none that fires, if none are alive in that collumn then no bullet will be added
	for ( int iY = 4 ; iY > -1 ; iY-- )
	{
		if ( g_bEnemiesAlive[iX][iY] )
		{
			int iEnemySprite = (( iY * 5 ) + iX) + 10;
			dbSprite ( iBulletSprite , dbSpriteX ( iEnemySprite ) + 48 , dbSpriteY ( iEnemySprite ) + 32 , 3 );
			return;
		}
	}
}

// check if we have hit the player
void enemyCheckBullets ( void )
{
	// check all bullets ( 3 - 5 )
	for ( int iBulletSprite = 3 ; iBulletSprite < 6 ; iBulletSprite++ )
	{
		if ( dbSpriteExist ( iBulletSprite ) )
		{
			int iPlayerX = dbSpriteX ( 1 ) + 8; // shave a bit off the side of the player to make it more exciting
			int iPlayerY = dbSpriteY ( 1 );
			int iBulletX = dbSpriteX ( iBulletSprite ) + 12;
			int iBulletY = dbSpriteY ( iBulletSprite );

			if ( ( iBulletX > iPlayerX && iBulletX < iPlayerX + dbSpriteWidth ( 1 ) - 16 ) || ( iBulletX + 8 > iPlayerX && iBulletX + 8 < iPlayerX + dbSpriteWidth ( 1 ) - 16 ) )
			{
				if ( ( iBulletY > iPlayerY && iBulletY < iPlayerY + dbSpriteHeight ( 1 ) ) || ( iBulletY + 32 > iPlayerY && iBulletY + 32 < iPlayerY + dbSpriteHeight ( 1 ) ) )
				{
					// yes we have, play the explosion sound and set the player to be hit
					dbPlaySound ( 3 );
					g_bPlayerHit = true;
				}
			}

		}
	}

	// if enemy has shot the player we delete all bullets so the player has a "safe" evironment to come back to
	if ( g_bPlayerHit == true )
	{
		for ( int iBulletSprite = 3 ; iBulletSprite < 6 ; iBulletSprite++ )
		{
			if ( dbSpriteExist ( iBulletSprite ) )
				dbDeleteSprite ( iBulletSprite );
		}
	}

}

// we need the enemies to go tightly to the left edge, so if some commumns have been destroyed we create an offset to show us how much further we need to move the enemies
int enemiesGetLeftOffset ( void )
{

	int iLeftOffset = 0;

	for ( int iX = 0 ; iX < 5 ; iX++ )
	{
		for ( int iY = 0; iY < 5 ; iY++ )
		{
			// if an enemy is alive in that row we can return from this function
			if ( g_bEnemiesAlive[iX][iY] == true )
				return iLeftOffset;
		}
		// whole collumn is dead so add the width of a collum to the offset
		iLeftOffset += 130;
	}
	return iLeftOffset;
}

// we need the enemies to go tightly to the right edge, so if some commumns have been destroyed we create an offset to show us how much further we need to move the enemies
int enemiesGetRightOffset ( void )
{

	int iRightOffset = 0;

	for ( int iX = 4 ; iX > -1 ; iX-- )
	{
		for ( int iY = 0; iY < 5 ; iY++ )
		{
			// if an enemy is alive in that row we can return from this function
			if ( g_bEnemiesAlive[iX][iY] == true )
				return iRightOffset;
		}
		// whole collumn is dead so add the width of a collum to the offset
		iRightOffset += 130;
	}

	return iRightOffset;
}

void enemiesSaucer ( void )
{
	// if the enemies are down the screen past 64 then there is a chance the saucer can show up
	// it will only show up if it is not currently visible, and isnt in the process of blowing up
	if ( g_iEnemiesY > 64 && dbSpriteVisible ( 60 ) == 0 && dbSpriteExist ( 61 ) == 0 )
	{
		if ( dbRND(800) == 0 )
		{
			// time to show and move the saucer
			dbSprite ( 60 , 1024 , 0 , 60 );
			dbShowSprite ( 60 );
			dbLoopSound ( 4 );
		}
	}

	// if the saucer is shown, lets move it
	if ( dbSpriteVisible ( 60 ) == 1 )
	{
		dbSprite ( 60 , dbSpriteX ( 60 ) - 2 , dbSpriteY ( 60 ) , 60 );
		dbSetSpriteFrame ( 60 , dbSpriteFrame ( 60 ) + 1 );
		if ( dbSpriteFrame ( 60 ) > 4 )
			dbSetSpriteFrame ( 60 , 1 );

		if ( dbSpriteX ( 60 ) < -128 )
		{
			dbStopSound ( 4 );
			dbHideSprite ( 60 );
		}
	}

	// if sprite 61 exists that means the saucer has been shot by the player, so we animate the explosion
	if ( dbSpriteExist ( 61 ) == 1 )
	{
		if ( dbSpriteVisible ( 61 ) == 1 )
		{
			if ( dbSpriteImage ( 61 ) < 23 )
			{
				dbSprite ( 61 , dbSpriteX ( 61 ) , dbSpriteY ( 61 ) , dbSpriteImage ( 61 )+1 );
			}
			else
			{
				dbStopSound ( 4 );
				dbDeleteSprite ( 61 );
			}
		}
	}

}

// check how much time has elapsed this level
// 1000 miliseconds = 1 second.
void enemiesTimeCheck ( void )
{
	int iTimeElapsed = dbTimer() - g_iLevelStartTime;

	if ( iTimeElapsed > 30*1000 )
		g_iEnemySpeedBoost = 1;

	if ( iTimeElapsed > 60*1000 )
		g_iEnemySpeedBoost = 2;

	if ( iTimeElapsed > 90*1000 )
		g_iEnemySpeedBoost = 4;

	if ( iTimeElapsed > 120*1000 )
		g_iEnemySpeedBoost = 10;

}

