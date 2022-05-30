#include <stdexcept>
#include "GPUBuffers_DX11.h"
#include "GPUBuffers.h"
#include "Renderer_DX11.h"

#ifdef BUILD_DX_11

GPUBuffers_DX::GPUBuffers_DX() : GPUBuffers()
{
	// Grab the d3d11 device from the renderer
	m_d3dDevice = Renderer_DX11::GetD3DDevice();
	// Grab the immediate context
	m_immediateContext = Renderer_DX11::GetImmediateContext();
}

GPUBuffers_DX::~GPUBuffers_DX()
{
	// Cleanup
	if (m_vertexBuffer)
		m_vertexBuffer.Reset();
	if (m_indexBuffer)
		m_indexBuffer.Reset();
	if (m_immediateContext)
		m_immediateContext.Reset();
	if (m_d3dDevice)
		m_d3dDevice.Reset();
}

void GPUBuffers_DX::GenerateBuffers()
{
	// If there are any existing buffers clean them up
	if (m_vertexBuffer)
		m_vertexBuffer.Reset();
	if (m_indexBuffer)
		m_indexBuffer.Reset();

	// Create vertex buffer
	D3D11_BUFFER_DESC vboDesc = {};
	vboDesc.Usage = D3D11_USAGE_DEFAULT;
	vboDesc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * m_verticies.size());
	vboDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vboDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = m_verticies.data();

	HRESULT hr = m_d3dDevice->CreateBuffer(&vboDesc, &vinitData, m_vertexBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		throw std::runtime_error("HR Failed on create vertex buffer");
	}

	// Create the index buffer
	D3D11_BUFFER_DESC iboDesc = {};
	iboDesc.Usage = D3D11_USAGE_DEFAULT;
	iboDesc.ByteWidth = static_cast<UINT>(sizeof(unsigned int) * m_indicies.size());
	iboDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iboDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = m_indicies.data();

	hr = m_d3dDevice->CreateBuffer(&iboDesc, &iinitData, m_indexBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		throw std::runtime_error("HR Failed on create index buffer");
	}
}

void GPUBuffers_DX::SetBuffersForDrawCall()
{
	// Setup the vertex buffer for the draw call
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;

	m_immediateContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);

	// NOTE: Just so I don't forget and mess this up later and cause a problem that takes 5+ hours to
	// debug we need to use DXGI_FORMAT_R32_UINT instead of DXGI_FORMAT_R16_UINT as we are using
	// unsigned int for the indices as apposed to WORD as WORD is specific to win32 API and is
	// not cross platform compatible and is also half the size

	// And the index buffer as well
	m_immediateContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

#endif // BUILD_DX_11