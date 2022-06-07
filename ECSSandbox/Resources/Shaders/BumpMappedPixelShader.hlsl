#include "ShaderLighting.fx"

Texture2D txDiffTexture : register(t0);
Texture2D txNormMap : register(t1);
TextureCube txEnviromentMap : register(t2);
SamplerState txTextureSampler : register(s0);

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
	// Sample the diffuse texture
	float4 finalColor = float4(txDiffTexture.Sample(txTextureSampler, input.tex).xyz, 1.0f);

	// Ensure that the normal is from [0,1] to [-1,1]
	float3 normalT = 2.0f * (txNormMap.Sample(txTextureSampler, input.tex).xyz) - 1.0f;

	// Get the normal, tangent and binormal
	float3 N = input.norm;
	float3 T = normalize(input.tangentW - dot(input.tangentW, N) * N);
	float3 B = cross(N, T);
	float3x3 TBN = float3x3(T, B, N);

	float3 normal = mul(normalT, TBN);

	if (ShowEnviromentMap)
	{
		// Sample the environment map
		float3 V = normalize(CameraPosition.xyz - input.posW.xyz);
		float3 viewDir = reflect(-V, normal);
		float4 enviroment = txEnviromentMap.Sample(txTextureSampler, viewDir);

		// Apply the metallic properties to the reflection of the enviroment
		enviroment = enviroment * Metallic;
		finalColor += enviroment;
	}

	// Run the lighting for this pixel
	LightingCalcResult light = CalculateLighting(input.posW, normalize(normal), CameraPosition);

	finalColor = (light.Diffuse + light.Specular + AmbientLight) * finalColor;

	return finalColor;
}