#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

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

    explicit CLogInfo(const CLogInfo& other) = delete;
    CLogInfo(CLogInfo&& other) noexcept;
    auto operator=(const CLogInfo& other) -> CLogInfo& = delete;
    auto operator=(const CLogInfo&& other) -> CLogInfo& = delete;

    bool m_bLogFromAlbikar;
    uint64_t m_uiNumber;
    std::string m_sFileName;
    std::string m_sFunctionName;
    uint64_t m_uiFileLine;
    LOG_MODE m_eMode;
    std::string m_sLogOutput;
};