#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"

#define WINDOW_OBJECT(...)                                     \
    explicit __VA_ARGS__(const __VA_ARGS__&) = delete;         \
    explicit __VA_ARGS__(__VA_ARGS__&&) = delete;              \
    auto operator=(const __VA_ARGS__&)->__VA_ARGS__& = delete; \
    auto operator=(const __VA_ARGS__&&)->__VA_ARGS__& = delete;

class IWindowObject {
    WINDOW_OBJECT(IWindowObject)
public:
    IWindowObject() = default;
    virtual ~IWindowObject() = default;
    virtual void Render() = 0;

public:
    bool m_Open = true;

public:
    static const ImGuiDockNodeFlags dockNoMoveWindow = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    static const ImGuiDockNodeFlags dockMainWindow = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    static const ImGuiDockNodeFlags dockFloatWindow = ImGuiWindowFlags_NoCollapse;
    static const ImGuiDockNodeFlags dockTopBardWindow = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_DockNodeHost | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
};