#pragma once
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include "AlbikarDefines.hpp"
#include "EngineProperties.hpp"
#include "FrontEnd.hpp"
#include <GLFW/glfw3.h>

namespace Albikar::render {
class CAlbikarRenderer final {
public:
    // INTERFACE
public:
    CAlbikarRenderer();
    ~CAlbikarRenderer();
    CAlbikarRenderer(const CAlbikarRenderer&) = default;
    CAlbikarRenderer(CAlbikarRenderer&&) = default;
    auto operator=(const CAlbikarRenderer&) -> CAlbikarRenderer& = default;
    auto operator=(CAlbikarRenderer&&) -> CAlbikarRenderer& = default;

    auto Init(GLFWwindow* window, const uint16_t resolutionWidth, const uint16_t resolutionHeight, const char* gameName, const std::shared_ptr<Albikar::engine::CEngineProperties>& engineProperties) -> ALBIKAR_RETURN;
    auto OnResize(const uint16_t newWidth, const uint16_t newHeight) -> ALBIKAR_RETURN;
    auto OnDrawFrame() -> ALBIKAR_RETURN;
    auto CleanUp() -> ALBIKAR_RETURN;

private:
    std::weak_ptr<Albikar::engine::CEngineProperties> m_EngineProperties;
    std::shared_ptr<CFrontEnd> m_FrontEnd;

private:
    GLFWwindow* m_Window;
    uint64_t m_CurrentFrame;
};
} // namespace Albikar::render