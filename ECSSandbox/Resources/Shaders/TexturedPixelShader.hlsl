Texture2D txTexture : register(t0);
TextureCube txEnviromentMap : register(t2);
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
	// 16 Bytes
	float SpecularPower;
	float Metallic;
	bool ShowEnviromentMap;
	bool padding1;
	bool padding2;
	bool padding3;
	float padding4;
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
	float4 finalColor = float4(txTexture.Sample(txTextureSampler, input.tex).xyz, 1.0f);
	float3 normal = normalize(input.norm);

	if (ShowEnviromentMap)
	{
		// Sample the environment map
		float3 V = normalize(CameraPosition.xyz - input.posW);
		float3 viewDir = reflect(-V, normal);
		float4 enviroment = txEnviromentMap.Sample(txTextureSampler, viewDir);

		// Apply the metallic properties to the reflection of the environment
		enviroment = enviroment * Metallic;
		finalColor += enviroment;
	}

	float3 lightDir = normalize(LightPos - input.posW.xyz);
	float diff = max(0.0, dot(lightDir, normal));

	float4 lightResult = (diff * MaterialDiff) * (LightColor * LightFactor);

	finalColor += lightResult;
	finalColor = saturate(finalColor);

	return finalColor;
}