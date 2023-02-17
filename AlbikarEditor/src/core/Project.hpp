#pragma once
#include "IAlbikarEngine.hpp"
#include <string>

class CProject final {
public:
    explicit CProject() = default;
    explicit CProject(std::string projectPath, std::string projectName, std::string projectDescription);
    ~CProject();
    CProject(const CProject&) = default;
    CProject(CProject&&) = default;
    auto operator=(const CProject&) -> CProject& = delete;
    auto operator=(const CProject&&) -> CProject& = delete;

public:
    auto StartProject() -> void;
    auto CloseProject() -> void;
    auto SaveProject() -> void;
    auto OpenProject() -> void;

private:
    std::string m_ProjectPath;
    std::string m_ProjectName;
    std::string m_ProjectDescription;

private:
    std::shared_ptr<Albikar::AlbikarAPI::IAlbikarEngine> m_engineProxy;
};