#include "GLWindowEngine.hpp"
#include <stdexcept>

#pragma warning(disable : 4702)

auto CGLWindowEngine::CreateWindow() -> GLFWwindow*
{
    throw std::runtime_error("OpenGL not implemented");
}

auto CGLWindowEngine::IsWindowsClosed() -> bool
{
    throw std::runtime_error("OpenGL not implemented");
    return true;
}

auto CGLWindowEngine::NewFrame() -> bool
{
    throw std::runtime_error("OpenGL not implemented");
    return true;
}

auto CGLWindowEngine::Render([[maybe_unused]] ImDrawData* imguiDrawData) -> bool
{
    throw std::runtime_error("OpenGL not implemented");
    return true;
}

auto CGLWindowEngine::Cleanup() -> bool
{
    throw std::runtime_error("OpenGL not implemented");
    return true;
}