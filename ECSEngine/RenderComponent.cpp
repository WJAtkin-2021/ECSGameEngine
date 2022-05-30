#include "RenderComponent.h"
#include "Mesh.h"

RenderComponent::RenderComponent(Entity* _entity, int _compId) : Component(_entity, _compId)
{

}

RenderComponent::~RenderComponent()
{

}

bool RenderComponent::DrawImGuiInterface()
{
	std::string headerTitle = std::to_string(GetCompId()) + ": RenderComponent";
	if (ImGui::CollapsingHeader(headerTitle.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		// Display primitive type
		const char* items[] = { "None", "Cube", "Sphere" };
		std::string primativeTypeText = "Primative type: ";
		int primativeType = static_cast<int>(m_mesh->GetPrimativeType());
		primativeTypeText += items[primativeType];
		ImGui::Text(primativeTypeText.c_str());

		// Display mesh file
		if (m_mesh->GetPrimativeType() == PrimitiveTypes::INVALID)
		{
			std::string meshFileText = "Mesh file: ";
			meshFileText += m_mesh->GetMeshFilePath();
			ImGui::Text(meshFileText.c_str());
		}
	}

	return true;
}