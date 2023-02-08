#pragma once
#include "IWindowObject.hpp"

class CTopBarWindowEdit final : public IWindowObject {
    WINDOW_OBJECT(CTopBarWindowEdit)
public:
    CTopBarWindowEdit() = default;
    ~CTopBarWindowEdit() final = default;

    auto Render() -> void final;
};
