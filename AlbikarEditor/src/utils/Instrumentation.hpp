#pragma once
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#define ENABLE_ALBIKAR_PROFILER_INSIDE 1 // TODO(dlorenz) add handling from cope point of view
// #define ENABLE_ALBIKAR_PROFILER_OUTSIDE 1 //TODO(dlorenz) add handling from cope point of view chrome://tracing/

struct ProfileLocalResult {
    std::string Name;
    int64_t Duration;
    uint32_t calls;
};

struct ProfileResult {
    std::string Name;
    int64_t Start, End;
    std::thread::id ThreadID;
};

struct InstrumentationSession {
    std::string Name;
};

class CInstrumentor {
private:
    std::mutex m_Mutex;
    InstrumentationSession* m_CurrentSession;
    std::ofstream m_OutputStream;
    std::vector<ProfileLocalResult> m_vLocalResult;

public:
    CInstrumentor();

    auto BeginSession(const std::string& name, const std::string& filepath = "results.json") -> void;
    auto EndSession() -> void;

    auto WriteOnlineProfile(const ProfileResult& result) -> void;
    auto WriteLocalProfile(const ProfileResult& result) -> void;

    auto GetAndClearLocalResult(std::vector<ProfileLocalResult>& newVector) -> void;

    static auto Get() -> CInstrumentor&;
    auto WriteHeader() -> void;
    auto WriteFooter() -> void;
    auto InternalEndSession() -> void;
};

class CInstrumentationTimer final {
public:
    explicit CInstrumentationTimer(const char* name);
    ~CInstrumentationTimer();
    explicit CInstrumentationTimer(const CInstrumentationTimer& other) = delete;
    CInstrumentationTimer(CInstrumentationTimer&& other) noexcept;
    auto operator=(const CInstrumentationTimer& other) -> CInstrumentationTimer& = delete;
    auto operator=(const CInstrumentationTimer&& other) -> CInstrumentationTimer& = delete;

    auto Stop() -> void;

private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
};
