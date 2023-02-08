#pragma once
#include "ApplicationArgs.hpp"
#include "ApplicationInfo.hpp"
#include "IWindowEngine.hpp"
#include "MainWindow.hpp"
#include "Project.hpp"
#include <GLFW/glfw3.h>
#include <memory>

class CApplication final {
public:
    static auto Get() -> CApplication&;
    static auto CreateApp(CApplicationInfo appInfo) -> CApplication&;

public:
    auto Start() -> void;
    auto Stop() -> void;
    auto Minimized() -> void;
    auto FullScrean() -> void;

    auto AutoSave() -> bool&;

    auto CreateProject(const std::string projectPath, const std::string projectName, const std::string projectDescription) -> bool;

private:
    auto SetAppInfo(CApplicationInfo& appInfo) -> void;
    auto CreateGuiRenderEngine() -> void;
    auto CreateMainWindow() -> void;

private:
    explicit CApplication();
    ~CApplication() = default;

public:
    explicit CApplication(const CApplication&) = delete;
    explicit CApplication(CApplication&&) = delete;
    auto operator=(const CApplication&) -> CApplication& = delete;
    auto operator=(const CApplication&&) -> CApplication& = delete;

private:
    auto GetAppName() -> std::string;

private:
    std::unique_ptr<IWindowEngine> m_WindowEngine;
    std::unique_ptr<CApplicationInfo> m_AppInfo;
    std::unique_ptr<CProject> m_Project;
    std::unique_ptr<CMainWindow> m_MainWindow;
    GLFWwindow* m_GlfwWindow = { nullptr };
    bool m_Running = { false };
    bool m_Minimized = { false };
    bool m_FullScrean = { false };
    bool m_AutoSave = { false };
};