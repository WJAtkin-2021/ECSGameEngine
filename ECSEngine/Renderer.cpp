#include "Renderer.h"

Renderer* Renderer::m_renderer = nullptr;

Renderer::Renderer()
{
	m_renderer = this;
}

Renderer::~Renderer()
{
	delete m_UI;
}