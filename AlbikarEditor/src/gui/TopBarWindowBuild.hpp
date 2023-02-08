#pragma once
#include "IWindowObject.hpp"

class CTopBarWindowBuild final : public IWindowObject {
    WINDOW_OBJECT(CTopBarWindowBuild)
public:
    CTopBarWindowBuild() = default;
    ~CTopBarWindowBuild() final = default;

    auto Render() -> void final;
};
