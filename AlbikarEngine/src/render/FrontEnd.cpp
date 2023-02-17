#include "FrontEnd.hpp"
#include "vulkan/BackEnd.hpp"
namespace Albikar::render {
CFrontEnd::CFrontEnd(const char* gameName, const uint16_t newWidth, const uint16_t newHeight, const std::shared_ptr<Albikar::engine::CEngineProperties>& engineProperties)
{
    m_BackEnd = std::make_unique<Albikar::render::vulkan::CBackEnd>(engineProperties);
}

auto CFrontEnd::Init() -> ALBIKAR_RETURN
{
    ALBIKAR_RETURN AlbReturn = m_BackEnd->Init();
    if (AlbReturn != ALBIKAR_SUCCESS) {
        return AlbReturn;
    }
    return AlbReturn;
}

auto CFrontEnd::OnResize(const uint16_t newWidth, const uint16_t newHeight) -> ALBIKAR_RETURN
{
    ALBIKAR_RETURN AlbReturn = m_BackEnd->OnResize(newWidth, newHeight);
    if (AlbReturn != ALBIKAR_SUCCESS) {
        return AlbReturn;
    }
    return AlbReturn;
}

auto CFrontEnd::OnDrawFrame() -> ALBIKAR_RETURN
{
    ALBIKAR_RETURN AlbReturn = ALBIKAR_SUCCESS;
    if (AlbReturn != ALBIKAR_SUCCESS) {
        return AlbReturn;
    }
    return AlbReturn;
}

auto CFrontEnd::CleanUp() -> ALBIKAR_RETURN
{
    ALBIKAR_RETURN AlbReturn = m_BackEnd->CleanUp();
    if (AlbReturn != ALBIKAR_SUCCESS) {
        return AlbReturn;
    }
    return AlbReturn;
}

auto CFrontEnd::BegineFrame(const float deltaTime) -> ALBIKAR_RETURN
{
    ALBIKAR_RETURN AlbReturn = m_BackEnd->BeginFrame(deltaTime);
    if (AlbReturn != ALBIKAR_SUCCESS) {
        return AlbReturn;
    }
    return AlbReturn;
}

auto CFrontEnd::EndFrame(const float deltaTime) -> ALBIKAR_RETURN
{
    ALBIKAR_RETURN AlbReturn = m_BackEnd->EndFrame(deltaTime);
    if (AlbReturn != ALBIKAR_SUCCESS) {
        return AlbReturn;
    }
    return AlbReturn;
}

} // namespace Albikar::render