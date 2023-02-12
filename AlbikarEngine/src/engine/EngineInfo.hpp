#pragma once
#include "Defines.hpp"

namespace Albikar::engine {
class CEngineInfo final {
public:
    CEngineInfo();
    ~CEngineInfo();
    auto GetInfo() -> const char*;

public:
    auto addAvailableLayers(const std::vector<VkLayerProperties>& availableLayers) -> void;
    auto addAvailableExtensions(const std::vector<VkExtensionProperties>& extensions) -> void;

private:
    std::vector<VkLayerProperties> m_LayersProperties;
    std::vector<VkExtensionProperties> m_ExtensionProperties;
};
} // namespace Albikar::engine
