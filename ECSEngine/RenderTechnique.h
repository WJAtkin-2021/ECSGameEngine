#pragma once

enum class RenderTechnique : unsigned int
{
	Wireframe = 0u,
	DiffuseUnTex = 1u,
	DiffuseTex = 2u,
	BumpMapped = 3u,
};