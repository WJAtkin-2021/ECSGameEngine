#pragma once
#include "UI.h"
#include "ConstantBuffer.h"
#include "Renderer.h"
#include "RenderTechnique.h"

class Renderer
{
public:
	virtual void InitGraphicsAPI(int _screenWidth, int _screenHeight) = 0;
	virtual void DrawScene() = 0;

	virtual ~Renderer();

	static Renderer* GetRenderer() { return m_renderer; }

	RenderTechnique GetMaxRenderLevel() { return m_renderLevel; }

protected:
	Renderer();

	int m_screenWidth = 0;
	int m_screenHeight = 0;

	// Constant buffer for updating the GPU
	std::shared_ptr<ConstantBuffer> m_constantBuffer;

	// UI class that sets up and manages ImGui
	UI* m_UI = nullptr;

	// Highest level of rendering permitted
	RenderTechnique m_renderLevel = RenderTechnique::BumpMapped;

protected:
	static Renderer* m_renderer;
};