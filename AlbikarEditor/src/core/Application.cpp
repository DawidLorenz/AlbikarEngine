#include "Application.hpp"
#include "ApplicationInfo.hpp"
#include "Logger.hpp"
#include "VKWindowEngine.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

auto CApplication::Get() -> CApplication&
{
    static CApplication app;
    return app;
}

auto CApplication::CreateApp(CApplicationInfo appInfo) -> CApplication&
{
    LOG_INFO("Create Application");
    CApplication& app = CApplication::Get();
    app.SetAppInfo(appInfo);
    return app;
}

auto CApplication::Start() -> void
{
    LOG_INFO("Start Application");
    m_Running = true;
    while (m_Running && m_WindowEngine->IsWindowsClosed()) {
        // Create Frame
        m_WindowEngine->NewFrame();

        // Render
        m_MainWindow->Render();
        m_WindowEngine->Render(ImGui::GetDrawData());
    }

    m_WindowEngine->Cleanup();
}

auto CApplication::Stop() -> void
{
    LOG_INFO("Stop Application");
    m_Running = false;
}

auto CApplication::Minimized() -> void
{
    LOG_INFO("Minimized Application");
    m_Minimized = true;
}

auto CApplication::AutoSave() -> bool&
{
    return m_AutoSave;
}

auto CApplication::CreateProject(const std::string projectPath, const std::string projectName, const std::string projectDescription) -> bool
{
    if (m_Project != nullptr) {
        m_Project->CloseProject();
        m_Project.release();
        m_Project = nullptr;
    }

    m_Project = std::make_unique<CProject>(projectPath, projectName, projectDescription);
    m_Project->StartProject();
    return true;
}

auto CApplication::FullScrean() -> void
{
    LOG_INFO("FullScrean Application");
    m_FullScrean = true;
}

auto CApplication::SetAppInfo(CApplicationInfo& appInfo) -> void
{
    m_AppInfo = std::make_unique<CApplicationInfo>(appInfo);
    if (m_GlfwWindow != nullptr) {
        glfwSetWindowTitle(m_GlfwWindow, m_AppInfo->GetName().c_str());
    }
}

auto CApplication::CreateGuiRenderEngine() -> void
{
    m_WindowEngine = std::make_unique<CVKWindowEngine>();
    if (m_WindowEngine == nullptr) {
        throw "Cannot create WindowEngine";
    }

    // Create Window
    m_GlfwWindow = m_WindowEngine->CreateWindow();
    if (m_GlfwWindow == nullptr) {
        throw "Cannot create GLFW Window";
    }
}

auto CApplication::CreateMainWindow() -> void
{
    if (m_GlfwWindow == nullptr) {
        return;
    }

    GLFWmonitor* mainMonitor = glfwGetPrimaryMonitor();
    if (mainMonitor == nullptr) {
        return;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(mainMonitor);
    if (mode == nullptr) {
        return;
    }

    // Resize width and height
    glfwSetWindowSize(m_GlfwWindow, mode->width, mode->height);

    // Rename
    glfwSetWindowTitle(m_GlfwWindow, GetAppName().c_str());
}

CApplication::CApplication()
    : m_WindowEngine(nullptr)
    , m_AppInfo(nullptr)
    , m_Project(nullptr)
    , m_MainWindow(nullptr)

{
    CreateGuiRenderEngine();
    CreateMainWindow();

    m_MainWindow = std::make_unique<CMainWindow>();
}

auto CApplication::GetAppName() -> std::string
{
    if (m_AppInfo) {
        return m_AppInfo->GetName();
    }
    return "NoName";
}