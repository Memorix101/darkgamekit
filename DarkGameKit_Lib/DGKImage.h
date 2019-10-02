#pragma once
#include "DGKBase.h"

void dbLoadImage(const char* szFilename, int iImage);
void dbSaveImage(const char* szFilename, int iImage);
void dbDeleteImage(int iImage);
void dbGetImage(int iImage, int iLeft, int iTop, int iRight, int iBottom);
void dbPasteImage(int iImage, int iX, int iY);
void dbSetImageColorKey(int iRed, int iGreen, int iBlue);

int dbImageExist(int iImage);