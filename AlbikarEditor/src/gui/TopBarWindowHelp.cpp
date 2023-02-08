#include "TopBarWindowHelp.hpp"
#include "Logger.hpp"
#include "Preferences.hpp"
#include <fstream>
#include <sstream>

namespace { // TODO(dlorenz) create class to handle multi languages
const char* const NAME_TOPBAR_HELP = "Help";
const char* const NAME_TOPBAR_DOCUMENTATION = "Documentation";
const char* const NAME_TOPBAR_RELEASE_NOTES = "Release Notes";
const char* const NAME_TOPBAR_RELEASE_NOTES_FILE = "ReleaseNotes";
const char* const NAME_TOPBAR_KEYBOARD_SHORTCUTS = "Keyboard Shortcuts";
const char* const NAME_TOPBAR_TIPS = "Tips and Tricks";
const char* const NAME_TOPBAR_VIEW_LICENSE = "View License";
const char* const NAME_TOPBAR_ENGINE_INFO = "Engine Info";
const char* const NAME_TOPBAR_WINDOW_VIEW_LICENSE = "License";
const char* const NAME_TOPBAR_VIEW_LICENSE_FILE = "LICENSE";
const char* const NAME_TOPBAR_VIEW_ABOUT_ALBIKAR = "About Albikar";
const char* const NAME_TOPBAR_VIEW_ABOUT_ALBIKAR_ENGINE = "About Albikar Engine";
} // namespace

CTopBarWindowHelp::CTopBarWindowHelp() noexcept
    : m_bShowDocumentation(false)
    , m_bShowReleaseNotes(false)
    , m_bShowKeyboardShortcuts(false)
    , m_bShowTipsAndTricks(false)
    , m_bShowViewLicense(false)
    , m_bShowEngineInfo(true)
    , m_bShowAboutAlbikar(false)
    , m_bShowAboutAlbikarEngine(false)
    , m_sReleaseNotes()
    , m_sLicense()
{
}

auto CTopBarWindowHelp::Render() -> void
{
    if (ImGui::BeginMenu(NAME_TOPBAR_HELP)) {
        if (ImGui::MenuItem(NAME_TOPBAR_DOCUMENTATION, nullptr, &m_bShowDocumentation)) {
            LOG_INFO("Documentation Item Press");
        }
        if (ImGui::MenuItem(NAME_TOPBAR_RELEASE_NOTES, nullptr, &m_bShowReleaseNotes)) {
            LOG_INFO("Release Item Press");
            m_sLicense = "";
            std::ifstream t(NAME_TOPBAR_RELEASE_NOTES_FILE);
            std::stringstream buffer;
            buffer << t.rdbuf();
            m_sReleaseNotes = buffer.str();
        }

        ImGui::Separator();

        if (ImGui::MenuItem(NAME_TOPBAR_KEYBOARD_SHORTCUTS, nullptr, &m_bShowKeyboardShortcuts)) {
            LOG_INFO("Short Cut Item Press");
        }
        if (ImGui::MenuItem(NAME_TOPBAR_TIPS, nullptr, &m_bShowTipsAndTricks)) {
            LOG_INFO("Tips and Tricks Item Press");
        }

        ImGui::Separator();

        if (ImGui::MenuItem(NAME_TOPBAR_VIEW_LICENSE, nullptr, &m_bShowViewLicense)) {
            LOG_INFO("License Item Press");
            m_sLicense = "";
            std::ifstream t(NAME_TOPBAR_VIEW_LICENSE_FILE);
            std::stringstream buffer;
            buffer << t.rdbuf();
            m_sLicense = buffer.str();
        }

        ImGui::Separator();

        if (ImGui::MenuItem(NAME_TOPBAR_ENGINE_INFO, nullptr, &m_bShowEngineInfo)) {
        }

        ImGui::Separator();

        if (ImGui::MenuItem(NAME_TOPBAR_VIEW_ABOUT_ALBIKAR, nullptr, &m_bShowAboutAlbikar)) {
            LOG_INFO("About Albikar Item Press");
        }
        if (ImGui::MenuItem(NAME_TOPBAR_VIEW_ABOUT_ALBIKAR_ENGINE, nullptr, &m_bShowAboutAlbikarEngine)) {
            LOG_INFO("About Albikar Engine Item Press");
        }

        ImGui::EndMenu();
    }

    RenderDocumentation();
    RenderReleaseNotes();
    RenderKeyboardShortcuts();
    RenderTipsAndTricks();
    RenderViewLicense();
    RenderEngineInfo();
    RenderAboutAlbikar();
    RenderAboutAlbikarEngine();
}

auto CTopBarWindowHelp::RenderDocumentation() -> void
{
    if (!m_bShowDocumentation) {
        return;
    }
}

auto CTopBarWindowHelp::RenderReleaseNotes() -> void
{
    if (!m_bShowReleaseNotes) {
        return;
    }

    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, CENTER_VEC);
    if (!ImGui::Begin(NAME_TOPBAR_RELEASE_NOTES, &m_bShowReleaseNotes)) {
        ImGui::End();
        return;
    }

    ImGui::Text("%s", m_sReleaseNotes.c_str());
    ImGui::End();
}

auto CTopBarWindowHelp::RenderKeyboardShortcuts() -> void
{
    if (!m_bShowKeyboardShortcuts) {
        return;
    }
}

auto CTopBarWindowHelp::RenderTipsAndTricks() -> void
{
    if (!m_bShowTipsAndTricks) {
        return;
    }
}

auto CTopBarWindowHelp::RenderViewLicense() -> void
{
    if (!m_bShowViewLicense) {
        return;
    }

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, CENTER_VEC);
    if (!ImGui::Begin(NAME_TOPBAR_WINDOW_VIEW_LICENSE, &m_bShowViewLicense)) {
        ImGui::End();
        return;
    }

    ImGui::Text("%s", m_sLicense.c_str());
    ImGui::End();
}

auto CTopBarWindowHelp::RenderEngineInfo() -> void
{
    if (!m_bShowEngineInfo) {
        return;
    }

    if (!ImGui::Begin(NAME_TOPBAR_ENGINE_INFO, &m_bShowEngineInfo)) {
    }
    ImGui::End();
}

auto CTopBarWindowHelp::RenderAboutAlbikar() -> void
{
    if (!m_bShowAboutAlbikar) {
        return;
    }

    if (!ImGui::Begin(NAME_TOPBAR_VIEW_ABOUT_ALBIKAR, &m_bShowAboutAlbikar, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    }

    ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
    ImGui::Separator();
    ImGui::Text("By Omar Cornut and all Dear ImGui contributors.");
    ImGui::Text("Dear ImGui is licensed under the MIT License, see LICENSE for more information.");

    static bool show_config_info = false;
    ImGui::Checkbox("Config", &show_config_info);
    if (show_config_info) {
    }

    ImGui::End();
}

auto CTopBarWindowHelp::RenderAboutAlbikarEngine() -> void
{
    if (!m_bShowAboutAlbikarEngine) {
        return;
    }
}