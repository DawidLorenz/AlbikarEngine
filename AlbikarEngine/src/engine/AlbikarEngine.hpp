#pragma once
#include "AlbikarDebug.hpp"
#include "AlbikarRenderer.hpp"
#include "AlbikarWindow.hpp"
#include "IAlbikarEngine.hpp"
#include <glm/glm.hpp>
#pragma warning(disable : 4273)

namespace Albikar::engine {
class AlbikarEngine final : public AlbikarAPI::IAlbikarEngine {
public:
    // INTERFACE
    auto InitEngine(const uint16_t resolutionWidth, const uint16_t resolutionHeight, const char* gameName, const bool fixedResolution) -> ALBIKAR_RETURN final;
    auto Start() -> ALBIKAR_RETURN final;
    auto Terminate() -> ALBIKAR_RETURN final;
    auto AlbikarWindow() -> std::shared_ptr<AlbikarAPI::IAlbikarWindow> final;
    auto AlbikarDebug() -> std::shared_ptr<AlbikarAPI::IAlbikarDebug> final;

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

} // namespace Albikar::engine

auto Albikar::AlbikarAPI::CreateEngine() -> std::shared_ptr<Albikar::AlbikarAPI::IAlbikarEngine>
{
    if (Albikar::engine::coreEngine != nullptr) {
        Albikar::engine::coreEngine.reset();
        Albikar::engine::coreEngine = nullptr;
    }
    Albikar::engine::coreEngine = std::make_shared<Albikar::engine::AlbikarEngine>();
    return Albikar::engine::coreEngine;
}