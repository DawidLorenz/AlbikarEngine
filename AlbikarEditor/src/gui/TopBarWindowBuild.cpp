#include "TopBarWindowBuild.hpp"

namespace { // TODO(dlorenz) create class to handle multi languages
const char* const NAME_TOPBAR_BUILD = "Build";
} // namespace

auto CTopBarWindowBuild::Render() -> void
{
    if (ImGui::BeginMenu(NAME_TOPBAR_BUILD)) {
        ImGui::EndMenu();
    }
}