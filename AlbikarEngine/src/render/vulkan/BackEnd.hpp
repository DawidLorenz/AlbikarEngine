#pragma once
#include "EngineProperties.hpp"
#include "IBackEnd.hpp"
#include "Instance.hpp"

namespace Albikar::render::vulkan {
class CBackEnd final : public Albikar::render::IBackEnd {
public:
    CBackEnd(std::shared_ptr<Albikar::engine::CEngineProperties> engineProperties);
    ~CBackEnd() final;
    auto Init() -> ALBIKAR_RETURN final;
    auto CleanUp() -> ALBIKAR_RETURN final;
    auto OnResize(const uint16_t newWidth, const uint16_t newHeight) -> ALBIKAR_RETURN final;
    auto BeginFrame(const float deltaTime) -> ALBIKAR_RETURN final;
    auto EndFrame(const float deltaTime) -> ALBIKAR_RETURN final;

private:
    std::shared_ptr<CInstance> m_Instance;
};
} // namespace Albikar::render::vulkan
