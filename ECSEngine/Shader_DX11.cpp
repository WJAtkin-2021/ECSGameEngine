#ifdef BUILD_DX_11

#include <stdexcept>
#include <d3dcompiler.h>
#include <string>
#include "Shader_DX11.h"
#include "Renderer_DX11.h"

Shader_DX11::Shader_DX11()
{
	m_context = Renderer_DX11::GetImmediateContext();
}

Shader_DX11::~Shader_DX11()
{
	if (m_vertexShader)
		m_vertexShader.Reset();
	if (m_pixelShader)
		m_pixelShader.Reset();
	if (m_inputLayout)
		m_inputLayout.Reset();
	if (m_context)
		m_context.Reset();
}

void Shader_DX11::SetVertexShaderForDrawCall()
{
	m_context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	m_context->IASetInputLayout(m_inputLayout.Get());
}

void Shader_DX11::SetPixelShaderForDrawCall()
{
	m_context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}

void Shader_DX11::LoadShader(ShaderType _shaderType)
{
	switch (_shaderType)
	{
	case ShaderType::Vertex_HLSL:
		CompileVertexShaderFromFile(L"Resources\\Shaders\\VertexShader.hlsl", "vs_5_0");
		break;
	case ShaderType::VertexSkyBox_HLSL:
		CompileVertexShaderFromFile(L"Resources\\Shaders\\SkyBoxVertexShader.hlsl", "vs_5_0");
		break;
	case ShaderType::PixelFallBack_HLSL:
		CompilePixelShaderFromFile(L"Resources\\Shaders\\FallbackPixelShader.hlsl", "ps_5_0");
		break;
	case ShaderType::PixelTextured_HLSL:
		CompilePixelShaderFromFile(L"Resources\\Shaders\\TexturedPixelShader.hlsl", "ps_5_0");
		break;
	case ShaderType::PixelSkyBox_HLSL:
		CompilePixelShaderFromFile(L"Resources\\Shaders\\SkyBoxPixelShader.hlsl", "ps_5_0");
		break;
	case ShaderType::PixelBumpMapped_HLSL:
		CompilePixelShaderFromFile(L"Resources\\Shaders\\BumpMappedPixelShader.hlsl", "ps_5_0");
		break;
	default:
		throw std::invalid_argument("Shader type not implemented on LoadShader");
		break;
	}
}

void Shader_DX11::CompileVertexShaderFromFile(const WCHAR* _filePath, const LPCSTR szShaderModel)
{
	// Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	LoadShaderFromFile(_filePath, szShaderModel, &pVSBlob);

	// Create the vertex shader
	Microsoft::WRL::ComPtr<ID3D11Device> device = Renderer_DX11::GetD3DDevice();
	HRESULT hr = device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, m_vertexShader.GetAddressOf());
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return;
	}

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = ARRAYSIZE(vertexDesc);

	// Create the input layout
	hr = device->CreateInputLayout(vertexDesc, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), m_inputLayout.GetAddressOf());
	pVSBlob->Release();
	if (FAILED(hr))
	{
		throw std::runtime_error("Unable to create vertex shader");
	}

	device.Reset();
}

void Shader_DX11::CompilePixelShaderFromFile(const WCHAR* _filePath, const LPCSTR szShaderModel)
{
	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	LoadShaderFromFile(_filePath, szShaderModel, &pPSBlob);

	// Create the pixel shader
	Microsoft::WRL::ComPtr<ID3D11Device> device = Renderer_DX11::GetD3DDevice();
	HRESULT hr = device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, m_pixelShader.GetAddressOf());
	pPSBlob->Release();
	if (FAILED(hr))
	{
		throw std::runtime_error("Unable to create pixel shader");
	}

	device.Reset();
}

void Shader_DX11::LoadShaderFromFile(const WCHAR* _filePath, const LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG

	// Used in debug mode to allow us to use the built in graphics debugger
	shaderFlags |= D3DCOMPILE_DEBUG;
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

#endif

	ID3DBlob* pErrorBlob = nullptr;
	const HRESULT hr = D3DCompileFromFile(_filePath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", szShaderModel,
		shaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		throw std::runtime_error("Unable to compile shader from file");
	}
	if (pErrorBlob) pErrorBlob->Release();
}

#endif // BUILD_DX_11