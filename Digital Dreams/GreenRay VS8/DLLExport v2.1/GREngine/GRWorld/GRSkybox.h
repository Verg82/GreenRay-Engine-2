/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GRSkybox.h: Interface For The TGRCamera Class.
// It's The GreenRay SkyBox Header File.
// Made Specially For Implementing SkyBox Environment Map.
// Date Creation: 29 August 2005
// Last Changing: 2 April 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GREngine.h>

//Export SkyBox Methods..
void CreateSkyBox();
void SetSkyBoxTextures(int _TexIndex,TCHAR* _ZNeg,TCHAR* _XPos,
TCHAR* _ZPos,TCHAR* _XNeg,TCHAR* _YNeg,TCHAR* _YPos);
void RenderSkyBox();
void ReleaseSkyBox();