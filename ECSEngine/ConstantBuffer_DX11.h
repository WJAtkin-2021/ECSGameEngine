#pragma once
#ifdef BUILD_DX_11

#include <d3d11.h>
#include <wrl.h>

#include "ConstantBuffer.h"
#include "ConstantBufferData.h"

class ConstantBuffer_DX11 : public ConstantBuffer
{
public:

	ConstantBuffer_DX11();
	~ConstantBuffer_DX11();

	void SetBufferForDrawCall() override;

	void SetWorldMat(DirectX::XMMATRIX _mat) override;
	void SetViewMat(DirectX::XMMATRIX _mat) override;
	void SetProjMat(DirectX::XMMATRIX _mat) override;
	void SetEntityColor(Vector3D _color) override;
	void SetCameraPosition(Vector3D _pos) override;
	void SetSpecularPower(float _specPower) override;
	void SetMetallic(float _metallic) override;
	void SetEnviromentMapFlag(bool _isEnabled) override;

private:

	// The struct that will hold the data to be copied
	// to the GPU
	ConstantBufferData m_constBufferData;

	// DX interface for the constant buffer
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
	// Interface for the immediate context
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_immediateContext;
};

#endif // BUILD_DX_11