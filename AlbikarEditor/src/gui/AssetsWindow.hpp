#pragma once
#include "IWindowObject.hpp"

class CAssetsWindow final : public IWindowObject {
    WINDOW_OBJECT(CAssetsWindow)
public:
    CAssetsWindow() = default;
    ~CAssetsWindow() final = default;

    auto Render() -> void final;
};