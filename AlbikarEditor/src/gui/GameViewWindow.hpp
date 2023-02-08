#pragma once
#include "IWindowObject.hpp"

class CGameViewWindow final : public IWindowObject {
    WINDOW_OBJECT(CGameViewWindow)
public:
    CGameViewWindow() = default;
    ~CGameViewWindow() final = default;

    auto Render() -> void final;
};