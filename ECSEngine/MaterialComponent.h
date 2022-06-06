#pragma once
#include <DirectXMath.h>
#include "Component.h"
#include "Texture.h"

struct MaterialProperties
{
	MaterialProperties(const  float _spec, const  float _metal)
		: specularPower(_spec), metallic(_metal) {}

	const DirectX::XMFLOAT4& ToXMFLOAT4() const { return DirectX::XMFLOAT4(specularPower, metallic, 0.0f, 0.0f); }

	float specularPower;
	float metallic;
};

class Shader;
class MaterialComponent : public Component
{
public:

	MaterialComponent() = default;
	MaterialComponent(Entity* _entity, int _compId);
	~MaterialComponent() {}

	// Setters
	void SetDiffuseTexture(const std::string& _newTexture) { SetTexture(&m_diffuseTex, _newTexture); }
	void SetNormalMap(const std::string& _newTexture) { SetTexture(&m_normalTex, _newTexture); }
	void SetEnvironmentMap(const std::string& _newTexture) { SetTexture(&m_environmentTex, _newTexture); }

	// Getters
	MaterialComponent* GetThis() { return this; }
	std::shared_ptr<Shader> GetShader() const;
	Texture* GetDiffuseTexture() const { return m_diffuseTex; }
	Texture* GetNormalMap() const { return m_normalTex; }
	Texture* GetEnvironmentMap() const { return m_environmentTex; }
	const MaterialProperties GetMaterialProperties() const { return MaterialProperties(m_specularPower, m_metallic); }

	// Internal
	void Update() override {};
	void StepPhysics() override {};
	bool DrawImGuiInterface() override;
	void WriteDataToFile(std::ofstream& _saveFile) override;
	void ReadDataFromFile(std::ifstream& _openFile) override;

private:

	// Helper functions
	void SetTexture(Texture** _textureToSet, const std::string& _newTexture) const;

	Texture* m_diffuseTex = nullptr;
	Texture* m_normalTex = nullptr;
	Texture* m_environmentTex = nullptr;

	float m_specularPower = 0.5f;
	float m_metallic = 0.1f;
};