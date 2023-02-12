#include "AlbikarLogger.hpp"
#include "IAlbikarDebug.hpp"

namespace Albikar::utils {
AlbikarAPI::IAlbikarDebug::LogCallBack CAlbikarLogger::logCallBack = nullptr;

auto CAlbikarLogger::log_info(CLogInfo& logInfo,
    const CLogInfo::LOG_MODE mode,
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
    AlbikarAPI::IAlbikarDebug::LOG_MODE mapMode { AlbikarAPI::IAlbikarDebug::LOG_MODE::ERROR };
    switch (logInfo.m_eMode) {
    case CLogInfo::LOG_MODE::WARN:
        mapMode = AlbikarAPI::IAlbikarDebug::LOG_MODE::WARN;
        break;
    case CLogInfo::LOG_MODE::CRITICAL:
        mapMode = AlbikarAPI::IAlbikarDebug::LOG_MODE::CRITICAL;
        break;
    case CLogInfo::LOG_MODE::INFO:
        mapMode = AlbikarAPI::IAlbikarDebug::LOG_MODE::INFO;
        break;
    case CLogInfo::LOG_MODE::ERROR:
        mapMode = AlbikarAPI::IAlbikarDebug::LOG_MODE::ERROR;
        break;
    case CLogInfo::LOG_MODE::LINE:
        mapMode = AlbikarAPI::IAlbikarDebug::LOG_MODE::LINE;
        break;
    default:
        break;
    }

    if (logCallBack) {
        logCallBack(logInfo.m_sFileName.c_str(), logInfo.m_sFunctionName.c_str(), 1, mapMode, logInfo.m_sLogOutput.c_str());
    }
};
} // namespace Albikar::utils
