/****************************************************************************/ 
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GREngine.cpp Visual Studio 8 Version.
// It's An GreenRay GREngine Source File.
// Made Specially For Implement 3DEngine Parameters.
// Date Creation: 29 August 2005
// Last Changing: 11 February 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
/*****************************************************************************/
//#pragma comment(lib,"d3d9.lib");
//#pragma comment(lib,"d3dx9.lib");
#include <GREngine.h>
#include <GRMetrics.h>
#include <GRWorld.h>
#include <GRGeometry.h>
#include <GRCamera.h>
#include <GRSound.h>
#include <GREffects.h>
#include <GRModels.h>
//#include <GRMusic.h>
#include <GRLight.h>
#include <PhongLighting.h>
#include <GRSkybox.h>
#include <GRShadow.h>
#include <GRShaders.h>
#include <GRInterface.h>
#include <GRTest.h>

#ifdef __cplusplus
#define export extern "C" __declspec(dllexport)
#else
#define export __declspec(dllexport)
#endif

#ifdef __cplusplus
#define import extern "C" __declspec(dllimport)
#else
#define import __declspec(dllimport)
#endif

//Direct3D Exports..
export void SetBackbufferColor(int R, int G, int B);
export void SetFillMode(int _Mode);
//Texturing Model For RoomBox
export void SetTexturePathes(int _TexIndex,TCHAR* _TexBack,TCHAR* _TexLeft,
TCHAR* _TexFront,TCHAR* _TexRight,TCHAR* _TexFloor,TCHAR* _TexCeiling);
//Texturing Model For SkyBox
export void GR_SetSkyBoxTextures(int _TextIndex,TCHAR* _ZNeg,TCHAR* _XPos,
TCHAR* _ZPos,TCHAR* _XNeg,TCHAR* _YNeg,TCHAR* _YPos);
export void GR_PlaybackSelectedSound(TCHAR* FileName,bool m_bWave);
export void GR_PlaySound(bool m_bPlay);
export void GR_CreateCamera(HWND _HWnd);
export void GR_ConnectToCamera(bool m_bConnect,bool m_bNoClip);
export void GR_SetCameraSpeed(float _MoveSpeed);
export void SetDebugConsole();

export HRESULT CreateDirect3DInterface(HWND _HWnd);
export void RenderingDirect3D();
export void ReleaseDirect3D();

//Global Direct3D Base Interfaces
IDirect3D9* gr_Direct3D = NULL;
IDirect3DDevice9* gr_Direct3DDevice = NULL;
int gr_BackBufferWidth;
int gr_BackBufferHeight;
int _Red,_Green,_Blue; //Color Selection

//-----------------------------------------------------------------------------
// Name: SetBackbufferColor()
// Desc: Set Up Background Color
//-----------------------------------------------------------------------------
void SetBackbufferColor(int R, int G, int B)
{
  _Red = R; _Green = G; _Blue = B;
} //EndSetBackbufferColorProcedure

//-----------------------------------------------------------------------------
// Name: SetFillMode()
// Desc: 
//-----------------------------------------------------------------------------
void SetFillMode(int _Mode)
{  
  if (_Mode == 1) gr_Direct3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID); //Solid Mode
  if (_Mode == 2) gr_Direct3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME); //Wireframe Mode
  if (_Mode == 3) gr_Direct3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_POINT); //Point Mode
} //EndSetFillModeProcedure

//-----------------------------------------------------------------------------
// Name: SetTexturePathes()
// Desc: 
//-----------------------------------------------------------------------------
void SetTexturePathes(int _TexIndex,TCHAR* _TexBack,TCHAR* _TexLeft,
TCHAR* _TexFront,TCHAR* _TexRight,TCHAR* _TexFloor,TCHAR* _TexCeiling)
{
  SetRoomBoxTextures(_TexIndex,_TexBack,_TexLeft,_TexFront,_TexRight,_TexFloor,_TexCeiling);
} //EndSetTexturePathesProcedure

//-----------------------------------------------------------------------------
// Name: GR_SetSkyBoxTextures()
// Desc: 
//-----------------------------------------------------------------------------
void GR_SetSkyBoxTextures(int _TexIndex,TCHAR* _ZNeg,TCHAR* _XPos,
TCHAR* _ZPos,TCHAR* _XNeg,TCHAR* _YNeg,TCHAR* _YPos)
{  
  SetSkyBoxTextures(_TexIndex,_ZNeg,_XPos,_ZPos,_XNeg,_YNeg,_YPos);
} //EndGR_SetSkyBoxTexturesProcedure

//-----------------------------------------------------------------------------
// Name: GR_PlaybackSelectedSound()
// Desc: 
//-----------------------------------------------------------------------------
void GR_PlaybackSelectedSound(TCHAR* FileName,bool m_bWave)
{  
  ReleaseMusic(); //Free Music
  CreateMusic(FileName); //Create Music Interface
  PlaybackMusic(); //Play Music
} //EndGR_PlaybackSelectedSoundProcedure

//-----------------------------------------------------------------------------
// Name: GR_PlaySound()
// Desc: 
//-----------------------------------------------------------------------------
void GR_PlaySound(bool m_bPlay)
{  
  if (m_bPlay) PlaybackMusic(); //Play Music
  else StopMusic(); //Stop Music
} //EndGR_PlaySoundProcedure

//-----------------------------------------------------------------------------
// Name: GR_CreateCamera()
// Desc: Create GreenRay Camera
//-----------------------------------------------------------------------------
void GR_CreateCamera(HWND _HWnd)
{
  CreateCamera(_HWnd);
  RefreshCamera(); //Reset Camera
} //EndGR_CreateCameraProcedure

//-----------------------------------------------------------------------------
// Name: GR_ConnectToCamera()
// Desc: 
//-----------------------------------------------------------------------------
void GR_ConnectToCamera(bool m_bConnect,bool m_bNoClip)
{
  ConnectToCamera(m_bConnect,m_bNoClip);
} //EndGR_ConnectToCameraProcedure

//-----------------------------------------------------------------------------
// Name: GR_SetCameraSpeed()
// Desc: 
//-----------------------------------------------------------------------------
void GR_SetCameraSpeed(float _MoveSpeed)
{
  SetCameraMoveSpeed(_MoveSpeed);
} //EndGR_SetCameraSpeedProcedure

//-----------------------------------------------------------------------------
// Name: SetDebugConsole()
// Desc: 
//-----------------------------------------------------------------------------
void SetDebugConsole()
{
  CallDebugConsole();
} //EndSetDebugConsoleProcedure

//-----------------------------------------------------------------------------
// Name: CreateDirect3DInterface()
// Desc: Direct3D Initialization
//-----------------------------------------------------------------------------
HRESULT CreateDirect3DInterface(HWND _HWnd)
{
  if (NULL == (gr_Direct3D = Direct3DCreate9(D3D_SDK_VERSION))) return E_FAIL;
  
  D3DDISPLAYMODE _Display;
  if (FAILED(gr_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&_Display))) return E_FAIL;

  D3DPRESENT_PARAMETERS _Direct3DParam;
  ZeroMemory(&_Direct3DParam,sizeof(_Direct3DParam));
  //For D3D Init
  _Direct3DParam.Windowed = TRUE; //Or FALSE For Full Screen Mode
  _Direct3DParam.SwapEffect = D3DSWAPEFFECT_DISCARD;  
  //Setting Up Resolution
  //_Direct3DParam.BackBufferWidth = 1024;
  //_Direct3DParam.BackBufferHeight = 768;
  _Direct3DParam.BackBufferFormat = _Display.Format; //D3DFMT_A8R8G8B8
  //This Parameter Prevent Under FullScreen Mode
  //_Direct3DParam.FullScreen_RefreshRateInHz = _Display.RefreshRate; //D3DPRESENT_RATE_DEFAULT; 
  _Direct3DParam.EnableAutoDepthStencil = TRUE;
  _Direct3DParam.AutoDepthStencilFormat = D3DFMT_D24S8;  //D3DFMT_D16 D3DFMT_D15S1 D3DFMT_D24X8
                                                       //D3DFMT_D24S8 D3DFMT_D24X4S4 D3DFMT_D32
  _Direct3DParam.BackBufferCount = 3;
  _Direct3DParam.MultiSampleType = D3DMULTISAMPLE_NONE;  //4_SAMPLES //For Antialiasing Mode On 4x
  //_Direct3DParam.MultiSampleQuality = 1;
  
  //Get BackBufer Size
  gr_BackBufferWidth = _Direct3DParam.BackBufferWidth;
  gr_BackBufferHeight = _Direct3DParam.BackBufferHeight;

  //Depth Stencil Flags For ShadowVolume
  _Direct3DParam.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL; //|D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
  
  //Presentation Interval
  _Direct3DParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //For Windowed Mode
  //_Direct3DParam.PresentationInterval = D3DPRESENT_INTERVAL_ONE; //For FullScreen Mode

  //Create Some Direct3D Device!
  if (FAILED(gr_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,_HWnd,
  D3DCREATE_SOFTWARE_VERTEXPROCESSING,&_Direct3DParam,&gr_Direct3DDevice))) return E_FAIL;


  //Create Our Objects Directives
  { 
    if (FAILED(CreateFont("FPS"))) return E_FAIL; //Create FPS Counter Font
 
    CreateSkyBox(); //Create The SkyBox
    CreateRoomBox(); //Create The Vitia's Room
 
    //Sound Creation Directives
    {
      CreateAllSoundParameters(_HWnd); //Create All Playing Sound Files
    }
    //End Sound Creation Directives

    //CreateShadow(); //Create Shadow Volume
    CreatePhongLightShader(); //Create PhongLight Shader

    //Create User Interface Parameters
    {
      CreateInterfaceObject("_01"); 
      CreateInterfaceObject("_02");
	  CreateInterfaceObject("CrossHair");
    } //End Create User Interface Parameters

  } //End Create Our Objects Directives


  //Turn Off The Light And Disable Cull 
  gr_Direct3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
  gr_Direct3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

  //Set Around Light
  //gr_Direct3DDevice->SetRenderState(D3DRS_AMBIENT,0xFFFFFFFF);
  
  //Enable Z-Buffer
  gr_Direct3DDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);

  //Enable Antialiasing Mode
  //gr_Direct3DDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE); 
  
  //Set Shade Mode   
  //gr_Direct3DDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_PHONG);
  //gr_Direct3DDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
  return S_OK;
} //EndCreateDirect3DInterfaceFunction

//-----------------------------------------------------------------------------
// Name: RenderingDirect3D()
// Desc: Draw Direct3D Scene
//-----------------------------------------------------------------------------
void RenderingDirect3D()
{
  if (gr_Direct3DDevice != NULL) 
  {
    UpdateCamera(); //Update GreenRay Camera
	UpdateDeltaTimer(); //Update Counter Timer For Camera Motion Velocity 
    UpdateVelocity(); //Hou Is It Updating Camera When Jump KeyPressed 
    
    //Clear Back Buffer
    gr_Direct3DDevice->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,
    D3DCOLOR_XRGB(_Red,_Green,_Blue),1.0f,0);

    //Begin Scene
    if (SUCCEEDED(gr_Direct3DDevice->BeginScene()))
    {
      //Here Code For SceneInit

      RenderCamera(); //Rendering GRCamera Perspective Level
      
      RenderSkyBox(); //Render The SkyBox
	  
	  //RenderLight(); //Rendering Light
 
      
     
	  //RenderShader();

	  //Render the scene into the shadow map texture from light view
	  //RenderShadowMap();

	  //Render the scene with shadow map applied
	  //RenderScene();

      RenderPhongLightShader(); //Render Light Shader Tech
      
	  //CollideWithWalls();
      
	  //DrawShadow(); //Draw The ShadowVolume

      OutputFPS(); //Output Current FPS
	 
	  RenderInterfaceObject(); //Rendering The User Interface
   
	  gr_Direct3DDevice->EndScene();
    }
    gr_Direct3DDevice->Present(NULL,NULL,NULL,NULL);
  }
} //EndRenderingDirect3DProcedure

//-----------------------------------------------------------------------------
// Name: ReleaseDirect3D()
// Desc: Free Resources And Destroy Direct3D
//-----------------------------------------------------------------------------
void ReleaseDirect3D()
{  
  ReleaseSkyBox(); //Free SkyBox
  ReleaseRoomBox(); //Free Vitia's RoomBox
  
  ReleaseCamera(); //Free Camera
  ReleaseFont("FPS"); //Free FPS Counter Font

  ReleaseSound("Footsteps"); //Free FootSteps Sound
  ReleaseSound("GdeKonsol"); //Free Vitia Sound01
  ReleaseSound("KogoTam"); //Free Vitia Sound02
  ReleaseSound("KudaTam"); //Free Vitia Sound03
  ReleaseSound("ZachemTam"); //Free Vitia Sound04
  ReleaseMusic(); //Free Music

  ReleaseInterfaceObject("_01"); //Free 01
  ReleaseInterfaceObject("_02"); //Free 02
  ReleaseInterfaceObject("CrossHair"); //Free CrossHair
  ReleaseInterfaceObject("DebugConsole"); //Free Debug Console

  ReleasePhongLightShader(); //Free PhongLight Shader

  gr_ShadowVolume->ReleaseShadowObjects(); //Release All Created Shadow Objects
  
  //Free Direct3D
  if (gr_Direct3DDevice != NULL) gr_Direct3DDevice->Release(); //Free Direct3D Device
  if (gr_Direct3D != NULL) gr_Direct3D->Release(); //Free Direct3D Interface
} //EndReleaseDirect3DProcedure

//------------------------------------------------------------------------------