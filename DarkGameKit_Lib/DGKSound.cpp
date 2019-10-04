#include "DGKSound.h"
#include <cstddef>

void dbLoadSound(const char* szFilename, int iSound)
{
	DGKSound _sound;
	_sound.id = iSound;
	_sound.looping = false;
	_sound.volume = 1.0f;
	_sound.pitch = 1.0f;
	_sound.sound = LoadSound(szFilename);
	soundRef.push_back(_sound);
}

void dbLoad3DSound(const char* szFilename, int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSaveSound(const char* szFilename, int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

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


void dbPositionSound(int iSound, float fX, float fY, float fZ)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbRecordSound(int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbStopRecordingSound(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetSoundPan(int iSound, int iPan)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbSetSoundSpeed(int iSound, int iFrequency) {
	if (dbSoundExist(iSound) == 1)
	{
		float _pitch = iFrequency * 0.000125f;

		if (_pitch <= 0)
			_pitch = 1;

		for (int i = 0; i < soundRef.size(); i++)
		{
			if (soundRef[i].id == iSound)
			{
				soundRef[i].pitch = _pitch;
				//std::cout << "pitch " << _pitch << std::endl;
				SetSoundPitch(soundRef[i].sound, soundRef[i].pitch);
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

void dbSetSoundVolume(int iSound, int iVolume)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbPositionListener(float fX, float fY, float fZ)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbRotateListener(float fX, float fY, float fZ)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

void dbScaleListener(float fScale)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
}

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
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbSoundPlaying(int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbSoundLooping(int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbSoundPaused(int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbSoundPositionX(int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbSoundPositionY(int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbSoundPositionZ(int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbSoundPan(int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbSoundSpeed(int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

int dbSoundVolume(int iSound)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbListenerPositionX(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbListenerPositionY(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbListenerPositionZ(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbListenerAngleX(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbListenerAngleY(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}

float dbListenerAngleZ(void)
{
	std::cout << __func__ << " NOT IMPLEMENTED" << std::endl;
	return NULL;
}