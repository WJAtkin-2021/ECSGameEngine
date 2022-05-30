#pragma once
#include <directxmath.h>

struct ConstantBufferData
{
	DirectX::XMMATRIX m_world;
	DirectX::XMMATRIX m_view;
	DirectX::XMMATRIX m_projection;
	DirectX::XMFLOAT4 m_color;
	DirectX::XMFLOAT4 m_cameraPosition;
};