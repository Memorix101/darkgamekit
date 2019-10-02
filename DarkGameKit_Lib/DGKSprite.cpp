
#include <cstddef>
#include "DGKSprite.h"
#include "DGKImage.h"

int framesCounter = 0;
int currentFrame = 0;
int framesSpeed = 8; // Number of spritesheet frames shown by second

void dbSprite(int iSprite, int iX, int iY, int iImage)
{
	//get sprite id in vector
	int image_id = 0;
	int sprite_id = 0;
	DGKSprite _sprite;

	bool _sprite_exists = false;

	if (dbImageExist(iImage) == 1) //only assign and draw if image exists
	{
		for (int i = 0; i < imageRef.size(); i++)
		{
			if (imageRef[i].id == iImage)
			{
				image_id = i;
			}
		}

		if (dbSpriteExist(iSprite) == 1)
		{
			for (int i = 0; i < spriteRef.size(); i++)
			{
				if (spriteRef[i].id == iSprite)
				{
					sprite_id = i;
					_sprite_exists = true;
					//UnloadTexture(spriteRef[sprite_id].texture2d);
				}

				if (sprite_id != 0)
					break;
			}
		}
		else
		{
			_sprite.id = iSprite;
			_sprite.image_id = iImage;
			_sprite.visible = true;
			_sprite_exists = true;
			_sprite.texture2d = LoadTextureFromImage(imageRef[image_id].image);
			spriteRef.push_back(_sprite);
		}

		//std::cout << spriteRef.size() << std::endl;
		if (spriteRef[sprite_id].visible == true && _sprite_exists == true)
		{
			DrawTexture(spriteRef[sprite_id].texture2d, iX, iY, WHITE);
		}
	}
	else
	{
		//error
	}
}

void dbSetSprite(int iSprite, int iBackSave, int iTransparency) {}

void dbDeleteSprite(int iSprite) {}

void dbCloneSprite(int iSprite, int iDestination)
{
	DGKSprite _copy;

	if (dbSpriteExist(iDestination) == 0) //check if destination is not already used
	{
		if (dbSpriteExist(iSprite) == 1)
		{
			for (int i = 0; i < spriteRef.size(); i++)
			{
				if (spriteRef[i].id == iSprite)
				{
					_copy = spriteRef[i];
					_copy.id = iDestination;
					spriteRef.push_back(_copy);
					break;
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR: Sprite destination ID " << iDestination << " already used" << std::endl;
	}
}

void dbShowSprite(int iSprite)
{
	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				spriteRef[i].visible = true;
			}
			else
			{
				//error
			}
		}
	}
	else
	{
		//error
	}
}

void dbHideSprite(int iSprite)
{
	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				spriteRef[i].visible = false;
			}
			else
			{
				//error
			}
		}
	}
	else
	{
		//error
	}
}

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

	//TODO Create DGKImage first and covert it to DKGSprite. So we have it handle it the vector 

	DGKSprite _sprite;
	_sprite.id = iSprite;
	//_sprite.image_id = iImage;
	_sprite.visible = true;
	_sprite.texture2d = tex2D;
	_sprite.rect = frameRec;
	_sprite.frames_x = iAcross;
	_sprite.frames_y = iDown;
	spriteRef.push_back(_sprite);
}

void dbPlaySprite(int iSprite, int iStart, int iEnd, int iDelay)
{
	//get sprite id in vector
	int sprite_id = 0;
	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				sprite_id = i;
			}
			else
			{
				//error
			}
		}
	}
	else
	{
		//error
	}

	framesCounter++;

	if (iDelay <= 0)
		iDelay = 1;

	if (iDelay / 0.02f > 100)
	{
		framesSpeed = iDelay * 0.02f;
	}
	else
	{
		framesSpeed = iDelay / 0.02f;
	}

	if (framesSpeed <= 0)
		framesSpeed = 1;

	if (framesCounter >= (60 / framesSpeed))
	{
		framesCounter = 0;
		currentFrame++;
		//std::cout << "currentFrame " << std::endl;

		if (currentFrame > spriteRef[sprite_id].frames_x)
		{
			currentFrame = 0;
			spriteRef[sprite_id].rect.y += spriteRef[sprite_id].rect.height;;
		}

		if (spriteRef[sprite_id].rect.y > spriteRef[sprite_id].texture2d.height)
		{
			spriteRef[sprite_id].rect.y = 0; // reset
		}

		spriteRef[sprite_id].rect.x = (float)currentFrame * spriteRef[sprite_id].rect.width;
		//std::cout << "currentFrame " << currentFrame << " X " << spriteRef[iSprite - 1].rect.x << " Y " << spriteRef[iSprite - 1].rect.y << std::endl;
	}

	if (spriteRef[sprite_id].visible == true)
	{
		DrawTextureRec(spriteRef[sprite_id].texture2d, spriteRef[sprite_id].rect, Vector2{ 0, 0 }, WHITE);  // Draw part of the texture
	}
}

void dbSetSpriteFrame(int iSprite, int iFrame) {}
void dbSetSpritePriority(int iSprite, int iPriority) {}
void dbSetSpriteImage(int iSprite, int iImage) {}
void dbSetSpriteAlpha(int iSprite, int iAlpha) {}
void dbSetSpriteDiffuse(int iSprite, int iRed, int iGreen, int iBlue) {}
void dbSetSpriteTextureCoord(int iSprite, int iVertex, float fU, float fV) {}

int dbSpriteExist(int iSprite)
{
	int id = 0;
	for (int i = 0; i < spriteRef.size(); i++)
	{
		if (spriteRef[i].id == iSprite)
		{
			id = 1;
		}

		if (id == 1)
			break;
	}
	return id;
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
	int image_id = -1;
	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				image_id = spriteRef[i].image_id;
				break;
			}
		}
	}
	else
	{
		//error
	}

	return image_id;
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
	int visible = 0;
	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				if (spriteRef[i].visible == true)
				{
					visible = 1;
				}
				break;
			}
		}
	}
	else
	{
		//error
	}

	return visible;
}