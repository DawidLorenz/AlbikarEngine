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