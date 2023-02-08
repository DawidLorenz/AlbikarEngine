#pragma once
#include "IWindowEngine.hpp"
#include "imgui_impl_vulkan.h"
#include <vulkan/vulkan.h>
#define IMGUI_UNLIMITED_FRAME_RATE

class CVKWindowEngine final : public IWindowEngine {
public:
    CVKWindowEngine();
    ~CVKWindowEngine() final;
    explicit CVKWindowEngine(const CVKWindowEngine&) = delete;
    explicit CVKWindowEngine(CVKWindowEngine&&) = delete;
    auto operator=(const CVKWindowEngine&) -> CVKWindowEngine& = delete;
    auto operator=(const CVKWindowEngine&&) -> CVKWindowEngine& = delete;

    auto CreateWindow() -> GLFWwindow* final;
    auto IsWindowsClosed() -> bool final;
    auto NewFrame() -> bool final;
    auto Render(ImDrawData* imguiDrawData) -> bool final;
    auto Cleanup() -> bool final;

private:
    VkInstance m_vkInstance;
    VkAllocationCallbacks* m_vkAllocator;
    ImGui_ImplVulkanH_Window m_imguiMainWindowData;
    GLFWwindow* m_glfwWindow;

private:
    auto SetupVulkan(const char** extensions, unsigned int extensions_count) -> void;
    auto FrameRender(ImDrawData* imguiDrawData) -> void;
    auto FramePresent() -> void;

    // VULKAN
    auto vkSetupWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height) -> void;
    static auto vkCheckResult(VkResult err) -> void;

    // GLFW
    static auto glfwErrorCallback(int error, const char* description) -> void;
};