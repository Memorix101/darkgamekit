#include "DGKMusic.h"
#include <cstddef>

void dbLoadMusic(const char* szFilename, int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbLoadCDMusic(int iTrack, int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbDeleteMusic(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbPlayMusic(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbLoopMusic(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbStopMusic(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbPauseMusic(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbResumeMusic(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetMusicSpeed(int iMusic, int iSpeed)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetMusicVolume(int iMusic, int iVolume)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

int dbMusicExist(int iMusic)
{
	int id = 0;
	for (int i = 0; i < musicRef.size(); i++)
	{
		if (soundRef[i].id == iMusic)
		{
			id = 1;
		}

		if (id == 1)
			break;
	}

	return id;
}

int dbMusicPlaying(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbMusicLooping(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbMusicPaused(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbMusicSpeed(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbMusicVolume(int iMusic)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbGetNumberOfCDTracks(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}