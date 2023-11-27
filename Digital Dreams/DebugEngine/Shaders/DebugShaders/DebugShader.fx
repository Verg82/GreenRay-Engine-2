//////////////////////////////////////////////////////////////////////////////////////////////////
// File: ShadowVolumeGroup.fx
// Author: Chris Smith
// Date Created: 2/26/06
// Description: Contains shaders to render shadow volumes and objects having SV cast onto them
// Disclaimer: Use this however you want, but I am not responsible for anything
//////////////////////////////////////////////////////////////////////////////////////////////////

float4x4 WorldViewProjection;    // World * View * Projection matrix
float4x4 WorldView;              // World * View
float4x4 Proj;                   // Projection matrix
float4   ShadowColor;            // Shadow volume color (for visualization)
float4   LightView;              // Position of light in view space
float    FarClip;                // Z of far clip plane


//-----------------------------------------------------------------------------
// Global constants
//-----------------------------------------------------------------------------
static const int NUM_LIGHTS = 3;     // Scene lights 

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

// Transformation matrices
float4x4 g_mObjectToView;   // Object space to view space
float4x4 g_mProjection;     // View space to clip space

bool g_bEnableTexture;   // Toggle texture modulation for current pixel

// Light variables
float4 g_avLightPositionView[NUM_LIGHTS];   // Light positions in view space
float4 g_avLightIntensity[NUM_LIGHTS];      // Floating point light intensities

float  g_fPhongExponent;        // Exponents for the phong equation
float  g_fPhongCoefficient;     // Coefficient for the phong equation
float  g_fDiffuseCoefficient;   // Coefficient for diffuse equation
float4 g_vEmissive;             // Emissive intensity of the current light






//-----------------------------------------------------------------------------
// Texture samplers
//-----------------------------------------------------------------------------
sampler s0 : register(s0);
sampler s1 : register(s1);
sampler s2 : register(s2);
sampler s3 : register(s3);
sampler s4 : register(s4);
sampler s5 : register(s5);
sampler s6 : register(s6);
sampler s7 : register(s7);


//////////////////////////////////////////////////////////////
//Structures
//////////////////////////////////////////////////////////////
struct ShadowVolumeA2V
{ 
     float4 Position : POSITION;
     float3 Normal : NORMAL;
};

struct ShadowVolumeV2P
{
     float4 Position : POSITION;
};







//-----------------------------------------------------------------------------
// Name: TransformScene     
// Type: Vertex shader                                      
// Desc: Transforms the incoming vertex from object to clip space, and passes
//       the vertex position and normal in view space on to the pixel shader
//-----------------------------------------------------------------------------
struct TransformSceneOutput
{
    float4 Position : POSITION;
    float2 Texture0 : TEXCOORD0;
    float3 Texture1 : TEXCOORD1;
    float3 Texture2 : TEXCOORD2;
};

TransformSceneOutput TransformScene
    (
    float3 vObjectPosition : POSITION, 
    float3 vObjectNormal : NORMAL,
    float2 vObjectTexture : TEXCOORD0
    )
{
    TransformSceneOutput Output;
    float4 vViewPosition;
    float3 vViewNormal;
  
    // tranform the position/normal into view space
    vViewPosition = mul(float4(vObjectPosition, 1.0f), g_mObjectToView);
    vViewNormal = normalize(mul(vObjectNormal, (float3x3)g_mObjectToView));

    // project view space to screen space
    Output.Position = mul(vViewPosition, g_mProjection);
    
    // Pass the texture coordinate without modification
    Output.Texture0 = vObjectTexture;

    // Pass view position into a texture iterator
    Output.Texture1 = vViewPosition.xyz;
    
    // Pass view surface normal into a texture iterator
    Output.Texture2 = vViewNormal;
    
    return Output;
}



//-----------------------------------------------------------------------------
// Pixel shaders
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Name: PointLight                                        
// Type: Pixel shader
// Desc: Per-pixel diffuse, specular, and emissive lighting
//-----------------------------------------------------------------------------
float4 PointLight
    (
    in float2 vTexture : TEXCOORD0,
    in float3 vViewPosition : TEXCOORD1,
    in float3 vNormal : TEXCOORD2
    ) : COLOR
{
    float3 vPointToCamera = normalize(-vViewPosition);

    // Start with ambient term
    float3 vIntensity = float3(0.28f, 0.25f, 0.2f);

    // Add emissive term to the total intensity
    vIntensity+= g_vEmissive; 
        
    for(int iLight = 0; iLight < NUM_LIGHTS; iLight++)
    {
        // Calculate illumination variables
        float3 vLightToPoint = normalize(vViewPosition - g_avLightPositionView[iLight]);
        float3 vReflection   = reflect(vLightToPoint, vNormal);
        float  fPhongValue   = saturate(dot(vReflection, vPointToCamera));

        // Calculate diffuse term
        float  fDiffuse      = g_fDiffuseCoefficient * saturate(dot(vNormal, -vLightToPoint));

        // Calculate specular term
        float  fSpecular     = g_fPhongCoefficient * pow(fPhongValue, g_fPhongExponent);
        
        // Scale according to distance from the light
        float fDistance = distance(g_avLightPositionView[iLight], vViewPosition);
        vIntensity += (fDiffuse + fSpecular) * g_avLightIntensity[iLight]/(fDistance*fDistance);
    }
    
    // Multiply by texture color
    if( g_bEnableTexture )
        vIntensity *= tex2D(s0, vTexture);

    return float4(vIntensity, 1.0f);
}










//////////////////////////////////////////////////////////////
//Vertex Shaders
//////////////////////////////////////////////////////////////


void ShadowVolumeVS( in ShadowVolumeA2V IN, out ShadowVolumeV2P OUT )
{
    //Compute view space normal
    IN.Normal = mul( IN.Normal, (float3x3)WorldView );

    //Obtain view space position
    float4 PosView = mul( IN.Position, WorldView );

    //Light-to-vertex vector in view space
    float3 LightVecView = PosView - LightView;

    //Extrude the vertex away from light if it's facing away from the light.
    if( dot( IN.Normal, -LightVecView ) < 0.0f )
    {
        if( PosView.z > LightView.z )
            PosView.xyz += LightVecView * ( FarClip - PosView.z ) / LightVecView.z;
        else
            PosView = float4( LightVecView, 0.0f );

        //Transform the position from view space to homogeneous projection space
        OUT.Position = mul( PosView, Proj );
    } else
        OUT.Position = mul( IN.Position, WorldViewProjection );
}

//////////////////////////////////////////////////////////////
//Pixel Shaders
//////////////////////////////////////////////////////////////

float4 ShadowVolumePS() : COLOR0
{
    return float4(ShadowColor.xyz, 0.1f);
}

//////////////////////////////////////////////////////////////
//Techniques
//////////////////////////////////////////////////////////////

technique Ambient
{
    pass P0
    {
        VertexShader = NULL;
        PixelShader  = NULL;
        StencilEnable = false;
        ZFunc = LessEqual;
    }
}

technique PointLight
{
//pass P0
//{  
  

      //  VertexShader = compile vs_2_0 TransformScene();
     //   PixelShader  = compile ps_2_0 PointLight();  
 //StencilEnable = true;
 //       ZFunc = Less;
//}

pass P0
{


                     ZEnable = true;
        ZFunc = LessEqual;
        StencilEnable = true;
        AlphaBlendEnable = true;
        BlendOp = Add;
        SrcBlend = One;
        DestBlend = One;
        StencilRef = 1;
        StencilFunc = Greater;
        StencilPass = Keep;

        //VertexShader = NULL;
        //PixelShader  = NULL;
//compile vs_1_1 PointLightVS();
//compile ps_2_0 PointLightPS();
}
   
}

technique ShadowVolume2Sided
{
    pass P0
    {
        VertexShader = compile vs_1_1 ShadowVolumeVS();
        PixelShader  = compile ps_1_1 ShadowVolumePS();
        CullMode = None;
        
        // Disable writing to the frame buffer
        AlphaBlendEnable = true;
        SrcBlend = Zero;
        DestBlend = One;
        
        // Disable writing to depth buffer
        ZWriteEnable = false;
        ZFunc = Less;
        
        // Setup stencil states
        TwoSidedStencilMode = true;
        StencilEnable = true;
        StencilRef = 1;
        StencilMask = 0xFFFFFFFF;
        StencilWriteMask = 0xFFFFFFFF;
        Ccw_StencilFunc = Always;
        Ccw_StencilZFail = Incr;
        Ccw_StencilPass = Keep;
        StencilFunc = Always;
        StencilZFail = Decr;
        StencilPass = Keep;
    }

}

technique ShadowVolume
{

    pass P0
    {
        VertexShader = compile vs_2_0 ShadowVolumeVS();
        PixelShader  = compile ps_2_0 ShadowVolumePS();
        CullMode = Ccw;
        
        // Disable writing to the frame buffer
        AlphaBlendEnable = true;
        SrcBlend = Zero;
        DestBlend = One;
        
        // Disable writing to depth buffer
        ZWriteEnable = false;
        ZFunc = Less;
        
        // Setup stencil states
        StencilEnable = true;
        StencilRef = 1;
        StencilMask = 0xFFFFFFFF;
        StencilWriteMask = 0xFFFFFFFF;
        StencilFunc = Always;
        StencilZFail = Decr;
        StencilPass = Keep;
    }
    pass P1
    {
        VertexShader = compile vs_2_0 ShadowVolumeVS();
        PixelShader  = compile ps_2_0 ShadowVolumePS();
        CullMode = Cw;
        StencilZFail = Incr;

    }

}

