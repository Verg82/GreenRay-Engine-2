//
// Lighting in HLSL
//

// The world view and projection matrices
float4x4 WorldViewProj : WORLDVIEWPROJECTION;
float4x4 WorldMatrix : WORLD;
float4 DiffuseDirection;
float4 EyeLocation;

// Color constants
const float4 MetallicColor = { 0.8f, 0.8f, 0.8f, 1.0f };
const float4 AmbientColor = { 0.05f, 0.05f, 0.05f, 1.0f };

///////////////////////////
///////////////////////////
// These effects are per vertex
///////////////////////////
///////////////////////////
struct VS_OUTPUT_PER_VERTEX
{
    float4 Position : POSITION;
    float4 Color : COLOR0;
};

// Transform our coordinates into world space
VS_OUTPUT_PER_VERTEX TransformDiffuse(
    float4 inputPosition : POSITION,
    float3 inputNormal : NORMAL,
    uniform bool metallic
    )
{
    //Declare our output structure
    VS_OUTPUT_PER_VERTEX Out = (VS_OUTPUT_PER_VERTEX)0;

    // Transform our position
    Out.Position = mul(inputPosition, WorldViewProj);

    // Transform the normals into the world matrix and normalize them
    float3 Normal = normalize(mul(inputNormal, WorldMatrix));
    
    // Make our diffuse color metallic for now
    float4 diffuseColor = MetallicColor;

    if(!metallic)
        diffuseColor.rgb = sin(Normal + inputPosition);
    
    // Store our diffuse component
    float4 diffuse = saturate(dot(DiffuseDirection, Normal));
    
    // Return the combined color 
    Out.Color = AmbientColor + diffuseColor * diffuse;

    return Out;
}

VS_OUTPUT_PER_VERTEX TransformSpecular(
    float4 inputPosition : POSITION,
    float3 inputNormal : NORMAL,
    uniform bool metallic
    )
{
    //Declare our output structure
    VS_OUTPUT_PER_VERTEX Out = (VS_OUTPUT_PER_VERTEX)0;
    // Transform our position
    Out.Position = mul(inputPosition, WorldViewProj);

    // Transform the normals into the world matrix and normalize them
    float3 Normal = normalize(mul(inputNormal, WorldMatrix));
    
    // Make our diffuse color metallic for now
    float4 diffuseColor = MetallicColor;
    
    // Normalize the world position of the vertex
    float3 worldPosition = normalize(mul(inputPosition, WorldMatrix));
    
    // Store the eye vector
    float3 eye = EyeLocation - worldPosition;

    // Normalize our vectors
    float3 normal = normalize(Normal);
    float3 light = normalize(DiffuseDirection);
    float3 eyeDirection = normalize(eye);
    
    if(!metallic)
        diffuseColor.rgb = cos(normal + eye);
    
    // Store our diffuse component
    float4 diffuse = saturate(dot(light, normal));
    
    // Calculate specular component
    float3 reflection = normalize(2 * diffuse * normal - light);
    float4 specular = pow(saturate(dot(reflection, eyeDirection)), 8);
        
    // Return the combined color 
    Out.Color = AmbientColor + diffuseColor * diffuse + specular;
    
    return Out;
}

technique TransformSpecularPerVertexMetallic
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 TransformSpecular(true);
        PixelShader  = NULL;
    }
}

technique TransformSpecularPerVertexColorful
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 TransformSpecular(false);
        PixelShader  = NULL;
    }
}

technique TransformDiffusePerVertexMetallic
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 TransformDiffuse(true);
        PixelShader  = NULL;
    }
}
technique TransformDiffusePerVertexColorful
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 TransformDiffuse(false);
        PixelShader  = NULL;
    }
}

///////////////////////////
///////////////////////////
// These effects are per pixel
///////////////////////////
///////////////////////////

struct VS_OUTPUT_PER_VERTEX_PER_PIXEL
{
    float4 Position : POSITION;
    float3 LightDirection : TEXCOORD0;
    float3 Normal : TEXCOORD1;
    float3 EyeWorld : TEXCOORD2;
};

// Transform our coordinates into world space
VS_OUTPUT_PER_VERTEX_PER_PIXEL Transform(
    float4 inputPosition : POSITION,
    float3 inputNormal : NORMAL
    )
{
    //Declare our output structure
    VS_OUTPUT_PER_VERTEX_PER_PIXEL Out = (VS_OUTPUT_PER_VERTEX_PER_PIXEL)0;
    // Transform our position
    Out.Position = mul(inputPosition, WorldViewProj);
    // Store our light direction
    Out.LightDirection = DiffuseDirection;
    // Transform the normals into the world matrix and normalize them
    Out.Normal = normalize(mul(inputNormal, WorldMatrix));
    // Normalize the world position of the vertex
    float3 worldPosition = normalize(mul(inputPosition, WorldMatrix));
    // Store the eye vector
    Out.EyeWorld = EyeLocation - worldPosition;
    
    return Out;
}

float4 ColorSpecular(
 float3 lightDirection : TEXCOORD0,
 float3 normal : TEXCOORD1,
 float3 eye : TEXCOORD2,
 uniform bool metallic) : COLOR0
{
    // Make our diffuse color metallic for now
    float4 diffuseColor = MetallicColor;
    
    if(!metallic)
        diffuseColor.rgb = cos(normal + eye);
    
    // Normalize our vectors
    float3 normalized = normalize(normal);
    float3 light = normalize(lightDirection);
    float3 eyeDirection = normalize(eye);
    // Store our diffuse component
    float4 diffuse = saturate(dot(light, normalized));
    
    // Calculate specular component
    float3 reflection = normalize(2 * diffuse * normalized - light);
    float4 specular = pow(saturate(dot(reflection, eyeDirection)), 8);
        
    // Return the combined color 
    return AmbientColor + diffuseColor * diffuse + specular;
};

float4 ColorDiffuse(
 float3 lightDirection : TEXCOORD0,
 float3 normal : TEXCOORD1,
 float3 eye : TEXCOORD2,
 uniform bool metallic) : COLOR0
{
    // Make our diffuse color metallic for now
    float4 diffuseColor = MetallicColor;
    
    if(!metallic)
        diffuseColor.rgb = sin(normal + eye);
    
    // Store our diffuse component
    float4 diffuse = saturate(dot(lightDirection, normal));
    
    // Return the combined color 
    return AmbientColor + diffuseColor * diffuse;
};

technique TransformSpecularPerPixelMetallic
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 Transform();
        PixelShader  = compile ps_2_0 ColorSpecular(true);
    }
}
technique TransformSpecularPerPixelColorful
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 Transform();
        PixelShader  = compile ps_2_0 ColorSpecular(false);
    }
}
technique TransformDiffusePerPixelMetallic
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 Transform();
        PixelShader  = compile ps_1_1 ColorDiffuse(true);
    }
}
technique TransformDiffusePerPixelColorful
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 Transform();
        PixelShader  = compile ps_2_0 ColorDiffuse(false);
    }
}
