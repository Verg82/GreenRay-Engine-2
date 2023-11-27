/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GRWorld.cpp
// It's The GreenRay WorldMap Geometry Transform Engine Source File.
// Made Specially For Implementing Only WorldMap Geometry Effects.
// Date Creation: 29 August 2005
// Last Changing: 2 April 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GRWorld.h>
#include <GRMethods.h>
#include <GRMetrics.h>
#include <GRGeometry.h>

//-----------------------------------------------------------------------------
// Scene Geometry Variables
//-----------------------------------------------------------------------------
CGRBox* gr_Room = NULL; //Global RoomBox Directive

//Room Methods
//-----------------------------------------------------------------------------
// Name: CreateRoomBox()
// Desc: 
//-----------------------------------------------------------------------------
void CreateRoomBox()
{ 
  //gr_Terrain = new CTerrain(2,2,20.0f,0); //Create Terrain
  //gr_Terrain->SetTexture("\Textures\\Cellar\\Ceiling_02.jpg"); //Setting Up Texture

  gr_Room = new CGRBox(); //Construct A RoomBox Class

  //Set Texturing Coords On TU And TV
  gr_Room->SetTextureCoordinates(
  //tu    tv
  2.1f, 0.499f, //On BackWall
  2.9f, 0.499f, //On LeftWall
  2.1f, 0.499f, //On FrontWall
  2.9f, 0.499f, //On RightWall
  6.0f, 6.0f,   //On Floor
  2.0f, 2.0f);  //On Ceiling

  //Create Our RoomBox Model With Size W   H    D
  if (SUCCEEDED(gr_Room->CreateBox(15.0f,3.5f,20.0f)))
  { gr_RoomSt = (TEXT("Room Geometry Created OK")); gr_RoomStE = 1; }
  else { gr_RoomSt = (TEXT("Error Create Room Geometry")); gr_RoomStE = 2; }
} //EndCreateRoomBoxProcedure

//-----------------------------------------------------------------------------
// Name: SetBoxTextures()
// Desc: 
//-----------------------------------------------------------------------------
void SetRoomBoxTextures(int _TexIndex,TCHAR* _TexBack,TCHAR* _TexLeft,
TCHAR* _TexFront,TCHAR* _TexRight,TCHAR* _TexFloor,TCHAR* _TexCeiling)
{
  gr_Room->SetTextures(_TexIndex,_TexBack,_TexLeft,_TexFront,_TexRight,_TexFloor,_TexCeiling);
} //EndSetBoxTexturesProcedure

//-----------------------------------------------------------------------------
// Name: RenderRoomBox()
// Desc: 
//-----------------------------------------------------------------------------
void RenderRoomBox(int _Index)
{
  //Setting Rendering Parameters And Draw A Room
  gr_Direct3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

  //VU Addr
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

  //Set Texture Mode
  //gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
  //gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_POINT);
  
  if (gr_Room != NULL) gr_Room->RenderBox(_Index); //Render Our Custom Room Box
} //EndRenderRoomBoxProcedure

//-----------------------------------------------------------------------------
// Name: ReleaseRoomBox()
// Desc: 
//-----------------------------------------------------------------------------
void ReleaseRoomBox()
{
  if (gr_Room != NULL) { ReleaseClass(gr_Room); DeleteClass(gr_Room); } //Release Room Box
  //if (gr_Terrain != NULL) { ReleaseClass(gr_Terrain); DeleteClass(gr_Terrain); } //Release Terrain
} //EndReleaseRoomBoxProcedure