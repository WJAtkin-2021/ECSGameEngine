#pragma once
#ifdef BUILD_DX_11

#include <wrl.h>
#include <d3d11_1.h>
#include "GPUBuffers.h"

class GPUBuffers_DX : public GPUBuffers
{
public:
	GPUBuffers_DX();
	~GPUBuffers_DX() override;

	void GenerateBuffers();
	void SetBuffersForDrawCall() override;

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice; // Handle to the d3dDevice
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_immediateContext;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
};

#endif // BUILD_DX_11