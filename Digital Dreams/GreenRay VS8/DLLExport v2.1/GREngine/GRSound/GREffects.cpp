/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GREffects.cpp
// It's The GreenRay Sound Effects Engine Source File.
// Made Specially For Implementing Ambient Music And Sound Effects.
// Date Creation: 29 August 2005
// Last Changing: 13 March 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GREffects.h>
#include <GRSound.h>

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
TGRWave* gr_FootStep = NULL; //Wave Directive For Playing FootSteps Sound
CGRMusic* Mp3 = NULL; //Mp3 Directive For Playing Music

TGRWave* gr_VitiaLoh01 = NULL; //Wave Directive For Playing Sound01
TGRWave* gr_VitiaLoh02 = NULL; //Wave Directive For Playing Sound02
TGRWave* gr_VitiaLoh03 = NULL; //Wave Directive For Playing Sound03
TGRWave* gr_VitiaLoh04 = NULL; //Wave Directive For Playing Sound04

//-----------------------------------------------------------------------------
// Name: CreateAllSoundParameters()
// Desc: 
//-----------------------------------------------------------------------------
void CreateAllSoundParameters(HWND _HWnd)
{
  //Create FootStep Sound
  gr_FootStep = new TGRWave();
  gr_FootStep->CreateSoundInterface(_HWnd,TEXT("\Sounds\\Player\\Foot\\Stone\\Tile_01.wav"),2,44100,32);

  //Bazar Loshpaka Viti
  gr_VitiaLoh01 = new TGRWave();
  gr_VitiaLoh01->CreateSoundInterface(_HWnd,TEXT("\Sounds\\Vitia\\Speech\\Gde Konsol.wav"),2,44100,32);
  gr_VitiaLoh02 = new TGRWave();
  gr_VitiaLoh02->CreateSoundInterface(_HWnd,TEXT("\Sounds\\Vitia\\Speech\\Kogo Tam.wav"),2,44100,32);
  gr_VitiaLoh03 = new TGRWave();
  gr_VitiaLoh03->CreateSoundInterface(_HWnd,TEXT("\Sounds\\Vitia\\Speech\\Kuda Tam.wav"),2,44100,32);
  gr_VitiaLoh04 = new TGRWave();
  gr_VitiaLoh04->CreateSoundInterface(_HWnd,TEXT("\Sounds\\Vitia\\Speech\\Zachem Tam.wav"),2,44100,32);

} //EndCreateAllSoundParametersProcedure

//-----------------------------------------------------------------------------
// Name: PlaybackSound()
// Desc: 
//-----------------------------------------------------------------------------
void PlaybackSound(LPCSTR Param)
{
  //Playing Footsteps
  if (Param == "Footsteps") { if (gr_FootStep != NULL) gr_FootStep->PlaybackSound(); } 
  
  //Playing Chmo
  if (Param == "GdeKonsol") { if (gr_VitiaLoh01 != NULL) gr_VitiaLoh01->PlaybackSound(); }
  if (Param == "KogoTam") { if (gr_VitiaLoh02 != NULL) gr_VitiaLoh02->PlaybackSound(); }
  if (Param == "KudaTam") { if (gr_VitiaLoh03 != NULL) gr_VitiaLoh03->PlaybackSound(); }
  if (Param == "ZachemTam") { if (gr_VitiaLoh04 != NULL) gr_VitiaLoh04->PlaybackSound(); }

} //EndPlaybackSoundProcedure

//-----------------------------------------------------------------------------
// Name: ReleaseSound()
// Desc: 
//-----------------------------------------------------------------------------
void ReleaseSound(LPCSTR Param)
{
  //Free Footsteps Sound
  if (Param == "Footsteps") { if (gr_FootStep != NULL) { gr_FootStep->ReleaseSound(); gr_FootStep = NULL; } }

  //Free Pizduk Bazar
  if (Param == "GdeKonsol") { if (gr_VitiaLoh01 != NULL) { gr_VitiaLoh01->ReleaseSound(); gr_VitiaLoh01 = NULL; } }
  if (Param == "KogoTam") { if (gr_VitiaLoh02 != NULL) { gr_VitiaLoh02->ReleaseSound(); gr_VitiaLoh02 = NULL; } }
  if (Param == "KudaTam") { if (gr_VitiaLoh03 != NULL) { gr_VitiaLoh03->ReleaseSound(); gr_VitiaLoh03 = NULL; } }
  if (Param == "ZachemTam") { if (gr_VitiaLoh04 != NULL) { gr_VitiaLoh04->ReleaseSound(); gr_VitiaLoh04 = NULL; } }

} //EndReleaseSoundProcedure


//Music
//-----------------------------------------------------------------------------
// Name: CreateMusic()
// Desc: 
//-----------------------------------------------------------------------------
void CreateMusic(TCHAR* FileName)
{
  Mp3 = new CGRMusic(); //Create A Static The CGRMusic Class

  if (FAILED(Mp3->CreateSound(FileName)))
  {
	ReleaseClass(Mp3); DeleteClass(Mp3);
	ShowErrorMessage("<GREffects.cpp> Can't Create Music");
  }
} //EndCreateMusicProcedure

//-----------------------------------------------------------------------------
// Name: PlaybackMusic()
// Desc: 
//-----------------------------------------------------------------------------
void PlaybackMusic()
{
  if (Mp3 != NULL) Mp3->PlaySound();
} //EndPlaybackMusicProcedure

//-----------------------------------------------------------------------------
// Name: StopMusic()
// Desc: 
//-----------------------------------------------------------------------------
void StopMusic()
{
  if (Mp3 != NULL) Mp3->StopSound();
} //EndStopMusicProcedure

//-----------------------------------------------------------------------------
// Name: ReleaseMusic()
// Desc: 
//-----------------------------------------------------------------------------
void ReleaseMusic()
{
  if (Mp3 != NULL)
  { 
	StopMusic();
    ReleaseClass(Mp3); DeleteClass(Mp3);
  }
} //EndReleaseMusicProcedure