#include "EngineProperties.hpp"

namespace Albikar::engine {

auto CEngineProperties::GetEngineInfo() -> const char*
{
    return m_EngineInfo->GetInfo();
}

auto CEngineProperties::NotifyEngineInfoChanged(NotifyOnChange change) -> void
{
    // TODO(dlorenz) ovserver DP...
}

auto CEngineProperties::GetAppName() -> const char*
{
    return m_AppName.c_str();
}

auto CEngineProperties::GetAppVersion() -> std::tuple<uint32_t, uint32_t, uint32_t>
{
    return { m_AppMajor, m_AppMinor, m_AppPatch };
}

auto CEngineProperties::GetEngineName() -> const char*
{
    return m_EngineName.c_str();
}

auto CEngineProperties::GetEngineVersion() -> std::tuple<uint32_t, uint32_t, uint32_t>
{
    return { m_EngineMajor, m_EngineMinor, m_EnginePatch };
}

CEngineProperties::CEngineProperties()
    : m_EngineInfo(std::make_shared<CEngineInfo>())
{
}

CEngineProperties::~CEngineProperties()
{
}

auto CEngineProperties::EngineInfo() -> std::shared_ptr<CEngineInfo>
{
    return m_EngineInfo;
}

} // namespace Albikar::engine