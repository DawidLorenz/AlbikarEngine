#pragma once
#define ENABLE_ALBIKAR_LOGGER // TODO(dlorenz)move to CMake

#ifdef ENABLE_ALBIKAR_LOGGER
#include "AlbikarLogger.hpp"
#define LOG_WARN(...) CAlbikarLogger::log(CLogInfo::LOG_MODE::WARN, __LINE__, __FILE__, __FUNCTION__, __VA_ARGS__)
#define LOG_CRITICAL(...) CAlbikarLogger::log(CLogInfo::LOG_MODE::CRITICAL, __LINE__, __FILE__, __FUNCTION__, __VA_ARGS__)
#define LOG_INFO(...) CAlbikarLogger::log(CLogInfo::LOG_MODE::INFO, __LINE__, __FILE__, __FUNCTION__, __VA_ARGS__)
#define LOG_ERROR(...) CAlbikarLogger::log(CLogInfo::LOG_MODE::ERROR, __LINE__, __FILE__, __FUNCTION__, __VA_ARGS__)
#define LOG_LINE(...) CAlbikarLogger::line(__LINE__, __FILE__, __FUNCTION__)
#else
#define LOG_WARN(...)
#define LOG_CRITICAL(...)
#define LOG_INFO(...)
#define LOG_ERROR(...)
#define LOG_LINE(...)
#endif