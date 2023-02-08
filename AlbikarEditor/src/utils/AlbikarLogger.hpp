#pragma once

#include "LogInfo.hpp"
#include <atomic>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CAlbikarLogger final {
public:
    enum class LOG_OUTPUT {
        CONSOLE,
        GUI_APP,
        FILE
    };

    template <typename... Args>
    static auto log(const CLogInfo::LOG_MODE& mode,
        const uint64_t& line,
        const char* fileName,
        const char* functionName,
        Args&&... args) -> void
    {
        CLogInfo logInfo;
        log_info(logInfo, mode, line, fileName, functionName);
        log_args(logInfo, std::forward<Args>(args)...);
        logInfo.m_bLogFromAlbikar = true;
        handle_output(logInfo);
    }

    static auto line(const uint64_t& line,
        const char* fileName,
        const char* functionName) -> void
    {
        CLogInfo logInfo;
        log_info(logInfo, CLogInfo::LOG_MODE::LINE, line, fileName, functionName);
        logInfo.m_bLogFromAlbikar = true;
        handle_output(logInfo);
    }

    static std::vector<CLogInfo> m_AllLog;

private:
    template <typename... Args>
    static auto log_args(CLogInfo& logInfo, Args&&... args) -> void
    {
        std::ostringstream stream;
        (stream << ... << std::forward<Args>(args));
        logInfo.m_sLogOutput = stream.str();
    }

    static auto log_info(CLogInfo& logInfo, CLogInfo::LOG_MODE mode, const uint64_t& line, const char* fileName, const char* functionName) -> void;
    static auto handle_output(CLogInfo& logInfo) -> void;
    static std::atomic<uint64_t> m_numberOfRecords;
    static LOG_OUTPUT m_OutPut;
};