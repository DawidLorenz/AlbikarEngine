#pragma once
#include "IAlbikarWindow.hpp"
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Albikar::window {
class CAlbikarWindow final : public AlbikarAPI::IAlbikarWindow {
public:
    CAlbikarWindow() = default;
    ~CAlbikarWindow() final;
    CAlbikarWindow(const CAlbikarWindow&) = default;
    CAlbikarWindow(CAlbikarWindow&&) = default;
    auto operator=(const CAlbikarWindow&) -> CAlbikarWindow& = default;
    auto operator=(CAlbikarWindow&&) -> CAlbikarWindow& = default;

    auto CreateWindow(const uint32_t& i_ResolutionWidth, const uint32_t& i_ResolutionHeight, const char* i_GameName, const bool i_DynamicResolution) -> GLFWwindow*;
    auto GetWindow() -> GLFWwindow*;

private:
    GLFWwindow* m_GLFWWindow;
};
} // namespace Albikar::window