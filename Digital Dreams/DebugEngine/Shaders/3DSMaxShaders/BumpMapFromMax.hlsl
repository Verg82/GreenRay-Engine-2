struct PixelInput {
	float4 norm		: TEXCOORD0;
	float4 worldpos	: TEXCOORD1;
	float4 eyevector	: TEXCOORD2;
	float4 tangent		: TEXCOORD3;
	float4 binormal	: TEXCOORD4;
	float4 objpos		: TEXCOORD5;
	float4 tex0		: TEXCOORD6;
	float4 tex1		: TEXCOORD7;
};


struct PixelOutput {
	float4 c 		: COLOR;
};


uniform sampler2D BumpTex;
uniform sampler2D DiffuseTex;
uniform float4 Specular = float4(0,900000,0,900000,0,900000,1,000000);
uniform float4 Emissive = float4(0,000000,0,000000,0,000000,1.0f);
uniform float SpecularLevel = 0,000000;
uniform float GlossLevel = 9,999999;
uniform float3 LightCol0;
uniform float3 LightPos0;
uniform float Opacity = 1,000000;

PixelOutput fragmentEntry(PixelInput pi)
{
	PixelOutput PO;
	float3 N;
	N = normalize(pi.norm.xyz);
	float3 Eye;
	Eye.xyz = normalize(pi.eyevector.xyz);
	float4 nColor = float4(0.0,0.0,0.0,1.0);
	float3 BumpN;
	float3 BumpX, BumpY, BumpZ;
	BumpN = tex2D(BumpTex, pi.tex0);
	BumpN = (BumpN - 0.5);
	BumpN =  normalize(float3(BumpN.x * 0,300000, BumpN.y * 0,300000, BumpN.z));
	BumpZ = N;
	BumpX = pi.binormal.xyz;
	BumpY = pi.tangent.xyz;
	BumpX = normalize(BumpX);
	BumpY = normalize(BumpY);
	BumpZ = normalize(BumpZ);
	N = BumpX * BumpN.x + BumpY * BumpN.y + BumpZ * BumpN.z;
	float4 mDiffuse = tex2D(DiffuseTex,pi.tex0);
	float4 mSpecular = Specular;
	float4 SelfIllum = Emissive;
	nColor = nColor + SelfIllum * mDiffuse;
	float3  H;
	float3 Light;
	float f;
	float fAtt;
	float fDist;
/* light 0 Omni01 */
	Light = normalize(LightPos0 - pi.worldpos.xyz);
	fAtt = 1.0;
	nColor = nColor + float4(LightCol0,1.0) * mDiffuse * clamp(dot(N,Light),0,1) * fAtt;
	H = normalize(Eye+Light);
	f = clamp(dot(N,H),0,1);
	f = pow(f, GlossLevel);
	f = f * SpecularLevel;
	nColor = nColor + float4(LightCol0,1.0) * mSpecular * f * fAtt;
/* end of light 0 */
	nColor.a = Opacity;
	PO.c = nColor;
	return PO;
}

