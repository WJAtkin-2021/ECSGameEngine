#pragma once
#include <wrl.h>
#include <d3d11_1.h>
#include "UI.h"

class UI_DX : public UI
{
public:
	UI_DX();
	~UI_DX() override;

	void DrawUI() override;

private:

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_immidiateContext = nullptr;
};