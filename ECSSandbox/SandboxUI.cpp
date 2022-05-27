#include "SandboxUI.h"
#include "imgui/imgui.h"

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
}

void SandboxUI::DrawTopBar()
{
    // Draw the top bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
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

    // TODO: Loop through each entity and display the info
    
    ImGui::EndChild();
    ImGui::End();
}

void SandboxUI::DrawInspector()
{
    // Inspector
    ImGui::Begin("Inspector");
    ImGui::BeginChild("Scrolling");

    // TODO: Show info for selected entity
    ImGui::EndChild();
    ImGui::End();
}