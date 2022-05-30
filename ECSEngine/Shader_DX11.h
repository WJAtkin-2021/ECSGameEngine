#ifdef BUILD_DX_11
#pragma once

#include <string.h>
#include <wrl.h>
#include <Windows.h>
#include <d3d11_1.h>
#include "Shader.h"


class Shader_DX11 : public Shader
{
public:
	Shader_DX11();
	~Shader_DX11();

	void LoadShader(ShaderType _shaderType) override;

	void SetVertexShaderForDrawCall();
	void SetPixelShaderForDrawCall();

private:
	void CompileVertexShaderFromFile(const WCHAR* _filePath, const LPCSTR szShaderModel);
	void CompilePixelShaderFromFile(const WCHAR* _filePath, const LPCSTR szShaderModel);
	void LoadShaderFromFile(const WCHAR* _filePath, const LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout = nullptr;
};

#endif // BUILD_DX_11