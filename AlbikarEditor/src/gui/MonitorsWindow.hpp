#pragma once
#include "IWindowObject.hpp"

class CMonitorsWindow final : public IWindowObject {
    WINDOW_OBJECT(CMonitorsWindow)
public:
    CMonitorsWindow() = default;
    ~CMonitorsWindow() final = default;

    auto Render() -> void final;
};