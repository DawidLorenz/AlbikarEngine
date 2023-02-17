#pragma once
#include "EngineInfo.hpp"

namespace Albikar::engine {

auto CEngineInfo::GetInfo() -> const char*
{
    return nullptr;
}

auto CEngineInfo::addAvailableLayers(const std::vector<VkLayerProperties>& availableLayers) -> void
{
    m_LayersProperties = availableLayers;
}

auto CEngineInfo::addAvailableExtensions(const std::vector<VkExtensionProperties>& extensions) -> void
{
    m_ExtensionProperties = extensions;
}

} // namespace Albikar::engine
