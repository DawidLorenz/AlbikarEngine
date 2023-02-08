#pragma once
#include "ApplicationArgs.hpp"
#include "ApplicationInfo.hpp"
#include "Preferences.hpp"
#include <string>

class CLogInfo;

class CApplicationInfo final {
public:
    CApplicationInfo() = default;
    CApplicationInfo(CApplicationArgs args);
    ~CApplicationInfo() = default;
    CApplicationInfo(const CApplicationInfo&) = default;
    CApplicationInfo(CApplicationInfo&&) = default;
    auto operator=(const CApplicationInfo&) -> CApplicationInfo& = default;
    auto operator=(CApplicationInfo&&) -> CApplicationInfo& = default;

    auto GetName() -> std::string;

private:
    std::string m_Name = APP_NAME;
    std::wstring m_WorkDir;
    CApplicationArgs m_Args;
};