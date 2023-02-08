#include "TopBarWindowView.hpp"

namespace { // TODO(dlorenz) create class to handle multi languages
const char* const NAME_TOPBAR_VIEW = "View";
} // namespace

auto CTopBarWindowView::Render() -> void
{
    if (ImGui::BeginMenu(NAME_TOPBAR_VIEW)) {
        ImGui::EndMenu();
    }
}