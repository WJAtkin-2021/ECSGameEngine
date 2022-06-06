#pragma once
#include <d3d11_1.h>
#include <wrl.h>
#include "Texture.h"

class Texture_DX11 : public Texture
{
public:
	Texture_DX11();
	Texture_DX11(const std::string _filePath);
	~Texture_DX11();

	void SetTextureAsDiffuseForDrawCall() override;
	void SetTextureAsNormalForDrawCall() override;
	void SetTextureAsEnviromentForDrawCall() override;
	
	void LoadTexture(const std::string _filePath) override;

private:

	void Init();

	// Handle to the context
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_immediateContext = nullptr;

	// Handle to the shader resource view and sampler state
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureRV = nullptr;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState = nullptr;
};