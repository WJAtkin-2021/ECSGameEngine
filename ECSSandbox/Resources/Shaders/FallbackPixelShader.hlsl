#include "ShaderLighting.fx"

//--------------------------------------------------------------------------------------
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
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_TARGET
{
	float4 finalColor = EntityColor;

	LightingCalcResult light = CalculateLighting(input.posW, normalize(input.normalWorld), CameraPosition);

	float4 specular = light.Specular * 0.5f;

	finalColor = (light.Diffuse + specular + AmbientLight) * EntityColor;

	return finalColor;
}