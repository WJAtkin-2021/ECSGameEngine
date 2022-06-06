#pragma once
#include <string>
#include <memory>

class Texture
{
public:
	Texture();
	Texture(const std::string _filePath);
	~Texture();

	static std::shared_ptr<Texture> FactoryCreateTexture();

	std::string GetTextureFilePath() { return m_filePath; }

	virtual void SetTextureAsDiffuseForDrawCall() = 0;
	virtual void SetTextureAsNormalForDrawCall() = 0;
	virtual void SetTextureAsEnviromentForDrawCall() = 0;
	virtual void LoadTexture(const std::string _filePath) = 0;

protected:

	std::string m_filePath;
};