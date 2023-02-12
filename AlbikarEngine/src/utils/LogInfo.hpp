#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
namespace Albikar::utils {

class CLogInfo final {
public:
    enum class LOG_MODE {
        WARN,
        CRITICAL,
        INFO,
        ERROR,
        LINE
    };

    explicit CLogInfo();
    ~CLogInfo() = default;

    explicit CLogInfo(const CLogInfo& o) = delete;
    CLogInfo(CLogInfo&& o) noexcept;
    auto operator=(const CLogInfo& o) -> CLogInfo& = delete;
    auto operator=(const CLogInfo&& o) -> CLogInfo& = delete;

    std::string m_sFileName;
    std::string m_sFunctionName;
    uint64_t m_uiFileLine;
    LOG_MODE m_eMode;
    std::string m_sLogOutput;
};

} // namespace Albikar::utils