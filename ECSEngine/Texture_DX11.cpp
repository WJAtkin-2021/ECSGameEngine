#include <stdexcept>
#include "Texture_DX11.h"
#include "Renderer_DX11.h"
#include "DDSTextureLoader11.h"

Texture_DX11::Texture_DX11()
{
	Init();
}

Texture_DX11::Texture_DX11(const std::string _filePath) : Texture(_filePath)
{
	Init();
	LoadTexture(_filePath);
}

Texture_DX11::~Texture_DX11()
{
	if (m_immediateContext)
		m_immediateContext.Reset();
	if (m_textureRV)
		m_textureRV.Reset();
	if (m_samplerState)
		m_samplerState.Reset();
}

void Texture_DX11::Init()
{
	// Grab the device and context from the renderer
	Microsoft::WRL::ComPtr<ID3D11Device> device = Renderer_DX11::GetD3DDevice();
	m_immediateContext = Renderer_DX11::GetImmediateContext();

	// Create the sampler
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	device->CreateSamplerState(&sampDesc, &m_samplerState);

	device.Reset();
}

void Texture_DX11::SetTextureForDrawCall()
{
	m_immediateContext->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	m_immediateContext->PSSetShaderResources(0, 1, m_textureRV.GetAddressOf());
}

void Texture_DX11::LoadTexture(const std::string _filePath)
{
	m_filePath = _filePath;

	// Grab the device and context from the renderer
	Microsoft::WRL::ComPtr<ID3D11Device> device = Renderer_DX11::GetD3DDevice();

	// Load in the texture using DDS texture loader
	// Turn the string into a wide string
	const std::wstring filePath = std::wstring(_filePath.begin(), _filePath.end());

	// Import the dds into memory
	const HRESULT hr = DirectX::CreateDDSTextureFromFile(device.Get(), filePath.c_str(), nullptr, m_textureRV.GetAddressOf());
	if (FAILED(hr))
	{
		throw std::runtime_error("Failed to load DDS Texture from file: " + _filePath);
	}

	device.Reset();
}