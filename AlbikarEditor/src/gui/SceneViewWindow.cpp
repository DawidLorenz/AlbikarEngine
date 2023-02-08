#include "SceneViewWindow.hpp"
#include "Preferences.hpp"
#include "Profiler.hpp"

auto CSceneViewWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("CSceneViewWindow::Render");
    if (ImGui::Begin(WINDOW_SCENE_VIEW, nullptr, dockFloatWindow)) {
    }
    ImGui::End();
}