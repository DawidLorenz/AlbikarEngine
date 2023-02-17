#include "AlbikarRenderer.hpp"
#include "Logger.hpp"
#include <stdexcept>

namespace Albikar::render {
CAlbikarRenderer::CAlbikarRenderer()
    : m_Window(nullptr)
    , m_CurrentFrame(0)
{
}

CAlbikarRenderer::~CAlbikarRenderer()
{
    CleanUp();
}

auto CAlbikarRenderer::Init(GLFWwindow* window, const uint16_t resolutionWidth, const uint16_t resolutionHeight, const char* gameName, const std::shared_ptr<Albikar::engine::CEngineProperties>& engineProperties) -> ALBIKAR_RETURN
{
    LOG_INFO("Init width: ", resolutionWidth, " height: ", resolutionHeight, " GameName: ", gameName);
    if (window == nullptr) {
        std::runtime_error("Failed to create Render Engine");
    }
    m_FrontEnd = std::make_shared<CFrontEnd>(gameName, resolutionWidth, resolutionHeight, engineProperties);

    ALBIKAR_RETURN AlbReturn = m_FrontEnd->Init();
    if (AlbReturn != ALBIKAR_SUCCESS) {
        return AlbReturn;
    }
    return AlbReturn;
}

auto CAlbikarRenderer::OnResize(const uint16_t newWidth, const uint16_t newHeight) -> ALBIKAR_RETURN
{
    LOG_INFO("OnResize width: ", newWidth, " height: ", newHeight);
    ALBIKAR_RETURN AlbReturn = m_FrontEnd->OnResize(newWidth, newHeight);
    if (AlbReturn != ALBIKAR_SUCCESS) {
        return AlbReturn;
    }
    return AlbReturn;
}

auto CAlbikarRenderer::OnDrawFrame() -> ALBIKAR_RETURN
{
    LOG_INFO("DrawFrame");
    ALBIKAR_RETURN AlbReturn = m_FrontEnd->OnDrawFrame();
    if (AlbReturn != ALBIKAR_SUCCESS) {
        return AlbReturn;
    }
    return AlbReturn;
}

auto CAlbikarRenderer::CleanUp() -> ALBIKAR_RETURN
{
    LOG_INFO("CleanUp");
    ALBIKAR_RETURN AlbReturn = m_FrontEnd->CleanUp();
    if (AlbReturn != ALBIKAR_SUCCESS) {
        return AlbReturn;
    }
    return AlbReturn;
}

} // namespace Albikar::render