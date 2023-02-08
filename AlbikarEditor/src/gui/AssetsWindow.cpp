#include "AssetsWindow.hpp"
#include "Preferences.hpp"
#include "Profiler.hpp"

auto CAssetsWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("CAssetsWindow::Render");
    if (ImGui::Begin(WINDOW_ASSETS, nullptr, dockFloatWindow)) {
    }
    ImGui::End();
}