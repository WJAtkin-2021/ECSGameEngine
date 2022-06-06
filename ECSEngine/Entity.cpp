#include "Entity.h"
#include "SceneManager.h"

Entity::Entity(int _id)
{
	m_id = _id;
}

Entity::~Entity()
{
	// Remove all components
	for (size_t i = 0; i < m_components.size(); i++)
	{
		delete m_components[i];
	}
}

bool Entity::DrawImGuiInterface()
{
	// Draw the entities interface
	ImGui::Text(m_name.c_str());
	ImGui::SameLine(120.0f);
	if (ImGui::Button("Delete"))
	{
		SceneManager::RemoveEntity(this);
		return true;
	}

	// Name
	ImGui::InputText("Entity Name", &m_name);

	// Color
	ImGui::Text("Entity Color:");
	float color[3] = { m_color.m_x, m_color.m_y, m_color.m_z };
	ImGui::ColorEdit3("", color, ImGuiColorEditFlags_Float);
	m_color.m_x = color[0];
	m_color.m_y = color[1];
	m_color.m_z = color[2];

	// Loop through each component and draw the UI
	for (int i = 0; i < m_components.size(); i++)
	{
		const bool keepThis = m_components[i]->DrawImGuiInterface();
		if (!keepThis)
		{
			// Delete this component and stop drawing for component UIs
			DeleteComponent(m_components[i]->GetCompId());
			break;
		}
	}

	// Draw the add component interface
	ImGui::Button("Add Component");
	if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
	{
		ImGui::Text("Select Component");
		bool selected = false;
		ImGui::Selectable("Render Component", &selected);
		if (selected)
		{
			AddComponent<RenderComponent>();
			ImGui::CloseCurrentPopup();
			selected = false;
		}
		ImGui::Selectable("Material", &selected);
		if (selected)
		{
			AddComponent<MaterialComponent>();
			ImGui::CloseCurrentPopup();
			selected = false;
		}
		ImGui::Selectable("Light", &selected);
		if (selected)
		{
			AddComponent<LightComponent>();
			ImGui::CloseCurrentPopup();
			selected = false;
		}

		if (ImGui::Button("Close"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Right-click to add component");

	return false;
}

void Entity::DeleteComponent(int _compId)
{
	// Loop until the component is found
	for (size_t i = 0; i < m_components.size(); i++)
	{
		if (m_components[i]->GetCompId() == _compId)
		{
			delete m_components[i];
			m_components.erase(m_components.begin() + i);
		}
	}
}