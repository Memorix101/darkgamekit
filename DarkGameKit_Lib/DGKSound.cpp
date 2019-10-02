#include "DGKSound.h"
#include <cstddef>

void dbLoadSound ( char* szFilename, int iSound ){ }
void dbLoad3DSound ( char* szFilename, int iSound ){ }
void dbSaveSound ( char* szFilename, int iSound ){ }
void dbDeleteSound ( int iSound ){ }
void dbCloneSound ( int iDestination, int iSource ){ }
void dbPlaySound ( int iSound ){ }
void dbLoopSound ( int iSound ){ }
void dbStopSound ( int iSound ){ }
void dbPauseSound ( int iSound ){ }
void dbResumeSound ( int iSound ){ }
void dbPositionSound ( int iSound, float fX, float fY, float fZ ){ }
void dbRecordSound ( int iSound ){ }
void dbStopRecordingSound ( void ){ }
void dbSetSoundPan ( int iSound, int iPan ){ }
void dbSetSoundSpeed ( int iSound, int iFrequency ){ }
void dbSetSoundVolume ( int iSound, int iVolume ){ }
void dbPositionListener ( float fX, float fY, float fZ ){ }
void dbRotateListener ( float fX, float fY, float fZ ){ }
void dbScaleListener ( float fScale ){ }

int dbSoundExist ( int iSound )
{
	return NULL;
}

int dbSoundType ( int iSound )
{
	return NULL;
}

int dbSoundPlaying ( int iSound )
{
	return NULL;
}

int dbSoundLooping ( int iSound )
{
	return NULL;
}

int dbSoundPaused ( int iSound )
{
	return NULL;
}

float dbSoundPositionX ( int iSound )
{
	return NULL;
}

float dbSoundPositionY ( int iSound )
{
	return NULL;
}

float dbSoundPositionZ ( int iSound )
{
	return NULL;
}

int dbSoundPan ( int iSound )
{
	return NULL;
}

int dbSoundSpeed ( int iSound )
{
	return NULL;
}

int dbSoundVolume ( int iSound )
{
	return NULL;
}

float dbListenerPositionX ( void )
{
	return NULL;
}

float dbListenerPositionY ( void )
{
	return NULL;
}

float dbListenerPositionZ ( void )
{
	return NULL;
}

float dbListenerAngleX ( void )
{
	return NULL;
}

float dbListenerAngleY ( void )
{
	return NULL;
}

float dbListenerAngleZ ( void )
{
	return NULL;
}