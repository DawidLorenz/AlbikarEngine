#include "AlbikarGui.hpp"
#include "imgui.h"

namespace AlbikarGui {
void SearchWidget(const char* const widgetName, const char* const hintName, char* buf)
{
    ImGui::InputTextWithHint(widgetName, hintName, buf, sizeof(buf) * 20);
}
} // namespace AlbikarGui