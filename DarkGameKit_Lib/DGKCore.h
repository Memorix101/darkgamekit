#pragma once

#include "DGKBase.h"

class DGKCore : public DarkGameKit
{
private:
	Rectangle print_cursor;
	Rectangle last_print_cursor;
	Rectangle last_printPos;
	int printObjCount;
public:
	DGKCore::DGKCore();
	void dbSyncOn();
	void dbSyncOff();
	void dbSync();
	void dbSyncRate(int rate);
	void dbFastsync(void);
	void dbCLS(void);
	void dbSetCursor(int x, int y);
	void dbPrint(std::string text);
	void dbInput(std::string, int variable);
	void dbWait(int ms);
	void dbSleep(int ms);
	void dbWaitKey(void);
	void dbWaitMouse(void);
	void dbSuspendForKey(void);
	void dbSuspendForMouse(void);
	void dbDrawToBack(void);
	void dbDrawToFront(void);
	void dbDrawSpritesFirst(void);
	void dbDrawSpritesLast(void);
	void dbRandomize(int seed);
	int dbRND(int range);
	float dbCOS(float value);
	float dbSIN(float value);
	float dbTAN(float value);
	float dbACOS(float value);
	float dbASIN(float value);
	float dbATANFULL(float x, float y);
	float dbHCOS(float value);
	float dbHSIN(float value);
	float dbHTAN(float value);
	float dbSQRT(float value);
	float dbABS(float value);
	int dbINT(float value);
	float dbEXP(float value);
	int dbTimer(void);
	char* dbInKey$(void);
	char* dbCL$(void);
	char* dbGetDate$(void);
	char* dbGetTime$(void);
	float dbCurveValue(float destination, float curve, float speed);
	float dbWrapValue(float angle);
	float dbNewXValue(float x, float angle, float step);
	float dbNewYValue(float x, float angle, float step);
	float dbNewZValue(float x, float angle, float step);
	float dvCurveValue(float fDestination, float fCurve, float fSpeed);
};


