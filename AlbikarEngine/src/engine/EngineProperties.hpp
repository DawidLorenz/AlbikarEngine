#pragma once
#include "EngineInfo.hpp"
#include "IEngineProperties.hpp"
#include "Preferences.hpp"
#include <string>

namespace Albikar::engine {
class CEngineProperties final : public AlbikarAPI::IEngineProperties {
public:
    // INTERFACE
    auto GetEngineInfo() -> const char* final;
    auto NotifyEngineInfoChanged(NotifyOnChange change) -> void final;

public:
    // ENGINE USAGE
    auto GetAppName() -> const char*;
    auto GetAppVersion() -> std::tuple<uint32_t, uint32_t, uint32_t>;
    auto GetEngineName() -> const char*;
    auto GetEngineVersion() -> std::tuple<uint32_t, uint32_t, uint32_t>;

public:
    CEngineProperties();
    ~CEngineProperties() final = default;
    CEngineProperties(const CEngineProperties&) = default;
    CEngineProperties(CEngineProperties&&) = default;
    auto operator=(const CEngineProperties&) -> CEngineProperties& = default;
    auto operator=(CEngineProperties&&) -> CEngineProperties& = default;

    // ENGINE USAGE
    auto EngineInfo() -> std::shared_ptr<CEngineInfo>;

private:
    std::string m_AppName = APP_NAME;
    uint32_t m_AppMajor = APP_MAJOR;
    uint32_t m_AppMinor = APP_MINIR;
    uint32_t m_AppPatch = APP_PATCH;
    std::string m_EngineName = ENGINE_NAME;
    uint32_t m_EngineMajor = ENGINE_MAJOR;
    uint32_t m_EngineMinor = ENGINE_MINIR;
    uint32_t m_EnginePatch = ENGINE_PATCH;

private:
    std::shared_ptr<CEngineInfo> m_EngineInfo;
};
} // namespace Albikar::engine
