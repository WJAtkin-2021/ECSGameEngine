#include <fstream>
#include "LightComponent.h"
#include "SceneManager.h"

LightComponent::LightComponent(Entity* _entity, int _compId) : Component(_entity, _compId)
{
	// Create a light object for this component
	m_light = SceneManager::CreateNewLight();
	// Set the lights position
	m_light->SetPosition(m_entity->GetComponent<Transform>()->Position());
}

LightComponent::~LightComponent()
{
	SceneManager::RemoveLight(m_light);
}

void LightComponent::Update()
{
	// Set the lights position
	m_light->SetPosition(m_entity->GetComponent<Transform>()->Position());
}

bool LightComponent::DrawImGuiInterface()
{
	const std::string headerName = std::to_string(m_componentId) + ": Light";
	bool keepThis = true;
	if (ImGui::CollapsingHeader(headerName.c_str(), &keepThis, ImGuiTreeNodeFlags_DefaultOpen))
	{
		// Lighting color picker
		float colorPick[3] = { m_light->Color().m_x, m_light->Color().m_y, m_light->Color().m_z };
		ImGui::ColorEdit3("Color", colorPick, ImGuiColorEditFlags_Float);
		m_light->SetColor(Vector3D(colorPick[0], colorPick[1], colorPick[2]));

		// Direction - Applicable to directional lights only
		float direction[3] = { m_light->Direction().m_x, m_light->Direction().m_y, m_light->Direction().m_z };
		ImGui::DragFloat3("Direction", direction, 0.0025f, -1.0f, 1.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
		m_light->SetDirection(Vector3D(direction[0], direction[1], direction[2]));

		// Type - Currently only two types exist (Directional and point)
		const char* type[] = { "Directional", "Point" };
		int selectedType = static_cast<int>(m_light->Type());
		ImGui::Combo("Light Type", &selectedType, type, IM_ARRAYSIZE(type));
		m_light->SetType(static_cast<LightType>(selectedType));

		// Light intensity - Used as a scalar to multiply the final result of the lighting equations
		float intensity[1] = { m_light->Intensity() };
		ImGui::SliderFloat("Intensity", intensity, 0.0f, 2.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
		m_light->SetIntensity(intensity[0]);

		// C1 used for light attenuation
		float c1[1] = { m_light->C1() };
		ImGui::SliderFloat("C1", c1, 0.0f, 4.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
		m_light->SetC1(c1[0]);

		// C2 used for light attenuation
		float c2[1] = { m_light->C2() };
		ImGui::SliderFloat("C2", c2, 0.0f, 4.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat);
		m_light->SetC2(c2[0]);

		// Enabled - whether the light is enabled or not
		bool enabled = m_light->Enabled();
		ImGui::Checkbox("Enabled", &enabled);
		m_light->SetEnabledState(enabled);
	}

	return keepThis;
}

void LightComponent::WriteDataToFile(std::ofstream& _saveFile)
{
	_saveFile << "<LightComponent>\n";
	_saveFile << "<ClassName> LightComponent </ClassName>\n";
	_saveFile << "<Color> " << m_light->Color().m_x << " " << m_light->Color().m_y << " " << m_light->Color().m_z << " </Color>\n";
	_saveFile << "<Direction> " << m_light->Direction().m_x << " " << m_light->Direction().m_y << " " << m_light->Direction().m_z << " </Direction>\n";
	_saveFile << "<Type> " << static_cast<int>(m_light->Type()) << " </Type>\n";
	_saveFile << "<Intensity> " << m_light->Intensity() << " </Intensity>\n";
	_saveFile << "<C1> " << m_light->C1() << " </C1>\n";
	_saveFile << "<C2> " << m_light->C2() << " </C2>\n";
	_saveFile << "<Enabled> " << m_light->Enabled() << " </Enabled>\n";
	_saveFile << "</LightComponent>\n";
}

void LightComponent::ReadDataFromFile(std::ifstream& _openFile)
{
	std::string data = "";
	_openFile >> data;

	// Color data
	Vector3D newColor = Vector3D();
	_openFile >> data; // <Color>
	_openFile >> data; // R component
	newColor.m_x = std::stof(data);
	_openFile >> data; // G component
	newColor.m_y = std::stof(data);
	_openFile >> data; // B component
	newColor.m_z = std::stof(data);
	_openFile >> data; // </Color>
	m_light->SetColor(newColor);

	// Direction
	Vector3D newDir = Vector3D();
	_openFile >> data; // <Direction>
	_openFile >> data; // X component
	newDir.m_x = std::stof(data);
	_openFile >> data; // Y component
	newDir.m_y = std::stof(data);
	_openFile >> data; // Z component
	newDir.m_z = std::stof(data);
	_openFile >> data; // </Direction>
	m_light->SetDirection(newDir);

	// Light type
	_openFile >> data; // <Type>
	_openFile >> data; // Type as int
	m_light->SetType(static_cast<LightType>(std::stoi(data)));
	_openFile >> data; // </Type>

	// Intensity
	_openFile >> data; // <Intensity>
	_openFile >> data; // Intensity as a float
	m_light->SetIntensity(std::stof(data));
	_openFile >> data; // </Intensity>

	// C1
	_openFile >> data; // <C1>
	_openFile >> data; // C1 as a float
	m_light->SetC1(std::stof(data));
	_openFile >> data; // </C1>

	// C2
	_openFile >> data; // <C2>
	_openFile >> data; // C2 as a float
	m_light->SetC2(std::stof(data));
	_openFile >> data; // </C2>

	// Enabled state
	_openFile >> data; // <Enabled>
	_openFile >> data; // Enabled as a bool
	m_light->SetEnabledState(static_cast<bool>(std::stoi(data)));
	_openFile >> data; // </Enabled>
}