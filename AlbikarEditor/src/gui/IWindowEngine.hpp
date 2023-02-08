#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class IWindowEngine {
public:
    IWindowEngine() = default;
    virtual ~IWindowEngine() = default;
    explicit IWindowEngine(const IWindowEngine&) = delete;
    explicit IWindowEngine(IWindowEngine&&) = delete;
    auto operator=(const IWindowEngine&) -> IWindowEngine& = delete;
    auto operator=(const IWindowEngine&&) -> IWindowEngine& = delete;

    virtual auto CreateWindow() -> GLFWwindow* = 0;
    virtual auto IsWindowsClosed() -> bool = 0;
    virtual auto NewFrame() -> bool = 0;
    virtual auto Render(ImDrawData* imguiDrawData) -> bool = 0;
    virtual auto Cleanup() -> bool = 0;
};