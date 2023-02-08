#pragma once
#include "IWindowObject.hpp"

class CTopBarWindowView final : public IWindowObject {
    WINDOW_OBJECT(CTopBarWindowView)
public:
    CTopBarWindowView() = default;
    ~CTopBarWindowView() final = default;

    auto Render() -> void final;
};
