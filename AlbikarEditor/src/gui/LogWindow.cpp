#include "LogWindow.hpp"
#include "Logger.hpp"
#include "Preferences.hpp"
#include "Profiler.hpp"
#pragma warning(disable : 4996)

CLogWindow::CLogWindow()
    : m_bAutoScroll(true)
    , m_bShowFile(true)
    , m_bShowFunction(true)
    , m_bSaveToFile(false)
    , m_bCheckWarn(true)
    , m_bCheckCritical(true)
    , m_bCheckInfo(true)
    , m_bCheckError(true)
    , m_bCheckLine(true)
    , m_iComboCurrentItem(0)
{
    LOG_ERROR("Debug error log for test1");
    LOG_WARN("Debug warning log for test1");
    LOG_CRITICAL("Debug critical log for test1");
    LOG_INFO("Debug info log for test1");
    LOG_LINE();
    LOG_ERROR("Debug error log for test2");
    LOG_WARN("Debug warning log for test2");
    LOG_CRITICAL("Debug critical log for test2");
    LOG_INFO("Debug info log for test2");
    LOG_LINE();
}

CLogWindow::~CLogWindow()
{
    if (m_bSaveToFile) {
        SaveToFile();
    }
}

auto CLogWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("CLogWindow::Render");
    static bool autoScroleActive = true;

    if (ImGui::Begin(WINDOW_LOG, nullptr, dockFloatWindow)) {

        // Options menu
        if (ImGui::BeginPopup("Options")) {
            ImGui::Checkbox("Save To File", &m_bSaveToFile);
            ImGui::Checkbox("Auto-scroll", &m_bAutoScroll);
            ImGui::Checkbox("Show File", &m_bShowFile);
            ImGui::Checkbox("Show Function Name", &m_bShowFunction);
            if (ImGui::BeginMenu("Show")) {
                ImGui::Checkbox("Warn", &m_bCheckWarn);
                ImGui::Checkbox("Critical", &m_bCheckCritical);
                ImGui::Checkbox("Info", &m_bCheckInfo);
                ImGui::Checkbox("Error", &m_bCheckError);
                ImGui::Checkbox("Line", &m_bCheckLine);
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }

        // Options, Filter
        if (ImGui::Button("Options")) {
            ImGui::OpenPopup("Options");
        }

        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, COLOR_ORANGE_DARK);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, COLOR_ORANGE_DARK);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, COLOR_ORANGE_DARK);
        if (ImGui::Button("Clear")) {
            CAlbikarLogger::m_AllLog.clear();
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGuiIO& io = ImGui::GetIO();
        ImTextureID my_tex_id = io.Fonts->TexID;
        if (ImGui::ImageButton("333333333333333", my_tex_id, ImVec2(23, 23), ImVec2(0, 0), ImVec2(23, 23), ImColor(0, 0, 0, 255))) {
        }
        ImGui::SameLine();
        if (ImGui::ImageButton("222222222222222222", my_tex_id, ImVec2(23, 23), ImVec2(0, 0), ImVec2(23, 23), ImColor(0, 0, 0, 255))) {
        }
        ImGui::SameLine();
        if (ImGui::ImageButton("1111111", my_tex_id, ImVec2(23, 23), ImVec2(0, 0), ImVec2(23, 23), ImColor(0, 0, 0, 255))) {
        }
        ImGui::PopStyleVar();

        ImGui::SameLine();
        ImGui::Text("Filter:");
        ImGui::SameLine();
        m_sFilter.Draw("##Filter", 160.0F);
        ImGui::SameLine();

        // Checkboxs
        ImGui::SameLine();
        ImGui::Text("Log:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(140.0F);
        ImGui::Combo("##Log", &m_iComboCurrentItem, "All\0Albikar Engine\0Albikar application\0");

        // Log text
        ImGui::Separator();
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar)) {

            for (const auto& element : CAlbikarLogger::m_AllLog) {
                PrintLog(element);
            }

            if ((autoScroleActive != m_bAutoScroll && m_bAutoScroll) || ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                ImGui::SetScrollHereY(1.0F);
            }

            autoScroleActive = m_bAutoScroll;
        }
        ImGui::EndChild();

        ImGui::PopStyleVar();
    }
    ImGui::End();
}

auto CLogWindow::PrintLog(const CLogInfo& log) -> void
{
    std::string toDisplay;

    if ((log.m_bLogFromAlbikar && m_iComboCurrentItem == 1) || (!log.m_bLogFromAlbikar && m_iComboCurrentItem == 2)) {
        return;
    }

    toDisplay += std::to_string(log.m_uiNumber) + " ";

    switch (log.m_eMode) {
    case CLogInfo::LOG_MODE::CRITICAL:
        if (!m_bCheckCritical) {
            return;
        }
        ImGui::PushStyleColor(ImGuiCol_Text, COLOR_RED);
        toDisplay += "[CRIT] ";
        break;
    case CLogInfo::LOG_MODE::WARN:
        if (!m_bCheckWarn) {
            return;
        }
        ImGui::PushStyleColor(ImGuiCol_Text, COLOR_YELLOW);
        toDisplay += "[WARN] ";
        break;
    case CLogInfo::LOG_MODE::INFO:
        if (!m_bCheckInfo) {
            return;
        }
        ImGui::PushStyleColor(ImGuiCol_Text, COLOR_WHITE);
        toDisplay += "[INFO] ";
        break;
    case CLogInfo::LOG_MODE::ERROR:
        if (!m_bCheckError) {
            return;
        }
        ImGui::PushStyleColor(ImGuiCol_Text, COLOR_RED);
        toDisplay += "[ERROR] ";
        break;
    case CLogInfo::LOG_MODE::LINE:
        if (!m_bCheckLine) {
            return;
        }
        ImGui::PushStyleColor(ImGuiCol_Text, COLOR_WHITE);
        toDisplay += "[LINE] ";
        break;
    default:
        return;
    }

    if (m_bShowFile) {
        toDisplay += log.m_sFileName + ":" + std::to_string(log.m_uiFileLine) + " ";
    }
    if (m_bShowFunction) {
        toDisplay += log.m_sFunctionName + " ";
    }
    toDisplay += log.m_sLogOutput;

    if (m_sFilter.IsActive()) {
        std::string filtr(m_sFilter.InputBuf);
        if (toDisplay.find(filtr) != std::string::npos) {
            ImGui::TextUnformatted(toDisplay.c_str());
        }
    } else {
        ImGui::TextUnformatted(toDisplay.c_str());
    }

    ImGui::PopStyleColor();
}

auto CLogWindow::SaveToFile() -> void
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::string logName = "Log-" + std::to_string(now->tm_year + 1900) + "-" + std::to_string(now->tm_mon + 1) + "-" + std::to_string(now->tm_mday) + "-" + std::to_string(now->tm_hour) + "-" + std::to_string(now->tm_min) + "-" + std::to_string(now->tm_sec) + ".txt";
    LOG_INFO("Save to file ", logName);
    std::ofstream outfile(logName);
    for (const auto& element : CAlbikarLogger::m_AllLog) {
        std::string saveLine;
        saveLine += std::to_string(element.m_uiNumber) + " ";
        switch (element.m_eMode) {
        case CLogInfo::LOG_MODE::CRITICAL:
            saveLine += "[CRIT] ";
            break;
        case CLogInfo::LOG_MODE::WARN:
            saveLine += "[WARN] ";
            break;
        case CLogInfo::LOG_MODE::INFO:
            saveLine += "[INFO] ";
            break;
        case CLogInfo::LOG_MODE::ERROR:
            saveLine += "[ERROR] ";
            break;
        case CLogInfo::LOG_MODE::LINE:
            saveLine += "[LINE] ";
            break;
        default:
            break;
        }
        saveLine += element.m_sFileName + ":" + std::to_string(element.m_uiFileLine) + " ";
        saveLine += element.m_sFunctionName + " ";
        saveLine += element.m_sLogOutput;
        outfile << saveLine << "\n";
    }
    outfile.close();
}