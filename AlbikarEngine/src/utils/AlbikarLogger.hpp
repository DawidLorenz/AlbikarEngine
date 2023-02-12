#pragma once
#include "IAlbikarDebug.hpp"
#include "LogInfo.hpp"
#include <atomic>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Albikar::utils {
class CAlbikarLogger final {
public:
    static Albikar::AlbikarAPI::IAlbikarDebug::LogCallBack logCallBack;

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
        handle_output(logInfo);
    }

    static auto line(const uint64_t& line,
        const char* fileName,
        const char* functionName) -> void
    {
        CLogInfo logInfo;
        log_info(logInfo, CLogInfo::LOG_MODE::LINE, line, fileName, functionName);
        handle_output(logInfo);
    }

private:
    template <typename... Args>
    static auto log_args(CLogInfo& logInfo, Args&&... args) -> void
    {
        std::ostringstream stream;
        (stream << ... << std::forward<Args>(args));
        logInfo.m_sLogOutput = stream.str();
    }

    static auto log_info(CLogInfo& logInfo, const CLogInfo::LOG_MODE mode, const uint64_t& line, const char* fileName, const char* functionName) -> void;
    static auto handle_output(CLogInfo& logInfo) -> void;
};
} // namespace Albikar::utils
