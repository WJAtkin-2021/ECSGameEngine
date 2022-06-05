#ifdef BUILD_DX_11

#include <stdexcept>
#include "Renderer_DX11.h"
#include "UI_DX11.h"
#include "ConstantBuffer_DX11.h"
#include "SceneManager.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include "ResourceManager.h"

Renderer_DX11* Renderer_DX11::m_renderDx11 = nullptr;

Renderer_DX11::Renderer_DX11()
{
	m_renderDx11 = this;
}

Renderer_DX11::~Renderer_DX11()
{
	// Release com interfaces
	if (m_d3dDevice)
		m_d3dDevice.Reset();
	if (m_immediateContext)
		m_immediateContext.Reset();
	if (m_swapChain)
		m_swapChain.Reset();
	if (m_renderTargetView)
		m_renderTargetView.Reset();
	if (m_depthStencilBuffer)
		m_depthStencilBuffer.Reset();
	if (m_depthStencilView)
		m_depthStencilView.Reset();
	if (m_rasterSolidState)
		m_rasterSolidState.Reset();
	if (m_rasterWireframeState)
		m_rasterWireframeState.Reset();
	if (m_depthStenStateNormal)
		m_depthStenStateNormal.Reset();
}

void Renderer_DX11::DrawScene()
{
	// Make sure the immediate context and swap chain are valid
	assert(m_immediateContext);
	assert(m_swapChain);

	// Clear the back buffer
	m_immediateContext->ClearRenderTargetView(m_renderTargetView.Get(), m_backBufferColour);

	// Clear the depth buffer to 1.0
	m_immediateContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Rebind the render target
	m_immediateContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

	// Set the vertex shader
	ResourceManager::GetShader(ShaderType::Vertex_HLSL)->SetVertexShaderForDrawCall();

	// ******************** Main Draw Calls ********************

	// Grab the camera
	Camera* camera = Camera::GetCamera();

	// Set the per frame variables in the constant buffer
	m_constantBuffer->SetViewMat(camera->GetViewMatrix());
	m_constantBuffer->SetProjMat(camera->GetProjMatrix());
	m_constantBuffer->SetCameraPosition(camera->GetTransform().Position());

	// Grab the entity list and loop through each entity
	std::vector<Entity*> entities = SceneManager::GetEntites();
	for (size_t i = 0; i < entities.size(); i++)
	{
		// Check if a render component is in use
		if (entities[i]->HasComponent<RenderComponent>())
		{
			RenderComponent* rc = entities[i]->GetComponent<RenderComponent>();
			// Check if it has a mesh to render
			Mesh* mesh = rc->GetMesh();
			if (mesh != nullptr)
			{
				// Setup for the draw call
				// Set the mesh index and vertex buffers
				mesh->SetBuffersForDrawCall();

				// Set the constant buffer
				m_constantBuffer->SetWorldMat(entities[i]->GetComponent<Transform>()->GetWorldMatrix());
				m_constantBuffer->SetEntityColor(entities[i]->GetColor());
				m_constantBuffer->SetBufferForDrawCall();

				// Set the correct pixel shader
				ResourceManager::GetShader(ShaderType::PixelFallBack_HLSL)->SetPixelShaderForDrawCall();

				// Draw call
				m_immediateContext->DrawIndexed(mesh->GetNumberOfIndicies(), 0, 0);
			}
		}
	}

	// *********************************************************

	// Draw the UI
	UI_DX11* ui = dynamic_cast<UI_DX11*>(UI::GetIU());
	ui->DrawUI();

	// Swap the buffers
	m_swapChain->Present(0, 0);
}

void Renderer_DX11::InitGraphicsAPI(int _screenWidth, int _screenHeight)
{
	m_screenWidth = _screenWidth;
	m_screenHeight = _screenHeight;

	CreateDeviceAndContext();
	CheckMSAASupport();
	CreateSwapChain();
	CreateRenderTarget();
	CreateDepthSencil();
	SetViewPort();
	CreateConstantBuffer();
	CreateRasterState();

	// TEMP: Set the topology
	m_immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Setup ImGui
	m_UI = dynamic_cast<UI*>(new UI_DX11());
}

void Renderer_DX11::CreateDeviceAndContext()
{
	// Create the device and context
	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDevice(
		0, // Use default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		createDeviceFlags,
		0, 0,
		D3D11_SDK_VERSION,
		m_d3dDevice.GetAddressOf(),
		&featureLevel,
		m_immediateContext.GetAddressOf());

	if (FAILED(hr))
	{
		throw std::runtime_error("D3D11CreateDevice Failed");
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		throw std::runtime_error("Direct3D Feature Level 11 unsupported");
	}
}

void Renderer_DX11::CheckMSAASupport()
{
	// Check for 4X MSAA support
	HRESULT hr = (m_d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality));
	if (m_4xMsaaQuality <= 0)
	{
		throw std::runtime_error("4X MSAA unsupported");
	}
}

void Renderer_DX11::CreateSwapChain()
{
	// Fill out the swap chain descriptor
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = m_screenWidth;
	sd.BufferDesc.Height = m_screenHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	// Enable 4x MSAA
	sd.SampleDesc.Count = 4;
	sd.SampleDesc.Quality = m_4xMsaaQuality - 1;

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = m_winHandle;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	// Get the IDXGIFactory interface
	IDXGIDevice* dxgiDevice = nullptr;
	m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	IDXGIAdapter* dxgiAdapter = nullptr;
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
	IDXGIFactory* dxgiFactory = nullptr;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	// Create the swapchain
	dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &sd, &m_swapChain);

	// Release the com interfaces that we no longer need
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();
}

void Renderer_DX11::CreateRenderTarget()
{
	// Create the render target view
	ID3D11Texture2D* backBuffer = NULL;
	HRESULT hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	if (backBuffer == NULL)
	{
		throw std::runtime_error("Failed to create back buffer");
	}
	hr = m_d3dDevice->CreateRenderTargetView(backBuffer, 0, m_renderTargetView.GetAddressOf());
	backBuffer->Release();
}

void Renderer_DX11::CreateDepthSencil()
{
	// Create the depth stencil
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = m_screenWidth;
	depthStencilDesc.Height = m_screenHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	// This assumes we are forcing the use of 4x MSAA
	depthStencilDesc.SampleDesc.Count = 4;
	depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, m_depthStencilBuffer.GetAddressOf());
	m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer.Get(), nullptr, m_depthStencilView.GetAddressOf());

	// Create the depth stencil states
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = false;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Normal depth stencil state
	HRESULT hr = m_d3dDevice->CreateDepthStencilState(&dsDesc, m_depthStenStateNormal.GetAddressOf());
	if (FAILED(hr))
	{
		throw std::runtime_error("Unable to create depth stencil state");
	}

	// Bind the views to the output merger
	m_immediateContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
}

void Renderer_DX11::SetViewPort()
{
	// Set the viewport
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<float>(m_screenWidth);
	vp.Height = static_cast<float>(m_screenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_immediateContext->RSSetViewports(1, &vp);
}

void Renderer_DX11::CreateConstantBuffer()
{
	m_constantBuffer = std::shared_ptr<ConstantBuffer>(dynamic_cast<ConstantBuffer*>(new ConstantBuffer_DX11()));
}

void Renderer_DX11::CreateRasterState()
{
	// Create the state descriptor
	D3D11_RASTERIZER_DESC rasterDesc;
	//rasterDesc.CullMode = D3D11_CULL_FRONT;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.FillMode = D3D11_FILL_SOLID;

	rasterDesc.ScissorEnable = false;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the state for normal geometry
	HRESULT hr = m_d3dDevice->CreateRasterizerState(&rasterDesc, m_rasterSolidState.GetAddressOf());
	if (FAILED(hr))
	{
		throw std::runtime_error("Failed to create rasterizer state");
	}

	// Create the state for wire-framed geometry
	rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
	hr = m_d3dDevice->CreateRasterizerState(&rasterDesc, m_rasterWireframeState.GetAddressOf());
	if (FAILED(hr))
	{
		throw std::runtime_error("Failed to create rasterizer state");
	}

	// Set the default raster state
	m_immediateContext->RSSetState(m_rasterSolidState.Get());
}

#endif // BUILD_DX_11