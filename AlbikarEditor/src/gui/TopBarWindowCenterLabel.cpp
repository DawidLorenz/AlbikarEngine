#include "TopBarWindowCenterLabel.hpp"
#include "Application.hpp"
#include <string>

auto CTopBarWindowCenterLabel::Render() -> void
{
    // std::string text = APP_NAME;
    // if (CApplication::Get().GetProject().use_count()) {
    //     text = CApplication::Get().GetProject().lock()->GetProjectName();
    //     text += " - ";
    //     text += APP_NAME;
    // }

    // auto windowWidth = ImGui::GetWindowSize().x;
    // auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

    // ImGui::AlignTextToFramePadding();
    // ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    // ImGui::Text("%s", text.c_str());

    // textWidth = 400;
    // ImGui::AlignTextToFramePadding();
    // ImGui::SetCursorPosX((windowWidth - textWidth) - 20.0f);
    // ImGui::Text("Albikar %.3f ms/frame (%.1f FPS) Mouse Position: (%.1f,%.1f)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate, ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
}