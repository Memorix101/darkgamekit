#include "DGKText.h"

//std::vector<DGKText> textRef;

void dbText(int x, int y, std::string text)
{
	DGKText a;
	a.text = text;
	GetFontSize(text);
	a.pos.x = x;
	a.pos.y = y;
	a.fontSize = fontSize;
	textRef.push_back(a);
}

void dbCenterText(int x, int y, std::string text)
{
	DGKText a;
	a.text = text;
	GetFontSize(text);
	a.pos.x = (x) - (fontWidth / 2);
	a.pos.y = y;
	a.fontSize = fontSize;
	textRef.push_back(a);
}

void dbSetTextFont(std::string font)
{
	fontTTF = font;
	SetSystemFont();
}

void dbSetTextFont(std::string font, int charset) //overload
{
	
}

void dbSetTextSize(int size)
{
	fontSize = size;
}

void dbSetTextOpaque(void)
{

}

void dbSetTextTransparent(void)
{

}

void dbSetTextToNormal(void)
{

}

void dbSetTextToItalic(void)
{

}

void dbSetTextToBoldItalic(void)
{

}

void dbPerformCheckListForFonts(void)
{

}

int dbTextBackgroundType(void)
{
	return NULL;
}

char* dbTextFont$(void)
{
	return NULL;
}

int dbTextSize(void)
{
	return NULL;
}

int dbTextStyle(void)
{
	return NULL;
}

int dbTextWidth(std::string text)
{
	return NULL;
}

int dbTextHeight(std::string text)
{
	return NULL;
}

int dbAsc(std::string text)
{
	return NULL;
}

char* dbBin$(int value)
{
	return NULL;
}

char* dbChr$(int value)
{
	return NULL;
}

char* dbHex$(int value)
{
	return NULL;
}

char* dbLeft$(std::string text, int value)
{
	return NULL;
}

int dbLen(std::string text)
{
	return NULL;
}

char* dbLower$(std::string text)
{
	return NULL;
}

char* dbMid$(std::string text, int value)
{
	return NULL;
}

char* dbRight$(std::string text, int value)
{
	return NULL;
}

char* dbStr$(std::string text, int value)
{
	return NULL;
}

char* dbUpper$(std::string text)
{
	return NULL;
}

int dbVal(std::string text)
{
	return NULL;
}

char* dbSpace$(int space)
{
	return NULL;
}
