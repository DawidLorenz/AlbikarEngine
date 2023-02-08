#include "TopBarWindowEdit.hpp"

namespace { // TODO(dlorenz) create class to handle multi languages
const char* const NAME_TOPBAR_EDIT = "Edit";
const char* const NAME_TOPBAR_UNDO = "Undo";
const char* const NAME_TOPBAR_UNDO_SHORT_CUT = "CTRL+Z";
const char* const NAME_TOPBAR_REDO = "Redo";
const char* const NAME_TOPBAR_REDO_SHORT_CUT = "CTRL+Y";
const char* const NAME_TOPBAR_COPY = "Copy";
const char* const NAME_TOPBAR_COPY_SHORT_CUT = "CTRL+C";
const char* const NAME_TOPBAR_CUT = "Cut";
const char* const NAME_TOPBAR_CUT_SHORT_CUT = "CTRL+X";
const char* const NAME_TOPBAR_PASTE = "Paste";
const char* const NAME_TOPBAR_PASTE_SHORT_CUT = "CTRL+V";
const char* const NAME_TOPBAR_FIND = "Find";
} // namespace

auto CTopBarWindowEdit::Render() -> void
{
    if (ImGui::BeginMenu(NAME_TOPBAR_EDIT)) {
        if (ImGui::MenuItem(NAME_TOPBAR_UNDO, NAME_TOPBAR_UNDO_SHORT_CUT)) { }
        if (ImGui::MenuItem(NAME_TOPBAR_REDO, NAME_TOPBAR_REDO_SHORT_CUT)) { }

        ImGui::Separator();

        if (ImGui::MenuItem(NAME_TOPBAR_CUT, NAME_TOPBAR_CUT_SHORT_CUT)) { }
        if (ImGui::MenuItem(NAME_TOPBAR_COPY, NAME_TOPBAR_COPY_SHORT_CUT)) { }
        if (ImGui::MenuItem(NAME_TOPBAR_PASTE, NAME_TOPBAR_PASTE_SHORT_CUT)) { }

        ImGui::Separator();

        if (ImGui::MenuItem(NAME_TOPBAR_FIND)) { }
        ImGui::EndMenu();
    }
}