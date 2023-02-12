#include "Project.hpp"
#include "AlbikarLogger.hpp"

CProject::~CProject()
{
    CloseProject();
}

CProject::CProject(const std::string projectPath, const std::string projectName, const std::string projectDescription)
{
    m_ProjectPath = projectPath;
    m_ProjectName = projectName;
    m_ProjectDescription = projectDescription;
}

auto CProject::StartProject() -> void
{
    m_engineProxy = Albikar::AlbikarAPI::CreateEngine();
    m_engineProxy->AlbikarDebug()->ConnectLogger(std::bind(&CAlbikarLogger::logCallBack, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
    m_engineProxy->InitEngine(1280, 720, "Example Game", false);
}

auto CProject::CloseProject() -> void
{
    if (m_engineProxy != nullptr) {
        m_engineProxy->AlbikarDebug()->DisconnectLogger();
        m_engineProxy->Terminate();
    }
}

auto CProject::SaveProject() -> void
{
}

auto CProject::OpenProject() -> void
{
}