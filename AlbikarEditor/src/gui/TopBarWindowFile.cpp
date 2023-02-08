#include "TopBarWindowFile.hpp"
#include "Application.hpp"
#include "Logger.hpp"
#include "StyleManager.hpp"
#include <algorithm>
#include <filesystem>
namespace fs = std::filesystem;

namespace { // TODO(dlorenz) create class to handle multi languages
const char* const NAME_TOPBAR = "File";
const char* const NAME_NEW_PROJECT = "New  Project...";
const char* const NAME_NEW_PROJECT_SHORT_CUT = "CTRL+N";
const char* const NAME_OPEN_PROJECT = "Open Project...";
const char* const NAME_OPEN_PROJECT_SHORT_CUT = "CTRL+O";
const char* const NAME_SAVE = "Save";
const char* const NAME_SAVE_SHORT_CUT = "CTRL+S";
const char* const NAME_SAVE_AS = "Save As...";
const char* const NAME_SAVE_AS_SHORT_CUT = "CTRL+Alt+S";
const char* const NAME_AUTO_SAVE = "Auto Save";
const char* const NAME_PREFERENCES = "Preferences";
const char* const NAME_STYLE = "Style";
const char* const NAME_STYLE_CB = "##Style";
const char* const NAME_LOCK_FPS = "Lock FPS (60fps)";
const char* const NAME_EXIT = "Exit";
const char* const NAME_EXIT_SHORT_CUT = "Alt+F4";
const char* const NAME_PROJECT_SETTINGS = "Project settings";
const char* const NAME_PROJECT_SETTINGS_NEW = "New project";
const char* const NAME_PROJECT_NAME = "Name";
const char* const NAME_PROJECT_NAME_TEXT = "##Name";
const char* const NAME_PROJECT_DESCRIPTION = "Description";
const char* const NAME_PROJECT_DESCRIPTION_TEXT = "##Description";
const char* const NAME_PROJECT_PATH_BUTTON = "Path";
const char* const NAME_PROJECT_PATH_TEXT = "Path: ";
const char* const NAME_PROJECT_CREATE = "Create";
const char* const NAME_PROJECT_CANCEL = "Cancel";
} // namespace

CTopBarWindowFile::CTopBarWindowFile()
    : m_bShowNewProject(false)
    , m_bShowOpenProject(false)
    , m_sProjectPath("")
{
}

auto CTopBarWindowFile::Render() -> void
{
    RenderNewProjectWindow();

    if (!ImGui::BeginMenu(NAME_TOPBAR)) {
        return;
    }

    if (ImGui::MenuItem(NAME_NEW_PROJECT, NAME_NEW_PROJECT_SHORT_CUT)) {
        LOG_INFO("Create new project");
        m_bShowNewProject = true;
    }
    if (ImGui::MenuItem(NAME_OPEN_PROJECT, NAME_OPEN_PROJECT_SHORT_CUT)) {
        LOG_INFO("Open project");
        m_bShowOpenProject = true;
    }

    ImGui::Separator();

    if (ImGui::MenuItem(NAME_SAVE, NAME_SAVE_SHORT_CUT)) {
        LOG_INFO("Save current project");
    }
    if (ImGui::MenuItem(NAME_SAVE_AS, NAME_SAVE_AS_SHORT_CUT)) {
        LOG_INFO("Save current project ass...");
    }

    ImGui::Separator();

    if (ImGui::MenuItem(NAME_AUTO_SAVE, nullptr, CApplication::Get().AutoSave())) {
        if (CApplication::Get().AutoSave()) {
            CApplication::Get().AutoSave() = false;
        } else {
            CApplication::Get().AutoSave() = true;
        }
    }
    if (ImGui::BeginMenu(NAME_PREFERENCES)) {
        static const float subMenuWidth { 100.0F };
        std::vector<std::string> styleName = CStyleManager::Get().GetStylesName();
        std::string styles;
        std::for_each(styleName.begin(), styleName.end(), [&](const std::string& piece) { styles += (piece + '\0'); });
        ImGui::Text(NAME_STYLE);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(subMenuWidth);
        static int style_idx { 0 };
        if (ImGui::Combo(NAME_STYLE_CB, &style_idx, styles.c_str())) {
            CStyleManager::Get().SetActiveStyle(styleName[style_idx]);
        }
        ImGui::SetNextItemWidth(subMenuWidth);
        static bool lockFps { false };
        if (ImGui::Checkbox(NAME_LOCK_FPS, &lockFps)) {
            LOG_CRITICAL("Not Implemented, add variable to Aplication class");
            // TODO(dlorenz) add implementation
        }
        ImGui::EndMenu();
    }

    ImGui::Separator();

    if (ImGui::MenuItem(NAME_EXIT, NAME_EXIT_SHORT_CUT)) {
        LOG_INFO("Exit Application");
        CApplication::Get().Stop();
    }
    ImGui::EndMenu();
}

auto CTopBarWindowFile::RenderNewProjectWindow() -> void
{
    static const float windowWidth = 500.0F;
    if (m_bShowNewProject) {
        ImGui::OpenPopup(NAME_PROJECT_SETTINGS_NEW);
        m_bShowNewProject = false;
    }

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, CENTER_VEC);
    if (ImGui::BeginPopupModal(NAME_PROJECT_SETTINGS_NEW, nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7, 4));

        ImGui::Text(NAME_PROJECT_NAME);
        // TODO(dlorenz) for Debug/Developers
        static char projectName[126] = "This is my Template project";
        ImGui::SetNextItemWidth(windowWidth);
        ImGui::InputText(NAME_PROJECT_NAME_TEXT, projectName, 126);

        ImGui::Separator();

        ImGui::Text(NAME_PROJECT_DESCRIPTION);
        static char description[126 * 5] = " ";
        static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
        ImGui::InputTextMultiline(NAME_PROJECT_DESCRIPTION_TEXT, description, IM_ARRAYSIZE(description), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 5), flags);

        ImGui::Separator();

        if (ImGui::Button(NAME_PROJECT_PATH_BUTTON, ImVec2(100, 0))) {
            LOG_CRITICAL("Not implemented, add new class FILESYSTEM to handle this button");
        }
        ImGui::SameLine();
        ImGui::Text(NAME_PROJECT_PATH_TEXT);
        ImGui::SameLine();
        ImGui::Text("%s", m_sProjectPath.c_str());
        ImGui::PopStyleVar();
        if (ImGui::Button(NAME_PROJECT_CREATE, ImVec2(245, 0))) {
            std::string stringProjectName = projectName;
            std::string stringProjectDescription = description;
            LOG_INFO("Create new project: ", stringProjectName);
            CApplication::Get().CreateProject(m_sProjectPath, stringProjectName, stringProjectDescription);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button(NAME_PROJECT_CANCEL, ImVec2(245, 0))) {
            ImGui::CloseCurrentPopup();
            LOG_INFO("Cancel new project");
        }

        ImGui::EndPopup();
    }
}