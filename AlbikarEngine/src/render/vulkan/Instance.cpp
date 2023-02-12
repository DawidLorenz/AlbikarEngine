#include "Instance.hpp"
#include "Preferences.hpp"
#include "VulkanUtils.hpp"
namespace Albikar::render::vulkan {

std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

CInstance::CInstance(std::shared_ptr<Albikar::engine::CEngineProperties> engineProperties)
    : m_EngineProperties(engineProperties)
    , m_EnableValidationLayers(true) // TODO(dlorenz) use it only in Debug
{
}

auto CInstance::Init() -> ALBIKAR_RETURN
{
    // Check if we need enable validation layers
    if (m_EnableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("Validation layers requested, but not available");
    }

    // Creation information for a VkInstance (Vulkan Instance)
    VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };

    // Information about the application itself
    // Most data here doesn't affect the program and is for developer convenience
    VkApplicationInfo appInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
    if (m_EngineProperties.lock()) {
        appInfo.pApplicationName = m_EngineProperties.lock()->GetAppName();
        const auto [appMajor, appMinor, appPatch] = m_EngineProperties.lock()->GetAppVersion();
        appInfo.applicationVersion = VK_MAKE_VERSION(appMajor, appMinor, appPatch);
        appInfo.pEngineName = m_EngineProperties.lock()->GetEngineName();
        const auto [engineMajor, engineMinor, enginePatch] = m_EngineProperties.lock()->GetEngineVersion();
        appInfo.engineVersion = VK_MAKE_VERSION(engineMajor, engineMinor, enginePatch);
        appInfo.apiVersion = VK_API_VERSION_1_3;
    } else {
        throw std::runtime_error("Failed to create App Info");
    }
    createInfo.pApplicationInfo = &appInfo;

    // Get GLFW extensions
    uint32_t glfwExtensionCount = { 0 };
    std::vector<const char*> instanceExtension = std::vector<const char*>();
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    for (size_t i = 0; i < glfwExtensionCount; i++) {
        instanceExtension.emplace_back(glfwExtensions[i]);
    }
    if (!checkInstanceExtensionSupport(&instanceExtension)) {
        throw std::runtime_error("VkInstance does not support required extensions !");
    }
    createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtension.size());
    createInfo.ppEnabledExtensionNames = instanceExtension.data();

    // Add Validation Layers
    if (m_EnableValidationLayers) {
        // TODO(dlorenz) add Message callback
        // https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Validation_layers
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }

    // Create instance
    VkResult res = vkCreateInstance(&createInfo, ALBIKAR_VK_MEMORY, &m_Instance);
    if (res != VK_SUCCESS) {
        throw std::runtime_error("Cannot create Vulakn Instance");
    }

    return ALBIKAR_SUCCESS;
}

auto CInstance::Destroy() -> ALBIKAR_RETURN
{
    vkDestroyInstance(m_Instance, nullptr);
    return ALBIKAR_SUCCESS;
}

auto CInstance::GetInstance() -> VkInstance const
{
    return m_Instance;
}

auto CInstance::checkValidationLayerSupport() -> bool
{
    uint32_t layerCount = { 0 };
    // Get number of validation layers to create vector of appropriate size
    VkResult res = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    ALBIKAR_VK_CHECK(res, "Failed to fetch number of layers")

    std::vector<VkLayerProperties> availableLayers(layerCount);
    // Check if no validation layers found AND we want at least 1 layer
    res = vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    ALBIKAR_VK_CHECK(res, "Failed to fetch layers data")

    if (layerCount == 0) {
        return false;
    }

    if (m_EngineProperties.lock()) {
        m_EngineProperties.lock()->EngineInfo()->addAvailableLayers(availableLayers);
    }

    // Check Instance Extensions supported...
    return checkInstanceExtensionSupport(&validationLayers);
}

auto CInstance::checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions) -> bool
{
    uint32_t extensionCount = 0;
    VkResult result = VK_SUCCESS;
    // Need to get number of extensions to create array of correct size to hold extensions
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    if ((result != VK_SUCCESS) || (extensionCount == 0)) {
        LOG_ERROR("Could not get the number of instance extensions.");
        return false;
    }

    // Create a list of VkExtensionProperties using count
    std::vector<VkExtensionProperties> extensions(extensionCount);
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    if ((result != VK_SUCCESS) || (extensionCount == 0)) {
        LOG_ERROR("Could not enumerate instance extensions.");
        return false;
    }

    if (m_EngineProperties.lock()) {
        m_EngineProperties.lock()->EngineInfo()->addAvailableExtensions(extensions);
    }

    // Check if given extensions are in list of available extensions
    for (const auto& checkExtension : *checkExtensions) {
        bool hasExtension = false;
        for (const auto& extension : extensions) {
            if (static_cast<bool>(strcmp(checkExtension, extension.extensionName))) {
                hasExtension = true;
                LOG_INFO("Extension :", checkExtension, " is supported");
                break;
            }
        }
        if (!hasExtension) {
            return false;
        }
    }

    return true;
}
} // namespace Albikar::render::vulkan
