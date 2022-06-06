#include "imgui/imgui.h"
#include "SandboxUI.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Window.h"

SandboxUI::SandboxUI()
{

}

SandboxUI::~SandboxUI()
{

}

void SandboxUI::DrawUI()
{
	DrawTopBar();
	DrawScenehierarchy();
	DrawInspector();
    DrawLightingWindow();
    DrawRenderWindow();
}

void SandboxUI::DrawTopBar()
{
    // Draw the top bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N"))
            {
                SceneManager::NewScene();
                m_selectedEntity = nullptr;
            }
            if (ImGui::MenuItem("Open", "Ctrl+O"))
            {
                const std::string filepath = Window::GetWindowInstance()->GetOpenFile();
                SceneManager::OpenScene(filepath);
            }
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
                if (SceneManager::HasValidSavePath())
                {
                    SceneManager::SaveScene();
                }
                else
                {
                    const std::string filepath = Window::GetWindowInstance()->GetSaveFile();
                    SceneManager::SaveSceneAs(filepath);
                }
            }
            if (ImGui::MenuItem("Save As..."))
            {
                const std::string filepath = Window::GetWindowInstance()->GetSaveFile();
                SceneManager::SaveSceneAs(filepath);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::EndMenu();
        }
    }
    ImGui::EndMenuBar();
    ImGui::End();
}

void SandboxUI::DrawScenehierarchy()
{
    // Scene hierarchy
    ImGui::Begin("Scene Hierarchy");
    ImGui::BeginChild("Scrolling");

    // Loop through each entity and display the info
    std::vector<Entity*> entities = SceneManager::GetEntites();
    for (int i = 0; i < entities.size(); i++)
    {
        DrawEnityInHierarchy(entities[i]);
    }

    ImGui::Button("Add Entity");
    if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
    {
        ImGui::Text("Select Mesh");
        bool selected = false;
        ImGui::Selectable("Cube", &selected);
        if (selected)
        {
            // Create cube
            SceneManager::CreatePrimative(PrimitiveTypes::Cube);
            ImGui::CloseCurrentPopup();
            selected = false;
        }

        if (ImGui::Button("Close"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Right-click to add entity");

    ImGui::EndChild();
    ImGui::End();
}

void SandboxUI::DrawInspector()
{
    // Inspector
    ImGui::Begin("Inspector");
    ImGui::BeginChild("Scrolling");

    // Get information on the current entity
    if (m_selectedEntity != nullptr)
    {
        const bool entityDeleted = m_selectedEntity->DrawImGuiInterface();
        if (entityDeleted)
            m_selectedEntity = nullptr;
    }
    else
    {
        // Show default text
        ImGui::Text("No Entity Selected");
    }

    // TODO: Show info for selected entity
    ImGui::EndChild();
    ImGui::End();
}

void SandboxUI::DrawEnityInHierarchy(Entity* _entity)
{
    // Text to display
    std::string text = std::to_string(_entity->GetId());
    text += ": " + _entity->GetName();

    bool selected = false;
    ImGui::Selectable(text.c_str(), &selected);
    if (selected)
    {
        m_selectedEntity = _entity;
    }
}

void SandboxUI::DrawLightingWindow()
{
    ImGui::Begin("Lighting");

    // Ambient lighting
    ImGui::Text("Ambient Lighting:");
    Vector3D ambient = SceneManager::GetAmbientRBG();
    float color[4] = { ambient.m_x, ambient.m_y, ambient.m_z, 1.0f };
    ImGui::ColorEdit4("", color, ImGuiColorEditFlags_Float);
    ambient = Vector3D(color[0], color[1], color[2]);
    SceneManager::SetAmbientRGB(ambient);
    ImGui::End();
}

void SandboxUI::DrawRenderWindow()
{
    ImGui::Begin("Render");

    // Show rendering technique
    ImGui::Text("Rendering Technique:");
    const char* technique[] = { "Wireframe", "Diffuse (Untextured)", "Diffuse (textured)", "Bump Mapped" };
    int selectedtechnique = static_cast<int>(Renderer::GetRenderer()->GetMaxRenderLevel());
    ImGui::Combo("##RenderWindow1", &selectedtechnique, technique, IM_ARRAYSIZE(technique));
    Renderer::GetRenderer()->SetRenderLevel(static_cast<RenderTechnique>(selectedtechnique));

    // Show skybox
    bool enableSky = Renderer::GetRenderer()->GetSkyboxShow();
    ImGui::Checkbox("Enable Skybox", &enableSky);
    Renderer::GetRenderer()->SetSkyboxShow(enableSky);

    ImGui::End();
}