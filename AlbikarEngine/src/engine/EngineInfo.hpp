#pragma once
#include "Defines.hpp"

namespace Albikar::engine {
class CEngineInfo final {
public:
    CEngineInfo();
    ~CEngineInfo();
    auto GetInfo() -> const char*;
};
} // namespace Albikar::engine
