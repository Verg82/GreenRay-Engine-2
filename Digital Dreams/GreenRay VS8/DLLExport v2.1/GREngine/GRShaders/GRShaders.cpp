/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GRShaders.cpp
// It's The GreenRay Shader Engine Source File.
// Date Creation: 29 August 2005
// Last Changing: 6 March 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GRShaders.h>

//-----------------------------------------------------------------------------
// Global Shader Initialization Variables
//-----------------------------------------------------------------------------
//Prepare For Shader
//LPD3DXBUFFER Code = NULL; //Buffer
//LPDIRECT3DPIXELSHADER9 pPShader = NULL; //Pixel Shader

///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction For CGRInterface Class
///////////////////////////////////////////////////////////////////////////////
CGRShaders::CGRShaders()
{
  gr_Effect = NULL;
  gr_Technique = NULL;
} //EndConstructionDirectives

CGRShaders::~CGRShaders()
{ 
} //EndDestructionDirectives

//-----------------------------------------------------------------------------
// Name: CGRShaders::CreateShader()
// Desc: 
//-----------------------------------------------------------------------------
void CGRShaders::CreateShader(TCHAR* EffectFile,DWORD ShaderFlags)
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
  NULL,NULL,ShaderFlags,NULL,&gr_Effect,NULL)))
  {
    ShowErrorMessage("GRShaders.cpp: Error Load Shader Effect File..");
	ReleaseClass(gr_Effect);
	return;
  } //EndCreationEffect

  //Find Valid Techniques
  if (FAILED(gr_Effect->FindNextValidTechnique(NULL,&gr_Technique)))
  {
    ShowErrorMessage("GRShaders.cpp: No Valid Techique Find In Effect File..");
	ReleaseClass(gr_Effect);
	return;
  } //EndGetTechniques

   //Set Technique
  if (FAILED(gr_Effect->SetTechnique(gr_Technique)))
  {
	ShowErrorMessage("GRShaders.cpp: Can't Set Technigue..");
	ReleaseClass(gr_Effect);
	return;
  } //EndSetTechnique

  //Load Pixel Shader
  //if (FAILED(D3DXAssembleShaderFromFile(TEXT("PixelShader.psh"),0,0,0,&Code,0)))
  //{
	 //ShowErrorMessage("GRGeometry.cpp: ");
  //}
  
  //Create Shader
  //gr_Direct3DDevice->CreatePixelShader((DWORD*)Code->GetBufferPointer(),&pPShader);
  //Destroy Buffer
  //Code->Release();

  //Render Shader
  //gr_Direct3DDevice->SetPixelShader(pPShader);
} //EndCreateShaderProcedure

