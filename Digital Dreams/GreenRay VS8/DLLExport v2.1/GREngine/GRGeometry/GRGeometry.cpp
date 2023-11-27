/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GRGeometry.cpp
// It's The GreenRay Geometry Transform Engine Source File.
// Made Specially For Implementing Geometry Effects, Work With Polygonal Methods
// And Tesselation.
// Date Creation: 29 August 2005
// Last Changing: 12 February 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GRGeometry.h>
#include <GRMethods.h>

////////////////////////////////////////////////////////////////////////////////
// External Definitions And Prototypes 
////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Name: GetTriangelNormal()
// Desc: 
//-----------------------------------------------------------------------------
D3DXVECTOR3 GetTriangelNormal(D3DXVECTOR3* vVertex1,D3DXVECTOR3* vVertex2,D3DXVECTOR3* vVertex3)
{
  D3DXVECTOR3 vNormal;
  D3DXVECTOR3 v1;
  D3DXVECTOR3 v2;
  
  D3DXVec3Subtract(&v1,vVertex2,vVertex1);
  D3DXVec3Subtract(&v2,vVertex3,vVertex1);

  D3DXVec3Cross(&vNormal,&v1,&v2);
  D3DXVec3Normalize(&vNormal,&vNormal);

  return vNormal;
} //EndGetTriangelNormalFunction

///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction For CTerrain Class
///////////////////////////////////////////////////////////////////////////////
CTerrain::CTerrain(WORD wRows,WORD wCols,float rTileSize,WORD wMaxHeight)
{
  m_pVertexBuffer = NULL;
  m_pIndexBuffer = NULL;
  m_pTexture = NULL;

  //Set A Default Size And Position
  m_wRows = wRows;
  m_wCols = wCols;
	
  //Set The Tile Size For The Terrain
  m_rTileSize = rTileSize;

  //Set The Max Height For Any Vertex
  m_wMaxHeight = wMaxHeight;

  //Setup Counts For This Object
  m_dwNumOfVertices = (m_wCols+1)*(m_wRows+1);
  m_dwNumOfPolygons = m_wRows*m_wCols*2;
  m_dwNumOfIndices = m_dwNumOfPolygons*3;

  //Set Material Default Values (R, G, B, A)
  D3DCOLORVALUE rgbaDiffuse  = {1.0, 1.0, 1.0, 0.0,};
  D3DCOLORVALUE rgbaAmbient  = {1.0, 1.0, 1.0, 0.0,};
  D3DCOLORVALUE rgbaSpecular = {0.0, 0.0, 0.0, 0.0,};
  D3DCOLORVALUE rgbaEmissive = {0.0, 0.0, 0.0, 0.0,};
  SetMaterial(rgbaDiffuse,rgbaAmbient,rgbaSpecular,rgbaEmissive,0);

  //Initialize Vertex Buffer
  if(CreateVertexBuffer())
  {
    if(CreateIndexBuffer())
	{
	  if(UpdateVertices())
	  {
	    //ShowErrorMessage("<Lua>Terrain Created OK..");
		return;
	  }
	}
  }
  //ShowErrorMessage("<Lua>Terrain Failed To Create..");
} //EndConstructionDirectives

CTerrain::~CTerrain()
{
} //EndDestructionDirectives

//-----------------------------------------------------------------------------
// Name: CTerrain::Release()
// Desc: 
//-----------------------------------------------------------------------------
void CTerrain::Release()
{
  ReleaseClass(m_pTexture);
  ReleaseClass(m_pIndexBuffer);
  ReleaseClass(m_pVertexBuffer);
} //EndCTerrainReleaseProcedure

//-----------------------------------------------------------------------------
// Name: CTerrain::RenderTerrain()
// Desc: 
//-----------------------------------------------------------------------------
DWORD CTerrain::RenderTerrain()
{
  //Setting Rendering Parameters And Draw A Terrain
  gr_Direct3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
  gr_Direct3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

  //Translation Matrices For The Terrain
  D3DXMATRIXA16 _MatTrans;
  D3DXMatrixTranslation(&_MatTrans,0.0f,-5.0f,0.0f); 

  gr_Direct3DDevice->SetStreamSource(0,m_pVertexBuffer,0,sizeof(TERRAIN_CUSTOMVERTEX));
  gr_Direct3DDevice->SetFVF(TERRAIN_D3DFVF_CUSTOMVERTEX);
	
  if(m_pTexture != NULL)
  {
    //A Texture Has Been Set. We Want Our Texture To Be Shaded Based
	//On The Current Light Levels, So Used D3DTOP_MODULATE.
	gr_Direct3DDevice->SetTexture(0,m_pTexture);
	gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
	gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_CURRENT);
  }
  else
  {
	//No Texture Has Been Set
	gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG2);
	gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	gr_Direct3DDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_CURRENT);
  }

  //Select The Material To Use
  gr_Direct3DDevice->SetMaterial(&m_matMaterial);

  //Select Index Buffer
  gr_Direct3DDevice->SetIndices(m_pIndexBuffer);

  //Translation Terrain Object In Space
  gr_Direct3DDevice->SetTransform(D3DTS_WORLD,&_MatTrans);

  //Render Polygons From Index Buffer
  gr_Direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,m_dwNumOfVertices,0,m_dwNumOfPolygons);
	
  gr_Direct3DDevice->SetTexture(0,0);
  gr_Direct3DDevice->SetStreamSource(0,0,0,0);
  gr_Direct3DDevice->SetIndices(0);

  //Return The Number Of Polygons Rendered
  return m_dwNumOfPolygons;
} //EndRenderTerrainFunction

//-----------------------------------------------------------------------------
// Name: CTerrain::CreateVertexBuffer()
// Desc: 
//-----------------------------------------------------------------------------
bool CTerrain::CreateVertexBuffer()
{
  //Create The Vertex Buffer From Our Device.
  if (FAILED(gr_Direct3DDevice->CreateVertexBuffer(m_dwNumOfVertices*sizeof(TERRAIN_CUSTOMVERTEX),
  0,TERRAIN_D3DFVF_CUSTOMVERTEX,D3DPOOL_DEFAULT,&m_pVertexBuffer,NULL)))
  {
    ShowErrorMessage("<Lua>CTerrain: Unable To Create Vertex Buffer..");
    return false;
  }
  return true;
} //EndCreateVertexBufferFunction

//-----------------------------------------------------------------------------
// Name: CTerrain::CreateIndexBuffer()
// Desc: 
//-----------------------------------------------------------------------------
bool CTerrain::CreateIndexBuffer()
{
  void* pBufferIndices;

  //Create The Index Buffer From Our Device
  if (FAILED(gr_Direct3DDevice->CreateIndexBuffer(m_dwNumOfIndices*sizeof(WORD), 
  0,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_pIndexBuffer,NULL)))
  {
    ShowErrorMessage("<Lua>CTerrain: Unable To Create Index Buffer..");
	return false;
  }
	
  //Set Values For The Index Buffer
  WORD* pIndices = new WORD[m_dwNumOfIndices]; //Array Holds The Indices
	
  WORD a = m_wCols+1;
  WORD b = 0;
  WORD c = a+1;

  WORD x,z,I = 0;

  for (z = 0; z<m_wRows; z++)
  {
    for (x = 0; x<m_wCols; x++)
	{
	  pIndices[I] = a;
	  pIndices[I+1]	= b;
	  pIndices[I+2]	= c;
	  pIndices[I+3]	= b+1;
	  pIndices[I+4]	= c;
	  pIndices[I+5]	= b;

	  a++;
	  b++;
	  c++;
	  I+= 6;
	} //End SndFor

	a = c;
	b++;
	c++;
  } //End FstFor

  //Get A Pointer To The Index Buffer Indices And Lock The Index Buffer    
  if (FAILED(m_pIndexBuffer->Lock(0,m_dwNumOfIndices*sizeof(WORD),(void**)&pBufferIndices,0)))
  {
    ShowErrorMessage("<Lua>CTerrain: Unable To Lock Index Buffer..");
	return false;
  }

  //Copy Our Stored Indices Values Into The Index Buffer
  memcpy(pBufferIndices,pIndices,m_dwNumOfIndices*sizeof(WORD));
	
  //Unlock The Index Buffer
  if (FAILED(m_pIndexBuffer->Unlock()))
  {
    ShowErrorMessage("<Lua>CTerrain: Unable To Unlock Index Buffer..");
	return false;
  }

  //Clean Up
  delete pIndices;
  pIndices = NULL;

  return true;
} //EndCreateIndexBufferFunction

//-----------------------------------------------------------------------------
// Name: CTerrain::UpdateVertices()
// Desc: 
//-----------------------------------------------------------------------------
bool CTerrain::UpdateVertices()
{
  DWORD i = 0;
  VOID* pVertices;
  WORD* pBufferIndices;
  D3DXVECTOR3 vNormal;
  DWORD dwVertex1;
  DWORD dwVertex2;
  DWORD dwVertex3;

  WORD* pNumOfSharedPolygons = new WORD[m_dwNumOfVertices];	//Array Holds How Many Times This Vertex Is Shared
  D3DVECTOR* pSumVertexNormal = new D3DVECTOR[m_dwNumOfVertices]; //Array Holds Sum Of All Face Normals For Shared Vertex
  TERRAIN_CUSTOMVERTEX* pcvVertices = new TERRAIN_CUSTOMVERTEX[m_dwNumOfVertices]; //Array Holds The Veritces																				

  float x,z;

  //Centre Terrain Around The Origin
  float zStart	= (float)(0.0-(m_wRows/2.0));
  float zEnd = (float)(m_wRows/2.0);
  float xStart = (float)(0.0-(m_wCols/2.0));
  float xEnd = (float)(m_wCols/2.0);

  //Initialise The Random Number Generator
  //srand(timeGetTime());  

  //Clear Memory And etup Vertices For Terrain
  for (z = zStart; z <= zEnd; z++)
  {
	for (x = xStart; x <= xEnd; x++)
	{
	  pNumOfSharedPolygons[i] = 0;
	  pSumVertexNormal[i] = D3DXVECTOR3(0,0,0);

	  pcvVertices[i].x = x*m_rTileSize;
			
	  //Make Sure That The Edges Are All The Same Level
	  if ((z == zStart)||(z == zEnd)||(x == xStart)||(x == xEnd))
	  {
	    pcvVertices[i].y = 0.0;
	  }
	  else
	  {
	    //Set A Height For Y
		pcvVertices[i].y = (float)m_wMaxHeight;
	  }
			
      pcvVertices[i].z = -z*m_rTileSize;	
	  pcvVertices[i].nx = 0.0;
	  pcvVertices[i].ny = 0.0;
	  pcvVertices[i].nz = 0.0;
			
	  if (((int)z % 2) == 0)
	  {
	    if (((int)x % 2) == 0)
		{
		  pcvVertices[i].tu = 0.0;
		  pcvVertices[i].tv = 0.0;
		}
		else
		{
		  pcvVertices[i].tu = 1.0;
		  pcvVertices[i].tv = 0.0;
		}
	  }
	  else
	  {
	    if (((int)x % 2) == 0)
		{
		  pcvVertices[i].tu = 0.0;
		  pcvVertices[i].tv = 1.0;
		}
		else
		{
		pcvVertices[i].tu = 1.0;
		pcvVertices[i].tv = 1.0;
		}
	  }
      i++;
	} //End SndFor
  } //End FstFor

  //Get A Pointer To The Index Buffer Indices And Lock The Index Buffer    
  if (FAILED(m_pIndexBuffer->Lock(0,m_dwNumOfIndices*sizeof(WORD), 
  (void**)&pBufferIndices,D3DLOCK_READONLY)))
  {
    ShowErrorMessage("<Lua>CTerrain: Unable To Lock Index Buffer..");
	return false;
  }

  //For Each Triangle, Count The Number Of Times Each Vertex Is Used And
  //Add Together The Normals Of Faces That Share A Vertex
  for (i = 0; i<m_dwNumOfIndices; i+= 3)
  {
    dwVertex1 = pBufferIndices[i];
	dwVertex2 = pBufferIndices[i+1];
	dwVertex3 = pBufferIndices[i+2];

	vNormal = GetTriangelNormal(
	&D3DXVECTOR3(pcvVertices[dwVertex1].x,pcvVertices[dwVertex1].y,pcvVertices[dwVertex1].z), 
	&D3DXVECTOR3(pcvVertices[dwVertex2].x,pcvVertices[dwVertex2].y,pcvVertices[dwVertex2].z), 
	&D3DXVECTOR3(pcvVertices[dwVertex3].x,pcvVertices[dwVertex3].y,pcvVertices[dwVertex3].z));

		
	pNumOfSharedPolygons[dwVertex1]++;
	pNumOfSharedPolygons[dwVertex2]++;
	pNumOfSharedPolygons[dwVertex3]++;

	pSumVertexNormal[dwVertex1].x+= vNormal.x;
	pSumVertexNormal[dwVertex1].y+= vNormal.y;
	pSumVertexNormal[dwVertex1].z+= vNormal.z;
		
	pSumVertexNormal[dwVertex2].x+= vNormal.x;
	pSumVertexNormal[dwVertex2].y+= vNormal.y;
	pSumVertexNormal[dwVertex2].z+= vNormal.z;

	pSumVertexNormal[dwVertex3].x+= vNormal.x;
	pSumVertexNormal[dwVertex3].y+= vNormal.y;
	pSumVertexNormal[dwVertex3].z+= vNormal.z;
  } //End For

  //Unlock The Index Buffer
  if (FAILED(m_pIndexBuffer->Unlock()))
  {
    ShowErrorMessage("<Lua>CTerrain: Unable To Unlock Index Buffer..");
	return false;
  }

  //For Each Vertex, Calculate The Average Normal
  for (i = 0; i<m_dwNumOfVertices; i++)
  {
    vNormal.x = pSumVertexNormal[i].x/pNumOfSharedPolygons[i];
	vNormal.y = pSumVertexNormal[i].y/pNumOfSharedPolygons[i];
	vNormal.z = pSumVertexNormal[i].z/pNumOfSharedPolygons[i];

	D3DXVec3Normalize(&vNormal,&vNormal);

	pcvVertices[i].nx = vNormal.x;
	pcvVertices[i].ny = vNormal.y;
	pcvVertices[i].nz = vNormal.z;

    //CHAR DEBUG[255];
	//sprintf(DEBUG,"Vertex Data %d: x = %f, y = %f, z = %f, nx = %f, ny = %f, nz = %f, tu = %f, tv = %f\n", 
	//i, pcvVertices[i].x, pcvVertices[i].y, pcvVertices[i].z, pcvVertices[i].nx, 
	//pcvVertices[i].ny, pcvVertices[i].nz, pcvVertices[i].tu, pcvVertices[i].tv);
	//OutputDebugString(DEBUG);
  } //End For

  //Get a pointer to the vertex buffer vertices and lock the vertex buffer
  if (FAILED(m_pVertexBuffer->Lock(0,m_dwNumOfVertices*sizeof(TERRAIN_CUSTOMVERTEX),(void**)&pVertices,0)))
  {
    ShowErrorMessage("<Lua>CTerrain: Unable To Lock Vertex Buffer..");
	return false;
  }

  //Copy Our Stored Vertices Values Into The Vertex Buffer
  memcpy(pVertices,pcvVertices,m_dwNumOfVertices*sizeof(TERRAIN_CUSTOMVERTEX));

  //Unlock The Vertex Buffer
  if (FAILED(m_pVertexBuffer->Unlock()))
  {
    ShowErrorMessage("<Lua>CTerrain: Unable To Unlock Vertex Buffer..");
	return false;
  }
	
  //Clean Up
  delete pNumOfSharedPolygons;
  delete pSumVertexNormal;
  delete pcvVertices;

  pNumOfSharedPolygons = NULL;
  pSumVertexNormal = NULL;
  pcvVertices = NULL;

  return true;
} //EndUpdateVerticesFunction

//-----------------------------------------------------------------------------
// Name: CTerrain::SetTexture()
// Desc: 
//-----------------------------------------------------------------------------
bool CTerrain::SetTexture(const char *szTextureFilePath)
{
  if (FAILED(D3DXCreateTextureFromFileA(gr_Direct3DDevice,szTextureFilePath,&m_pTexture)))
  {
    ShowErrorMessage("<Lua>CTerrain: Failed To Load Texture..");
	return false;
  }
  return false;
} //EndSetTextureFunction

//-----------------------------------------------------------------------------
// Name: CTerrain::SetMaterial()
// Desc: 
//-----------------------------------------------------------------------------
bool CTerrain::SetMaterial(D3DCOLORVALUE rgbaDiffuse,D3DCOLORVALUE rgbaAmbient, 
D3DCOLORVALUE rgbaSpecular,D3DCOLORVALUE rgbaEmissive,float rPower)
{
  //Set The RGBA For Diffuse Light Reflected From This Material 
  m_matMaterial.Diffuse = rgbaDiffuse; 

  //Set The RGBA For Ambient Light Reflected From This Material 
  m_matMaterial.Ambient = rgbaAmbient; 

  //Set The Color And Sharpness Of Specular Highlights For The Material 
  m_matMaterial.Specular = rgbaSpecular; 
  m_matMaterial.Power = rPower;

  //Set The RGBA For Light Emitted From This Material 
  m_matMaterial.Emissive = rgbaEmissive;

  return true;
} //EndSetMaterialFunction

//////////////////////////////////////////////////////////////////////////////
// Construction/Destruction For CGRBox Class
//////////////////////////////////////////////////////////////////////////////
CGRBox::CGRBox()
{
  pVertexBuffer = NULL; //Prepare Vertex Buffer
  pIndexBuffer = NULL; //Prepare Index Buffer
  memset(m_pTex,0x00,sizeof(m_pTex));

  //Reset Texture Coordinates On TU Ant TV
  bW_nTU =  1.0f;  bW_nTV =  1.0f; //For BackWall
  lW_nTU =  1.0f;  lW_nTV =  1.0f; //For LeftWall 
  fW_nTU =  1.0f;  fW_nTV =  1.0f; //For FrontWall
  rW_nTU =  1.0f;  rW_nTV =  1.0f; //For RightWall
  frW_nTU = 1.0f;  frW_nTV = 1.0f; //For Floor
  cW_nTU =  1.0f;  cW_nTV =  1.0f; //For Ceiling
} //EndConstructionDirectives

CGRBox::~CGRBox()
{  
} //EndDestructionDirectives

//------------------------------------------------------------------------------
// Name: CGRBox::Release()
// Desc: 
//------------------------------------------------------------------------------
void CGRBox::Release()
{
  for (UINT I = 0; I < 6; I++) { ReleaseClass(m_pTex[I]); } //Free Textures
  ReleaseClass(pVertexBuffer); //Free Vertex Buffer
  ReleaseClass(pIndexBuffer); //Free Index Buffer
} //EndReleaseProcedure

//-----------------------------------------------------------------------------
// Name: CGRBox::SetTextureCoordinates()
// Desc: Set Texture Coordinates On TU Ant TV
//-----------------------------------------------------------------------------
void CGRBox::SetTextureCoordinates(
float bW_TU,float bW_TV,float lW_TU,float lW_TV,
float fW_TU,float fW_TV,float rW_TU,float rW_TV,
float frW_TU,float frW_TV,float cW_TU,float cW_TV)
{
  bW_nTU =  bW_TU;  bW_nTV =  bW_TV;  //For BackWall
  lW_nTU =  lW_TU;  lW_nTV =  lW_TV;  //For LeftWall 
  fW_nTU =  fW_TU;  fW_nTV =  fW_TV;  //For FrontWall
  rW_nTU =  rW_TU;  rW_nTV =  rW_TV;  //For RightWall
  frW_nTU = frW_TU; frW_nTV = frW_TV; //For Floor
  cW_nTU =  cW_TU;  cW_nTV = cW_TV;   //For Ceiling
} //EndSetTextureCoordinatesProcedure

//-----------------------------------------------------------------------------
// Name: CGRBox::SetTextures()
// Desc: Loading And Init Texturing
//-----------------------------------------------------------------------------
void CGRBox::SetTextures(int _TexIndex,TCHAR* _TexBack,TCHAR* _TexLeft,
TCHAR* _TexFront,TCHAR* _TexRight,TCHAR* _TexFloor,TCHAR* _TexCeiling)
{
  //Release Needed Texture
  //m_TexPath[_TexIndex] = NULL;
  ReleaseClass(m_pTex[_TexIndex]);
  for (UINT I = 0; I < 6; I++) { m_TexPath[I] = NULL; }

  m_TexPath[0] = _TexBack;
  m_TexPath[1] = _TexLeft;
  m_TexPath[2] = _TexFront;
  m_TexPath[3] = _TexRight;
  m_TexPath[4] = _TexFloor;
  m_TexPath[5] = _TexCeiling;

  //Create Same Textures
  D3DXCreateTextureFromFileEx(gr_Direct3DDevice,m_TexPath[_TexIndex],D3DX_DEFAULT,D3DX_DEFAULT,
  1,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,0,NULL,NULL,&m_pTex[_TexIndex]);
} //EndSetTexturesProcedure

//-----------------------------------------------------------------------------
// Name: CGRBox::CreateBox()
// Desc: Initialize Our Vertexes Structure
//-----------------------------------------------------------------------------
HRESULT CGRBox::CreateBox(float fWidth,float fHeight,float fDepth)
{
  BOX_VERTEX Vertexes[] =
  {
    //Width   Height   Depth  nx     ny    nz    Color   tu(W)   tv(H)
    //Back Wall
	{ fWidth, 0.0f,    0.0f, 0.0f, 0.0f, 1.0f, 0xffffff, 0.0f,   bW_nTV, }, //A
    { fWidth, fHeight, 0.0f, 0.0f, 0.0f, 1.0f, 0xffffff, 0.0f,   0.0f,   }, //B
    { 0.0f,   fHeight, 0.0f, 0.0f, 0.0f, 1.0f, 0xffffff, bW_nTU, 0.0f,   }, //C
	{ 0.0f,   0.0f,    0.0f, 0.0f, 0.0f, 1.0f, 0xffffff, bW_nTU, bW_nTV, }, //D
    
	//Left Wall
    { 0.0f, 0.0f,    0.0f,   1.0f, 0.0f, 0.0f, 0xffffff, 0.0f,   lW_nTV, }, //A2
    { 0.0f, fHeight, 0.0f,   1.0f, 0.0f, 0.0f, 0xffffff, 0.0f,   0.0f,   }, //B2
    { 0.0f, fHeight, fDepth, 1.0f, 0.0f, 0.0f, 0xffffff, lW_nTU, 0.0f,   }, //C2
	{ 0.0f, 0.0f,    fDepth, 1.0f, 0.0f, 0.0f, 0xffffff, lW_nTU, lW_nTV, }, //D2
    
	//Front Wall
	{ 0.0f,   0.0f,    fDepth, 0.0f, 0.0f, -1.0f, 0xffffff, 0.0f,   fW_nTV, }, //A3
    { 0.0f,   fHeight, fDepth, 0.0f, 0.0f, -1.0f, 0xffffff, 0.0f,   0.0f,   }, //B3
    { fWidth, fHeight, fDepth, 0.0f, 0.0f, -1.0f, 0xffffff, fW_nTU, 0.0f,   }, //C3
	{ fWidth, 0.0f,    fDepth, 0.0f, 0.0f, -1.0f, 0xffffff, fW_nTU, fW_nTV, }, //D3
    
	//Right Wall
    { fWidth, 0.0f,    fDepth, -1.0f, 0.0f, 0.0f, 0xffffff, 0.0f,   rW_nTV, }, //A4  
    { fWidth, fHeight, fDepth, -1.0f, 0.0f, 0.0f, 0xffffff, 0.0f,   0.0f,   }, //B4
    { fWidth, fHeight, 0.0f,   -1.0f, 0.0f, 0.0f, 0xffffff, rW_nTU, 0.0f,   }, //C4
	{ fWidth, 0.0f,    0.0f,   -1.0f, 0.0f, 0.0f, 0xffffff, rW_nTU, rW_nTV, }, //D4
    
	//Floor    
    { fWidth, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 0xffffff, frW_nTU, frW_nTV, }, //A5
    { 0.0f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 0xffffff, 0.0f,    frW_nTV, }, //B5
    { 0.0f,   0.0f, fDepth, 0.0f, 1.0f, 0.0f, 0xffffff, 0.0f,    0.0f,    }, //C5
	{ fWidth, 0.0f, fDepth, 0.0f, 1.0f, 0.0f, 0xffffff, frW_nTU, 0.0f,    }, //D5
     
	//Ceiling
    { fWidth, fHeight, fDepth, 0.0f, -1.0f, 0.0f, 0xffffff, cW_nTU, cW_nTV, }, //A6 
    { 0.0f,   fHeight, fDepth, 0.0f, -1.0f, 0.0f, 0xffffff, 0.0f,   cW_nTV, }, //B6
    { 0.0f,   fHeight, 0.0f,   0.0f, -1.0f, 0.0f, 0xffffff, 0.0f,   0.0f,   }, //C6
	{ fWidth, fHeight, 0.0f,   0.0f, -1.0f, 0.0f, 0xffffff, cW_nTU, 0.0f,   }, //D6
    //  x        y       z      nx     ny    nz     Color    tu(W)   tv(H)
  }; //End Vertexes Description

  const unsigned short Index[] = 
  {
  0,1,2,    2,3,0,
  4,5,6,    6,7,4,
  8,9,10,   10,11,8,
  12,13,14, 14,15,12,
  16,17,18, 18,19,16,
  20,21,22, 22,23,20, 
  }; //End Indexes Description
	
  //For Loading Textures Previous Declarations

  //Create Vertex Buffer
  if (FAILED(gr_Direct3DDevice->CreateVertexBuffer(36*sizeof(BOX_VERTEX),0, 
  D3DFVF_BOXVERTEX,D3DPOOL_DEFAULT,&pVertexBuffer,NULL))) return E_FAIL;

  //Lock The Vertex Buffer
  VOID* pBV;
  if (FAILED(pVertexBuffer->Lock(0,sizeof(Vertexes),(void**)&pBV,0))) return E_FAIL;
  
  memcpy(pBV,Vertexes,sizeof(Vertexes)); //Copy Vertex Data To Memory

  pVertexBuffer->Unlock(); //Unlock The Vertex Buffer
    
  //Create Index Buffer
  gr_Direct3DDevice->CreateIndexBuffer(36*sizeof(Index),0, 
  D3DFMT_INDEX16,D3DPOOL_DEFAULT,&pIndexBuffer,NULL);
    
  //Lock The Index Buffer
  VOID* pBI;
  pIndexBuffer->Lock(0,sizeof(Index),(void**)&pBI,0); 
    
  memcpy(pBI,Index,sizeof(Index)); //Copy Index Data To Memory
      
  pIndexBuffer->Unlock(); //Unlock The Index Buffer
 
  return S_OK;
} //EndCreateBoxFunction

//-----------------------------------------------------------------------------
// Name: CGRBox::RenderBox()
// Desc: Rendering The Box Geometry With Textures
//-----------------------------------------------------------------------------
void CGRBox::RenderBox(int _Index)
{  
  //Set Vertex And Index Buffers To Render
  gr_Direct3DDevice->SetStreamSource(0,pVertexBuffer,0,sizeof(BOX_VERTEX));
  gr_Direct3DDevice->SetFVF(D3DFVF_BOXVERTEX);
  gr_Direct3DDevice->SetIndices(pIndexBuffer);
  
  //Output For Created Objects
  if (_Index == 0) //Render BackWall
  {
	if (m_pTex[0] != NULL) gr_Direct3DDevice->SetTexture(0,m_pTex[0]);
    gr_Direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );
  }

  if (_Index == 1) //Render LeftWall
  {
    if (m_pTex[1] != NULL) gr_Direct3DDevice->SetTexture(0,m_pTex[1]);
    gr_Direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 4, 0, 4, 0, 2 ); //Offset To 4 Base Vertex Index 
  }

  if (_Index == 2) //Render FrontWall
  {
	if (m_pTex[2] != NULL) gr_Direct3DDevice->SetTexture(0,m_pTex[2]);
    gr_Direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 8, 0, 4, 0, 2 ); //Offset To 8 Base Vertex Index 
  }

  if (_Index == 3) //Render RightWall
  {
	if (m_pTex[3] != NULL) gr_Direct3DDevice->SetTexture(0,m_pTex[3]);
    gr_Direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 12, 0, 4, 0, 2 ); //Offset To 12 Base Vertex Index 
  }

  if (_Index == 4) //Render Floor
  {
	if (m_pTex[4] != NULL) gr_Direct3DDevice->SetTexture(0,m_pTex[4]);
    gr_Direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 16, 0, 4, 0, 2 ); //Offset To 16 Base Vertex Index
  }

  if (_Index == 5) //Render Ceiling
  {
	if (m_pTex[5] != NULL) gr_Direct3DDevice->SetTexture(0,m_pTex[5]);
	gr_Direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 20, 0, 4, 0, 2 ); //Offset To 20 Base Vertex Index
  }
} //EndRenderBoxProcedure

///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction For CGRPrimitive Class
///////////////////////////////////////////////////////////////////////////////
CGRPrimitive::CGRPrimitive(int Width,int Height, 
/*int nScreenWidth,int nScreenHeight,*/DWORD m_dwColor)
{
  pVertexBuffer = NULL;
  m_nWidth = (float)Width;
  m_nHeight = (float)Height;
  dwColor = m_dwColor;

  //Initialize Vertex Buffer
  if (FAILED(CreateVertexBuffer())) ShowErrorMessage("GRInterface.cpp: Unable To Create Vertex Buffer.."); 
} //EndConstructionDirectives

CGRPrimitive::~CGRPrimitive()
{ 
  //ReleaseClass(pTexture);
  //ReleaseClass(pVertexBuffer);
} //EndDestructionDirectives

//-----------------------------------------------------------------------------
// Name: CGRPrimitive::CreateVertexBuffer()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CGRPrimitive::CreateVertexBuffer()
{
  HRESULT _Result = S_OK;

  const FLOAT fDepth = 1.0f; //Z

  //m_nWidth = 594.0f;
  //m_nHeight = 520.0f;

  //Vertexes Description
  PANEL_VERTEXA Vertexes[] = 
  {
	{0.0,      m_nHeight, fDepth, dwColor, 0.0f, 0.0f}, //A
	{m_nWidth, m_nHeight, fDepth, dwColor, 1.0f, 0.0f}, //B
	{m_nWidth, 0.0f,      fDepth, dwColor, 1.0f, 1.0f}, //C

	{m_nWidth, 0.0f,      fDepth, dwColor, 1.0f, 1.0f}, //C
	{0.0f,     0.0f,      fDepth, dwColor, 0.0f, 1.0f}, //D
	{0.0f,     m_nHeight, fDepth, dwColor, 0.0f, 0.0f}, //A
     //X         Y           Z     Color   TexU  TexV
  }; //End Vertexes Description

  //Create Vertex Buffer
  if (FAILED(gr_Direct3DDevice->CreateVertexBuffer(6*sizeof(PANEL_VERTEXA),0, 
  PANEL_D3DFVF_VERTEXA,D3DPOOL_DEFAULT,&pVertexBuffer,NULL))) _Result = E_FAIL;

  //Lock The Vertex Buffer
  VOID* pBV;
  if (FAILED(pVertexBuffer->Lock(0,sizeof(Vertexes),(void**)&pBV,0))) _Result = E_FAIL;
  
  memcpy(pBV,Vertexes,sizeof(Vertexes)); //Copy Vertex Data To Memory

  pVertexBuffer->Unlock(); //Unlock The Vertex Buffer

  return _Result;
} //EndCreateVertexBufferFunction

//-----------------------------------------------------------------------------
// Name: CGRPrimitive::RenderPrimitive()
// Desc: 
//-----------------------------------------------------------------------------
void CGRPrimitive::RenderPrimitive()
{
  //Setting Rendering Parameters
  gr_Direct3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
  
  //Translation Matrices For This Object  
  D3DXMATRIXA16 _MatCentered; 
  D3DXMatrixTranslation(&_MatCentered,1.5f,0.5f,10.0f); 
  gr_Direct3DDevice->SetTransform(D3DTS_WORLD,&_MatCentered); //Transform Object Position In Space
  
  //Render Some Primitive
  gr_Direct3DDevice->SetStreamSource(0,pVertexBuffer,0,sizeof(PANEL_VERTEXA));
  gr_Direct3DDevice->SetFVF(PANEL_D3DFVF_VERTEXA);
  gr_Direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);
} //EndRenderPrimitiveProcedure

//-----------------------------------------------------------------------------
