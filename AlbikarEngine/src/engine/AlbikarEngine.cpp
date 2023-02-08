#include "AlbikarEngine.hpp"

namespace engine {
auto AlbikarEngine::InitEngine(const uint16_t resolutionWidth, const uint16_t resolutionHeight, const char* gameName, const bool fixedResolution) -> ALBIKAR_RETURN
{

    return ALBIKAR_SUCCESS;
}

auto AlbikarEngine::Start() -> ALBIKAR_RETURN
{
    return ALBIKAR_SUCCESS;
}

auto AlbikarEngine::Terminate() -> ALBIKAR_RETURN
{
    StopEngine();
    return ALBIKAR_SUCCESS;
}

AlbikarEngine::~AlbikarEngine()
{
    StopEngine();
}

AlbikarEngine::AlbikarEngine()
{
    StartEngine();
}

auto AlbikarEngine::StartEngine() -> bool
{
    m_Window = std::make_shared<window::CAlbikarWindow>();
    m_Render = std::make_shared<render::CAlbikarRenderer>();
    m_Debug = std::make_shared<debug::CAlbikarDebug>();
    return true;
}

auto AlbikarEngine::StopEngine() -> bool
{
    coreEngine.reset();
    coreEngine = nullptr;
    return true;
}

} // namespace engine