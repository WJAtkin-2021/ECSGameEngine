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
	float4 posW : TEXCOORD0;
	float2 tex : TEXCOORD1;
	float3 tangentW : TANGENT;
	float3 norm : TEXCOORD2;
	float3 normalWorld : TEXCOORD3;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

    output.pos = mul(input.pos, World);
	output.posW = output.pos;
    output.pos = mul(output.pos, View);
    output.pos = mul(output.pos, Projection);

	output.tex = input.uv.xy;

	output.tangentW = mul(input.tangent, (float3x3)World).xyz;
	output.tangentW = normalize(output.tangentW);

	output.norm = input.norm.xyz;

	output.normalWorld = mul(input.norm, InverseWorld).xyz;

	return output;
}