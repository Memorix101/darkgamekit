#pragma once
#include "DGKBase.h"

//protected:
//private:
//public:
void dbText(int x, int y, std::string text);
void dbCenterText(int x, int y, std::string text);
void dbSetTextFont(std::string font);
void dbSetTextFont(std::string font, int charset); //overload
void dbSetTextSize(int size);
void dbSetTextOpaque(void);
void dbSetTextTransparent(void);
void dbSetTextToNormal(void);
void dbSetTextToItalic(void);
void dbSetTextToBoldItalic(void);
void dbPerformCheckListForFonts(void);
int dbTextBackgroundType(void);
char* dbTextFont$(void);
int dbTextSize(void);
int dbTextStyle(void);
int dbTextWidth(std::string text);
int dbTextHeight(std::string text);
int dbAsc(std::string text);
char* dbBin$(int value);
char* dbChr$(int value);
char* dbHex$(int value);
char* dbLeft$(std::string text, int value);
int dbLen(std::string text);
char* dbLower$(std::string text);
char* dbMid$(std::string text, int value);
char* dbRight$(std::string text, int value);
char* dbStr$(std::string text, int value);
char* dbUpper$(std::string text);
int dbVal(std::string text);
char* dbSpace$(int space);