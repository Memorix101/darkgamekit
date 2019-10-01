#pragma once

#include <raylib.h>

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <iostream>
#include <stdlib.h>

//protected:
	/*const char* window_title;
	int window_width;
	int window_height;
	bool quit;
	int sync_i;*/

extern int fontSize;
extern int fontHeight;
extern int fontWidth;
extern int printFontHeight;
extern int printFontWidth;
extern bool fontScrolling;
extern std::string fontTTF;
extern std::string system_font;

void DrawSprite(Rectangle rect);
void DrawPrint(Rectangle rect, std::string text);
void DrawFont(Rectangle rect, std::string text, int _fontSize);
void DrawTrailModeWatermark();
void SetIcon();
void SetSystemFont();

int GetFontSize(std::string text);

// references and other stuff

struct printObj
{
	std::string text;
	Rectangle pos;
};
extern bool printOnce;
extern std::vector<printObj> printRef;
extern std::vector<printObj> printCopy;

struct textObj
{
	std::string text;
	Rectangle pos;
	int fontSize;
};
extern std::vector<textObj> textRef;

//private:
void CallOnce();
void InitFont();

//public:
	//DarkGameKit();
void StartGDK(); //entry point
bool LoopGDK();
void Init();
void Run();
