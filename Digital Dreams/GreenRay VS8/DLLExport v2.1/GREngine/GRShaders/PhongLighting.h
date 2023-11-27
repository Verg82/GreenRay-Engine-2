/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.3
// PhongLighting.h
// It's The GreenRay Phong PointLight Effects Engine Header File.
// Made Specially For Implementing 3DEngine Lighting Parameters.
// Date Creation: 29 August 2005
// Last Changing: 13 April 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GREngine.h>

//Export Creation Procedure Of Phong Light Shader
void CreatePhongLightShader();
void RenderPhongLightShader();
void ReleasePhongLightShader();

////////////////////////////////////////////////////////////////////////////////
// Classes Used By This Header
////////////////////////////////////////////////////////////////////////////////
//class CPhongLight;

//-----------------------------------------------------------------------------
// Name: Struct CPhongLight
// Desc: 
//-----------------------------------------------------------------------------
#if !defined(AFX_PhongLight_H__)
#define AFX_PhongLight_H__
class CPhongLight
{	
private:
  /*Private Directives*/
public:
  /*Public Directives*/
  CPhongLight();
  virtual ~CPhongLight();

  void CreateShader(TCHAR* EffectFile,DWORD ShaderFlags);
  void CreatePhongLight();
  void RenderPhongLight();
  void Release();
public:  
  /*Public Directives*/
  ID3DXEffect* m_pEffect; //D3DX Effect Interface
  D3DXHANDLE m_pTechnique01; //D3DX Technigue01 Handle
protected:
  /*Protected Directives*/
};
#endif //!defined(AFX_PhongLight_H__)