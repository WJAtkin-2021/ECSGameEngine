#include "Texture.h"
#include "Texture_DX11.h"

Texture::Texture()
{

}

Texture::Texture(const std::string _filePath)
{
	m_filePath = _filePath;
}

Texture::~Texture()
{

}

std::shared_ptr<Texture> Texture::FactoryCreateTexture()
{
#ifdef BUILD_DX_11
	return std::shared_ptr<Texture>(new Texture_DX11());
#elif BUILD_OpenGL
	return std::shared_ptr<Texture>(new Texture_GL());
#endif
}