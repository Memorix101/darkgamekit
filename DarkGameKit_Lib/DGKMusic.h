#pragma once
#include "DGKBase.h"

void dbLoadMusic (const char* szFilename, int iMusic );
void dbLoadCDMusic ( int iTrack, int iMusic );
void dbDeleteMusic ( int iMusic );
void dbPlayMusic ( int iMusic );
void dbLoopMusic ( int iMusic );
void dbStopMusic ( int iMusic );
void dbPauseMusic ( int iMusic );
void dbResumeMusic ( int iMusic );
void dbSetMusicSpeed ( int iMusic, int iSpeed );
void dbSetMusicVolume ( int iMusic, int iVolume );

int dbMusicExist ( int iMusic );
int dbMusicPlaying ( int iMusic );
int dbMusicLooping ( int iMusic );
int dbMusicPaused ( int iMusic );
int dbMusicSpeed ( int iMusic );
int dbMusicVolume ( int iMusic );
int dbGetNumberOfCDTracks ( void );