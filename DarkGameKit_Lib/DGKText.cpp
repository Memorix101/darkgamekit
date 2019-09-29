#include "DGKText.h"

std::vector<DarkGameKit::textObj>  DarkGameKit::textRef;

void DGKText::dbText(int x, int y, std::string text)
{
	textObj a;
	a.text = text;
	GetFontSize(text);
	a.pos.x = x;
	a.pos.y = y;
	a.fontSize = fontSize;
	textRef.push_back(a);
}

void DGKText::dbCenterText(int x, int y, std::string text)
{
	textObj a;
	a.text = text;
	GetFontSize(text);
	a.pos.x = (x) - (fontWidth / 2);
	a.pos.y = y;
	a.fontSize = fontSize;
	textRef.push_back(a);
}

void DGKText::dbSetTextFont(std::string font)
{
	fontTTF = font;
	SetSystemFont();
}

void DGKText::dbSetTextFont(std::string font, int charset) //overload
{
	
}

void DGKText::dbSetTextSize(int size)
{
	fontSize = size;
}

void DGKText::dbSetTextOpaque(void)
{

}

void DGKText::dbSetTextTransparent(void)
{

}

void DGKText::dbSetTextToNormal(void)
{

}

void DGKText::dbSetTextToItalic(void)
{

}

void DGKText::dbSetTextToBoldItalic(void)
{

}

void DGKText::dbPerformCheckListForFonts(void)
{

}

int DGKText::dbTextBackgroundType(void)
{
	return NULL;
}

char* DGKText::dbTextFont$(void)
{
	return NULL;
}

int DGKText::dbTextSize(void)
{
	return NULL;
}

int DGKText::dbTextStyle(void)
{
	return NULL;
}

int DGKText::dbTextWidth(std::string text)
{
	return NULL;
}

int DGKText::dbTextHeight(std::string text)
{
	return NULL;
}

int DGKText::dbAsc(std::string text)
{
	return NULL;
}

char* DGKText::dbBin$(int value)
{
	return NULL;
}

char* DGKText::dbChr$(int value)
{
	return NULL;
}

char* DGKText::dbHex$(int value)
{
	return NULL;
}

char* DGKText::dbLeft$(std::string text, int value)
{
	return NULL;
}

int DGKText::dbLen(std::string text)
{
	return NULL;
}

char* DGKText::dbLower$(std::string text)
{
	return NULL;
}

char* DGKText::dbMid$(std::string text, int value)
{
	return NULL;
}

char* DGKText::dbRight$(std::string text, int value)
{
	return NULL;
}

char* DGKText::dbStr$(std::string text, int value)
{
	return NULL;
}

char* DGKText::dbUpper$(std::string text)
{
	return NULL;
}

int DGKText::dbVal(std::string text)
{
	return NULL;
}

char* DGKText::dbSpace$(int space)
{
	return NULL;
}
