
#include <PhongLighting.h>
#include <GRTest.h>
#include <GRMethods.h>
#include <GRGeometry.h>
#include <GRWorld.h>
#include <GRCamera.h>
#include <ShadowVolumeCreator.h>
#include <GRModels.h>

#define NUM_LIGHTSA 3 //Number Of Lights In The Scene

//-----------------------------------------------------------------------------
// Global Shader Initialization Variables
//-----------------------------------------------------------------------------
IDirect3DTexture9* LightTexture;
ID3DXEffect* ProjTextureEffect;

CGRPrimitive* Kaska = NULL;
IDirect3DTexture9* Pedik;

//For Shadow Volume Effects Directives
ID3DXEffect* ShadowVolumeEffect;
ID3DXMesh* ChairShadowMesh;

//For Notmal Map Directives
IDirect3DTexture9* RoomTexture;
IDirect3DTexture9* NormalTexture;
ID3DXEffect* PointLightEffect;
CGRModels* Sazan = NULL;
CGRModels* Room = NULL;
LPD3DXMESH Sraka;
LPD3DXMESH RoomA;



//Shader Light Methods
D3DXVECTOR4 g_avLightPositionA[NUM_LIGHTSA]; //Light Positions In World Space
D3DXVECTOR4 g_avLightIntensityA[NUM_LIGHTSA]; //Light Floating Point Intensities
int g_nLightLogIntensityA[NUM_LIGHTSA]; //Light Intensities On A Log Scale
int g_nLightMantissaA[NUM_LIGHTSA]; //Mantissa Of The Light Intensity


//dgh ad  
#define SHADOW_MAP_SIZE	512
IDirect3DTexture9* GrassTexture;
IDirect3DTexture9* SpotlightTexture;
ID3DXEffect* ShadowMapEffect;

LPDIRECT3DSURFACE9 BackBuffer = NULL, ZBuffer = NULL;
LPDIRECT3DSURFACE9 SMColorSurface = NULL, SMZSurface = NULL;
LPDIRECT3DTEXTURE9 SMColorTexture = NULL, SMZTexture = NULL;
D3DXMATRIX View;
D3DXMATRIX Proj;
D3DXMATRIX LightView;
D3DXMATRIX LightProj;

//-----------------------------------------------------------------------------
// Name: RefreshLights()
// Desc: Set The Light Intensities To Match The Current Log Luminance
//-----------------------------------------------------------------------------
void RefreshLightsA()
{
  for (int i = 0; i < NUM_LIGHTSA; i++)
  {
    g_avLightIntensityA[i].x = g_nLightMantissaA[i]*(float)pow(1.0f,g_nLightLogIntensityA[i]);
    g_avLightIntensityA[i].y = g_nLightMantissaA[i]*(float)pow(1.0f,g_nLightLogIntensityA[i]);
    g_avLightIntensityA[i].z = g_nLightMantissaA[i]*(float)pow(1.0f,g_nLightLogIntensityA[i]);
    g_avLightIntensityA[i].w = 1.0f;          
  }
}

void SetupShader()
{
  //Load The Texture Into LightTexture
  /*D3DXCreateTextureFromFile(gr_Direct3DDevice,
  TEXT("\Textures\\Lightmaps\\FlashLight.bmp"),&LightTexture);

  //Load The HLSL Shader
  D3DXCreateEffectFromFile(gr_Direct3DDevice,
  TEXT("\Shaders\\FlashLight.fx"),NULL,NULL,NULL,NULL,&ProjTextureEffect,NULL);

   //Load The Texture Into LightTexture
  D3DXCreateTextureFromFile(gr_Direct3DDevice,
  TEXT("\Textures\\Cellar\\Wall_01.bmp"),&Pedik);

  Kaska = new CGRPrimitive(3,3,0xffffff); //Construct A Mesh Class
  Kaska->CreateVertexBuffer();*/


  //
  Sazan = new CGRModels(); //Construct A Vitia's Picture Model
  Sazan->CreateModelFromX(TEXT("Box.x"));

 


  //For Shadow Volume Directives Uncomplete Yet
  LPD3DXMESH Sraka = Sazan->GetLocalMeshGeometry();

    //For Shadow Volume Directives Uncomplete Yet
  //LPD3DXMESH RoomA = Room->GetLocalMeshGeometry();


  //Create The Chair Shadow Mesh
  GenerateShadowMesh(gr_Direct3DDevice,Sraka,&ChairShadowMesh);

  //Load The Color Texture Into RoomTexture
  D3DXCreateTextureFromFile(gr_Direct3DDevice,TEXT("StoneWall.bmp"),&RoomTexture);

  //Load The HLSL Shader
  D3DXCreateEffectFromFile(gr_Direct3DDevice, 
  TEXT("\Shaders\\DebugShaders\\DebugShader.fx"),NULL,NULL,NULL,NULL,&ShadowVolumeEffect,NULL);



	//Set the View matrix
	D3DXVECTOR3 Position(0.0f, 20.0f, -25.0f);
	D3DXVECTOR3 Target(0.0f, 0.0f, 5.0f);
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&View, &Position, &Target, &Up);

	//Set the Projection matrix
	D3DXMatrixPerspectiveFovLH( &Proj, D3DX_PI /4, 1.0f, 1.0f, 1000.0f );


  //Set Light Positions In World Space And Light Intensity
  g_avLightPositionA[0] = D3DXVECTOR4(1.0f, 2.5f, 4.0f, 1.0f);
  g_nLightMantissaA[0] = 6.5f;
  g_nLightLogIntensityA[0] = 6.5f;

  #if NUM_LIGHTSA > 1
  g_avLightPositionA[1] = D3DXVECTOR4(1.0f, 2.5f, 16.0f, 1.0f);
  g_nLightMantissaA[1] = 6.5f;
  g_nLightLogIntensityA[1] = 6.5f;
  #endif
 
  #if NUM_LIGHTSA > 2
  g_avLightPositionA[2] = D3DXVECTOR4(14.0f, 2.5f, 10.0f, 1.0f);
  g_nLightMantissaA[2] = 6.5f;
  g_nLightLogIntensityA[2] = 6.5f;
  #endif

  #if NUM_LIGHTSA > 3
  g_avLightPositionA[3] = D3DXVECTOR4(14.0f, 2.5f, 16.0f, 1.0f);
  g_nLightMantissaA[3] = 6.5f;
  g_nLightLogIntensityA[3] = 6.5f;
  #endif

 RefreshLightsA();

/*
  //For Normal Mapping Uncomlete Yet
  Sazan = new CGRModels(); //Construct A Vitia's Picture Model
  Sazan->CreateModelFromX(TEXT("Box.x"));

  //Sazan->RotationModel(-1.5f, 0.0f, 0.0f);
  //Sazan->ScaleModel(0.0090f, 0.0090f, 0.0090f);
  //Sazan->DispositionModel(0.0f, 2.5f, 4.0f);
  //gr_Direct3DDevice->SetTransform(D3DTS_WORLD,&Sazan->_ObjectToView); //Transform Object Position In Space


/*
  Sraka = Sazan->GetLocalMeshGeometry();

  D3DVERTEXELEMENT9 Elements[] =
  {
    {0, sizeof(float)*0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0, sizeof(float)*3,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
	{0, sizeof(float)*6,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	{0, sizeof(float)*8,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
	{0, sizeof(float)*11, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
	D3DDECL_END()
  };

  //Compute The Tangent Frame For The Mesh (Needed For Normal Mapping)
  ID3DXMesh* Temp;
  Sraka->CloneMesh(D3DXMESH_MANAGED,Elements,gr_Direct3DDevice,&Temp);
  //Sraka->Release(); ???
  Sraka = Temp;
  
  void* Data;
  Sraka->LockVertexBuffer(D3DLOCK_DISCARD,&Data);
  Sraka->UnlockVertexBuffer();
  D3DXComputeTangentFrame(Sraka,0);

  //Load The Color Texture Into RoomTexture
  D3DXCreateTextureFromFile(gr_Direct3DDevice,TEXT("StoneWall.bmp"),&RoomTexture);

  //Load The Normal Map Texture Into NormalTexture
  D3DXCreateTextureFromFile(gr_Direct3DDevice,TEXT("StoneDot3.bmp"),&NormalTexture);

  //Load The HLSL Shader
  D3DXCreateEffectFromFile(gr_Direct3DDevice,
  TEXT("\Shaders\\NormalMapPointLight.fx"),NULL,NULL,NULL,NULL,&PointLightEffect,NULL);*/


/*

  //
  Sazan = new CGRModels(); //Construct A Vitia's Picture Model
  Sazan->CreateModelFromX(TEXT("Box.x"));

    //
  Room = new CGRModels(); //Construct A Vitia's Picture Model
  Room->CreateModelFromX(TEXT("Plane.x"));
 
  //For Shadow Volume Directives Uncomplete Yet
  Sraka = Sazan->GetLocalMeshGeometry();

  D3DXCreateTextureFromFile(gr_Direct3DDevice,TEXT("Grass.bmp"),&GrassTexture );
  D3DXCreateTextureFromFile(gr_Direct3DDevice,TEXT("Satan.tga"),&SpotlightTexture);

 //Get render target and zbuffer surface
  gr_Direct3DDevice->GetRenderTarget(0,&BackBuffer);
  gr_Direct3DDevice->GetDepthStencilSurface(&ZBuffer);

  //Create the shadow map textures
  gr_Direct3DDevice->CreateTexture(SHADOW_MAP_SIZE,SHADOW_MAP_SIZE,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT, &SMColorTexture, NULL);
  gr_Direct3DDevice->CreateTexture(SHADOW_MAP_SIZE,SHADOW_MAP_SIZE,1,D3DUSAGE_DEPTHSTENCIL,D3DFMT_D24S8,D3DPOOL_DEFAULT, &SMZTexture, NULL);

  //Get the surface levels for the shadow map textures
  SMColorTexture->GetSurfaceLevel(0,&SMColorSurface);
  SMZTexture->GetSurfaceLevel(0,&SMZSurface);
	
  //Load the HLSL shader
  D3DXCreateEffectFromFile(gr_Direct3DDevice,TEXT("\Shaders\\HLSLShadowMap.fx"), 
  NULL,NULL,NULL,NULL,&ShadowMapEffect,NULL);

	//Set the View matrix
	D3DXVECTOR3 Position(0.0f, 20.0f, -25.0f);
	D3DXVECTOR3 Target(0.0f, 0.0f, 5.0f);
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&View, &Position, &Target, &Up);

	//Set the Projection matrix
	D3DXMatrixPerspectiveFovLH( &Proj, D3DX_PI /4, 1.0f, 1.0f, 1000.0f );

	//Set the Light's View matrix
	D3DXVECTOR3 LightPosition(8.0f, 12.0f, 0.0f);
	D3DXVECTOR3 LightTarget(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&LightView, &LightPosition, &LightTarget, &Up);

	//Set the Light's Projection matrix
	D3DXMatrixPerspectiveFovLH(&LightProj, D3DX_PI/4, 1.0f, 1.0f, 500.0f);
*/





} //EndSetupShaderProcedure









///////////////////////////////////////////////////////
// Render Shadow Map
///////////////////////////////////////////////////////
void RenderShadowMap( void )
{

	Sraka = Sazan->GetLocalMeshGeometry();
   
	RoomA = Room->GetLocalMeshGeometry();

	//Set render target to shadow map surfaces
    gr_Direct3DDevice->SetRenderTarget(0, SMColorSurface);

    //Set depth stencil
    gr_Direct3DDevice->SetDepthStencilSurface(SMZSurface);

    //Save old viewport
    D3DVIEWPORT9 OldViewport;
    gr_Direct3DDevice->GetViewport(&OldViewport);

	//Set new projected texture viewport
    D3DVIEWPORT9 NewViewport;
    NewViewport.X = 0;
    NewViewport.Y = 0;
    NewViewport.Width  = SHADOW_MAP_SIZE;
    NewViewport.Height = SHADOW_MAP_SIZE;
    NewViewport.MinZ = 0.0f;
    NewViewport.MaxZ = 1.0f;
    gr_Direct3DDevice->SetViewport(&NewViewport);

	//Set the depth bias information
	float DepthBias = 0.0002f;
	float BiasSlope = 2.0f;
	gr_Direct3DDevice->SetRenderState(D3DRS_DEPTHBIAS, *(DWORD*)&DepthBias);
    gr_Direct3DDevice->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, *(DWORD*)&BiasSlope);

	//Clear the target and zbuffer
	gr_Direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00FFFFFF, 1.0f, 0L);

	//Set the technique to create a shadow map texture
	ShadowMapEffect->SetTechnique("CreateShadowMap");

	//Set the world matrix
	D3DXMATRIX World;
	D3DXMatrixIdentity(&World);

	//Set dynamic shader variables
	ShadowMapEffect->SetMatrix( "WorldViewProj", &(World * LightView * LightProj) );
	ShadowMapEffect->SetMatrix( "TexTransform", &(World) );
	ShadowMapEffect->CommitChanges();

	//We only want to render objects that cast shadows here
	UINT Pass, Passes;
	ShadowMapEffect->Begin(&Passes, 0);
	for (Pass = 0; Pass < Passes; Pass++)
	{
		ShadowMapEffect->BeginPass(Pass);

		//Render the chair
	for (int Koks = 0; Koks < 21; Koks++) Sraka->DrawSubset(Koks);

		ShadowMapEffect->EndPass();
	}
	ShadowMapEffect->End();

	//Set the old viewport
	gr_Direct3DDevice->SetViewport(&OldViewport);

    //Set depth bias
    float Zero = 0.0f;
    gr_Direct3DDevice->SetRenderState(D3DRS_DEPTHBIAS, *(DWORD*)&Zero);
    gr_Direct3DDevice->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, *(DWORD*)&Zero);
}

///////////////////////////////////////////////////////
// Render scene with shadow map applied
///////////////////////////////////////////////////////
void RenderScene( void )
{


    //Set render target and depth surface back to normal
    gr_Direct3DDevice->SetRenderTarget(0, BackBuffer);
    gr_Direct3DDevice->SetDepthStencilSurface(ZBuffer);

    //Set depth map as texture
    ShadowMapEffect->SetTexture("ShadowMap", SMZTexture);
    
    //Set the spotlight and color texture
    ShadowMapEffect->SetTexture("LightTex", SpotlightTexture);
	ShadowMapEffect->SetTexture("ColorTex", GrassTexture);

	 //Set special texture matrix for shadow mapping
    float OffsetX = 0.5f + (0.5f / (float)SHADOW_MAP_SIZE);
    float OffsetY = 0.5f + (0.5f / (float)SHADOW_MAP_SIZE);

    //float fBias    = -0.001f * (float)range;
	unsigned int Range = 1;
    float Bias = 0.0f;

	//Set the matrix values
    D3DXMATRIX TexScaleBiasMat( 0.5f,     0.0f,     0.0f,         0.0f,
                                0.0f,    -0.5f,     0.0f,         0.0f,
                                0.0f,     0.0f,     (float)Range, 0.0f,
                                OffsetX, OffsetY,   Bias,         1.0f );
    
	//Create a world matrix
    D3DXMATRIX World;
    D3DXMatrixIdentity(&World);

	//Set the shader dynamic values
	ShadowMapEffect->SetMatrix( "WorldViewProj", &(World * View * Proj) );
	ShadowMapEffect->SetMatrix( "TexTransform", &(World * LightView * LightProj * TexScaleBiasMat) );
	//Set technique to render scene with shadow map applied
	ShadowMapEffect->SetTechnique( "MainShadowMap" );
	ShadowMapEffect->CommitChanges();

	UINT Pass, Passes;
	ShadowMapEffect->Begin(&Passes, 0);
	for (Pass = 0; Pass < Passes; Pass++)
	{
		ShadowMapEffect->BeginPass(Pass);

		//Render the chair
		for (int Koks = 0; Koks < 21; Koks++) Sraka->DrawSubset(Koks);
        
		RoomA->DrawSubset(0);
		 RenderPhongLightShader();
		//Render The
		

		ShadowMapEffect->EndPass();
	}
	ShadowMapEffect->End();
}




void RenderShader()
{	
  //Set Some Render States To Determine Texture Quality
  /*gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
  gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
  gr_Direct3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);

  //Set The Texture Adjustment Matrix Offsets
  float XOffset = 0.5f+(0.5f/(float)256); //Width Of The Light Texture
  float YOffset = 0.5f+(0.5f/(float)256); //Height Of The Light Texture

  //Create The Texture Adjustment Matrix
  D3DXMATRIX TexMatrix;
  ZeroMemory(&TexMatrix,sizeof(D3DXMATRIX));
  TexMatrix._11 = 0.5f;
  TexMatrix._22 = -0.5f;
  TexMatrix._33 = 0.5f;
  TexMatrix._41 = XOffset;
  TexMatrix._42 = YOffset;
  TexMatrix._43 = 0.5f;
  TexMatrix._44 = 1.0f;	

  //Create The Projection Matrix For The Light
  D3DXMATRIX LightProj;
  D3DXMatrixPerspectiveFovLH(&LightProj,D3DX_PI/4,1.0f,0.0f,500.0f);

  //Set Dynamic Shader Variables
  ProjTextureEffect->SetTechnique("ProjectiveTexture");

  //_MatrixWorld,_MatrixView,_MatrixProjection;
 
  ProjTextureEffect->SetMatrix("WorldViewProj",&(_MatrixWorld*_MatrixView*_MatrixProjection));
  ProjTextureEffect->SetMatrix("World",&(_MatrixWorld));
  ProjTextureEffect->SetMatrix("TexTransform",&(_MatrixWorld*_MatrixView*LightProj*TexMatrix));
  ProjTextureEffect->SetValue("EyePos",&(_MatrixView),sizeof(D3DXVECTOR3));

  
  
  ProjTextureEffect->SetTexture("ColorTex",Pedik);

  ProjTextureEffect->SetTexture("LightTex",LightTexture);
  ProjTextureEffect->SetFloat("LightFalloff",35.0f);

  //Begin The Shader Pass
  UINT Pass,Passes;
 
  ProjTextureEffect->Begin(&Passes, 0);
  for (Pass = 0; Pass < Passes; Pass++)
  {
    ProjTextureEffect->BeginPass(Pass);
    //Render the Room
	//RoomMesh->DrawSubset(0);
   
    //gr_Direct3DDevice->SetTexture(0,Pedik);
    ProjTextureEffect->CommitChanges();


	RenderRoomBox(0);
	//Kaska->RenderPrimitive();

    //RenderLightShaderConstant(); //Render Light Shader Tech

	ProjTextureEffect->EndPass(); 
  }
  ProjTextureEffect->End();*/


  //_MatrixWorld,_MatrixView,_MatrixProjection;
 
/*
  //Set Dynamic Shader Variables
  PointLightEffect->SetTechnique("NormalMapPointLight");

  PointLightEffect->SetMatrix("WorldViewProj",&(_MatrixWorld*_MatrixView*_MatrixProjection));
  PointLightEffect->SetMatrix("World",&(_MatrixWorld));
  PointLightEffect->SetVector("LightPos",&(D3DXVECTOR4(-10.0f,20.0f,5.0f,0.0f)));
  PointLightEffect->SetVector("LightColor",&(D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f)));
  PointLightEffect->SetTexture("ColorMap",RoomTexture);
  PointLightEffect->SetTexture("NormalMap",NormalTexture);
  PointLightEffect->SetFloat("Falloff",25.0f);
  PointLightEffect->SetFloat("Ambient",0.0f);



m = (tr1 * rot) * tr2; // m - матрица композиции преобразований

gr_Direct3DDevice->SetTransform(D3DTS_WORLD,&m);


		UINT Time = GetTickCount()%4000;
   D3DXMATRIXA16 MatrixWorld; //World Matrix
  //World Matrix
  float Angle = Time*(2.0f*D3DX_PI)/4000.0f;
  D3DXMatrixRotationY(&MatrixWorld,Angle);
  gr_Direct3DDevice->SetTransform(D3DTS_WORLD,&MatrixWorld);

  //Begin The Shader Pass
	UINT Pass, Passes;
	PointLightEffect->Begin(&Passes, 0);
	for (Pass = 0; Pass < Passes; Pass++)
	{
		PointLightEffect->BeginPass(Pass);

		//Render the Room
        RenderLightShaderConstant();

		Sraka->DrawSubset(0);

		PointLightEffect->EndPass();
	}
	PointLightEffect->End();*/

 //_MatrixWorld,_MatrixView,_MatrixProjection;
	
   //Set the world matrix
	D3DXMATRIX World;
	D3DXMatrixIdentity(&World);

	//Set Dynamic Shader Variables
	ShadowVolumeEffect->SetMatrix("WorldViewProjection",&(_MatrixWorld*_MatrixView*_MatrixProjection));
	ShadowVolumeEffect->SetMatrix("WorldView",&(_MatrixWorld*_MatrixView));
	ShadowVolumeEffect->SetMatrix("Proj",&(_MatrixProjection));
	
	//	ShadowVolumeEffect->SetMatrix( "WorldViewProjection", &(World * View * Proj) );
	//ShadowVolumeEffect->SetMatrix( "WorldView", &(World * View) );
//	ShadowVolumeEffect->SetMatrix( "Proj", &(Proj) );
	ShadowVolumeEffect->SetVector("ShadowColor",&(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 0.5f)));
	ShadowVolumeEffect->SetFloat("FarClip",100.0f);








/*
//For every new light we want, we must clear the stencil buffer, then
	//render the shadow mesh for the objects we want to cast a shadow.
	//And finally, we render the scene with a point light.
		for(int LightNum = 0; LightNum<NumOfLights; LightNum++)
	            {
		//First order of business is to clear the stencil buffer
		
gr_Direct3DDevice->Clear(0,NULL,D3DCLEAR_STENCIL,D3DCOLOR_ARGB(0,0,0,0),1.0f,0);
        //Transform the light position into view space and send it to the shader
		D3DXVec4Transform( &LightPositions[LightNum], &LightPositions[LightNum],&_MatrixView);
		ShadowVolumeEffect->SetVector( "LightView", &(LightPositions[LightNum]));
	
		}*/
	
		//ShadowVolumeEffect->SetVector( "LightView", &LightPositions[0]/*,sizeof(D3DXVECTOR4)*2*/); 
        //ShadowVolumeEffect->SetVector( "LightView", &LightPositions[1]/*,sizeof(D3DXVECTOR4)*2*/);















	//Create Some Light Positions
	D3DXVECTOR4 LightPositions[2];
	LightPositions[0] = D3DXVECTOR4(5.0f, 2.0f, -5.0f, 1.0f);
	LightPositions[1] = D3DXVECTOR4(10.0f, 10.0f, -5.0f, 1.0f);

	//Set the number of lights
	int NumOfLights = 2;

//For every new light we want, we must clear the stencil buffer, then
	//render the shadow mesh for the objects we want to cast a shadow.
	//And finally, we render the scene with a point light.
		for(int LightNum = 0; LightNum<NumOfLights; LightNum++)
	            {
		//First order of business is to clear the stencil buffer
					
		gr_Direct3DDevice->Clear(0,NULL,D3DCLEAR_STENCIL,D3DCOLOR_ARGB(0,0,0,0),1.0f,0);

        //Transform the light position into view space and send it to the shader
		D3DXVec4Transform( &LightPositions[LightNum], &LightPositions[LightNum],&_MatrixView);
		ShadowVolumeEffect->SetVector( "LightView", &(LightPositions[LightNum]));





		//Set the technique to render shadow volumes
		ShadowVolumeEffect->SetTechnique( "ShadowVolume" );
		

		//During this pass we render meshes we want to cast shadows.
		//It is important that we only render meshes that were created
		//with the GenerateShadowMesh() function in this pass.
		UINT zPass, zPasses;
		ShadowVolumeEffect->Begin(&zPasses, 0);
		for(zPass = 0; zPass < zPasses; ++zPass)
		{
			ShadowVolumeEffect->BeginPass(zPass);
		
	


              ShadowVolumeEffect->CommitChanges();
			//Render the chair's shadow
			ChairShadowMesh->DrawSubset(0);
			  		
		
		ShadowVolumeEffect->EndPass();
		}
		
		ShadowVolumeEffect->End();





	
  //Set the point light technique
  ShadowVolumeEffect->SetTechnique("PointLight");

		//Finally, render the scene with a point light
		UINT iPass, iPasses;
		ShadowVolumeEffect->Begin(&iPasses, 0);
		for(iPass = 0; iPass < iPasses; ++iPass)
		{
			ShadowVolumeEffect->BeginPass(iPass);

ShadowVolumeEffect->CommitChanges();
 RenderPhongLightShader();

	
    
		//gr_Direct3DDevice->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_STENCIL,D3DCOLOR_ARGB(0,0,0,0),1.0f,0);			
	
		ShadowVolumeEffect->EndPass();
		}
     ShadowVolumeEffect->End();	
	





 










}





  /*
	ShadowVolumeEffect->CommitChanges();
	ShadowVolumeEffect->SetTechnique( "Ambient" );

	//In the first pass, we want to render the scene with simple ambient lighting.
	UINT Pass, Passes;
	ShadowVolumeEffect->Begin(&Passes, 0);
	for (Pass = 0; Pass < Passes; Pass++)
	{
		ShadowVolumeEffect->BeginPass(Pass);

  RenderLightShaderConstant(); 

		ShadowVolumeEffect->EndPass();
	}
	ShadowVolumeEffect->End();*/


	
	
	 
 
}




///////////////////////////////////////////////////////
// Cleanup
///////////////////////////////////////////////////////
/*void Cleanup( void )
{
		//Release the LightTexture object
	LightTexture->Release();

	//Release the PointLight effect
	ProjTextureEffect->Release();
}*/