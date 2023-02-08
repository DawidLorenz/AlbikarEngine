#include "InspectorWindow.hpp"
#include "Preferences.hpp"
#include "Profiler.hpp"
#include "StyleManager.hpp"

// TODO(dlorenz) clean plz
static ImGuiTableFlags flags = ImGuiTableFlags_None;
static const float width = 73.0F;
static const float widthTextBox = 250.0F;
static const float widthNumberBox = 60.0F;
static float f1 = 1.00f;

namespace { // TODO(dlorenz) create class to handle multi languages
const char* const NAME_INSP_GENERAL_TAB = "General";
const char* const NAME_INSP_TRANSLATE_TAB = "Translate";
const char* const NAME_INSP_PHY_TAB = "Physical Box";
const char* const NAME_INSP_SHAD_TAB = "Shading";
} // namespace

CInspectorWindow::CInspectorWindow()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4 c = style.Colors[ImGuiCol_Header];
    m_iColorForTable = ImGui::GetColorU32(c);
}

auto CInspectorWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("CInspectorWindow::Render");
    // Different style only for Inspector
    ImGuiStyle currentStyle = CStyleManager::Get().GetCurrentStyle();
    currentStyle.WindowPadding = { 0, 0 };
    currentStyle.ItemSpacing.y = 0;
    ImGuiStyle* dst = &ImGui::GetStyle();
    *dst = currentStyle;
    ImVec4 c = currentStyle.Colors[ImGuiCol_Header];
    m_iColorForTable = ImGui::GetColorU32(c);

    if (ImGui::Begin(WINDOW_INSPECTOR, nullptr, dockFloatWindow)) {
        RenderGeneral();
        RenderTranslate();
        RenderPhysicalBox();
        RenderShading();
    }
    CStyleManager::Get().ActiveCurrentStyle();
    ImGui::End();
}

auto CInspectorWindow::RenderGeneral() -> void
{
    if (ImGui::CollapsingHeader(NAME_INSP_GENERAL_TAB, ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::BeginTable("##General", 2, flags)) {
            ImGui::TableSetupColumn("##Type", ImGuiTableColumnFlags_WidthFixed, width);
            ImGui::TableSetupColumn("##Label", ImGuiTableColumnFlags_NoHide);

            // Type
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Type");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("Ractangle");

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Active");
            ImGui::TableSetColumnIndex(1);
            static int e = 0;
            ImGui::RadioButton("##Active", &e, 0);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Name");
            ImGui::TableSetColumnIndex(1);
            static char buf1[64] = "";
            ImGui::SetNextItemWidth(widthTextBox);
            ImGui::InputText("##Name", buf1, 64);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Tags");
            ImGui::TableSetColumnIndex(1);
            static char buf2[64] = "";
            ImGui::SetNextItemWidth(widthTextBox);
            ImGui::InputText("##Tags", buf2, 64);

            ImGui::EndTable();
        }
    }
}

auto CInspectorWindow::RenderTranslate() -> void
{
    if (ImGui::CollapsingHeader(NAME_INSP_TRANSLATE_TAB, ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::BeginTable("##Translate", 2, flags)) {
            ImGui::TableSetupColumn("##Type", ImGuiTableColumnFlags_WidthFixed, width);
            ImGui::TableSetupColumn("##Label", ImGuiTableColumnFlags_NoHide);
            // Position
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Position");
            ImGui::TableSetColumnIndex(1);
            ImGui::PushID(0);
            ImGui::PushStyleColor(ImGuiCol_Button, COLOR_RED_DARK);
            ImGui::Button("X");
            ImGui::PopStyleColor(1);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::SetNextItemWidth(widthNumberBox);
            ImGui::DragFloat("##X", &f1, 0.005f);
            ImGui::SameLine();

            ImGui::PushID(1);
            ImGui::PushStyleColor(ImGuiCol_Button, COLOR_GREEN_DARK);
            ImGui::Button("Y");
            ImGui::PopStyleColor(1);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::SetNextItemWidth(widthNumberBox);
            ImGui::DragFloat("##Y", &f1, 0.005f);
            ImGui::SameLine();

            ImGui::PushID(2);
            ImGui::PushStyleColor(ImGuiCol_Button, COLOR_BLUE_DARK);
            ImGui::Button("Z");
            ImGui::PopStyleColor(1);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::SetNextItemWidth(widthNumberBox);
            ImGui::DragFloat("##Z", &f1, 0.005f);
            ImGui::SameLine();

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Scale");
            ImGui::TableSetColumnIndex(1);
            ImGui::PushID(0);
            ImGui::PushStyleColor(ImGuiCol_Button, COLOR_RED_DARK);
            ImGui::Button("X");
            ImGui::PopStyleColor(1);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::SetNextItemWidth(widthNumberBox);
            ImGui::DragFloat("##X", &f1, 0.005f);
            ImGui::SameLine();

            ImGui::PushID(1);
            ImGui::PushStyleColor(ImGuiCol_Button, COLOR_GREEN_DARK);
            ImGui::Button("Y");
            ImGui::PopStyleColor(1);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::SetNextItemWidth(widthNumberBox);
            ImGui::DragFloat("##Y", &f1, 0.005f);
            ImGui::SameLine();

            ImGui::PushID(2);
            ImGui::PushStyleColor(ImGuiCol_Button, COLOR_BLUE_DARK);
            ImGui::Button("Z");
            ImGui::PopStyleColor(1);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::SetNextItemWidth(widthNumberBox);
            ImGui::DragFloat("##Z", &f1, 0.005f);
            ImGui::SameLine();

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Rotation");
            ImGui::TableSetColumnIndex(1);
            ImGui::PushID(0);
            ImGui::PushStyleColor(ImGuiCol_Button, COLOR_RED_DARK);
            ImGui::Button("X");
            ImGui::PopStyleColor(1);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::SetNextItemWidth(widthNumberBox);
            ImGui::DragFloat("##X", &f1, 0.005f);
            ImGui::SameLine();

            ImGui::PushID(1);
            ImGui::PushStyleColor(ImGuiCol_Button, COLOR_GREEN_DARK);
            ImGui::Button("Y");
            ImGui::PopStyleColor(1);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::SetNextItemWidth(widthNumberBox);
            ImGui::DragFloat("##Y", &f1, 0.005f);
            ImGui::SameLine();

            ImGui::PushID(2);
            ImGui::PushStyleColor(ImGuiCol_Button, COLOR_BLUE_DARK);
            ImGui::Button("Z");
            ImGui::PopStyleColor(1);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::SetNextItemWidth(widthNumberBox);
            ImGui::DragFloat("##Z", &f1, 0.005f);
            ImGui::SameLine();

            ImGui::EndTable();
        }
    }
}

auto CInspectorWindow::RenderPhysicalBox() -> void
{
    if (ImGui::CollapsingHeader(NAME_INSP_PHY_TAB, ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::BeginTable("##PhysicalBox", 2, flags)) {
            ImGui::TableSetupColumn("##Type", ImGuiTableColumnFlags_WidthFixed, width);
            ImGui::TableSetupColumn("##Label", ImGuiTableColumnFlags_NoHide);

            // Type
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Active");
            ImGui::TableSetColumnIndex(1);
            static int e = 0;
            ImGui::RadioButton("##Active", &e, 0);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Kinematic");
            ImGui::TableSetColumnIndex(1);
            static int ex = 0;
            ImGui::RadioButton("##Kinematic", &ex, 0);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Mass");
            ImGui::TableSetColumnIndex(1);
            static char buf1[64] = "";
            ImGui::SetNextItemWidth(widthTextBox);
            ImGui::InputText("##Name", buf1, 64);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, m_iColorForTable);
            ImGui::Text("  Bounciness");
            ImGui::TableSetColumnIndex(1);
            static char buf2[64] = "";
            ImGui::SetNextItemWidth(widthTextBox);
            ImGui::InputText("##Tags", buf2, 64);

            ImGui::EndTable();
        }
    }
}

auto CInspectorWindow::RenderShading() -> void
{
    if (ImGui::CollapsingHeader(NAME_INSP_SHAD_TAB, ImGuiTreeNodeFlags_DefaultOpen)) {
    }
}
