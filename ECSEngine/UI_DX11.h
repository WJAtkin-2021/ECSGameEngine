#pragma once
#ifdef BUILD_DX_11

#include <wrl.h>
#include <d3d11_1.h>
#include "UI.h"

class UI_DX11 : public UI
{
public:
	UI_DX11();
	~UI_DX11() override;

	void DrawUI() override;

private:

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_immidiateContext = nullptr;
};

#endif // BUILD_DX_11