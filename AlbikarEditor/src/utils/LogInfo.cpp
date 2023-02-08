#include "LogInfo.hpp"

CLogInfo::CLogInfo()
    : m_bLogFromAlbikar(false)
    , m_uiNumber(0)
    , m_sFileName()
    , m_sFunctionName()
    , m_uiFileLine(0)
    , m_eMode(LOG_MODE::CRITICAL)
    , m_sLogOutput()
{
}

CLogInfo::CLogInfo(CLogInfo&& other) noexcept
    : m_bLogFromAlbikar(std::exchange(other.m_bLogFromAlbikar, false))
    , m_uiNumber(std::exchange(other.m_uiNumber, 0))
    , m_sFileName(std::move(other.m_sFileName))
    , m_sFunctionName(std::move(other.m_sFunctionName))
    , m_uiFileLine(std::exchange(other.m_uiFileLine, 0))
    , m_eMode(std::exchange(other.m_eMode, LOG_MODE::INFO))
    , m_sLogOutput(std::move(other.m_sLogOutput))
{
}