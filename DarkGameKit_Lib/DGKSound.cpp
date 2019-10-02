#include "DGKSound.h"
#include <cstddef>

void dbLoadSound(const char* szFilename, int iSound)
{
	DGKSound _sound;
	_sound.id = iSound;
	_sound.looping = false;
	_sound.volume = 1.0f;
	_sound.sound = LoadSound(szFilename);
	soundRef.push_back(_sound);
}

void dbLoad3DSound(const char* szFilename, int iSound) { }
void dbSaveSound(const char* szFilename, int iSound) { }

void dbDeleteSound(int iSound)
{
	if (dbSoundExist(iSound) == 1)
	{
		for (int i = 0; i < soundRef.size(); i++)
		{
			if (soundRef[i].id == iSound)
			{
				UnloadSound(soundRef[i].sound);
			}
			else
			{
				//error
			}
		}
	}
	else
	{
		//error
	}
}

void dbCloneSound(int iDestination, int iSource) { }

void dbPlaySound(int iSound)
{
	if (dbSoundExist(iSound) == 1)
	{
		for (int i = 0; i < soundRef.size(); i++)
		{
			if (soundRef[i].id == iSound)
			{
				PlaySound(soundRef[i].sound);
			}
			else
			{
				//error
			}
		}
	}
	else
	{
		//error
	}
}

void dbLoopSound(int iSound)
{
	if (dbSoundExist(iSound) == 1)
	{
		for (int i = 0; i < soundRef.size(); i++)
		{
			if (soundRef[i].id == iSound)
			{
				soundRef[i].looping = true;
			}
			else
			{
				//error
			}
		}
	}
	else
	{
		//error
	}
}

void dbStopSound(int iSound)
{
	if (dbSoundExist(iSound) == 1)
	{
		for (int i = 0; i < soundRef.size(); i++)
		{
			if (soundRef[i].id == iSound)
			{
				soundRef[i].looping = false;
				StopSound(soundRef[i].sound);
			}
			else
			{
				//error
			}
		}
	}
	else
	{
		//error
	}
}

void dbPauseSound(int iSound)
{
	if (dbSoundExist(iSound) == 1)
	{
		for (int i = 0; i < soundRef.size(); i++)
		{
			if (soundRef[i].id == iSound)
			{
				soundRef[i].looping = false;
				PauseSound(soundRef[i].sound);
			}
			else
			{
				//error
			}
		}
	}
	else
	{
		//error
	}
}

void dbResumeSound(int iSound)
{
	if (dbSoundExist(iSound) == 1)
	{
		for (int i = 0; i < soundRef.size(); i++)
		{
			if (soundRef[i].id == iSound)
			{
				ResumeSound(soundRef[i].sound);
			}
			else
			{
				//error
			}
		}
	}
	else
	{
		//error
	}
}


void dbPositionSound(int iSound, float fX, float fY, float fZ) { }
void dbRecordSound(int iSound) { }
void dbStopRecordingSound(void) { }
void dbSetSoundPan(int iSound, int iPan) { }
void dbSetSoundSpeed(int iSound, int iFrequency) { }
void dbSetSoundVolume(int iSound, int iVolume) { }
void dbPositionListener(float fX, float fY, float fZ) { }
void dbRotateListener(float fX, float fY, float fZ) { }
void dbScaleListener(float fScale) { }

int dbSoundExist(int iSound)
{
	int sound_id = 0;
	for (int i = 0; i < soundRef.size(); i++)
	{
		if (soundRef[i].id == iSound)
		{
			sound_id = 1;
		}

		if (sound_id == 1)
			break;
	}

	return sound_id;
}

int dbSoundType(int iSound)
{
	return NULL;
}

int dbSoundPlaying(int iSound)
{
	return NULL;
}

int dbSoundLooping(int iSound)
{
	return NULL;
}

int dbSoundPaused(int iSound)
{
	return NULL;
}

float dbSoundPositionX(int iSound)
{
	return NULL;
}

float dbSoundPositionY(int iSound)
{
	return NULL;
}

float dbSoundPositionZ(int iSound)
{
	return NULL;
}

int dbSoundPan(int iSound)
{
	return NULL;
}

int dbSoundSpeed(int iSound)
{
	return NULL;
}

int dbSoundVolume(int iSound)
{
	return NULL;
}

float dbListenerPositionX(void)
{
	return NULL;
}

float dbListenerPositionY(void)
{
	return NULL;
}

float dbListenerPositionZ(void)
{
	return NULL;
}

float dbListenerAngleX(void)
{
	return NULL;
}

float dbListenerAngleY(void)
{
	return NULL;
}

float dbListenerAngleZ(void)
{
	return NULL;
}