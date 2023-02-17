#include "TopBarWindowDebug.hpp"
#include "imgui_internal.h"

namespace { // TODO(dlorenz) create class to handle multi languages
const char* const NAME_TOPBAR_DEBUG = "Debug";

const char* const NAME_TOPBAR_STYLE_EDITOR = "Style Editor";
const char* const NAME_TOPBAR_DEMO_WINDOW = "Demo Window";
const char* const NAME_TOPBAR_DEBUG_LOG = "IMG Gui Debug Log";
const char* const NAME_TOPBAR_STACK_WINDOW = "Stack Window";
const char* const NAME_TOPBAR_SHOW_WINDOW_REC = "Show windows rectangles";
} // namespace

CTopBarWindowDebug::CTopBarWindowDebug()
    : m_bShowDemoWindow(false)
    , m_bShowStyleEditor(false)
    , m_bShowIMGUIDebugLog(false)
    , m_bShowStackToolWindow(false)
{
}

auto CTopBarWindowDebug::Render() -> void
{
    ImGuiContext& g = *GImGui;
    ImGuiMetricsConfig* cfg = &g.DebugMetricsConfig;

    if (ImGui::BeginMenu(NAME_TOPBAR_DEBUG)) {

        if (ImGui::MenuItem(NAME_TOPBAR_STYLE_EDITOR, nullptr, m_bShowStyleEditor)) {
            m_bShowStyleEditor = true;
        }
        if (ImGui::MenuItem(NAME_TOPBAR_DEMO_WINDOW, nullptr, m_bShowDemoWindow)) {
            m_bShowDemoWindow = true;
        }

        ImGui::Separator();

        if (ImGui::MenuItem(NAME_TOPBAR_DEBUG_LOG, nullptr, m_bShowIMGUIDebugLog)) {
            m_bShowIMGUIDebugLog = true;
        }
        if (ImGui::MenuItem(NAME_TOPBAR_STACK_WINDOW, nullptr, m_bShowStackToolWindow)) {
            m_bShowStackToolWindow = true;
        }
        if (ImGui::MenuItem(NAME_TOPBAR_SHOW_WINDOW_REC, nullptr, &cfg->ShowWindowsRects)) {
            cfg->ShowWindowsRectsType = 4;
        }

        ImGui::EndMenu();
    }

    RenderStyleEditor();
    RenderDemoWindow();
    RenderDebugLog();
    RenderStackTool();
    RenderDebugWindowRect();
}

auto CTopBarWindowDebug::RenderStyleEditor() -> void
{
    if (m_bShowStyleEditor) {
        ImGui::Begin("Dear ImGui Style Editor", &m_bShowStyleEditor);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }
}

auto CTopBarWindowDebug::RenderDemoWindow() -> void
{
    if (m_bShowDemoWindow) {
        ImGui::ShowDemoWindow(&m_bShowDemoWindow);
    }
}

auto CTopBarWindowDebug::RenderDebugLog() -> void
{
    if (m_bShowIMGUIDebugLog) {
        ImGui::ShowDebugLogWindow(&m_bShowIMGUIDebugLog);
    }
}

auto CTopBarWindowDebug::RenderStackTool() -> void
{
    if (m_bShowStackToolWindow) {
        ImGui::ShowStackToolWindow(&m_bShowStackToolWindow);
    }
}

auto CTopBarWindowDebug::RenderDebugWindowRect() -> void
{
    ImGuiContext& g = *GImGui;
    ImGuiMetricsConfig* cfg = &g.DebugMetricsConfig;

    if (cfg->ShowWindowsRects) {
        for (int n = 0; n < g.Windows.Size; n++) {
            ImGuiWindow* window = g.Windows[n];
            if (!window->WasActive) {
                continue;
            }
            ImDrawList* draw_list = ImGui::GetForegroundDrawList(window);
            if (cfg->ShowWindowsRects) {
                ImRect r = window->WorkRect;
                draw_list->AddRect(r.Min, r.Max, IM_COL32(255, 0, 128, 255));
            }
            if (cfg->ShowWindowsBeginOrder && ((window->Flags & ImGuiWindowFlags_ChildWindow) == 0)) {
                char buf[32];
                ImFormatString(buf, IM_ARRAYSIZE(buf), "%d", window->BeginOrderWithinContext);
                float font_size = ImGui::GetFontSize();
                draw_list->AddRectFilled(window->Pos, window->Pos + ImVec2(font_size, font_size), IM_COL32(200, 100, 100, 255));
                draw_list->AddText(window->Pos, IM_COL32(255, 255, 255, 255), buf);
            }
        }
    }
}
