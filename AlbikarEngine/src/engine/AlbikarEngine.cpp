#include "AlbikarEngine.hpp"
#include "Defines.hpp"

namespace Albikar::engine {
auto AlbikarEngine::InitEngine(const uint16_t resolutionWidth, const uint16_t resolutionHeight, const char* gameName, const bool fixedResolution) -> ALBIKAR_RETURN
{
    LOG_INFO("Init Engine res(", resolutionWidth, "/", resolutionHeight, ") GameName: ", gameName, " FixedRes: ", fixedResolution);
    GLFWwindow* window = m_Window->CreateWindow(resolutionWidth, resolutionHeight, gameName, fixedResolution);
    if (window == nullptr) {
        throw std::runtime_error("Failed to create Window");
    }

    if (m_Render->Init(window, resolutionWidth, resolutionHeight, gameName, m_Debug->EngineProperties()) != ALBIKAR_SUCCESS) {
        throw std::runtime_error("Failed to create Render Engine");
    }

    return ALBIKAR_SUCCESS;
}

auto AlbikarEngine::Start() -> ALBIKAR_RETURN
{
    // TODO(dlorenz) Render Loop
    return ALBIKAR_SUCCESS;
}

auto AlbikarEngine::Terminate() -> ALBIKAR_RETURN
{
    StopEngine();
    return ALBIKAR_SUCCESS;
}

auto AlbikarEngine::AlbikarWindow() -> std::shared_ptr<AlbikarAPI::IAlbikarWindow>
{
    return m_Window;
}

auto AlbikarEngine::AlbikarDebug() -> std::shared_ptr<AlbikarAPI::IAlbikarDebug>
{
    return m_Debug;
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

} // namespace Albikar::engine