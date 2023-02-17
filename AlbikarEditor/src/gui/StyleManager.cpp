#include "StyleManager.hpp"
#include "imgui_internal.h"
#include <algorithm>

auto CStyleManager::Get() -> CStyleManager&
{
    static CStyleManager style;
    return style;
}

auto CStyleManager::GetStylesName() -> std::vector<std::string>
{
    std::vector<std::string> styles;
    styles.reserve(constStyles.size());
    for (auto& constStyle : constStyles) {
        styles.emplace_back(constStyle.GetName());
    }
    return styles;
}

auto CStyleManager::SetActiveStyle(std::string styleName) -> void
{
    auto i = std::find_if(constStyles.begin(),
        constStyles.end(),
        [&](auto& val) { return val.GetName() == styleName; });
    if (i != constStyles.end()) {
        (*i).Active();
        m_sCurrentStyleName = styleName;
    }
}

auto CStyleManager::ActiveCurrentStyle() -> void
{
    SetActiveStyle(m_sCurrentStyleName);
}

auto CStyleManager::GetCurrentStyle() -> ImGuiStyle
{
    auto i = std::find_if(constStyles.begin(),
        constStyles.end(),
        [&](auto& val) { return val.GetName() == m_sCurrentStyleName; });
    return (*i).GetStyle();
}

CStyleManager::CStyleManager()
{
    InitConstStyles();
    SetActiveStyle("Albikar");
}

void CStyleManager::InitConstStyles()
{
    ImGuiStyle styleBlack;
    ImVec4* colorsBlack = styleBlack.Colors;
    styleBlack.WindowBorderSize = 0.0f;
    styleBlack.WindowPadding = { 2.0, 2.0 };
    styleBlack.CellPadding.y = 0;
    styleBlack.ItemSpacing = { 4, 2 };
    styleBlack.IndentSpacing = 10;
    styleBlack.ScrollbarSize = 10;
    colorsBlack[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colorsBlack[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colorsBlack[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    colorsBlack[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsBlack[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colorsBlack[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colorsBlack[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsBlack[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
    colorsBlack[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    colorsBlack[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colorsBlack[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colorsBlack[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
    colorsBlack[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colorsBlack[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colorsBlack[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colorsBlack[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colorsBlack[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colorsBlack[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colorsBlack[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colorsBlack[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
    colorsBlack[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colorsBlack[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    colorsBlack[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colorsBlack[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    colorsBlack[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    colorsBlack[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colorsBlack[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colorsBlack[ImGuiCol_Separator] = colorsBlack[ImGuiCol_Border];
    colorsBlack[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colorsBlack[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colorsBlack[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
    colorsBlack[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colorsBlack[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colorsBlack[ImGuiCol_Tab] = ImLerp(colorsBlack[ImGuiCol_Header], colorsBlack[ImGuiCol_TitleBgActive], 0.80f);
    colorsBlack[ImGuiCol_TabHovered] = colorsBlack[ImGuiCol_HeaderHovered];
    colorsBlack[ImGuiCol_TabActive] = ImLerp(colorsBlack[ImGuiCol_HeaderActive], colorsBlack[ImGuiCol_TitleBgActive], 0.60f);
    colorsBlack[ImGuiCol_TabUnfocused] = ImLerp(colorsBlack[ImGuiCol_Tab], colorsBlack[ImGuiCol_TitleBg], 0.80f);
    colorsBlack[ImGuiCol_TabUnfocusedActive] = ImLerp(colorsBlack[ImGuiCol_TabActive], colorsBlack[ImGuiCol_TitleBg], 0.40f);
    // TODO(dlorenz) colorsBlack[ImGuiCol_DockingPreview] = colorsBlack[ImGuiCol_HeaderActive] * ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
    colorsBlack[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colorsBlack[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colorsBlack[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colorsBlack[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colorsBlack[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colorsBlack[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colorsBlack[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f); // Prefer using Alpha=1.0 here
    colorsBlack[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f); // Prefer using Alpha=1.0 here
    colorsBlack[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsBlack[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colorsBlack[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colorsBlack[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colorsBlack[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colorsBlack[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colorsBlack[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colorsBlack[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    styleBlack.WindowMenuButtonPosition = -1;
    styleBlack.ChildBorderSize = 0;
    styleBlack.PopupBorderSize = 0;
    Style black("Black", styleBlack);

    ImGuiStyle styleWhite;
    ImVec4* colorsWhite = styleWhite.Colors;
    styleWhite.WindowBorderSize = 0.0f;
    styleWhite.WindowBorderSize = 0.0f;
    styleWhite.WindowPadding = { 2.0, 2.0 };
    styleWhite.CellPadding.y = 0;
    styleWhite.ItemSpacing = { 4, 2 };
    styleWhite.IndentSpacing = 10;
    styleWhite.ScrollbarSize = 10;
    colorsWhite[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colorsWhite[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colorsWhite[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colorsWhite[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsWhite[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
    colorsWhite[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
    colorsWhite[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsWhite[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colorsWhite[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    colorsWhite[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colorsWhite[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colorsWhite[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    colorsWhite[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
    colorsWhite[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colorsWhite[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    colorsWhite[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
    colorsWhite[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
    colorsWhite[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    colorsWhite[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colorsWhite[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    colorsWhite[ImGuiCol_SliderGrabActive] = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
    colorsWhite[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    colorsWhite[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colorsWhite[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    colorsWhite[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    colorsWhite[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colorsWhite[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colorsWhite[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
    colorsWhite[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
    colorsWhite[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
    colorsWhite[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.35f, 0.35f, 0.17f);
    colorsWhite[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colorsWhite[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colorsWhite[ImGuiCol_Tab] = ImLerp(colorsWhite[ImGuiCol_Header], colorsWhite[ImGuiCol_TitleBgActive], 0.90f);
    colorsWhite[ImGuiCol_TabHovered] = colorsWhite[ImGuiCol_HeaderHovered];
    colorsWhite[ImGuiCol_TabActive] = ImLerp(colorsWhite[ImGuiCol_HeaderActive], colorsWhite[ImGuiCol_TitleBgActive], 0.60f);
    colorsWhite[ImGuiCol_TabUnfocused] = ImLerp(colorsWhite[ImGuiCol_Tab], colorsWhite[ImGuiCol_TitleBg], 0.80f);
    colorsWhite[ImGuiCol_TabUnfocusedActive] = ImLerp(colorsWhite[ImGuiCol_TabActive], colorsWhite[ImGuiCol_TitleBg], 0.40f);
    // TODO(dlorenz) colorsWhite[ImGuiCol_DockingPreview] = colorsWhite[ImGuiCol_Header] * ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
    colorsWhite[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colorsWhite[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colorsWhite[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colorsWhite[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colorsWhite[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
    colorsWhite[ImGuiCol_TableHeaderBg] = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
    colorsWhite[ImGuiCol_TableBorderStrong] = ImVec4(0.57f, 0.57f, 0.64f, 1.00f); // Prefer using Alpha=1.0 here
    colorsWhite[ImGuiCol_TableBorderLight] = ImVec4(0.68f, 0.68f, 0.74f, 1.00f); // Prefer using Alpha=1.0 here
    colorsWhite[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsWhite[ImGuiCol_TableRowBgAlt] = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
    colorsWhite[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colorsWhite[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colorsWhite[ImGuiCol_NavHighlight] = colorsWhite[ImGuiCol_HeaderHovered];
    colorsWhite[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
    colorsWhite[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
    colorsWhite[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    styleWhite.WindowMenuButtonPosition = -1;
    styleWhite.ChildBorderSize = 0;
    styleWhite.PopupBorderSize = 0;
    Style white("White", styleWhite);

    ImGuiStyle styleClassic;
    ImVec4* colorsClassic = styleClassic.Colors;
    styleClassic.WindowBorderSize = 0.0f;
    styleClassic.WindowBorderSize = 0.0f;
    styleClassic.WindowBorderSize = 0.0f;
    styleClassic.WindowBorderSize = 0.0f;
    styleClassic.WindowPadding = { 2.0, 2.0 };
    styleClassic.CellPadding.y = 0;
    styleClassic.ItemSpacing = { 4, 2 };
    styleClassic.IndentSpacing = 10;
    styleClassic.ScrollbarSize = 10;
    colorsClassic[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colorsClassic[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colorsClassic[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.85f);
    colorsClassic[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsClassic[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
    colorsClassic[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
    colorsClassic[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsClassic[ImGuiCol_FrameBg] = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
    colorsClassic[ImGuiCol_FrameBgHovered] = ImVec4(0.47f, 0.47f, 0.69f, 0.40f);
    colorsClassic[ImGuiCol_FrameBgActive] = ImVec4(0.42f, 0.41f, 0.64f, 0.69f);
    colorsClassic[ImGuiCol_TitleBg] = ImVec4(0.27f, 0.27f, 0.54f, 0.83f);
    colorsClassic[ImGuiCol_TitleBgActive] = ImVec4(0.32f, 0.32f, 0.63f, 0.87f);
    colorsClassic[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    colorsClassic[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
    colorsClassic[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    colorsClassic[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
    colorsClassic[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
    colorsClassic[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
    colorsClassic[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
    colorsClassic[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
    colorsClassic[ImGuiCol_SliderGrabActive] = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
    colorsClassic[ImGuiCol_Button] = ImVec4(0.35f, 0.40f, 0.61f, 0.62f);
    colorsClassic[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.48f, 0.71f, 0.79f);
    colorsClassic[ImGuiCol_ButtonActive] = ImVec4(0.46f, 0.54f, 0.80f, 1.00f);
    colorsClassic[ImGuiCol_Header] = ImVec4(0.40f, 0.40f, 0.90f, 0.45f);
    colorsClassic[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
    colorsClassic[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
    colorsClassic[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
    colorsClassic[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
    colorsClassic[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.70f, 0.90f, 1.00f);
    colorsClassic[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
    colorsClassic[ImGuiCol_ResizeGripHovered] = ImVec4(0.78f, 0.82f, 1.00f, 0.60f);
    colorsClassic[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.82f, 1.00f, 0.90f);
    colorsClassic[ImGuiCol_Tab] = ImLerp(colorsClassic[ImGuiCol_Header], colorsClassic[ImGuiCol_TitleBgActive], 0.80f);
    colorsClassic[ImGuiCol_TabHovered] = colorsClassic[ImGuiCol_HeaderHovered];
    colorsClassic[ImGuiCol_TabActive] = ImLerp(colorsClassic[ImGuiCol_HeaderActive], colorsClassic[ImGuiCol_TitleBgActive], 0.60f);
    colorsClassic[ImGuiCol_TabUnfocused] = ImLerp(colorsClassic[ImGuiCol_Tab], colorsClassic[ImGuiCol_TitleBg], 0.80f);
    colorsClassic[ImGuiCol_TabUnfocusedActive] = ImLerp(colorsClassic[ImGuiCol_TabActive], colorsClassic[ImGuiCol_TitleBg], 0.40f);
    // TODO(dlorenz) colorsClassic[ImGuiCol_DockingPreview] = colorsClassic[ImGuiCol_Header] * ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
    colorsClassic[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colorsClassic[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colorsClassic[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colorsClassic[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colorsClassic[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colorsClassic[ImGuiCol_TableHeaderBg] = ImVec4(0.27f, 0.27f, 0.38f, 1.00f);
    colorsClassic[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.45f, 1.00f); // Prefer using Alpha=1.0 here
    colorsClassic[ImGuiCol_TableBorderLight] = ImVec4(0.26f, 0.26f, 0.28f, 1.00f); // Prefer using Alpha=1.0 here
    colorsClassic[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsClassic[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
    colorsClassic[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    colorsClassic[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colorsClassic[ImGuiCol_NavHighlight] = colorsClassic[ImGuiCol_HeaderHovered];
    colorsClassic[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colorsClassic[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colorsClassic[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    styleClassic.WindowMenuButtonPosition = -1;
    styleClassic.ChildBorderSize = 0;
    styleClassic.PopupBorderSize = 0;
    Style classic("Classic", styleClassic);

    ImGuiStyle styleAlbikar;
    ImVec4* colorsAlbikar = styleAlbikar.Colors;
    styleAlbikar.WindowBorderSize = 0.0f;
    styleAlbikar.WindowPadding = { 2.0, 2.0 };
    styleAlbikar.CellPadding.y = 0;
    styleAlbikar.ItemSpacing = { 4, 2 };
    styleAlbikar.IndentSpacing = 10;
    styleAlbikar.ScrollbarSize = 10;

    colorsAlbikar[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colorsAlbikar[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colorsAlbikar[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    colorsAlbikar[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    colorsAlbikar[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    colorsAlbikar[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colorsAlbikar[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsAlbikar[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colorsAlbikar[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colorsAlbikar[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    colorsAlbikar[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    colorsAlbikar[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    colorsAlbikar[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colorsAlbikar[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colorsAlbikar[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colorsAlbikar[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colorsAlbikar[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colorsAlbikar[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colorsAlbikar[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    colorsAlbikar[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    colorsAlbikar[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
    colorsAlbikar[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colorsAlbikar[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colorsAlbikar[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    colorsAlbikar[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colorsAlbikar[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colorsAlbikar[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    colorsAlbikar[ImGuiCol_Separator] = colorsAlbikar[ImGuiCol_Border];
    colorsAlbikar[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
    colorsAlbikar[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colorsAlbikar[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colorsAlbikar[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
    colorsAlbikar[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colorsAlbikar[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
    colorsAlbikar[ImGuiCol_TabHovered] = ImVec4(0.996096F, 0.335932F, 0.01569F, 1.0F);
    colorsAlbikar[ImGuiCol_TabActive] = ImVec4(0.996096F, 0.335932F, 0.01569F, 1.0F);
    colorsAlbikar[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    colorsAlbikar[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    colorsAlbikar[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
    colorsAlbikar[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colorsAlbikar[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colorsAlbikar[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colorsAlbikar[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colorsAlbikar[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colorsAlbikar[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colorsAlbikar[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    colorsAlbikar[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colorsAlbikar[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colorsAlbikar[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colorsAlbikar[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    colorsAlbikar[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colorsAlbikar[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colorsAlbikar[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colorsAlbikar[ImGuiCol_SliderGrabActive] = ImVec4(0.996096F, 0.335932F, 0.01569F, 1.0F);
    colorsAlbikar[ImGuiCol_SeparatorActive] = ImVec4(0.996096F, 0.335932F, 0.01569F, 1.0F);
    colorsAlbikar[ImGuiCol_ResizeGripActive] = ImVec4(0.996096F, 0.335932F, 0.01569F, 1.0F);
    colorsAlbikar[ImGuiCol_DockingPreview] = ImVec4(0.996096F, 0.335932F, 0.01569F, 1.0F);

    styleAlbikar.WindowMenuButtonPosition = -1;
    styleAlbikar.ChildBorderSize = 0;
    styleAlbikar.PopupBorderSize = 1;
    Style albikar("Albikar", styleAlbikar);

    constStyles.emplace_back(albikar);
    constStyles.emplace_back(black);
    constStyles.emplace_back(white);
    constStyles.emplace_back(classic);
}