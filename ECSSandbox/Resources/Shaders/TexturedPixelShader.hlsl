Texture2D txTexture : register(t0);
SamplerState txTextureSampler : register(s0);

static float4 MaterialDiff = float4(0.9, 0.7, 1.0, 1.0);
static float4 LightColor = float4(245.0 / 255.0, 243.0 / 255.0, 184.0 / 255.0, 1.0);
static float3 LightPos = float3(0.0, 1000.0, 0.0);
static float LightFactor = 0.25f;

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
	// 64 Bytes
	matrix World;
	// 64 Bytes
	matrix View;
	// 64 Bytes
	matrix Projection;
	// 16 Bytes
	float4 Color;
	// 16 Bytes
	float4 CameraPosition;
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 posW : TEXCOORD0;
	float2 tex : TEXCOORD1;
	float3 tangentW : TANGENT;
	float3 norm : TEXCOORD2;
};

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_TARGET
{
	float4 textureColor = float4(txTexture.Sample(txTextureSampler, input.tex).xyz, 1.0f);

	float3 lightDir = normalize(LightPos - input.posW.xyz);
	float3 normal = normalize(input.norm);
	float diff = max(0.0, dot(lightDir, normal));

	float4 lightResult = (diff * MaterialDiff) * (LightColor * LightFactor);

	lightResult += textureColor;
	lightResult = saturate(lightResult);

	return lightResult;
}