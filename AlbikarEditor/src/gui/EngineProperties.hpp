#pragma once
#include "IWindowObject.hpp"

class CEnginePropertiesWindow final : public IWindowObject {
    WINDOW_OBJECT(CEnginePropertiesWindow)
public:
    CEnginePropertiesWindow() = default;
    ~CEnginePropertiesWindow() final = default;

    auto Render() -> void final;
};