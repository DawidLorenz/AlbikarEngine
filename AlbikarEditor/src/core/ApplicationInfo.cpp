#include "ApplicationInfo.hpp"
#include "ApplicationArgs.hpp"

CApplicationInfo::CApplicationInfo(CApplicationArgs args)
    : m_Args(args)
{
}

auto CApplicationInfo::GetName() -> std::string
{
    return m_Name;
}