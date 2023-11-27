//////////////////////////////////////////////////////////////////////////////////////////////////
// File: NormalMapPointLight.fx
// Author: Chris Smith
// Date Created: 2/25/06
// Description: Renders a scene with normal mapping from a point light
// Disclaimer: Use this however you want, but I am not responsible for anything
//////////////////////////////////////////////////////////////////////////////////////////////////

float4x4 WorldViewProj; //World * View * Projection Matrix
float4x4 World;         //World matrix of object
float4 LightPos;        //Light position in world space
float4 LightColor;      //Color of the light
texture ColorMap;       //Color texture
texture NormalMap;      //Normal map texture
float Falloff;          // Distance until light begins to falloff
float Ambient;          // Ambient amount of lighting

sampler colorSampler = sampler_state
{
     Texture = (ColorMap);
    MIPFILTER = LINEAR;
    MAGFILTER = LINEAR;
    MINFILTER = LINEAR;
};
sampler normalSampler = sampler_state
{
    Texture = (NormalMap);
   MIPFILTER = LINEAR;
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};

//////////////////////////////////////////////////////////////
//Structures
//////////////////////////////////////////////////////////////

//Application to vertex shader
struct A2V
{ 
     float4 Position : POSITION;
     float3 Normal : NORMAL;
     float2 TexCoord0 : TEXCOORD0;
     float3 Tangent : TANGENT;
     float3 Binormal : BINORMAL;
};

//Vertex shader to pixel shader
struct V2P
{
     float4 Position : POSITION;
     float2 TexCoord0 : TEXCOORD0;
     float3 LightDir : TEXCOORD1;
};

//////////////////////////////////////////////////////////////
//Vertex Shader
//////////////////////////////////////////////////////////////
void VS( in A2V IN, out V2P OUT ) 
{
    //Transform the position from view space to homogeneous projection space
    OUT.Position = mul(IN.Position, WorldViewProj);

    //Compute world space position
    float4 WorldPos = mul(IN.Position, World);
    
    //Calculate Binormal and set Tangent Binormal and Normal matrix
    float3x3 TBNMatrix = float3x3(IN.Binormal, IN.Tangent , IN.Normal); 

    //Compute light direction
    OUT.LightDir = LightPos - WorldPos;

    //Compute light direction * TBN Matrix
    OUT.LightDir = mul(TBNMatrix, OUT.LightDir);
 
    //Copy the texture coordinate as is
    OUT.TexCoord0 = IN.TexCoord0;
}

//////////////////////////////////////////////////////////////
//Pixel Shader
//////////////////////////////////////////////////////////////
float4 PS( in V2P IN ) : COLOR0
{
    //calculate the color and the normal
    float4 Color = tex2D(colorSampler, IN.TexCoord0);

    //Uncompress the normal map
    float3 Normal = 2.0f * tex2D(normalSampler, IN.TexCoord0).rgb - 1.0f;

    //Pixel to light vector
    float LenSq = dot( IN.LightDir, IN.LightDir );
    IN.LightDir = normalize( IN.LightDir );
        
    //Compute the light's attenuation
    float Attn = min(( Falloff * Falloff ) / LenSq, 1.0f);

    //Compute the diffuse lighting amount
    float Diffuse = Attn * saturate(dot(Normal, IN.LightDir));

    //Lighting amount * Texture Color * Light Color
    return Color =  (Diffuse + Ambient)  * Color * LightColor;
}

//////////////////////////////////////////////////////////////
//Technique
//////////////////////////////////////////////////////////////
technique NormalMapPointLight
{
    pass p0
    {
        vertexshader = compile vs_1_1 VS();
        pixelshader = compile ps_2_0 PS();
    }
}