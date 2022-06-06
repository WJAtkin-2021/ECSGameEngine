#ifdef BUILD_DX_11

#include <Windows.h>
#include <stdexcept>
#include "Renderer_DX11.h"
#include "ConstantBuffer_DX11.h"

using namespace DirectX;

ConstantBuffer_DX11::ConstantBuffer_DX11()
{
	// Blank out the matrices
	m_constBufferData.m_world = XMMatrixIdentity();
	m_constBufferData.m_view = XMMatrixIdentity();
	m_constBufferData.m_projection = XMMatrixIdentity();

	// Fill out the descriptor for the constant buffer
	D3D11_BUFFER_DESC constBuffDesc;
	constBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	constBuffDesc.ByteWidth = sizeof(ConstantBufferData);
	constBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBuffDesc.CPUAccessFlags = 0;
	constBuffDesc.MiscFlags = 0;

	// Create the buffer
	const HRESULT hr = Renderer_DX11::GetD3DDevice()->CreateBuffer(&constBuffDesc, nullptr, m_constantBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		throw std::runtime_error("Unable to create constant buffer in ConstantBuffer_DX::ConstantBuffer_DX()");
	}

	// Store the d3d context for later use
	m_immediateContext = Renderer_DX11::GetImmediateContext();
}

ConstantBuffer_DX11::~ConstantBuffer_DX11()
{
	// Cleanup
	if (m_constantBuffer)
		m_constantBuffer.Reset();
	if (m_immediateContext)
		m_immediateContext.Reset();
}

void ConstantBuffer_DX11::SetBufferForDrawCall()
{
	m_immediateContext->UpdateSubresource(m_constantBuffer.Get(), 0, nullptr, &m_constBufferData, 0, 0);

	// Make this buffer avail on the shaders
	m_immediateContext->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	m_immediateContext->PSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
}

void ConstantBuffer_DX11::SetWorldMat(DirectX::XMMATRIX _mat)
{
	m_constBufferData.m_world = _mat;
}

void ConstantBuffer_DX11::SetViewMat(DirectX::XMMATRIX _mat)
{
	m_constBufferData.m_view = _mat;
}

void ConstantBuffer_DX11::SetProjMat(DirectX::XMMATRIX _mat)
{
	m_constBufferData.m_projection = _mat;
}

void ConstantBuffer_DX11::SetEntityColor(Vector3D _color)
{
	m_constBufferData.m_color.x = _color.m_x;
	m_constBufferData.m_color.y = _color.m_y;
	m_constBufferData.m_color.z = _color.m_z;
	m_constBufferData.m_color.w = 1.0f;
}

void ConstantBuffer_DX11::SetCameraPosition(Vector3D _pos)
{
	m_constBufferData.m_cameraPosition.x = _pos.m_x;
	m_constBufferData.m_cameraPosition.y = _pos.m_y;
	m_constBufferData.m_cameraPosition.z = _pos.m_z;
	m_constBufferData.m_cameraPosition.w = 0.0f;
}

void ConstantBuffer_DX11::SetSpecularPower(float _specPower)
{
	m_constBufferData.m_specularPower = _specPower;
}

void ConstantBuffer_DX11::SetMetallic(float _metallic)
{
	m_constBufferData.m_metallic = _metallic;
}

void ConstantBuffer_DX11::SetEnviromentMapFlag(bool _isEnabled)
{
	m_constBufferData.m_showEnviromentMap = _isEnabled;
}

#endif // BUILD_DX_11