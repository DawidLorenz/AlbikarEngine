#pragma once
#include "IWindowObject.hpp"

class CHierarchyWindow final : public IWindowObject {
    WINDOW_OBJECT(CHierarchyWindow)
public:
    CHierarchyWindow() = default;
    ~CHierarchyWindow() final = default;

    auto Render() -> void final;

private:
    auto RenderHierarchy() -> void;
};