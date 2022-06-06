#ifndef __SHADER_LIGHTING__
#define __SHADER_LIGHTING__

#include "ShaderData.fx"

// Calc the amount of diffuse lighting
float4 CalculateDiffuse(Light light, float3 L, float3 N)
{
	float diffuseStrength = max(0.0, dot(N, L));
	return light.Color * diffuseStrength;
}

float4 CalculateSpecular(Light light, float3 V, float3 L, float3 N, float specPower)
{
	// Using Phong lighting
	float3 R = normalize(reflect(-L, N));
	float RdotV = max(0.0, dot(N, V));

	return light.Color * pow(RdotV, specPower);
}

LightingCalcResult CalculatePointLight(Light light, float3 V, float4 P, float3 N, float specPower)
{
	LightingCalcResult result;

	// Divided the light by the distance to create basic
	// attenuation
	float3 L = (light.Position - P).xyz;
	float distance = length(L);
	L = L / distance;

	// Calculate the attenuation
	float attenuation = 1.0f / (1.0f + light.c1 * distance + light.c2 * (distance * distance));

	result.Diffuse = CalculateDiffuse(light, L, N) * light.Intensity * attenuation;
	result.Specular = CalculateSpecular(light, V, L, N, specPower) * light.Intensity * attenuation;

	return result;
}

LightingCalcResult CalculateDirectionalLight(Light light, float3 V, float4 P, float3 N, float specPower)
{
	LightingCalcResult result;

	float3 L = -light.Direction.xyz;
	result.Diffuse = CalculateDiffuse(light, L, N) * light.Intensity;
	result.Specular = CalculateSpecular(light, V, L, N, specPower) * light.Intensity;

	return result;
}

LightingCalcResult CalculateLighting(float4 P, float3 N, float4 cameraPosition)
{
	float3 V = normalize(cameraPosition - P).xyz;

	LightingCalcResult totalLighting = { float4(0.0, 0.0, 0.0, 0.0), float4(0.0, 0.0, 0.0, 0.0) };

	// Loop through each light and add its lighting to the total
	for (int i = 0; i < MAX_LIGHTS; ++i)
	{
		LightingCalcResult result = { {0, 0, 0, 0}, {0, 0, 0, 0} };

		// Skip to the next if this one is off
		if (!lights[i].Enabled) continue;

		switch (abs(lights[i].LightType))
		{
		case DIRECTIONAL_LIGHT:
		{
			result = CalculateDirectionalLight(lights[i], V, P, N, SpecularPower);
		}
		break;
		case POINT_LIGHT:
		{
			result = CalculatePointLight(lights[i], V, P, N, SpecularPower);
		}
		break;
		}
		totalLighting.Diffuse += result.Diffuse;
		totalLighting.Specular += result.Specular;
	}

	totalLighting.Diffuse = saturate(totalLighting.Diffuse);
	totalLighting.Specular = saturate(totalLighting.Specular);

	return totalLighting;
}

#endif // __SHADER_LIGHTING__