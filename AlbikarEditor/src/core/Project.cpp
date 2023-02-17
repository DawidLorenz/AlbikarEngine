#include "Project.hpp"

#include "AlbikarLogger.hpp"
#include <utility>

CProject::~CProject()
{
    CloseProject();
}

CProject::CProject(std::string projectPath, std::string projectName, std::string projectDescription)
    : m_ProjectPath(std::move(projectPath))
    , m_ProjectName(std::move(projectName))
    , m_ProjectDescription(std::move(projectDescription))
{
}

auto CProject::StartProject() -> void
{
    m_engineProxy = Albikar::AlbikarAPI::CreateEngine();
    m_engineProxy->AlbikarDebug()->ConnectLogger([](auto&& PH1, auto&& PH2, auto&& PH3, auto&& PH4, auto&& PH5) { return CAlbikarLogger::logCallBack(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2), std::forward<decltype(PH3)>(PH3), std::forward<decltype(PH4)>(PH4), std::forward<decltype(PH5)>(PH5)); });
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