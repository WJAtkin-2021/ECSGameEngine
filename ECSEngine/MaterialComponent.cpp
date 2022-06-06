#include <fstream>
#include "MaterialComponent.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Window.h"

MaterialComponent::MaterialComponent(Entity* _entity, int _compId) : Component(_entity, _compId) { }

void MaterialComponent::SetTexture(Texture** _textureToSet, const std::string& _newTexture) const
{
	// Check to see if this was meant to clear the set texture
	if (_newTexture == "")
	{
		*_textureToSet = nullptr;
		return;
	}
	
	*_textureToSet = &ResourceManager::GetTexture(_newTexture);
}

std::shared_ptr<Shader> MaterialComponent::GetShader() const
{
	// Get the highest rendering level from the renderer
	const RenderTechnique maxLevel = Renderer::GetRenderer()->GetMaxRenderLevel();

	switch (maxLevel)
	{
	case RenderTechnique::Wireframe:
	{
		return ResourceManager::GetShader(ShaderType::PixelFallBack_HLSL);
	}
	break;
	case RenderTechnique::DiffuseUnTex:
	{
		return ResourceManager::GetShader(ShaderType::PixelFallBack_HLSL);
	}
	break;
	case RenderTechnique::DiffuseTex:
	{
		// Ensure we have a texture before using the textured shader
		// otherwise fall back to the untextured shader
		if (m_diffuseTex)
		{
			return ResourceManager::GetShader(ShaderType::PixelTextured_HLSL);
		}
		else
		{
			return ResourceManager::GetShader(ShaderType::PixelFallBack_HLSL);
		}
	}
	break;
	case RenderTechnique::BumpMapped:
	{
		// Make sure we have both a diffuse texture and a normal map
		if (m_diffuseTex && m_normalTex)
		{
			return ResourceManager::GetShader(ShaderType::PixelBumpMapped_HLSL);
		}
		// Else if we have a diffuse texture just use the textured shader
		else if (m_diffuseTex)
		{
			return ResourceManager::GetShader(ShaderType::PixelTextured_HLSL);
		}
		// Else fall back to the untextured shader
		else
		{
			return ResourceManager::GetShader(ShaderType::PixelFallBack_HLSL);
		}
	}
	break;
	default:
	{
		throw std::logic_error("Unable to determine shader to use");
	}
	break;
	}
}

bool MaterialComponent::DrawImGuiInterface()
{
	const std::string headerName = std::to_string(m_componentId) + ": Material";
	bool keepThis = true;
	if (ImGui::CollapsingHeader(headerName.c_str(), &keepThis, ImGuiTreeNodeFlags_DefaultOpen))
	{
		// Diffuse texture
		std::string textureFileText = "Diffuse Texture: ";
		if (m_diffuseTex)
		{
			textureFileText += m_diffuseTex->GetTextureFilePath();
		}
		ImGui::Text(textureFileText.c_str());
		if (ImGui::Button("New Diffuse Texture"))
		{
			const std::string newTextureFile = Window::GetWindowInstance()->GetTextureFile();
			if (newTextureFile != "")
			{
				SetDiffuseTexture(newTextureFile);
			}
		}
		ImGui::SameLine(146.0f);
		if (ImGui::Button("Remove##1"))
		{
			SetDiffuseTexture("");
		}
	
		// Normal Map
		textureFileText = "Normal Map: ";
		if (m_normalTex)
		{
			textureFileText += m_normalTex->GetTextureFilePath();
		}
		ImGui::Text(textureFileText.c_str());
		if (ImGui::Button("New Normal Map"))
		{
			const std::string newTextureFile = Window::GetWindowInstance()->GetTextureFile();
			if (newTextureFile != "")
			{
				SetNormalMap(newTextureFile);
			}
		}
		ImGui::SameLine(111.0f);
		if (ImGui::Button("Remove##2"))
		{
			SetNormalMap("");
		}
	
		// Environment Map
		textureFileText = "Environment Map: ";
		if (m_environmentTex)
		{
			textureFileText += m_environmentTex->GetTextureFilePath();
		}
		ImGui::Text(textureFileText.c_str());
		if (ImGui::Button("New Environment Map"))
		{
			const std::string newTextureFile = Window::GetWindowInstance()->GetTextureFile();
			if (newTextureFile != "")
			{
				SetEnvironmentMap(newTextureFile);
			}
		}
		ImGui::SameLine(146.0f);
		if (ImGui::Button("Remove##3"))
		{
			SetEnvironmentMap("");
		}
	
		// Specular Power
		ImGui::SliderFloat("Specular", &m_specularPower, 0.0f, 1.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
	
		// Metallic
		ImGui::SliderFloat("Metallic", &m_metallic, 0.0f, 1.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
	}
	
	return keepThis;
}


void MaterialComponent::WriteDataToFile(std::ofstream& _saveFile)
{
	_saveFile << "<ClassName> MaterialComponent </ClassName>\n";
	// Diffuse texture
	_saveFile << "<DiffuseFilePath> ";
	if (m_diffuseTex)
	{
		_saveFile << m_diffuseTex->GetTextureFilePath();
	}
	else
	{
		_saveFile << "NONE";
	}
	_saveFile << " </DiffuseFilePath>\n";
	// Normal texture
	_saveFile << "<NormalFilePath> ";
	if (m_normalTex)
	{
		_saveFile << m_normalTex->GetTextureFilePath();
	}
	else
	{
		_saveFile << "NONE";
	}
	_saveFile << " </NormalFilePath>\n";
	// Environment map
	_saveFile << "<EnvironmentFilePath> ";
	if (m_environmentTex)
	{
		_saveFile << m_environmentTex->GetTextureFilePath();
	}
	else
	{
		_saveFile << "NONE";
	}
	_saveFile << " </EnvironmentFilePath>\n";
	// Settings
	_saveFile << "<Specular> " << std::to_string(m_specularPower) << " </Specular>\n";
	_saveFile << "<Metallic> " << std::to_string(m_metallic) << " </Metallic>\n";
	_saveFile << "</ClassName>\n";
}

void MaterialComponent::ReadDataFromFile(std::ifstream& _openFile)
{
	std::string data = "";
	_openFile >> data;

	// Diffuse filepath
	_openFile >> data; // <DiffuseFilePath>
	_openFile >> data; // The filepath stored as a string
	if (data != "NONE")
	{
		SetDiffuseTexture(data);
	}
	_openFile >> data; // </DiffuseFilePath>

	// Normal filepath
	_openFile >> data; // <NormalFilePath>
	_openFile >> data; // The filepath stored as a string
	if (data != "NONE")
	{
		SetNormalMap(data);
	}
	_openFile >> data; // </NormalFilePath>

	// Environment filepath
	_openFile >> data; // <EnvironmentFilePath>
	_openFile >> data; // The filepath stored as a string
	if (data != "NONE")
	{
		SetEnvironmentMap(data);
	}
	_openFile >> data; // </EnvironmentFilePath>

	// Settings
	_openFile >> data; // <Specular>
	_openFile >> data; // Specular power stored as a float
	m_specularPower = std::stof(data);
	_openFile >> data; // </Specular>

	_openFile >> data; // <Metallic>
	_openFile >> data; // Metallic stored as a float
	m_metallic = std::stof(data);
	_openFile >> data; // </Metallic>
}