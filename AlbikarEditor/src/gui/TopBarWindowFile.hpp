#pragma once
#include "IWindowObject.hpp"
#include <string>

class CTopBarWindowFile final : public IWindowObject {
    WINDOW_OBJECT(CTopBarWindowFile)
public:
    CTopBarWindowFile();
    ~CTopBarWindowFile() final = default;

    auto Render() -> void final;

private:
    auto RenderNewProjectWindow() -> void;

private:
    bool m_bShowNewProject;
    bool m_bShowOpenProject;

    std::string m_sProjectPath;
};
