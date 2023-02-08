#include "MonitorsWindow.hpp"
#include "Preferences.hpp"
#include "Profiler.hpp"

auto CMonitorsWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("CMonitorsWindow::Render");
    if (ImGui::Begin(WINDOW_MONITORS, nullptr, dockFloatWindow)) {
    }
    ImGui::End();
}