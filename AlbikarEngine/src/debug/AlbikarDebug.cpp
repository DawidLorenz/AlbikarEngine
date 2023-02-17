#include "AlbikarDebug.hpp"
#include "AlbikarLogger.hpp"
#include "IAlbikarDebug.hpp"
#include "IEngineProperties.hpp"

namespace Albikar::debug {
auto CAlbikarDebug::ConnectLogger(LogCallBack callBack) -> ALBIKAR_RETURN
{
    if (callBack != nullptr) {
        utils::CAlbikarLogger::logCallBack = callBack;
        return ALBIKAR_SUCCESS;
    }
    return ALBIKAR_FAILURE;
}

auto CAlbikarDebug::DisconnectLogger() -> ALBIKAR_RETURN
{
    utils::CAlbikarLogger::logCallBack = nullptr;
    return ALBIKAR_SUCCESS;
}

auto CAlbikarDebug::AlbikarEngineProperties() -> std::shared_ptr<Albikar::AlbikarAPI::IEngineProperties>
{
    return m_EngineProperties;
}

CAlbikarDebug::CAlbikarDebug()
{
    m_EngineProperties = std::make_shared<engine::CEngineProperties>();
}

auto CAlbikarDebug::EngineProperties() -> std::shared_ptr<Albikar::engine::CEngineProperties>
{
    return m_EngineProperties;
}

} // namespace Albikar::debug