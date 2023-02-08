#pragma once
#include "IWindowObject.hpp"
#include "Instrumentation.hpp"
#include <vector>

class CProfilerWindow final : public IWindowObject {
    WINDOW_OBJECT(CProfilerWindow)
public:
    CProfilerWindow() = default;
    ~CProfilerWindow() final = default;

    auto Render() -> void final;

private:
    std::vector<ProfileLocalResult> m_vLocalResult;
};