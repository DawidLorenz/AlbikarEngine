#pragma once
#include "IWindowObject.hpp"

class CAssetsPreviewWindow final : public IWindowObject {
    WINDOW_OBJECT(CAssetsPreviewWindow)
public:
    CAssetsPreviewWindow() = default;
    ~CAssetsPreviewWindow() final = default;

    auto Render() -> void final;
};