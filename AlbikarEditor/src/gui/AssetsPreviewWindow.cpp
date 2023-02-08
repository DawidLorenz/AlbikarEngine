#include "AssetsPreviewWindow.hpp"
#include "Preferences.hpp"
#include "Profiler.hpp"

auto CAssetsPreviewWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("CAssetsPreviewWindow::Render");
    if (ImGui::Begin(WINDOW_ASSETS_PREVIEW, nullptr, dockFloatWindow)) {
    }
    ImGui::End();
}