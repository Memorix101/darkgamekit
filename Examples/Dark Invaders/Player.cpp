#include "DarkSDK.h"
#include "Player.h"
#include "Input.h"
#include "Enemies.h"
#include "Invader Text.h"

// player variables
// Player X position
int iPlayerX = 448;
// player Y position
int iPlayerY = 650;
// speed the player should move
int iPlayerSpeed = 5;
// current frame the player is on
int iPlayerFrame = 7;
// we increment this to form a delay for out animation
int iFrameAnimateDelay = 0;
// set true if the player is currently firing a bullet
bool bPlayerIsFiring = false;
// the y position of the player bullet
int iPlayerBulletY = 0;
// player has cleared the level if this is true
bool g_bPlayerWin = false;
// player has lost a life if this is true (or game over if no lives)
bool g_bPlayerHit = false;
// what frame of animation the dead player is showing of the explosion frames
int g_iPlayerDieFrame = 1;
// the delay for the player explosion frames
int g_iPlayerExplosionDelay = 0;
// how many lives the player has
int g_iPlayerLives = 5;
// the players score
int g_iPlayerScore = 0;

// player directions
const int STRAIGHT = 0 , LEFT = 1 , RIGHT = 2;

int iPlayerDirection = STRAIGHT;

// set up the animated sprite for the player and load in the explosion images as well as lazer bolt and the icon for a lives display
void playerSetup ( void )
{
	// the player animated sprite
	dbCreateAnimatedSprite ( 1 , "Assets\\ship_anim.png" , 3 , 3 , 1 );
	dbSprite ( 1 , iPlayerX , iPlayerY , 1 );
	dbSetSpriteFrame ( 1 , iPlayerFrame );
	dbSetSpritePriority ( 1 , 2 );

	// the images for explosions
	dbLoadImage ( "Assets\\boom0001.png" , 11 );
	dbLoadImage ( "Assets\\boom0002.png" , 12 );
	dbLoadImage ( "Assets\\boom0003.png" , 13 );
	dbLoadImage ( "Assets\\boom0004.png" , 14 );
	dbLoadImage ( "Assets\\boom0005.png" , 15 );
	dbLoadImage ( "Assets\\boom0006.png" , 16 );
	dbLoadImage ( "Assets\\boom0007.png" , 17 );
	dbLoadImage ( "Assets\\boom0008.png" , 18 );
	dbLoadImage ( "Assets\\boom0009.png" , 19 );
	dbLoadImage ( "Assets\\boom0010.png" , 20 );
	dbLoadImage ( "Assets\\boom0011.png" , 21 );
	dbLoadImage ( "Assets\\boom0012.png" , 22 );

	// player bullet
	dbLoadImage ( "Assets\\bolt.png" , 2 );
	// ship icon to use for showing how many lives we have left
	dbLoadImage ( "Assets\\shipicon.png" , 40 );
}

// update the player in game
void playerUpdate ( void )
{
	// see if the player ship needs to try and go left
	if ( checkLeft() )
	{
		iPlayerX -= iPlayerSpeed;
		if ( iPlayerX < 0 )
			iPlayerX = 0;
		iPlayerDirection = LEFT;
	}
	// see if the player ship needs to try and go right
	else if ( checkRight() )
	{
		iPlayerX += iPlayerSpeed ;
		if ( iPlayerX > 1024 - 128 )
			iPlayerX = 1024 - 128;
		iPlayerDirection = RIGHT;
	}
	// not left or right, so lets face straight
	else
		iPlayerDirection = STRAIGHT;

	// animate the player
	playerAnimate();
	// check for player firing and update firing if a bullet is already in action
	playerUpdateFire();

	// place the player sprite at it's correct location
	dbSprite ( 1 , iPlayerX , iPlayerY , 1 );
	// set the frame the player sprite should show
	dbSetSpriteFrame ( 1 , iPlayerFrame );
}

// animate the player ship dependant on which direction we are going
void playerAnimate ( void )
{
	// firstly increment the animation delay
	iFrameAnimateDelay++;
		if ( iFrameAnimateDelay > 2 )
		{
			// reset the delay and lets go animate
			iFrameAnimateDelay = 0;
			switch ( iPlayerDirection )
			{
			case STRAIGHT:
				{
					// if we were heading left
					if ( iPlayerFrame < 3 )
						iPlayerFrame++;
					// if we were heading right
					else if ( iPlayerFrame > 4 && iPlayerFrame < 7 )
						iPlayerFrame--;
					else iPlayerFrame = 7;

				} break;
			case LEFT:
				{
					// lets animate to lean to the left
					if ( iPlayerFrame == 7 )
						iPlayerFrame = 3;
					else if ( iPlayerFrame > 1 )
						iPlayerFrame--;
				} break;
			case RIGHT:
				{
					// lean the ship to the right
					if ( iPlayerFrame == 7 )
						iPlayerFrame = 4;
					else if ( iPlayerFrame < 6 )
						iPlayerFrame++;
				} break;
			}
		}
}

// reset all the players variables back to default and place the player sprite there
void playerReset ( void )
{
	iPlayerX = 448;
	iPlayerY = 650;
	iPlayerSpeed = 5;
	iPlayerFrame = 7;
	iFrameAnimateDelay = 0;
	dbSprite ( 1 , iPlayerX , iPlayerY , 1 );
	dbSetSpriteFrame ( 1 , iPlayerFrame );
	g_bPlayerHit = false;
}

// move player ship past the top of the screen
bool playerLevelStart ( void )
{
	dbMoveSprite ( 1 , 8 );

	if ( dbSpriteY( 1 ) <= 0 )
	{
		dbSprite ( 1 , iPlayerX , 768 , 1 );
		return true;
	}
	else
		return false;

}

// move player ship from beneath the bottom back to its usual spot
bool playerLevelStart2 ( void )
{
	dbMoveSprite ( 1 , 8 );

	if ( dbSpriteY( 1 ) < iPlayerY )
	{
		dbSprite ( 1 , iPlayerX , iPlayerY , 1 );
		return true;
	}
	else
		return false;

}

// update player bullets and check for fire
void playerUpdateFire ( void )
{
	// are we already firing? if so lets update
	if ( bPlayerIsFiring )
	{
		iPlayerBulletY -= 8;
		dbSprite ( 2 , dbSpriteX ( 2 ) , iPlayerBulletY , 2 );
		// have we hit anything?
		playerCheckHitEnemies();
		if ( iPlayerBulletY < 1 )
		{
			dbDeleteSprite ( 2 );
			bPlayerIsFiring = false;
		}
	}

	// if we arent currently shooting and have pressed fire - lets shoot a bullet
	if ( checkFire() == true && bPlayerIsFiring == false )
	{
		bPlayerIsFiring = true;
		dbPlaySound ( 2 );
		iPlayerBulletY = iPlayerY-32;
		dbSprite ( 2 , iPlayerX + 48 , iPlayerBulletY , 2 );
		dbSetSpritePriority ( 2 , 1 );
	}
}

// has out bullet hit any enemies?
void playerCheckHitEnemies ( void )
{
	int iBulletX = dbSpriteX ( 2 ) + 12;
	int iBulletY = dbSpriteY ( 2 );
	int iEnemyX;
	int iEnemyY;
	int iEnemySprite = 9;

	// check bullet against all enemies
	for ( int iY = 0 ; iY < 5 ; iY++ )
	{
		for ( int iX = 0; iX < 5 ; iX++ )
		{
			iEnemySprite++;
			if ( g_bEnemiesAlive[iX][iY] == false )
				continue;
			iEnemyX = dbSpriteX ( iEnemySprite );
			iEnemyY = dbSpriteY ( iEnemySprite );

			// have we scored a hit?
			if ( ( iBulletX > iEnemyX && iBulletX < iEnemyX + dbSpriteWidth ( iEnemySprite ) ) || ( iBulletX + 8 > iEnemyX && iBulletX + 8 < iEnemyX + dbSpriteWidth ( iEnemySprite ) ) )
			{
				if ( ( iBulletY > iEnemyY && iBulletY < iEnemyY + dbSpriteHeight ( iEnemySprite ) ) || ( iBulletY + 32 > iEnemyY && iBulletY + 32 < iEnemyY + dbSpriteHeight ( iEnemySprite ) ) )
				{
					// yes! we have hit an enemy, lets increase the score and blow that enemy up
					dbPlaySound ( 3 );
					// delete the sprite
					dbDeleteSprite ( iEnemySprite );
					// make a new sprite to show the explosion
					dbSprite ( iEnemySprite , iEnemyX , iEnemyY , 11 );
					iPlayerBulletY = -1;
					g_bEnemiesAlive[iX][iY] = false;
					// add and display the new score
					g_iPlayerScore += 100;
					playerUpdateScore();
					return;
				}
			}
		}
	}

	// lastly check if we hit the saucer if it's flying past
	if ( dbSpriteVisible ( 60 ) == 1 )
	{
		iEnemySprite = 60;
		iEnemyX = dbSpriteX ( iEnemySprite );
		iEnemyY = dbSpriteY ( iEnemySprite );

		// have we hit the saucer?
		if ( ( iBulletX > iEnemyX && iBulletX < iEnemyX + dbSpriteWidth ( iEnemySprite ) ) || ( iBulletX + 8 > iEnemyX && iBulletX + 8 < iEnemyX + dbSpriteWidth ( iEnemySprite ) ) )
		{
			if ( ( iBulletY > iEnemyY && iBulletY < iEnemyY + dbSpriteHeight ( iEnemySprite ) ) || ( iBulletY + 32 > iEnemyY && iBulletY + 32 < iEnemyY + dbSpriteHeight ( iEnemySprite ) ) )
			{
				// yes to lets blow it up and update score
				dbPlaySound ( 3 );
				dbHideSprite ( iEnemySprite );
				dbSprite ( iEnemySprite+1 , iEnemyX , iEnemyY , 11 );
				iPlayerBulletY = -1;
				// update and display the new score
				g_iPlayerScore += 2000;
				playerUpdateScore();
				return;
			}
		}
	}

}

// player has died, play back the explosion animation
bool playerDie ( void )
{

	// if the sprite doesnt exist we havent started the animation yet
	if ( dbSpriteExist ( 6 ) == 0 )
	{
		// lets set the frame to the correct one
		g_iPlayerDieFrame = 11;
		// set up the explosion sprite (player sprite is currently hidden)
		dbSprite ( 6 , dbSpriteX ( 1 ) , dbSpriteY ( 1 ) , g_iPlayerDieFrame );
		return false;
	}
	else
	{
		// carry on the animation we started previously
		// increment the explosion delay
		g_iPlayerExplosionDelay++;
		if ( g_iPlayerExplosionDelay > 2 )
		{
			// increment the next frame to show
			g_iPlayerDieFrame++;
			g_iPlayerExplosionDelay = 0;
		}
		// show the explosion if we havent finished it yet
		if ( g_iPlayerDieFrame < 23 )
		{
			dbSprite ( 6 , dbSpriteX ( 1 ) , dbSpriteY ( 1 ) , g_iPlayerDieFrame );
			return false;
		}
		else
		{
			// we have finished the explosion
			g_iPlayerExplosionDelay = 0;
			// delete the explosion sprite and return true
			dbDeleteSprite ( 6 );
			return true;
		}

	}
}

// display how many lives the player has remaining on screen
void playerShowLives ( void )
{
	// firstly clean up any sprites we have already used for this
	for ( int i = 0 ; i < 5 ; i++ )
	{
		if ( dbSpriteExist ( 40 + i ) )
			dbDeleteSprite ( 40 + i );
	}

	// now make the right amount of sprites for how many lives we have
	int iX = 1024-70;
	for ( int iLife = 0 ; iLife < g_iPlayerLives-1 ; iLife++ )
	{
		dbSprite ( iLife + 40 , iX , 768-35 , 40 );
		iX -= 54;
	}
}

// update the players score on screen
void playerUpdateScore ( void )
{
	// first clear up any text shown
	invaderTextClear();
	char czScore[20];
	sprintf ( czScore , "%d" , g_iPlayerScore );
	// display the score
	InvaderText ( 0 , 730 , 32 , czScore , false , false );
}
