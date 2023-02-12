#pragma once
#include "AlbikarDefines.hpp"

namespace Albikar::AlbikarAPI {
class IEngineProperties {
public:
    ALBIKAR_INTERFACE(IEngineProperties)

    virtual auto GetEngineInfo() -> const char* = 0;
    virtual auto NotifyEngineInfoChanged(NotifyOnChange change) -> void = 0;
};
} // namespace Albikar::AlbikarAPI