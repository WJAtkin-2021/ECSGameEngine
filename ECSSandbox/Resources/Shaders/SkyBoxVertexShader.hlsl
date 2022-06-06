#include "ShaderData.fx"

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
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float4 inPos = input.pos;
	output.viewDir = inPos.xyz;

	inPos.xyz += CameraPosition.xyz;
	inPos = mul(inPos, View);
	inPos = mul(inPos, Projection);
	output.pos = inPos;

	return output;
}