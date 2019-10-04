#include "DGKImage.h"
#include "DGKSprite.h"

void dbLoadImage(const char* szFilename, int iImage)
{
	DGKImage _image;
	_image.id = iImage;
	_image.image = LoadImage(szFilename);
	imageRef.push_back(_image);
}

void dbSaveImage(const char* szFilename, int iImage)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbDeleteImage(int iImage)
{
	if (dbImageExist(iImage) == 1)
	{
		for (int i = 0; i < imageRef.size(); i++)
		{
			if (imageRef[i].id == iImage)
			{
				UnloadImage(imageRef[i].image);
				imageRef.erase(imageRef.begin() + i); // deletes single item by index https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
				break;
			}
		}
	}
	else
	{
		//error
	}
}
void dbGetImage(int iImage, int iLeft, int iTop, int iRight, int iBottom)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbPasteImage(int iImage, int iX, int iY)
{
		if (dbImageExist(iImage) == 1)
	{
		for (int i = 0; i < imageRef.size(); i++)
		{
			if (imageRef[i].id == iImage)
			{
				imageRef[i].visible = true;
				imageRef[i].pos = {(float)iX, (float)iY};
				break;
			}
		}
	}
	else
	{
		//error
	}
}

void dbSetImageColorKey(int iRed, int iGreen, int iBlue)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

int dbImageExist(int iImage)
{
	int id = 0;
	for (int i = 0; i < imageRef.size(); i++)
	{
		if (imageRef[i].id == iImage)
		{
			id = 1;
		}

		if(id == 1)
			break;
	}

	return id;
}
