#pragma once
#include "imgui.h"
#include <string>
#include <utility>
#include <vector>

class Style;

class CStyleManager {
public:
    static auto Get() -> CStyleManager&;

public:
    auto GetStylesName() -> std::vector<std::string>;
    auto SetActiveStyle(std::string styleName) -> void;
    auto ActiveCurrentStyle() -> void;
    auto GetCurrentStyle() -> ImGuiStyle;

    explicit CStyleManager(const CStyleManager&) = delete;
    explicit CStyleManager(CStyleManager&&) = delete;
    auto operator=(const CStyleManager&) -> CStyleManager& = delete;
    auto operator=(const CStyleManager&&) -> CStyleManager& = delete;

private:
    CStyleManager();
    ~CStyleManager() = default;

private:
    std::vector<Style> constStyles;
    void InitConstStyles();
    std::string m_sCurrentStyleName;
};

class Style {
public:
    Style(std::string name, ImGuiStyle style)
        : m_StyleName(std::move(name))
        , m_Style(style)
    {
    }

    auto GetName() -> std::string
    {
        return m_StyleName;
    }

    void Active()
    {
        ImGuiStyle* dst = &ImGui::GetStyle();
        *dst = m_Style;
    }

    auto GetStyle() -> ImGuiStyle
    {
        return m_Style;
    }

private:
    std::string m_StyleName;
    ImGuiStyle m_Style;
};