#include <DarkGameKit.h>
#include "Invader Text.h"

int iNextTextSprite = 100;

// load in our font immage we will use to display all text
void invaderTextSetup(void)
{
	dbLoadImage("Assets\\font.png", 100);
}

// our main text routine
void InvaderText(int iX, int iY, int iSize, const char* czText, bool bHorizontalCenter = false, bool bVerticalCenter = false)
{
	// if bHorizonalCenter is true then work out the x coordinate to make the text centered
	if (bHorizontalCenter)
	{
		iX = (int)((dbScreenWidth() / 2) - ((strlen(czText) * iSize) / 2));
	}

	// if bHorizonalCenter is true then work out the y coordinate to make the text centered
	if (bVerticalCenter)
	{
		iY = (dbScreenHeight() / 2) - (iSize / 2);
	}

	// loop through and draw each character
	for (int i = 0; i < (int)strlen(czText); i++)
	{
		if (czText[i] == 32)
			iX += iSize;
		else
		{
			dbSprite(iNextTextSprite, iX, iY, 100);
			// call our routine to change the texture coordinates of the sprite manually to show the correct character
			fixUV(czText[i]);
			dbSizeSprite(iNextTextSprite, iSize, iSize);
			iX += iSize;
			iNextTextSprite++;
		}
	}
}

void fixUV(char c)
{
	// we have the ascii code of the letter to draw, we dont have the entire character set in our font image however
	// so we offset it to line up with our image
	c -= 33;

	float U = 0.0f;
	float V = 0.0f;

	int iY = c / 8;
	int iX = c % 8;

	float fOffset = 1.0f / 8.0f;

	U = iX * fOffset;
	V = iY * fOffset;

	// 4 vertices in a sprites (quad), we adjust the U and V ( think x and y) coordinates of the texture to show only the letter we want
	// rather than the whole texture
	dbSetSpriteTextureCoord(iNextTextSprite, 0, U, V);
	dbSetSpriteTextureCoord(iNextTextSprite, 1, U + fOffset, V);
	dbSetSpriteTextureCoord(iNextTextSprite, 2, U, V + fOffset);
	dbSetSpriteTextureCoord(iNextTextSprite, 3, U + fOffset, V + fOffset);
}

// delete all text sprites we have made
void invaderTextClear()
{
	for (int i = 100; i < iNextTextSprite; i++)
	{
		if (dbSpriteExist(i))
			dbDeleteSprite(i);
	}

	iNextTextSprite = 100;

}