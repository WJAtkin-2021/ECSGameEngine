#ifdef BUILD_DX_11

#include "UI_DX11.h"
#include "Renderer_DX11.h"
#include "Window_Win.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_dx11.h"

UI_DX11::UI_DX11()
{
    // Get the context
    m_immidiateContext = Renderer_DX11::GetImmediateContext();
    Microsoft::WRL::ComPtr<ID3D11Device> device = Renderer_DX11::GetD3DDevice();

    // Setup the platform independent parts of ImGui
    SetupImGuiPlatformIndependant();

    // Setup the render backend for win32 and dx11
    ImGui_ImplWin32_Init(Window_Win::GetHandle());
    ImGui_ImplDX11_Init(device.Get(), m_immidiateContext.Get());

    device.Reset();
}

UI_DX11::~UI_DX11()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    if (m_immidiateContext)
        m_immidiateContext.Reset();
}

void UI_DX11::DrawUI()
{
    // Start the ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    // Call drawUI on the base
    UI::DrawUI();

    // Render
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and render additional platform windows
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

#endif // BUILD_DX_11