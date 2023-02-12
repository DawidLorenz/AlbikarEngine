#pragma once

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define ALBIKAR_PLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define ALBIKAR_PLATFORM_LINUX 1
#if defined(__ANDROID__)
#define ALBIKAR_PLATFORM_ANDROID 1
#endif
#elif defined(__unix__)
// Catch anything not caught by the above.
#define ALBIKAR_PLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#define ALBIKAR_PLATFORM_POSIX 1
#elif __APPLE__
// Apple platforms
#define ALBIKAR_PLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define ALBIKAR_PLATFORM_IOS 1
#define ALBIKAR_PLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define ALBIKAR_PLATFORM_IOS 1
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif

#ifdef ALBIKAR_EXPORT
// Exports
#ifdef _MSC_VER
#define ALBIKAR_API __declspec(dllexport)
#else
#define ALBIKAR_API __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
/** @brief Import/export qualifier */
#define ALBIKAR_API __declspec(dllimport)
#else
/** @brief Import/export qualifier */
#define ALBIKAR_API
#endif
#endif

#include <cstdint>
#include <functional>
#include <memory>

#define ALBIKAR_INTERFACE(...)                                  \
    __VA_ARGS__() = default;                                    \
    virtual ~__VA_ARGS__() = default;                           \
    __VA_ARGS__(const __VA_ARGS__&) = default;                  \
    __VA_ARGS__(__VA_ARGS__&&) = default;                       \
    auto operator=(const __VA_ARGS__&)->__VA_ARGS__& = default; \
    auto operator=(__VA_ARGS__&&)->__VA_ARGS__& = default;

using ALBIKAR_RETURN = uint16_t;
constexpr ALBIKAR_RETURN ALBIKAR_SUCCESS = 0;
constexpr ALBIKAR_RETURN ALBIKAR_FAILURE = 1;

using NotifyOnChange = std::function<void()>;