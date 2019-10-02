#pragma once
#include "DGKBase.h"

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
	int image_id;
	int layer = 0; //priority 
	bool visible = false;
	bool animated = false;
	bool setUV = false;
	Texture2D texture2d;
	Rectangle rect; //animation
	Vector2 pos = { 0, 0 };
	float frames_x;
	float frames_y;
	int currentFrame = 0;
	int currentFrameTmp = 0;
	const char* filepath;
	float fU[4] = { 0.0f, 0.0f,  1.0f,  1.0f };
	float fV[4] = { 0.0f, 1.0f, 1.0f,  1.0f };
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
void Init();
void Run();