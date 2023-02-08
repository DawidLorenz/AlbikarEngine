#pragma once
#include <string>
#include <vector>

class CApplicationArgs final {
public:
    CApplicationArgs() = default;
    CApplicationArgs(int argc, char** argv);
    ~CApplicationArgs() = default;
    CApplicationArgs(const CApplicationArgs&) = default;
    CApplicationArgs(CApplicationArgs&&) = default;
    auto operator=(const CApplicationArgs&) -> CApplicationArgs& = default;
    auto operator=(CApplicationArgs&&) -> CApplicationArgs& = default;

private:
    std::vector<std::string> m_Args;
};