/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GREffects.h: Interface For The CGREffects Class.
// It's The GreenRay Sound Effects Engine.
// Made Specially For Implementing Ambient Music And Sound Effects.
// Date Creation: 29 August 2005
// Last Changing: 13 March 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GREngine.h>

//Exports..
//For Playing Any Different Sounds
void CreateAllSoundParameters(HWND _HWnd);
void PlaybackSound(LPCSTR Param);
void ReleaseSound(LPCSTR Param);

//Music
void CreateMusic(TCHAR* FileName);
void PlaybackMusic();
void StopMusic();
void ReleaseMusic();