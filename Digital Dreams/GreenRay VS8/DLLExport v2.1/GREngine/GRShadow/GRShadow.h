/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GRShadow.h: Interface For The CGRShadowVolume Class.
// It's The GreenRay ShadowVolume Engine.
// Made Specially For Implementing Shadow Effects With Using Stencil Buffer.
// Date Creation: 29 August 2005
// Last Changing: 11 February 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GREngine.h>
#include <GRMesh.h>

//Exports..
void CreateShadow();
void DrawShadow();

////////////////////////////////////////////////////////////////////////////////
// External Definitions And Prototypes 
////////////////////////////////////////////////////////////////////////////////
struct VERTEX
{
  D3DXVECTOR3 p;
  D3DXVECTOR3 n;
  FLOAT tu,tv;
};

const DWORD VERTEX_FVF = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1;

struct SHADOWVERTEX
{
  D3DXVECTOR4 _Pos;
  D3DCOLOR _Color;
};

const DWORD SHADOWVERTEX_FVF = D3DFVF_XYZRHW|D3DFVF_DIFFUSE; //Base ShadowVertex

////////////////////////////////////////////////////////////////////////////////
// Classes Used By This Header
////////////////////////////////////////////////////////////////////////////////
//class CShadowVolume;

//-----------------------------------------------------------------------------
// Name: Struct CShadowVolume
// Desc: A Shadow Volume Object
//-----------------------------------------------------------------------------
#if !defined(AFX_SHADOWVOLUME_H__)
#define AFX_SHADOWVOLUME_H__

class CShadowVolume
{
  D3DXVECTOR3 m_pVertices[32000]; //Vertex Data For Rendering Shadow Volume
  DWORD m_dwNumVertices;  
public:
  /*Public Directives*/
  CShadowVolume();
  virtual ~CShadowVolume();
  void ReleaseShadow();
  void ReleaseShadowObjects();
  void Reset() { m_dwNumVertices = 0L; }
  HRESULT BuildShadowSquare(LPDIRECT3DDEVICE9 pDevice,float sx,float sy,int _Color);
  HRESULT BuildFromMesh(LPD3DXMESH pObject,D3DXVECTOR3 vLight);
 
  HRESULT Render(LPDIRECT3DDEVICE9 pDevice);
  HRESULT RenderShadow(LPDIRECT3DDEVICE9 pDevice,D3DXMATRIXA16* _TransMatrix);
  HRESULT DrawShadow(LPDIRECT3DDEVICE9 pDevice);
private:
  /*Private Directives*/
  LPDIRECT3DVERTEXBUFFER9 m_pBigSquareVB;
  void AddEdge(WORD* pEdges,DWORD& dwNumEdges,WORD v0,WORD v1);
};
#endif //!defined(AFX_SHADOWVOLUME_H__)

////////////////////////////////////////////////////////////////////////////////
// External Directives
////////////////////////////////////////////////////////////////////////////////
extern CShadowVolume* gr_ShadowVolume; //Global GreenRay ShadowVolume Interface

