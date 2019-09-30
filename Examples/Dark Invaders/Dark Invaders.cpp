
// Dark GDK - The Game Creators - www.thegamecreators.com

// Dark Invaders by Dave "Ravey" Milton

// Converted to DarkGameKit by Memorix101 - https://gitlab.com/Memorix101/darkgamekit

#include "../../DarkGameKit_Lib/DarkGameKit.h"
#include "Dark Invaders.h"
#include "backdrop.h"
#include "Invader Text.h"
#include "Input.h"
#include "Player.h"
#include "Sound.h"
#include "Enemies.h"

#pragma comment(lib, "DarkGameKit.lib")

// these are the different modes throughout the game which can be set when the player starts, dies, clears a level etc. It will make the game flow from one phase to the next
// much easier to manage
enum  eMode { eGameSetup, eGameReset, eGameTitle, eGameWaitForFire, eGameLevel, eGameLevelWait, eGameLevelWait2, eGamePlay, eGameDie, eGameWin, eGameOver };
eMode g_eGameMode = eGameSetup;

// the level we are currently on
int g_iLevel = 1;
// we will use this to store what time we started the level, in the enemies.cpp we check how much time has expired, and increase enemy speed dependant on exactly
// how much time has passed
int g_iLevelStartTime = 0;

class Game1 : public DarkGameKit {

	// our "main"  - nice and small
	/*void DarkGDK(void)
	{

		// our main gdk loop
		while (LoopGDK())
		{
			// the game itself
			game();
			// dbSync will wait for the screen to finish drawing, and then draw our whole scene for us
			dbSync();
		}

	}*/

	DGKCore Core;

	void DarkGDK() override
	{

	}

	void LoopGDK() override
	{
		// the game itself
		game();
		// dbSync will wait for the screen to finish drawing, and then draw our whole scene for us
		dbSync();
	}

	int main(int argc, char* argv[])
	{
		DarkGameKit* game1 = new Game1;
		game1->Init();
		game1->Run();

		return 0;
	}
};

// the game loop
void game(void)
{
	// lets find out which game mode we are in and call the appropiate routine
	// from here we can easily see the different parts that make up the game
	switch (g_eGameMode)
	{
		// initial setting up of the game
	case eGameSetup:
		gameSetup(); break;

		// resetting the game after the player looses a life, or before a new game starts
	case eGameReset:
		gameReset(); break;

		// display the main title screen
	case eGameTitle:
		gameTitle(); break;

		// wait for the player to press fire to start
	case eGameWaitForFire:
		gameWaitForFire(); break;

		// display the new level screen
	case eGameLevel:
		gameLevel(); break;

		// wait for player to press fire to start the level
	case eGameLevelWait:
		gameLevelWait(); break;

		// animate the ship flying off to the new level
	case eGameLevelWait2:
		gameLevelWait2(); break;

		// the game itself!
	case eGamePlay:
		gamePlay(); break;

		// player has completed a level!
	case eGameWin:
		gameWin(); break;

		// player has lost a life
	case eGameDie:
		gameDie(); break;

		// player has lost all lives, Game Over!
	case eGameOver:
		gameOver(); break;
	}

	// call our scrolling routine to update the backdrops
	backdropUpdate();

}

// one time game setup on first run, load in everything we need
void gameSetup(void)
{
	// set the display to 1024 x 768 with 32bit depth
	dbSetDisplayMode(1024, 768, 32);
	// turn sync on, so our game waits for the screen to finish drawing before displaying, also handles backbuffer automatically for us
	dbSyncOn();
	// lets run at a nice 60 frames per second - automatically!
	dbSyncRate(60);
	// full screen windowed mode
	dbMaximiseWindow();

	// set up our text drawing routine
	invaderTextSetup();
	// set up out backdrop routine
	backdropSetup();
	// set up the player graphics
	playerSetup();
	// set up the sounds we will use
	soundSetup();

	// switch to game title mode
	g_eGameMode = eGameTitle;
}

// reset the game after a life is lost or level complete
void gameReset(void)
{
	// stop the background sound playing
	dbStopSound(5);
	// start the title screen sound and change the speed it plays back for a different effect
	dbSetSoundSpeed(1, 2000);
	dbPlaySound(1);
	// change the speed the backdrops scroll at for a different visual effect
	g_fBackdropSpeed = 2.0f;

	// reset the player and enemies
	g_bPlayerWin = false;
	g_bEnemiesSpawned = false;
	playerReset();

	// set the mode to wait for the player to press fire
	g_eGameMode = eGameWaitForFire;

}

// display our game title
void gameTitle(void)
{
	// call our custom text routine to display our title text
	InvaderText(0, 340, 32, "DARK INVADERS", true, false);
	InvaderText(0, 400, 16, "PRESS FIRE TO START", true, false);
	// change the speed of background sound to give a different sound
	dbSetSoundSpeed(1, 2000);
	dbPlaySound(1);
	// change the speed of backdrop scrolling again
	g_fBackdropSpeed = 2.0f;
	// set players starting lives to 5
	g_iPlayerLives = 5;

	// reset player statistics and reset the level to 1 for a new game
	g_bPlayerWin = false;
	g_bEnemiesSpawned = false;
	playerReset();
	g_iPlayerScore = 0;
	g_iLevel = 1;

	// wait for the user to press fire
	g_eGameMode = eGameWaitForFire;
}

// wait for fire to be pressed
void gameWaitForFire(void)
{

	if (checkFire())
	{
		// once fire is pressed update the player score using our custom text
		playerUpdateScore();
		// switch to display the level screen
		g_eGameMode = eGameLevel;
	}
}

// display the level screen
void gameLevel(void)
{
	// use our custom text routine to display the level
	char czLevel[20];
	sprintf(czLevel, "LEVEL %d", g_iLevel);
	InvaderText(0, 340, 32, czLevel, true, true);
	// change the sound speed of sound 1 again to give a different twist on the sound
	dbSetSoundSpeed(1, 8000);
	dbPlaySound(1);
	// change the scrolling speed of the backdrops
	g_fBackdropSpeed = 8.0f;
	// show the player lives on screen
	playerShowLives();

	// wait for the user to press fire
	g_eGameMode = eGameLevelWait;
}

// move the player up the screen until it passes out of view
void gameLevelWait(void)
{
	// has the player gone out of view?
	if (playerLevelStart() == true)
	{
		// yes so switch to second stage
		g_eGameMode = eGameLevelWait2;
	}
}

// move the player from the bottom back to its normal position
void gameLevelWait2(void)
{
	// is the player in position?
	if (playerLevelStart2() == true)
	{
		// yes so change the backdrop scrolling for the speed we want "in game"
		g_fBackdropSpeed = 1.0f;
		// update player score
		playerUpdateScore();
		// loop our atompsheric sound effect
		dbLoopSound(5);
		// Lets store when the level starts so we can speed things up after a while to punish them for taking their time
		g_iLevelStartTime = dbTimer();
		// lets go play
		g_eGameMode = eGamePlay;
	}
}

// main gameplay loop
void gamePlay(void)
{

	// update the player
	playerUpdate();

	// update the enemies
	enemiesUpdate();

	// if the player has killed all enemies go to the level win screen
	if (g_bPlayerWin)
		g_eGameMode = eGameWin;

	// if the player has been hit, hide the player sprite and go to the die routine to show the player exploding
	if (g_bPlayerHit == true)
	{
		// delete any enemy bullets so the player doesnt return to the game and get killed instantly
		for (int iBulletSprite = 3; iBulletSprite < 6; iBulletSprite++)
		{
			if (dbSpriteExist(iBulletSprite))
				dbDeleteSprite(iBulletSprite);
		}
		dbHideSprite(1);
		g_eGameMode = eGameDie;
	}
}

// player has cleared the level
void gameWin(void)
{
	// hide the saucer
	dbHideSprite(60);
	// stop the saucer sound
	dbStopSound(4);
	// delete all bullets both player (2) and enemies (3-5)
	for (int iBulletSprite = 2; iBulletSprite < 6; iBulletSprite++)
	{
		if (dbSpriteExist(iBulletSprite))
			dbDeleteSprite(iBulletSprite);
	}
	// use our custom text routine to show the level is completed
	InvaderText(0, 340, 32, "LEVEL COMPLETE!", true, false);
	InvaderText(0, 400, 16, "PRESS FIRE", true, false);

	// increase the level by 1
	g_iLevel++;

	// reset the game
	g_eGameMode = eGameReset;
}

// player has lost a life
void gameDie(void)
{
	// player can keep shooting
	playerUpdateFire();
	// update enemies (they will not fire while the player is out of action
	enemiesUpdate();
	// has the explosion of the player completed?
	if (playerDie() == true)
	{
		// decrease players lives by 1
		g_iPlayerLives--;
		// update how many lives the player has left
		playerShowLives();
		// show the player sprite again
		dbShowSprite(1);
		// reset the fact he was hit
		g_bPlayerHit = false;
		// if the player still has a life lets carry on, if not its game over
		if (g_iPlayerLives > 0)
			g_eGameMode = eGamePlay;
		else
			g_eGameMode = eGameOver;
	}
}

// game over
void gameOver(void)
{
	// hide the saucer
	dbHideSprite(60);
	// stop the saucer sound
	dbStopSound(4);
	// stop atmospheric sound
	dbStopSound(5);
	// updaye the player score on screen using our custom text routine
	playerUpdateScore();
	// show the game over text and the players final score
	char szScore[20];
	sprintf(szScore, "YOU SCORED: %d", g_iPlayerScore);
	InvaderText(0, 340, 32, "GAME OVER!", true, false);
	InvaderText(0, 400, 32, szScore, true, false);
	// change the speed of our title screen sound and player it
	dbSetSoundSpeed(1, 2000);
	dbPlaySound(1);
	// clean up enemies
	for (int iEnemy = 10; iEnemy < 35; iEnemy++)
	{
		if (dbSpriteExist(iEnemy))
			dbDeleteSprite(iEnemy);
	}
	// clean up all bullets
	for (int iBullet = 2; iBullet < 6; iBullet++)
	{
		if (dbSpriteExist(iBullet))
			dbDeleteSprite(iBullet);
	}
	// call sync to display the screen (we call it here because we are going to wait for a while before going back to the title screen)
	dbSync();
	// wait for 5 seconds (1000 milliseconds = 1 second)
	dbWait(5000);
	// clear all custom text
	invaderTextClear();
	// head back to the title screen
	g_eGameMode = eGameTitle;
}
