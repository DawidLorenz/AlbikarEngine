#include "MainWindow.hpp"
#include "AssetsPreviewWindow.hpp"
#include "AssetsWindow.hpp"
#include "DockspaceWindow.hpp"
#include "EngineProperties.hpp"
#include "GameViewWindow.hpp"
#include "HierarchyWindow.hpp"
#include "InspectorWindow.hpp"
#include "LogWindow.hpp"
#include "Logger.hpp"
#include "MonitorsWindow.hpp"
#include "Profiler.hpp"
#include "ProfilerWindow.hpp"
#include "SceneViewWindow.hpp"
#include "StyleManager.hpp"
#include "TopBarWindow.hpp"

CMainWindow::CMainWindow()
{
    LOG_INFO("Create MainWindow");
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0F);
    DefaultStyle();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    m_SubWindows.emplace_back(std::make_unique<CDockspaceWindow>());
    m_SubWindows.emplace_back(std::make_unique<CTopBarWindow>());
    m_SubWindows.emplace_back(std::make_unique<CAssetsPreviewWindow>());
    m_SubWindows.emplace_back(std::make_unique<CAssetsWindow>());
    m_SubWindows.emplace_back(std::make_unique<CGameViewWindow>());
    m_SubWindows.emplace_back(std::make_unique<CHierarchyWindow>());
    m_SubWindows.emplace_back(std::make_unique<CInspectorWindow>());
    m_SubWindows.emplace_back(std::make_unique<CLogWindow>());
    m_SubWindows.emplace_back(std::make_unique<CProfilerWindow>());
    m_SubWindows.emplace_back(std::make_unique<CSceneViewWindow>());
    m_SubWindows.emplace_back(std::make_unique<CMonitorsWindow>());
    m_SubWindows.emplace_back(std::make_unique<CEnginePropertiesWindow>());
    m_SubWindows.shrink_to_fit();

    CStyleManager::Get();
}

void CMainWindow::Render()
{
    {
        ALB_PROFILE_SCOPE("MainWindow::Render::ImGui::NewFrame");
        ImGui::NewFrame();
    }
    RenderWindows();
    {
        ALB_PROFILE_SCOPE("MainWindow::Render::ImGui::Render");
        ImGui::Render();
    }
}

void CMainWindow::RenderWindows()
{
    for (auto& m_SubWindow : m_SubWindows) {
        m_SubWindow->Render();
    }
}

void CMainWindow::DefaultStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding.x = 4.0f;
    style.WindowPadding.y = 4.0f;
}