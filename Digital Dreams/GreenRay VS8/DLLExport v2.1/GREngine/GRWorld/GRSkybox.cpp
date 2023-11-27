/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GRSkybox.cpp: Interface For The TGRCamera Class.
// It's The GreenRay SkyBox.
// Made Specially For Implementing SkyBox Environment Map.
// Date Creation: 29 August 2005
// Last Changing: 2 April 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GRSkybox.h>
#include <GRMethods.h>
#include <GRGeometry.h>
#include <GRCamera.h>

//-----------------------------------------------------------------------------
// SkyBox Geometry Initialization Variables
//-----------------------------------------------------------------------------
CGRBox* gr_SkyBox = NULL; //Global SkyBox Directive

//SkyBox Methods
//-----------------------------------------------------------------------------
// Name: CreateSkyBox()
// Desc: 
//-----------------------------------------------------------------------------
void CreateSkyBox()
{ 
  gr_SkyBox = new CGRBox(); //Construct A SkyBox Class
    
  //Create Our SkyBox Model With Size W      H       D
  if (FAILED(gr_SkyBox->CreateBox(1000.0f,1000.0f,1000.0f)))
  { 
    ShowErrorMessage("GRWorld.cpp Error Create SkyBox Geometry..");
  }
} //EndCreateSkyBoxProcedure

//-----------------------------------------------------------------------------
// Name: SetSkyBoxTextures()
// Desc: 
//-----------------------------------------------------------------------------
void SetSkyBoxTextures(int _TexIndex,TCHAR* _ZNeg,TCHAR* _XPos,
TCHAR* _ZPos,TCHAR* _XNeg,TCHAR* _YNeg,TCHAR* _YPos)
{
  gr_SkyBox->SetTextures(_TexIndex,_ZNeg,_XPos,_ZPos,_XNeg,_YNeg,_YPos);
} //EndSetSkyBoxTexturesProcedure

//-----------------------------------------------------------------------------
// Name: RenderSkyBox()
// Desc: 
//-----------------------------------------------------------------------------
void RenderSkyBox()
{
  //Setting Rendering Parameters And Draw A SkyBox
  gr_Direct3DDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
  gr_Direct3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
  gr_Direct3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
  gr_Direct3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

  //VU Addr
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);
  gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
  gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);

  //Set Texture Mode
  //gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
  //gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);	
  //gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
  gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
  gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_POINT);

  //Set Perspective View For Spherical Show SkyBox In Space (60 Grad)
  D3DXMATRIXA16 _MatProj;
  //FLOAT fAspectRatio = (float)m_d3dsdBackBuffer.Width/(float)m_d3dsdBackBuffer.Height;
  D3DXMatrixPerspectiveFovLH(&_MatProj,/*D3DX_PI*0.5f*/D3DXToRadian(60.0f),
  1.0f/*fAspectRatio*/,1.0f,1000.0f);
  gr_Direct3DDevice->SetTransform(D3DTS_PROJECTION,&_MatProj); 

  if (gr_SkyBox != NULL) 
  {
	//gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
    //gr_Direct3DDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_ALWAYS);
		
    //Translation Matrices For The SkyBox Object
    D3DXMATRIXA16 _MatTrans,_MatRotate,_MatPos,_MatCentered; 
    //                                    X       Y       Z
    D3DXMatrixTranslation(&_MatCentered,-500.0f,-500.0f,-500.0f); 
    D3DXMatrixRotationYawPitchRoll(&_MatRotate,D3DX_PI,0.0f,0.0f);
    D3DXMatrixTranslation(&_MatPos,GetCameraX(),GetCameraY(),GetCameraZ());
    _MatTrans = (_MatCentered*_MatRotate)*_MatPos;
    gr_Direct3DDevice->SetTransform(D3DTS_WORLD,&_MatTrans); //Transform Object Position In Space

	//Draw Some SkyBox Here 
	gr_Direct3DDevice->SetTexture(0,NULL);
    for (int I = 0; I < 6; I++) gr_SkyBox->RenderBox(I); //Render Our Custom SkyBox
	
	//gr_Direct3DDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
    //gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_DISABLE);
  }
} //EndRenderSkyBoxProcedure

//-----------------------------------------------------------------------------
// Name: ReleaseSkyBox()
// Desc: 
//-----------------------------------------------------------------------------
void ReleaseSkyBox()
{
  if (gr_SkyBox != NULL) { ReleaseClass(gr_SkyBox); DeleteClass(gr_SkyBox); } //Release SkyBox
} //EndReleaseSkyBoxProcedure

//-----------------------------------------------------------------------------

//Old SkyBox Examle
/*
//SkyBox Texture Vertex Positions
struct ENV_VERTEX
{
  D3DXVECTOR3 m_vecPos;
  D3DXVECTOR2 m_vecTex;
};

const DWORD ENV_VERTEX_FVF = D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0);

//Global Skybox Variables
TGRSkyBox gr_SkyBox;
IDirect3DTexture9* m_pSkyTex[6];
TCHAR* szSkyTex[6];
BOOL m_bDrawSkyBox;

//------------------------------------------------------------------------------
// Name: TGRSkyBox::CreateSkyBox()
// Desc: 
//------------------------------------------------------------------------------
HRESULT CreateSkyBox()
{
  //Initialize Environment
  float _Radius = 1000.0f; 
  if(FAILED(gr_SkyBox.Initialize(_Radius))) return E_FAIL;
  
  //Misc Stuff
  D3DXMATRIXA16 m_matPosition;
  D3DXMatrixRotationX(&m_matPosition,D3DX_PI*-0.3f);
  m_matPosition._42 = 15.0f;
  m_matPosition._43 = 15.0f;  
  D3DXMatrixInverse(&m_matView,NULL,&m_matPosition);
  
  //Setup Render States
  //gr_Direct3DDevice->SetFVF(D3DFVF_XYZ);

  m_bDrawSkyBox = TRUE;

  for (UINT I = 0; I<6; I++)
  {
    D3DXCreateTextureFromFileEx(gr_Direct3DDevice,szSkyTex[I],D3DX_DEFAULT,D3DX_DEFAULT, 
    1,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,0,NULL,NULL,&m_pSkyTex[I]);
  }

  //gr_Direct3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
  //gr_Direct3DDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);

  //gr_Direct3DDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
 
  //Set Texture Modes
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_MIRROR);
  //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_MIRROR);
  //gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_TEXCOORDINDEX,0); 
  
  //Set Cull Mode
  gr_Direct3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
  
  //Set Skybox Surfaces
  if (FAILED(gr_SkyBox.SetSurfaces(
  m_pSkyTex[D3DCUBEMAP_FACE_NEGATIVE_X],m_pSkyTex[D3DCUBEMAP_FACE_POSITIVE_X], 
  m_pSkyTex[D3DCUBEMAP_FACE_NEGATIVE_Y],m_pSkyTex[D3DCUBEMAP_FACE_POSITIVE_Y],
  m_pSkyTex[D3DCUBEMAP_FACE_POSITIVE_Z],m_pSkyTex[D3DCUBEMAP_FACE_NEGATIVE_Z]))) return E_FAIL;
    
  return S_OK;
} //EndCreateSkyBoxFunction

//------------------------------------------------------------------------------
// Name: TGRSkyBox::DrawTheSkyBox()
// Desc: 
//------------------------------------------------------------------------------
void DrawTheSkybox()
{
  //Setting Rendering Parameters And Draw Environment
  gr_Direct3DDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
  gr_Direct3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
  //gr_Direct3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
  gr_Direct3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
		


  D3DXMATRIXA16 _MatTrans;
  D3DXMatrixTranslation(&_MatTrans,0.0f,0.0f,0.0f); //Translation Matrix For Skybox

  if (m_bDrawSkyBox)
  {
    //gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
    //gr_Direct3DDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_ALWAYS);
    gr_Direct3DDevice->SetTransform(D3DTS_WORLD,&_MatTrans); 
    gr_SkyBox.Draw();

    //gr_Direct3DDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
    //gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_DISABLE);
  }
  else
  {
    gr_Direct3DDevice->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,0x00000000,1.0f,0);
  }
} //EndDrawTheSkyboxProcedure

//////////////////////////////////////////////////////////////////////////////
// Construction/Destruction For TGRSkyBox Class
//////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
// Name: TGRSkyBox::Initialize()
// Desc: 
//------------------------------------------------------------------------------
HRESULT TGRSkyBox::Initialize(float fSize)
{
  m_fSize = fSize;
  return S_OK;
} //EndInitializeFunction

//------------------------------------------------------------------------------
// Name: TGRSkyBox::Release()
// Desc: 
//------------------------------------------------------------------------------
void TGRSkyBox::Release()
{
  for (UINT I = 0; I<6; I++) ReleaseClass(m_pSkyTex[I]);
  m_bDrawSkyBox = FALSE;
} //EndReleaseProcedure

//------------------------------------------------------------------------------
// Name: TGRSkyBox::SetSurfaces()
// Desc: 
//------------------------------------------------------------------------------
HRESULT TGRSkyBox::SetSurfaces(
IDirect3DTexture9* pXNeg, IDirect3DTexture9* pXPos,
IDirect3DTexture9* pYNeg, IDirect3DTexture9* pYPos,
IDirect3DTexture9* pZNeg, IDirect3DTexture9* pZPos)
{
  m_pSurf[0] = pXNeg;
  m_pSurf[1] = pXPos;
  m_pSurf[2] = pYNeg;
  m_pSurf[3] = pYPos;
  m_pSurf[4] = pZNeg;
  m_pSurf[5] = pZPos;

  return S_OK;
} //EndSetSurfacesFunction

//------------------------------------------------------------------------------
// Name: TGRSkyBox::Draw()
// Desc: 
//------------------------------------------------------------------------------
HRESULT TGRSkyBox::Draw()
{
  float f;
  ENV_VERTEX vert[4];

  f = 0.5f/512.0f;

  vert[0].m_vecTex = D3DXVECTOR2(0.0f+f, 0.0f+f);
  vert[1].m_vecTex = D3DXVECTOR2(0.0f+f, 1.0f-f);
  vert[2].m_vecTex = D3DXVECTOR2(1.0f-f, 0.0f+f);
  vert[3].m_vecTex = D3DXVECTOR2(1.0f-f, 1.0f-f);

  gr_Direct3DDevice->SetFVF(ENV_VERTEX_FVF);
  f = m_fSize*0.5f;

  //XNeg
  vert[0].m_vecPos = D3DXVECTOR3(-f,  f,  f);
  vert[1].m_vecPos = D3DXVECTOR3(-f, -f,  f);
  vert[2].m_vecPos = D3DXVECTOR3(-f,  f, -f);
  vert[3].m_vecPos = D3DXVECTOR3(-f, -f, -f);

  gr_Direct3DDevice->SetTexture(0,m_pSurf[0]);
  gr_Direct3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,(LPVOID)vert,sizeof(ENV_VERTEX));

  //XPos
  vert[0].m_vecPos = D3DXVECTOR3( f,  f, -f);
  vert[1].m_vecPos = D3DXVECTOR3( f, -f, -f);
  vert[2].m_vecPos = D3DXVECTOR3( f,  f,  f);
  vert[3].m_vecPos = D3DXVECTOR3( f, -f,  f);

  gr_Direct3DDevice->SetTexture(0,m_pSurf[1]);
  gr_Direct3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,(LPVOID)vert,sizeof(ENV_VERTEX));

  //YNeg
  vert[0].m_vecPos = D3DXVECTOR3(-f, -f, -f);
  vert[1].m_vecPos = D3DXVECTOR3(-f, -f,  f);
  vert[2].m_vecPos = D3DXVECTOR3( f, -f, -f);
  vert[3].m_vecPos = D3DXVECTOR3( f, -f,  f);

  gr_Direct3DDevice->SetTexture(0,m_pSurf[2]);
  gr_Direct3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,(LPVOID)vert,sizeof(ENV_VERTEX));
    
  //YPos
  vert[0].m_vecPos = D3DXVECTOR3(-f,  f,  f);
  vert[1].m_vecPos = D3DXVECTOR3(-f,  f, -f);
  vert[2].m_vecPos = D3DXVECTOR3( f,  f,  f);
  vert[3].m_vecPos = D3DXVECTOR3( f,  f, -f);

  gr_Direct3DDevice->SetTexture(0,m_pSurf[3]);
  gr_Direct3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,(LPVOID)vert,sizeof(ENV_VERTEX));

  //ZNeg
  vert[0].m_vecPos = D3DXVECTOR3(-f,  f, -f);
  vert[1].m_vecPos = D3DXVECTOR3(-f, -f, -f);
  vert[2].m_vecPos = D3DXVECTOR3( f,  f, -f);
  vert[3].m_vecPos = D3DXVECTOR3( f, -f, -f);

  gr_Direct3DDevice->SetTexture(0,m_pSurf[4]);
  gr_Direct3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,(LPVOID)vert,sizeof(ENV_VERTEX));

  //ZPos
  vert[0].m_vecPos = D3DXVECTOR3( f,  f,  f);
  vert[1].m_vecPos = D3DXVECTOR3( f, -f,  f);
  vert[2].m_vecPos = D3DXVECTOR3(-f,  f,  f);
  vert[3].m_vecPos = D3DXVECTOR3(-f, -f,  f);

  gr_Direct3DDevice->SetTexture(0,m_pSurf[5]);
  gr_Direct3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,(LPVOID)vert,sizeof(ENV_VERTEX));

  return S_OK;
} //EndDrawFunction
*/
//-----------------------------------------------------------------------------