#pragma once
#include <DirectXMath.h>
#include "Vector3D.h"

class ConstantBuffer
{
public:

	ConstantBuffer();
	virtual ~ConstantBuffer() = default;

	virtual void SetBufferForDrawCall() = 0;

	virtual void SetWorldMat(DirectX::XMMATRIX _mat) = 0;
	virtual void SetViewMat(DirectX::XMMATRIX _mat) = 0;
	virtual void SetProjMat(DirectX::XMMATRIX _mat) = 0;
	virtual void SetEntityColor(Vector3D _color) = 0;
	virtual void SetCameraPosition(Vector3D _pos) = 0;
	virtual void SetSpecularPower(float _specPower) = 0;
	virtual void SetMetallic(float _metallic) = 0;
	virtual void SetEnviromentMapFlag(bool _isEnabled) = 0;
};