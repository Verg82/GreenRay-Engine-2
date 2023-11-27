//////////////////////////////////////////////////////////////////////////////////////////////////
// File: HLSLShadowMap.fx
// Author: Chris Smith
// Date Created: 2/26/06
// Description: Renders a scene with shadow mapping
// Disclaimer: Use this however you want, but I am not responsible for anything
//////////////////////////////////////////////////////////////////////////////////////////////////

float4x4 WorldViewProj; //World * View * Projection
float4x4 TexTransform;  //Texture transformation matrix
float Ambient = 0.3f;   //Amount of ambient light

texture ShadowMap;
texture LightTex;
texture ColorTex;

//Must be clamped so the shadow shows up only once
sampler ShadowMapSampler = sampler_state
{
    Texture = <ShadowMap>;
    MinFilter = LINEAR;  
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU  = Clamp;
    AddressV  = Clamp;
};

//Must be clamped so the light texture shows up only once
sampler LightTexSampler = sampler_state
{
    Texture = <LightTex>;
    MinFilter = LINEAR;  
    MagFilter = LINEAR;
    MipFilter = LINEAR;
    AddressU  = Clamp;
    AddressV  = Clamp;
};

sampler ColorTexSampler = sampler_state
{
    Texture = <ColorTex>;
    MinFilter = LINEAR;  
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};

////////////////////////////////////////////////////////////
// Structures
////////////////////////////////////////////////////////////
struct MainA2V{
    float4 Position : POSITION;
    float2 TexCoord0 : TEXCOORD0;
};

struct MainV2P{
    float4 Position  : POSITION;
    float4 TexCoord0 : TEXCOORD0;
    float4 TexCoord1 : TEXCOORD1;
    float2 TexCoord2 : TEXCOORD2;
};

struct CreateShadowMapA2V{
    float4 Position : POSITION;
};

struct CreateShadowMapV2P{
    float4 Position  : POSITION;
    float4 TexCoord0 : TEXCOORD0;
};

////////////////////////////////////////////////////////////
// Vertex Shaders
////////////////////////////////////////////////////////////
void MainVS(in MainA2V IN, out MainV2P OUT)
{
    //First two are the projected texture coordinates
    OUT.TexCoord0 = mul(IN.Position, TexTransform);
    OUT.TexCoord1 = OUT.TexCoord0;
    
    //Copy color texture coordinates through
    OUT.TexCoord2 = IN.TexCoord0;
    
    //Transform model-space vertex position to screen space:
    OUT.Position = mul(IN.Position, WorldViewProj);
}

void CreateShadowMapVS(in CreateShadowMapA2V IN, out CreateShadowMapV2P OUT)
{
    //Transform position into screen space
    OUT.Position = mul(IN.Position, WorldViewProj);
    
    //Transform texture coordiante into projected texture space
    OUT.TexCoord0 = float4(OUT.Position.zzz, OUT.Position.w);
}

////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////
float4 MainPS(in MainV2P IN) : COLOR 
{
    //Read in values for shadow, light texture and color texture
    float4 Shadow   = tex2D(ShadowMapSampler, IN.TexCoord0);
    float4 Light    = tex2D(LightTexSampler, IN.TexCoord1);
    float4 Color    = tex2D(ColorTexSampler, IN.TexCoord2);
    
    //Compute lighting amount
    float4 I = (Light * Shadow) + Ambient;
    
    //Color of texture * lighting amount
    return Color * I;
}

////////////////////////////////////////////////////////////
// Techniques
////////////////////////////////////////////////////////////
technique MainShadowMap
{
    pass P0
    {
        VertexShader = compile vs_1_1 MainVS();
        PixelShader = compile ps_1_1 MainPS();
        
        ZEnable          = True;
        AlphaBlendEnable = False;
        Lighting         = False;
        CullMode         = CCW;
    
        TexCoordIndex[0] = 0;
        TexCoordIndex[1] = 1;
        TextureTransformFlags[0] = Projected;
        TextureTransformFlags[1] = Projected;
    }
}

technique CreateShadowMap
{
    pass P0
    {
        VertexShader = compile vs_1_1 CreateShadowMapVS();

        ZEnable          = True;
        AlphaBlendEnable = False;
        Lighting         = False;
        CullMode         = CCW;  // note: not quite optimal
        
        ColorWriteEnable = 0;     // no need to render to color, we only need z
    }
}

