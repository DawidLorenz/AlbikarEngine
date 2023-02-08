#pragma once
#include "IWindowObject.hpp"

class CTopBarWindowCenterLabel final : public IWindowObject {
    WINDOW_OBJECT(CTopBarWindowCenterLabel)
public:
    CTopBarWindowCenterLabel() = default;
    ~CTopBarWindowCenterLabel() final = default;

    auto Render() -> void final;
};
