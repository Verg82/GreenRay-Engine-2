/******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.3
// GRLight.cpp
// It's The GreenRay Direct3D Light Effects Engine Source File.
// Made Specially For Implementing 3DEngine Parameters.
// Date Creation: 29 August 2005
// Last Changing: 17 January 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
******************************************************************************/
#include <GRLight.h>

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
D3DLIGHT9 _Light;

//-----------------------------------------------------------------------------
// Name: SetLightPreferences()
// Desc: Initializes A D3DLIGHT Structure, Setting The Light Position. The
//       Diffuse Color Is Set To White; Specular And Ambient Are Left As Black
//-----------------------------------------------------------------------------
void SetLightPreferences(D3DLIGHT9& _pLight,D3DLIGHTTYPE _Type,float x,float y,float z)
{
  D3DXVECTOR3 _VecLightDir(x,y,z);
  ZeroMemory(&_pLight,sizeof(D3DLIGHT9));
  _pLight.Type = _Type;
  _pLight.Diffuse.r = 1.0f;
  _pLight.Diffuse.g = 1.0f;
  _pLight.Diffuse.b = 1.0f;
  D3DXVec3Normalize((D3DXVECTOR3*)&_pLight.Direction,&_VecLightDir);
  _pLight.Position.x = x;
  _pLight.Position.y = y;
  _pLight.Position.z = z;
  _pLight.Range = 1000.0f;
} //EndSetLightPreferencesProcedure

//-----------------------------------------------------------------------------
// Name: RenderLight()
// Desc: 
//-----------------------------------------------------------------------------
void RenderLight(LPDIRECT3DDEVICE9 pDevice)
{
  //float x,y,z;

  //Set Up A Material
  D3DMATERIAL9 _Material;
    
  ZeroMemory(&_Material,sizeof(D3DMATERIAL9));
  
  _Material.Diffuse.r = 1.0f; _Material.Ambient.r = 0.5f;
  _Material.Diffuse.g = 1.0f; _Material.Ambient.g = 0.5f;
  _Material.Diffuse.b = 1.0f; _Material.Ambient.b = 0.5f;
  _Material.Diffuse.a = 0.5f; _Material.Ambient.a = 0.5f;

  //Specular Material Property
  //_Material.Specular.r = 1.0f;
  //_Material.Specular.g = 1.0f; 
  //_Material.Specular.b = 1.0f;
  //_Material.Specular.a = 1.0f;
  //Emissive Material Property
  //_Material.Emissive.r = 0.0f;
  //_Material.Emissive.g = 0.75f;
  //_Material.Emissive.b = 0.0f;
  //_Material.Emissive.a = 0.0f;

  pDevice->SetMaterial(&_Material);

  //Note That Many Lights May Be Active At A Time (But Each One Slows Down
  //The Rendering Of Our Scene). Also, We Need To Set The D3DRS_LIGHTING Renderstate To Enable Lighting
   
  D3DLIGHT9 _Light;
  ZeroMemory(&_Light,sizeof(D3DLIGHT9));
  
  //_Light.Type = D3DLIGHT_DIRECTIONAL;
  _Light.Type = D3DLIGHT_POINT;
  _Light.Diffuse.r = 1.0f;
  _Light.Diffuse.g = 1.0f;
  _Light.Diffuse.b = 1.0f;
  _Light.Diffuse.a = 0.5f;

  _Light.Ambient.r = 0.4f;
  _Light.Ambient.g = 0.4f;
  _Light.Ambient.b = 0.4f;
	
  D3DXVECTOR3 _VectorDir;
  //Values For The Light Position, Direction, And Color
  //x = Sin(GetTickCount/500);
  //y = 1.0f;
  //z = 1.0f;

  /*X = X-(GetTickCount/500*0.003f);
  Y = Y-(GetTickCount/500*0.01f);

  _Light.Diffuse.r = 1.0f;
  _Light.Diffuse.g = 1.0f;
  _Light.Diffuse.b = 1.0f;
  _Light.Range  = 100.0f;  */

  

  /*D3DXVec3Scale(_Light.Position,D3DXVector3(cos(X),1.0f,sin(X)),2.5f);
  _D3DLight.Attenuation1 = 0.4f;*/



  /*Effect землетрясение
  D3DXMatrixTranslation(&matWorld,x,y,z);
  gr_Direct3DDevice->SetTransform(D3DTS_WORLD,&matWorld);*/


  //_Light.Specular.r = 1.0f;
  //_Light.Specular.g = 1.0f;
  //_Light.Specular.b = 1.0f;

  //Y = 1/(a0+a1*x+a2*x*x)

  //_VectorDir = D3DXVector3(1*Power(10.0,2), 1.0, 1*Power(10.0,2));
  //D3DXVec3Normalize(_Light.Position,&_VectorDir);  


  /*vecDir = D3DXVECTOR3(cosf(timeGetTime()/350.0f),1.0f,sinf(timeGetTime()/350.0f));
  D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
  _Light.Range = 1000.0f;
  gr_Direct3DDevice->SetLight(0,&_Light);
  gr_Direct3DDevice->LightEnable(0,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);*/
   
  _Light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

  _Light.Attenuation0 = 1.0f;
  _Light.Attenuation1 = 0.0f;
  _Light.Attenuation2 = 0.0f;

  //_Light.Falloff = 12.0f;
  //_Light.Theta = 1.0f;

  _Light.Range = 16.5f;

  //Normalize Light Direction
  D3DXVECTOR3 _VecDir;
  //SetUp Normal
  _VecDir = D3DXVECTOR3(0.0f,0.0f,-1.0f);
  D3DXVec3Normalize((D3DXVECTOR3*)&_Light.Direction,&_VecDir);

  pDevice->SetLight(0,&_Light);
  pDevice->LightEnable(0,TRUE);

  //Finally Turn On Some Ambient Light.
  pDevice->SetRenderState(D3DRS_AMBIENT,D3DCOLOR_COLORVALUE(0.1f,0.1f,0.1f,1.0f));
} //EndRenderLightProcedure

//------------------------------------------------------------------------------