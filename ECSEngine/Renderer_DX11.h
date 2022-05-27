#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d11_1.h>
#include <DirectXMath.h>

#include "Renderer.h"

class Renderer_DX11 : public Renderer
{
public:
	Renderer_DX11();
	~Renderer_DX11() override;

	// Getters / Setters
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetImmediateContext() { return m_renderDx11->m_immediateContext; }
	static Microsoft::WRL::ComPtr<ID3D11Device> GetD3DDevice() { return m_renderDx11->m_d3dDevice; }
	void SetWindowsHandle(HWND _winHand) { m_winHandle = _winHand; }
	
	void InitGraphicsAPI(int _screenWidth, int _screenHeight) override;
	void DrawScene() override;


private:

	static Renderer_DX11* m_renderDx11;

	// Functions for setting up DirectX 11
	void CreateDeviceAndContext();
	void CheckMSAASupport();
	void CreateSwapChain();
	void CreateRenderTarget();
	void CreateDepthSencil();
	void SetViewPort();
	void CreateConstantBuffer();
	void CreateRasterState();

	const float m_backBufferColour[4] = { 73.0f / 255.0f, 180.0f / 255.0f, 204.0f / 255.0f, 1.0f };
	UINT m_4xMsaaQuality = 0;
	HWND m_winHandle = NULL;

	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_immediateContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterSolidState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterWireframeState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStenStateNormal;
};
