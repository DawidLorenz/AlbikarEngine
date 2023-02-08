#pragma once
#include "AlbikarDebug.hpp"
#include "AlbikarRenderer.hpp"
#include "AlbikarWindow.hpp"
#include "IAlbikarEngine.hpp"
#include <glm/glm.hpp>

namespace engine {
class AlbikarEngine final : public AlbikarAPI::IAlbikarEngine {
public:
    // INTERFACE
    [[nodiscard]] auto InitEngine(const uint16_t resolutionWidth, const uint16_t resolutionHeight, const char* gameName, const bool fixedResolution) -> ALBIKAR_RETURN final;
    [[nodiscard]] auto Start() -> ALBIKAR_RETURN final;
    [[nodiscard]] auto Terminate() -> ALBIKAR_RETURN final;

public:
    ~AlbikarEngine() final;
    AlbikarEngine();

private:
    auto StartEngine() -> bool;
    auto StopEngine() -> bool;

private:
    std::shared_ptr<window::CAlbikarWindow> m_Window;
    std::shared_ptr<render::CAlbikarRenderer> m_Render;
    std::shared_ptr<debug::CAlbikarDebug> m_Debug;
};

std::shared_ptr<AlbikarEngine> coreEngine = nullptr;

} // namespace engine

auto AlbikarAPI::CreateEngine() -> std::shared_ptr<AlbikarAPI::IAlbikarEngine>
{
    if (engine::coreEngine != nullptr) {
        engine::coreEngine.reset();
        engine::coreEngine = nullptr;
    }
    engine::coreEngine = std::make_shared<engine::AlbikarEngine>();
    return engine::coreEngine;
}