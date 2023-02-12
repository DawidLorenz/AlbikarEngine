#pragma once
#include "AlbikarDefines.hpp"
#include "EngineProperties.hpp"
#include "IBackEnd.hpp"

namespace Albikar::render {
class CFrontEnd final {
public:
    CFrontEnd(const char* gameName, const uint16_t newWidth, const uint16_t newHeight, std::shared_ptr<Albikar::engine::CEngineProperties> engineProperties);
    ~CFrontEnd();
    auto Init() -> ALBIKAR_RETURN;
    auto OnResize(const uint16_t newWidth, const uint16_t newHeight) -> ALBIKAR_RETURN;
    auto OnDrawFrame() -> ALBIKAR_RETURN;
    auto CleanUp() -> ALBIKAR_RETURN;

private:
    auto BegineFrame(const float deltaTime) -> ALBIKAR_RETURN;
    auto EndFrame(const float deltaTime) -> ALBIKAR_RETURN;

private:
    std::unique_ptr<IBackEnd> m_BackEnd;
};

} // namespace Albikar::render