#include "BackEnd.hpp"
#include "Logger.hpp"

namespace Albikar::render::vulkan {
CBackEnd::CBackEnd(std::shared_ptr<Albikar::engine::CEngineProperties> engineProperties)
{
    m_Instance = std::make_shared<CVulkanInstance>(engineProperties);
}

CBackEnd::~CBackEnd()
{
}

auto CBackEnd::Init() -> ALBIKAR_RETURN
{
    if (m_Instance->Init() != ALBIKAR_SUCCESS) {
        LOG_ERROR("Cannot create Instance");
    }
    return ALBIKAR_SUCCESS;
}

auto CBackEnd::CleanUp() -> ALBIKAR_RETURN
{
    m_Instance->Destroy();
    return ALBIKAR_SUCCESS;
}

auto CBackEnd::OnResize(const uint16_t newWidth, const uint16_t newHeight) -> ALBIKAR_RETURN
{
    return ALBIKAR_SUCCESS;
}

auto CBackEnd::BeginFrame(const float deltaTime) -> ALBIKAR_RETURN
{
    return ALBIKAR_SUCCESS;
}

auto CBackEnd::EndFrame(const float deltaTime) -> ALBIKAR_RETURN
{
    return ALBIKAR_SUCCESS;
}

} // namespace Albikar::render::vulkan