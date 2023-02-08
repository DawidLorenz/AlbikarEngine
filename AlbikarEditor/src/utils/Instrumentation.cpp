#include "Instrumentation.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <thread>
#include <vector>

CInstrumentor::CInstrumentor()
    : m_CurrentSession(nullptr)
{
}

#if ENABLE_ALBIKAR_PROFILER_OUTSIDE
auto CInstrumentor::BeginSession(const std::string& name, const std::string& filepath) -> void
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (m_CurrentSession) {
        InternalEndSession();
    }
    m_OutputStream.open(filepath);
    if (m_OutputStream.is_open()) {
        m_CurrentSession = new InstrumentationSession({ name });
        WriteHeader();
    }
}

auto CInstrumentor::EndSession() -> void
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    InternalEndSession();
}

auto CInstrumentor::WriteOnlineProfile(const ProfileResult& result) -> void
{
    std::stringstream json;

    json << ",{";
    json << "\"cat\":\"function\",";
    json << "\"dur\":" << (result.End - result.Start) << ',';
    json << "\"name\":\"" << result.Name << "\",";
    json << "\"ph\":\"X\",";
    json << "\"pid\":0,";
    json << "\"tid\":" << result.ThreadID << ",";
    json << "\"ts\":" << result.Start;
    json << "}";

    std::lock_guard<std::mutex> lock(m_Mutex);
    if (m_CurrentSession) {
        m_OutputStream << json.str();
        m_OutputStream.flush();
    }
}
#else
auto CInstrumentor::BeginSession(
    [[maybe_unused]] const std::string& name,
    [[maybe_unused]] const std::string& filepath) -> void
{
}

auto CInstrumentor::EndSession() -> void
{
}

auto CInstrumentor::WriteOnlineProfile(
    [[maybe_unused]] const ProfileResult& result) -> void
{
}
#endif

#if ENABLE_ALBIKAR_PROFILER_INSIDE
auto CInstrumentor::WriteLocalProfile(const ProfileResult& result) -> void
{
    auto i = std::find_if(m_vLocalResult.begin(),
        m_vLocalResult.end(),
        [&](const auto& val) { return val.Name == result.Name; });
    if (i == m_vLocalResult.end()) {
        ProfileLocalResult localResult = { result.Name, result.End - result.Start, 1 };
        m_vLocalResult.emplace_back(localResult);
    } else {
        (*i).Duration += (result.End - result.Start);
        (*i).calls += 1;
    }
}
#else
auto CInstrumentor::WriteLocalProfile(const ProfileResult& result) -> void
{
}
#endif

auto CInstrumentor::GetAndClearLocalResult(std::vector<ProfileLocalResult>& newVector) -> void
{
    newVector = std::move(m_vLocalResult);
    m_vLocalResult.clear();
}

auto CInstrumentor::Get() -> CInstrumentor&
{
    static CInstrumentor instance;
    return instance;
}

auto CInstrumentor::WriteHeader() -> void
{
    m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
    m_OutputStream.flush();
}

auto CInstrumentor::WriteFooter() -> void
{
    m_OutputStream << "]}";
    m_OutputStream.flush();
}

auto CInstrumentor::InternalEndSession() -> void
{
    if (m_CurrentSession != nullptr) {
        WriteFooter();
        m_OutputStream.close();
        delete m_CurrentSession;
        m_CurrentSession = nullptr;
    }
}

CInstrumentationTimer::CInstrumentationTimer(const char* name)
    : m_Name(name)
    , m_Stopped(false)
{
    m_StartTimepoint = std::chrono::high_resolution_clock::now();
}

CInstrumentationTimer::~CInstrumentationTimer()
{
    if (!m_Stopped) {
        Stop();
    }
}

auto CInstrumentationTimer::Stop() -> void
{
    auto endTimepoint = std::chrono::high_resolution_clock::now();

    int64_t start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
    int64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

    CInstrumentor::Get().WriteOnlineProfile({ m_Name, start, end, std::this_thread::get_id() });
    CInstrumentor::Get().WriteLocalProfile({ m_Name, start, end, std::this_thread::get_id() });

    m_Stopped = true;
}