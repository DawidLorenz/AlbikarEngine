#pragma once
#include "IWindowObject.hpp"

class CDockspaceWindow final : public IWindowObject {
    WINDOW_OBJECT(CDockspaceWindow)
public:
    CDockspaceWindow() = default;
    ~CDockspaceWindow() final = default;

    auto Render() -> void final;
};