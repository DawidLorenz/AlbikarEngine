#pragma once
#include "EngineInfo.hpp"
#include "IEngineProperties.hpp"

namespace Albikar::engine {
class CEngineProperties final : public AlbikarAPI::IEngineProperties {
public:
    // INTERFACE
    auto GetEngineInfo() -> const char*;
    auto NotifyEngineInfoChanged(NotifyOnChange change) -> void;

public:
    CEngineProperties();
    ~CEngineProperties();
    auto EngineInfo() -> std::shared_ptr<CEngineInfo>;

private:
    std::shared_ptr<CEngineInfo> m_EngineInfo;
};
} // namespace Albikar::engine
