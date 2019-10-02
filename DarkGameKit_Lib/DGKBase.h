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
extern std::string window_title;
extern	int window_width;
extern	int window_height;
// bool quit;
// int sync_i

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

struct DGKPrint
{
	std::string text;
	Rectangle pos;
};
extern bool printOnce;
extern std::vector<DGKPrint> printRef;
//extern std::vector<DGKPrint> printCopy;

struct DGKText
{
	std::string text;
	Rectangle pos;
	int fontSize;
};
extern std::vector<DGKText> textRef;

struct DGKSprite
{
	int id;
	Texture2D texture2d;
	Rectangle rect;
	float frames_x;
	float frames_y;
};
extern std::vector<DGKSprite> spriteRef;

struct DGKSound
{
	int id;
	bool looping;
	float volume;
	float pitch;
	Sound sound;
};
extern std::vector<DGKSound> soundRef;

struct DGKImage
{
	int id;
	Image image;
};
extern std::vector<DGKImage> imageRef;

struct DGKMusic
{
	int id;
	bool looping;
	float volume;
	Music music;
};
extern std::vector<DGKMusic> musicRef;

//private:
void CallOnce();
void InitFont();

//public:
	//DarkGameKit();
void StartGDK(); //entry point
bool LoopGDK();
void Init();
void Run();
