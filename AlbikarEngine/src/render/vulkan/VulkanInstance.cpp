#include "VulkanInstance.hpp"
#include "VulkanUtils.hpp"
namespace Albikar::render::vulkan {

std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

CVulkanInstance::CVulkanInstance(std::shared_ptr<Albikar::engine::CEngineProperties> engineProperties)
    : m_EnableValidationLayers(true) // TODO(dlorenz) use it only in Debug
{
    m_EngineProperties = engineProperties;
}

auto CVulkanInstance::Init() -> ALBIKAR_RETURN
{
    // Check if we need enable validation layers
    if (m_EnableValidationLayers && !VulkanUtils::checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available");
    }

    // Check Instance Validation Layer is supported...
    if (m_EnableValidationLayers && !checkInstanceExtensionSupport(&validationLayers)) {
        throw std::runtime_error("VkInstance does not support required extensions");
    }
    return ALBIKAR_SUCCESS;
}

auto CVulkanInstance::Destroy() -> ALBIKAR_RETURN
{
    return ALBIKAR_SUCCESS;
}

auto CVulkanInstance::GetInstance() -> VkInstance const
{
    return m_Instance;
}

auto CVulkanInstance::checkValidationLayerSupport() -> bool
{
    uint32_t layerCount = { 0 };
    VkResult res = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    ALBIKAR_VK_CHECK(res, "Failed to fetch number of layers")

    std::vector<VkLayerProperties> availableLayers(layerCount);
    res = vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    ALBIKAR_VK_CHECK(res, "Failed to fetch layers data")

    return layerCount > 0;
}

auto CVulkanInstance::checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions) -> bool
{
}
} // namespace Albikar::render::vulkan
