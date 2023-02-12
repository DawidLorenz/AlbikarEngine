#include "LogInfo.hpp"
namespace Albikar::utils {

CLogInfo::CLogInfo()
    : m_sFileName()
    , m_sFunctionName()
    , m_uiFileLine(0)
    , m_eMode(LOG_MODE::CRITICAL)
    , m_sLogOutput()
{
}

CLogInfo::CLogInfo(CLogInfo&& o) noexcept
    : m_sFileName(std::move(o.m_sFileName))
    , m_sFunctionName(std::move(o.m_sFunctionName))
    , m_uiFileLine(std::exchange(o.m_uiFileLine, 0))
    , m_eMode(std::exchange(o.m_eMode, LOG_MODE::INFO))
    , m_sLogOutput(std::move(o.m_sLogOutput))
{
}
} // namespace Albikar::utils