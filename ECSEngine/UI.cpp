#include <string>
#include "imgui/imgui.h"
#include "UI.h"

UI* UI::m_instance = nullptr;

UI::UI()
{
	m_instance = this;
}

UI::~UI()
{
	ImGui::DestroyContext();
}

void UI::SetApplicationUI(std::shared_ptr<ApplicationUI> _applicationUI)
{
    m_instance->m_applicationUI = _applicationUI;
}

void UI::DrawUI()
{
    ImGui::NewFrame();

    // Draw the dock space
    DrawDockSpace();

    // Draw the applications UI if there is one
    if (m_applicationUI)
        m_applicationUI->DrawUI();

    // Render
    ImGui::Render();
}

void UI::SetupImGuiPlatformIndependant()
{
    // Setup the ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); static_cast<void>(io);
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     // Enable Multi-Viewport / Platform Windows

    // Style
    ImGui::StyleColorsDark();

    // Makes the style of the ImGui viewports look the same when dragged out of the
    // application's render context
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}

void UI::DrawDockSpace()
{
    // Setup the dockspace
    static const bool opt_fullscreen_persistant = true;
    static const ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    const bool opt_fullscreen = opt_fullscreen_persistant;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (opt_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    bool show_dockspace = true;
    ImGui::Begin("DockSpace", &show_dockspace, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    const ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
}