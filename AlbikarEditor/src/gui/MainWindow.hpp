#pragma once
#include "IWindowObject.hpp"
#include <memory>
#include <vector>

class CMainWindow final : public IWindowObject {
    WINDOW_OBJECT(CMainWindow)
public:
    CMainWindow();
    ~CMainWindow() final = default;

    auto Render() -> void final;

private:
    auto RenderWindows() -> void;
    auto DefaultStyle() -> void;

private:
    std::vector<std::unique_ptr<IWindowObject>> m_SubWindows;
};