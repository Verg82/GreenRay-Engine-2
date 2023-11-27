//-----------------------------------------------------------------------------
// Name: PixScene
// Type: Pixel shader
// Desc: This shader outputs the pixel's color by modulating the texture's
//		 color with diffuse material color
//-----------------------------------------------------------------------------
float4 PixScene( float4 MatDiffuse : COLOR0,
                 float2 Tex0 : TEXCOORD0,
                 float3 ViewPos : TEXCOORD1,
                 float3 ViewNormal : TEXCOORD2 ) : COLOR0
{
    // Compute half vector for specular lighting
    float3 vHalf = normalize( normalize( -ViewPos ) + normalize( g_vLight - ViewPos ) );

    // Compute normal dot half for specular light
    float4 fSpecular = pow( saturate( dot( vHalf, normalize( ViewNormal ) ) ) * Specular, Power );

    return float4( (float3)( g_vLightColor * ( tex2D( g_samScene, Tex0 ) * MatDiffuse + fSpecular ) ), 1.0f );
}