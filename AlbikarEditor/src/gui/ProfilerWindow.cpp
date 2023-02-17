#include "ProfilerWindow.hpp"
#include "Preferences.hpp"
#include "Profiler.hpp"

auto CProfilerWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("CProfilerWindow::Render");
    if (ImGui::Begin(WINDOW_PROFILER, nullptr, dockFloatWindow)) {
        static bool profiler = true;
        ImGui::Checkbox("Enable Profiler", &profiler);

        static time_t start = time(nullptr);
        double seconds_since_start = difftime(time(nullptr), start);
        static const float stop1sec = 1.0F;
        static int frames = 0;
        static int frameLast = 1;
        frames++;
        if (seconds_since_start >= stop1sec) {
            start = time(nullptr);
            CInstrumentor::Get().GetAndClearLocalResult(m_vLocalResult);
            frameLast = frames;
            frames = 0;
        }

        if (profiler) {
            ImGui::SameLine();
            ImGui::Text("Albikar: %.1f(fps)", ImGui::GetIO().Framerate);
            ImGui::SameLine();
            ImGui::Text("    Albikar Engine: %.1f(fps)", ImGui::GetIO().Framerate);

            ImGui::Separator();
            static ImGuiTableFlags flags = ImGuiTableFlags_None;
            if (ImGui::BeginChild("##scrollingProfilerTab", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar)) {
                if (ImGui::BeginTable("##ProfilerTable", 5, flags)) {
                    ImGui::TableSetupColumn("Action");
                    ImGui::TableSetupColumn("Total duration", ImGuiTableColumnFlags_WidthFixed, 80.0F);
                    ImGui::TableSetupColumn("Frame duration", ImGuiTableColumnFlags_WidthFixed, 90.0F);
                    ImGui::TableSetupColumn("Frame load", ImGuiTableColumnFlags_WidthFixed, 65.0F);
                    ImGui::TableSetupColumn("Total calls", ImGuiTableColumnFlags_WidthFixed, 70.0F);
                    ImGui::TableHeadersRow();

                    // Render Rows
                    for (auto& i : m_vLocalResult) {
                        ImGui::TableNextRow();

                        ImGui::TableSetColumnIndex(0);
                        std::string action = i.Name;
                        ImGui::TextUnformatted(action.c_str());

                        ImGui::TableSetColumnIndex(1);
                        std::string totalDuration = std::to_string(static_cast<double>(i.Duration));
                        ImGui::TextUnformatted(totalDuration.c_str());

                        ImGui::TableSetColumnIndex(2);
                        std::string frameDuration = std::to_string(static_cast<double>(i.Duration / i.calls));
                        ImGui::TextUnformatted(frameDuration.c_str());

                        ImGui::TableSetColumnIndex(3);
                        std::string frameLoad = std::to_string(i.calls / frameLast);
                        ImGui::TextUnformatted(frameLoad.c_str());

                        ImGui::TableSetColumnIndex(4);
                        std::string calls = std::to_string(i.calls);
                        ImGui::TextUnformatted(calls.c_str());
                    }
                    ImGui::EndTable();
                }
            }
            ImGui::EndChild();
        }
    }
    ImGui::End();
}