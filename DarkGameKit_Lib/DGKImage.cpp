#include "DGKImage.h"

void dbLoadImage(const char* szFilename, int iImage)
{
	DGKImage _image;
	_image.id = iImage;
	_image.image = LoadImage(szFilename);
	imageRef.push_back(_image);
}

void dbSaveImage(const char* szFilename, int iImage) { }

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
void dbGetImage(int iImage, int iLeft, int iTop, int iRight, int iBottom) { }
void dbPasteImage(int iImage, int iX, int iY) { }
void dbSetImageColorKey(int iRed, int iGreen, int iBlue) { }

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
