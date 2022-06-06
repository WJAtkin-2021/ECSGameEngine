#pragma once
#include <directxmath.h>

struct ConstantBufferData
{
	DirectX::XMMATRIX m_world;
	DirectX::XMMATRIX m_view;
	DirectX::XMMATRIX m_projection;
	DirectX::XMFLOAT4 m_color;
	DirectX::XMFLOAT4 m_cameraPosition;
	
	float m_specularPower;
	float m_metallic;
	bool m_showEnviromentMap;
	bool m_padding1;
	bool m_padding2;
	bool m_padding3;
	float m_padding4;
};