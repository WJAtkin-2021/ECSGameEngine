#include "ShaderData.fx"

//--------------------------------------------------------------------------------------
TextureCube txSkyTexture : register(t0);
SamplerState txSkySampler : register(s0);

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 pos : SV_POSITION;
	float4 norm : NORMAL;
	float3 uv : TEXCOORD;
	float3 tangent : TANGENT;
};
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 viewDir: TEXCOORD0;
};
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_TARGET
{
	return txSkyTexture.Sample(txSkySampler, input.viewDir);
}