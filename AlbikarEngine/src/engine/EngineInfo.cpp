#pragma once
#include "EngineInfo.hpp"

namespace Albikar::engine {
CEngineInfo::CEngineInfo()
{
}

CEngineInfo::~CEngineInfo()
{
}

auto CEngineInfo::GetInfo() -> const char*
{
    return nullptr;
}

} // namespace Albikar::engine
