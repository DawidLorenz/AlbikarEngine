#pragma once
#include "AlbikarDefines.hpp"
#include "IEngineProperties.hpp"

namespace Albikar::AlbikarAPI {
class IAlbikarDebug {
public:
    ALBIKAR_INTERFACE(IAlbikarDebug)
    enum class LOG_MODE { WARN,
        CRITICAL,
        INFO,
        ERROR,
        LINE };

    using LogCallBack = std::function<void(const char* i_fileName, const char* i_functionName, const uint64_t i_fileLine, const LOG_MODE mode, const char* logOutput)>;
    virtual auto ConnectLogger(LogCallBack callBack) -> ALBIKAR_RETURN = 0;
    virtual auto DisconnectLogger() -> ALBIKAR_RETURN = 0;

    virtual auto AlbikarEngineProperties() -> std::shared_ptr<IEngineProperties> = 0;
};
} // namespace Albikar::AlbikarAPI