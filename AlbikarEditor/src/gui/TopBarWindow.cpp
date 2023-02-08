#include "TopBarWindow.hpp"
#include "Profiler.hpp"
#include "TopBarWindowBuild.hpp"
#include "TopBarWindowCenterLabel.hpp"
#include "TopBarWindowDebug.hpp"
#include "TopBarWindowEdit.hpp"
#include "TopBarWindowFile.hpp"
#include "TopBarWindowHelp.hpp"
#include "TopBarWindowView.hpp"

CTopBarWindow::CTopBarWindow()
{
    m_SubWindows.emplace_back(std::make_unique<CTopBarWindowFile>());
    m_SubWindows.emplace_back(std::make_unique<CTopBarWindowEdit>());
    m_SubWindows.emplace_back(std::make_unique<CTopBarWindowBuild>());
    m_SubWindows.emplace_back(std::make_unique<CTopBarWindowView>());
    m_SubWindows.emplace_back(std::make_unique<CTopBarWindowHelp>());
    m_SubWindows.emplace_back(std::make_unique<CTopBarWindowDebug>());
    m_SubWindows.emplace_back(std::make_unique<CTopBarWindowCenterLabel>());
    m_SubWindows.shrink_to_fit();
}

auto CTopBarWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("TopBarWindow::Render");
    if (ImGui::BeginMainMenuBar()) {

        for (auto& m_SubWindow : m_SubWindows) {
            m_SubWindow->Render();
        }

        ImGui::EndMainMenuBar();
    }
}