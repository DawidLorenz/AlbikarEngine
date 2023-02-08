#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define PLATFORM_WINDOWS
#elif __APPLE__
#define PLATFORM_APPLE
#elif __ANDROID__
// Below __linux__ check should be enough to handle Android,
// but something may be unique to Android.
#elif __linux__
#define PLATFORM_LINUX
#elif __unix__ // all unices not caught above
#define PLATFORM_LINUX
#elif defined(_POSIX_VERSION)
// POSIX
#else
#error "Unknown compiler"
#endif

namespace PLATFORM {

} // namespace PLATFORM