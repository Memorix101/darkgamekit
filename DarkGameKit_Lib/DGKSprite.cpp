
#include <cstddef>
#include <algorithm>
#include "DGKSprite.h"
#include "DGKImage.h"

int framesCounter = 0;
int framesSpeed = 8; // Number of spritesheet frames shown by second

void dbSprite(int iSprite, int iX, int iY, int iImage)
{
	//get sprite id in vector
	int image_id = 0;
	int sprite_id = 0;
	DGKSprite _sprite;

	bool _sprite_exists = false;

	if (dbImageExist(iImage) == 1) //if image exists assign it to sprite
	{
		for (int i = 0; i < imageRef.size(); i++)
		{
			if (imageRef[i].id == iImage)
			{
				image_id = i;
			}
		}

		if (dbSpriteExist(iSprite) == 1) //if sprite exists update values
		{
			for (int i = 0; i < spriteRef.size(); i++)
			{
				if (spriteRef[i].id == iSprite)
				{
					sprite_id = i;
					_sprite_exists = true;
					spriteRef[i].pos.x = iX;
					spriteRef[i].pos.y = iY;
					spriteRef[i].visible = true;
					break;
				}
			}
		}
		else
		{
			//if image exists assign it to sprite
			_sprite.id = iSprite;
			_sprite.image_id = iImage;
			_sprite.pos.x = iX;
			_sprite.pos.y = iY;
			_sprite_exists = true;
			_sprite.visible = true;
			_sprite.texture2d = LoadTextureFromImage(imageRef[image_id].image);
			spriteRef.push_back(_sprite);
		}
	}
	else
	{
		if (dbSpriteExist(iSprite) == 1) //if sprite exists assign it to image
		{
			for (int i = 0; i < spriteRef.size(); i++)
			{
				if (dbImageExist(iImage) == 1) //if image exists assign it to sprite
				{
					for (int i = 0; i < imageRef.size(); i++)
					{
						if (imageRef[i].id == iImage)
						{
							image_id = i;
						}
					}
				}
				/*DGKImage _image;
				_image.id = iImage;
				_image.image = LoadImage(spriteRef[i].filepath);
				imageRef.push_back(_image);*/

				if (spriteRef[i].id == iSprite) //if sprite exists update values
				{
					sprite_id = i;
					_sprite_exists = true;
					spriteRef[i].pos.x = iX;
					spriteRef[i].pos.y = iY;
					spriteRef[i].visible = true;
					break;
				}
			}
		}
	}
}

void dbSetSprite(int iSprite, int iBackSave, int iTransparency) {}

void dbDeleteSprite(int iSprite)
{
	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				UnloadTexture(spriteRef[i].texture2d);
				spriteRef.erase(spriteRef.begin() + i); // deletes single item by index https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
				break;
			}
		}
	}
	else
	{
		//error
	}
}

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
					_copy.visible = false;
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

void dbMoveSprite(int iSprite, float fVelocity)
{
	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				spriteRef[i].pos.y -= fVelocity;
				break;
			}
		}
	}
}
void dbOffsetSprite(int iSprite, int iX, int iY) {}
void dbScaleSprite(int iSprite, int iScale) {}

void dbSizeSprite(int iSprite, int iX, int iY)
{
	int sprite_id = 0;
	for (int i = 0; i < spriteRef.size(); i++)
	{
		if (spriteRef[i].id == iSprite)
		{
			Image _image = GetTextureData(spriteRef[i].texture2d);
			ImageResize(&_image, iX, iY);
			UnloadTexture(spriteRef[i].texture2d);
			spriteRef[i].texture2d = LoadTextureFromImage(_image);
		}
	}
}

void dbStretchSprite(int iSprite, int iX, int iY) {}
void dbRotateSprite(int iSprite, float fAngle) {}
void dbFlipSprite(int iSprite) {}
void dbMirrorSprite(int iSprite) {}

void dbPasteSprite(int iSprite, int iX, int iY)
{
	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				spriteRef[i].pos.x = iX;
				spriteRef[i].pos.y = iY;
				spriteRef[i].visible = true;
				break;
			}
		}
	}
}

void dbCreateAnimatedSprite(int iSprite, const char* szFilename, int iAcross, int iDown, int iImage)
{
	Texture2D tex2D = LoadTexture(szFilename);
	Rectangle frameRec = { 0.0f, 0.0f, tex2D.width / iAcross, tex2D.height / iDown };

	//TODO Create DGKImage first and covert it to DKGSprite. So we have it handle it the vector 

	DGKSprite _sprite;
	_sprite.id = iSprite;
	//_sprite.image_id = iImage;
	_sprite.animated = true;
	_sprite.texture2d = tex2D;
	_sprite.rect = frameRec;
	_sprite.frames_x = iAcross;
	_sprite.frames_y = iDown;
	_sprite.filepath = szFilename;
	spriteRef.push_back(_sprite);
}

void dbPlaySprite(int iSprite, int iStart, int iEnd, int iDelay)
{
	//get sprite id in vector
	int sprite_id = 0;
	int start_offset = iStart;

	if(iStart == 1)
			iStart = 0;

	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				sprite_id = i;

				if (spriteRef[sprite_id].currentFrame == 0) // set start offset
				{
					spriteRef[sprite_id].currentFrame = start_offset;
				}
			}
			else
			{
				//error
			}
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
		
		/*
		if (GetFrameTime() != 0)
			framesSpeed = (iDelay / GetFPS()) * 0.3f;*/

		if (framesSpeed <= 0)
			framesSpeed = 1;

		//if (framesCounter >= (60 / framesSpeed))
		if (framesCounter >= (GetFPS() / framesSpeed))
		{
			framesCounter = 0;

			if (spriteRef[sprite_id].currentFrame > iEnd - 1) // reset
			{
				spriteRef[sprite_id].currentFrame_X = 0;
				spriteRef[sprite_id].currentFrame_Y = 0;
				spriteRef[sprite_id].currentFrame = start_offset - 1;
				//std::cout << "iEnd " << std::endl;
			}

			int f_x = spriteRef[sprite_id].currentFrame % spriteRef[sprite_id].frames_x;
			int f_y = spriteRef[sprite_id].currentFrame / spriteRef[sprite_id].frames_y;

			spriteRef[sprite_id].currentFrame_X = f_x;
			spriteRef[sprite_id].currentFrame_Y = f_y;

			spriteRef[sprite_id].rect.x = (float)spriteRef[sprite_id].currentFrame_X * spriteRef[sprite_id].rect.width;
			spriteRef[sprite_id].rect.y = (float)spriteRef[sprite_id].currentFrame_Y * spriteRef[sprite_id].rect.height;

			std::cout << "currentFrame " << spriteRef[sprite_id].currentFrame << " currentFrame_X " << spriteRef[sprite_id].currentFrame_X << " X "
				<< spriteRef[sprite_id].rect.x << " Y " << spriteRef[sprite_id].rect.y << std::endl;

			spriteRef[sprite_id].currentFrame++;
		}
	}
	else
	{
		//error
	}
}

void dbSetSpriteFrame(int iSprite, int iFrame)
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

		//set frame
		spriteRef[sprite_id].currentFrame = iFrame;
		int f_x = (iFrame % spriteRef[sprite_id].frames_x);
		int f_y = iFrame / spriteRef[sprite_id].frames_y;

		spriteRef[sprite_id].currentFrame_X = f_x;
		spriteRef[sprite_id].currentFrame_Y = f_y;
		spriteRef[sprite_id].rect.x = (float)spriteRef[sprite_id].currentFrame_X * spriteRef[sprite_id].rect.width;
		spriteRef[sprite_id].rect.y = (float)spriteRef[sprite_id].currentFrame_Y * spriteRef[sprite_id].rect.height;

		/*std::cout << "currentFrame " << spriteRef[sprite_id].currentFrame << " currentFrame_X " << spriteRef[sprite_id].currentFrame_X << " X "
			<< spriteRef[sprite_id].rect.x << " Y " << spriteRef[sprite_id].rect.y << std::endl;*/
	}
	else
	{
		//error
	}
}

inline bool operator<(const DGKSprite& a, const DGKSprite& b)
{
	return a.layer < b.layer;
}


void dbSetSpritePriority(int iSprite, int iPriority) //By setting a single sprite a value of one will cause that sprite to be drawn last
{
	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				spriteRef[i].layer = iPriority;
				std::sort(spriteRef.begin(), spriteRef.end());
				break;
			}
		}
	}
	else
	{
		//error
	}
}

void dbSetSpriteImage(int iSprite, int iImage) {}
void dbSetSpriteAlpha(int iSprite, int iAlpha) {}
void dbSetSpriteDiffuse(int iSprite, int iRed, int iGreen, int iBlue) {}

void dbSetSpriteTextureCoord(int iSprite, int iVertex, float fU, float fV)
{
	int sprite_id = 0;
	for (int i = 0; i < spriteRef.size(); i++)
	{
		if (spriteRef[i].id == iSprite)
		{
			sprite_id = i;
			// UV https://learn.foundry.com/nuke/8.0/content/resources/images/ug_images/uv_coordinates.png
			spriteRef[sprite_id].fU[iVertex] = fU; //x
			spriteRef[sprite_id].fV[iVertex] = fV; //y
			spriteRef[sprite_id].setUV = true;
		}

		/*
		if (spriteRef[sprite_id].visible == true)
		{
			DrawTextureRec(spriteRef[sprite_id].texture2d, _rect, Vector2{ 0, 0 }, WHITE);  // Draw part of the texture
		}
		*/
	}
}

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
	int pos = 0;
	for (int i = 0; i < spriteRef.size(); i++)
	{
		if (spriteRef[i].id == iSprite)
		{
			pos = spriteRef[i].pos.x;
			break;
		}
	}
	return pos;
}

int dbSpriteY(int iSprite)
{
	int pos = 0;
	for (int i = 0; i < spriteRef.size(); i++)
	{
		if (spriteRef[i].id == iSprite)
		{
			pos = spriteRef[i].pos.y;
			break;
		}
	}
	return pos;
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
	int width = 0;
	for (int i = 0; i < spriteRef.size(); i++)
	{
		if (spriteRef[i].id == iSprite)
		{
			width = spriteRef[i].texture2d.width;
			break;
		}
	}
	return width;
}

int dbSpriteHeight(int iSprite)
{
	int height = 0;
	for (int i = 0; i < spriteRef.size(); i++)
	{
		if (spriteRef[i].id == iSprite)
		{
			height = spriteRef[i].texture2d.height;
			break;
		}
	}
	return height;
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
	int frame = 0;
	if (dbSpriteExist(iSprite) == 1)
	{
		for (int i = 0; i < spriteRef.size(); i++)
		{
			if (spriteRef[i].id == iSprite)
			{
				if (spriteRef[i].animated == true)
				{
					frame = spriteRef[i].currentFrame;
					break;
				}

				break;
			}
		}
	}
	else
	{
		//error
	}

	return frame;
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