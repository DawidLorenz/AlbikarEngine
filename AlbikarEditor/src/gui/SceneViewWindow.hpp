#pragma once
#include "IWindowObject.hpp"

class CSceneViewWindow final : public IWindowObject {
    WINDOW_OBJECT(CSceneViewWindow)
public:
    CSceneViewWindow() = default;
    ~CSceneViewWindow() final = default;

    auto Render() -> void final;
};