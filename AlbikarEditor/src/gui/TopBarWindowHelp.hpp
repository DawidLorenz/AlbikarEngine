#pragma once
#include "IWindowObject.hpp"
#include <string>

class CTopBarWindowHelp final : public IWindowObject {
    WINDOW_OBJECT(CTopBarWindowHelp)
public:
    CTopBarWindowHelp() noexcept;
    ~CTopBarWindowHelp() final = default;

    auto Render() -> void final;

private:
    auto RenderDocumentation() -> void;
    auto RenderReleaseNotes() -> void;
    auto RenderKeyboardShortcuts() -> void;
    auto RenderTipsAndTricks() -> void;
    auto RenderViewLicense() -> void;
    auto RenderEngineInfo() -> void;
    auto RenderAboutAlbikar() -> void;
    auto RenderAboutAlbikarEngine() -> void;

private:
    bool m_bShowDocumentation;
    bool m_bShowReleaseNotes;
    bool m_bShowKeyboardShortcuts;
    bool m_bShowTipsAndTricks;
    bool m_bShowViewLicense;
    bool m_bShowEngineInfo;
    bool m_bShowAboutAlbikar;
    bool m_bShowAboutAlbikarEngine;

    std::string m_sReleaseNotes;
    std::string m_sLicense;
};
