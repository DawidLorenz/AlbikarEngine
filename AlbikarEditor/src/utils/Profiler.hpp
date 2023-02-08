#pragma once
#define ENABLE_ALBIKAR_PROFILER 1 // TODO(dlorenz) move to CMake

#if ENABLE_ALBIKAR_PROFILER
#include "Instrumentation.hpp"
#define ALB_PROFILE_BEGIN_SESSION(name, filepath) CInstrumentor::Get().BeginSession(name, filepath)
#define ALB_PROFILE_END_SESSION() CInstrumentor::Get().EndSession()
#define ALB_PROFILE_SCOPE(name) CInstrumentationTimer timer##__LINE__(name);
#define ALB_PROFILE_FUNCTION() ATP_PROFILE_SCOPE(__FUNCSIG__)
#else
#define ALB_PROFILE_BEGIN_SESSION(name, filepath)
#define ALB_PROFILE_END_SESSION()
#define ALB_PROFILE_SCOPE(name)
#define ALB_PROFILE_FUNCTION()
#endif