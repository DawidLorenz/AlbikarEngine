#pragma once
#include "AlbikarDefines.hpp"

// INCLUSED
// --VULKAN
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// -- ALBIKAR ENGINE
#include "Logger.hpp"
// -- Core

#include <stdexcept>
#include <tuple>

#define ALBIKAR_DEFAULT_CALSS(...)                             \
    __VA_ARGS__() = default;                                   \
    virtual ~__VA_ARGS__() = default;                          \
    __VA_ARGS__(const __VA_ARGS__&) = delete;                  \
    __VA_ARGS__(__VA_ARGS__&&) = delete;                       \
    auto operator=(const __VA_ARGS__&)->__VA_ARGS__& = delete; \
    auto operator=(__VA_ARGS__&&)->__VA_ARGS__& = delete;

// VULKAN
#define ALBIKAR_VK_CHECK(vkResult, throwInfo)    \
    do {                                         \
        VkResult err = vkResult;                 \
        if (err != VK_SUCCESS) {                 \
            LOG_CRITICAL(throwInfo);             \
            throw std::runtime_error(throwInfo); \
        }                                        \
    } while (0);

#define ALBIKAR_VK_MEMORY nullptr
// ALBIKAR ENGINE