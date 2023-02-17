#include "GameViewWindow.hpp"
#include "Preferences.hpp"
#include "Profiler.hpp"

auto CGameViewWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("CGameViewWindow::Render");
    if (ImGui::Begin(WINDOW_GAME_VIEW, nullptr, dockFloatWindow)) {
        ImGui::BeginChild("GameRender");
        ImVec2 wsize = ImGui::GetWindowSize();
        ImGuiIO& io = ImGui::GetIO(); // TODO(dlorenz) get buffer form engine
        ImTextureID my_tex_id = io.Fonts->TexID; // TODO(dlorenz) get buffer form engine
        ImGui::Image(my_tex_id, wsize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }
    ImGui::End();
}