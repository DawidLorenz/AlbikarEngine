#pragma once
#include "AlbikarDefines.hpp"
#include "EngineProperties.hpp"
#include "IAlbikarDebug.hpp"
#include <iostream>
namespace Albikar::debug {
class CAlbikarDebug final : public AlbikarAPI::IAlbikarDebug {
public:
    // INTERFACE
    auto ConnectLogger(LogCallBack callBack) -> ALBIKAR_RETURN final;
    auto DisconnectLogger() -> ALBIKAR_RETURN final;
    auto AlbikarEngineProperties() -> std::shared_ptr<Albikar::AlbikarAPI::IEngineProperties> final;

public:
    CAlbikarDebug();
    ~CAlbikarDebug();
    auto EngineProperties() -> std::shared_ptr<Albikar::engine::CEngineProperties>;

private:
    std::shared_ptr<engine::CEngineProperties> m_EngineProperties;
};
} // namespace Albikar::debug