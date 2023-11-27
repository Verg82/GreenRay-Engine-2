/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GRWorld.h: Interface For The WorldMap Geometry Implementation Class.
// It's The GreenRay WorldMap Geometry Transform Engine.
// Made Specially For Implementing Only WorldMap Geometry Effects.
// Date Creation: 29 August 2005
// Last Changing: 2 April 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GREngine.h>

//Exports For Scene Geometry Initialization Routines
void CreateRoomBox();
void SetRoomBoxTextures(int _TexIndex,TCHAR* _TexBack,TCHAR* _TexLeft,
TCHAR* _TexFront,TCHAR* _TexRight,TCHAR* _TexFloor,TCHAR* _TexCeiling);
void RenderRoomBox(int _Index);
void ReleaseRoomBox();

