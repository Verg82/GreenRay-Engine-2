/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GRGeometry.h: Interface For The Geometry Implementation Class.
// It's The GreenRay Geometry Transform Engine.
// Made Specially For Implementing Geometry Effects, Work With Polygonal Methods
// And Tesselation.
// Date Creation: 29 August 2005
// Last Changing: 12 February 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GREngine.h>

////////////////////////////////////////////////////////////////////////////////
// Classes Used By This Header
////////////////////////////////////////////////////////////////////////////////
//class CTerrain;
//class CGRBox;
//class CGRPrimitive;

//-----------------------------------------------------------------------------
// Name: Struct CTerrain
// Desc: Interface For The CTerrain Class
//-----------------------------------------------------------------------------
#if !defined(AFX_TERRAIN_H__)
#define AFX_TERRAIN_H__

//Define A FVF For Our Terrain
#define TERRAIN_D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

class CTerrain
{
private:
  //Define A Custom Vertex For Our Terrain
  struct TERRAIN_CUSTOMVERTEX
  {
    FLOAT x,y,z;	//Position Of Vertex In 3D Space
	FLOAT nx,ny,nz; //Lighting Normal
	FLOAT tu,tv;	//Texture Coordinates
  };
public:
	bool SetMaterial(D3DCOLORVALUE rgbaDiffuse,D3DCOLORVALUE rgbaAmbient, 
	D3DCOLORVALUE rgbaSpecular,D3DCOLORVALUE rgbaEmissive,float rPower);
	bool SetTexture(const char* szTextureFilePath);
	DWORD RenderTerrain();
	CTerrain(WORD wRows = 10,WORD wCols = 10,float rTileSize = 1.0,WORD wMaxHeight = 0);
	virtual ~CTerrain();
	void Release();	
private:
	bool CreateIndexBuffer();
	bool UpdateVertices();
	bool CreateVertexBuffer();
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DMATERIAL9 m_matMaterial;
		
	WORD m_wRows;
	WORD m_wCols;
	WORD m_wMaxHeight;
	float m_rTileSize;

	DWORD m_dwNumOfVertices;	
	DWORD m_dwNumOfIndices;
	DWORD m_dwNumOfPolygons;
};
#endif //!defined(AFX_TERRAIN_H__)

//-----------------------------------------------------------------------------
// Name: CGRBox
// Desc: The Box Class
//-----------------------------------------------------------------------------
#if !defined(AFX_BOX_H__)
#define AFX_BOX_H__

#define D3DFVF_BOXVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0)) //Vertex Format

class CGRBox
{
public:
   /*Public Directives*/
  //Box Vertex, Normals, Texures Positions
  struct BOX_VERTEX
  {
    FLOAT x,y,z;    //Coordinates
    FLOAT nx,ny,nz; //Normals
    DWORD _Color;   //Vertex Color
    FLOAT tu,tv;    //Textures
  }; //End Box Vertex Formats

  CGRBox();
  virtual ~CGRBox();
 
  void SetTextureCoordinates(
  float bW_TU,float bW_TV,float lW_TU,float lW_TV,
  float fW_TU,float fW_TV,float rW_TU,float rW_TV,
  float frW_TU,float frW_TV,float cW_TU,float cW_TV);

  void SetTextures(int _TexIndex,TCHAR* _TexBack,TCHAR* _TexLeft,
  TCHAR* _TexFront,TCHAR* _TexRight,TCHAR* _TexFloor,TCHAR* _TexCeiling);
  HRESULT CreateBox(float fWidth,float fHeight,float fDepth);
  void RenderBox(int _Index);
  void Release();
protected:
  /*Protected Directives*/
  IDirect3DVertexBuffer9* pVertexBuffer; //The Vertex Buffer
  IDirect3DIndexBuffer9* pIndexBuffer; //The Index Buffer
  IDirect3DTexture9* m_pTex[6]; //Variable To Hold Same Textures
  TCHAR* m_TexPath[6]; //Variable To Hold Texture Path
  //Texture Coordinates on TU And TV
  float bW_nTU,bW_nTV;   //For BackWall
  float lW_nTU,lW_nTV;   //For LeftWall
  float fW_nTU,fW_nTV;   //For FrontWall
  float rW_nTU,rW_nTV;   //For RightWall
  float frW_nTU,frW_nTV; //For Floor
  float cW_nTU,cW_nTV;   //For Ceiling
};
#endif //!defined(AFX_BOX_H__)

//-----------------------------------------------------------------------------
// Name: CGRPrimitive
// Desc: The Primitive Class
//-----------------------------------------------------------------------------
#if !defined(AFX_PRIMITIVE_H__)
#define AFX_PRIMITIVE_H__

//Define A FVF For Our Interface Panel
#define PANEL_D3DFVF_VERTEXA (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class CGRPrimitive
{
public:
  /*Public Directives*/

  //Define A Custom Vertex For Our Panel
  struct PANEL_VERTEXA
  {
    FLOAT x,y,z; //Position Of Vertex In Space
	DWORD Color; //Colour Of Vertex
	FLOAT u,v;	 //Texture Coordinates
  };

  CGRPrimitive(int Width,int Height, 
  /*int nScreenWidth,int nScreenHeight,*/DWORD m_dwColor);
  virtual ~CGRPrimitive();
  HRESULT CreateVertexBuffer();
  void RenderPrimitive();
protected:
  /*Protected Directives*/
  IDirect3DVertexBuffer9* pVertexBuffer; //The Vertex Buffer
  DWORD dwColor;
  float m_nWidth;
  float m_nHeight;
};
#endif //!defined(AFX_PRIMITIVE_H__)
