#include "HierarchyWindow.hpp"
#include "AlbikarGui.hpp"
#include "Preferences.hpp"
#include "Profiler.hpp"

auto CHierarchyWindow::Render() -> void
{
    ALB_PROFILE_SCOPE("CHierarchyWindow::Render");
    if (ImGui::Begin(WINDOW_HIERARCHY, nullptr, dockFloatWindow)) {
        static char serachObject[128] = "";
        AlbikarGui::SearchWidget("##HierarchySearch", "Serach Object", serachObject);
        ImGui::Separator();
        RenderHierarchy();
    }
    ImGui::End();
}

auto CHierarchyWindow::RenderHierarchy() -> void
{
    static ImGuiTableFlags flags = ImGuiTableFlags_None;
    if (ImGui::BeginChild("##hierarhy", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar)) {
        // Using those as a base value to create width/height that are factor of the size of our font
        const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
        // const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
        if (ImGui::BeginTable("3ways", 2, flags)) {
            // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
            ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_NoHide);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 9.0f);
            ImGui::TableHeadersRow();

            // Simple storage to output a dummy file-system.
            struct MyTreeNode {
                const char* Name;
                const char* Type;
                int Size;
                int ChildIdx;
                int ChildCount;
                static void DisplayNode(const MyTreeNode* node, const MyTreeNode* all_nodes)
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    const bool is_folder = (node->ChildCount > 0);
                    if (is_folder) {
                        bool open = ImGui::TreeNodeEx(node->Name, ImGuiTreeNodeFlags_SpanFullWidth);
                        ImGui::TableNextColumn();
                        ImGui::TextUnformatted(node->Type);
                        if (open) {
                            for (int child_n = 0; child_n < node->ChildCount; child_n++)
                                DisplayNode(&all_nodes[node->ChildIdx + child_n], all_nodes);
                            ImGui::TreePop();
                        }
                    } else {
                        ImGui::TreeNodeEx(node->Name, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth);
                        ImGui::TableNextColumn();
                        ImGui::TextUnformatted(node->Type);
                    }
                }
            };
            static const MyTreeNode nodes[] = {
                { "Root", "Folder", -1, 1, 3 }, // 0
                { "Background", "Folder", -1, 4, 2 }, // 1
                { "Game World", "Folder", -1, 6, 3 }, // 2
                { "HUD", "Folder", -1, 6, 1 }, // 2
                { "File1_a.wav", "Audio file", 123000, -1, -1 }, // 4
                { "File1_b.wav", "Audio file", 456000, -1, -1 }, // 5
                { "Image001.png", "Image file", 203128, -1, -1 }, // 6
                { "Copy of Image001.png", "Image file", 203256, -1, -1 }, // 7
                { "Copy of Image001 (Final2).png", "Image file", 203512, -1, -1 }, // 8
                { "Copy of Image001 (Final2).png", "Image file", 203512, -1, -1 }, // 8
            };

            MyTreeNode::DisplayNode(&nodes[0], nodes);

            ImGui::EndTable();
        }
        ImGui::EndChild();
    }
}