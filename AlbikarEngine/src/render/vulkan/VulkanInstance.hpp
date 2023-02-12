#pragma once
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include "Defines.hpp"
#include "EngineProperties.hpp"
#include <GLFW/glfw3.h>

namespace Albikar::render::vulkan {
class CVulkanInstance final {
public:
    CVulkanInstance(std::shared_ptr<Albikar::engine::CEngineProperties> engineProperties);
    auto Init() -> ALBIKAR_RETURN;
    auto Destroy() -> ALBIKAR_RETURN;
    [[nodiscard]] auto GetInstance() -> VkInstance const;

private:
    // -- Support Functions
    auto checkValidationLayerSupport() -> bool;
    auto checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions) -> bool;

private:
    VkInstance m_Instance;
    std::weak_ptr<Albikar::engine::CEngineProperties> m_EngineProperties;
    const bool m_EnableValidationLayers;
};
} // namespace Albikar::render::vulkan