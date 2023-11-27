/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GRShaders.h: Interface For The CGRShaders Class.
// It's The GreenRay Shader Engine.
// Made Specially For Implementing Shader Effects.
// Date Creation: 29 August 2005
// Last Changing: 6 March 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GREngine.h>
#include <GRMethods.h>

////////////////////////////////////////////////////////////////////////////////
// Classes Used By This Header
////////////////////////////////////////////////////////////////////////////////
//class CGRShaders;

//-----------------------------------------------------------------------------
// Name: Struct CGRShaders
// Desc:
//-----------------------------------------------------------------------------
#if !defined(AFX_SHADERS_H__)
#define AFX_SHADERS_H__

class CGRShaders
{
public:
  /*Public Directives*/
  CGRShaders();
  virtual ~CGRShaders();
  void CreateShader(TCHAR* EffectFile,DWORD ShaderFlags);
private:
  /*Private Directives*/
  ID3DXEffect* gr_Effect; //General GreenRay D3DX Effect Interface
  D3DXHANDLE gr_Technique; //D3DX Technigue Handle
};
#endif //!defined(AFX_SHADERS_H__)