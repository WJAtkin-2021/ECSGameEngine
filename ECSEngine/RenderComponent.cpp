#include "RenderComponent.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "Window.h"

RenderComponent::RenderComponent(Entity* _entity, int _compId) : Component(_entity, _compId)
{

}

RenderComponent::~RenderComponent()
{

}

void RenderComponent::SetMesh(Mesh& _mesh)
{ 
	m_mesh = &_mesh;

	// Grab the primitive type and file path from the new mesh
	m_meshFilePath = m_mesh->GetMeshFilePath();
	m_meshPrimative = m_mesh->GetPrimativeType();
}

void RenderComponent::RemoveMesh()
{
	m_mesh = nullptr;
	m_meshFilePath = "";
	m_meshPrimative = PrimitiveTypes::INVALID;
}

bool RenderComponent::DrawImGuiInterface()
{
	std::string headerTitle = std::to_string(GetCompId()) + ": RenderComponent";
	bool keepThis = true;
	if (ImGui::CollapsingHeader(headerTitle.c_str(), &keepThis, ImGuiTreeNodeFlags_DefaultOpen))
	{
		const char* items[] = { "None", "Cube" };
		int arraySize = (sizeof(items) / sizeof(*items));
		int itemIndex = static_cast<int>(m_meshPrimative);
		if (ImGui::BeginListBox("Primitive Type"))
		{
			for (int i = 0; i < arraySize; i++)
			{
				const bool isSelected = (itemIndex == i);
				if (ImGui::Selectable(items[i], isSelected))
				{
					itemIndex = i;
					if (itemIndex == 1)
					{
						SetMesh(ResourceManager::GetMesh(PrimitiveTypes::Cube));
					}
					else if (itemIndex == 0)
					{
						RemoveMesh();
					}
				}

				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndListBox();
		}

		std::string meshFileText = "Mesh file: ";
		meshFileText += m_meshFilePath;
		ImGui::Text(meshFileText.c_str());
		if (ImGui::Button("Select New Mesh"))
		{
			const std::string newMeshFile = Window::GetWindowInstance()->GetMeshFile();
			if (newMeshFile != "")
			{
				SetMesh(ResourceManager::GetMesh(newMeshFile));
			}
		}
	}

	return keepThis;
}