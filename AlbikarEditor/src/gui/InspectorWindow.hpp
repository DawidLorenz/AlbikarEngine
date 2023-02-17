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
    auto RenderGeneral() const -> void;
    auto RenderTranslate() const -> void;
    auto RenderPhysicalBox() const -> void;
    auto RenderShading() -> void;
};