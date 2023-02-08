#include "GLWindowEngine.hpp"
#pragma warning(disable : 4702)

auto CGLWindowEngine::CreateWindow() -> GLFWwindow*
{
    throw "OpenGL not implemented";
}

auto CGLWindowEngine::IsWindowsClosed() -> bool
{
    throw "OpenGL not implemented";
    return true;
}

auto CGLWindowEngine::NewFrame() -> bool
{
    throw "OpenGL not implemented";
    return true;
}

auto CGLWindowEngine::Render([[maybe_unused]] ImDrawData* imguiDrawData) -> bool
{
    throw "OpenGL not implemented";
    return true;
}

auto CGLWindowEngine::Cleanup() -> bool
{
    throw "OpenGL not implemented";
    return true;
}