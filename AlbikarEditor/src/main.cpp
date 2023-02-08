#include "Application.hpp"
#include "Logger.hpp"
#include "Platform.hpp"
#include "Profiler.hpp"

#include <exception>

auto main(int argc, char** argv) -> int
{
    ALB_PROFILE_BEGIN_SESSION("AlbikarApplication", "AlbikarApplication.json");

    CApplication& app = CApplication::CreateApp({ { argc, argv } });
    try {
        app.Start();
    } catch (const std::exception& e) {
        LOG_CRITICAL(e.what());
        ALB_PROFILE_END_SESSION();
        return static_cast<int>(false);
    }

    ALB_PROFILE_END_SESSION();
    return static_cast<int>(true);
}