
#include <cstddef>
#include "DGKSprite.h"

int framesCounter = 0;
int currentFrame = 0;
int framesSpeed = 8; // Number of spritesheet frames shown by second

void dbSprite(int iSprite, int iX, int iY, int iImage) {}
void dbSetSprite(int iSprite, int iBackSave, int iTransparency) {}
void dbDeleteSprite(int iSprite) {}
void dbCloneSprite(int iSprite, int iDestination) {}
void dbShowSprite(int iSprite) {}
void dbHideSprite(int iSprite) {}
void dbHideAllSprites(void) {}
void dbShowAllSprites(void) {}
void dbMoveSprite(int iNUmber, float fVelocity) {}
void dbOffsetSprite(int iSprite, int iX, int iY) {}
void dbScaleSprite(int iSprite, int iScale) {}
void dbSizeSprite(int iSprite, int iX, int iY) {}
void dbStretchSprite(int iSprite, int iX, int iY) {}
void dbRotateSprite(int iSprite, float fAngle) {}
void dbFlipSprite(int iSprite) {}
void dbMirrorSprite(int iSprite) {}
void dbPasteSprite(int iSprite, int iX, int iY) {}

void dbCreateAnimatedSprite(int iSprite, const char* szFilename, int iAcross, int iDown, int iImage)
{
	Texture2D tex2D = LoadTexture(szFilename);        // Texture loading
	Rectangle frameRec = { 0.0f, 0.0f, tex2D.width / iAcross, tex2D.height / iDown };
 	
	Sprite _sprite;
	_sprite.texture2d = tex2D;
	_sprite.rect = frameRec;
	_sprite.frames_x = iAcross;
	_sprite.frames_y = iDown;
	spriteRef.push_back(_sprite);
}

void dbPlaySprite(int iSprite, int iStart, int iEnd, int iDelay)
{
	//Rectangle frameRec = { 0, 0, spriteRef[iSprite - 1].rect.width, spriteRef[iSprite - 1].rect.height };

	framesCounter++;

	if (framesCounter >= (60 / framesSpeed))
	{
		framesCounter = 0;
		currentFrame++;
		//std::cout << "currentFrame " << std::endl;

		if (currentFrame > spriteRef[iSprite - 1].frames_x)
		{			
			currentFrame = 0;
			spriteRef[iSprite - 1].rect.y += spriteRef[iSprite - 1].rect.height;;
		}

		if(spriteRef[iSprite - 1].rect.y > spriteRef[iSprite - 1].texture2d.height)
		{
			spriteRef[iSprite - 1].rect.y = 0; // reset
		}
		
		spriteRef[iSprite - 1].rect.x = (float)currentFrame * spriteRef[iSprite - 1].rect.width;
		//std::cout << "currentFrame " << currentFrame << " X " << spriteRef[iSprite - 1].rect.x << " Y " << spriteRef[iSprite - 1].rect.y << std::endl;
	}
	
	DrawTextureRec(spriteRef[iSprite - 1].texture2d, spriteRef[iSprite - 1].rect, Vector2{ 0, 0 }, WHITE);  // Draw part of the texture
}

void dbSetSpriteFrame(int iSprite, int iFrame) {}
void dbSetSpritePriority(int iSprite, int iPriority) {}
void dbSetSpriteImage(int iSprite, int iImage) {}
void dbSetSpriteAlpha(int iSprite, int iAlpha) {}
void dbSetSpriteDiffuse(int iSprite, int iRed, int iGreen, int iBlue) {}
void dbSetSpriteTextureCoord(int iSprite, int iVertex, float fU, float fV) {}

int dbSpriteExist(int iSprite)
{
	return NULL;
}

int dbSpriteX(int iSprite)
{
	return NULL;
}

int dbSpriteY(int iSprite)
{
	return NULL;
}

int dbSpriteOffsetX(int iSprite)
{
	return NULL;
}

int dbSpriteOffsetY(int iSprite)
{
	return NULL;
}

int dbSpriteScaleX(int iSprite)
{
	return NULL;
}

int dbSpriteScaleY(int iSprite)
{
	return NULL;
}

int dbSpriteWidth(int iSprite)
{
	return NULL;
}

int dbSpriteHeight(int iSprite)
{
	return NULL;
}

int dbSpriteImage(int iSprite)
{
	return NULL;
}

int dbSpriteMirrored(int iSprite)
{
	return NULL;
}

int dbSpriteFlipped(int iSprite)
{
	return NULL;
}

int dbSpriteHit(int iSprite, int iTarget)
{
	return NULL;
}

int dbSpriteCollision(int iSprite, int iTarget)
{
	return NULL;
}

float dbSpriteAngle(int iSprite)
{
	return NULL;
}

int dbSpriteFrame(int iSprite)
{
	return NULL;
}

int dbSpriteAlpha(int iSprite)
{
	return NULL;
}

int dbSpriteRed(int iSprite)
{
	return NULL;
}

int dbSpriteGreen(int iSprite)
{
	return NULL;
}

int dbSpriteBlue(int iSprite)
{
	return NULL;
}

int dbSpriteVisible(int iSprite)
{
	return NULL;
}