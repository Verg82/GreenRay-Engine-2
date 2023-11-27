// Uniform parameters. 
float4x4 worldViewProj  : WorldViewProjection; 
float4x4 worldView      : WorldView; 

float3 lightPos; 
float1 Intens; 

texture decal; 
texture bump; 

// This sampler struct is used to specifiy texture options. 
sampler DecalSampler = sampler_state 
{ 
    Texture  = (decal); 
    MipFilter = LINEAR; 
    MinFilter = LINEAR; 
    MagFilter = LINEAR; 
}; 

sampler BumpSampler = sampler_state 
{ 
    Texture  = (bump); 
    MipFilter = LINEAR; 
    MinFilter = LINEAR; 
    MagFilter = LINEAR; 
}; 


// Vertex shader input. 
struct VS_Input 
{ 
  float3 vertexPos  : POSITION; 
  float3 normal    : NORMAL; 
  float2 texture0  : TEXCOORD0; 
  float3 sTangent  : TANGENT; 
  float3 binormal  : BINORMAL; 
}; 


// Vertex shader output. 
struct Vs_Output 
{ 
  float4 vertexPos  : POSITION; 
  float2 texture0  : TEXCOORD0; 
  float3 lightDirection : TEXCOORD1; 
}; 


// Pixel shader output. 
struct Ps_Output 
{ 
  float4 color      : COLOR; 
}; 


// The vertex shader... 
Vs_Output VertexShaderEffect(VS_Input IN) 
{ 
  Vs_Output vs_out; 

  // Set output vertex pos, and texture coords. 
  vs_out.vertexPos = mul(worldViewProj, float4(IN.vertexPos, 1)); 
  vs_out.texture0 = IN.texture0; 

  // Set the object space light direction. 
  //формируем матрицу трансформации вектора источника света 
  float3x3 tbnMatrix = {IN.sTangent.x, IN.binormal.x, IN.normal.x, 
                  IN.sTangent.y, IN.binormal.y, IN.normal.y, 
            IN.sTangent.z, IN.binormal.z, IN.normal.z}; 

  // Convert light direction to texture space. 
  float3 LightVector = normalize(lightPos - IN.vertexPos); 
  vs_out.lightDirection = normalize(mul(LightVector,tbnMatrix)); 

  return vs_out; 
} 


// The pixel shader... 
Ps_Output PixelShaderEffect(Vs_Output IN) 
{ 
  Ps_Output ps_out; 

  float4 decalCol = tex2D(DecalSampler, IN.texture0); 
  float3 bumpCol = 2.0f*( tex2D(BumpSampler, IN.texture0) - 0.5f ); 

  float lightDirection = dot(bumpCol, IN.lightDirection); 
  lightDirection = max(0.0f, lightDirection); 

  decalCol.rgb *= lightDirection * Intens;  // Умножением или делением на X (decalCol.rgb *= lightDirection(*/)X) можно менять интенсивность света 

  ps_out.color = decalCol; 

  return ps_out; 
} 


// Effect... 
technique BumpMapping 
{ 
  pass Pass0 
  { 
      // Here we will compile and set the vertex and pixel shader. 
      VertexShader = compile vs_2_0 VertexShaderEffect(); 
      PixelShader  = compile ps_2_0 PixelShaderEffect(); 
  } 
} 
