#include "AlbikarLogger.hpp"

std::atomic<uint64_t> CAlbikarLogger::m_numberOfRecords(0);
CAlbikarLogger::LOG_OUTPUT CAlbikarLogger::m_OutPut = CAlbikarLogger::LOG_OUTPUT::GUI_APP;
std::vector<CLogInfo> CAlbikarLogger::m_AllLog = {};

auto CAlbikarLogger::log_info(CLogInfo& logInfo,
    CLogInfo::LOG_MODE mode,
    const uint64_t& line,
    const char* fileName,
    const char* functionName) -> void
{
    logInfo.m_sFileName = fileName;
    logInfo.m_sFunctionName = functionName;
    logInfo.m_uiFileLine = line;
    logInfo.m_eMode = mode;
};

auto CAlbikarLogger::handle_output(CLogInfo& logInfo) -> void
{
    logInfo.m_uiNumber = m_numberOfRecords;
    ++m_numberOfRecords;
    m_AllLog.emplace_back(std::move(logInfo));
};