#include "EngineProperties.hpp"
#include "Preferences.hpp"
#include "Profiler.hpp"

auto CEnginePropertiesWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("CEnginePropertiesWindow::Render");
    if (ImGui::Begin(WINDOW_ENGINE_PROPERTIES, nullptr, dockFloatWindow)) {
    }
    ImGui::End();
}