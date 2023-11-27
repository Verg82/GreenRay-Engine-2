/******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.3
// PhongLighting.cpp
// It's The GreenRay Phong PointLight Effects Engine Source File.
// Made Specially For Implementing 3DEngine Lighting Parameters.
// Date Creation: 29 August 2005
// Last Changing: 13 April 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
******************************************************************************/
#include <PhongLighting.h>
#include <GRMethods.h>
#include <GRModels.h>
#include <GRCamera.h>
#include <GRWorld.h>

//-----------------------------------------------------------------------------
// Defines And Constants
//-----------------------------------------------------------------------------
#define NUM_LIGHTS 3 //Number Of Lights In The Scene
#define EMISSIVE_COEFFICIENT 39.78f //Emissive Color Multiplier For Each Lumen Of Light Intensity 

//-----------------------------------------------------------------------------
// Global Shader Initialization Variables
//-----------------------------------------------------------------------------
CPhongLight* gr_Phong = NULL;
CGRModels* gr_Lamp_01 = NULL;
CGRModels* gr_Lamp_02 = NULL;
CGRModels* gr_Lamp_03 = NULL;
CGRModels* gr_Table = NULL;
CGRModels* gr_Pipe_01 = NULL;
CGRModels* gr_Pipe_02 = NULL;
CGRModels* gr_Pic = NULL;
CGRModels* gr_Shelving = NULL;

//Shader Light Methods
D3DXVECTOR4 g_avLightPosition[NUM_LIGHTS]; //Light Positions In World Space
D3DXVECTOR4 g_avLightIntensity[NUM_LIGHTS]; //Light Floating Point Intensities
int g_nLightLogIntensity[NUM_LIGHTS]; //Light Intensities On A Log Scale
int g_nLightMantissa[NUM_LIGHTS]; //Mantissa Of The Light Intensity

////////////////////////////////////////////////////////////////////////////////
// External Definitions And Prototypes 
////////////////////////////////////////////////////////////////////////////////                  
//-----------------------------------------------------------------------------
// Name: RefreshLights()
// Desc: Set The Light Intensities To Match The Current Log Luminance
//-----------------------------------------------------------------------------
void RefreshLights()
{
  for (int I = 0; I < NUM_LIGHTS; I++)
  {
    g_avLightIntensity[I].x = g_nLightMantissa[I]*(float)pow(1.0f,g_nLightLogIntensity[I]);
    g_avLightIntensity[I].y = g_nLightMantissa[I]*(float)pow(1.0f,g_nLightLogIntensity[I]);
    g_avLightIntensity[I].z = g_nLightMantissa[I]*(float)pow(1.0f,g_nLightLogIntensity[I]);
    g_avLightIntensity[I].w = 1.0f;          
  }
} //EndRefreshLightsProcedure

//-----------------------------------------------------------------------------
// Name: AdjustLight
// Desc: Increment Or Decrement The Light At The Given Index
//-----------------------------------------------------------------------------
HRESULT AdjustLight(UINT iLight,bool bIncrement)
{
  if (iLight >= NUM_LIGHTS) return E_INVALIDARG;

  if (bIncrement && g_nLightLogIntensity[iLight] < 7)
  {
    g_nLightMantissa[iLight]++;
    if (g_nLightMantissa[iLight] > 9)
    {
      g_nLightMantissa[iLight] = 1;
      g_nLightLogIntensity[iLight]++;
    }
  }
    
  if (!bIncrement && g_nLightLogIntensity[iLight] > -4)
  {
    g_nLightMantissa[iLight]--;
    if (g_nLightMantissa[iLight] < 1)
    {
      g_nLightMantissa[iLight] = 9;
      g_nLightLogIntensity[iLight]--;
    }
  }

  RefreshLights();
  return S_OK;
} //EndAdjustLightFunction

///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction For CPhongLight Class
///////////////////////////////////////////////////////////////////////////////
CPhongLight::CPhongLight()
{
  m_pEffect = NULL;
  m_pTechnique01 = NULL;
} //EndConstructionDirectives

CPhongLight::~CPhongLight()
{ 
} //EndDestructionDirectives

//-----------------------------------------------------------------------------
// Name: CPhongLight::CreateShader()
// Desc: 
//-----------------------------------------------------------------------------
void CPhongLight::CreateShader(TCHAR* EffectFile,DWORD ShaderFlags)
{
  //Read The D3DX Effect File
  //If This Fails, There Should Be Debug Output As To 
  //They The .fx File Failed To Compile
  //Set Of Three Flags
  //DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;
  //dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
  //dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;

  //Creation Effect
  if (FAILED(D3DXCreateEffectFromFile(gr_Direct3DDevice,EffectFile,
  NULL,NULL,ShaderFlags,NULL,&m_pEffect,NULL)))
  {
    ShowErrorMessage("PhongLighting.cpp: Error Load Shader Effect File..");
	ReleaseClass(m_pEffect);
	return;
  } //EndCreationEffect

  //Set Effect File Variables For Effective Methods
  m_pTechnique01 = m_pEffect->GetTechniqueByName("RenderScene");  
  //g_pEffect->SetFloat("g_fBloomScale",10.0f);
  //g_pEffect->SetFloat("g_fStarScale",0.5f);
  //g_pEffect->SetBool("g_bEnableToneMap",false);
  //g_pEffect->SetBool("g_bEnableBlueShift",false);

  //SetTechnique
  if (FAILED(m_pEffect->SetTechnique(m_pTechnique01)))
  {
	ShowErrorMessage("PhongLighting.cpp: Can't Set Technigue..");
	ReleaseClass(m_pEffect);
    m_pTechnique01 = NULL;
	return;
  } //EndSetTechnique
} //EndCreateShaderProcedure

//-----------------------------------------------------------------------------
// Name: CPhongLight::CreatePhongLight()
// Desc: 
//-----------------------------------------------------------------------------
void CPhongLight::CreatePhongLight()
{
  //Construct A PhongLight Class
  gr_Phong = new CPhongLight(); 
  gr_Phong->CreateShader(TEXT("\Shaders\\PhongLighting.fx"),D3DXFX_NOT_CLONEABLE);

  //Set Light Positions In World Space And Light Intensity
  g_avLightPosition[0] = D3DXVECTOR4(1.0f, 2.5f, 4.0f, 1.0f);
  g_nLightMantissa[0] = 6.5f;
  g_nLightLogIntensity[0] = 6.5f;

  #if NUM_LIGHTS > 1
  g_avLightPosition[1] = D3DXVECTOR4(1.0f, 2.5f, 16.0f, 1.0f);
  g_nLightMantissa[1] = 6.5f;
  g_nLightLogIntensity[1] = 6.5f;
  #endif
 
  #if NUM_LIGHTS > 2
  g_avLightPosition[2] = D3DXVECTOR4(14.0f, 2.5f, 10.0f, 1.0f);
  g_nLightMantissa[2] = 6.5f;
  g_nLightLogIntensity[2] = 6.5f;
  #endif

  #if NUM_LIGHTS > 3
  g_avLightPosition[3] = D3DXVECTOR4(14.0f, 2.5f, 16.0f, 1.0f);
  g_nLightMantissa[3] = 6.5f;
  g_nLightLogIntensity[3] = 6.5f;
  #endif

  RefreshLights();

  //Create Mesh-Models To Represent Room Appartments
  gr_Lamp_01 = new CGRModels(); //Construct A Lamp Model
  gr_Lamp_01->CreateModelFromX(TEXT("\Models\\Lamps\\Wall_Lamp_01.x"));
  gr_Lamp_02 = new CGRModels(); //Construct A Lamp Model
  gr_Lamp_02->CreateModelFromX(TEXT("\Models\\Lamps\\Wall_Lamp_01.x"));
  gr_Lamp_03 = new CGRModels(); //Construct A Lamp Model
  gr_Lamp_03->CreateModelFromX(TEXT("\Models\\Lamps\\Wall_Lamp_01.x"));

  gr_Table = new CGRModels(); //Construct A Table Model
  gr_Table->CreateModelFromX(TEXT("\Models\\Table\\Table_01.x"));

  gr_Pipe_01 = new CGRModels(); //Construct A Tube_01 Model
  gr_Pipe_01->CreateModelFromX(TEXT("\Models\\Pipes\\Pipe_01.x"));
  gr_Pipe_02 = new CGRModels(); //Construct A Tube_02 Model
  gr_Pipe_02->CreateModelFromX(TEXT("\Models\\Pipes\\Pipe_01.x"));

  gr_Pic = new CGRModels(); //Construct A Vitia's Picture Model
  gr_Pic->CreateModelFromX(TEXT("\Models\\Pictures\\VitiaPic_01.x"));

  gr_Shelving = new CGRModels(); //Construct A Vitia's Picture Model
  gr_Shelving->CreateModelFromX(TEXT("\Models\\Shelving\\Shelving_01.x"));
} //EndCreatePhongLightProcedure

//-----------------------------------------------------------------------------
// Name: CPhongLight::RenderPhongLight()
// Desc: 
//-----------------------------------------------------------------------------
void CPhongLight::RenderPhongLight()
{
  //Setting Rendering Parameters
  gr_Direct3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

  //Setting Shader Parameters
  m_pEffect->SetMatrix("g_mProjection",&_MatrixProjection); //Set Projection Matrix For Our Effect !!!

  //Calculate The Position Of The Lights In View Space
  D3DXVECTOR4 avLightViewPosition[NUM_LIGHTS]; 
  
  for (int iLight = 0; iLight < NUM_LIGHTS; iLight++)
  {
    D3DXVec4Transform(&avLightViewPosition[iLight],&g_avLightPosition[iLight],&_MatrixView);
  }

  //Set Frame Shader Constants
  m_pEffect->SetValue("g_avLightPositionView",avLightViewPosition,sizeof(D3DXVECTOR4)*NUM_LIGHTS);
  m_pEffect->SetValue("g_avLightIntensity",g_avLightIntensity,sizeof(D3DXVECTOR4)*NUM_LIGHTS);

  UINT uiPassCount,uiPass;

  gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
  gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);
  
  m_pEffect->SetTechnique(m_pTechnique01);
  m_pEffect->SetMatrix("g_mObjectToView",&_MatrixView);
   
  m_pEffect->Begin(&uiPassCount,0);
  for (uiPass = 0; uiPass < uiPassCount; uiPass++)
  {
    m_pEffect->BeginPass(uiPass);

    //Turn Off Emissive Lighting
    D3DXVECTOR4 vNull(0.0f, 0.0f, 0.0f, 0.0f);
    m_pEffect->SetVector("g_vEmissive",&vNull); 
    
    //Enable Texturing
    m_pEffect->SetBool("g_bEnableTexture",true);
    //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
    //gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
    
    //Anisotropic Texture Filtering
    gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MAXANISOTROPY,4);
    gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_ANISOTROPIC);
    gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_ANISOTROPIC);
    gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_ANISOTROPIC);

    //Render Back Wall
    m_pEffect->SetFloat("g_fPhongExponent", 2.0f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 1.0f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 0.7f);
    m_pEffect->CommitChanges();
	RenderRoomBox(0);
    
    //Render Left Wall
    m_pEffect->SetFloat("g_fPhongExponent", 0.03f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 0.03f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 0.5f);
    m_pEffect->CommitChanges();
    RenderRoomBox(1);

    //Render Front Wall
    m_pEffect->SetFloat("g_fPhongExponent", 2.0f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 1.0f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 0.7f);
    m_pEffect->CommitChanges();
    RenderRoomBox(2);

    //Render Right Wall
    m_pEffect->SetFloat("g_fPhongExponent", 0.03f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 0.03f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 0.5f);
    m_pEffect->CommitChanges();
    RenderRoomBox(3);
      
    //Render Floor
    m_pEffect->SetFloat("g_fPhongExponent", 65.0f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 3.0f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 1.0f);
    m_pEffect->CommitChanges();
    RenderRoomBox(4);
    
    //Render Ceiling
    m_pEffect->SetFloat("g_fPhongExponent", 0.02f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 0.02f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 0.3f);
    m_pEffect->CommitChanges();
    RenderRoomBox(5);

    //Draw Vitia's Lamps
	{ 
    m_pEffect->SetFloat("g_fPhongExponent", 3.0f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 0.1f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 0.25f);
    m_pEffect->SetBool("g_bEnableTexture",true);

    //Set Transform,Scale And Rotation Matrices
	//Lamp_01
	gr_Lamp_01->RotationModel(-1.5f, 0.0f, 0.0f);
    gr_Lamp_01->ScaleModel(0.0090f, 0.0090f, 0.0090f);
    gr_Lamp_01->DispositionModel(0.0f, 2.5f, 4.0f);
    m_pEffect->SetMatrix("g_mObjectToView",&gr_Lamp_01->_ObjectToView);

	m_pEffect->CommitChanges();
	gr_Lamp_01->Render();
    
	//Lamp_02
	gr_Lamp_02->RotationModel(-1.5f, 0.0f, 0.0f);
    gr_Lamp_02->ScaleModel(0.0090f, 0.0090f, 0.0090f);
    gr_Lamp_02->DispositionModel(0.0f, 2.5f, 16.0f);
    m_pEffect->SetMatrix("g_mObjectToView",&gr_Lamp_02->_ObjectToView);

	m_pEffect->CommitChanges();
	gr_Lamp_02->Render();
	
	//Lamp_03
	gr_Lamp_03->RotationModel(1.5f, 0.0f, 0.0f);
    gr_Lamp_03->ScaleModel(0.0090f, 0.0090f, 0.0090f);
    gr_Lamp_03->DispositionModel(15.0f, 2.5f, 10.0f);
    m_pEffect->SetMatrix("g_mObjectToView",&gr_Lamp_03->_ObjectToView);
	m_pEffect->CommitChanges();
	gr_Lamp_03->Render();
	} 
    //End Draw Vitia's Lamps

    //Draw Vitia's Table
	{
    m_pEffect->SetFloat("g_fPhongExponent", 5.0f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 0.5f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 0.5f);
    m_pEffect->SetBool("g_bEnableTexture",true);

	gr_Table->RotationModel(-6.3f, 0.0f, 0.0f);
    gr_Table->ScaleModel(0.014f, 0.014f, 0.014f);
    gr_Table->DispositionModel(1.65f, 0.0f, 6.0f);
    m_pEffect->SetMatrix("g_mObjectToView",&gr_Table->_ObjectToView);
	m_pEffect->CommitChanges();
	gr_Table->Render();
	} 
    //End Draw Vitia's Table

    //Draw Vitia's Pipe_01
	{ 
    m_pEffect->SetFloat("g_fPhongExponent", 5.0f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 4.0f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 1.25f);
    m_pEffect->SetBool("g_bEnableTexture",true);

	gr_Pipe_01->RotationModel(1.58f, 0.0f, 0.0f);
    gr_Pipe_01->ScaleModel(0.014f, 0.014f, 0.014f);
    gr_Pipe_01->DispositionModel(15.0f, 0.51f, 12.85f);
    m_pEffect->SetMatrix("g_mObjectToView",&gr_Pipe_01->_ObjectToView);
	m_pEffect->CommitChanges();
	gr_Pipe_01->Render();
	} 
    //End Draw Vitia's Pipe_01

	//Draw Vitia's Pipe_02
	{ 
	gr_Pipe_02->RotationModel(1.58f, 0.0f, 0.0f);
    gr_Pipe_02->ScaleModel(0.014f, 0.014f, 0.014f);
    gr_Pipe_02->DispositionModel(15.0f, 0.51f, 13.55f);
    m_pEffect->SetMatrix("g_mObjectToView",&gr_Pipe_02->_ObjectToView);
	m_pEffect->CommitChanges();
	gr_Pipe_02->Render();
	}
    //End Draw Vitia's Pipe_02

	//Draw Vitia's Picture
	{ 
    m_pEffect->SetFloat("g_fPhongExponent", 5.0f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 0.5f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 0.5f);
    m_pEffect->SetBool("g_bEnableTexture",true);

	gr_Pic->RotationModel(0.0f, 0.1f, 0.0f);
    gr_Pic->ScaleModel(0.015f, 0.015f, 0.015f);
    gr_Pic->DispositionModel(0.0f, 2.0f, 6.0f);
    m_pEffect->SetMatrix("g_mObjectToView",&gr_Pic->_ObjectToView);

	m_pEffect->CommitChanges();
	gr_Pic->Render();
	} 
    //End Draw Vitia's Picture

	//Draw Vitia's Shelving
	{ 
    m_pEffect->SetFloat("g_fPhongExponent", 5.0f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 0.5f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 0.5f);
    m_pEffect->SetBool("g_bEnableTexture",true);

	gr_Shelving->RotationModel(-0.1f, 0.0f, 0.0f);
    gr_Shelving->ScaleModel(0.024f, 0.024f, 0.018f);
    gr_Shelving->DispositionModel(1.3f, 0.0f, 13.8f);
    m_pEffect->SetMatrix("g_mObjectToView",&gr_Shelving->_ObjectToView);

	m_pEffect->CommitChanges();
	gr_Shelving->Render();
	} 
    //End Draw Vitia's Shelving

    //Draw Vitia's Sraka
	/*{ 
    m_pEffect->SetFloat("g_fPhongExponent", 3.0f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 1.5f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 0.5f);
    m_pEffect->SetBool("g_bEnableTexture",false);

	gr_Sraka->RotationModel(1.58f, 0.0f, 0.0f);
    gr_Sraka->ScaleModel(0.012f, 0.012f, 0.012f);
    gr_Sraka->DispositionModel(14.95f, 0.9f, 6.5f);
    g_pEffect->SetMatrix("g_mObjectToView",&gr_Sraka->_ObjectToView);

	m_pEffect->CommitChanges();
	gr_Sraka->Render();
	}*/ 
    //End Draw Vitia's Sraka
	

    //Draw The Light Meshes
    /*g_pEffect->SetFloat("g_fPhongExponent", 5.0f);
    m_pEffect->SetFloat("g_fPhongCoefficient", 1.0f);
    m_pEffect->SetFloat("g_fDiffuseCoefficient", 1.0f);
    m_pEffect->SetBool("g_bEnableTexture",true);
	
    for (int iLight = 0; iLight < NUM_LIGHTS; iLight++)
    {  
      //Just Position The Point Light -- No Need To Orient It
      D3DXMATRIXA16 mScale;
      D3DXMatrixScaling(&mScale,0.07f, 0.07f, 0.07f);
      D3DXMatrixTranslation(&_MatrixWorld,g_avLightPosition[iLight].x, 
      g_avLightPosition[iLight].y,g_avLightPosition[iLight].z);
            
	  D3DXMATRIXA16 mWorld = mScale*_MatrixWorld;
      D3DXMATRIXA16 mObjectToView = mWorld*_MatrixView;
      g_pEffect->SetMatrix("g_mObjectToView",&mObjectToView);

      //A Light Which Illuminates Objects At 80 Lum/Sr Should Be Drawn
      //At 3183 Lumens/Meter^2/Steradian, Which Equates To A Multiplier
      //Of 39.78 Per Lumen
      D3DXVECTOR4 vEmissive = EMISSIVE_COEFFICIENT*g_avLightIntensity[iLight];
      g_pEffect->SetVector("g_vEmissive",&vEmissive);    
    
      g_pEffect->CommitChanges();
      
	  //g_pmeshSphere->DrawSubset(0);
    }gr_Lamp_01->Render();*/

    m_pEffect->EndPass();
  }
  m_pEffect->End();  
} //EndRenderPhongLightProcedure

//-----------------------------------------------------------------------------
// Name: CPhongLight::Release()
// Desc: 
//-----------------------------------------------------------------------------
void CPhongLight::Release()
{
  ReleaseClass(m_pEffect);
  m_pTechnique01 = NULL;
} //EndReleaseProcedure

//-----------------------------------------------------------------------------
// Name: CreatePhongLightShader()
// Desc: 
//-----------------------------------------------------------------------------
void CreatePhongLightShader()
{
  //Check On PixelShader 2.0 Present Parameters
  D3DCAPS9 _Caps;
  gr_Direct3DDevice->GetDeviceCaps(&_Caps);
  if (FAILED(_Caps.PixelShaderVersion < D3DPS_VERSION(2,0)))
  {
    ShowErrorMessage("PhongLighting.cpp: Your Video Card Not Support Pixel Shader Version 2.0..");
  }
  else 
  {
    gr_Phong->CreatePhongLight();
  }
} //EndCreatePhongLightShaderProcedure

//-----------------------------------------------------------------------------
// Name: RenderPhongLightShader()
// Desc: 
//-----------------------------------------------------------------------------
void RenderPhongLightShader()
{
  if (gr_Phong != NULL) gr_Phong->RenderPhongLight();
} //EndRenderPhongLightShaderProcedure

//-----------------------------------------------------------------------------
// Name: ReleaseShader()
// Desc: 
//-----------------------------------------------------------------------------
void ReleasePhongLightShader()
{
  if (gr_Phong != NULL) 
  {
	ReleaseClass(gr_Phong); DeleteClass(gr_Phong);
    
	gr_Lamp_01->ReleaseModel(); gr_Lamp_01 = NULL; //
	gr_Lamp_02->ReleaseModel(); gr_Lamp_02 = NULL; //
	gr_Lamp_03->ReleaseModel(); gr_Lamp_03 = NULL; //
	gr_Table->ReleaseModel(); gr_Table = NULL; //
  }
} //EndReleaseShaderProcedure