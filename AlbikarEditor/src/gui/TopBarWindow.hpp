#pragma once
#include "IWindowObject.hpp"
#include <memory>
#include <vector>

class CTopBarWindow final : public IWindowObject {
    WINDOW_OBJECT(CTopBarWindow)
public:
    CTopBarWindow();
    ~CTopBarWindow() final = default;

    auto Render() -> void final;

private:
    std::vector<std::unique_ptr<IWindowObject>> m_SubWindows;
};