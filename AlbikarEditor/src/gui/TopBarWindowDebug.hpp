#pragma once
#include "IWindowObject.hpp"

class CTopBarWindowDebug final : public IWindowObject {
    WINDOW_OBJECT(CTopBarWindowDebug)
public:
    CTopBarWindowDebug();
    virtual ~CTopBarWindowDebug() = default;

    auto Render() -> void final;

private:
    auto RenderStyleEditor() -> void;
    auto RenderDemoWindow() -> void;
    auto RenderDebugLog() -> void;
    auto RenderStackTool() -> void;
    auto RenderDebugWindowRect() -> void;

private:
    bool m_bShowDemoWindow;
    bool m_bShowStyleEditor;
    bool m_bShowIMGUIDebugLog;
    bool m_bShowStackToolWindow;
};
