#pragma once
#include "DGKBase.h"

void dbLoadSound ( char* szFilename, int iSound );
void dbLoad3DSound ( char* szFilename, int iSound );
void dbSaveSound ( char* szFilename, int iSound );
void dbDeleteSound ( int iSound );
void dbCloneSound ( int iDestination, int iSource );
void dbPlaySound ( int iSound );
void dbLoopSound ( int iSound );
void dbStopSound ( int iSound );
void dbPauseSound ( int iSound );
void dbResumeSound ( int iSound );
void dbPositionSound ( int iSound, float fX, float fY, float fZ );
void dbRecordSound ( int iSound );
void dbStopRecordingSound ( void );
void dbSetSoundPan ( int iSound, int iPan );
void dbSetSoundSpeed ( int iSound, int iFrequency );
void dbSetSoundVolume ( int iSound, int iVolume );
void dbPositionListener ( float fX, float fY, float fZ );
void dbRotateListener ( float fX, float fY, float fZ );
void dbScaleListener ( float fScale );

int dbSoundExist ( int iSound );
int dbSoundType ( int iSound );
int dbSoundPlaying ( int iSound );
int dbSoundLooping ( int iSound );
int dbSoundPaused ( int iSound );
float dbSoundPositionX ( int iSound );
float dbSoundPositionY ( int iSound );
float dbSoundPositionZ ( int iSound );
int dbSoundPan ( int iSound );
int dbSoundSpeed ( int iSound );
int dbSoundVolume ( int iSound );

float dbListenerPositionX ( void );
float dbListenerPositionY ( void );
float dbListenerPositionZ ( void );
float dbListenerAngleX ( void );
float dbListenerAngleY ( void );
float dbListenerAngleZ ( void );