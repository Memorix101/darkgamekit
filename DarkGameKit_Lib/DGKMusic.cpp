#include "DGKMusic.h"
#include <cstddef>

void dbLoadMusic (const char* szFilename, int iMusic ){ }
void dbLoadCDMusic ( int iTrack, int iMusic ){ }
void dbDeleteMusic ( int iMusic ){ }
void dbPlayMusic ( int iMusic ){ }
void dbLoopMusic ( int iMusic ){ }
void dbStopMusic ( int iMusic ){ }
void dbPauseMusic ( int iMusic ){ }
void dbResumeMusic ( int iMusic ){ }
void dbSetMusicSpeed ( int iMusic, int iSpeed ){ }
void dbSetMusicVolume ( int iMusic, int iVolume ){ }

int dbMusicExist ( int iMusic )
{
	return NULL;
}

int dbMusicPlaying ( int iMusic )
{
	return NULL;
}

int dbMusicLooping ( int iMusic )
{
	return NULL;
}

int dbMusicPaused ( int iMusic )
{
	return NULL;
}

int dbMusicSpeed ( int iMusic )
{
	return NULL;
}

int dbMusicVolume ( int iMusic )
{
	return NULL;
}

int dbGetNumberOfCDTracks ( void )
{
	return NULL;
}