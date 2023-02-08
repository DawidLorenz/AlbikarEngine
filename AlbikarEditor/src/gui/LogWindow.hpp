#pragma once
#include "IWindowObject.hpp"
#include "imgui.h"
class CLogInfo;

class CLogWindow final : public IWindowObject {
    WINDOW_OBJECT(CLogWindow)
public:
    CLogWindow();
    ~CLogWindow() final;

    auto Render() -> void final;

private:
    void PrintLog(const CLogInfo& log);
    void SaveToFile();

private:
    bool m_bAutoScroll;
    bool m_bShowFile;
    bool m_bShowFunction;
    bool m_bSaveToFile;
    bool m_bCheckWarn;
    bool m_bCheckCritical;
    bool m_bCheckInfo;
    bool m_bCheckError;
    bool m_bCheckLine;

    int m_iComboCurrentItem;

    ImGuiTextFilter m_sFilter;
};