#pragma once
#include "IWindowObject.hpp"

class CInspectorWindow final : public IWindowObject {
    WINDOW_OBJECT(CInspectorWindow)
public:
    CInspectorWindow();
    ~CInspectorWindow() final = default;

    auto Render() -> void final;

private:
    ImU32 m_iColorForTable;

private:
    auto RenderGeneral() -> void;
    auto RenderTranslate() -> void;
    auto RenderPhysicalBox() -> void;
    auto RenderShading() -> void;
};