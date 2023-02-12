#pragma once
#define ENABLE_ALBIKAR_ENGINE_LOGGER // TODO(dlorenz)move to CMake

#ifdef ENABLE_ALBIKAR_ENGINE_LOGGER
#include "AlbikarLogger.hpp"
#define LOG_WARN(...) Albikar::utils::CAlbikarLogger::log(Albikar::utils::CLogInfo::LOG_MODE::WARN, __LINE__, __FILE__, __FUNCTION__, __VA_ARGS__)
#define LOG_CRITICAL(...) Albikar::utils::CAlbikarLogger::log(Albikar::utils::CLogInfo::LOG_MODE::CRITICAL, __LINE__, __FILE__, __FUNCTION__, __VA_ARGS__)
#define LOG_INFO(...) Albikar::utils::CAlbikarLogger::log(Albikar::utils::CLogInfo::LOG_MODE::INFO, __LINE__, __FILE__, __FUNCTION__, __VA_ARGS__)
#define LOG_ERROR(...) Albikar::utils::CAlbikarLogger::log(Albikar::utils::CLogInfo::LOG_MODE::ERROR, __LINE__, __FILE__, __FUNCTION__, __VA_ARGS__)
#define LOG_LINE(...) Albikar::utils::CAlbikarLogger::line(__LINE__, __FILE__, __FUNCTION__)
#else
#define LOG_WARN(...)
#define LOG_CRITICAL(...)
#define LOG_INFO(...)
#define LOG_ERROR(...)
#define LOG_LINE(...)
#endif