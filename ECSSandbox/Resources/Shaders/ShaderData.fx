#ifndef __SHADER_DATA__
#define __SHADER_DATA__

// Max number of lights to support in the scene
#define MAX_LIGHTS 10

// Enums for light types
#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1

// Struct for the lights data
// Note that we must use 16 byte of padding in HLSL
struct Light
{
	float4 Position; // 16 Bytes
	float4 Color; // 16 Bytes
	float4 Direction; // 16 Bytes

	int LightType; // 4 Bytes
	bool Enabled; // 4 Bytes but this is only 1 byte on the c++ program!

	float Intensity; // 4 Bytes
	float c1; // 4 Bytes

	float c2; // 4 Bytes
	float3 Padding2; // 12 Bytes

	// Total: 80 bytes
};

// Struct for holding data about diffuse and specular from
// a lighting calculation
struct LightingCalcResult
{
	float4 Diffuse;
	float4 Specular;
};

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
	// 64 Bytes
	matrix World;
	// 64 Bytes
	matrix InverseWorld;
	// 64 Bytes
	matrix View;
	// 64 Bytes
	matrix Projection;
	// 16 Bytes
	float4 EntityColor;
	// 16 Bytes
	float4 AmbientLight;
	// 16 Bytes
	float4 CameraPosition;
	// 16 Bytes
	float SpecularPower;
	float Metallic;
	bool ShowEnviromentMap;
	float padding1;

	// 64 bytes * 10 = 640 bytes
	Light lights[MAX_LIGHTS];
}

#endif // __SHADER_DATA__