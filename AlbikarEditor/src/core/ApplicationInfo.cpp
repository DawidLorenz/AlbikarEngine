#include "ApplicationInfo.hpp"

#include "ApplicationArgs.hpp"
#include <utility>

CApplicationInfo::CApplicationInfo(CApplicationArgs args)
    : m_Args(std::move(args))
{
}

auto CApplicationInfo::GetName() -> std::string
{
    return m_Name;
}