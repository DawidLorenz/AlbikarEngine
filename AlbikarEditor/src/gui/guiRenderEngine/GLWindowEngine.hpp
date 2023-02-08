#pragma once
#include "IWindowEngine.hpp"

class CGLWindowEngine final : public IWindowEngine {
public:
    CGLWindowEngine() = default;
    ~CGLWindowEngine() = default;
    explicit CGLWindowEngine(const CGLWindowEngine&) = delete;
    explicit CGLWindowEngine(CGLWindowEngine&&) = delete;
    auto operator=(const CGLWindowEngine&) -> CGLWindowEngine& = delete;
    auto operator=(const CGLWindowEngine&&) -> CGLWindowEngine& = delete;

    auto CreateWindow() -> GLFWwindow* final;
    auto IsWindowsClosed() -> bool final;
    auto NewFrame() -> bool final;
    auto Render(ImDrawData* imguiDrawData) -> bool final;
    auto Cleanup() -> bool final;
};