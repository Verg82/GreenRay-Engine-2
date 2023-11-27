/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.2
// GRShadow.cpp
// It's The GreenRay ShadowVolume Engine Source File.
// Made Specially For Implementing Shadow Effects With Using Stencil Buffer.
// Date Creation: 29 August 2005
// Last Changing: 11 February 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <GRShadow.h>
#include <GRLight.h>
#include <GRMesh.h>
#include <GRGeometry.h>
#include <GRMethods.h>
#include <GRModels.h>
#include <GRCamera.h>

CShadowVolume* gr_ShadowVolume = NULL; //Base GreenRay ShadowVolume Interface
CGRMesh* gr_MeshA = NULL; //Use Simple GreenRay Mesh
D3DXMATRIXA16 gr_ObjectMatrix; //Matrix For Translate Needed Mesh
 
///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction For CGRShadowVolume Class
///////////////////////////////////////////////////////////////////////////////
CShadowVolume::CShadowVolume()
{
  m_pBigSquareVB = NULL;
} //EndConstructionDirectives

CShadowVolume::~CShadowVolume()
{ 
} //EndDestructionDirectives

//-----------------------------------------------------------------------------
// Name: CGRShadowVolume::ReleaseShadow()
// Desc: CGRShadowVolume Destructor
//-----------------------------------------------------------------------------
void CShadowVolume::ReleaseShadow()
{
  ReleaseClass(m_pBigSquareVB); //Release ShadowSquare
} //EndReleaseShadowProcedure

//-----------------------------------------------------------------------------
// Name: CGRShadowVolume::AddEdge()
// Desc: Adds An Edge To A List Of Silohuette Edges Of A Shadow Volume.
//-----------------------------------------------------------------------------
void CShadowVolume::AddEdge(WORD* pEdges,DWORD& dwNumEdges,WORD v0,WORD v1)
{
  //Remove Interior Edges (Which Appear In The List Twice)
  for (DWORD i = 0; i<dwNumEdges; i++)
  {
    if ((pEdges[2*i+0] == v0 && pEdges[2*i+1] == v1)||(pEdges[2*i+0] == v1 && pEdges[2*i+1] == v0))
    {
      if (dwNumEdges > 1)
      {
        pEdges[2*i+0] = pEdges[2*(dwNumEdges-1)+0];
        pEdges[2*i+1] = pEdges[2*(dwNumEdges-1)+1];
      }
      dwNumEdges--;
      return;
    } //End First If
  } //End For

  pEdges[2*dwNumEdges+0] = v0;
  pEdges[2*dwNumEdges+1] = v1;
  dwNumEdges++;
} //EndAddEdgeProcedure

//-----------------------------------------------------------------------------
// Name: CShadowVolume::BuildShadowSquare()
// Desc: Create A Big Square For Rendering The StencilBuffer Contents
//-----------------------------------------------------------------------------
HRESULT CShadowVolume::BuildShadowSquare(LPDIRECT3DDEVICE9 pDevice,float sx,float sy,int _Color)
{
  HRESULT _Result;
  //Build Square Vertex Parameters
  if (FAILED(_Result = pDevice->CreateVertexBuffer(4*sizeof(SHADOWVERTEX),
  D3DUSAGE_WRITEONLY,SHADOWVERTEX_FVF,D3DPOOL_MANAGED,&m_pBigSquareVB,NULL))) return _Result;

  //Set The Size Of The Big Square Shadow
  SHADOWVERTEX* _Vert;
  m_pBigSquareVB->Lock(0,0,(void**)&_Vert,0);

  //Setting Up Shadow Dispose
  _Vert[0]._Pos = D3DXVECTOR4(0,  sy, 0.0f, 1.0f);
  _Vert[1]._Pos = D3DXVECTOR4(0,   0, 0.0f, 1.0f);
  _Vert[2]._Pos = D3DXVECTOR4(sx, sy, 0.0f, 1.0f);
  _Vert[3]._Pos = D3DXVECTOR4(sx,  0, 0.0f, 1.0f);
  
  //Setting Up Shadow Color
  _Vert[0]._Color = _Color;
  _Vert[1]._Color = _Color;
  _Vert[2]._Color = _Color;
  _Vert[3]._Color = _Color;
  
  m_pBigSquareVB->Unlock();

  return _Result;
} //EndBuildShadowSquareFunction

//-----------------------------------------------------------------------------
// Name: CShadowVolume::BuildFromMesh()
// Desc: Takes A Mesh As Input, And Uses It To Build A ShadowVolume. The
//       Technique Used Considers Each Triangle Of The Mesh, And Adds It's
//       Edges To A Temporary List. The Edge List Is Maintained, Such That
//       Only Silohuette Edges Are Kept. Finally, The Silohuette Edges Are
//       Extruded To Make The Shadow Volume Vertex List.
//-----------------------------------------------------------------------------
HRESULT CShadowVolume::BuildFromMesh(LPD3DXMESH pMesh,D3DXVECTOR3 vLight)
{
  //Note: The MESHVERTEX Format Depends On The FVF Of The Mesh
  struct MESHVERTEX 
  { 
    D3DXVECTOR3 p,n; 
    FLOAT tu,tv; 
  };

  MESHVERTEX* pVertices;
  WORD* pIndices;

  //Lock The Geometry Buffers
  pMesh->LockVertexBuffer(0L,(LPVOID*)&pVertices);
  pMesh->LockIndexBuffer(0L,(LPVOID*)&pIndices);
  DWORD dwNumFaces = pMesh->GetNumFaces();

  //Allocate A Temporary Edge List
  WORD* pEdges = new WORD[dwNumFaces*6];
  if (pEdges == NULL)
  {
    pMesh->UnlockVertexBuffer();
    pMesh->UnlockIndexBuffer();
    return E_OUTOFMEMORY;
  }
  DWORD dwNumEdges = 0;

  //For Each Face
  for (DWORD i = 0; i<dwNumFaces; i++)
  {
    WORD wFace0 = pIndices[3*i+0];
    WORD wFace1 = pIndices[3*i+1];
    WORD wFace2 = pIndices[3*i+2];

    D3DXVECTOR3 v0 = pVertices[wFace0].p;
    D3DXVECTOR3 v1 = pVertices[wFace1].p;
    D3DXVECTOR3 v2 = pVertices[wFace2].p;

    //Transform Vertices Or Transform Light?
    D3DXVECTOR3 vCross1(v2-v1);
    D3DXVECTOR3 vCross2(v1-v0);
    D3DXVECTOR3 vNormal;
    D3DXVec3Cross(&vNormal,&vCross1,&vCross2);

    if (D3DXVec3Dot(&vNormal,&vLight) >= 0.0f)
    {
      AddEdge(pEdges, dwNumEdges, wFace0, wFace1);
      AddEdge(pEdges, dwNumEdges, wFace1, wFace2);
      AddEdge(pEdges, dwNumEdges, wFace2, wFace0);
    }
  }

  for (DWORD i = 0; i<dwNumEdges; i++)
  {
    D3DXVECTOR3 v1 = pVertices[pEdges[2*i+0]].p;
    D3DXVECTOR3 v2 = pVertices[pEdges[2*i+1]].p;
    D3DXVECTOR3 v3 = v1-vLight*10;
    D3DXVECTOR3 v4 = v2-vLight*10;

    //Add A Quad (Two Triangles) To The Vertex List
    m_pVertices[m_dwNumVertices++] = v1;
    m_pVertices[m_dwNumVertices++] = v2;
    m_pVertices[m_dwNumVertices++] = v3;

    m_pVertices[m_dwNumVertices++] = v2;
    m_pVertices[m_dwNumVertices++] = v4;
    m_pVertices[m_dwNumVertices++] = v3;
  }
  
  //Delete The Temporary Edge List
  delete []pEdges;

  //Unlock The Geometry Buffers
  pMesh->UnlockVertexBuffer();
  pMesh->UnlockIndexBuffer();

  return S_OK;
} //EndBuildFromMeshFunction

//-----------------------------------------------------------------------------
// Name: CShadowVolume::Render()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CShadowVolume::Render(LPDIRECT3DDEVICE9 pDevice)
{
  pDevice->SetFVF(D3DFVF_XYZ);
  return pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,m_dwNumVertices/3,m_pVertices,sizeof(D3DXVECTOR3));
} //EndRenderFunction

//-----------------------------------------------------------------------------
// Name: CShadowVolume::RenderShadow()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CShadowVolume::RenderShadow(LPDIRECT3DDEVICE9 pDevice,D3DXMATRIXA16* _TransMatrix)
{
  //Disable Z-Buffer Writes (Note: Z-Testing Still Occurs), And Enable The Stencil-Buffer
  pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
  pDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);

  //Don't Hother With Interpolating Color
  pDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_FLAT);

  //Set Up Stencil Compare Fuction, Reference Value, And Masks.
  //Stencil Test Passes If ((Ref & Mask) Cmpfn (Stencil & Mask)) Is True.
  //Note: Since We Set Up The Stencil-Test To Always Pass, The STENCILFAIL
  //Renderstate Is Really Not Needed.
  pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);
  pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_KEEP);
  pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_KEEP);

  //If ZTest Passes, Inc/Decrement Stencil Buffer Value
  pDevice->SetRenderState(D3DRS_STENCILREF,0x1);
  pDevice->SetRenderState(D3DRS_STENCILMASK,0xffffffff);
  pDevice->SetRenderState(D3DRS_STENCILWRITEMASK,0xffffffff);
  pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_INCR);

  //Make Sure That No Pixels Get Drawn To The Frame Buffer
  pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
  pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ZERO);
  pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

  /*if (( m_d3dCaps.StencilCaps & D3DSTENCILCAPS_TWOSIDED) != 0)
  {
    //With 2-Sided Stencil, We Can void Rendering Twice:
    pDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE,TRUE);
    pDevice->SetRenderState(D3DRS_CCW_STENCILFUNC,D3DCMP_ALWAYS);
    pDevice->SetRenderState(D3DRS_CCW_STENCILZFAIL,D3DSTENCILOP_KEEP);
    pDevice->SetRenderState(D3DRS_CCW_STENCILFAIL,D3DSTENCILOP_KEEP);
    pDevice->SetRenderState(D3DRS_CCW_STENCILPASS,D3DSTENCILOP_DECR);
    pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

    //Draw Both Sides Of Shadow Volume In Stencil/Z Only
    pDevice->SetTransform(D3DTS_WORLD,_TransMatrix);
    Render(pDevice);

    pDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE,FALSE);
  }*/
    
  //Draw Front-Side Of Shadow Volume In Stencil/Z Only
  pDevice->SetTransform(D3DTS_WORLD,_TransMatrix);
  Render(pDevice);

  //Now Reverse Cull Order So Back Sides Of Shadow Volume Are Written.
  pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);

  //Decrement Stencil Buffer Value
  pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_DECR);

  //Draw Back-Side Of Shadow Volume in Stencil/Z Only
  pDevice->SetTransform(D3DTS_WORLD,_TransMatrix);
  Render(pDevice);

  //Restore Render States
  pDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
  pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
  pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
  pDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);
  pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

  return S_OK;
} //EndRenderShadowFunction

//-----------------------------------------------------------------------------
// Name: CShadowVolume::DrawShadow()
// Desc: Draws A Big Gray Polygon Over Scene According To The Mask In The
//       Stencil Buffer. (Any Pixel With Stencil==1 Is In The Shadow)
//-----------------------------------------------------------------------------
HRESULT CShadowVolume::DrawShadow(LPDIRECT3DDEVICE9 pDevice)
{
  //Set Renderstates(Disable Z-Buffering, Enable Stencil, Disable Fog, And Turn On AlphaBlending)
  pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
  pDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
  pDevice->SetRenderState(D3DRS_FOGENABLE,FALSE);
  pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
  pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
  pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

  pDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
  pDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);
  pDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
  pDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
  pDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
  pDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);

  //Only Write Where Stencil Val >= 1 (Count Indicates # Of Shadows ThatOverlap That Pixel)
  pDevice->SetRenderState(D3DRS_STENCILREF,0x1);
  pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_LESSEQUAL);
  pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_KEEP);

  //Draw A Big, Gray Square
  pDevice->SetFVF(SHADOWVERTEX_FVF);
  pDevice->SetStreamSource(0,m_pBigSquareVB,0,sizeof(SHADOWVERTEX));
  pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

  //Restore Render States
  pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
  pDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);
  //pDevice->SetRenderState(D3DRS_FOGENABLE,TRUE);
  pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

  return S_OK;
} //EndDrawShadowFunction

//-----------------------------------------------------------------------------
// Name: CShadowVolume::ReleaseShadowObjects()
// Desc: 
//-----------------------------------------------------------------------------
void CShadowVolume::ReleaseShadowObjects()
{
  //Release ShadowVolume
  if (gr_ShadowVolume != NULL)
  {
	ReleaseShadow();
	DeleteClass(gr_ShadowVolume);
  }

  //Release Mesh
  if (gr_MeshA != NULL) 
  {
    //gr_Mesh->Destroy();
	//DeleteClass(gr_Mesh);
	gr_MeshA = NULL;
  }  
} //EndReleaseShadowObjectsProcedure

//-----------------------------------------------------------------------------
// Name: CreateShadow()
// Desc: 
//-----------------------------------------------------------------------------
void CreateShadow()
{
  gr_MeshA = new CGRMesh(); //Construct A Mesh 
  //gr_MeshA = new CGRModels(); //Construct A Model
  gr_ShadowVolume = new CShadowVolume(); //Construct A Shadow Volume Object
   
  //Load An Object To Cast The Shadow
  if (FAILED(gr_MeshA->Create(gr_Direct3DDevice,_T("\Models\\Pipes\\Pipe_01.x")))) 
  {
    ShowErrorMessage("<Lua>gr_Mesh Load Error..");
    return;
  }

  //gr_MeshA->CreateModelFromX(TEXT("\Models\\Pipes\\Pipe_01.x"));



  //Set A Reasonable Vertex Type
  gr_MeshA->SetFVF(gr_Direct3DDevice,VERTEX_FVF);

  //Initialize The Vertex Buffers For The File-Based Objects
  gr_MeshA->RestoreDeviceObjects(gr_Direct3DDevice);

  //Build Shadow Square
  gr_ShadowVolume->BuildShadowSquare(gr_Direct3DDevice,
  (float)/*gr_BackBufferWidth*/790,(float)/*gr_BackBufferHeight*/690,0x7F000000);





} //EndCreateShadowProcedure

//-----------------------------------------------------------------------------
// Name: DrawShadow()
// Desc: 
//-----------------------------------------------------------------------------
void DrawShadow()
{
  //Setting Rendering Parameters
  gr_Direct3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
  //gr_Direct3DDevice->SetRenderState(D3DRS_DITHERENABLE,TRUE);
  gr_Direct3DDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);
  
  //Setup Viewing Postion
  //For Moving Object
  D3DXMatrixTranslation(&gr_ObjectMatrix,13.75f,-0.4f,2.0f); //Translation Matrix For Custom Mesh
  

  //gr_MeshA->RotationModel(-1.5f, 0.0f, 0.0f);
  //gr_MeshA->ScaleModel(0.0090f, 0.0090f, 0.0090f);
  //gr_MeshA->DispositionModel(0.0f, 2.5f, 4.0f);
  
  D3DXMATRIXA16 _ScaleMatrix;
  D3DXMATRIXA16 _RollMatrix;
  D3DXMATRIXA16 _WrldMatrix;

  D3DXMatrixRotationYawPitchRoll(&_RollMatrix,0.0f,0.0f,0.0f);
  D3DXMatrixScaling(&_ScaleMatrix,0.010f,0.010f,0.010f);
  D3DXMatrixTranslation(&_MatrixWorld,0.0f,2.5f,4.0f);
  _WrldMatrix = _ScaleMatrix*_RollMatrix*_MatrixWorld;
  D3DXMATRIXA16 _ObjectToView = _WrldMatrix*_MatrixView;
 gr_Direct3DDevice->SetTransform(D3DTS_WORLD,&_ObjectToView);  

  //For Rotation Object
  //D3DXMatrixRotationYawPitchRoll(&gr_ObjectMatrix,gr_MeshPosX,gr_MeshPosY,0.0f);
  
  //Move The Light
  float Lx =  5.0f;
  float Ly =  5.0f;
  float Lz = -5.0f;

  //D3DLIGHT9 _Light;
  //SetLightPreferences(_Light,D3DLIGHT_POINT,Lx,Ly,Lz);
  //_Light.Attenuation0 = 0.9f;
  //_Light.Attenuation1 = 0.0f;
  //gr_Direct3DDevice->SetLight(0,&_Light);

  //Transform The Light Vector To Be In Object Space
  D3DXVECTOR3 vLight;
  D3DXMATRIXA16 m;
  D3DXMatrixInverse(&m,NULL,&_ObjectToView);
  vLight.x = Lx*m._11+Ly*m._21+Lz*m._31+m._41;
  vLight.y = Lx*m._12+Ly*m._22+Lz*m._32+m._42;
  vLight.z = Lx*m._13+Ly*m._23+Lz*m._33+m._43;

  //Build The Shadow Volume
  gr_ShadowVolume->Reset();
  gr_ShadowVolume->BuildFromMesh(gr_MeshA->GetSysMemMesh(),vLight);

  //Rendering Mesh
 
  //gr_Direct3DDevice->SetTransform(D3DTS_WORLD,&gr_MeshA->_ObjectToView); //Transform Object Position In Space
  //gr_MeshA->Render(gr_Direct3DDevice);
  
  //Render The Shadow Volume Into The Stenicl Buffer, Then Add It Into The Scene
  gr_ShadowVolume->RenderShadow(gr_Direct3DDevice,&gr_ObjectMatrix);

  //Finally Draw Some Shadow
  gr_ShadowVolume->DrawShadow(gr_Direct3DDevice);
} //EndDrawShadowProcedur





