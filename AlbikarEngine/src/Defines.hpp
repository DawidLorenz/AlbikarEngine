#pragma once
#include "AlbikarDefines.hpp"
#include "Logger.hpp"
#include <stdexcept>

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

// ALBIKAR ENGINE