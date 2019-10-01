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

static int fontSize;
static int fontHeight;
static int fontWidth;
static int printFontHeight;
static int printFontWidth;
static bool fontScrolling;
static std::string fontTTF;
static std::string system_font;

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
