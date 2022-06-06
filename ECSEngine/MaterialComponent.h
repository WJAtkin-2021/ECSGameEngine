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
	void SetDiffuseTexture(const std::string& _newTexture) { SetTexture(&mp_diffuseTex, _newTexture); }
	void SetNormalMap(const std::string& _newTexture) { SetTexture(&mp_normalTex, _newTexture); }
	void SetEnvironmentMap(const std::string& _newTexture) { SetTexture(&mp_environmentTex, _newTexture); }

	// Getters
	MaterialComponent* GetThis() { return this; }
	std::shared_ptr<Shader> GetShader() const;
	const Texture* GetDiffuseTexture() const { return mp_diffuseTex; }
	const Texture* GetNormalMap() const { return mp_normalTex; }
	const Texture* GetEnvironmentMap() const { return mp_environmentTex; }
	const MaterialProperties& GetMaterialProperties() const { return MaterialProperties(m_specularPower, m_metallic); }

	// Internal
	void Update() override {};
	void StepPhysics() override {};
	bool DrawImGuiInterface() override;

private:

	// Helper functions
	void SetTexture(Texture** _textureToSet, const std::string& _newTexture) const;

	Texture* mp_diffuseTex = nullptr;
	Texture* mp_normalTex = nullptr;
	Texture* mp_environmentTex = nullptr;

	float m_specularPower = 0.5f;
	float m_metallic = 0.1f;
};