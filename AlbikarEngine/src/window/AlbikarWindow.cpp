#include "AlbikarWindow.hpp"
#include "Logger.hpp"

namespace Albikar::window {
CAlbikarWindow::~CAlbikarWindow()
{
    LOG_INFO("Destroy Albikar Window");
    glfwDestroyWindow(m_GLFWWindow);
}

auto CAlbikarWindow::CreateWindow(const uint32_t& i_ResolutionWidth, const uint32_t& i_ResolutionHeight, const char* i_GameName, const bool i_DynamicResolution) -> GLFWwindow*
{
    LOG_INFO("Create Albikar Window");

    // Initialise GLFW
    glfwInit();

    // Set GLFW to NOT work with OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_GLFWWindow = glfwCreateWindow(static_cast<int>(i_ResolutionWidth), static_cast<int>(i_ResolutionHeight), i_GameName, nullptr, nullptr);
    return m_GLFWWindow;
}

auto CAlbikarWindow::GetWindow() -> GLFWwindow*
{
    return m_GLFWWindow;
}
} // namespace Albikar::window