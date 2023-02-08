#include "Project.hpp"

CProject::~CProject()
{
    if (m_engineProxy) {
        m_engineProxy->Terminate();
    }
}

CProject::CProject(const std::string projectPath, const std::string projectName, const std::string projectDescription)
{
    m_ProjectPath = projectPath;
    m_ProjectName = projectName;
    m_ProjectDescription = projectDescription;
}

auto CProject::StartProject() -> void
{
    m_engineProxy = AlbikarAPI::CreateEngine();
}

auto CProject::CloseProject() -> void
{
    m_engineProxy->Terminate();
}

auto CProject::SaveProject() -> void
{
}

auto CProject::OpenProject() -> void
{
}